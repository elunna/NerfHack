# NerfHack

Welcome, traveler, to NerfHack!

NerfHack is the followup to Hack'EM, which was a modernized SLASH'EM based on EvilHack. NerfHack starts fresh from NetHack 3.7.0 WIP and aims to accomplish a couple concise goals: 

NerfHack is intended to be a more difficult variant than Vanilla NetHack. By pulling changes from many variants and fine-tuning various exploitable aspects of the game, we have uncovered many pain-points to smooth out the difficulty curve. The general idea has been to nerf strategies commonly employed by seasoned players with the goal of making the game more interesting.

It's not all nerfs though, many small buffs and mechanics have been added to even the playing field and make the game more interesting.

## Development and Gameplay Goals:
1) Nullify many tried-and-true exploits, for example:
   * Pet Theft
   * The Protection Racket
   * Astral Rain
   * Wraith luring
   * Healing potion HP gorging
   * Infinite Altar camping
   * Genociding on the planes
   * Polypiling
   * Bones peeking
   * Excalibur for all lawfuls
2) Create resource scarcity for the player
   * Put a tight leash on all the different resources a player has access to so they never have quite too much (or it's a game dependant situation.)
   * This spans everything from AC to wishes.
    - AC and HP
    - Altars can eventually be used up
    - Encourage player to spend enchant weapon on Unicorn Horn
    - Limit wishes
    - Polymorph yields diminishing returns.
3) Introduce new threats
    - New monsters, monster behaviors and spells for the mages
    - Many old monsters have new tricks
    - New traps
    - Many cursed items have new dangerous effects
    - Many impairments (fumbling, glib, etc) have more dangers associated with them
4) Smooth out dramatic power spikes for the player
    * Things like partial intrinsics, partial reflection greatly affect this
    * Gaining permanant intrinsics is much more difficult and carries challenges deep into the game
    * Gaining levels from 20-30 now has some enticing damage and to-hit bonus benefits
    * Many item nerfs also softly nerf wishes in general so wishes are not so overpowered
5) Introduce quality-of-life features
    * Speed up the pace of the game, auto-identifying anything that is umambiguous
    * Give the player access to in-game object and monster lookup information
6) Shorten the endgame
    * Gehennom is much shorter, the wizards tower is accessible from the Castle level
    * Allow players to enchant weapons to +13 so they can clear through the hordes with ease (it still won't be easy!)
7) Emphasize role and race uniqueness
    * By not allowing quest artifacts to be wished for, each role has to rely on their own and play around it's powers.
    * Put in measures to make the roles feel different or have noticeable strengths and weakness that carry through the entire game.
    * Racial bonuses and penalties for armors
    * New special mechanics for roles.
8) Make it easy to variant-hop
   * The player should be able to easily transition from Vanilla NetHack to NerfHack. We hope players don't have to think too much about the changes. Most of the mechanics are designed to be understood intuitively based on game feedback.
   * Don't require the player to memorize or lookup large tables of information (ex: forging recipes, tinker mechanics, object materials, object properties, gem alchemy, potion fermentation, etc, etc, etc)
   * Don't change anything major in the interface or functionality.
   * Don't introduce any new #extended commands (other than wiz-mode tools)
   * Don't change any monster letters
9)  Stay current with upstream NetHack and contribute issues and bug-fixes back when possible.

There are definitely some changes that the player should know about, however, we will leave it up to the individual to decide what those are. The thrill of discovery should not be spoiled.

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