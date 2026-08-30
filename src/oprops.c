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
