# NerfHack 3.0.0 — Changelog

NerfHack 3.0 is the clearest step yet toward the game I've always believed
NetHack could be at its finest. So much of classic NetHack's difficulty is held
together by meta-knowledge — price identification, altar farming, wish engines,
long exploit chains — and every one of those tricks quietly turns a living
dungeon into a solved puzzle. This release keeps pulling them out from under the
player, so the game plays less like a spreadsheet to be optimized and more like
a dangerous dungeon that pushes back.

But difficulty without generosity is just punishment, and 3.0 gives as deliberately
as it takes: variable materials, item properties, build quality, and even
item alignment make the loot you find worth studying, forging, and building a
run around.


Major changes since **NerfHack 2.2.1** (May 2025 – September 2026). This release
rebases the variant onto the newly released **vanilla NetHack 5.0.0** and layers
a large amount of new content, systems, and rebalancing on top. This document
lists the significant, player- and packager-facing changes; routine
bug/crash/leak fixes and features that were added and later reverted within the
cycle are omitted. Because of the new base, a few engine and interface entries
below originate from NetHack 5.0 rather than NerfHack itself.


---

## New base — NetHack 5.0.0

- Rebased/merged onto released vanilla **NetHack 5.0.0**, inheriting all of
  5.0's content and engine:

## Item systems overhaul

- **Materials** (greatly expanded): items generate in varied materials with
  damage/behavior effects; new **cold iron/coldsteel**, **chiton** (Grung
  gear), and **gemstone/gold/platinum** supermaterials; "metal" renamed
  **steel** and can now rust; mithril and silver made much rarer; dragonhide
  is flimsy and removed from supermaterials so it can rot; racial
  (elven/dwarvish) material lists; mail-type armor restricted to metal, crystal
  plate hardcoded to gemstone; robes changed to cloth; amulets default to iron.
  Worn accessories always touch skin (material damage), and armor/cloaks no longer
  block an amulet's material damage; iron's sear damage reduced.
- **Object properties ("oprops")**: items roll special properties shown in
  `{curly braces}` — burden, rage, danger, stench, carrying, nulling,
  integrity, disease, venom, magic-resistance (armor), **Peace** (was ESP;
  also blocks berserk), **preservation** (was stasis), **vigilance** (revamped
  searching), and Hexed (was Nasty). Antimagic now also blocks the *wearer's*
  spellcasting; wish-time oprops are filtered and wizard-gated.
- **Build quality** (inferior → standard → superior → exceptional →
  legendary): affects to-hit, sear damage, and breakage; forgeable. Inferior
  armor no longer imposes an AC penalty but crumbles when it blocks a hit;
  inferior aklys/boomerangs/launchers are now breakable.
- **Item alignment**: aligned items grant a bonus to matching heroes,
  cross-aligned items blast you like hated items, and are valued at 2×; racial
  alignment constraints fixed (were backwards).
- **Forging** expanded: dip items into forges, new recipes, duplicates/mixed
  qualities, retouch hammers; role/race restrictions removed; reachable via
  mouse menu.

## Monsters

- **New (~20):** soul shadow and degenerator (inflict vulnerability), shadow
  dragon / baby shadow dragon, shadow wolf, giant shoggoth, chiton golem,
  crystallid, basilisket, blight sprite, bone naga, boulderer, bandikot
  (untameable), plague rat, carrion crawler and carrion larva, elven mage,
  hill giant shaman, giant scorpion (saddleable), illusion, and disguised
  werefoo. (koala removed - replaced by bandikot)
- **Dragons:** baby-dragon overhaul; all adults can swallow/engulf, gain
  passive attacks, and can flank; they rage when you wear matching scales;
  breath damage increased; dragons and dragon scales rebalanced; guaranteed
  adults in the Wyrm Caves, Castle, and Ludios.
- **Demons and casters:** blood imps come in fast groups with a spell attack;
  dretches summon dretches and gain a passive rot attack; nupperibo, rutterkin,
  and quasit reworked; the Wizard of Yendor casts from a dedicated spell list
  with weakened melee; Vlad and Asmodeus gain/buff spellcasting.
- Shadow monsters are much harder to detect and dim the lights as they move;
  piercers and trappers retry hiding to a ~90% rate and deal level-scaling
  damage (no 4d6 cap); insects/"bugs" stripped of most resistances; worm-that-walks
  maggots flee and seek corpses to infest; broad rebalances to Titans,
  lieutenants/captains, krakens, cerastes, and more; Cthulhu is now the only
  covetous non-warper.

## Monster AI and behavior

- **Gear AI overhaul:** monsters loot carried containers for gear and stash
  spares, dual-wield a secondary weapon, pick the most effective weapon of a
  type, re-arm outside combat, use ranged ammo sensibly, value
  resistance-granting oprops, avoid redundant rings, and gear up within one
  turn.
- Hostile monsters now pursue and attack pets; `M2_IGNOREPETS` extended to
  quest nemeses, angels, mind flayers, deep ones, maggots, phoenix, and gnolls.
- Berserking and rabid monsters now respect Elbereth and magical scaring;
  zombies ignore Elbereth outright; covetous monsters teleport to the stairs;
  aggravate monster now turns peaceful monsters hostile.

## New mechanics and systems

- **Monster-vulnerability system** (dNetHack): monsters can be vulnerable to
  specific damage types, materials, and weapon types; inflicted by ice traps,
  magic traps, soul shadows, and degenerators; a vulnerability spell (EvilHack)
  and the potion of milk cure it; vulnerability also drains the affected
  intrinsic.
- **Monster spellcasting overhaul** (NetHack 5.0 + CrecelleHack): per-monster
  custom spell lists, a short-range spell class, and monster spells that also
  hit other monsters.
- **Choking (AD_CHOK):** rope golem/stalker grab-and-strangle attack that
  suppresses its own claw attacks while gripping.
- **Displacement rework:** displaced monsters visually float, grant no combat
  evasion (hero-vs-monster and monster-vs-monster), and no longer scramble the
  warning display. (FIQHack)
- **Warning-disruption overhaul:** stable warning positions, disrupted by
  Confusion, magic-trap proximity, and short-outs.
- **Spell-beings:** summoned creatures and mirror-image illusions are now
  temporary "spell beings"; illusions can be created only by the mirror-image
  spell.
- **Monster familiarity ("unknown tins"):** a tin names its contents only once
  you are familiar with that monster (by eating, smelling a corpse,
  polymorphing into it, or killing it up close); amnesia and mind-flayer
  brain-eating erode that familiarity.
- **Ice boxes** freeze stashed, tipped, or scripted corpses/objects, and pause
  only rotting and mold — never revival or zombification.
- Tree-walking (walk through and hide in trees; wood nymphs grow a tree on
  death); traitorous pets/monsters; monster group leaders and support casters;
  expanded rabid/diseased status; the SKIN body part and bloody tiles
  (EvilHack).

## Difficulty, balance, and anti-exploit

- **Wish-source purge:** removed wands/scrolls of wishing from the Castle and
  special levels, magic lamps, wand-of-wonder wishes, water-demon/djinn/throne
  wishes, and the deck of fate; wishing can no longer pick up the Amulet of
  Yendor.
- **Sacrifice and altars:** altar-cracking reworked (EvilHack); altars start
  appearing at Dlvl 3; temple donation costs scale with the hero's alignment abuse.
- **Farming and erosion:** lizard-corpse nutrition greatly reduced;
  item-collectors now grudge lizards; disenchanter attacks strip erodeproofing.
- **Combat and magic:** death ray reworked (12d12 baseline, reflection reduced
  to a 25% shield); touch of death is unconditionally fatal without Antimagic;
  magic resistance is only a 90% shield against involuntary polymorph and only
  shortens (rather than blocks) confusion/stun/paralyze/weaken; cancellation
  zeroes the hero's magic energy; wand ray damage scales with the zapper's
  experience level.
- Skill overhaul: higher advancement requirements, one master-level weapon per
  role, a bigger master-tier damage bonus, and only the first thrown projectile
  trains skill; no role exceeds basic skill in club; 
- enchant armor/weapon generation odds restored to 5.0.
- scroll of exile is now a targetable effect

## Roles and races

- **Undead Slayer** fleshed out: stealth and a +3 crossbow, fast speed at L10,
  poison resistance at L15, expert mace/flail, Disrupter as first sacrifice
  gift; elven variant starts with elven ring mail.
- **Dhampir** reworked: EvilHack-style vampire hunger, hunger + regeneration at
  L12, Flying at L24, bone-armor bonus, cannot gain fire resistance, and can
  gain intrinsics from eating while polymorphed.
- **Grung** race: always spawn with poisoned projectiles; hydration/dehydration
  mechanic; searching at L13; racial equipment substitutions; red grung can
  flank.
- **Cartomancer** role: cards from cracked altars and revived/cancelled monsters,
  crystal-ball clairvoyance (now blocks blindness), Deluder as crowning gift,
  and an XL15 ability to BUC-identify all scrolls/cards.
- Elves gain see-invisible at XP1 and vomit when eating meat; 
- Barbarians start with an axe plus a mid weapon; 
- Wizard/Archeologist/Caveman starting kits and sacrifice gifts reworked;
- crowning now requires 13 Luck.

## Spells, magic, and combat

- New/ported spells: **NOOSE** and **LOADSTONE** (dNetHack), illusion /
  mirror image, call undead (creates spell-beings), betray, disenchant
  (xNetHack), and make familiar/pool/minion; touch of death buffed; Raise Dead
  removed.
- Magic missile damage now scales with skill; monster-cast spells also hit
  monster targets; **flanking/outflanking** combat added (role-based
  outflankers, monsters jumping into flanking position, and `ITEM_VIGIL`
  flank-evasion for defenders).
- Hero-dealt AD_ACID now reliably corrodes the defender's gear (removed the 2/3
  "nothing happens" gate; main and offhand rolled separately); unarmed
  hand/foot attacks carry weapon-style damage types; self-zapping a wand of
  opening frees you from strangulation;
- spellcasting failure scales with proximity to anti-magic traps.

## Dungeon, levels, and branches

- Rogue level re-enabled (the bones contain a war hammer);
- Sokoban "Stacked Dozen" variant;
- temples are always lit;
- Moloch's Temple may hold a bag of holding

## Interface, display, and accessibility

- **Object-lookup overhaul** (`olookup.c`): shows alternate materials,
  generation frequency, corpse info, and previously-hidden artifact behaviors.
  **Pokedex** additions: damage/material vulnerabilities, saddleability,
  edibility, "grows into" form, kebab-ability, and whether a monster ignores
  Elbereth / how it wanders.
- Typed-name prompts replaced with cursor/menu selection (scroll of exile,
  controlled polymorph, scroll of knowledge); oprops/quality/alignment shown in
  descriptions; **left-handed** wielding/gear references fixed; new
  `classic_statues` option (pre-3.6 backtick glyph, on by default); TTY
  status-line fixes (3-line conditions no longer erased; weapon/armor/terrain
  text no longer drifts); mouse UI (forging reachable, toilets default to
  sitting); a fully documented `sys/unix/nerfhackrc.template` shipped for
  packagers.

## Notable bug fixes

- **Save-corruption fix:** worn-item pointers were being wiped by ordinary
  saves (not just shutdown).
- Restore no longer crashes when a game was saved while hallucinating and
  wielding a hated item.
- Hardened the monster death pipeline against wand-explosion chain-reaction
  double-detach crashes (root-cause fix); exploding wand of digging dropping
  the hero through the floor fixed; scroll of destroy armor now actually
  destroys armor; gold dragon scales keep their light after polymorph reversion
  (#138); cold-trap HP-vs-maxHP check fixed (#154); several `rn2(0)`
  divide-by-zero crashes fixed.

## Developer tooling, build, and infrastructure

- **Unattended rr record/replay fuzzing harness** with a turn cap and crash
  triage, rotating scenario profiles (special levels, pets, cursed wands, cold
  code paths, thrones/toilets, gluttony, …), save/exit/restore cycling, prompt
  auto-answering, per-profile command bias, and profile-driven game endings
  (die/escape/ascend).
- Mid-session LeakSanitizer checks (`#wizleakcheck` plus a fuzzer hook); UBSan
  enabled unconditionally in the linux-debug build; extensive per-turn
  sanity-check invariants (light sources/timers vs objects, monster worn-masks
  vs wielded weapons, artifact/unique-item uniqueness, hero water/trap/
  strangulation state, non-stacking potions); unattended Lua test scripts.
- GitHub Actions overhauled (artifacts, concurrency, pinned actions); the
  **Windows build re-enabled**; config/data/env references renamed
  `nethackdir` → `nerfhackdir`; NerfHack splash screen restored; version bumped
  to **3.0.0**.
