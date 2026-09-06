# NerfHack
- [NerfHack](#nerfhack)
  - [QUALITY OF LIFE FEATURES](#quality-of-life-features)
      - [Safer bags of holding:](#safer-bags-of-holding)
    - [Streamlined Identification Features](#streamlined-identification-features)
    - [Interface Changes](#interface-changes)
      - [Farlook enhancements](#farlook-enhancements)
    - [New config options](#new-config-options)
    - [Wizmode features](#wizmode-features)
  - [MAJOR NERFS AND CHANGES](#major-nerfs-and-changes)
    - [No wishes are allowed in NerfHack.](#no-wishes-are-allowed-in-nerfhack)
    - [Genocide has been nerfed and renamed to Exile](#genocide-has-been-nerfed-and-renamed-to-exile)
    - [Pet Theft Prevention](#pet-theft-prevention)
    - [Price Identification Nerf](#price-identification-nerf)
    - [Polypiling Nerfs](#polypiling-nerfs)
    - [Farming Nerfs](#farming-nerfs)
    - [Partial Resistances](#partial-resistances)
    - [Nerfed intrinsics and extrinsics](#nerfed-intrinsics-and-extrinsics)
    - [Partial Reflection](#partial-reflection)
    - [Items can be completely destroyed from erosion](#items-can-be-completely-destroyed-from-erosion)
      - [Fragile items are more vulnerable](#fragile-items-are-more-vulnerable)
    - [New dragon armor system: DSM replaced by scaled armor](#new-dragon-armor-system-dsm-replaced-by-scaled-armor)
    - [Increased item variety](#increased-item-variety)
    - [Enhanced monster traits](#enhanced-monster-traits)
    - [Racial item preferences](#racial-item-preferences)
    - [Cracked altars:](#cracked-altars)
  - [MECHANICS CHANGES](#mechanics-changes)
    - [Instakills](#instakills)
    - [Slow Luck timeouts](#slow-luck-timeouts)
    - [Pet behavior](#pet-behavior)
      - [Quantity of pets you can manage](#quantity-of-pets-you-can-manage)
    - [Polymorphing Objects and Polypiling](#polymorphing-objects-and-polypiling)
    - [Poly-Self](#poly-self)
    - [Elbereth and Scare Monster](#elbereth-and-scare-monster)
    - [New Grease Effects](#new-grease-effects)
    - [Underwater mechanics](#underwater-mechanics)
    - [Endgame Changes](#endgame-changes)
  - [INTRINSICS AND EXTRINSICS](#intrinsics-and-extrinsics)
    - [Magic cancellation (MC) protects items vs cancellation](#magic-cancellation-mc-protects-items-vs-cancellation)
    - [Gaze attack protection](#gaze-attack-protection)
    - [Slow digestion nerf](#slow-digestion-nerf)
    - [Stealth changes](#stealth-changes)
    - [Warning changes](#warning-changes)
    - [Flying Changes](#flying-changes)
    - [Intelligence and literacy](#intelligence-and-literacy)
    - [Aggravate Monster changes](#aggravate-monster-changes)
    - [Vulnerability properties](#vulnerability-properties)
    - [Impaired States and actions](#impaired-states-and-actions)
      - [Encumbrance affects AC](#encumbrance-affects-ac)
      - [**The "wounded legs" status**](#the-wounded-legs-status)
  - [AC nerfs \& buffs](#ac-nerfs--buffs)
    - [Dexterity affects AC](#dexterity-affects-ac)
  - [SKILLS AND EXPERIENCE](#skills-and-experience)
    - [Skill Changes](#skill-changes)
    - [Shield Skill](#shield-skill)
      - [Effects at different skill levels:](#effects-at-different-skill-levels)
    - [Experience Curve Changes](#experience-curve-changes)
    - [Leveling up bonuses](#leveling-up-bonuses)
    - [To-hit bonuses and penalties](#to-hit-bonuses-and-penalties)
  - [ITEM CHANGES](#item-changes)
      - [Bones files trimming](#bones-files-trimming)
    - [Anti-magical items resist being enchanted (from SpliceHack)](#anti-magical-items-resist-being-enchanted-from-splicehack)
    - [Weapon changes](#weapon-changes)
      - [Specific weapon changes](#specific-weapon-changes)
    - [Armor changes](#armor-changes)
      - [New armor type: bracers](#new-armor-type-bracers)
    - [Comestibles](#comestibles)
    - [Potions and alchemy](#potions-and-alchemy)
      - [Gem Alchemy](#gem-alchemy)
    - [Scrolls](#scrolls)
    - [Wands](#wands)
    - [Rings/Amulets](#ringsamulets)
      - [Eating Jewelry \& Accessories](#eating-jewelry--accessories)
    - [Tools](#tools)
      - [Magic markers](#magic-markers)
      - [Unicorn horns](#unicorn-horns)
      - [Booby-trapped tins](#booby-trapped-tins)
      - [Mirrors confer reflection whilst carried](#mirrors-confer-reflection-whilst-carried)
    - [Gems/Stones/Rocks](#gemsstonesrocks)
    - [Object materials](#object-materials)
    - [Object Properties](#object-properties)
      - [Generation odds](#generation-odds)
      - [Table of object properties ====](#table-of-object-properties-)
    - [Item build qualities](#item-build-qualities)
      - [Forging different levels of quality:](#forging-different-levels-of-quality)
    - [Object alignments](#object-alignments)
  - [NEW ITEMS](#new-items)
    - [potions of blood and vampire blood](#potions-of-blood-and-vampire-blood)
    - [potion of milk](#potion-of-milk)
    - [playing card deck](#playing-card-deck)
    - [scroll of cloning](#scroll-of-cloning)
    - [scroll of transmogrify](#scroll-of-transmogrify)
      - [confused reading of scroll of transmogrify](#confused-reading-of-scroll-of-transmogrify)
    - [healthstone](#healthstone)
    - [whetstone](#whetstone)
    - [foulstone](#foulstone)
  - [ARTIFACT CHANGES](#artifact-changes)
    - [General artifact changes](#general-artifact-changes)
    - [Specific artifact changes](#specific-artifact-changes)
  - [NEW ARTIFACTS](#new-artifacts)
    - [Load Brand](#load-brand)
    - [The Lenses of Truth](#the-lenses-of-truth)
    - [Serenity](#serenity)
    - [Thunderfists](#thunderfists)
  - [NEW MONSTERS](#new-monsters)
  - [MONSTER CHANGES](#monster-changes)
    - [Misc monster changes](#misc-monster-changes)
    - [Delayed stoning for all footrice effects](#delayed-stoning-for-all-footrice-effects)
    - [Dangerous piercers](#dangerous-piercers)
    - [Reviving and Poisonous Zombies](#reviving-and-poisonous-zombies)
    - [Dragon changes](#dragon-changes)
    - [Unique monster changes](#unique-monster-changes)
      - [Cthulhu:](#cthulhu)
  - [MONSTER BEHAVIOR](#monster-behavior)
    - [Monster item use](#monster-item-use)
    - [Monster accessory use](#monster-accessory-use)
    - [Misc monster behavior changes](#misc-monster-behavior-changes)
    - [Flanking behavior](#flanking-behavior)
    - [Berserking behavior](#berserking-behavior)
    - [Traitorous monsters](#traitorous-monsters)
    - [Monster elemental vulnerabilities](#monster-elemental-vulnerabilities)
    - [Resistance and vulnerability to weapon damage types](#resistance-and-vulnerability-to-weapon-damage-types)
    - [Rabid monsters](#rabid-monsters)
    - [Diseased monsters](#diseased-monsters)
    - [Accurate behavior](#accurate-behavior)
    - [Jumping behavior](#jumping-behavior)
    - [Tree walking](#tree-walking)
    - [Withering attacks](#withering-attacks)
  - [MONSTER SPELLCASTING](#monster-spellcasting)
    - [Countering monster spells](#countering-monster-spells)
  - [ROLE CHANGES](#role-changes)
    - [Archeologist](#archeologist)
    - [Barbarian](#barbarian)
    - [Cavemen](#cavemen)
    - [Healer](#healer)
    - [Knight](#knight)
    - [Monk](#monk)
    - [Priest](#priest)
    - [Rogue](#rogue)
    - [Ranger](#ranger)
    - [Samurai](#samurai)
    - [Tourist](#tourist)
    - [Valkyrie](#valkyrie)
    - [Wizard](#wizard)
  - [NEW ROLES](#new-roles)
    - [Undead Slayer](#undead-slayer)
    - [Cartomancer](#cartomancer)
  - [PLAYER RACE CHANGES](#player-race-changes)
    - [Elves](#elves)
    - [Dwarves](#dwarves)
    - [Gnomes](#gnomes)
    - [Orcs](#orcs)
  - [NEW RACES](#new-races)
    - [Dhampir](#dhampir)
      - [NerfHack introduces smarter feeding to regulate vampire bite mechanics:](#nerfhack-introduces-smarter-feeding-to-regulate-vampire-bite-mechanics)
      - [Dhampir's resistances and abilities](#dhampirs-resistances-and-abilities)
    - [Grung](#grung)
      - [Grung's resistances and abilities](#grungs-resistances-and-abilities)
      - [Grung Hydration Mechanics](#grung-hydration-mechanics)
  - [SPELLCASTING CHANGES](#spellcasting-changes)
    - [Spell memory](#spell-memory)
    - [Other spellcasting changes](#other-spellcasting-changes)
    - [New skill-dependent spell ranges](#new-skill-dependent-spell-ranges)
    - [Spell changes and updates](#spell-changes-and-updates)
  - [DUNGEON CHANGES](#dungeon-changes)
    - [New levels](#new-levels)
    - [Castle changes](#castle-changes)
    - [Valley of the Dead](#valley-of-the-dead)
    - [Enhanced Gehennom](#enhanced-gehennom)
    - [The Wizard's Tower Overhaul](#the-wizards-tower-overhaul)
    - [Vlad's Tower revamp](#vlads-tower-revamp)
    - [DEMON AND DEMON LAIR CHANGES](#demon-and-demon-lair-changes)
    - [Sokoban](#sokoban)
  - [DUNGEON FEATURES](#dungeon-features)
    - [Grass](#grass)
    - [Puddles](#puddles)
    - [Forges](#forges)
      - [Forging and Forging Recipes](#forging-and-forging-recipes)
    - [Toilets](#toilets)
      - [Toilet kicking:](#toilet-kicking)
    - [Bloody tiles](#bloody-tiles)
    - [New container traps](#new-container-traps)
    - [Misc trap changes](#misc-trap-changes)
    - [Falling rock traps](#falling-rock-traps)
    - [Spear traps](#spear-traps)
    - [Magic beam traps](#magic-beam-traps)
    - [Grease traps](#grease-traps)
    - [Cold Traps](#cold-traps)
    - [Door traps](#door-traps)
  - [NEW SPECIAL ROOMS](#new-special-rooms)
  - [ALTARS, PRAYER, AND PRIESTS](#altars-prayer-and-priests)
    - [Altars](#altars)
    - [Revised divine protection scheme](#revised-divine-protection-scheme)
    - [Crowning](#crowning)
  - [THE QUEST](#the-quest)
  - [Special thanks to:](#special-thanks-to)

This changelog exists to track the changes in NerfHack: https://github.com/elunna/NerfHack.


## QUALITY OF LIFE FEATURES


* Chaotics do not get alignment penalties for angering, attacking, or killing peacefuls (xNetHack)
* Running into a boulder whilst traveling no longer pushes it (xNetHack)
* Whilst traveling, engravings on graves will not be considered interesting enough to cease movement
* Whilst traveling, the player will avoid ice and puddles.
* Stop occupations when the hero is caught in a poison gas cloud
* Allow lighting only one candle in a stack (GnollHack).
* Inform the player when casting healing spells at a monster with full health.
* Swapping weapons takes zero turns (dNetHack)
* A welded cursed quarterstaff doesn't block spellcasting (xNetHack)
* Crysknives are never auto-quivered
* Launchers don't count as weapons for the 'hit with a wielded weapon' conduct
* Give a vibrate warning for all weapons and armor when the enchantment reaches an unsafe level (Dynahack)
* You don't waste turns for aborted engrave attempts.
* The Amulet of Yendor needs only be carried to hint of nearby portals (Sporkhack).
* Make inventory more explicit about the container we put in/take out of.

#### Safer bags of holding:
The following safeguards were added to protect players from accidentally exploding their bags:
* Players cannot put **known** wands of cancellation or **known** magical bags into **identified** bags of holding. Keep in mind, unknown wands and bags are still dangerous and should be handled with care until formally identified (dNetHack)
* Players are prevented from #tipping **known** explosive items into **identified** bags of holding
* Empty wands of cancellation may still be placed inside bags of holding with no risk of blowing up
* DISCLAIMER: Bag of holding explosions are not prevented when confused or hallucinating!
* Another subtle but helpful change: bags are not susceptible to burning up when lava walking. In Vanilla this was never the case, but in some variants bags are destroyed unless foo-proofed.
* Moloch's Temple has a 50% chance of generating a bag of holding.
* Sokoban only has a 25% of having a bag of holding as the prize.

### Streamlined Identification Features
A general design philosophy of NerfHack is to automatically identify items when it becomes obvious what they are from various effects. If a quick wiki lookup is all that is needed (ie: sink ring identification) let's save the player from opening up a browser.

* All roles start out knowing potions of water, blank scrolls, and scrolls of identify (the exception is cavemen, who don't know about scrolls of identify)
* When dropping a container on an altar, the BUC status of all contained items is revealed (NetHack4)
* Your primary wielded weapon is auto-identified after killing enough monsters with it (EvilHack)
* Rings of increase damage and accuracy are identified along with their enchantment after killing enough monsters
* When you have expert skill in a weapon type, you will auto-id the enchantment on those types of items (only for non-missile weapons)
* Auto-ID potions of acid when water explosions result from dipping (xNetHack)
* Auto-ID potions of acid when a lichen corpse is dipped
* Auto-ID potions of phasing when any item is dipped
* Auto-ID potions of sickness when they coat a weapon in poison
* Auto-ID potions of sickness and fruit juice when dipping a unihorn in sickness
* Auto-ID potions of see invisible or fruit juice by process of elimination when quaffed
* Auto-ID potions of restore ability and booze when quaffed
* Auto-ID amethyst, fruit juice, and booze when dipping amethyst into booze (Fourk)
* Auto-ID some potions when inhaling their vapors (xNetHack)
* Auto-ID scrolls of scare monster when they crumble from being picked up (UnNetHack)
* Auto-ID scrolls that have obvious effects when read: scare monster, confuse monster, food detection, remove curse, flood, enchant armor
* Auto-ID rings dropped into a sink (UnNetHack)
* Auto-ID rings of regeneration upon wearing
* Auto-ID +0 rings of protection (if MC is increased)
* Auto-ID wands of cancellation after they destroy a bag of holding (UnNetHack)
* Auto-ID most wands when engraving (xNetHack)
* Automatically use a process of elimination for auto-identifying wands when available (UnNetHack)
* Auto-id flint stones yielded from applying rocks to each other
* Auto-ID most musical instruments upon use (UnNetHack)
* Auto-ID dunce caps when one is first put on (UnNetHack)
* Auto-ID jumping boots when they are worn (UnNetHack/Ace)
* Auto-ID water walking boots when they waterwalk (xNetHack)
* Auto-ID kicking boots when you #kick with them
* Auto-ID BUC of products from BUC identified tinning kit or horn of plenty (UnNetHack++)
* Auto-ID BUC of wands when they backfire
* Auto-id bags of holding when items are added or removed
* Blessed stethoscopes can identify eggs (EvilHack/Sporkhack)
* Make rustproof/erodeproof/fixed known by default (Dynahack)
* Make object properties obvious and known by default
* Make the item build quality of items obvious and known by default

* **Items that are 'lost'** from the player's inventory are no longer un-identified.

### Interface Changes
* Created a new splash screen for the Windows build.
* A detailed object and monster Pokedex is available in the in-game lookup (xNetHack/UnNetHack)
  * Farlook any monster (press '//'), then press ':' to access the pokedex entry
  * You can also search for a monster or item: press '/' then '?', then type the name of the thing you want information on.
  * For item details, open your inventory and press the letter of the item for info.
* The object lookup also works for artifacts
* Peaceful monsters are underlined [TTY and curses] (xNetHack)
* Magic cancellation (MC) value is shown on the player's status line (EvilHack)
* Skill caps and percentage towards next level is available in #enhance
* Show available skill slots in the #enhance menu (Dynahack)
* Show if a monster ignores magical scaring or Elbereth in the pokedex info.
* Inventory weight and carry capacity data are shown in the inventory (can be toggled with the invweight option)
* \> or < can be used to autotravel to stairs (can be toggled with the autostairtravel option)
* AC values for armor are displayed next to armor in the hero's inventory - these take into account all available bonuses (racial bonuses, item appearances, enchantment, etc) (SpliceHack)
* Prayer statistics (last prayed, reconciled, received a gift, divine protection) can be viewed in the attributes screen (via Ctrl-X)
* All position prompts may be aborted
* Show the '0' warning level for very weak monsters in addition to all other standard warning symbols (Dynahack)
* More descriptive combat messages have been added to enhance hits and misses during combat (xNetHack)
* Show explicit messages when objects are randomly cursed from the Curse Items spell (Dynahack)
* Show an explicit message when summon nasties occurs as part of wizard harassment
* Special room and special level walls can have their own unique coloring (SpliceHack/xNetHack)
* Enabled autocomplete for #twoweapon
* Enable **full options** by default
* Disabled **#chronicle** from auto-completing (so #chat will autocomplete as normal)
* Disabled **farlook help**
* Disabled the 3.7 **tutorial**
* Changed the symbol for **sinks** back to #
* The hero's color reflects their race (SLASH'EM)
* Suggest a donation amount (relative to XP level) when #chatting to priests
* Use NERFHACKOPTIONS instead of NETHACKOPTIONS so it doesn't clash with other NetHack installations
* Added a "Rabid" status that indicates when the player is rabid
* Added a "Wither" status that indicates when the player is withering
* Added a "Phasing" status that indicates when the player is phasing
* Don't livelog events in explore mode

#### Farlook enhancements
* We are able to see more monster conditions on farlook (EvilHack/SpliceHack/xNetHack)
  * You can ascertain when monsters are reflecting, withering, diseased, berserking, rabid, confused, stunned, or blinded
  * **Spell-beings** will appear as "sparkling" on farlook.
* Farlook also shows amulets and rings monsters are wearing
* We are able to see what weapon a monster is wielding from farlook (EvilHack)
* We are able to see roughly how much armor a monster is wearing on farlook (EvilHack)

### New config options

* **showdamage:** Displays damage dealt by both the player and monsters. Also shows flanking bonuses and penalties if active.
* **invweight:** Shows the weights of objects in inventory along with carry capacity and inventory slots available.
* **autostairtravel:** Allow fast travel to stairs with < and >
* **hide_old_spells:** This option allows the player to control whether spells with 0% retention (spells that have been forgotten) show up in the spellcasting menu.

### Wizmode features
* The #wizcrown command has been added for testing crowning (EvilHack)
* The #wizclear (^z) command, clears all monsters on the screen (SpliceHack)
* Allow overriding artifact invoke timeout in wizmode (xNetHack)
* Allow teleportation into unteleportable spots in wizard mode
* Allow wishing (^W) for monsters (UnNetHack)
* Allow wishing for specific spell beings
* Changed #debugfuzzer command to just #fuzz
* Show timeouts for sick, rabid, withering, and other afflictions in the wizmode enlightenment menu
* wiz_prop command to add properties to items in wizmode.



## MAJOR NERFS AND CHANGES


### No wishes are allowed in NerfHack.
* That's right: 0, None, Zero, Zilch. Wishes have been totally removed from normal play (however they are still available in wizmode or explore mode)
* A key design philosophy of NerfHack is to "use what the dungeon gives you".
* Magic lamps have been removed and replaced by magic candles.
* Water demons that come from fountains will never offer wishes
* Djinni will never offer wishes
* Thrones cannot grant wishes when sitting
* The wand of wishing in the Castle has been replaced by chests of loot
* Vlad's throne doesn't grant a wish
* The Amulet of Yendor does not grant a wish

### Genocide has been nerfed and renamed to Exile
* A renaming was in order because genocide was heavily nerfed and functions differently from vanilla NetHack.
* Permanent dungeon-wide monster genocides are no longer allowed.
* An uncursed scroll of exile works to wipe out a single species of monster that is in close proximity to the player.
* A blessed scroll of exile wipes out a single species on the level.
* All other effects are identical to the scroll of genocide in vanilla.
* Genocides from thrones have been replaced with a generous gift of gold.

### Pet Theft Prevention
* Pet theft from shops has been totally disabled.
* Pets will never pick up objects in shops nor eat unpaid food (Gnoll)
* Pets will also never take items from outside shops and drop them inside (like a pick-axe that you always have to leave right outside the door)
* You also cannot #loot items to or from your pet that are unpaid.
* Shopkeepers start with much more gold, more than double the standard amounts (Gnoll)

### Price Identification Nerf
* This change destroys price identification and conforms most potions, scrolls, wands, and rings to the same price (SLEX).
* All rings, potions, wands, and scrolls cost $200

Exceptions:
* cursed or blessed potions of water still cost $100
* potions of blood, milk, and healing cost $100
* scrolls of identify and knowledge cost $100
* cards of zapping cost $50

### Polypiling Nerfs
* Non-magical potions, scrolls, spellbooks, and wands are much less likely to transform into magical items. These types of items only have a 1% chance of transforming into something magical. This is now comparable to how other non-magical items polymorph. (dNetHack)
* The chances of getting a golem from polypiling have been accelerated (K-Mod/Sporkhack)
* The enchantment level or charges on items is randomly reduced when polymorphed (Sporkhack)
* Golems created from polypiling immediately halt the polypiling process. This effectively nerfs the "one-giant-pile" strategy of polypiling.

### Farming Nerfs
A big philosophy of NerfHack is to discourage repetitive and potentially infinite strategies and exploits. These specific nerfs also are aimed at encouraging using "found items" and prodding the player deeper into the dungeon.

* **Vault guard farming:** Vault guards do not get special offensive or defensive items on spawn and do not leave death drops.
* **Temple ghost farming:** Each abandoned temple spawns a single ghost before permanently losing its status as a temple, preventing further ghosts from generating.
* **Quest monster/giant farming:** This is mostly in regard to what is known as "giant farming" in the valkyrie quest. Players could possibly farm giants for strength and gems by subsisting on their corpses. Monster generation in quests is now dramatically less frequent.
* **Werefoo farming:** Werefoo summon temporary spell-beings that don't leave death drops or corpses.
* **Horn of plenty farming:** Historically, Horns of Plenty could be endlessly recharged using the Tourist’s quest artifact, the Platinum Yendorian Express Card. This exploit has since been nerfed: tool recharging now follows the same rules as wands: tools can be recharged up to 7 times, with each additional recharge increasing the risk of the item crumbling.
* **Trees on special levels are pre-looted.** Whilst this doesn’t qualify as classic 'infinite' farming, the abundance of trees added to many levels means a player could theoretically spend an excessive amount of time harvesting them for bees and fruit.


### Partial Resistances
* Instead of binary resistances, the player gradually builds up their resistance from 0% to 100%.
* When eating a corpse, player gains a percentage of certain intrinsics.
* Percentage gained is based on the weight of the corpse; minimum being 2% and maximum at 25% (capped at 100%).
* Tins convey the same percentage from whatever they are made from.
* You will always get a percentage intrinsic from each corpse eaten.
* You receive all intrinsics that the corpse can convey if there are multiple intrinsics it can give (ie: eating a black pudding glob grants a small percentage each of poison, cold, and shock resistance.)
* Damage and effects dealt are adjusted based on the percentage intrinsic currently possessed. Damage reduction is rounded down, requiring slightly more resistance to be effective.
* Gremlins steal (25 + d25)% of your intrinsics
* Enlightenment shows the partial percentage acquired for intrinsics so you can monitor your progress. If you have an extrinsic resistance it will be displayed separately from the partial percentage.

### Nerfed intrinsics and extrinsics
* **Many intrinsics cannot be permanently gained**:
  * invisibility
  * see invisible
  * telepathy
  * teleportitis
  * teleport control
* **Intrinsic disintegration resistance** doesn't protect items from disintegration.
* The chance of gaining levels from wraiths has been reduced using SLASH'EM's wraith corpse adjustments.
* **Giant corpses** have less of a chance of conferring strength gain (SLASH'EM)
* Passive fire damage burns away slime.
* **Unchanging** pauses rather than cancels sliming (xNetHack)
* There is an increased CON penalty for getting lifesaved (xNetHack).
* **Extrinsic acid resistance** only provides 50% damage reduction.
* **Magic resistance and spell damage reduction** only halve magic missile damage instead of preventing it (EvilHack)
* **Magic resistance only protects you from 90% of unintentional polymorphs.**
* **Half physical damage** only provides one-quarter (25%) physical damage reduction.
* **Half spell damage** only provides one-quarter (25%) spell damage reduction.

### Partial Reflection
* Reflection will deflect most, but not all, of the effects of ray attacks. Instead of full damage you will usually take about half the damage - depending on the damage type. Item destruction from elemental effects (like fire or cold) is also prevented when rays are reflected.
* If you don't have full sleep resistance, but you reflect a sleep ray, you will fall asleep for 1d6 turns (which could be further lessened by your partial sleep resistance).
* If you reflect a disintegration ray, you still take 12d6 damage (subject to your current level of disintegration resistance).
* If you reflect a death ray, you still take 12d12 damage and lose max HP. This can be mitigated by magic resistance and spell damage reduction, but is impossible to fully prevent.
* Reflection only provides partial protection from **floating eye gazes** - the player will still be subject to 1-2 turns of paralysis without free action. This is weighted on Luck, so the higher your Luck the better the chance to avoid the gaze.
* **Medusa's gaze** has no effect on her if reflected back from more than 3 squares away.
  * If she might be affected by her own gaze, Medusa will protect herself 98% of the time.
* Partial reflection also applies to monsters, making them more vulnerable to various ray attacks if they happen to possess reflection of some form.

### Items can be completely destroyed from erosion
* Almost all items are erodible or destroyable (EvilHack)
  * amulets, rings, wands, and tools are now eligible for erosion and destruction.
  * Silver items can also corrode (xNetHack)
  * Bone items can burn
  * Dragonhide can rot (NetHack 5.0)
  * The iron ball and chain cannot be destroyed from rusting (EvilHack)
* Poison gas clouds can rot organic armor
* Extrinsic poison resistance (or the venom property) protects items from rotting in poison gas
* Monster spellcasters can wear down and destroy any armor with the Destroy Armor spell (excepting crystal plate mail which is immune) (EvilHack)
* Scrolls can burn up when hitting hot ground in Gehennom. (3.7 introduced potions being shattered when dropping on hot ground - this just takes it a step further.)
* Water damage may disintegrate scrolls, which may occur when dipping (Dynahack)
* Disintegration rays can vaporize boulders
* Items can be erodeproofed by dipping into non-diluted potions of reflection.
* Item erosion and negative enchantment can be repaired by dipping into a non-diluted potion of restore ability; read counters on spellbooks can also be refreshed (xNetHack)
* The damage from item destruction has been increased to double or triple its Vanilla values.

**Acid and corrosion:**
* Acid has been turned into a potent source of item-destruction. Wherever acid damage is inflicted, there is now a chance for item corrosion to also occur.
* Getting hit by potions of acid can corrode armor.
* Monster acid attacks and spit also corrode armor.
* Passive acid attacks corrode armor more often.
* Thrown potions of acid can corrode items or armor when they hit a monster or the player.

#### Fragile items are more vulnerable
* Beams of force bolt and striking can break fragile items in inventory.
* Knockback attacks can also shatter fragile items in your inventory
* Fragile items can be fixed to avoid destruction (note that although mirrors can be tempered, they are still subject to shattering when reflecting rays)
* Wands of striking and rings of shock resistance are immune from impact damage.
* Extrinsic shock resistance protects fragile items in your inventory from physical damage (ie: from the ring of shock resistance or blue dragon scaled armor).

### New dragon armor system: DSM replaced by scaled armor
Ported from xNetHack:

This proposal, referred to as the "dtsund-DSM" system, developed by dtsund and jonadab, introduces a significant change to how dragon scales are used in the game. Instead of dragon scale mail being its own type of armor, players can now incorporate dragon scales into existing armors, such as leather armor, chain mail, and others. These "scaled" armors provide the same extrinsic benefits as traditional dragon scale mail whilst retaining their original properties.

The primary reason for replacing dragon scale mail with this system is to enhance armor strategy. Dragon scale mail was overwhelmingly optimal, rendering other armor choices irrelevant. It was simultaneously:
- **Lightweight**,
- **Higher in base AC** than any other armor,
- **Naturally erodeproof**,
- **Unrestrictive for spellcasting**,
- **Easily obtainable** before the Castle or Quest, often as an early wish, and
- **A source of powerful extrinsics** (e.g., reflection, magic resistance).

Once dragon scale mail became available, there was little incentive to consider other armors. With this new system, players must weigh the pros and cons of different base armors, making armor strategy relevant beyond defeating the first few dragons.

**Benefits**
This approach aligns with the philosophy of prioritizing found items over wished ones. Previously, even excellent armors like dwarvish mithril would only serve as placeholders until dragon scale mail became available. Now, players can find dragon scales, integrate them into their chosen armor, and continue using it throughout the game and even change the scaling to adapt their kit.

**Key Details**
- Dragon scales provide -3AC when used as a cloak and add -3AC to any scaled armor.
- Scaled armor is **not automatically erodeproof**, maintaining the risk of erosion into the mid-game. Players can still erodeproof their armor or attach scales to naturally erodeproof materials.
- Following the system used in Nethack Fourk, if a player polymorphs and merges with their scaled armor, it will return after unpolymorphing. This is an intentional buff, ensuring that players do not lose enchantments or scales.
- **Potions of phasing** can also be used to graft dragon scales onto armor in place of reading a confused scroll of enchant armor.

**Other dragon scale notes:**
* Shopkeepers price dragon-scaled armor at a high value (xNetHack).
* By themselves, dragon scales do not provide secondary intrinsics, they must be enchanted onto armor for the secondary effect(s) to kick in.

| Dragon     | Scales confer      | Scaled armor confers     |
| ---------- | ------------------ | ------------------------ |
| gray       | magic resistance   | cancellation resistance  |
| gold       | light source       | hallucination resistance |
| silver     | reflection         | blinding resistance      |
| shimmering | displacement       | stun resistance          |
| red        | fire resistance    | increase damage          |
| white      | cold resistance    | slow digest              |
| orange     | sleep resistance   | free action              |
| black      | disintegration res | withering res            |
| blue       | shock resistance   | speed                    |
| green      | poison resistance  | sickness res             |
| yellow     | acid resistance    | petrification res        |
| shadow     | drain resistance   | death res                |

* Red dragon scaled armor confers increase damage; enchantment works in the same fashion as a ring of increase damage.

### Increased item variety
Items in NerfHack have been enhanced with many new features:
* Object materials
  * Rings have appearances distinct from material
* Build quality
* Object properties
* Item alignments

### Enhanced monster traits
Monsters have many new tricks and abilities:
* [Berserking](#berserking-behavior)
* [Traitors](#traitorous-monsters)
* [Flanking](#flanking-behavior)
* [Jumping](#jumping-behavior)
* Some monsters are [vulnerable to certain elements](#monster-elemental-vulnerabilities)
* Some monsters have [resistances or vulnerabilities to weapon types](#resistance-and-vulnerability-to-weapon-damage-types) (slashing, piercing, blunt)
* [Diseased](#diseased-monsters)
* [Rabid](#rabid-monsters)
* [Accurate](#accurate-behavior)
* [Tree walking](#tree-walking)
* [Withering](#withering-attacks)
* Greatly expanded repertoire of [offensive and defensive spells](#monster-spellcasting) for monster spellcasters.

### Racial item preferences
Dwarves, elves, orcs, gnomes, and grung all fight better in gear built for their own kind: wearing a piece of racially aligned armor grants a -1AC bonus (Evil/THEM), and wielding a racially aligned weapon - in either hand - adds a +1 to-hit bonus. Dhampirs (and anyone currently polymorphed into a vampire) get the same +1AC bonus for wearing bone armor.

The flip side is that most races can't stand each other's equipment. Elves, dwarves, gnomes, and orcs each find the other three races' gear, as well as grung gear, awkward or uncomfortable; grung, in turn, hate dwarvish, orcish, and gnomish equipment, but respect elven craftsmanship enough to wear it. Humans and dhampirs dislike only gnomish and grung gear, and are otherwise free to use anything else. This mechanic applies to monsters too, though in practice they'll simply avoid choosing items they don't like - a monster that does end up stuck with hated gear suffers the same penalties the hero would.

Wearing or wielding something your race hates carries a real cost: a flat +3AC penalty and a -d5 to-hit penalty for every hated piece worn or wielded, an explicit message the moment you put it on, and periodic reminders during combat that your form is suffering for it. Hated items are also more likely to betray you outright - throwing one carries the same 1-in-7 chance of slipping from your grip as a cursed or greased projectile.

### Cracked altars:
* Only one artifact gift can be granted at each altar, after which it will be cracked by your god.
* Altars that are cracked do not yield any more artifacts.
* After level 15, altars can sometimes appear cracked.
* If a level generates with more than one altar, the extra altars have a chance of generating cracked.
* Crowning on an altar will crack it.
* There is a 1 in 127 chance of fracturing an altar after converting it.


## MECHANICS CHANGES


### Instakills
* It is no longer possible to be insta-petrified by touching a footrice or the corpse of any monster that would petrify you.
* Bardiches are a new, but rare, source of instadeath, in two different ways:
  * Wielding one and landing an applied (2-square reach) polearm attack while Skilled or better in polearms has a 1 in 100 chance of beheading the target monster.
  * Separately, getting hit by a thrown bardiche has its own 1 in 100 chance of beheading you, regardless of anyone's skill.
* Only magic resistance protects you from a self-zapped wand of death or the finger of death spell; half-spell damage does not help here, since this effect is normally an instant, guaranteed kill rather than a source of reducible damage. With magic resistance, the self-zap still hurts badly - it drops your HP to 1 - but you survive.

### Slow Luck timeouts
In NerfHack, **Luck items slow down your Luck timeout rather than stopping it completely** - this is similar to how it works in UnNetHack. However, the timeouts have been modified and extended to cover negative base luck situations. The timeouts have also been reduced heavily from the UnNetHack calculations.

The modified Luck timeout depends on how far your Luck is from your base Luck: the higher or lower your Luck, the less the timeout is slowed. The timeout is calculated every turn, meaning gaining or losing a point of Luck could result in that point timing out immediately.

The modified Luck timeout is calculated by the following formula:

    Timeout = 25 * (20 - base_distance) * (20 - base_distance)

base_distance is how far you are from your base luck. If your base luck is 0 and you have 3 Luck, the base_distance is 3. If you have -10 base luck and 10 Luck, the base_distance is 20. The following chart shows how many turns it takes to timeout from one luck level to the next and the total turns to reach the base distance of 0.

| base distance | Timeout | Time to base Luck |
| ------------- | ------- | ----------------- |
| 0             | ∞       | 0                 |
| 1             | 9 025   | 9 025             |
| 2             | 8 100   | 17 125            |
| 3             | 7 225   | 24 350            |
| 4             | 6 400   | 30 750            |
| 5             | 5 625   | 36 375            |
| 6             | 4 900   | 41 275            |
| 7             | 4 225   | 45 500            |
| 8             | 3 600   | 49 100            |
| 9             | 3 025   | 52 125            |
| 10            | 2 500   | 54 625            |

### Pet behavior

#### Quantity of pets you can manage

The number of pets you can have on a level at once is capped by your Charisma, ported from EvilHack: the limit is simply Charisma divided by 3, so a Charisma of 7 allows 2 pets and a Charisma of 9 allows 3. If you exceed the limit, your weakest pets (by level, with ties broken randomly) are the first to become untamed. An untamed pet that was previously mistreated, such as one you resurrected after letting it die, may even turn hostile rather than simply wandering off. Your steed counts toward this limit but is exempt from being untamed by it, and summoned spell beings don't count toward the limit at all. Since the minimum possible Charisma is 3, you'll always be able to keep at least one pet.

#### Misc pet changes

Steeds are more aggressive (EvilHack): once your steed reaches a tameness level of 15 or higher, it will attack monsters on its own initiative instead of only reacting when attacked. Casting a healing spell on a pet no longer carries an alignment penalty (xNetHack) — previously it nudged your alignment record the same way healing any other peaceful creature did, which unfairly punished chaotic characters for helping their own pets. Pets won't attack a gas spore, or any other monster with an explosive attack, while you're standing adjacent to it (xNetHack), and they no longer displace you from the stairs when following you to a new level (Dynahack) — you'll always land on the stairs yourself, with your pet appearing nearby instead.

Pet items can be managed with the **#loot** command, which lets you give items to pets as well as take items from their inventory, and farlook now reports whether a pet is stunned, confused, or blinded. Pets also use their inventory more intelligently (EvilHack): extensive additions to the pet AI let them weigh armor, weapons, and other items by quality, material, and alignment so they favor the best equipment available to them. Tame pets will no longer hide or conceal themselves, and tame spiders won't spin web traps — both would only make them less useful to you. Pets will also hesitate to attack grungs unless they're resistant to that grung's passive (poison for green/blue/red, sleep for gold; purple and orange are avoided outright).

Beyond fighting, pets can help you in a few other ways. A sufficiently tame, uninjured spellcasting pet may cast healing or protection on you when you need it, and a high-level one can even cast reflection; a strong pet can pull you free of a pit (or tear you loose from a bear trap or web); and if you've been put to sleep, a pet will try to rouse you, nudging you awake more reliably if you're carrying treats.

### Polymorphing Objects and Polypiling

* The number of items you have polymorphed can be viewed in #conduct
* **Item quality and alignment** will always transfer to the result of polypiling.
* **Item material** will usually transfer to the result of polypiling if it is valid for the new item.
* **Item properties** will transfer when polypiling depending on a Luck roll. The higher your luck, the more likely the results will retain the original item's property.

Chance of item properties transferring:

    LUCK:     <0      0     +2     +5     +8    +11
    SUCCESS: 0.5%  20.0%  39.5%  59.0%  78.5%  98.0%

### Poly-Self
* Players can use gaze attacks in melee combat when polymorphed into monsters with a gaze attack. This doesn't require using the #monster command, so you can just engage in combat to trigger the form's gaze.
* Humanoids are more careful about attacking you when you are a dangerous polyform (like a cockatrice)
* Mind flayers won't purposely eat the brains of petrifying monsters (ie: when you are polymorphed into a cockatrice)
* When you polymorph into a monster without limbs, you are able to easily slip out of a ball and chain (EvilHack)
* Escape from the controlled polymorph prompt no longer causes a random polymorph (xNetHack).
* Polymorphing into a horned monster destroys any flimsy or cloth helms you may be wearing.
* Being polymorphed into a **wandering form** will sometimes make you wander.
  * Includes powerful monsters like gorgon hulks, revenants, gugs, ghoul queens, byakhees, nightgaunts.
* Being polymorphed into a vampire bat doesn't cause stunning (the vampire bat does not wander like other B class monsters do)

### Elbereth and Scare Monster
* **Conflict** negates the protection of Elbereth and scrolls of scare monster (EvilHack)
* Engraving Elbereth no longer exercises wisdom (Fourk).
* You can't dust engrave whilst being held by a monster - you are limited to using wands that burn or hard engrave (like wands of fire or digging) that still have charges.
* You can't dust engrave on bloody or grassy tiles.

**Reverted 82f0b1e8e from NetHack 3.7.0**
* This 3.7.0 commit implemented this behavior: "Scared hostile monster which cannot move away will attack."
* This has been reverted so players will be able to stand on scrolls of scare monster or Elbereth without risk of random melee attacks from scared or fleeing monsters.
* The reason for this is that it violates the classic, expected behavior of Elbereth. There are other nerfs to Elbereth and scare monster that take the place of this.

### New Grease Effects
Many of these changes were introduced to work in conjunction with the new grease trap.

**Greased boots and gloves should be avoided:**
* Greased feet or boots cause **fumbling**
* Greased gloves cause the Glib status
* If you try to take off greased boots (or put on any boots whilst you have greasy feet), you become Glib for a short time.
* Grease can be washed off your feet or boots by dipping '-' in water (same action as dipping the player's hands)
* Greased gloves can also be cleaned by dipping in a water source.
* NOTE: do not grease your boots or especially gloves since the glove grease will not timeout.

**Other grease effects:**
* Greased items can't be disarmed with a bullwhip
* Greased items are harder to steal
* Glib hands makes applying any item except towels drop them
* Towels can be used to remove grease from specific objects (with the risk that the towel may absorb the grime and become greased itself)
* Grease can be washed off towels by wetting them in fountains or other water sources.
* Greased towels now operate in the same fashion as cursed towels
* Kicking monsters can sometimes get the grease to wear off your boots/feet.
* Greased rings will slip off your fingers.

### Underwater mechanics
* Prevent kicking monsters out of water whilst underwater or vice versa.
* The hero and other monsters resist splash, spore, and fire effects whilst underwater.
* Being underwater provides immunity from explosions and fire damage.

### Endgame Changes
* Occasional earthquakes can occur during the ascension run (UnNetHack/EvilHack). These will cease after entering the planes.
* After the invocation (and whilst traversing through Gehennom), monsters will flood from the upstairs (UnNetHack/EvilHack)
* The correct temple on the Astral Plane will not be revealed due to fleeing monsters (UnNetHack)
* **Level-teleporting (or branchporting) in hell causes teleport sickness**. The levelport will still succeed as normal, but costs a large fraction of the hero's HP and energy. It also drains the max of both (up to 1d3 each). To be fair, the player is warned before this happens and can abort the teleport. This also includes the Wizard's Tower and Vlad's Tower. **Teleport pain goes away once you've killed the Wizard of Yendor.**
* Causing conflict on the astral plane may result in twice the usual number of hostile angels appearing.


## INTRINSICS AND EXTRINSICS


* The **beginner flag** is only set true for tourists.

* **Regeneration** only causes additional hunger when it's actively healing your HP, however when active it burns twice as much hunger.
* **Free action:**
  * protects from paralysis that occurs during the last steps of stoning
  * reduces crystal ball paralysis (Dynahack)
  * offers protection from grabbing attacks, depending on Luck (SLASH'EM).

* **Phasing** allows escape from being engulfed (EvilHack)
* Max carry capacity has been raised to 1250, with strength playing a larger factor in its calculation.
* When invisibility is about to time out, the player gets a warning (xNetHack)

### Magic cancellation (MC) protects items vs cancellation
* Any level of MC limits the damage from cancellation effects if the enchantment on an item is positive.
* If the enchantment is negative, the item's enchantment is canceled to +0 as usual.
* If a potion, scroll, or other item would be blanked, it also gets an additional save roll.
* With MC0, there is no protection when facing a cancel zap and the standard NetHack 3.7.0 rules apply.

Each level of MC offers a higher minimum that you should expect to maintain. This minimum is not absolute however, there is an additional roll (of 1 in MC x 2) to determine if some damage will pass through.
* MC1:
  * Item enchantments will not usually go below +2
  * Items have a 1 in 2 chance to avoid blanking
* MC2:
  * Item enchantments will not usually go below +4
  * Items have a 2 in 3 chance to avoid blanking
* MC3:
  * Item enchantments will not usually go below +6
  * Items have a 5 in 6 chance to avoid blanking

### Gaze attack protection
In vanilla NetHack, there are some attacks that have almost no barriers when monsters target the player: these include gaze attacks and monster spells. In NerfHack, I've tried to implement some minor diversions the player can employ to increase their chances of evading these attacks.

* Displacement protects from gaze attacks, only letting 1 in 3 gaze attacks find the player
* Invisibility protects from gaze attacks, only letting 1 in 3 gaze attacks find the player
* Darkness offers protection from gaze attacks (as long as the player is on a dark square and the gazer doesn't have infravision and the player is infravisible).
* If a gazer is in melee range, it will naturally bypass invisibility and darkness protection.
* Hallucination always protects against floating eye gazes and negates all incoming gaze attacks, except Medusa's glare (xNetHack).

### Slow digestion nerf
* Slow digestion now functions in a fashion opposite of the ring of hunger.
* Slow digestion only prevents hunger for 1 in every 2 turns.
* The previous behavior slowed hunger to only occur 1 in 20 turns

### Stealth changes
* To bring back the feeling of the 3.4.3 **stealth** mechanic, the chance of sleeping monsters waking up and growling has been lowered dramatically and is based on Luck.
  * 0 Luck: 12.5% chance of a monster screaming when roused
  * 2+ Luck: 0.3% chance
  * Negative luck has at least a 30% chance of rousing monsters

### Warning changes
* Certain effects can scramble warning signals around monsters being warned against:
  * Confusion
  * Monsters close to a magic trap
  * Monsters that are displaced

### Flying Changes
* You cannot be Fast or Very Fast whilst levitating.
* Stomping boots and Jumping boots block flying.
* Extrinsic fumbling (from boots or gloves) blocks flying
* Jumping is not physically possible whilst flying.
* Items that grant **steadfastness** will do so even if the hero is flying or levitating. In Vanilla NetHack, this is not the case - especially on the plane of water where the hero is always presumed to be floating in bubbles.

### Intelligence and literacy
* Low intelligence players (<6 INT) cannot successfully write Elbereth or read.
* Having really low intelligence (under 6 INT) prevents you from reading most things (EvilHack).

### Aggravate Monster changes
* **Aggravate monster** causes monsters to not be scared of musical instruments.
* **Aggravate Monster** lets monsters track you from anywhere on the level.
* **Extrinsic aggravate monster** causes pets to attack anything without fear.
* Note: **Extrinsic aggravate monster** increases the monster generation difficulty by 15 (this was already implemented in NetHack 3.7, but it's worth including here as a recent change)
* **Intrinsic aggravate monster** increases monster difficulty by 5 (which can also stack with extrinsic aggravate monster).
* **Cannibalism** causes aggravation for 10000-15000 turns instead of permanently.
* Eating domestic animals causes aggravation for 5000-7500 turns instead of permanently.
* **Aggravate monster spells** cast at hero cause intrinsic aggravation for 50-300 turns.
* Aggravate monster causes peaceful monsters to become hostile.
* **Foulstones** carried in open inventory also confer aggravate monster (however this does not add to the difficulty of spawned monsters)
* Items with the Stench property confer aggravate monster
* The artifact weapon Serenity blocks aggravate monster effects
* Items with the Peace property also block aggravate monster.

### Vulnerability properties
* Ported from EvilHack
* The hero can become temporarily vulnerable to the following attacks even if they have built up 100% intrinsic resistance:
  * Fire
  * Cold
  * Acid
  * Shock
  * Poison
  * Sleep
  * Disintegration
* Sources of vulnerability include the following:
  * Monster spellcasters' Vulnerability spell
  * magic trap spell effect
  * The Degenerator monster attack
  * The Soul Shadow monster attack
* Whilst vulnerable, the hero's resistance is decreased by 50%. If your resistance was below 50% it can go below 0% and act as a damage booster.
* Whilst vulnerable, players can not gain any additional resistances from eating corpses.
* If a player is crowned, all vulnerabilities are cleared before granting any resistances.
* Vulnerabilities can also be cleared by drinking milk.

### Impaired States and actions
* Allow successful use of the #terrain command whilst impaired (xNetHack)
* Falling downstairs does more damage: 10-19 damage instead of 1d3 damage (K-Mod)
* Falling onto sinks does more damage
* Levitating into the ceiling does more damage
* Falling down a hole or pit whilst fumbling - or with low dexterity - can make you fall on a wielded weapon.
* Going downstairs whilst stunned always results in falling, confusion sometimes does.
* Jumping is not possible whilst **stunned**, and jumping whilst **confused** has a 20% chance to fail (EvilHack)
* Many item actions are now forbidden if you have both hands **welded**.
* If you (or a monster) are stuck in a pit, the range of wand zaps and thrown items is limited to the squares adjacent to the pit.
* **Hallucination** affects all item descriptions and appearances in and outside of your inventory (SLASH'EM)
* Whilst **hallucinating** it's impossible to identify objects.
* Auto-pickup is automatically disabled whilst **hallucinating**.
* Allow performing the invocation whilst hallucinating.
* You will always hit monsters who are **holding you**.
* Whilst **fumbling**, your character will be incapable of multishotting projectiles.
* **Fumbling** only causes 50% of kicks to be ineffective.

#### Encumbrance affects AC
* Being encumbered has a severe negative effect on your AC and inflicts a +4AC penalty for each level of encumbrance.

| <!-- -->    | <!-- --> | <!-- --> | <!-- --> | <!-- -->  | <!-- -->   |
| ----------- | -------- | -------- | -------- | --------- | ---------- |
| Encumbrance | Burdened | Stressed | Strained | Overtaxed | Overloaded |
| Change      | +4AC     | +8AC     | +12AC    | +16AC     | +20AC      |

#### **The "wounded legs" status**
* Inflicts a severe AC penalty for bearing weight.
* You get +1AC for every 100aum you are carrying whilst you are wounded.
* Many traps (and some monsters) can inflict wounded legs, but now the jungle boots can be useful to prevent it.


## AC nerfs & buffs


### Dexterity affects AC
* Being encumbered negates AC bonuses from dexterity
* Wearing any kind of heavy metallic body armor (not mithril) or other rigid material also negates beneficial AC bonuses

| <!-- -->  | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> |
| --------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |
| Dexterity | <= 6     | 7-9      | 10-14    | 15-16    | 17-18    | 19-20    | 21-23    | 24-25    |
| Change    | +3AC     | +1AC     | +0AC     | -1AC     | -2AC     | -3AC     | -4AC     | -5AC     |


## SKILLS AND EXPERIENCE


### Skill Changes
The skill system for achieving proficiency in weapons and spells has been adapted from the UnNetHack system and made progressively more difficult. In UnNetHack most of the requirements for advancing skills have been substantially increased. The major exception is that training skills from unskilled only takes 50 uses compared to UnNetHack's 100.

This chart shows the number of successful uses of a skill required to reach each level.

| Skill level  | Successful uses | Vanilla NetHack |
| ------------ | --------------- | --------------- |
| Unskilled    | 0               | 0               |
| Basic        | 150/50          | 20              |
| Skilled      | 300             | 80              |
| Expert       | 600             | 180             |
| Master       | 1200            | 320             |
| Grand Master | 2400            | 500             |

* Every role gets at least one skill that they can advance to Master level.
* Riding skill is exercised more quickly, closer to vanilla (UnNetHack)
* Skill gain for spells is faster than skill gain for weapons (UnNetHack)
* Shield skill gains are also increased to keep pace with the increased skill requirements.
* Reaching Master in a weapon skill grants 1 more damage for attacks
* No role can reach higher than Basic skill in club.
* Training skill in pick-axe affects how fast you can dig (EvilHack)
    * Skilled gives you the same bonus as a dwarf (x2)
    * Expert gives you double the bonus of a dwarf (x4)

### Shield Skill
* Ported from EvilHack with some modifications
* Shield skill can be trained up like any other weapon attack. It is not actively trained, but passively as you block attacks with your shield. Sometimes you will train even if not directly shielding. There's a 2 in 3 chance of training shield skill whilst wearing one and a regular miss event occurs. A further check is rolled against the enchantment of the shield, with a higher enchantment resulting in more chance of training.
* Different roles can reach different levels of shield skill. Any role that starts with a shield starts with at least Basic skill in shield.
* As a player levels up with shield, there is also a small chance of **shield bashing** when attacking a monster. If you are Expert or greater in shield skill, you deal an extra d4 damage. Bigger shields deal more damage than small shields.

#### Effects at different skill levels:
* Unskilled:  No AC bonus
* Basic:      Grants -1AC, 1 in 25 chance of shield bash
* Skilled:    Grants -3AC, 1 in 17 chance of shield bash
* Expert:     Grants -5AC, 1 in 13 chance of shield bash
* Master:     Grants -8AC, 1 in 10 chance of shield bash

**Bracers** still benefit from shield skill, but the rate is only 1AC per skill. So basic = 1AC, skilled = 2AC, etc.

### Experience Curve Changes
* The XP level requirements follow the same formula for levels 1-11.
* After level 11, the curve follows a blend of FIQHack and EvilHack's XP curves, but ultimately ends at the same level 30 value that EvilHack has whereas FIQHack ends at a value of 700,000 for level 30.

| XP Level | XP Required |
| -------- | ----------- |
| 12       | 15 000      |
| 13       | 22 000      |
| 14       | 33 000      |
| 15       | 50 000      |
| 16       | 75 000      |
| 17       | 113 000     |
| 18       | 170 000     |
| 19       | 256 000     |
| 20       | 384 000     |
| 21       | 576 000     |
| 22       | 864 000     |
| 23       | 1 297 000   |
| 24       | 1 946 000   |
| 25       | 3 200 000   |
| 26       | 3 520 000   |
| 27       | 3 840 000   |
| 28       | 4 160 000   |
| 29       | 4 480 000   |
| 30       | 4 800 000   |

### Leveling up bonuses
Leveling up grants damage bonuses (SlashTHEM)
- **Level 10:** +1 damage to attacks
- **Level 20+:** +d(x), where x is 1 damage for every additional level gained

For example:
- At level 25, you would gain a combined total of +7 damage
- This is +d6 + 1 damage (+1 for reaching XP 10 and +6 for levels 20-25).

### To-hit bonuses and penalties
A lot of changes have been introduced to reign back the bonuses for to-hit because in vanilla NetHack, it's not uncommon to have nearly a 100% hit rate by the late-or-midgame.

* Strength doesn't affect to-hit calculations
* The effect Luck has on to-hit bonuses has been reduced to (Luck / 3) (EvilHack/Sporkhack)
* Luck still has an effect when -1, -2, +1, and +2 (xNetHack)
* Players get an additional +1 to-hit bonus whilst XP1-5
* Weapon enchantments give variable to-hit bonus instead of flat bonus
* The enchantment based to-hit bonus for projectiles is capped at +7
* All short swords get +1 to-hit (Dynahack)
* You get a +4 to-hit bonus for attacking with a scimitar on a steed
* **Polearms** get a +4 to-hit bonus vs horses and centaurs
* fencing gloves provide +2 to-hit when you are attacking with a free off-hand (dNetHack)
* gauntlets of dexterity grant +1 to-hit whilst using bows (EvilHack)
* gauntlets of fumbling inflict -9 to-hit penalty whilst using bows (EvilHack)
* combat boots provide 1AC and +1 to-hit (dNetHack)
* You have an increased wand to-hit chance for high-dexterity characters (SpliceHack)


**Players get a to-hit bonus after reaching level 20**
| XP Level | To-Hit Bonus |
| -------- | ------------ |
| 21       | +1           |
| 22       | +1           |
| 23       | +d2          |
| 24       | +d2          |
| 25       | +d3          |
| 26       | +d3          |
| 27       | +d4          |
| 28       | +d4          |
| 29       | +d5          |
| 30       | +d5          |


## ITEM CHANGES


* Levels of erosion on an item decrease its value (EvilHack)
* Orcish equipment usually generates rusty and/or corroded
* Dwarvish items sometimes spawn as fixed
* Wet towels provide 100% protection from poison gas when worn
* Scrolls, rings, and wands have a variety of new appearances (UnNetHack/Slice)
* The weights of non-mergable weapons and armors can vary slightly (from CrecelleHack)
* Cut down on items for monsters that won't use those items, specifically dragons that won't use their potions or scrolls.

#### Bones files trimming
* When bones files are left, a random selection of items are subject to shuddering.
* Magic markers are converted to athames.
* Quest artifacts cannot be left in bones, they revert to ordinary objects.

### Anti-magical items resist being enchanted (from SpliceHack)
* If an item grants magic resistance, it will try to resist enchanting from scrolls of enchant weapon and enchant armor.
* The resistance is not absolute and instead depends on the items current enchantment level.
* **gray dragon scales** can always be converted to dragon scaled armor.
* Armors with oprops are also harder to enchant (like magical armors).

**For enchant armor:**
| <!-- -->            | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> |
| ------------------- | -------- | -------- | -------- | -------- | -------- |
| Current enchantment | <=0      | +1       | +2       | +3       | +4       |
| Chance of failure   | 0%       | 14%      | 29%      | 43%      | 57%      |

**For enchant weapon:**
| <!-- -->            | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> | <!-- --> |
| ------------------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |
| Current enchantment | <=0      | +1       | +2       | +3       | +4       | +4       | +4       | +4       |
| Chance of failure   | 0%       | 8%       | 15%      | 23%      | 31%      | 38%      | 46%      | 54%      |


### Weapon changes
* Weapon enchantment gives variable **to-hit bonus** instead of flat bonus. This means that instead of a +7 weapon granting +7 to-hit, it grants a random to-hit bonus from +1 to +7, inclusive.
* Lords, princes, and uniques will appear with enchanted weapons.
* Over-enchanted weapons that vaporize now explode, abusing your wisdom
* Kicking edged weapons with bare feet or non-metal boots is painful.
* **All *launchers* can contribute to missile projectile damage** (adapted from SpliceHack); the damage is calculated as d(x/3), where x is the current enchantment of the launcher.
* Cursed launchers always have a chance of misfiring.
* Cursed projectiles can hit yourself in the leg (EvilHack).
* Any slashing or piercing weapons can now be poisoned (SLASH'EM)
* Special weapon effects (like rogue backstab, flail stunning, and samurai katana weapon smashing) have been enabled when two-weaponing.
* Wielding and unwielding **curved swords** takes 0 turns.
* Lawful and chaotic weapons cannot be two-weaponed

#### Specific weapon changes
* **boomerangs** have a higher probability of generating and can pass through enemies on hit.
* **long swords** have a slightly lower chance of randomly generating (K-Mod)
* **spears** at expert skill can skewer through enemies, allowing you to hit the enemy directly behind the target. Peacefuls are prevented from being hit unless the spear is cursed. We also won't auto-skewer the spot unless it is visible or spottable via ESP. Skewering doesn't trigger most passive attacks unless it's a passive electrifying attack and you attack with a metal spear. Most of the time you won't get a skewer unless the monster is below 20% of its health, otherwise if it's a kebabable monster or a solid or blobby monster, you'll always skewer.
* **tridents** at basic can also skewer monsters.
* **morning stars and flails** can stun monsters (or the player) on critical hits. Player must be skilled or better.
* **daggers and knives** have a small chance to mulch. If non-cursed, the probability is 1 in 100. If cursed, they go through the same checks as other mulchable projectiles.
* **shuriken** now weigh 2 aum each.

* **bullwhips:**
  * Ported a modified version of L's Bullwhip Patch (xNetHack).
  * Reduced weight of bullwhips to 7 aum
* **polearms:**
  * Polearms can be used to trigger traps (Fourk).
  * **polearms and lances** can be pounded when blind (as long as you can sense the target)
  * Wielded polearms grant an AC bonus depending on their weight (for every 30aum, they grant -1AC)
  * **spetums** can skewer up to 3 monsters when used in melee whilst riding a steed
  * **ranseurs** can disarm monsters or the player when pounded or used in melee whilst riding a steed.
  * **bardiches (long poleaxes)** have a 1 in 100 chance of beheading monsters (or the player)
* **bows and crossbows** are two-handed.
* **crossbows:**
  * no longer grant multishot, instead their damage output is multiplied by your skill (dNetHack).
  * crossbow bolts have been buffed to deal 1d7+1 versus small and 1d8+1 vs large monsters with a +2 to-hit bonus.
  * Gnomish players get a bonus for using crossbows
* **slings:**
  * Projectiles receive a strength bonus when using slings (xNetHack). However, this bonus is 3/4'th what is normally granted.
  * Gem class projectiles do minimal damage vs thick-skinned monsters or unsolid monsters.
  * Launching gem class projectiles from slings has the potential to instakill H

### Armor changes
* robes now use the body armor slot instead being a cloak (SLASH'EM)
* reduced weight of most armors by 50 aum (K-Mod)
* reduced weight of elvish gear by about 1/3'rd (EvilHack)
* reduced weight of dwarvish shields to 75
* kicking boots can always damage thick skinned monsters and work even whilst burdened (SpliceHack)
* mud boots provide protection from wrapping attacks
* hiking boots let you avoid pit traps
* hiking boots provide extra carrying capacity (dNetHack)
* old gloves are immune to erosion damage (dNetHack)
* padded gloves provide an additional bonus -1AC (dNetHack)
* combat boots provide 1AC and +1 to-hit (dNetHack)
* jungle boots provide protection from wounded legs (dNetHack)
* kicking boots allow kicking even when your legs are wounded
* oilskin cloaks let you slip effortlessly out of web traps
* increased weight of dwarvish mithril coats to 200 aum
* dwarvish and elvish mithril coats only grant MC1
* increased weight of dragon scales to 80 aum
* mummy wrappings always generate rotted
* mummy wrappings grant 0MC
* cursed armor weighs more when worn
* **the protective effect of hard helmets** has been reduced when heavy objects fall on the hero's head.
* only elves can safely enchant elvish armor over +3 - other races will get a warning vibration once their armor passes +3.
* worn armor has a 25% weight reduction (xNetHack/FIQ)
* plate mail now grants 8AC
* crystal plate mail now weighs 200, is gemstone, resists destruction, but only grants 5AC
* bronze plate mail now grants 7AC
* leather armor and studded leather armor don't grant any MC but weigh much less
* leather cloaks grant 1AC and 0MC

#### New armor type: bracers

Adapted from EvilHack.

Bracers are a type of shield worn on the forearms, making them unique in that they allow the use of both two-weapon combat and two-handed weapons. Unlike standard shields, bracers do not penalize a Monk’s to-hit when attacking unarmed, nor do they suppress the extra attacks granted to Monks at Grand Master martial arts skill. They also do not interfere with staggering blows from skilled bare-handed combatants or shattering blows delivered by a Samurai wielding a katana. Whilst bracers provide smaller AC bonuses from the shield skill and cannot be used for shield bashing, successfully blocking attacks with them still trains the skill. For spellcasting purposes, bracers are considered non-bulky, similar to a small shield. Bracers provide a base AC bonus of 1AC.

Bracers weigh 15 (half as much as a small shield).

If a player undergoes polymorph into a large monster, any non-artifact bracers being worn will be destroyed. Artifact bracers will be pushed off.

NerfHack introduces a few new magical bracers:
* **bracers of integrity**: conveys wither resistance, erodeproof
* **bracers of sleep resistance**: confers sleep resistance
* **bracers of cold resistance**: confers cold resistance
* **bracers vs shapechangers**: confers protection vs shapechangers
* **bracers of unchanging**: confers unchanging
* **bracers vs stone**: confers petrification resistance


### Comestibles
* Port the Oily Corpses Patch (xNetHack) which gives certain corpses a chance of causing slippery fingers. Eating the corpse of an amorphous or slithy monster that is not a snake, naga or mimic has a 1 in 5 chance of giving you slippery fingers.
* Blessed food items are rotten much less often
* Eucalyptus leaves can never be rotten unless cursed
* Zapping eggs with cancellation sterilizes them
* Cursed food items no longer tame or pacify monsters
* Royal jelly was recolored to magenta (EvilHack/xNetHack)
* Nutrition tweaks and messages for lembas wafers and cram rations (EvilHack)
* Bump up fried tin nutrition and add stale tins (xNetHack)
* Tins are unknown until the player has experience with the tinned monster (eaten, killed, probed)

### Potions and alchemy
* Potions can sometimes generate diluted in the dungeon or in monster inventory
* Most potions have a less potent effect when diluted (EvilHack)
* Shopkeepers only offer half price for diluted potions
* Potions can shatter when dropped on cold floors

* Dipping water into any potion will simply dilute the other potion (SLASH'EM)
* Dipping into a cursed potion always causes an explosion (SLASH'EM)
* Mixing oil with water always results in diluted oil
* Potion vapors have more effects covering more potions when inhaled (xNetHack)
* Non-magical alchemy is less likely to result in an alchemical explosion (1 in 20 chance instead of 1 in 10)
* HP gained from healing potions is subject to nurse dancing limits, but the limit is always calculated as if the player were at the maximum level of 30.
* **fizzy potions and booze** can cause loud belches
* **diluted smoky potions** will never yield a djinni from a bottle
* **diluted milky potions** never yield ghosts
* **diluted healing potions** heal less and grant less max-HP (EvilHack)
* **potions of gain energy** grant a lot more energy and get an alchemy recipe (xNetHack).
* **potions of holy water** can cure withering status when quaffed
* **potions of reflection** are immune to cold and fire damage
* **non-diluted potions of reflection** can erodeproof items
* **cursed potions of reflection** aggravate monster
* **cursed potions of phasing** remove any intrinsic phasing and reset your stats (like self polymorph)
* **cursed potions of gain ability** now subtract 1 point from a random status, adding it to a different status (xNetHack)
* **diluted potions of gain ability** can only achieve uncursed results
* **cursed potions of gain level** can be used in Sokoban to bypass a floor (xNetHack)
* **cursed diluted potions of gain level** don't transport you, they levitate you momentarily.
* **diluted vampire blood** doesn't provide HP gains
* **potions of phasing** can be used to convert dragon scales to dragon scaled armor
* **potions of acid:**
  * are immune to freezing (xNetHack)
  * dipping acid into toilet causes an explosion and destroys the toilet
  * dipping a unicorn horn into a potion of acid will dissolve the horn, resulting in a potion of full healing
* **potions of restore ability:**
  * can be alchemized
  * can be quaffed to cure wounded legs
  * blessed restore ability only restores a few levels (EvilHack)
  * dipping an eroded item in non-diluted restore ability repairs the erosion (xNetHack)

#### Gem Alchemy
* Ported from UnNetHack, originally from SLASH'EM
* Allows you to dip a gem into a potion of acid, to alchemize a potion with a specific appearance
* Gem alchemy recipes can be viewed in the object lookup entry for "potion of acid", or even just "acid"
* Other potions and gems should display their respective recipes
* Gems auto-id after successful gem alchemy
* Gem alchemy results are usually diluted; achieving pure results improves slightly with high Luck

### Scrolls
* Decreased the probability of scrolls of identify, and increased the probability of scrolls of knowledge
* Blank scrolls cost 50
* **scrolls of light** illuminate a greater radius when uncursed and light up the entire level when blessed (xNetHack)
* **cursed scrolls of remove curse** will curse items
* **scrolls of genocide** have been nerfed and renamed to scrolls of exile
* **scrolls of enchant armor** let you choose which worn piece of armor to enchant or repair when you know the identify of these scrolls, otherwise the armor chosen is still random (EvilHack)
* **blessed scroll of destroy armor** asks which armor to destroy (xNetHack)
* **confused cursed scrolls of destroy armor** prompt for which piece of armor to fix
* **confused scrolls of identify** give enlightenment (xNetHack)
* **confused cursed scrolls of punishment** decrease your god's anger by one point (if angry).
* **confused scrolls of gold detection** no longer detect magic portals.

### Wands
* **Wands discharge their effects when they explode (SLASH'EM).**
  * This makes open-carrying many wands much more dangerous
  * For illustration, a wand of cancellation that explodes in your inventory will cancel your entire inventory (subject to MC reduction - see "Magic cancellation (MC) protects items vs cancellation")
* **Cursed wand backfire patch (EvilHack)**
  * If a directional wand is cursed and the player zaps it, there's a 1 in 8 chance it will backfire, hitting the player instead.
  * Wands will never explode when engraved with (SLASH'EM)
  * Raise odds of a zapped cursed wand exploding to 1 in 30 (UnNetHack)
  * Monsters zapping cursed wands have double the chance of explosions.
* **Blessed and uncursed wands wrest much more often (EvilHack)**
  * blessed wands wrest 1/4 of the time
  * uncursed wrest 1/6 of the time
  * cursed wands still wrest 1/8 of the time
  * Wands are used up even if they fail their wresting chance (EvilHack)
* Wand of cancellation extensions
  * Monsters can zap the player with wands of cancellation
  * Being cancelled removes most temporary effects (invisibility, protection, reflection)
* You must have at least one free hand (that is not welded to a cursed item or shield) to zap a wand.
* Plastic wands can neither be broken (via apply) nor exploded by shock damage. This includes all wands made of plastic material including: "plastic", "pliable", and "green" appearances.
* Wands can sometimes generate pre-charged. This occurs frequently for monster inventories.
* Wands of polymorph appear less often and monsters never spawn with them
* Scale wand/horn ray damage with the zapper's level: (XL)d6 damage (from FIQHack). This is throttled after level 10.
* The new 5.0 behavior for monsters zapping wands has been slightly modified so that monsters that don't have experience with wands have a 12 in 13 chance of missing (as opposed to a 100% chance of missing).

### Rings/Amulets
* Port FIQHack's ring initial enchantment rules from xNetHack. Results in more rings that are highly enchanted either in the positive or negative direction and less +0 rings.
* The chance of rings exploding during charging has been reduced (SporkHack). Rings with an enchantment of +3 or lower will no longer explode when charged. Additionally, rings with an enchantment of -5 or lower will only explode if charged using a cursed scroll.
* Allow enchant weapon to charge amulets of guarding and rings of protection.
* Allow charging rings and amulets by wielding them and reading ?oEnchantWeapon.
* **cursed rings** burn extra nutrition when worn.
* **cursed rings** can slip off your fingers when Glib.
* **rings of sustain ability** also protect legs from wounding.
* **rings of sustain ability** prevent skill and spell loss from amnesia
* **rings of conflict** usually generate cursed.
* **rings of protection from shapechangers** wake up normalized shifters when worn.
* **amulets of magical breathing** are immune to water damage
* **amulets of unchanging** can't be polymorphed (UnNetHack)
* **rings of sustain ability** cannot be polymorphed
* **amulets of guarding** are now chargeable with variable AC protection (positive or negative)
* **amulets of reflection** have a lower probability of generating.
* **amulets of life saving** will not work if the player is in nonliving form (EvilHack).
* **cursed amulets of life-saving** are ineffective.
* Rings now deal damage when destroyed by shock damage.

#### Eating Jewelry & Accessories
* Eating rings and amulets only confers an intrinsic for a temporary period.
* To compensate for this nerf, the possibility of getting the property is guaranteed.
* Before, the chance of getting an intrinsic from a ring was 1 in 3 and the chance for an amulet was 1 in 5. Both have been changed and guaranteed.
- Eating a ring now grants 750-1500 turns of its property intrinsically.
- Eating an amulet now grants 1250-2000 turns of its property intrinsically.
- Eating the amulet of reflection now gives intrinsic reflection for 1250-2000 turns. Previously it would not grant anything.
- Eating the amulet of flying now gives intrinsic flying for 1250-2000 turns. Previously it had no effect.
- Rings of increase damage and increase accuracy only grant (+x / 2) with a minimum of 1 for positive enchantment. So rings that are +1 through +3 only grant a permanent +1, +4 and +5 will grant a +2 permanent bonus.

### Tools
* Reduced weight of land mines to 40 aum (xNetHack)
* Reduced weight of beartraps to 50 aum (xNetHack)
* Reduced weight of pick-axe to 75 aum (SLASH'EM)
* Reduced weight of potions to 10 aum
* Reduced weight of crystal balls to 100 aum
* Increased weight of towels to 22 aum
* Increased the prices of many magical tools
* magic lamps have been removed and replaced by magic candles.

* eroded unlocking tools have a chance to break when applied
* cursed unlocking tools also have a chance to break (EvilHack)
* eroded musical instruments have a chance of breaking or failing to play when applied
* rusty stethoscopes are much less effective when applied
* stethoscopes don't work on undead or nonliving monsters
* rusty tin openers can break
* cursed horns of plenty cause hunger when applied
* cursed credit cards may slip through a lock when unlocking, also happens if you are fumbling (xNetHack)
* saddles are now twice as common (FIQHack)
* Switched the probabilities of bags of holding and oilskin sacks so bags of holding are more rare.
* Make beartraps stackable (xNetHack).
* Tools have the same recharging limits as wands and have a chance to crumble.
* pick-axe and mattock now inflict piercing damage (dnh)

#### Magic markers
* Magic markers don't spawn randomly, cannot be created from polypiling, and do not appear in any role's starting inventory.
* Raised base price to 500
* There is a 1 in 4 chance of a magic marker being the Sokoban prize
* One Sokoban ending level has a magic marker guaranteed for a prize
* There is a chance of a magic marker being hidden in the Lost Tomb level.
* A magic marker can also be found in the Boulder Bonanza Mine's End level.

#### Unicorn horns
* Cancelled unicorn horns become degraded, barely usable for curing. However, a degraded horn still has a 1 in 20 chance of success.
* Unicorn horn drops decrease as the number of unicorns killed increases.
* Since unihorns are more scarce, be careful when dipping into random potions as acid will dissolve your unihorn!
* Unicorn horns cannot be poisoned

**Unicorn horns now reduce the timeouts of most afflictions instead of outright curing.**
* For troubles that time out (not illness or vomiting), the unihorn has been nerfed so that it only reduces the timeout.
* The amount reduced depends on a few factors, try to maximize any of these to improve the effectiveness of your unicorn horn:
  * your skill in unicorn horn
  * the enchantment on your unicorn horn
  * your Luck
* if you are a healer you'll always have double the effectiveness versus other roles.
* Regardless of any of the above, there is always a 1 in 20 chance of completely curing a condition.
* Applying a unihorn can also exercise your unihorn skill.

Historical Note: The success rate change from SLASH'EM was experimented with, but ultimately discarded in favor of the timeout nerf.

#### Booby-trapped tins
* From xNetHack
* Randomly generated tins have a 1 in 30 chance of exploding in a blast of fire when opened.
* Tins that you create from tinning kits will always be safe.

#### Mirrors confer reflection whilst carried
* Carrying a mirror in your open inventory grants you the benefit of reflection. Keep in mind this effect applies to both players and monsters.
* However, each time a mirror reflects a ray, there is roughly a 25% chance it will shatter.
* If you are the originator of the reflected ray, you will suffer a -2 Luck penalty when the mirror breaks; no Luck penalty occurs if a monster causes the breakage.
* Artifact mirrors, such as the Magic Mirror of Merlin, are shatterproof and will not break when reflecting rays.
* Cracked mirrors always shatter upon reflection and Medusa’s stoning gaze will always shatter mirrors that reflect it.
* Be cautious around nymphs, as they commonly carry mirrors.
* Cursed mirrors always shatter when reflecting rays.

### Gems/Stones/Rocks
* Reduced weight of flint stones to 2 aum (xNetHack/Sporkhack)
* Reduced base cost of flint stones to 1.
* Reduced weight of rocks to 4 aum
* Rocks can be broken (via apply) to produce flint stones (xNetHack). When the player breaks rocks, they enter into an occupation which continues until the rocks are used up.
* Flint stones can be struck (applied) against objects made of iron, producing sparks (fire). This can scare certain monsters away who fear fire (Sporkhack/THEM)
* Boulders deal 1+5d4 damage instead of 1d20.
* Cursed gems count as attacks when thrown at unicorns.
* Significantly lowered the odds of luckstones generating randomly; increased the odds of other gray stones
* Unicorn gems are used up when they yield Luck.
* Remove bonus Luck point for throwing named valuable gems at unicorns (from xNetHack).

### Object materials
* Ported from xNetHack/EvilHack
* Items can appear in all types of materials now.
* New materials:
  * Coldsteel: does extra damage to fae type monsters.
  * Chiton: commonly used for grung items. Does extra damage for slashing and piercing weapons.
* Rings and their appearances have been overhauled. All rings have new appearances that allow for different materials to generate on them.
* The scroll of transmogrify can be used to change the material of an item at random.

### Object Properties
The object properties patch exists in a handful of variants - the code used for NerfHack was taken from Hack'EM, which was taken from EvilHack, which in turn was taken from GruntHack and then modified significantly.

An object property is a magical attribute associated with an item - in other variants that have object properties, the number of magical properties and the number and types of items they can be applied to is rather broad, and finding such properties on these items is not uncommon. In NerfHack, there are many object properties, and they can found on weapons, armor, and rings, but the chances of finding such items at random is quite rare.

In NerfHack, object properties are not hidden from the player and are made obvious with {} around the properties to distinguish them from other ordinary items.

**Restricted items:**
- non-weapons (ie: cockatrice corpses), artifacts, dragon scales, and unique items.
- A player's starting inventory will never spawn with an object property
- Changing a regular item with object properties into an artifact (e.g., dipping for Excalibur) will strip that item of its object properties.
- Extrinsic properties that are applied to weapons or armor are active only when those objects are wielded/worn.
- With weapons, extrinsic properties also work in the offhand whilst twoweaponing.

#### Generation odds
**Random item generation:**
- Odds of an eligible item having a magical property: 1 in 150
- Odds improve deeper into the dungeon
- The chances of an item having 2 properties on creation is 0 - items can only have a single property.
- Rings have a 1 in 20 chance of generating with a property.

**Forging and property transfers:**

- Properties will never spontaneously appear from forging results, the property has to come from the first or second ingredient.
- Forging will take the secondary object property over the primary.

**Polypiling and Property transfers:**
- Polymorphing items that are cursed always wipes the properties from an obj.
- A non-cursed object has a luck dependent chance of retaining its properties.

LUCK:     <0      0     +2     +5     +8    +11
SUCCESS: 0.5%  20.0%  39.5%  59.0%  78.5%  98.0%

**Scrolls of transmogrify and property manipulation**
* See the section on these scrolls for more info.

#### Table of object properties ====
The table below lists all available magical properties, what items they can be applied to, and what their function is.

| Object property | Armor attributes                        | Weapon attributes                                     |
| --------------- | --------------------------------------- | ----------------------------------------------------- |
| Fire            | fire resistance                         | +(1d5+3) fire damage                                  |
| Frost           | cold resistance                         | +(1d5+3) cold damage                                  |
| Sleep           | sleep resistance                        | +d2 dmg, sleep attack                                 |
| Shock           | shock resistance                        | +(1d5+3) shock damage                                 |
| Venom           | poison resistance                       | +d2 poison                                            |
| Acid            | acid resistance                         | +(1d5+3) acid damage                                  |
| Draining        | drain resistance                        | drain life attack                                     |
| Health          | sickness resistance                     | n/a                                                   |
| Filth           | n/a                                     | disease attack                                        |
| Peace           | blocks aggro mon/berserk                | blocks aggro mon/berserk                              |
| vigilance       | lg autosearch radius                    | lg autosearch radius                                  |
| Stealth         | stealth                                 | stealth                                               |
| Warning         | warning                                 | warning                                               |
| Insight         | see invisible                           | see invisible                                         |
| Charisma        | charisma adjustment                     | charisma adjustment                                   |
| Fumbling        | fumbling                                | fumbling                                              |
| Hunger          | hunger                                  | hunger                                                |
| Burden          | steadfast, heavier item                 | steadfast, heavier item                               |
| Danger          | infravision, higher difficulty          | infravision, higher difficulty                        |
| Rage            | n/a                                     | double damage, bloodthirsty                           |
| Stench          | aggravate monster, prevents digestion   | aggravate monster, prevents digestion                 |
| preservation    | protects item enchantment               | n/a                                                   |
| carrying        | increases carry capacity                | increases carry capacity                              |
| antimagic       | magic resistance, prevents spellcasting | n/a                                                   |
| hexed           | n/a                                     | +3d6 dmg, with 2d6 to self on attacks. Absorbs curses |
| nulling         | n/a                                     | cancel attack                                         |
| integrity       | withering res                           | n/a                                                   |

Notes:
* All sources of resistances or statuses are considered extrinsic
* If a property affects a stat (like charisma), the adjustment is based on BUC status (blessed = +2/uncursed = +1/cursed = -2)
(*) Venom inflicts the normal 1d6 extra poison damage with a 10% chance of instakill by poison, plus an additional 1d2 poison damage.

### Item build qualities
Ported from EvilHack

Weapons, armor, and barding can possess varying levels of quality: inferior, superior, exceptional, and legendary.
* superior weapons deal an extra 1 damage, with +1 to-hit.
* exceptional weapons deal an extra 3 damage, with +2 to-hit
* legendary weapons deal an extra 6 damage, with +3 to-hit
* inferior weapons suffer a -2 penalty to both damage and to-hit
* superior armors provide an extra +1 AC
* exceptional armors provide an extra +3 AC
* legendary armors provide an extra +6 AC
* Inferior armor doesn't have a penalty, but it will fall apart easily.

**Quality effects:**
* Exceptional weapons (and better) are immune to shattering blows, whilst superior weapons are still vulnerable, though they shatter only half as often.
* Inferior weapons are much more prone to breaking, particularly if they are eroded. Additionally, attacking with an inferior weapon carries a small chance of it falling apart upon impact, and inferior armor has a chance to disintegrate when it blocks an attack.
* In terms of value, inferior items are priced at half the cost of standard ones, superior items cost 2x, and exceptional items 4x, and legendary items 10x.

#### Forging different levels of quality:
* Previously, two forging ingredients needed to be exactly the same to produce the same result (with a small chance of something better).
* For example, a superior dagger must be combined with a superior dagger to make a superior dagger. If you combined an exceptional dagger with a superior dagger, you probably ended up with a regular dagger.
* In NerfHack we have a combination formula for mixing items of different qualities so not everything is lost when forging items. We take the average of both ingredient qualities and 50% of the time add a level. This encourages forging more and experimenting more.

### Object alignments
Sometimes items can generate specifically aligned as lawful, neutral, or chaotic.

* Cross-aligned items can blast you when worn or wielded (to a lesser degree than artifact blasts)
* Wearing/wielding cross aligned items acts the same as hated items.
* Item alignment is handled when forging.
* Weapons of opposing alignments cannot be two-weaponed.
* Aligned item bonuses only apply if your alignment is good. If it's negative, they count as cross-aligned.
* Aligned items are valued at twice their base cost.
* Aligned items effects for hero and monsters.
    - Aligned weapons grant +1 to-hit when wielded for the hero (this still needs to get figured out on the monsters' side).
    - Aligned weapons do 1 extra damage vs cross-aligned monsters (and you)
    - Aligned armor grants -1AC for each piece worn, both for the hero and for monsters.
* Gods can change the alignment of items to your alignment as a result of #offering

## NEW ITEMS

| Item                          | Class     | cost | aum | Origin             | Notes                                               |
| ----------------------------- | --------- | ---- | --- | ------------------ | --------------------------------------------------- |
| razor card                    | weapon    | 5    | 1   | SpliceHack         | 1d6/1d6, weaker shuriken for cartomancers           |
| stake                         | weapon    | 50   | 20  | SLASH'EM           | 1d6/1d6,kills vampires                              |
| clawbone hatchet              | weapon    | 8    | 15  | NerfHack           | 1d6/1d4,grung axe                                   |
| orcish scimitar               | weapon    | 15   | 40  | EvilHack           | 1d6/1d8, orc saber                                  |
| spineback cutter              | weapon    | 15   | 20  | NerfHack           | 1d8/1d6, grung saber                                |
| rapier                        | weapon    | 40   | 15  | SLASH'EM           | light metal saber, erodeproof steel                 |
| elven long sword              | weapon    | 40   | 15  | EvilHack           | 1d10/1d12, elf item                                 |
| orcish long sword             | weapon    | 12   | 40  | EvilHack           | 1d8/1d10, orc item                                  |
| heavy sword                   | weapon    | 50   | 500 | NerfHack           | base item for Load Brand                            |
| scythe                        | weapon    | 10   | 120 | SpliceHack         | 1d8+1d4/1d10+1d4, -2 to-hit, polearm that can melee |
| skullclaw mace                | weapon    | 5    | 21  | NerfHack           | 1d6+1/1d6, grung item                               |
| gnomish helm                  | armor     | 8    | 3   | SlashTHEM          | 1AC, grung item                                     |
| turtle-shell helm             | armor     | 10   | 18  | NerfHack           | 1AC, grung item                                     |
| sporecap hood                 | armor     | 1    | 3   | NerfHack           | 0AC, grung item                                     |
| shimmering dragon scales      | armor     | 700  | 80  | Deferred           | displacement                                        |
| shadow dragon scales          | armor     | 700  | 80  | EvilHack           | drain resistance                                    |
| gnomish suit                  | armor     | 40   | 50  | SlashTHEM          | 2AC                                                 |
| giant beetle carapace         | armor     | 45   | 75  | NerfHack           | 3AC, MC1, grung item                                |
| spider-rib shell              | armor     | 15   | 55  | NerfHack           | 2AC, MC1, grung item                                |
| swampwing vest                | armor     | 5    | 30  | NerfHack           | 1AC, MC1, grung item                                |
| snakehide jerkin              | armor     | 10   | 14  | NerfHack           | 0AC, MC0, grung item                                |
| gnomish robe                  | armor     | 50   | 40  | NerfHack           | 1AC, MC0                                            |
| elven robe                    | armor     | 50   | 40  | NerfHack           | 1AC, MC1                                            |
| orcish robe                   | armor     | 50   | 40  | NerfHack           | 1AC, MC0                                            |
| robe of power                 | armor     | 50   | 40  | NerfHack           | 1AC, MC1                                            |
| robe of protection            | armor     | 50   | 40  | NerfHack           | 5AC, MC1                                            |
| snakeskin wrap                | armor     | 2    | 5   | NerfHack           | 0AC, MC1, grung item                                |
| dragonfly cloak               | armor     | 0    | 6   | NerfHack           | 0AC, MC2, grung item                                |
| crabback shield               | armor     | 3    | 8   | NerfHack           | 1AC, MC0, grung item                                |
| tortle-shell shield           | armor     | 7    | 15  | NerfHack           | 2AC, MC0, grung item                                |
| tower shield                  | armor     | 20   | 150 | SpliceHack         | Heavy, provides 4AC                                 |
| shield of countering          | armor     | 75   | 25  | NerfHack           | 1AC/2MC, counters spells                            |
| bracers                       | armor     | 10   | 15  | NerfHack           | 1AC                                                 |
| elven bracers                 | armor     | 10   | 15  | EvilHack           | 1AC                                                 |
| spider-leg wraps              | armor     | 10   | 15  | NerfHack           | 1AC, grung item                                     |
| bracers of integrity          | armor     | 50   | 15  | NerfHack           | conveys wither res, erodeproof                      |
| bracers of sleep resistance   | armor     | 50   | 15  | NerfHack           | confers sleep res                                   |
| bracers of cold resistance    | armor     | 50   | 15  | NerfHack           | confers cold res                                    |
| bracers vs shapechangers      | armor     | 50   | 15  | NerfHack           | confers protection vs shapechangers                 |
| bracers of unchanging         | armor     | 50   | 15  | NerfHack           | confers unchanging                                  |
| bracers vs stone              | armor     | 50   | 15  | NerfHack           | confers petrification res                           |
| rogue's gloves                | armor     | 50   | 10  | SpliceHack         | Confers searching, fingerless (!)                   |
| pincer gauntlets              | armor     | 8    | 5   | NerfHack           | 1AC, grung item                                     |
| gauntlets                     | armor     | 30   | 20  | NerfHack           | 2AC                                                 |
| gauntlets of swimming         | armor     | 50   | 10  | SLASH'EM           | 1AC, grants swimming, protects items from water     |
| gauntlets of force            | armor     | 50   | 10  | NerfHack           | 1AC, stuns monsters, steadfastness                  |
| orcish boots                  | armor     | 16   | 30  | EvilHack           | 1AC (+ 1AC for orcs)                                |
| dwarvish boots                | armor     | 16   | 50  | EvilHack           | 2AC - replaces iron boots                           |
| gnomish boots                 | armor     | 16   | 10  | SlashTHEM          | 0AC                                                 |
| freedom boots                 | armor     | 50   | 20  | NerfHack           | conveys free action                                 |
| stomping boots                | armor     | 50   | 50  | SpliceHack         | Instakills tiny/small monsters, noisy               |
| ring of gain intelligence     | ring      | 200  | 3   | SLASH'EM           | adjusts INT                                         |
| ring of nothing               | ring      | 200  | 3   | dNetHack           |                                                     |
| ring of wounding              | ring      | 200  | 3   | NerfHack           | causes random wounds, reduces regeneration rate     |
| ring of sleeping              | ring      | 200  | 3   | SLASH'EM           | causes restful sleep                                |
| ring of carrying              | ring      | 200  | 3   | xNetHack           | grants expanded carrying capacity                   |
| fang necklace                 | armor     | 0    | 20  | NerfHack           | +1AC for grung                                      |
| magic candle                  | tool      | 500  | 2   | SLASH'EM           | permanent light source                              |
| playing card deck             | tool      | 80   | 10  | SpliceHack         | can reveal your current luck                        |
| glob of like-like             | food      | 6    | 20  |                    |                                                     |
| mistletoe                     | food      | 10   | 1   | EvilHack           | can cure hallucination                              |
| pineapple                     | food      | 9    | 15  | SpliceHack         | can be thrown for extra damage                      |
| pinch of catnip               | food      | 7    | 1   | SpliceHack         | can tame felines                                    |
| holy wafer                    | food      | 12   | 1   | SLASH'EM           | cures lycanthropy, withering                        |
| potion of reflection          | potion    | 200  | 10  | SpliceHack         | conveys temporary reflection                        |
| potion of phasing             | potion    | 200  | 10  | NerfHack           | conveys temporary phasing                           |
| potion of milk                | potion    | 100  | 10  | NerfHack           | cancels good and bad statuses                       |
| potion of blood               | potion    | 100  | 10  | SLASH'EM           | nutrition for vampires                              |
| potion of vampire blood       | potion    | 200  | 10  | SLASH'EM           | nutrition/healing for vampires                      |
| scroll of exile               | scroll    | 200  | 5   | NerfHack           | genocide specific monster(s) on the level           |
| scroll of knowledge           | scroll    | 100  | 5   | SpliceHack         | learn about a random magic item                     |
| scroll of flood               | scroll    | 200  | 5   | UnNetHack/xNetHack | generates water pools                               |
| scroll of transmogrify        | scroll    | 200  | 5   | SpliceHack         | clones items or monsters                            |
| scroll of cloning             | scroll    | 200  | 5   | SpliceHack         | clones items or monsters                            |
| scroll of zapping             | scroll    | 50   | 5   | NerfHack           | special for cartomancers                            |
| scroll of stasis              | scroll    | 200  | 5   | NetHack            | appears instead of wand of stasis                   |
| spellbook of lightning        | spellbook | 500  | 55  | SLASH'EM           | Level 5: shoots a ray of lightning                  |
| spellbook of poison blast     | spellbook | 500  | 55  | SLASH'EM           | Level 5: shoots a ray of poison gas                 |
| spellbook of fire bolt        | spellbook | 100  | 35  | NerfHack           | Level 1: shoots a beam of fire                      |
| spellbook of sacred vision    | spellbook | 200  | 40  | NerfHack           | Level 2: confers see invisible whilst active         |
| spellbook of waterproofing    | spellbook | 200  | 40  | NerfHack           | Level 2: protects items from water and rust         |
| spellbook of divine reckoning | spellbook | 800  | 70  | NerfHack           | Level 8: Massive damage vs undead and demons        |
| spellbook of flesh-to-stone   | spellbook | 700  | 65  | NerfHack           | Level 7: stones monsters                            |
| spellbook of repair           | spellbook | 300  | 45  | EvilHack           | Level 3: repairs any item erosion                   |
| spellbook of flame sphere     | spellbook | 200  | 40  | SLASH'EM           | Level 2: summons flame sphere spell beings          |
| spellbook of freeze sphere    | spellbook | 200  | 40  | SLASH'EM           | Level 2: summons freeze sphere spell beings         |
| wand of wonder                | wand      | 200  | 7   | SpliceHack         | random wand effect                                  |
| wand of identify              | wand      | 200  | 7   | SlashTHEM          | identifies items, spawns with 4-8 charges           |
| wand of poison gas            | wand      | 200  | 7   | SpliceHack         | shoots poison gas                                   |
| wand of corrosion             | wand      | 200  | 7   | SpliceHack         | shoots acid rays                                    |
| wand of draining              | wand      | 200  | 7   | SLASH'EM           | shoots drain life rays                              |
| healthstone                   | gem       | 60   | 10  | SLASH'EM           | affects regeneration                                |
| whetstone                     | gem       | 45   | 10  | SLASH'EM           | sharpens edged weapons                              |
| foulstone                     | gem       | 0    | 10  | NerfHack           | aggravate monster & stinking clouds                 |
| sling bullet                  | weapon    | 1    | 2   | EvilHack           | 1d6 + 1 damage                                      |

* (!) fingerless gloves do not protect against petrification

### potions of blood and vampire blood
* **potions of blood** provide 450 nutrition
* **potions of vampire blood** provide 900 nutrition
* **diluted potions of blood** provide 150 nutrition
* **diluted potions of vampire blood** provide 300 nutrition
* Non-vampire players turning into a vampire via potion of vampire blood is not permanent (from EvilHack).

### potion of milk
* Non-cursed potions of milk reliably cancel out a lot of good and bad effects:
hallucination, confusion, stunning, blindness, protection (from spells), reflection (from potions), phasing (from potions or phase spider corpses), invisibility, see invisible, telepathy, and all vulnerabilities with timeouts
* milk also will un-poly a player or monster back to their original form.

**Other effects:**
* non-diluted milk heals 1 HP and blessed milk increases your max HP by 1.
* cursed milk is always spoiled and causes nausea without cancelling any effects.
* dipping a poisoned item into milk unpoisons it.

### playing card deck
* When applied, gives you a poker hand which correlates to your luck.
* If the deck is blessed (or you are a cartomancer), you get a clear indication of your luck
  by using the kicker.
* If uncursed, you get a rough indication of your luck by the hand strength.
* If cursed, the meanings are reversed.
* Can be #tipped and emptied for a stack of **razor cards**

### scroll of cloning
* Ported from SpliceHack
* clones an item in your inventory or yourself if read whilst confused.
* Attempting to clone unique items or items that are too powerful will result in lesser quality results: magic markers, scrolls of cloning, artifacts, and any invocation items will produce a lesser type of item.
* To copy the enchantment on an item, the scroll must be blessed.
* If the scroll is cursed, the resulting item will be cursed.
* All other properties on the item should be copied exactly as is.
* When confused, the scroll clones the player. The resulting clone will have no inventory. A blessed scroll creates a tame clone, an uncursed scroll makes a peaceful clone, and a cursed scroll makes a hostile clone. A notable side-effect of this is that cloning yourself reduces your current HP by half.
* If confused and the scroll is blessed, you can also clone yourself to create a powerful tame pet if you currently hold a strong polyform (ie: master mind flayer, purple worm, etc)
* Scrolls of cloning cannot be created from polypiling nor written.
* Unpaid items cloned in shops now become the property of the shopkeeper. Additionally, more item properties are carried over during cloning, including erosion-proofing, container status, and other miscellaneous attributes to ensure that items are genuinely cloned.
* Intelligent monsters can also use these scrolls to clone themselves. When monsters read the scrolls, they are always read-as-confused, meaning they can only clone themselves. Whilst this approach might seem odd, it simplifies the system by avoiding the complexities of allowing monsters to clone items.
* **Unique monsters can use these scrolls as well**, but the Wizard of Yendor must still follow the Double Trouble routine, ensuring that no more than two Rodneys can oppose you at any time. However, other unique monsters have the potential to clone themselves more than once if the opportunity arises.

### scroll of transmogrify
* These scrolls can change the material of an item.
* When blessed, they will also bless the item.
* If cursed or confused, the item's material will change to a material your race hates, or plastic if no valid materials are found.

#### confused reading of scroll of transmogrify
* When read whilst confused, scroll of transmogrify skips its normal change material effect and instead operates on the target item's properties.
* It picks a target the same way as usual (your wielded weapon or a piece of worn armor).
* If the scroll is cursed, it strips off any existing property off the item.
* If blessed — or the item already carries a property even when uncursed — it strips the old property in blue light and rerolls a new one (re-rolling until it actually gets something different), reapplying any worn/wielded bonuses before and after.
* An uncursed scroll on a plain, property-less item just fizzles with "nothing happens."
* Artifacts flatly resist this effect.

### healthstone
* A blessed healthstone now increases your regeneration rate by 10%.
* An uncursed healthstone increases regeneration by 5%.
* A cursed healthstone decreases regeneration by 10%.
* Healthstones usually generate cursed, making them stand out a bit more among gray stones and a little easier to identify.
* Monsters carrying non-cursed healthstones also gain regeneration.

### whetstone
* Refined the functionality of whetstones and made much more functional and user friendly. We can now apply a stack of whetstones to a stack of weapons (Before this was limited to applying one whetstone to a single object). We can use (a)pply or #rub with whetstones.
* Previously, whetstones took too long to use and the required time has been lowered considerably. If sharpening a stack of weapons, the turns will scale with the size of the stack. Cavemen are skilled with rocks so they can sharpen much faster than other roles.
* You can use whetstones in shallow water, pools, moats, rust traps, sinks, and toilets.
* If you don't have a water source available, you can use potions of water. There is a 1d7 chance of using the potion up on each application.
* In SLASH'EM, using a whetstone on a water source would also activate the quaffing effects of those features. In NerfHack these effects have been removed.
* Cursed whetstones can rust or corrode items.
* Blessed whetstones can uncurse a cursed weapon, but lose their blessed state in the process.
* Blessed whetstones can also enchant a +0 weapon up to a max of +1.
* Whetstones can now remove corrosion (in addition to rust)

### foulstone
A **foulstone** is a new gray stone with several unusual effects for anyone carrying it. Simply possessing a foulstone causes monsters to become aggravated, though it does not increase the difficulty of those that spawn as a ring of aggravate monster would. Whilst carrying a foulstone, monsters cannot digest you. Likewise, you cannot digest monsters that are also carrying a foulstone. Shopkeepers will refuse to let you enter their stores if you have one, and they will not purchase the stone under any circumstances (it is very stinky).

Foulstones have unique magical properties depending on their blessing status. If blessed, there is a 1 in 100 chance per turn that the stone emits a stench that temporarily scares nearby monsters, similar to the effect of garlic breath. If not blessed, there is a 1 in 100 chance per turn of releasing a poisonous cloud centered on the carrier. These effects can stack, so carrying multiple foulstones increases the likelihood of either event occurring each turn. The stacking effects only count up to a maximum of 10 foulstones for either the blessed or cursed effects.

Additional traits include its total inedibility - monsters will never eat it. Pets treat it as a cursed object and will avoid stepping on it. Rubbing a foulstone on another rock will cause it to emit a poisonous cloud. Foulstones always generate cursed. If cursed, they behave like loadstones and cannot be dropped voluntarily - making this another dangerous gray stone to be wary of.


## ARTIFACT CHANGES


### General artifact changes
* Artifacts always blast you if they have the chance (instead of passing a 1 in 4 roll)
* Artifact blasts inflict much more damage (SLASH'EM)
* Increase rate of artifact drops slightly; allow lenses and amulets to generate as artifacts.
* Increase timeout of artifact invokes to match prayer timeout.

### Specific artifact changes
* Cleaver is prevented from cleaving peaceful bystanders (unless cursed) (xNetHack)
* Excalibur will fix any negative enchantment on it when created from #dipping (xNetHack)
* Buff Excalibur with magic missile attacks (from Hack'EM)
* Eye of the Aethiopica must be worn to grant energy regeneration and half-spell damage
* Eyes of the Overworld protect against more gaze attacks (EvilHack)
* Eyes of the Overworld's xray-vision range was increased to 8 (from FIQHack)
* Fire Brand instakills highly flammable monsters and green slimes (xNetHack)
* Fire Brand cures sliming whenever you attack with it
* Frost Brand instakills water elementals
* Giantslayer is now a spear (EvilHack)
* Giantslayer conveys 18/\* strength whilst wielded (Dynahack)
* Grimtooth can inflict disease on its victims (EvilHack)
* Heart of Ahriman is now a ruby that grants slotless flying, displacement, and Luck instead of stealth (FIQHack)
* Heart of Ahriman can be invoked for a blessed remove curse effect (Fourk)
* The Heart of Ahriman inflicts random pillars of fire on enemies when attacking
* The Longbow of Diana must be wielded to grant ESP
* Longbow of Diana confers half physical damage when wielded
* Magicbane is a quarterstaff (FIQHack)
* Magic Mirror of Merlin grants reflection and 1/2 spell damage instead of magic resistance (EvilHack)
* Master Key of Thievery doesn't need to be wielded to auto-sense traps
* Mjollnir is louder when it strikes monsters with lightning
* Mjollnir can be invoked for a lightning bolt (xNetHack)
* Ogresmasher can also hurtle light-weight monsters (EvilHack)
* Orb of Detection grants clairvoyance whilst carried
* Sceptre of Might grants steadfastness when wielded
* Sceptre of Might gets a bonus on all monsters (this is to compensate for the difficulty in enchanting it due to its magic resistance)
* Sceptre of Might blocks spellcasting and counters monster spells
* Snickersnee grants stun resistance when wielded (EvilHack)
* Staff of Aesculapius can cure withering (xNetHack/EvilHack)
* Sting actually cuts through webs when exiting a web
* Trollsbane grants regeneration whilst wielded (many variants)
* Trollsbane only needs to be carried to suppress troll revival
* Tsurugi of Muramasa has a 10% chance of bisection (SLASH'EM)
* Tsurugi of Muramasa also confers very fast speed when wielded (Fourk)
* Vorpal Blade gets a 10% chance of beheading (SLASH'EM)
* Vorpal Blade grants see invisible whilst wielded
* Vorpal Blade provides warning vs jabberwocks (EvilHack)
* Werebane provides protection from shapechangers when wielded

**Bane changes:**
* All banes provide warning vs their bane monster type when wielded (EvilHack)
* All banes glow red in response to their monster types (EvilHack)
* All banes can instakill their associated monster types with a 1 in 5 chance (UnNetHack)
* Sunsword and Disrupter don't get instakills
* Banes can't instakill unique monsters


## NEW ARTIFACTS


| Name                  | Align      | Type                  | From        | to-hit/dmg                         | Notes                                                    |
| --------------------- | ---------- | --------------------- | ----------- | ---------------------------------- | -------------------------------------------------------- |
| Acidfall              | chaotic    | long sword            | SpliceHack  | +d5 to-hit, 2x acid dmg            | acid res                                                 |
| Amulet of Storms      | chaotic    | amulet of flying      | xNetHack    | n/a                                | shock res, storm paralysis res                           |
| Angelslayer           | chaotic    | trident               | EvilHack    | +d5 to-hit, +d10 dmg               | bane vs angels; searching, 1/4 spell dmg                 |
| Blackshroud           | chaotic    | cloak of invisibility | SlashTHEM   | n/a                                | warning, drain res                                       |
| Carnwennan            | lawful     | knife                 | SpliceHack  | +d3 to-hit, +d8 dmg                | searching, stealth                                       |
| David's Sling         | neutral    | sling                 | SlashTHEM   | +d5 to-hit, +d6 dmg                | bane vs giants; confers 1/4 phys dmg                     |
| Deluder               | neutral    | cloak of displacement | SLASH'EM    | n/a                                | stealth, protection                                      |
| Disrupter             | neutral    | mace                  | SLASH'EM    | +d5 to-hit, +d30 dmg               | bane vs undead                                           |
| Doomblade             | chaotic    | short sword           | SLASH'EM    | bonus damage                       |                                                          |
| Drowsing Rod          | unaligned  | quarterstaff          | HackEM      | +d5 to-hit, +d5 sleep dmg          | sac gift for healers; sleep res                          |
| Glamdring             | chaotic    | long sword            | EvilHack    | +d8 to-hit, +d10 dmg               | bane vs orcs; shock res, protection                      |
| Hellfire              | chaotic    | crossbow              | SLASH'EM    | +d5 to-hit, +d7 dmg + explosion    | fire res                                                 |
| Holographic Void Lily | chaotic(!) | credit card           | SpliceHack  | n/a                                | energy regen, 1/4 spell dmg, reflection                  |
| Load Brand            | unaligned  | heavy sword           | NerfHack    | -9 to-hit, double damage           | 1/4 phys dmg, steadfastness, protection; absorbs curses. |
| Mayhem                | chaotic    | stomping boots        | NerfHack    | n/a                                | conflict, warn vs undead.                                |
| Mirrorbright          | neutral    | shield of reflection  | SLASH'EM    | n/a                                | light, hallu res, doesn't impede spells.                 |
| Mortality Dial        | lawful     | morning star          | SpliceHack  | +d5 to-hit, +d12 dmg               | warning, regen; prevents monster regen                   |
| Mouser's Scalpel      | neutral    | rapier                | SLASH'EM-up | +d5 to-hit, +1 dmg; multihit bonus |                                                          |
| Origin                | unaligned  | quarterstaff          | SpliceHack  | +d3 to-hit, +d8 dmg                | telepathy, teleport control; boosts spellcasting         |
| Plague                | chaotic    | bow                   | SLASH'EM    | +d5 to-hit, +d7 poison dmg         | sickness res on wield, poison res when carried.          |
| Poseidon's trident    | chaotic    | trident               | SpliceHack  | +d3 to-hit, +d14                   | magical breathing; #invoke for water walking             |
| Pridwen               | lawful     | large shield          | SpliceHack  | n/a                                | 1/4 phys damage, steadfastness                           |
| Quick Blade           | lawful     | silver short sword    | SLASH'EM    | +d9 to-hit, +d2                    | confers speed when wielded                               |
| Serenity              | lawful     | silver spear          | NerfHack    | +d3 to-hit, +d10                   | counterspells; blocks aggravation/berserk/conflict       |
| Serpent's Tongue      | chaotic    | dagger                | SLASH'EM    | +d2 to-hit, 2x damage + poison     | permapoison, #invoke to fling poison                     |
| Skullcrusher          | lawful     | club                  | SLASH'EM    | +d3 to-hit, +d10 dmg               | sac gift for cavemen                                     |
| Snakeskin             | Neutral    | robe                  | SlashTHEM   | n/a                                | acid/hallu res                                           |
| The End               | neutral    | scythe                | SpliceHack  | +d3 to-hit, +d10 dmg               | drain res                                                |
| The Lenses of Truth   | unaligned  | lenses                | NerfHack    | n/a                                | see inv,stun res                                         |
| Thunderfists          | neutral    | gauntlets of force    | NerfHack    | +3 to-hit, +1d8 shock damage       | shock res, protection                                    |
| Whisperfeet           | neutral    | speed boots           | SLASH'EM    | n/a                                | stealth, luck                                            |
| Oathfire              | lawful     | leather bracers       | NerfHack    | n/a                                | fire res, protection, passive fire                       |
| The Argent Cross      | lawful(!)  | amulet of reflection  | NerfHack    | n/a                                | light, spell damage, dis/wither res, passive turn undead |

(!) - Means the artifact is intelligent
Misc changes:
* Plague was changed from an orcish bow to a standard bow.
* Quick Blade is a silver short sword instead of an elvish short sword
* Blackshroud was a neutral cloak in SlashTHEM - it was changed to chaotic.
* Skullcrusher was a club in SLASH'EM, but it has been changed to an aklys.
* Wielding Origin protects from amnesia.
* Snakeskin provided a point of protection in SlashTHEM but that was removed and provides MC2 as a robe.
* Scythes are a type of polearm that can be used in melee but they have a -2 to-hit penalty.
* Mortality Dial was an executioner's mace in SpliceHack but it was changed to a morning star with higher damage. It also now grants warning.
* In NetHack 3.7.0, Grimtooth can be invoked to fling poison. However, since it was already buffed with a disease attack, this ability was moved to Serpent's Tongue.

### Load Brand
* This heavy sword was forged from load stones and weighs in at a hefty 500aum!
* Deals 3d6 vs small monsters and 3d8 vs large monsters
* -9 to-hit penalty
* Double damage
* It also confers half physical damage, steadfastness, and MC1 protection
* Similar to Magicbane, it also absorbs curses

### The Lenses of Truth
* Confers see invisible and stun resistance when worn.

### Serenity
* +d10 damage
* counters 80% of monster spells whilst wielded
* whenever it successfully counters, the caster briefly requires more time to recover and cast another spell
* blocks you from casting spells when wielded
* blocks aggravate monster and conflict
* blocks barbarian blood rage from activating if wielded
* prevents monsters from berserking

### Thunderfists
* gauntlets of force
* Grants shock resistance when worn
* Deals shock damage when used bare-handed
* When monks don these, they occasionally release a chain lightning blast on attacking
* Grants MC1
* Crowning gift for monks


## NEW MONSTERS


Many new monsters have been added to NerfHack. See the separate file with all the additions and info on changes from related variants.

The following summarizes the new monsters, advanced info can be found in the monster pokedex in NerfHack or on the NetHack Wiki.

| Monster                | Sym | Origin               |
| ---------------------- | --- | -------------------- |
| giant fly              | a   | SpliceHack           |
| giant cockroach        | a   | EvilHack             |
| giant praying mantis   | a   | SpliceHack           |
| bullet ant             | a   | SpliceHack           |
| locust                 | a   | EvilHack             |
| queen ant              | a   | EvilHack             |
| assassin bug           | a   | SLASH'EM             |
| migo drone             | 7   | SLASH'EM             |
| migo warrior           | 7   | SLASH'EM             |
| migo queen             | 7   | SLASH'EM             |
| jiggling blob          | b   | SLASH'EM             |
| lava blob              | b   | SLASH'EM             |
| static blob            | b   | SLASH'EM             |
| burbling blob          | b   | SLASH'EM             |
| basilisket             | c   | NerfHack             |
| basilisk               | c   | EvilHack             |
| warg pup               | d   | NerfHack             |
| revenant pup           | d   | NerfHack             |
| barghest               | d   | SpliceHack           |
| shadow wolf            | d   | SLASH'EM             |
| revenant hound         | d   | NerfHack             |
| vulpenferno            | d   | SpliceHack           |
| weredemon              | d/@ | EvilHack             |
| glowing eye            | e   | SLASH'EM             |
| stinking sphere        | e   | Fourk                |
| acid sphere            | e   | SpliceHack/EvilHack  |
| third eye              | e   | SLASH'EM/YANI        |
| blinking eye           | e   | SLASH'EM             |
| kamadan                | f   | SLASH'EM             |
| weretiger              | f/@ | SLASH'EM             |
| deep one               | h   | SLASH'EM             |
| deeper one             | h   | SLASH'EM             |
| deepest one            | h   | SLASH'EM             |
| alhoon                 | h   | EvilHack             |
| dretch                 | i   | SLASH'EM             |
| rutterkin              | i   | SLASH'EM             |
| blood imp              | i   | SLASH'EM             |
| nupperibo              | i   | SLASH'EM             |
| redcap                 | i   | SpliceHack           |
| clear jelly            | j   | SLASH'EM             |
| yellow jelly           | j   | SLASH'EM             |
| orange jelly           | j   | SLASH'EM             |
| rancid jelly           | j   | SLASH'EM             |
| leper                  | l   | NerfHack             |
| killer mimic           | m   | SpliceHack           |
| boulderer              | m   | CrecelleHack         |
| pixie                  | n   | SLASH'EM             |
| blight sprite          | n   | NerfHack             |
| spiked orc             | o   | NerfHack             |
| diamond piercer        | p   | SpliceHack           |
| god piercer            | p   | SpliceHack           |
| landshark              | q   | SpliceHack           |
| pack rat               | r   | SLASH'EM             |
| hedgehog               | r   | SpliceHack           |
| plague rat             | r   | NerfHack             |
| recluse spider         | s   | SLASH'EM             |
| nickelpede             | s   | SLASH'EM             |
| phase spider           | s   | SLASH'EM             |
| werespider             | s/@ | SLASH'EM             |
| carrion crawler        | s   | SLASH'EM             |
| monstrous spider       | s   | SpliceHack           |
| giant scorpion         | s   | SLASH'EM             |
| giant centipede        | s   | EvilHack             |
| acid worm              | w   | SLASH'EM             |
| bloodworm              | w   | SLASH'EM             |
| tunnel worm            | w   | SLASH'EM             |
| carrion larva          | w   | NerfHack             |
| rot worm               | w   | SLASH'EM             |
| maggot                 | w   | SLASH'EM/SpliceHack  |
| spark bug              | x   | SLASH'EM             |
| arc bug                | x   | SLASH'EM             |
| crystallid             | x   | NerfHack             |
| lightning bug          | x   | SLASH'EM             |
| soul shadow            | y   | NerfHack             |
| will-o'-the-wisp       | y   | SpliceHack           |
| bandikot               | z   | SLASH'EM/NerfHack    |
| compsognathus          | z   | NerfHack             |
| velociraptor           | z   | SpliceHack           |
| t-rex                  | z   | SpliceHack           |
| dark angel             | A   | UnNetHack            |
| movanic deva           | A   | SLASH'EM             |
| monadic deva           | A   | SLASH'EM             |
| astral deva            | A   | SLASH'EM             |
| zoo bat                | B   | SpliceHack           |
| athol                  | B   | SLASH'EM             |
| phoenix                | B   | SpliceHack           |
| byahkee                | B   | SLASH'EM             |
| nightgaunt             | B   | SLASH'EM             |
| fell beast             | D   | EvilHack             |
| baby shimmering dragon | D   | Deferred             |
| baby shadow dragon     | D   | EvilHack             |
| shimmering dragon      | D   | Deferred             |
| shadow dragon          | D   | EvilHack             |
| volatile mushroom      | F   | SpliceHack           |
| gray fungus            | F   | EvilHack/SlashTHEM   |
| gnoll                  | 9   | SLASH'EM             |
| gnoll warrior          | 9   | SLASH'EM             |
| gnoll chieftain        | 9   | SLASH'EM             |
| gnoll shaman           | 9   | SLASH'EM             |
| hill giant shaman      | H   | EvilHack             |
| elder minotaur         | H   | EvilHack             |
| worm that walks        | L   | SpliceHack           |
| eye of fear and flame  | L   | SpliceHack           |
| arch-vile              | L   | NerfHack             |
| adherer                | M   | SpliceHack           |
| troll mummy            | M   | SLASH'EM             |
| ha-naga                | N   | SpliceHack           |
| ogre mage              | O   | SLASH'EM             |
| shadow ogre            | O   | SLASH'EM             |
| like-like              | P   | NerfHack             |
| shoggoth               | P   | SLASH'EM             |
| orb weaver             | Q   | NerfHack             |
| alchemist              | Q   | SpliceHack           |
| degenerator            | R   | NerfHack             |
| cerastes               | S   | SpliceHack           |
| asphynx                | S   | SLASH'EM             |
| weresnake              | S/@ | SLASH'EM             |
| giant anaconda         | S   | EvilHack             |
| grave troll            | T   | SpliceHack           |
| umbral hulk            | U   | SlashTHEM/SpliceHack |
| water hulk             | U   | SLASH'EM             |
| hunger hulk            | U   | SpliceHack           |
| slumber hulk           | U   | SpliceHack           |
| gorgon hulk            | U   | NerfHack             |
| fire vampire           | U   | SLASH'EM             |
| star vampire           | U   | SLASH'EM/dnh         |
| dhampir                | V   | NerfHack             |
| vampire mage           | V   | SLASH'EM             |
| vampire king           | V   | EvilHack             |
| bodak                  | W   | SpliceHack           |
| slaughter wight        | W   | HackEM               |
| illusion               | X   | CrecelleHack         |
| shadow                 | X   | SLASH'EM             |
| ghoul mage             | Z   | SLASH'EM             |
| revenant               | Z   | EvilHack             |
| gug                    | Z   | SLASH'EM             |
| ghoul queen            | Z   | SLASH'EM             |
| wax golem              | '   | SLASH'EM             |
| plastic golem          | '   | SLASH'EM             |
| elven cleric           | @   | EvilHack             |
| elven mage             | @   | NerfHack             |
| familiar               | @   | NerfHack             |
| lava demon             | &   | Convict Patch        |
| spined devil           | &   | SLASH'EM             |
| merfolk                | ;   | SpliceHack/SlashTHEM |
| thing from below       | ;   | SpliceHack           |
| grung                  | 6   | NerfHack             |
| green grung            | 6   | NerfHack             |
| blue grung             | 6   | NerfHack             |
| purple grung           | 6   | NerfHack             |
| red grung              | 6   | NerfHack             |
| orange grung           | 6   | NerfHack             |
| gold grung             | 6   | NerfHack             |
| cartomancer            | @   | SpliceHack           |
| duelist                | @   | SpliceHack           |
| King of Games          | @   | SpliceHack           |
| Del Zethire            | @   | SpliceHack           |
| undead slayer          | @   | SLASH'EM             |
| exterminator           | @   | SLASH'EM             |
| Van Helsing            | @   | SLASH'EM             |
| The First Evil         | X   | NerfHack             |
| Wintercloak            | D   | NerfHack             |
| The Executioner        | @   | UnNetHack            |
| Cthulhu                | &   | SLASH'EM/UnNetHack   |


## MONSTER CHANGES


### Misc monster changes
* all quest guardian colors were changed to cyan
* all A class monsters are immune to death magic (xNetHack)
* all A class monsters resist sickness
* increased difficulty of all A-class spellcasters.
* Some monsters on the Astral Plane spawn with foulstones or teleport control to thwart "purple rain" and teleportation strategies.
* air elementals get shock resistance
* Aleax difficulty raised to 16 (SLASH'EM)
* Aleax weapon attacks raised to 2d6 (Sporkhack)
* baluchitherium are now huge; have -5 AC, strengthened claw attack from 5d4 to 5d12; increased difficulty
* all bats can see invisible
* captains are considered princes (xNetHack)
* captains and watch captains generate with keys (EvilHack)
* captains have poison resistance
* centaurs will keep their distance from the player (xNetHack)
* couatls get sleep and shock resistance (Fourk)
* couatls get a stunning gaze and can generate invisible
* many major demons have been given flight (xNetHack)
* dingos have been replaced with warg pups - very similar to dingos but slight adjustments so they can grow into wargs
* disenchanters can appear in the main dungeon
* disenchanter attacks can also remove erodeproofing from items.
* dragons, nagas, and golems don't balk at approaching as much
* dwarves sometimes start with potions of booze (xNetHack)
* all elementals resist sickness
* arch-liches resist acid
* elf-lords get 9AC, Elvenkings get 8AC (K-Mod)
* erinys can generate up to 13 times (previously only 3 could be birthed in the entire game)
* ettins count as giants and are vulnerable to sling damage
* fire giants get an active fire attack (xNetHack)
* floating eyes inflict less passive paralysis; wisdom limits duration (Dynahack)
* all footrice can fly
* all footrice have more potent hissing attacks that have double the chance of inflicting stoning
* foocubi gain a level when draining one from the player (xNetHack)
* frost giants get an active frost attack (xNetHack)
* gas spores and volatile mushrooms start with exactly 1 HP
* genetic engineers grudge all other monsters; increased difficulty
* all ghost class monsters get acid resistance
* giant mimics get an engulf-digest attack
* giant spiders can ensnare monsters in webs (EvilHack)
* giant spiders can be saddled
* gnome lords and kings always get gnomish suits
* gnomish wizards always get a gnomish helm
* gnomes get candles in the mines twice as often as before
* goblins can generate in small groups (Sporkhack)
* green slimes can hide on the ceiling (xNetHack)
* green slimes can appear in the main dungeon, are faster (going from 6 to 13 speed), higher difficulty
* green slimes have a passive sliming attack (Grunt)
* gremlins can steal intrinsics no matter the time of day (FIQHack)
* peaceful gremlins don't use fountains/pools/etc to split themselves (Fourk)
* hobbits can get flint with their slings (xNetHack)
* horned devils get a butt attack
* all hulks resist poison
* ice and bone devils are now lawful (xNetHack)
* ice devils have speed 8 (K-Mod)
* ice devils' cold sting and claw attacks have been buffed, they have the power to strip cold resistance from the player or monsters (xNetHack)
* iron golems get a passive disenchant attack (from SLASH'EM steel golems)
* jellyfish get a passive paralyzing attack
* Keystone Kops are tougher (K-Mod)
* Keystone Kops no longer wander, but instead can flank
* leprechauns do not stash gold in the ground after stealing it (reverted from 3.7)
* leprechauns can steal any item made of gold (from EvilHack)
* lizards appear with slightly less frequency
* ki-rin get shock, sleep, cold, and poison resistance (xNetHack)
* long worms have thick skin, 7 speed, -5AC, a 2d10 bite attack, and accurate behavior
* long worm segments have a lower chance to be cut
* lords and princes never get negative weapons or armor (xNetHack)
* lieutenants are considered lords (xNetHack)
* lieutenants have poison resistance
* master liches and arch-liches can see invisible (FIQHack)
* mastodons are now huge, have -8 AC, stronger butt attacks, increased difficulty
* mastodons get a hug attack and can berserk (EvilHack)
* giant mimics, large mimics, and killer mimics are higher level and difficulty
* mimics take the form of strange objects much less often
* mind flayers are bright magenta (EvilHack)
* mind flayer attacks can make hero forget skills (EvilHack) - however the frequency and impact of these attacks has been weakened
* mind flayer psychic blasts do more damage; if the victim is telepathic they can also be stunned
* minotaurs resist death magic (SLASH'EM)
* minotaurs have a thick hide, have flanking, and berserk
* minotaurs carry wands of digging less often
* molds can generate in small groups
* molds and fungus can grow on corpses (SLASH'EM/xNetHack)
* monkeys get a small head start after they steal an item (xNetHack)
* Mordor orcs can spawn with orcish boots
* mumakil get butts or kicks instead of bites
* all mummies get a nasty withering attack (xNetHack/EvilHack)
* all mummies get an additional -1AC to compensate for their ragged wrappings
* Nazgul always spawn accompanied by a fell beast (EvilHack)
* Nazgul have increased level, difficulty, AC, attack strength, infravision, and MR (EvilHack)
* Nazgul get an additional weapon/drain attack, can flank, and resist stoning
* nurses won't heal you if you are undead
* nurses can also cure rabid status
* nurses cannot flank or assist flanking
* nurses grant max-HP at a much higher rate, for quicker "nurse dancing"
* nurses will follow you across levels
* nymphs spawn with mirrors half as often (25% chance instead of 50%)
* olog hai get poison resistance, are huge, have thick skin, higher level and speed, with raised difficulty
* all orcs can stalk the player
* orc captains now are lords and have speed 9 (xNetHack)
* orc shamans and kobold shamans are skittish (FIQHack)
* pit fiends have speed 8 (K-Mod)
* priests of Moloch are always generated hostile (SLASH'EM)
* purple worms have thick skin
* pyrolisks have negative alignment
* quasits are faster, have stronger attacks, see invisible, and can appear in small groups (xNetHack)
* quasits can flank
* queen bees can displace monsters
* quest leaders resist death magic (EvilHack)
* quest nemeses can break boulders after getting frustrated enough
* rock moles can actually eat rocks (xNetHack)
* rock trolls are stoning resistant (xNetHack)
* shriekers can shriek from any distance whenever they see you
* all spheres explode on death (unless cancelled)
* all spheres have speed 15 and 0 AC
* all spheres are tiny (so they can pass through iron bars)
* skeleton and shade slow attacks are ineffective vs undead
* soldiers get half as many C-and-K-rations (K-Mod)
* soldiers and their higher ranks get level, speed, AC, and MR boosts (K-Mod)
* soldiers can generate with shuriken
* Mercenaries sometimes get bracers instead of a large shield.
* seducing monsters will introduce themselves before stealing items (SpliceHack/xNetHack)
* sewer rats hide under objects (xNetHack)
* scorpions are tiny
* shades get 20MR
* shapechangers turn back to their base form when killed with 50-75% of their health (SLASH'EM)
* shapechangers hold level-appropriate form longer, out-of-depth forms for less time (Fourk)
* cancelled shapeshifters cannot change form
* shopkeepers' base level raised to 24, AC to -6 (SLASH'EM)
* shopkeepers get extra defensive items (SLASH'EM)
* shopkeepers get a wand of sleep instead of striking (EvilHack)
* shopkeepers and priests are colored yellow (xNetHack)
* shopkeepers resist sleep and poison
* tame spiders will not spin webs
* storm giants get an active ranged lightning attack (xNetHack)
* telepathic monsters convey a short amount of intrinsic telepathy when eaten
* titans can see invisible (FIQHack)
* titans resist death magic (SLASH'EM)
* titans are level 17 (K-Mod)
* titans get shock and poison resistance.
* tigers are orange (EvilHack)
* tigers can also jump
* titanotheres are now huge, have -2 AC, stronger claw attacks, increased difficulty
* trappers and lurkers above are mindless and speed 6
* troll meat provides temporary intrinsic regeneration (xNetHack)
* violet fungi puff out hallucination-inducing spores when hit
* all vortices (v) resist shock damage
* vampshifting has been totally removed for both monsters and polyforms.
* vampires (any V) are not afraid of Molochian altars
* vampires attack with their bite attacks first
* vampires can use weapons (EvilHack)
* wargs have a thick hide
* all werefoo in animal form get infravision
* werefoo revert back to their base form when killed (SLASH'EM)
* werefoo can occasionally summon rabid brethren
* werefoo can disguise themselves in both animal and humanoid forms (Crecelle)
* werewolves and weretigers have a higher level and difficulty, stronger attacks
* wraiths also no longer "stalk" the player and follow them across levels (Dynahack)
* the wumpus is now unique to the ranger quest; it appears in a random room in the Ranger's locate level
* the wumpus is now huge with a thick hide, stronger bite attack, increased difficulty
* xans can't fly (dNetHack)
* xorns have flanking
* yellow and black light explosions are directionless (xNetHack)
* yellow molds puff out stunning spores when hit
* wood nymphs are slightly slower than average, lower difficulty (xNetHack)
* wood nymphs leave grass instead of corpses (CrecelleHack), and also 1 in 3 times they will leave a tree instead (NerfHack)
* water nymphs are slightly higher level and difficulty (xNetHack)
* mountain nymphs are higher level, faster, and higher difficulty (xNetHack)
* hill giants are lower level and difficulty (xNetHack)
* stone giants are slightly stronger and can wrest boulders out of the ground (xNetHack)

### Delayed stoning for all footrice effects
* This was ported from EvilHack with extensions.
* Instant petrification has been removed for all effects EXCEPT for Medusa's stoning gaze.
* Instead, wherever a monster or player would have been instakilled, a stoning timer is started for 5 turns.
* This applies for every non-Medusa instapetrification effect: touching a footrice corpse, being knocked into a footrice, and so on.
* Footrice only inflict slow stoning for the player and for monsters
* Related change: the nutrition for lizard corpses has been dramatically reduced. The intention is to limit their use to 1-2 un-stonings per corpse.
* Strong monster spellcasters also have the ability to cast stone-to-flesh on themselves in an emergency.

### Dangerous piercers
* All piercers are mindless and can grow up into stronger piercers.
* Much more AC is required to dodge dropping piercers (previously, -2AC would nullify their drop attacks, now -22AC is required).
* Piercing damage scales with their level (monster level * 6) with a minimum of 4d6 being dealt.
* Piercers and lurkers/trappers always generate hidden if possible.
* Hidden piercers (and other ceiling clingers) can surprise attack you from adjacent squares.
* Undead monsters on the Astral Plane are replaced with random A (xNetHack).

**Piercers can actually pierce hard helmets:** Piercers can penetrate even the toughest helmets, but the level of enchantment on your helmet determines its resistance to piercer damage and destruction:

**Helmet Resistance:**
* Only hard and metal helmets are affected, cloth and leather helms are safe from this specific damage.
* If a piercer strikes a helmet with a negative enchantment, the helmet is instantly destroyed.
* For helmets with positive enchantments, a successful hit reduces the enchantment level by -1. With bad luck, the penalty may range from -1 to -3.
* Glass and crystal helmets: glass helmets don’t lose enchantments. Instead, they crack over time, following erosion rules rather than enchantment degradation.
* Enchanting your helmet can protect it from damage. A higher enchantment level defends against weaker piercers but may still be vulnerable to stronger ones.
* Special case - god piercers: God piercers deal extremely high damage. Your best defense is achieving an AC of -22 or better, as even the most enchanted helmets provide limited protection against their attacks.

**Enchantment Levels and Piercer Resistance:**
* +1 enchantment: Generally protects against rock piercers.
* +2 enchantment: Generally protects against iron piercers.
* +3 enchantment: Generally protects against glass piercers.
* +4 enchantment: Generally protects against diamond piercers.

### Reviving and Poisonous Zombies
* Zombie corpses may auto-revive similar to trolls (EvilHack/xNetHack)
* Cancelled or beheaded zombies/trolls don't revive (EvilHack)
* Wielding Sunsword prevents zombies corpses from appearing (EvilHack)
* Playing as a priest reduces the chance of zombie revival by 50% (Dynahack)
* All zombies get an additional poisonous bite attack that can drain constitution.
* Sometimes zombies will try to bite the player's legs, inflicting wounded legs for a short time.
* Zombies are immune to being scared by Elbereth

### Dragon changes
* Dragons have been overhauled to present a more potent threat to the player, with influences from FIQHack, SLASH'EM, and EvilHack.
* Part of the challenge in SLASH'EM was that adult dragons (and therefore dragon scales) were more difficult to come by. In NerfHack, adult dragons are guaranteed in certain places like the Castle, Ludios, and the Healer quest. Dragons of all types can appear in the Wyrm Caves and in the dragon lair themed rooms.
* Dragons are always generated awake and angry for Knights (from EvilHack).
* Dragons get extremely angry when the hero wears matching scales.
* All dragons generate at a higher frequency; baby dragons will generate randomly in the dungeon but not in Gehennom

**Baby dragon changes**
* Most baby dragons have these base level stats:
  *  level 8, difficulty 8, speed 14, AC 2, MR 10
* Increased their bite attack to 3d6.
* All baby dragons get two additional 2d4 claw attacks
* For most dragons, their bite matches their adult breath attack (red = fire bite, blue = shock bite, etc). (K-Mod)
  * baby gray dragons get a disenchanting bite
  * baby black dragons get a withering bite
  * baby silver and shimmering dragons get a stunning bite
* baby dragon alignments match their adult counterparts (EvilHack)
* baby red dragons can berserk
* baby blue dragons are slightly faster at speed 18

| Dragon     | Level | Difficulty | Speed | AC  | MR  | Align | resists            |
| ---------- | ----- | ---------- | ----- | --- | --- | ----- | ------------------ |
| gray       | 8     | 8          | 14    | 2   | 30  | 4     | magic              |
| gold       | 8     | 8          | 14    | 2   | 10  | 4     | fire               |
| silver     | 8     | 8          | 14    | 2   | 40  | 4     | -                  |
| shimmering | 8     | 8          | 14    | 2   | 10  | 4     | stun               |
| red        | 8     | 8          | 14    | 2   | 10  | -4    | fire               |
| white      | 8     | 8          | 14    | 2   | 10  | -4    | cold               |
| orange     | 8     | 8          | 14    | 2   | 10  | -5    | sleep              |
| black      | 8     | 8          | 14    | 2   | 10  | -6    | disintegration     |
| blue       | 8     | 8          | 18    | 2   | 10  | -7    | shock              |
| green      | 8     | 8          | 14    | 2   | 10  | -6    | poison/sick        |
| shadow     | 8     | 16         | 12    | 2   | 10  | -7    | sleep/poison/drain |
| yellow     | 8     | 8          | 14    | 2   | 10  | -7    | acid/stone         |

**Adult dragon changes**
* Stronger attacks:
  * Increased both claw attacks from 1d4 to 2d4 each.
  * Increase damage of dragon breaths to 6d8.
  * All adult dragons get a passive attack that matches their type
  * All adult dragons get an engulf attack
* All adult dragons can flank
* Speed has been increased from 12 to 20, with a small buff to their claw attacks (FIQHack)
* all dragons stalk/follow the player (FIQHack)
* red dragons can berserk
* blue dragons are faster (speed 24)
* shimmering dragons have displacement and resist stunning
* Red, green, white, orange, and yellow dragons can no longer see invisible.

| Dragon     | Level | Difficulty | Speed | AC  | MR  | Align | resists                  |
| ---------- | ----- | ---------- | ----- | --- | --- | ----- | ------------------------ |
| gray       | 15    | 20         | 20    | -1  | 60  | 4     | magic                    |
| gold       | 15    | 20         | 20    | -1  | 20  | 4     | fire                     |
| silver     | 15    | 20         | 20    | -1  | 95  | 4     | -                        |
| shimmering | 15    | 20         | 20    | -1  | 20  | 4     | stun                     |
| red        | 15    | 20         | 20    | -1  | 20  | -4    | fire                     |
| white      | 15    | 20         | 20    | -1  | 20  | -5    | cold                     |
| orange     | 15    | 20         | 20    | -1  | 20  | -5    | sleep                    |
| black      | 15    | 20         | 20    | -1  | 20  | -6    | disintegration           |
| blue       | 15    | 20         | 24    | -1  | 20  | -7    | shock                    |
| green      | 15    | 20         | 20    | -1  | 20  | -6    | poison/sick              |
| shadow     | 15    | 28         | 14    | -4  | 20  | -8    | sleep/poison/drain/death |
| yellow     | 15    | 20         | 20    | -1  | 20  | -7    | acid/stone               |

### Unique monster changes
* Unique monsters cannot be tamed
* Croesus can move other monsters out of his way (EvilHack)
* Ixoth can berserk and gets poison resistance. Speed raised to 20, AC raised from -1 to -4, stronger claw attacks.
* Lord Surtur can berserk, jump, and cast mage spells.
* Cyclops can berserk
* The Master Assassin is stronger, faster, sees invisible, resists sleep and poison, and gets one additional attack.
* Yeenoghu's magic missile attack has been buffed to 6d6 (EvilHack)
* Vlad gets stoning resistance.
* Vlad can cast spells
* Asmodeus can cast spells
* King Arthur now resists poison, fire, cold, shock, and sleep.
* Baalzebub is faster, gets an extra sting attack with a stronger main attack, can spawn flies (xNetHack).
* Master Kaen also gets sleep, fire, cold, and shock resistance
* The Grand Master also gets stoning and cold resistance.
* Dispater can walk through walls

**Medusa**
Inspired by EvilHack, Medusa receives a significant overall difficulty boost. Her level increases from 20 to 24, and her armor class improves dramatically, going from 2 AC to -8 AC. Her weapon attack is also enhanced, changing from 2d4 damage to 4d4. In addition to her traditional poisonous bite, she now has two poisonous snake bite attacks, increasing her offensive threat. She also gains a stoning bite, similar to the one featured in EvilHack. Finally, Medusa is now equipped with infravision.

**Wizard of Yendor**
* Rodney is bright magenta (EvilHack)
* Rodney will never steal the quest artifact of the current role (UnNetHack)
* Rodney gets a strong weapon and the ability to use it (EvilHack)
* Rodney is now telepathic
* Wizard harassment (after initially killing the Wizard of Yendor) has been increased by 20-25%

**The riders**
* Each rider gets an additional 100 HP (EvilHack)
* The identity of the Riders is hidden via farlook (UnNetHack)

#### Cthulhu:
NerfHack’s version of Cthulhu is a fusion of elements from his appearances in SLASH'EM and UnNetHack; he is a formidable endgame threat.

Stats:
* Difficulty 61, speed 18, base level 106, base AC -8, 95 MR, weight 3000.
* Size: gigantic
* Alignment: neutral
* Unique.
* Can not be exiled.
* Resists sleep, disintegration, poison, acid, petrification.
* Edibility: poisonous.
* Leaves no corpse.
* Is inexilable, breathless, regenerating, reviving, telepathic, displaces monsters, strong, follows you,
carnivorous, herbivorous.
* Can fly.
* Has a thick hide.
* Has infravision.
* Can see invisible.
* Is not a valid polymorph form.
* Does not respect Elbereth.
* Immune to magical scaring.
* Attacks:
  * 6d8 claw physical
  * 4d10 bite physical
  * 6d6 bearhug physical
  * 2d1 tentacle blood drain
  * gaze confuse
  * 4d6 spellcast clerical

Other attributes of Cthulhu:
* probing Cthulhu will not reveal his inventory.
* Cthulhu can displace other monsters, pass through iron bars, break boulders, and smash down doors in pursuit of the player, and he will relentlessly track and chase them.
* His drain intelligence attack has been replaced with a drain energy effect.
* Cthulhu is placed at the center of Moloch's Sanctum as a powerful guardian, although he does not carry the Amulet of Yendor.
* However, if the player acquires the Amulet, Cthulhu is allowed to return via wizard harassment.
* Cthulhu is covetous and will perform a **single warp** to the player upon first appearing. After that, he reverts to standard non-covetous movement.
* If he is killed and resurrects (which he will do quite quickly), he will regain the ability to warp again.


## MONSTER BEHAVIOR


### Monster item use
* Monsters can use figurines and magic flutes (EvilHack)
* Monsters can use cameras to blind you (SpliceHack)
* Monsters can read scrolls of remove curse and stinking cloud (EvilHack)
* Monsters can read scrolls of fire and flood
* Monsters can throw potions of oil and hallucination at you (xNetHack)
* Monsters can throw potions of polymorph at you (EvilHack)
* Non-lawful monsters can poison weapons with potions of sickness.
* Monsters can zap wands of cancellation and slow monster at the player (EvilHack)
* Monsters can zap wands of wonder at the player
* Hostile monsters wielding a digging tool can break boulders (EvilHack)
* Monsters can quaff potions of restore ability to un-cancel themselves (EvilHack)
* Monsters will quaff potions of reflection if you have a reflectable attack available.
* Monsters will quaff potions of milk to cure stunning and confusion
* Vampire monsters can quaff vampire blood to heal (SLASH'EM)
* When playing as a cartomancer, monsters can use monster summon cards and zappable cards against you.
* Some monsters will not throw weapons that are usable for melee.
* Monsters won't try to use wands of digging on hardfloor levels.
* Monster will attempt to wrest wands
* Monsters will pick up all kinds of potions (Crecelle)
* Monsters that collect items will grudge lizards for their corpses (from SporkHack).
* Monsters pick the most effective weapon of a given type, not just the first one found
* Monster movement is sped up: they can pick up items the same turn as moving and they can equip gear in 1 turn, allowing them to pursue you more effectively.
* monster dual-wielding: 2+ AT_WEAP monsters wield a secondary weapon (EvilHack)
* Monsters can use containers (EvilHack)
* Berserking and rabid monsters don't bother managing gear, looting, or eating - they pursue you.

### Monster accessory use
* Monsters can wear most rings and amulets.
* Your pets can also wear the same items, but you need to #loot them and manually give them the gear you want them to equip.
* The range of usable items has been expanded upon, notably all resistance rings, rings of teleportation and teleport control, amulets of flying and boots of levitation, stomping boots, amulets versus poison, amulets of ESP, and rings of polymorph

### Misc monster behavior changes
* Monsters with a negative AC get damage reduction from melee attacks (EvilHack)
* Monsters will switch to their melee attack intelligently (Sporkhack)
* When a monster spawns with a weapon, it wields it immediately (xNetHack)
* Intelligent monsters pick up keys and lock picks (UnNetHack)
* Magic-liking monsters will pick up magical tools (xNetHack)
* Covetous monsters will equip wearable items that they target (xNetHack)
* Monsters will use ranged combat in melee as a fallback option (Grunt)
* Monster stunning now works similarly to player stunning (xNetHack)
* Hallucination protects against skeleton bone rattling (xNetHack)
* Headless and breathless monsters don't cough in poison gas clouds
* Monster knockback is noisy
* Monsters may be woken up by eating carrots, reading dusty books, or rolling boulders
* Monsters that hatch in water drown unless amphibious or natural swimmers
* Monsters can use breath and spit attacks in melee range (FIQHack)
* Cancelled monsters can't explode (in death or as an attack)
* Displacing monsters (like the displacer beast) cannot displace you if helpless or trapped
* Cancelled displacers are incapable of displacement
* Force-fighting displaced monster can also result in displacement
* Peaceful monsters will not make themselves invisible by means of potions, wands, or other means
* Monsters can hide under other dungeon furniture (xNetHack)
* Player monsters can steal the amulet from the player (EvilHack) - however they will not attempt to sacrifice it
* Monsters carrying the Amulet of Yendor are incapable of teleportation
* Player monsters or any covetous monsters will grudge any monster that has the Amulet of Yendor (EvilHack)
* Thrown potions of hallucination that hit monsters confuse them (EvilHack)
* Potion of paralysis lasts 3-24 turns on monsters and has less effect when diluted (EvilHack)
* Monster groups sometimes spawn with a stronger leader or support caster (EvilHack/SpliceHack).
* Hostile monsters actively pursue and attack pets
* Divert accidental peaceful-anger penalties to luck instead of alignment (EvilHack)

### Flanking behavior
The flanking mechanic has been ported from *SpliceHack*, with several enhancements. In this system, any two monsters can flank a target, whether a player or another monster, by positioning themselves on opposite sides to "sandwich" their victim. However, monsters with the "outflanker" trait are more tactical than others and will actively seek out opportunities to flank the player. When flanking is successful, monsters gain a significant to-hit bonus, which now scales with the attacker's level, rather than applying a flat +4 AC penalty as in *SpliceHack*. Natural outflankers receive a much higher bonus than ordinary monsters, and flanking has been applied to a wide variety of monsters in *NerfHack*.

Be careful, flankers are clever and will aggressively try to maneuver you into bad situations. Some monsters can even jump into flanking position.

Players can also utilize flanking by coordinating with their pets. By positioning yourself and your pet on opposite sides of a monster, either of you will receive a flanking bonus during attacks. However, several conditions can prevent flanking. You cannot flank if you are hallucinating, afraid, confused, punished, fumbling, wounded, unaware, stunned, or standing on an Elbereth engraving. Additionally, you must be able to see the target. Similarly, monsters cannot flank if they are eating, sleeping, fleeing, confused, stunned, trapped, petrified, sick, diseased, stationary, or hiding.

Some player roles are considered natural flankers and receive greater bonuses when flanking. These include Knights, Monks, Rangers, Rogues, Samurai, and Valkyries.

### Berserking behavior
The berserking mechanic, ported from *EvilHack* with modifications, introduces a powerful and often dangerous behavior in certain monsters. Creatures with the ability to berserk can become a serious threat if underestimated. When such a monster drops below 50% of its maximum health, it has a high chance of entering berserk mode. Upon going berserk, the monster becomes fully hostile (even if peaceful) and regains a random amount of health, potentially restoring itself to full.

The act of going berserk is loud - nearby creatures are awakened by the monster’s furious scream. Whilst berserking, the monster becomes completely fearless, ignoring the effects of Elbereth and Scare Monster. Even creatures that are normally skittish or cautious will charge toward their target instead of retreating. A berserking monster will never flee, regardless of how low its health becomes, and it deals double damage rolls on successful hits.

Attempting to tame a berserking creature will only bring it out of berserk mode, leaving it still hostile - it will not pacify or domesticate the monster. Monsters capable of berserking include all dwarves, orcs, mumakil, giants, ogres, and several others.

### Traitorous monsters
* Ported from SLASH'EM
* Similar to SLASH'EM, many monster in NerfHack are traitorous and are capable of spontaneously turning against the player when tame.
  * Only intelligent monsters are capable of betrayal, mindless monsters will never betray.
  * Spell beings exist for a singular purpose, they will never betray you

* However, betrayals are much more likely to occur in NerfHack than in SLASH'EM:
  * In SLASH'EM: betrayal checks occur with a 1 in 850 chance during each of that pet's moves
  * In NerfHack betrayal checks occur with a 1 in 250 chance during each of that pet's moves, in Gehennom it drops to 1 in 50 chance.
  * In SLASH'EM: there is a further 1 in 3 roll that must be passed inside the betrayal check, in NerfHack this is bypassed (otherwise the chance of a betrayal is reduced to 1 in 850*3, or 2550 each turn).
  * In SLASH'EM, the betrayal check fails if the pet is further than 3 squares away, in NerfHack the potential traitor's proximity doesn't matter.
  * In NerfHack, a lot more variables go into the betrayal check. The monster observes the hero's ailments and HP and pounces if they seem weak.
  * Tame pets that are capable of berserking also have the chance to betray if they might berserk. If they fail the betray check though, they are prevented from berserking.
  * When you kill peaceful monsters in view of traitors, tame ones have a chance to betray.
  * There is a new monster spell "betrayal" that will encourage a pet to betray, even if it isn't normally traitorous.

Kinds of monsters that betray: All monsters that were traitorous in SLASH'EM can betray in NerfHack
* migos
* gargoyles, gremlins
* mind flayers, deep ones
* most imps
* all kobolds
* all orcs
* all gnolls
* forest centaur, mountain centaurs
* all chaotic dragons
* invisible stalkers
* minotaurs
* all lich class (L) monsters
* all ogres
* assassin bugs, shadow wolves, displacer beasts, blight sprites, byakhee, nightgaunts, shoggoths
* degenerators, disenchanters
* all trolls
* gorgon hulks
* all vampires
* Nazgul
* ghoul mages, gugs, ghoul queens
* most demons


### Monster elemental vulnerabilities
Ported from EvilHack: Monsters can be vulnerable to fire, cold, acid, and shock damage.

### Resistance and vulnerability to weapon damage types
Ported from dNetHack: Monsters can take extra or reduced damage from slashing damage, piercing damage, or blunt weapon damage types.

### Rabid monsters
This is a brand new mechanic, debuting in NerfHack!

* There is a fairly small probability of a monster spawning rabid, but bats and coyotes always have a 1 in 10 chance of spawning infected.
* Rabid is mostly limited to living mammals. Insects, birds, and lizards cannot contract it.
* Rabid monsters are prevented from spawning in special rooms like zoos or throne rooms.

**Effects of the rabid status on monsters:**
Monsters afflicted with the **rabid** status become significantly more dangerous and unpredictable. A rabid monster gains an extra bite attack, which is both poisonous - targeting the player's constitution - and capable of transmitting rabies. Once rabid, a monster no longer regenerates health and begins to grudge all nearby non-rabid creatures that are susceptible to the disease. Their behavior becomes erratic, with occasional unpredictable movements, and they are completely fearless - never fleeing and always moving toward their targets.

Rabid monsters also lose the ability to quaff potions and cannot be tamed or pacified. If a tame pet contracts rabies, it instantly loses its tameness and turns hostile. Whilst dangerous, rabid monsters do offer a small bonus in experience points when killed.

**Effect of being rabid on the player:**
* You cannot regenerate
* You become bloodthirsty in your attacks (similar to wielding Stormbringer).
* You occasionally move erratically as if confused.
* When the player is infected a timer starts from 100 + d(CON*2) turns.
  * At 40 turns, you develop a fear of water and cannot quaff potions.
  * At 10 turns, you become confused.
  * At 0 turns, you die.

**Curing rabid:**
* Generally the same guidelines for illness apply, but there are a couple important differences to know about.
* **You cannot use a unicorn horn to heal rabid status!**
* You can drink healing potions (before the fear of water sets in)
* You can cast cure illness
* You can pray (counts as a major trouble)
* You can eat a eucalyptus leaf or a clove of garlic
* You can eat the corpse of a dog (tinned or otherwise)
* You can be healed and cured by a nurse
* You can rub a non-cursed foulstone. When the foulstone is used this way, it autocurses and becomes a dangerous item again.
* Rabid monsters that poly can stop being rabid if the new form is immune - the same goes for the player.

### Diseased monsters
* Ported from EvilHack
* Similar to the Sickness status for the hero - Monsters can become infected with terminal illness, with a short countdown to death.
* Monsters can cure themselves if they have the means, and the player can use cure sickness or eucalyptus leaves to heal sick pets.
* Currently, the only weapon that causes disease is Grimtooth.

### Accurate behavior
* Ported from EvilHack, with modifications
* This property makes monsters more accurate in melee and with projectiles
* These monsters get a large to-hit bonus of +5 or more
* Players that are Elven or polymorphed into elves also enjoy a to-hit bonus that scales with your level.

### Jumping behavior
* Ported from EvilHack/SpliceHack
* Lets monsters jump at you from a few squares away, quickly bridging the gap between you
* They can also cross short barriers like water and lava and even jump over other monsters

### Tree walking
* Some monsters have the innate ability to walk/pass through trees and even hide in them.

### Withering attacks
Withering is a dangerous status effect introduced from *xNetHack* and *EvilHack*, now with additional modifications. When struck by a withering attack, the player gains the "Wither" status temporarily, causing them to lose 1 HP per turn. If the player is already affected and the new attack is sufficiently strong, it may also drain a portion of their maximum HP, making withering particularly insidious and difficult to ignore.

Fortunately, there are several ways to cure withering: quaffing holy water, consuming holy wafers, praying, or invoking the Staff of Aesculapius will all remove the effect. Items that provide extrinsic disintegration resistance - such as black dragon scales or bracers of integrity - also confer resistance to withering. All mummies possess withering attacks by default, and powerful clerics can cast the withering Blight spell at range.


## MONSTER SPELLCASTING


* Monsters can target and cast spells at other monsters (EvilHack).
* Spellcasters are able to misfire some spells and hit close squares or targets if you possess something like displacement or invisibility.
* Peaceful monsters won't cast make invisible on themselves.
* Monster spellcasters will prioritize healing when wounded (SporkHack)
* Self heal spells scale with monster level (Crecelle).
* Monster spellcasters can cast stone-to-flesh in response to getting stoned (EvilHack).
* Displacement, invisibility, and darkness offer limited protection from spellcasters.
* Telepathic spellcasters can usually bypass invisibility and displacement protections.
* Monster types or individual monsters can now have their own special list of spells to draw from (Crecelle)

### Countering monster spells
* There are a few ways to passively counter monster spells
  * The artifact silver spear Serenity
  * The Caveman's quest artifact: the Sceptre of Might
  * The Shield of Countering
* If you are using one of these items and are facing off with a spellcaster, each time the mcaster tries to conjure something you have an 80% chance of countering that spell. If you are successful, the counter will cost you 5-10 energy.
* The counterspell will fail if:
  * your item that counters is cursed
  * you have less than 10 energy
  * the distance between you and the caster is greater than 10 squares.

**psi bolt (level 0)**
* Can be cast from a short range (up to 4 squares away)
* Psi bolts also inflict bonus damage versus telepathic minds.
* Damage scales down the further away the caster is.

**fire blast (level 0)**
* This spell explodes a small fireball upon its target (and surrounding squares)
* Any flammable objects in open inventory are subject to being burned.
* Ranged, can be cast at the hero up to 13 squares away.
* Ported from EvilHack

**ice blast (level 0)**
* This spell explodes a small ice blast upon its target (and surrounding squares)
* Any non-protected objects in open inventory are subject to being frozen.
* Ranged, can be cast at the hero up to 13 squares away.
* Ported from EvilHack

**open wounds (level 0)**
* Now can be cast from a short range (up to 4 squares away)
* Damage scales down the further away the caster is.
* causes bloody tiles at higher damages.

**summon spheres (level 0)**
* The signature spell of the Orb Weaver (Q class).
* It allows the caster to summon a random group of exploding spheres like flaming spheres or shocking spheres. Because this is only available to orb weavers, it's designated as level 0 to guarantee castability. It can be cast at range but the caster must be able to see the hero. Unlike other summoning spells, this will center the summoned monsters around the caster and not the hero. It can also be cast from any range as long as the weaver can see the hero.
* All the summoned spheres count as spell beings.

**cure self (level 1)**
* Spellcasters can now cast this to cure illness, blindness, and rabid statuses.
* The amount healed scales with the caster's level (Crecelle)
* support casters can use this on members of their group

**darkness (level 1)**
* This spell casts an aura of darkness around the hero.
* Currently it only functions against the hero and other monsters cannot be targeted.
* It is available to cast from range as long as the hero is in sight.
* Ported from CrecelleHack.

**grease blast (level 1)**
* Blasts the target with a gush of grease (very similar to the effect of the grease trap)
* Limited to melee range

**blood rain (level 1)**
* Causes a shower of blood around the target, causing all affected tiles to become bloody.
* This spell is only utilized by vampiric casters and blood imps.
* Can be cast at range as long as the hero is in sight.

**haste self (level 2)**
* No major changes from Vanilla.
* support casters can use this on members of their group

**confusion (level 2)**
* Magic resistance no longer nullifies this spell, it cuts the duration in half.

**protection (level 2)**
* This is the monster version of the protection spell already available to the player.
* Provides a temporary magical shield that increases the monster's AC protection.
* Can be dissipated with a blast of cancellation.
* support casters can use this on members of their group
* Ported from EvilHack

**stunning force (level 3)**
* Magic resistance and Free Action no longer nullify this spell, possessing either cuts the duration by 25%.
* Stun resistance will prevent being stunned.

**sleepel (level 3)**
* Caster can put a target to sleep.
* If the player is targeted, having magic resistance or free action reduces the duration by 50%.
* Spell damage reduction reduces the duration by 25%.
* Ported from Crecelle

**disappear (level 4)**
* No major changes from Vanilla.

**hold/paralyze (level 4)**
* Magic resistance no longer nullifies this spell, it cuts the duration in half.
* mcasters can cast at other monsters

**vulnerability (level 4)**
* Caster can cause the player to become vulnerable to an element for a period of time, usually 250-500 turns.
* Vulnerability reduces the specific resistance to the element by 50% - with the potential for negative resistance converting into damage increase.
* This spell also drains 5-10% from the intrinsic resistance that is targeted.
* Magic resistance helps reduce the duration of the vulnerability by 50%, spell damage reduction reduces duration by 25%.
* All partial resistances are open to vulnerabilities now including sleep and disintegration.
* Ported from EvilHack

**levitate (level 4)**
* Makes the target levitate.
* If targeting the hero, it first causes the cursed potion of levitation effect (bumping your head on the ceiling), followed by a short period of levitation. Half spell damage reduces the levitation time. If targeting a monster, they just get permanent levitation. This spell is only cast by 'trickster' mages and only in melee range.
* Ported from Crecelle

**disguise (level 4)**
* Allows the caster to take on an alternative appearance - similar to a mimic. There is no timeout and the caster will retain the appearance until the hero uncovers it through hitting, searching, or other means.
* Protection from shapeshifters will also uncover the disguise and prevent it from being cast.
* Because this is fairly powerful (and annoying), it's limited to 'trickster' casters like gnomish wizards and kobold shamans, but also Dispater...
* Ported from Crecelle

**betray (level 5)**
* Causes a pet to betray you.
* This works very similarly to how traitorous monsters betray except that this spell also adds one point of abuse to the pet before checking for betrayal.
* New spell debuting in NerfHack

**blight (level 5)**
* Causes the target to start withering and can reduce their maximum hp; also causes a bit of hunger.
* Not effective on non-living monsters or targets that possess disintegration resistance.
* Duration scales with monster level.
* In xNetHack, this spell was reserved for 'dark speech' - a nasty group of curses that Asmodeus and Demogorgon can use. But it was extracted out and used as a new clerical spell which inflicts withering on the player.
* Can be cast from a short range (up to 4 squares away)
* Ported from xNetHack

**blind (level 6)**
* Caster can cause blindness in a target not through goop or intrinsic, but through physical scales covering the target's eyes, so certain methods that resist blinding don't work.
* Strangely, magic resistance doesn't have any effect on this spell (it didn't in Vanilla and doesn't in NerfHack).
* This remains a melee range spell.

**weaken/strength of newt (level 6)**
* Magic resistance no longer nullifies this spell, it cuts the duration by 50%.

**evil eye (level 7)**
* Caster can inflict a luck-draining gaze attack upon the target.
* If the target is not the hero, instead just confuses them.
* Can be cast at range with no maximum distance (ie: could be cast across the level if possible).
* Evil eye can only be cast by undead spellcasters.
* Because this is implemented as a gaze attack, the player can increase their protection by being invisible or displaced.
* Ported from dNetHack

**destroy armor (level 8)**
* Altered from Vanilla NetHack, modifications ported from EvilHack
* Having magic resistance is no longer full protection against this spell. Any piece of armor being worn can have its fixed status removed, and then can be deteriorated to the point that it's completely destroyed. Even armor that is normally erodeproof is affected. Having MR keeps the erosion level at one per cast, otherwise the erosion level is of one to three levels per cast. Blessed pieces of armor have a small chance of resisting. Armor-based quest artifacts are immune to this spell, as is crystal plate mail.

**mirror image (level 8)**
* Caster can summon a group of lookalike illusions to confuse you.
* Can be cast from range (max 13 squares away) as long as hero is in sight. Can only target the hero. Illusions are weak, ghostlike monsters once they are uncovered.
* Protection from shapechangers will also uncover their disguises and prevent casters from choosing this spell.
* Ported from Crecelle

**blood spear (level 8)**
* Caster can cause the blood on a tile to turn into a spear that attacks the target, dealing 10d10 if Vlad casts it, otherwise d(ml/2 + 4, 4) where ml is the monster's level.
* Used by vampiric casters. Can be cast at range.
* Ported from Crecelle

**summon insects (level 8)**
* Only priestly clerics can cast summon insects.

**hobble (level 9)**
* This clerical spell smashes the hero's legs with magical force and inflicts you with wounded legs for a brief period
* Hobble damage can be reduced by Antimagic or Half Spell Damage
* Can be cast from a short range (up to 4 squares away)
* New spell debuting in NerfHack

**curse items (level 10)**
* Caster curses a random assortment of the target's inventory.
* Certain items absorb curses: Magicbane, Load Brand both protect against this spell 95% of the time.
* Hexed items also protect (as long as they are uncursed).
* Allow high level spellcasters to also curse containers with curse items.

**reflection (level 10)**
* A spell that creates a shimmering globe around the caster, granting them reflection for several turns. Lasts longer for stronger monsters.
* Can be dissipated with a blast of cancellation.
* Ported from EvilHack
* support casters can use this on members of their group

**call undead (level 10)**
* Caster summons a small horde of undead.
* Only lich-class (L) monsters can cast this spell.
* Monsters summoned by this spell only count as spell beings.
* Ranged, can be cast at the hero from up to 7 squares away.
* Centers the summons around the caster, not the hero.
* Excessive chain-summon spawns are prevented; a caster can only summon a spellcaster of lower difficulty, so for example a demilich could summon a lich, but not another demilich. Ghoul mages and liches are both difficulty 14 so neither can summon the other.
* Weredemons (and other werefoo) are prevented from being summoned.
* Ported from SLASH'EM

**disenchant (level 10)**
* Allows caster to disenchant an item from hero's inventory. Must be cast in melee range.
* Available to clerical and trickster casters.
* 40% chance of zapping enchantment from current wielded weapon
* 45% chance from random piece of worn gear
* 15% chance of taking it from a random charged ring, charged tool, wand, or unequipped weapon or armor
* Ported from xNetHack
* Can also be cast monster-vs-monster

**lightning (level 11)**
* Now can be cast from a short range (up to 4 squares away)

**fire pillar (level 12)**
* Now can be cast from a short range (up to 4 squares away)
* Arch-viles can cast this spell from any distance.

**summon minion (level 12)**
* Allows the monster spellcaster to summon a type of minion based on its alignment.
* The minion is placed next to the player.
* Can be cast at a distance.
* Ported from EvilHack

**entomb (level 12)**
* Defensive spell that allows casters to drop a pile of boulders on and around the hero, blocking them from immediate movement. This potentially buys the caster some time to flee and heal.
* Used by high-level monsters when they are low on health or fleeing. It is primarily intended for escape.
* Limited to undead casters
* Ported from xNetHack

**geyser (level 13)**
* Now the geyser also rusts armor and instakills iron golems (EvilHack)
* Now can be cast from a short range (up to 4 squares away)
* Remove 1 in 5 useless check for Geyser so it should be selected more often.

**make pool (level 13)**
* melee-range spell that creates a moat at the hero's location, which the hero may immediately fall into, and the creation of the moat also removes any engravings on that square and subjects items on that square to water damage.
* The caster has a 19⁄20 chance of selecting another valid spell if the hero does not have the Amulet of Yendor, and will not cast the spell if they are not in a diggable space.
* The spell is affected by displacement and invisibility.
* Ported from SLASH'EM, with updates from slashem-up.

**aggravation (level 13)**
* The caster aggravates monsters on the level and causes the hero to gain intrinsic aggravate monster for a brief period. The duration is calculated in function.

**acid blast (level 14)**
* Explodes an acid blast on its target and the surrounding squares. The damage output is dependent on the level of the monster casting it. Has a chance of eroding any unprotected weapons or armor in open inventory.
* Ranged, can be cast at the hero up to 13 squares away.
* Ported from EvilHack

**blood bind (level 14)**
* This spell allows the caster to create explosions on any squares that have blood on them.
* Ported from CrecelleHack with some modifications: in NerfHack the range of effect is centered in a 8x8 circle around the caster and the caster won't create explosions that blast themselves.

**teleport (level 15)**
* High level spellcasters are able to warp to the hero to melee attack, or warp away when weak.
* Ported from Crecelle and xNetHack

**summon nasties (level 15)**
* No major changes

**flesh to stone (level 16)**
* When cast it can start the stoning process on the target.
* Can be cast from a short range (up to 4 squares away)
* New spell debuting in NerfHack

**clone wizard (level 18)**
* No major changes

**death touch (level 20)**
* Wielding an uncursed weapon with the Hexed property will protect you once.
* Immediately kills the player if they don't possess magic resistance or other form of resisting death.
* Ported some effects from EvilHack:
  * removed the caster's level check, "if (rn2(caster->m_lev) > 12)" so that it always goes through.
  * Even with MR, if you are not immune to death magic, you will take 12d12 damage and lose a portion of maximum HP. The 12d12 is subject to Half_spell_damage reduction.


## ROLE CHANGES


### Archeologist
* An Archeologist wielding a bullwhip will not fall through trap doors (SLASH'EM)
* Archeologists always get a bonus when searching (FIQHack)
* Archeologists start out knowing dwarvish mattocks and archeologists of any race can use them without penalty.
* Archeologists always get a bonus identify when reading scrolls of identify.
* Archeologists start with an extra spellbook (SLASH'EM).
* Archeologists sometimes crack their whip at animals, scaring them.
* Archeologists count as *primary spellcasters*, so they benefit from memory bonuses when casting spells.
* Archeologists can highly enchant fedoras (xNetHack)
* Arcs are now restricted in axe and spear but can become skilled in shields.
* Arcs can reach Master skill in pick-axe

**Archeologists vs snakes!**
* Archeologists get a -1 to-hit penalty when fighting snakes (any S class monsters).
* Snakes get a +1 to-hit bonus on archeologists
* All snakes have the potential to paralyze archeologists in fear when they successfully connect a hit. Free action only protects the hero 75% of the time vs these paralyzing attacks.
* Archeologists are not afraid of snakes when hallucinating.

### Barbarian
* Barbarians start with a little more food (SLASH'EM).
* Barbs can now become skilled in riding and shields.
* Barbs can reach Master skill in axe
* Barbarians always start with the plain axe and a mid-tier weapon.
* Barbarians get a **blood rage bonus** for low health.
  * Only occurs when barbarians reach level 4 and higher.
  * When under 40% of their max HP, they get a damage bonus that scales with their level.
  * When under 25%, this bonus is doubled.
  * Each rage attack uses up 1d5 energy, so at least 3 energy is required to trigger a rage attack.

### Cavemen
* Cavemen have 2 guaranteed sacrifice gifts: Skullcrusher and David's Sling. After these two artifacts have been gifted, no further artifacts can be yielded from #offer.
* Instead of the standard crowning gift, cavemen always receive Giantslayer (EvilHack)
* Cavemen start with a random set of dragon scales.
* Unlike other roles, cavemen do not start out knowing scrolls of identify.
* When reading scrolls of identify, cavemen will never be able to identify all items, instead being limited to a single identify per scroll.
* Cavemen have also been gifted with more skills in rudimentary tools like rocks and flint:
  * They start the game with more flint in place of standard rocks (xNetHack)
  * Cavemen can lash flint to arrows, making them do slightly more damage (Sporkhack/THEM). When arrows are flinted, their enchantment is also revealed.
* Cavemen can get an alignment boost via cannibalism (Sporkhack)
* Cavemen's gods sometimes don't respond to prayer. If you have abused your alignment, there is a 10% chance of being ignored (Sporkhack/SlashTHEM/EvilHack)
* Cavemen start with really low intelligence. As a result, they are incapable of reading legible items or engraving Elbereth until reaching 6 INT.
* Cavemen are now restricted in pointy weapon skills like dagger and polearms. They also lose attack and matter skills, but can gain basic in riding and shields.
* Cavemen start with a nightvision radius of 2 (SLASH'EM)

**Caveman quest updates:**
* The caveman quest has been updated and filled with more jungle type monsters: tigers, pythons, and the like. There is also a lot of water added and ; monsters to occupy it (SlashTHEM)
* The Chromatic Dragon has some buffs: she can berserk, has faster speed, lower AC, and stronger claw attacks.
* Quest narration and dialogue is more caveman-like (xNetHack/Fourk)

**Illiterate bonuses:**
* Cavemen can increase their max-HP at each level-up if they remain illiterate (Sporkhack/THEM)
* Updated XP boosts are from EvilHack:
  * Experience levels 1-2: 2-4 HP boost per level.
  * Experience levels 3-9: 3-6 hp boost per level.
  * Experience levels 10-17: 3-8 hp boost per level.
  * Experience levels 18 and up: 5-12 hp boost per level.

**Spellcasting nerfs**
* They cannot receive spells from their deity (EvilHack)
* They have an 80% chance of failing to read any spellbook
* Their special spell has been removed (EvilHack)

### Healer
* Added L's Wounds patch: healers can see damage on monsters
* Healers start with a +1 scalpel and 2 eucalyptus leaves.
* Healers get a bonus when applying unicorn horns
* Healers can use an uncursed unicorn horn as if it is blessed.
* Healers start out knowing potions of restore ability, sickness, paralysis, blood, and sleeping.
* Healers can reach Master skill in unicorn horns

### Knight
* Knights start with a +0 studded leather armor instead of a +1 ring mail (K-Mod)
* The knight's quest has been infested with a swarm of merfolk
* Knights are now restricted in daggers, knives, clubs, tridents, axes, and pick-axes. However, now they can reach expert in broadsword, polearms, spear, and shield.
* Knights can reach Master skill in long sword

### Monk
* Monks can start with the spell of sleep (in addition to confuse monster, light, and protection).
* Monk starting spell competency depends on the spellbook.
* Monks start with a potion of reflection.
* Monks gain acid resistance at level 19 (dNetHack).
* Dramatically increased the monk's body armor penalty (EvilHack)
* Stop giving "You feel guilty message" eventually after breaking vegetarian conduct enough times (xNetHack)
* Monks get a **fully charged magic marker** as a crowning gift.
* Martial arts users are immune to leg damage from bad kicks (xNetHack).
* Whilst wearing the gauntlets of force, monks can break boulders and iron bars whilst bare-handed.
* Monks that have reached grand master in martial arts and achieved at least level 21 start getting a 1 in 20 chance for critical hits when fighting bare-handed. On critical hits, you inflict double damage.
* Monks are now restricted in divination, escape, and matter spell schools. They are also restricted in crossbow, but can reach expert in quarterstaff and skilled in enchantment spells.

### Priest
* Priests start with a +2 small shield (SLASH'EM)
* Priests reduce the chance of zombie revival by 50% (Dynahack); when a zombie is destroyed for good, you get a special message
* Priests start with more garlic and wolfsbane (similar to the undead slayer in SLASH'EM)
* Vampire priests don't start with any food items. Instead they get potions of vampire blood.
* Priests are restricted in lances and shuriken, but can now reach basic in riding and shields. Flail and trident skills were also lowered to skilled and basic, respectively.
* Priests can reach Master skill in mace

### Rogue
* Rogues also get a multishot bonus for knives.
* Rogues start with a +2 stiletto instead of a short sword
* Rogues start with a stack of knives instead of daggers
* Rogues start with a leather jacket instead of armor.
* Rogues start with scrolls of gold detection and teleport (SLASH'EM).
* Rogues are now restricted in all big sword skills, as well as mace, morning star, spear, and polearms. Their skills in club, crossbow, and divination were lowered to basic.
* Rogues can reach Master skill in knife

**Return of Backstab Damage:**
* Rogues can inflict **backstab damage** for the first thrown weapon. In 3.4.3 this was a very powerful mechanic that was nerfed in 3.6. We are bringing it back in a limited form as a callback to 3.4.3 but also because it strongly fits the theme of the role.
* Rogues get bonus backstab damage when using stilettos in melee

**Rogue counterattacks:**
* Whilst wielding a knife or dagger, a rogue has a chance of counter-attacking an opponent when hit.
* There are many restrictions:
  * The incoming attack must be a weapon, bite, claw, or kick attack.
  * You cannot be polymorphed
  * You cannot be wearing any heavy metallic armor (excludes mithril) or wielding a bulky shield.
  * You cannot be weak (or worse from hunger) and you cannot be encumbered.
  * You cannot be fumbling or unaware.
  * You must be able to see the monster.
* The chance of countering goes up with your skill in the wielded weapon.
* Each counterattack uses up 10 energy (at least 10 energy required to execute)

### Ranger
* Rangers get extended range for seeing object's appearance (this lets them see potions and gems from much further away)
* Rangers get auto-id for launchers when they reach XP level 7
* Rangers get auto-id for ammo enchantment when they reach XP level 10 (xNetHack)
* Rangers are not stunned from using portals (they are used to quick travel)
* Rangers start the game with 2 beartraps (xNetHack).
* Rangers are now restricted or basic in most of the melee weapon skills they previously possessed. These changes put more weight on their skills with bows and crossbows. They can now reach skilled in shield.
* Rangers can reach Master skill in bow
* Make Rangers much better at finding pits and spiked pits (xnh)

### Samurai
* Samurai start with +3 wakizashi (Dynahack)
* Samurai get to-hit and damage bonuses for two-weaponing a katana with a wakizashi.
* The samurai quest was updated to have more water and monsters (jellyfish, more ninjas, some nagas).
* Being satiated abuses wisdom for Samurai.
* Samurai are also are immune to leg damage from bad kicks (xNetHack).
* Samurai can now reach expert in spear.
* Samurai can reach Master skill in two-handed sword

### Tourist
* Tourists get automatic type identification for shop items (UnNetHack). This means that all items for sale are identified for you in shops. You can instantly identify anything by selling it.
* Tourists start with more darts (UnNetHack)
* Tourists gain experience by discovering new special rooms.
* Tourists start with a pair of walking shoes.
* Tourists have had the majority of their skill maxes reduced to basic, with the exception of enchantment spells which their special spell uses.
* Tourists can reach Master skill in darts

### Valkyrie
* Valkyries can pacify and tame winter wolves/cubs with food as if they were domestic animals.
* More fire traps appear on their quest
* Valks can reach master in shield skill
* Valks can reach Master skill in hammer

### Wizard
* Wizards start with a cloak of protection instead of magic resistance.
* Wizards never receive magic missile in their starting inventory.
* Wizards can start with a spellbook of fire bolt instead of force bolt.
* Wizards are able to sense magic fountains.
* Wizards can always sense how many charges are left in wands.
* The Dark One gets a cloak of magic resistances and staff (xNetHack)
* Most of the wizard's combat based skills have been restricted and removed (EvilHack)
* Wizards start with less magical accessories and an additional spellbook.
* Wizards can reach Master skill in quarterstaff


## NEW ROLES


### Undead Slayer

The **Undead Slayer** has been implemented as a new role, distinct from the Priest. This rework includes a fresh quest storyline in which the player must reclaim *The Argent Cross* from *The First Evil*. Custom quest levels include the Desecrated Monastery, Haunted Catacombs, and The Abyssal Vaults. Unlike the divine spellcasting Priest, the Undead Slayer is a dedicated warrior whose sole mission is to purge the undead.

This version of the Undead Slayer blends old and new mechanics, making it a more challenging role early on but highly rewarding in the endgame. Undead Slayers begin with **drain resistance, sickness resistance, and warning against undead.** They start with **slow movement (speed 10)** as they did in SLASH'EM, but they gain **to-hit and damage bonuses against undead and demons**. One unique trait is their ability to **completely obliterate zombies, preventing them from leaving corpses.** However, they receive significant alignment and Luck penalties for consuming wraith corpses. Their special spell is *protection*.

**Intrinsics:**

| XL  | Intrinsic              |
| --- | ---------------------- |
| 1   | Slow (speed 10)        |
| 1   | Drain resistance       |
| 1   | Sickness resistance    |
| 1   | Warning against undead |
| 1   | Stealth                |
| 10  | Speed                  |
| 15  | Poison resistance      |

Undead Slayers also start with a **revenant pup**, a new undead canine with numerous resistances and the ability to phase through walls. These creatures do not eat, so they are tamed via `#chat` rather than food. Chatting with your pet also increases apport. If you take care of your pup it will grow into the powerful revenant hound, a beast comparable in strength to the hell hound.

However, there are a couple differences from SLASH'EM. They get fast speed and poison resistance at much later levels. They do not receive any special techniques and unlike Priests and Knights, they **cannot turn undead.** Additionally, they do not start with a silver pistol or silver bullets, but a new fourth starting kit has been substituted which features a silver short sword and leather cloak. Whilst they can reach **expert** in daggers, they are still **weak at multi-throwing.**

The **new quest artifact** is *The Argent Cross*, an **artifact amulet of reflection** that grants **spell damage reduction, disintegration resistance, and withering resistance** when worn. It also acts as an **artifact light source**. When blessed, it will periodically activate the `#turn undead` effect without requiring the player to stand still. However, if cursed, if your god is angry, or if you are non-chaotic and polymorphed into an evil form, it will instead **aggravate monsters.** The cross follows the same activation timer as clairvoyance, triggering every **15-45 turns** after the last activation.

The **new quest nemesis** is *The First Evil*, who guards *The Argent Cross* and the *Bell of Opening*. This is a **high-level evil shade** with an arsenal of powerful abilities. It can cast mage spells and possesses **nasty touch attacks** that can paralyze, slow, freeze, and shock its foes. Additionally, it is highly resistant to various forms of damage, including cold, disintegration, stoning, sleep, poison, acid, and electricity.

**Other notes:**
* The HP growth curve for undead slayers has been buffed from SLASH'EM to make them more durable.
* Slayers can reach Master skill in dagger
* Undead slayers take alignment penalties for drinking vampire blood and eating wraith corpses.
* **Undead slayers' max skills vary dynamically based on their starting kits.**
  * Crossbow, spear, long sword, short sword, and whip all default to a max of basic
  * Starting with the crossbow unlocks expert skill in crossbow (the crossbow is also +3 and you start with more bolts)
  * Starting with the silver short sword unlocks expert skill in short sword and skilled for long sword
  * Starting with the whip unlocks expert skill in whip and master skill in martial arts
  * Starting with the silver spear unlocks expert skill in spear

### Cartomancer
* The cartomancer is a unique role ported over from SpliceHack. Cartomancers are spellcasters with a focus on using cards and summoning temporary minions to do their bidding. Many parts of the role are inspired by or pay homage to various trading card games. The cartomancer has undergone some dramatic transformations from its original implementation in SpliceHack, becoming a more focused and surprising role to play.

**Starting inventory:**
* graphic tee
* 40 blessed +2 razor cards
* ~4 meat sticks
* ~4 candy bars
* 7 blessed summon raven cards
* 1 random rulebook
* 4 potions of phasing
* sack
* a playing card deck

**Intrinsics:**

| XL  | Intrinsic                             |
| --- | ------------------------------------- |
| 1   | Slow (speed 10)                       |
| 1   | Searching                             |
| 7   | Warning                               |
| 7   | Can ascertain razor card enchantments |
| 15  | Fast                                  |
| 15  | Can ascertain all scroll/card BUC     |

**Quest artifact**
The **Holographic Void Lily** is a quest artifact that functions as a chaotic credit card. When carried, it grants energy regeneration, spell damage reduction and reflection. Additionally, it can be invoked to provide a temporary boost in card drops, during which the Void Lily will shine brightly for 25-50 turns. This invocation effect replaces the original #invoke ability from SpliceHack, where it previously summoned a large group of random monsters.

**Cartomancer rarity descriptions**
Scrolls are also labeled according to their rarity. In the original SpliceHack implementation, this reflected the price. So a $100 card would be "uncommon", a $200 card would be rare, and so on. With the nerfing of price identification, this system has been revised so that the actual probability of cards is reflected.

**Card abuse penalties**
* Cartomancers receive severe alignment penalties for forging or defacing cards.
  - writing cards: -20 alignment, -5 luck
  - cloning cards: -20 alignment, -5 luck
  - polymorphing cards: -10 alignment, -2 luck

**Play mechanics**
* Cards (scrolls) only weigh 1 for cartomancers.
* Rulebooks (spellbooks) only weigh 5 for cartomancers.
* The camera is played as a holographic card for cartomancers, it doesn't break when thrown.
* When applying a deck of cards, cartomancers will always be able to use them as if they
  were blessed.
  - For playing card decks, this enables you to easily evaluate your current luck.
* Cartomancers don't break illiterate conduct when playing cards.

**No perma-pets**

Cartomancers do not receive a starting pet and are unable to tame monsters in the usual way. When food is thrown at domestic animals, it only pacifies them rather than taming them. Any figurines that generate are automatically converted into summon cards, and the rulebook of create familiar also produces summon cards instead of familiars. All standard methods of creating permanent pets have been nullified for Cartomancers. On the Astral Plane, they receive an archon card in place of a guardian angel. When reading a confused scroll of cloning, they will simply receive a summon card instead of a possible tame pet.

**Melee combat nerfs**
* Cartomancers are awful melee fighters - they prefer ranged weapons or fighting behind their summoned help. They receive severe penalties for melee combat.
* Flat -5 to-hit penalty for all melee combat.
* If wearing armor, they receive an additional -20 to-hit penalty
* If wearing a shield, they receive an additional -10 to-hit penalty
* If attacking with a wielded weapon, they receive an additional -10 to-hit penalty.
* Cartomancers get messages (similar to monks) for cumbersome armor and shields.

**Card drops**

When playing as a cartomancer, there is a chance that a monster will leave a card instead of a corpse upon death. Initially, this chance is 50%, but as you level up and progress deeper into the dungeon, the chance gradually decreases. When a monster dies and is eligible for a drop, one of three outcomes can occur: **razor cards** (with any BUC status or enchantment) may be dropped, a **zap card** may appear, or a **summon card** might be left behind. Summon drops are the most complex, as they can vary depending on RNG. The drop could be the same card as the monster that was killed, a higher difficulty monster, a random monster, or a sphere. If the monster is low level (below 3), it often doesn't leave any card. However, nasty monsters always drop their own summon cards.

* Some monsters are restricted from dropping cards:
  * spell beings
  * cancelled monsters
  * phoenixes (they always leave an egg)
  * cloned monsters (gremlins, blue jellies, etc.)
  * Keystone Kops
* Cartomancers don't get card drops whilst in polymorphed form.

**Spell beings**

Spell beings originally came from SLASH'EM. Whenever the flame sphere or freeze sphere spells were cast, they would summon a temporary sphere, which counted as a spell being. These beings are tame and act like pets, but they have a limited lifespan. (In SLASH'EM, there was no lifespan unless you left them on a level, causing them to become untame.) Here, when the cartomancer plays a summon card, it will summon a spell being with a predetermined lifespan that will fight aggressively for you, ignoring any hesitation a regular pet might exhibit and never stopping to eat or hide. If you receive credit for killing a spell being, they only grant 1 XP. Spell beings never leave corpses and spawn with no inventory. Spell-beings also don't count toward vanquished or special logged monsters.

Spell beings have a "sparkling" description in farlook, so you can distinguish them from permanent monsters.

As you gain levels your innate casting skill improves, your spell beings will survive for longer periods of time.

**Summon cards**

For cartomancers, **cards of create monster** are twice as common as for other roles, and when these cards spawn, they are keyed to a specific summon monster card. Cartomancers begin the game with seven **summon raven cards** and have opportunities to expand their collection as they slay monsters. Whilst low-level monsters rarely drop their own summon cards, there is always a small chance that any death drop will leave a higher-level monster card. As the cartomancer's level increases, so does the strength of these rare drops.

The price of summon cards scales according to the difficulty of the monster they summon. In addition to reading summon cards, **cartomancers can also throw them to activate the effect**, which allows them to summon monsters at a distance, directly next to a threat.

**Monsters can also read summon cards**, so it’s important for cartomancers to collect them before they are used against them. **Cursed summon cards will always create hostile monsters**.

Activating summon cards **costs 5 energy per card**. If the cartomancer lacks enough energy, the card will have no effect and will not be consumed. Unique monsters can drop summon cards, with a few exceptions, such as the Wizard of Yendor and the Riders, due to their ability to revive.

Whilst sacrificing corpses at an altar, cartomancers can sometimes receive cards as gifts after an artifact has been bestowed.

**Explosive summon cards**

Summon "sphere" cards are special because they **instantly explode when thrown at a monster**. However, if cursed, they will not explode and instead summon a hostile sphere, which includes gas spores and volatile mushrooms. Exploding sphere monster cards are more likely to drop for cartomancers, providing them with useful ranged explosive options.

**Razor cards**

In NerfHack, razor cards have been properly implemented as their own weapon type, using the shuriken skill, unlike in *SpliceHack*, where they were simply shuriken with a different label. Razor cards deal 1d6 damage to both small and large creatures, have a +2 to-hit bonus, and weigh 1. Cartomancers can multishot with shuriken-skill projectiles, such as shuriken and razor cards, and they gain multishot bonuses up to expert skill.

Razor cards will occasionally appear as part of a cartomancer’s regular death drops, sometimes replacing summon or zap cards. These follow the same rules as stacked weapons, so they may appear in stacks of 6-11 and could be blessed, cursed, unblessed, or possibly even poisoned.

If a player comes across a deck of cards that they have no use for, they can #tip the deck to empty it, yielding a potentially large stack of razor cards.

**Zappable cards**

Zap cards, which function as **one-use wands**, can drop when cartomancers kill monsters. These cards have a 0% generation chance for other roles, meaning only cartomancers will encounter them. Cursed zap cards have a chance to backfire like wands, but they cannot explode. Playing zap cards requires 5 energy per card.

Cartomancers will never see wands generate. Anytime a wand would spawn it is instead replaced with its equivalent zap card. It's important to note that monsters can and will use both zap and summon cards against the player, so it's crucial to collect them as soon as they drop.

**Spellcasting overhaul**

Cartomancers do not learn spells in the traditional way, meaning they cannot acquire spells from starting books, reading spellbooks, or receiving gifts from gods. Instead, they cast spells instantaneously by reading rulebooks. These rulebooks generate with 4-5 charges, and each reading consumes one charge. Once all charges are used, the rulebook is consumed and disappears.

Cartomancers begin the game knowing the identities of all rulebooks, as the title and purpose of a rulebook are typically clear from the cover. They always cast spells at expert level, ensuring high proficiency. Whilst rulebooks can still be written using magic markers without penalties (unlike when forging cards), they cannot be recharged with scrolls of charging. Additionally, cartomancers are fortunate enough to know braille, allowing them to invoke their rulebooks even whilst blind.

**Cartomancers get special bonuses for wielding crystal balls:**
* Whilst wielding a crystal ball, a cartomancer will enjoy **maximum charisma, telepathy, see invisible, and clairvoyance.**


## PLAYER RACE CHANGES


* Removed infravision from dwarves, elves, gnomes, and orcs.

### Elves
* Elves start with see invisible at level 1
* Elves can always squeeze diagonally between two trees (xNetHack)
* Elves start the game with the ability to pass through trees
* Elves can always reach Basic in enchantment spells (xNetHack)
* Elves throw up when eating meat (Crecelle)

### Dwarves
* Dwarves can always reach Skilled in pick-axe (xNetHack)

### Gnomes
* Gnomes are good at slipping free from grabbing attacks
* Gnomes start with an interesting tool
* Gnomes get stealth at level 5 (SLASH'EM)
* Gnomes get a damage bonus for shooting crossbows
* Gnomes can always reach Skilled in crossbow and Basic in club (xNetHack)

### Orcs
* Orcs cannot successfully engrave Elbereth.
* Orcs start with a sickness potion (Sporkhack)
* Orcs get an alignment boost for cannibalism (dNetHack)
* Orcs can always reach Skilled in saber (xNetHack)
* Orcs start with -20 alignment
* Orcs don't get penalties for attacking and murdering peacefuls, even quest guardians or leaders.
* Orcs get alignment bonuses for attacking peaceful, helpless, or fleeing monsters.
* Shopkeepers generate peaceful, but watch guards and watch captains will immediately pursue orcs on sight.
* Cross-aligned priests will generate hostile - however, priests of Moloch will generate peaceful.
* Orcs and watch guards have a grudge vs each other.
* Orcs love drinking blood and get an alignment bonus and exercise constitution when doing so.
* Orcs cannot pacify or tame most monsters because they are just too evil. However, they do have the ability to pacify and tame a few monsters with food: goblins, wargs, trolls, ogres, and barghests.
* The range of monsters they can tame magically is reduced to these monster types: o O T D U (along with the previously named monsters they can befriend with food)
* Orcs get significant STR, CON, and DEX bonuses for leveling up.
* Orcs can saddle and ride wargs
* Orcs always start with a warg pup
* Orcs never get help on Astral and always receive an angry pack of Angels.
* Orcs also hate items made of mithril


## NEW RACES


### Dhampir
Vampires have a rich history in NetHack, first appearing in SLASH'EM and later spreading to many other variants, with each variant implementing them slightly differently. However, in NerfHack, vampires take a U-turn from the traditional design due to their overwhelming power. As a playable race, they allowed players to bypass too many core mechanics and obstacles, including newly introduced features.

For instance, their **immunity to withering** made mummies and priests trivial threats, whilst **immunity to rabid attacks** negated an entirely new mechanic. **Poison resistance** let them fight deadly monsters like orcs or **team a** without fear, and **sleep resistance** nullified sleep rays. Beyond resistances, their innate abilities made the game even easier: their hardcoded vampire-bat and fog cloud polyforms rendered polytraps meaningless, **flying** allowed them to **bypass ground traps, water, and tough terrain**, and **regeneration** gave them an immense edge in combat. All of these factors stripped away much of the game's intended challenge, particularly in the early stages.

**A Balanced Alternative: The Dhampir**

To address these issues, a **lesser type of vampire - the dhampir (or demi-vampire) - was introduced**. This new race retains some of the vampire's strengths but is far more balanced, fitting alongside other vanilla races. The Dhampir preserves the appeal of playing as a vampire whilst maintaining the integrity of NerfHack's mechanics and difficulty.

Dhampirs start with **resistance to draining and death magic**, and being **breathless**, they are immune to gas, spores, choking, and drowning. They also resist **lycanthropy** and possess **infravision**. However, **all partial intrinsics are capped at 50%**, even when granted through crowning, ensuring they rely more on extrinsic protections. Dhampir have a further **restriction on fire resistance** and are incapable of gaining any protection in that area.

Dhampirs **excel at climbing** and can easily escape pits. Their standout ability is a **1d6 draining bite**, which **heals HP** when feeding on blood - replacing the vampire's intrinsic regeneration. As an added bonus, they can **absorb partial intrinsics from drained monsters**, such as **cold and sleep resistance**.

To prevent frustrating deaths, **bite attacks are automatically prevented** when facing dangerous foes such as **cockatrices, Medusa, or green slimes** - even if the player is only polymorphed into a vampire. However, **stunned, confused, or hallucinating dhampirs and vampires will bite indiscriminately**, making careful gameplay crucial when impaired.

The corpse draining mechanic from SLASH'EM was never ported due to bugs in the nutrition code and tedious corpse draining mechanics. Instead, SpliceHack's approach was adopted, where **life blood feeding in combat now provides more nutrition**. The tradeoff is that **Dhampirs can no longer eat nor gain benefits from eating corpses**.

 Dhampir no longer die from hunger (from EvilHack) - they have the following effects as their hunger status advances (these conditions are temporary whilst the hunger status is active and are restored when the hunger status is cured/alleviated):
    * From hungry to weak: you lose 1 point from ALL attributes.
    * From weak to frail: you lose 5 points from ALL attributes and become deaf.
    * From frail to starving: all attributes are set to 3 and you also become blind.

#### NerfHack introduces smarter feeding to regulate vampire bite mechanics:
- Low-level dhampir can only use either a bite attack or weapon attack, but not both in the same round.
- If the vampire is hungry (or close to hungry), they will always bite and attempt to feed first.
- Otherwise, there is a 50/50 chance of either biting or attacking with a weapon.
- The ability to combine a bite with a weapon attack is locked until Level 10.
- After **Level 9**, dhampir can perform **both biting and weapon attacks in the same round**.
- If a player **wants to avoid biting**, they can forcefight using `"F"` to **only use their weapon attack**.
- Dhampir also feed more efficiently when their victims are confused, incapacitated, or trapped.

#### Dhampir's resistances and abilities

| XL  | Intrinsic                   |
| --- | --------------------------- |
| 1   | Infravision                 |
| 1   | Warning vs humans and elves |
| 1   | Breathless                  |
| 1   | Drain resistance            |
| 1   | Immune to death magic       |
| 1   | Immune to lycanthropy       |
| 12  | Hunger                      |
| 12  | Regeneration                |
| 24  | Flying                      |

Although dhampir have drain level resistance, they remain **vulnerable to blood-draining bite attacks** from other vampirics and blood-suckers. Intrinsic drain resistance does not protect against these attacks, but an extrinsic source will.

In terms of food, **most rations and fruit juice potions are replaced with blood potions** when playing as a dhampir. This avoids creating junk items throughout the game and helps the player survive longer. Some vampires receive an opera cloak, though it is rarer than in SLASH'EM, and **wearing an opera cloak grants a charisma bonus**, as in UnNetHack. Potions of blood and vampire blood offer vampires a drinkable food source. Dhampir can use any racial items, except for gnomish items, which are too small for them.

**Silver weapons also generate more frequently** when playing as a dhampir. After difficulty level 8 kicks in, 10% of all eligible weapons will be converted to silver. Dhampir can handle silver items, but if they come into direct contact (ie: wielding a silver saber without gloves), they will take some damage and be unable to regenerate further HP.


### Grung
**Grung** are a nasty little race of frog-like people known for their toxic skin, sharp teeth, vibrant colors, and lack of long tongues. The featured race here is the green grung. Their **skin naturally secretes poison**, giving them a **passive poison attack**. In combat, they can **poison enemies when striking barehanded**. Although their poison is only about half as strong as a standard poisoned weapon attack, it is still very efficient at wiping out enemies that don't resist poison. Additionally, they can **poison their weapons using their toxic skin** to coat them with venom for extra lethality.

Grung possess several natural abilities. They have **resistance to poison** and are adept at **searching**. Their natural agility allows them to **swim effortlessly**, and as they gain experience, they achieve **jumping ability (XP5)** and **speed (XP7)**.

#### Grung's resistances and abilities

| XL  | Intrinsic         |
| --- | ----------------- |
| 1   | Poison resistance |
| 1   | Swimming          |
| 5   | Jumping           |
| 13  | Searching         |

One of the grung's **biggest concerns is hydration**.

#### Grung Hydration Mechanics

- **Hydration Requirement:** Grung **must stay hydrated to survive**
- **Hydration Timer:** Starts at **3000** and counts down every turn
- **Penalties for Low Hydration:**
  - Below **1000** → **Speed and combat penalties**
  - At **0** → **Instant death**
- **Dehydration Accelerators:**
  - **Fire, heat, and dry environments** speed up dehydration
  - **Fire resistance** can **reduce some effects**
- **Methods of Rehydration:**
  - **Drinking water** (+100-199)
  - **Sitting in water sources** (+100-199)
  - **Being splashed with water** (+100-199)
  - **Submerging in water** restores **1000 hydration per turn**
- **Scrolls of Flood:**
  - Can be used for **rapid hydration**  (+4500-6000)
  - If **read whilst confused**, they cause **severe dehydration** instead
- **Environmental Effects:**
  - Faster dehydration in Gehennom & the Plane of Fire
  - Easy rehydration in the Plane of Water
- **Prayer for Hydration:**
  - If hydration drops to **250 or below**, it counts as **major trouble**
  - **Praying** may grant **1000 hydration**, if your **god blesses you**

Grung have several strengths in combat. Their **DEX-based armor class (AC) bonus** is **slightly increased** compared to other races. They also gain a **to-hit bonus against kamadan** and can **always reach skilled proficiency in darts**. However, they also have notable weaknesses. They **cannot wear boots** and strongly **dislike heavy or bulky armor**, though they are comfortable wearing racial armor as long as it isn’t cumbersome - mithril is a good choice. Additionally, their **passive poison ability does not function** whilst wearing **bulky armor**. Grung are particularly vulnerable to **dust vortices**, which accelerate their dehydration process.

Beyond the green grung, there are other members of the grung clan, each with slightly different abilities and strengths. Grung come in **six colors**:
- **Green grung** possess passive and active poison that drains strength.
- **Blue grung** drain constitution with their poison and can cast mage spells.
- **Purple grung** have a stunning poison and can cast clerical spells.
- **Red grung** poison their enemies by draining dexterity and wield a 2d6 weapon attack.
- **Orange grung** cause hallucinations with their poison and have a 1d6 weapon attack.
- **Gold grung** induce sleep with their poison and wield a powerful 2d6 weapon attack.


## SPELLCASTING CHANGES


Most of these changes are to strengthen natural spellcasters abilities and to dull roles
that don't specialize (like fighters). Non-specialists can still attempt to utilize spells
but they will have to work harder to maintain their spells. Cavemen will have a very
difficult time with spellcasting.

### Spell memory
* The base memory retention for spells is now 20000 turns for primary spellcasters and 10000 for all other roles.
* When reading or re-reading a spellbook, you will bring the retention back up to your role's KEEN value.
* Reading restricted spellbooks only grants **half** of your role's KEEN value.
* Primary spellcasters (healers, priests, monks, wizards, archeologists) get a memory boost of 500 turns when they cast spells (SLASH'EM).
* Casting your **special spell** also grants a retention bonus of 500 turns no matter what role you are

### Other spellcasting changes
* Removed the spellbook of identify (xNetHack)
* Wielding a quarterstaff provides a small bonus to spellcasting (about a 1/3rd of the bonus a robe confers) (Fourk)
* Hungerless casting ignores too hungry to cast penalty (xNetHack)
* Spellbooks' weight is directly related to their level (xNetHack)
* When casting a SKILLED attack spell, you can choose to cast basic fireball or cone of cold (xNetHack/dnh)
* You get a 100 turn reminder for spells that are close to fading away
* Spellcasting no longer exercises wisdom (FIQHack)
* Total hungerless casting is not possible anymore and the intelligence requirements have been increased. (FIQHack)
* Only primary spellcasters can receive divine spellbook gifts
* Spellbooks can generate pre-read
* Display a single accurate spellcasting retention percentage in the spellbook list
* Hide spells that are at 0% retention in the casting menu (this can be toggled with the hide_old_spells option)
* Anti-magic fields block spellcasting for the player and monsters
* Anti-magic fields also block wand zapping
* Failing to read spellbooks causes confusion instead of paralysis (from xNetHack).

### New skill-dependent spell ranges
* Your skill in a spell directly affects how far its ray or beam will travel:

| Spellbook       | Unskilled | Basic | Skilled | Expert |
| --------------- | --------- | ----- | ------- | ------ |
| cancellation    | 2-8       | 7-13  | 9-13    | 11-13  |
| charm monster   | 1-4       | 2-8   | 7-13    | 7-13   |
| cone of cold    | 2-8       | 7-13  | 9-13    | 11-13  |
| dig             | 1-4       | 2-8   | 7-13    | 7-13   |
| drain life      | 1-4       | 2-8   | 7-13    | 7-13   |
| finger of death | 2-8       | 7-13  | 9-13    | 11-13  |
| fire bolt       | 1-4       | 2-8   | 7-13    | 7-13   |
| fireball        | 2-8       | 7-13  | 9-13    | 11-13  |
| force bolt      | 1-4       | 2-8   | 7-13    | 7-13   |
| knock           | 1-4       | 2-8   | 7-13    | 7-13   |
| polymorph       | 2-8       | 7-13  | 9-13    | 11-13  |
| sleep           | 1-4       | 2-8   | 7-13    | 7-13   |
| slow monster    | 1-4       | 2-8   | 7-13    | 7-13   |
| wizard lock     | 1-4       | 2-8   | 7-13    | 7-13   |


### Spell changes and updates

| Spellbook      | Notes                                                                                                                                                                                              |
| -------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| charm monster  | now a directional level 3 spell; <br/>only works on the first monster hit. <br/>At unskilled, the spell can only pacify monsters. <br/>At expert, you get 2 chances to tame each affected monster. |
| clairvoyance   | At skilled, the effect will persist for a while                                                                                                                                                    |
| cone of cold   | Moved to the Matter school (SLASH'EM)                                                                                                                                                              |
| create monster | Increased from level 2 to level 4<br/>Only creates spell beings at unskilled and basic levels.                                                                                                     |
| cure sickness  | Cure sickness is now directional and can be used to cure pets or other monsters (EvilHack)                                                                                                         |
| dig            | Lowered from a level 5 spell to level 3                                                                                                                                                            |
| drain life     | Increased from level 2 to level 3 (xNetHack)<br/>Now shoots a ray instead of a beam<br/>At expert, there is a 10% chance of firing an explosive ball of necrotic energy on each cast.              |
| fireball       | Moved to the Matter school (SLASH'EM)                                                                                                                                                              |
| food detection | Dhampir always detect potions with food detection spells and scrolls.                                                                                                                              |
| haste self     | At unskilled, same effect as a diluted potion of speed                                                                                                                                             |
| invisibility   | unskilled = diluted potion of invisibility                                                                                                                                                         |
| knock          | Cannot be used to escape from an engulfer (this ability is retained for the wand of opening)                                                                                                       |
| levitation     | unskilled = diluted potion of levitation                                                                                                                                                           |
| magic missile  | damage scales with skill                                                                                                                                                                           |
| sleep          | Lowered to level 2                                                                                                                                                                                 |
| poison blast   | Was level 4 in SLASH'EM, raised to level 5                                                                                                                                                         |
| lightning      | Was level 4 in SLASH'EM, raised to level 5                                                                                                                                                         |
| fire bolt      | Moved to the Attack school<br/>stops after the first monster hit<br/>Updated damage bonuses                                                                                                        |
| healing        | Healing spell effectiveness is determined by skill (EvilHack)                                                                                                                                      |
| extra healing  | Healing spell effectiveness is determined by skill (EvilHack)                                                                                                                                      |

**spellbook of fire bolt**
* Base damage is 1d10 fire damage
* At skilled it deals 2d10 fire damage
* At expert it deals 3d10 fire damage
* At level 5 it deals an additional +1d4 damage
* At level 11 it deals an additional +1d4 damage
* At level 17 it deals an additional +1d4 damage
* If the target resists cold a bonus +7 damage is applied.

This means if the player has maxed out their attack spell skill and leveled up to XP17, they could be dealing 3d10+3d4 with a level 1 spell.


**spellbooks of healing and extra healing**
* Healing power scales with skill level

| spell         | Unskilled | Basic | Skilled | Expert |
| ------------- | --------- | ----- | ------- | ------ |
| healing       | 4d4       | 6d4   | 8d4     | 10d4   |
| extra healing | 4d8       | 6d8   | 8d8     | 10d8   |


**spellbook of light**
* Spell of light's diameter of effect scales with spellcasting ability.
* For reference, the uncursed scroll of light always illuminates a radius of 11.

|       | Unskilled | Basic | Skilled | Expert |
| ----- | --------- | ----- | ------- | ------ |
| range | 1         | 3     | 5       | 7      |

**spellbook of magic mapping**

* The effectiveness of magic mapping depends on your spellcasting ability. The spell will never fully map a level, only the scroll can be depended upon for that.
* Lowered from level 5 to level 4
* Unskilled acts like a confused magic mapping (1 in 7 squares successfully mapped)
* Basic maps 1 in 5 squares
* Skilled maps 1 in 3 squares
* Expert maps all squares

**spellbook of magic missile**

Damage scales with level. Unskilled now deals half the damage expert can.

|       | Unskilled    | Basic        | Skilled      | Expert       |
| ----- | ------------ | ------------ | ------------ | ------------ |
| range | ((XL/2)+1)d3 | ((XL/2)+1)d4 | ((XL/2)+1)d5 | ((XL/2)+1)d6 |


## DUNGEON CHANGES


* Extended the main dungeon by 5 levels.
* Removed the **mysterious force** from the game (xNetHack)
* **Branchport** always brings you to the entry level of a branch
* The Rogue level ghost gets a war hammer.
* Chickatrices and cockatrice eggs will now appear in cockatrice nests (xNetHack)
* Shops cannot have themed rooms with unusual floor textures (xNetHack)
* Allow delis to buy and sell tin openers.
* No special **themed rooms** generate until level 3
* Random rivers were added to many of the quest filler levels
* Random secret doors are secret less of the time (xNetHack)
* Random secret corridors have been removed (xNetHack)
* Removed the "temple of the gods" theme room. This room contains 3 altars, one of each alignment.
* Many new themed rooms ported from xNetHack.
* The portal to Fort Ludios is placed in the first eligible vault generated (xNetHack/UnNetHack).
* Temples are always lit.

### New levels
* All original Vanilla Sokoban levels have been removed and replaced.
* 18 new demon lairs levels or variants
* 40 new soko levels
* Many new big room variants
* 2 new oracle levels
* 2 new castle variants
* 2 new fort ludios variants
* 4 new mine end variants
* 5 new minetown levels
* 3 new levels for Vlad's tower
* 7 new levels for the wizards tower
* alternate moloch's sanctum
* alternate valley level
* new levels for gehennom
* Lost Tomb branch (2 versions)
* Moloch's Temple branch (2 versions)
* Wyrm Caves branch

### Castle changes
* The castle level is now marked as a graveyard
* The drawbridge passtune range has been expanded by one square (xNetHack)
* The drawbridge also does not always close with the passtune, one out of five times it will malfunction when trying to close it (xNetHack)

### Valley of the Dead
* Non-undead players can't regenerate hit points whilst in the Valley of the Dead (EvilHack)

### Enhanced Gehennom
* The second fake wizard level has been removed.
* The portal to the Wizard's Tower can appear in Gehennom levels 10-17.
* The wizard's tower has been extracted to its own branch (xNetHack/EvilHack)
* The structure of Gehennom now roughly follows the SLASH'EM template

### The Wizard's Tower Overhaul
* NerfHack borrows from other great variants to create the biggest and baddest tower that Rodney could ever reside in.
* The Wizard's Tower has been expanded to a staggering 7 levels high to provide a highly challenging penultimate test.

### Vlad's Tower revamp
* This ports the updated and enlarged levels for Vlad's from EvilHack.
* Some flair was added to the levels to further torture players.
* All levels of Vlad's Tower are fully lit.

### DEMON AND DEMON LAIR CHANGES
* Demonic bribes are much more expensive
* Juiblex buffs
* Geryon buffs (EvilHack)
* Increase speed of Baalzebub

### Sokoban
* Sokoban levels are cold and icy - legend has it a white dragon named Wintercloak took the tower over, leaving a trail of frost in its wake. In addition to the level being colored blue with splashes of icy cyan, you will see random patches of ice form in the level. Because they are cold, if potions land on the floor, they have a chance of freezing and shattering.
* Note: A recent change from NetHack 3.7 also makes ice occasionally slide the player in a random direction.
* Sokoban now has two additional levels - an entry level with river obstacles (adapted from the town filler level from UnNetHack) and another puzzle level to solve.
* Monsters won't break boulders in Sokoban with pick-axes or mattocks, or spellcasting.
* All the vanilla sokoban levels have been replaced with levels from SLASH'EM or other variants.
* All Sokoban zoos have Wintercloak, a powerful white dragon, guarding the treasure.
* The zoos in Sokoban have been expanded slightly.
* In addition to the amulet and bag, the Sokoban prize can also be a cloak of magic resistance or a magic marker. Sokoban prizes are always erodeproofed.
* You will now receive a message when incurring a Sokoban Luck penalty.
* Stop Sokoban guilt after acquiring the prize.
* Sokoban maps above puzzle #2 get 2 mimics.
* soko5 (the bottommost puzzle level) has holes instead of pits (from FIQHack)

## DUNGEON FEATURES
* Thrones can grant knowledge of magical items.
* Thrones can summon much larger audiences when that #sit effect is hit.
* Trees can generate in dungeon rooms (xNetHack)
* Trees on special levels are generated pre-looted (they cannot be kicked for killer bees or fruits)
* Trees can be destroyed by fire, cold, and disintegration rays. If a tree is destroyed by fire or cold, it has a 1 in 3 chance of exploding - possibly creating a chain reaction

### Grass
* A new dungeon feature ported from xNetHack, SpliceHack.
* Monsters can hide under grass (xNetHack).
* You cannot dust engrave on grassy tiles.
* Burned engravings also burn up grass.
* Walking on grass makes you more stealthy.
* Herbivore pets will eat grass (EvilHack)

### Puddles
* A new dungeon feature ported from EvilHack and SlashTHEM.
* Many pools are replaced with puddles instead.
* Fountains gush out puddles instead of pools
* Whetstones can be used in puddles and can dry up puddles.
* Tiny monsters can drown in puddles (relevant if polymorphed into one)

### Forges
* A new dungeon feature ported from EvilHack
* In addition to facilitating forging, forges allow the player to perform many interesting tricks like repairing armor and disposing of zombies.
* Items can pass over forges.
* There is a one-time 1 in 30 chance of erodeproofing an item when dipping in a forge. After this occurs, the forge will instead emit a puff of steam.
* Forges always light up the square they occupy.
* Cold rays have a chance cool forges.
* Forges burn the grease and poison off dipped items.
* You cannot forge whilst confused, stunned, hallucinating, weak from hunger, or with STR under 4.
* A forge is always guaranteed in the Castle level.

#### Forging and Forging Recipes
* Items can be forged by **(a)pplying a hammer** whilst standing on a forge (no #forge or #craft command)
* Forging always has a 1 in 20 chance of creating an **inferior product**.
* Anytime a product of forging has a property, there is a 1 in 13 chance the forge will cool and cease functioning.

In addition to the below recipes, every item has an additional identity recipe: mixing two of the same item creates more of the same item. This allows combining things like an object property with a desirable material or enchantment on another item.

| Result               | Ingredient #1      | Ingredient #2         |
| -------------------- | ------------------ | --------------------- |
| aklys                | flail              | club                  |
| axe                  | dagger             | spear                 |
| battle axe           | axe                | broadsword            |
| broadsword           | scimitar           | short sword           |
| dagger               | arrow (x2)         | knife                 |
| dwarvish boots       | gauntlets          | dwarvish short sword  |
| dwarvish helm        | helmet             | dwarvish short sword  |
| dwarvish mattock     | pick axe           | dwarvish short sword  |
| dwarvish ring mail   | chain mail         | dwarvish round shield |
| dwarvish roundshield | large shield       | dwarvish helm         |
| dwarvish short sword | dwarvish spear     | short sword           |
| dwarvish spear       | arrow (x2)         | spear                 |
| elven broadsword     | scimitar           | elven short sword     |
| elven dagger         | elven arrow (x2)   | knife                 |
| elven long sword     | elven short sword  | broadsword            |
| elven ring mail      | chain mail         | elven shield          |
| elven shield         | elven dagger       | small shield          |
| elven short sword    | crossbow bolt (x2) | elven dagger          |
| elven spear          | elven arrow (x2)   | elven dagger          |
| flail                | morning star       | mace                  |
| javelin              | crossbow bolt (x2) | spear                 |
| katana               | long sword         | broadsword            |
| knife                | arrow (x2)         | dart (x2)             |
| long sword           | short sword        | broadsword            |
| mace                 | club               | dagger                |
| morning star         | mace               | dagger                |
| orcish boots         | gauntlets          | orcish short sword    |
| orcish chain mail    | ring mail          | orcish shield         |
| orcish dagger        | orcish arrow (x2)  | knife                 |
| orcish helm          | dented pot         | orcish dagger         |
| orcish ring mail     | orcish shield      | orcish helm           |
| orcish shield        | orcish helm        | orcish boots          |
| orcish long sword    | orcish short sword | broadsword            |
| orcish short sword   | crossbow bolt (x2) | orcish dagger         |
| orcish scimitar      | knife              | orcish short sword    |
| orcish spear         | orcish arrow (x2)  | orcish dagger         |
| saber                | scimitar           | long sword            |
| scalpel              | knife              | stiletto              |
| scimitar             | knife              | short sword           |
| short sword          | crossbow bolt (x2) | dagger                |
| spear                | arrow (x2)         | dagger                |
| stiletto             | crossbow bolt (x2) | knife                 |
| trident              | scimitar           | spear                 |
| tsurugi              | two handed sword   | katana                |
| two handed sword     | battle axe         | broadsword            |
| war hammer           | mace               | flail                 |
| bardiche             | battle axe         | javelin               |
| bec de corbin        | war hammer         | spear                 |
| bill guisarme        | guisarme           | javelin               |
| fauchard             | saber              | javelin               |
| glaive               | short sword        | javelin               |
| guisarme             | grappling hook     | javelin               |
| halberd              | ranseur            | axe                   |
| lance                | glaive             | javelin               |
| lucern hammer        | war hammer         | javelin               |
| partisan             | broadsword         | javelin               |
| ranseur              | stiletto           | javelin               |
| spetum               | knife              | javelin               |
| voulge               | axe                | javelin               |

### Toilets
* A new dungeon feature ported from SLASH'EM.
* Toilets have received many enhancements after adapting them from SLASH'EM. Notably, toilets can now appear on their own, separate from sinks, whereas in SLASH'EM, they only came in pairs with sinks. Overall, their frequency has been dialed way back so they are quite rare.

* Toilet prayer can now stop the vomiting process
* Praying at toilets can cure sickness.
* Sitting on toilets can alleviate satiated status.
* Sitting on toilets fully heals your HP.
* Toilets can sometimes break when sat on, especially if you are a giant...
* Dipping potions into toilets only contaminates potions into sickness.
* Dropping amulets into toilets can identify them (SLEX)

#### Toilet kicking:
* Like sinks, toilets now have a couple different effects from kicking them, including a few YAFM.
* Kicking now only breaks the toilet in a 1/7 chance
* Kicking can generate giant cockroaches and pools from kicking (1 in 17 chance)
* Kicking can generate brown puddings (only once per toilet)
* Kicking can generate a random tool. Normally this tool will weigh under 15aum, but sometimes you'll get a large tool that bonks against the piping. If a large tool bonks 3x - you'll get that tool no matter how big it is and the toilet is destroyed in the process.

Dipping an edged weapon into a toilet can poison it, but also probably rust any metallic items.

### Bloody tiles
* Ported from SpliceHack
* When a monster is killed, it can spray blood around the surrounding tiles depending on its size.
* The blood is mostly cosmetic, however, players cannot engrave in the dust whilst blood covers that tile.
* Blood can be wiped off with a towel, or will wear off after enough activity.
* Fire and acid rays also burn off blood from tiles.
* Bloody doors are more difficult to open and close.

### New container traps
* A cream pie may spring out of the box and hit the player in the face.
* A small critter may jump out of the container, briefly scaring you.
* A loud alarm may sound, waking up nearby monsters.

### Misc trap changes
* **Magic traps:**
  * can inflict resistance vulnerability on the hero.
  * Invisibility from magic traps lasts a long time (2500-5000 turns), instead of permanently.
  * Cause disrupted warning signals for monsters in the vicinity of their effect.
* **Polymorph traps:**
  * are always used up when monsters are polymorphed as a result of moving onto them.
  * will only polymorph iron boots above level 13, otherwise it acts like legacy pre-5.0 behavior.
* Proximity to anti-magic traps reduces the success rate of spellcasting.
* Cold traps and ice demons can also steal (25 + d25)% of your cold resistance.
* Arrow traps and dart traps cannot be avoided by flight.
* You cannot fly over falling rock traps.
* Flying and levitation usually protect from being harmed by spear traps, however, there is still a 25% chance of being hit (by an abnormally long spear)
* Disarming a rust trap results in a puddle instead of a fountain

### Falling rock traps
* At higher levels, boulders can drop from falling rock traps.
* Falling rock traps can result in stunning
* Falling rock traps can drop multiple rocks (or boulders).
* You can now #untrap falling rock traps, obtaining rocks (Fourk).

### Spear traps
* A new floor trap ported from EvilHack
* Spear traps only start appearing after level 5
* Spear traps can be untrapped, potentially yielding a random spear type in the process.
* If you or a monster hit by the trap is thick-skinned, the spear just breaks and the trap is deleted.
* The trap also doesn't affect unsolid monsters.
* When hit, it deals 7-14 damage and wounds your legs for 10-19 turns.
* Spear traps sometimes have poisoned spears.
* Spear traps abuse strength and constitution.

### Magic beam traps
* A new trap ported from EvilHack
* Magic beam traps only start appearing after level 14
* When you (or a monster) steps on this trap, it shoots a random ray type from a pre-set location that crosses through the beam trap. The beam type is set for each trap, so once you notice it shoots fire rays, it will always shoot fire rays.
* Magic beam traps can very rarely shoot disintegration rays.

### Grease traps
* A new trap debuting in NerfHack
* Grease traps function similarly to rust traps, but they spray a blast of grease at the player or monster that stepped on it.
* When you step on a grease trap, you either slip in a puddle of grease or get sprayed by a grease hose.
* When stepped on, the trap disarms with a random 1 in 15 chance.
* You can also #untrap grease traps, if successful you may yield a rubber hose or - in rare cases - a can of grease.

**Puddle of grease:**
  * If you don't have levitation or flying, you gain fumbling ("You step in a puddle of grease.")
  * Slipping in grease traps can cause you or monsters to become paralyzed for a few turns and inflicts a small amount of damage.
  * Mud boots and water walking boots protect from slipping on grease traps.

**Grease hose:**
  * If the grease hits your head, you are blinded unless you are wearing a visored helmet. Your blindfold/lenses/etc may also become greased and fall off.
  * If the grease hits your arm, your weapon(s) or shield can become greased and fall off. You also become Glib for 10 to 15 turns.
  * If the grease hits your feet, your boots can become greased and fall off.
  * Otherwise, the grease hits your torso and your outermost armor becomes greased. Random items you are carrying can also become greased and fall from your possession. If you are carrying a towel, there is a 50% chance it becomes greased as well. If you are riding a steed the saddle will get hit with grease, making you fall off.
* When a monster gets hit with grease, it will randomly grease an item in their inventory.

Note: Getting hit by grease will not knock off worn cursed items.

### Cold Traps
* Ported from xNetHack, originally from UnNetHack
* Cold traps are nasty and deal 4d8 cold damage, potentially shattering potions.
* If you have less than 25% cold resistance, you can have your HP drained similar to fire traps
* If you are 25% or more cold resistant, you may have a significant portion of your resistance (25-50%) sucked away by the trap.
* Ice traps confer vulnerability to cold.

### Door traps
* Door traps actually explode in a ball of flame (EvilHack)
* These traps will start appearing at level 8.


## NEW SPECIAL ROOMS


**Art rooms:**
* Ported from SpliceHack
* These rooms have a one-time event that occurs upon entering a room
* Most of the time it's a fun piece of art depicting something with the denizens of the dungeon. But sometimes it's a special effect.
* Art rooms exercise INT and WIS, depending on the room; in rare cases, your intelligence is directly increased.
* To get any effects, you must not be blind when you enter the room

**Dragon lairs:**
* Ported from SLASH'EM
* Dragon scales can sometimes appear in dragon lairs.
* Dragon lairs now produce special sounds when they appear on levels.

**Giant courtroom:**
* Ported from SLASH'EM
* Giant courts sometimes have tinning kits.
* Monsters in giant courts are always hostile.
* Always ruled by a titan

**Real zoo:**
* Ported from SLASH'EM
* Monsters in real zoos are always hostile.

**Fungus farm**
* Ported from SLASH'EM
* Features a collection of slimy and oozy monsters

**Migo hive**
* Ported from SLASH'EM
* Features a roomful of migos and migo warriors ruled by a migo queen.

**terror halls**
* Ported from SlashTHEM
* Features a random assortment of U (hulk class) monsters

**Junk Shop**
* Ported from SpliceHack
* This counts as a general store that is usually pre-populated with a bunch of junky items.

**Collectible Card Game Company**
* This shop only spawns for cartomancers and features a large variety of summon cards, with the occasional deck box or backpack. Takes the place of most food and weapon shops.


## ALTARS, PRAYER, AND PRIESTS


### Altars
* Altars won't start to appear until dungeon level 3.
* When donating to priests - the gold vanishes upon receipt
* There is a greater chance of hostile minions appearing when converting an altar. Especially if the altar is in an occupied temple (EvilHack)
* Intrinsics speed, stealth, and telepathy are no longer granted by the gods when #offering.
* Getting troubles fixed by prayer abuses constitution.
* Permanent alignment conversion prevents more divine protection from being granted
* New #offer effect: sometimes your god will change the alignment of your weapon to match your alignment, giving it a small boost to damage and to-hit.
* Scale temple donation costs by alignment abuse (EvilHack)

### Revised divine protection scheme
* The more protection the player has, the less likely it is to be granted (K-Mod)
* The maximum possible divine protection is capped at -9AC.
* When protection is granted from priests or your god, it is limited to increments of 1AC per granting.

### Crowning
* Crowning requires 13 Luck (dNetHack).
* Crowning only provides a 50% increase in resistances.
* Intrinsic see invisible is no longer granted via crowning
* Intrinsic telepathy is no longer granted via crowning
* Crowning gifts are only granted when crowned.
* Your god will not crown you until you have completed the quest.
* Crowning makes it impossible to change alignment ever again.


## THE QUEST


* Removed the quest turn limit (UnNetHack)
* Players can enter the quest as soon as they reach level XL 10 (UnNetHack)
* Prevent the player from skipping most of the quest (xNetHack).
* Mark all quest levels as hardfloor.
* Players cannot do horizontal or downward teleporting whilst the quest nemesis is alive.


## Special thanks to:
- My wife - for being endlessly patient with this time-consuming endeavor!
- K2, for hosting NerfHack on hardfought.org
- anyone who has contributed, played, playtested, reported bugs, filed issues, or helped out NerfHack in any way.
