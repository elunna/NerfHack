/* NetHack 3.7  artilist.h      $NHDT-Date: 1710957374 2024/03/20 17:56:14 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.30 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2017. */
/* NetHack may be freely redistributed.  See license for details. */

#if defined(MAKEDEFS_C) || defined (MDLIB_C)
/* in makedefs.c, all we care about is the list of names */

#define A(nam, typ, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac, \
          cost, clr, bn) nam

static const char *const artifact_names[] = {

#elif defined(ARTI_ENUM)
#define A(nam, typ, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac, \
          cost, clr, bn)                                         \
    ART_##bn

#elif defined(DUMP_ARTI_ENUM)
#define A(nam, typ, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac, \
          cost, clr, bn)                                         \
    { ART_##bn, "ART_" #bn }
#else
/* in artifact.c, set up the actual artifact list structure;
   color field is for an artifact when it glows, not for the item itself */

#define A(nam, typ, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac, \
          cost, clr, bn)                                         \
    {                                                            \
        typ, nam, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac,   \
        cost, clr                                                \
    }

/* clang-format off */
#define     NO_ATTK     {0,0,0,0}               /* no attack */
#define     NO_DFNS     {0,0,0,0}               /* no defense */
#define     NO_CARY     {0,0,0,0}               /* no carry effects */
#define     DFNS(c)     {0,c,0,0}
#define     CARY(c)     {0,c,0,0}
#define     PHYS(a,b)   {0,AD_PHYS,a,b}         /* physical */
#define     DRLI(a,b)   {0,AD_DRLI,a,b}         /* life drain */
#define     COLD(a,b)   {0,AD_COLD,a,b}
#define     FIRE(a,b)   {0,AD_FIRE,a,b}
#define     ELEC(a,b)   {0,AD_ELEC,a,b}         /* electrical shock */
#define     ACID(a,b)   {0,AD_ACID,a,b}         /* acid */
#define     STUN(a,b)   {0,AD_STUN,a,b}         /* magical attack */
#define     DISE(a,b)   {0,AD_DISE,a,b}         /* disease attack */
/* clang-format on */

static NEARDATA struct artifact artilist[] = {
#endif /* MAKEDEFS_C || MDLIB_C */

    /* Artifact cost rationale:
     * 1.  The more useful the artifact, the better its cost.
     * 2.  Quest artifacts are highly valued.
     * 3.  Chaotic artifacts are inflated due to scarcity (and balance).
     * 
     * The combination of SPFX_WARN+SPFX_DFLAGH+MH_value will trigger
     * EWarn_of_mon for all monsters that have the MH_value flag.
     * For example, Sting and Orcrist will warn of MH_ORC monsters.
     */

    /*  dummy element #0, so that all interesting indices are non-zero */
    A("", STRANGE_OBJECT,
      0, 0, 0, NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 0L, NO_COLOR, NONARTIFACT),

    
    /*** Lawful artifacts ***/
    
    
    /* From SpliceHack: Some "worse" sacrifice gifts are needed to avoid
     * making #offer overpowered. Used to be PM_KNIGHT. */
    A("Carnwennan", KNIFE,
      (SPFX_RESTR | SPFX_SEARCH | SPFX_STLTH), 0, 0,
      PHYS(3, 8), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM, 400L, NO_COLOR, CARNWENNAN),
    
    A("Demonbane", MACE,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_WARN), 0, MH_DEMON,
      PHYS(5, 0), NO_DFNS, NO_CARY, BANISH,
      A_LAWFUL, PM_CLERIC, NON_PM, 2500L, CLR_RED, DEMONBANE),
    
    /* Excalibur it no longer available to any lawful character when dipping
     * in fountains - only lawful knights can be blessed with it. */
    A("Excalibur", LONG_SWORD, (SPFX_NOGEN | SPFX_RESTR | SPFX_DEFN 
                                | SPFX_INTEL | SPFX_SEARCH),
      0, 0, PHYS(5, 10), DRLI(0, 0), NO_CARY, 0,
      A_LAWFUL, PM_KNIGHT, NON_PM, 4000L, NO_COLOR, EXCALIBUR),
    
    A("Grayswandir", SILVER_SABER,
      (SPFX_RESTR | SPFX_HALRES), 0, 0,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM, 8000L, NO_COLOR, GRAYSWANDIR),
    
    /* From SpliceHack: Shield of King Arthur.
     * This shield now grants steadfastness. */
    A("Pridwen", LARGE_SHIELD,
      (SPFX_RESTR | SPFX_HPHDAM | SPFX_DEFN), 0, 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM, 1500L, NO_COLOR, PRIDWEN),
    
    /* From SLASH'EM */
    A("Quick Blade", SILVER_SHORT_SWORD,
      SPFX_RESTR, 0, 0,
      /* +d9 to-hit bonus handled in artifact.c:spec_abon */
      PHYS(0, 2), NO_DFNS, NO_CARY, 0, 
      A_LAWFUL, NON_PM, NON_PM, 1000L, NO_COLOR, QUICK_BLADE),

    A("Serenity", SILVER_SPEAR,
      (SPFX_RESTR), 0, 0,
      PHYS(5, 10), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM, 5000L, NO_COLOR, SERENITY),


        /*
         *      Ah, never shall I forget the cry,
         *              or the shriek that shrieked he,
         *      As I gnashed my teeth, and from my sheath
         *              I drew my Snickersnee!
         *                      --Koko, Lord high executioner of Titipu
         *                        (From Sir W.S. Gilbert's "The Mikado")
         */
    A("Snickersnee", KATANA,
      SPFX_RESTR, 0, 0,
      PHYS(0, 8), DFNS(AD_STUN), NO_CARY,
      0, A_LAWFUL, PM_SAMURAI, NON_PM, 1200L, NO_COLOR, SNICKERSNEE),
    
    A("Sunsword", LONG_SWORD,
      (SPFX_RESTR | SPFX_DFLAGH), 0, MH_UNDEAD,
      PHYS(5, 0), DFNS(AD_BLND), NO_CARY, BLINDING_RAY,
      A_LAWFUL, NON_PM, NON_PM, 1500L, NO_COLOR, SUNSWORD),

    
    /*** Neutral artifacts ***/
    
    /* From SlashTHEM with changes:
     * In THEM, this was a neutral cloak of protection that granted luck,
     * drain resistance, and warning. Now it is a cloak of invisibility that 
     * grants drain resistance and warning. Luck was removed. */
    A("Blackshroud", CLOAK_OF_INVISIBILITY,
      (SPFX_RESTR | SPFX_WARN), 0, 0,
      NO_ATTK, DFNS(AD_DRLI), NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM, 1500L, NO_COLOR, BLACKSHROUD),
    
    A("Cleaver", BATTLE_AXE,
      SPFX_RESTR, 0, 0,
      PHYS(3, 6), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, PM_BARBARIAN, NON_PM, 1500L, NO_COLOR, CLEAVER),
    
    A("David's Sling", SLING, 
      (SPFX_RESTR | SPFX_ATTK | SPFX_HPHDAM 
        | SPFX_WARN | SPFX_DFLAGH), 0, MH_GIANT, 
      PHYS(5, 0), NO_DFNS, NO_CARY, 0, 
      A_NEUTRAL, NON_PM, NON_PM, 2000L, CLR_RED, DAVID_S_SLING),

    /* From SLASH'EM with changes: removed the Luck bonus and replaced it MC1
     * protection. */
    A("Deluder", CLOAK_OF_DISPLACEMENT,
      (SPFX_RESTR | SPFX_STLTH | SPFX_PROTECT), 0, 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM, 5000L, NO_COLOR, DELUDER),
    
    /* From SLASH'EM with changes: This now grants warning vs undead */
    A("Disrupter", MACE,
      (SPFX_RESTR | SPFX_WARN | SPFX_DFLAGH), 0, MH_UNDEAD,
      PHYS(5, 30), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM, 500L, CLR_RED, DISRUPTER),
    
    /* When wielded:
     * - grants warning vs giants and instakills giants
     * - grants steadfastness
     * - grants max STR
     * - type was changed from long sword to spear */
    A("Giantslayer", SPEAR,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_WARN), 0, MH_GIANT,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM, 200L, CLR_RED, GIANTSLAYER),
    
    /* From EvilHack */
    A("Keolewa", CLUB,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      ELEC(5, 8), DFNS(AD_ELEC), NO_CARY, 0,
      A_NEUTRAL, PM_CAVE_DWELLER, NON_PM, 2000L, NO_COLOR, KEOLEWA),
    
    /*Magicbane is a bit different!  Its magic fanfare unbalances victims 
     * in addition to doing some damage.
     * - Magicbane was changed from an athame to a quarterstaff. */
    A("Magicbane", QUARTERSTAFF,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      STUN(3, 4), DFNS(AD_MAGM), NO_CARY, 0,
      A_NEUTRAL, PM_WIZARD, NON_PM, 3500L, NO_COLOR, MAGICBANE),
    
    /* From SLASH'EM with changes:
     * - Now doesn't impede spellcasting when worn
     * - It acts as a light source.
     * - It is not the healers first sacrifice gift as it was in SLASH'EM */
    A("Mirrorbright", SHIELD_OF_REFLECTION, 
      (SPFX_RESTR | SPFX_HALRES), 0, 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0, 
      A_NEUTRAL, NON_PM, NON_PM, 5000L, NO_COLOR, MIRRORBRIGHT),
    
    /*
     *      Mjollnir can be thrown when wielded if hero has 25 Strength
     *      (usually via gauntlets of power but possible with rings of
     *      gain strength).  If the thrower is a Valkyrie, Mjollnir will
     *      usually (99%) return and then usually (separate 99%) be caught
     *      and automatically be re-wielded.  When returning Mjollnir is
     *      not caught, there is a 50:50 chance of hitting hero for damage
     *      and its lightning shock might destroy some wands and/or rings.
     *
     *      Monsters don't throw Mjollnir regardless of strength (not even
     *      fake-player valkyries).
     *      
     * Changes from vanilla:
     * - The warhammer is now 2-handed and deals 2d6 vs small, 2d8 vs large
     * - Can be invoked for a lightning bolt
     */
    A("Mjollnir", WAR_HAMMER, /* Mjo:llnir */
      (SPFX_RESTR | SPFX_ATTK), 0, 0,
      ELEC(5, 24), NO_DFNS, NO_CARY, 
      LIGHTNING_BOLT,
      A_NEUTRAL, PM_VALKYRIE, NON_PM, 4000L, NO_COLOR, MJOLLNIR),
    
    /* From SLASH6/slashem-up/SlashTHEM */
    A("Mouser\'s Scalpel", RAPIER,
      SPFX_RESTR, 0, 0,
      PHYS(5, 1), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM, 600L, NO_COLOR, MOUSER_S_SCALPEL),
    
    /* From SlashTHEM with changes:  In SlashTHEM this is a neutral robe that
     * confers hallucination resistance and acid resistance when worn. It 
     * also granted protection, but was removed since the robe already has MC2.
     * */
    A("Snakeskin", ROBE,
      (SPFX_RESTR | SPFX_HALRES), 0, 0,
      NO_ATTK, DFNS(AD_ACID), NO_CARY, 0,
      A_NEUTRAL, 0, NON_PM, 1700L, NO_COLOR, SNAKESKIN),
    
    /* From SpliceHack */
    A("The End", SCYTHE, 
      (SPFX_RESTR | SPFX_DEFN), 0, 0,
      COLD(3, 20), DFNS(AD_DRLI), NO_CARY, 0, 
      A_NEUTRAL, NON_PM, NON_PM, 6000L, NO_COLOR, THE_END),
    
    /* Two problems:
     *  1) doesn't let trolls regenerate heads,
     *  2) doesn't give unusual message for 2-headed monsters (but allowing
     *  those at all causes more problems than worth the effort).
     *  
     *  Changes:
     *  - Now grants see invisible when wielded
     *  - Provides warning vs jabberwocks
     *  - Increased rate of beheading from 5% to 10%
     */
    A("Vorpal Blade", LONG_SWORD,
      (SPFX_RESTR | SPFX_BEHEAD | SPFX_SEEINV | SPFX_WARN | SPFX_DFLAGH), 
      0, MH_JABBERWOCK,
      PHYS(5, 1), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM, 4000L, CLR_RED, VORPAL_BLADE),

    /* From SLASH'EM */
    A("Whisperfeet", SPEED_BOOTS,
      (SPFX_RESTR | SPFX_STLTH | SPFX_LUCK), 0, 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM, 5000L, NO_COLOR, WHISPERFEET),
    
   
    /*** Chaotic artifacts ***/
    
    /* From xNetHack */
    A("The Amulet of Storms", AMULET_OF_FLYING,
      (SPFX_RESTR | SPFX_DEFN), 0, 0,
      NO_ATTK, DFNS(AD_ELEC), NO_CARY, 0, 
      A_CHAOTIC, NON_PM, NON_PM, 600L, NO_COLOR, AMULET_OF_STORMS),

    /* From SLASH'EM */
    A("Doomblade", SHORT_SWORD,
      SPFX_RESTR, 0, 0,
      PHYS(0, 20), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM, 1000L, NO_COLOR, DOOMBLADE),
    
    /*
     *      Grimtooth glows in warning when elves are present, but its
     *      damage bonus applies to all targets rather than just elves
     *      (handled as special case in spec_dbon()).
     */
    A("Grimtooth", ORCISH_DAGGER,
      (SPFX_RESTR | SPFX_ATTK | SPFX_WARN | SPFX_DFLAGH), 0, MH_ELF,
      DISE(5, 6), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, PM_ORC, 1500L, CLR_RED, GRIMTOOTH),
    
    /* From SLASH'EM */
    A("Hellfire", CROSSBOW,
      (SPFX_RESTR | SPFX_DEFN), 0, 0,
      PHYS(5, 7), DFNS(AD_FIRE), NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM, 4000L, NO_COLOR, HELLFIRE),
    
    /* Debut artifact in NerfHack */
    A("Mayhem", STOMPING_BOOTS,
      (SPFX_RESTR | SPFX_DEFN | SPFX_WARN | SPFX_DFLAGH), 0, MH_UNDEAD,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM, 5000L, NO_COLOR, MAYHEM),
    
    /* From SLASH'EM: Instead of granting poison resistance, this grants
     * sickness resistance instead. */
    A("Plague", BOW,
      (SPFX_RESTR | SPFX_DEFN), 0, 0,
      PHYS(5, 7), DFNS(AD_DISE), NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM, 4000L, NO_COLOR, PLAGUE),
    
    /* From SpliceHack */
    A("Poseidon\'s Trident", TRIDENT,
      (SPFX_RESTR | SPFX_BREATHE), 0, 0,
      PHYS(3, 7), NO_DFNS, NO_CARY, WWALKING,
      A_CHAOTIC, NON_PM, NON_PM, 1500L, NO_COLOR, POSEIDON_S_TRIDENT),

    /* From SLASH'EM */
    A("Serpent's Tongue", DAGGER,
      SPFX_RESTR, 0, 0,
      PHYS(2,0), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM, 400L, NO_COLOR, SERPENT_S_TONGUE),
    
    /* Same alignment as elves */
    A("Sting", ELVEN_DAGGER,
      (SPFX_WARN | SPFX_DFLAGH), 0, MH_ORC,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, PM_ELF, 800L, CLR_BRIGHT_BLUE, STING),
    
    /* Stormbringer only has a 2 because it can drain a level,
     * providing 8 more. */
    A("Stormbringer", RUNESWORD,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN | SPFX_INTEL | SPFX_DRLI), 0, 0,
      DRLI(5, 2), DFNS(AD_DRLI), NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM, 8000L, NO_COLOR, STORMBRINGER),

    /* Same alignment as elves. */
    A("Orcrist", ELVEN_BROADSWORD,
      (SPFX_WARN | SPFX_DFLAGH), 0, MH_ORC,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, PM_ELF, 2000L, CLR_BRIGHT_BLUE, ORCRIST),

    /*** Unaligned artifacts ***/
    
    /* Changes: Now grants warning vs dragons and can instakill dragons */
    A("Dragonbane", BROADSWORD,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_REFLECT | SPFX_WARN), 0, MH_DRAGON,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 500L, CLR_RED, DRAGONBANE),
    
    /* Changes: Now can instakill flammable monsters and green slime */
    A("Fire Brand", LONG_SWORD,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      FIRE(5, 0), DFNS(AD_FIRE), NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 3000L, NO_COLOR, FIRE_BRAND),
    
    /* Changes: Now can instakill water elementals */
    A("Frost Brand", LONG_SWORD,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      COLD(5, 0), DFNS(AD_COLD), NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 3000L, NO_COLOR, FROST_BRAND),
    
    /* Debut artifact in NerfHack */
    A("Load Brand", HEAVY_SWORD,
      (SPFX_RESTR | SPFX_PROTECT | SPFX_HPHDAM),
      0, 0, PHYS(5, 40), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 3000L, NO_COLOR, LOAD_BRAND),
    
    /* Changes: Now grants warning vs ogres and can instakill ogres */
    A("Ogresmasher", WAR_HAMMER,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_WARN), 0,
      MH_OGRE, PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 200L, CLR_RED, OGRESMASHER),

    /* From SpliceHack with changes:
     * Grants teleport control; greatly increases spellcasting ability. */
    A("Origin", QUARTERSTAFF,
      (SPFX_RESTR | SPFX_TCTRL), 0, 0,
      PHYS(2, 6), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 500L, NO_COLOR, ORIGIN),
    
    /* Debut artifact in NerfHack.
     * Provides see invisible, searching, and stun resistance.
     * With these glasses - you CAN handle the Truth! */
    A("The Lenses of Truth", LENSES,
      (SPFX_RESTR | SPFX_SEEINV | SPFX_SEARCH), 0, 0,
      NO_ATTK, DFNS(AD_STUN), NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 3000L, NO_COLOR, LENSES_OF_TRUTH),
    
    /* Changes: Now grants regeneration, warning vs trolls and can instakill
     * trolls */
    A("Trollsbane", MORNING_STAR,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_REGEN | SPFX_WARN), 0, MH_TROLL,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 1000L, CLR_RED, TROLLSBANE),
    
    /* Changes: Now grants protection from shapechangers, warning vs werefoo
     * and can instakill werefoo */
    A("Werebane", SILVER_SABER,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_WARN), 0, MH_WERE,
      PHYS(5, 0), DFNS(AD_WERE), NO_CARY, 0,
      A_NONE, NON_PM, NON_PM, 1500L, CLR_RED, WEREBANE),

    
    /*
     *      The artifacts for the quest dungeon, all self-willed.
     */

    
    A("The Orb of Detection", CRYSTAL_BALL,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_NOWISH),
      (SPFX_ESP | SPFX_HSPDAM), 0,
      NO_ATTK, NO_DFNS, CARY(AD_MAGM), INVIS,
      A_LAWFUL, PM_ARCHEOLOGIST, NON_PM, 2500L, NO_COLOR, ORB_OF_DETECTION),

    /* Instead of stealth, this grants displacement and flying when carried */
    A("The Heart of Ahriman", LUCKSTONE,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_NOWISH), 
      (SPFX_FLYING | SPFX_DISPLAC), 0,
      /* this stone does double damage if used as a projectile weapon */
      PHYS(5, 0), NO_DFNS, NO_CARY, UNCURSE_INVK,
      A_NEUTRAL, PM_BARBARIAN, NON_PM, 2500L, NO_COLOR, HEART_OF_AHRIMAN),

    A("The Holographic Void Lily", CREDIT_CARD,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL),
      (SPFX_EREGEN | SPFX_HSPDAM | SPFX_REFLECT), 0,
      NO_ATTK, NO_DFNS, NO_CARY, SUMMONING,
      A_CHAOTIC, PM_CARTOMANCER, NON_PM, 7000L, NO_COLOR, HOLOGRAPHIC_VOID_LILY),

    A("The Sceptre of Might", MACE,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_DALIGN
        | SPFX_NOWISH), 0, 0,
      PHYS(5, 0), NO_DFNS, CARY(AD_MAGM), CONFLICT,
      A_LAWFUL, PM_CAVE_DWELLER, NON_PM, 2500L, NO_COLOR, SCEPTRE_OF_MIGHT),

#if 0 /* OBSOLETE -- from 3.1.0 to 3.2.x, this was quest artifact for the
         * Elf role; in 3.3.0 elf became a race available to several roles
         * and the Elf role along with its quest was eliminated; it's a bit
         * overpowered to be an ordinary artifact so leave it excluded */
A("The Palantir of Westernesse", CRYSTAL_BALL,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_NOWISH),
      (SPFX_ESP | SPFX_REGEN | SPFX_HSPDAM), 0,
      NO_ATTK, NO_DFNS, NO_CARY, TAMING,        
      A_CHAOTIC, NON_PM , PM_ELF, 8000L, NO_COLOR, PALANTIR_OF_WESTERNESSE ),
#endif

    A("The Staff of Aesculapius", QUARTERSTAFF,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_ATTK | SPFX_INTEL | SPFX_DRLI
       | SPFX_REGEN | SPFX_NOWISH), 0, 0,
      DRLI(0, 0), DFNS(AD_DRLI), NO_CARY, HEALING,
      A_NEUTRAL, PM_HEALER, NON_PM, 5000L, NO_COLOR, STAFF_OF_AESCULAPIUS),

    A("The Magic Mirror of Merlin", MIRROR,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_SPEAK | SPFX_NOWISH),
      SPFX_ESP, 0,
      NO_ATTK, NO_DFNS, CARY(AD_MAGM), 0,
      A_LAWFUL, PM_KNIGHT, NON_PM, 1500L, NO_COLOR, MAGIC_MIRROR_OF_MERLIN),

    A("The Eyes of the Overworld", LENSES,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_XRAY | SPFX_NOWISH), 0, 0,
      NO_ATTK, DFNS(AD_MAGM), NO_CARY, ENLIGHTENING,
      A_NEUTRAL, PM_MONK, NON_PM, 2500L, NO_COLOR, EYES_OF_THE_OVERWORLD),

    A("The Mitre of Holiness", HELM_OF_BRILLIANCE,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_DFLAGH | SPFX_INTEL | SPFX_PROTECT 
       | SPFX_NOWISH),
      0, MH_UNDEAD,
      NO_ATTK, NO_DFNS, CARY(AD_FIRE), ENERGY_BOOST,
      A_LAWFUL, PM_CLERIC, NON_PM, 2000L, NO_COLOR, MITRE_OF_HOLINESS),

    /* Changes: Now grants physical damage reduction */
    A("The Longbow of Diana", BOW,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_REFLECT | SPFX_HPHDAM 
        | SPFX_NOWISH),
      SPFX_ESP, 0,
      PHYS(5, 0), NO_DFNS, NO_CARY, CREATE_AMMO,
      A_CHAOTIC, PM_RANGER, NON_PM, 4000L, NO_COLOR, LONGBOW_OF_DIANA),

    /* MKoT has an additional carry property if the Key is not cursed (for
       rogues) or blessed (for non-rogues):  #untrap of doors and chests
       will always find any traps and disarming those will always succeed */
    A("The Master Key of Thievery", SKELETON_KEY,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_SPEAK | SPFX_NOWISH),
      (SPFX_WARN | SPFX_TCTRL | SPFX_HPHDAM), 0,
      NO_ATTK, NO_DFNS, NO_CARY,
      UNTRAP,
      A_CHAOTIC, PM_ROGUE, NON_PM, 3500L, NO_COLOR, MASTER_KEY_OF_THIEVERY),

    /* Changes: Increased the rate of bisection from 5% to 10% */
    A("The Tsurugi of Muramasa", TSURUGI,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_BEHEAD | SPFX_LUCK
       | SPFX_PROTECT | SPFX_NOWISH), 0, 0,
      PHYS(0, 8), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, PM_SAMURAI, NON_PM, 4500L, NO_COLOR, TSURUGI_OF_MURAMASA),

    A("The Platinum Yendorian Express Card", CREDIT_CARD,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_DEFN | SPFX_NOWISH),
      (SPFX_ESP | SPFX_HSPDAM), 0,
      NO_ATTK, NO_DFNS, CARY(AD_MAGM), CHARGE_OBJ,
      A_NEUTRAL, PM_TOURIST, NON_PM, 7000L, NO_COLOR, YENDORIAN_EXPRESS_CARD),

    A("The Orb of Fate", CRYSTAL_BALL,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_LUCK | SPFX_NOWISH),
      (SPFX_WARN | SPFX_HSPDAM | SPFX_HPHDAM), 0,
      NO_ATTK, NO_DFNS, NO_CARY, LEV_TELE,
      A_NEUTRAL, PM_VALKYRIE, NON_PM, 3500L, NO_COLOR, ORB_OF_FATE),

    A("The Eye of the Aethiopica", AMULET_OF_ESP,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_NOWISH),
      (SPFX_EREGEN | SPFX_HSPDAM), 0,
      NO_ATTK, DFNS(AD_MAGM), NO_CARY, CREATE_PORTAL,
      A_NEUTRAL, PM_WIZARD, NON_PM, 4000L, NO_COLOR, EYE_OF_THE_AETHIOPICA),

#if !defined(ARTI_ENUM) && !defined(DUMP_ARTI_ENUM)
    /*
     *  terminator; otyp must be zero
     */
    A(0, 0, 0, 0, 0, NO_ATTK, NO_DFNS, NO_CARY, 0, A_NONE, NON_PM, NON_PM, 0L,
      NO_COLOR, TERMINATOR)

}; /* artilist[] (or artifact_names[]) */
#endif

#undef A

#ifdef NO_ATTK
#undef NO_ATTK
#undef NO_DFNS
#undef DFNS
#undef PHYS
#undef DRLI
#undef COLD
#undef FIRE
#undef ELEC
#undef ACID
#undef STUN
#undef DISE
#endif

/*artilist.h*/
