-- NetHack castle castle.lua	$NHDT-Date: 1652196024 2022/05/10 15:20:24 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.7 $
--	Copyright (c) 1989 by Jean-Christophe Collet
-- NetHack may be freely redistributed.  See license for details.
--
--
-- Ported from UnNetHack
-- Author: Pasi Kallinen
-- Converted to lua by hackemslashem
--
-- This is the stronghold level
-- The thick walls on the corners of the armouries and the dragon pens
-- are a kludge to prevent the walls showing up through the iron bars from
-- outside the castle.
--

des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "noteleport", "noflipy", "graveyard")
--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00T...}}}}}}}}}..}}}}}}}}}}}}}}}}}}}}}..}}...}}}}}}}}}}}}}....T.....}}}}...T..
01...}}}}}}}}}}}}}}}}}}..}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}.......}}}}}}}.....
02.}}..}}}----------------------------------------------}}}}}}}..---------S---
03}}}}....F...-|.........|........|......S......+......|}}}}}}}}}| - - - - - -
04}}}}.}}}|....|.........+........|......--------......|}.}}}}}}}|------------
05}}}..}}}|....+.........|........+......|......|-.....|}..}}}}}.S - - - - - -
06}}}.T.}}|....|----------........|......|......--FFFF--}}}}}}}}.|------------
07}}}...}}|----|...f...|..........|......|......|}}}}}}}}}}}.....| - - - - - -
08}}}}}}}}|....|.LLLLL.|..........--FFFF-|......|}.....}}}....T..|------------
09.}}}}}..|....S.LLLLL.S.\........S......+..{...|}...............| - - - - - -
10T...}.}.|....|.LLLLL.|..........--FFFF-|......|}....}}}...}....|------------
11..}}.}}}|----|...f...|..........|......|......|}}}}}}}}}.}}}...| - - - - - -
12}}}}}.}}|....|----------........|......|......--FFFF--}}}}}....|------------
13}}}}}.}}|....+.........|........+......|......|-.....|}}}}}}}..| - - - - - -
14}}}}....|....|.........+........|......--------......|}}}}}}}}.|------------
15}}}.....F...-|.........|........|......S......+......|}}....}}}| - - - - - -
16}}..}...----------------------------------------------}..}...}}|------------
17}}}}}......}}}}...}}}}}}}..}}......}}}}}}}}}}}}}}}}}}}}.....}}}S - - - - - -
18}}}}}}...}}}}}}}}...}}.}..}}}}.T.}}}}}}}}}...}}}}}.}}}}}}}...}}|------------
19}}}}}}}}}}}}..}}}}}}}}}}.}}}}}}}..}}.}}........}}.}}...}}}}}}}.| - - - - - -
10}}}}}}}}}.....}}}}}}}}}}}}}}}}}}}}}}}}.....T..}}}}}}}}.}}}}}}..-------------
]]);

-- Random registers initialisation
local object = { "[", ")", "*", "%" };
shuffle(object)

-- For placing the real and fake chests for wands of wishing
local place = selection.new();
place:set(09,08);
place:set(09,09);
place:set(09,10);
place:set(52,03);
place:set(52,15);

local monster = { "L", "N", "E", "V", "M", "O", "R", "T", "X", "Z" }
shuffle(monster)

des.teleport_region({ region = {64,03,75,20}, region_islev=1, exclude={07,01,54,17}, dir="down" })
des.teleport_region({ region = {01,01,07,18}, region_islev=1, exclude={07,01,75,20}, dir="up" })

-- Stairs
des.levregion({ region = {66,05,75,20}, region_islev=1, exclude={07,01,66,20}, type="stair-up" })

-- the inner courtyard
des.feature("fountain", 42,09)

des.drawbridge({ dir="west", state="closed", x=47,y=09})
des.door("locked",39,09)

-- doors leading to the dragon pens
des.door("locked",39,03)
des.door("locked",46,03)
des.door("locked",39,15)
des.door("locked",46,15)

-- doors to the throne room
des.door("locked",32,09)

des.door("locked",32,05)
if percent(50) then
    des.door("locked",39,05)
end
des.door("locked",32,13)
if percent(50) then
    des.door("locked",39,13)
end
-- doors to the barracks
des.door("closed",23,04)
des.door("closed",23,14)

-- doors to the armouries
des.door("locked",13,05)
des.door("locked",13,13)

-- Removed so that the castle can be breached with either levitation OR an
-- instrument.
--des.trap("trap door", 38,09);
--des.trap("trap door", 36,09);
--des.trap("trap door", 34,09);

des.trap("trap door", 41,03);
des.trap("trap door", 44,03);
des.trap("trap door", 41,15);
des.trap("trap door", 44,15);

des.mazewalk(63,09,"east")

-- only the inner walls of the maze are diggable
des.non_diggable(selection.area(00,00,63,20))
des.non_diggable(selection.area(63,00,75,02))

-- the maze is unlit
des.region(selection.area(00,00,62,20),"unlit")
des.region(selection.area(63,00,75,01),"unlit")

-- and the dragon pens are unlit
des.region(selection.area(47,03,52,06),"unlit")
des.region(selection.area(47,12,52,15),"unlit")
des.region({ region={24,03,31,15},lit=1,type="throne", filled=2 })
des.region({ region={14,03,22,05},lit=1,type="barracks", filled=1 })
des.region({ region={14,13,22,15},lit=1,type="barracks", filled=1 })

-- the armouries and the treasure room are unlit
des.region(selection.area(09,03,12,15),"unlit")

-- northern armoury
des.object(object[1],09,03)
des.object(object[1],10,03)
des.object(object[1],11,03)
des.object(object[1],09,04)
des.object(object[1],10,04)
des.object(object[1],11,04)
des.object(object[1],12,04)
des.object(object[1],09,05)
des.object(object[1],10,05)
des.object(object[1],11,05)
des.object(object[1],12,05)
des.object(object[1],09,06)
des.object(object[1],10,06)
des.object(object[1],11,06)
des.object(object[1],12,06)

-- southern armoury
des.object(object[2],09,12)
des.object(object[2],10,12)
des.object(object[2],11,12)
des.object(object[2],12,12)
des.object(object[2],09,13)
des.object(object[2],10,13)
des.object(object[2],11,13)
des.object(object[2],12,13)
des.object(object[2],09,14)
des.object(object[2],10,14)
des.object(object[2],11,14)
des.object(object[2],12,14)
des.object(object[2],09,15)
des.object(object[2],10,15)
des.object(object[2],11,15)

-- treasure room
local loc = place:rndcoord(1);

des.object({ id = "chest", trapped = 0, locked = 1, coord = loc ,
             contents = function()
                -- This is converted into a zappable scroll of wishing
                des.object("wishing");
             end
});
-- Prevent monsters from eating it.  (@'s never eat objects)
des.engraving({ coord = loc, type="burn", text="Elbereth" })
des.object({ id = "scroll of scare monster", coord = loc, buc="cursed" })

-- THE NOT QUITE WANDS OF WISHING
-- ...since you can see the chest now through the bars,
-- we have to find a better way to disguise where the wand is
-- From SporkHack

local loc = place:rndcoord(2);
des.object({ id = "chest", locked = 1, coord = loc ,
             contents = function()
                des.object("?");
                des.object("?")
                des.object("?")
                des.object("+")
                des.object("*")
                des.object("*")
             end
});
des.engraving({ coord = loc, type="burn", text="Elbereth" })
des.object({ id = "scroll of scare monster", coord = loc, buc="cursed" })


local loc = place:rndcoord(3);
des.object({ id = "chest", locked = 1, coord = loc ,
             contents = function()
                des.object("?");
                des.object("/")
                des.object('"')
                des.object("*")
                des.object("*")
             end
});
des.engraving({ coord = loc, type="burn", text="Elbereth" })
des.object({ id = "scroll of scare monster", coord = loc, buc="cursed" })

local loc = place:rndcoord(4);
des.object({ id = "chest", locked = 1, coord = loc ,
             contents = function()
                des.object("?");
                des.object("?")
                des.object("?")
                des.object("+")
                des.object("*")
                des.object("*")
                des.object("!")
             end
});
des.engraving({ coord = loc, type="burn", text="Elbereth" })
des.object({ id = "scroll of scare monster", coord = loc, buc="cursed" })

local loc = place:rndcoord(5);
des.object({ id = "chest", locked = 1, coord = loc })

-- statues behind the throne
des.object({ id = "statue", x=22, y=07 })
des.object({ id = "statue", x=22, y=11 })

-- the king (and his adviser[s])
des.monster({ id = "titan", x=23, y=09, peaceful=0,asleep = 1 })
des.monster({ class = "V", x=23, y=08,asleep = 1 })
des.monster({ class = "V", x=23, y=10,asleep = 1 })

-- monsters in the water around the castle
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")

-- monsters in attendance in the throne room
des.monster(monster[1],25,04)
des.monster(monster[2],27,04)
des.monster(monster[3],29,04)
des.monster(monster[4],26,05)
des.monster(monster[5],28,05)
des.monster(monster[6],30,05)
des.monster(monster[7],25,06)
des.monster(monster[8],27,06)
des.monster(monster[9],29,06)
des.monster(monster[1],26,07)
des.monster(monster[2],28,07)
des.monster(monster[3],30,07)
des.monster(monster[4],25,08)
des.monster(monster[5],27,08)
des.monster(monster[6],29,08)

-- Straight line to titan from door here.
des.monster(monster[1],25,14)
des.monster(monster[2],27,14)
des.monster(monster[3],29,14)
des.monster(monster[4],26,13)
des.monster(monster[5],28,13)
des.monster(monster[6],30,13)
des.monster(monster[7],25,12)
des.monster(monster[8],27,12)
des.monster(monster[9],29,12)
des.monster(monster[4],26,11)
des.monster(monster[5],28,11)
des.monster(monster[6],30,11)
des.monster(monster[7],25,10)
des.monster(monster[8],27,10)
des.monster(monster[9],29,10)

-- welcoming committee
des.monster("D",48,05)
des.monster("D",50,04)
des.monster("D",51,13)
des.monster("D",52,14)

-- guardians in the antechamber of the treasure room
des.monster("fire elemental",14,09)
des.monster("fire elemental",17,09)
des.monster("fire vortex",20,09)
des.monster("fire vortex",18,09)

-- sharpshooters in the chambers next to the hallway
des.monster("C",35,06)
des.monster("C",36,04)
des.monster("C",35,11)
des.monster("C",36,12)
des.monster("C",37,13)