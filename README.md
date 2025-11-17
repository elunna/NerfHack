# NerfHack

Welcome, traveler, to NerfHack!

![nerfhack.bmp](nerfhack.bmp)

---
**NerfHack** is the successor to **Hack'EM**, which was a modernized variant of **SLASH'EM** based on **EvilHack**. Unlike Hack'EM, **NerfHack** starts fresh from **NetHack 3.7.0** and is designed to be a significantly more challenging variant than Vanilla NetHack. While it incorporates many features and mechanics from Hack'EM, it is *not* a full port, introducing numerous new changes in both content and design. By drawing inspiration from various NetHack variants and carefully fine-tuning different aspects of gameplay, key pain points have been identified and addressed to refine the difficulty curve - resulting in a more treacherous and rewarding dungeon.


## Main goals and ideas for NerfHack:

### Usurp assumptions and approaches to the game

Some of the changes in NerfHack are controversial and challenge decades-old assumptions held by a passionate user-base. This variant will pose pertinent philosophical questions:

**What is fairness in a game that was designed around unfairness?**

    NetHack is known for its brutal difficulty, but it also provides powerful tools and exploits to mitigate this. By nerfing these exploits, does NerfHack make the game fairer, or does it simply shift the balance of unfairness?

**Do players "deserve" to win, or must victory always be earned?**

    Traditional NetHack allows for lucky breaks, powerful item combos, and even near-invincibility through knowledge and exploitation. NerfHack asks whether true mastery should require overcoming even those advantages.

**Is knowledge still power if its applications are restricted?**

    Many of NetHack's challenges can be bypassed through deep game knowledge - like using price identification, alchemy abuse, or resource farming of some sort. If those tools are weakened, does the game reward a different kind of knowledge, or does it simply punish players more?

**What does "difficulty" mean in a game with near-infinite possibilities?**

    By removing exploits, NerfHack raises questions about what constitutes a fair challenge. Is difficulty about strategic depth, resource scarcity, or raw randomness?

**Is a game still fun if it removes "broken" mechanics?**

    Some players enjoy NetHack precisely because of the wild, overpowered strategies they can discover and use. By taking those away, does NerfHack enhance the experience or simply make it more frustrating?

**Is optimization a form of creativity, or just an arms race?**

    Many players see NetHack as a puzzle to be solved through optimal play. If NerfHack forces them to rethink their approach by removing dominant strategies, does it encourage more creative play, or does it just lead to a different set of rigid optimizations?

**If a game removes "cheap" tactics, does it reveal true skill?**

    Some exploits in NetHack might be considered "cheap," but their removal in NerfHack asks whether true skill is about navigating the game's systems under harsher constraints.

**Does nerfing exploits make the game more "realistic," and does that matter?**

    Many nerfs in NerfHack attempt to close loopholes that feel unrealistic (e.g., too-many-wishes, abuse of polymorph, pet theft). But does realism improve a roguelike experience, or is the chaotic absurdity part of the appeal?

**Is frustration an essential part of mastery?**

    By making the game significantly harder, NerfHack raises the question of whether enduring more losses leads to greater satisfaction - or just burnout.

Ultimately, NerfHack challenges the notion of what makes NetHack "fair," "fun," and "winnable," forcing players to reconsider their relationship with difficulty, strategy, and perseverance.


## **NerfHack Design Goals**

### **Discourage and Prevent Degenerate Behavior**
Players should *play the game* and play around the game's *core mechanics*, not just exploit unintended side effects. Strategies that trivialize gameplay through excessive farming, grinding, or repetitive abuse of loopholes are discouraged or removed.

**Examples of discouraged behaviors:**
- **Altar camping** – Preventing infinite sacrifice grinding for artifacts.
- **Farming exploits** – Nerfing tactics like vault guard farming, quest monster farming, and werefoo farming.
- **Polypiling abuse** – Limiting big-pile polypiling to reduce overpowered item generation.
- **Wraith luring** – Preventing excessive level farming by luring wraiths to controlled environments.

**Here are some general guidelines as to what qualifies for nerfing:**
* Is it an infinite or unbounded resource?
* Does it encourage repetitive or mindless farming?
* Does it encourage tedious or time-consuming gameplay?
* Is the exploit the result of unintended or broken mechanics?
* Does the exploit allow the player to bypass core mechanics of the game or dungeon design?
* Does the exploit dissuade the player from interacting or advancing deeper into the dungeon?
* Is it an overwhelmingly effective strategy, making all other options seem trivial in comparison?

---

### **Encourage Exciting and Creative Gameplay**
By nerfing or limiting dominant strategies, players are encouraged to think outside the box and adapt in novel ways. The best players will be those who can creatively solve problems rather than rely on rote strategies.

**Examples of nerfed mechanics that encourage adaptation:**
- **Pet Theft** – Without the option to loot shops or credit clone with a pet, players will have to earn their own gold or steal by brute-force.
- **Astral Rain** – By limiting high-level pets, players will have to contend with the last level without a horde of purple worms to do their bidding. Some foes also spawn with rings of slow digestion or teleport control, adding more uncertainty to the fight.
- **Unicorn Horns** – Less reliable unihorns force the player to use other items, like potions of healing or milk, to cure their maladies. They can also choose to invest enchantment into their unicorn horn for a more reliable source of healing.
- **Price Identification** – Without the tedious activity of price identification, players will have to find more novel ways of identifying items or embrace the uncertainty of use-testing.

---

### **Give Value to Underutilized Features**
Many items and mechanics in *NetHack* are underused due to stronger alternatives. *NerfHack* aims to breathe new life into these features by making them more viable or rewarding in the right situations.

**Examples:**
- **Towels** cannot be used to blind one's self, making the blindfold an integral asset where before it became a junk item as soon as a towel was acquired.
- **Invisibility and displacement** both provide more protection against gaze attacks (and there are many new threats with dangerous gazes in NerfHack)
- **Polearms** now grant an AC bonus and can be used to disarm traps. They are also more effective versus horses and centaurs.
- **Sources of ESP** like the helm of ESP and amulet of ESP become more valuable because of the absence of easily attainable intrinsic telepathy.
- **Sources of warning** like the ring of warning and helm of caution also become more valuable with the nerfing of intrinsic telepathy gain.
- **Sources of see invisible** like the ring and potion also become quite useful because of the lack of attainable intrinsic see invisible.
- **Gem alchemy** adds value and utility to both potions of acid and valuable gems.

---

### **Create Meaningful Resource Scarcity**
Players should always feel that their resources are valuable and must be managed wisely. Excessive resources are quelled in many ways.

**Ways scarcity is enforced:**
- **Item destruction and erosion** – More environmental hazards that can destroy or degrade items.
- **Limited wishes** – Wands of wishing are replaced with one-off scrolls of wishing (which never appear randomly); wishes from fountains, thrones and magic lamps are all more rare.
- **Finite altars** – Making alignment gifts more constrained.
- **AC scaling** – Making dramatically high armor optimization less attainable.
- **Tighter control over HP and healing** – Reducing the ability to gorge maximum HP with alchemy.
- **Donated gold vanishes** – Reducing the supply of gold in the dungeon, adding more value to gold.
- **Gifted gems vanish** – Similar the above change - creating more value in gems because of scarcity.
- **Less guaranteed death drops** – In specific cases, some monsters drop items less frequently. For example, soldiers only drop half the rations they previously did. Minotaurs also drop wands of digging less often.

---

### **Introduce New Threats**
Players should always be on their toes. New threats are designed to add challenge, unpredictability, and danger at all stages of the game.

**Examples:**
- **An expanded bestiary** – Interesting monsters all over the NetHack variant community have been ported in or created from scratch to challenge adventurers.
- **New monster behaviors** – Existing monsters gain new abilities and AI tweaks.
- **Expanded spellcaster spells** – More enemy spellcasters with powerful effects in both clerical and mage spells.
- **New traps** – Additional environmental hazards and surprises like the infamous grease trap!
- **More dangerous impairments** – Effects like fumbling and glibness now have deadlier consequences. "Never be burdened" should be your new maxim for survival.
- **Cursed items are worse** – More severe downsides for equipping cursed gear carelessly.
- **Cthulhu is a major endgame boss** and awaits the player in Moloch's Sanctum. Cthulhu has received many buffs and will even resurrect to haunt the player much like the Wizard of Yendor.

---

### **Smooth Out Dramatic Power Spikes**
Player progression should feel more balanced, preventing sudden jumps in power that trivialize later stages of the game.

**How power progression is balanced:**
- **Spread wishes throughout the late game** – Instead of 5-7 wishes guaranteed at the Castle, four (4) scrolls of wishing are distributed to the Castle, Rodney's Tower, Vlad's Tower, and Moloch's Sanctum.
- **Soft nerfs to wishes** – Many item nerfs indirectly make wishes less dominant.
- **Partial intrinsics and reflection** – Instead of binary intrinsics, the player has to build up immunity from 0% to 100%. Reflection also doesn't provide full protection anymore.
- **Nerfed intrinsic gains** – Permanent intrinsics like telepathy, see invisible, and teleport control cannot be acquired by eating corpses or other means, keeping challenges alive throughout the game.
- **Better scaling for levels 20-30** – Maximizing levels now has some enticing damage and to-hit bonus benefits
- **Altars don't dish out artifacts at low levels** – At low levels, the probability of receiving artifacts is miniscule. As the player gets closer to level 20 they increase their odds of receiving the goods.

---

### **Introduce Quality-of-Life Features**
While *NerfHack* is harder, it shouldn't be tedious. The intention is to reduce unnecessary micromanagement and make useful information more accessible.

**Examples:**
- **Auto-identification** – Anything that is unambiguously known is identified automatically.
- **You gain familiarity with weapons** (and even rings of increase damage and increase accuracy) after killing enough monsters with them.
- **In-game lookup** – Players can access detailed information on objects and monsters without external wikis.
- **+13 weapon enchantments** – To help clear late-game hordes (without making things too easy).
- **Peaceful monsters are underlined**
- **Magic cancellation (MC) value is shown on the bottom status line**
- **More useful information** is shown in the Ctrl-X enlightenment screen and skill enhancement screen, making external note-taking less necessary
- **/> or < can be used to autotravel to stairs**
- **Farlook enhancements** – The player is able to see more monster conditions for both pets and enemies.

---

### **Emphasize Role and Race Uniqueness**
Roles and races should feel distinct, each with unique strengths, weaknesses, and playstyles that persist throughout the game.

**How uniqueness is reinforced:**
- **No wishing for quest artifacts** – Players must rely on their own quest artifact rather than wishing for others. In turn, most quest artifacts have also had custom buffs applied.
- **Role differentiation** – Each role has defining abilities or mechanics that make them stand out.
- **Race differentiation** – Small tweaks have been applied to each race to make them more unique and interesting.
- **Racial armor bonuses/penalties** – Making racial differences more meaningful.

---

### **Introduce New and Innovative Features**
*NerfHack* isn't just about nerfing exploits - it's about introducing new mechanics, items, and abilities to keep the game fresh and fun.

**Examples:**
- **Two new roles:** – The Cartomancer and the Undead Slayer join the roster
- **Two new races:** – Dhampir and Grung add variety to both new and old roles.
- **New items and spells** – Expanding the player's toolkit.
- **Many new levels and branches** – The Lost Tomb, Moloch's Temple, and the Wyrm Caves are new branches, and many levels have alternate versions to mix things up.
- **Weapon secondary effects** – Some weapons gain unique abilities (e.g., spears can pierce through multiple enemies).
- **Mirrors provide a fragile source of reflection** – Reflection is an important property for survival, and now it can be attained much earlier in the game. However, mirrors are quite fragile and can break if they reflect a strong ray or are subject to too much impact damage.

---

### **Follow the Feature Uniqueness Principle**

New mechanics should not needlessly duplicate existing ones. Features should either be distinct or implemented in a way that preserves the uniqueness of older features, otherwise they risk making existing items redundant. This is especially true if the mechanic is critical for the player

An interesting side effect that occurs when you nerf certain mechanics is that other items' individual powers start to shine and become unique in usually being the only way to bestow that ability in the game.

**Examples:**
- **Invisibility is common but balanced** – Many sources exist, but it's not an overpowered ability.
- **New mechanics should not replace old ones** – Any overlapping mechanics should be designed to complement rather than devalue existing ones.

**Why Object Properties Were Not Imported**

If players ask why object properties were not ported into *NerfHack*, the key answer lies in our adherence to the *Feature Uniqueness Principle*. This principle aims to preserve the distinctiveness and rarity of item effects, ensuring that each item remains special in its own right.

Object properties often introduce effects that overlap with or duplicate existing item properties. For example, fire resistance is a valuable and rare property in *NetHack*, typically granted by specific items like the **ring of fire resistance** or **Fire Brand**. If a generic "fire resistance" property was introduced that could be applied to multiple items, it would dilute the unique appeal of these specific items. Suddenly, instead of having a few prized items that grant fire resistance, there would be many ways to achieve the same effect, reducing the rarity and significance of these items.

By preserving the uniqueness of individual items, challenge and excitement of acquiring powerful or rare effects is maintained. The value of an item like the **ring of fire resistance** lies not just in the mechanics it provides, but in the fact that it's an item with a specific and often hard-to-come-by property. Introducing object properties would make such items less important and impose fewer decisions about equipment and the potential trade-offs they face.


### **Why Some Items Violate the Uniqueness Principle:**

- **Freedom Boots:** These confer *free action*, which is typically granted by the ring of free action. Due to nerfs to flying and speed in NerfHack, an additional powerful pair of boots felt appropriate.
- **Fire Helmet:** Grants *fire resistance*, a property normally associated with the ring of fire resistance. However, it competes with other helmets, such as the helm of ESP or helm of caution, which have their own useful effects.
- **Rogue's Gloves:** These confer *searching*, but they are *fingerless*, which leaves the wearer vulnerable to petrification from touch-based threats.
- **Spellbook of Lightning:** While this duplicates the effect of the wand of lightning, it's costly to cast (Level 5) and carries the risk of destroying rings and wands. It provides an additional long-term tool for spellcasters proficient in attack spells.
- **Spellbook of Poison Blast:** This spellbook duplicates the effect of the *wand of poison blast*, but it comes with the drawback of damaging rottable items. As a level 5 spell it is also costly. Many monsters also exist that resist poison, but it's another useful *attack* spell.
- **Wand of Identify:** This duplicates the effect of the *scroll of identify* but also replaces the spellbook of identify which was removed for its ability to squash the identification game. It also makes it mechanically possible for cartomancers to see **zapping-cards of identify** spawn.
- **Bracers of Sleep Resistance:** These duplicate the effect of orange dragon scales, which provide *sleep resistance*, but they are unique as the only non-scale source of this resistance. Their main utility lies in being particularly useful for Dhampir, who may struggle to get the full benefits of sleep resistance through more traditional means.
- **Bracers of Cold Resistance:** These add another source of *cold resistance*, which already exists in the ring and white dragon scales. While the item itself is rare, it offers players more security since **cold traps** can steal away your intrinsic cold resistance.
- **Bracers vs. Shapeshifters:** These introduce a third source of the *shapeshifter protection* effect, which was previously limited to the ring of protection vs. shapechangers and Werebane. This property isn't usually considered over-powered in vanilla NetHack, however, it is more useful in NerfHack because there are more dangerous werefoo and shapeshifters. Another source felt appropriate to compensate for the increased threat of shapechangers.
- **Bracers of Unchanging:** This duplicates the effect of the amulet of unchanging, however, amulet slots are valuable and a secondary source makes for more flexible builds, especially in the early game when magic resistance may be lacking.

---

### **Make It Easy to Variant-Hop**
Transitioning from Vanilla *NetHack* to *NerfHack* should feel natural, without forcing players to relearn the game from scratch.

**Ways accessibility is ensured:**
- **Intuitive mechanics** – Changes are designed to make sense based on in-game feedback.
- **Minimal external lookup requirements** – No need to memorize complex tables for mechanics like forging or alchemy; all necessary information is available in-game.
- **No major interface changes** – The UI remains familiar to veteran players.
- **No new #extended commands** – Except for developer/debugging tools.
- **No changes to Vanilla monster letters** – Ensuring compatibility with player expectations and muscle memory. Please note that some monster letters were changed when porting monsters from other variants to ensure unique color and symbol combinations for monsters.


For a complete list of changes, please visit the changelog repo: https://github.com/elunna/nerfhack-changelog


## For playtesters
In wizmode, there are some extra tools to speed up things:

To create rabid monsters, use ^W and specify rabid.
    ex: "rabid rothe"

To create diseased monsters, use ^W and specify diseased.
    ex: "diseased rothe"

To create berserking monsters, use ^W and specify berserking.
    ex: "berserking rothe"

To create spell beings, wish for a "summoned" monster:
    ex: "summoned rothe"

The #wizcrown command has been added for testing crowning

The #wizclear (^z) command, clears all monsters on the screen

The #debugfuzzer command was changed to just #fuzz.
