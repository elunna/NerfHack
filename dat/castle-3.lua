-- NetHack castle castle.lua	$NHDT-Date: 1652196024 2022/05/10 15:20:24 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.7 $
--	Copyright (c) 1989 by Jean-Christophe Collet
-- NetHack may be freely redistributed.  See license for details.
--
--
-- Ported from UnNetHack
-- Author: Pasi Kallinen
-- Converted to lua by hackemslashem
--
-- This is the stronghold level :
-- there are several ways to enter it :
--    - opening the drawbridge (wand of opening, knock spell, playing
--      the appropriate tune)
--
--    - enter via the back entry (this suppose a ring of levitation, boots
--      of water walking, etc.)
--
-- Note : If you don't play the right tune, you get indications like in the
--     MasterMind game...
--
-- To motivate the player : there are 4 storerooms (armors, weapons, food and
-- gems) and a wand of wishing in one of the 4 towers...
--
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "noteleport", "noflipy", "graveyard")

--0         1         2         3         4         5         6         7     
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00---------------------------------------------.LLLLLLL.......................
01|...S..S..|..S..S.......|.|.......|f...S..F.S.LLLLLL........................
02|.|---F-F---F-F--.......+.+.......|....|-----LLLLLLLL.............------....
03|.S.|...........+.......|.|.......|....|...LLLLLLL.LLLLL..L.......|....|....
04|.|.F...........---------+---------+----LLLLLLL.......LLLL........+.|..|....
05|.|-|.\.........+...................|.LLLLL....L.....LLLL.........|....|....
06|.|.F...........---------------------LLLLLL............LLLL.......------....
07|.S.|...........+...FLLLLLLLLLLLLL.LLLLL.LLLL...L.......LLLLL...............
08|.|---F--F-F--F-|...FLL.....LLLLLLLLLL.....LLLL..L....LLLLLLLLL.............
09|...|..|..|..|..S...FL.L...L...LLLLLLL........LLLL.LLLLLLL.LLLLLLL......LLLL
10|.{.-S--S---S--S|...FLL......LLLL-------S-------LLLLLLL-------LLL.LLLLLLLLLL
11|...............|----LLLL...LL..L| - - - - - - - - LL- - - - |LL-LLLLLLLLLLL
12|.-+--+--+-------LLLLLLLLLLL.....|-----------------LLL-------LL---LLLLLLLLLL
13|.|..|..|..F...LLL..........L....| - - - - - - - - -L- - - - - - |...LLLLLLL
14|+--F--F----LLLL...---------L-----------------------------------------LL.LL.
15|..FL....LLLLLL....| - - - - - - - - - - - - - - - - - - - - - - - - LL.....
16----LLLLLLL...LL...|-------------------------------------------------|......
17LLLLLLLLLLL........+ - - - - - - - - - - - - - - - - - - - - - - - - S......
18LLLLLLLL..LL.......|-------------------------------------------------|......
19LLLLLL.............| - - - - - - - - - - - - - - - - - - - - - - - - |......
20LLLL...............---------------------------------------------------......
]]);

-- Random registers initialisation
local object = { "[", ")", "*", "%" };
shuffle(object)

-- Random registers initialization
local places = { {05,01},{09,01},{11,01},{15,01},
                 {03,03},
                 {03,07},
                 {05,06},{08,09},{12,09},{14,09},
                 {02,15}}
 -- Prisoners appear at {03,13}, {06,13}, {10,13}
shuffle(places)

local monster = { "L", "L", "E", "E", "R", "R", "T", "T", "O", "O" }
shuffle(monster)

des.teleport_region({ region = {33,15,68,20}, region_islev=1, exclude={10,00,18,14}, dir="up" })
des.teleport_region({ region = {47,01,75,09}, region_islev=1, exclude={17,00,44,09}, dir="down" })

-- Stairs
des.levregion({ region = {33,15,68,20}, region_islev=1, exclude={00,00,00,00}, type="stair-up" })

-- castle is non-diggable
des.non_diggable(selection.area(00,00,18,20))
des.non_diggable(selection.area(00,00,75,09))

-- Subrooms:
--   Entire castle area
des.region(selection.area(00,00,75,20),"lit")

-- the maze is dark
des.region(selection.area(20,15,68,20),"unlit")
des.region(selection.area(34,11,60,14),"unlit")
des.region(selection.area(60,13,64,14),"unlit")

-- the hallways in the castle are dark
des.region(selection.area(17,05,35,05),"unlit")
des.region(selection.area(25,00,25,04),"unlit")

des.region(selection.area(01,01,03,01),"unlit")
des.region(selection.area(01,01,01,13),"unlit")
des.region(selection.area(01,09,03,11),"unlit")
des.region(selection.area(01,11,15,11),"unlit")

--   Throne room
des.region({ region={05,03,15,07},lit=1,type="throne", filled=2 })

-- the special rooms in the castle
des.region({ region={17,01,23,03},lit=1,type="barracks", filled=1 })
des.region({ region={27,01,33,03},lit=1,type="barracks", filled=1 })
des.region({ region={17,07,19,10},lit=1,type="barracks", filled=1 })

-- Dragon lair to the side
des.region({ region={66,02, 71,06}, lit=0, type="dragon lair", filled=1 })

des.mazewalk(33,13,"east")

des.feature("fountain", 02,10)

des.drawbridge({ dir="north", state="closed", x=25,y=07})

-- the castle doors
des.door("locked",39,01)
des.door("locked",35,04)
des.door("locked",26,02)
des.door("locked",24,02)
des.door("locked",25,04)
des.door("locked",16,01)
des.door("locked",16,03)
des.door("locked",16,05)
des.door("locked",16,07)
des.door("locked",16,09)
des.door("locked",15,10)
des.door("locked",13,01)
des.door("locked",12,10)
des.door("locked",09,12)
des.door("locked",08,10)
des.door("locked",07,01)
des.door("locked",06,12)
des.door("locked",05,10)
des.door("locked",04,01)
des.door("locked",03,12)
des.door("locked",02,03)
des.door("locked",02,07)
des.door("locked",01,14)

-- door of the small building
des.door("random",66,04)

-- doors for the maze
des.door("locked",69,17)
des.door("locked",40,10)
des.door("locked",19,17)

des.trap("hole",69,04)
des.trap("trap door",33,05)
des.trap("trap door",41,01)

-- lord of the keep
des.monster({ class = "T", x=06,y=05,peaceful=0,asleep=1})

-- monsters in attendance
des.monster({ class = monster[0], x = 15, y = 04 })
des.monster({ class = monster[0], x = 13, y = 04 })
des.monster({ class = monster[0], x = 11, y = 04 })
des.monster({ class = monster[1], x = 09, y = 04 })
des.monster({ class = monster[1], x = 07, y = 04 })
des.monster({ class = monster[2], x = 15, y = 06 })
des.monster({ class = monster[2], x = 13, y = 06 })
des.monster({ class = monster[3], x = 11, y = 06 })
des.monster({ class = monster[4], x = 09, y = 06 })
des.monster({ class = monster[5], x = 07, y = 06 })

-- monsters behind the bars
des.monster({ id = "iron golem", coord = places[1], peaceful=0,asleep=1 })
des.monster({ id = "iron golem", coord = places[2], peaceful=0,asleep=1 })
des.monster({ id = "iron golem", coord = places[3], peaceful=0,asleep=1 })

des.monster({ class = "D", coord = places[4] })
des.monster({ class = "D", coord = places[5] })
des.monster({ class = "D", coord = places[6] })
des.monster({ class = "D", coord = places[7] })
des.monster({ class = "D", coord = places[8] })
des.monster({ class = "D", coord = places[9] })

-- the prisoners
-- des.monster({ id = "prisoner", x = 02, y = 15, peaceful=1,asleep=1 })
des.monster({ id = "prisoner", x = 03, y = 13, peaceful=1 })
des.monster("prisoner",06,13)
des.monster("prisoner",10,13)

des.monster({ id = "fire giant", x = 36, y = 03, peaceful=1 })
des.monster({ id = "ochre jelly", x = 43, y = 01, asleep=1 })

-- treasure
des.object({ id = "chest", trapped = 0, locked = 1, coord = places[1] ,
             contents = function()
                -- This is converted into a zappable scroll of wishing
                des.object("wishing");
             end
});

-- Prevent monsters from eating it.  (@'s never eat objects)
des.engraving({ coord = loc, type="burn", text="Elbereth" })
des.object({ id = "scroll of scare monster", coord = loc, buc="cursed" })

des.object({ id = "chest", coord = places[2] })
des.object({ id = "chest", coord = places[3] })
des.object({ id = "chest", coord = places[4] })
des.object({ id = "chest", coord = places[5] })
des.object({ id = "chest", coord = places[6] })
des.object({ id = "chest", coord = places[7] })

-- Guaranteed to be empty.
des.object({ id = "chest", locked = 1, coord = places[8],
             contents = function()
             end
});
des.object({ id = "chest", locked = 1, coord = places[9],
             contents = function()
             end
});
des.object({ id = "chest", locked = 1, coord = places[10] ,
             contents = function()
             end
});

-- the soldiers' equipment; also doubles as a reward for player

-- NW barracks
des.object("[",17,01)
des.object("[",19,01)
des.object("[",20,01)
des.object("[",22,01)
des.object("[",19,02)
des.object("[",21,02)
des.object("[",22,02)
des.object("[",17,03)
des.object("[",18,03)
des.object("[",20,03)
des.object("[",21,03)
des.object(")",18,01)
des.object(")",21,01)
des.object(")",17,02)
des.object(")",18,02)
des.object(")",20,02)
des.object(")",19,03)
des.object(")",22,03)

-- NE barracks
des.object("[",29,01)
des.object("[",30,01)
des.object("[",32,01)
des.object("[",33,01)
des.object("[",31,02)
des.object("[",32,02)
des.object("[",33,02)
des.object("[",28,03)
des.object("[",30,03)
des.object("[",31,03)
des.object("[",33,03)
des.object(")",28,01)
des.object(")",31,01)
des.object(")",28,02)
des.object(")",29,02)
des.object(")",30,02)
des.object(")",29,03)
des.object(")",32,03)

-- the items in the barracks with iron bars, facing the drawbridge
des.object("arrow",18,07)
des.object("arrow",18,08)
des.object("arrow",18,09)
des.object("arrow",18,10)
des.object("orcish arrow",18,07)
des.object({ id = "elven arrow", x = 18, y = 08, buc="blessed", spe=2 })
des.object({ id = "elven arrow", x = 18, y = 09, buc="blessed", spe=3 })
des.object("orcish arrow",18,10)
des.object({ id = "orcish bow", x = 18, y = 07, buc="blessed", spe=1 })
des.object({ id = "elven bow", x = 18, y = 08, buc="blessed" })
des.object("elven bow",18,09)
des.object("orcish bow",18,10)

-- some boulders on the island
des.object("boulder",45,06)
des.object("boulder",51,08)
des.object("boulder",51,06)

-- polearms for poking the captured monsters
des.object("partisan",09,03)
des.object("ranseur",11,03)
des.object("spetum",08,07)
des.object("bill-guisarme",12,07)