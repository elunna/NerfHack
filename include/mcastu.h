

#define MCF_NONE     0x0000
#define MCF_INDIR 0x0001 /* untargeted/indirect spell */
#define MCF_SEE    0x0002 /* monster needs to see hero */
#define MCF_HOST  0x0004 /* cast by hostile monsters only */
#define MCF_HERO  0x0008 /* cast at hero only */
#define MCF_MIS  0x0010 /* allow the spell to miss the hero */

#if defined(MCASTU_ENUM)
#define MONSPELL(def, nam, lvl, flags) MCAST_##def
#elif defined(MCASTU_INIT)
#define MONSPELL(def, nam, lvl, flags) { nam, lvl, flags }
#elif defined(DUMP_MCASTU_ENUM1)
#define MONSPELL(def, nam, lvl, flags) MCAST_DUMPENUM_##def
#elif defined(DUMP_MCASTU_ENUM2)
#define MONSPELL(def, nam, lvl, flags) { MCAST_DUMPENUM_##def, #def }
#endif

MONSPELL(PSI_BOLT,     "psi bolt",         0, MCF_HOST | MCF_SEE | MCF_INDIR),
MONSPELL(FIRE_BLAST,   "fire blast",       0, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_MIS),
MONSPELL(ICE_BLAST,    "ice blast",        0, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_MIS),
MONSPELL(OPEN_WOUNDS,  "open wounds",      0, MCF_HOST | MCF_SEE | MCF_INDIR),
MONSPELL(SPHERES,      "spheres",          0, MCF_HOST | MCF_INDIR | MCF_SEE | MCF_HERO),
MONSPELL(CURE_SELF,    "cure self",        1, MCF_INDIR),
MONSPELL(DARKNESS,     "darkness",         1, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_HERO),
MONSPELL(GREASE,       "grease",           1, MCF_HOST | MCF_SEE),
MONSPELL(BLOOD_RAIN,   "blood rain",       1, MCF_HOST | MCF_INDIR),
MONSPELL(HASTE_MON,    "hasting",          2, MCF_INDIR),
MONSPELL(CONFUSE,      "confusion",        2, MCF_HOST | MCF_SEE),
MONSPELL(PROTECTION,   "protection",       2, MCF_INDIR),
MONSPELL(STUN,         "stunning force",   3, MCF_HOST | MCF_SEE),
MONSPELL(SLEEP,        "sleepel",          3, MCF_HOST | MCF_SEE),
MONSPELL(DISAPPEAR,    "invisibility",     4, MCF_INDIR),
MONSPELL(PARALYZE,     "hold",             4, MCF_HOST | MCF_SEE),
MONSPELL(VULN,         "vulnerability",    4, MCF_HOST | MCF_INDIR | MCF_SEE),
MONSPELL(LEVITATE,     "levitation",       4, MCF_HOST | MCF_SEE),
MONSPELL(DISGUISE,     "disguise self",    4, MCF_HOST | MCF_INDIR | MCF_HERO),
MONSPELL(BETRAY,       "betrayal",         5, MCF_HOST | MCF_SEE),
MONSPELL(BLIGHT,       "blight",           5, MCF_HOST | MCF_INDIR | MCF_SEE),
MONSPELL(BLIND,        "blind",            6, MCF_HOST | MCF_SEE),
MONSPELL(WEAKEN,       "strength of newt", 6, MCF_HOST | MCF_SEE),
MONSPELL(EVIL_EYE,     "evil eye",         7, MCF_HOST | MCF_SEE | MCF_INDIR),
MONSPELL(DESTRY_ARMR,  "destroy armor",    8, MCF_HOST | MCF_SEE),
MONSPELL(MIRROR_IMAGE, "mirror image",     8, MCF_HOST | MCF_INDIR | MCF_SEE | MCF_HERO),
MONSPELL(BLOOD_SPEAR,  "bloody pierce",    8, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_MIS),
MONSPELL(INSECTS,      "summon vermin",    8, MCF_HOST | MCF_INDIR | MCF_SEE | MCF_HERO),
MONSPELL(HOBBLE,       "hobbling strike",  9, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_MIS),
MONSPELL(CURSE_ITEMS,  "curse",           10, MCF_HOST | MCF_SEE),
MONSPELL(REFLECTION,   "reflection",      10, MCF_INDIR| MCF_SEE),
MONSPELL(CALL_UNDEAD,  "call undead",     10, MCF_HOST | MCF_SEE | MCF_HERO),
MONSPELL(DISENCHANT,   "disenchant",      10, MCF_HOST | MCF_SEE),
MONSPELL(LIGHTNING,    "lightning bolt",  11, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_MIS),
MONSPELL(FIRE_PILLAR,  "divine wrath",    12, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_MIS),
MONSPELL(SUMMON_MINION,"summon minion",   12, MCF_HOST | MCF_SEE | MCF_INDIR),
MONSPELL(ENTOMB,       "summon wall",     12, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_HERO),
MONSPELL(GEYSER,       "geyser",          13, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_MIS),
MONSPELL(MAKE_POOL,    "make pool",       13, MCF_HOST | MCF_SEE | MCF_MIS),
MONSPELL(AGGRAVATION,  "aggravation",     13, MCF_HOST | MCF_INDIR | MCF_SEE | MCF_HERO),
MONSPELL(ACID_BLAST,   "acid blast",      14, MCF_HOST | MCF_SEE | MCF_INDIR | MCF_MIS),
MONSPELL(BLOOD_BIND,   "blood bind",      14, MCF_HOST | MCF_INDIR | MCF_SEE),
MONSPELL(TELEPORT,     "teleport",        15, MCF_INDIR | MCF_HERO),
MONSPELL(SUMMON_MONS,  "summon nasties",  15, MCF_HOST | MCF_INDIR | MCF_SEE | MCF_HERO),
MONSPELL(FLESH_TO_STONE, "flesh to stone",16, MCF_HOST | MCF_SEE | MCF_INDIR),
MONSPELL(CLONE_WIZ,    "simulacrum",      18, MCF_HOST | MCF_INDIR | MCF_SEE | MCF_HERO),
MONSPELL(DEATH_TOUCH,  "death magic",     20, MCF_HOST | MCF_SEE),

#undef MONSPELL
