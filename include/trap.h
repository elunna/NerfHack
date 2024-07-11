/* NetHack 3.7	trap.h	$NHDT-Date: 1670316586 2022/12/06 08:49:46 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.31 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Pasi Kallinen, 2016. */
/* NetHack may be freely redistributed.  See license for details. */

/* note for 3.1.0 and later: no longer manipulated by 'makedefs' */

#ifndef TRAP_H
#define TRAP_H

union vlaunchinfo {
    short v_launch_otyp; /* type of object to be triggered */
    coord v_launch2;     /* secondary launch point (for boulders) */
    uchar v_conjoined;   /* conjoined pit locations */
    short v_tnote;       /* boards: 12 notes        */
};

struct trap {
    struct trap *ntrap;
    coordxy tx, ty;
    d_level dst; /* destination for portals/holes/trapdoors */
    coord launch;
#define teledest launch /* x,y destination for teleport traps, if > 0 */
    Bitfield(ttyp, 5);
    Bitfield(tseen, 1);
    Bitfield(once, 1);
    Bitfield(madeby_u, 1); /* So monsters may take offence when you trap
                            * them.  Recognizing who made the trap isn't
                            * completely unreasonable, everybody has
                            * their own style.  This flag is also needed
                            * when you untrap a monster.  It would be too
                            * easy to make a monster peaceful if you could
                            * set a trap for it and then untrap it. */
    union vlaunchinfo vl;
#define launch_otyp vl.v_launch_otyp
#define launch2 vl.v_launch2
#define conjoined vl.v_conjoined
#define tnote vl.v_tnote
};

#define newtrap() (struct trap *) alloc(sizeof(struct trap))
#define dealloc_trap(trap) free((genericptr_t)(trap))

/* reasons for statue animation */
#define ANIMATE_NORMAL 0
#define ANIMATE_SHATTER 1
#define ANIMATE_SPELL 2

/* reasons for animate_statue's failure */
#define AS_OK 0            /* didn't fail */
#define AS_NO_MON 1        /* makemon failed */
#define AS_MON_IS_UNIQUE 2 /* statue monster is unique */

/* Note: if adding/removing a trap, adjust trap_engravings[] in mklev.c */

/* unconditional traps */
enum trap_types {
    ALL_TRAPS    = -1, /* mon_knows_traps(), mon_learns_traps() */
    NO_TRAP      =  0,
    ARROW_TRAP   =  1,
    DART_TRAP    =  2,
    ROCKTRAP     =  3,
    SQKY_BOARD   =  4,
    BEAR_TRAP    =  5,
    LANDMINE     =  6,
    ROLLING_BOULDER_TRAP = 7,
    SLP_GAS_TRAP =  8,
    RUST_TRAP    =  9,
    GREASE_TRAP  = 10,
    FIRE_TRAP    = 11,
    COLD_TRAP    = 12,
    PIT          = 13,
    SPIKED_PIT   = 14,
    HOLE         = 15,
    TRAPDOOR     = 16,
    TELEP_TRAP   = 17,
    LEVEL_TELEP  = 18,
    MAGIC_PORTAL = 19,
    WEB          = 20,
    STATUE_TRAP  = 21,
    MAGIC_TRAP   = 22,
    ANTI_MAGIC   = 23,
    POLY_TRAP    = 24,
    MAGIC_BEAM_TRAP  = 25,
    SPEAR_TRAP  = 26,
    VIBRATING_SQUARE = 27, /* not a trap but shown/remembered as if one
                            * once it has been discovered */

    /* trapped door and trapped chest aren't traps on the map, but they
       might be shown/remembered as such after trap detection until hero
       comes in view of them and sees the feature or object;
       key-using or door-busting monsters who survive a door trap learn
       to avoid other such doors [not implemented] */
    TRAPPED_DOOR = 28, /* part of door; not present on map as a trap */
    TRAPPED_CHEST = 29, /* part of object; not on map */

    TRAPNUM = 30
};

/* some trap-related function return results */
enum trap_result {
    Trap_Effect_Finished = 0,
    Trap_Is_Gone = 0,
    Trap_Caught_Mon = 1,
    Trap_Killed_Mon = 2,
    Trap_Moved_Mon = 3, /* new location, or new level */
};

/* return codes from immune_to_trap() */
enum trap_immunities {
    TRAP_NOT_IMMUNE = 0,
    TRAP_CLEARLY_IMMUNE = 1,
    TRAP_HIDDEN_IMMUNE = 2,
};


#define is_pit(ttyp) ((ttyp) == PIT || (ttyp) == SPIKED_PIT)
#define is_hole(ttyp)  ((ttyp) == HOLE || (ttyp) == TRAPDOOR)
#define unhideable_trap(ttyp) ((ttyp) == HOLE) /* visible traps */
#define undestroyable_trap(ttyp) ((ttyp) == MAGIC_PORTAL         \
                                  || (ttyp) == VIBRATING_SQUARE)
#define is_magical_trap(ttyp) ((ttyp) == TELEP_TRAP     \
                               || (ttyp) == LEVEL_TELEP \
                               || (ttyp) == MAGIC_TRAP  \
                               || (ttyp) == ANTI_MAGIC  \
                               || (ttyp) == MAGIC_BEAM_TRAP \
                               || (ttyp) == POLY_TRAP)
/* "transportation" traps */
#define is_xport(ttyp) ((ttyp) >= TELEP_TRAP && (ttyp) <= MAGIC_PORTAL)
#define fixed_tele_trap(t) ((t)->ttyp == TELEP_TRAP \
                            && isok((t)->teledest.x,(t)->teledest.y))

#endif /* TRAP_H */
