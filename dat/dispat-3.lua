-- SCCS Id: @(#)gehennom.des	3.4	1996/11/09
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
--
-- The Dispater level
--
-- Based upon Tom Proudfoots Slash'em Dispater level
--
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem
--
-- Dispaters origins are in the Roman god of the underworld.
-- originally Dis Pater (rich father) he is associated with
-- wealth (naturally found underground).
--

des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor")

des.map({ halign = "right", valign = "center", map = [[
              }}}}                               
---------       }}}}    ..        ....     ------
|...|.S.|     ..}}}}. .....     .......----|.S..|
|.|S|.|S|    ..}}}}..  ....    .. .... |...----.|
|.|...|.|    .}}}}..      ..  ..       |...S..|.|
|.-------..  .}}}}.     ........    ----S----.|.|
|.|.....|......}}}}..........  -----|.....|.S.|.|
|.|.--|.|.......}}}}...... .   |....+.....|.|.|.|
|.|...|S|  ...  }}}}.....  .|---+-----S---|.|.S.|
-S-S|.|.|....  }}}}   ... ..+............ |S---.|
....|S--|S|....}}}}  ...... | .........\..F...|.|
-S-S|...|.|.....}}}}....  ..+............ |----S|
|.|.|.|.|S| ... }}}}.....  .|---+-----S---|..S..|
|.|.|.|.|.| ..  }}}} ..... ..  |....+.....|-----|
|.|...|...|  ..}}}}.... ..  .. -----|.....S....| 
|.---------  .}}}}...    .. ..      -------....| 
|.....|     .. }}}}...  .....  ...  .... .+....| 
|----.|    ....}}}} .. .. ...... .... ....------ 
|.S...|      .}}}}...   .....      .....         
-------        }}}}                              
]] });

des.region(selection.area(00,00,48,19), "unlit");

-- Branch and Teleport points
des.levregion({ region = {01,00,74,19}, region_islev=1, exclude={26,00,74,19}, exclude_islev=1, type="stair-up" })
des.levregion({ region = {01,00,74,19}, region_islev=1, exclude={26,00,74,19}, exclude_islev=1, type="branch" })
des.teleport_region({region={01,00,74,19}, exclude = {26,00,74,19} })

-- Protect the walls
des.non_diggable(selection.area(00,00,48,19))
des.non_passwall(selection.area(00,00,48,19));

-- Maze the rest of the level
des.mazewalk(00,10,"west")

-- Stairs
des.stair("down", 43,12)

-- Doors
des.door("locked",01,09)
des.door("locked",03,09)
des.door("locked",01,11)
des.door("locked",03,11)
des.door("locked",05,10)
des.door("locked",07,08)
des.door("locked",09,10)
des.door("locked",09,12)
des.door("locked",02,18)
des.door("locked",03,03)
des.door("locked",06,02)
des.door("locked",07,03)
des.door("locked",28,09)
des.door("locked",28,11)
des.door("locked",32,08)
des.door("locked",32,12)
des.door("locked",38,08)
des.door("locked",38,12)
des.door("locked",36,07)
des.door("locked",36,13)
des.door("locked",40,05)
des.door("locked",43,04)
des.door("locked",45,02)
des.door("locked",44,06)
des.door("locked",46,08)
des.door("locked",43,09)
des.door("locked",47,11)
des.door("locked",45,12)
des.door("locked",42,14)
des.door("locked",42,16)

-- Some random money
des.gold();
des.gold();
des.gold();
des.gold();
des.gold();
des.gold();
des.gold();
des.gold();
des.gold();
des.gold();

-- Some random gems
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")

-- Some random traps
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")

-- Gold in the outer vaults
des.monster("gold golem",07,04)
des.object({ x = 07, y = 04 })
des.monster("gold golem",07,02)
des.object({ x = 07, y = 02 })
des.monster("gold golem",03,04)
des.object({ x = 03, y = 04 })
des.monster("gold golem",07,09)
des.object({ x = 07, y = 09 })
des.monster("gold golem",01,18)
des.object({ x = 01, y = 18 })
des.monster("gold golem",09,11)
des.object({ x = 09, y = 11 })

-- A river of gold?
des.gold({ x = 15, y = 02 });
des.gold({ x = 14, y = 03 });
des.gold({ x = 13, y = 05 });
des.gold({ x = 14, y = 06 });
des.gold({ x = 15, y = 07 });
des.gold({ x = 14, y = 10 });
des.gold({ x = 15, y = 11 });
des.gold({ x = 14, y = 14 });
des.gold({ x = 13, y = 15 });
des.gold({ x = 14, y = 17 });
des.gold({ x = 13, y = 18 });
des.gold({ x = 20, y = 02 });
des.gold({ x = 19, y = 03 });
des.gold({ x = 18, y = 04 });
des.gold({ x = 19, y = 06 });
des.gold({ x = 20, y = 07 });
des.gold({ x = 21, y = 08 });
des.gold({ x = 20, y = 11 });
des.gold({ x = 20, y = 12 });
des.gold({ x = 19, y = 14 });
des.gold({ x = 18, y = 15 });
des.gold({ x = 19, y = 16 });
des.gold({ x = 18, y = 18 });

-- Outer Guardians
-- MONSTER:''',"crystal golem",(11,06)
-- MONSTER:''',"ruby golem",(12,11)
-- MONSTER:''',"sapphire golem",(13,04)
-- MONSTER:''',"diamond golem",(13,15)
des.monster("iron golem",11,06)
des.monster("iron golem",12,11)
des.monster("iron golem",13,04)
des.monster("iron golem",13,15)

-- Fishies in the river
des.monster(";",17,02)
des.monster(";",15,05)
des.monster(";",18,08)
des.monster(";",17,11)
des.monster(";",16,14)
des.monster(";",17,17)

-- Nearside Guardians
-- MONSTER:''',"ruby golem",(26,04)
-- MONSTER:''',"ruby golem",(25,15)
-- MONSTER:''',"sapphire golem",(29,05)
-- MONSTER:''',"sapphire golem",(27,13)
-- MONSTER:''',"diamond golem",(25,10)
des.monster("iron golem",26,04)
des.monster("iron golem",25,15)
des.monster("iron golem",29,05)
des.monster("iron golem",27,13)
des.monster("iron golem",25,10)

-- The fellow in residence
des.monster({id="Dispater", x=39, y=10})

-- His court
des.monster({ id = "nalfeshnee", x=38, y=09, peaceful=0, asleep = 1 })
des.monster({ id = "nalfeshnee", x=38, y=11, peaceful=0, asleep = 1 })
des.monster({ id = "succubus", x=39, y=09, peaceful=0, asleep = 1 })
des.monster({ id = "incubus", x=39, y=11, peaceful=0, asleep = 1 })
--MONSTER:''',"diamond golem",(35,09),asleep,hostile
--MONSTER:''',"diamond golem",(35,11),asleep,hostile
des.monster({ id = "iron golem", x=35, y=09, peaceful=0, asleep = 1 })
des.monster({ id = "iron golem", x=35, y=11, peaceful=0, asleep = 1 })

-- His guards
des.monster({ id = "ice devil", x=31, y=09, peaceful=0, asleep = 1 })
des.monster({ id = "ice devil", x=33, y=09, peaceful=0, asleep = 1 })
des.monster({ id = "ice devil", x=31, y=11, peaceful=0, asleep = 1 })
des.monster({ id = "ice devil", x=31, y=11, peaceful=0, asleep = 1 })
des.monster({ id = "ice devil", x=30, y=10, peaceful=0, asleep = 1 })

-- Some doorbells
des.trap("board", 27,09)
des.trap("board", 27,11)
des.trap("board", 29,09)
des.trap("board", 29,09)
des.trap("board", 32,09)
des.trap("board", 32,11)

-- Traps for the unwary
des.trap("anti magic", 32,07)
des.trap("anti magic", 32,13)
des.trap("magic", 33,07)
des.trap("magic", 33,13)
des.trap("polymorph", 34,07)
des.trap("polymorph", 34,13)
des.trap("magic", 35,07)
des.trap("magic", 35,13)
des.trap("fire", 37,07)
des.trap("fire", 37,13)

-- Northern antichamber
des.monster("&",40,07)
des.monster("&",38,06)
des.object("chest",41,06)
des.object("chest",41,07)

-- Southern antichamber
des.monster("&",40,13)
des.monster("&",38,14)
des.object("chest",41,14)
des.object("chest",41,13)

-- Escape Room
des.trap("polymorph", 44,15)
des.trap("magic", 45,15)

-- MONSTER:''',"diamond golem",(43,15),asleep,hostile
des.monster({ id = "iron golem", x=43, y=15, peaceful=0, asleep = 1 })

-- Northern Vault
des.trap("board", 40,04)

des.gold({ x = 40, y = 03 });
des.object("*",40,03)
des.object("*",40,03)

des.gold({ x = 41, y = 03 });
des.object("*",41,03)
des.object("*",41,03)

des.gold({ x = 42, y = 03 });
des.object("*",42,03)
des.object("*",42,03)

des.gold({ x = 40, y = 04 });
des.object("*",40,04)
des.object("*",40,04)

des.gold({ x = 41, y = 04 });
des.object("*",41,04)
des.object("*",41,04)

des.gold({ x = 42, y = 04 });
des.object("*",42,04)
des.object("*",42,04)

des.monster("giant mimic",42,04)

-- Animate Gold
des.monster("gold golem",43,07)
des.monster("gold golem",45,06)
des.monster("gold golem",47,04)
des.monster("gold golem",47,12)

-- Exit chamber (and ref to old TV show - Saphire and Steel)
--MONSTER:''',"sapphire golem",()
--MONSTER:''',"steel golem",()
des.monster("gold golem",44,12)
des.monster("iron golem",43,12)

des.gold({ x = 43, y = 12 });
des.gold({ x = 44, y = 12 });
des.gold({ x = 46, y = 12 });
des.gold({ x = 47, y = 12 });

-- Barred Vault
--MONSTER:''',"sapphire golem",(43,10)
--MONSTER:''',"sapphire golem",(44,10)
--MONSTER:''',"sapphire golem",(45,10)
des.monster("gold golem",43,10)
des.monster("gold golem",44,10)
des.monster("gold golem",45,10)
des.gold({ x = 43, y = 10 });
des.gold({ x = 44, y = 10 });
des.gold({ x = 45, y = 10 });

des.object("diamond",43,10)
des.object("ruby",43,10)
des.object("loadstone",43,10)
des.object("emerald",43,10)
des.object("sapphire",43,10)
des.object("amethyst",44,10)
des.object("jade",44,10)
des.object("opal",44,10)
des.object("luckstone",44,10)
des.object("jacinth",44,10)
des.object("aquamarine",45,10)
des.object("fluorite",45,10)
des.object("loadstone",45,10)
des.object("jasper",45,10)
des.object("citrine",45,10)
