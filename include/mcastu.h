

#define MCF_NONE        0x0000
#define MCF_INDIRECT    0x0001 /* untargeted/indirect spell */
#define MCF_SIGHT       0x0002 /* monster needs to see hero */
#define MCF_HOSTILE     0x0004 /* cast by hostile monsters only */
#define MCF_HEROONLY    0x0008 /* cast at hero only */
#define MCF_ALLOWMISS   0x0010 /* allow the spell to miss the hero */

#if defined(MCASTU_ENUM)
#define MONSPELL(def, nam, lvl, flags) MCAST_##def
#elif defined(MCASTU_INIT)
#define MONSPELL(def, nam, lvl, flags) { nam, lvl, flags }
#elif defined(DUMP_MCASTU_ENUM1)
#define MONSPELL(def, nam, lvl, flags) MCAST_DUMPENUM_##def
#elif defined(DUMP_MCASTU_ENUM2)
#define MONSPELL(def, nam, lvl, flags) { MCAST_DUMPENUM_##def, #def }
#endif

MONSPELL(PSI_BOLT,     "psi bolt",         0, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT),
MONSPELL(FIRE_BLAST,   "fire blast",       0, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(ICE_BLAST,    "ice blast",        0, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(OPEN_WOUNDS,  "open wounds",      0, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT),
MONSPELL(SPHERES,      "spheres",          0, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT | MCF_HEROONLY),
MONSPELL(CURE_SELF,    "cure self",        1, MCF_INDIRECT),
MONSPELL(DARKNESS,     "darkness",         1, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_HEROONLY),
MONSPELL(GREASE,       "grease",           1, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(BLOOD_RAIN,   "blood rain",       1, MCF_HOSTILE | MCF_INDIRECT),
MONSPELL(HASTE_MON,    "hasting",          2, MCF_INDIRECT),
MONSPELL(CONFUSE,      "confusion",        2, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(PROTECTION,   "protection",       2, MCF_INDIRECT),
MONSPELL(STUN,         "stunning force",   3, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(SLEEP,        "sleepel",          3, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(DISAPPEAR,    "invisibility",     4, MCF_INDIRECT),
MONSPELL(PARALYZE,     "hold",             4, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(VULN,         "vulnerability",    4, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT | MCF_HEROONLY),
MONSPELL(LEVITATE,     "levitation",       4, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(DISGUISE,     "disguise self",    4, MCF_HOSTILE | MCF_INDIRECT | MCF_HEROONLY),
MONSPELL(BETRAY,       "betrayal",         5, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(BLIGHT,       "blight",           5, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT),
MONSPELL(BLIND,        "blind",            6, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(WEAKEN,       "strength of newt", 6, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(EVIL_EYE,     "evil eye",         7, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT),
MONSPELL(DESTRY_ARMR,  "destroy armor",    8, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(MIRROR_IMAGE, "mirror image",     8, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT | MCF_HEROONLY),
MONSPELL(BLOOD_SPEAR,  "bloody pierce",    8, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(INSECTS,      "summon vermin",    8, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT | MCF_HEROONLY),
MONSPELL(HOBBLE,       "hobbling strike",  9, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(CURSE_ITEMS,  "curse",           10, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(REFLECTION,   "reflection",      10, MCF_INDIRECT| MCF_SIGHT),
MONSPELL(CALL_UNDEAD,  "call undead",     10, MCF_HOSTILE | MCF_SIGHT | MCF_HEROONLY),
MONSPELL(DISENCHANT,   "disenchant",      10, MCF_HOSTILE | MCF_SIGHT),
MONSPELL(LIGHTNING,    "lightning bolt",  11, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(FIRE_PILLAR,  "divine wrath",    12, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(SUMMON_MINION,"summon minion",   12, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT),
MONSPELL(ENTOMB,       "summon wall",     12, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_HEROONLY),
MONSPELL(GEYSER,       "geyser",          13, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(MAKE_POOL,    "make pool",       13, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(AGGRAVATION,  "aggravation",     13, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT | MCF_HEROONLY),
MONSPELL(ACID_BLAST,   "acid blast",      14, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT | MCF_ALLOWMISS),
MONSPELL(BLOOD_BIND,   "blood bind",      14, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT),
MONSPELL(TELEPORT,     "teleport",        15, MCF_INDIRECT | MCF_HEROONLY),
MONSPELL(SUMMON_MONS,  "summon nasties",  15, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT | MCF_HEROONLY),
MONSPELL(FLESH_TO_STONE, "flesh to stone",16, MCF_HOSTILE | MCF_SIGHT | MCF_INDIRECT),
MONSPELL(CLONE_WIZ,    "simulacrum",      18, MCF_HOSTILE | MCF_INDIRECT | MCF_SIGHT | MCF_HEROONLY),
MONSPELL(DEATH_TOUCH,  "death magic",     20, MCF_HOSTILE | MCF_SIGHT),

#undef MONSPELL
