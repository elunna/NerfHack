/* NetHack 3.7	sym.h */
/*      Copyright (c) 2016 by Pasi Kallinen              */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef SYM_H
#define SYM_H

/*
 * Default characters for monsters.
 */
/* clang-format off */
enum mon_defchars {
#define MONSYMS_DEFCHAR_ENUM
#include "defsym.h"
#undef MONSYMS_DEFCHAR_ENUM
};
/* clang-format on */

enum mon_syms {
#define MONSYMS_S_ENUM
#include "defsym.h"
#undef MONSYMS_S_ENUM

    MAXMCLASSES  /* number of monster classes */
};

#ifndef MAKEDEFS_C
/* Default characters for dungeon surroundings and furniture */
enum cmap_symbols {
#define PCHAR_S_ENUM
#include "defsym.h"
#undef PCHAR_S_ENUM
    MAXPCHARS
};

/*
 * special symbol set handling types ( for invoking callbacks, etc.)
 * Must match the order of the known_handlers strings
 * in drawing.c
 */

enum symset_handling_types {
    H_UNK = 0,
    H_IBM = 1,
    H_DEC = 2,
    H_CURS = 3,
    H_MAC = 4, /* obsolete; needed so that the listing of available
                * symsets by 'O' can skip it for !MAC_GRAPHICS_ENV */
    H_UTF8 = 5
};

struct symdef {
    uchar sym;
    const char *explanation;
    uchar color;
};

enum symparse_range {
    SYM_INVALID = 0,
    SYM_CONTROL = 1, /* start/finish markers */
    SYM_PCHAR = 2,   /* index into showsyms  */
    SYM_OC = 3,      /* index into oc_syms   */
    SYM_MON = 4,     /* index into monsyms   */
    SYM_OTH = 5      /* misc                 */
};

struct symparse {
    enum symparse_range range;
    int idx;
    const char *name;
};

/* linked list of symsets and their characteristics */
struct symsetentry {
    struct symsetentry *next; /* next in list                         */
    char *name;               /* ptr to symset name                   */
    char *desc;               /* ptr to description                   */
    int idx;                  /* an index value                       */
    enum symset_handling_types handling;      /* known handlers value */
    Bitfield(nocolor, 1);     /* don't use color if set               */
    Bitfield(primary, 1);     /* restricted for use as primary set    */
    Bitfield(rogue, 1);       /* restricted for use as rogue lev set  */
    Bitfield(explicitly, 1);  /* explicit symset set                  */
                              /* 4 free bits */
};

/*
 *
 */

#define MAXDCHARS (S_water - S_stone + 1) /* mapped dungeon characters */
#define MAXTCHARS (TRAPNUM - 1) /* trap chars */
#define MAXECHARS (S_expl_br - S_vbeam + 1) /* mapped effects characters */
#define MAXEXPCHARS 9 /* number of explosion characters */

#define DARKROOMSYM (Is_rogue_level(&u.uz) ? S_stone : S_darkroom)

#define is_cmap_trap(i) ((i) >= S_arrow_trap && (i) < S_arrow_trap + MAXTCHARS)
#define is_cmap_drawbridge(i) ((i) >= S_vodbridge && (i) <= S_hcdbridge)
#define is_cmap_door(i) ((i) >= S_vodoor && (i) <= S_hcdoor)
#define is_cmap_wall(i) ((i) >= S_stone && (i) <= S_trwall)
#define is_cmap_room(i) ((i) >= S_room && (i) <= S_darkroom)
#define is_cmap_corr(i) ((i) >= S_corr && (i) <= S_litcorr)
#define is_cmap_furniture(i) ((i) >= S_upstair && (i) <= S_fountain)
#define is_cmap_water(i) ((i) == S_pool || (i) == S_water)
#define is_cmap_lava(i) ((i) == S_lava || (i) == S_lavawall)
#define is_cmap_stairs(i) ((i) >= S_upstair && (i) <= S_brdnladder)

/* misc symbol definitions */
enum misc_symbols {
        SYM_NOTHING = 0,
        SYM_UNEXPLORED = 1,
        SYM_BOULDER = 2,
        SYM_INVISIBLE = 3,
        SYM_PET_OVERRIDE = 4,
        SYM_HERO_OVERRIDE = 5,
        MAXOTHER
};

/*
 * Graphics sets for display symbols
 */
#define DEFAULT_GRAPHICS 0 /* regular characters: '-', '+', &c */
enum graphics_sets {
        PRIMARYSET = 0,       /* primary graphics set        */
        ROGUESET = 1,         /* rogue graphics set          */
        NUM_GRAPHICS,
        UNICODESET = NUM_GRAPHICS
};

enum do_customizations {
       do_custom_none,
       do_custom_colors,
       do_custom_symbols
};

enum customization_types { custom_none, custom_symbols,
    custom_ureps, custom_nhcolor,  custom_count };

struct custom_symbol {
    const struct symparse *symparse;
    unsigned char val;
};
struct custom_urep {
    int glyphidx;
    struct unicode_representation u;
};
struct custom_nhcolor {
    int glyphidx;
    uint32 nhcolor;
};
union customization_content {
    struct custom_symbol sym;
    struct custom_urep urep;
    struct custom_nhcolor ccolor;
};
struct customization_detail {
    union customization_content content;
    struct customization_detail *next;
};


/* one set per symset_name */
struct symset_customization {
    const char *customization_name;
    int count;
    enum customization_types custtype;
    struct customization_detail *details;
    struct customization_detail *details_end;
};

extern const struct symdef defsyms[MAXPCHARS + 1]; /* defaults */
#define WARNCOUNT 6 /* number of different warning levels */
extern const struct symdef def_warnsyms[WARNCOUNT];
#define SYMHANDLING(ht) (gs.symset[gc.currentgraphics].handling == (ht))

#endif /* !MAKEDEFS_C */
#endif /* SYM_H */

