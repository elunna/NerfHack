--       SCCS Id: @(#)Slayer.des 3.4     1992/09/22
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--    The "start" level for the quest.
--
--    Here you meet your (besieged) class leader, High Priest
--    and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = "," });

des.level_flags("mazelevel", "noteleport", "hardfloor", "graveyard", "noflip")

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
01,-----,,-----,,-----,,-------,T,T,T,T,T,T,T,T,T,T,
02,|...|,,|...|,,|...|,,|.....|,,,,,,,,,,,,,,,,,,,,,
03,---+-..--+--..--+--..|.....|,T,T,T,T,T,T,T,T,T,T,
04,.....................|.....|,,,,,,,,,,,,,,,,,,,,,
05,|-|..................|.....|,T,T,T,T,|---------|,
06,|.|..................---+---,,,,,,,,,|.........|,
07,|.+..................................+.........|,
08,|.|......................,,,,,,,,,,,.|.........|,
09,|-|.....................,,,,,,,,,,,,.|---------|,
10,,...................|-|,,,,,,,,,,,,,...........F,
11,--+-................+.|,,,,,,,,,,,,,,F.........F,
12,|..|.--+--..--+--...|.|,,,,,,,,,,,,,,F.........F,
13,|..|,|...|,,|...|,,,|.|,,,,,,,,,,,,,,F.........F,
14,----,-----,,-----,,,|-|,,,,,,,,,,,,,,FFFFFFFFFFF,
15,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
]]);

--# Random Monsters
-- RANDOM_MONSTERS: 'Z', 'W', 'V', 'M'

-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
des.region({ region={24,06, 33,13}, lit=1, type="temple", filled=2 })

-- Portal arrival point
des.levregion({ region = {01,01,14,17}, exclude = {04,03,20,11}, type="branch" })

-- Stairs
des.stair("down", 47,07)

-- Doors
des.door("random",04,03)
des.door("random",10,03)
des.door("random",17,03)

des.door("random",03,07)
des.door("random",11,07)

des.door("random",25,06)

des.door("random",08,12)
des.door("random",15,12)

des.door("random",21,11)

des.door("random",38,07)


-- Unattended Altar - unaligned due to conflict - player must align it.
des.altar({ x=25, y=03, align="noalign", type="altar", cracked=1 })

des.region({ region={39,10,47,13}, lit=0, type="morgue", filled=1 })

-- Your quest leader
des.monster({ id = "Van Helsing", coord = {28, 10}, inventory = function()
   des.object({ id = "leather jacket", spe = 4 });
   des.object({ id = "wooden stake", spe = 4 });
end })

-- The treasure of Van Helsing
des.object("chest", 27, 10)

-- knight guards for the audience chamber
des.monster("exterminator", 32, 07)
des.monster("exterminator", 32, 08)
des.monster("exterminator", 32, 11)
des.monster("exterminator", 32, 12)
des.monster("exterminator", 33, 07)
des.monster("exterminator", 33, 08)
des.monster("exterminator", 33, 11)
des.monster("exterminator", 33, 12)

-- Non diggable walls
des.non_diggable(selection.area(18,03,55,16))

-- Random traps
for i = 1, 2 do
   des.trap("dart")
end
des.trap()
des.trap()
des.trap()
des.trap()

-- Monsters on siege duty.
for i = 1, 12 do
   des.monster("M");
end