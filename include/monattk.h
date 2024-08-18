/* NetHack 3.7	monattk.h	$NHDT-Date: 1596498548 2020/08/03 23:49:08 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.13 $ */
/* NetHack may be freely redistributed.  See license for details. */
/* Copyright 1988, M. Stephenson */

#ifndef MONATTK_H
#define MONATTK_H

/*      Add new attack types below - ordering affects experience (exper.c).
 *      Attacks > AT_BUTT are worth extra experience.
 */
#define AT_ANY (-1) /* fake attack; dmgtype_fromattack wildcard */
#define AT_NONE 0   /* passive monster (ex. acid blob) */
#define AT_CLAW 1   /* claw (punch, hit, etc.) */
#define AT_BITE 2   /* bite */
#define AT_KICK 3   /* kick */
#define AT_BUTT 4   /* head butt (ex. a unicorn) */
#define AT_TUCH 5   /* touches */
#define AT_STNG 6   /* sting */
#define AT_HUGS 7   /* crushing bearhug */
#define AT_SPIT 8  /* spits substance - ranged */
#define AT_ENGL 9  /* engulf (swallow or by a cloud) */
#define AT_BREA 10  /* breath - ranged */
#define AT_EXPL 11  /* explodes - proximity */
#define AT_BOOM 12  /* explodes when killed */
#define AT_GAZE 13  /* gaze - ranged */
#define AT_TENT 14  /* tentacles */

#define AT_WEAP 15 /* uses weapon */
#define AT_MAGC 16 /* uses magic spell(s) */

#define LAST_AT AT_MAGC

#define DISTANCE_ATTK_TYPE(atyp) ((atyp) == AT_SPIT \
                                  || (atyp) == AT_BREA \
                                  || (atyp) == AT_MAGC \
                                  || (atyp) == AT_GAZE)

/*      Add new damage types below.
 *
 *      Note that 1-10 correspond to the types of attack used in buzz().
 *      Please don't disturb the order unless you rewrite the buzz() code.
 */
#define AD_ANY (-1) /* fake damage; attacktype_fordmg wildcard */
#define AD_PHYS 0   /* ordinary physical */
#define AD_MAGM 1   /* magic missiles */
/* Beginning of partial resistances: order is important.
 * See explode.c and monattk.h */
#define AD_FIRE 2   /* fire damage */
#define AD_COLD 3   /* frost damage */
#define AD_SLEE 4   /* sleep ray */
#define AD_DISN 5   /* disintegration (death ray) */
#define AD_ELEC 6   /* shock damage */
#define AD_DRST 7   /* drains str (poison) */
/* End of partial resistances */
#define AD_ACID 8   /* acid damage */
#define AD_DRLI 9   /* drains life levels (Vampire) */
#define AD_STUN 10  /* stun damage */
#define AD_BLND 11  /* blinds (yellow light) */
#define AD_SLOW 12  /* slows */
#define AD_PLYS 13  /* paralyses */
#define AD_DREN 14  /* drains magic energy */
#define AD_LEGS 15  /* damages legs (xan) */
#define AD_STON 16  /* petrifies (Medusa, cockatrice) */
#define AD_STCK 17  /* sticks to you (mimic) */
#define AD_SGLD 18  /* steals gold (leppie) */
#define AD_SITM 19  /* steals item (nymphs) */
#define AD_SEDU 20  /* seduces & steals multiple items */
#define AD_TLPT 21  /* teleports you (Quantum Mech.) */
#define AD_RUST 22  /* rusts armour (Rust Monster)*/
#define AD_CONF 23  /* confuses (Umber Hulk) */
#define AD_DGST 24  /* digests opponent (trapper, etc.) */
#define AD_HEAL 25  /* heals opponent's wounds (nurse) */
#define AD_WRAP 26  /* special "stick" for eels */
#define AD_WERE 27  /* confers lycanthropy */
#define AD_DRDX 28  /* drains dexterity (quasit) */
#define AD_DRCO 29  /* drains constitution */
#define AD_DRIN 30  /* drains intelligence (mind flayer) */
#define AD_DISE 31  /* confers diseases */
#define AD_DCAY 32  /* decays organics (brown Pudding) */
#define AD_SSEX 33  /* Succubus seduction (extended) */
#define AD_HALU 34  /* causes hallucination */
#define AD_DETH 35  /* for Death only */
#define AD_PEST 36  /* for Pestilence only */
#define AD_FAMN 37  /* for Famine only */
#define AD_SLIM 38  /* turns you into green slime */
#define AD_ENCH 39  /* remove enchantment (disenchanter) */
#define AD_CORR 40  /* corrode armor (black pudding) */
#define AD_POLY 41  /* polymorph the target (genetic engineer) */
#define AD_WTHR 42  /* withering (from xNetHack/EvilHack, for mummies) */
#define AD_TCKL 43  /* tickle (from SLASH'EM, for nightgaunts) */
#define AD_DSRM 44  /* disarm the player (from SpliceHack) */
#define AD_WEBS 45  /* entangles target in webbing (from EvilHack) */
#define AD_LUCK 46  /* drain luck */
#define AD_RABD 47  /* cause rabies */
#define AD_CLRC 48  /* random clerical spell */
#define AD_SPEL 49  /* random magic spell */
#define AD_RBRE 50  /* random breath weapon */

#define AD_SAMU 51  /* hits, may steal Amulet (Wizard) */
#define AD_CURS 52  /* random curse (ex. gremlin) */

#define LAST_AD AD_CURS

struct mhitm_data {
    int damage;
    int hitflags; /* M_ATTK_DEF_DIED | M_ATTK_AGR_DIED | ... */
    boolean done;
    boolean permdmg;
    int specialdmg;
    int dieroll;
};

/*
 *  Monster to monster attacks.  When a monster attacks another (mattackm),
 *  any or all of the following can be returned.  See mattackm() for more
 *  details.
 */
#define M_ATTK_MISS 0x0     /* aggressor missed */
#define M_ATTK_HIT 0x1      /* aggressor hit defender */
#define M_ATTK_DEF_DIED 0x2 /* defender died */
#define M_ATTK_AGR_DIED 0x4 /* aggressor died */
#define M_ATTK_AGR_DONE 0x8 /* aggressor is done with their turn */

#endif /* MONATTK_H */
