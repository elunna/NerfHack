-- NetHack sokoban soko3-2.lua	$NHDT-Date: 1652196036 2022/05/10 15:20:36 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- https://nethackwiki.com/wiki/Sokoban_Level_1l

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
          ----      
       ---|..----   
       |..|.....|---
 ----  |.....|..|..|
 |..----.|...|.....|
 |...........|--...|
 |.--F--...|.|....--
 |.|...|-.-|......| 
 |.F.L.+...|......| 
--.|...|........--- 
|..--F-----.|.---   
|.........|...|     
---------------     
]]);

des.stair("down", 12,09)
des.stair("up", 09,11)
des.region(selection.area(00,00,19,12), "lit")
des.non_diggable(selection.area(00,00,19,12))
des.non_passwall(selection.area(00,00,19,12))

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=30 })

des.door("locked",07,08)

-- Boulders
des.object("boulder",14,02)
des.object("boulder",12,03)
des.object("boulder",14,03)
des.object("boulder",17,04)
des.object("boulder",16,05)
des.object("boulder",12,06)
des.object("boulder",16,06)
des.object("boulder",09,07)
des.object("boulder",13,07)
des.object("boulder",14,07)
des.object("boulder",16,08)
des.object("boulder",09,09)
des.object("boulder",13,09)
des.object("boulder",11,10)

-- Traps
des.trap("hole",05,05)
des.trap("hole",06,05)
des.trap("hole",07,05)
des.trap("hole",02,06)
des.trap("hole",02,07)
des.trap("hole",02,08)
des.trap("hole",02,09)
des.trap("hole",03,11)
des.trap("hole",04,11)
des.trap("hole",05,11)
des.trap("hole",06,11)
des.trap("hole",07,11)
des.trap("hole",08,11)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")