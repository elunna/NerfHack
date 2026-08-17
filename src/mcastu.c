/* NetHack 3.7	mcastu.c	$NHDT-Date: 1726168598 2024/09/12 19:16:38 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.105 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2011. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"
#include <math.h>

#define MCASTU_ENUM
enum mcast_spells {
#include "mcastu.h"
};
#undef MCASTU_ENUM

struct _mcast_data {
    const char *name;
    int level;
    int flags;
};

#define MCASTU_INIT
static struct _mcast_data mcast_data[] = {
#include "mcastu.h"
};
#undef MCASTU_INIT

/* spell lists for specific monster casters */
/* the spells in the list should be in ascending level order */
static int mon_wizard_spells[] = {
    MCAST_PSI_BOLT,         /* lev 0 */
    MCAST_ICE_BOLT,         /* lev 0 */
    MCAST_FIRE_BOLT,        /* lev 0 */
    MCAST_CURE_SELF,        /* lev 1 */
    MCAST_HASTE_SELF,       /* lev 2 */
    MCAST_STUN,             /* lev 3 */
    MCAST_VULN,             /* lev 4 */
    MCAST_DISAPPEAR,        /* lev 4 */
    MCAST_WEAKEN,           /* lev 6 */
    MCAST_MIRROR_IMAGE,     /* lev 8 */
    MCAST_DESTRY_ARMR,      /* lev 8 */
    MCAST_REFLECTION,       /* lev 10 */
    MCAST_CURSE_ITEMS,      /* lev 10 */
    MCAST_SUMMON_MINION,    /* lev 12 */
    MCAST_MAKE_POOL,        /* lev 13 */
    MCAST_AGGRAVATION,      /* lev 13 */
    MCAST_ACID_BLAST,       /* lev 14 */
    MCAST_SUMMON_MONS,      /* lev 15 */
    MCAST_CLONE_WIZ,        /* lev 18 */
    MCAST_DEATH_TOUCH       /* lev 20 */
};
static int mon_shadow_mage_spells[] = {
    /* similar to mon_wizard_spells: no cure_self */
    MCAST_PSI_BOLT,         /* lev 0 */
    MCAST_DARKNESS,         /* lev 1 */
    MCAST_HASTE_SELF,       /* lev 2 */
    MCAST_SLEEP,            /* lev 3 */
    MCAST_STUN,             /* lev 3 */
    MCAST_DISAPPEAR,        /* lev 4 */
    MCAST_WEAKEN,           /* lev 6 */
    MCAST_MIRROR_IMAGE,     /* lev 8 */
    MCAST_DESTRY_ARMR,      /* lev 8 */
    MCAST_CURSE_ITEMS,      /* lev 10 */
    MCAST_SUMMON_MINION,    /* lev 12 */
    MCAST_SUMMON_MONS,      /* lev 15 */
    MCAST_DEATH_TOUCH       /* lev 20 */
};
static int mon_vamp_spells[] = {
    MCAST_OPEN_WOUNDS,      /* lev 0 */
    MCAST_CURE_SELF,        /* lev 1 */
    MCAST_BLOOD_RAIN,       /* lev 1 */
    MCAST_PARALYZE,         /* lev 4 */
    // MCAST_BLOODRUSH,
    MCAST_DISAPPEAR,        /* lev 4 */
    MCAST_BETRAY,       /* lev 5 */
    MCAST_EVIL_EYE,         /* lev 7 */
    MCAST_BLOOD_SPEAR,      /* lev 8 */
    MCAST_CURSE_ITEMS,      /* lev 10 */
    MCAST_BLOOD_BIND,       /* lev 14 */
    MCAST_TELEPORT,         /* lev 15 */
};
static int mon_cleric_spells[] = {
    MCAST_OPEN_WOUNDS,      /* lev 0 */
    MCAST_CURE_SELF,        /* lev 1 */
    MCAST_PROTECTION,       /* lev 2 */
    MCAST_CONFUSE,          /* lev 2 */
    MCAST_PARALYZE,         /* lev 4 */
    MCAST_BLIND,            /* lev 6 */
    MCAST_BLIGHT,           /* lev 6 */
    MCAST_INSECTS,          /* lev 8 */
    MCAST_HOBBLE,           /* lev 9 */
    MCAST_CURSE_ITEMS,      /* lev 10 */
    MCAST_DISENCHANT,       /* lev 10 */
    MCAST_LIGHTNING,        /* lev 11 */
    MCAST_FIRE_PILLAR,      /* lev 12 */
    MCAST_GEYSER,           /* lev 13 */
    MCAST_FLESH_TO_STONE    /* lev 16 */
};
static int mon_undead_spells[] = {
    MCAST_HASTE_SELF,       /* lev 2 */
    MCAST_STUN,             /* lev 3 */
    MCAST_SLEEP,            /* lev 3 */
    MCAST_DISAPPEAR,        /* lev 4 */
    MCAST_WEAKEN,           /* lev 6 */
    MCAST_EVIL_EYE,         /* lev 7 */
    MCAST_MIRROR_IMAGE,     /* lev 8 */
    MCAST_CURSE_ITEMS,      /* lev 10 */
    MCAST_CALL_UNDEAD,      /* lev 10 */
    MCAST_SUMMON_MINION,    /* lev 12 */
    MCAST_ENTOMB,           /* lev 12 */
    MCAST_AGGRAVATION,      /* lev 13 */
    MCAST_DEATH_TOUCH       /* lev 20 */
};
static int mon_trickster_spells[] = {
    MCAST_PSI_BOLT,         /* lev 0 */
    MCAST_GREASE,           /* lev 1 */
    MCAST_CONFUSE,          /* lev 2 */
    MCAST_HASTE_SELF,       /* lev 2 */
    MCAST_STUN,             /* lev 3 */
    MCAST_VULN,             /* lev 4 */
    MCAST_DISGUISE,         /* lev 4 */
    MCAST_LEVITATE,         /* lev 4 */
    MCAST_BETRAY,           /* lev 5 */
    MCAST_HOBBLE,           /* lev 9 */
    MCAST_CURSE_ITEMS,      /* lev 10 */
    MCAST_DISENCHANT,       /* lev 10 */
    MCAST_MAKE_POOL,        /* lev 13 */
    MCAST_AGGRAVATION,      /* lev 13 */
    MCAST_SUMMON_MONS,      /* lev 15 */
    MCAST_TELEPORT          /* lev 15 */

};
static int mon_arch_vile_spells[] = {
    MCAST_OPEN_WOUNDS,      /* lev 0 */
    MCAST_CURE_SELF,        /* lev 1 */
    MCAST_PROTECTION,       /* lev 2 */
    MCAST_HASTE_SELF,       /* lev 2 */
    MCAST_REFLECTION,       /* lev 10 */
    MCAST_FIRE_PILLAR,      /* lev 12 */
};
static int mon_blight_sprite_spells[] = {
    MCAST_CURE_SELF,        /* lev 1 */
    MCAST_BLIGHT,           /* lev 6 */
    MCAST_CURSE_ITEMS,      /* lev 10 */
};

static int mon_orb_weaver_spells[] = {
    MCAST_SPHERES,          /* lev 0 */
    MCAST_CURE_SELF,        /* lev 1 */
    MCAST_PROTECTION,       /* lev 2 */
    MCAST_VULN,             /* lev 4 */
    MCAST_REFLECTION,       /* lev 10 */
};

static int mon_bone_naga_spells[] = {
    MCAST_ICE_BOLT,         /* lev 0 */
    MCAST_WEAKEN,           /* lev 6 */
    MCAST_BLIND,            /* lev 6 */
    MCAST_REFLECTION,       /* lev 10 */
    MCAST_LIGHTNING,        /* lev 11 */
    MCAST_TELEPORT          /* lev 15 */
};

DISABLE_WARNING_FORMAT_NONLITERAL

staticfn void cursetxt(struct monst *, boolean);
staticfn int choose_monster_spell(struct monst *, int);

staticfn int mcast_spell(struct monst *, struct monst *, int, int);
staticfn boolean is_undirected_spell(int);
staticfn boolean spell_would_be_useless(struct monst *, int);
staticfn boolean mspell_would_be_useless(struct monst *, struct monst *, int);
staticfn boolean counterspell(struct monst *);
staticfn int calculate_damage(int, int);

staticfn int mcast_psi_bolt(struct monst *, struct monst *, int);  /* lev 0 */
staticfn int mcast_fire_bolt(struct monst *, struct monst *, int); /* lev 0 */
staticfn int mcast_ice_bolt(struct monst *, struct monst *, int);  /* lev 0 */
staticfn int mcast_open_wounds(struct monst *, struct monst *);    /* lev 0 */
staticfn int mcast_spheres(struct monst *, struct monst *);        /* lev 0 */
staticfn int rnd_sphere(void);
staticfn int mcast_cure_self(struct monst *);                      /* lev 1 */
staticfn int mcast_darkness(struct monst *, struct monst *);       /* lev 1 */
staticfn int mcast_greasemon(struct monst *, struct monst *);      /* lev 1 */
staticfn int mcast_blood_rain(struct monst *, struct monst *);     /* lev 1 */
staticfn int mcast_haste_self(struct monst *);                     /* lev 2 */
// bloodrush                                                       /* lev 2 */
staticfn int mcast_confuse_mon(struct monst *, struct monst *);    /* lev 2 */
staticfn int mcast_protection(struct monst *);                     /* lev 2 */
staticfn int mcast_stun_mon(struct monst *, struct monst *);       /* lev 3 */
staticfn int mcast_sleep_mon(struct monst *, struct monst *);      /* lev 3 */
staticfn int mcast_disappear(struct monst *);                      /* lev 4 */
staticfn int mcast_paralyze(struct monst *, struct monst *);       /* lev 4 */
staticfn int mcast_vuln_mon(struct monst *, struct monst *);       /* lev 4 */
staticfn int mcast_disguise(struct monst *, struct monst *);       /* lev 5 */
staticfn int mcast_betray(struct monst *, struct monst *);     /* lev 5 */
staticfn struct monst * find_adjacent_pet(struct monst *);
staticfn int mcast_blind_mon(struct monst *, struct monst *);      /* lev 6 */
staticfn int mcast_weaken_mon(struct monst *, struct monst *, int);/* lev 6 */
staticfn int mcast_evil_eye(struct monst *, struct monst *);       /* lev 7 */
// int mcast_destroy_armor(struct monst *, struct monst *);        /* lev 8 */
staticfn int mcast_mirror_image(struct monst *);                   /* lev 8 */
staticfn int spawn_mirror_image(struct monst *, coordxy, coordxy);
staticfn int mcast_blood_spear(struct monst *, struct monst *);    /* lev 8 */
staticfn int mcast_insects(struct monst *, struct monst *);        /* lev 8 */
staticfn int mcast_hobble(struct monst *, struct monst *, int);    /* lev 9 */
staticfn int mcast_levitate(struct monst *, struct monst *);       /* lev 10 */
staticfn int mcast_curse_items(struct monst *, struct monst *);   /* lev 10 */
staticfn int mcast_reflection(struct monst *);                    /* lev 10 */
// Force field                                                    /* lev 10 */
staticfn int mcast_call_undead(struct monst *, struct monst *);   /* lev 10 */
staticfn int mcast_blight(struct monst *, struct monst *);        /* lev 10 */
staticfn int mcast_disenchant(struct monst *, struct monst *);    /* lev 10 */
staticfn int mcast_lightning(struct monst *, struct monst *);     /* lev 11 */
staticfn int mcast_fire_pillar(struct monst *, struct monst *);   /* lev 12 */
staticfn int mcast_summon_minion(struct monst *, struct monst *); /* lev 12 */
staticfn int mcast_entomb(struct monst *, struct monst *);        /* lev 12 */
staticfn boolean is_entombed(coordxy, coordxy);
staticfn int mcast_geyser(struct monst *, struct monst *);        /* lev 13 */
staticfn int mcast_aggravation(struct monst *, struct monst *);   /* lev 13 */
staticfn int mcast_acid_blast(struct monst *, struct monst *);    /* lev 14 */
staticfn int mcast_teleport(struct monst *, struct monst *);      /* lev 15 */
staticfn int mcast_summon_mons(struct monst *, struct monst *);   /* lev 15 */
staticfn int mcast_flesh_to_stone(struct monst *, struct monst *);/* lev 16 */
staticfn int mcast_make_pool(struct monst *, struct monst *);     /* lev 16 */
staticfn int mcast_clone_wiz(struct monst *, struct monst *);     /* lev 18 */
staticfn int mcast_blood_bind(struct monst *, struct monst *);    /* lev 20 */
staticfn int mcast_death_touch(struct monst *, struct monst *);   /* lev 20 */

/* Magic melee spells */
staticfn int mgc_melee_ad_fire(struct monst *, struct monst *, int);
staticfn int mgc_melee_ad_cold(struct monst *, struct monst *, int);
staticfn int mgc_melee_ad_elec(struct monst *, struct monst *, int);
staticfn int mgc_melee_ad_magm(struct monst *, struct monst *, int);
staticfn int mgc_melee_ad_acid(struct monst *, struct monst *, int);

const char* vulntext[] = {
    "chartreuse polka-dot",
    "reddish-orange",
    "purplish-blue",
    "coppery-yellow",
    "greenish-mottled",
    "silvery-velvety"
};

/* feedback when frustrated monster couldn't cast a spell */
staticfn void
cursetxt(struct monst *caster, boolean undirected)
{
    /* Prevent curse spam if 10+ squares away */
    if (distu(caster->mx, caster->my) > 81)
        return;
    if (canseemon(caster) && couldsee(caster->mx, caster->my)) {
        const char *pointer_msg; /* how do they point? */
        const char *point_msg; /* spellcasting monsters are impolite */

        if (nohands(caster->data)) {
            if (haseyes(caster->data)) {
                pointer_msg = "looks";
            } else {
                pointer_msg = "wiggles";
            }
        } else {
            pointer_msg = "points";
        }

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

        pline_mon(caster, "%s %s %s.", Monnam(caster), pointer_msg, point_msg);
    } else if ((!(svm.moves % 4) || !rn2(4))) {
        if (!Deaf)
            Norep("You hear a mumbled curse.");   /* Deaf-aware */
    }
}

/* convert a level-based random selection into a specific monster spell;
   inappropriate choices will be screened out by spell_would_be_useless() */
staticfn int
choose_monster_spell(struct monst *caster, int adtyp)
{
    int *list = NULL;
    int i, len = 0;
    int maxlev;
    int a;

    a = mon_aligntyp(caster);
    /* Randomly determine the alignment of unaligned casters. */
    if (a == A_NONE)
        a = aligns[(caster->m_id % 3)].value;

    /* Low HP, prioritize healing */
    if ((caster->mhp * 7) <= caster->mhpmax) {
        if ((!rn2(10) || caster->mflee) && caster->m_lev > 8)
            return MCAST_ENTOMB;
        return MCAST_CURE_SELF;
    }

    /* which spell list to use? */

    /* Specific monsters first */
    if (caster->data == &mons[PM_ORB_WEAVER]) {
        list = mon_orb_weaver_spells;
        len = SIZE(mon_orb_weaver_spells);
    } else if (caster->data == &mons[PM_BLIGHT_SPRITE]) {
        list = mon_blight_sprite_spells;
        len = SIZE(mon_blight_sprite_spells);
    } else if (caster->data == &mons[PM_BONE_NAGA]) {
        list = mon_bone_naga_spells;
        len = SIZE(mon_bone_naga_spells);
    } else if (caster->data == &mons[PM_DARK_ONE]) {
        list = mon_shadow_mage_spells;
        len = SIZE(mon_shadow_mage_spells);
    /* List archie before undead so it isn't caught as undead */
    } else if (caster->data == &mons[PM_ARCH_VILE]) {
        list = mon_arch_vile_spells;
        len = SIZE(mon_arch_vile_spells);

    /* More general categories */
    } else if (caster->data->mlet == S_VAMPIRE
            || caster->data == &mons[PM_BLOOD_IMP]) {
        list = mon_vamp_spells;
        len = SIZE(mon_vamp_spells);
    } else if (is_undead(caster->data)
            || caster->data == &mons[PM_ORCUS]) {
        list = mon_undead_spells;
        len = SIZE(mon_undead_spells);
    } else if (caster->data->mlet == S_GNOME
            || caster->data->mlet == S_KOBOLD
            || caster->data == &mons[PM_DISPATER]) {
        list = mon_trickster_spells;
        len = SIZE(mon_trickster_spells);
    } else if (adtyp == AD_CLRC) {
        list = mon_cleric_spells;
        len = SIZE(mon_cleric_spells);
    } else {
        list = mon_wizard_spells;
        len = SIZE(mon_wizard_spells);
    }
    if (!list || len < 1)
        return MCAST_PSI_BOLT;

    /* max level spell possible to cast */
    maxlev = caster->m_lev;

    /* randomly determine the spell. we can't do it the vanilla way because
       many monsters have multiple spells of the same level now. */
    for (i = 0; i < len; i++) {
        if (mcast_data[list[i]].level > maxlev) {
            break;
        }
    }
    if (i > 1) {
        return list[rn2(i)];
    }
    /* or return the first spell in the list */
    return list[0];
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
    boolean allow_misfire;

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
            spellnum = choose_monster_spell(caster, mattk->adtyp);
            /* not trying to attack?  don't allow directed spells */
            if (!thinks_it_foundyou) {
                if (!is_undirected_spell(spellnum)
                    || spell_would_be_useless(caster, spellnum)) {
                    if (foundyou)
                        impossible(
                       "spellcasting monster found you and doesn't know it?");
                    return M_ATTK_MISS;
                }
                break;
            }
        } while (--cnt > 0
                 && spell_would_be_useless(caster, spellnum));
        if (cnt == 0)
            return M_ATTK_MISS;
    }
    allow_misfire = (boolean) ((mcast_data[spellnum].flags & MCF_MISFIRE) != 0);

    /* monster unable to cast spells? */
    if (caster->mcan || caster->mspec_used || !ml
        || m_seenres(caster, cvt_adtyp_to_mseenres(mattk->adtyp))) {
        cursetxt(caster, is_undirected_spell(spellnum));
        return M_ATTK_MISS;
    }

    debugpline3("castmu:%s,lvl:%i,spell:%i", noit_Monnam(caster), ml, spellnum);

    if (mattk->adtyp == AD_SPEL || mattk->adtyp == AD_CLRC) {
        /* monst->m_lev is unsigned (uchar), monst->mspec_used is int */
        caster->mspec_used = (int) ((caster->m_lev < 8) ? (10 - caster->m_lev) : 2);

        /* mspec 0 two thirds of the time */
        if ((rn2(3) && power_caster(caster->data))
            || is_dprince(caster->data) || caster->iswiz)
            /* mspec 0 always */
            caster->mspec_used = 0;
    }

    /* Telepathic spellcasters don't have much reason to miss.
       They have a chance to be wrong in mon_really_found_us */
    if (telepathic(caster->data)
            || (mattk->adtyp == AD_SPEL && spellnum == MCAST_TELEPORT))
        foundyou = thinks_it_foundyou = 1;

    /* Check for protection from invisibility, displacement,
       or cover of darkness */
    if (!mon_really_found_us(caster)) {
        foundyou = 0;
        /* Let some spells be blocked; but always let the blasts through. */
        if (allow_misfire)
            thinks_it_foundyou = 0;
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
    if (!foundyou && thinks_it_foundyou && !allow_misfire) {
        pline_mon(caster, "%s casts %s at %s!",
                 canseemon(caster) ? Monnam(caster) : "Something",
                 ((Role_if(PM_WIZARD) && mattk->adtyp == AD_SPEL)
                    || (Role_if(PM_CLERIC) && mattk->adtyp == AD_CLRC))
                        ? mcast_data[spellnum].name : "a spell",
                 is_waterwall(caster->mux, caster->muy) ? "empty water"
                                                    : "thin air");
        return M_ATTK_MISS;
    }

    if (rn2(ml * 10) < (caster->mconf ? 100 : 20)) { /* fumbled attack */
        Soundeffect(se_air_crackles, 60);
        if (canseemon(caster) && !Deaf) {
            set_msg_xy(caster->mx, caster->my);
            pline_The("air crackles around %s.", mon_nam(caster));
        }
        return M_ATTK_MISS;
    }

    if (canspotmon(caster) || !is_undirected_spell(spellnum)) {
        pline_mon(caster, "%s casts %s%s!",
                 canspotmon(caster) ? Monnam(caster) : "Something",
                 ((Role_if(PM_WIZARD) && mattk->adtyp == AD_SPEL)
                   || (Role_if(PM_CLERIC) && mattk->adtyp == AD_CLRC))
                       ? mcast_data[spellnum].name : "a spell",
                 is_undirected_spell(spellnum) ? ""
                 : (Invis && !mon_prop(caster, SEE_INVIS)
                    && !u_at(caster->mux, caster->muy))
                   ? " at a spot near you"
                   : (Displaced && !u_at(caster->mux, caster->muy))
                     ? " at your displaced image"
                     : " at you");
        nomul(0);
    }

    if (Spell_blocking && counterspell(caster)) {
        return M_ATTK_MISS;
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
        dmg -= (dmg + 1) / 4;

    ret = M_ATTK_HIT;

    switch (mattk->adtyp) {
    case AD_FIRE:
        dmg = mgc_melee_ad_fire(caster, &gy.youmonst, dmg);
        break;
    case AD_COLD:
        dmg = mgc_melee_ad_cold(caster, &gy.youmonst, dmg);
        break;
    case AD_ELEC:
        dmg = mgc_melee_ad_elec(caster, &gy.youmonst, dmg);
        break;
    case AD_MAGM:
        dmg = mgc_melee_ad_magm(caster, &gy.youmonst, dmg);
        break;
    case AD_SPEL: /* wizard spell */
    case AD_CLRC: /* clerical spell */
        dmg = mcast_spell(caster, &gy.youmonst, dmg, spellnum);
        break;
    default:
        impossible("castmu: adtype %d not handled.", mattk->adtyp);
    } /* switch */

    if (dmg)
        mdamageu(caster, dmg);
    if (DEADMONSTER(caster))
        ret |= M_ATTK_AGR_DIED;
    return ret;
}

/*
   If dmg is zero, then the monster is not casting at you.
   If the monster is intentionally not casting at you, we have previously
   called spell_would_be_useless() and spellnum should always be a valid
   undirected spell.
   If you modify either of these, be sure to change is_undirected_spell()
   and spell_would_be_useless().
 */
staticfn int
mcast_spell(
    struct monst *caster,
    struct monst *mdef,
    int dmg,
    int spellnum)
{
    if (dmg < 0) {
        impossible("monster cast spell (%d-%s) with negative dmg (%d)?",
                   spellnum, mcast_data[spellnum].name, dmg);
        return 0;
    }
    if (dmg == 0 && !is_undirected_spell(spellnum)) {
        impossible("cast directed spell (%d-%s) with dmg=0?",
            spellnum, mcast_data[spellnum].name);
        return 0;
    }

#if 0
    if (caster == mdef)
        impossible("cast_wizard_spell (%d-%s): caster/mdef are same monster.",
            spellnum, mcast_data[spellnum].name);
#endif

    switch (spellnum) {
    case MCAST_PSI_BOLT:
        dmg = mcast_psi_bolt(caster, mdef, dmg);
        break;
    case MCAST_FIRE_BOLT:
        dmg = mcast_fire_bolt(caster, mdef, dmg);
        break;
    case MCAST_ICE_BOLT:
        dmg = mcast_ice_bolt(caster, mdef, dmg);
        break;
    case MCAST_OPEN_WOUNDS:
        dmg = mcast_open_wounds(caster, mdef);
        break;
    case MCAST_SPHERES:
        dmg = mcast_spheres(caster, mdef);
        break;
    case MCAST_CURE_SELF:
        dmg = mcast_cure_self(caster);
        break;
    case MCAST_DARKNESS:
        dmg = mcast_darkness(caster, mdef);
        break;
    case MCAST_GREASE:
        dmg = mcast_greasemon(caster, mdef);
        break;
    case MCAST_BLOOD_RAIN:
        dmg = mcast_blood_rain(caster, mdef);
        break;
    case MCAST_HASTE_SELF:
        dmg = mcast_haste_self(caster);
        break;
    case MCAST_CONFUSE:
        dmg = mcast_confuse_mon(caster, mdef);
        break;
    case MCAST_PROTECTION:
        dmg = mcast_protection(caster);
        break;
    case MCAST_STUN:
        dmg = mcast_stun_mon(caster, mdef);
        break;
    case MCAST_SLEEP:
        dmg = mcast_sleep_mon(caster, mdef);
        break;
    case MCAST_DISAPPEAR:
        dmg = mcast_disappear(caster);
        break;
    case MCAST_PARALYZE:
        dmg = mcast_paralyze(caster, mdef);
        break;
    case MCAST_VULN:
        dmg = mcast_vuln_mon(caster, mdef);
        break;
    case MCAST_DISGUISE:
        dmg = mcast_disguise(caster, mdef);
        break;
    case MCAST_BETRAY:
        dmg = mcast_betray(caster, mdef);
        break;
    case MCAST_BLIND:
        dmg = mcast_blind_mon(caster, mdef);
        break;
    case MCAST_WEAKEN:
        dmg = mcast_weaken_mon(caster, mdef, dmg);
        break;
    case MCAST_EVIL_EYE:
        dmg = mcast_evil_eye(caster, mdef);
        break;
    case MCAST_DESTRY_ARMR:
        dmg = mcast_destroy_armor(caster, mdef);
        break;
    case MCAST_MIRROR_IMAGE:
        dmg = mcast_mirror_image(caster);
        break;
    case MCAST_BLOOD_SPEAR:
        dmg = mcast_blood_spear(caster, mdef);
        break;
    case MCAST_INSECTS:
        dmg = mcast_insects(caster, mdef);
        break;
    case MCAST_HOBBLE:
        dmg = mcast_hobble(caster, mdef, dmg);
        break;
    case MCAST_LEVITATE:
        dmg = mcast_levitate(caster, mdef);
        break;
    case MCAST_CURSE_ITEMS:
        dmg = mcast_curse_items(caster, mdef);
        break;
    case MCAST_REFLECTION:
        dmg = mcast_reflection(caster);
        break;
    case MCAST_CALL_UNDEAD:
        dmg = mcast_call_undead(caster, mdef);
        break;
    case MCAST_BLIGHT:
        dmg = mcast_blight(caster, mdef);
        break;
    case MCAST_DISENCHANT:
        dmg = mcast_disenchant(caster, mdef);
        break;
    case MCAST_LIGHTNING:
        dmg = mcast_lightning(caster, mdef);
        break;
    case MCAST_FIRE_PILLAR:
        dmg = mcast_fire_pillar(caster, mdef);
        break;
    case MCAST_SUMMON_MINION:
        dmg = mcast_summon_minion(caster, mdef);
        break;
    case MCAST_ENTOMB:
        dmg = mcast_entomb(caster, mdef);
        break;
    case MCAST_GEYSER:
        dmg = mcast_geyser(caster, mdef);
        break;
    case MCAST_AGGRAVATION:
        dmg = mcast_aggravation(caster, mdef);
        break;
    case MCAST_ACID_BLAST:
        dmg = mcast_acid_blast(caster, mdef);
        break;
    case MCAST_TELEPORT:
        dmg = mcast_teleport(caster, mdef);
        break;
    case MCAST_SUMMON_MONS:
        dmg = mcast_summon_mons(caster, mdef);
        break;
    case MCAST_FLESH_TO_STONE:
        dmg = mcast_flesh_to_stone(caster, mdef);
        break;
    case MCAST_MAKE_POOL:
        dmg = mcast_make_pool(caster, mdef);
        break;
    case MCAST_CLONE_WIZ:
        dmg = mcast_clone_wiz(caster, mdef);
        break;
    case MCAST_BLOOD_BIND:
        dmg = mcast_blood_bind(caster, mdef);
        break;
    case MCAST_DEATH_TOUCH:
        dmg = mcast_death_touch(caster, mdef);
        break;

#if 0 /* Crecelle specific - covers mon with blood and speeds up */
    case MCAST_BLOODRUSH:
        if (canseemon(caster))
            pline_mon(caster, "%s is covered in blood.", Monnam(caster));

        levl[caster->mx][caster->my].splatpm = PM_HUMAN;
        // make_mdripping(caster, -1 * caster->mnum);
        FALLTHROUGH;
        /*FALLTHRU*/
#endif
#if 0 /* Crecelle Specific Spells */
    case MCAST_FORCE_FIELD:
        pline("A wall of force slams down around you!");
        create_force_field(u.ux, u.uy, 2, (long) rn1(5, 5));
        dmg = 0;
        break;
    case MCAST_GRAVITY: {
        int quan = rnd(2);
        coord bypos;
        pline_The("air quavers.");
        for (int i = 0; i < quan; i++) {
            if (!enexto(&bypos, caster->mx, caster->my, caster->data))
                break;
            makemon(&mons[PM_GRAVIMETRIC_SPHERE], bypos.x, bypos.y, MM_NOCOUNTBIRTH | MM_ANGRY);
        }
        dmg = 0;
        break;
    }
#endif
    }
    return dmg;
}

staticfn boolean
is_undirected_spell(int spellnum)
{
    if ((mcast_data[spellnum].flags & MCF_INDIRECT) != 0)
        return TRUE;
    return FALSE;
}

/* Some spells are useless under some circumstances. */
staticfn boolean
spell_would_be_useless(
    struct monst *caster,
    int spellnum)
{
    /* Some spells don't require the player to really be there and can be cast
     * by the monster when you're invisible, yet still shouldn't be cast when
     * the monster doesn't even think you're there.
     * This check isn't quite right because it always uses your real position.
     * We really want something like "if the monster could see mux, muy".
     */
    boolean mcouldseeu = m_canseeu(caster);
    boolean telepath_caster = mon_prop(caster, TELEPAT);

    struct trap *trap = t_at(caster->mx, caster->my);
    /* Anti-magic fields block spellcasting */
    if (trap && trap->ttyp == ANTI_MAGIC)
        return TRUE;

    /* spell is only cast by hostile monsters */
    if ((mcast_data[spellnum].flags & MCF_HOSTILE) != 0) {
        if (caster->mpeaceful && !Conflict)
            return TRUE;
    }

    /* spell needs the monster to see hero */
    if ((mcast_data[spellnum].flags & MCF_SIGHT) != 0) {
        if (!mcouldseeu && !telepath_caster)
            return TRUE;
    }
    if (!is_undirected_spell(spellnum)
        && distu(caster->mx, caster->my) > 2) {
        return TRUE;
    }

    switch (spellnum) {
    case MCAST_FIRE_BOLT:
        if ((m_seenres(caster, M_SEEN_FIRE) || Underwater)) {
            return TRUE;
        }
        break;
    case MCAST_ICE_BOLT:
        if (m_seenres(caster, M_SEEN_COLD)) {
            return TRUE;
        }
        break;
    case MCAST_CURE_SELF:
        /* healing when already healed */
        if (caster->mhp == caster->mhpmax
                && !caster->mdiseased
                && !caster->mwither
                && !caster->mblinded)
            return TRUE;
        break;
    case MCAST_DARKNESS:
        if (levl[caster->mx][caster->my].lit == 0) /* Already dark */
            return TRUE;
        break;
    case MCAST_GREASE:
        if (Glib || GreasedFeet || GreasedBoots) /* Already greased */
            return TRUE;
        break;
    case MCAST_BLOOD_RAIN:
        if (IS_BLOODY(caster->mux, caster->muy))
            return TRUE;
        break;
    case MCAST_HASTE_SELF:
        /* haste self when already fast */
        if (caster->permspeed == MFAST)
            return TRUE;
        break;
    case MCAST_CONFUSE:
        ; /* What if we are already confused? */
        break;
    case MCAST_STUN:
        ; /* What if we are already stunned? */
        if (m_seenres(caster, M_SEEN_STUN))
            return TRUE;
        break;
    case MCAST_SLEEP:
        if (m_seenres(caster, M_SEEN_SLEEP)) {
            return TRUE;
        }
        if (u.usleep) /* We are already sleeping */
            return TRUE;
        break;
    case MCAST_DISAPPEAR:
        /* invisibility when already invisible */
        if (caster->minvis || caster->invis_blkd)
            return TRUE;
        /* peaceful monster won't cast invisibility if you can't see
           invisible,
           same as when monsters drink potions of invisibility.  This doesn't
           really make a lot of sense, but lets the player avoid hitting
           peaceful monsters by mistake */
        if (caster->mpeaceful && !See_invisible)
            return TRUE;
        break;
    case MCAST_PARALYZE:
        if (Free_action) /* Maybe obvious that we have it (to intelligents)? */
            return TRUE;
        break;
    case MCAST_VULN:
        ; /* Any possible checks here? */
        break;
    case MCAST_DISGUISE:
        if (Protection_from_shape_changers) /* Prevents disguise */
            return TRUE;
        break;
    case MCAST_BLIND:
        if (Blinded) /* blindness spell on blinded player */
            return TRUE;
        break;
    case MCAST_BETRAY:
        /* Don't cast this if there are no valid tarets */
        if (!find_adjacent_pet(caster))
            return TRUE;
        break;
    case MCAST_EVIL_EYE:
        if (!is_undead(caster->data) && !is_demon(caster->data))
            return TRUE;
        if (Blind)
            return TRUE;
        break;
    case MCAST_DESTRY_ARMR:
        if (!count_worn_armor())
            return TRUE;
        break;
    case MCAST_MIRROR_IMAGE:
        /* Cannot disguise if protected */
        if (Protection_from_shape_changers)
            return TRUE;
        break;
    case MCAST_BLOOD_SPEAR:
    case MCAST_BLOOD_BIND:
        if (IS_BLOODY(caster->mux, caster->muy))
            return TRUE;
        break;
    case MCAST_HOBBLE:
        if (Wounded_legs)
            return TRUE;
        break;
    case MCAST_LEVITATE:
        if (Levitation || Flying || Punished)
            return TRUE;
        break;
    case MCAST_REFLECTION:
        if (has_reflection(caster) || mon_reflectsrc(caster))
            return TRUE;
        break;
    case MCAST_CALL_UNDEAD:
        /* only undead and demons can cast evil eye/call undead */
        if (!is_undead(caster->data) && !is_demon(caster->data))
            return TRUE;
        /* Erinys + Call Undead doesn't make sense */
        if (caster->data == &mons[PM_ERINYS]) {
            return TRUE;
        }
        break;
    case MCAST_BLIGHT:
        if (m_seenres(caster, M_SEEN_DISINT))
            return TRUE;
        if (nonliving(gy.youmonst.data))
            return TRUE;
        break;
    case MCAST_LIGHTNING:
        /* lightning vs shock res */
        if (m_seenres(caster, M_SEEN_ELEC))
            return TRUE;
        break;
    case MCAST_FIRE_PILLAR:
        /* Only arch-viles can cast fire pillar at range. */
        if (caster->data != &mons[PM_ARCH_VILE]
            && distu(caster->mx, caster->my) > 2)
            return TRUE;
        if ((m_seenres(caster, M_SEEN_FIRE) || Underwater)) {
            return TRUE;
        }
        break;
    case MCAST_ENTOMB:
        /* don't entomb if hero is already entombed */
        if (is_entombed(u.ux, u.uy))
            return TRUE;
        /* only entomb as a desperation measure */
        if (caster->mhp > (caster->mhpmax / 5 || caster->mflee))
            return TRUE;
        break;
    case MCAST_AGGRAVATION:
        /* aggravation (global wakeup) when everyone is already active */
        /* if nothing needs to be awakened then this spell is useless
           but caster might not realize that [chance to pick it then
           must be very small otherwise caller's many retry attempts
           will eventually end up picking it too often] */
        if (!has_aggravatables(caster) && !Aggravate_monster)
            return rn2(100) ? TRUE : FALSE;
        break;
    case MCAST_ACID_BLAST:
        /* acid vs acid res */
        if (m_seenres(caster, M_SEEN_ACID)) {
            return TRUE;
        }
        break;
    case MCAST_TELEPORT:
        /* don't teleport is covetous; they already do that. */
        if (is_covetous(caster->data))
            return TRUE;
        /* Don't break the no-teleport rules on a level */
        if (noteleport_level(caster))
            return TRUE;
        break;
    case MCAST_FLESH_TO_STONE:
        /* Don't try to stone us if we are stoning resistant or already stoned */
        if (Stone_resistance || Stoned) {
            return TRUE;
        }
        break;
    case MCAST_MAKE_POOL:
        /* pools can only be created in certain locations */
        if (levl[u.ux][u.uy].typ != ROOM && levl[u.ux][u.uy].typ != CORR)
            return TRUE;
        /* Monsters won't cast at you if you are flying or levitating.
         * Waterwalking isn't obvious so we don't check that. */
        if (Flying || Levitation)
            return TRUE;
        /* and then only rarely unless you're carrying the amulet. */
        if (!u.uhave.amulet && rn2(20))
            return TRUE;
        break;
    case MCAST_CLONE_WIZ:
        /* only the Wizard is allowed to clone himself */
        if (!caster->iswiz)
            return TRUE;
        /* and don't allow double trouble when there are already 2 wizards in play */
        if (svc.context.no_of_wizards > 1)
            return TRUE;
        break;
    case MCAST_DEATH_TOUCH:
        if ((Antimagic || Hallucination) && !rn2(2))
            return TRUE;
        break;

#if 0
    case MCAST_BLOODRUSH:
#endif

#if 0
    case MCAST_FORCE_FIELD:
        if ((distu(caster->mx, caster->my) <= 4)
            || (((ff = visible_region_at(u.ux, u.uy)) != 0)
            && ff->glyph == S_force_field))
            return TRUE;
        break;
#endif
    default:
        break;
    }
    return FALSE;
}

staticfn boolean
mspell_would_be_useless(
    struct monst *caster,
    struct monst *mdef,
    int spellnum)
{
    struct trap *trap = t_at(caster->mx, caster->my);
    /* Anti-magic fields block spellcasting */
    if (trap && trap->ttyp == ANTI_MAGIC)
        return TRUE;

    /* spell is only cast by hostile monsters */
    if ((mcast_data[spellnum].flags & MCF_HOSTILE) != 0) {
        if (caster->mpeaceful && !Conflict)
            return TRUE;
    }

    /* spell is only cast at the player, castmm doesn't apply */
    if ((mcast_data[spellnum].flags & MCF_VS_HERO) != 0) {
        return TRUE;
    }

    /* spell needs the monster to see target */
    if ((mcast_data[spellnum].flags & MCF_SIGHT) != 0) {
        if (!caster->mcansee)
            return TRUE;
    }
    if (!is_undirected_spell(spellnum)
        && dist2(caster->mx, caster->my, mdef->mx, mdef->my) > 2) {
        return TRUE;
    }

    switch (spellnum) {
    case MCAST_FIRE_BOLT:
        /* Don't blast itself with its own explosions */
        if (!(resists_fire(caster) || defended(caster, AD_FIRE))
            && distmin(caster->mx, caster->my, mdef->mx, mdef->my) < 3 && rn2(5))
            return TRUE;
        /* prevent peacefuls from blasting player */
        if (caster->mpeaceful && distu(mdef->mx, mdef->my) < 3)
            return TRUE;
        break;
    case MCAST_ICE_BOLT:
        /* Don't blast itself with its own explosions */
        if (!(resists_cold(caster) || defended(caster, AD_COLD))
            && distmin(caster->mx, caster->my, mdef->mx, mdef->my) < 3 && rn2(5))
            return TRUE;
        /* prevent peacefuls from blasting player */
        if (caster->mpeaceful && distu(mdef->mx, mdef->my) < 3)
            return TRUE;
        break;
    case MCAST_CURE_SELF:
        /* healing when already healed */
        if (caster->mhp == caster->mhpmax
                && !caster->mdiseased
                && !caster->mwither
                && !caster->mblinded)
            return TRUE;
        break;
    case MCAST_HASTE_SELF:
        /* haste self when already fast */
        if (caster->permspeed == MFAST)
            return TRUE;
        break;
    case MCAST_DISAPPEAR:
        /* invisibility when already invisible */
        if ((caster->minvis || caster->invis_blkd))
            return TRUE;
        /* don't let peacefuls disappear. */
        if (caster->mpeaceful && !See_invisible && !Conflict)
            return TRUE;
        break;
    case MCAST_BLIND:
        /* blindness spell on blinded target */
        if (!haseyes(mdef->data) || mdef->mblinded)
            return TRUE;
        break;
    case MCAST_DESTRY_ARMR:
        /* Don't try to destroy armor if none is being worn */
        if (!(mdef->misc_worn_check & W_ARMOR))
            return TRUE;
        break;
    case MCAST_LEVITATE:
        if (is_floater(mdef->data) || is_flyer(mdef->data))
            return TRUE;
        if (mdef->mextrinsics & MR2_LEVITATE || mdef->mextrinsics & MR2_FLYING)
            return TRUE;
        break;
    case MCAST_REFLECTION:
        /* reflection when already reflecting */
        if ((has_reflection(caster) || mon_reflectsrc(caster)))
            return TRUE;
        break;
    case MCAST_FIRE_PILLAR:
        if (distmin(caster->mx, caster->my, mdef->mx, mdef->my) > 1
            && caster->data != &mons[PM_ARCH_VILE])
            return TRUE;
        break;
    case MCAST_ACID_BLAST:
        /* Don't blast itself with its own explosions */
        if (!(resists_acid(caster) || defended(caster, AD_ACID))
            && distmin(caster->mx, caster->my, mdef->mx, mdef->my) < 3 && rn2(5))
            return TRUE;
        /* prevent peacefuls from blasting player */
        if (caster->mpeaceful && distu(mdef->mx, mdef->my) < 3)
            return TRUE;
        break;
    case MCAST_FLESH_TO_STONE:
        if (resists_ston(mdef) || defended(mdef, AD_STON))
            return TRUE;
        if (mdef->mstone) /* Already stoned */
            return TRUE;
        break;
    case MCAST_MAKE_POOL:
        /* pools can only be created in certain locations */
        if (levl[mdef->mx][mdef->my].typ != ROOM && levl[mdef->mx][mdef->my].typ != CORR)
            return TRUE;
        /* Not effective vs flying or levitating mon */
        if (is_flyer(mdef->data) || is_floater(mdef->data) || amphibious(mdef->data))
            return TRUE;
        /* and then only rarely unless you're carrying the amulet. */
        if (!mon_has_amulet(mdef) && rn2(20))
            return TRUE;
        break;
    /* For now these are vs-player only spells */
    case MCAST_SPHERES:
    case MCAST_DARKNESS:
    case MCAST_BLOOD_RAIN:
    case MCAST_DISGUISE:
    case MCAST_MIRROR_IMAGE:
    case MCAST_INSECTS:
    case MCAST_CALL_UNDEAD:
    case MCAST_ENTOMB:
    case MCAST_AGGRAVATION:
    case MCAST_TELEPORT:
    case MCAST_SUMMON_MONS:
    case MCAST_CLONE_WIZ:
        impossible("castmm: monster cast MCF_VS_HERO spell (%d-%s) at monster",
                   spellnum, mcast_data[spellnum].name);
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
                caster->mx, caster->my, sgn(gt.tbx), sgn(gt.tby), FALSE, FALSE);
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
            spellnum = choose_monster_spell(caster, mattk->adtyp);
        /* not trying to attack?  don't allow directed spells */
        } while (--cnt > 0
                 && mspell_would_be_useless(caster, mdef, spellnum));
        if (cnt == 0)
            return M_ATTK_MISS;
    }

    /* monster unable to cast spells? */
    if (caster->mcan || caster->mspec_used || !ml) {
        if (canseemon(caster)) {
            if (is_undirected_spell(spellnum))
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
        caster->mspec_used = (int) (4 - caster->m_lev);
        if (caster->mspec_used < 2)
            caster->mspec_used = 2;

        /* mspec 0 two thirds of the time */
        if ((rn2(3) && power_caster(caster->data))
            /* mspec 0 always */
            || is_dprince(caster->data) || caster->iswiz)
            caster->mspec_used = 0;
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
        if (!is_undirected_spell(spellnum))
            pline_mon(caster, "%s casts a spell at %s!",
                canspotmon(caster) ? Monnam(caster) : "Something",
                mon_nam(mdef));

        if (is_undirected_spell(spellnum))
            pline("%s casts a spell!", Monnam(caster));
    }

    debugpline1("spellnum=%d", spellnum);
    if (Spell_blocking && counterspell(caster)) {
        return M_ATTK_MISS;
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
        dmg = mgc_melee_ad_fire(caster, mdef, dmg);
        break;
    case AD_COLD:
        dmg = mgc_melee_ad_cold(caster, mdef, dmg);
        break;
    case AD_ACID:
        dmg = mgc_melee_ad_acid(caster, mdef, dmg);
        break;
    case AD_MAGM:
        dmg = mgc_melee_ad_magm(caster, mdef, dmg);
        break;
    case AD_SPEL:  /* wizard spell */
    case AD_CLRC:  /* clerical spell */
        dmg = mcast_spell(caster, mdef, dmg, spellnum);
        break;
    default:
        impossible("castmm: adtype %d not handled.", mattk->adtyp);
    }

    if (dmg) {
        if (damage_mon(mdef, dmg, AD_SPEL, FALSE)) {
            monkilled(mdef, "", mattk->adtyp);
            ret |= M_ATTK_DEF_DIED;
        }
    }
    if (DEADMONSTER(caster))
        ret |= M_ATTK_AGR_DIED;
    return ret;
}

staticfn boolean
counterspell(struct monst *caster) {
    struct obj *otmp;
    /* If any more items are added for countering spells, we should
     * create a property instead. */
    if (u_wield_art(ART_SERENITY) || u_wield_art(ART_SCEPTRE_OF_MIGHT))
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

/* Helper function to standardize how far away spellcasters can target us.
 * For the exploding spells like ice bolt, we add an extra check for being
 * too close to the explosion.
 * A radius of 13 squares feels about right for the cutoff.
 * We don't check for sight because that should be covered in the useless spell
 * checks.
 */
boolean
mcast_dist_ok(struct monst *caster, boolean explosion)
{
    if (distu(caster->mx, caster->my) > 13*13)
        return FALSE;

    /* Sometimes allow them to cast at close range. */
    if (explosion) {
        if (distu(caster->mx, caster->my) <= 2 && rn2(5))
            return FALSE;
    }
    return TRUE;
}

staticfn int
calculate_damage(int base_damage, int distance) {
    /* Anything less is next to the player */
    if (distance < 9)
        return base_damage;
    if (distance > 80)
        distance = 80;

    float tmp = 100 - distance;
    tmp /= 100;
    tmp = ceil((float) (base_damage * tmp));

    /* debug line */
    if (flags.showdamage)
        debugpline2("(in: %d  out: %d)", base_damage, (int) tmp);

    return (int) tmp;
}


/*
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 * Monster wizard and cleric spellcasting functions.
 * Listed from low level to highest level.
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 */


staticfn int
mcast_psi_bolt(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;
    int mdist;

    if (!mdef || (DEADMONSTER(mdef) && !youdefend))
        return 0;

    /* prior to 3.4.0 Antimagic was setting the damage to 1--this
       made the spell virtually harmless to players with magic res. */
    if (youdefend) {
        if (!mcast_dist_ok(caster, FALSE))
            return 0;

        /* Less damage the farther away */
        mdist = distu(caster->mx, caster->my);
        dmg = calculate_damage(dmg, mdist);

        if (HTelepat || ETelepat) /* Little extra for sensitive minds */
            dmg += rnd(6);

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
    } else { /* mhitm */
        /* Less damage the farther away */
        mdist = dist2(caster->mx, caster->my, mdef->mx, mdef->my);
        dmg = calculate_damage(dmg, mdist);

        if (telepathic(mdef->data))
            dmg += rnd(6);
        if (resist(mdef, 0, 0, FALSE)) {
            shieldeff(mdef->mx, mdef->my);
            dmg = (dmg + 1) / 2;
        }
        if (canseemon(mdef))
            pline("%s %s%s", Monnam(mdef),
                can_flollop(mdef->data) ? "flollops" : "winces",
                (dmg <= 5) ? "." : "!");
    }
    return dmg;
}

staticfn int
mcast_fire_bolt(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;

    /* hotwire these to only go off if the critter can see you
     * to avoid bugs WRT the Eyes and detect monsters */
    if (youdefend) {
        if (!mcast_dist_ok(caster, TRUE)) {
            dmg = 0;
            if (canseemon(caster)) {
                pline("%s blasts the %s with fire and curses!",
                    Monnam(caster), rn2(2) ? "ceiling" : "floor");
            } else if (!rn2(20)) {
                You_hear("some cursing!");
            }
            return 0;
        }
        pline("%s blasts you with a bolt of fire!", Monnam(caster));
        /* Use monster's perception of hero's position */
        explode(caster->mux, caster->muy, BZ_M_SPELL(ZT_FIRE), dmg,
            MON_CASTBALL, EXPL_FIERY);

        if (fully_resistant(FIRE_RES)) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_FIRE);
        } else {
            monstunseesu(M_SEEN_FIRE);
        }
    } else if (mdef && !DEADMONSTER(mdef)) {
        if (canseemon(caster))
            pline("%s blasts %s with fire!", Monnam(caster), mon_nam(mdef));
        explode(mdef->mx, mdef->my, BZ_M_SPELL(ZT_FIRE), dmg,
                MON_CASTBALL, EXPL_FIERY);
    }
    return 0; /* damage handled by explode() */
}

staticfn int
mcast_ice_bolt(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean telepath_caster = mon_prop(caster, TELEPAT);

    if (youdefend) {
        /* caster must be within range and have line-of-sight or ESP */
        if (!mcast_dist_ok(caster, TRUE)
            || (!m_canseeu(caster) && !telepath_caster)) {
            if (canseemon(caster)) {
                pline("%s blasts the %s with cold and curses!",
                    Monnam(caster), rn2(2) ? "ceiling" : "floor");
            } else if (!rn2(20)) {
                You_hear("some cursing!");
            }
            return 0;
                                       }
        pline("%s blasts you with a bolt of cold!", Monnam(caster));
        /* Use monster's perception of hero's position */
        explode(caster->mux, caster->muy, BZ_M_SPELL(ZT_COLD), dmg,
            MON_CASTBALL, EXPL_FROSTY);

        if (fully_resistant(COLD_RES)) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_COLD);
        } else {
            monstunseesu(M_SEEN_COLD);
        }
    } else if (mdef && !DEADMONSTER(mdef)) {
        if (canseemon(caster))
            pline("%s blasts %s with ice!", Monnam(caster), mon_nam(mdef));
        explode(mdef->mx, mdef->my, BZ_M_SPELL(ZT_COLD), dmg,
                MON_CASTBALL, EXPL_FROSTY);
    }
    return 0; /* damage is handled by explode() */
}

staticfn int
mcast_open_wounds(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    int mdist = distu(caster->mx, caster->my);
    int ml = caster->m_lev;
    int dmg = d((int) ((ml / 2) + 1), 6);

    if (youdefend) {
        /* caster must be within range and have line-of-sight or ESP */
        if (!mcast_dist_ok(caster, FALSE)) {
            return 0;
        }
        /* Less damage the farther away */
        mdist = distu(caster->mx, caster->my);
        dmg = calculate_damage(dmg, mdist);

        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            dmg = (dmg + 1) / 2;
        } else {
            monstunseesu(M_SEEN_MAGR);
        }
        if (dmg <= 5) {
            Your("%s itches badly for a moment.", body_part(SKIN));
        } else if (dmg <= 10) {
            pline("Wounds appear on your body!");
            add_blood(u.ux, u.uy, gu.urace.mnum);
        } else if (dmg <= 20) {
            pline("Severe wounds appear on your body!");
            add_blood(u.ux, u.uy, gu.urace.mnum);
        } else {
            Your("body is covered with painful wounds!");
            add_blood(u.ux, u.uy, gu.urace.mnum);
        }
    } else if (mdef && !DEADMONSTER(mdef)) {
        /* mhitm */
        /* Less damage the farther away */
        mdist = dist2(caster->mx, caster->my, mdef->mx, mdef->my);
        dmg = calculate_damage(dmg, mdist);

        if (resist(mdef, 0, 0, FALSE)) {
            shieldeff(mdef->mx, mdef->my);
            dmg = (dmg + 1) / 2;
        }
        if (canseemon(mdef)) {
            if (dmg <= 5) {
                pline("%s looks itchy!", Monnam(mdef));
            } else if (dmg <= 10) {
                pline("Wounds appear on %s!", mon_nam(mdef));
                add_blood(mdef->mx, mdef->my, mdef->mnum);
            } else if (dmg <= 20) {
                pline("Severe wounds appear on %s!", mon_nam(mdef));
                add_blood(mdef->mx, mdef->my, mdef->mnum);
            } else {
                pline("%s is covered in wounds!", Monnam(mdef));
                add_blood(mdef->mx, mdef->my, mdef->mnum);
            }
        }
    }
    return dmg;
}

staticfn int
mcast_spheres(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    if (!youdefend)
        return 0;

    struct permonst *pm = &mons[rnd_sphere()];
    struct monst *mtmp2 = (struct monst *) 0;
    const char *fmt, *what;
    char whatbuf[QBUFSZ];
    boolean success = FALSE, seecaster;
    int i, quan = rnd(3), oldseen, newseen;
    coord bypos;

    oldseen = monster_census(TRUE);

    for (i = 0; i <= quan; i++) {
        if (!enexto(&bypos, caster->mx, caster->my, caster->data))
            break;
        if ((pm = &mons[rnd_sphere()]) != 0
            && (mtmp2 = make_msummoned(pm, caster, FALSE, bypos.x, bypos.y)) != 0) {
            success = TRUE;
            mtmp2->msleeping = mtmp2->mpeaceful = mtmp2->mtame = 0;
            set_malign(mtmp2);
            }
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

    return 0;
}

/* helper function for: mcast_spheres */
staticfn int
rnd_sphere(void)
{
    return PM_FREEZING_SPHERE + rn2(PM_ACID_SPHERE - PM_FREEZING_SPHERE);
}

/* TODO: Handle curing other monsters */
staticfn int
mcast_cure_self(struct monst *caster)
{
    int heal_dice = max(3, 3 + caster->m_lev / 8);
    if (caster->mhp < caster->mhpmax) {
        if (canseemon(caster))
            pline_mon(caster, "%s looks better.", Monnam(caster));
        /* note: player healing does 6d4; this used to do 1d8 */
        healmon(caster, d(heal_dice, 6), 0);
    }
    /* Cure other ailments that players spells are capable of. */
    if (caster->mblinded)
        mcureblindness(caster, canseemon(caster));
    if (caster->mdiseased || caster->mrabid) {
        caster->mdiseased = caster->mrabid = 0;
        if (canseemon(caster))
            pline("%s is no longer ill.", Monnam(caster));
    }
    if (caster->mwither) {
        caster->mwither = 0;
        pline("%s is no longer withering away.", Monnam(caster));
    }
    return 0;
}

staticfn int
mcast_darkness(struct monst *caster UNUSED, struct monst *mdef UNUSED)
{
    litroom(FALSE, (struct obj *) 0);
    return 0;
}

staticfn int
mcast_greasemon(struct monst *caster UNUSED, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    /* Reusing the grease trap effect */
    if (youdefend) {
        grease_hitu();
    } else if (mdef && !DEADMONSTER(mdef)) { /* mhitm */
        grease_hitm(mdef);
    }
    return 0;
}

staticfn int
mcast_blood_rain(struct monst *caster UNUSED, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    int startx = max(u.ux - 1, 0);
    int starty = max(u.uy - 1, 0);
    int stopx = min(u.ux + 1, COLNO - 1);
    int stopy = min(u.uy + 1, ROWNO - 1);

    if (!youdefend) { /* mhitm */
        startx = max(mdef->mx - 1, 0);
        starty = max(mdef->my - 1, 0);
        stopx = min(mdef->mx + 1, COLNO - 1);
        stopy = min(mdef->my + 1, ROWNO - 1);
    }

    pline("Blood rains down around %s!", youdefend ? "you" : mon_nam(mdef));
    for (coordxy i = startx; i <= stopx; i++) {
        for (coordxy j = starty; j <= stopy; j++) {
            if (isok(i, j))
                levl[i][j].splatpm = PM_HUMAN; /* Default to human blood */
        }
    }
    return d(1, 6);
}

staticfn int
mcast_haste_self(struct monst *caster)
{
    mon_adjust_speed(caster, 1, (struct obj *) 0);
    return 0;
}

/* Magic resistance no longer nullifies this spell, it cuts the duration in half.
 * The duration is also now calculated a bit differently as d(ml, 4)
 */
staticfn int
mcast_confuse_mon(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    int dmg = d((int) caster->m_lev, 4);

    if (youdefend) {
        boolean oldprop = !!Confusion;
        if (Antimagic)
            dmg -= (dmg + 1) / 2;
        if (Half_spell_damage)
            dmg -= (dmg + 1) / 4;
        make_confused(HConfusion + dmg, TRUE);
        if (Hallucination)
            You_feel("%s!", oldprop ? "trippier" : "trippy");
        else
            You_feel("%sconfused!", oldprop ? "more " : "");
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
    return 0;
}

staticfn int
mcast_protection(struct monst *caster)
{
    int natac = find_mac(caster) + caster->mprotection;
    int loglev = 0, gain = 0;

    for (int ml = caster->m_lev; ml > 0; ml /= 2)
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
                caster->mprottime = (caster->iswiz || caster->iscthulhu
                                   || is_prince(caster->data)
                                   || caster->data->msound == MS_NEMESIS
                                   || caster->data->msound == MS_LEADER)
                                   ? 20 : 10;
                pline_The("air around %s begins to shimmer with a %s haze.",
                          mon_nam(caster), hcolor(NH_GOLDEN));
            }
        }
    }
    caster->mprotection += gain;
    return 0;
}

/* Magic resistance no longer nullifies this spell, it cuts the duration by 25%.
 */
staticfn int
mcast_stun_mon(struct monst *caster UNUSED, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    int dmg = d(ACURR(A_DEX) < 12 ? 6 : 4, 4);;

    if (!mdef || (DEADMONSTER(mdef) && !youdefend))
        return 0;

    if (youdefend) {
        if (Antimagic || Free_action)
            dmg -= (dmg + 1) / 4;
        /* make_stunned checks Stun_resistance */
        if (!Stun_resistance)
            You(Stunned ? "struggle to keep your balance." : "reel...");
        if (Half_spell_damage)
            dmg -= (dmg + 1) / 4;
        make_stunned((HStun & TIMEOUT) + (long) dmg, FALSE);
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
    return 0;
}

/* Caster can put monster to sleep */
staticfn int
mcast_sleep_mon(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    int dmg = d(4 + (int) caster->m_lev, 5);

    if (youdefend) {
        if (fully_resistant(SLEEP_RES)) {
            You("yawn.");
            monstseesu(M_SEEN_SLEEP);
        } else {
            You_feel("feel exhausted.");
            fall_asleep(-d(dmg, 5), TRUE);
            exercise(A_DEX, FALSE);
            monstunseesu(M_SEEN_SLEEP);
        }
    } else { /* mhitm */
        if (!mdef->msleeping && sleep_monst(mdef, dmg, -1)) {
            if (gv.vis && canspotmon(mdef)) {
                char buf[BUFSZ];

                Strcpy(buf, Monnam(mdef));
                pline("%s is put to sleep by %s.", buf, mon_nam(caster));
            }
            mdef->mstrategy &= ~STRAT_WAITFORU;
            slept_monst(mdef);
        }
    }
    return 0;
}

/* makes self invisible */
staticfn int
mcast_disappear(struct monst *caster)
{
    if (!caster->minvis && !caster->invis_blkd) {
        if (canseemon(caster))
            pline_mon(caster, "%s suddenly %s!", Monnam(caster),
                  !See_invisible ? "disappears" : "becomes transparent");
        mon_set_minvis(caster);
        if (cansee(caster->mx, caster->my) && !canspotmon(caster))
            map_invisible(caster->mx, caster->my);
    } else
        impossible("no reason for monster to cast disappear spell?");
    return 0;
}

/* Magic resistance no longer nullifies this spell, it cuts the duration in half. */
staticfn int
mcast_paralyze(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    int dmg;

    if (youdefend) {
        dmg = 4 + (int) caster->m_lev;
        if (Free_action) {
            shieldeff(u.ux, u.uy);
            if (gm.multi >= 0)
                You("stiffen briefly.");
            dmg = 1; /* to produce nomul(-1), not actual damage */
        } else {
            if (gm.multi >= 0)
                You("are frozen in place!");
            if (Half_spell_damage)
                dmg -= (dmg + 1) / 4;
            if (Antimagic)
                dmg -= (dmg + 1) / 4;
            dmg = max(1, dmg);
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
    return 0;
}

staticfn int
mcast_vuln_mon(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    int dur = rnd(250) + 250;
    if (!youdefend) {
        return 0;
    }
    if (!mcast_dist_ok(caster, FALSE))
        return 0;

    if (caster->data == &mons[PM_ASMODEUS]) {
        if (Vulnerable_cold)
            return 0;
        pline("A %s film oozes over your %s!",
                  Blind ? "slimy" : vulntext[2], body_part(SKIN));
        dur += rnd(250) + 250;
        if (Half_spell_damage)
            dur = (dur + 1) / 2;
        incr_itimeout(&HVulnerable_cold, dur);
    } else {
        if (Half_spell_damage)
            dur = (dur + 1) / 2;
        if (Antimagic)
            dur -= (dur + 1) / 4;
        vuln_u(dur);
    }
    return 0;
}

/* helper function for MCAST_VULN; also used in other places.
 * Spin a random property to make the player vulnerable to. */
void vuln_u(int dur)
{
    int i = rnd(5);
    pline("A %s film oozes over your %s!",
                      Blind ? "slimy" : vulntext[i], body_part(SKIN));
    switch (i) {
    case 1:
        You_feel("%s inflammable.", Vulnerable_fire ? "even more" : "quite");
        incr_itimeout(&HVulnerable_fire, dur);
        break;
    case 2:
        You_feel("%s extremely chilly.", Vulnerable_cold ? "even more" : "extremely");
        incr_itimeout(&HVulnerable_cold, dur);
        break;
    case 3:
        You_feel("%s conductive.", Vulnerable_elec ? "even more" : "overly");
        incr_itimeout(&HVulnerable_elec, dur);
        break;
    case 4:
        You_feel("%s corrodable.", Vulnerable_acid ? "even more" : "easily");
        incr_itimeout(&HVulnerable_acid, dur);
        break;
    case 5:
        incr_itimeout(&HVulnerable_poi, dur);
        You_feel("%s hearty.", Vulnerable_poi ? "even less" : "less");
        break;
    }
}

staticfn int
mcast_disguise(struct monst *caster, struct monst *mdef UNUSED)
{
    if (canseemon(caster))
        pline_mon(caster, "%s %s.", Monnam(caster),
            Role_if(PM_ROGUE) ? "magically disguises itself" : "transforms");

    caster->m_ap_type = M_AP_MONSTER;
    caster->mappearance = rndmonnum_adj(5, 10);
    newsym(caster->mx, caster->my);
    return 0;
}

/* Causes a pet to betray you. If target is provided and tame, abuse it and
 * give it a chance to betray you; otherwise find random adjacent pet */
staticfn int
mcast_betray(struct monst *caster, struct monst *mdef UNUSED)
{
    struct monst *pet;

    /* Use specific target if it's tame, otherwise find random
       adjacent pet */
    if (mdef && mdef->mtame)
        pet = mdef;
    else
        pet = find_adjacent_pet(caster);

    if (pet) {
        struct edog *edog = EDOG(pet);
        /* betrayed isn't guaranteed, but we can nudge it a little ;) */
        edog->abuse++;

        /* Betrayed takes care of everything */
        betrayed(pet);
    }
    return 0;
}

/* Returns a random adjacent tame monster, or NULL.
   Used by MGC_BETRAY. */
staticfn struct monst *
find_adjacent_pet(struct monst *mtmp)
{
    struct monst *candidates[8];
    int count = 0;
    int dx, dy;

    for (dx = -1; dx <= 1; dx++) {
        for (dy = -1; dy <= 1; dy++) {
            struct monst *m;
            if (dx == 0 && dy == 0)
                continue;
            if (!isok(mtmp->mx + dx, mtmp->my + dy))
                continue;
            m = m_at(mtmp->mx + dx, mtmp->my + dy);
            if (m && m->mtame)
                candidates[count++] = m;
        }
    }
    if (count == 0)
        return (struct monst *) 0;
    return candidates[rn2(count)];
}

staticfn int
mcast_blind_mon(struct monst *caster UNUSED, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (youdefend) {
        /* note: resists_blnd() doesn't apply here */
        if (!Blinded) {
            int num_eyes = eyecount(gy.youmonst.data);

            pline("Scales cover your %s!", (num_eyes == 1)
                                            ? body_part(EYE)
                                            : makeplural(body_part(EYE)));
            make_blinded(Half_spell_damage ? 150L : 200L, FALSE);
            if (!Blind)
                Your1(vision_clears);
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
    return 0;
}

/* drain strength */
staticfn int
mcast_weaken_mon(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (youdefend) {
        dmg = caster->m_lev - 6;
        if (Antimagic)
            dmg -= (dmg + 1) / 4;
        if (Half_spell_damage)
            dmg -= (dmg + 1) / 4;
        char kbuf[BUFSZ];
        You("suddenly feel weaker!");

        if (dmg < 1) /* paranoia since only chosen when m_lev is high */
            dmg = 1;

        losestr(rnd(dmg),
                death_inflicted_by(kbuf, "strength loss", caster),
                KILLED_BY);
        svk.killer.name[0] = '\0'; /* not killed if we get here... */
    } else if (mdef && !DEADMONSTER(mdef)) { /* mhitm */
        if (resist(mdef, 0, 0, FALSE)) {
            shieldeff(mdef->mx, mdef->my);
            pline("%s looks momentarily weakened.", Monnam(mdef));
        } else {
            if (canseemon(mdef))
                pline("%s suddenly seems weaker!", Monnam(mdef));
            /* monsters don't have strength, so drain max hp instead */
            mdef->mhpmax -= dmg;
            if (damage_mon(mdef, dmg, AD_SPEL, FALSE)) {
                monkilled(mdef, "", AD_SPEL);
            }
        }
    }
    return dmg;
}

/* drains luck */
staticfn int
mcast_evil_eye(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (youdefend) {
        if (mcast_dist_ok(caster, FALSE)) {
            struct attack evilEye = { AT_GAZE, AD_LUCK, 1, 4 };
            (void) gazemu(caster, &evilEye);
        }
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
    return 0;
}

int
mcast_destroy_armor(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst,
            uattk = caster == &gy.youmonst;
    boolean mtrap = !caster;
    int erodelvl = rnd(3);
    struct obj *oatmp;
    static const char mal_aura[] = "feel a malignant aura surround %s.";

    if (!mdef || (DEADMONSTER(mdef) && !youdefend))
        return 0;

    if (youdefend ? Antimagic
                : (resists_magm(mdef) || defended(mdef, AD_MAGM))) {
        if (youdefend) {
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
            if (youdefend || canseemon(mdef)) {
                if (!Blind)
                    pline("%s shines brightly.", The(xname(oatmp)));
                pline("%s is immune to %s destructive magic.",
                      The(xname(oatmp)),
                      mtrap ? "the trap's"
                      : uattk ? "your" : s_suffix(mon_nam(caster)));
            }
            return 0;
        } else if (oatmp->otyp == CRYSTAL_PLATE_MAIL
            || oatmp->otyp == BRACERS_OF_INTEGRITY
            || oatmp->oprops & ITEM_INTEGRITY) {
            if (youdefend && !Blind)
                pline("%s glimmers brightly.", Yname2(oatmp));
            pline("%s is immune to %s destructive magic.",
                  Yname2(oatmp),
                  mtrap ? "the trap's"
                  : uattk ? "your" : s_suffix(mon_nam(caster)));
            return 0; /* no effect */
        } else if (uwep && uwep->oprops & ITEM_HEXING && !uwep->cursed) {
            You(mal_aura, "the hexed weapon");
            curse(uwep);
            update_inventory();
            return 0; /* no effect... for now */
        } else if (oatmp->oerodeproof) {
            if (!youdefend && !canseemon(mdef) && olfaction(gy.youmonst.data)) {
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
            if (youdefend) {
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
                        action = is_bracer(oatmp) ? "crumble away"
                                                  : "crumbles away";
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
        if (youdefend)
            Your("body itches.");
        else if (uattk || canseemon(mdef))
            pline("%s seems irritated.", Monnam(mdef));
    }
    update_inventory();

    return 0;
}

staticfn int
mcast_mirror_image(struct monst *caster)
{
    if (!mcast_dist_ok(caster, FALSE))
        return 0;

    int quan = rnd(caster->m_lev < 10 ? 2 : 5);
    coord bypos;
    boolean created = FALSE;

    for (int i = 0; i < quan; i++) {
        if (!enexto(&bypos, caster->mx, caster->my, caster->data))
            break;
        created = spawn_mirror_image(caster, bypos.x, bypos.y);
    }

    if (caster->iswiz && created) {
        SetVoice(caster, 0, 80, 0);
        verbalize("Ah, but which of us is the real one, fool?");
    } else if (caster && canseemon(caster)) {
        pline_mon(caster, "%s image splinters!", s_suffix(Monnam(caster)));
    }
    return 0;
}

/* helper functionf or mcast_mirror_image
 * Returns 1 if illusions were seen being created */
staticfn int
spawn_mirror_image(struct monst *mtmp, coordxy x, coordxy y) {
    struct monst *illusion =
        makemon(&mons[PM_ILLUSION],
        x, y, MM_NOCOUNTBIRTH | MM_ANGRY | MM_NOMSG);
    if (illusion) {
        if (mtmp->mappearance && !Protection_from_shape_changers)
            illusion->mappearance = mtmp->mappearance;
        else
            illusion->mappearance = mtmp->mnum;
        newsym(illusion->mx, illusion->my);
        if (canseemon(mtmp))
            return 1;
    }
    return 0;
}

staticfn int
mcast_blood_spear(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean vlad_casts = caster->data == &mons[PM_VLAD_THE_IMPALER];
    int dmg = vlad_casts ? d(10, 10) : d((min(caster->m_lev, 50) / 2) + 4, 4);
    boolean foundyou = (u.ux == caster->mux && u.uy == caster->muy);

    /* Allow misfires (from displacement) to target other monsters */
    if (youdefend && !foundyou) {
        youdefend = FALSE;
        mdef = m_at(caster->mux, caster->muy);
    }

    if (youdefend) {
        if (!mcast_dist_ok(caster, FALSE))
            return 0;

        pline("The blood on the %s springs to life and %s you!",
                    surface(u.ux, u.uy),
                    vlad_casts ? "impales" : "stabs");
        wipe_blood(u.ux, u.uy);
        return dmg;
    } else if (mdef && !DEADMONSTER(mdef))  { /* mhitm */
        pline("The blood on the %s springs to life and %s %s!",
                   surface(mdef->mx, mdef->my),
                   vlad_casts ? "impales" : "stabs",
                   mon_nam(mdef));
        wipe_blood(mdef->mx, mdef->my);
        return dmg;
    }
    return 0;
}

staticfn int
mcast_insects(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (!youdefend)
        return 0;
    if (!mcast_dist_ok(caster, FALSE)) {
        return 0;
    }
    /* Try for insects, and if there are none
       left, go for (sticks to) snakes.  -3. */
    struct permonst *pm = mkclass(S_ANT, 0);
    struct monst *mtmp2 = (struct monst *) 0;
    char whatbuf[QBUFSZ], let = (pm ? S_ANT : S_SNAKE);
    boolean success = FALSE, seecaster;
    int i, quan, oldseen, newseen;
    coord bypos;
    const char *fmt, *what;

    oldseen = monster_census(TRUE);
    quan = caster->m_lev < 2 ? 1 : rnd((int) caster->m_lev / 2);
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
    what = (let == S_SNAKE) ? "snakes" : "insects";
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

    return 0;
}

staticfn int
mcast_hobble(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean foundyou = (u.ux == caster->mux && u.uy == caster->muy);
    int mdist;

    /* Allow misfires (from displacement) to target other monsters */
    if (youdefend && !foundyou) {
        youdefend = FALSE;
        mdef = m_at(caster->mux, caster->muy);
    }

    if (youdefend) {
        if (!mcast_dist_ok(caster, FALSE))
            return 0;

        if (Antimagic)
            dmg -= (dmg + 1) / 4;
        if (Half_spell_damage)
            dmg -= (dmg + 1) / 4;
        /* Less damage the farther away */
        mdist = distu(caster->mx, caster->my);
        dmg = calculate_damage(dmg, mdist);

        if (dmg <= 0)
            return 0;

        long side = rn2(3) ? LEFT_SIDE : RIGHT_SIDE;
        Your("%s are smashed by a bolt of force!",
            makeplural(body_part(LEG)));

        if (!(uarmf && objdescr_is(uarmf, "jungle boots")))
            set_wounded_legs(side, rn1(15, 15));
    } else if (mdef && !DEADMONSTER(mdef))  { /* mhitm */
        /* Less damage the farther away */
        mdist = dist2(caster->mx, caster->my, mdef->mx, mdef->my);
        dmg = calculate_damage(dmg, mdist);

        if (resist(mdef, 0, 0, FALSE)) {
            shieldeff(mdef->mx, mdef->my);
            dmg = (dmg + 1) / 2;
        }
        if (dmg <= 0)
            return 0;

        if (canseemon(mdef)) {
            pline("%s %s is smashed by a bolt of force!",
                s_suffix(Monnam(mdef)),
                mbodypart(mdef, LEG));
        }
    }
    return dmg;
}

staticfn int
mcast_levitate(struct monst *caster UNUSED, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (youdefend) {
        struct obj *pseudo = mksobj(SPE_LEVITATION, FALSE, FALSE);
        pseudo->cursed = 1;
        pseudo->blessed = 0;
        (void) peffects(pseudo);
        obfree(pseudo, (struct obj *) 0);

        /* Keep them floating a bit longer */
        struct obj *pseudo2 = mksobj(SPE_LEVITATION, FALSE, FALSE);
        pseudo2->cursed = 0;
        pseudo2->blessed = 0;
        pseudo2->odiluted = 1;
        (void) peffects(pseudo2);
        obfree(pseudo2, (struct obj *) 0);
    } else {
        mdef->mextrinsics |= MR2_LEVITATE;
        if (canseemon(mdef)) {
            pline("%s starts to float in the air!", Monnam(mdef));
        }
    }
    return 0;
}

staticfn int
mcast_curse_items(struct monst *caster UNUSED, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
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
    return 0;
}

staticfn int
mcast_reflection(struct monst *caster)
{
    boolean strongbad = (caster->iswiz
                         || caster->iscthulhu
                         || is_prince(caster->data)
                         || caster->data->msound == MS_NEMESIS
                         || caster->data->msound == MS_LEADER);
    if (canseemon(caster))
        pline("A shimmering globe appears around %s!", mon_nam(caster));

    /* monster reflection is handled in mon_reflectsrc() */
    caster->mextrinsics |= MR2_REFLECTION;
    caster->mreflecttime = rn1(50, strongbad ? 200 : 100);
    return 0;
}

staticfn int
mcast_call_undead(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (!youdefend)
        return 0;
    if (!mcast_dist_ok(caster, FALSE))
        return 0;
    coord mm;
    mm.x = u.ux;
    mm.y = u.uy;
    pline("Undead creatures are called forth from the grave!");
    mkundead(caster, &mm, FALSE, NO_MINVENT);
    return 0;
}

staticfn int
mcast_blight(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    /* This could use is_fleshy(), but that would make a large set
     * of monsters immune like fungus, blobs, and jellies. */
    boolean no_effect = nonliving(mdef->data) || mon_prop(mdef, DISINT_RES);
    uchar withertime = rn1(41, 20);
    boolean lose_maxhp = (withertime >= 8); /* if already withering */

    if (no_effect)
        return 0;

    if (youdefend) {
        if (!mcast_dist_ok(caster, FALSE))
            return 0;
        if (BWithering)
            return 0;

        You("%s rapidly decomposing!", Withering ? "continue" : "begin");
        incr_itimeout(&HWithering, withertime);
        morehungry(40 + d(6, 4));
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
    } else if (mdef && !DEADMONSTER(mdef)) { /* mhitm */
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
    return 0;
}


/* 40% chance of zapping enchantment from current wielded weapon
 * 45% chance from random piece of worn gear
 * 15% chance of taking it from a random charged ring, charged tool, wand, or
 * unequipped weapon or armor */
staticfn int
mcast_disenchant(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    struct obj *targ = (struct obj *) 0;
    short loss = (short) rnd(3);
    const schar MIN_SPE1 = -7; /* for worn gear */
    const schar MIN_SPE2 = 0;  /* for tools & wands */
    schar floor = MIN_SPE1;

    /* TODO: Implement mhitm effects */
    if (!youdefend)
        return 0;

    if (uwep && uwep->spe > MIN_SPE1 && 40 > rn2(100))
        targ = uwep;
    else if ((targ = some_armor(&gy.youmonst)) && targ->spe > MIN_SPE1
             && 75 > rn2(100))
        ; /* targ already selected */
    else {
        struct obj *otmp;
        int choices = 0;
        for (otmp = gi.invent; otmp; otmp = otmp->nobj) {
            short oclass = objects[otmp->otyp].oc_class;
            if ((oclass == RING_CLASS && objects[otmp->otyp].oc_charged)
                || (oclass == TOOL_CLASS && is_weptool(otmp))) {
                /* weptools and charged rings use the same rules for weapons and
                 * armor */
                if (otmp->spe > MIN_SPE1 && !rn2(++choices)) {
                    targ = otmp;
                    floor = MIN_SPE1;
                }
            }
            else if (oclass == WAND_CLASS
                     || (oclass == TOOL_CLASS
                         && objects[otmp->otyp].oc_charged
                         && objects[otmp->otyp].oc_magic)) {
                /* wands and charged tools do not use the same rules since
                 * negative spe doesn't make sense for them (well, it does for
                 * wands, but that would mix this up with cancellation) */
                if (otmp->spe > MIN_SPE2 && !rn2(++choices)) {
                    targ = otmp;
                    floor = MIN_SPE2;
                    /* account for tools and wands which have a higher number of
                     * charges than normal, or have been recharged beyond their
                     * normal amount */
                    loss = max(loss, otmp->spe / 3);
                }
            }
        }
    }
    if (!targ)
        /* couldn't find anything to disenchant... */
        return 0;
    if (targ->spe > 0) {
        pline("%s absorbs magic energies from %s!", Monnam(caster),
              yname(targ));
        caster->mspec_used = max(caster->mspec_used - loss, 0);
        floor = 0;
    }
    else {
        pline("%s glows black.", Yname2(targ));
    }
    targ->spe = max(floor, targ->spe - loss);
    if (targ->spe < 0)
        curse(targ);

    return 0;
}

staticfn int
mcast_lightning(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean foundyou = (u.ux == caster->mux && u.uy == caster->muy);
    boolean reflects = FALSE;

    Soundeffect(se_bolt_of_lightning, 80);
    int dmg = d(8, 6);
    int orig_dmg = dmg;

    /* Allow misfires (from displacement) to target other monsters */
    if (youdefend && !foundyou) {
        youdefend = FALSE;
        mdef = m_at(caster->mux, caster->muy);
    }

    if (youdefend) {
        /* caster must be within range and have line-of-sight or ESP */
        if (!mcast_dist_ok(caster, FALSE))
            return 0;

        pline("A bolt of lightning strikes down at you from above!");
        const char* reflectsrc = ureflectsrc();

        if (reflectsrc || fully_resistant(SHOCK_RES)) {
            shieldeff(u.ux, u.uy);
            if (reflectsrc) {
                dmg = resist_reduce(d(4, 6), SHOCK_RES);
                pline("It bounces off your %s.", reflectsrc);
                monstseesu(M_SEEN_REFL);
                reflects = TRUE;
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
            dmg -= (dmg + 1) / 4;

        (void) destroy_items(&gy.youmonst, AD_ELEC, orig_dmg);
        /* blind hero; no effect if already blind */
        (void) flashburn((long) rnd(100), TRUE);
    } else if (mdef && !DEADMONSTER(mdef))  { /* mhitm */
        if (canseemon(mdef))
            pline("A bolt of lightning strikes down at %s from above!",
                mon_nam(mdef));

        const char* monreflector = mon_reflectsrc(mdef);
        if (monreflector)
            pline("It bounces off %s %s.", s_suffix(mon_nam(mdef)),
                  monreflector);
        if (resists_elec(mdef) || defended(mdef, AD_ELEC)) {
            shieldeff(u.ux, u.uy);
            dmg = 0;
        } else {
            dmg = d(8, 6);
        }
        if (monreflector) {
            dmg /= 2;
            reflects = TRUE;
        } else {
            dmg += destroy_items(mdef, AD_ELEC, orig_dmg);
        }
    }

    /* lightning might destroy iron bars if hero is on such a spot;
       reflection protects terrain here [execution won't get here due
       to 'if (reflects) break' above] but hero resistance doesn't;
       do this before maybe blinding the hero via flashburn() */
    if (!reflects)
        mon_spell_hits_spot(caster, AD_ELEC, u.ux, u.uy);
    return dmg;
}

staticfn int
mcast_fire_pillar(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean foundyou = (u.ux == caster->mux && u.uy == caster->muy);

    int dmg = d(8, 6);
    int orig_dmg = dmg;

    /* Allow misfires (from displacement) to target other monsters */
    if (youdefend && !foundyou) {
        youdefend = FALSE;
        mdef = m_at(caster->mux, caster->muy);
    }

    if (youdefend) {
        if (!mcast_dist_ok(caster, FALSE))
            return 0;

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
            dmg -= (dmg + 1) / 4;
        burn_away_slime();
        (void) burnarmor(&gy.youmonst);
        (void) destroy_items(&gy.youmonst, AD_FIRE, orig_dmg);
        ignite_items(gi.invent);
        /* burn up flammable items on the floor, melt ice terrain */
        mon_spell_hits_spot(caster, AD_FIRE, u.ux, u.uy);
    } else if (mdef && !DEADMONSTER(mdef)) { /* mhitm */
        if (canseemon(mdef))
            pline("A pillar of fire strikes all around %s!", mon_nam(mdef));
        if (resists_fire(mdef) || defended(mdef, AD_FIRE)) {
            shieldeff(mdef->mx, mdef->my);
            dmg = 0;
        }
        if (!defended(mdef, AD_FIRE)) {
            (void) burnarmor(mdef);
            dmg += destroy_items(mdef, AD_FIRE, orig_dmg);
        }
        /* burn up flammable items on the floor, melt ice terrain */
        mon_spell_hits_spot(caster, AD_FIRE, mdef->mx, mdef->my);
    }
    return dmg;
}

staticfn int
mcast_summon_minion(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    struct monst *minion = (struct monst *) 0;
    int aligntype;

    if (youdefend) {
        /* Monster casting at player - can summon near player */
        if (!mcast_dist_ok(caster, FALSE))
            return 0;

        aligntype = mon_aligntyp(caster);
        minion = summon_minion(aligntype, FALSE);
        if (minion) {
            boolean vassal = (aligntype == A_NONE);
            set_malign(minion);
            if (canspotmon(minion))
                pline("A %s of %s appears!",
                      vassal ? "vassal" : "servant",
                       aligns[1 - aligntype].noun);
        }
    } else { /* mhitm */
        ; /* monster vs monster is suppressed, as summon_minion()
           currently does not support anything but the player
           as a target */
    }
    return 0;
}

staticfn int
mcast_entomb(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    if (!youdefend)
        return 0;

    /* entomb you in rocks to delay you and get away */
    coordxy x, y;
    /* Only allow casting at relatively short-range */
    if (mcast_dist_ok(caster, FALSE) && !m_next2u(caster)) {
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
        /* Don't let monsters spam this, they should be trying to get away */
        caster->mspec_used += d(20, 20);
        caster->mflee = 1;
    }
    return 0;
}

/* helper function for mcast_entomb
 * is (x,y) entombed (completely surrounded by boulders or nonwalkable spaces)?
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

/* this is physical damage (force not heat), not magical, nor fire damage */
staticfn int
mcast_geyser(struct monst *caster UNUSED, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean foundyou = (u.ux == caster->mux && u.uy == caster->muy);
    int dmg = d(8, 6);

    /* Allow misfires (from displacement) to target other monsters */
    if (youdefend && !foundyou) {
        youdefend = FALSE;
        mdef = m_at(caster->mux, caster->muy);
    }

    if (youdefend) {
        pline("A sudden geyser slams into you from nowhere!");
        if (Half_physical_damage)
            dmg -= (dmg + 1) / 4;
        if (u.umonnum == PM_IRON_GOLEM) {
            You("rust!");
            Strcpy(svk.killer.name, "rusted away");
            svk.killer.format = NO_KILLER_PREFIX;
            rehumanize();
            dmg = 0; /* prevent further damage after rehumanization */
            rehydrate(rn1(300, 300));
        }
        erode_armor(&gy.youmonst, ERODE_RUST);
        /* since inventory items aren't affected, don't include this */
        /* make floor items wet */
        water_damage_chain(svl.level.objects[u.ux][u.uy], TRUE);
    } else if (mdef && !DEADMONSTER(mdef)) { /* mhitm */
        if (canseemon(mdef))
            pline("A sudden geyser slams into %s from nowhere!",
                mon_nam(mdef));
        erode_armor(mdef, ERODE_RUST);
        /* since inventory items aren't affected, don't include this */
        /* make floor items wet */
        water_damage_chain(svl.level.objects[mdef->mx][mdef->my], TRUE);
    }
    return dmg;
}

staticfn int
mcast_aggravation(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    /* Skip aggravate if we are not the target */
    if (youdefend) {
        if (!mcast_dist_ok(caster, FALSE))
            return 0;
        incr_itimeout(&HAggravate_monster, rnd(75) + 50);
        You_feel("that monsters are aware of your presence.");
        aggravate();
    }
    return 0;
}

staticfn int
mcast_acid_blast(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    int dmg = d((min(caster->m_lev, 50) / 2) + 4, 8);

    /* hotwire these to only go off if the critter can see you
     * to avoid bugs WRT the Eyes and detect monsters */
    if (youdefend) {
        /* caster must be within range and have line-of-sight or ESP */
        if (!mcast_dist_ok(caster, TRUE)) {
            if (canseemon(caster)) {
                pline("%s blasts the %s with %s and curses!",
                  Monnam(caster), rn2(2) ? "ceiling"
                                       : "floor", "acid");
            } else if (!rn2(20)) {
                You_hear("some cursing!");
            }
            return 0;
                                       }
        pline("%s douses you in a torrent of acid!", Monnam(caster));
        explode(caster->mux, caster->muy, BZ_M_SPELL(ZT_ACID), dmg,
            MON_CASTBALL, EXPL_WET);

        if (fully_resistant(ACID_RES)) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_ACID);
        } else {
            monstunseesu(M_SEEN_ACID);
        }
    } else if (mdef && !DEADMONSTER(mdef)) {
        if (canseemon(caster))
            pline("%s blasts %s with acid!", Monnam(caster), mon_nam(mdef));
        explode(mdef->mx, mdef->my, BZ_M_SPELL(ZT_ACID), dmg,
                MON_CASTBALL, EXPL_WET);
    }
    return 0; /* damage handled by explode() */
}

staticfn int
mcast_teleport(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (youdefend) {
        /* If the caster is feeling strong (hp is 80% or better) warp them
         * directly next to the player */
        if (caster->mhp * 5 >= caster->mhpmax * 4) {
            mnexto(caster, RLOC_MSG);
        }
        /* teleport them elsewhere if their health is low (under 1/3).*/
        else if (caster->mhp * 3 <= caster->mhpmax) {
            coordxy sx, sy;
            coordxy ox = caster->mx;
            coordxy oy = caster->my;
            choose_stairs(&sx, &sy, (caster->m_id % 2));
            mnearto(caster, sx, sy, TRUE, RLOC_MSG);

            /* Leave behind an illusory duplicate (maybe) */
            if (!Protection_from_shape_changers && rn2(caster->m_lev) < 20) {
                spawn_mirror_image(caster, ox, oy);
            }
        }
    }
    return 0;
}

staticfn int
mcast_summon_mons(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    /* Must respect field of vision */
    if (youdefend) {
        if (!mcast_dist_ok(caster, FALSE))
            return 0;
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
    return 0;
}

staticfn int
mcast_flesh_to_stone(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean disguised_mimic = (mdef->data->mlet == S_MIMIC
                           && M_AP_TYPE(mdef) != M_AP_NOTHING);

    if (youdefend) {
        /* Limit the range to either adjacent to hero or 1 square away,
         * any more and this spell would be insane to deal with. */
        if (distu(caster->mx, caster->my) > 16 )
            return 0;
        if (!Blind)
            pline("A dense gray haze engulfs you!");
        else
            You("suddenly catch a strong scent of sulfur in the air...");
        if (Stone_resistance)
            return 0;
        urgent_pline("You start turning to stone!");
        make_stoned(5L, (char *) 0, KILLED_BY, "flesh-to-stone spell");
    } else if (mdef && !DEADMONSTER(mdef)) { /* mhitm */
        if (mdef->mstone)
            return 0; /* already turning to stone */
        if (resists_ston(mdef) || defended(mdef, AD_STON)) {
            shieldeff_mon(mdef);
            return 0;
        }
        if (disguised_mimic)
            seemimic(mdef);
        if (canseemon(mdef)) {
            pline("%s is turning to stone!", Monnam(mdef));
            if (!canspotmon(mdef))
                map_invisible(gb.bhitpos.x, gb.bhitpos.y);
        }
        if (!mdef->mstone) {
            mdef->mstone = 5;
            mdef->mstonebyu = TRUE;
        }
    }
    return 0;
}

staticfn int
mcast_make_pool(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean diggable_square;
    int pptr = -1; /* required to use the flood_space callback */

    if (youdefend) {
        /* Imported from slashem-up: Create pool spell can be affected by
         * invisibility and/or displacement. */
        boolean mon_foundu = caster->mux == u.ux || caster->muy == u.uy;

        diggable_square = zombie_can_dig(caster->mux, caster->muy);

        if (!diggable_square) {
            pline("Some water comes down from the ceiling.");
            return 0;
        } else if (Invisible && !perceives(caster->data) && !mon_foundu) {
            pline("A pool appears beneath a spot near you!");
            flood_space(caster->mux, caster->muy, (genericptr_t) &pptr);
        } else if (Displaced && !mon_foundu) {
            pline("A pool appears beneath your displaced image!");
            flood_space(caster->mux, caster->muy, (genericptr_t) &pptr);
        } else if (zombie_can_dig(u.ux, u.uy)) {
            pline("A pool appears beneath you!");
            flood_space(caster->mux, caster->muy, (genericptr_t) &pptr);
        }
        return 0;
    } else { /* mhitm */
        pptr = 1;
        if (zombie_can_dig(mdef->mx, mdef->my)) {
            if (canseemon(mdef)) {
                pline("A pool appears beneath %s!", mon_nam(mdef));
            }
            flood_space(mdef->mux, mdef->muy, (genericptr_t) &pptr);
        }
    }
    return 0;
}

staticfn int
mcast_clone_wiz(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (!youdefend)
        impossible("mcast_clone_wiz vs non-player monster.");

    if (caster->iswiz && svc.context.no_of_wizards == 1) {
        pline("Double Trouble...");
        clonewiz();
    } else
        impossible("bad wizard cloning?");
    return 0;
}

/* This spell allows the caster to create explosions on any squares that
 * have blood on them. Ported from CrecelleHack with some modifications: here
 * the range of effect is centered in a 8x8 circle around the caster and
 * the caster won't create explosions that will hit themselves.
 */
staticfn int
mcast_blood_bind(struct monst *caster, struct monst *mdef UNUSED)
{
    boolean youdefend = mdef == &gy.youmonst;
    int dist_from_caster = 0;

    if (!youdefend)
        return 0;
    if (!mcast_dist_ok(caster, FALSE))
        return 0;
    if (canseemon(caster))
        urgent_pline("%s claps %s hands together:", Monnam(caster), mhis(caster));

    verbalize("Blood bind!");

    /* Goodbye. */
    for (coordxy x = 0; x < COLNO; x++) {
        for (coordxy y = 0; y < ROWNO; y++) {
            dist_from_caster = dist2(caster->mx, caster->my, x, y);
            if (dist_from_caster > 8) /* Too far */
                continue;
            if (dist_from_caster < 3) /* Too close - hits self */
                continue;

            if (IS_BLOODY(x, y)) {
                wipe_blood(x, y);
                explode(x, y, PHYS_EXPL_TYPE, d(4, 4), 0, EXPL_MAGICAL);
            }
        }
    }
    return 0; /* Damage done by explode */
}

staticfn int
mcast_death_touch(struct monst *caster, struct monst *mdef)
{
    boolean youdefend = mdef == &gy.youmonst;
    boolean resisted;

    if (youdefend) { /* mhitu */
        pline("Oh no, %s's using the touch of death!", mhe(caster));
        if (nonliving(gy.youmonst.data)) {
            You("seem no deader than before.");
        } else if (resists_death(gy.youmonst.data)) {
            You("are unaffected.");
        } else if (uwep && uwep->oprops & ITEM_HEXING && !uwep->cursed) {
            You_feel("feel a malignant aura surround your hexed weapon");
            curse(uwep);
            update_inventory();
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
    } else if (mdef && !DEADMONSTER(mdef)) { /* mhitm */
        struct obj *mwep = MON_WEP(mdef);
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
                pline("%s %s.", Monnam(mdef), nonliving(mdef->data)
                        ? "seems no more dead than before"
                        : "is unaffected");
        } else if (mwep && mwep->oprops & ITEM_HEXING && !mwep->cursed) {
            curse(mwep);
            if (canseemon(mdef)) {
                You_see("a malignant aura surround %s %s",
                s_suffix(mon_nam(mdef)), xname(mwep));
            }
        } else if (!resisted) {
            mdef->mhp = -1;
            monkilled(mdef, "", AD_SPEL);
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
    }
    return 0;
}

/* helper function for: mcast_death_touch
 * unlike the finger of death spell which behaves like a wand of death,
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

/* helper function for: mcast_death_touch
 * give a reason for death by some monster spells */
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

/*
 * FIXME: none of these hit the steed when hero is riding.
 */
staticfn int
mgc_melee_ad_fire(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;
    const int orig_dmg = dmg; /* damage coming into the function */

    if (youdefend) {
        pline("You're enveloped in flames.");

        if (Underwater) {
            pline("The flames are quenched by the water around %s.",
                      mon_nam(mdef));
            return 0;
        }
        if (fully_resistant(FIRE_RES)) {
            shieldeff(u.ux, u.uy);
            pline("But you resist the effects.");
            monstseesu(M_SEEN_FIRE);
            dmg = 0;
        } else {
            dmg = resist_reduce(dmg, FIRE_RES);
            dehydrate(resist_reduce(rn1(150, 150), FIRE_RES));
            monstunseesu(M_SEEN_FIRE);
        }
        if ((int) caster->m_lev > rn2(20)) {
            (void) destroy_items(&gy.youmonst, AD_FIRE, orig_dmg);
            ignite_items(gi.invent);
        }
        burn_away_slime();
        /* burn up flammable items on the floor, melt ice terrain */
        mon_spell_hits_spot(caster, AD_FIRE, u.ux, u.uy);
    } else { /* mhitm */
        if (canseemon(mdef)) {
            if (mon_underwater(mdef)) {
                pline("The flames are quenched by the water around %s.",
                     mon_nam(mdef));
                return 0;
            }
            if (is_demon(caster->data))
                pline("%s is enveloped in hellfire!", Monnam(mdef));
            else
                pline("%s is enveloped in flames.", Monnam(mdef));
        }

        if (resists_fire(mdef) || defended(mdef, AD_FIRE)) {
            shieldeff(mdef->mx, mdef->my);
            if (canseemon(mdef))
                pline("But %s resists the effects.", mhe(mdef));
            dmg = 0;
        }
        dmg += destroy_items(mdef, AD_FIRE, orig_dmg);
        ignite_items(mdef->minvent);

        /* burn up flammable items on the floor, melt ice terrain */
        mon_spell_hits_spot(caster, AD_FIRE, mdef->mx, mdef->my);
    }
    return dmg;
}

staticfn int
mgc_melee_ad_cold(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;
    const int orig_dmg = dmg; /* damage coming into the function */

    if (youdefend) {
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
        if ((int) caster->m_lev > rn2(20))
            (void) destroy_items(&gy.youmonst, AD_COLD, orig_dmg);
        mon_spell_hits_spot(caster, AD_COLD, u.ux, u.uy);
    } else { /* mhitm */
        if (canseemon(mdef))
            pline("%s is covered in frost.", Monnam(mdef));
        if (resists_cold(mdef) || defended(mdef, AD_COLD)) {
            shieldeff(mdef->mx, mdef->my);
            if (canseemon(mdef))
                pline("But %s resists the effects.", mhe(mdef));
            dmg = 0;
        }
        dmg += destroy_items(mdef, AD_COLD, orig_dmg);
        mon_spell_hits_spot(caster, AD_COLD, mdef->mx, mdef->my);
    }
    return dmg;
}

staticfn int
mgc_melee_ad_elec(struct monst *caster UNUSED, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;
    const int orig_dmg = dmg; /* damage coming into the function */

    if (youdefend) {
        You("are blasted with electricity%s", exclam(dmg));
        if (Shock_resistance)
            dmg = 0;
        if (fully_resistant(SHOCK_RES)) {
            shieldeff(u.ux, u.uy);
            pline("But you resist the effects.");
            monstseesu(M_SEEN_ELEC);
        } else {
            dmg = resist_reduce(dmg, SHOCK_RES);
            monstunseesu(M_SEEN_ELEC);
        }
        ugolemeffects(AD_ELEC, orig_dmg);
        /* creates a lightning-like flash */
        (void) flashburn((long) rnd(100), TRUE);

        if ((int) caster->m_lev > rn2(10))
            (void) destroy_items(&gy.youmonst, AD_ELEC, orig_dmg);
    } else { /* mhitm */
        ; /* TODO: Implement mhitm */
    }
    return dmg;
}

staticfn int
mgc_melee_ad_magm(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;

    if (youdefend) {
        You("are hit by a shower of missiles!");

        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            pline("Some missiles bounce off!");
            dmg = (dmg + 1) / 2;
            monstseesu(M_SEEN_MAGR);
        } else
            monstunseesu(M_SEEN_MAGR);
        if (Half_spell_damage) { /* stacks with Antimagic */
            dmg -= (dmg + 1) / 4;
        }
        /* shower of magic missiles scuffs an engraving */
        mon_spell_hits_spot(caster, AD_MAGM, u.ux, u.uy);
    } else { /* mhitm */
        if (canseemon(mdef))
            pline("%s is hit by a shower of missiles!", Monnam(mdef));

        if (resists_magm(mdef) || defended(mdef, AD_MAGM)) {
            shieldeff(mdef->mx, mdef->my);
            if (canseemon(mdef))
                pline("Some missiles bounce off!");
            dmg = (dmg + 1) / 2;
        }
        /* shower of magic missiles scuffs an engraving */
        mon_spell_hits_spot(caster, AD_MAGM, mdef->mx, mdef->my);
    }
    return dmg;
}

staticfn int
mgc_melee_ad_acid(struct monst *caster, struct monst *mdef, int dmg)
{
    boolean youdefend = mdef == &gy.youmonst;
    const int orig_dmg = dmg; /* damage coming into the function */

    if (youdefend) {
        pline("You're covered in acid.");
        if (fully_resistant(ACID_RES)) {
            shieldeff(u.ux, u.uy);
            pline("But you resist the effects.");
            monstseesu(M_SEEN_ACID);
            dmg = 0;
        } else {
            dmg = resist_reduce(dmg, ACID_RES);
            monstunseesu(M_SEEN_ACID);
        }
        if ((int) caster->m_lev > rn2(20))
            (void) destroy_items(&gy.youmonst, AD_ACID, orig_dmg);

        mon_spell_hits_spot(caster, AD_ACID, u.ux, u.uy);
    } else { /* mhitm */
        if (canseemon(mdef)) {
            if (mon_underwater(mdef)) {
                pline("The acid dissipates harmlessly in the water around %s.",
                      mon_nam(mdef));
                return 0;
            } else {
                pline("%s is covered in acid.", Monnam(mdef));
            }
        }
        if (resists_acid(mdef) || defended(mdef, AD_ACID)) {
            shieldeff(mdef->mx, mdef->my);
            if (canseemon(mdef))
                pline("But %s resists the effects.", mhe(mdef));
            dmg = 0;
        }
        if (!rn2(3))
            erode_armor(mdef, ERODE_CORRODE);
        if (!rn2(6))
            acid_damage(MON_WEP(mdef));
        mon_spell_hits_spot(caster, AD_ACID, mdef->mx, mdef->my);
    }
    return dmg;
}

/*mcastu.c*/