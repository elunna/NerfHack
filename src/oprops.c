/* NetHack 5.0	oprops.c	$NHDT-Date$  $NHDT-Branch: NetHack-5.0 $:$NHDT-Revision$ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Erik Lunna, 2026. */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * This file contains the "oprops" (object property) system: granting
 * random flame/frost/stealth/etc. properties to generated items
 * (create_oprop()), querying and (de)activating them, and rendering
 * their names. It was split out of artifact.c, which retains the
 * artifact-specific mechanics that also consult an object's oprops.
 */

#include "hack.h"

staticfn boolean is_redundant_prop(struct obj *, int);
staticfn long inherent_oprop_flag(struct obj *);

/* Create an item with special properties, or grant the item those properties */
struct obj *
create_oprop(struct obj *obj, boolean allow_detrimental)
{
    struct obj *otmp = obj;
    int i, j;

    if (!otmp) {
        int type = 0, skill = P_NONE,
            candidates[128], ccount,
            threshold = P_EXPERT;
        /* Find an appropriate type of weapon */
        while (threshold > P_UNSKILLED) {
            ccount = 0;
            for (i = P_FIRST_WEAPON; i < P_LAST_WEAPON; i++) {
                if (P_MAX_SKILL(i) >= max(threshold, P_BASIC)
                    && P_SKILL(i) >= threshold)
                    candidates[ccount++] = i;
                if (ccount >= 128)
                    break;
            }
            if (ccount == 0) {
                threshold--;
                continue;
            }
            skill = candidates[rn2(ccount)];
            ccount = 0;
            for (i = ARROW; i <= CROSSBOW; i++) {
                if (abs(objects[i].oc_skill) == skill)
                    candidates[ccount++] = i;
                if (ccount == 128)
                    break;
            }
            if (!ccount) {
                impossible("found no weapons for skill %d?", skill);
                threshold--;
                continue;
            }
            type = candidates[rn2(ccount)];
            break;
        }
        /* Now make one, if we can */
        if (type != 0)
            otmp = mksobj(type, TRUE, FALSE);
        else
            otmp = mkobj(WEAPON_CLASS, FALSE);
    }

    if (!may_generate_with_oprops(otmp))
        return otmp;

    /* already magical items obtain properties a tenth as often
     * - make an exception for rings b/c they are already rare af
     */
    if (objects[otmp->otyp].oc_magic
            && otmp->oclass != RING_CLASS && rn2(10))
        return otmp;

    /* Don't allow more than 1 oprop per item;
     * this is not meant as a nerf, but to manage the handling of oprops.
     * I'm not sure if more than one oprop on a weapon is handled correctly
     * and for the rarity I don't think it's worth the effort. It would also
     * result in really clunky descriptions...
     */
    while (!otmp->oprops) {
        i = rn2(MAX_ITEM_PROPS);
        j = 1 << i; /* pick an object property */

        if (otmp->oprops & j) /* Same oprop already exists */
            continue;

        if (j & ITEM_BAD_PROPS && !allow_detrimental)
            continue;

        /* Launchers can have defensive properties, but not offensive;
         * rage/hexing/nulling also don't make sense for launchers.
         */
        if (is_launcher(otmp) && j & (ONLY_WEP_PROPS | ITEM_RES_PROPS))
            continue;
        if ((is_ammo(otmp) || is_missile(otmp))
            && j & (ITEM_GOOD_PROPS | ITEM_BAD_PROPS
                     | ONLY_ARM_PROPS | ITEM_HEXING))
            continue;
        /* check for restrictions */
        if ((otmp->oclass == WEAPON_CLASS || is_weptool(otmp))
            && j & ONLY_ARM_PROPS)
            continue;

        if ((otmp->oclass == ARMOR_CLASS || otmp->oclass == RING_CLASS)
              && j & ONLY_WEP_PROPS)
            continue;

        if ((otmp->oprops & ITEM_RES_PROPS) && j & ITEM_RES_PROPS)
            continue; /* these are mutually exclusive */

        if (is_redundant_prop(otmp, j))
            continue;

        otmp->oprops |= j;
    }

    /* Fix it up as necessary */
    if (otmp->oprops && !(otmp->oprops & ITEM_BAD_PROPS)) {
        if (!rn2(8)) {
            blessorcurse(otmp, 8);
            if (otmp->cursed) {
                if (!otmp->spe)
                    otmp->spe = -rne(3);
                else
                    otmp->spe -= rnd(2); /* Item already exists? */
            } else {
                if (!otmp->spe)
                    otmp->spe = rne(3);
                else if (otmp->spe <= 3)
                    otmp->spe += rnd(2);
            }
        }
    }

    if (otmp->oprops & ITEM_BAD_PROPS) {
        if (!otmp->cursed)
            curse(otmp);
        if (!otmp->spe)
            otmp->spe = -rne(3);
        else
            otmp->spe -= rnd(2);
    }
    return otmp;
}

/* the oprop flag corresponding to otmp's own inherent oc_oprop (its object
 * type's built-in invocable/worn property, e.g. FIRE_RES for a ring of
 * fire resistance), via prop_lookup -- or 0 if oc_oprop doesn't
 * correspond to any oprop. */
staticfn long
inherent_oprop_flag(struct obj *otmp)
{
    int i;

    for (i = 0; i < MAX_ITEM_PROPS; i++)
        if (objects[otmp->otyp].oc_oprop == prop_lookup[i].prop)
            return prop_lookup[i].flag;
    return 0L;
}

staticfn boolean
is_redundant_prop(struct obj *otmp, int prop)
{
    /* Alchemy smock is the king of exceptions */
    if (otmp->otyp == ALCHEMY_SMOCK && (prop & (ITEM_ACID | ITEM_VENOM)))
        return TRUE;
    if (otmp->otyp == RIN_CARRYING && (prop & (ITEM_CARRY | ITEM_BURDEN)))
        return TRUE;

    return (inherent_oprop_flag(otmp) & prop) != 0;
}

const struct PropTypes prop_lookup[MAX_ITEM_PROPS] = {
    { FIRE_RES,          ITEM_FLAME },
    { COLD_RES,          ITEM_FROST },
    { SHOCK_RES,         ITEM_SHOCK },
    { POISON_RES,        ITEM_VENOM },
    { ACID_RES,          ITEM_ACID },
    { DRAIN_RES,         ITEM_DRAIN },
    { DISINT_RES,        ITEM_INTEGRITY },
    { SLEEP_RES,         ITEM_SLEEP },
    { SEARCHING,         ITEM_VIGIL },
    { SEE_INVIS,         ITEM_INSIGHT },
    { FUMBLING,          ITEM_FUMBLE },
    { STEALTH,           ITEM_STEALTH },
    { HUNGER,            ITEM_HUNGER },
    { WARNING,           ITEM_WARN },
    { SICK_RES,          ITEM_FILTH },
    { STABLE,            ITEM_BURDEN },
    { INFRAVISION,       ITEM_DANGER },
    { AGGRAVATE_MONSTER, ITEM_STENCH },

    { ANTIMAGIC,         ITEM_MR },
};

/* does otmp's oprops confer a weapon attack of the given damage type? */
boolean
oprop_attacks(int adtyp, struct obj *otmp)
{
    if (!otmp->oprops
        || !(otmp->oclass == WEAPON_CLASS || is_weptool(otmp)
             || (uarms && otmp == uarms)))
        return FALSE;

    if (adtyp == AD_FIRE && (otmp->oprops & ITEM_FLAME))
        return TRUE;
    if (adtyp == AD_COLD && (otmp->oprops & ITEM_FROST))
        return TRUE;
    if (adtyp == AD_ELEC && (otmp->oprops & ITEM_SHOCK))
        return TRUE;
    if (adtyp == AD_DRST && (otmp->oprops & ITEM_VENOM))
        return TRUE;
    if (adtyp == AD_ACID && (otmp->oprops & ITEM_ACID))
        return TRUE;
    if (adtyp == AD_DRLI && (otmp->oprops & ITEM_DRAIN))
        return TRUE;
    if (adtyp == AD_SLEE && (otmp->oprops & ITEM_SLEEP))
        return TRUE;
    if (adtyp == AD_DISE && (otmp->oprops & ITEM_FILTH))
        return TRUE;
    if (adtyp == AD_MAGM && (otmp->oprops & ITEM_MR))
        return TRUE;
    if (adtyp == AD_DISN && (otmp->oprops & ITEM_INTEGRITY))
        return TRUE;

    return FALSE;
}

/* Find properties the object has inherently and remove the
 * redundant ones. The purpose of this function is to prevent
 * items like "a ring of fire resistance of fire". */
long
rm_redundant_oprops(struct obj *otmp, long objprops)
{
    /* Alchemy smock is the king of exceptions */
    if (otmp->otyp == ALCHEMY_SMOCK)
        objprops &= ~(ITEM_ACID | ITEM_VENOM);
    if (otmp->otyp == RIN_CARRYING)
        objprops &= ~(ITEM_CARRY | ITEM_BURDEN);
    /* a ring of sleeping causes sleep rather than resisting it, so its
     * oc_oprop (SLEEPY) doesn't correspond to any oprop via prop_lookup;
     * suppress ITEM_SLEEP here as a thematic exception rather than the
     * literal redundancy the general case below covers */
    if (otmp->otyp == RIN_SLEEPING)
        objprops &= ~ITEM_SLEEP;

    return objprops & ~inherent_oprop_flag(otmp);
}

/* Filter a candidate set of wished-for oprops (see parse_oprop_wishname())
 * down to what's actually valid for otmp: mutually exclusive resistances,
 * launcher/ammo and weapon-vs-armor/ring class restrictions, redundancy
 * against otmp's own inherent properties, and (via may_generate_with_oprops())
 * exclusion of artifacts, unique objects, dragon armor, and anything that
 * isn't a weapon, weapon-tool, armor, or ring. Wishing for oprops is a
 * wizard-mode-only feature; see readobjnam(). */
long
filter_wish_oprops(struct obj *otmp, long objprops)
{
    if (!objprops || !may_generate_with_oprops(otmp))
        return 0L;

    if (objprops & ITEM_FLAME)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_FLAME);
    else if (objprops & ITEM_FROST)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_FROST);
    else if (objprops & ITEM_SHOCK)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_SHOCK);
    else if (objprops & ITEM_VENOM)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_VENOM);
    else if (objprops & ITEM_ACID)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_ACID);
    else if (objprops & ITEM_DRAIN)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_DRAIN);
    else if (objprops & ITEM_INTEGRITY)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_INTEGRITY);
    else if (objprops & ITEM_SLEEP)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_SLEEP);
    else if (objprops & ITEM_VIGIL)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_VIGIL);
    else if (objprops & ITEM_FILTH)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_FILTH);
    else if (objprops & ITEM_RAGE)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_RAGE);
    else if (objprops & ITEM_MR)
        objprops &= ~(ITEM_RES_PROPS & ~ITEM_MR);

    if (objects[otmp->otyp].oc_magic)
        objprops &= ~ITEM_PROP_MASK;

    /* Launchers can have defensive properties, but not offensive;
     * rage/hexing/nulling also don't make sense for launchers (matches
     * create_oprop()'s restriction for randomly-generated items) */
    if (is_launcher(otmp))
        objprops &= ~(ONLY_WEP_PROPS | ITEM_RES_PROPS);
    else if (is_ammo(otmp) || is_missile(otmp))
        objprops &= ~(ITEM_GOOD_PROPS | ITEM_BAD_PROPS | ONLY_ARM_PROPS);
    else if (otmp->oclass == WEAPON_CLASS || is_weptool(otmp))
        objprops &= ~ONLY_ARM_PROPS;

    if (otmp->oclass == ARMOR_CLASS || otmp->oclass == RING_CLASS)
        objprops &= ~ONLY_WEP_PROPS;

    /* Burden doesn't really affect ring weight much */
    if (otmp->oclass == RING_CLASS)
        objprops &= ~ITEM_BURDEN;

    return rm_redundant_oprops(otmp, objprops);
}

/* display name for each oprop; rsc_name is the "passive resistance" wording
 * used when weapon is FALSE, or NULL if the prop reads the same either way */
struct oprop_name {
    long flag;
    const char *wpn_name;
    const char *rsc_name;
};

static const struct oprop_name oprop_names[] = {
    { ITEM_FLAME,     " {flame}",        " {fire resistance}" },
    { ITEM_FROST,     " {frost}",        " {cold resistance}" },
    { ITEM_SHOCK,     " {shock}",        " {shock resistance}" },
    { ITEM_VENOM,     " {venom}",        " {poison resistance}" },
    { ITEM_ACID,      " {acid}",         " {acid resistance}" },
    { ITEM_DRAIN,     " {draining}",     " {drain resistance}" },
    { ITEM_SLEEP,     " {slumber}",      " {alertness}" },
    { ITEM_PEACE,     " {peace}",        NULL },
    { ITEM_VIGIL,     " {vigilance}",    NULL },
    { ITEM_STEALTH,   " {stealth}",      NULL },
    { ITEM_FUMBLE,    " {fumbling}",     NULL },
    { ITEM_HUNGER,    " {hunger}",       NULL },
    { ITEM_WARN,      " {warning}",      NULL },
    { ITEM_FILTH,     " {filth}",        " {health}" },
    { ITEM_INSIGHT,   " {insight}",      NULL },
    { ITEM_CHA,       " {charisma}",     NULL },
    { ITEM_BURDEN,    " {burden}",       NULL },
    { ITEM_RAGE,      " {rage}",         NULL },
    { ITEM_DANGER,    " {danger}",       NULL },
    { ITEM_STENCH,    " {stench}",       NULL },
    { ITEM_SUSTAIN,   " {preservation}", NULL },
    { ITEM_CARRY,     " {carrying}",     NULL },
    { ITEM_HEXING,    " {hexing}",       NULL },
    { ITEM_MR,        " {antimagic}",    NULL },
    { ITEM_NULLING,   " {nulling}",      NULL },
    { ITEM_INTEGRITY, " {integrity}",    NULL },
};

void
propnames(char *buf, long props,
          boolean weapon, boolean has_of)
{
    char of[6];
    int i;

    if (props)
        Strcpy(of, (has_of) ? " and" : " of");
    for (i = 0; i < SIZE(oprop_names); i++) {
        if (!(props & oprop_names[i].flag))
            continue;
        Strcat(buf, of);
        Strcat(buf, (!weapon && oprop_names[i].rsc_name)
                        ? oprop_names[i].rsc_name : oprop_names[i].wpn_name);
        Strcpy(of, " and");
    }
}

/* a wish-string oprop suffix; the entry only matches if bp does NOT start
 * with not_prefix (e.g. "ring of stealth" names a real, distinct item
 * rather than an oprop), or unconditionally if not_prefix is NULL */
struct oprop_wishname {
    const char *phrase;
    long flag;
    const char *not_prefix;
};

static const struct oprop_wishname oprop_wishnames[] = {
    { " of flame",        ITEM_FLAME,     NULL },
    { " of frost",        ITEM_FROST,     NULL },
    { " of slumber",      ITEM_SLEEP,     NULL },
    { " of shock",        ITEM_SHOCK,     NULL },
    { " of venom",        ITEM_VENOM,     NULL },
    { " of acid",         ITEM_ACID,      "potion" },
    { " of decay",        ITEM_DRAIN,     NULL },
    { " of integrity",    ITEM_INTEGRITY, NULL },
    { " of filth",        ITEM_FILTH,     NULL },
    { " of peace",        ITEM_PEACE,     NULL },
    { " of vigilance",    ITEM_VIGIL,     "ring" },
    { " of stealth",      ITEM_STEALTH,   "ring" },
    { " of warning",      ITEM_WARN,      "ring" },
    { " of insight",      ITEM_INSIGHT,   NULL },
    { " of charisma",     ITEM_CHA,       NULL },
    { " of fumbling",     ITEM_FUMBLE,    NULL },
    { " of hunger",       ITEM_HUNGER,    "ring" },
    { " of burden",       ITEM_BURDEN,    NULL },
    { " of rage",         ITEM_RAGE,      NULL },
    { " of danger",       ITEM_DANGER,    NULL },
    { " of stench",       ITEM_STENCH,    NULL },
    { " of sleep",        ITEM_SLEEP,     "wand" },
    { " of preservation", ITEM_SUSTAIN,   NULL },
    { " of carrying",     ITEM_CARRY,     NULL },
    { " of hexing",       ITEM_HEXING,    NULL },
    { " of antimagic",    ITEM_MR,        NULL },
    { " of nulling",      ITEM_NULLING,   NULL },
};

/* Parse a wish/name string's trailing " of <propname>" oprop suffix out
 * of bp, in place -- like the " named "/" called "/" labeled " parsing
 * readobjnam_postparse1() does elsewhere, the matched text is truncated
 * from bp so the remaining name can still be looked up normally. Returns
 * the matching ITEM_* flag, or 0 if nothing matched. */
long
parse_oprop_wishname(char *bp)
{
    char *p;
    int i;

    for (i = 0; i < SIZE(oprop_wishnames); i++) {
        const struct oprop_wishname *e = &oprop_wishnames[i];

        if ((p = strstri(bp, e->phrase)) != 0
            && (!e->not_prefix
                || strncmpi(bp, e->not_prefix, strlen(e->not_prefix)))) {
            *p = 0;
            return e->flag;
        }
    }
    return 0L;
}

struct obj *
using_oprop(long oprop)
{
    struct obj *otmp;
    for (otmp = gi.invent; otmp; otmp = otmp->nobj) {
        if (otmp->oprops & oprop && is_worn(otmp))
            return otmp;
        if (oprop == ITEM_STENCH
            && (otmp->oprops & ITEM_STENCH || otmp->otyp == FOULSTONE))
            return otmp;
    }
    return (struct obj *) 0;
}

/* Turn on otmp's oprops in the given worn/wielded slot (mask is one of
 * the W_* owornmask bits). Weapons and weapon-tools skip the
 * resistance-granting props (ITEM_FLAME et al, plus the armor-only
 * ITEM_MR/ITEM_SUSTAIN): a weapon's elemental oprops manifest as an
 * attack instead, checked live by oprop_attacks() rather than toggled
 * here, and it can't be granted the armor-only ones at all (see
 * ONLY_ARM_PROPS in oprops.h). Everything else (peace, vigilance,
 * stealth, warning, etc.) applies the same way whether otmp is being
 * worn or wielded. */
void
oprops_on(struct obj *otmp, long mask)
{
    long props = otmp->oprops;

    if (otmp->oclass != WEAPON_CLASS && !is_weptool(otmp)) {
        if (props & ITEM_FLAME)
            EFire_resistance |= mask;
        if (props & ITEM_FROST)
            ECold_resistance |= mask;
        if (props & ITEM_SHOCK)
            EShock_resistance |= mask;
        if (props & ITEM_ACID)
            EAcid_resistance |= mask;
        if (props & ITEM_DRAIN)
            EDrain_resistance |= mask;
        if (props & ITEM_INTEGRITY)
            EDisint_resistance |= mask;
        if (props & ITEM_VENOM)
            EPoison_resistance |= mask;
        if (props & ITEM_SLEEP)
            ESleep_resistance |= mask;
        if (props & ITEM_FILTH)
            ESick_resistance |= mask;
        if (props & ITEM_SUSTAIN)
            Preservation |= mask;
        if (props & ITEM_MR)
            EAntimagic |= mask;
    }

    if (props & ITEM_PEACE) {
        BAggravate_monster |= mask;
    }
    if (props & ITEM_VIGIL)
        ESearching |= mask;
    if (props & ITEM_STEALTH) {
        EStealth |= mask;
        if (maybe_polyd(is_giant(gy.youmonst.data), Race_if(PM_GIANT))) {
            pline("This %s will not silence someone %s.",
                  xname(otmp), rn2(2) ? "as large as you" : "of your stature");
            EStealth &= ~mask;
        } else if (Stomping) {
            pline("This %s will not silence your stomping!", xname(otmp));
            EStealth &= ~mask;
        } else
            toggle_stealth(otmp, (EStealth & ~mask), TRUE);
    }
    if (props & ITEM_INSIGHT) {
        ESee_invisible |= mask;
        toggle_seeinv(otmp, (ESee_invisible & ~mask), TRUE);
    }
    if (props & ITEM_FUMBLE) {
        if (!EFumbling && !(HFumbling & ~TIMEOUT))
            incr_itimeout(&HFumbling, rnd(20));
        EFumbling |= mask;
    }
    if (props & ITEM_HUNGER)
        EHunger |= mask;
    if (props & ITEM_WARN) {
        EWarning |= mask;
        see_monsters();
    }
    if (props & ITEM_CHA) {
        changes_stat();
    }
    if (props & ITEM_BURDEN)
        EStable |= mask;
    if (props & ITEM_DANGER)
        EInfravision |= mask;
    if (props & ITEM_STENCH)
        EAggravate_monster |= mask;
}

/* counterpart of oprops_on() */
void
oprops_off(struct obj *otmp, long mask)
{
    long props = otmp->oprops;

    if (otmp->oclass != WEAPON_CLASS && !is_weptool(otmp)) {
        if (props & ITEM_FLAME)
            EFire_resistance &= ~mask;
        if (props & ITEM_FROST)
            ECold_resistance &= ~mask;
        if (props & ITEM_SHOCK)
            EShock_resistance &= ~mask;
        if (props & ITEM_VENOM)
            EPoison_resistance &= ~mask;
        if (props & ITEM_ACID)
            EAcid_resistance &= ~mask;
        if (props & ITEM_DRAIN)
            EDrain_resistance &= ~mask;
        if (props & ITEM_INTEGRITY)
            EDisint_resistance &= ~mask;
        if (props & ITEM_SLEEP)
            ESleep_resistance &= ~mask;
        if (props & ITEM_FILTH)
            ESick_resistance &= ~mask;
        if (props & ITEM_SUSTAIN)
            Preservation &= ~mask;
        if (props & ITEM_MR)
            EAntimagic &= ~mask;
    }

    if (props & ITEM_PEACE) {
        BAggravate_monster &= ~mask;
    }
    if (props & ITEM_VIGIL)
        ESearching &= ~mask;
    if (props & ITEM_INSIGHT) {
        ESee_invisible &= ~mask;
        toggle_seeinv(otmp, (ESee_invisible & ~mask), FALSE);
    }
    if (props & ITEM_STEALTH) {
        EStealth &= ~mask;
        toggle_stealth(otmp, (EStealth & ~mask), FALSE);
    }
    if (props & ITEM_FUMBLE) {
        EFumbling &= ~mask;
    	if (!EFumbling && !(HFumbling & ~TIMEOUT))
        	HFumbling = EFumbling = 0L;
    }
    if (props & ITEM_HUNGER)
        EHunger &= ~mask;
    if (props & ITEM_WARN) {
        EWarning &= ~mask;
        see_monsters();
    }
     if (props & ITEM_CHA) {
        changes_stat();
    }
    if (props & ITEM_BURDEN)
        EStable &= ~mask;
    if (props & ITEM_DANGER)
        EInfravision &= ~mask;
    if (props & ITEM_STENCH)
        EAggravate_monster &= ~mask;
}

/** Returns the bonus available for wearing/wielding
  * items with the specified property
  **/
schar
calc_prop_bonus(long prop)
{
    struct obj *otmp = using_oprop(prop);
    schar bonus = 0;

    /* TODO: Handle having 2 or more items with the same prop and different BUC... */
    for (otmp = gi.invent; otmp; otmp = otmp->nobj)
        if (otmp->oprops & prop && otmp->owornmask) {
            if (otmp->cursed)
                bonus -= (schar) 2;
            else if (otmp->blessed)
                bonus += (schar) 2;
            else
                bonus += (schar) 1;
    }
    return bonus;
}

/* Refresh the botl/inventory display after an ITEM_CHA oprop (the only
 * stat-affecting oprop) is toggled on or off, so the charisma-derived
 * bonus from calc_prop_bonus() shows up immediately. */
void
changes_stat(void)
{
    disp.botl = 1;
    update_inventory();
}
