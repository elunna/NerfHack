-- # Bottom most stage of Vlad's tower
-- MAZE:"tower3",' '

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "solidify"")

--0         1         2         3         4         5
--01234567890123456789012345678901234567890123456789012345
des.map({ halign = "half-left", valign = "center", map = [[
00-----------  --- ---   ------   --- ---  -----------
01|.........|  |.| |.|  -|....|-  |.| |.|  |.........|
02|...---...|---S---S---|......|---S---S---|...---...|
03|.........|...........S......S.....................|
04|...---...|...........|......|...............---...|
05|.........|--+----F----|....|----F-------|.........|
06-FF-...-FF-...|........--FF--........|...-FF-...-FF-
07 ..F...F......F.............................F...F.. 
08 ..F...F......F.............................F...F.. 
09-FF-...-FF-...|........--++--........|...-FF-...-FF-
10|.........|--+----F----|....|----F-------|.........|
11|...---...............F......|...............---...|
12|.....................F......S.....................|
13|...---...|---S---S---|......|---S---S---|...---...|
14|.........|  |.| |.|  -|....|-  |.| |.|  |.........|
15-----------  --- ---   ------   --- ---  -----------
]] });

-- Random 8 niches
local niches = { {14,01}, {18,01}, {33,01}, {37,01},
                 {14,14}, {18,14}, {33,14}, {37,14} }
shuffle(niches);

-- des.ladder("down", 05,03)
des.levregion({ type="branch", region={05,03,05,03} })
des.ladder("up", 43,07)

-- # Locked doors
des.door("locked",13,05)
des.door("locked",13,10)
des.door("locked",25,09)
des.door("locked",26,09)
des.door("locked",22,03)
des.door("locked",29,03)
des.door("locked",29,12)

-- # Gargoyles in the four corners
des.monster("winged gargoyle", 01,01)
des.monster("winged gargoyle", 01,14)
des.monster("winged gargoyle", 50,01)
des.monster("winged gargoyle", 50,14)

-- # Zombies and skeletons patrol the hallways
des.monster("human zombie", 13,03)
des.monster("human zombie", 32,03)
des.monster("human zombie", 34,04)
des.monster("human zombie", 13,11)
des.monster("human zombie", 32,11)
des.monster("human zombie", 34,12)
des.monster("ettin zombie", 14,04)
des.monster("ettin zombie", 14,12)
des.monster("giant zombie", 16,04)
des.monster("giant zombie", 36,04)
des.monster("giant zombie", 16,12)
des.monster("giant zombie", 36,12)

-- Were skeleton warriors in EvilHack
des.monster("skeleton", 15,03)
des.monster("skeleton", 35,03)
des.monster("skeleton", 15,11)
des.monster("skeleton", 35,11)

-- # Liches reside in the center chambers
-- # along with some noncorporeal undead
des.monster("L", 26,03)
des.monster("L", 26,12)
des.monster(" ", 25,03)
des.monster(" ", 25,12)

-- # The lycan horde guards the very center
-- # with their vampire masters
des.monster("weredemon", 17,08)
des.monster("weredemon", 18,07)
des.monster("weredemon", 18,08)
des.monster("weredemon", 33,07)
des.monster("weredemon", 33,08)
des.monster("weredemon", 34,07)
des.monster("werewolf", 17,07)
des.monster("werewolf", 19,07)
des.monster("werewolf", 19,08)
des.monster("werewolf", 32,07)
des.monster("werewolf", 32,08)
des.monster("werewolf", 34,08)

des.monster("vampire lord", 42,07)
des.monster("vampire lord", 42,08)

-- What is Vlad keeping in the closet??
local prisoners = {
    "orb weaver", "third eye", "glowing eye", "prisoner",
    "couatl", "eye of fear and flame", "pyrolisk", "barghest",
    "monstrous spider", "worm that walks", "hunger hulk",
    "black dragon", "green dragon", "yellow dragon", "shimmering dragon",
 };
shuffle(prisoners)
des.monster({ id = prisoners[1], x = 01, y = 07, peaceful=0 })
des.monster({ id = prisoners[2], x = 01, y = 08, peaceful=0 })
des.monster({ id = prisoners[3], x = 50, y = 07, peaceful=0 })
des.monster({ id = prisoners[4], x = 50, y = 08, peaceful=0 })
-- These guys will take cheap pot-shots
des.monster({ id = prisoners[5], x = 10, y = 07, peaceful=0 })
des.monster({ id = prisoners[5], x = 10, y = 08, peaceful=0 })
des.monster({ id = prisoners[6], x = 43, y = 07, peaceful=0 })
des.monster({ id = prisoners[6], x = 43, y = 08, peaceful=0 })

-- # Random objects and traps in the niches
des.object({ id = "long sword", coord = niches[1] });
des.trap({ coord = niches[1] })

des.object({ id = "lock pick", coord = niches[2] });
des.trap({ coord = niches[2] })

des.object({ id = "elven cloak", coord = niches[3] });
des.trap({ coord = niches[3] })

des.object({ id = "blindfold", coord = niches[4] });
des.trap({ coord = niches[4] })

des.object({ id = "ring of levitation", coord = niches[5] });
des.trap({ coord = niches[5] })

des.object({ id = "chest", coord = niches[6] });
des.trap({ coord = niches[6] })

-- # Random corpses of past adventurers
des.object({ id="corpse", montype="wizard" })
des.object({ id="corpse", montype="samurai" })
des.object({ id="corpse", montype="barbarian" })
des.object({ id="corpse", montype="undead slayer" })
des.object({ id="corpse", montype="knight" })
des.object({ id="corpse", montype="cartomancer" })
des.object({ id="corpse", montype="rogue" })
des.object({ id="corpse", montype="valkyrie" })
des.object({ id="corpse", montype="healer" })

-- # Some random traps
des.trap()
des.trap()
des.trap()
des.trap()

-- Walls in the tower are non diggable and non passable
des.non_diggable(selection.area(00,00,51,15))
