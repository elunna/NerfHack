-- NetHack sokoban soko3-2.lua	$NHDT-Date: 1652196036 2022/05/10 15:20:36 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- https://nethackwiki.com/wiki/Sokoban_Level_1n

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
----------------    
|...|..|.|.--..|    
|.|.|..........---  
|.|....--FF--....---
|...|..|....|......|
--.-|.-|.FF.|......|
 |.||.|-....--.--.--
 |.FF.FL....LF.FF.| 
 |.||.|--..--|.||.| 
--.--.--|..|-|.||.| 
|......||..|--.--.--
|......-|..|-......|
|.......|..|..---..|
-----..............|
    |.|....|..|...--
    --------------- 
]]);

des.stair("down", 08,01)
des.stair("up", 08,04)
des.region(selection.area(00,00,19,15), "lit")
des.non_diggable(selection.area(00,00,19,15))
des.non_passwall(selection.area(00,00,19,15))

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Boulders
des.object("boulder",07,02)
des.object("boulder",12,02)
des.object("boulder",14,03)
des.object("boulder",15,04)
des.object("boulder",16,04)
des.object("boulder",02,05)
des.object("boulder",05,05)
des.object("boulder",14,10)
des.object("boulder",17,10)
des.object("boulder",03,11)
des.object("boulder",04,11)
des.object("boulder",02,12)
des.object("boulder",05,12)
des.object("boulder",07,13)
des.object("boulder",11,13)
des.object("boulder",16,13)

-- Traps
des.trap("hole",08,05)
des.trap("hole",11,05)
des.trap("hole",08,06)
des.trap("hole",09,06)
des.trap("hole",10,06)
des.trap("hole",11,06)
des.trap("hole",08,07)
des.trap("hole",09,07)
des.trap("hole",10,07)
des.trap("hole",11,07)
des.trap("hole",09,08)
des.trap("hole",10,08)
des.trap("hole",09,09)
des.trap("hole",10,09)
des.trap("hole",09,10)
des.trap("hole",10,10)
des.trap("hole",09,11)
des.trap("hole",10,11)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")