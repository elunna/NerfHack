--
-- "Picking out the Seeds"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "sokoban", "premapped", "solidify", "cold");
des.map([[
   ---------   
 ---..F....--- 
 |....|......| 
--..........---
|.....|.....F.|
|.........---.|
|-F-FF-...|...|
|.......---...|
--...........--
 |......---..| 
 ---......|--- 
   ---------   
]]);

des.stair("up", 13,04)
des.stair("down", 12,02)
des.region(selection.area(00,00,14,11),"lit")
des.non_diggable(selection.area(00,00,14,11))
des.non_passwall(selection.area(00,00,14,11))

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })
-- No ice on branch location
des.replace_terrain({ region={12,02,12,02}, fromterrain="I", toterrain="." })

-- Boulders
des.object("boulder", 03,02)
des.object("boulder", 09,02)
des.object("boulder", 11,02)
des.object("boulder", 05,03)
des.object("boulder", 06,03)
des.object("boulder", 10,03)
des.object("boulder", 09,04)
des.object("boulder", 02,05)
des.object("boulder", 04,05)
des.object("boulder", 09,05)
des.object("boulder", 04,07)
des.object("boulder", 06,07)
des.object("boulder", 03,09)
des.object("boulder", 07,09)

-- Traps

des.exclusion({ type = "monster-generation", region = { 13,05, 13,06 } });
des.trap("hole", 13,05)
des.trap("hole", 13,06)
des.exclusion({ type = "monster-generation", region = { 07,06, 07,07 } });
des.trap("hole", 07,06)
des.trap("hole", 07,07)
des.exclusion({ type = "monster-generation", region = { 12,06, 12,07 } });
des.trap("hole", 12,06)
des.trap("hole", 12,07)
des.exclusion({ type = "monster-generation", region = { 07,08, 12,08 } });
des.trap("hole", 07,08)
des.trap("hole", 08,08)
des.trap("hole", 09,08)
des.trap("hole", 10,08)
des.trap("hole", 11,08)
des.trap("hole", 12,08)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });
des.object({ id = "statue", x=05, y=01, montype="white dragon", historic=1 })

-- A little help
des.object("earth",11,09)
des.object("earth",12,09)

-- One random mimic
des.monster("m")
