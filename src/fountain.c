/* NetHack 3.7	fountain.c	$NHDT-Date: 1699582923 2023/11/10 02:22:03 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.100 $ */
/*      Copyright Scott R. Turner, srt@ucla, 10/27/86 */
/* NetHack may be freely redistributed.  See license for details. */

/* Code for drinking from fountains. */

#include "hack.h"

staticfn void dowatersnakes(void);
staticfn void dowaterdemon(void);
staticfn void dowaternymph(void);
staticfn void gush(coordxy, coordxy, genericptr_t) NONNULLARG3;
staticfn void dofindgem(void);
staticfn boolean watchman_warn_fountain(struct monst *) NONNULLARG1;
staticfn void blowupforge(coordxy, coordxy);

DISABLE_WARNING_FORMAT_NONLITERAL

/* used when trying to dip in or drink from fountain or sink or pool while
   levitating above it, or when trying to move downwards in that state */
void
floating_above(const char *what)
{
    const char *umsg = "are floating high above the %s.";

    if (u.utrap && (u.utraptype == TT_INFLOOR || u.utraptype == TT_LAVA)) {
        /* when stuck in floor (not possible at fountain or sink location,
           so must be attempting to move down), override the usual message */
        umsg = "are trapped in the %s.";
        what = surface(u.ux, u.uy); /* probably redundant */
    }
    You(umsg, what);
}

RESTORE_WARNING_FORMAT_NONLITERAL

/* Fountain of snakes! */
staticfn void
dowatersnakes(void)
{
    int num = rn1(5, 2);
    struct monst *mtmp;

    if (!(svm.mvitals[PM_WATER_MOCCASIN].mvflags & G_GONE)) {
        if (!Blind) {
            pline("An endless stream of %s pours forth!",
                  Hallucination ? makeplural(rndmonnam(NULL)) : "snakes");
        } else {
            Soundeffect(se_snakes_hissing, 75);
            You_hear("%s hissing!", something);
        }
        while (num-- > 0)
            if ((mtmp = makemon(&mons[PM_WATER_MOCCASIN], u.ux, u.uy,
                                MM_NOMSG)) != 0
                && t_at(mtmp->mx, mtmp->my))
                (void) mintrap(mtmp, NO_TRAP_FLAGS);
    } else {
        Soundeffect(se_furious_bubbling, 20);
        pline_The("fountain bubbles furiously for a moment, then calms.");
    }
}

/* Water demon */
staticfn void
dowaterdemon(void)
{
    struct monst *mtmp;

    if (!(svm.mvitals[PM_WATER_DEMON].mvflags & G_GONE)) {
        if ((mtmp = makemon(&mons[PM_WATER_DEMON], u.ux, u.uy,
                            MM_NOMSG)) != 0) {
            if (!Blind)
                You("unleash %s!", a_monnam(mtmp));
            else
                You_feel("the presence of evil.");

            /* Reward those on higher levels with better chances */
            if (rnd(256) < level_difficulty()) {
                pline("Grateful for %s release, %s grants you a wish!",
                      mhis(mtmp), mhe(mtmp));
                /* give a wish and discard the monster (mtmp set to null) */
                mongrantswish(&mtmp);
            } else if (t_at(mtmp->mx, mtmp->my))
                (void) mintrap(mtmp, NO_TRAP_FLAGS);
        }
    } else {
        Soundeffect(se_furious_bubbling, 20);
        pline_The("fountain bubbles furiously for a moment, then calms.");
    }
}

/* Water Nymph */
staticfn void
dowaternymph(void)
{
    struct monst *mtmp;

    if (!(svm.mvitals[PM_WATER_NYMPH].mvflags & G_GONE)
        && (mtmp = makemon(&mons[PM_WATER_NYMPH], u.ux, u.uy,
                            MM_NOMSG)) != 0) {
        if (!Blind)
            You("attract %s!", a_monnam(mtmp));
        else
            You_hear("a seductive voice.");
        mtmp->msleeping = 0;
        if (t_at(mtmp->mx, mtmp->my))
            (void) mintrap(mtmp, NO_TRAP_FLAGS);
    } else if (!Blind) {
        Soundeffect(se_bubble_rising, 50);
        Soundeffect(se_loud_pop, 50);
        pline("A large bubble rises to the surface and pops.");
    } else {
        Soundeffect(se_loud_pop, 50);
        You_hear("a loud pop.");
    }
}

/* Lava Demon */
static void
dolavademon(void)
{
    struct monst *mtmp;

    if (!(svm.mvitals[PM_LAVA_DEMON].mvflags & G_GONE)) {
        if ((mtmp = makemon(&mons[PM_LAVA_DEMON], u.ux, u.uy,
                            MM_NOMSG)) != 0) {
            if (!Blind)
                You("summon %s!", a_monnam(mtmp));
            else
                You_feel("the temperature rise significantly.");

            /* low levels offer a (slightly) better chance of survival */
            if (rnd(100) > (80 + level_difficulty()) && !fully_resistant(FIRE_RES)) {
                pline("Freed from the depths of Gehennom, "
                      "%s grants you protection from fire!", mhe(mtmp));
                incr_resistance(&HFire_resistance, 100);
                mongone(mtmp);
            } else if (t_at(mtmp->mx, mtmp->my)) {
                (void) mintrap(mtmp, NO_TRAP_FLAGS);
            }
        }
    } else
        pline_The("forge violently spews lava for a moment, then settles.");
}

/* Gushing forth along LOS from (u.ux, u.uy) */
void
dogushforth(int drinking)
{
    int madepool = 0;

    do_clear_area(u.ux, u.uy, 7, gush, (genericptr_t) &madepool);
    if (!madepool) {
        if (drinking)
            Your("thirst is quenched.");
        else
            pline("Water sprays all over you.");
    }
}

staticfn void
gush(coordxy x, coordxy y, genericptr_t poolcnt)
{
    struct monst *mtmp;
    struct trap *ttmp;

    if (((x + y) % 2) || u_at(x, y)
        || (rn2(1 + distmin(u.ux, u.uy, x, y))) || (levl[x][y].typ != ROOM)
        || (sobj_at(BOULDER, x, y)) || nexttodoor(x, y))
        return;

    if ((ttmp = t_at(x, y)) != 0 && !delfloortrap(ttmp))
        return;

    if (!((*(int *) poolcnt)++))
        pline("Water gushes forth from the overflowing fountain!");

    /* Put a pool at x, y */
    set_levltyp(x, y, PUDDLE);
    levl[x][y].flags = 0;
    /* No kelp! */
    del_engr_at(x, y);
    water_damage_chain(svl.level.objects[x][y], TRUE);

    if ((mtmp = m_at(x, y)) != 0)
        (void) minliquid(mtmp);
    else
        newsym(x, y);
}

/* Find a gem in the sparkling waters. */
staticfn void
dofindgem(void)
{
    if (!Blind)
        You("spot a gem in the sparkling waters!");
    else
        You_feel("a gem here!");
    (void) mksobj_at(rnd_class(DILITHIUM_CRYSTAL, LUCKSTONE - 1), u.ux, u.uy,
                     FALSE, FALSE);
    SET_FOUNTAIN_LOOTED(u.ux, u.uy);
    newsym(u.ux, u.uy);
    exercise(A_WIS, TRUE); /* a discovery! */
}

staticfn boolean
watchman_warn_fountain(struct monst *mtmp)
{
    if (is_watch(mtmp->data) && couldsee(mtmp->mx, mtmp->my)
        && mtmp->mpeaceful) {
        if (!Deaf) {
            pline("%s yells:", Amonnam(mtmp));
            verbalize("Hey, stop using that fountain!");
        } else {
            pline("%s earnestly %s %s %s!",
                  Amonnam(mtmp),
                  nolimbs(mtmp->data) ? "shakes" : "waves",
                  mhis(mtmp),
                  nolimbs(mtmp->data)
                  ? mbodypart(mtmp, HEAD)
                  : makeplural(mbodypart(mtmp, ARM)));
        }
        return TRUE;
    }
    return FALSE;
}

void
dipforge(struct obj *obj)
{
    boolean is_hands = (obj == &hands_obj);

    if (Levitation) {
        floating_above("forge");
        return;
    }

    burn_away_slime();

    if (is_hands) {
        if (uarmg) {
            obj = uarmg; /* Process below */
        } else {
            You("dip your %s into the forge.", makeplural(body_part(HAND)));

            if (!fully_resistant(AD_FIRE)) {
                You("burn yourself!");
                losehp(resist_reduce(d(2, 16), FIRE_RES),
                "touching forge lava", KILLED_BY);
                dehydrate(resist_reduce(rn1(150, 150), FIRE_RES));
            } else {
                You("swirl the lava around...");
            }
            /* Burn any goop off */
            if (Glib) {
                make_glib(0);
                Your("%s are no longer slippery.", fingers_or_gloves(TRUE));
            }
            return;
        }
    }

    /* Dipping something you're still wearing into a forge filled with
     * lava, probably not the smartest thing to do. This is gonna hurt.
     * Non-metallic objects are handled by lava_damage().
     */
    if (obj->owornmask & (W_ARMOR | W_ACCESSORY)) {
        if (!fully_resistant(FIRE_RES)) {
            You("dip your worn %s into the forge.  You burn yourself!",
                xname(obj));
            if (!rn2(3))
                You("may want to remove your %s first...", xname(obj));
        }
        if (is_metallic(obj) && fully_resistant(FIRE_RES)) {
            You("can't reforge something you're wearing.");
        }
        losehp(resist_reduce(d(2, 16), FIRE_RES),
               "dipping a worn object into a forge", KILLED_BY);
    }

    /* If punished and wielding a hammer, there's a good chance
     * you can use a forge to free yourself */
    if (Punished && obj->otyp == HEAVY_IRON_BALL) {
        if (!uwep || uwep->otyp != WAR_HAMMER) {
            /* sometimes drop a hint */
            if (!rn2(4))
                pline("You'll need a hammer to be able to break the chain.");
            goto result;
        } else if (uwep && uwep->otyp == WAR_HAMMER) {
            You("place the ball and chain inside the forge.");
            pline("Raising your %s, you strike the chain...",
                  xname(uwep));
            if (!rn2((P_SKILL(P_HAMMER) < P_SKILLED) ? 8 : 2)
                && Luck >= 0) { /* training up hammer skill pays off */
                pline("The chain breaks free!");
                unpunish();
            } else {
                pline("Clang!");
            }
        }
        return;
    }

    if (obj->greased) {
        obj->greased = 0;
        if (!Blind)
            pline_The("grease burns off.");
    }
    /* Zombies also share the otrapped var (zombie_corpse) */
    if (obj->opoisoned && obj->otyp != CORPSE) {
        obj->opoisoned = 0;
        if (!Blind)
            pline_The("poison evaporates.");
    }

result:
    switch (rnd(30)) {
    case 6:
    case 7:
    case 8:
    case 9: /* Strange feeling */
        pline("A weird sensation runs up your %s.", body_part(ARM));
        break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        if (!is_metallic(obj))
            goto lava;

        if (is_metallic(obj) && Luck >= 0) {
            if (greatest_erosion(obj) > 0) {
                if (!Blind)
                    You("successfully reforge your %s, repairing some of the damage.",
                        xname(obj));
                if (obj->oeroded > 0)
                    obj->oeroded--;
                if (obj->oeroded2 > 0)
                    obj->oeroded2--;
            } else {
                if (!Blind) {
                    Your("%s glows briefly from the heat, but looks reforged and as new as ever.",
                         xname(obj));
                }
            }
        }
        break;
    case 19:
    case 20:
        if (!is_metallic(obj))
            goto lava;

        if (!obj->blessed && is_metallic(obj) && Luck > 5) {
            bless(obj);
            if (!Blind) {
                Your("%s glows blue for a moment.",
                     xname(obj));
            }
        } else {
            You_feel("a sudden wave of heat.");
        }
        break;
    case 21: /* Lava Demon */
        if (!rn2(8))
            dolavademon();
        else
            pline_The("forge violently spews lava for a moment, then settles.");
        break;
    case 22:
        if (Luck < 0) {
            blowupforge(u.ux, u.uy);
            /* Avoid destroying the same item twice (lava_damage) */
            return;
        } else {
            pline("Molten lava surges up and splashes all over you!");
            losehp(resist_reduce(d(3, 8), FIRE_RES),
                   "dipping into a forge", KILLED_BY);
            dehydrate(resist_reduce(rn1(150, 150), FIRE_RES));
        }
        break;
    case 23:
        if (!is_metallic(obj))
            goto lava;
        if (greatest_erosion(obj) > 0)
            goto lava;
         /* One-time erodeproofing of an item */
        if (!levl[u.ux][u.uy].looted && !obj->oerodeproof
                && !is_supermaterial(obj)) {
            if (!Blind)
                pline("%s flickers with purple light.", Doname2(obj));
            else
                pline("%s shudders slightly in your grip.", Doname2(obj));
            obj->oerodeproof = 1;
            obj->rknown = 1;
            levl[u.ux][u.uy].looted |= T_LOOTED;
        } else {
            /* Steam cloud */
            if (!Blind)
                pline("A blast of steam surges from the forge!");
            else
                You("a blast of hot air rush past you.");
            losehp(resist_reduce(rnd(4), FIRE_RES),
                   "blasted by steam", KILLED_BY);
            (void) create_gas_cloud(u.ux, u.uy, rn1(15, 10), 0);
        }
        break;
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30: /* Strange feeling */
        You_feel("a sudden flare of heat.");
        break;
    }
lava:
    lava_damage(obj, u.ux, u.uy);
    update_inventory();
    dehydrate(resist_reduce(rn1(150, 150), FIRE_RES));
}

/* forging recipes - first object is the end result
   of combining objects two and three */
const struct ForgeRecipe fusions[] = {
    /* Only samurai can forge these: */
    { KATANA,               LONG_SWORD,         LONG_SWORD,     1, 1 },
    { TSURUGI,              TWO_HANDED_SWORD,   KATANA,         1, 1 },
    { SHURIKEN,             DART,               DAGGER,         2, 1 },
    /* Dwarvish items - only dwarves can forge */
    { DWARVISH_MATTOCK,     PICK_AXE,           DWARVISH_SHORT_SWORD, 1, 1 },
    { DWARVISH_SHORT_SWORD, DWARVISH_SPEAR,     SHORT_SWORD,    1, 1 },
    { DWARVISH_SPEAR,       ARROW,              SPEAR,          10, 1 },
    { DWARVISH_IRON_HELM,   HELMET,             DWARVISH_SHORT_SWORD, 1, 1 },
    { DWARVISH_MITHRIL_COAT, CHAIN_MAIL,        DWARVISH_ROUNDSHIELD, 1, 1 },
    { DWARVISH_ROUNDSHIELD, LARGE_SHIELD,       DWARVISH_IRON_HELM, 1, 1 },
    /* Orcish items - only orcs can forge */
    { ORCISH_DAGGER,        ORCISH_ARROW,       KNIFE,          2, 1 },
    { ORCISH_SHORT_SWORD,   ORCISH_SPEAR,       ORCISH_DAGGER,  1, 1 },
    { ORCISH_SPEAR,         ORCISH_ARROW,       ORCISH_DAGGER,  10, 1 },
    { ORCISH_HELM,          DENTED_POT,         ORCISH_DAGGER,  1, 1 },
    { ORCISH_CHAIN_MAIL,    RING_MAIL,          ORCISH_SHIELD,  1, 1 },
    { ORCISH_RING_MAIL,     ORCISH_SHIELD,      ORCISH_HELM,    1, 1 },
    { ORCISH_SHIELD,        ORCISH_HELM,        ORCISH_BOOTS,   1, 1 },
    { ORCISH_BOOTS,         ORCISH_HELM,        ORCISH_SHORT_SWORD, 1, 1 },
    /* Any role can forge the rest */
    { DAGGER,               ARROW,              KNIFE,          2, 1 },
    { KNIFE,                ARROW,              DART,           2, 2 },
    { JAVELIN,              CROSSBOW_BOLT,      SPEAR,          2, 1 },
    { TRIDENT,              SCIMITAR,           SPEAR,          1, 1 },
    { SCALPEL,              KNIFE,              STILETTO,       1, 1 },
    { STILETTO,             DAGGER,             KNIFE,          2, 1 },
    { AXE,                  DAGGER,             SPEAR,          1, 1 },
    { BATTLE_AXE,           AXE,                BROADSWORD,     1, 1 },
    { SHORT_SWORD,          HELMET,             DAGGER,         1, 1 },
    { SCIMITAR,             KNIFE,              SHORT_SWORD,    1, 1 },
    { BROADSWORD,           SCIMITAR,           SHORT_SWORD,    1, 1 },
    { LONG_SWORD,           SHORT_SWORD,        SHORT_SWORD,    1, 1 },
    { TWO_HANDED_SWORD,     LONG_SWORD,         BROADSWORD,     1, 1 },
    { WAR_HAMMER,           MACE,               FLAIL,          1, 1 },
    { SILVER_DAGGER,        SILVER_ARROW,       DAGGER,         2, 1 },
    { SILVER_SPEAR,         SILVER_DAGGER,      SPEAR,          1, 1 },
    { SILVER_SPEAR,         SILVER_DAGGER,      DWARVISH_SPEAR, 1, 1 },
    { SILVER_SABER,         SILVER_DAGGER,      SCIMITAR,       1, 1 },
    { SILVER_SHORT_SWORD,   SILVER_DAGGER,      SHORT_SWORD,    1, 1 },
    { SILVER_SHORT_SWORD,   SILVER_DAGGER,      DWARVISH_SHORT_SWORD, 1, 1 },
    { MORNING_STAR,         MACE,               DAGGER,         1, 1 },
    { MACE,                 AKLYS,              DAGGER,         1, 1 },
    /* Polearms*/
    { PARTISAN,             BROADSWORD,         SPEAR,          1, 1 },
    { RANSEUR,              STILETTO,           SPEAR,          1, 1 },
    { SPETUM,               KNIFE,              SPEAR,          1, 1 },
    { GLAIVE,               SHORT_SWORD,        SPEAR,          1, 1 },
    { LANCE,                JAVELIN,            GLAIVE,         1, 1 },
    { HALBERD,              RANSEUR,            AXE,            1, 1 },
    { BARDICHE,             BATTLE_AXE,         SPEAR,          1, 1 },
    { VOULGE,               AXE,                SPEAR,          1, 1 },
    { FAUCHARD,             SILVER_SABER,       SPEAR,          1, 1 },
    { GUISARME,             GRAPPLING_HOOK,     SPEAR,          1, 1 },
    { BILL_GUISARME,        GUISARME,           SPEAR,          1, 1 },
    { LUCERN_HAMMER,        WAR_HAMMER,         JAVELIN,        1, 1 },
    { BEC_DE_CORBIN,        WAR_HAMMER,         SPEAR,          1, 1 },
    /* Ammo */
    { SLING_BULLET,         ROCK,               DART,           3, 1 },

    { 0, 0, 0, 0, 0 }
};


int
doforging(void)
{
    const struct ForgeRecipe *recipe;
    struct obj* obj1;
    struct obj* obj2;
    struct obj* output;
    int objtype = 0;

    /* first, we need a forge */
    if (!IS_FORGE(levl[u.ux][u.uy].typ)) {
        You("need a forge in order to forge objects.");
        return 0;
    }

    /* next, the proper tool to do the job */
    if (!uwep || uwep->otyp != WAR_HAMMER) {
        pline("You need to be wielding a hammer to forge successfully.");
        return 0;
    }

    /* various player conditions can prevent successful forging */
    if (Stunned || Confusion || Hallucination) {
        You_cant("use the forge while incapacitated.");
        return 0;
    } else if (u.uhunger < 50) { /* weak */
        You("are too weak from hunger to use the forge.");
        return 0;
    } else if (ACURR(A_STR) < 4) {
        You("lack the strength to use the forge.");
        return 0;
    }
    
    /* setup the base object */
    obj1 = getobj("use as a base", any_obj_ok, GETOBJ_PROMPT);
    if (!obj1) {
        You("need a base object to forge with.");
        return 0;
    } else if (!(is_metallic(obj1) || obj1->otyp == ROCK)) {
        /* object should be gemstone or metallic */
        pline_The("base object must be metallic, mineral, or gemstone.");
        return 0;
    }

    /* setup the secondary object */
    obj2 = getobj("combine with the base object", any_obj_ok, GETOBJ_PROMPT);
    if (!obj2) {
        You("need more than one object.");
        return 0;
    } else if (!(is_metallic(obj2) || obj2->otyp == ROCK)) {
        /* secondary object should also be metallic */
        pline_The("secondary object must be metallic or mineral.");
        return 0;
    }

    /* handle illogical cases */
    if (obj1 == obj2) {
        You_cant("combine an object with itself!");
        return 0;

    /* not that the Amulet of Yendor or invocation items would
       ever be part of a forging recipe, but these should be
       protected in any case */
    } else if (obj_resists(obj1, 0, 0) || obj_resists(obj2, 0, 0)) {
        You_cant("forge such a thing!");
        blowupforge(u.ux, u.uy);
        return 0;
    /* worn or wielded objects */
    } else if (is_worn(obj1) || is_worn(obj2)) {
        You("must first %s the objects you wish to forge.",
            ((obj1->owornmask & W_QUIVER) || (obj2->owornmask & W_QUIVER)) ? "unquiver"
            : ((obj1->owornmask & W_ARMOR) || (obj2->owornmask & W_ARMOR)) ? "remove"
                                                                           : "unwield");
        return 0;
    /* Artifacts can never be applied to a non-artifact base. */
    } else if ((obj2->oartifact && !obj1->oartifact)
               || (obj1->oartifact && !obj2->oartifact)) {
        pline("Artifacts cannot be forged with lesser objects.");
        return 0;
    /* dragon-scaled armor can never be fully metallic */
    } else if (Is_dragon_armor(obj1)) {
        pline("Dragon-scaled armor cannot be forged.");
        return 0;
    }

    /* start the forging process */

    for (recipe = fusions; recipe->result_typ; recipe++) {
        if ((obj1->otyp == recipe->typ1
                && obj2->otyp == recipe->typ2
                && obj1->quan >= recipe->quan_typ1
                && obj2->quan >= recipe->quan_typ2)
            || (obj2->otyp == recipe->typ1
                && obj1->otyp == recipe->typ2
                && obj2->quan >= recipe->quan_typ1
                && obj1->quan >= recipe->quan_typ2)) {
            objtype = recipe->result_typ;
            break;
        }
    }

    if (!objtype) {
        /* if the objects used do not match the recipe array,
            the forging process fails */
        You("fail to combine these two objects.");
        return 1;
    } else if (!Role_if(PM_SAMURAI)
          && (objtype == KATANA || objtype == TSURUGI
            || objtype == SHURIKEN)) {
        You("need the mastery of a samurai to accomplish that.");
        return 1;
    } else if (is_dwarvish_obj(objtype) && !Race_if(PM_DWARF)) {
        pline("Only a true dwarf would have the skills for that...");
        return 1;
    } else if (is_orcish_obj(objtype) && !Race_if(PM_ORC)) {
        pline("Only an orc would be willing to forge that...");
        return 1;
    } else if (objtype) {
        /* success */
        You("place %s, then %s inside the forge.",
            the(xname(obj1)), the(xname(obj2)));
        pline("Raising your %s, you begin to forge the objects together...",
              xname(uwep));
        output = mksobj(objtype, TRUE, FALSE);

        /* if objects are enchanted or have charges,
            carry that over, and use the greater of the two */
        if (output->oclass == obj2->oclass) {
            output->spe = obj2->spe;
            if (output->oclass == obj1->oclass)
                output->spe = max(output->spe, obj1->spe);
        } else if (output->oclass == obj1->oclass) {
            output->spe = obj1->spe;
        }

        /* Output gets erodeproofing if either ingredient has it  */
        if (obj1->oerodeproof || obj2->oerodeproof) {
            output->oerodeproof = 1;
        }

        /* transfer curses and blessings from secondary object */
        output->cursed = obj2->cursed;
        output->blessed = obj2->blessed;
        /* ensure the final product is not degraded or poisoned
            in any way */
        output->oeroded = output->oeroded2 = output->opoisoned = 0;

        /* no grease should be present after forging */
        output->greased = 0;

        /* toss out old objects, add new one */
        if (obj1->otyp == recipe->typ1)
            obj1->quan -= recipe->quan_typ1;
        if (obj2->otyp == recipe->typ1)
            obj2->quan -= recipe->quan_typ1;
        if (obj1->otyp == recipe->typ2)
            obj1->quan -= recipe->quan_typ2;
        if (obj2->otyp == recipe->typ2)
            obj2->quan -= recipe->quan_typ2;

        /* recalculate weight of the recipe objects if
            using a stack */
        if (obj1->quan > 0)
            obj1->owt = weight(obj1);
        if (obj2->quan > 0)
            obj2->owt = weight(obj2);

        /* delete recipe objects if quantity reaches zero */
        if (obj1->quan <= 0)
            delobj(obj1);
        if (obj2->quan <= 0)
            delobj(obj2);

        /* forged object is created */
        output = addinv(output);
        /* prevent large stacks of ammo-type weapons */
        if (output->quan > 3L) {
            output->quan = 3L;
            if (!rn2(4)) /* small chance of an extra */
                output->quan += 1L;

        }

        output->owt = weight(output);
        You("have successfully forged %s.", doname(output));
        update_inventory();
        if (!rn2(127)) {
            /* forging magic can sometimes be too much stress */
            if (!rn2(6))
                coolforge(u.ux, u.uy);
            else
                pline_The("lava in the forge bubbles ominously.");
        }
        dehydrate(resist_reduce(rn1(20, 20), FIRE_RES));
        /* remove result from inventory and re-insert it, possibly stacking
          with compatible ones; override 'pickup_burden' while doing so */
        hold_potion(output, "You juggle and drop %s!",
                    doname(output), (const char *) 0);
    }

    return 1;
}


void
dryup(coordxy x, coordxy y, boolean isyou)
{
    if (IS_FOUNTAIN(levl[x][y].typ)
        && (!rn2(3) || FOUNTAIN_IS_WARNED(x, y))) {
        if (isyou && in_town(x, y) && !FOUNTAIN_IS_WARNED(x, y)) {
            struct monst *mtmp;

            SET_FOUNTAIN_WARNED(x, y);
            /* Warn about future fountain use. */
            mtmp = get_iter_mons(watchman_warn_fountain);
            /* You can see or hear this effect */
            if (!mtmp)
                pline_The("flow reduces to a trickle.");
            return;
        }
        if (isyou && wizard) {
            if (y_n("Dry up fountain?") == 'n')
                return;
        }
        /* FIXME: sight-blocking clouds should use block_point() when
           being created and unblock_point() when going away, then this
           glyph hackery wouldn't be necessary */
        if (cansee(x, y)) {
            int glyph = glyph_at(x, y);

            if (!glyph_is_cmap(glyph) || glyph_to_cmap(glyph) != S_cloud)
                pline_The("fountain dries up!");
        }
        /* replace the fountain with ordinary floor */
        set_levltyp(x, y, ROOM); /* updates level.flags.nfountains */
        levl[x][y].flags = 0;
        levl[x][y].blessedftn = 0;
        /* The location is seen if the hero/monster is invisible
           or felt if the hero is blind. */
        maybe_unhide_at(x, y);
        newsym(x, y);
        if (isyou && in_town(x, y))
            (void) angry_guards(FALSE);
    }
}

/* quaff from a fountain when standing on its location */
void
drinkfountain(void)
{
    /* What happens when you drink from a fountain? */
    boolean mgkftn = (levl[u.ux][u.uy].blessedftn == 1);
    int fate = rnd(30);
    struct obj *pseudo;

    if (Levitation) {
        floating_above("fountain");
        return;
    }

    if (mgkftn && u.uluck >= 0 && fate >= 10) {
        int littleluck = (u.uluck < 4);

        /* blessed restore ability */
        pseudo = mksobj(POT_RESTORE_ABILITY, FALSE, FALSE);
        pseudo->cursed = 0;
        pseudo->blessed = 1;
        peffects(pseudo);
        obfree(pseudo, (struct obj *) 0);
        
        /* gain ability, blessed if "natural" luck is high */
        pseudo = mksobj(POT_GAIN_ABILITY, FALSE, FALSE);
        pseudo->cursed = 0;
        pseudo->blessed = !littleluck;
        peffects(pseudo);
        obfree(pseudo, (struct obj *) 0);
        
        display_nhwindow(WIN_MESSAGE, FALSE);
        pline("A wisp of vapor escapes the fountain...");
        exercise(A_WIS, TRUE);
        levl[u.ux][u.uy].blessedftn = 0;
        rehydrate(rn1(250, 250));
        return;
    }

    if (fate < 10) {
        pline_The("cool draught refreshes you.");
        u.uhunger += rnd(10); /* don't choke on water */
        newuhs(FALSE);
        rehydrate(rn1(75, 25));
        if (mgkftn)
            return;
    } else {
        switch (fate) {
        case 19: /* Self-knowledge */
            You_feel("self-knowledgeable...");
            display_nhwindow(WIN_MESSAGE, FALSE);
            enlightenment(MAGICENLIGHTENMENT, ENL_GAMEINPROGRESS);
            exercise(A_WIS, TRUE);
            pline_The("feeling subsides.");
            rehydrate(rn1(75, 25));
            break;
        case 20: /* Foul water */
            pline_The("water is foul!  You gag and vomit.");
            morehungry(rn1(20, 11));
            vomit();
            break;
        case 21: /* Poisonous */
            pline_The("water is contaminated!");
            if (fully_resistant(POISON_RES)) {
                pline("Perhaps it is runoff from the nearby %s farm.",
                      fruitname(FALSE));
                losehp(resist_reduce(rnd(4), POISON_RES),
                       "unrefrigerated sip of juice", KILLED_BY_AN);
                break;
            }
            poison_strdmg(rn1(4, 3), rnd(10), "contaminated water",
                          KILLED_BY);
            exercise(A_CON, FALSE);
            break;
        case 22: /* Fountain of snakes! */
            dowatersnakes();
            break;
        case 23: /* Water demon */
            dowaterdemon();
            break;
        case 24: { /* Maybe curse some items */
            struct obj *obj, *nextobj;
            int buc_changed = 0;

            pline("This water's no good!");
            morehungry(rn1(20, 11));
            exercise(A_CON, FALSE);
            /* this is more severe than rndcurse() */
            for (obj = gi.invent; obj; obj = nextobj) {
                nextobj = obj->nobj;
                if (obj->oclass != COIN_CLASS && !obj->cursed && !rn2(5)) {
                    curse(obj);
                    ++buc_changed;
                }
            }
            if (buc_changed)
                update_inventory();
            break;
        }
        case 25: /* See invisible */
            if (Blind) {
                if (Invisible) {
                    You("feel transparent.");
                } else {
                    You("feel very self-conscious.");
                    pline("Then it passes.");
                }
            } else {
                You_see("an image of someone stalking you.");
                pline("But it disappears.");
            }
            incr_itimeout(&HSee_invisible, rn1(1000, 1000));
            newsym(u.ux, u.uy);
            exercise(A_WIS, TRUE);
            rehydrate(rn1(75, 25));
            break;
        case 26: /* See Monsters */
            if (monster_detect((struct obj *) 0, 0))
                pline_The("%s tastes like nothing.", hliquid("water"));
            exercise(A_WIS, TRUE);
            rehydrate(rn1(75, 25));
            break;
        case 27: /* Find a gem in the sparkling waters. */
            if (!FOUNTAIN_IS_LOOTED(u.ux, u.uy)) {
                dofindgem();
                break;
            }
            FALLTHROUGH;
            /*FALLTHRU*/
        case 28: /* Water Nymph */
            dowaternymph();
            break;
        case 29: /* Scare */
        {
            struct monst *mtmp;

            pline("This %s gives you bad breath!",
                  hliquid("water"));
            for (mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
                if (DEADMONSTER(mtmp))
                    continue;
                monflee(mtmp, 0, FALSE, FALSE);
            }
            rehydrate(rn1(75, 25));
            break;
        }
        case 30: /* Gushing forth in this room */
            dogushforth(TRUE);
            rehydrate(rn1(75, 25));
            break;
        default:
            pline("This tepid %s is tasteless.",
                  hliquid("water"));
            rehydrate(rn1(75, 25));
            break;
        }
    }
    dryup(u.ux, u.uy, TRUE);
}

/* Monty Python and the Holy Grail ;) */
static const char *const excalmsgs[] = {
    "had Excalibur thrown at them by some watery tart",
    "received Excalibur from a strange woman laying about in a pond",
    "signified by divine providence, was chosen to carry Excalibur",
    "has been given Excalibur, and now enjoys supreme executive power",
    "endured an absurd aquatic ceremony, and now wields Excalibur"
};

/* dip an object into a fountain when standing on its location */
void
dipfountain(struct obj *obj)
{
    int er = ER_NOTHING;
    boolean is_hands = (obj == &hands_obj);

    if (Levitation) {
        floating_above("fountain");
        return;
    }

    if (obj->otyp == LONG_SWORD && u.ulevel >= 5 && !rn2(6)
        /* once upon a time it was possible to poly N daggers into N swords */
        && obj->quan == 1L && !obj->oartifact
        && !(uarmh && uarmh->otyp == HELM_OF_OPPOSITE_ALIGNMENT)
        && !exist_artifact(LONG_SWORD, artiname(ART_EXCALIBUR))) {
        static const char lady[] = "Lady of the Lake";

        if (u.ualign.type != A_LAWFUL || !Role_if(PM_KNIGHT)) {
            /* Ha!  Trying to cheat her. */
            pline("A freezing mist rises from the %s"
                  " and envelopes the sword.",
                  hliquid("water"));
            pline_The("fountain disappears!");
            curse(obj);
            if (obj->spe > -6 && !rn2(3))
                obj->spe--;
            obj->oerodeproof = FALSE;
            exercise(A_WIS, FALSE);
            livelog_printf(LL_ARTIFACT,
                           "was denied %s!  The %s has deemed %s unworthy",
                           artiname(ART_EXCALIBUR), lady, uhim());
        } else {
            /* The lady of the lake acts! - Eric Backus */
            /* Be *REAL* nice */
            pline(
              "From the murky depths, a hand reaches up to bless the sword.");
            pline("As the hand retreats, the fountain disappears!");
            obj = oname(obj, artiname(ART_EXCALIBUR),
                        ONAME_VIA_DIP | ONAME_KNOW_ARTI);
            discover_artifact(ART_EXCALIBUR);
            bless(obj);
            if (obj->spe < 0) {
                obj->spe = 0;
            }
            obj->oeroded = obj->oeroded2 = 0;
            obj->oerodeproof = TRUE;
            exercise(A_WIS, TRUE);
            livelog_printf(LL_ARTIFACT, "%s", excalmsgs[rn2(SIZE(excalmsgs))]);
        }
        update_inventory();
        set_levltyp(u.ux, u.uy, ROOM); /* updates level.flags.nfountains */
        levl[u.ux][u.uy].flags = 0;
        maybe_unhide_at(u.ux, u.uy);
        newsym(u.ux, u.uy);
        if (in_town(u.ux, u.uy))
            (void) angry_guards(FALSE);
        return;
    } else if (is_hands || obj == uarmg) {
        er = wash_hands();
    } else {
        er = water_damage(obj, NULL, TRUE);
    }

    if (er == ER_DESTROYED || (er != ER_NOTHING && !rn2(2))) {
        return; /* no further effect */
    }

    switch (rnd(30)) {
    case 16: /* Curse the item */
        if (!is_hands && obj->oclass != COIN_CLASS && !obj->cursed) {
            curse(obj);
        }
        break;
    case 17:
    case 18:
    case 19:
    case 20: /* Uncurse the item */
        if (!is_hands && obj->cursed) {
            if (!Blind)
                pline_The("%s glows for a moment.", hliquid("water"));
            uncurse(obj);
        } else {
            pline("A feeling of loss comes over you.");
        }
        break;
    case 21: /* Water Demon */
        dowaterdemon();
        break;
    case 22: /* Water Nymph */
        dowaternymph();
        break;
    case 23: /* an Endless Stream of Snakes */
        dowatersnakes();
        break;
    case 24: /* Find a gem */
        if (!FOUNTAIN_IS_LOOTED(u.ux, u.uy)) {
            dofindgem();
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 25: /* Water gushes forth */
        dogushforth(FALSE);
        break;
    case 26: /* Strange feeling */
        pline("A strange tingling runs up your %s.", body_part(ARM));
        break;
    case 27: /* Strange feeling */
        You_feel("a sudden chill.");
        break;
    case 28: /* Strange feeling */
        if (rn2(50) < ACURR(A_WIS)
            && (Role_if(PM_CAVE_DWELLER) || Role_if(PM_BARBARIAN)
                || Role_if(PM_CARTOMANCER) || Race_if(PM_ORC))) {
            pline("The water smells suspiciously clean.");
            break;
        }
        pline("An urge to take a bath overwhelms you.");
        {
            long money = money_cnt(gi.invent);
            struct obj *otmp, *nextobj;

            if (money > 10) {
                /* Amount to lose.  Might get rounded up as fountains don't
                 * pay change... */
                money = somegold(money) / 10;
                for (otmp = gi.invent; otmp && money > 0; otmp = nextobj) {
                    nextobj = otmp->nobj;
                    if (otmp->oclass == COIN_CLASS) {
                        int denomination = objects[otmp->otyp].oc_cost;
                        long coin_loss =
                            (money + denomination - 1) / denomination;
                        coin_loss = min(coin_loss, otmp->quan);
                        otmp->quan -= coin_loss;
                        money -= coin_loss * denomination;
                        if (!otmp->quan)
                            delobj(otmp);
                    }
                }
                You("lost some of your gold in the fountain!");
                CLEAR_FOUNTAIN_LOOTED(u.ux, u.uy);
                exercise(A_WIS, FALSE);
            }
            rehydrate(rn1(75, 25));
        }
        break;
    case 29: /* You see coins */
        /* We make fountains have more coins the closer you are to the
         * surface.  After all, there will have been more people going
         * by.  Just like a shopping mall!  Chris Woodbury  */

        if (FOUNTAIN_IS_LOOTED(u.ux, u.uy))
            break;
        SET_FOUNTAIN_LOOTED(u.ux, u.uy);
        (void) mkgold((long) (rnd((dunlevs_in_dungeon(&u.uz) - dunlev(&u.uz)
                                   + 1) * 2) + 5),
                      u.ux, u.uy);
        if (!Blind)
            pline("Far below you, you see coins glistening in the %s.",
                  hliquid("water"));
        exercise(A_WIS, TRUE);
        newsym(u.ux, u.uy);
        break;
    default:
        if (er == ER_NOTHING)
            pline1(nothing_seems_to_happen);
        break;
    }
    update_inventory();
    dryup(u.ux, u.uy, TRUE);
}

/* dipping '-' in fountain, pool, or sink */
int
wash_hands(void)
{
    const char *hands = makeplural(body_part(HAND));
    int res = ER_NOTHING;
    boolean was_glib = !!Glib;
    boolean was_goopy = !!(HFumbling & I_SPECIAL);

    if (was_goopy) {
        pline("You wash the goop off your %s.",
            uarmf ? xname(uarmf) : makeplural(body_part(FOOT)));
        make_fumbling(0);
        if (uarmf) {
            uarmf->greased = 0;
            res = water_damage(uarmf, (const char *) 0, TRUE);
            update_inventory();
        }
    } else {
        You("wash your %s%s in the %s.", uarmg ? "gloved " : "", hands,
            hliquid("water"));
        if (Glib) {
            make_glib(0);
            if (uarmg)
                uarmg->greased = 0;
            Your("%s are no longer slippery.", fingers_or_gloves(TRUE));
            update_inventory();
        }
        if (uarmg)
            res = water_damage(uarmg, (const char *) 0, TRUE);
    }
     /* not what ER_GREASED is for, but the checks in dipfountain just
        compare the result to ER_DESTROYED and ER_NOTHING, so it works */
    if ((was_glib || was_goopy) && res == ER_NOTHING)
        res = ER_GREASED;
    rehydrate(rn1(75, 25));
    return res;
}

/* convert a sink into a fountain */
void
breaksink(coordxy x, coordxy y)
{
    if (cansee(x, y) || u_at(x, y))
        pline_The("pipes break!  Water spurts out!");
    /* updates level.flags.nsinks and level.flags.nfountains */
    set_levltyp(x, y, FOUNTAIN);
    levl[x][y].looted = 0;
    levl[x][y].blessedftn = 0;
    SET_FOUNTAIN_LOOTED(x, y);
    maybe_unhide_at(x, y);
    newsym(x, y);
}

void
breaktoilet(coordxy x, coordxy y)
{
    int num = rn1(5, 2);
    struct monst *mtmp;

    if (cansee(x, y) || u_at(x, y))
        pline_The("toilet suddenly shatters!");
    else
        You_hear("something shatter!");
    /* updates level.flags.ntoilets and level.flags.nfountains */
    set_levltyp(x, y, FOUNTAIN);
    levl[x][y].looted = 0;
    levl[x][y].blessedftn = 0;
    SET_FOUNTAIN_LOOTED(x, y);
    maybe_unhide_at(x, y);
    newsym(x, y);

    if (!rn2(3)) {
        if (!(svm.mvitals[PM_BABY_CROCODILE].mvflags & G_GONE)) {
            if (!Blind) {
                if (!Hallucination)
                    pline("Oh no! Crocodiles come out from the pipes!");
                else
                    pline("Oh no! Tons of poopies!");
            } else
                You_hear("something scuttling around you!");
            while (num-- > 0) {
                /* Since toilet can be broken by ranged means, generate
                 * around the broken toilet */
                if ((mtmp = makemon(&mons[PM_BABY_CROCODILE], x, y, NO_MM_FLAGS))
                    && t_at(mtmp->mx, mtmp->my))
                    (void) mintrap(mtmp, NO_TRAP_FLAGS);
            }
        } else
            pline_The("sewers seem strangely quiet.");
    }
}

/* quaff from a sink while standing on its location */
void
drinksink(void)
{
    struct obj *otmp;
    struct monst *mtmp;

    if (Levitation) {
        floating_above("sink");
        return;
    }
    switch (rn2(20)) {
    case 0:
        You("take a sip of very cold %s.", hliquid("water"));
        rehydrate(rn1(75, 25));
        break;
    case 1:
        You("take a sip of very warm %s.", hliquid("water"));
        rehydrate(rn1(75, 25));
        break;
    case 2:
        You("take a sip of scalding hot %s.", hliquid("water"));
        if (fully_resistant(FIRE_RES)) {
            pline("It seems quite tasty.");
            monstseesu(M_SEEN_FIRE);
            rehydrate(rn1(75, 25));
        } else {
            losehp(resist_reduce(rnd(8), FIRE_RES),
                   "sipping boiling water", KILLED_BY);
            monstunseesu(M_SEEN_FIRE);
        }
        /* boiling water burns considered fire damage */
        break;
    case 3:
        if (svm.mvitals[PM_SEWER_RAT].mvflags & G_GONE)
            pline_The("sink seems quite dirty.");
        else {
            mtmp = makemon(&mons[PM_SEWER_RAT], u.ux, u.uy, MM_NOMSG);
            if (mtmp)
                pline("Eek!  There's %s in the sink!",
                      (Blind || !canspotmon(mtmp)) ? "something squirmy"
                                                   : a_monnam(mtmp));
        }
        break;
    case 4:
        for (;;) {
	        /* use Luck here instead of u.uluck */
            if (!rn2(13) && ((Luck >= 0 && maybe_polyd(is_vampire(gy.youmonst.data),
				Race_if(PM_DHAMPIR)))
			    || (Luck <= 0 && !maybe_polyd(is_vampire(gy.youmonst.data),
				Race_if(PM_DHAMPIR))))) {
                otmp = mksobj(POT_VAMPIRE_BLOOD, FALSE, FALSE);
            } else {
                otmp = mkobj(POTION_CLASS, FALSE);
                if (otmp->otyp != POT_WATER)
                    break;
                /* reject water and try again */
                obfree(otmp, (struct obj *) 0);
            }
        }
        otmp->cursed = otmp->blessed = 0;
        pline("Some %s liquid flows from the faucet.",
              Blind ? "odd" : hcolor(OBJ_DESCR(objects[otmp->otyp])));
        otmp->dknown = !(Blind || Hallucination);
        otmp->quan++;       /* Avoid panic upon useup() */
        otmp->fromsink = 1; /* kludge for docall() */
        (void) dopotion(otmp);
        obfree(otmp, (struct obj *) 0);
        break;
    case 5:
        if (!(levl[u.ux][u.uy].looted & S_LRING)) {
            You("find a ring in the sink!");
            (void) mkobj_at(RING_CLASS, u.ux, u.uy, TRUE);
            levl[u.ux][u.uy].looted |= S_LRING;
            exercise(A_WIS, TRUE);
            newsym(u.ux, u.uy);
        } else
            pline("Some dirty %s backs up in the drain.", hliquid("water"));
        break;
    case 6:
        breaksink(u.ux, u.uy);
        break;
    case 7:
        pline_The("%s moves as though of its own will!", hliquid("water"));
        if ((svm.mvitals[PM_WATER_ELEMENTAL].mvflags & G_GONE)
            || !makemon(&mons[PM_WATER_ELEMENTAL], u.ux, u.uy, MM_NOMSG))
            pline("But it quiets down.");
        break;
    case 8:
        pline("Yuk, this %s tastes awful.", hliquid("water"));
        more_experienced(1, 0);
        newexplevel();
        rehydrate(rn1(75, 25));
        break;
    case 9:
        pline("Gaggg... this tastes like sewage!  You vomit.");
        morehungry(rn1(30 - ACURR(A_CON), 11));
        vomit();
        break;
    case 10:
        pline("This %s contains toxic wastes!", hliquid("water"));
        if (!Unchanging) {
            You("undergo a freakish metamorphosis!");
            polyself(POLY_NOFLAGS);
        }
        break;
    /* more odd messages --JJB */
    case 11:
        Soundeffect(se_clanking_pipe, 50);
        You_hear("clanking from the pipes...");
        rehydrate(rn1(75, 25));
        break;
    case 12:
        Soundeffect(se_sewer_song, 100);
        You_hear("snatches of song from among the sewers...");
        rehydrate(rn1(75, 25));
        break;
    case 13:
        pline("Ew, what a stench!");
        create_gas_cloud(u.ux, u.uy, 1, 4);
        break;
    case 19:
        if (Hallucination) {
            pline("From the murky drain, a hand reaches up... --oops--");
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    default:
        You("take a sip of %s %s.",
            rn2(3) ? (rn2(2) ? "cold" : "warm") : "hot",
            hliquid("water"));
        rehydrate(rn1(75, 25));
    }
}

/* for #dip(potion.c) when standing on a sink */
void
dipsink(struct obj *obj)
{
    boolean try_call = FALSE,
            not_looted_yet = (levl[u.ux][u.uy].looted & S_LRING) == 0,
            is_hands = (obj == &hands_obj || (uarmg && obj == uarmg));

    if (!rn2(not_looted_yet ? 25 : 15)) {
        /* can't rely on using sink for unlimited scroll blanking; however,
           since sink will be converted into a fountain, hero can dip again */
        breaksink(u.ux, u.uy); /* "The pipes break!  Water spurts out!" */
        if (Glib && is_hands)
            Your("%s are still slippery.", fingers_or_gloves(TRUE));
        return;
    } else if (is_hands) {
        (void) wash_hands();
        return;
    } else if (obj->oclass != POTION_CLASS) {
        You("hold %s under the tap.", the(xname(obj)));
        if (water_damage(obj, (const char *) 0, TRUE) == ER_NOTHING)
            pline1(nothing_seems_to_happen);
        return;
    }

    /* at this point the object must be a potion */
    You("pour %s%s down the drain.", (obj->quan > 1L ? "one of " : ""),
        the(xname(obj)));
    switch (obj->otyp) {
    case POT_POLYMORPH:
        polymorph_sink();
        try_call = TRUE;
        break;
    case POT_OIL:
        if (!Blind) {
            pline("It leaves an oily film on the basin.");
            try_call = TRUE;
        } else {
            pline1(nothing_seems_to_happen);
        }
        break;
    case POT_ACID:
        /* acts like a drain cleaner product */
        try_call = TRUE;
        if (!Blind) {
            pline_The("drain seems less clogged.");
        } else if (!Deaf) {
            You_hear("a sucking sound.");
        } else {
            pline1(nothing_seems_to_happen);
            try_call = FALSE;
        }
        break;
    case POT_LEVITATION:
        sink_backs_up(u.ux, u.uy);
        try_call = TRUE;
        break;
    case POT_OBJECT_DETECTION:
        if (!(levl[u.ux][u.uy].looted & S_LRING)) {
            You("sense a ring lost down the drain.");
            try_call = TRUE;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case POT_GAIN_LEVEL:
    case POT_GAIN_ENERGY:
    case POT_MONSTER_DETECTION:
    case POT_FRUIT_JUICE:
    case POT_WATER:
        /* potions with no potionbreathe() effects, plus water.  if effects
           are added to potionbreathe these should go to that instead (except
           for water). */
        pline1(nothing_seems_to_happen);
        break;
    default:
        /* hero can feel the vapor on her skin, so no need to check Blind or
           breathless for this message */
        pline("A wisp of vapor rises up...");
        /* NB: potionbreathe calls trycall or makeknown as appropriate */
        if (!breathless(gy.youmonst.data) || haseyes(gy.youmonst.data))
            potionbreathe(obj);
        break;
    }
    if (try_call && obj->dknown)
        trycall(obj);
    useup(obj);
}

/* find a ring in a sink */
void
sink_backs_up(coordxy x, coordxy y)
{
    char buf[BUFSZ];

    if (!Blind)
        Strcpy(buf, "Muddy waste pops up from the drain");
    else if (!Deaf)
        Strcpy(buf, "You hear a sloshing sound"); /* Deaf-aware */
    else
        Sprintf(buf, "Something splashes you in the %s", body_part(FACE));
    pline("%s%s.", !Deaf ? "Flupp!  " : "", buf);

    if (!(levl[x][y].looted & S_LRING)) { /* once per sink */
        if (!Blind)
            You_see("a ring shining in its midst.");
        (void) mkobj_at(RING_CLASS, x, y, TRUE);
        newsym(x, y);
        exercise(A_DEX, TRUE);
        exercise(A_WIS, TRUE); /* a discovery! */
        levl[x][y].looted |= S_LRING;
    }
}

void
breakforge(coordxy x, coordxy y)
{
    if (cansee(x, y) || u_at(x, y))
        pline_The("forge splits in two as molten lava rushes forth!");
    levl[x][y].doormask = 0;
    /* replace the forge with lava */
    set_levltyp(x, y, LAVAPOOL); /* updates level.flags.nforges */
    maybe_unhide_at(x, y);
    newsym(x, y);
}

staticfn void
blowupforge(coordxy x, coordxy y)
{
    if (cansee(x, y) || u_at(x, y))
        pline_The("forge rumbles, then explodes!  Molten lava splashes everywhere!");
    levl[x][y].flags = 0;
    levl[x][y].doormask = 0;

    /* replace the forge with ordinary floor */
    set_levltyp(x, y, LAVAPOOL); /* updates level.flags.nforges */
    explode(u.ux, u.uy, BZ_M_SPELL(ZT_FIRE), resist_reduce(rnd(30), FIRE_RES),
            FORGE_EXPLODE, EXPL_FIERY);
    maybe_unhide_at(x, y);
    newsym(x, y);
}

void
coolforge(int x, int y)
{
    if (cansee(x, y) || u_at(x, y))
        pline_The("lava in the forge cools and solidifies.");
    levl[x][y].doormask = 0;
    set_levltyp(x, y, ROOM); /* updates level.flags.nforges */
    levl[x][y].flags = 0;
    newsym(x, y);
    maybe_unhide_at(x, y);
}

void
drinkforge(void)
{
    if (Levitation) {
        floating_above("forge");
        return;
    }

    /* Assumes that there are no playable likes-fire races! */
    if (!likes_fire(gy.youmonst.data)) {
        pline("Molten lava incinerates its way down your gullet...");
        losehp(Upolyd ? u.mh : u.uhp, "trying to drink molten lava", KILLED_BY);
        return;
    }
    burn_away_slime();
    switch(rn2(20)) {
    case 0:
        pline("You drink some molten lava.  Mmmmm mmm!");
        u.uhunger += rnd(50);
        break;
    case 1:
        breakforge(u.ux, u.uy);
        break;
    case 2:
    case 3:
        pline_The("%s moves as though of its own will!", hliquid("lava"));
        if ((svm.mvitals[PM_FIRE_ELEMENTAL].mvflags & G_GONE)
            || !makemon(&mons[PM_FIRE_ELEMENTAL], u.ux, u.uy, MM_NOMSG))
            pline("But it settles down.");
        break;
    default:
        pline("You take a sip of molten lava.");
        u.uhunger += rnd(5);
    }
}

void
drinktoilet(void)
{
    if (Levitation) {
        floating_above("toilet");
        return;
    }
    if ((gy.youmonst.data->mlet == S_DOG) && (rn2(5))) {
        pline_The("toilet water is quite refreshing!");
        u.uhunger += 10;
        return;
    }

    switch (rn2(9)) {
    case 0:
        if (svm.mvitals[PM_SEWER_RAT].mvflags & G_GONE)
            pline_The("toilet seems quite dirty.");
        else {
            static NEARDATA struct monst *mtmp;

            mtmp = makemon(&mons[PM_SEWER_RAT], u.ux, u.uy, NO_MM_FLAGS);
            pline("Eek!  There's %s in the toilet!",
                Blind ? "something squirmy" : a_monnam(mtmp));
        }
        break;
    case 1:
        breaktoilet(u.ux, u.uy);
        break;
    case 2:
        pline("Something begins to crawl out of the toilet!");
        if (svm.mvitals[PM_BROWN_PUDDING].mvflags & G_GONE
                || !makemon(&mons[PM_BROWN_PUDDING],
                u.ux, u.uy, NO_MM_FLAGS))
            pline("But it slithers back out of sight.");
        break;
    case 3:
        /* New effect borrowed from EvilHack's sewage quaffing. Yech. */
        pline("This %s is foul!", hliquid("sewage"));
        if (how_resistant(SICK_RES) == 100) {
            You_feel("mildly nauseous.");
            losehp(rnd(4), "upset stomach", KILLED_BY_AN);
        }
        poisoned("sewage", A_STR, "drinking raw sewage",
                            rnd(10) + rn1(4, 3), FALSE);
        exercise(A_CON, FALSE);
        break;
    case 4:
        if (svm.mvitals[PM_BABY_CROCODILE].mvflags & G_GONE) {
            pline_The("toilet smells fishy.");
        } else {
            static NEARDATA struct monst *mtmp;
            mtmp = makemon(&mons[PM_BABY_CROCODILE], u.ux,
                     u.uy, NO_MM_FLAGS);
            pline("Egad!  There's %s in the toilet!",
                Blind ? "something squirmy" :
                a_monnam(mtmp));
        }
        break;
    default:
        pline("Gaggg... this tastes like sewage!  You vomit.");
        morehungry(rn1(30 - ACURR(A_CON), 11));
        vomit();
    }
}

void
diptoilet(struct obj *obj)
{
    boolean is_hands = (obj == &hands_obj);

    if (Levitation) {
        floating_above("toilet");
        return;
    }

    if (is_hands || obj == uarmg) {
        wash_hands();
        You("would rather not wash your %s there.",
            makeplural(body_part(HAND)));
        return;
    } else if (obj->otyp == POT_ACID ) {
        /* Acid and water don't mix */
        wake_nearto(u.ux, u.uy, (BOLT_LIM + 1) * (BOLT_LIM + 1));
        exercise(A_STR, FALSE);
        if (!Breathless || haseyes(gy.youmonst.data))
            potionbreathe(obj);
        useupall(obj);
        losehp(1 + rnd(9), /* not physical damage */
                "alchemic blast", KILLED_BY_AN);
        breaktoilet(u.ux, u.uy);
    } else {
        /* unlimited water dipping nerf here:
           potions only turn to sickness */
        if (obj->oclass == POTION_CLASS) {
            if (!Blind && obj->otyp != POT_SICKNESS)
                pline_The("toilet water contaminates your %s.", cxname(obj));
            obj->otyp = POT_SICKNESS;
        } else
            water_damage(obj, NULL, TRUE);
    }

    if (is_poisonable(obj)) {
        if (flags.verbose)
            You("cover it in filth.");
        obj->opoisoned = TRUE;
        update_inventory();
    }
    if (obj->oclass == FOOD_CLASS) {
        if (flags.verbose)
            pline("My! It certainly looks tastier now...");
        obj->orotten = TRUE;
    }
    if (flags.verbose)
        pline("Yuck!");
}

/*fountain.c*/
