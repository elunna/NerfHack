/* NetHack 5.0	oprops.h	$NHDT-Date$  $NHDT-Branch: NetHack-5.0 $:$NHDT-Revision$ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Erik Lunna, 2026. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef OPROPS_H
#define OPROPS_H

/* clang-format off */

/* object properties */

/* When adding new properties:
 * - IMPORTANT: Update the MAX_ITEM_PROPS and ITEM_PROP_MASK!
 * - Also update ITEM_RES_PROPS, ITEM_GOOD_PROPS, and ITEM_BAD_PROPS below.
 * - Also, check existing items for properties that would be redundant and add
 *   them to is_redundant_prop and rm_redundant_oprops.
 */
#define ITEM_FLAME        0x00000001L /* fire damage or resistance */
#define ITEM_FROST       0x00000002L /* frost damage or resistance */
#define ITEM_SLEEP       0x00000004L /* sleep resistance */
#define ITEM_SHOCK       0x00000008L /* shock damage or resistance */

#define ITEM_VENOM       0x00000010L /* poison damage or resistance */
#define ITEM_ACID        0x00000020L /* acid damage or resistance */
#define ITEM_DRAIN       0x00000040L /* drains life or resistance */
#define ITEM_FILTH       0x00000080L /* disease damage or sickness resistance */

#define ITEM_PEACE       0x00000100L /* block aggravate monster */
#define ITEM_VIGIL       0x00000200L /* greater searching, evade flanks */
#define ITEM_STEALTH     0x00000400L /* stealth */
#define ITEM_WARN        0x00000800L /* warning */

#define ITEM_INSIGHT     0x00001000L /* see invisible */
#define ITEM_CHA         0x00002000L /* charisma boost */
#define ITEM_FUMBLE      0x00004000L /* fumbling */
#define ITEM_HUNGER      0x00008000L /* hunger */

#define ITEM_BURDEN      0x00010000L /* stability, but item weighs more */
#define ITEM_RAGE        0x00020000L /* bloodthirsty, double weapon damage */
#define ITEM_DANGER      0x00040000L /* infravision + increased difficulty */
#define ITEM_STENCH      0x00080000L /* aggravate monster, prevents digestion
                    * stenchy items cannot be eaten by players or monsters */

#define ITEM_SUSTAIN     0x00100000L /* preservation, items retain enchantment */
#define ITEM_CARRY       0x00200000L /* increases carry cap by 100 */
#define ITEM_HEXING      0x00400000L /* Adds 3d6 dmg, inflicts 2d6 to user
                               * causes confusion and absorbs curses easily */
#define ITEM_MR          0x00800000L /* Magic resistance */

#define ITEM_NULLING     0x01000000L /* Cancels enemies */
#define ITEM_INTEGRITY   0x02000000L /* Disintegration and withering res */

#define ITEM_PROP_MASK   0x03FFFFFFL /* all current properties */
#define MAX_ITEM_PROPS            26

/* Property and otyp property lookup table */
struct PropTypes{
    int prop;
    int flag;
};

extern const struct PropTypes prop_lookup[]; /* table of properties */

/* Properties that grant both a worn resistance and attack type */
#define ITEM_RES_PROPS (ITEM_FLAME | ITEM_FROST | ITEM_SHOCK | ITEM_VENOM \
                      | ITEM_ACID | ITEM_DRAIN | ITEM_SLEEP | ITEM_FILTH)
/* Positive properties */
#define ITEM_GOOD_PROPS (ITEM_PEACE | ITEM_VIGIL | ITEM_STEALTH | ITEM_WARN \
                         | ITEM_INSIGHT | ITEM_CHA | ITEM_RAGE \
                         | ITEM_CARRY | ITEM_MR | ITEM_NULLING | ITEM_INTEGRITY)
/* Negative properties */
#define ITEM_BAD_PROPS (ITEM_FUMBLE | ITEM_HUNGER | ITEM_BURDEN | ITEM_DANGER \
                        | ITEM_STENCH | ITEM_HEXING)

#define ONLY_ARM_PROPS (ITEM_MR | ITEM_INTEGRITY | ITEM_SUSTAIN)
/* Tend to give only weapons the props that appear naturally on
 * items like armor and rings. For exaple, stealth is already
 * provided by the elven cloak, elven boots, and ring of stealth.  */
#define ONLY_WEP_PROPS (ITEM_RAGE | ITEM_HEXING | ITEM_NULLING)

#define u_wield_oprop(oprop) ((uwep && (uwep->oprops & oprop)) \
    || (u.twoweap && uswapwep && (uswapwep->oprops & oprop)))

/* clang-format on */

#endif /* OPROPS_H */
