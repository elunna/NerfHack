/* NetHack 5.0  artilist.h      $NHDT-Date: 1781973076 2026/06/20 16:31:16 $  $NHDT-Branch: NetHack-5.0 $:$NHDT-Revision: 1.39 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2017. */
/* NetHack may be freely redistributed.  See license for details. */

#ifdef ARTI_DECL
/* Declare-only mode: gives read access to the single artifact.c-owned
 * artilist[] instance (including any runtime fixups from hack_artifacts())
 * without pulling in another copy of the big initializer table below.
 * Requires "artifact.h" (struct artifact, SPFX_*) to already be included. */

extern NEARDATA struct artifact artilist[];

#else /* !ARTI_DECL */

#if defined(MAKEDEFS_C) || defined (MDLIB_C)
/* in makedefs.c, all we care about is the list of names */

#define A(nam, typ, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac, \
          gs, gv, cost, clr, mat, bn) nam

static const char *const artifact_names[] = {

#elif defined(ARTI_ENUM)
#define A(nam, typ, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac, \
          gs, gv, cost, clr, mat, bn)                            \
    ART_##bn

#elif defined(DUMP_ARTI_ENUM)
#define A(nam, typ, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac, \
          gs, gv, cost, clr, mat, bn)                            \
    { ART_##bn, "ART_" #bn }
#else
/* in artifact.c, set up the actual artifact list structure;
   color field is for an artifact when it glows, not for the item itself */

#define A(nam, typ, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac, \
          gs, gv, cost, clr, mat, bn)                            \
    {                                                            \
        typ, nam, s1, s2, mt, atk, dfn, cry, inv, al, cl, rac,   \
        gs, gv, cost, clr, mat                                   \
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
#define     POIS(a,b)   {0,AD_DRST,a,b}         /* poison */
#define     DISE(a,b)   {0,AD_DISE,a,b}         /* disease attack */
#define     SLEE(a,b)   {0,AD_SLEE,a,b}         /* Sleep attack  */
#define     DISN(a,b)   {0,AD_DISN,a,b}         /* disintegration attack */
#define     MAST(a,b)   {0,AD_MAGM,a,b}         /* magic missile attack  */

#define DEFAULT_MAT 0 /* use base object's default material */

/* Some helper macros for artifact value.
 * We diverge from Vanilla 3.7.0 and assign a value of 1 to all artifacts
 * (except for quest artifacts). This is because we already have altar
 * cracking nerfs in place and artifacts are rare.
 */

#define QAVAL 12
/* clang-format on */

NEARDATA struct artifact artilist[] = {
#endif /* MAKEDEFS_C || MDLIB_C */

    /* Artifact cost rationale:
     * 1.  The more useful the artifact, the better its cost.
     * 2.  Quest artifacts are highly valued.
     * 3.  Chaotic artifacts are inflated due to scarcity (and balance).
     *
     * The combination of SPFX_WARN+SPFX_DFLAGH+MH_value will trigger
     * EWarn_of_mon for all monsters that have the MH_value flag.
     * For example, Sting and Orcrist will warn of MH_ORC monsters.
     *
     *    * Artifact gen_spe rationale:
     * 1.  If the artifact is useful against most enemies, +0.
     * 2.  If the artifact is useful against only a few enemies, usually +2.
     *     This gives the artifact use to early-game characters who receive
     *     it as a gift or find it on the ground.
     * 3.  Role gift gen_spe is chosen to balance against the role's
     *     default starting weapon (it should be better, but need not be
     *     much better).
     * 4.  This can be modified as required for special cases.
     *     (In some cases, like Excalibur, the value is irrelevant.)
     * 5.  Nonweapon spe may have a special meaning, so gen_spe for
     *     nonweapons must always be 0.
     *
     * Artifact gift_value is chosen so that "endgame-quality" artifacts are
     * not gifted in the early game (so that characters don't grind on an
     * altar early-game until they have their endgame weapon, then use it to
     * carry them through the game).  Those artifacts have values ranging from
     * around 8 to 10, based on how good the artifact is.  Less powerful
     * artifacts have values in the 1 to 5 range.  Values in between are used
     * for conditionally good artifacts.  (Note that the value of a gift is
     * normally 1 higher than the difficulty of the monster.)
     */

    /*  dummy element #0, so that all interesting indices are non-zero */
    A("", STRANGE_OBJECT, 0, 0, 0, NO_ATTK, NO_DFNS, NO_CARY, 0, A_NONE,
      NON_PM, NON_PM,
      0, 0, 0L, NO_COLOR, DEFAULT_MAT, NONARTIFACT),

    A("Carnwennan", KNIFE,
      (SPFX_RESTR | SPFX_SEARCH | SPFX_STLTH), 0, 0,
      PHYS(3, 8), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM,
      0, 1, 400L, NO_COLOR, COLDSTEEL, CARNWENNAN),

    /* First sac gift for priests */
    A("Demonbane", MACE,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_WARN), 0, MH_DEMON,
      PHYS(5, 0), NO_DFNS, NO_CARY, BANISH,
      A_LAWFUL, PM_CLERIC, NON_PM,
      0, 1, 2500L, CLR_RED, SILVER, DEMONBANE),

    /* Excalibur it no longer available to any lawful character when dipping
     * in fountains - only lawful knights can dip for it. */
    A("Excalibur", LONG_SWORD,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_DEFN | SPFX_INTEL | SPFX_SEARCH), 0, 0,
      MAST(5, 10), DRLI(0, 0), NO_CARY, 0,
      A_LAWFUL, PM_KNIGHT, NON_PM,
      0, 1, 4000L, NO_COLOR, DEFAULT_MAT, EXCALIBUR),

    A("Grayswandir", SABER,
      (SPFX_RESTR | SPFX_HALRES), 0, 0,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM,
      0, 1, 8000L, NO_COLOR, SILVER, GRAYSWANDIR),

    /* Original idea by Spicy.
     * Grants regeneration and prevents all monster regen. */
    A("Mortality Dial", MORNING_STAR,
      (SPFX_RESTR | SPFX_REGEN | SPFX_WARN), 0, 0,
      PHYS(5, 12), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM,
      0, 1, 5000L, NO_COLOR, DEFAULT_MAT, MORTALITY_DIAL),

    /* From SLASH'EM */
    A("Skullcrusher", CLUB,
      (SPFX_RESTR), 0, 0,
      PHYS(3, 10), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, PM_CAVE_DWELLER, NON_PM,
      0, 1, 300L, NO_COLOR, DEFAULT_MAT, SKULLCRUSHER),

    /* also grants steadfastness. */
    A("Pridwen", LARGE_SHIELD,
      (SPFX_RESTR | SPFX_HPHDAM | SPFX_DEFN | SPFX_STABLE), 0, 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM,
      0, 1, 1500L, NO_COLOR, DEFAULT_MAT, PRIDWEN),

    /* Conferts a passive fire attack */
    A("Oathfire", BRACERS,
      (SPFX_RESTR | SPFX_DEFN | SPFX_PROTECT), 0, 0,
      NO_ATTK, DFNS(AD_FIRE), NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM,
      0, 1, 3400L, NO_COLOR, DRAGON_HIDE, OATHFIRE),

    /* From SLASH'EM; +9 to-hit bonus
     * Grants actual fast speed */
    A("Quick Blade", SHORT_SWORD,
      (SPFX_RESTR | SPFX_FAST), 0, 0,
      PHYS(9, 2), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM,
      0, 1, 1000L, NO_COLOR, SILVER, QUICK_BLADE),

    /* Whilst wielded, prevents monsters from berserking and cancels aggravate
     * monster. Also prevents the hero from spellcasting and counters 80% of
     * monster spells. */
    A("Serenity", SPEAR,
      (SPFX_RESTR | SPFX_BAGGRV), 0, 0,
      PHYS(3, 10), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, NON_PM, NON_PM,
      0, 1, 5000L, NO_COLOR, SILVER, SERENITY),


        /*
         *      Ah, never shall I forget the cry,
         *              or the shriek that shrieked he,
         *      As I gnashed my teeth, and from my sheath
         *              I drew my Snickersnee!
         *                      --Koko, Lord high executioner of Titipu
         *                        (From Sir W.S. Gilbert's "The Mikado")
         */
    /* Now confers stun resistance */
    A("Snickersnee", KATANA,
      SPFX_RESTR, 0, 0,
      PHYS(0, 8), DFNS(AD_STUN), NO_CARY,
      0, A_LAWFUL, PM_SAMURAI, NON_PM,
      0, 1, 1200L, NO_COLOR, DEFAULT_MAT, SNICKERSNEE),

    A("Sunsword", LONG_SWORD,
      (SPFX_RESTR | SPFX_DFLAGH), 0, MH_UNDEAD,
      PHYS(5, 0), DFNS(AD_BLND), NO_CARY, BLINDING_RAY,
      A_LAWFUL, NON_PM, NON_PM,
      0, 1, 1500L, NO_COLOR, GEMSTONE, SUNSWORD),


    /*** Neutral artifacts ***/

    /* The wide arc will not target peaceful monsters */
    A("Cleaver", BATTLE_AXE,
      SPFX_RESTR, 0, 0,
      PHYS(3, 6), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, PM_BARBARIAN, NON_PM,
      0, 1, 1500L, NO_COLOR, DEFAULT_MAT, CLEAVER),

    A("David's Sling", SLING,
      (SPFX_RESTR | SPFX_ATTK | SPFX_HPHDAM | SPFX_STABLE
        | SPFX_WARN | SPFX_DFLAGH), 0, MH_GIANT,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, PM_CAVE_DWELLER, NON_PM,
      0, 1, 2000L, CLR_RED, DEFAULT_MAT, DAVID_S_SLING),

    /* From SLASH'EM with changes: removed the Luck bonus and replaced it MC1
     * protection. Also the crowning gift for Cartomancers -- see
     * CARTOMANCER_GIFT in pray.c. */
    A("Deluder", CLOAK_OF_DISPLACEMENT,
      (SPFX_RESTR | SPFX_STLTH | SPFX_PROTECT), 0, 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 5000L, NO_COLOR, DEFAULT_MAT, DELUDER),

    /* From SLASH'EM with changes: now grants warning vs undead.
     * First sac gift for undead slayers.
     */
    A("Disrupter", MACE,
      (SPFX_RESTR | SPFX_WARN | SPFX_DFLAGH), 0, MH_UNDEAD,
      PHYS(5, 30), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, PM_UNDEAD_SLAYER, NON_PM,
      0, 1, 500L, CLR_RED, COLDSTEEL, DISRUPTER),

    /* When wielded:
     * - grants warning vs giants and instakills giants
     * - grants steadfastness
     * - grants max STR
     * - type was changed from long sword to spear */
    A("Giantslayer", SPEAR,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_WARN | SPFX_STABLE), 0, MH_GIANT,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 200L, CLR_RED, DEFAULT_MAT, GIANTSLAYER),

    /* Magicbane is a bit different!  Its magic fanfare unbalances victims
     * in addition to doing some damage.
     * - Magicbane was changed from an athame to a quarterstaff.
     */
    A("Magicbane", QUARTERSTAFF,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      STUN(3, 4), DFNS(AD_MAGM), NO_CARY, 0,
      A_NEUTRAL, PM_WIZARD, NON_PM,
      0, 1, 3500L, NO_COLOR, DEFAULT_MAT, MAGICBANE),

    /* From SLASH'EM with changes:
     * - Doesn't impede spellcasting when worn
     * - Acts as a light source.
     * - It is NOT the healers first sacrifice gift, Drowsing Rod is. */
    A("Mirrorbright", SHIELD_OF_REFLECTION,
      (SPFX_RESTR | SPFX_HALRES), 0, 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 5000L, NO_COLOR, GEMSTONE, MIRRORBRIGHT),

    /* Crowning gift for monks */
    A("Thunderfists", GAUNTLETS_OF_FORCE,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN | SPFX_PROTECT), 0, 0,
      ELEC(3, 8), DFNS(AD_ELEC), NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 5000L, NO_COLOR, DEFAULT_MAT, THUNDERFISTS),

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
      A_NEUTRAL, PM_VALKYRIE, NON_PM,
      0, 1, 4000L, NO_COLOR, DEFAULT_MAT, MJOLLNIR),

    /* From SLASH6/slashem-up/SlashTHEM */
    A("Mouser\'s Scalpel", RAPIER,
      SPFX_RESTR, 0, 0,
      PHYS(5, 1), NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 600L, NO_COLOR, METAL, MOUSER_S_SCALPEL),

    /* From SlashTHEM with changes:  In SlashTHEM this is a neutral robe that
     * confers hallucination resistance and acid resistance when worn. It
     * also granted protection, but that was removed since the robe already has MC2.
     * */
    A("Snakeskin", ROBE,
      (SPFX_RESTR | SPFX_HALRES), 0, 0,
      NO_ATTK, DFNS(AD_ACID), NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 1700L, NO_COLOR, DRAGON_HIDE, SNAKESKIN),

    A("The End", SCYTHE,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      COLD(3, 20), DFNS(AD_DRLI), NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 6000L, NO_COLOR, BONE, THE_END),

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
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 4000L, CLR_RED, METAL, VORPAL_BLADE),

    /* From SLASH'EM */
    A("Whisperfeet", SPEED_BOOTS,
      (SPFX_RESTR | SPFX_STLTH | SPFX_LUCK), 0, 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_NEUTRAL, NON_PM, NON_PM,
      0, 1, 5000L, NO_COLOR, DEFAULT_MAT, WHISPERFEET),


    /*** Chaotic artifacts ***/

    A("Acidfall", LONG_SWORD,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      ACID(5, 0), DFNS(AD_ACID), NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 3000L, NO_COLOR, DEFAULT_MAT, ACIDFALL),

    A("The Amulet of Storms", AMULET_OF_FLYING,
      (SPFX_RESTR | SPFX_DEFN), 0, 0,
      NO_ATTK, DFNS(AD_ELEC), NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 600L, NO_COLOR, DEFAULT_MAT, AMULET_OF_STORMS),

    /* The quasi-evil twin of Demonbane, Angelslayer is an unholy trident
     * geared towards the destruction of all angelic beings */
    A("Angelslayer", TRIDENT,
      (SPFX_RESTR | SPFX_ATTK | SPFX_SEARCH | SPFX_HSPDAM
       | SPFX_WARN | SPFX_DFLAGH), 0, MH_ANGEL,
      FIRE(5, 10), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 5000L, CLR_RED, COLDSTEEL, ANGELSLAYER),

    /* From SlashTHEM with changes:
     * In THEM, this was a neutral cloak of protection that granted luck,
     * drain resistance, and warning. Now it is a chaotic cloak of
     * invisibility that grants drain resistance and warning.
     * Luck was removed. */
    A("Blackshroud", CLOAK_OF_INVISIBILITY,
      (SPFX_RESTR | SPFX_WARN), 0, 0,
      NO_ATTK, DFNS(AD_DRLI), NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 1500L, NO_COLOR, DEFAULT_MAT, BLACKSHROUD),

    /* From SLASH'EM */
    A("Doomblade", SHORT_SWORD,
      SPFX_RESTR, 0, 0,
      PHYS(0, 10), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 1000L, NO_COLOR, METAL, DOOMBLADE),

    /*
     *      Grimtooth glows in warning when elves are present, but its
     *      damage bonus applies to all targets rather than just elves
     *      (handled as special case in spec_dbon()).
     */
    A("Grimtooth", ORCISH_DAGGER,
      (SPFX_RESTR | SPFX_ATTK | SPFX_WARN | SPFX_DFLAGH), 0, MH_ELF,
      DISE(2, 6), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, PM_ORC,
      0, 1, 1500L, CLR_RED, COLDSTEEL, GRIMTOOTH),

    /* From SLASH'EM */
    A("Hellfire", CROSSBOW,
      (SPFX_RESTR | SPFX_DEFN), 0, 0,
      PHYS(5, 7), DFNS(AD_FIRE), NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 4000L, NO_COLOR, DEFAULT_MAT, HELLFIRE),

    /* Debut artifact in NerfHack;
     * Boots of stomping that confer warning vs undead and conflict. */
    A("Mayhem", STOMPING_BOOTS,
      (SPFX_RESTR | SPFX_DEFN | SPFX_WARN | SPFX_DFLAGH), 0, MH_UNDEAD,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 5000L, NO_COLOR, DEFAULT_MAT, MAYHEM),

    /* From SLASH'EM: Grants poison resistance when carried, and
     * sickness resistance when wielded. */
    A("Plague", BOW,
      (SPFX_RESTR | SPFX_DEFN), 0, 0,
      PHYS(5, 7), DFNS(AD_DISE), DFNS(AD_DRST), 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 4000L, NO_COLOR, DEFAULT_MAT, PLAGUE),

    A("Poseidon\'s Trident", TRIDENT,
      (SPFX_RESTR | SPFX_BREATHE), 0, 0,
      PHYS(3, 14), NO_DFNS, NO_CARY, WWALKING,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 1500L, NO_COLOR, GOLD, POSEIDON_S_TRIDENT),

    /* In Vanilla 3.7.0, Grimtooth has the Fling Poison invoke ability,
       but this felt much more fitting for Serpent's Tongue so I moved it there. */
    A("Serpent's Tongue", DAGGER,
      SPFX_RESTR, 0, 0,
      PHYS(2, 0), NO_DFNS, NO_CARY, FLING_POISON,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 400L, NO_COLOR, DEFAULT_MAT, SERPENT_S_TONGUE),

    /* Same alignment as elves */
    A("Sting", ELVEN_DAGGER,
      (SPFX_WARN | SPFX_DFLAGH), 0, MH_ORC,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, PM_ELF,
      0, 1, 800L, CLR_BRIGHT_BLUE, MITHRIL, STING),

    /* Stormbringer only has a 2 because it can drain a level,
     * providing 8 more. */
    A("Stormbringer", RUNESWORD,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN | SPFX_INTEL| SPFX_DRLI), 0, 0,
      DRLI(5, 2), DFNS(AD_DRLI), NO_CARY, 0,
      A_CHAOTIC, NON_PM, NON_PM,
      0, 1, 8000L, NO_COLOR, METAL, STORMBRINGER),

    /* Same alignment as elves. */
    A("Orcrist", ELVEN_BROADSWORD,
      (SPFX_WARN | SPFX_DFLAGH), 0, MH_ORC,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_CHAOTIC, NON_PM, PM_ELF,
      0, 1, 2000L, CLR_BRIGHT_BLUE, MITHRIL, ORCRIST),

    /* Glamdring, from the LotR series by J.R.R Tolkien. This was the
     * sword that was found along side Orcrist and Sting in a troll cave,
     * and was used by Gandalf thereafter. Like its brethren, this sword
     * glows blue in the presence of orcs. */
    A("Glamdring", LONG_SWORD,
      (SPFX_RESTR | SPFX_WARN | SPFX_PROTECT | SPFX_DFLAGH), 0, MH_ORC,
      PHYS(8, 10), DFNS(AD_ELEC), NO_CARY, 0,
      A_CHAOTIC, NON_PM, PM_ELF,
      0, 1, 8000L, CLR_BRIGHT_BLUE, MITHRIL, GLAMDRING),

    /*** Unaligned artifacts ***/

    /* Now grants warning vs dragons and can instakill dragons */
    A("Dragonbane", BROADSWORD,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_REFLECT | SPFX_WARN), 0, MH_DRAGON,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM,
      0, 1, 500L, CLR_RED, DEFAULT_MAT, DRAGONBANE),

    /* First sac gift for Healers. */
    A("Drowsing Rod", QUARTERSTAFF,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      SLEE(5, 5), DFNS(AD_SLEE), NO_CARY, 0,
      A_NONE, PM_HEALER, NON_PM,
      0, 1, 500L, CLR_MAGENTA, GEMSTONE, DROWSING_ROD),

    /* Now can instakill flammable monsters and green slime */
    A("Fire Brand", LONG_SWORD,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      FIRE(5, 0), DFNS(AD_FIRE), NO_CARY, FIRESTORM,
      A_NONE, NON_PM, NON_PM,
      0, 1, 3000L, NO_COLOR, DEFAULT_MAT, FIRE_BRAND),

    /* Now can instakill water elementals */
    A("Frost Brand", LONG_SWORD,
      (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0, 0,
      COLD(5, 0), DFNS(AD_COLD), NO_CARY, SNOWSTORM,
      A_NONE, NON_PM, NON_PM,
      0, 1, 3000L, NO_COLOR, DEFAULT_MAT, FROST_BRAND),

    /* Debut artifact in NerfHack; powerful, but insanely heavy. */
    A("Load Brand", HEAVY_SWORD,
      (SPFX_RESTR | SPFX_PROTECT | SPFX_HPHDAM | SPFX_STABLE), 0, 0,
      PHYS(1, 0), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM,
      0, 1, 3000L, NO_COLOR, DEFAULT_MAT, LOAD_BRAND),

    /* Now grants warning vs ogres and can instakill ogres */
    A("Ogresmasher", WAR_HAMMER,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_WARN), 0, MH_OGRE,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM,
      0, 1, 200L, CLR_RED, DEFAULT_MAT, OGRESMASHER),

    /* Grants teleport control; greatly increases spellcasting ability. */
    A("Origin", QUARTERSTAFF,
      (SPFX_RESTR | SPFX_TCTRL | SPFX_ESP), 0, 0,
      PHYS(3, 8), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM,
      0, 1, 500L, NO_COLOR, DEFAULT_MAT, ORIGIN),

    /* Debut artifact in NerfHack.
     * Provides see invisible and stun resistance.
     * With these glasses - you CAN handle the Truth! */
    A("The Lenses of Truth", LENSES,
      (SPFX_RESTR | SPFX_SEEINV), 0, 0,
      NO_ATTK, DFNS(AD_STUN), NO_CARY, 0,
      A_NONE, NON_PM, NON_PM,
      0, 1, 3000L, NO_COLOR, DEFAULT_MAT, LENSES_OF_TRUTH),

    /* Now grants regeneration, warning vs trolls and can instakill trolls */
    A("Trollsbane", MORNING_STAR,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_REGEN | SPFX_WARN), 0, MH_TROLL,
      PHYS(5, 0), NO_DFNS, NO_CARY, 0,
      A_NONE, NON_PM, NON_PM,
      0, 1, 1000L, CLR_RED, DEFAULT_MAT, TROLLSBANE),

    /* Now grants protection from shapechangers, warning vs werefoo
     * and can instakill werefoo */
    A("Werebane", SABER,
      (SPFX_RESTR | SPFX_DFLAGH | SPFX_WARN | SPFX_PROTSC), 0, MH_WERE,
      PHYS(5, 0), DFNS(AD_WERE), NO_CARY, 0,
      A_NONE, NON_PM, NON_PM,
      0, 1, 1500L, CLR_RED, SILVER, WEREBANE),

    /*
     *      The artifacts for the quest dungeon, all self-willed.
     */

    A("The Orb of Detection", CRYSTAL_BALL,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL),
      (SPFX_ESP | SPFX_HSPDAM), 0,
      NO_ATTK, NO_DFNS, CARY(AD_MAGM), INVIS,
      A_LAWFUL, PM_ARCHEOLOGIST, NON_PM,
      0, QAVAL, 2500L, NO_COLOR, DEFAULT_MAT, ORB_OF_DETECTION),

    /* Instead of stealth, this grants displacement and flying when carried */
    A("The Heart of Ahriman", RUBY,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL),
      (SPFX_FLYING | SPFX_DISPLAC | SPFX_LUCK), 0,
      /* this stone does double damage if used as a projectile weapon */
      PHYS(0, 0), NO_DFNS, NO_CARY, UNCURSE_INVK,
      A_NEUTRAL, PM_BARBARIAN, NON_PM,
      0, QAVAL, 2500L, NO_COLOR, DEFAULT_MAT, HEART_OF_AHRIMAN),

    A("The Holographic Void Lily", CREDIT_CARD,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL),
      (SPFX_EREGEN | SPFX_HSPDAM | SPFX_REFLECT), 0,
      NO_ATTK, NO_DFNS, NO_CARY, SUMMONING,
      A_CHAOTIC, PM_CARTOMANCER, NON_PM,
      0, QAVAL, 7000L, NO_COLOR, DEFAULT_MAT, HOLOGRAPHIC_VOID_LILY),

    A("The Sceptre of Might", MACE,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_STABLE), 0, 0,
      PHYS(5, 0), DFNS(AD_MAGM), NO_CARY, CONFLICT,
      A_LAWFUL, PM_CAVE_DWELLER, NON_PM,
      0, QAVAL, 2500L, NO_COLOR, GEMSTONE, SCEPTRE_OF_MIGHT),

#if 0 /* OBSOLETE -- from 3.1.0 to 3.2.x, this was quest artifact for the
         * Elf role; in 3.3.0 elf became a race available to several roles
         * and the Elf role along with its quest was eliminated; it's a bit
         * overpowered to be an ordinary artifact so leave it excluded */
A("The Palantir of Westernesse", CRYSTAL_BALL,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL),
      (SPFX_ESP | SPFX_REGEN | SPFX_HSPDAM), 0,
      NO_ATTK, NO_DFNS, NO_CARY, TAMING,
      A_CHAOTIC, NON_PM , PM_ELF,
      0, QAVAL, 8000L, NO_COLOR, DEFAULT_MAT, PALANTIR_OF_WESTERNESSE ),
#endif

    A("The Staff of Aesculapius", QUARTERSTAFF,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_ATTK | SPFX_INTEL | SPFX_DRLI
       | SPFX_REGEN), 0, 0,
      DRLI(3, 0), DFNS(AD_DRLI), NO_CARY, HEALING,
      A_NEUTRAL, PM_HEALER, NON_PM,
      0, QAVAL, 5000L, NO_COLOR, DEFAULT_MAT, STAFF_OF_AESCULAPIUS),

    A("The Magic Mirror of Merlin", MIRROR,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_SPEAK),
      (SPFX_REFLECT | SPFX_ESP | SPFX_HSPDAM), 0,
      NO_ATTK, NO_DFNS, NO_CARY, 0,
      A_LAWFUL, PM_KNIGHT, NON_PM,
      0, QAVAL, 1500L, NO_COLOR, DEFAULT_MAT, MAGIC_MIRROR_OF_MERLIN),

    A("The Eyes of the Overworld", LENSES,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_XRAY), 0, 0,
      NO_ATTK, DFNS(AD_MAGM), NO_CARY, ENLIGHTENING,
      A_NEUTRAL, PM_MONK, NON_PM,
      0, QAVAL, 2500L, NO_COLOR, DEFAULT_MAT, EYES_OF_THE_OVERWORLD),

    A("The Mitre of Holiness", HELM_OF_BRILLIANCE,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_DFLAGH | SPFX_INTEL | SPFX_PROTECT),
      0, MH_UNDEAD,
      NO_ATTK, NO_DFNS, CARY(AD_FIRE), ENERGY_BOOST,
      A_LAWFUL, PM_CLERIC, NON_PM,
      0, QAVAL, 2000L, NO_COLOR, GLASS, MITRE_OF_HOLINESS),

    /* Now grants physical damage reduction */
    A("The Longbow of Diana", BOW,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_REFLECT | SPFX_HPHDAM
       | SPFX_ESP),
      0, 0,
      PHYS(5, 0), NO_DFNS, NO_CARY, CREATE_AMMO,
      A_CHAOTIC, PM_RANGER, NON_PM,
      0, QAVAL, 4000L, NO_COLOR, DEFAULT_MAT, LONGBOW_OF_DIANA),

    /* MKoT has an additional carry property if the Key is not cursed (for
       rogues) or blessed (for non-rogues):  #untrap of doors and chests
       will always find any traps and disarming those will always succeed */
    A("The Master Key of Thievery", SKELETON_KEY,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_SPEAK),
      (SPFX_WARN | SPFX_TCTRL | SPFX_HPHDAM), 0,
      NO_ATTK, NO_DFNS, NO_CARY, UNTRAP,
      A_CHAOTIC, PM_ROGUE, NON_PM,
      0, QAVAL, 3500L, NO_COLOR, DEFAULT_MAT, MASTER_KEY_OF_THIEVERY),

    /* Increased the rate of bisection from 5% to 10% */
    A("The Tsurugi of Muramasa", TSURUGI,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_BEHEAD | SPFX_LUCK
       | SPFX_PROTECT | SPFX_FAST), 0, 0,
      PHYS(0, 8), NO_DFNS, NO_CARY, 0,
      A_LAWFUL, PM_SAMURAI, NON_PM,
      0, QAVAL, 4500L, NO_COLOR, DEFAULT_MAT, TSURUGI_OF_MURAMASA),

    A("The Platinum Yendorian Express Card", CREDIT_CARD,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_DEFN),
      (SPFX_ESP | SPFX_HSPDAM), 0,
      NO_ATTK, NO_DFNS, CARY(AD_MAGM), CHARGE_OBJ,
      A_NEUTRAL, PM_TOURIST, NON_PM,
      0, QAVAL, 7000L, NO_COLOR, PLATINUM, YENDORIAN_EXPRESS_CARD),

    /* Revamped Undead Slayer quest artifact
     * Acts as a magical light source, grants reflection, disintegration and
     * withering resistance, and passively turns undead when in the presence
     * of evil */
    A("The Argent Cross", AMULET_OF_REFLECTION,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_HSPDAM),
      0, 0,
      NO_ATTK, DFNS(AD_DISN), NO_CARY, 0,
      A_NEUTRAL, PM_UNDEAD_SLAYER, NON_PM,
      0, QAVAL, 4000L, NO_COLOR, DEFAULT_MAT, ARGENT_CROSS),

    A("The Orb of Fate", CRYSTAL_BALL,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_LUCK),
      (SPFX_WARN | SPFX_HSPDAM | SPFX_HPHDAM), 0,
      NO_ATTK, NO_DFNS, NO_CARY, LEV_TELE,
      A_NEUTRAL, PM_VALKYRIE, NON_PM,
      0, QAVAL, 3500L, NO_COLOR, DEFAULT_MAT, ORB_OF_FATE),

    A("The Eye of the Aethiopica", AMULET_OF_ESP,
      (SPFX_NOGEN | SPFX_RESTR | SPFX_INTEL | SPFX_EREGEN | SPFX_HSPDAM),
      0, 0,
      NO_ATTK, DFNS(AD_MAGM), NO_CARY, CREATE_PORTAL,
      A_NEUTRAL, PM_WIZARD, NON_PM,
      0, QAVAL, 4000L, NO_COLOR, DEFAULT_MAT, EYE_OF_THE_AETHIOPICA),

#if !defined(ARTI_ENUM) && !defined(DUMP_ARTI_ENUM)
    /*
     *  terminator; otyp must be zero
     */
    A(0, 0, 0, 0, 0, NO_ATTK, NO_DFNS, NO_CARY, 0, A_NONE, NON_PM, NON_PM,
      0, 0, 0L, 0, 0, TERMINATOR) /* 0 is CLR_BLACK rather than NO_COLOR but it
                                     doesn't matter here */

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
#undef SLEE
#undef DISN
#undef MAST
#endif

#endif /* !ARTI_DECL */

/*artilist.h*/
