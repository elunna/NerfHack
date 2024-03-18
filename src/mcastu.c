/* NetHack 3.7	mcastu.c	$NHDT-Date: 1705428596 2024/01/16 18:09:56 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.95 $ */
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
    CLC_HOBBLE
};

static void cursetxt(struct monst *, boolean);
static int choose_magic_spell(struct monst *, int);
static int choose_clerical_spell(struct monst *, int);
static int m_cure_self(struct monst *, int);
static void cast_wizard_spell(struct monst *, int, int);
static void cast_cleric_spell(struct monst *, int, int);
static boolean is_undirected_spell(unsigned int, int);
static boolean spell_would_be_useless(struct monst *, unsigned int, int);
static boolean is_entombed(coordxy, coordxy);
static boolean counterspell(struct monst *, struct obj *);

/* feedback when frustrated monster couldn't cast a spell */
static void
cursetxt(struct monst *mtmp, boolean undirected)
{
    if (canseemon(mtmp) && couldsee(mtmp->mx, mtmp->my)) {
        const char *point_msg; /* spellcasting monsters are impolite */

        if (undirected)
            point_msg = "all around, then curses";
        else if ((Invis && !perceives(mtmp->data)
                  && (mtmp->mux != u.ux || mtmp->muy != u.uy))
                 || is_obj_mappear(&gy.youmonst, STRANGE_OBJECT)
                 || u.uundetected)
            point_msg = "and curses in your general direction";
        else if (Displaced && (mtmp->mux != u.ux || mtmp->muy != u.uy))
            point_msg = "and curses at your displaced image";
        else
            point_msg = "at you, then curses";

        pline_xy(mtmp->mx, mtmp->my,
                 "%s points %s.", Monnam(mtmp), point_msg);
    } else if ((!(gm.moves % 4) || !rn2(4))) {
        if (!Deaf)
            Norep("You hear a mumbled curse.");   /* Deaf-aware */
    }
}

/* convert a level-based random selection into a specific mage spell;
   inappropriate choices will be screened out by spell_would_be_useless() */
static int
choose_magic_spell(struct monst* mtmp, int spellval)
{
    /* for 3.4.3 and earlier, val greater than 22 selected default spell */
    while (spellval > 24 && rn2(25))
        spellval = rn2(spellval);

    /* Low HP, prioritize healing */
    if ((mtmp->mhp * 4) <= mtmp->mhpmax) {
        if (!rn2(10) || mtmp->mflee)
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
        if (mtmp->mflee)
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
static int
choose_clerical_spell(struct monst* mtmp, int spellnum)
{
    /* for 3.4.3 and earlier, num greater than 13 selected the default spell
     */
    while (spellnum > 15 && rn2(16))
        spellnum = rn2(spellnum);

    /* Low HP, prioritize healing */
    if ((mtmp->mhp * 4) <= mtmp->mhpmax)
        spellnum = 1;

    switch (spellnum) {
    case 15:
    case 14:
        if (rn2(3))
            return CLC_OPEN_WOUNDS;
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
    struct monst *mtmp,   /* caster */
    struct attack *mattk, /* caster's current attack */
    boolean thinks_it_foundyou,    /* might be mistaken if displaced */
    boolean foundyou)              /* knows hero's precise location */
{
    int dmg, ml = mtmp->m_lev;
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
                spellnum = choose_magic_spell(mtmp, spellnum);
            else
                spellnum = choose_clerical_spell(mtmp, spellnum);
            /* not trying to attack?  don't allow directed spells */
            if (!thinks_it_foundyou) {
                if (!is_undirected_spell(mattk->adtyp, spellnum)
                    || spell_would_be_useless(mtmp, mattk->adtyp, spellnum)) {
                    if (foundyou)
                        impossible(
                       "spellcasting monster found you and doesn't know it?");
                    return M_ATTK_MISS;
                }
                break;
            }
        } while (--cnt > 0
                 && spell_would_be_useless(mtmp, mattk->adtyp, spellnum));
        if (cnt == 0)
            return M_ATTK_MISS;
    }

    /* monster unable to cast spells? */
    if (mtmp->mcan || mtmp->mspec_used || !ml
        || m_seenres(mtmp, cvt_adtyp_to_mseenres(mattk->adtyp))) {
        cursetxt(mtmp, is_undirected_spell(mattk->adtyp, spellnum));
        return M_ATTK_MISS;
    }

    if (mattk->adtyp == AD_SPEL || mattk->adtyp == AD_CLRC) {
        /* monst->m_lev is unsigned (uchar), permonst->mspec_used is int */
        mtmp->mspec_used = (int) ((mtmp->m_lev < 8) ? (10 - mtmp->m_lev) : 2);
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
        pline_xy(mtmp->mx, mtmp->my, "%s casts a spell at %s!",
                 canseemon(mtmp) ? Monnam(mtmp) : "Something",
                 is_waterwall(mtmp->mux, mtmp->muy) ? "empty water"
                                                    : "thin air");
        return M_ATTK_MISS;
    }

    nomul(0);
    if (rn2(ml * 10) < (mtmp->mconf ? 100 : 20)) { /* fumbled attack */
        Soundeffect(se_air_crackles, 60);
        if (canseemon(mtmp) && !Deaf) {
            set_msg_xy(mtmp->mx, mtmp->my);
            pline_The("air crackles around %s.", mon_nam(mtmp));
        }
        return M_ATTK_MISS;
    }
    if (canspotmon(mtmp) || !is_undirected_spell(mattk->adtyp, spellnum)) {
        pline_xy(mtmp->mx, mtmp->my, "%s casts a spell%s!",
                 canspotmon(mtmp) ? Monnam(mtmp) : "Something",
                 is_undirected_spell(mattk->adtyp, spellnum) ? ""
                 : (Invis && !perceives(mtmp->data)
                    && !u_at(mtmp->mux, mtmp->muy))
                   ? " at a spot near you"
                   : (Displaced && !u_at(mtmp->mux, mtmp->muy))
                     ? " at your displaced image"
                     : " at you");
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
                       Monnam(mtmp), mattk->adtyp);
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
        mon_spell_hits_spot(mtmp, AD_FIRE, u.ux, u.uy);
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
        mon_spell_hits_spot(mtmp, AD_COLD, u.ux, u.uy);
        break;
    case AD_MAGM:
        You("are hit by a shower of missiles!");
        dmg = d((int) mtmp->m_lev / 2 + 1, 6);
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
        mon_spell_hits_spot(mtmp, AD_MAGM, u.ux, u.uy);
        break;
    case AD_SPEL: /* wizard spell */
    case AD_CLRC: /* clerical spell */
    {
        if (mattk->adtyp == AD_SPEL)
            cast_wizard_spell(mtmp, dmg, spellnum);
        else
            cast_cleric_spell(mtmp, dmg, spellnum);
        dmg = 0; /* done by the spell casting functions */
        break;
    }
    } /* switch */
    if (dmg)
        mdamageu(mtmp, dmg);
    return ret;
}

static int
m_cure_self(struct monst *mtmp, int dmg)
{
    if (mtmp->mhp < mtmp->mhpmax) {
        if (canseemon(mtmp))
            pline("%s looks better.", Monnam(mtmp));
        /* note: player healing does 6d4; this used to do 1d8 */
        if ((mtmp->mhp += d(3, 6)) > mtmp->mhpmax)
            mtmp->mhp = mtmp->mhpmax;
        dmg = 0;
    }
    return dmg;
}

/* unlike the finger of death spell which behaves like a wand of death,
   this monster spell only attacks the hero */
void
touch_of_death(struct monst *mtmp)
{
    char kbuf[BUFSZ];
    int dmg = 50 + d(8, 6);
    int drain = dmg / 2;

    /* if we get here, we know that hero isn't magic resistant and isn't
       poly'd into an undead or demon */
    You_feel("drained...");
    (void) death_inflicted_by(kbuf, "the touch of death", mtmp);

    if (Upolyd) {
        u.mh = 0;
        rehumanize(); /* fatal iff Unchanging */
    } else if (drain >= u.uhpmax) {
        gk.killer.format = KILLED_BY;
        Strcpy(gk.killer.name, kbuf);
        done(DIED);
    } else {
        u.uhpmax -= drain;
        losehp(dmg, kbuf, KILLED_BY);
    }
    gk.killer.name[0] = '\0'; /* not killed if we get here... */
}

/* give a reason for death by some monster spells */
char *
death_inflicted_by(
    char *outbuf,            /* assumed big enough; pm_names are short */
    const char *deathreason, /* cause of death */
    struct monst *mtmp)      /* monster who caused it */
{
    Strcpy(outbuf, deathreason);
    if (mtmp) {
        struct permonst *mptr = mtmp->data,
            *champtr = (ismnum(mtmp->cham)) ? &mons[mtmp->cham] : mptr;
        const char *realnm = pmname(champtr, Mgender(mtmp)),
            *fakenm = pmname(mptr, Mgender(mtmp));

        /* greatly simplified extract from done_in_by(), primarily for
           reason for death due to 'touch of death' spell; if mtmp is
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
m_destroy_armor(struct monst *mattk, struct monst *mdef)
{
    boolean udefend = (mdef == &gy.youmonst),
            uattk = (mattk == &gy.youmonst);
    boolean mtrap = !mattk;
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
                      : uattk ? "your" : s_suffix(mon_nam(mattk)));
            }
            return 0;
        } else if (oatmp->otyp == CRYSTAL_PLATE_MAIL) {
            if (udefend && !Blind)
                pline("%s glimmers brightly.", Yname2(oatmp));
            pline("%s is immune to %s destructive magic.",
                  Yname2(oatmp),
                  mtrap ? "the trap's" 
                  : uattk ? "your" : s_suffix(mon_nam(mattk)));
            return 0; /* no effect */
        } else if (oatmp->oerodeproof) {
            if (!udefend && !canseemon(mdef)) {
                You("smell something strange.");
            } else if (!Blind) {
                pline("%s glows brown for a moment.", Yname2(oatmp));
            } else {
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
static
void
cast_wizard_spell(struct monst *mtmp, int dmg, int spellnum)
{
    int ml = min(mtmp->m_lev, 50);
    int orig_dmg = 0;
    if (dmg == 0 && !is_undirected_spell(AD_SPEL, spellnum)) {
        impossible("cast directed wizard spell (%d) with dmg=0?", spellnum);
        return;
    }

    if (u_wield_art(ART_SERENITY) && rn2(5)) {
        pline("%s shines and %s %s magic!", artiname(uwep->oartifact),
            !rn2(2) ? "absorbs" : "cancels", s_suffix(mon_nam(mtmp)));
        /* TODO: Maybe more explicit astonishment? */
        if (canseemon(mtmp)) {
            pline("%s curses!", Monnam(mtmp));
        } else {
            You_hear("some cursing!");
        }
        return;
    }
    
    switch (spellnum) {
    case MGC_DEATH_TOUCH:
        pline("Oh no, %s's using the touch of death!", mhe(mtmp));
        if (nonliving(gy.youmonst.data)) {
            You("seem no deader than before.");
        } else if (resists_death(gy.youmonst.data)) {
            You("are unaffected.");
        } else if (!Antimagic && rn2(mtmp->m_lev) > 12) {
            if (Hallucination) {
                You("have an out of body experience.");
            } else {
                touch_of_death(mtmp);
            }
            monstunseesu(M_SEEN_MAGR);
        } else {
            if (Antimagic) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_MAGR);
            }
            pline("Lucky for you, it didn't work!");
        }
        dmg = 0;
        break;
    case MGC_REFLECTION: {
        boolean strongbad = (mtmp->iswiz || is_prince(mtmp->data)
                             || mtmp->data->msound == MS_NEMESIS
                             || mtmp->data->msound == MS_LEADER);
        if (canseemon(mtmp))
            pline("A shimmering globe appears around %s!", mon_nam(mtmp));
        /* monster reflection is handled in mon_reflects() */
        mtmp->mextrinsics |= MR2_REFLECTION;
        mtmp->mreflecttime = rn1(50, strongbad ? 200 : 100);
        dmg = 0;
        break;
    }
    case MGC_ACID_BLAST:
        orig_dmg = dmg = d((ml / 2) + 4, 6);
        if (m_canseeu(mtmp) && distu(mtmp->mx, mtmp->my) <= 192) {
            pline("%s douses you in a torrent of acid!", Monnam(mtmp));
            if (Acid_resistance) {
                shieldeff(u.ux, u.uy);
                pline("The acid doesn't harm you.");
                monstseesu(M_SEEN_ACID);
                dmg = 0;
            }
            if (rn2(u.twoweap ? 2 : 3))
                acid_damage(uwep);
            if (u.twoweap && rn2(2))
                acid_damage(uswapwep);
            if (rn2(4))
                erode_armor(&gy.youmonst, ERODE_CORRODE);
            if (!rn2(2))
                (void) destroy_items(&gy.youmonst, AD_ACID, orig_dmg);
        } else {
            if (canseemon(mtmp)) {
                pline("%s blasts the %s with %s and curses!",
                      Monnam(mtmp), rn2(2) ? "ceiling"
                                           : "floor", "acid");
            } else {
                You_hear("some cursing!");
            }
            dmg = 0;
        }
        break;
    case MGC_CLONE_WIZ:
        if (mtmp->iswiz && gc.context.no_of_wizards == 1) {
            pline("Double Trouble...");
            clonewiz();
            dmg = 0;
        } else
            impossible("bad wizard cloning?");
        break;
    case MGC_SUMMON_MONS: {
        int count = nasty(mtmp, FALSE);

        if (!count) {
            ; /* nothing was created? */
        } else if (mtmp->iswiz) {
            SetVoice(mtmp, 0, 80, 0);
            verbalize("Destroy the thief, my pet%s!", plur(count));
        } else {
            boolean one = (count == 1);
            const char *mappear = one ? "A monster appears"
                                      : "Monsters appear";

            /* messages not quite right if plural monsters created but
               only a single monster is seen */
            if (Invis && !perceives(mtmp->data)
                && (mtmp->mux != u.ux || mtmp->muy != u.uy))
                pline("%s %s a spot near you!", mappear,
                      one ? "at" : "around");
            else if (Displaced && (mtmp->mux != u.ux || mtmp->muy != u.uy))
                pline("%s %s your displaced image!", mappear,
                      one ? "by" : "around");
            else
                pline("%s from nowhere!", mappear);
        }
        dmg = 0;
        break;
    }
    case MGC_CALL_UNDEAD: {
        if (m_canseeu(mtmp) && distu(mtmp->mx, mtmp->my) <= 192) {
            coord mm;
            mm.x = u.ux;
            mm.y = u.uy;
            pline("Undead creatures are called forth from the grave!");
            mkundead(&mm, FALSE, NO_MINVENT);
            dmg = 0;
        }
        break;
    }
    case MGC_AGGRAVATION:
        You_feel("that monsters are aware of your presence.");
        aggravate();
        dmg = 0;
        break;
    case MGC_CURSE_ITEMS:
        You_feel("as if you need some help.");
        rndcurse();
        dmg = 0;
        break;
    case MGC_DESTRY_ARMR:
        dmg = m_destroy_armor(mtmp, &gy.youmonst);
        break;
    case MGC_EVIL_EYE: { /* drains luck */
        struct attack evilEye = { AT_GAZE, AD_LUCK, 1, 4 };
        (void) gazemu(mtmp, &evilEye);
        dmg = 0;
        break;
    }
    case MGC_WEAKEN_YOU: /* drain strength */
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            You_feel("momentarily weakened.");
        } else {
            char kbuf[BUFSZ];

            You("suddenly feel weaker!");
            dmg = mtmp->m_lev - 6;
            if (dmg < 1) /* paranoia since only chosen when m_lev is high */
                dmg = 1;
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            losestr(rnd(dmg),
                    death_inflicted_by(kbuf, "strength loss", mtmp),
                    KILLED_BY);
            gk.killer.name[0] = '\0'; /* not killed if we get here... */
            monstunseesu(M_SEEN_MAGR);
        }
        dmg = 0;
        break;
    case MGC_DISAPPEAR: /* makes self invisible */
        if (!mtmp->minvis && !mtmp->invis_blkd) {
            if (canseemon(mtmp))
                pline("%s suddenly %s!", Monnam(mtmp),
                      !See_invisible ? "disappears" : "becomes transparent");
            mon_set_minvis(mtmp);
            if (cansee(mtmp->mx, mtmp->my) && !canspotmon(mtmp))
                map_invisible(mtmp->mx, mtmp->my);
            dmg = 0;
        } else
            impossible("no reason for monster to cast disappear spell?");
        break;
    case MGC_STUN_YOU:
        if (Antimagic || Free_action) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            if (!Stunned || Stun_resistance)
                You_feel("momentarily disoriented.");
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
        dmg = 0;
        break;
    case MGC_HASTE_SELF:
        mon_adjust_speed(mtmp, 1, (struct obj *) 0);
        dmg = 0;
        break;
    case MGC_CURE_SELF:
        dmg = m_cure_self(mtmp, dmg);
        break;
    case MGC_FIRE_BOLT:
        /* hotwire these to only go off if the critter can see you
         * to avoid bugs WRT the Eyes and detect monsters */
        orig_dmg = dmg = d((ml / 5) + 1, 8);
        if (m_canseeu(mtmp) && distu(mtmp->mx, mtmp->my) <= 192) {
            pline("%s blasts you with a bolt of fire!", Monnam(mtmp));
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
        } else {
            if (canseemon(mtmp)) {
                pline("%s blasts the %s with fire and curses!",
                      Monnam(mtmp), rn2(2) ? "ceiling" : "floor");
            } else {
                You_hear("some cursing!");
            }
            dmg = 0;
        }
        break;
    case MGC_ICE_BOLT:
        orig_dmg = dmg = d((ml / 5) + 1, 8);
        if (m_canseeu(mtmp) && distu(mtmp->mx, mtmp->my) <= 192) {
            pline("%s blasts you with a bolt of cold!", Monnam(mtmp));
            if (fully_resistant(COLD_RES)) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_COLD);
                dmg = 0;
            } else {
                resist_reduce(dmg, COLD_RES);
                monstunseesu(M_SEEN_COLD);
            }
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            (void) destroy_items(&gy.youmonst, AD_COLD, orig_dmg);
        } else {
            if (canseemon(mtmp)) {
                pline("%s blasts the %s with cold and curses!",
                      Monnam(mtmp), rn2(2) ? "ceiling" : "floor");
            } else {
                You_hear("some cursing!");
            }
            dmg = 0;
        }
        break;
    case MGC_PSI_BOLT:
        /* prior to 3.4.0 Antimagic was setting the damage to 1--this
           made the spell virtually harmless to players with magic res. */
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
        break;
    case MGC_ENTOMB: {
        /* entomb you in rocks to delay you and get away */
        coordxy x, y;
        /* Only allow casting at relatively short-range */
        if (m_canseeu(mtmp) && distu(mtmp->mx, mtmp->my) <= 26
            /* Don't cast if we get hit by the boulders! */
            && distu(mtmp->mx, mtmp->my) > 2) {
            pline_The("ground shakes violently!");
            if (!Blind)
                pline("Boulders fall from above!");
            for (x = u.ux - 1; x <= u.ux + 1; ++x) {
                for (y = u.uy - 1; y <= u.uy + 1; ++y) {
                    if (!isok(x, y))
                        continue;
                    if (!SPACE_POS(levl[x][y].typ))
                        continue;
                    if (x == u.ux && y == u.uy)
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

    if (dmg)
        mdamageu(mtmp, dmg);
}

DISABLE_WARNING_FORMAT_NONLITERAL

static void
cast_cleric_spell(struct monst *mtmp, int dmg, int spellnum)
{
    int ml = min(mtmp->m_lev, 50);
    int orig_dmg = 0;
    if (dmg == 0 && !is_undirected_spell(AD_CLRC, spellnum)) {
        impossible("cast directed cleric spell (%d) with dmg=0?", spellnum);
        return;
    }
    
    if (u_wield_art(ART_SERENITY) && rn2(5)) {
        if (counterspell(mtmp, uwep))
            return;
    }

    switch (spellnum) {
    case CLC_BLIGHT: {
        /* This could use is_fleshy(), but that would make a large set 
         * of monsters immune like fungus, blobs, and jellies. */
        boolean no_effect = nonliving(gy.youmonst.data);

        if (!no_effect && m_canseeu(mtmp)
            && distu(mtmp->mx, mtmp->my) <= 65) {
            You("%s rapidly decomposing!", Withering ? "continue" : "begin");
            incr_itimeout(&HWithering, rn1(41, 20));
            dmg = 0;
        }
        break;
    }
    case CLC_GEYSER:
        /* this is physical damage (force not heat),
         * not magical damage or fire damage
         */
        pline("A sudden geyser slams into you from nowhere!");
        dmg = d(8, 6);
        if (Half_physical_damage)
            dmg = (dmg + 1) / 2;
        if (u.umonnum == PM_IRON_GOLEM) {
            You("rust!");
            Strcpy(gk.killer.name, "rusted away");
            gk.killer.format = NO_KILLER_PREFIX;
            rehumanize();
            dmg = 0; /* prevent further damage after rehumanization */
        }
        erode_armor(&gy.youmonst, ERODE_RUST);
        /* since inventory items aren't affected, don't include this */
        /* make floor items wet */
        water_damage_chain(gl.level.objects[u.ux][u.uy], TRUE);
        break;
    case CLC_FIRE_PILLAR:
        pline("A pillar of fire strikes all around you!");
        orig_dmg = dmg = d(8, 6);
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
        /* burn up flammable items on the floor, melt ice terrain */
        mon_spell_hits_spot(mtmp, AD_FIRE, u.ux, u.uy);
        break;
    case CLC_LIGHTNING: {
        boolean reflects;

        Soundeffect(se_bolt_of_lightning, 80);
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
        /* lightning might destroy iron bars if hero is on such a spot;
           reflection protects terrain here [execution won't get here due
           to 'if (reflects) break' above] but hero resistance doesn't;
           do this before maybe blinding the hero via flashburn() */
        mon_spell_hits_spot(mtmp, AD_ELEC, u.ux, u.uy);
        /* blind hero; no effect if already blind */
        (void) flashburn((long) rnd(100));
        break;
    }
    case CLC_CURSE_ITEMS:
        You_feel("as if you need some help.");
        rndcurse();
        dmg = 0;
        break;
    case CLC_INSECTS: {
        /* Try for insects, and if there are none
           left, go for (sticks to) snakes.  -3.
           Lolth summons spiders as he does in EvilHack */
        boolean spiders = (mtmp->data == &mons[PM_LOLTH]);
        struct permonst *pm = mkclass(S_ANT, 0);
        struct monst *mtmp2 = (struct monst *) 0;
        char whatbuf[QBUFSZ],
            let = (pm ? (spiders ? S_SPIDER : S_ANT) : S_SNAKE);
        boolean success = FALSE, seecaster;
        int i, quan, oldseen, newseen;
        coord bypos;
        const char *fmt, *what;

        oldseen = monster_census(TRUE);
        quan = (mtmp->m_lev < 2) ? 1 : rnd((int) mtmp->m_lev / 2);
        if (quan < 3)
            quan = 3;
        for (i = 0; i <= quan; i++) {
            if (!enexto(&bypos, mtmp->mux, mtmp->muy, mtmp->data))
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
        seecaster = canseemon(mtmp) || tp_sensemon(mtmp) || Detect_monsters;
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
        } else if (Invis && !perceives(mtmp->data)
                   && (mtmp->mux != u.ux || mtmp->muy != u.uy)) {
            fmt = "%s summons %s around a spot near you!";
        } else if (Displaced && (mtmp->mux != u.ux || mtmp->muy != u.uy)) {
            fmt = "%s summons %s around your displaced image!";
        } else {
            fmt = "%s summons %s!";
        }
        if (fmt)
            pline(fmt, Monnam(mtmp), what);

        dmg = 0;
        break;
    }
    case CLC_BLIND_YOU:
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
        break;
    case CLC_HOBBLE: {
        if (m_canseeu(mtmp) && distu(mtmp->mx, mtmp->my) <= 192) {
            long side = rn2(3) ? LEFT_SIDE : RIGHT_SIDE;
            Your("%s are smashed by a bolt of force!",
                 makeplural(body_part(LEG)));

            if (!(uarmf && objdescr_is(uarmf, "jungle boots")))
                set_wounded_legs(side, rn1(100, 50));
        }
        break;
    }
    case CLC_PARALYZE:
        dmg = 4 + (int) mtmp->m_lev;
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
        dmg = 0;
        break;
    case CLC_CONFUSE_YOU:
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            You_feel("momentarily dizzy.");
        } else {
            boolean oldprop = !!Confusion;

            dmg = (int) mtmp->m_lev;
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            make_confused(HConfusion + dmg, TRUE);
            if (Hallucination)
                You_feel("%s!", oldprop ? "trippier" : "trippy");
            else
                You_feel("%sconfused!", oldprop ? "more " : "");
            monstunseesu(M_SEEN_MAGR);
        }
        dmg = 0;
        break;
    case CLC_CURE_SELF:
        dmg = m_cure_self(mtmp, dmg);
        break;
    case CLC_OPEN_WOUNDS:
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
        break;
    case CLC_PROTECTION: {
        int natac = find_mac(mtmp) + mtmp->mprotection;
        int loglev = 0;
        int gain = 0;

        dmg = 0;

        for (; ml > 0; ml /= 2)
            loglev++;

        gain = loglev - mtmp->mprotection / (4 - min(3, (10 - natac) / 10));

        if (mtmp->mpeaceful) {
            ; /* cut down on the protection spam */
        } else {
            if (gain && canseemon(mtmp)) {
                if (mtmp->mprotection) {
                    pline_The("%s haze around %s becomes more dense.",
                              hcolor(NH_GOLDEN), mon_nam(mtmp));
                } else {
                    mtmp->mprottime = (mtmp->iswiz || is_prince(mtmp->data)
                                       || mtmp->data->msound == MS_NEMESIS
                                       || mtmp->data->msound == MS_LEADER)
                                       ? 20 : 10;
                    pline_The("air around %s begins to shimmer with a %s haze.",
                              mon_nam(mtmp), hcolor(NH_GOLDEN));
                }
            }
        }
        mtmp->mprotection += gain;
        break;
    }
    default:
        impossible("mcastu: invalid clerical spell (%d)", spellnum);
        dmg = 0;
        break;
    }

    if (dmg)
        mdamageu(mtmp, dmg);
}

RESTORE_WARNING_FORMAT_NONLITERAL

static boolean
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
        case CLC_CURE_SELF:
        case CLC_PROTECTION:
        case CLC_BLIGHT:
        case CLC_HOBBLE:
            return TRUE;
        default:
            break;
        }
    }
    return FALSE;
}

/* Some spells are useless under some circumstances. */
static boolean
spell_would_be_useless(struct monst *mtmp, unsigned int adtyp, int spellnum)
{
    /* Some spells don't require the player to really be there and can be cast
     * by the monster when you're invisible, yet still shouldn't be cast when
     * the monster doesn't even think you're there.
     * This check isn't quite right because it always uses your real position.
     * We really want something like "if the monster could see mux, muy".
     */
    boolean mcouldseeu = couldsee(mtmp->mx, mtmp->my);

    if (adtyp == AD_SPEL) {
        /* aggravate monsters, etc. won't be cast by peaceful monsters */
        if (mtmp->mpeaceful
            && (spellnum == MGC_AGGRAVATION 
                || spellnum == MGC_SUMMON_MONS
                || spellnum == MGC_CALL_UNDEAD
                || spellnum == MGC_EVIL_EYE 
                || spellnum == MGC_CLONE_WIZ))
            return TRUE;
        /* haste self when already fast */
        if (mtmp->permspeed == MFAST && spellnum == MGC_HASTE_SELF)
            return TRUE;
        /* invisibility when already invisible */
        if ((mtmp->minvis || mtmp->invis_blkd) && spellnum == MGC_DISAPPEAR)
            return TRUE;
        if ((has_reflection(mtmp) || mon_reflects(mtmp, (char *) 0))
            && spellnum == MGC_REFLECTION)
            return TRUE;
        /* peaceful monster won't cast invisibility. This doesn't
           really make a lot of sense, but lets the player avoid hitting
           peaceful monsters by mistake */
        if (mtmp->mpeaceful && spellnum == MGC_DISAPPEAR)
            return TRUE;
        /* healing when already healed */
        if (mtmp->mhp == mtmp->mhpmax && spellnum == MGC_CURE_SELF)
            return TRUE;
        /* don't summon monsters if it doesn't think you're around */
        if (!mcouldseeu && (spellnum == MGC_SUMMON_MONS
                            || spellnum == MGC_CALL_UNDEAD
                            || (!mtmp->iswiz && spellnum == MGC_CLONE_WIZ)))
            return TRUE;
        /* only undead and demons can cast evil eye/call undead */
        if (spellnum == MGC_EVIL_EYE || spellnum == MGC_CALL_UNDEAD) {
            if (!is_undead(mtmp->data) && !is_demon(mtmp->data))
                return TRUE;
        }
        if ((!mtmp->iswiz || gc.context.no_of_wizards > 1)
            && spellnum == MGC_CLONE_WIZ)
            return TRUE;
        /* aggravation (global wakeup) when everyone is already active */
        if (spellnum == MGC_AGGRAVATION) {
            /* if nothing needs to be awakened then this spell is useless
               but caster might not realize that [chance to pick it then
               must be very small otherwise caller's many retry attempts
               will eventually end up picking it too often] */
            if (!has_aggravatables(mtmp))
                return rn2(100) ? TRUE : FALSE;
        }
        if ((m_seenres(mtmp, M_SEEN_FIRE))
            && spellnum == MGC_FIRE_BOLT) {
            return TRUE;
        }
        if ((m_seenres(mtmp, M_SEEN_COLD))
            && spellnum == MGC_ICE_BOLT) {
            return TRUE;
        }
        if ((m_seenres(mtmp, M_SEEN_ACID))
            && spellnum == MGC_ACID_BLAST) {
            return TRUE;
        }
        if ((spellnum == MGC_ICE_BOLT || spellnum == MGC_FIRE_BOLT
             || spellnum == MGC_ACID_BLAST) 
            && (mtmp->mpeaceful || u.uinvulnerable)) {
            return TRUE;
        }
        /* don't entomb if hero is already entombed */
        if (spellnum == MGC_ENTOMB && is_entombed(u.ux, u.uy))
            return TRUE;
        /* only entomb as a desperation measure */
        if (spellnum == MGC_ENTOMB && mtmp->mhp > (mtmp->mhpmax / 5)
            && !mtmp->mflee)
            return TRUE;
    } else if (adtyp == AD_CLRC) {
        /* summon insects/sticks to snakes won't be cast by peaceful monsters
         */
        if (mtmp->mpeaceful && (spellnum == CLC_INSECTS 
                                || spellnum == CLC_HOBBLE
                                || spellnum == CLC_BLIGHT))
            return TRUE;
        /* healing when already healed */
        if (mtmp->mhp == mtmp->mhpmax && spellnum == CLC_CURE_SELF)
            return TRUE;
        /* don't summon insects if it doesn't think you're around */
        if (!mcouldseeu && (spellnum == CLC_INSECTS
                            || spellnum == CLC_HOBBLE
                            || spellnum == CLC_BLIGHT))
            return TRUE;
        /* blindness spell on blinded player */
        if (Blinded && spellnum == CLC_BLIND_YOU)
            return TRUE;
    }
    return FALSE;
}

/* monster uses spell (ranged) */
int
buzzmu(struct monst *mtmp, struct attack *mattk)
{
    /* don't print constant stream of curse messages for 'normal'
       spellcasting monsters at range */
    if (!BZ_VALID_ADTYP(mattk->adtyp))
        return M_ATTK_MISS;

    if (mtmp->mcan || m_seenres(mtmp, cvt_adtyp_to_mseenres(mattk->adtyp))) {
        cursetxt(mtmp, FALSE);
        return M_ATTK_MISS;
    }
    if (lined_up(mtmp) && rn2(3)) {
        nomul(0);
        if (canseemon(mtmp))
            pline("%s zaps you with a %s!", Monnam(mtmp),
                  flash_str(BZ_OFS_AD(mattk->adtyp), FALSE));
        gb.buzzer = mtmp;
        buzz(BZ_M_SPELL(BZ_OFS_AD(mattk->adtyp)), (int) mattk->damn,
             mtmp->mx, mtmp->my, sgn(gt.tbx), sgn(gt.tby));
        gb.buzzer = 0;
        return M_ATTK_HIT;
    }
    return M_ATTK_MISS;
}

/* is (x,y) entombed (completely surrounded by boulders or nonwalkable spaces)?
 * note that (x,y) itself is not checked */
static boolean
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

static boolean
counterspell(struct monst *mtmp, struct obj *otmp) {
    if (otmp->cursed)
        return FALSE;

    pline("%s shines and %s %s magic!", artiname(uwep->oartifact),
          !rn2(2) ? "absorbs" : "cancels", s_suffix(mon_nam(mtmp)));

    if (canseemon(mtmp)) {
        pline("%s %s!", Monnam(mtmp),
              rn2(2) ? "sputters" : rn2(2) ? "swears" : "curses");
    } else {
        You_hear("some cursing!");
    }
    return TRUE;
}

/*mcastu.c*/
