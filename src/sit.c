/* NetHack 3.7	sit.c	$NHDT-Date: 1718136168 2024/06/11 20:02:48 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.95 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2012. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"
#include "artifact.h"

staticfn void throne_sit_effect(void);
staticfn int lay_an_egg(void);

/* take away the hero's money */
void
take_gold(void)
{
    struct obj *otmp, *nobj;
    int lost_money = 0;

    for (otmp = gi.invent; otmp; otmp = nobj) {
        nobj = otmp->nobj;
        if (otmp->oclass == COIN_CLASS) {
            lost_money = 1;
            remove_worn_item(otmp, FALSE);
            delobj(otmp);
        }
    }
    if (!lost_money) {
        You_feel("a strange sensation.");
    } else {
        You("notice you have no gold!");
        disp.botl = TRUE;
    }
}

/* maybe do something when hero sits on a throne */
staticfn void
throne_sit_effect(void)
{
    coordxy tx = u.ux, ty = u.uy;
    int learnabout;

    if (rnd(6) > 4) { /* [why so convoluted? it's the same as '!rn2(3)'] */
        int effect = rnd(13);

        if (wizard && !iflags.debug_fuzzer) {
            char buf[BUFSZ];
            int which;

            buf[0] = '\0';
            getlin("Throne sit effect (1..13) [0=random]", buf);
            if (buf[0] == '\033') {
                pline("%s", Never_mind);
                return; /* caller will still cause a move to elapse */
            }
            which = atoi(buf);
            if (which >= 1 && which <= 13)
                effect = which;
        }

        switch (effect) {
        case 1:
            (void) adjattrib(rn2(A_MAX), -rn1(4, 3), FALSE);
            losehp(rnd(10), "cursed throne", KILLED_BY_AN);
            break;
        case 2:
            (void) adjattrib(rn2(A_MAX), 1, FALSE);
            break;
        case 3:
            pline("A%s electric shock shoots through your body!",
                  (!hardly_resistant(SHOCK_RES)) ? "n" : " massive");
            losehp(resist_reduce(rnd(24), SHOCK_RES)  + rnd(6), 
                   "electric chair", KILLED_BY_AN);
            exercise(A_CON, FALSE);
            break;
        case 4:
            You_feel("much, much better!");
            if (Upolyd) {
                if (u.mh >= (u.mhmax - 5))
                    u.mhmax += 4;
                u.mh = u.mhmax;
            }
            if (u.uhp >= (u.uhpmax - 5)) {
                u.uhpmax += 4;
                if (u.uhpmax > u.uhppeak)
                    u.uhppeak = u.uhpmax;
            }
            u.uhp = u.uhpmax;
            u.ucreamed = 0;
            make_blinded(0L, TRUE);
            make_sick(0L, (char *) 0, FALSE, SICK_ALL);
            heal_legs(0);
            disp.botl = TRUE;
            break;
        case 5:
            take_gold();
            break;
        case 6:
            if (u.uluck + rn2(5) < 0) {
                You_feel("your luck is changing.");
                change_luck(1);
            } else {
                  /* overall this equates to a 1.5% chance for a wish */
                if (!rn2(5)) {
                    makewish();
                    /* no farming thrones for multiple wishes */
                    set_levltyp(u.ux, u.uy, ROOM);
                    levl[u.ux][u.uy].flags = 0;
                    pline_The("throne vanishes in a puff of logic.");
                    maybe_unhide_at(u.ux, u.uy);
                    newsym(u.ux, u.uy);
                } else {
                    You_feel("your luck is changing...");
                    change_luck(-1); /* oops */
                }
            }
            break;
        case 7:
            {
                int cnt = rnd(4) + 10;

                /* Magical voice not affected by deafness */
                pline("A voice echoes:");
                SetVoice((struct monst *) 0, 0, 80, voice_throne);
                verbalize("Thine audience hath been summoned, %s!",
                          flags.female ? "Dame" : "Sire");
                while (cnt--)
                    (void) makemon(courtmon(), tx, ty, NO_MM_FLAGS);
                break;
            }
        case 8:
            /* Magical voice not affected by deafness */
            pline("A voice echoes:");
            SetVoice((struct monst *) 0, 0, 80, voice_throne);
            verbalize("By thine Imperious order, %s...",
                      flags.female ? "Dame" : "Sire");
            /* Dungeon wide */
            do_genocide(5, FALSE);	/* REALLY|ONTHRONE, see do_genocide() */
            break;
        case 9:
            /* Magical voice not affected by deafness */
            pline("A voice echoes:");
            SetVoice((struct monst *) 0, 0, 80, voice_throne);
            verbalize(
                 "A curse upon thee for sitting upon this most holy throne!");
            if (Luck > 0) {
                make_blinded(BlindedTimeout + rn1(100, 250), TRUE);
                change_luck((Luck > 1) ? -rnd(2) : -1);
            } else
                rndcurse();
            break;
        case 10:
            if (Luck < 0 || (HSee_invisible & INTRINSIC)) {
                if (svl.level.flags.nommap) {
                    pline("A terrible drone fills your head!");
                    make_confused((HConfusion & TIMEOUT) + (long) rnd(30),
                                  FALSE);
                } else {
                    pline("An image forms in your mind.");
                    do_mapping(4);
                }
            } else {
                /* avoid "vision clears" if hero can't see */
                if (!Blind) {
                    Your("vision becomes clear.");
                } else {
                    int num_of_eyes = eyecount(gy.youmonst.data);
                    const char *eye = body_part(EYE);

                    /* note: 1 eye case won't actually happen--can't
                       sit on throne when poly'd into always-levitating
                       floating eye and can't polymorph into Cyclops */
                    switch (num_of_eyes) { /* 2, 1, or 0 */
                    default:
                    case 2: /* more than 1 eye */
                        eye = makeplural(eye);
                        FALLTHROUGH;
                        /*FALLTHRU*/
                    case 1: /* one eye (Cyclops, floating eye) */
                        Your("%s %s...", eye, vtense(eye, "tingle"));
                        break;
                    case 0: /* no eyes */
                        You("have a very strange feeling in your %s.",
                            body_part(HEAD));
                        break;
                    }
                }
                incr_itimeout(&HSee_invisible, rn1(1000, 1000));
                newsym(u.ux, u.uy);
            }
            break;
        case 11:
            if (Luck < 0) {
                You_feel("threatened.");
                aggravate();
            } else {
                You_feel("a wrenching sensation.");
                tele(); /* teleport him */
            }
            break;
        case 12:
            if (gi.invent) {
                if (u.uluck + rn2(3) > 5) {
                    You("are granted an epiphany!");
                    /* Recursively identify all items in all containers */
                    identify_pack(-1, FALSE);
                } else {
                    You("are granted an insight!");
                    /* rn2(5) agrees w/seffects() */
                    identify_pack(rn2(5), FALSE);
                }
            }
            break;
        case 13:
            Your("mind turns into a pretzel!");
            make_confused((HConfusion & TIMEOUT) + (long) rn1(7, 16),
                          FALSE);
            break;
        default:
            impossible("throne effect");
            break;
        }
    } else {
        if (!rn2(2)) {
            /* Learn something interesting */
            learnabout = learnme();
            if (learnabout)
                You("suddenly receive knowledge of %s.",
                    makeplural(simple_typename(learnabout)));
        } else if (is_prince(gy.youmonst.data) || u.uevent.uhand_of_elbereth)
            You_feel("very comfortable here.");
        else
            You_feel("somehow out of place...");
    }

    /* 3.7: when the random chance for removal is hit, ask for confirmation
       if in wizard mode, and remove the throne even if hero was teleported
       away from it.  [This used to remove a throne at hero's current
       location if there happened to be one, so for the teleport case that
       only happened when teleporting back to the same point where hero
       started from.]  "Analyzing a throne" doesn't really make any sense
       but if the answer is yes than it will vanish in a puff of logic. */
    if (!rn2(3) && (!wizard || y_n("Analyze throne?") == 'y')) {
        levl[tx][ty].typ = ROOM, levl[tx][ty].flags = 0;
        maybe_unhide_at(tx, ty);
        map_background(tx, ty, FALSE);
        newsym_force(tx, ty);
        /* "[God] promptly vanishes in a puff of logic" is from
           Douglas Adams' _The_Hitchhiker's_Guide_to_the_Galaxy_. */
        pline_The("throne %s in a puff of logic.",
                  cansee(tx, ty) ? "vanishes" : "has vanished");
    }
}

/* hero lays an egg */
staticfn int
lay_an_egg(void)
{
    struct obj *uegg;

    if (!flags.female) {
        pline("%s can't lay eggs!",
              Hallucination
              ? "You may think you are a platypus, but a male still"
              : "Males");
        return ECMD_OK;
    } else if (u.uhunger < (int) objects[EGG].oc_nutrition) {
        You("don't have enough energy to lay an egg.");
        return ECMD_OK;
    } else if (eggs_in_water(gy.youmonst.data)) {
        if (!(Underwater || Is_waterlevel(&u.uz))) {
            pline("A splash tetra you are not.");
            return ECMD_OK;
        }
        if (Upolyd
            && (gy.youmonst.data == &mons[PM_GIANT_EEL]
                || gy.youmonst.data == &mons[PM_ELECTRIC_EEL])) {
            You("yearn for the Sargasso Sea.");
            return ECMD_OK;
        }
    }
    uegg = mksobj(EGG, FALSE, FALSE);
    uegg->spe = 1;
    uegg->quan = 1L;
    uegg->owt = weight(uegg);
    /* this sets hatch timers if appropriate */
    set_corpsenm(uegg, egg_type_from_parent(u.umonnum, FALSE));
    uegg->known = uegg->dknown = 1;
    You("%s an egg.", eggs_in_water(gy.youmonst.data) ? "spawn" : "lay");
    dropy(uegg);
    stackobj(uegg);
    morehungry((int) objects[EGG].oc_nutrition);
    return ECMD_TIME;
}

/* #sit command */
int
dosit(void)
{
    static const char sit_message[] = "sit on the %s.";
    struct trap *trap = t_at(u.ux, u.uy);
    int typ = levl[u.ux][u.uy].typ;

    if (u.usteed) {
        You("are already sitting on %s.", mon_nam(u.usteed));
        return ECMD_OK;
    }
    if (u.uundetected && is_hider(gy.youmonst.data)
        && u.umonnum != PM_TRAPPER) /* trapper can stay hidden on floor */
        u.uundetected = 0; /* no longer on the ceiling */

    if (!can_reach_floor(FALSE)) {
        if (u.uswallow)
            There("are no seats in here!");
        else if (Levitation)
            You("tumble in place.");
        else
            You("are sitting on air.");
        return ECMD_OK;
    } else if (u.ustuck && !sticks(gy.youmonst.data)) {
        /* holding monster is next to hero rather than beneath, but
           hero is in no condition to actually sit at has/her own spot */
        if (humanoid(u.ustuck->data))
            pline("%s won't offer %s lap.", Monnam(u.ustuck), mhis(u.ustuck));
        else
            pline("%s has no lap.", Monnam(u.ustuck));
        return ECMD_OK;
    } else if (is_damp_terrain(u.ux, u.uy) && !Underwater) { /* water walking */
        goto in_water;
    } else if (Upolyd && u.umonnum == PM_GREMLIN
               && (levl[u.ux][u.uy].typ == FOUNTAIN || is_damp_terrain(u.ux, u.uy))) {
        goto in_water;
    }

    u_wipe_engr(rnd(5));
    
    if (OBJ_AT(u.ux, u.uy)
        /* ensure we're not standing on the precipice */
        && !(uteetering_at_seen_pit(trap) || uescaped_shaft(trap))) {
        struct obj *obj;

        obj = svl.level.objects[u.ux][u.uy];
        if (gy.youmonst.data->mlet == S_DRAGON && obj->oclass == COIN_CLASS) {
            You("coil up around your %shoard.",
                (obj->quan + money_cnt(gi.invent) < u.ulevel * 1000)
                ? "meager " : "");
        } else if (obj->otyp == TOWEL) {
            pline("It's probably not a good time for a picnic...");
        } else {
            if (slithy(gy.youmonst.data))
                You("coil up around %s.", the(xname(obj)));
            else
                You("sit on %s.", the(xname(obj)));
            if (obj->otyp == CORPSE && amorphous(&mons[obj->corpsenm]))
                pline("It's squishy...");
            else if (obj->otyp == CREAM_PIE) {
                 if (!Deaf) {
                   Soundeffect(se_squelch, 30);
                   pline("Squelch!");
                }
                useupf(obj, obj->quan);
            } else if (!(Is_box(obj)
                         || objects[obj->otyp].oc_material == CLOTH))
                pline("It's not very comfortable...");
        }
    } else if (trap != 0 || (u.utrap && (u.utraptype >= TT_LAVA))) {
        if (u.utrap) {
            exercise(A_WIS, FALSE); /* you're getting stuck longer */
            if (u.utraptype == TT_BEARTRAP) {
                You_cant("sit down with your %s in the bear trap.",
                         body_part(FOOT));
                u.utrap++;
            } else if (u.utraptype == TT_PIT) {
                if (trap && trap->ttyp == SPIKED_PIT) {
                    You("sit down on a spike.  Ouch!");
                    losehp(Half_physical_damage ? rn2(2) : 1,
                           "sitting on an iron spike", KILLED_BY);
                    exercise(A_STR, FALSE);
                } else
                    You("sit down in the pit.");
                u.utrap += rn2(5);
            } else if (u.utraptype == TT_WEB) {
                You("sit in the spider web and get entangled further!");
                u.utrap += rn1(10, 5);
            } else if (u.utraptype == TT_LAVA) {
                /* Must have fire resistance or they'd be dead already */
                You("sit in the %s!", hliquid("lava"));
                if (Slimed)
                    burn_away_slime();
                u.utrap += rnd(4);
                losehp(d(2, 10), "sitting in lava",
                       KILLED_BY); /* lava damage */
            } else if (u.utraptype == TT_INFLOOR
                       || u.utraptype == TT_BURIEDBALL) {
                You_cant("maneuver to sit!");
                u.utrap++;
            }
        } else {
            /* when flying, "you land" might need some refinement; it sounds
               as if you're staying on the ground but you will immediately
               take off again unless you become stuck in a holding trap */
            You("%s.", Flying ? "land" : "sit down");
            dotrap(trap, VIASITTING);
        }
    } else if ((Underwater || Is_waterlevel(&u.uz))
                && !eggs_in_water(gy.youmonst.data)) {
        if (Is_waterlevel(&u.uz))
            There("are no cushions floating nearby.");
        else
            You("sit down on the muddy bottom.");
    } else if (is_damp_terrain(u.ux, u.uy) && !eggs_in_water(gy.youmonst.data)) {
 in_water:
        You("sit in the %s.", hliquid("water"));
        if (Upolyd && u.umonnum == PM_GREMLIN) {
            if (split_mon(&gy.youmonst, (struct monst *) 0)) {
                if (levl[u.ux][u.uy].typ == FOUNTAIN)
                    dryup(u.ux, u.uy, TRUE);
            }
        } else if (maybe_polyd(is_grung(gy.youmonst.data), Race_if(PM_GRUNG))) {
            if (rehydrate(FALSE)) {
                if (levl[u.ux][u.uy].typ == FOUNTAIN)
                    dryup(u.ux, u.uy, TRUE);
                else
                    dryup_puddle(u.ux, u.uy, "dries up");
            }
            /* splitting--or failing to do so--protects gear from the water */
        } else {
            if (!rn2(10) && uarm)
                (void) water_damage(uarm, "armor", TRUE);
            if (!rn2(10) && uarmf && uarmf->otyp != WATER_WALKING_BOOTS)
                (void) water_damage(uarmf, "armor", TRUE);
            dryup_puddle(u.ux, u.uy, "dries up");
        }
    } else if (IS_FOUNTAIN(typ)) {
        You(sit_message, defsyms[S_sink].explanation);
        Your("%s gets wet.",
             humanoid(gy.youmonst.data) ? "rump" : "underside");
        if (maybe_polyd(is_grung(gy.youmonst.data), Race_if(PM_GRUNG))) {
            if (rehydrate(FALSE))
                dryup(u.ux, u.uy, TRUE);
        }
    } else if (IS_SINK(typ)) {
        You(sit_message, defsyms[S_sink].explanation);
        Your("%s gets wet.",
             humanoid(gy.youmonst.data) ? "rump" : "underside");
    } else if (IS_TOILET(typ)) {
        You(sit_message, defsyms[S_toilet].explanation);

        if (maybe_polyd(is_giant(gy.youmonst.data), Race_if(PM_GIANT))) {
            breaktoilet(u.ux, u.uy);
        } else if (!Sick && u.uhs > 0
                && (Upolyd ? u.mh == u.mhmax : u.uhp == u.uhpmax)) {
            You("don't have to go...");
        } else {
            if (is_crude())
                You("miss...");
            else
                You("grunt.");
            if (Sick)
                make_sick(0L, (char *) 0, TRUE, SICK_ALL);
            if (u.uhs == 0)
                morehungry(rn2(400) + 200);
            /* Like the fourk bench */
            if (Upolyd)
                u.mh = u.mhmax;
            else
                u.uhp = u.uhpmax;
            /* Luck based chance of toilet breaking, very low with positive luck */
            if (rnl(4) == 3)
                breaktoilet(u.ux, u.uy);

        }
    } else if (IS_FORGE(typ)) {
        You(sit_message, defsyms[S_forge].explanation);
        burn_away_slime();
        if (likes_fire(gy.youmonst.data) || fully_resistant(FIRE_RES)) {
            pline_The("forge feels nice and warm.");
            return 1;
        }
        pline("Argh!  This forge is hot!");
        losehp(resist_reduce(d(4, 4), FIRE_RES), /* lava damage */
               "sitting on a forge", KILLED_BY);
    } else if (IS_ALTAR(typ)) {
        You(sit_message, defsyms[S_altar].explanation);
        altar_wrath(u.ux, u.uy);
    } else if (IS_GRAVE(typ)) {
        You(sit_message, defsyms[S_grave].explanation);
    } else if (typ == STAIRS) {
        You(sit_message, "stairs");
    } else if (typ == LADDER) {
        You(sit_message, "ladder");
    } else if (is_lava(u.ux, u.uy)) {
        /* must be WWalking */
        You(sit_message, hliquid("lava"));
        burn_away_slime();
        if (likes_lava(gy.youmonst.data)) {
            pline_The("%s feels warm.", hliquid("lava"));
            return ECMD_TIME;
        }
        pline_The("%s burns you!", hliquid("lava"));
        losehp(resist_reduce(d(8, 10),
               FIRE_RES) + d(2, 10), /* lava damage */
               "sitting on lava", KILLED_BY);
    } else if (is_ice(u.ux, u.uy)) {
        You(sit_message, defsyms[S_ice].explanation);
        if (hardly_resistant(COLD_RES))
            pline_The("ice feels cold.");
    } else if (typ == DRAWBRIDGE_DOWN) {
        You(sit_message, "drawbridge");
    } else if (IS_THRONE(typ)) {
        You(sit_message, defsyms[S_throne].explanation);
        throne_sit_effect();
    } else if (lays_eggs(gy.youmonst.data)) {
        return lay_an_egg();
    } else {
        pline("Having fun sitting on the %s?", surface(u.ux, u.uy));
    }
    return ECMD_TIME;
}

/* curse a few inventory items at random! */
void
rndcurse(void)
{
    int nobj = 0;
    int cnt, onum;
    struct obj *otmp;
    static const char mal_aura[] = "feel a malignant aura surround %s.";

    if (u_wield_art(ART_MAGICBANE) && rn2(20)) {
        You(mal_aura, "the magic-absorbing staff");
        return;
    }
    if (u_wield_art(ART_LOAD_BRAND) && rn2(20)) {
        You(mal_aura, "the heavy sword");
        return;
    }
    if (Antimagic) {
        shieldeff(u.ux, u.uy);
        You(mal_aura, "you");
    }

    for (otmp = gi.invent; otmp; otmp = otmp->nobj) {
        /* gold isn't subject to being cursed or blessed */
        if (otmp->oclass == COIN_CLASS)
            continue;
        nobj++;
    }
    if (nobj) {
        for (cnt = rnd(6 / ((!!Antimagic) + (!!Half_spell_damage) + 1));
             cnt > 0; cnt--) {
            char Your_buf[BUFSZ];
            onum = rnd(nobj);
            for (otmp = gi.invent; otmp; otmp = otmp->nobj) {
                /* as above */
                if (otmp->oclass == COIN_CLASS)
                    continue;
                if (--onum == 0)
                    break; /* found the target */
            }
            /* the !otmp case should never happen; picking an already
               cursed item happens--avoid "resists" message in that case */
            if (!otmp || otmp->cursed)
                continue; /* next target */

            if (otmp->oartifact && spec_ability(otmp, SPFX_INTEL)
                && rn2(10) < 8) {
                pline("%s!", Tobjnam(otmp, "resist"));
                continue;
            }

            /* Tell the player what was cursed please. */
            if (!Blind) 
                Shk_Your(Your_buf, otmp);

            if (otmp->blessed) {
                if (!Blind) {
                    pline("%s%s %s.",
                          Your_buf,
                          aobjnam(otmp, "glow"),
                          hcolor("brown"));
                }
                unbless(otmp);
            } else {
                if (!Blind) {
                    pline("%s%s with %s aura.",
                          Your_buf,
                          aobjnam(otmp, "glow"),
                          an(hcolor("black")));
                }
                curse(otmp);
            }
            otmp->bknown = TRUE;
        }
        update_inventory();
    }

    /* treat steed's saddle as extended part of hero's inventory */
    if (u.usteed && !rn2(4) && (otmp = which_armor(u.usteed, W_SADDLE)) != 0
        && !otmp->cursed) { /* skip if already cursed */
        if (otmp->blessed)
            unbless(otmp);
        else
            curse(otmp);
        if (!Blind) {
            pline("%s %s.", Yobjnam2(otmp, "glow"),
                  hcolor(otmp->cursed ? NH_BLACK : (const char *) "brown"));
            otmp->bknown = Hallucination ? 0 : 1; /* bypass set_bknown() */
        } else {
            otmp->bknown = 0; /* bypass set_bknown() */
        }
    }
}


void
mrndcurse(struct monst *mtmp) /* curse a few inventory items at random! */
{
    int nobj = 0;
    int cnt, onum;
    struct obj *otmp;
    struct obj *mwep = MON_WEP(mtmp);
    static const char mal_aura[] = "feel a malignant aura surround %s.";

    boolean resists = resist(mtmp, 0, 0, FALSE),
            vis = couldsee(mtmp->mx, mtmp->my);

    if (mwep && mwep->oartifact == ART_MAGICBANE && rn2(20)) {
        if (vis)
            You(mal_aura, "the magic-absorbing staff");
        return;
    }
    if (mwep && mwep->oartifact == ART_LOAD_BRAND && rn2(20)) {
        if (vis)
            You(mal_aura, "the magic-absorbing staff");
        return;
    }

    if (vis && resists) {
        shieldeff(mtmp->mx, mtmp->my);
        You(mal_aura, mon_nam(mtmp));
    }

    for (otmp = mtmp->minvent; otmp; otmp = otmp->nobj) {
        /* gold isn't subject to being cursed or blessed */
        if (otmp->oclass == COIN_CLASS)
            continue;
        nobj++;
    }

    if (nobj) {
        for (cnt = rnd(6 / ((!!resists) + 1)); cnt > 0; cnt--) {
            onum = rnd(nobj);
            for (otmp = mtmp->minvent; otmp; otmp = otmp->nobj) {
                /* as above */
                if (otmp->oclass == COIN_CLASS)
                    continue;
                if (--onum == 0)
                    break; /* found the target */
            }
            /* the !otmp case should never happen; picking an already
               cursed item happens--avoid "resists" message in that case */
            if (!otmp || otmp->cursed)
                continue; /* next target */

            if (otmp->oartifact
                && spec_ability(otmp, SPFX_INTEL) && rn2(10) < 8) {
                if (vis)
                    pline("%s!", Tobjnam(otmp, "resist"));
                continue;
            }

            if (otmp->blessed)
                unbless(otmp);
            else
                curse(otmp);
        }
    }
}

/* remove a random INTRINSIC ability from hero.
   returns the intrinsic property which was removed,
   or 0 if nothing was removed. */
int
attrcurse(void)
{
    int ret = 0;

    switch (rnd(14)) {
    case 1:
        if (HFire_resistance) {
            HFire_resistance =
                HFire_resistance & (TIMEOUT | FROMOUTSIDE | HAVEPARTIAL);
            decr_resistance(&HFire_resistance, rnd(25) + 25);
            You_feel("warmer.");
            ret = FIRE_RES;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 2:
        if (HTeleportation & INTRINSIC) {
            HTeleportation &= ~INTRINSIC;
            You_feel("less jumpy.");
            ret = TELEPORT;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 3:
        if (HPoison_resistance) {
            HPoison_resistance =
                HPoison_resistance & (TIMEOUT | FROMOUTSIDE | HAVEPARTIAL);
            decr_resistance(&HPoison_resistance, rnd(25) + 25);
            You_feel("a little sick!");
            ret = POISON_RES;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 4:
        if (HTelepat & INTRINSIC) {
            HTelepat &= ~INTRINSIC;
            if (Blind && !Blind_telepat)
                see_monsters(); /* Can't sense mons anymore! */
            Your("senses fail!");
            ret = TELEPAT;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 5:
        if (HCold_resistance) {
            HCold_resistance =
                HCold_resistance & (TIMEOUT | FROMOUTSIDE | HAVEPARTIAL);
            decr_resistance(&HCold_resistance, rnd(25) + 25);
            You_feel("cooler.");
            ret = COLD_RES;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 6:
        if (HInvis & INTRINSIC) {
            HInvis &= ~INTRINSIC;
            You_feel("paranoid.");
            ret = INVIS;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 7:
        if (HSee_invisible & INTRINSIC) {
            HSee_invisible &= ~INTRINSIC;
            if (!See_invisible) {
                set_mimic_blocking();
                see_monsters();
                /* might not be able to see self anymore */
                newsym(u.ux, u.uy);
            }
            You("%s!", Hallucination ? "tawt you taw a puttie tat"
                                     : "thought you saw something");
            ret = SEE_INVIS;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 8:
        if (HFast & INTRINSIC) {
            HFast &= ~INTRINSIC;
            You_feel("slower.");
            ret = FAST;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 9:
        if (HStealth & INTRINSIC) {
            HStealth &= ~INTRINSIC;
            You_feel("clumsy.");
            ret = STEALTH;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 10:
        /* intrinsic protection is just disabled, not set back to 0 */
        if (HProtection & INTRINSIC) {
            HProtection &= ~INTRINSIC;
            You_feel("vulnerable.");
            ret = PROTECTION;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 11:
        if (HAggravate_monster & TIMEOUT) {
            HAggravate_monster &= ~TIMEOUT;
            You_feel("less attractive.");
            ret = AGGRAVATE_MONSTER;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 12:
        if (HSleep_resistance) {
            HSleep_resistance =
                HSleep_resistance & (TIMEOUT | FROMOUTSIDE | HAVEPARTIAL);
            decr_resistance(&HSleep_resistance, rnd(25) + 25);
            You_feel("a little tired.");
            ret = SLEEP_RES;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 13:
        if (HDisint_resistance) {
            HDisint_resistance =
                HDisint_resistance & (TIMEOUT | FROMOUTSIDE | HAVEPARTIAL);
            decr_resistance(&HDisint_resistance, rnd(25) + 25);
            You_feel("less firm.");
            ret = DISINT_RES;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 14:
        if (HShock_resistance) {
            HShock_resistance =
                HShock_resistance & (TIMEOUT | FROMOUTSIDE | HAVEPARTIAL);
            decr_resistance(&HShock_resistance, rnd(25) + 25);
            You_feel("more conductive.");
            ret = SHOCK_RES;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    default:
        break;
    }
    return ret;
}

/*sit.c*/
