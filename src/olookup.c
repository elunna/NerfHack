/* NetHack 5.0	olookup.c	$NHDT-Date$  $NHDT-Branch: NetHack-5.0 $:$NHDT-Revision$ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2018. */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * This file contains the object-lookup ("What is this thing and what does
 * it do?") rendering logic for the encyclopedia/data.base window: add_obj_info()
 * and its objinfo_*() helpers. It was split out of pager.c, which retains the
 * dowhatis()/dohelp() command routines and the data.base file parsing that
 * feeds this code (add_obj_info() is called from pager.c's checkfile()).
 */

#include "hack.h"
#include "artifact.h"

/* declare-only mode: read access to artifact.c's single artilist[]
 * instance (see artilist.h) without duplicating its big initializer table */
#define ARTI_DECL
#include "artilist.h"
#undef ARTI_DECL

struct objinfo_ctx;
staticfn void objinfo_header(winid, const struct objinfo_ctx *, char *);
staticfn void objinfo_weapon(winid, const struct objinfo_ctx *);
staticfn void objinfo_armor(winid, const struct objinfo_ctx *);
staticfn void objinfo_food(winid, const struct objinfo_ctx *);
staticfn void objinfo_spellbook(winid, const struct objinfo_ctx *);
staticfn void objinfo_wand(winid, const struct objinfo_ctx *);
staticfn void objinfo_ring(winid, const struct objinfo_ctx *);
staticfn void objinfo_gem(winid, const struct objinfo_ctx *);
staticfn void objinfo_tool(winid, const struct objinfo_ctx *);
staticfn void objinfo_cost_weight(winid, const struct objinfo_ctx *);
staticfn void objinfo_probability(winid, const struct objinfo_ctx *);
staticfn void objinfo_ink_cost(winid, const struct objinfo_ctx *);
staticfn void objinfo_powers(winid, const struct objinfo_ctx *);
staticfn void objinfo_magic_and_material(winid, const struct objinfo_ctx *);
staticfn void objinfo_remarks(winid, const struct objinfo_ctx *);
staticfn void objinfo_recipes(winid, const struct objinfo_ctx *);
staticfn void objinfo_artifact(winid, const struct objinfo_ctx *);
staticfn const char *adtyp_str(int, boolean);

/* located in timeout.c */
extern const struct propname {
    int prop_num;
    const char *prop_name;
} propertynames[];

/* Shared, read-only context passed to the add_obj_info() family of
 * helpers below. reveal_info is the single gate for anything that would
 * otherwise leak an unidentified item's true type; see its assignment
 * in add_obj_info() for the exact rule. Route any new
 * identification-sensitive text through reveal_info (or is_artifact,
 * which is always fully revealed) rather than inventing a new check. */
struct objinfo_ctx {
    struct obj *obj;    /* real object, or Null for a pure name/dbase lookup */
    struct obj dummy;   /* stand-in instance of the same type, for helpers
                            that need an obj* but obj may be Null */
    short otyp;
    struct objclass oc; /* objects[otyp], copied out for convenience */
    char olet;
    const char *actualn;
    const char *dir;    /* "Non-directional"/"Beam"/"Ray", from oc_dir */
    boolean weptool;    /* TOOL_CLASS item usable as a weapon */
    boolean is_artifact;
    boolean show_corpse;
    boolean reveal_info;
};

#define OBJPUTSTR(str) putstr(datawin, ATR_NONE, str)
#define ADDCLASSPROP(cond, str)             \
    if (cond) {                             \
        if (*buf) { Strcat(buf, ", "); }    \
        Strcat(buf, str);                   \
    }

/* Add some information to an encyclopedia window which is printing information
 * about an object. */
void
add_obj_info(winid datawin, struct obj *obj, short otyp, char *usr_text)
{
    struct objinfo_ctx ctx;

    if (!otyp && obj)
        otyp = obj->otyp;

    ctx.obj = obj;
    ctx.otyp = otyp;
    ctx.oc = obj ? objects[obj->otyp] : objects[otyp];
    ctx.olet = ctx.oc.oc_class;
    ctx.actualn = OBJ_NAME(ctx.oc);
    ctx.dir = (ctx.oc.oc_dir == NODIR ? "Non-directional"
               : (ctx.oc.oc_dir == IMMEDIATE ? "Beam" : "Ray"));
    ctx.weptool = (ctx.olet == TOOL_CLASS && ctx.oc.oc_skill != P_NONE);
    /* If it's an artifact, we always have it in obj. */
    ctx.is_artifact = obj && obj->oartifact;
    ctx.show_corpse = obj && obj->otyp == CORPSE;
    /* the single gate for anything that would otherwise leak an
       unidentified item's true type: safe to reveal iff not
       hallucinating, and either this is a pure name/dbase lookup (no
       real obj in hand) or the held obj's type has actually been
       discovered. is_artifact bypasses it separately below, since a
       wielded/worn/named artifact is always fully revealed. */
    ctx.reveal_info = (boolean) (!Hallucination
                                  && (!obj || ctx.oc.oc_name_known));

    ctx.dummy = cg.zeroobj;
    ctx.dummy.otyp = otyp;
    ctx.dummy.oclass = ctx.olet;

    objinfo_header(datawin, &ctx, usr_text);

    if (ctx.olet == WEAPON_CLASS || ctx.weptool || ctx.olet == GEM_CLASS
        || otyp == BOULDER)
        objinfo_weapon(datawin, &ctx);

    if (ctx.olet == ARMOR_CLASS)
        objinfo_armor(datawin, &ctx);

    if (ctx.olet == FOOD_CLASS)
        objinfo_food(datawin, &ctx);

    if (ctx.olet == POTION_CLASS)
        /* nothing special */
        putstr(datawin, ATR_NONE, "Potion.");

    if (ctx.olet == SCROLL_CLASS)
        /* nothing special (ink is covered by objinfo_ink_cost()) */
        putstr(datawin, ATR_NONE, Role_if(PM_CARTOMANCER) ? "Card" : "Scroll.");

    if (ctx.olet == SPBOOK_CLASS)
        objinfo_spellbook(datawin, &ctx);

    if (ctx.olet == WAND_CLASS)
        objinfo_wand(datawin, &ctx);

    if (ctx.olet == RING_CLASS)
        objinfo_ring(datawin, &ctx);

    if (ctx.olet == GEM_CLASS)
        objinfo_gem(datawin, &ctx);

    if (ctx.olet == TOOL_CLASS && !ctx.weptool)
        objinfo_tool(datawin, &ctx);

    if (ctx.olet == AMULET_CLASS)
        putstr(datawin, ATR_NONE, "Amulet.");
    if (ctx.olet == COIN_CLASS)
        putstr(datawin, ATR_NONE, "Coin.");
    if (ctx.olet == ROCK_CLASS)
        putstr(datawin, ATR_NONE, otyp == STATUE ? "Statue." : "Boulder.");
    if (ctx.olet == BALL_CLASS)
        putstr(datawin, ATR_NONE, "Heavy iron ball.");
    if (ctx.olet == CHAIN_CLASS)
        putstr(datawin, ATR_NONE, "Chain.");
    if (ctx.olet == VENOM_CLASS)
        putstr(datawin, ATR_NONE, "Venom.");

    /* cost, wt should go next */
    objinfo_cost_weight(datawin, &ctx);
    objinfo_probability(datawin, &ctx);

    if (ctx.olet == SCROLL_CLASS || ctx.olet == SPBOOK_CLASS)
        objinfo_ink_cost(datawin, &ctx);

    objinfo_powers(datawin, &ctx);
    objinfo_magic_and_material(datawin, &ctx);

    /* TODO: prevent obj lookup from displaying with monster database entry
     * (e.g. scroll of light gives "light" monster database) */

    objinfo_remarks(datawin, &ctx);
    objinfo_recipes(datawin, &ctx);

    if (ctx.is_artifact)
        objinfo_artifact(datawin, &ctx);
}

staticfn void
objinfo_header(winid datawin, const struct objinfo_ctx *ctx, char *usr_text)
{
    char buf[BUFSZ];

    /* We have the object */
    if (ctx->obj && !ctx->is_artifact && !ctx->show_corpse)
        Sprintf(buf, "Object lookup for \"%s\":", xname(ctx->obj));
    else if (ctx->show_corpse)
        Sprintf(buf, "Object lookup for \"%s\":",
                corpse_xname(ctx->obj, (const char *) 0, CXN_NO_PFX));
    else if (ctx->is_artifact && !ctx->oc.oc_name_known)
        Sprintf(buf, "Object lookup for \"%s\":",
                artiname(ctx->obj->oartifact));
    else /* We don't have it and don't know it */
        Sprintf(buf, "Object lookup for \"%s\":",
                usr_text ? usr_text : ctx->actualn);

    putstr(datawin, ATR_BOLD, buf);
    putstr(datawin, ATR_NONE, "");
}

/* WEAPON INFO (also covers weapon-skill tools, gems, and boulders, all of
   which can be thrown or wielded) */
staticfn void
objinfo_weapon(winid datawin, const struct objinfo_ctx *ctx)
{
    struct damage_info_t damage_info;
    char buf[BUFSZ];
    const char *dmgtyp;
    const int skill = ctx->oc.oc_skill;
    /* ctx->dummy is a read-only stand-in; cast away const here rather
       than on the shared ctx, so is_launcher()/is_poisonable()/etc, which
       don't parenthesize their macro parameter before applying "->" to
       it, get a single token instead of a multi-token expression */
    struct obj *const dummy = (struct obj *) &ctx->dummy;

    if (skill >= 0) {
        Sprintf(buf, "%s-handed weapon%s using the %s skill.",
                (ctx->oc.oc_bimanual ? "Two" : "Single"),
                (ctx->weptool ? "-tool" : ""),
                skill_name(skill));
    } else if (is_ammo(dummy)) {
        /* Minor assumption: the skill name will be the same as the launcher
         * itself. Currently this is only bow and crossbow. */
        Sprintf(buf, "Ammunition meant to be fired from a %s.",
                skill_name(-skill));
    } else if (skill == -P_SLING) {
        Sprintf(buf, "Ammunition meant to be fired from %s.",
                skill_name(-skill));
    } else {
        Sprintf(buf, "Thrown missile using the %s skill.",
                skill_name(-skill));
    }
    OBJPUTSTR(buf);

    dmgtyp = "blunt";
    if (ctx->oc.oc_dir & PIERCE) {
        dmgtyp = "piercing";
        if (ctx->oc.oc_dir & SLASH)
            dmgtyp = "piercing/slashing";
    } else if (ctx->oc.oc_dir & SLASH) {
        dmgtyp = "slashing";
    }
    Sprintf(buf, "Deals %s damage.", dmgtyp);
    OBJPUTSTR(buf);

    damage_info = dmgval_info(dummy);

    if (ctx->reveal_info || ctx->is_artifact) {
        Sprintf(buf,
                "Damage:  1d%d%s versus small and 1d%d%s versus large monsters.",
                damage_info.damage_small, damage_info.bonus_small,
                damage_info.damage_large, damage_info.bonus_large);
        OBJPUTSTR(buf);
    } else {
        Sprintf(buf, "Damage: unknown");
        OBJPUTSTR(buf);
    }

    if (damage_info.buc_damage)
        OBJPUTSTR(damage_info.buc_damage);
    if (damage_info.axe_damage)
        OBJPUTSTR(damage_info.axe_damage);
    if (damage_info.light_damage)
        OBJPUTSTR(damage_info.light_damage);
    if (damage_info.mat_damage)
        OBJPUTSTR(damage_info.mat_damage);
    if (damage_info.hate_damage)
        OBJPUTSTR(damage_info.hate_damage);

    if (ctx->reveal_info || ctx->is_artifact) {
        Sprintf(buf, "Has a %s%d %s to hit.",
                (ctx->oc.oc_hitbon >= 0 ? "+" : ""), ctx->oc.oc_hitbon,
                (ctx->oc.oc_hitbon >= 0 ? "bonus" : "penalty"));
        OBJPUTSTR(buf);
    }

    if (is_launcher(dummy)) {
        Sprintf(buf, "Fires %s.",
                skill == P_BOW ? "arrows"
                : skill == P_CROSSBOW ? "crossbow bolts"
                                       : "sling bullets, stones, and gems");
        OBJPUTSTR(buf);
    }
    if (is_poisonable(dummy))
        OBJPUTSTR("Can be coated with poison.");
    if (is_multigen(dummy))
        OBJPUTSTR("Normally generated in stacks.");
}

/* ARMOR INFO */
staticfn void
objinfo_armor(winid datawin, const struct objinfo_ctx *ctx)
{
    /* Indexes here correspond to ARM_SHIELD, etc; not the W_* masks.
     * Expects ARM_SUIT = 0, all the way up to ARM_SHIRT = 6. */
    static const char *const armorslots[] = {
        "torso", "shield", "helm", "gloves", "boots", "cloak", "shirt"
    };
    char buf[BUFSZ];

    Sprintf(buf, "%s, worn in the %s slot.",
            (ctx->oc.oc_bulky ? "Bulky armor" : "Armor"),
            armorslots[ctx->oc.oc_armcat]);
    OBJPUTSTR(buf);

    if (ctx->reveal_info || ctx->is_artifact) {
        Sprintf(buf, "Base AC %d, magic cancellation %d.",
                ctx->oc.a_ac, ctx->oc.a_can);
        OBJPUTSTR(buf);
        Sprintf(buf, "Takes %d turn%s to put on or remove.",
                ctx->oc.oc_delay, (ctx->oc.oc_delay == 1 ? "" : "s"));
        OBJPUTSTR(buf);
    } else {
        Sprintf(buf, "Base AC %d.", ctx->oc.a_ac);
        OBJPUTSTR(buf);
    }

#if 0 /* Currently leaks info */
    /* APPEARANCE BONUSES */

    /* Effects based on the base description of the item --
        only one will apply, so an if-else chain is appropriate */
    if (objdescr_is(&ctx->dummy, "snow boots"))
        OBJPUTSTR("Prevents slipping on ice (snow boots)");
    else if (objdescr_is(&ctx->dummy, "combat boots"))
        OBJPUTSTR("+1AC, +1 to-hit for thrown (combat boots)");
    else if (objdescr_is(&ctx->dummy, "mud boots"))
        OBJPUTSTR("Protects against drowning attacks (mud boots)");
    else if (objdescr_is(&ctx->dummy, "hiking boots"))
        OBJPUTSTR("Increases carrying capacity (hiking boots)");
    else if (objdescr_is(&ctx->dummy, "jungle boots"))
        OBJPUTSTR("Reduces the severity of leg wounds (jungle boots)");
    else if (objdescr_is(&ctx->dummy, "old gloves"))
        OBJPUTSTR("Erosion resistant (old gloves)");
    else if (objdescr_is(&ctx->dummy, "padded gloves"))
        OBJPUTSTR("Slightly increased defense (padded gloves)");
    else if (objdescr_is(&ctx->dummy, "fencing gloves"))
        OBJPUTSTR("Increases to-hit when fighting with a free off-hand (fencing gloves)");
    else if (objdescr_is(&ctx->dummy, "visored helm"))
        OBJPUTSTR("Protects from blinding claws and venom (visored helm)");
#endif
}

/* COMESTIBLE INFO */
staticfn void
objinfo_food(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ], buf2[BUFSZ];

    /* TODO: Process tins later, note that spinach is NON_PM with spe=-1 */
    if (ctx->otyp == CORPSE) {
        if (ctx->obj && ctx->obj->known) {
            /* corpsenm is only meaningful for CORPSE; other comestibles
               (e.g. fortune cookie) leave it as NON_PM (-1), so mons[]
               must not be indexed with it outside this branch */
            int cnum = ctx->obj->corpsenm;
            struct permonst *pm = &mons[cnum];

            Sprintf(buf, "Comestible providing %d nutrition at the most.",
                    pm->cnutrit);
            OBJPUTSTR(buf);
            OBJPUTSTR("Takes various amounts of turns to eat.");

            /* Corpse conveyances */
            corpse_conveys(buf, pm);
            if (*buf) {
                Snprintf(buf2, BUFSZ, "Conveys %s.", buf);
                OBJPUTSTR(buf2);
            } else {
                OBJPUTSTR("Conveys no intrinsics.");
            }
            if (is_giant(pm))
                OBJPUTSTR("Conveys strength.");
            if (cnum == PM_LIZARD || acidic(pm))
                OBJPUTSTR("Consuming this can cure petrification.");
            /* poison is removed by the tinning process */
            if (poisonous(pm) && ctx->otyp != TIN)
                OBJPUTSTR("Is poisonous.");
            /* acid damage is removed by the tinning process */
            if (acidic(pm) && ctx->otyp != TIN)
                OBJPUTSTR("Is acidic.");
            if (is_were(pm))
                OBJPUTSTR("Conveys lycanthropy.");
            if (flesh_petrifies(pm))
                OBJPUTSTR("Consuming this can cause petrification.");
            if (ctx->otyp == GLOB_OF_GREEN_SLIME)
                OBJPUTSTR("Consuming this can cause sliming.");
            if ((amorphous(pm) || slithy(pm) || mons[cnum].mlet == S_BLOB)
                && mons[cnum].mlet != S_SNAKE
                && mons[cnum].mlet != S_NAGA
                && mons[cnum].mlet != S_MIMIC)
                OBJPUTSTR("Consuming this can cause slippery fingers.");
            if (cnum == PM_YELLOW_LIGHT || cnum == PM_GIANT_BAT
                || cnum == PM_ZOO_BAT || cnum == PM_BAT)
                OBJPUTSTR("Consuming this can cause stunning.");
            if (dmgtype(pm, AD_STUN) || dmgtype(pm, AD_HALU)
                || cnum == PM_VIOLET_FUNGUS)
                OBJPUTSTR("Consuming this can cause hallucination.");
            if (vegan(pm))
                OBJPUTSTR("Is vegan.");
            else if (vegetarian(pm))
                OBJPUTSTR("Is vegetarian but not vegan.");
            else
                OBJPUTSTR("Is not vegetarian.");
        } else {
            OBJPUTSTR("Comestible providing varied nutrition.");
            OBJPUTSTR("May or may not be vegetarian.");
        }
    } else {
        Sprintf(buf, "Comestible providing %d nutrition.",
                ctx->oc.oc_nutrition);
        OBJPUTSTR(buf);
        Sprintf(buf, "Takes %d turn%s to eat.", ctx->oc.oc_delay,
                (ctx->oc.oc_delay == 1 ? "" : "s"));
        OBJPUTSTR(buf);

        /* TODO: put special-case VEGGY foods in a list which can be
         * referenced by doeat(), so there's no second source for this. */
        if (ctx->oc.oc_material == FLESH && ctx->otyp != EGG) {
            OBJPUTSTR("Is not vegetarian.");
        } else {
            /* is either VEGGY food or egg */
            switch (ctx->otyp) {
            case PANCAKE:
            case FORTUNE_COOKIE:
            case EGG:
            case CREAM_PIE:
            case CANDY_BAR:
            case LUMP_OF_ROYAL_JELLY:
                OBJPUTSTR("Is vegetarian but not vegan.");
                break;
            default:
                OBJPUTSTR("Is vegan.");
            }
        }
    }
}

/* SPELLBOOK INFO */
staticfn void
objinfo_spellbook(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ];

    if (ctx->otyp == SPE_BLANK_PAPER || !ctx->reveal_info) {
        OBJPUTSTR(Role_if(PM_CARTOMANCER) ? "Rulebook" : "Spellbook");
    } else if (ctx->otyp == SPE_NOVEL || ctx->otyp == SPE_BOOK_OF_THE_DEAD) {
        OBJPUTSTR("Book.");
    } else {
        Sprintf(buf, "Level %d %s, in the %s school. %s spell.",
                ctx->oc.oc_level,
                Role_if(PM_CARTOMANCER) ? "Rulebook" : "Spellbook",
                spelltypemnemonic(ctx->oc.oc_skill), ctx->dir);
        OBJPUTSTR(buf);
        Sprintf(buf, "Takes %d actions to read.", ctx->oc.oc_delay);
        OBJPUTSTR(buf);
    }
}

/* WAND INFO */
staticfn void
objinfo_wand(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ];

    if (!ctx->reveal_info)
        Strcpy(buf, "Wand.");
    else
        Sprintf(buf, "%s wand.", ctx->dir);
    OBJPUTSTR(buf);
}

/* RING INFO */
staticfn void
objinfo_ring(winid datawin, const struct objinfo_ctx *ctx)
{
    OBJPUTSTR(ctx->reveal_info && ctx->oc.oc_charged
              ? "Chargeable ring." : "Ring.");
    /* see material comment in objinfo_magic_and_material(); only show
     * toughness status if this particular ring is already identified... */
    if (ctx->oc.oc_tough && ctx->oc.oc_name_known)
        OBJPUTSTR("Is made of a hard material.");
}

/* GEM INFO */
staticfn void
objinfo_gem(winid datawin, const struct objinfo_ctx *ctx)
{
    if (!(ctx->reveal_info || ctx->is_artifact))
        return;

    if (ctx->oc.oc_material == MINERAL)
        OBJPUTSTR("Type of stone.");
    else if (ctx->oc.oc_material == GLASS)
        OBJPUTSTR("Piece of colored glass.");
    else
        OBJPUTSTR("Precious gem.");
    /* can do unconditionally, these aren't randomized */
    if (ctx->oc.oc_tough)
        OBJPUTSTR("Is made of a hard material.");
}

/* TOOL INFO */
staticfn void
objinfo_tool(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ];
    const char *subclass = "tool";

    switch (ctx->otyp) {
    case LARGE_BOX:
    case CHEST:
    case ICE_BOX:
    case SACK:
    case OILSKIN_SACK:
    case BAG_OF_HOLDING:
        subclass = "container";
        break;
    case SKELETON_KEY:
    case LOCK_PICK:
    case CREDIT_CARD:
        subclass = "unlocking tool";
        break;
    case TALLOW_CANDLE:
    case WAX_CANDLE:
    case MAGIC_CANDLE:
    case LANTERN:
    case OIL_LAMP:
        subclass = "light source";
        break;
    case LAND_MINE:
    case BEARTRAP:
        subclass = "trap which can be set";
        break;
    case PEA_WHISTLE:
    case MAGIC_WHISTLE:
    case BELL:
    case WAR_DRUM:
    case DRUM_OF_EARTHQUAKE:
        subclass = "atonal instrument";
        break;
    case BUGLE:
    case MAGIC_FLUTE:
    case CHEAP_FLUTE:
    case TOOLED_HORN:
    case FIRE_HORN:
    case FROST_HORN:
    case CHEAP_HARP:
    case MAGIC_HARP:
        subclass = "tonal instrument";
        break;
    }
    Sprintf(buf, "%s%s.",
            (ctx->reveal_info && ctx->oc.oc_charged ? "chargeable " : ""),
            subclass);
    /* capitalize first letter of buf */
    buf[0] -= ('a' - 'A');
    OBJPUTSTR(buf);
}

/* cost, weight */
staticfn void
objinfo_cost_weight(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ];

    if (ctx->reveal_info)
        Sprintf(buf, "Base cost %d, weighs %d aum.", ctx->oc.oc_cost,
                ctx->show_corpse ? ctx->obj->owt : ctx->oc.oc_weight);
    else
        Sprintf(buf, "Weighs %d aum.", ctx->oc.oc_weight);
    OBJPUTSTR(buf);
}

/* random-generation probability */
staticfn void
objinfo_probability(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ];
    int j, pmil, totprob = 0;

    if (!ctx->reveal_info)
        return;

    if (!ctx->oc.oc_prob) {
        OBJPUTSTR("Not randomly generated.");
        return;
    }

    /* oc_prob values are relative weights, normalized over the
        class total at selection time (see mkobj); not every
        class sums its weights to 1000 */
    for (j = svb.bases[(int) ctx->olet];
         j < NUM_OBJECTS && objects[j].oc_class == ctx->olet; j++)
        totprob += objects[j].oc_prob;
    pmil = (ctx->oc.oc_prob * 1000 + totprob / 2) / totprob;
    if (pmil == 0)
        Sprintf(buf, "Makes up less than 0.1%% of randomly"
                     " generated %s.",
                (ctx->olet == GEM_CLASS) ? "gems and stones"
                                          : def_oc_syms[(int) ctx->olet].name);
    else
        Sprintf(buf, "Makes up %d.%d%% of randomly generated %s.",
                pmil / 10, pmil % 10,
                (ctx->olet == GEM_CLASS) ? "gems and stones"
                                          : def_oc_syms[(int) ctx->olet].name);
    OBJPUTSTR(buf);
}

/* Scrolls or spellbooks: ink cost */
staticfn void
objinfo_ink_cost(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ];

    if (ctx->otyp == SCR_BLANK_PAPER || ctx->otyp == SPE_BLANK_PAPER) {
        OBJPUTSTR("Can be written on.");
    } else if (ctx->otyp == SPE_NOVEL || ctx->otyp == SPE_BOOK_OF_THE_DEAD) {
        OBJPUTSTR("Cannot be written.");
    } else if (ctx->reveal_info) {
        Sprintf(buf, "Takes %d to %d ink to write.",
                ink_cost(ctx->otyp) / 2, ink_cost(ctx->otyp) - 1);
        OBJPUTSTR(buf);
    }
}

/* power conferred, plus assorted misc powers keyed off specific otyps */
staticfn void
objinfo_powers(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ];
    int i;

    if ((ctx->reveal_info || ctx->is_artifact) && ctx->oc.oc_oprop) {
        for (i = 0; propertynames[i].prop_name; ++i) {
            /* hack for alchemy smocks because everything about alchemy
               smocks is a hack */
            if (propertynames[i].prop_num == ACID_RES
                && ctx->otyp == ALCHEMY_SMOCK) {
                OBJPUTSTR("Confers acid resistance.");
                continue;
            }
            if (ctx->oc.oc_oprop == propertynames[i].prop_num) {
                /* proper grammar */
                const char *confers = "Makes you";
                const char *effect = propertynames[i].prop_name;

                switch (propertynames[i].prop_num) {
                    /* special overrides because prop_name is bad */
                    case STRANGLED:
                        effect = "choke";
                        break;
                    case LIFESAVED:
                        effect = "life saving";
                        FALLTHROUGH;
                        /*FALLTHRU*/
                    /* for things that don't work with "Makes you" */
                    case GLIB:
                    case WOUNDED_LEGS:
                    case DETECT_MONSTERS:
                    case SEE_INVIS:
                    case HUNGER:
                    case WARNING:
                    /* don't do special warn_of_mon */
                    case SEARCHING:
                    case INFRAVISION:
                    case AGGRAVATE_MONSTER:
                    case CONFLICT:
                    case JUMPING:
                    case TELEPORT_CONTROL:
                    case SWIMMING:
                    case SLOW_DIGESTION:
                    case HALF_SPDAM:
                    case HALF_PHDAM:
                    case REGENERATION:
                    case ENERGY_REGENERATION:
                    case WITHERING:
                    case PROTECTION:
                    case PROT_FROM_SHAPE_CHANGERS:
                    case POLYMORPH_CONTROL:
                    case FREE_ACTION:
                    case FIXED_ABIL:
                    case STOMPING:
                    case FLYING:
                    case REFLECTING:
                    case TREEWALK:
                        confers = "Confers";
                        break;
                    default:
                        break;
                }
                if (strstri(propertynames[i].prop_name, "resistance"))
                    confers = "Confers";
                Sprintf(buf, "%s %s.", confers, effect);
                OBJPUTSTR(buf);
            }
        }
    }

    if (!(ctx->reveal_info || ctx->is_artifact))
        return;

    if (ctx->otyp == GAUNTLETS_OF_FORCE) {
        OBJPUTSTR("Force open doors or locks, break boulders and iron bars.");
        OBJPUTSTR("Occasionally stuns enemies in hand-to-hand combat.");
    }
    if (ctx->otyp == TOWEL)
        OBJPUTSTR("Can cleanse grease and blood.");
    if (ctx->otyp == LUCKSTONE)
        OBJPUTSTR("Confers luck.");
    if (ctx->otyp == FOULSTONE)
        OBJPUTSTR("Confers aggravate monster and stench.");
    if (ctx->otyp == ROCK)
        OBJPUTSTR("Can be broken to produce flint stones.");
    if (ctx->otyp == FLINT) {
        OBJPUTSTR("Can be applied to arrows for extra damage (only cave dwellers).");
        OBJPUTSTR("Can be rubbed on iron to produce monster-scaring sparks.");
    }
    if (ctx->otyp == SILVER_DRAGON_SCALES)
        OBJPUTSTR("Protects from bright lights.");
    else if (ctx->otyp == GOLD_DRAGON_SCALES) {
        OBJPUTSTR("Permanent light source.");
        OBJPUTSTR("Confers hallucination resistance.");
    } else if (ctx->otyp == SHIMMERING_DRAGON_SCALES)
        OBJPUTSTR("Confers stun resistance.");
    else if (ctx->otyp == RED_DRAGON_SCALES)
        OBJPUTSTR("Confers infravision.");
    else if (ctx->otyp == WHITE_DRAGON_SCALES)
        OBJPUTSTR("Confers slow digestion.");
    else if (ctx->otyp == ORANGE_DRAGON_SCALES)
        OBJPUTSTR("Confers free action.");
    else if (ctx->otyp == BLUE_DRAGON_SCALES)
        OBJPUTSTR("Confers very fast speed.");
    else if (ctx->otyp == GREEN_DRAGON_SCALES)
        OBJPUTSTR("Confers sickness resistance.");
    else if (ctx->otyp == SHADOW_DRAGON_SCALES)
        OBJPUTSTR("Confers sleep resistance.");
    else if (ctx->otyp == YELLOW_DRAGON_SCALES)
        OBJPUTSTR("Confers petrification resistance.");
}

/* "inherently magical" class property, and material (including the list
 * of alternate materials this object type can randomly generate as).
 *
 * Note that we should not show the material of certain objects if they are
 * subject to description shuffling that includes materials. If the player
 * has already discovered this object, though, then it's fine to show the
 * material.
 * Object classes where this may matter: rings, wands, spellbooks (leather
 * vs cloth vs paper...). All randomized tools share materials, and all
 * scrolls and potions are the same material. */
staticfn void
objinfo_magic_and_material(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ], buf2[BUFSZ];
    const char *mat_str;
    int mat;

    buf[0] = '\0';
    if (ctx->reveal_info)
        ADDCLASSPROP(ctx->oc.oc_magic, "inherently magical");
    if (*buf) {
        Snprintf(buf2, BUFSZ, "Is %s.", buf);
        OBJPUTSTR(buf2);
    }

    /* materialnm[] gives the adjective form, which is what's wanted here
     * for every material except these two, which don't double as nouns */
    mat_str = materialnm[ctx->oc.oc_material];
    if (ctx->oc.oc_material == WOOD)
        mat_str = "wood";
    else if (ctx->oc.oc_material == VEGGY)
        mat_str = "vegetable matter";

    if (!ctx->reveal_info
        && ((ctx->olet == GEM_CLASS && !is_graystone(ctx->otyp))
            || ctx->olet == RING_CLASS || ctx->olet == WAND_CLASS
            || ctx->olet == SPBOOK_CLASS))
        Sprintf(buf, "Standard material is unknown.");
    else
        Sprintf(buf, "Normally made of %s.", mat_str);
    OBJPUTSTR(buf);

    /* other materials this object type can randomly generate as; the
       dummy stands in for a generic non-artifact instance */
    buf[0] = '\0';
    /* NUM_MATERIAL_TYPES is MINERAL, the last valid material index, not a
       count, so this needs <= to include it (e.g. "stone") */
    for (mat = 1; mat <= NUM_MATERIAL_TYPES; mat++) {
        if (mat == (int) ctx->oc.oc_material)
            continue;
        if (valid_obj_material((struct obj *) &ctx->dummy, mat))
            ADDCLASSPROP(TRUE, materialnm[mat]);
    }
    if (*buf) {
        Snprintf(buf2, BUFSZ, "Can also be made of %s.", buf);
        OBJPUTSTR(buf2);
    }
}

/* Full-line remarks */
staticfn void
objinfo_remarks(winid datawin, const struct objinfo_ctx *ctx)
{
    if (ctx->oc.oc_merge)
        OBJPUTSTR("Merges with identical items.");
    if (ctx->oc.oc_unique)
        OBJPUTSTR("Unique item.");
}

/* forge recipes, potion alchemy (#dip), and gem alchemy (#dip) */
staticfn void
objinfo_recipes(winid datawin, const struct objinfo_ctx *ctx)
{
    char buf[BUFSZ];
    const struct ForgeRecipe *recipe;
    const struct PotionRecipe *precipe;
    boolean has_recipes = FALSE;
    int i;

    /* forge recipes */
    if (ctx->reveal_info && !ctx->is_artifact) {
        for (recipe = fusions; recipe->result_typ; recipe++) {
            if (ctx->otyp == recipe->typ1 || ctx->otyp == recipe->typ2
                || ctx->otyp == recipe->result_typ) {
                if (!has_recipes) {
                    OBJPUTSTR("");
                    OBJPUTSTR("Forging recipes:");
                    has_recipes = TRUE;
                }
                Sprintf(buf, "  %d %s + %d %s = %s",
                        recipe->quan_typ1, OBJ_NAME(objects[recipe->typ1]),
                        recipe->quan_typ2, OBJ_NAME(objects[recipe->typ2]),
                        OBJ_NAME(objects[recipe->result_typ]));
                OBJPUTSTR(buf);
            }
        }
    }

    /* potion alchemy */
    /* This can involve potions, gems, unicorn horn */
    if (ctx->reveal_info) {
        for (precipe = potionrecipes; precipe->result_typ; precipe++) {
            if (ctx->otyp == precipe->typ1 || ctx->otyp == precipe->typ2
                || ctx->otyp == precipe->result_typ) {
                if (!has_recipes) {
                    OBJPUTSTR("");
                    OBJPUTSTR("Potion alchemy recipes (#dip):");
                    has_recipes = TRUE;
                }
                Sprintf(buf, "  %-13s + %-13s = %s%s",
                        OBJ_NAME(objects[precipe->typ1]),
                        OBJ_NAME(objects[precipe->typ2]),
                        OBJ_NAME(objects[precipe->result_typ]),
                        precipe->chance == 3 ? " (3/10)"
                        : precipe->chance == 6 ? " (6/10)" : "");
                OBJPUTSTR(buf);
            }
        }
    }

    /* gem alchemy: dipping this gem into acid */
    if (ctx->reveal_info && ctx->olet == GEM_CLASS) {
        struct obj *potion = mksobj(POT_ACID, FALSE, FALSE);
        struct obj *gem = mksobj(ctx->otyp, FALSE, FALSE);
        short mixture = mixtype(gem, potion);

        obfree(potion, (struct obj *) 0);
        obfree(gem, (struct obj *) 0);

        if (ctx->otyp == DILITHIUM_CRYSTAL) {
            OBJPUTSTR("");
            OBJPUTSTR("Gem alchemy recipes (#dip):");
            OBJPUTSTR("  dilithium crystal + acid = an explosion.");
        } else if (mixture > 0) {
            const char *identified_potion_name = OBJ_NAME(objects[mixture]);
            boolean potion_known = objects[mixture].oc_name_known;

            OBJPUTSTR("");
            OBJPUTSTR("Gem alchemy recipes (#dip):");
            Sprintf(buf, "  %-13s + acid = %s potion.",
                    OBJ_NAME(objects[ctx->otyp]),
                    an(OBJ_DESCR(objects[mixture])));
            if (potion_known && identified_potion_name)
                Sprintf(eos(buf) - 1, " (%s).", identified_potion_name);
            OBJPUTSTR(buf);
        }
    }

    /* gem alchemy: dipping acid into this potion, or (for acid itself)
       listing every gem that turns into a potion when dipped into it */
    if (ctx->reveal_info) {
        if (ctx->otyp == POT_ACID) {
            OBJPUTSTR("");
            OBJPUTSTR("Gem alchemy recipes (#dip):");
            for (i = svb.bases[GEM_CLASS]; i <= JADE; i++) {
                const char *result = gem_to_potion(i);

                if (i == DILITHIUM_CRYSTAL) {
                    OBJPUTSTR("  dilithium crystal + acid = an explosion");
                } else if (result) {
                    struct obj *potion
                        = mksobj(figure_out_potion(result), FALSE, FALSE);

                    Sprintf(buf, "  %-13s + acid = %s",
                            OBJ_NAME(objects[i]),   /* The gem */
                            xname(potion));         /* The potion */
                    OBJPUTSTR(buf);
                    obfree(potion, (struct obj *) 0);
                }
            }
        } else if (ctx->olet == POTION_CLASS
                   && objects[ctx->otyp].oc_name_known) {
            int gem = potion_to_gem(ctx->otyp);

            if (gem) {
                struct obj *potion = mksobj(ctx->otyp, FALSE, FALSE);

                OBJPUTSTR("");
                Sprintf(buf, "  %-13s + acid = %s.",
                        OBJ_NAME(objects[gem]), xname(potion));
                OBJPUTSTR(buf);
                obfree(potion, (struct obj *) 0);
            }
        }
    }
}

/* create an obj containing otyp and oartifact from a name.
 * this is used when looking up artifact names in pager.c
 * Modeled after artifact_name */
struct obj *
get_faux_artifact_obj(const char *name)
{
    struct obj *obj = 0;
    const struct artifact *a;
    register const char *aname;
    int index = 1;

    if (!strncmpi(name, "the ", 4))
        name += 4;

    for (a = artilist + 1; a->otyp; a++) {
        aname = a->name;
        if (!strncmpi(aname, "the ", 4))
            aname += 4;
        if (!strcmpi(name, aname)) {
            obj = mksobj(a->otyp, TRUE, FALSE);
            obj->otyp = a->otyp;
            obj->oartifact = index;
            break;
        }
        index++;
    }
    return obj;
}

struct art_info_t
artifact_info(int anum)
{
    struct art_info_t art_info = { 0 };
    char buf[QBUFSZ];
    art_info.name = artiname(anum);
    art_info.alignment = align_str(artilist[anum].alignment);
    art_info.cost = artilist[anum].cost;
    art_info.role = (artilist[anum].role == NON_PM)
                        ? "None" : mons[artilist[anum].role].pmnames[NEUTRAL];
    art_info.race = (artilist[anum].race == NON_PM)
                        ? "None" : mons[artilist[anum].race].pmnames[NEUTRAL];
    art_info.intelligent = (artilist[anum].spfx & SPFX_INTEL) != 0;
    art_info.restricted = (artilist[anum].spfx & SPFX_RESTR) != 0;
    art_info.nogen = (artilist[anum].spfx & SPFX_NOGEN) != 0;
    art_info.speaks = (artilist[anum].spfx & SPFX_SPEAK) != 0;
    art_info.beheads = (artilist[anum].spfx & SPFX_BEHEAD) != 0;
    art_info.vscross = (artilist[anum].spfx & SPFX_DALIGN) != 0;

    /* Hated/Targeted Monster */
    if (artilist[anum].mtype) {
        int i;
        buf[0] = '\0';

        for (i = 0; i < 32; i++) {
            if (artilist[anum].mtype & (1UL << i)) {
                strcat(buf, makeplural(mon_race_name(1UL << i)));
                Strcat(buf, " ");
            }
        }
        art_info.hates = malloc(100);
        strcpy(art_info.hates, buf);
    }

    /* Special attacks */
    if (artilist[anum].attk.adtyp
          || artilist[anum].attk.damn || artilist[anum].attk.damd) {
        Sprintf(buf, "%s, +%d to-hit, +1d%d damage",
                adtyp_str(artilist[anum].attk.adtyp, FALSE),
                artilist[anum].attk.damn,
                artilist[anum].attk.damd);
        art_info.attack = malloc(100);
        strcpy(art_info.attack, buf);

        /* Does this deal double damage? */
        if (artilist[anum].attk.damd == 0) {
            art_info.dbldmg = malloc(100);
            if (art_info.hates) {
                Sprintf(buf, "double damage vs %s", art_info.hates);
                strcpy(art_info.dbldmg, buf);
            } else
                strcpy(art_info.dbldmg, "deals double damage");
        }
    } else
        art_info.attack = NULL;

    /* Granted while wielded. */
    if (artilist[anum].defn.adtyp) {
        Sprintf(buf, "%s", adtyp_str(artilist[anum].defn.adtyp, TRUE));
        art_info.wield_res = malloc(100);
        strcpy(art_info.wield_res, buf);
    }

    if ((artilist[anum].spfx & SPFX_FLYING) != 0)
        art_info.wielded[0] = "flying";
    if ((artilist[anum].spfx & SPFX_SEARCH) != 0)
        art_info.wielded[1] = "searching";
    if ((artilist[anum].spfx & SPFX_HALRES) != 0)
        art_info.wielded[2] = "hallucination resistance";
    if ((artilist[anum].spfx & SPFX_ESP) != 0)
        art_info.wielded[3] = "telepathy";
    if ((artilist[anum].spfx & SPFX_STLTH) != 0)
        art_info.wielded[4] = "stealth";
    if ((artilist[anum].spfx & SPFX_REGEN) != 0)
        art_info.wielded[5] = "regeneration";
    if ((artilist[anum].spfx & SPFX_EREGEN) != 0)
        art_info.wielded[6] = "energy regeneration";
    if ((artilist[anum].spfx & SPFX_HSPDAM) != 0)
        art_info.wielded[7] = "half spell damage";
    if ((artilist[anum].spfx & SPFX_HPHDAM) != 0)
        art_info.wielded[8] = "half physical damage";
    if ((artilist[anum].spfx & SPFX_TCTRL) != 0)
        art_info.wielded[9] = "teleport control";
    if ((artilist[anum].spfx & SPFX_LUCK) != 0)
        art_info.wielded[10] = "luck";
    if ((artilist[anum].spfx & SPFX_XRAY) != 0)
        art_info.wielded[11] = "astral vision";
    if ((artilist[anum].spfx & SPFX_REFLECT) != 0)
        art_info.wielded[12] = "reflection";
    if ((artilist[anum].spfx & SPFX_PROTECT) != 0)
        art_info.wielded[13] = "protection";
    if ((artilist[anum].spfx & SPFX_BREATHE) != 0)
        art_info.wielded[14] = "magical breathing";
    if ((artilist[anum].spfx & SPFX_SEEINV) != 0)
        art_info.wielded[15] = "see invisible";
    if ((artilist[anum].spfx & SPFX_DISPLAC) != 0)
        art_info.wielded[16] = "displacement";
    if ((artilist[anum].spfx & SPFX_FAST) != 0)
        art_info.wielded[17] = "very vast";
    if ((artilist[anum].spfx & SPFX_PROTSC) != 0)
        art_info.wielded[18] = "protection vs shapechangers";
    if ((artilist[anum].spfx & SPFX_BAGGRV) != 0)
        art_info.wielded[19] = "suppresses aggravate monster";
    if ((artilist[anum].spfx & SPFX_STABLE) != 0)
        art_info.wielded[20] = "steadfastness";

    if ((artilist[anum].spfx & SPFX_WARN) != 0) {
        if ((artilist[anum].spfx & SPFX_DFLAGH) != 0) {
            Sprintf(buf, "warning against %s ", art_info.hates);
            art_info.wield_warn = malloc(100);
            strcpy(art_info.wield_warn, buf);
        } else {
            if (!art_info.wield_warn) art_info.wield_warn = malloc(100);
            strcpy(art_info.wield_warn, "warning");
        }
    }
    /* Granted while carried. */
    if (artilist[anum].cary.adtyp) {
        Sprintf(buf, "%s", adtyp_str(artilist[anum].cary.adtyp, TRUE));
        art_info.carr_res = malloc(100);
        strcpy(art_info.carr_res, buf);
    }
    if ((artilist[anum].cspfx & SPFX_FLYING) != 0)
        art_info.carried[0] = "flying";
    if ((artilist[anum].cspfx & SPFX_SEARCH) != 0)
        art_info.carried[1] = "searching";
    if ((artilist[anum].cspfx & SPFX_HALRES) != 0)
        art_info.carried[2] = "hallucination resistance";
    if ((artilist[anum].cspfx & SPFX_ESP) != 0)
        art_info.carried[3] = "telepathy";
    if ((artilist[anum].cspfx & SPFX_STLTH) != 0)
        art_info.carried[4] = "stealth";
    if ((artilist[anum].cspfx & SPFX_REGEN) != 0)
        art_info.carried[5] = "regeneration";
    if ((artilist[anum].cspfx & SPFX_EREGEN) != 0)
        art_info.carried[6] = "energy regeneration";
    if ((artilist[anum].cspfx & SPFX_HSPDAM) != 0)
        art_info.carried[7] = "half spell damage";
    if ((artilist[anum].cspfx & SPFX_HPHDAM) != 0)
        art_info.carried[8] = "half physical damage";
    if ((artilist[anum].cspfx & SPFX_TCTRL) != 0)
        art_info.carried[9] = "teleport control";
    if ((artilist[anum].cspfx & SPFX_LUCK) != 0)
        art_info.carried[10] = "luck";
    if ((artilist[anum].cspfx & SPFX_XRAY) != 0)
        art_info.carried[11] = "astral vision";
    if ((artilist[anum].cspfx & SPFX_REFLECT) != 0)
        art_info.carried[12] = "reflection";
    if ((artilist[anum].cspfx & SPFX_PROTECT) != 0)
        art_info.carried[13] = "protection";
    if ((artilist[anum].cspfx & SPFX_BREATHE) != 0)
        art_info.carried[14] = "magical breathing";
    if ((artilist[anum].cspfx & SPFX_SEEINV) != 0)
        art_info.carried[15] = "see invisible";
    if ((artilist[anum].cspfx & SPFX_DISPLAC) != 0)
        art_info.carried[16] = "displacement";
    if ((artilist[anum].cspfx & SPFX_FAST) != 0)
        art_info.carried[17] = "very fast";
    if ((artilist[anum].cspfx & SPFX_WARN) != 0)
        art_info.carried[18] = "warning";

    switch (artilist[anum].inv_prop) {
    case TAMING: art_info.invoke = "Taming"; break;
    case HEALING: art_info.invoke = "Healing"; break;
    case ENERGY_BOOST: art_info.invoke = "Energy Boost"; break;
    case UNTRAP: art_info.invoke = "Untrap"; break;
    case CHARGE_OBJ: art_info.invoke = "Charge Object"; break;
    case LEV_TELE: art_info.invoke = "Level Teleport"; break;
    case CREATE_PORTAL: art_info.invoke = "Branchport"; break;
    case ENLIGHTENING: art_info.invoke = "Enlightenment"; break;
    case CREATE_AMMO: art_info.invoke = "Create Ammo"; break;
    case BANISH: art_info.invoke = "Banish demon"; break;
    case BLINDING_RAY: art_info.invoke = "Blinding ray"; break;
    case LIGHTNING_BOLT: art_info.invoke = "Lightning Bolt"; break;
    case SUMMONING: art_info.invoke = "Card drop boost"; break;
    case UNCURSE_INVK: art_info.invoke = "Uncurse Inventory"; break;
    /* The following are properties converted to invokes */
    case CONFLICT: art_info.invoke = "Conflict"; break;
    case LEVITATION: art_info.invoke = "Levitation"; break;
    case INVIS: art_info.invoke = "Invisibility"; break;
    case WWALKING: art_info.invoke = "Water Walking"; break;
    case FLYING: art_info.invoke = "Flying"; break;

    default:
        art_info.invoke = "None"; break;
    }

    /* Extra hard-coded info (not possible to automate into the lookup) */
    switch (anum) {
    case ART_ACIDFALL:
        art_info.xinfo = "dissolves iron bars when thrown at them";
        break;
    case ART_AMULET_OF_STORMS:
        art_info.wielded[20] = "pacify stormy monsters via #chat";
        art_info.wielded[21] = "prevents thunderstorm paralysis";
        break;
    case ART_CLEAVER:
        art_info.xattack = "wide slashing arc";
        break;
    case ART_DAVID_S_SLING:
        art_info.xattack = "instakills giants while slinging; +1d6 damage vs other targets";
        break;
    case ART_DEMONBANE:
        art_info.wielded[20] = "angers demons princes and lords";
        art_info.wielded[21] = "blocks demon gating";
        art_info.xattack = "instakills lesser demons; triples damage vs demon lords/princes";
        break;
    case ART_DOOMBLADE:
        art_info.xattack = "bonus damage";
        break;
    case ART_DRAGONBANE:
        art_info.wielded[20] = "protects from dragon roars";
        art_info.xattack = "instakills dragons; triples damage vs unique dragons";
        break;
    case ART_EXCALIBUR:
        art_info.wielded[20] = "angers demons princes and lords";
        art_info.wielded[21] = "always tracks monsters";
        break;
    case ART_EYES_OF_THE_OVERWORLD:
        art_info.wielded[16] = "blocks all gaze attacks";
        art_info.wielded[17] = "negates cancellation attacks (Monks only)";
        break;
    case ART_FIRE_BRAND:
        art_info.xattack = "instantly destroys flammable, wooden, and green slime foes";
        break;
    case ART_FROST_BRAND:
        art_info.xattack = "shatters water elementals instantly";
        break;
    case ART_GIANTSLAYER:
        art_info.wielded[21] = "boosts strength";
        art_info.xattack = "instakills giants; triples damage vs unique giants";
        break;
    case ART_GRIMTOOTH:
        art_info.xattack = "sickness attack";
        break;
    case ART_HEART_OF_AHRIMAN:
        art_info.carried[19] = "Barbarians: chance of a fiery nova on hit";
        break;
    case ART_HELLFIRE:
        art_info.xattack = "bolts explode in a fireball on impact";
        break;
    case ART_LOAD_BRAND:
        art_info.wielded[21] = "negates curses";
        break;
    case ART_MAGICBANE:
        art_info.wielded[20] = "negates curses";
        art_info.wielded[21] = "extra vulnerable to magic traps";
        art_info.xattack = "chance to stun, scare, or cancel foes; weaker at high enchantment";
        break;
    case ART_MASTER_KEY_OF_THIEVERY:
        art_info.carried[19] = "warns of nearby trapped locks; guarantees trap detection & disarming (Rogues: uncursed, others: blessed)";
        break;
    case ART_MAYHEM:
        art_info.wielded[20] = "conflict";
        break;
    case ART_MIRRORBRIGHT:
        art_info.wielded[20] = "does not impede spellcasting";
        art_info.wielded[21] = "light source";
        break;
    case ART_MOUSER_S_SCALPEL:
        art_info.xattack = "chance to unleash a flurry of extra strikes";
        break;
    case ART_ARGENT_CROSS:
        art_info.wielded[20] = "turns undead";
        art_info.wielded[21] = "light source";
        break;
    case ART_MITRE_OF_HOLINESS:
        art_info.wielded[16] = "1/4 less physical damage from undead and demons (Priests only)";
        break;
    case ART_ORB_OF_DETECTION:
        art_info.carried[20] = "clairvoyance";
        break;
    case ART_OGRESMASHER:
        art_info.wielded[16] = "boosts constitution";
        art_info.xattack = "instakills ogres; chance to knock back smaller foes";
        break;
    case ART_MORTALITY_DIAL:
        art_info.wielded[16] = "prevents monster regeneration";
        break;
    case ART_ORCRIST:
    case ART_GLAMDRING:
        art_info.xattack = "instakills orcs";
        break;
    case ART_ANGELSLAYER:
        art_info.xattack = "instakills angels";
        break;
    case ART_ORIGIN:
        art_info.wielded[16] = "boosts spellcasting";
        art_info.wielded[21] = "extra vulnerable to magic traps";
        break;
    case ART_PLAGUE:
        art_info.xattack = "auto-poisons arrows";
        break;
    case ART_PRIDWEN:
        art_info.wielded[20] = "steadfastness";
        break;
    case ART_SCEPTRE_OF_MIGHT:
        art_info.wielded[20] = "steadfastness";
        art_info.wielded[21] = "blocks spellcasting";
        break;
    case ART_SERENITY:
        art_info.wielded[18] = "blocks spellcasting";
        art_info.wielded[20] = "counters spells";
        art_info.wielded[21] = "suppresses berserking";
        art_info.wielded[22] = "suppresses conflict";
        break;
    case ART_SERPENT_S_TONGUE:
        art_info.xattack = "always poisoned";
        break;
    case ART_SNICKERSNEE:
        art_info.xattack = "can strike at a distance like a polearm, once per turn";
        break;
    case ART_STING:
        art_info.wielded[20] = "cuts through webs effortlessly";
        art_info.xattack = "instakills orcs";
        break;
    case ART_STORMBRINGER:
        art_info.xinfo = "compels the wielder to attack, even peaceful monsters, without confirmation";
        break;
    case ART_TROLLSBANE:
        art_info.wielded[16] = "prevents troll revival";
        art_info.xattack = "instakills trolls in a burst of flame";
        break;
    case ART_TSURUGI_OF_MURAMASA:
        art_info.xattack = "bisects any foe, including headless ones; double damage instead vs huge monsters";
        break;
    case ART_WEREBANE:
        art_info.xattack = "instakills lycanthropes";
        break;
    case ART_OATHFIRE:
        art_info.wielded[20] = "passive fire damage";
        break;

#if 0
    case ART_ELFRIST:
        art_info.xattack = "instakills elves";
        break;
    case ART_BALMUNG:
        art_info.xattack = "Shreds armor";
        /*Balmung always resists destruction */
        break;
    case ART_MYSTIC_EYES:
        art_info.wielded[16] = "confers Death Vision";
        art_info.wielded[17] = "confers hallucination";
        break;
    case ART_LUCKLESS_FOLLY:
        art_info.xinfo = "cursed luck bonuses";
        break;
    case ART_TREASURY_OF_PROTEUS:
        art_info.xinfo = "polymorphs contents";
        art_info.carried[17] = "negates curses";
        break;
#endif
    default:
        art_info.xinfo = "";
    }

    return art_info;
}

staticfn const char *
adtyp_str(int adtyp, boolean defend)
{
    switch (adtyp) {
        case AD_ACID: return defend ? "acid resistance" : "acid";
        case AD_BLND: return defend ? "blinding resistance" : "blinding";
        case AD_COLD: return defend ? "cold resistance" : "cold";
        case AD_DETH: return defend ? "death resistance" : "death";
        case AD_DISE: return defend ? "sickness resistance" : "disease";
        case AD_DISN: return defend ? "disintegration resistance" : "disintegration";
        case AD_DREN: return "drain energy";
        case AD_DRLI: return defend ? "drain resistance" : "drain life";
        case AD_DRST: return defend ? "poison resistance" : "poison";
        case AD_ELEC: return defend ? "shock resistance" : "shock";
        case AD_FIRE: return defend ? "fire resistance" : "fire";
        case AD_MAGM: return defend ? "magic resistance" : "magic missile";
        case AD_PHYS: return "physical";
        case AD_PLYS: return defend ? "free action" : "paralyze";
        case AD_SLEE: return defend ? "sleep resistance" : "sleep";
        case AD_SLOW: return "slow";
        case AD_STON: return defend ? "petrification resistance" : "petrification";
        case AD_STUN: return defend ? "stun resistance" : "stuns/magic";
        case AD_WEBS: return "webs";
        case AD_WERE: return defend ? "lycanthropy resistance" : "lycanthropy";
        case AD_WTHR: return defend ? "withering resistance" : "withering";
        default:impossible("adtyp_str: Bad AD_TYPE! [%d]", adtyp);
    }
    return "";
}

/* ARTIFACT PROPERTIES; only called when ctx->is_artifact, so ctx->obj is
 * guaranteed non-Null */
staticfn void
objinfo_artifact(winid datawin, const struct objinfo_ctx *ctx)
{
    struct obj *obj = ctx->obj;
    struct art_info_t a_info = artifact_info(obj->oartifact);
    char buf[BUFSZ];
    boolean wielded, carried;
    int i;

    /* Make it look like it fits with the first section */
    Sprintf(buf, "Base Cost: %d ", a_info.cost);
    OBJPUTSTR(buf);

    OBJPUTSTR("");
    Sprintf(buf, "~~~ Artifact: %s ~~~", a_info.name);
    OBJPUTSTR(buf);

    Sprintf(buf, "Type: %s ", OBJ_NAME(objects[obj->otyp]));
    OBJPUTSTR(buf);

    Sprintf(buf, "Alignment: %s ", a_info.alignment);
    OBJPUTSTR(buf);
    if (a_info.intelligent)
        OBJPUTSTR("Intelligent");
    if (a_info.speaks)
        OBJPUTSTR("Capable of speaking");
    if (a_info.restricted)
        OBJPUTSTR("Restricted (cannot be #named)");
    if (a_info.nogen)
        OBJPUTSTR("Does not generate randomly.");

    Sprintf(buf, "Associated class/race: %s/%s ",
            a_info.role, a_info.race);
    OBJPUTSTR(buf);

    if (artifact_light(obj))
        OBJPUTSTR("Artifact light source");

    if (a_info.attack) {
        OBJPUTSTR("Special attack(s):");
        Sprintf(buf, "\t%s ", a_info.attack);
        OBJPUTSTR(buf);

        if (a_info.beheads)
            OBJPUTSTR("\tbeheads");
        if (a_info.vscross)
            OBJPUTSTR("\tbonus vs cross-aligned monsters");
        if (a_info.dbldmg) {
            Sprintf(buf, "\t%s ", a_info.dbldmg);
            OBJPUTSTR(buf);
        }
        if (a_info.xattack) {
            Sprintf(buf, "\t%s ", a_info.xattack);
            OBJPUTSTR(buf);
        }
    }

    if (a_info.hates) {
        Sprintf(buf, "Bane vs: %s ", a_info.hates);
        OBJPUTSTR(buf);
    }

    wielded = FALSE;
    OBJPUTSTR("While wielded/worn:");
    if (a_info.wield_res) {
        Sprintf(buf, "\t%s", a_info.wield_res);
        OBJPUTSTR(buf);
    }
    if (a_info.wield_warn) {
        Sprintf(buf, "\t%s", a_info.wield_warn);
        OBJPUTSTR(buf);
    }
    for (i = 0; i < INTRINSICS; i++) {
        if (a_info.wielded[i]) {
            Sprintf(buf, "\t%s", a_info.wielded[i]);
            OBJPUTSTR(buf);
            wielded = TRUE;
        }
    }
    if (!wielded && !a_info.wield_res && !a_info.wield_warn)
        OBJPUTSTR("\tNone");

    carried = FALSE;
    OBJPUTSTR("While carried:");
    if (a_info.carr_res) {
        Sprintf(buf, "\t%s", a_info.carr_res);
        OBJPUTSTR(buf);
    }
    for (i = 0; i < INTRINSICS; i++) {
        if (a_info.carried[i]) {
            Sprintf(buf, "\t%s", a_info.carried[i]);
            OBJPUTSTR(buf);
            carried = TRUE;
        }
    }
    if (!carried && !a_info.carr_res)
        OBJPUTSTR("\tNone");

    Sprintf(buf, "When #invoked: %s ", a_info.invoke);
    OBJPUTSTR(buf);

    if (a_info.xinfo)
        OBJPUTSTR(a_info.xinfo);

    /* Free some of these manually */
    free(a_info.wield_warn);
    free(a_info.wield_res);
    free(a_info.carr_res);
    free(a_info.attack);
    free(a_info.dbldmg);
    free(a_info.hates);
}

#undef OBJPUTSTR
#undef ADDCLASSPROP

