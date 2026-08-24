-- NetHack sokoban soko3-2.lua	$NHDT-Date: 1652196036 2022/05/10 15:20:36 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- https://nethackwiki.com/wiki/Stacked_Dozen
-- NetHack Fourk
-- "Stacked Dozen"
-- Map created by karadoc
-- Converted to lua by hackemslashem
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
---------         ------ 
|.......|     ----|....--
|.......|    --..--.....|
|.......|  ---......-.|.|
|.......|  |..........|.|
|.......|  |.....-......|
|+------------.....--...|
|...............|.......|
-------------------------
]]);

des.stair("down", 17,07)
des.stair("up", 04,03)

des.door("locked",01,06)
des.region(selection.area(00,00,24,08), "lit")
des.non_diggable(selection.area(00,00,24,08))
des.non_passwall(selection.area(00,00,24,08))


-- # Spoiler: positions to aim for are as follows:
-- # (19,02),(21,02),(16,03),(17,03),(13,04),(17,04),(20,04),
-- # (21,04),(16,05),(22,05),(21,06), and the last stands at (14,05).
for i = 1,12 do
   des.object("boulder",14,05)
end

des.engraving({ x = 17, y = 07, type = "burn",
                text = "How did they all end up on top of each other?" });

des.trap("hole",02,07)
des.trap("hole",03,07)
des.trap("hole",04,07)
des.trap("hole",05,07)
des.trap("hole",06,07)
des.trap("hole",07,07)
des.trap("hole",08,07)
des.trap("hole",09,07)
des.trap("hole",10,07)
des.trap("hole",11,07)
des.trap("hole",12,07)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- Two random mimics!
des.monster("m")
des.monster("m")