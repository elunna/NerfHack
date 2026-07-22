/* NetHack 3.7	u_init.c	$NHDT-Date: 1737620595 2025/01/23 00:23:15 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.113 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2017. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"

struct trobj {
    short trotyp;
    schar trspe;
    char trclass;
    char trquan_min;
    char trquan_max;
    char trbless;
};

staticfn long trquan(const struct trobj *);
staticfn struct obj *ini_inv_mkobj_filter(int, boolean);
staticfn short ini_inv_obj_substitution(const struct trobj *,
                                        struct obj *) NONNULLPTRS;
staticfn boolean ini_inv_adjust_obj(const struct trobj *,
                                    struct obj *) NONNULLPTRS;
staticfn void ini_inv_use_obj(struct obj *) NONNULLARG1;
staticfn void ini_inv(const struct trobj *) NONNULLARG1;
staticfn void knows_object(int, boolean);
staticfn void knows_class(char);
staticfn void set_skill_cap_minimum(int, int);
staticfn void u_init_role(void);
staticfn void u_init_race(void);
staticfn void pauper_reinit(void);
staticfn const struct def_skill *skills_for_role(void);
staticfn void u_init_carry_attr_boost(void);
staticfn boolean restricted_spell_discipline(int);

#define UNDEF_TYP 0
#define UNDEF_SPE '\177'
#define UNDEF_BLESS 2
#define CURSED 3
/*
 *      Initial inventory for the various roles.
 */

static const struct trobj Archeologist[] = {
    /* if adventure has a name...  idea from tan@uvm-gen */
    { BULLWHIP, 2, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { JACKET, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { FEDORA, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { FOOD_RATION, 0, FOOD_CLASS, 3, 3, 0 },
    { PICK_AXE, UNDEF_SPE, TOOL_CLASS, 1, 1, UNDEF_BLESS },
    { TINNING_KIT, UNDEF_SPE, TOOL_CLASS, 1, 1, UNDEF_BLESS },
    { TOUCHSTONE, 0, GEM_CLASS, 1, 1, 0 },
    { SACK, 0, TOOL_CLASS, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Barbarian_0[] = {
    { TWO_HANDED_SWORD, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { AXE, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { STUDDED_ARMOR, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { FOOD_RATION, 0, FOOD_CLASS, 2, 2, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Barbarian_1[] = {
    { BATTLE_AXE, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { SHORT_SWORD, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { STUDDED_ARMOR, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { FOOD_RATION, 0, FOOD_CLASS, 2, 2, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Cartomancer[] = {
    { RAZOR_CARD, 2, WEAPON_CLASS, 40, 40, 1 },
    { HAWAIIAN_SHIRT, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { MEAT_STICK, 0, FOOD_CLASS, 2, 2, 0 },
    { CANDY_BAR, 0, FOOD_CLASS, 2, 2, 0 },
    { SCR_CREATE_MONSTER, 0, SCROLL_CLASS, 7, 7, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, SPBOOK_CLASS, 1, 1, UNDEF_BLESS },
    { POT_PHASING, 0, POTION_CLASS, 4, 4, UNDEF_BLESS },
    { SACK, 0, TOOL_CLASS, 1, 1, 0 },
    { PLAYING_CARD_DECK, 0, TOOL_CLASS, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Cave_man[] = {
    { CLUB, 1, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { SLING, 2, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { FLINT, 0, GEM_CLASS, 20, 30, UNDEF_BLESS },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Healer[] = {
    { SCALPEL, 1, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { GLOVES, 1, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { STETHOSCOPE, 0, TOOL_CLASS, 1, 1, 0 },
    { POT_HEALING, 0, POTION_CLASS, 4, 4, UNDEF_BLESS },
    { POT_EXTRA_HEALING, 0, POTION_CLASS, 4, 4, UNDEF_BLESS },
    { WAN_SLEEP, UNDEF_SPE, WAND_CLASS, 1, 1, UNDEF_BLESS },
    /* always blessed, so it's guaranteed readable */
    { SPE_HEALING, 0, SPBOOK_CLASS, 1, 1, 1 },
    { SPE_EXTRA_HEALING, 0, SPBOOK_CLASS, 1, 1, 1 },
    { SPE_STONE_TO_FLESH, 0, SPBOOK_CLASS, 1, 1, 1 },
    { APPLE, 0, FOOD_CLASS, 5, 5, 0 },
    { EUCALYPTUS_LEAF, 0, FOOD_CLASS, 2, 2, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Knight[] = {
    { LONG_SWORD, 1, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { LANCE, 1, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { STUDDED_ARMOR, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { HELMET, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { SMALL_SHIELD, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { GLOVES, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { APPLE, 0, FOOD_CLASS, 10, 10, 0 },
    { CARROT, 0, FOOD_CLASS, 10, 10, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Monk[] = {
    { GLOVES, 2, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { ROBE_OF_POWER, 1, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, SCROLL_CLASS, 1, 1, UNDEF_BLESS },
    { POT_HEALING, 0, POTION_CLASS, 3, 3, UNDEF_BLESS },
    { POT_REFLECTION, 0, POTION_CLASS, 1, 1, UNDEF_BLESS },
    { FOOD_RATION, 0, FOOD_CLASS, 3, 3, 0 },
    { APPLE, 0, FOOD_CLASS, 5, 5, UNDEF_BLESS },
    { ORANGE, 0, FOOD_CLASS, 5, 5, UNDEF_BLESS },
    { FORTUNE_COOKIE, 0, FOOD_CLASS, 3, 3, UNDEF_BLESS },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Priest[] = {
    { MACE, 1, WEAPON_CLASS, 1, 1, 1 },
    { ROBE_OF_POWER, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { SMALL_SHIELD, 2, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { POT_WATER, 0, POTION_CLASS, 4, 4, 1 }, /* holy water */
    { CLOVE_OF_GARLIC, 0, FOOD_CLASS, 1, 1, 1 },
    { SPRIG_OF_WOLFSBANE, 0, FOOD_CLASS, 2, 2, 1 },
    { UNDEF_TYP, UNDEF_SPE, SPBOOK_CLASS, 2, 2, UNDEF_BLESS },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Ranger[] = {
    { DAGGER, 1, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { BOW, 1, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { ARROW, 2, WEAPON_CLASS, 50, 59, UNDEF_BLESS },
    { ARROW, 0, WEAPON_CLASS, 30, 39, UNDEF_BLESS },
    { CLOAK_OF_DISPLACEMENT, 2, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { CRAM_RATION, 0, FOOD_CLASS, 4, 4, 0 },
    { BEARTRAP, 0, TOOL_CLASS, 2, 2, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Rogue[] = {
#define R_KNIVES 1
    { STILETTO, 2, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { KNIFE, 0, WEAPON_CLASS, 7, 16, 0 },
    { JACKET, 1, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { POT_SICKNESS, 0, POTION_CLASS, 1, 1, 0 },
    { SCR_GOLD_DETECTION, 0, SCROLL_CLASS, 4, 4, 1 },
    { SCR_TELEPORTATION, 0, SCROLL_CLASS, 4, 4, 1 },
    { LOCK_PICK, 0, TOOL_CLASS, 1, 1, 0 },
    { SACK, 0, TOOL_CLASS, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Samurai[] = {
    { KATANA, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { SHORT_SWORD, 3, WEAPON_CLASS, 1, 1, UNDEF_BLESS }, /* wakizashi */
    { YUMI, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { YA, 0, WEAPON_CLASS, 26, 45, UNDEF_BLESS },
    { SPLINT_MAIL, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Tourist[] = {
    { DART, 2, WEAPON_CLASS, 40, 60, UNDEF_BLESS },
    { LOW_BOOTS, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, FOOD_CLASS, 10, 10, 0 },
    { POT_EXTRA_HEALING, 0, POTION_CLASS, 2, 2, UNDEF_BLESS },
    { SCR_MAGIC_MAPPING, 0, SCROLL_CLASS, 4, 4, UNDEF_BLESS },
    { HAWAIIAN_SHIRT, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { EXPENSIVE_CAMERA, UNDEF_SPE, TOOL_CLASS, 1, 1, 0 },
    { CREDIT_CARD, 0, TOOL_CLASS, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj UndeadSlayer_0[] = {
    { STAKE, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { CROSSBOW, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { CROSSBOW_BOLT, 0, WEAPON_CLASS, 30, 40, UNDEF_BLESS },
    { LOW_BOOTS, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { JACKET, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { CLOVE_OF_GARLIC, 0, FOOD_CLASS, 3, 3, 1 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj UndeadSlayer_1[] = {
    { STAKE, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { BULLWHIP, 2, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { DAGGER, 0, WEAPON_CLASS, 5, 5, UNDEF_BLESS },
    { HELMET, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { CHAIN_MAIL, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { POT_WATER, 0, POTION_CLASS, 4, 4, 1 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj UndeadSlayer_2[] = {
    { STAKE, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { SPEAR, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { DAGGER, 0, WEAPON_CLASS, 5, 5, UNDEF_BLESS },
    { HELMET, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { CHAIN_MAIL, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { SPRIG_OF_WOLFSBANE, 0, FOOD_CLASS, 5, 5, 1 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj UndeadSlayer_3[] = {
    { STAKE, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { SHORT_SWORD, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { DAGGER, 0, WEAPON_CLASS, 5, 5, UNDEF_BLESS },
    { HELMET, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { CLOAK, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { HOLY_WAFER, 0, FOOD_CLASS, 4, 4, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Valkyrie[] = {
    { SPEAR, 1, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { DAGGER, 0, WEAPON_CLASS, 1, 1, UNDEF_BLESS },
    { SMALL_SHIELD, 3, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { FOOD_RATION, 0, FOOD_CLASS, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0 }
};
static const struct trobj Wizard[] = {
    { QUARTERSTAFF, 1, WEAPON_CLASS, 1, 1, 1 },
    { CLOAK_OF_PROTECTION, 0, ARMOR_CLASS, 1, 1, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, WAND_CLASS, 1, 1, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, RING_CLASS, 1, 1, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, POTION_CLASS, 2, 2, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, SCROLL_CLASS, 2, 2, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, SPBOOK_CLASS, 1, 1, UNDEF_BLESS },
    { UNDEF_TYP, UNDEF_SPE, SPBOOK_CLASS, 1, 1, UNDEF_BLESS },
    { 0, 0, 0, 0, 0, 0 }
};

/*
 *      Optional extra inventory items.
 */
static const struct trobj Healing_book[] =
    { { SPE_HEALING, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Protection_book[] =
    { { SPE_PROTECTION, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Confuse_monster_book[] =
    { { SPE_CONFUSE_MONSTER, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj DetectFoodBook[] =
    { { SPE_DETECT_FOOD, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj DetectMonBook[] =
    { { SPE_DETECT_MONSTERS, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj LightBook[] =
    { { SPE_LIGHT, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj KnockBook[] =
    { { SPE_KNOCK, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj LockBook[] =
    { { SPE_WIZARD_LOCK, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj ForceBolt_book[] =
    { { SPE_FORCE_BOLT, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj FireBolt_book[] =
    { { SPE_FIRE_BOLT, UNDEF_SPE, SPBOOK_CLASS, 1, 1, 1 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Tinopener[] =
    { { TIN_OPENER, 0, TOOL_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Lamp[] =
    { { OIL_LAMP, 1, TOOL_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj OilPotion[] =
    { { POT_OIL, 0, POTION_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj PoisonPotion[] =
    { { POT_SICKNESS, 0, POTION_CLASS, 2, 2, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Blindfold[] =
    { { BLINDFOLD, 0, TOOL_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Xtra_food[] =
    { { UNDEF_TYP, UNDEF_SPE, FOOD_CLASS, 2, 2, 0},
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Leash[] =
    { { LEASH, 0, TOOL_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Towel[] =
    { { TOWEL, 0, TOOL_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Wishing[] =
    { { WAN_WISHING, 3, WAND_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Money[] =
    { { GOLD_PIECE, 0, COIN_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Wax_Candles[] =
    { { WAX_CANDLE, 0, TOOL_CLASS, 3, 7, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Tallow_Candles[] =
    { { WAX_CANDLE, 0, TOOL_CLASS, 3, 7, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj Figurine[] =
    { { FIGURINE, 0, TOOL_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };
static const struct trobj GreaseCan[] =
    { { CAN_OF_GREASE, 0, TOOL_CLASS, 1, 1, 0 },
      { 0, 0, 0, 0, 0, 0 } };

/* align-based substitutions for initial inventory */
struct inv_asub {
    aligntyp align;
    short item_otyp, subs_otyp;
} inv_asubs[] = {
    { A_CHAOTIC, HOLY_WAFER, LEMBAS_WAFER },
    { A_NONE, STRANGE_OBJECT, STRANGE_OBJECT }
};

/* race-based substitutions for initial inventory;
   the weaker cloak for elven rangers is intentional--they shoot better */
static const struct inv_sub {
    short race_pm, item_otyp, subs_otyp;
} inv_subs[] = {
    { PM_ELF, DAGGER, ELVEN_DAGGER },
    { PM_ELF, SPEAR, ELVEN_SPEAR },
    { PM_ELF, SHORT_SWORD, ELVEN_SHORT_SWORD },
    { PM_ELF, LONG_SWORD, ELVEN_LONG_SWORD },
    { PM_ELF, BOW, ELVEN_BOW },
    { PM_ELF, ARROW, ELVEN_ARROW },
    { PM_ELF, HELMET, ELVEN_HELM },
    { PM_ELF, CHAIN_MAIL, ELVEN_RING_MAIL },
    /* { PM_ELF, SMALL_SHIELD, ELVEN_SHIELD }, */
    { PM_ELF, CLOAK_OF_DISPLACEMENT, ELVEN_CLOAK },
    { PM_ELF, CLOAK, ELVEN_CLOAK },
    { PM_ELF, CRAM_RATION, LEMBAS_WAFER },
    { PM_ORC, DAGGER, ORCISH_DAGGER },
    { PM_ORC, SPEAR, ORCISH_SPEAR },
    { PM_ORC, SHORT_SWORD, ORCISH_SHORT_SWORD },
    { PM_ORC, LONG_SWORD, ORCISH_LONG_SWORD },
    { PM_ORC, BOW, ORCISH_BOW },
    { PM_ORC, ARROW, ORCISH_ARROW },
    { PM_ORC, HELMET, ORCISH_HELM },
    /*{ PM_ORC, SMALL_SHIELD, ORCISH_SHIELD },*/
    { PM_ORC, RING_MAIL, ORCISH_RING_MAIL },
    { PM_ORC, CHAIN_MAIL, ORCISH_CHAIN_MAIL },
    { PM_ORC, CRAM_RATION, TRIPE_RATION },
    { PM_ORC, LEMBAS_WAFER, TRIPE_RATION },
    { PM_DWARF, SPEAR, DWARVISH_SPEAR },
    { PM_DWARF, SHORT_SWORD, DWARVISH_SHORT_SWORD },
    { PM_DWARF, HELMET, DWARVISH_HELM },
    /* { PM_DWARF, SMALL_SHIELD, DWARVISH_ROUNDSHIELD }, */
    /* { PM_DWARF, PICK_AXE, DWARVISH_MATTOCK }, */
    { PM_DWARF, CLOAK, DWARVISH_CLOAK },
    { PM_DWARF, LEMBAS_WAFER, CRAM_RATION },
    { PM_GNOME, BOW, CROSSBOW },
    { PM_GNOME, ARROW, CROSSBOW_BOLT },
    { PM_GNOME, HELMET, GNOMISH_HELM },
    { PM_GNOME, LOW_BOOTS, GNOMISH_BOOTS },
    { PM_GNOME, HIGH_BOOTS, GNOMISH_BOOTS },
    { PM_GNOME, ARMOR, GNOMISH_SUIT },
    /* Create vampire blood */
    { PM_DHAMPIR, POT_FRUIT_JUICE, POT_VAMPIRE_BLOOD },
    { PM_DHAMPIR, CLOVE_OF_GARLIC, POT_VAMPIRE_BLOOD },
    { PM_DHAMPIR, SPRIG_OF_WOLFSBANE, POT_VAMPIRE_BLOOD },
    { PM_DHAMPIR, FOOD_RATION, POT_VAMPIRE_BLOOD },
    { PM_DHAMPIR, CRAM_RATION, POT_VAMPIRE_BLOOD },
    { PM_DHAMPIR, LEMBAS_WAFER, POT_VAMPIRE_BLOOD },
    { PM_DHAMPIR, CHAIN_MAIL, JACKET },
    /* grung can't wear boots */
    { PM_GRUNG, HIGH_BOOTS, STRANGE_OBJECT },
    { PM_GRUNG, LOW_BOOTS, GRUNG_BRACERS },
    { PM_GRUNG, SACK, OILSKIN_SACK },
    { PM_GRUNG, SMALL_SHIELD, CRABBACK_SHIELD },
    { PM_GRUNG, GLOVES, PINCER_GAUNTLETS },
    { PM_GRUNG, JACKET, SNAKEHIDE_JERKIN },
    { PM_GRUNG, STUDDED_ARMOR, SPIDER_RIB_SHELL },
    { PM_GRUNG, FEDORA, SPORECAP_HOOD },
    { PM_GRUNG, CLOAK_OF_DISPLACEMENT, DRAGONFLY_CLOAK },
    { PM_GRUNG, CLOAK_OF_PROTECTION, DRAGONFLY_CLOAK },
    { PM_GRUNG, SCIMITAR, SPINEBACK_CUTTER },
    { PM_GRUNG, SHORT_SWORD, SPINEBACK_CUTTER },
    { PM_GRUNG, MACE, SKULLCLAW_MACE },
    { PM_GRUNG, AXE, CLAWBONE_HATCHET },
    { PM_GRUNG, DAGGER, CLAWBONE_HATCHET },
    { PM_GRUNG, KNIFE, CLAWBONE_HATCHET },

    { NON_PM, STRANGE_OBJECT, STRANGE_OBJECT }
};

static const struct def_skill Skill_A[] = {
    { P_DAGGER, P_BASIC },
    { P_KNIFE, P_BASIC },
    { P_AXE, P_BASIC },
    { P_PICK_AXE, P_MASTER },
    { P_SHORT_SWORD, P_BASIC },
    { P_SABER, P_EXPERT },
    { P_SPEAR, P_BASIC },
    { P_CLUB, P_SKILLED },
    { P_QUARTERSTAFF, P_SKILLED },
    { P_SLING, P_SKILLED },
    { P_DART, P_BASIC },
    { P_BOOMERANG, P_EXPERT },
    { P_WHIP, P_EXPERT },
    { P_UNICORN_HORN, P_SKILLED },
    { P_ATTACK_SPELL, P_BASIC },
    { P_HEALING_SPELL, P_BASIC },
    { P_DIVINATION_SPELL, P_EXPERT },
    { P_MATTER_SPELL, P_BASIC },
    { P_RIDING, P_BASIC },
    { P_TWO_WEAPON_COMBAT, P_BASIC },
    { P_SHIELD, P_SKILLED },
    { P_BARE_HANDED_COMBAT, P_EXPERT },
    { P_NONE, 0 }
};
static const struct def_skill Skill_B[] = {
    { P_DAGGER, P_BASIC },
    { P_AXE, P_MASTER },
    { P_PICK_AXE, P_SKILLED },
    { P_SHORT_SWORD, P_EXPERT },
    { P_BROAD_SWORD, P_SKILLED },
    { P_LONG_SWORD, P_SKILLED },
    { P_TWO_HANDED_SWORD, P_EXPERT },
    { P_SABER, P_SKILLED },
    { P_CLUB, P_SKILLED },
    { P_MACE, P_SKILLED },
    { P_MORNING_STAR, P_SKILLED },
    { P_FLAIL, P_BASIC },
    { P_HAMMER, P_EXPERT },
    { P_QUARTERSTAFF, P_BASIC },
    { P_SPEAR, P_SKILLED },
    { P_TRIDENT, P_SKILLED },
    { P_BOW, P_BASIC },
    { P_ATTACK_SPELL, P_BASIC },
    { P_ESCAPE_SPELL, P_BASIC }, /* special spell is haste self */
    { P_RIDING, P_SKILLED },
    { P_TWO_WEAPON_COMBAT, P_BASIC },
    { P_SHIELD, P_SKILLED },
    { P_BARE_HANDED_COMBAT, P_MASTER },
    { P_NONE, 0 }
};
static const struct def_skill Skill_Car[] = {
    /* Cartomancers are extremely narrow in their skills because
     * they are guaranteed a steady stream of cards for offense
     * and defense. Multishot only applies to shuriken class projectiles.
     *
     * Cartomancers also have a base -5 to-hit penalty for melee fighting
     * Dwarvish carts can reach skilled in pick-axe
     * Gnomish carts can reach skilled in crossbow, basic in club
     * Orcs can reach skilled in saber
     * Elves do not get the enchantment spell skill however.
     * */
    { P_DART, P_SKILLED },
    { P_SHURIKEN, P_MASTER },
    { P_SLING, P_SKILLED },
    { P_BOOMERANG, P_SKILLED },
    { P_UNICORN_HORN, P_EXPERT },
    { P_BARE_HANDED_COMBAT, P_BASIC },
    /* Cartomancers don't get skill in spellcasting - they have rulebooks. */
    { P_NONE, 0 }
};
static const struct def_skill Skill_C[] = {
    { P_AXE, P_SKILLED },
    { P_PICK_AXE, P_BASIC },
    { P_CLUB, P_MASTER },
    { P_MACE, P_EXPERT },
    { P_FLAIL, P_SKILLED },
    { P_HAMMER, P_SKILLED },
    { P_QUARTERSTAFF, P_EXPERT },
    { P_SPEAR, P_EXPERT },
    { P_TRIDENT, P_SKILLED },
    { P_BOW, P_SKILLED },
    { P_SLING, P_EXPERT },
    { P_BOOMERANG, P_EXPERT },
    { P_UNICORN_HORN, P_BASIC },
    { P_RIDING, P_BASIC },
    { P_BARE_HANDED_COMBAT, P_MASTER },
    { P_SHIELD, P_BASIC },
    { P_NONE, 0 }
};
static const struct def_skill Skill_H[] = {
    { P_DAGGER, P_SKILLED },
    { P_KNIFE, P_EXPERT },
    { P_SHORT_SWORD, P_SKILLED },
    { P_SABER, P_BASIC },
    { P_CLUB, P_SKILLED },
    { P_MACE, P_BASIC },
    { P_QUARTERSTAFF, P_EXPERT },
    { P_POLEARMS, P_BASIC },
    { P_SPEAR, P_BASIC },
    { P_TRIDENT, P_BASIC },
    { P_SLING, P_SKILLED },
    { P_DART, P_EXPERT },
    { P_SHURIKEN, P_SKILLED },
    { P_UNICORN_HORN, P_MASTER },
    { P_HEALING_SPELL, P_EXPERT },
    { P_BARE_HANDED_COMBAT, P_BASIC },
    { P_NONE, 0 }
};
static const struct def_skill Skill_K[] = {
    { P_SHORT_SWORD, P_SKILLED },
    { P_BROAD_SWORD, P_EXPERT },
    { P_LONG_SWORD, P_MASTER },
    { P_TWO_HANDED_SWORD, P_SKILLED },
    { P_SABER, P_SKILLED },
    { P_MACE, P_SKILLED },
    { P_MORNING_STAR, P_SKILLED },
    { P_FLAIL, P_BASIC },
    { P_HAMMER, P_BASIC },
    { P_POLEARMS, P_EXPERT },
    { P_SPEAR, P_EXPERT },
    { P_LANCE, P_EXPERT },
    { P_BOW, P_BASIC },
    { P_CROSSBOW, P_SKILLED },
    { P_ATTACK_SPELL, P_SKILLED },
    { P_HEALING_SPELL, P_SKILLED },
    { P_CLERIC_SPELL, P_SKILLED },
    { P_RIDING, P_EXPERT },
    { P_TWO_WEAPON_COMBAT, P_SKILLED },
    { P_BARE_HANDED_COMBAT, P_EXPERT },
    { P_SHIELD, P_EXPERT },
    { P_NONE, 0 }
};
static const struct def_skill Skill_Mon[] = {
    { P_QUARTERSTAFF, P_EXPERT },
    { P_SPEAR, P_BASIC },
    { P_SHURIKEN, P_BASIC },
    { P_HEALING_SPELL, P_EXPERT },
    { P_CLERIC_SPELL, P_SKILLED },
    { P_ENCHANTMENT_SPELL, P_SKILLED },
    { P_ATTACK_SPELL, P_BASIC },
#if 0
    { P_ESCAPE_SPELL, P_SKILLED },
    { P_MATTER_SPELL, P_BASIC },
    { P_DIVINATION_SPELL, P_BASIC },
#endif
    { P_MARTIAL_ARTS, P_GRAND_MASTER },
    { P_NONE, 0 }
};
static const struct def_skill Skill_P[] = {
    { P_CLUB, P_EXPERT },
    { P_MACE, P_MASTER },
    { P_MORNING_STAR, P_EXPERT },
    { P_FLAIL, P_SKILLED },
    { P_HAMMER, P_EXPERT },
    { P_QUARTERSTAFF, P_EXPERT },
    { P_POLEARMS, P_SKILLED },
    { P_SPEAR, P_SKILLED },
    { P_TRIDENT, P_BASIC },
    { P_BOW, P_BASIC },
    { P_SLING, P_BASIC },
    { P_CROSSBOW, P_BASIC },
    { P_DART, P_BASIC },
    { P_BOOMERANG, P_BASIC },
    { P_UNICORN_HORN, P_SKILLED },
    { P_HEALING_SPELL, P_EXPERT },
    { P_DIVINATION_SPELL, P_EXPERT },
    { P_CLERIC_SPELL, P_EXPERT },
    { P_RIDING, P_BASIC },
    { P_BARE_HANDED_COMBAT, P_BASIC },
    { P_SHIELD, P_SKILLED },
    { P_NONE, 0 }
};
static const struct def_skill Skill_R[] = {
    { P_DAGGER, P_EXPERT },
    { P_KNIFE, P_MASTER },
    { P_SHORT_SWORD, P_EXPERT },
    { P_SABER, P_SKILLED },
    { P_CLUB, P_BASIC },
    { P_FLAIL, P_BASIC },
    { P_HAMMER, P_BASIC },
    { P_CROSSBOW, P_BASIC },
    { P_DART, P_EXPERT },
    { P_SHURIKEN, P_SKILLED },
    { P_DIVINATION_SPELL, P_BASIC }, /* Special spell */
    { P_ESCAPE_SPELL, P_SKILLED },
    { P_RIDING, P_BASIC },
    { P_TWO_WEAPON_COMBAT, P_EXPERT },
    { P_BARE_HANDED_COMBAT, P_EXPERT },
    { P_NONE, 0 }
};
static const struct def_skill Skill_Ran[] = {
    { P_DAGGER, P_SKILLED },
    { P_AXE, P_BASIC },
    { P_FLAIL, P_SKILLED },
    { P_BOW, P_MASTER },
    { P_CROSSBOW, P_EXPERT },
    { P_DART, P_SKILLED },
    { P_WHIP, P_BASIC },
    { P_HEALING_SPELL, P_BASIC },
    { P_DIVINATION_SPELL, P_BASIC },
    { P_ESCAPE_SPELL, P_BASIC },
    { P_RIDING, P_BASIC },
    { P_BARE_HANDED_COMBAT, P_BASIC },
    { P_SHIELD, P_SKILLED },
    { P_NONE, 0 }
};
static const struct def_skill Skill_S[] = {
    { P_DAGGER, P_BASIC },
    { P_KNIFE, P_SKILLED },
    { P_SHORT_SWORD, P_EXPERT },
    { P_BROAD_SWORD, P_SKILLED },
    { P_LONG_SWORD, P_EXPERT },
    { P_TWO_HANDED_SWORD, P_MASTER },
    { P_SABER, P_BASIC },
    { P_FLAIL, P_SKILLED },
    { P_QUARTERSTAFF, P_BASIC },
    { P_POLEARMS, P_SKILLED },
    { P_SPEAR, P_EXPERT },
    { P_LANCE, P_SKILLED },
    { P_BOW, P_EXPERT },
    { P_SHURIKEN, P_EXPERT },
    { P_ATTACK_SPELL, P_BASIC },
    { P_DIVINATION_SPELL, P_BASIC }, /* special spell is clairvoyance */
    { P_CLERIC_SPELL, P_SKILLED },
    { P_RIDING, P_SKILLED },
    { P_TWO_WEAPON_COMBAT, P_EXPERT },
    { P_MARTIAL_ARTS, P_MASTER },
    { P_NONE, 0 }
};
static const struct def_skill Skill_T[] = {
    /* "Jack of all trades, master of none" */
    { P_CLUB, P_BASIC },
    { P_DAGGER, P_BASIC },
    { P_KNIFE, P_BASIC },
    { P_AXE, P_BASIC },
    { P_PICK_AXE, P_BASIC },
    { P_SHORT_SWORD, P_BASIC },
    { P_BROAD_SWORD, P_BASIC },
    { P_LONG_SWORD, P_BASIC },
    { P_TWO_HANDED_SWORD, P_BASIC },
    { P_SABER, P_BASIC },
    { P_MACE, P_BASIC },
    { P_MORNING_STAR, P_BASIC },
    { P_FLAIL, P_BASIC },
    { P_HAMMER, P_BASIC },
    { P_QUARTERSTAFF, P_BASIC },
    { P_POLEARMS, P_BASIC },
    { P_SPEAR, P_BASIC },
    { P_TRIDENT, P_BASIC },
    { P_LANCE, P_BASIC },
    { P_BOW, P_BASIC },
    { P_SLING, P_BASIC },
    { P_CROSSBOW, P_BASIC },
    { P_DART, P_MASTER },
    { P_SHURIKEN, P_BASIC },
    { P_BOOMERANG, P_BASIC },
    { P_WHIP, P_BASIC },
    { P_UNICORN_HORN, P_BASIC },
    { P_DIVINATION_SPELL, P_BASIC },
    { P_ENCHANTMENT_SPELL, P_SKILLED }, /* Special spell: charm monster */
    { P_ESCAPE_SPELL, P_BASIC },
    { P_RIDING, P_BASIC },
    { P_TWO_WEAPON_COMBAT, P_BASIC },
    { P_BARE_HANDED_COMBAT, P_BASIC },
    { P_SHIELD, P_BASIC },
    { P_NONE, 0 }
};
static const struct def_skill Skill_U[] = {
    { P_DAGGER, P_MASTER },              /* Stakes */
    { P_LONG_SWORD, P_BASIC },           /* Buffy */
    { P_SHORT_SWORD, P_BASIC },
    { P_BROAD_SWORD, P_SKILLED },        /* Buffy */
    { P_CLUB, P_SKILLED },
    { P_MACE, P_EXPERT },                /* Sac gift is Disrupter */
    { P_MORNING_STAR, P_EXPERT },        /* Castlevania */
    { P_FLAIL, P_SKILLED },
    { P_HAMMER, P_SKILLED },
    { P_POLEARMS, P_SKILLED },
    { P_SPEAR, P_EXPERT },
    { P_CROSSBOW, P_EXPERT },              /* Dracula movies */
    { P_WHIP, P_EXPERT },                  /* Castlevania */
    { P_UNICORN_HORN, P_SKILLED },
    { P_CLERIC_SPELL, P_BASIC },
    { P_ESCAPE_SPELL, P_BASIC },
    { P_MATTER_SPELL, P_SKILLED },        /* Fireball, flame sphere, etc */
    { P_RIDING, P_SKILLED },
    /* This counts as martial arts for undead slayers */
    { P_BARE_HANDED_COMBAT, P_EXPERT }, /* Buffy the Vampire Slayer */
    { P_SHIELD, P_SKILLED },
    { P_RIDING, P_SKILLED },
    { P_NONE, 0 }
};
static const struct def_skill Skill_V[] = {
    { P_DAGGER, P_EXPERT },
    { P_AXE, P_EXPERT },
    { P_PICK_AXE, P_SKILLED },
    { P_SHORT_SWORD, P_SKILLED },
    { P_BROAD_SWORD, P_SKILLED },
    { P_LONG_SWORD, P_EXPERT },
    { P_TWO_HANDED_SWORD, P_EXPERT },
    { P_SABER, P_BASIC },
    { P_HAMMER, P_MASTER },
    { P_QUARTERSTAFF, P_BASIC },
    { P_POLEARMS, P_SKILLED },
    { P_SPEAR, P_EXPERT },
    { P_TRIDENT, P_BASIC },
    { P_LANCE, P_SKILLED },
    { P_SLING, P_BASIC },
    { P_ATTACK_SPELL, P_BASIC },
    { P_ESCAPE_SPELL, P_BASIC },
    { P_RIDING, P_SKILLED },
    { P_TWO_WEAPON_COMBAT, P_SKILLED },
    { P_BARE_HANDED_COMBAT, P_EXPERT },
    { P_SHIELD, P_MASTER },
    { P_NONE, 0 }
};
static const struct def_skill Skill_W[] = {
    { P_DAGGER, P_EXPERT },
    { P_QUARTERSTAFF, P_MASTER },
    { P_SLING, P_SKILLED },
    { P_DART, P_EXPERT },
    { P_ATTACK_SPELL, P_EXPERT },
    { P_HEALING_SPELL, P_SKILLED },
    { P_DIVINATION_SPELL, P_EXPERT },
    { P_ENCHANTMENT_SPELL, P_SKILLED },
    { P_CLERIC_SPELL, P_SKILLED },
    { P_ESCAPE_SPELL, P_EXPERT },
    { P_MATTER_SPELL, P_EXPERT },
    { P_RIDING, P_BASIC },
    { P_BARE_HANDED_COMBAT, P_BASIC },
    { P_NONE, 0 }
};

staticfn void
knows_object(int obj, boolean override_pauper)
{
    if (u.uroleplay.pauper && !override_pauper)
        return;
    /* mark as known, but not yet encountered */
    discover_object(obj, TRUE, FALSE, FALSE);
}

/* Know ordinary (non-magical) objects of a certain class,
   like all gems except the loadstone and luckstone. */
staticfn void
knows_class(char sym)
{
    struct obj odummy, *o;
    int ct;

    if (u.uroleplay.pauper)
        return;

    odummy = cg.zeroobj;
    odummy.oclass = sym;
    o = &odummy; /* for use in various obj.h macros */

    /*
     * Note:  the exceptions here can be bypassed if necessary by
     *        calling knows_object() directly.  So an elven ranger,
     *        for example, knows all elven weapons despite the bow,
     *        arrow, and spear limitation below.
     */

    for (ct = svb.bases[(uchar) sym]; ct < svb.bases[(uchar) sym + 1]; ct++) {
        /* not flagged as magic but shouldn't be pre-discovered */
        if (ct == CORNUTHAUM || ct == DUNCE_CAP)
            continue;
        if (sym == WEAPON_CLASS) {
            odummy.otyp = ct; /* update 'o' */
            /* arbitrary: only knights and samurai recognize polearms */
            if ((!Role_if(PM_KNIGHT) && !Role_if(PM_SAMURAI)) && is_pole(o))
                continue;
            /* rangers know all launchers (bows, &c), ammo (arrows, &c),
               and spears regardless of race/species, but not other weapons */
            if (Role_if(PM_RANGER)
                && (!is_launcher(o) && !is_ammo(o) && !is_spear(o)))
                continue;
            /* rogues know daggers, regardless of racial variations */
            if (Role_if(PM_ROGUE) && (objects[o->otyp].oc_skill != P_DAGGER))
                continue;
        }
        /* Let cartomancers start knowing all rulebooks. */
        if (sym == SPBOOK_CLASS && Role_if(PM_CARTOMANCER)
            && objects[ct].oc_class == sym
            && ct != SPE_NOVEL && ct != SPE_BOOK_OF_THE_DEAD) {
            knows_object(ct, FALSE);
        } else if (objects[ct].oc_class == sym && !objects[ct].oc_magic) {
            knows_object(ct, FALSE);
        }
    }
}

/* role-specific initializations, mostly inventory

   other things may be initialised here, but the function might run more than
   once, so any non-inventory initialisations should be nonrandom and
   idempotent (i.e. doing them twice is OK) */
staticfn void
u_init_role(void)
{
    int i;

    /* the program used to check moves<=1 && invent==NULL do decide whether
       a new game has started, but due to the 'pauper' option/conduct, can't
       rely on invent becoming non-Null anymore; instead, initialize moves
       to 0 instead of 1, then set it to 1 here, where invent init occurs */
    svm.moves = 1L;

    switch (Role_switch) {
    /* rn2(100) > 50 necessary for some choices because some
     * random number generators are bad enough to seriously
     * skew the results if we use rn2(2)...  --KAA
     */
    case PM_ARCHEOLOGIST: {
        static const struct trobj *A_spell[] = {
            DetectFoodBook,
            DetectMonBook,
            LightBook,
            KnockBook,
            LockBook
        };

        ini_inv(Archeologist);
        ini_inv(A_spell[rn2(100) / 20]); /* [0..4] */
        if (!rn2(10))
            ini_inv(Tinopener);
        else if (!rn2(4))
            ini_inv(Lamp);
        knows_object(SACK, FALSE);
        knows_object(TOUCHSTONE, FALSE); /* FALSE: don't override pauper here,
                                          * but TOUCHSTONE will be made known
                                          * in pauper_reinit() */
        knows_object(DWARVISH_MATTOCK, FALSE);
        break;
    }
    case PM_BARBARIAN:
        if (rn2(100) >= 50) { /* see above comment */
            ini_inv(Barbarian_0);
        } else {
            ini_inv(Barbarian_1);
        }
        if (!rn2(6))
            ini_inv(Lamp);
        knows_class(WEAPON_CLASS); /* excluding polearms */
        knows_class(ARMOR_CLASS);
        break;
    case PM_CARTOMANCER:
        /* Cards only weigh 1 for Cartomancers */
        for (int s = SCR_ENCHANT_ARMOR; s < SCR_STINKING_CLOUD; s++)
            objects[s].oc_weight = 1;
        /* Rulebooks weigh 5 for Cartomancers */
        for (int s = SPE_DIG; s < SPE_CHAIN_LIGHTNING; s++)
            objects[s].oc_weight = 5;
        /* Create monster cards are double as likely */
        objects[SCR_CREATE_MONSTER].oc_prob *= 2;

        ini_inv(Cartomancer);
        skill_init(Skill_Car);
        knows_object(CRYSTAL_BALL, FALSE);
        knows_object(PLAYING_CARD_DECK, FALSE);
        knows_class(SPBOOK_CLASS); /* all rulebooks */
        break;
    case PM_CAVE_DWELLER:
        ini_inv(Cave_man);

        /* Cavemen start with a random set of dragon scales.
         * Leave out Gray and Silver - on purpose */
        static const int trotyp[] = {
            GOLD_DRAGON_SCALES,
            SHIMMERING_DRAGON_SCALES,
            RED_DRAGON_SCALES,
            WHITE_DRAGON_SCALES,
            ORANGE_DRAGON_SCALES,
            BLACK_DRAGON_SCALES,
            BLUE_DRAGON_SCALES,
            GREEN_DRAGON_SCALES,
            YELLOW_DRAGON_SCALES
        };
        const struct trobj DragonScales[] =
        { { ROLL_FROM(trotyp), 0, ARMOR_CLASS, 1, 1, 0 },
          { 0, 0, 0, 0, 0, 0 } };
        ini_inv(DragonScales);

        knows_object(SLING_BULLET, FALSE);
        break;
    case PM_HEALER:
        u.umoney0 = rn1(1000, 1001);
        ini_inv(Healer);
        if (!rn2(25))
            ini_inv(Lamp);
        knows_object(POT_FULL_HEALING, FALSE);
        knows_object(HEALTHSTONE, FALSE);	/* KMH */
        knows_object(POT_BLOOD, FALSE);
        knows_object(POT_VAMPIRE_BLOOD, FALSE);
        /* Naturally familiar with healing items in their work */
        knows_object(POT_SICKNESS, FALSE);
        knows_object(POT_PARALYSIS, FALSE);
        knows_object(POT_SLEEPING, FALSE);
        knows_object(POT_RESTORE_ABILITY, FALSE);
        skill_init(Skill_H);
        break;
    case PM_KNIGHT:
        ini_inv(Knight);
        knows_class(WEAPON_CLASS); /* all weapons */
        knows_class(ARMOR_CLASS);
        /* give knights chess-like mobility--idea from wooledge@..cwru.edu */
        HJumping |= FROMOUTSIDE;
        break;
    case PM_MONK: {
        static const struct trobj *M_spell[] = { Healing_book,
                                                 Protection_book,
                                                 Confuse_monster_book };

        ini_inv(Monk);
        ini_inv(M_spell[rn2(90) / 30]); /* [0..2] */
        if (!rn2(10))
            ini_inv(Lamp);
        knows_class(ARMOR_CLASS);
        /* sufficiently martial-arts oriented item to ignore language issue */
        knows_object(SHURIKEN, FALSE);
        break;
    }
    case PM_CLERIC: /* priest/priestess */
        ini_inv(Priest);
        if (!rn2(10))
            ini_inv(Lamp);
        /* KMH, conduct --
         * Some may claim that this isn't agnostic, since they
         * are literally "priests" and they have holy water.
         * But we don't count it as such.  Purists can always
         * avoid playing priests and/or confirm another player's
         * role in their YAAP.
         */
        break;
    case PM_RANGER:
        ini_inv(Ranger);
        knows_class(WEAPON_CLASS); /* bows, arrows, spears only */
        break;
    case PM_ROGUE:
        u.umoney0 = 0;
        ini_inv(Rogue);
        if (!rn2(5))
            ini_inv(Blindfold);
        knows_object(SACK, FALSE); /* FALSE: don't override pauper here,
                                    * but sack will be made known in
                                    * pauper_reinit() */
        knows_class(WEAPON_CLASS); /* daggers only */
        break;
    case PM_SAMURAI:
        ini_inv(Samurai);
        if (!rn2(5))
            ini_inv(Blindfold);
        knows_class(WEAPON_CLASS); /* all weapons */
        knows_class(ARMOR_CLASS);
        /* in order to assist non-Japanese speakers, pre-discover items
           that switch to Japanese names when playing as a Samurai */
        for (i = MAXOCLASSES; i < NUM_OBJECTS; ++i) {
            if (objects[i].oc_magic) /* skip "magic koto" */
                continue;
            if (Japanese_item_name(i, (const char *) 0))
                /* we don't override pauper here because that would give
                   samarai an advantage of knowing several items in advance */
                knows_object(i, FALSE);
        }
        break;
    case PM_TOURIST:
        u.umoney0 = rnd(1000);
        ini_inv(Tourist);
        if (!rn2(25))
            ini_inv(Tinopener);
        else if (!rn2(25))
            ini_inv(Leash);
        else if (!rn2(25))
            ini_inv(Towel);

        break;
    case PM_UNDEAD_SLAYER: {
        /* The undead slayers starting kits also affect their
         * potential skill sets. */
        int kit = rn2(100) / 25;
        switch (kit) {
        case 0:	/* Crossbow and bolts */
            ini_inv(UndeadSlayer_0);
            break;
        case 1:	/* Whip and daggers */
            ini_inv(UndeadSlayer_1);
            break;
        case 2:	/* Default: Silver spear and daggers */
            ini_inv(UndeadSlayer_2);
            break;
        case 3: /* Silver short sword, silver daggers, and cloak */
            ini_inv(UndeadSlayer_3);
            break;
        }

        knows_class(WEAPON_CLASS);
        knows_class(ARMOR_CLASS);
        if (!rn2(6))
            ini_inv(Lamp);

        /* Kludge here to trigger Undead Warning */
        HWarn_of_mon = HUndead_warning;
        svc.context.warntype.intrins |= MH_UNDEAD;
        break;
    }
    case PM_VALKYRIE:
        ini_inv(Valkyrie);
        if (!rn2(6))
            ini_inv(Lamp);
        knows_class(WEAPON_CLASS); /* excludes polearms */
        knows_class(ARMOR_CLASS);
        break;
    case PM_WIZARD:
        ini_inv(Wizard);
        if (!rn2(5))
            ini_inv(Blindfold);
        if (rn2(100) >= 50) { /* see above comment */
            ini_inv(ForceBolt_book);
        } else {
            ini_inv(FireBolt_book);
        }
        break;
    default: /* impossible */
        break;
    }

    gn.nocreate = STRANGE_OBJECT;
    gn.nocreate2 = STRANGE_OBJECT;
    gn.nocreate3 = STRANGE_OBJECT;
    gn.nocreate4 = STRANGE_OBJECT;
}

/* race-specific initializations, same restrictions as u_init_role */
staticfn void
u_init_race(void)
{
    switch (Race_switch) {
    case PM_HUMAN:
        /* Nothing special */
        break;

    case PM_ELF:
        /*
         * Elves are people of music and song, or they are warriors.
         * Non-warriors get an instrument.  We use a kludge to
         * get only non-magic instruments.
         */
        if (Role_if(PM_CLERIC) || Role_if(PM_WIZARD)
            || Role_if(PM_HEALER) || Role_if(PM_ROGUE)
            || Role_if(PM_ARCHEOLOGIST) || Role_if(PM_CARTOMANCER)) {
            static const int trotyp[] = {
                CHEAP_FLUTE,
                TOOLED_HORN,
                CHEAP_HARP,
                BELL,
                BUGLE,
                WAR_DRUM
            };
            const struct trobj Instrument[] =
                { { ROLL_FROM(trotyp), 0, TOOL_CLASS, 1, 1, 0 },
                  { 0, 0, 0, 0, 0, 0 } };
            ini_inv(Instrument);
        }

        /* Elves can recognize all elvish objects */
        knows_object(ELVEN_SHORT_SWORD, FALSE);
        knows_object(ELVEN_LONG_SWORD, FALSE);
        knows_object(ELVEN_ARROW, FALSE);
        knows_object(ELVEN_BOW, FALSE);
        knows_object(ELVEN_SPEAR, FALSE);
        knows_object(ELVEN_DAGGER, FALSE);
        knows_object(ELVEN_BROADSWORD, FALSE);
        knows_object(ELVEN_RING_MAIL, FALSE);
        knows_object(ELVEN_HELM, FALSE);
        knows_object(ELVEN_SHIELD, FALSE);
        knows_object(ELVEN_BRACERS, FALSE);
        knows_object(ELVEN_BOOTS, FALSE);
        knows_object(ELVEN_CLOAK, FALSE);

        /* All elves have a natural affinity for enchantments */
        if (!Role_if(PM_CARTOMANCER))
            set_skill_cap_minimum(P_ENCHANTMENT_SPELL, P_BASIC);
        break;

    case PM_DWARF:
        /* Dwarves can recognize all dwarvish objects */
        knows_object(DWARVISH_SPEAR, FALSE);
        knows_object(DWARVISH_SHORT_SWORD, FALSE);
        knows_object(DWARVISH_MATTOCK, FALSE);
        knows_object(DWARVISH_HELM, FALSE);
        knows_object(DWARVISH_RING_MAIL, FALSE);
        knows_object(DWARVISH_CLOAK, FALSE);
        knows_object(DWARVISH_ROUNDSHIELD, FALSE);

        /* All dwarves have skill with digging tools */
        set_skill_cap_minimum(P_PICK_AXE, P_SKILLED);
        break;

    case PM_GNOME:
        knows_object(GNOMISH_HELM, FALSE);
        knows_object(GNOMISH_BOOTS, FALSE);
        knows_object(GNOMISH_SUIT, FALSE);
        u.nv_range = 2;

        /* Gnomes get an interesting tool.
         * Tourists already get many of these tools...
         **/
        static const struct trobj *G_tools[] = {
            Tinopener,
            Wax_Candles,
            Tallow_Candles,
            Figurine,
            GreaseCan,
            Towel
        };
        if (!Role_if(PM_TOURIST) && rn2(2)) {
            ini_inv(G_tools[rn2(120) / 20]); /* [0..6] */
        } else {
            ini_inv(OilPotion);
            knows_object(POT_OIL, FALSE);
        }

        /* All gnomes are familiar with crossbows and aklyses */
        set_skill_cap_minimum(P_CROSSBOW, P_SKILLED);
        set_skill_cap_minimum(P_CLUB, P_BASIC);
        break;

    case PM_ORC:
        /* compensate for generally inferior equipment */
        if (!Role_if(PM_WIZARD) && !Role_if(PM_UNDEAD_SLAYER))
            ini_inv(Xtra_food);
        /* Orcs carry poison */
        ini_inv(PoisonPotion);
        /* Orcs can recognize all orcish objects */
        knows_object(ORCISH_SHORT_SWORD, FALSE);
        knows_object(ORCISH_LONG_SWORD, FALSE);
        knows_object(ORCISH_SCIMITAR, FALSE);
        knows_object(ORCISH_ARROW, FALSE);
        knows_object(ORCISH_BOW, FALSE);
        knows_object(ORCISH_SPEAR, FALSE);
        knows_object(ORCISH_DAGGER, FALSE);
        knows_object(ORCISH_CHAIN_MAIL, FALSE);
        knows_object(ORCISH_RING_MAIL, FALSE);
        knows_object(ORCISH_HELM, FALSE);
        knows_object(ORCISH_SHIELD, FALSE);
        knows_object(URUK_HAI_SHIELD, FALSE);
        knows_object(ORCISH_CLOAK, FALSE);
        knows_object(ORCISH_BOOTS, FALSE);
        knows_object(POT_SICKNESS, FALSE);

        /* All orcs are familiar with scimitars */
        set_skill_cap_minimum(P_SABER, P_SKILLED);

        /* Orcs start off very bad alignment */
        adjalign(-20);
        break;

    case PM_DHAMPIR:
        knows_object(POT_VAMPIRE_BLOOD, FALSE);
        knows_object(POT_BLOOD, FALSE);
        /* Enable random generation too */
        objects[POT_VAMPIRE_BLOOD].oc_prob = 40;
        objects[POT_BLOOD].oc_prob = 40;

        /* Vampires start off with gods not as pleased, luck penalty */
        adjalign(-5);
        change_luck(-1);
        break;
    case PM_GRUNG:
        knows_object(GRUNG_BRACERS, FALSE);
        knows_object(SNAKESKIN_WRAP, FALSE);
        knows_object(SWAMPWING_VEST, FALSE);
        knows_object(SNAKEHIDE_JERKIN, FALSE);
        knows_object(SPIDER_RIB_SHELL, FALSE);
        knows_object(BEETLE_CARAPACE, FALSE);
        knows_object(DRAGONFLY_CLOAK, FALSE);
        knows_object(TURTLE_SHELL_HELM, FALSE);
        knows_object(SPORECAP_HOOD, FALSE);
        knows_object(PINCER_GAUNTLETS, FALSE);
        knows_object(TORTLE_SHELL_SHIELD, FALSE);
        knows_object(CRABBACK_SHIELD, FALSE);
        knows_object(FANG_NECKLACE, FALSE);
        knows_object(SPINEBACK_CUTTER, FALSE);
        knows_object(SKULLCLAW_MACE, FALSE);
        knows_object(CLAWBONE_HATCHET, FALSE);
        u.hydration = HYDRATION_MAX;
        /* All grung are familiar with darts */
        set_skill_cap_minimum(P_DART, P_SKILLED);
        set_skill_cap_minimum(P_AXE, P_BASIC);
        break;
    default: /* impossible */
        break;
    }
}

/* for 'pauper' aka 'unpreparsed'; take away any skills (bare-handed combat,
   riding) that are better than unskilled; learn the book (without carrying
   it or knowing its spell yet) for some key spells */
staticfn void
pauper_reinit(void)
{
    int skill, preknown = STRANGE_OBJECT;

    if (!u.uroleplay.pauper)
        return;

    for (skill = 0; skill < P_NUM_SKILLS; skill++)
        if (P_SKILL(skill) > P_UNSKILLED) {
            P_SKILL(skill) = P_UNSKILLED;
            P_ADVANCE(skill) = 0;
        }
    /* pauper has lost out on initial skills, but provide some unspent skill
       credits to make up for that */
    u.weapon_slots = 2;

    /* paupers don't know any spells yet, but several roles will recognize
       the spellbook for a key spell (not necessarily that role's special
       spell); "supply chests" on the first few levels provide a fairly
       high chance to find the book; some other roles know a non-book item */
    switch (Role_switch) {
    case PM_HEALER:
        preknown = SPE_HEALING;
        break;
    case PM_CLERIC:
    case PM_KNIGHT:
    case PM_MONK:
        preknown = SPE_PROTECTION;
        break;
    case PM_WIZARD:
        preknown = SPE_FORCE_BOLT;
        break;
    case PM_ARCHEOLOGIST:
        preknown = TOUCHSTONE;
        break;
    case PM_CAVE_DWELLER:
        preknown = FLINT;
        break;
    case PM_ROGUE:
    case PM_TOURIST:
        preknown = SACK;
        break;
    case PM_SAMURAI:
        /* food ration isn't interesting to discover, but put "gunyoki" into
           discoveries list for players who might not recognize what it is */
        preknown = FOOD_RATION;
        break;
    default:
    case PM_BARBARIAN:
    case PM_RANGER:
    case PM_VALKYRIE:
        break;
    }
    if (preknown != STRANGE_OBJECT)
        knows_object(preknown, TRUE);
}

/* boost STR and CON until hero can carry inventory */
staticfn void
u_init_carry_attr_boost(void)
{
    /* make sure you can carry all you have - especially for Tourists */
    while (inv_weight() > 0) {
        if (adjattrib(A_STR, 1, TRUE))
            continue;
        if (adjattrib(A_CON, 1, TRUE))
            continue;
        /* only get here when didn't boost strength or constitution */
        break;
    }
}

/* Adjust a skill cap to a specified minimum. */
staticfn void
set_skill_cap_minimum(int skill, int minimum)
{
    if (P_MAX_SKILL(skill) < minimum) {
        P_MAX_SKILL(skill) = minimum;

        if (P_SKILL(skill) == P_ISRESTRICTED) /* skill pre-set */
            P_SKILL(skill) = P_UNSKILLED;
    }
}

/* initialise u, except inventory, attributes, skills and discoveries */

void
u_init_misc(void)
{
    int i;
    struct u_roleplay tmpuroleplay = u.uroleplay; /* set by rcfile options */

    flags.female = flags.initgend;
    flags.beginner = Role_if(PM_TOURIST) ? TRUE : FALSE;

    /* zero u, including pointer values --
     * necessary when aborting from a failed restore */
    (void) memset((genericptr_t) &u, 0, sizeof(u));
    u.ustuck = (struct monst *) 0;
    (void) memset((genericptr_t) &ubirthday, 0, sizeof(ubirthday));
    (void) memset((genericptr_t) &urealtime, 0, sizeof(urealtime));

    u.uroleplay = tmpuroleplay; /* restore options set via rcfile */

#if 0  /* documentation of more zero values as desirable */
    u.usick_cause[0] = 0;
    u.uluck  = u.moreluck = 0;
    uarmu = 0;
    uarm = uarmc = uarmh = uarms = uarmg = uarmf = 0;
    uwep = uball = uchain = uleft = uright = 0;
    uswapwep = uquiver = 0;
    u.twoweap = FALSE; /* bypass set_twoweap() */
    u.ublessed = 0;                     /* not worthy yet */
    u.ugangr   = 0;                     /* gods not angry */
    u.ugifts   = 0;                     /* no divine gifts bestowed */
    u.uevent.uhand_of_elbereth = 0;
    u.uevent.uheard_tune = 0;
    u.uevent.uopened_dbridge = 0;
    u.uevent.uskilled = 0;
    u.uevent.udemigod = 0;              /* not a demi-god yet... */
    u.uevent.amulet_wish = 0;
    u.udg_cnt = 0;
    u.mh = u.mhmax = u.mtimedone = 0;
    u.uz.dnum = u.uz0.dnum = 0;
    u.utotype = UTOTYPE_NONE;
#endif /* 0 */

    u.uz.dlevel = 1;
    u.uz0.dlevel = 0;
    u.utolev = u.uz;

    u.umoved = FALSE;
    u.umortality = 0;
    u.ugrave_arise = NON_PM;

    u.umonnum = u.umonster = gu.urole.mnum;
    u.ulycn = NON_PM;
    set_uasmon();

    u.ulevel = 0; /* set up some of the initial attributes */
    u.uhp = u.uhpmax = u.uhppeak = newhp();
    u.uen = u.uenmax = u.uenpeak = newpw();
    u.uspellprot = 0;
    adjabil(0, 1);
    u.ulevel = u.ulevelmax = 1;

    init_uhunger();
    for (i = 0; i <= MAXSPELL; i++)
        svs.spl_book[i].sp_id = NO_SPELL;
    u.ublesscnt = 300; /* no prayers just yet */
    u.ualignbase[A_CURRENT] = u.ualignbase[A_ORIGINAL] = u.ualign.type =
        aligns[flags.initalign].value;

#if defined(BSD) && !defined(POSIX_TYPES)
    (void) time((long *) &ubirthday);
#else
    (void) time(&ubirthday);
#endif

    /*
     *  For now, everyone starts out with a night vision range of 1 and
     *  their xray range disabled.
     */
    u.nv_range = 1;
    u.xray_range = -1;
    u.unblind_telepat_range = -1;

    /* OPTIONS:blind results in permanent blindness (unless overridden
       by the Eyes of the Overworld, which will clear 'u.uroleplay.blind'
       to void the conduct, but will leave the PermaBlind bit set so that
       blindness resumes when the Eyes are removed). */
    if (u.uroleplay.blind)
        HBlinded |= FROMOUTSIDE; /* set PermaBlind */

    /* roughly based on distribution in human population */
    u.uhandedness = rn2(10) ? RIGHT_HANDED : LEFT_HANDED;

    max_rank_sz(); /* set max str size for class ranks */

    /* Same idea as above, cartomancers should be able to play summons right away. */
    if (Role_if(PM_CARTOMANCER) && u.uen < CARD_COST)
        u.uen = u.uenmax = CARD_COST;

    /* Quality-of-Life */
    knows_object(POT_WATER, FALSE);
    knows_object(SCR_BLANK_PAPER, FALSE);
    if (!Role_if(PM_CAVE_DWELLER))
        knows_object(SCR_IDENTIFY, FALSE);
    /* All roles know zapping scrolls so that the scroll of wishing is
       pre-known */
    knows_object(SCR_ZAPPING, TRUE);
    return;
}

/* the appropriate set of skills for the role */
staticfn const struct def_skill *
skills_for_role(void)
{
    const struct def_skill *skills;

    switch (Role_switch) {
    case PM_ARCHEOLOGIST:
        skills = Skill_A;
        break;
    case PM_BARBARIAN:
        skills = Skill_B;
        break;
    case PM_CARTOMANCER:
        skills = Skill_Car;
        break;
    case PM_CAVE_DWELLER:
        skills = Skill_C;
        break;
    case PM_HEALER:
        skills = Skill_H;
        break;
    case PM_KNIGHT:
        skills = Skill_K;
        break;
    case PM_MONK:
        skills = Skill_Mon;
        break;
    case PM_CLERIC:
        skills = Skill_P;
        break;
    case PM_RANGER:
        skills = Skill_Ran;
        break;
    case PM_ROGUE:
        skills = Skill_R;
        break;
    case PM_SAMURAI:
        skills = Skill_S;
        break;
    case PM_TOURIST:
        skills = Skill_T;
        break;
    case PM_UNDEAD_SLAYER:
        skills = Skill_U;
        break;
    case PM_VALKYRIE:
        skills = Skill_V;
        break;
    case PM_WIZARD:
        skills = Skill_W;
        break;
    default:
        panic("No skills found for role");
        break;
    }

    return skills;
}

/* skills aren't initialized, so we use the role-specific skill lists */
staticfn boolean
restricted_spell_discipline(int otyp)
{
    const struct def_skill *skills = skills_for_role();
    int this_skill = spell_skilltype(otyp);

    while (skills && skills->skill != P_NONE) {
        if (skills->skill == this_skill)
            return FALSE;
        ++skills;
    }
    return TRUE;
}

/* randomizes the quantity given a trobj description */
staticfn long
trquan(const struct trobj *trop)
{
    if (!trop->trquan_min)
        return 1;
    return trop->trquan_min + rn2(trop->trquan_max - trop->trquan_min + 1);
}

/* create random object of certain class, filtering out too powerful items */
staticfn struct obj *
ini_inv_mkobj_filter(int oclass, boolean got_level1_spellbook)
{
    struct obj *obj;
    int otyp, trycnt = 0;

    /*
     * For random objects, do not create certain overly powerful
     * items: wand of wishing, ring of levitation, or the
     * polymorph/polymorph control combination.  Specific objects,
     * i.e. the discovery wishing, are still OK.
     * Also, don't get a couple of really useless items.  (Note:
     * punishment isn't "useless".  Some players who start out with
     * one will immediately read it and use the iron ball as a
     * weapon.)
     */
    obj = mkobj(oclass, FALSE);
    otyp = obj->otyp;

    while (otyp == WAN_WISHING
           || otyp == gn.nocreate
           || otyp == gn.nocreate2
           || otyp == gn.nocreate3
           || otyp == gn.nocreate4
           || otyp == RIN_LEVITATION
           /* 'useless' items */
           || otyp == POT_HALLUCINATION
           || otyp == POT_ACID
           || otyp == SCR_AMNESIA
           || otyp == SCR_FLOOD
           || otyp == SCR_FIRE
           || otyp == SCR_BLANK_PAPER
           || otyp == SPE_BLANK_PAPER
           || otyp == RIN_AGGRAVATE_MONSTER
           || otyp == RIN_HUNGER
           || otyp == RIN_SLEEPING
           || otyp == RIN_WITHERING
           || otyp == WAN_NOTHING
           /* items that will be silver for dhampir (rings/wands perhaps) that can't
            * become copper */
           || (Race_if(PM_DHAMPIR) && objects[otyp].oc_material == SILVER
               && !valid_obj_material(obj, COPPER))
           /* TODO: also iron for elves? */
           /* TODO: also mithril for orcs? */
           /* orcs start with poison resistance */
           || (otyp == RIN_POISON_RESISTANCE
               && (Race_if(PM_ORC) || Race_if(PM_GRUNG)))
           /* Monks don't use weapons */
           || (otyp == SCR_ENCHANT_WEAPON && Role_if(PM_MONK))
           /* wizard patch -- they already have one of these */
           || (Role_if(PM_WIZARD)
               && (otyp == SPE_FORCE_BOLT || otyp == SPE_FIRE_BOLT))
           /* Make them hunt for it!*/
           || (otyp == SPE_MAGIC_MISSILE && Role_if(PM_WIZARD))
           /* powerful spells are either useless to
              low level players or unbalancing; also
              spells in restricted skill categories */
           || (obj->oclass == SPBOOK_CLASS
               && (objects[otyp].oc_level > (got_level1_spellbook ? 3 : 1)
                   || (restricted_spell_discipline(otyp)
                        && !Role_if(PM_CARTOMANCER))))
           || otyp == SPE_NOVEL) {
        dealloc_obj(obj);
        if (++trycnt > 1000) {
            /* This lonely pancake's potential will never be realized.
             * It will exist only as a thought, of something that could have
             * been, but never will be. It will never experience maple syrup
             * oozing into its nooks, or see the delightful expression on
             * someone's face as they are about to let it dance across their
             * taste buds. */
            obj = mksobj(PANCAKE, TRUE, FALSE);
            break;
        }
        obj = mkobj(oclass, FALSE);
        otyp = obj->otyp;
    }
    return obj;
}

/* substitute object with something else based on race.
   also can change class, and returns it. */
staticfn short
ini_inv_obj_substitution(const struct trobj *trop, struct obj *obj)
{
    if (gu.urace.mnum != PM_HUMAN) {
        int i;

        /* substitute race-specific items; this used to be in
           the 'if (otyp != UNDEF_TYP) { }' block above, but then
           substitutions didn't occur for randomly generated items
           (particularly food) which have racial substitutes */
        for (i = 0; inv_subs[i].race_pm != NON_PM; ++i)
            if (inv_subs[i].race_pm == gu.urace.mnum
                && obj->otyp == inv_subs[i].item_otyp) {
                debugpline3("ini_inv: substituting %s for %s%s",
                            OBJ_NAME(objects[inv_subs[i].subs_otyp]),
                            (trop->trotyp == UNDEF_TYP) ? "random " : "",
                            OBJ_NAME(objects[obj->otyp]));
                obj->otyp = inv_subs[i].subs_otyp;
                obj->oclass = objects[obj->otyp].oc_class;
            break;
        }
        /* Alignment based substitutions */
        for (i = 0; inv_asubs[i].align != A_NONE; ++i) {
            if (inv_asubs[i].align == u.ualign.type
                    && obj->otyp == inv_asubs[i].item_otyp) {
                debugpline3("ini_inv: substituting %s for %s%s",
                            OBJ_NAME(objects[inv_asubs[i].subs_otyp]),
                            (trop->trotyp == UNDEF_TYP) ? "random " : "",
                            OBJ_NAME(objects[obj->otyp]));
                obj->otyp = inv_asubs[i].subs_otyp;
                obj->oclass = objects[obj->otyp].oc_class;
                break;
            }
        }

    }
    return obj->otyp;
}

/* returns: TRUE to stop generating items from this trobj,
   FALSE for normal behaviour */
staticfn boolean
ini_inv_adjust_obj(const struct trobj *trop, struct obj *obj)
{
    boolean stop = FALSE;
    if (trop->trclass == COIN_CLASS) {
        /* no "blessed" or "identified" money */
        obj->quan = u.umoney0;
    } else {
        if (objects[obj->otyp].oc_uses_known)
            obj->known = 1;
        /* not observe_object during startup, that's handled later */
        obj->dknown = obj->bknown = obj->rknown = 1;
        if (Is_container(obj) || obj->otyp == STATUE) {
            obj->cknown = obj->lknown = 1;
            obj->otrapped = 0;
        }
        obj->cursed = (trop->trbless == CURSED);
        if (obj->opoisoned && u.ualign.type != A_CHAOTIC)
            obj->opoisoned = 0;
        if (obj->oclass == WEAPON_CLASS || obj->oclass == TOOL_CLASS) {
            obj->quan = trquan(trop);
            stop = TRUE;
        } else if (obj->oclass == GEM_CLASS && is_graystone(obj->otyp)
                   && obj->otyp != FLINT) {
            obj->quan = 1L;
        }

        /* Don't allow materials to be start scummed for */
        set_material(obj, objects[obj->otyp].oc_material);

        /* No aligned items or quality adjustments either */
        set_alignment(obj, FA_NONE);
        obj->bquality = FQ_NORMAL;

        /* Replace silver objects with copper for dhampir */
        if (Race_if(PM_DHAMPIR) && obj->material == SILVER) {
            set_material(obj, COPPER);
        }

        /* Undead Slayers get special silver weapons.
         * Before the object materials patch this was easy, but
         * looks like we'll just do it here. */
        if (Role_if(PM_UNDEAD_SLAYER)) {
            if (is_spear(obj) ||  obj->otyp == SHORT_SWORD
                || obj->otyp == DAGGER || obj->otyp == ELVEN_DAGGER)
                set_material(obj, SILVER);

            if (obj->otyp == JACKET || obj->otyp == CLOAK)
                set_material(obj, LEATHER);
        }

        if (trop->trspe != UNDEF_SPE) {
            obj->spe = trop->trspe;
        } else {
            /* Don't start with +0 or negative rings */
            if (objects[obj->otyp].oc_class == RING_CLASS
                && objects[obj->otyp].oc_charged && obj->spe <= 0)
                obj->spe = rne(3);
        }
        if (trop->trbless != UNDEF_BLESS)
            obj->blessed = (trop->trbless == 1);
    }
    /* defined after setting otyp+quan + blessedness */
    obj->owt = weight(obj);
    return stop;
}

/* initial inventory: wear, wield, learn the spell/obj */
staticfn void
ini_inv_use_obj(struct obj *obj)
{
    /* Make the type known if necessary */
    if (OBJ_DESCR(objects[obj->otyp]) && obj->known)
        discover_object(obj->otyp, TRUE, TRUE, FALSE);
    if (obj->otyp == OIL_LAMP)
        discover_object(POT_OIL, TRUE, TRUE, FALSE);

    if (obj->oclass == ARMOR_CLASS) {
        if (is_shield(obj) && !uarms && !(uwep && bimanual(uwep))) {
            setworn(obj, W_ARMS);
            /* Prior to 3.6.2 this used to unset uswapwep if it was set,
               but wearing a shield doesn't prevent having an alternate
               weapon ready to swap with the primary; just make sure we
               aren't two-weaponing (academic; no one starts that way) */
            set_twoweap(FALSE); /* u.twoweap = FALSE */
        }
        else if (is_bracer(obj) && !uarms)
            setworn(obj, W_ARMS);
        else if (is_helmet(obj) && !uarmh)
            setworn(obj, W_ARMH);
        else if (is_gloves(obj) && !uarmg)
            setworn(obj, W_ARMG);
        else if (is_shirt(obj) && !uarmu)
            setworn(obj, W_ARMU);
        else if (is_cloak(obj) && !uarmc)
            setworn(obj, W_ARMC);
        else if (is_boots(obj) && !uarmf)
            setworn(obj, W_ARMF);
        else if (is_suit(obj) && !uarm)
            setworn(obj, W_ARM);
    }

    /* Don't allow gear with object properties
     * to be start scummed for */
    obj->oprops = 0L;

    if (obj->oclass == WEAPON_CLASS || is_weptool(obj)
        || obj->otyp == TIN_OPENER
        || obj->otyp == FLINT || obj->otyp == ROCK) {
        if (is_ammo(obj) || is_missile(obj)) {
            if (!uquiver)
                setuqwep(obj);
        } else if (!uwep && (!uarms || !bimanual(obj))) {
            setuwep(obj);
        } else if (!uswapwep) {
            setuswapwep(obj);
        }
    }
    if (obj->oclass == SPBOOK_CLASS && obj->otyp != SPE_BLANK_PAPER)
        initialspell(obj);
}

staticfn void
ini_inv(const struct trobj *trop)
{
    struct obj *obj;
    int otyp;
    boolean got_sp1 = FALSE; /* got a level 1 spellbook? */
    long quan;

    if (u.uroleplay.pauper) /* pauper gets no items */
        return;

    quan = trquan(trop);
    while (trop->trclass) {
        otyp = (int) trop->trotyp;
        if (otyp != UNDEF_TYP) {
            obj = mksobj(otyp, TRUE, FALSE);
        } else { /* UNDEF_TYP */
            obj = ini_inv_mkobj_filter(trop->trclass, got_sp1);
            otyp = obj->otyp;
            /* Heavily relies on the fact that 1) we create wands
             * before rings, 2) that we create rings before
             * spellbooks, and that 3) not more than 1 object of a
             * particular symbol is to be prohibited.  (For more
             * objects, we need more nocreate variables...)
             */
            switch (otyp) {
            case WAN_POLYMORPH:
            case RIN_POLYMORPH:
            case POT_POLYMORPH:
                gn.nocreate = RIN_POLYMORPH_CONTROL;
                break;
            case RIN_POLYMORPH_CONTROL:
                gn.nocreate = RIN_POLYMORPH;
                gn.nocreate2 = SPE_POLYMORPH;
                gn.nocreate3 = POT_POLYMORPH;
            }
            /* Don't have 2 of the same ring or spellbook */
            if (obj->oclass == RING_CLASS || obj->oclass == SPBOOK_CLASS)
                gn.nocreate4 = otyp;
        }
        /* Put post-creation object adjustments that don't depend on whether
         * it was UNDEF_TYP or not after this. */

        otyp = ini_inv_obj_substitution(trop, obj);
        nhUse(otyp);

	/* Set up cartomancer cards */
        if (Role_if(PM_CARTOMANCER) && obj->otyp == SCR_CREATE_MONSTER) {
            obj->corpsenm = PM_RAVEN;
            bless(obj);
        }

        /* nudist gets no armor, vampires get no food */
        if ((u.uroleplay.nudist && obj->oclass == ARMOR_CLASS)
            || (Race_if(PM_DHAMPIR) && obj->oclass == FOOD_CLASS)) {
            dealloc_obj(obj);
            trop++;
            continue;
        }

        if (ini_inv_adjust_obj(trop, obj))
            quan = 1;
        obj = addinv(obj);

        /* First spellbook should be level 1 - did we get it? */
        if (obj->oclass == SPBOOK_CLASS && objects[obj->otyp].oc_level == 1)
            got_sp1 = TRUE;

        if (--quan)
            continue; /* make a similar object */
        trop++;
        quan = trquan(trop);
    }
}

/* initialise starting inventory and attributes

   this function can be run multiple times and will overwrite the effects of
   previous runs */
void
u_init_inventory_attrs(void)
{
    gl.lastinvnr = 51;
    while (gi.invent)
        useupall(gi.invent);

    u.umoney0 = 0;
    u_init_role();
    u_init_race();

    if (discover)
        ini_inv(Wishing);

    if (u.umoney0)
        ini_inv(Money);
    u.umoney0 += hidden_gold(TRUE); /* in case sack has gold in it */

    init_attr(75);    /* init attribute values */
    vary_init_attr(); /* minor variation to attrs */
    u_init_carry_attr_boost();
}

/* side effects of starting inventory (e.g. discovering it) and skills (both
   those based on role and those based on starting inventory) */
void
u_init_skills_discoveries(void)
{
    struct obj *otmp;
    for (otmp = gi.invent; otmp; otmp = otmp->nobj)
        ini_inv_use_obj(otmp);

    skill_init(skills_for_role());
    if (u.uroleplay.pauper)
        pauper_reinit();

    /* If we have at least one spell, force starting Pw to be enough,
       so hero can cast the level 1 spell they should have */
    if (num_spells() && (u.uenmax < SPELL_LEV_PW(1)))
        u.uen = u.uenmax = u.uenpeak = u.ueninc[u.ulevel] = SPELL_LEV_PW(1);

    find_ac();     /* get initial ac value */
}

#undef UNDEF_TYP
#undef UNDEF_SPE
#undef UNDEF_BLESS
#undef UNDEF_CURSED
/*u_init.c*/
