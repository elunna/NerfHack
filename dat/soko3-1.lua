-- NetHack 3.7  sokoban.des $NHDT-Date: 1432512784 2015/05/25 00:13:04 $  $NHDT-Branch: master $:$NHDT-Revision: 1.13 $
--  Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- SLASH'EM 3e
-- https://nethackwiki.com/wiki/Sokoban_Level_3e
-- Ported from SpliceHack, original source SLASH'EM
-- Converted to lua by Kestrel Gregorich-Trevor
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
    ------------------
 ----....|.........+.|
 |....--.|.........|.|
 |.......|.........|.|
---.----.|.........|.|
|........-F-F-F-F-F-.|
|....................|
|........--F-F-F-F-..|
--.--.--.|...........|
 |--.....|...........|
 |.......|...........|
 |....|..|...........|
 ---------------------
]]);

des.stair("down", 02,08)
des.stair("up", 11,03)
des.region(selection.area(00,00,21,12), "lit");
des.non_diggable(selection.area(00,00,21,12));
des.non_passwall(selection.area(00,00,21,12));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked",19,01)

-- Boulders
des.object("boulder",03,03)
des.object("boulder",03,05)
des.object("boulder",07,05)
des.object("boulder",04,06)
des.object("boulder",05,06)
des.object("boulder",07,06)
des.object("boulder",08,06)
des.object("boulder",05,07)
des.object("boulder",08,07)
des.object("boulder",06,09)
des.object("boulder",15,09)
des.object("boulder",16,09)
des.object("boulder",05,10)
des.object("boulder",06,10)


-- Traps
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 20,02, 20,05 } });
des.trap("hole",20,02)
des.trap("hole",20,03)
des.trap("hole",20,04)
des.trap("hole",20,05)
des.exclusion({ type = "monster-generation", region = { 09,06, 18,06 } });
-- reduced holes by 1, to allow for small mistakes
--des.trap("hole",09,06)
des.trap("hole",10,06)
des.trap("hole",11,06)
des.trap("hole",12,06)
des.trap("hole",13,06)
des.trap("hole",14,06)
des.trap("hole",15,06)
des.trap("hole",16,06)
des.trap("hole",17,06)
des.trap("hole",18,06)

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