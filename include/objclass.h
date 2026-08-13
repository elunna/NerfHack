/* NetHack 3.7	objclass.h	$NHDT-Date: 1596498553 2020/08/03 23:49:13 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.22 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Pasi Kallinen, 2018. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef OBJCLASS_H
#define OBJCLASS_H

/* [misnamed] definition of a type of object; many objects are composites
   (liquid potion inside glass bottle, metal arrowhead on wooden shaft)
   and object definitions only specify one type on a best-fit basis */
enum obj_material_types {
    NO_MATERIAL =  0,
    LIQUID      =  1, /* currently only for venom */
    WAX         =  2,
    VEGGY       =  3, /* foodstuffs */
    FLESH       =  4, /*   ditto    */
    PAPER       =  5,
    CLOTH       =  6,
    LEATHER     =  7,
    WOOD        =  8,
    BONE        =  9,
    CHITON      = 10,
    DRAGON_HIDE = 11, /* not leather! */
    IRON        = 12, /* Fe - includes steel */
    COLDSTEEL   = 13, /* Iron that has been cold-forged */
    METAL       = 14, /* Sn, &c. */
    COPPER      = 15, /* Cu - includes brass */
    SILVER      = 16, /* Ag */
    GOLD        = 17, /* Au */
    PLATINUM    = 18, /* Pt */
    MITHRIL     = 19,
    PLASTIC     = 20,
    GLASS       = 21,
    GEMSTONE    = 22,
    MINERAL     = 23
};

#define NUM_MATERIAL_TYPES MINERAL
#define MATERIAL_PROB_TOTAL 1000

enum obj_armor_types {
    ARM_SUIT   = 0,
    ARM_SHIELD = 1,        /* needed for special wear function */
    ARM_HELM   = 2,
    ARM_GLOVES = 3,
    ARM_BOOTS  = 4,
    ARM_CLOAK  = 5,
    ARM_SHIRT  = 6
};

struct objclass {
    short oc_name_idx;              /* index of actual name */
    short oc_descr_idx;             /* description when name unknown */
    char *oc_uname;                 /* called by user */
    Bitfield(oc_name_known, 1);     /* discovered */
    Bitfield(oc_merge, 1);          /* merge otherwise equal objects */
    Bitfield(oc_uses_known, 1);     /* obj->known affects full description;
                                     * otherwise, obj->dknown and obj->bknown
                                     * tell all, and obj->known should always
                                     * be set for proper merging behavior. */
    Bitfield(oc_encountered, 1);    /* hero has observed such an item at least
                                       once (perhaps without naming it) */
    Bitfield(oc_magic, 1);          /* inherently magical object */
    Bitfield(oc_charged, 1);        /* may have +n or (n) charges */
    Bitfield(oc_unique, 1);         /* special one-of-a-kind object */
    Bitfield(oc_nowish, 1);         /* cannot wish for this object */

    Bitfield(oc_big, 1);
#define oc_bimanual oc_big /* for weapons & tools used as weapons */
#define oc_bulky oc_big    /* for armor */
    Bitfield(oc_tough, 1); /* hard gems/rings */

    Bitfield(oc_spare1, 6);         /* padding to align oc_dir + oc_material;
                                     * can be cannibalized for other use;
                                     * aka 6 free bits */

    Bitfield(oc_dir, 3);
    /* oc_dir: zap style for wands and spells */
#define NODIR     1 /* non-directional */
#define IMMEDIATE 2 /* directional beam that doesn't ricochet */
#define RAY       3 /* beam that does bounce off walls */
    /* overloaded oc_dir: strike mode bit mask for weapons and weptools */
#define PIERCE   1 /* pointed weapon punctures target */
#define SLASH    2 /* sharp weapon cuts target */
#define WHACK    4 /* blunt weapon bashes target */

#define is_pierce(otmp) (objects[otmp->otyp].oc_dir == PIERCE)
#define is_slash(otmp) (objects[otmp->otyp].oc_dir == SLASH)
#define is_whack(otmp) (objects[otmp->otyp].oc_dir == WHACK)

    Bitfield(oc_material, 5); /* one of obj_material_types */

    schar oc_subtyp;
#define oc_skill oc_subtyp  /* Skills of weapons, spellbooks, tools, gems */
#define oc_armcat oc_subtyp /* for armor (enum obj_armor_types) */

    uchar oc_oprop; /* property (invis, &c.) conveyed */
    char  oc_class; /* object class (enum obj_class_types) */
    schar oc_delay; /* delay when using such an object */
    uchar oc_color; /* color of the object */

    short oc_prob;            /* probability, used in mkobj() */
    unsigned short oc_weight; /* encumbrance (1 cn = 0.1 lb.) */
    short oc_cost;            /* base cost in shops */
    /* Check the AD&D rules!  The FIRST is small monster damage. */
    /* for weapons, and tools, rocks, and gems useful as weapons */
    schar oc_wsdam, oc_wldam; /* max small/large monster damage */
    schar oc_oc1, oc_oc2;
#define oc_hitbon oc_oc1 /* weapons: "to hit" bonus */

#define a_ac oc_oc1     /* armor class, used in armor_bonus in worn.c */
#define a_can oc_oc2    /* armor: used in mhitu.c */
#define oc_level oc_oc2 /* books: spell level */

    unsigned short oc_nutrition; /* food value */
};

struct class_sym {
    char sym;
    const char *name;
    const char *explain;
};

struct objdescr {
    const char *oc_name;  /* actual name */
    const char *oc_descr; /* description when name unknown */
};

/*
 * All objects have a class. Make sure that all classes have a corresponding
 * symbol below.
 */

enum objclass_defchars {
#define OBJCLASS_DEFCHAR_ENUM
#include "defsym.h"
#undef OBJCLASS_DEFCHAR_ENUM
};

enum objclass_classes {
    RANDOM_CLASS =  0, /* used for generating random objects */
#define OBJCLASS_CLASS_ENUM
#include "defsym.h"
#undef OBJCLASS_CLASS_ENUM
    MAXOCLASSES
};

/* Default characters for object classes */
enum objclass_syms {
#define OBJCLASS_S_ENUM
#include "defsym.h"
#undef OBJCLASS_S_ENUM
};

/* for mkobj() use ONLY! odd '-SPBOOK_CLASS' is in case of unsigned enums */
#define SPBOOK_no_NOVEL (0 - (int) SPBOOK_CLASS)

#define BURNING_OIL     (MAXOCLASSES + 1) /* Can be used as input to explode.   */
#define MON_EXPLODE     (MAXOCLASSES + 2) /* Exploding monster (e.g. gas spore) */
#define DOOR_TRAP       (MAXOCLASSES + 3) /* Exploding booby-trapped doors (GruntHack) */
#define MON_CASTBALL    (MAXOCLASSES + 4) /* For monsters casting area-effect spells    */
#define FORGE_EXPLODE   (MAXOCLASSES + 5) /* Exploding forges */
#define TRAP_EXPLODE    (MAXOCLASSES + 6) /* Exploding magical trap due to cancellation */

#if 0 /* moved to decl.h so that makedefs.c won't see them */
extern const struct class_sym
        def_oc_syms[MAXOCLASSES];       /* default class symbols */
extern uchar oc_syms[MAXOCLASSES];      /* current class symbols */
#endif

struct fruit {
    char fname[PL_FSIZ];
    int fid;
    struct fruit *nextf;
};
#define newfruit() (struct fruit *) alloc(sizeof(struct fruit))
#define dealloc_fruit(rind) free((genericptr_t)(rind))

enum objects_nums {
#define OBJECTS_ENUM
#include "objects.h"
#undef OBJECTS_ENUM
    NUM_OBJECTS
};

enum misc_object_nums {
    NUM_REAL_GEMS  = (LAST_REAL_GEM - FIRST_REAL_GEM + 1),
    NUM_GLASS_GEMS = (LAST_GLASS_GEM - FIRST_GLASS_GEM + 1),
    /* LAST_SPELL is SPE_BLANK_PAPER, guaranteeing that spl_book[] will
       have at least one unused slot at end to be used as a terminator */
    MAXSPELL       = (LAST_SPELL - FIRST_SPELL + 1),
};

extern NEARDATA struct objclass objects[NUM_OBJECTS + 1];
extern NEARDATA struct objdescr obj_descr[NUM_OBJECTS + 1];

#define OBJ_NAME(obj) (obj_descr[(obj).oc_name_idx].oc_name)
#define OBJ_DESCR(obj) (obj_descr[(obj).oc_descr_idx].oc_descr)

#define is_organic(otmp) ((otmp)->material <= WOOD)
#define is_metallic(otmp)                    \
    ((otmp)->material >= IRON && (otmp)->material <= MITHRIL)
#define is_heavy_metallic(otmp)                    \
    ((otmp)->material >= IRON && (otmp)->material <= PLATINUM)

/* primary damage: fire/rust/--- */
/* is_flammable(otmp), is_rottable(otmp) in mkobj.c */
#define is_rustprone(otmp) ((otmp)->material == IRON \
        || (otmp)->material == METAL \
        || (otmp)->material == COLDSTEEL)
/* note: is_crackable doesn't need to include weptools because none of them can
 * generate as glass */
#define is_crackable(otmp) \
    ((otmp)->bquality == FQ_INFERIOR         \
    || ((otmp)->material == GLASS            \
     && ((otmp)->oclass == ARMOR_CLASS       \
         || (otmp)->oclass == AMULET_CLASS   \
         || (otmp)->oclass == RING_CLASS     \
         || (otmp)->oclass == WAND_CLASS)))  /* erosion_matters() */
/* secondary damage: rot/acid/acid */
#define is_corrodeable(otmp)                   \
    ((otmp)->material == COPPER || (otmp)->material == SILVER \
     || (otmp)->material == IRON)
/* inherently fooproof */
#define is_supermaterial(otmp) \
    ((otmp)->material == DRAGON_HIDE || (otmp)->material == MITHRIL \
    || otmp->material == GOLD || otmp->material == PLATINUM \
    || otmp->material == GEMSTONE)
/* subject to any damage */
#define is_damageable(otmp) \
    (is_rustprone(otmp) || is_flammable(otmp)           \
     || is_rottable(otmp) || is_corrodeable(otmp)       \
     || is_crackable(otmp))
#define is_silver(otmp) ((otmp)->material == SILVER \
    || otmp->otyp == SILVER_DRAGON_SCALES)
#define is_bone(otmp) ((otmp)->material == BONE)
#define is_chiton(otmp) ((otmp)->material == CHITON)
#define is_glass(otmp) ((otmp)->material == GLASS)
#define is_plastic(otmp) ((otmp)->material == PLASTIC)
#define is_fragile(otmp) ((is_glass(otmp) && (otmp)->oclass != GEM_CLASS) \
    || (otmp)->otyp == EXPENSIVE_CAMERA \
    || (otmp)->otyp == EGG \
    || (otmp)->otyp == CREAM_PIE \
    || (otmp)->otyp == MELON)
#define is_bulky(otmp) (objects[otmp->otyp].oc_bulky)

/* Force rendering of materials on certain items where the object name
 * wouldn't make as much sense without a material (e.g. "leather jacket" vs
 * "jacket"), or those where the default material is non-obvious.
 * NB: GLOVES have a randomized description when not identified; "leather
 * padded gloves" would give the game away if we did not check their
 * identification status */
#define force_material_name(typ) \
((typ) == ARMOR || (typ) == STUDDED_ARMOR || (typ) == JACKET \
|| (typ) == CLOAK || (typ) == FIGURINE || (typ) == STATUE \
|| ((typ) == GLOVES && objects[GLOVES].oc_name_known))
/* has a fuzzed weight */
#define is_fuzzy_weight(otmp) \
((otmp->oclass == WEAPON_CLASS || otmp->oclass == ARMOR_CLASS \
|| is_weptool(otmp)) && !(objects[otmp->otyp].oc_merge || otmp->nomerge || is_ammo(otmp)))

#endif /* OBJCLASS_H */
