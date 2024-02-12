-- NetHack sokoban soko3-2.lua	$NHDT-Date: 1652196036 2022/05/10 15:20:36 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- https://nethackwiki.com/wiki/Sokoban_Level_1k

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
----------------- 
|........F......| 
|..--....F......| 
--.|.....F......| 
 |.---------.--.| 
 |...........||.| 
 |..------...--.--
 ----    |.......|
       ---.----.--
       |........| 
       |....----- 
       --...|     
        -----     
]]);

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=30 })

des.stair("down", 16,07)
des.stair("up", 04,03)

des.region(selection.area(00,00,17,12), "lit")
des.non_diggable(selection.area(00,00,17,12))
des.non_passwall(selection.area(00,00,17,12))

-- Boulders
des.object("boulder",12,02)
des.object("boulder",14,02)
des.object("boulder",11,03)
des.object("boulder",13,03)
des.object("boulder",11,06)
des.object("boulder",12,06)
des.object("boulder",11,07)
des.object("boulder",09,09)
des.object("boulder",11,09)
des.object("boulder",10,10)

-- Traps
des.trap("hole",03,01)
des.trap("hole",04,01)
des.trap("hole",02,03)
des.trap("hole",02,04)
des.trap("hole",04,05)
des.trap("hole",05,05)
des.trap("hole",06,05)
des.trap("hole",07,05)
des.trap("hole",08,05)
des.trap("hole",09,05)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")