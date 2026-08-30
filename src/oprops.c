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

boolean
is_redundant_prop(struct obj *otmp, int prop)
{
    int i;

    /* Alchemy smock is the king of exceptions */
    if (otmp->otyp == ALCHEMY_SMOCK && (prop & (ITEM_ACID | ITEM_VENOM)))
        return TRUE;
    if (otmp->otyp == RIN_CARRYING && prop & (ITEM_CARRY | ITEM_BURDEN))
        return TRUE;

    for (i = 0; i < MAX_ITEM_PROPS; i++) {
        if (objects[otmp->otyp].oc_oprop
                == prop_lookup[i].prop && (prop & prop_lookup[i].flag))
            return TRUE;
    }
    return FALSE;
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

boolean obj_has_prop(struct obj *obj, int which)
{
    boolean is_non_weapon = (obj->oclass != WEAPON_CLASS && !is_weptool(obj));
    int i;

    if (objects[obj->otyp].oc_oprop == which)
        return TRUE;

    if (!obj->oprops)
        return FALSE;

    for (i = 0; i < MAX_ITEM_PROPS; i++) {
        if (prop_lookup[i].prop == which) {
            return !!(is_non_weapon && (obj->oprops & prop_lookup[i].flag));
        }
    }
    return FALSE;
}

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
 * items like "a ring of fire resistance of fire".
 *
 * Maybe we can even combine with is_redundant_prop... */
long
rm_redundant_oprops(struct obj *otmp, long objprops)
{
    /* Going in order of objects.h */
    if (otmp->otyp == HELM_OF_CAUTION)
        objprops &= ~ITEM_WARN;
    if (otmp->otyp == ELVEN_CLOAK)
        objprops &= ~ITEM_STEALTH;
    if (otmp->otyp == ALCHEMY_SMOCK)
        objprops &= ~(ITEM_ACID | ITEM_VENOM);
    if (otmp->otyp == CLOAK_OF_MAGIC_RESISTANCE)
        objprops &= ~ITEM_MR;

    if (otmp->otyp == BRACERS_OF_INTEGRITY)
        objprops &= ~ITEM_INTEGRITY;
    if (otmp->otyp == BRACERS_OF_SLEEP_RESISTANCE)
        objprops &= ~ITEM_SLEEP;
    if (otmp->otyp == BRACERS_OF_COLD_RESISTANCE)
        objprops &= ~ITEM_FROST;

    if (otmp->otyp == ROGUE_S_GLOVES)
        objprops &= ~ITEM_VIGIL;
    if (otmp->otyp == GAUNTLETS_OF_FUMBLING)
        objprops &= ~ITEM_FUMBLE;
    if (otmp->otyp == ELVEN_BOOTS)
        objprops &= ~ITEM_STEALTH;
    if (otmp->otyp == FUMBLE_BOOTS)
        objprops &= ~ITEM_FUMBLE;

    if (otmp->otyp == RIN_SEARCHING)
        objprops &= ~ITEM_VIGIL;
    if (otmp->otyp == RIN_STEALTH)
        objprops &= ~ITEM_STEALTH;
    if (otmp->otyp == RIN_HUNGER)
        objprops &= ~ITEM_HUNGER;
    if (otmp->otyp == RIN_AGGRAVATE_MONSTER)
        objprops &= ~ITEM_STENCH;
    if (otmp->otyp == RIN_WARNING)
        objprops &= ~ITEM_WARN;
    if (otmp->otyp == RIN_POISON_RESISTANCE)
        objprops &= ~ITEM_VENOM;
    if (otmp->otyp == RIN_FIRE_RESISTANCE)
        objprops &= ~ITEM_FLAME;
    if (otmp->otyp == RIN_COLD_RESISTANCE)
        objprops &= ~ITEM_FROST;
    if (otmp->otyp == RIN_SHOCK_RESISTANCE)
        objprops &= ~ITEM_SHOCK;
    if (otmp->otyp == RIN_SEE_INVISIBLE)
        objprops &= ~ITEM_INSIGHT;
    if (otmp->otyp == RIN_SLEEPING)
        objprops &= ~ITEM_SLEEP;
    if (otmp->otyp == RIN_CARRYING)
        objprops &= ~(ITEM_CARRY | ITEM_BURDEN);
    return objprops;
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

    /* Launchers can have defensive properties */
    if (is_launcher(otmp))
        objprops &= ~(ITEM_RES_PROPS & ~ONLY_ARM_PROPS);
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

void
propnames(char *buf, long props,
          boolean weapon, boolean has_of)
{
    char of[6];
    if (props)
        Strcpy(of, (has_of) ? " and" : " of");
    if (props & ITEM_FLAME) {
        Strcat(buf, of), Strcat(buf, weapon ? " {flame}" : " {fire resistance}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_FROST) {
        Strcat(buf, of), Strcat(buf, weapon ? " {frost}" : " {cold resistance}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_SHOCK) {
        Strcat(buf, of), Strcat(buf, weapon ? " {shock}" : " {shock resistance}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_VENOM) {
        Strcat(buf, of), Strcat(buf, weapon ? " {venom}" : " {poison resistance}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_ACID) {
        Strcat(buf, of), Strcat(buf, weapon ? " {acid}" : " {acid resistance}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_DRAIN) {
        Strcat(buf, of), Strcat(buf, weapon ? " {draining}" : " {drain resistance}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_SLEEP) {
        Strcat(buf, of), Strcat(buf, weapon ? " {slumber}" : " {alertness}"),
                Strcpy(of, " and");
    }
    if (props & ITEM_PEACE) {
        Strcat(buf, of), Strcat(buf, " {peace}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_VIGIL) {
        Strcat(buf, of), Strcat(buf, " {vigilance}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_STEALTH) {
        Strcat(buf, of), Strcat(buf, " {stealth}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_FUMBLE) {
        Strcat(buf, of), Strcat(buf, " {fumbling}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_HUNGER) {
        Strcat(buf, of), Strcat(buf, " {hunger}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_WARN) {
        Strcat(buf, of), Strcat(buf, " {warning}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_FILTH) {
        Strcat(buf, of), Strcat(buf, weapon ? " {filth}" : " {health}"),
                Strcpy(of, " and");
    }
    if (props & ITEM_INSIGHT) {
        Strcat(buf, of), Strcat(buf, " {insight}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_CHA) {
        Strcat(buf, of), Strcat(buf, " {charisma}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_BURDEN) {
        Strcat(buf, of), Strcat(buf, " {burden}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_RAGE) {
        Strcat(buf, of), Strcat(buf, " {rage}"),
        Strcpy(of, " and");
    }
    if (props & ITEM_DANGER) {
        Strcat(buf, of), Strcat(buf, " {danger}"),
            Strcpy(of, " and");
    }
    if (props & ITEM_STENCH) {
        Strcat(buf, of), Strcat(buf, " {stench}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_SUSTAIN) {
        Strcat(buf, of), Strcat(buf, " {preservation}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_CARRY) {
        Strcat(buf, of), Strcat(buf, " {carrying}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_HEXING) {
        Strcat(buf, of), Strcat(buf, " {hexing}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_MR) {
        Strcat(buf, of), Strcat(buf, " {antimagic}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_NULLING) {
        Strcat(buf, of), Strcat(buf, " {nulling}"),
               Strcpy(of, " and");
    }
    if (props & ITEM_INTEGRITY) {
        Strcat(buf, of), Strcat(buf, " {integrity}"),
               Strcpy(of, " and");
    }
}

/* Parse a wish/name string's trailing " of <propname>" oprop suffix out
 * of bp, in place -- like the " named "/" called "/" labeled " parsing
 * readobjnam_postparse1() does elsewhere, the matched text is truncated
 * from bp so the remaining name can still be looked up normally. Some
 * propnames are guarded against a leading object type that names a real,
 * distinct item (e.g. "ring of stealth", "wand of sleep") rather than an
 * oprop. Returns the matching ITEM_* flag, or 0 if nothing matched. */
long
parse_oprop_wishname(char *bp)
{
    char *p;

    if ((p = strstri(bp, " of flame")) != 0) {
        *p = 0;
        return ITEM_FLAME;
    } else if ((p = strstri(bp, " of frost")) != 0) {
        *p = 0;
        return ITEM_FROST;
    } else if ((p = strstri(bp, " of slumber")) != 0) {
        *p = 0;
        return ITEM_SLEEP;
    } else if ((p = strstri(bp, " of shock")) != 0) {
        *p = 0;
        return ITEM_SHOCK;
    } else if ((p = strstri(bp, " of venom")) != 0) {
        *p = 0;
        return ITEM_VENOM;
    } else if ((p = strstri(bp, " of acid")) != 0
            && strncmpi(bp, "potion", 6)) {
        *p = 0;
        return ITEM_ACID;
    } else if ((p = strstri(bp, " of decay")) != 0) {
        *p = 0;
        return ITEM_DRAIN;
    } else if ((p = strstri(bp, " of integrity")) != 0) {
        *p = 0;
        return ITEM_INTEGRITY;
    } else if ((p = strstri(bp, " of filth")) != 0) {
        *p = 0;
        return ITEM_FILTH;
    } else if ((p = strstri(bp, " of peace")) != 0) {
        *p = 0;
        return ITEM_PEACE;
    } else if ((p = strstri(bp, " of vigilance")) != 0
            && strncmpi(bp, "ring", 4)) {
        *p = 0;
        return ITEM_VIGIL;
    } else if ((p = strstri(bp, " of stealth")) != 0
            && strncmpi(bp, "ring", 4)) {
        *p = 0;
        return ITEM_STEALTH;
    } else if ((p = strstri(bp, " of warning")) != 0
            && strncmpi(bp, "ring", 4)) {
        *p = 0;
        return ITEM_WARN;
    } else if ((p = strstri(bp, " of insight")) != 0) {
        *p = 0;
        return ITEM_INSIGHT;
    } else if ((p = strstri(bp, " of charisma")) != 0) {
        *p = 0;
        return ITEM_CHA;
    } else if ((p = strstri(bp, " of fumbling")) != 0
            && (strncmpi(bp, "boots", 5) || strncmpi(bp, "gauntlets", 9))) {
        *p = 0;
        return ITEM_FUMBLE;
    } else if ((p = strstri(bp, " of hunger")) != 0
            && strncmpi(bp, "ring", 4)) {
        *p = 0;
        return ITEM_HUNGER;
    } else if ((p = strstri(bp, " of burden")) != 0) {
        *p = 0;
        return ITEM_BURDEN;
    } else if ((p = strstri(bp, " of rage")) != 0) {
        *p = 0;
        return ITEM_RAGE;
    } else if ((p = strstri(bp, " of danger")) != 0) {
        *p = 0;
        return ITEM_DANGER;
    } else if ((p = strstri(bp, " of stench")) != 0) {
        *p = 0;
        return ITEM_STENCH;
    } else if ((p = strstri(bp, " of sleep")) != 0
            && strncmpi(bp, "wand", 4)) {
        *p = 0;
        return ITEM_STENCH;
    } else if ((p = strstri(bp, " of preservation")) != 0) {
        *p = 0;
        return ITEM_SUSTAIN;
    } else if ((p = strstri(bp, " of carrying")) != 0) {
        *p = 0;
        return ITEM_CARRY;
    } else if ((p = strstri(bp, " of hexing")) != 0) {
        *p = 0;
        return ITEM_HEXING;
    } else if ((p = strstri(bp, " of antimagic")) != 0) {
        *p = 0;
        return ITEM_MR;
    } else if ((p = strstri(bp, " of nulling")) != 0) {
        *p = 0;
        return ITEM_NULLING;
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

void
oprops_on(struct obj *otmp, long mask)
{
    long props = otmp->oprops;

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
    if (props & ITEM_PEACE) {
        BAggravate_monster |= mask;
    }
    if (props & ITEM_VIGIL)
        ESearching |= mask;
    if (props & ITEM_STEALTH)
        EStealth |= mask;
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
        (void) changes_stat(ITEM_CHA);
    }
    if (props & ITEM_BURDEN)
        EStable |= mask;
    if (props & ITEM_DANGER)
        EInfravision |= mask;
    if (props & ITEM_STENCH)
        EAggravate_monster |= mask;
    if (props & ITEM_SUSTAIN)
        Preservation |= mask;
    if (props & ITEM_MR)
        EAntimagic |= mask;
}

void
oprops_off(struct obj *otmp, long mask)
{
    long props = otmp->oprops;

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
    if (props & ITEM_PEACE) {
        BAggravate_monster &= ~mask;
    }
    if (props & ITEM_VIGIL)
        ESearching &= ~mask;
    if (props & ITEM_INSIGHT) {
        ESee_invisible &= ~mask;
        toggle_seeinv(otmp, (ESee_invisible & ~mask), FALSE);
    }
    if (props & ITEM_STEALTH)
        EStealth &= ~mask;
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
        (void) changes_stat(ITEM_CHA);
    }
    if (props & ITEM_BURDEN)
        EStable &= ~mask;
    if (props & ITEM_DANGER)
        EInfravision &= ~mask;
    if (props & ITEM_STENCH)
        EAggravate_monster &= ~mask;
    if (props & ITEM_SUSTAIN)
        Preservation &= ~mask;
    if (props & ITEM_MR)
        EAntimagic &= ~mask;
}

/* Turn on the intrinsic-conferring oprops of a weapon being wielded
 * (uwep or, while two-weapon fighting, uswapwep). Elemental attack
 * properties (ITEM_FLAME et al) aren't handled here -- weapons can't be
 * granted resistance-granting oprops (see ONLY_ARM_PROPS in oprops.h),
 * and their attack-type props are checked live by oprop_attacks()
 * rather than toggled as standing intrinsics. */
void
wep_oprops_on(struct obj *otmp, long mask)
{
    long props = otmp->oprops;

    if (props & ITEM_FUMBLE) {
        if (!(HFumbling & ~TIMEOUT))
            incr_itimeout(&HFumbling, rnd(20));
        EFumbling |= mask;
    }
    if (props & ITEM_PEACE)
        BAggravate_monster |= mask;
    if (props & ITEM_HUNGER)
        EHunger |= mask;
    if (props & ITEM_STENCH)
        EAggravate_monster |= mask;
    if (props & ITEM_VIGIL)
        ESearching |= mask;
    if (props & ITEM_INSIGHT) {
        ESee_invisible |= mask;
        toggle_seeinv(otmp, (ESee_invisible & ~mask), TRUE);
    }
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
    if (props & ITEM_WARN) {
        EWarning |= mask;
        see_monsters();
    }
    if (props & ITEM_CHA)
        (void) changes_stat(ITEM_CHA);
    if (props & ITEM_BURDEN)
        EStable |= mask;
    if (props & ITEM_DANGER)
        EInfravision |= mask;
}

/* Turn off the intrinsic-conferring oprops of a weapon being unwielded;
 * counterpart of wep_oprops_on(). */
void
wep_oprops_off(struct obj *otmp, long mask)
{
    long props = otmp->oprops;

    if (props & ITEM_FUMBLE) {
        if (!(HFumbling & ~TIMEOUT))
            HFumbling = EFumbling = 0L;
        EFumbling &= ~mask;
    }
    if (props & ITEM_PEACE)
        BAggravate_monster &= ~mask;
    if (props & ITEM_HUNGER)
        EHunger &= ~mask;
    if (props & ITEM_STENCH)
        EAggravate_monster &= ~mask;
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
    if (props & ITEM_WARN) {
        EWarning &= ~mask;
        see_monsters();
    }
    if (props & ITEM_CHA)
        (void) changes_stat(ITEM_CHA);
    if (props & ITEM_BURDEN)
        EStable &= ~mask;
    if (props & ITEM_DANGER)
        EInfravision &= ~mask;
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

/** Checks if an property will affect any stats.
  * If it does, we'll update the display.
  **/
boolean
changes_stat(long prop)
{
    int c;
    for (c = 0; c < A_MAX; c++) {
        int old_attrib = ACURR(c);
        if (calc_prop_bonus(prop) != old_attrib) {
            disp.botl = 1;
            update_inventory();
            return TRUE;
        }
    }
    return FALSE;
}
