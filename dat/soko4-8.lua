--
-- "Fly on the Wall"
--MAZE:"soko3-11",' '
-- Ported from 
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
                      ---- 
    -------------------..| 
 ----....................--
 |......--...----------...|
 |...--.....--        |...|
 |...--.....|         --|.|
 |..........--  --------|+|
 |...........|  |.........|
 --.----------  |.........|
  |..|          |.........|
 --..-------    |.........|
 |.........|    |.........|
 |.........|    -----------
 -----------               
]]);

des.stair("down",12,07)
des.stair("up",21,09)
des.region(selection.area(00,00,25,13),"lit");
des.non_diggable(selection.area(00,00,26,13));
des.non_passwall(selection.area(00,00,26,13));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 25,06)

-- Boulders
des.object("boulder", 03,11)
des.object("boulder", 05,11)
des.object("boulder", 07,11)
des.object("boulder", 03,08)
des.object("boulder", 03,06)
des.object("boulder", 02,05)
des.object("boulder", 03,04)
des.object("boulder", 04,05)
des.object("boulder", 04,06)
des.object("boulder", 08,07)
des.object("boulder", 07,06)
des.object("boulder", 07,05)
des.object("boulder", 08,05)
des.object("boulder", 09,04)
des.object("boulder", 10,05)
des.object("boulder", 10,03)
des.object("boulder", 11,03)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 13,02, 24,02 } });
des.trap("hole", 13,02)
des.trap("hole", 14,02)
des.trap("hole", 15,02)
des.trap("hole", 16,02)
des.trap("hole", 17,02)
des.trap("hole", 18,02)
des.trap("hole", 19,02)
des.trap("hole", 20,02)
des.trap("hole", 21,02)
des.trap("hole", 22,02)
des.trap("hole", 23,02)
des.trap("hole", 24,02)
des.exclusion({ type = "monster-generation", region = { 24,03, 24,03 } });
des.trap("hole", 24,03)
des.exclusion({ type = "monster-generation", region = { 25,04, 25,05 } });
des.trap("hole", 25,04)
des.trap("hole", 25,05)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")