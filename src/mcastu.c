/* NetHack 3.7	mcastu.c	$NHDT-Date: 1726168598 2024/09/12 19:16:38 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.105 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2011. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"

/* monster mage spells */
enum mcast_mage_spells {
    MGC_PSI_BOLT = 0,
    MGC_FIRE_BOLT,
    MGC_ICE_BOLT,
    MGC_CURE_SELF,
    MGC_HASTE_SELF,
    MGC_STUN_YOU,
    MGC_DISAPPEAR,
    MGC_WEAKEN_YOU,
    MGC_DESTRY_ARMR,
    MGC_EVIL_EYE,
    MGC_CURSE_ITEMS,
    MGC_AGGRAVATION,
    MGC_ACID_BLAST,
    MGC_SUMMON_MONS,
    MGC_CLONE_WIZ,
    MGC_REFLECTION,
    MGC_DEATH_TOUCH,
    MGC_CALL_UNDEAD,
    MGC_ENTOMB
};

/* monster cleric spells */
enum mcast_cleric_spells {
    CLC_OPEN_WOUNDS = 0,
    CLC_CURE_SELF,
    CLC_PROTECTION,
    CLC_CONFUSE_YOU,
    CLC_PARALYZE,
    CLC_BLIND_YOU,
    CLC_INSECTS,
    CLC_CURSE_ITEMS,
    CLC_LIGHTNING,
    CLC_FIRE_PILLAR,
    CLC_GEYSER,
    CLC_BLIGHT,
    CLC_HOBBLE,
    CLC_SPHERES, /* Only for orb weavers */
};

extern const char *const flash_types[]; /* from zap.c */

staticfn void cursetxt(struct monst *, boolean);
staticfn int choose_magic_spell(struct monst *, int);
staticfn int choose_clerical_spell(struct monst *, int);
staticfn int m_cure_self(struct monst *, int);
staticfn int cast_wizard_spell(struct monst *, struct monst *, int, int);
staticfn int cast_cleric_spell(struct monst *, struct monst *, int, int);
staticfn boolean is_undirected_spell(unsigned int, int);
staticfn boolean spell_would_be_useless(struct monst *, unsigned int, int);
staticfn boolean mspell_would_be_useless(struct monst *,
                                        struct monst *, unsigned int, int);
staticfn boolean is_entombed(coordxy, coordxy);
staticfn boolean counterspell(struct monst *);
staticfn int rnd_sphere(void);

/* feedback when frustrated monster couldn't cast a spell */
staticfn void
cursetxt(struct monst *caster, boolean undirected)
{
    if (canseemon(caster) && couldsee(caster->mx, caster->my)) {
        const char *point_msg; /* spellcasting monsters are impolite */

        if (undirected)
            point_msg = "all around, then curses";
        else if ((Invis && !mon_prop(caster, SEE_INVIS)
                  && (caster->mux != u.ux || caster->muy != u.uy))
                 || is_obj_mappear(&gy.youmonst, STRANGE_OBJECT)
                 || u.uundetected)
            point_msg = "and curses in your general direction";
        else if (Displaced && (caster->mux != u.ux || caster->muy != u.uy))
            point_msg = "and curses at your displaced image";
        else
            point_msg = "at you, then curses";

        pline_mon(caster, "%s points %s.", Monnam(caster), point_msg);
    } else if ((!(svm.moves % 4) || !rn2(4))) {
        if (!Deaf)
            Norep("You hear a mumbled curse.");   /* Deaf-aware */
    }
}

/* convert a level-based random selection into a specific mage spell;
   inappropriate choices will be screened out by spell_would_be_useless() */
staticfn int
choose_magic_spell(struct monst* caster, int spellval)
{
    /* for 3.4.3 and earlier, val greater than 22 selected default spell */
    while (spellval > 24 && rn2(25))
        spellval = rn2(spellval);

    /* Low HP, prioritize healing */
    if ((caster->mhp * 4) <= caster->mhpmax) {
        if ((!rn2(10) || caster->mflee) && caster->m_lev > 10)
            return MGC_ENTOMB;
        return MGC_CURE_SELF;
    }

    switch (spellval) {
    case 24:
    case 23:
        switch (rnd(3)) {
        case 1: return MGC_FIRE_BOLT;
        case 2: return MGC_ICE_BOLT;
        default:
            if (Antimagic || Hallucination)
                return MGC_PSI_BOLT;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case 22:
    case 21:
        return MGC_DEATH_TOUCH;
    case 20:
    case 19:
        return MGC_CLONE_WIZ;
    case 18:
    case 17:
        return MGC_SUMMON_MONS;
    case 16:
        return MGC_CALL_UNDEAD;
    case 15:
        return MGC_ACID_BLAST;
    case 14:
    case 13:
        return MGC_AGGRAVATION;
    case 12:
        return MGC_REFLECTION;
    case 11:
    case 10:
        return MGC_CURSE_ITEMS;
    case 9:
    case 8:
        if (caster->mflee)
            return MGC_ENTOMB;
        return MGC_DESTRY_ARMR;
    case 7:
    case 6:
        if (!rn2(2))
            return MGC_EVIL_EYE;
        else
            return MGC_WEAKEN_YOU;
        break;
    case 5:
        return MGC_FIRE_BOLT;
    case 4:
        return MGC_DISAPPEAR;
    case 3:
        return MGC_STUN_YOU;
    case 2:
        return MGC_HASTE_SELF;
    case 1:
        return MGC_CURE_SELF;
    case 0:
    default:
        switch (rnd(3)) {
        case 1: return MGC_FIRE_BOLT;
        case 2: return MGC_ICE_BOLT;
        default:
            return MGC_PSI_BOLT;
        }
    }
}

/* convert a level-based random selection into a specific cleric spell */
staticfn int
choose_clerical_spell(struct monst* caster, int spellnum)
{
    /* for 3.4.3 and earlier, num greater than 13 selected the default spell
     */
    while (spellnum > 15 && rn2(16))
        spellnum = rn2(spellnum);

    /* Low HP, prioritize healing */
    if ((caster->mhp * 4) <= caster->mhpmax)
        spellnum = 1;

    if (caster->data == &mons[PM_ARCH_VILE] && spellnum != 1)
        return CLC_FIRE_PILLAR;

    if (caster->data == &mons[PM_ORB_WEAVER] && spellnum != 1) {
        if (rn2(4))
            return CLC_PROTECTION;
        else
            return CLC_SPHERES;
    }

    switch (spellnum) {
    case 15:
    case 14:
        if (rn2(3))
            return CLC_OPEN_WOUNDS;
        FALLTHROUGH;
        /*FALLTHRU*/
    case 13:
        return CLC_GEYSER;
    case 12:
        return CLC_FIRE_PILLAR;
    case 11:
        return CLC_LIGHTNING;
    case 10:
        return CLC_BLIGHT;
    case 9:
        return CLC_CURSE_ITEMS;
    case 8:
        return CLC_INSECTS;
    case 7:
    case 6:
        return CLC_BLIND_YOU;
    case 5:
        return CLC_HOBBLE;
    case 4:
        return CLC_PARALYZE;
    case 3:
        return CLC_CONFUSE_YOU;
    case 2:
        return CLC_PROTECTION;
    case 1:
        return CLC_CURE_SELF;
    case 0:
    default:
        return CLC_OPEN_WOUNDS;
    }
}

/* return values:
 * 1: successful spell
 * 0: unsuccessful spell
 */
int
castmu(
    struct monst *caster,   /* caster */
    struct attack *mattk, /* caster's current attack */
    boolean thinks_it_foundyou,    /* might be mistaken if displaced */
    boolean foundyou)              /* knows hero's precise location */
{
    int dmg, ml = caster->m_lev;
    int ret;
    int spellnum = 0;

    /* Three cases:
     * -- monster is attacking you.  Search for a useful spell.
     * -- monster thinks it's attacking you.  Search for a useful spell,
     *    without checking for undirected.  If the spell found is directed,
     *    it fails with cursetxt() and loss of mspec_used.
     * -- monster isn't trying to attack.  Select a spell once.  Don't keep
     *    searching; if that spell is not useful (or if it's directed),
     *    return and do something else.
     * Since most spells are directed, this means that a monster that isn't
     * attacking casts spells only a small portion of the time that an
     * attacking monster does.
     */
    if ((mattk->adtyp == AD_SPEL || mattk->adtyp == AD_CLRC) && ml) {
        int cnt = 40;

        do {
            spellnum = rn2(ml);
            if (mattk->adtyp == AD_SPEL)
                spellnum = choose_magic_spell(caster, spellnum);
            else
                spellnum = choose_clerical_spell(caster, spellnum);
            /* not trying to attack?  don't allow directed spells */
            if (!thinks_it_foundyou) {
                if (!is_undirected_spell(mattk->adtyp, spellnum)
                    || spell_would_be_useless(caster, mattk->adtyp, spellnum)) {
                    if (foundyou)
                        impossible(
                       "spellcasting monster found you and doesn't know it?");
                    return M_ATTK_MISS;
                }
                break;
            }
        } while (--cnt > 0
                 && spell_would_be_useless(caster, mattk->adtyp, spellnum));
        if (cnt == 0)
            return M_ATTK_MISS;
    }

    /* monster unable to cast spells? */
    if (caster->mcan || caster->mspec_used || !ml
        || m_seenres(caster, cvt_adtyp_to_mseenres(mattk->adtyp))) {
        cursetxt(caster, is_undirected_spell(mattk->adtyp, spellnum));
        return M_ATTK_MISS;
    }

    if (mattk->adtyp == AD_SPEL || mattk->adtyp == AD_CLRC) {
        /* monst->m_lev is unsigned (uchar), monst->mspec_used is int */
        caster->mspec_used = (int) ((caster->m_lev < 8) ? (10 - caster->m_lev) : 2);
    }

    /* Monster can cast spells, but is casting a directed spell at the
     * wrong place?  If so, give a message, and return.
     * Do this *after* penalizing mspec_used.
     *
     * FIXME?
     *  Shouldn't wall of lava have a case similar to wall of water?
     *  And should cold damage hit water or lava instead of missing
     *  even when the caster has targeted the wrong spot?  Likewise
     *  for fire mis-aimed at ice.
     */
    if (!foundyou && thinks_it_foundyou
        && !is_undirected_spell(mattk->adtyp, spellnum)) {
        pline_mon(caster, "%s casts a spell at %s!",
                 canseemon(caster) ? Monnam(caster) : "Something",
                 is_waterwall(caster->mux, caster->muy) ? "empty water"
                                                    : "thin air");
        return M_ATTK_MISS;
    }

    nomul(0);
    if (rn2(ml * 10) < (caster->mconf ? 100 : 20)) { /* fumbled attack */
        Soundeffect(se_air_crackles, 60);
        if (canseemon(caster) && !Deaf) {
            set_msg_xy(caster->mx, caster->my);
            pline_The("air crackles around %s.", mon_nam(caster));
        }
        return M_ATTK_MISS;
    }

    if (canspotmon(caster) || !is_undirected_spell(mattk->adtyp, spellnum)) {
        pline_mon(caster, "%s casts a spell%s!",
                 canspotmon(caster) ? Monnam(caster) : "Something",
                 is_undirected_spell(mattk->adtyp, spellnum) ? ""
                 : (Invis && !mon_prop(caster, SEE_INVIS)
                    && !u_at(caster->mux, caster->muy))
                   ? " at a spot near you"
                   : (Displaced && !u_at(caster->mux, caster->muy))
                     ? " at your displaced image"
                     : " at you");
    }

    if (u_wield_art(ART_SERENITY) || u_offhand_art(ART_SERENITY)
            || (uarms && uarms->otyp == ANTI_MAGIC_SHIELD)) {
        if (counterspell(caster))
            return 0;
    }

    /*
     * As these are spells, the damage is related to the level
     * of the monster casting the spell.
     */
    if (!foundyou) {
        dmg = 0;
        if (mattk->adtyp != AD_SPEL && mattk->adtyp != AD_CLRC) {
            impossible(
              "%s casting non-hand-to-hand version of hand-to-hand spell %d?",
                       Monnam(caster), mattk->adtyp);
            return M_ATTK_MISS;
        }
    } else if (mattk->damd)
        dmg = d((int) ((ml / 2) + mattk->damn), (int) mattk->damd);
    else
        dmg = d((int) ((ml / 2) + 1), 6);
    if (Half_spell_damage)
        dmg = (dmg + 1) / 2;

    ret = M_ATTK_HIT;
    /*
     * FIXME: none of these hit the steed when hero is riding, nor do
     *  they inflict damage on carried items.
     */
    switch (mattk->adtyp) {
    case AD_FIRE:
        pline("You're enveloped in flames.");
        if (fully_resistant(FIRE_RES)) {
            shieldeff(u.ux, u.uy);
            pline("But you resist the effects.");
            monstseesu(M_SEEN_FIRE);
            dmg = 0;
        } else {
            dmg = resist_reduce(dmg, FIRE_RES);
            monstunseesu(M_SEEN_FIRE);
        }
        burn_away_slime();
        /* burn up flammable items on the floor, melt ice terrain */
        mon_spell_hits_spot(caster, AD_FIRE, u.ux, u.uy);
        break;
    case AD_COLD:
        pline("You're covered in frost.");
        if (fully_resistant(COLD_RES)) {
            shieldeff(u.ux, u.uy);
            pline("But you resist the effects.");
            monstseesu(M_SEEN_COLD);
            dmg = 0;
        } else {
            dmg = resist_reduce(dmg, COLD_RES);
            monstunseesu(M_SEEN_COLD);
        }
        /* freeze water or lava terrain */
        /* FIXME: mon_spell_hits_spot() uses zap_over_floor(); unlike with
         * fire, it does not target susceptible floor items with cold */
        mon_spell_hits_spot(caster, AD_COLD, u.ux, u.uy);
        break;
    case AD_MAGM:
        You("are hit by a shower of missiles!");
        dmg = d((int) caster->m_lev / 2 + 1, 6);
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            pline("Some missiles bounce off!");
            dmg = (dmg + 1) / 2;
            monstseesu(M_SEEN_MAGR);
        } else
            monstunseesu(M_SEEN_MAGR);
        if (Half_spell_damage) { /* stacks with Antimagic */
            dmg = (dmg + 1) / 2;
        }
        /* shower of magic missiles scuffs an engraving */
        mon_spell_hits_spot(caster, AD_MAGM, u.ux, u.uy);
        break;
    case AD_SPEL: /* wizard spell */
    case AD_CLRC: /* clerical spell */
        if (mattk->adtyp == AD_SPEL)
            (void) cast_wizard_spell(caster, &gy.youmonst, dmg, spellnum);
        else
            (void) cast_cleric_spell(caster, &gy.youmonst, dmg, spellnum);
        dmg = 0; /* done by the spell casting functions */
        break;
    } /* switch */
    if (dmg)
        mdamageu(caster, dmg);
    return ret;
}

staticfn int
m_cure_self(struct monst *caster, int dmg)
{
    if (caster->mhp < caster->mhpmax) {
        if (canseemon(caster))
            pline_mon(caster, "%s looks better.", Monnam(caster));
        /* note: player healing does 6d4; this used to do 1d8 */
        if ((caster->mhp += d(3, 6)) > caster->mhpmax)
            caster->mhp = caster->mhpmax;
        dmg = 0;
    }
    /* Cure other ailments that players spells are capable of. */
    if (caster->mblinded)
        mcureblindness(caster, TRUE);
    if (caster->mdiseased || caster->mrabid) {
        caster->mdiseased = caster->mrabid = 0;
        if (canseemon(caster))
            pline("%s is no longer ill.", Monnam(caster));
    }
    if (caster->mwither) {
        caster->mwither = 0;
        pline("%s is no longer withering away.", Monnam(caster));
    }

    return dmg;
}

/* unlike the finger of death spell which behaves like a wand of death,
   this monster spell only attacks the hero */
void
touch_of_death(struct monst *caster)
{
    char kbuf[BUFSZ];
    int dmg = 50 + d(8, 6);
    int drain = dmg / 2;

    /* if we get here, we know that hero isn't magic resistant and isn't
       poly'd into an undead or demon */
    You_feel("drained...");
    (void) death_inflicted_by(kbuf, "the touch of death", caster);

    if (Upolyd) {
        u.mh = 0;
        rehumanize(); /* fatal iff Unchanging */
    } else if (drain >= u.uhpmax) {
        svk.killer.format = KILLED_BY;
        Strcpy(svk.killer.name, kbuf);
        done(DIED);
    } else {
        /* HP manipulation similar to poisoned(attrib.c) */
        int olduhp = u.uhp,
            uhpmin = minuhpmax(3),
            newuhpmax = u.uhpmax - drain;

        setuhpmax(max(newuhpmax, uhpmin), FALSE);
        dmg = adjuhploss(dmg, olduhp); /* reduce pending damage if uhp has
                                        * already been reduced due to drop
                                        * in uhpmax */
        losehp(dmg, kbuf, KILLED_BY);
    }
    svk.killer.name[0] = '\0'; /* not killed if we get here... */
}

/* give a reason for death by some monster spells */
char *
death_inflicted_by(
    char *outbuf,            /* assumed big enough; pm_names are short */
    const char *deathreason, /* cause of death */
    struct monst *caster)      /* monster who caused it */
{
    Strcpy(outbuf, deathreason);
    if (caster) {
        struct permonst *mptr = caster->data,
            *champtr = (ismnum(caster->cham)) ? &mons[caster->cham] : mptr;
        const char *realnm = pmname(champtr, Mgender(caster)),
            *fakenm = pmname(mptr, Mgender(caster));

        /* greatly simplified extract from done_in_by(), primarily for
           reason for death due to 'touch of death' spell; if caster is
           shape changed, it won't be a vampshifter or mimic since they
           can't cast spells */
        if (!type_is_pname(champtr) && !the_unique_pm(mptr))
            realnm = an(realnm);
        Sprintf(eos(outbuf), " inflicted by %s%s",
                the_unique_pm(mptr) ? "the " : "", realnm);
        if (champtr != mptr)
            Sprintf(eos(outbuf), " imitating %s", an(fakenm));
    }
    return outbuf;
}


int
m_destroy_armor(struct monst *caster, struct monst *mdef)
{
    boolean udefend = (mdef == &gy.youmonst),
            uattk = (caster == &gy.youmonst);
    boolean mtrap = !caster;
    int erodelvl = rnd(3);
    struct obj *oatmp;

    if (udefend ? Antimagic
                : (resists_magm(mdef) || defended(mdef, AD_MAGM))) {
        if (udefend) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
        } else {
            shieldeff(mdef->mx, mdef->my);
        }
        erodelvl = 1;
    }

    oatmp = some_armor(mdef);
    if (oatmp) {
        if (any_quest_artifact(oatmp)) {
            if (udefend || canseemon(mdef)) {
                if (!Blind)
                    pline("%s shines brightly.", The(xname(oatmp)));
                pline("%s is immune to %s destructive magic.",
                      The(xname(oatmp)),
                      mtrap ? "the trap's"
                      : uattk ? "your" : s_suffix(mon_nam(caster)));
            }
            return 0;
        } else if (oatmp->otyp == CRYSTAL_PLATE_MAIL
            || oatmp->otyp == SHIELD_OF_INTEGRITY) {
            if (udefend && !Blind)
                pline("%s glimmers brightly.", Yname2(oatmp));
            pline("%s is immune to %s destructive magic.",
                  Yname2(oatmp),
                  mtrap ? "the trap's"
                  : uattk ? "your" : s_suffix(mon_nam(caster)));
            return 0; /* no effect */
        } else if (oatmp->oerodeproof) {
            if (!udefend && !canseemon(mdef) && olfaction(gy.youmonst.data)) {
                You("smell something strange.");
            } else if (!Blind) {
                pline("%s glows brown for a moment.", Yname2(oatmp));
            } else if (olfaction(gy.youmonst.data)) {
                pline("%s briefly emits an odd smell.", Yname2(oatmp));
            }
            oatmp->oerodeproof = 0;
            erodelvl--;
        }

        if (greatest_erosion(oatmp) >= MAX_ERODE) {
            if (objects[oatmp->otyp].oc_oprop == DISINT_RES
                || obj_resists(oatmp, 0, 90)) {
                pline("%s resists the destructive spell!", Yname2(oatmp));
                return 0;
            }
            if (udefend) {
                destroy_arm(oatmp, FALSE, TRUE);
            } else {
                if (canseemon(mdef)) {
                    const char *action;
                    if (is_cloak(oatmp))
                        action = "crumbles and turns to dust";
                    else if (is_shirt(oatmp))
                        action = "crumbles into tiny threads";
                    else if (is_helmet(oatmp))
                        action = "turns to dust and is blown away";
                    else if (is_gloves(oatmp))
                        action = "vanish";
                    else if (is_boots(oatmp))
                        action = "disintegrate";
                    else if (is_shield(oatmp))
                        action = "crumbles away";
                    else
                        action = "turns to dust";
                    pline("%s %s %s!", s_suffix(Monnam(mdef)), xname(oatmp),
                          action);
                }
                m_useupall(mdef, oatmp);
            }
        } else {
            int erodetype;
            if (is_corrodeable(oatmp))
                erodetype = ERODE_CORRODE;
            else if (is_flammable(oatmp))
                erodetype = ERODE_BURN;
            else if (is_supermaterial(oatmp))
                erodetype = ERODE_DETERIORATE;
            else
                erodetype = ERODE_ROT;

            while (erodelvl-- > 0) {
                (void) erode_obj(oatmp, (char *) 0, erodetype, EF_NONE);
            }
        }
    } else {
        if (udefend)
            Your("body itches.");
        else if (uattk || canseemon(mdef))
            pline("%s seems irritated.", Monnam(mdef));
    }
    update_inventory();

    return 0;
}

/*
 * Monster wizard and cleric spellcasting functions.
 */

/*
   If dmg is zero, then the monster is not casting at you.
   If the monster is intentionally not casting at you, we have previously
   called spell_would_be_useless() and spellnum should always be a valid
   undirected spell.
   If you modify either of these, be sure to change is_undirected_spell()
   and spell_would_be_useless().
 */
staticfn int
cast_wizard_spell(
    struct monst *caster, /* caster */
    struct monst *mdef, /* target */
    int dmg, int spellnum)
{
    boolean youdefend = (mdef == &gy.youmonst),
            resisted = FALSE;

    if (dmg < 0) {
        impossible("monster cast wizard spell (%d) with negative dmg (%d)?",
                   spellnum, dmg);
        return 0;
    }

    int ml = min(caster->m_lev, 50);
    if (dmg == 0 && !is_undirected_spell(AD_SPEL, spellnum)) {
        impossible("cast directed wizard spell (%d) with dmg=0?", spellnum);
        return 0;
    }

    switch (spellnum) {
    case MGC_DEATH_TOUCH:
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;

        if (youdefend) { /* mhitu */
            pline("Oh no, %s's using the touch of death!", mhe(caster));
            if (nonliving(gy.youmonst.data)) {
                You("seem no deader than before.");
            } else if (resists_death(gy.youmonst.data)) {
                You("are unaffected.");
            } else if (!Antimagic && rn2(caster->m_lev) > 12) {
                if (Hallucination) {
                    You("have an out of body experience.");
                } else {
                    touch_of_death(caster);
                }
                monstunseesu(M_SEEN_MAGR);
            } else {
                if (Antimagic) {
                    shieldeff(u.ux, u.uy);
                    monstseesu(M_SEEN_MAGR);
                }
                pline("Lucky for you, it didn't work!");
            }
        } else { /* mhitm */
            if (canseemon(caster)) {
                char buf[BUFSZ];
                Sprintf(buf, "%s%s",
                        caster->mtame ? "Oh no, " : "", mhe(caster));
                if (!caster->mtame)
                    *buf = highc(*buf);

                pline("%s's using the touch of death!", buf);
            }
            resisted =
                ((resist(mdef, 0, 0, FALSE)
                && rn2(mons[caster->mnum].mlevel) <= 12)
                || resists_magm(mdef) || defended(mdef, AD_MAGM));

            if (resists_death(mdef->data) || is_vampshifter(mdef)) {
                if (canseemon(mdef))
                    pline("%s %s.", Monnam(mdef),
                        nonliving(mdef->data)
                            ? "seems no more dead than before"
                            : "is unaffected");
            } else if (!resisted) {
                mdef->mhp = -1;
                monkilled(caster, "", AD_SPEL);
                return 0;
            } else {
                if (resisted)
                    shieldeff(mdef->mx, mdef->my);
                if (canseemon(mdef)) {
                    if (mdef->mtame)
                        pline("Lucky for %s, it didn't work!", mon_nam(mdef));
                    else
                        pline("Well.  That didn't work...");
                }
            }
	dmg = 0;
        }
        break;
    case MGC_REFLECTION: {
        boolean strongbad = (caster->iswiz || is_prince(caster->data)
                             || caster->data->msound == MS_NEMESIS
                             || caster->data->msound == MS_LEADER);
        if (canseemon(caster))
            pline("A shimmering globe appears around %s!", mon_nam(caster));
        /* monster reflection is handled in mon_reflects() */
        caster->mextrinsics |= MR2_REFLECTION;
        caster->mreflecttime = rn1(50, strongbad ? 200 : 100);
        dmg = 0;
        break;
    }
    case MGC_ACID_BLAST:
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;
        dmg = d((ml / 2) + 4, 8);
        if (mcast_dist_ok(caster)) {
            if (youdefend)
                pline("%s douses you in a torrent of acid!", Monnam(caster));
            else
                pline("%s douses %s in a torrent of acid!",
                    Monnam(caster), mon_nam(mdef));
            explode(mdef->mx, mdef->my, BZ_M_SPELL(ZT_ACID), dmg,
                    MON_CASTBALL, EXPL_WET);

            if (youdefend) {
                if (Acid_resistance) {
                    shieldeff(u.ux, u.uy);
                    pline("The acid doesn't harm you.");
                    monstseesu(M_SEEN_ACID);
                }
            } else { /* mhitm */
                if (resists_acid(mdef) || defended(mdef, AD_ACID)) {
                    shieldeff(mdef->mx, mdef->my);
                    if (canseemon(mdef))
                        pline("But the acid dissipates harmlessly.");
                }
                if (!rn2(6))
                    acid_damage(MON_WEP(mdef));
                if (!rn2(6))
                    erode_armor(mdef, ERODE_CORRODE);
            }
        } else {
            if (canseemon(caster)) {
                pline("%s blasts the %s with %s and curses!",
                      Monnam(caster), rn2(2) ? "ceiling"
                                           : "floor", "acid");
            } else {
                You_hear("some cursing!");
            }
        }
        dmg = 0; /* damage is handled by explode() */
        break;
    case MGC_CLONE_WIZ:
        if (!youdefend)
            impossible("MGC_CLONE_WIZ vs non-player monster.");

        if (caster->iswiz && svc.context.no_of_wizards == 1) {
            pline("Double Trouble...");
            clonewiz();
            dmg = 0;
        } else
            impossible("bad wizard cloning?");
        break;
    case MGC_SUMMON_MONS: {
        /* In EvilHack this is handled a bit differently -
           we'll keep it simple and ignore this for mhitm. */
        if (youdefend) {
            int count = nasty(caster, FALSE);

            if (!count) {
                ; /* nothing was created? */
            } else if (caster->iswiz) {
                SetVoice(caster, 0, 80, 0);
                verbalize("Destroy the thief, my pet%s!", plur(count));
            } else {
                boolean one = (count == 1);
                const char *mappear = one ? "A monster appears"
                                        : "Monsters appear";

                /* messages not quite right if plural monsters created but
                only a single monster is seen */
                if (Invis && !mon_prop(caster, SEE_INVIS)
                    && (caster->mux != u.ux || caster->muy != u.uy))
                    pline("%s %s a spot near you!", mappear,
                        one ? "at" : "around");
                else if (Displaced && (caster->mux != u.ux || caster->muy != u.uy))
                    pline("%s %s your displaced image!", mappear,
                        one ? "by" : "around");
                else
                    pline("%s from nowhere!", mappear);
            }
        }
        dmg = 0;
        break;
    }
    case MGC_CALL_UNDEAD: {
        dmg = 0;
        /* We don't want summons if we're not the target */
        if (!youdefend)
            break;
        if (m_canseeu(caster) && distu(caster->mx, caster->my) <= 192) {
            coord mm;
            mm.x = u.ux;
            mm.y = u.uy;
            pline("Undead creatures are called forth from the grave!");
            mkundead(&mm, FALSE, NO_MINVENT);
        }
        break;
    }
    case MGC_AGGRAVATION:
        /* Skip aggravate if we are not the target */
        if (youdefend) {
            if (m_canseeu(caster) && distu(caster->mx, caster->my) <= 192)
                incr_itimeout(&HAggravate_monster, rnd(250) + 50);
            You_feel("that monsters are aware of your presence.");
            aggravate();
        }
        dmg = 0;
        break;
    case MGC_CURSE_ITEMS:
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;
        if (youdefend) {
            You_feel("as if you need some help.");
            rndcurse();
        } else { /* mhitm */
            if (canseemon(mdef))
                You_feel("as though %s needs some help.", mon_nam(mdef));
            mrndcurse(mdef);
        }
        dmg = 0;
        break;
    case MGC_DESTRY_ARMR:
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;
        dmg = m_destroy_armor(caster, mdef);
        break;
    case MGC_EVIL_EYE: { /* drains luck */
        if (youdefend) {
            struct attack evilEye = { AT_GAZE, AD_LUCK, 1, 4 };
            (void) gazemu(caster, &evilEye);
        } else { /* mhitm */
            /* Since monsters don't have Luck - confuse them instead */
            if (resist(mdef, 0, 0, FALSE)) {
                shieldeff(mdef->mx, mdef->my);
                if (canseemon(mdef))
                    pline("%s seems momentarily dizzy.", Monnam(mdef));
            } else {
                if (canseemon(mdef))
                    pline("%s seems %sconfused!", Monnam(mdef),
                        mdef->mconf ? "more " : "");
                mdef->mconf = 1;
            }
        }
        dmg = 0;
        break;
    }
    case MGC_WEAKEN_YOU: /* drain strength */
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;
        if (youdefend) {
            if (Antimagic) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_MAGR);
                You_feel("momentarily weakened.");
            } else {
                char kbuf[BUFSZ];

                You("suddenly feel weaker!");
                dmg = caster->m_lev - 6;
                if (dmg < 1) /* paranoia since only chosen when m_lev is high */
                    dmg = 1;
                if (Half_spell_damage)
                    dmg = (dmg + 1) / 2;
                losestr(rnd(dmg),
                        death_inflicted_by(kbuf, "strength loss", caster),
                        KILLED_BY);
                svk.killer.name[0] = '\0'; /* not killed if we get here... */
                monstunseesu(M_SEEN_MAGR);
            }
        } else { /* mhitm */
            if (resist(mdef, 0, 0, FALSE)) {
                shieldeff(mdef->mx, mdef->my);
                pline("%s looks momentarily weakened.", Monnam(mdef));
            } else {
                if (canseemon(mdef))
                    pline("%s suddenly seems weaker!", Monnam(mdef));
                /* monsters don't have strength, so drain max hp instead */
                mdef->mhpmax -= dmg;
                if ((mdef->mhp -= dmg) <= 0) {
                    monkilled(mdef, "", AD_SPEL);
                }
            }
        }
        dmg = 0;
        break;
    case MGC_DISAPPEAR: /* makes self invisible */
        if (!caster->minvis && !caster->invis_blkd) {
            if (canseemon(caster))
                pline_mon(caster, "%s suddenly %s!", Monnam(caster),
                      !See_invisible ? "disappears" : "becomes transparent");
            mon_set_minvis(caster);
            if (cansee(caster->mx, caster->my) && !canspotmon(caster))
                map_invisible(caster->mx, caster->my);
            dmg = 0;
        } else
            impossible("no reason for monster to cast disappear spell?");
        break;
    case MGC_STUN_YOU:
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;
        if (youdefend) {
            if (Antimagic || Free_action) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_MAGR);
                if (!Stunned || Stun_resistance)
                    You_feel("momentarily disoriented.");
                if (!Stunned)
                    make_stunned(1L, FALSE);
            } else {
                if (!Stun_resistance)
                    You(Stunned ? "struggle to keep your balance." : "reel...");
                dmg = d(ACURR(A_DEX) < 12 ? 6 : 4, 4);
                if (Half_spell_damage)
                    dmg = (dmg + 1) / 2;
                make_stunned((HStun & TIMEOUT) + (long) dmg, FALSE);
                monstunseesu(M_SEEN_MAGR);
            }
        } else { /* mhitm */
            if (resist(mdef, 0, 0, FALSE)) {
                shieldeff(mdef->mx, mdef->my);
                if (canseemon(mdef)
                    || resists_stun(mdef->data) || defended(mdef, AD_STUN))
                    pline("%s seems momentarily disoriented.", Monnam(mdef));
            } else {
                if (canseemon(mdef)) {
                    if (mdef->mstun)
                        pline("%s struggles to keep %s balance.",
                            Monnam(mdef), mhis(mdef));
                    else
                        pline("%s reels...", Monnam(mdef));
                }
                mdef->mstun = 1;
            }
        }
        dmg = 0;
        break;
    case MGC_HASTE_SELF:
        mon_adjust_speed(caster, 1, (struct obj *) 0);
        dmg = 0;
        break;
    case MGC_CURE_SELF:
        dmg = m_cure_self(caster, dmg);
        break;
    case MGC_FIRE_BOLT:
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;
        dmg = d((ml / 5) + 1, 8);
        if (youdefend) {
            /* hotwire these to only go off if the critter can see you
            * to avoid bugs WRT the Eyes and detect monsters */

            if (mcast_dist_ok(caster)) {
                pline("%s blasts you with a bolt of fire!", Monnam(caster));
                explode(u.ux, u.uy, BZ_M_SPELL(ZT_FIRE), dmg,
                    MON_CASTBALL, EXPL_FIERY);

                if (fully_resistant(FIRE_RES)) {
                    shieldeff(u.ux, u.uy);
                    monstseesu(M_SEEN_FIRE);
                } else {
                    monstunseesu(M_SEEN_FIRE);
                }
            } else {
                if (canseemon(caster)) {
                    pline("%s blasts the %s with fire and curses!",
                        Monnam(caster), rn2(2) ? "ceiling" : "floor");
                } else {
                    You_hear("some cursing!");
                }
            }
        } else {
            if (canseemon(caster))
                pline("%s blasts %s with fire!", Monnam(caster), mon_nam(mdef));
            explode(mdef->mx, mdef->my, BZ_M_SPELL(ZT_FIRE), dmg,
                    MON_CASTBALL, EXPL_FIERY);
        }
        dmg = 0; /* damage is handled by explode() */
        break;
    case MGC_ICE_BOLT:
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;
        dmg = d((ml / 5) + 1, 8);
        if (youdefend) {
            if (mcast_dist_ok(caster)) {
                pline("%s blasts you with a bolt of cold!", Monnam(caster));
                explode(u.ux, u.uy, BZ_M_SPELL(ZT_COLD), dmg,
                    MON_CASTBALL, EXPL_FROSTY);

                if (fully_resistant(COLD_RES)) {
                    shieldeff(u.ux, u.uy);
                    monstseesu(M_SEEN_COLD);
                } else {
                    monstunseesu(M_SEEN_COLD);
                }
            } else {
                if (canseemon(caster)) {
                    pline("%s blasts the %s with cold and curses!",
                        Monnam(caster), rn2(2) ? "ceiling" : "floor");
                } else {
                    You_hear("some cursing!");
                }
            }
        } else {
            if (canseemon(caster))
                pline("%s blasts %s with ice!", Monnam(caster), mon_nam(mdef));
            explode(mdef->mx, mdef->my, BZ_M_SPELL(ZT_COLD), dmg,
                    MON_CASTBALL, EXPL_FROSTY);
        }
        dmg = 0; /* damage is handled by explode() */
        break;
    case MGC_PSI_BOLT:
        if (!mdef || (DEADMONSTER(mdef) && !youdefend))
            return 0;
        /* prior to 3.4.0 Antimagic was setting the damage to 1--this
           made the spell virtually harmless to players with magic res. */
        if (youdefend) {
            if (Antimagic) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_MAGR);
                dmg = (dmg + 1) / 2;
            } else {
                monstunseesu(M_SEEN_MAGR);
            }
            if (dmg <= 5)
                You("get a slight %sache.", body_part(HEAD));
            else if (dmg <= 10)
                Your("brain is on fire!");
            else if (dmg <= 20)
                Your("%s suddenly aches painfully!", body_part(HEAD));
            else
                Your("%s suddenly aches very painfully!", body_part(HEAD));
        } else {
            if (resist(mdef, 0, 0, FALSE)) {
                shieldeff(mdef->mx, mdef->my);
                dmg = (dmg + 1) / 2;
            }
            if (canseemon(mdef))
                pline("%s %s%s", Monnam(mdef),
                    can_flollop(mdef->data) ? "flollops" : "winces",
                    (dmg <= 5) ? "." : "!");
        }
        break;
    case MGC_ENTOMB: {
        if (!youdefend) {
            dmg = 0;
            break;
        }
        /* entomb you in rocks to delay you and get away */
        coordxy x, y;
        /* Only allow casting at relatively short-range */
        if (m_canseeu(caster) && distu(caster->mx, caster->my) <= 26
            /* Don't cast if we get hit by the boulders! */
            && distu(caster->mx, caster->my) > 2) {
            pline_The("ground shakes violently!");
            if (!Blind)
                pline("Boulders fall from above!");
            for (x = u.ux - 1; x <= u.ux + 1; ++x) {
                for (y = u.uy - 1; y <= u.uy + 1; ++y) {
                    if (!isok(x, y))
                        continue;
                    if (!SPACE_POS(levl[x][y].typ))
                        continue;
                    if (u_at(x, y))
                        continue;
                    if (rn2(5))
                        drop_boulder_on_monster(x, y, FALSE, FALSE);
                    if (rn2(3))
                        drop_boulder_on_monster(x, y, FALSE, FALSE);
                }
            }
            if (rn2(4))
                drop_boulder_on_player(FALSE, FALSE, FALSE, FALSE);
            dmg = 0;
        }
        break;
    }
    default:
        impossible("mcastu: invalid magic spell (%d)", spellnum);
        dmg = 0;
        break;
    }

    if (youdefend && dmg)
	mdamageu(caster, dmg);
    return dmg;
}

DISABLE_WARNING_FORMAT_NONLITERAL

staticfn int
cast_cleric_spell(
    struct monst *caster,
    struct monst *mdef,
    int dmg, int spellnum)
{
    int ml = min(caster->m_lev, 50);
    int orig_dmg = 0;
    boolean youdefend = (mdef == &gy.youmonst);

    if (dmg < 0) {
        impossible("monster cast cleric spell (%d) with negative dmg (%d)?",
                   spellnum, dmg);
        return 0;
    }
    if (dmg == 0 && !is_undirected_spell(AD_CLRC, spellnum)) {
        impossible("cast directed cleric spell (%d) with dmg=0?", spellnum);
        return 0;
    }

    switch (spellnum) {
    case CLC_BLIGHT: {
        /* This could use is_fleshy(), but that would make a large set
         * of monsters immune like fungus, blobs, and jellies. */
        boolean no_effect = nonliving(mdef->data) || mon_prop(mdef, DISINT_RES);
        uchar withertime = rn1(41, 20);
        boolean lose_maxhp = (withertime >= 8); /* if already withering */

        if (no_effect) {
            dmg = 0;
            break;
        }
        if (youdefend) {
            if (m_canseeu(caster) && distu(caster->mx, caster->my) <= 65
                && !BWithering) {
                You("%s rapidly decomposing!", Withering ? "continue" : "begin");
                incr_itimeout(&HWithering, withertime);
                if (lose_maxhp) {
                    if (Upolyd && u.mhmax > 1) {
                        u.mhmax--;
                        u.mh = min(u.mh, u.mhmax);
                    }
                    else if (u.uhpmax > 1) {
                        u.uhpmax--;
                        u.uhp = min(u.uhp, u.uhpmax);
                    }
                }
                disp.botl = TRUE;
            }
        } else if (!mon_prop(mdef, DISINT_RES)) { /* mhitm */
            if (canseemon(mdef))
                pline("%s is withering away!", Monnam(mdef));

            if (mdef->mwither + withertime > UCHAR_MAX) {
                mdef->mwither = UCHAR_MAX;
            } else {
                mdef->mwither += withertime;
            }
            if (lose_maxhp && mdef->mhpmax > 1) {
                mdef->mhpmax--;
                mdef->mhp = min(mdef->mhp, mdef->mhpmax);
            }
        }
        dmg = 0;
        break;
    }
    case CLC_GEYSER:
        /* this is physical damage (force not heat),
         * not magical damage or fire damage
         */
        dmg = d(8, 6);
        if (youdefend) {
            pline("A sudden geyser slams into you from nowhere!");
            if (Half_physical_damage)
                dmg = (dmg + 1) / 2;
            if (u.umonnum == PM_IRON_GOLEM) {
                You("rust!");
                Strcpy(svk.killer.name, "rusted away");
                svk.killer.format = NO_KILLER_PREFIX;
                rehumanize();
                dmg = 0; /* prevent further damage after rehumanization */
            }
            erode_armor(&gy.youmonst, ERODE_RUST);
        } else { /* mhitm */
            if (canseemon(mdef))
                pline("A sudden geyser slams into %s from nowhere!",
                    mon_nam(mdef));
            (void) erode_armor(mdef, ERODE_RUST);
        }

        /* since inventory items aren't affected, don't include this */
        /* make floor items wet */
        water_damage_chain(svl.level.objects[mdef->mx][mdef->my], TRUE);
        break;
    case CLC_FIRE_PILLAR:
        orig_dmg = dmg = d(8, 6);
        if (youdefend) {
            pline("A pillar of fire strikes all around you!");
            if (fully_resistant(FIRE_RES)) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_FIRE);
                dmg = 0;
            } else {
                dmg = resist_reduce(dmg, FIRE_RES);
                monstunseesu(M_SEEN_FIRE);
            }
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            burn_away_slime();
            (void) burnarmor(&gy.youmonst);
            (void) destroy_items(&gy.youmonst, AD_FIRE, orig_dmg);
            ignite_items(gi.invent);
        } else { /* mhitm */
            if (canseemon(mdef))
                pline("A pillar of fire strikes all around %s!",
                    mon_nam(mdef));
            if (resists_fire(mdef) || defended(mdef, AD_FIRE)) {
                shieldeff(mdef->mx, mdef->my);
                dmg = 0;
            }
            if (!defended(mdef, AD_FIRE)) {
                (void) burnarmor(mdef);
                dmg += destroy_items(mdef, AD_FIRE, orig_dmg);
            }
        }

        /* burn up flammable items on the floor, melt ice terrain */
        mon_spell_hits_spot(caster, AD_FIRE, u.ux, u.uy);
        break;
    case CLC_LIGHTNING: {
        boolean reflects;
        Soundeffect(se_bolt_of_lightning, 80);

        if (youdefend) {
            pline("A bolt of lightning strikes down at you from above!");
            reflects = ureflects("It bounces off your %s%s.", "");
            orig_dmg = dmg = d(8, 6);
            if (reflects || fully_resistant(SHOCK_RES)) {
                shieldeff(u.ux, u.uy);
                if (reflects) {
                    dmg = resist_reduce(d(4, 6), SHOCK_RES);
                    monstseesu(M_SEEN_REFL);
                    break;
                }
                monstunseesu(M_SEEN_REFL);
                if (fully_resistant(SHOCK_RES)) {
                    pline("You aren't shocked.");
                    monstseesu(M_SEEN_ELEC);
                    dmg = 0;
                }
            } else {
                dmg = resist_reduce(dmg, SHOCK_RES);
                monstunseesu(M_SEEN_ELEC | M_SEEN_REFL);
            }
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            (void) destroy_items(&gy.youmonst, AD_ELEC, orig_dmg);
            /* blind hero; no effect if already blind */
            (void) flashburn((long) rnd(100), TRUE);
        } else { /* mhitm */
            if (canseemon(mdef))
                pline("A bolt of lightning strikes down at %s from above!",
                    mon_nam(mdef));
            reflects = mon_reflects(mdef, "It bounces off %s %s.");
            if (reflects || resists_elec(mdef) || defended(mdef, AD_ELEC)) {
                shieldeff(u.ux, u.uy);
                dmg = 0;
                if (reflects)
                    break;
            } else
                dmg = d(8, 6);
            dmg += destroy_items(mdef, AD_ELEC, orig_dmg);
        }

        /* lightning might destroy iron bars if hero is on such a spot;
           reflection protects terrain here [execution won't get here due
           to 'if (reflects) break' above] but hero resistance doesn't;
           do this before maybe blinding the hero via flashburn() */
        mon_spell_hits_spot(caster, AD_ELEC, u.ux, u.uy);

        break;
    }
    case CLC_CURSE_ITEMS:
        if (youdefend) {
            You_feel("as if you need some help.");
            rndcurse();
        } else { /* mhitm */
            if (canseemon(mdef))
                You_feel("as though %s needs some help.", mon_nam(mdef));
            mrndcurse(mdef);
        }

        dmg = 0;
        break;
    case CLC_INSECTS: {
        /* TODO: prevent this pre-emptively in mspell_would_be_useless? */
        if (!youdefend) {
            dmg = 0;
            break;
        }
        /* Try for insects, and if there are none
           left, go for (sticks to) snakes.  -3.
           Lolth summons spiders as he does in EvilHack */
        boolean spiders = (caster->data == &mons[PM_LOLTH]);
        struct permonst *pm = mkclass(S_ANT, 0);
        struct monst *mtmp2 = (struct monst *) 0;
        char whatbuf[QBUFSZ],
            let = (pm ? (spiders ? S_SPIDER : S_ANT) : S_SNAKE);
        boolean success = FALSE, seecaster;
        int i, quan, oldseen, newseen;
        coord bypos;
        const char *fmt, *what;

        oldseen = monster_census(TRUE);
        quan = (caster->m_lev < 2) ? 1 : rnd((int) caster->m_lev / 2);
        if (quan < 3)
            quan = 3;
        for (i = 0; i <= quan; i++) {
            if (!enexto(&bypos, caster->mux, caster->muy, caster->data))
                break;
            if ((pm = mkclass(let, 0)) != 0
                && (mtmp2 = makemon(pm, bypos.x, bypos.y, MM_ANGRY | MM_NOMSG))
                   != 0) {
                success = TRUE;
                mtmp2->msleeping = mtmp2->mpeaceful = mtmp2->mtame = 0;
                set_malign(mtmp2);
            }
        }
        newseen = monster_census(TRUE);

        /* not canspotmon() which includes unseen things sensed via warning */
        seecaster = canseemon(caster) || tp_sensemon(caster) || Detect_monsters;
        what = (let == S_SNAKE) ? "snake"
               : (let == S_SPIDER) ? "arachnid"
                                   : "insect";
        if (Hallucination)
            what = makeplural(bogusmon(whatbuf, (char *) 0));

        fmt = 0;
        if (!seecaster) {
            if (newseen <= oldseen || Unaware) {
                /* unseen caster fails or summons unseen critters,
                   or unconscious hero ("You dream that you hear...") */
                You_hear("someone summoning %s.", what);
            } else {
                char *arg;

                if (what != whatbuf)
                    what = strcpy(whatbuf, what);
                /* unseen caster summoned seen critter(s) */
                arg = (newseen == oldseen + 1) ? an(makesingular(what))
                                               : whatbuf;
                if (!Deaf) {
                    Soundeffect(se_someone_summoning, 100);
                    You_hear("someone summoning something, and %s %s.", arg,
                             vtense(arg, "appear"));
                } else {
                    pline("%s %s.", upstart(arg), vtense(arg, "appear"));
                }
            }

        /* seen caster, possibly producing unseen--or just one--critters;
           hero is told what the caster is doing and doesn't necessarily
           observe complete accuracy of that caster's results (in other
           words, no need to fuss with visibility or singularization;
           player is told what's happening even if hero is unconscious) */
        } else if (!success) {
            fmt = "%s casts at a clump of sticks, but nothing happens.%s";
            what = "";
        } else if (let == S_SNAKE) {
            fmt = "%s transforms a clump of sticks into %s!";
        } else if (Invis && !mon_prop(caster, SEE_INVIS)
                   && (caster->mux != u.ux || caster->muy != u.uy)) {
            fmt = "%s summons %s around a spot near you!";
        } else if (Displaced && (caster->mux != u.ux || caster->muy != u.uy)) {
            fmt = "%s summons %s around your displaced image!";
        } else {
            fmt = "%s summons %s!";
        }
        if (fmt)
            pline_mon(caster, fmt, Monnam(caster), what);

        dmg = 0;
        break;
    }
    case CLC_SPHERES: {
        if (!youdefend) {
            dmg = 0;
            break;
        }
        struct permonst *pm = &mons[rnd_sphere()];
        struct monst *mtmp2 = (struct monst *) 0;
        const char *fmt, *what;
        char whatbuf[QBUFSZ];
        boolean success = FALSE, seecaster;
        int oldseen, newseen;
        coord bypos;

        oldseen = monster_census(TRUE);

        if (!enexto(&bypos, caster->mx, caster->my, caster->data))
            break;
        if ((pm = &mons[rnd_sphere()]) != 0
            && (mtmp2 = make_msummoned(pm, caster, FALSE, bypos.x, bypos.y)) != 0) {
            success = TRUE;
            mtmp2->msleeping = mtmp2->mpeaceful = mtmp2->mtame = 0;
            set_malign(mtmp2);
        }
        newseen = monster_census(TRUE);

        /* not canspotmon() which includes unseen things sensed via warning */
        seecaster = canseemon(caster) || tp_sensemon(caster) || Detect_monsters;
        what = "an orb";
        if (Hallucination)
            what = makeplural(bogusmon(whatbuf, (char *) 0));

        fmt = 0;
        if (!seecaster) {
            if (newseen <= oldseen || Unaware) {
                /* unseen caster fails or summons unseen critters,
                   or unconscious hero ("You dream that you hear...") */
                You_hear("someone summoning %s.", what);
            } else {
                char *arg;

                if (what != whatbuf)
                    what = strcpy(whatbuf, what);
                /* unseen caster summoned seen critter(s) */
                arg = (newseen == oldseen + 1) ? an(makesingular(what))
                                               : whatbuf;
                if (!Deaf) {
                    Soundeffect(se_someone_summoning, 100);
                    You_hear("someone summoning something, and %s %s.", arg,
                             vtense(arg, "appear"));
                } else {
                    pline("%s %s.", upstart(arg), vtense(arg, "appear"));
                }
            }

        /* seen caster, possibly producing unseen--or just one--critters;
           hero is told what the caster is doing and doesn't necessarily
           observe complete accuracy of that caster's results (in other
           words, no need to fuss with visibility or singularization;
           player is told what's happening even if hero is unconscious) */
        } else if (!success) {
            fmt = "%s waves its hands, but nothing happens.%s";
            what = "";
        } else if (Invis && !mon_prop(caster, SEE_INVIS)
                   && (caster->mux != u.ux || caster->muy != u.uy)) {
            fmt = "%s summons %s around a spot near you!";
        } else if (Displaced && (caster->mux != u.ux || caster->muy != u.uy)) {
            fmt = "%s summons %s around your displaced image!";
        } else {
            fmt = "%s summons %s!";
        }
        if (fmt)
            pline(fmt, Monnam(caster), what);

        dmg = 0;
        break;
    }
    case CLC_BLIND_YOU:
        if (youdefend) {
            /* note: resists_blnd() doesn't apply here */
            if (!Blinded) {
                int num_eyes = eyecount(gy.youmonst.data);

                pline("Scales cover your %s!", (num_eyes == 1)
                                                ? body_part(EYE)
                                                : makeplural(body_part(EYE)));
                make_blinded(Half_spell_damage ? 100L : 200L, FALSE);
                if (!Blind)
                    Your1(vision_clears);
                dmg = 0;
            } else
                impossible("no reason for monster to cast blindness spell?");
        } else { /* mhitm */
            /* note: resists_blnd() doesn't apply here */
            if (!mdef->mblinded
                && haseyes(mdef->data)) {
                if (!resists_blnd(mdef)) {
                    int num_eyes = eyecount(mdef->data);
                    if (canseemon(mdef))
                        pline("Scales cover %s %s!", s_suffix(mon_nam(mdef)),
                            (num_eyes == 1) ? "eye" : "eyes");
                    mdef->mblinded = 127;
                }
            }
        }
        break;
    case CLC_HOBBLE:
        dmg = 4 + (int) caster->m_lev;
        if (youdefend) {
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            if (m_canseeu(caster) && distu(caster->mx, caster->my) <= 192) {
                long side = rn2(3) ? LEFT_SIDE : RIGHT_SIDE;
                Your("%s are smashed by a bolt of force!",
                    makeplural(body_part(LEG)));

                if (!(uarmf && objdescr_is(uarmf, "jungle boots")))
                    set_wounded_legs(side, rn1(15, 15));
            }
        } else { /* mhitm */
            if (resist(mdef, 0, 0, FALSE)) {
                shieldeff(mdef->mx, mdef->my);
                dmg = (dmg + 1) / 2;
            }
            if (canseemon(mdef)) {
                pline("%s %s is smashed by a bolt of force!",
                    s_suffix(Monnam(mdef)),
                    mbodypart(mdef, LEG));
            }
        }
        break;
    case CLC_PARALYZE:
        if (youdefend) {
            dmg = 4 + (int) caster->m_lev;
            if (Antimagic || Free_action) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_MAGR);
                if (gm.multi >= 0)
                    You("stiffen briefly.");
                dmg = 1; /* to produce nomul(-1), not actual damage */
            } else {
                if (gm.multi >= 0)
                    You("are frozen in place!");
                if (Half_spell_damage)
                    dmg = (dmg + 1) / 2;
                monstunseesu(M_SEEN_MAGR);
            }
            nomul(-dmg);
            gm.multi_reason = "paralyzed by a monster";
            gn.nomovemsg = 0;
        } else { /* mhitm */
            if (resist(mdef, 0, 0, FALSE)) {
                shieldeff(mdef->mx, mdef->my);
                if (canseemon(mdef))
                    pline("%s stiffens briefly.", Monnam(mdef));
            } else {
                if (canseemon(mdef))
                    pline("%s is frozen in place!", Monnam(mdef));
                dmg = 4 + mons[caster->mnum].mlevel;
                mdef->mcanmove = 0;
                mdef->mfrozen = dmg;
            }
        }
        dmg = 0;
        break;
    case CLC_CONFUSE_YOU:
        if (youdefend) {
            if (Antimagic) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_MAGR);
                You_feel("momentarily dizzy.");
            } else {
                boolean oldprop = !!Confusion;

                dmg = (int) caster->m_lev;
                if (Half_spell_damage)
                    dmg = (dmg + 1) / 2;
                make_confused(HConfusion + dmg, TRUE);
                if (Hallucination)
                    You_feel("%s!", oldprop ? "trippier" : "trippy");
                else
                    You_feel("%sconfused!", oldprop ? "more " : "");
                monstunseesu(M_SEEN_MAGR);
            }
        } else { /* mhitm */
            if (resist(mdef, 0, 0, FALSE)) {
                shieldeff(mdef->mx, mdef->my);
                if (canseemon(mdef))
                    pline("%s seems momentarily dizzy.", Monnam(mdef));
            } else {
                if (canseemon(mdef))
                    pline("%s seems %sconfused!", Monnam(mdef),
                        mdef->mconf ? "more " : "");
                mdef->mconf = 1;
            }
        }

        dmg = 0;
        break;
    case CLC_CURE_SELF:
        dmg = m_cure_self(caster, dmg);
        break;
    case CLC_OPEN_WOUNDS:
#if 0 /* EvilHack version of damage - use this? */
        dmg = d((int) (((yours ? mons[u.umonnum].mlevel
                               : min(caster->m_lev, 50)) / 2) + 1), 6);
#endif
        if (youdefend) {
            if (Antimagic) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_MAGR);
                dmg = (dmg + 1) / 2;
            } else {
                monstunseesu(M_SEEN_MAGR);
            }
            if (dmg <= 5)
                Your("skin itches badly for a moment.");
            else if (dmg <= 10)
                pline("Wounds appear on your body!");
            else if (dmg <= 20)
                pline("Severe wounds appear on your body!");
            else
                Your("body is covered with painful wounds!");
        } else { /* mhitm */
            if (resist(mdef, 0, 0, FALSE)) {
                shieldeff(mdef->mx, mdef->my);
                dmg = (dmg + 1) / 2;
            }
            if (canseemon(mdef)) {
                if (dmg <= 5)
                    pline("%s looks itchy!", Monnam(mdef));
                else if (dmg <= 10)
                    pline("Wounds appear on %s!", mon_nam(mdef));
                else if (dmg <= 20)
                    pline("Severe wounds appear on %s!", mon_nam(mdef));
                else
                    pline("%s is covered in wounds!", Monnam(mdef));
            }
        }
        break;
    case CLC_PROTECTION: {
        int natac = find_mac(caster) + caster->mprotection;
        int loglev = 0, gain = 0;
        dmg = 0;

        for (; ml > 0; ml /= 2)
            loglev++;

        gain = loglev - caster->mprotection / (4 - min(3, (10 - natac) / 10));

        if (caster->mpeaceful) {
            ; /* cut down on the protection spam */
        } else {
            if (gain && canseemon(caster)) {
                if (caster->mprotection) {
                    pline_The("%s haze around %s becomes more dense.",
                              hcolor(NH_GOLDEN), mon_nam(caster));
                } else {
                    caster->mprottime = (caster->iswiz || is_prince(caster->data)
                                       || caster->data->msound == MS_NEMESIS
                                       || caster->data->msound == MS_LEADER)
                                       ? 20 : 10;
                    pline_The("air around %s begins to shimmer with a %s haze.",
                              mon_nam(caster), hcolor(NH_GOLDEN));
                }
            }
        }
        caster->mprotection += gain;
        break;
    }
    default:
        impossible("mcastu: invalid clerical spell (%d)", spellnum);
        dmg = 0;
        break;
    }

    if (youdefend && dmg)
        mdamageu(caster, dmg);
    return dmg;
}

RESTORE_WARNING_FORMAT_NONLITERAL

staticfn boolean
is_undirected_spell(unsigned int adtyp, int spellnum)
{
    if (adtyp == AD_SPEL) {
        switch (spellnum) {
        case MGC_CLONE_WIZ:
        case MGC_SUMMON_MONS:
        case MGC_AGGRAVATION:
        case MGC_DISAPPEAR:
        case MGC_HASTE_SELF:
        case MGC_CURE_SELF:
        case MGC_CALL_UNDEAD:
        case MGC_FIRE_BOLT:
        case MGC_ICE_BOLT:
        case MGC_ACID_BLAST:
        case MGC_REFLECTION:
        case MGC_EVIL_EYE:
        case MGC_ENTOMB:
            return TRUE;
        default:
            break;
        }
    } else if (adtyp == AD_CLRC) {
        switch (spellnum) {
        case CLC_INSECTS:
        case CLC_SPHERES:
        case CLC_CURE_SELF:
        case CLC_PROTECTION:
        case CLC_BLIGHT:
        case CLC_HOBBLE:
        case CLC_FIRE_PILLAR:
            return TRUE;
        default:
            break;
        }
    }
    return FALSE;
}

/* Some spells are useless under some circumstances. */
staticfn boolean
spell_would_be_useless(struct monst *caster, unsigned int adtyp, int spellnum)
{
    /* Some spells don't require the player to really be there and can be cast
     * by the monster when you're invisible, yet still shouldn't be cast when
     * the monster doesn't even think you're there.
     * This check isn't quite right because it always uses your real position.
     * We really want something like "if the monster could see mux, muy".
     */
    boolean mcouldseeu = couldsee(caster->mx, caster->my);
    struct trap *trap = t_at(caster->mx, caster->my);

    /* Anti-magic fields block spellcasting */
    if (trap && trap->ttyp == ANTI_MAGIC)
        return TRUE;

    if (adtyp == AD_SPEL) {
        /* aggravate monsters, etc. won't be cast by peaceful monsters */
        if (caster->mpeaceful
            && (spellnum == MGC_AGGRAVATION
                || spellnum == MGC_SUMMON_MONS
                || spellnum == MGC_CALL_UNDEAD
                || spellnum == MGC_EVIL_EYE
                || spellnum == MGC_CLONE_WIZ))
            return TRUE;
        /* haste self when already fast */
        if (caster->permspeed == MFAST && spellnum == MGC_HASTE_SELF)
            return TRUE;
        /* invisibility when already invisible */
        if ((caster->minvis || caster->invis_blkd) && spellnum == MGC_DISAPPEAR)
            return TRUE;
        if ((has_reflection(caster) || mon_reflects(caster, (char *) 0))
            && spellnum == MGC_REFLECTION)
            return TRUE;
        /* peaceful monster won't cast invisibility. This doesn't
           really make a lot of sense, but lets the player avoid hitting
           peaceful monsters by mistake */
        if (caster->mpeaceful && spellnum == MGC_DISAPPEAR)
            return TRUE;
        /* healing when already healed */
        if (spellnum == MGC_CURE_SELF && (caster->mhp == caster->mhpmax
            && !caster->mdiseased && !caster->mwither && !caster->mblinded))
            return TRUE;
        /* don't summon monsters if it doesn't think you're around */
        if (!mcouldseeu && (spellnum == MGC_SUMMON_MONS
                            || spellnum == MGC_CALL_UNDEAD
                            || (!caster->iswiz && spellnum == MGC_CLONE_WIZ)))
            return TRUE;
        /* only undead and demons can cast evil eye/call undead */
        if (spellnum == MGC_EVIL_EYE || spellnum == MGC_CALL_UNDEAD) {
            if (!is_undead(caster->data) && !is_demon(caster->data))
                return TRUE;
        }
        if ((!caster->iswiz || svc.context.no_of_wizards > 1)
            && spellnum == MGC_CLONE_WIZ)
            return TRUE;
        /* aggravation (global wakeup) when everyone is already active */
        if (spellnum == MGC_AGGRAVATION) {
            /* if nothing needs to be awakened then this spell is useless
               but caster might not realize that [chance to pick it then
               must be very small otherwise caller's many retry attempts
               will eventually end up picking it too often] */
            if (!has_aggravatables(caster))
                return rn2(100) ? TRUE : FALSE;
        }
        if ((m_seenres(caster, M_SEEN_FIRE))
            && spellnum == MGC_FIRE_BOLT) {
            return TRUE;
        }
        if ((m_seenres(caster, M_SEEN_COLD))
            && spellnum == MGC_ICE_BOLT) {
            return TRUE;
        }
        if ((m_seenres(caster, M_SEEN_ACID))
            && spellnum == MGC_ACID_BLAST) {
            return TRUE;
        }
        if ((spellnum == MGC_ICE_BOLT || spellnum == MGC_FIRE_BOLT
             || spellnum == MGC_ACID_BLAST)
            && (caster->mpeaceful || u.uinvulnerable)) {
            return TRUE;
        }
        /* don't entomb if hero is already entombed */
        if (spellnum == MGC_ENTOMB && is_entombed(u.ux, u.uy))
            return TRUE;
        /* only entomb as a desperation measure */
        if (spellnum == MGC_ENTOMB && caster->mhp > (caster->mhpmax / 5)
            && !caster->mflee)
            return TRUE;
    } else if (adtyp == AD_CLRC) {
        /* summon insects/sticks to snakes won't be cast by peaceful monsters
         */
        if (caster->mpeaceful && (spellnum == CLC_INSECTS
                                || spellnum == CLC_SPHERES
                                || spellnum == CLC_HOBBLE
                                || spellnum == CLC_FIRE_PILLAR
                                || spellnum == CLC_BLIGHT))
            return TRUE;
        /* healing when already healed */
        if (caster->mhp == caster->mhpmax && spellnum == CLC_CURE_SELF
            && !caster->mdiseased && !caster->mwither && !caster->mblinded)
            return TRUE;
        /* don't summon insects if it doesn't think you're around */
        if (!mcouldseeu && (spellnum == CLC_INSECTS
                            || spellnum == CLC_SPHERES
                            || spellnum == CLC_HOBBLE
                            || spellnum == CLC_BLIGHT))
            return TRUE;
        /* blindness spell on blinded player */
        if (Blinded && spellnum == CLC_BLIND_YOU)
            return TRUE;

        /* Only arch-viles can cast fire pillar at range. */
        if (spellnum == CLC_FIRE_PILLAR
            && caster->data != &mons[PM_ARCH_VILE]
            && (distu(caster->mx, caster->my) > 2))
            return TRUE;

        if ((m_seenres(caster, M_SEEN_FIRE))
            && spellnum == CLC_FIRE_PILLAR) {
            return TRUE;
        }
        /* Prevent monsters from constantly spamming protection */
        if (spellnum == CLC_PROTECTION && rn2(caster->mprotection + 1)
            && !(caster->mhp * 2 <= caster->mhpmax)) {
            return TRUE;
        }
    }
    return FALSE;
}

staticfn boolean
mspell_would_be_useless(
    struct monst *caster, struct monst *mdef,
    unsigned int adtyp, int spellnum)
{
    boolean evilpriest = (caster->ispriest && mon_aligntyp(caster) < A_NEUTRAL);

    if (adtyp == AD_SPEL) {
        /* don't cast these spells at range vs other monsters */
        if (distmin(caster->mx, caster->my, mdef->mx, mdef->my) > 1
            && (spellnum == MGC_PSI_BOLT
                || spellnum == MGC_STUN_YOU
                || spellnum == MGC_WEAKEN_YOU
                || spellnum == MGC_CURSE_ITEMS
                || spellnum == MGC_AGGRAVATION
                || spellnum == MGC_SUMMON_MONS
                || spellnum == MGC_CLONE_WIZ
                || spellnum == MGC_DEATH_TOUCH
                || spellnum == MGC_CALL_UNDEAD))
            return TRUE;
        /* aggravate monsters, monster summoning won't
           be cast by tame or peaceful monsters */
        if ((caster->mtame || caster->mpeaceful)
            && (spellnum == MGC_AGGRAVATION
                || spellnum == MGC_CALL_UNDEAD
                || spellnum == MGC_CLONE_WIZ))
            return TRUE;
        /* haste self when already fast */
        if (caster->permspeed == MFAST && spellnum == MGC_HASTE_SELF)
            return TRUE;
        /* invisibility when already invisible */
        if ((caster->minvis || caster->invis_blkd)
            && spellnum == MGC_DISAPPEAR)
            return TRUE;
        /* don't let peacefuls disappear. */
        if ((caster->mtame || caster->mpeaceful)
            && !See_invisible && spellnum == MGC_DISAPPEAR)
            return TRUE;
        /* reflection when already reflecting */
        if ((has_reflection(caster) || mon_reflects(caster, (char *) 0))
            && spellnum == MGC_REFLECTION)
            return TRUE;
        /* healing when already healed */
        if (caster->mhp == caster->mhpmax && (spellnum == MGC_CURE_SELF)
            && !caster->mdiseased && !caster->mwither && !caster->mblinded)
            return TRUE;
        /* don't summon monsters if it doesn't think they're around */
        if ((!caster->iswiz || svc.context.no_of_wizards > 1)
            && spellnum == MGC_CLONE_WIZ)
            return TRUE;
        /* Don't try to destroy armor if none is being worn */
        if (!(mdef->misc_worn_check & W_ARMOR)
            && spellnum == MGC_DESTRY_ARMR) {
            return TRUE;
        }
        /* Don't blast itself with its own explosions
           if it doesn't resist the attack type (most times) */
        if (!(resists_fire(caster) || defended(caster, AD_FIRE))
            && spellnum == MGC_FIRE_BOLT
            && distmin(caster->mx, caster->my,
                       mdef->mx, mdef->my) < 3 && rn2(5)) {
            return TRUE;
        }
        if (!(resists_cold(caster) || defended(caster, AD_COLD))
            && spellnum == MGC_ICE_BOLT
            && distmin(caster->mx, caster->my,
                       mdef->mx, mdef->my) < 3 && rn2(5)) {
            return TRUE;
        }
        if (!(resists_acid(caster) || defended(caster, AD_ACID))
            && spellnum == MGC_ACID_BLAST
            && distmin(caster->mx, caster->my,
                       mdef->mx, mdef->my) < 3 && rn2(5)) {
            return TRUE;
        }
        /* prevent pet or peaceful monster from nuking
           the player if they are close to the target */
        if ((caster->mtame || caster->mpeaceful)
            && distu(mdef->mx, mdef->my) < 3
            && (spellnum == MGC_ICE_BOLT
                || spellnum == MGC_FIRE_BOLT
                || spellnum == MGC_ACID_BLAST)) {
            return TRUE;
        }
        /* only undead/demonic spell casters, chaotic/unaligned priests
           and quest nemesis can summon undead */
        if (spellnum == MGC_CALL_UNDEAD && !is_undead(caster->data)
            && !is_demon(caster->data) && !evilpriest
            && caster->data->msound != MS_NEMESIS)
            return TRUE;
     } else if (adtyp == AD_CLRC) {
        /* don't cast these spells at range vs other monsters */
        if (distmin(caster->mx, caster->my, mdef->mx, mdef->my) > 1
            && (spellnum == CLC_CONFUSE_YOU
                || spellnum == CLC_PARALYZE
                || spellnum == CLC_BLIND_YOU
                || spellnum == CLC_CURSE_ITEMS
                || spellnum == CLC_LIGHTNING
                || spellnum == CLC_GEYSER
                /* Only arch-viles can cast fire pillar at range. */
                || (spellnum == CLC_FIRE_PILLAR
                    && caster->data != &mons[PM_ARCH_VILE])))
            return TRUE;
        /* healing when already healed */
        if (caster->mhp == caster->mhpmax && spellnum == CLC_CURE_SELF
            && !caster->mdiseased && !caster->mwither && !caster->mblinded)
            return TRUE;
        /* blindness spell on blinded target */
        if ((!haseyes(mdef->data) || mdef->mblinded)
            && spellnum == CLC_BLIND_YOU)
            return TRUE;
        /* monster summoning won't be cast by tame
           or peaceful monsters */
        if ((caster->mtame || caster->mpeaceful)
            && (spellnum == CLC_INSECTS || spellnum == CLC_SPHERES))
            return TRUE;
    }
    return FALSE;
}

/* monster uses spell (ranged) */
int
buzzmu(struct monst *caster, struct attack *mattk)
{
    /* don't print constant stream of curse messages for 'normal'
       spellcasting monsters at range */
    if (!BZ_VALID_ADTYP(mattk->adtyp))
        return M_ATTK_MISS;

    if (caster->mcan || m_seenres(caster, cvt_adtyp_to_mseenres(mattk->adtyp))) {
        cursetxt(caster, FALSE);
        return M_ATTK_MISS;
    }
    if (lined_up(caster) && !rn2(3)) {
        nomul(0);
        if (canseemon(caster))
            pline_mon(caster, "%s zaps you with a %s!", Monnam(caster),
                  flash_str(BZ_OFS_AD(mattk->adtyp), FALSE));
        gb.buzzer = caster;
        buzz(BZ_M_SPELL(BZ_OFS_AD(mattk->adtyp)), (int) mattk->damn,
             caster->mx, caster->my, sgn(gt.tbx), sgn(gt.tby));
        gb.buzzer = 0;
        return M_ATTK_HIT;
    }
    return M_ATTK_MISS;
}


/* monster uses spell against monster (ranged) */
int
buzzmm(
    register struct monst *caster,
    register struct monst *mdef,
    register struct attack *mattk)
{
    boolean seecaster = (canseemon(caster) || tp_sensemon(caster) || Detect_monsters);

    /* don't print constant stream of curse messages for 'normal'
       spellcasting monsters at range */
    if (!BZ_VALID_ADTYP(mattk->adtyp))
        return M_ATTK_MISS;

    if (caster->mcan) {
        cursetxt(caster, FALSE);
        return M_ATTK_MISS;
    }
    if (m_lined_up(caster, mdef) && !rn2(3)) {
        if (mattk->adtyp && (mattk->adtyp <= ZT_STUN)) { /* no cf unsigned > 0 */
            if (seecaster)
                pline("%s zaps %s with a %s!",
                      Monnam(caster), mon_nam(mdef),
                      flash_str(BZ_OFS_AD(mattk->adtyp), FALSE));
            dobuzz(BZ_M_SPELL(BZ_OFS_AD(mattk->adtyp)), (int) mattk->damn,
                caster->mx, caster->my, sgn(gt.tbx), sgn(gt.tby), FALSE);
        } else
            impossible("Monster spell %d cast", mattk->adtyp - 1);
    }
    return M_ATTK_HIT;
}

int
castmm(
    struct monst *caster,
    struct monst *mdef,
    struct attack *mattk)
{
    int dmg, ml = min(caster->m_lev, 50);
    int ret;
    int spellnum = 0;

    // boolean seecaster = (canseemon(caster) || tp_sensemon(caster) || Detect_monsters);

    /* guard against casting another spell attack
       at an already dead monster; some monsters
       have multiple AT_MAGC attacks */
    if (mdef->mhp <= 0)
        return M_ATTK_MISS;

    if ((mattk->adtyp == AD_SPEL || mattk->adtyp == AD_CLRC) && ml) {
        int cnt = 40;

        do {
            spellnum = rn2(ml);
            if (mattk->adtyp == AD_SPEL)
                spellnum = choose_magic_spell(caster, spellnum);
            else
                spellnum = choose_clerical_spell(caster, spellnum);
        /* not trying to attack?  don't allow directed spells */
        } while (--cnt > 0
                 && mspell_would_be_useless(caster, mdef, mattk->adtyp, spellnum));
        if (cnt == 0)
            return M_ATTK_MISS;
    }

    /* monster unable to cast spells? */
    if (caster->mcan || caster->mspec_used || !ml) {
        if (canseemon(caster)) {
            if (is_undirected_spell(mattk->adtyp, spellnum))
                pline("%s points all around, then curses.",
                      Monnam(caster));
            else
                pline("%s points at %s, then curses.",
                      Monnam(caster), mon_nam(mdef));
        } else if ((!(svm.moves % 4) || !rn2(4))) {
            if (!Deaf)
                Norep("You hear a mumbled curse.");
        }
        return M_ATTK_MISS;
    }
    
    if (mattk->adtyp == AD_SPEL || mattk->adtyp == AD_CLRC) {
         /* monst->m_lev is unsigned (uchar), monst->mspec_used is int */
        caster->mspec_used =  (int) (4 - caster->m_lev);
        if (caster->mspec_used < 2)
            caster->mspec_used = 2;

        /* many boss-type monsters than have two or more spell attacks
           per turn are never able to fire off their second attack due
           to mspec always being greater than 0. So set to 0 for those
           types of monsters, either sometimes or all of the time
           depending on how powerful they are or what their role is */
        if (rn2(3) /* mspec 0 two thirds of the time */
            && (is_dlord(caster->data)
                || caster->data->msound == MS_LEADER
                || caster->data->msound == MS_NEMESIS
                || caster->data == &mons[PM_ORACLE]
                || caster->data == &mons[PM_HIGH_CLERIC]))
            caster->mspec_used = 0;

        if (is_dprince(caster->data) || caster->iswiz)
            caster->mspec_used = 0; /* mspec 0 always */

        /* Having the EotA in inventory drops mspec to 0 */
        if (carrying_arti(ART_EYE_OF_THE_AETHIOPICA) ||
            carrying_arti(ART_HOLOGRAPHIC_VOID_LILY) ) {
            caster->mspec_used = 0;
        }
    }

    if (rn2(ml * 10) < (caster->mconf ? 100 : 20)) {	/* fumbled attack */
        Soundeffect(se_air_crackles, 60);
        if (canseemon(caster) && !Deaf) {
            set_msg_xy(caster->mx, caster->my);
            pline_The("air crackles around %s.", mon_nam(caster));
        }
        return M_ATTK_MISS;
    }

    if (canspotmon(caster)) {
        if (!is_undirected_spell(mattk->adtyp, spellnum))
            pline_mon(caster, "%s casts a spell at %s!",
                canspotmon(caster) ? Monnam(caster) : "Something",
                mon_nam(mdef));

        if (is_undirected_spell(mattk->adtyp, spellnum))
            pline("%s casts a spell!", Monnam(caster));
    }

    if (u_wield_art(ART_SERENITY) || u_offhand_art(ART_SERENITY)
            || (uarms && uarms->otyp == ANTI_MAGIC_SHIELD)) {
        if (counterspell(caster))
            return 0;
    }

    /*
     * As these are spells, the damage is related to the level
     * of the monster casting the spell.
     */
    if (mattk->damd)
        dmg = d((int) ((ml / 2) + mattk->damn), (int) mattk->damd);
    else
        dmg = d((int) ((ml / 2) + 1), 6);

    ret = M_ATTK_HIT;

    switch (mattk->adtyp) {
    case AD_FIRE:
        if (canseemon(mdef)) {
            if (is_demon(caster->data))
                pline("%s is enveloped in hellfire!", Monnam(mdef));
            else if (!mon_underwater(mdef))
                pline("%s is enveloped in flames.", Monnam(mdef));
            else {
                pline("The flames are quenched by the water around %s.",
                      mon_nam(mdef));
                dmg = 0;
                break;
            }
        }

        if (resists_fire(mdef) || defended(mdef, AD_FIRE)) {
            shieldeff(mdef->mx, mdef->my);
            if (canseemon(mdef))
                pline("But %s resists the effects.", mhe(mdef));
            dmg = 0;
#if 0
             /* EvilHack: Some monsters are capable of extra hellfire damage.
              * This still burns fire-resistant monsters if they are not
              * demons or undead. */
            if (is_demon(caster->data)) {
                if (!(nonliving(mdef->data) || is_demon(mdef->data))) {
                    if (canseemon(mdef))
                        pline_The("hellish flames sear %s soul!",
                                  s_suffix(mon_nam(mdef)));
                    dmg = (dmg + 1) / 2;
                } else {
                    dmg = 0;
                }
            } else {
                if (canseemon(mdef))
                    pline("But %s resists the effects.", mhe(mdef));
                dmg = 0;
            }
#endif
        }
         /* burn up flammable items on the floor, melt ice terrain */
        mon_spell_hits_spot(caster, AD_FIRE, u.ux, u.uy);
        break;
    case AD_COLD:
        if (canseemon(mdef))
            pline("%s is covered in frost.", Monnam(mdef));
        if (resists_cold(mdef) || defended(mdef, AD_COLD)) {
            shieldeff(mdef->mx, mdef->my);
            if (canseemon(mdef))
                pline("But %s resists the effects.", mhe(mdef));
            dmg = 0;
        }
        /* freeze water or lava terrain */
        /* FIXME: mon_spell_hits_spot() uses zap_over_floor(); unlike with
         * fire, it does not target susceptible floor items with cold */
        mon_spell_hits_spot(caster, AD_COLD, u.ux, u.uy);
        break;
    case AD_ACID:
        if (canseemon(mdef)) {
            if (!mon_underwater(mdef))
                pline("%s is covered in acid.", Monnam(mdef));
            else {
                pline("The acid dissipates harmlessly in the water around %s.",
                      mon_nam(mdef));
                dmg = 0;
                break;
            }
        }
        if (resists_acid(mdef) || defended(mdef, AD_ACID)) {
            shieldeff(mdef->mx, mdef->my);
            if (canseemon(mdef))
                pline("But %s resists the effects.", mhe(mdef));
            dmg = 0;
        }
        break;
    case AD_MAGM:
        if (canseemon(mdef))
            pline("%s is hit by a shower of missiles!", Monnam(mdef));
        dmg = d((int) ml / 2 + 1, 6);
        if (resists_magm(mdef) || defended(mdef, AD_MAGM)) {
            shieldeff(mdef->mx, mdef->my);
            if (canseemon(mdef))
                pline("Some missiles bounce off!");
            dmg = (dmg + 1) / 2;
        }
        /* shower of magic missiles scuffs an engraving */
        mon_spell_hits_spot(caster, AD_MAGM, u.ux, u.uy);
        break;
    case AD_SPEL:  /* wizard spell */
        dmg = cast_wizard_spell(caster, mdef, dmg, spellnum);
        break;
    case AD_CLRC:  /* clerical spell */
        dmg = cast_cleric_spell(caster, mdef, dmg, spellnum);
        break;
    }

    if (dmg) {
        mdef->mhp -= dmg;
        if (DEADMONSTER(mdef))
            monkilled(mdef, "", mattk->adtyp);
    }

    return ret;
}

/* is (x,y) entombed (completely surrounded by boulders or nonwalkable spaces)?
 * note that (x,y) itself is not checked */
staticfn boolean
is_entombed(coordxy x, coordxy y)
{
    coordxy xx, yy;
    for (xx = x - 1; xx <= x + 1; xx++) {
        for (yy = y - 1; yy <= y + 1; yy++) {
            if (isok(xx, yy) && xx != x && yy != y
                && SPACE_POS(levl[xx][yy].typ) && !sobj_at(BOULDER, xx, yy))
                return FALSE;
        }
    }
    return TRUE;
}

staticfn boolean
counterspell(struct monst *caster) {
    struct obj *otmp;
    /* If any more items are added for countering spells, we should
     * create a property instead. */
    if (u_wield_art(ART_SERENITY))
        otmp = uwep;
    else if (u_offhand_art(ART_SERENITY))
        otmp = uswapwep;
    else if (uarms && uarms->otyp == ANTI_MAGIC_SHIELD)
        otmp = uarms;
    else {
        impossible("counterspell with no item?");
        return FALSE;
    }

    if (otmp->cursed)
        return FALSE;
    if (dist2(u.ux, u.uy, caster->mx, caster->my) > 192)
        return FALSE;
    if (!rn2(5))
        return FALSE;

    if (!rn2(4))
        Your("%s %s and %s %s magic!",
            xname(otmp), (Blind ? "vibrates" : "flashes"),
            !rn2(2) ? "absorbs" : "cancels", s_suffix(mon_nam(caster)));

    if (canseemon(caster)) {
        if (caster->data == &mons[PM_THING_FROM_BELOW])
            pline("%s %s!", Monnam(caster),
              rn2(2) ? "sputters" : rn2(2) ? "spits" : "hisses");
        else
            pline("%s %s!", Monnam(caster),
              rn2(2) ? "sputters" : rn2(2) ? "chokes" : "stutters");
    } else {
        You_hear("some cursing!");
    }

    /* A little salt... */
    caster->mspec_used += d(2, 3);
    return TRUE;
}

boolean
mcast_dist_ok(struct monst *caster)
{
    if (!m_canseeu(caster))
        return FALSE;
    if (distu(caster->mx, caster->my) > 192)
        return FALSE;
    /* Sometimes allow them to cast at close range. */
    if (distu(caster->mx, caster->my) <= 2 && rn2(5))
        return FALSE;
    return TRUE;
}

staticfn int
rnd_sphere(void)
{
    return PM_FREEZING_SPHERE + rn2(PM_ACID_SPHERE - PM_FREEZING_SPHERE);
}
/*mcastu.c*/
