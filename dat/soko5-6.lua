--
-- "Boomerang Boulders"
-- MAZE:"soko4-10",' '
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
         ----    
 ---------..---  
 |............---
 |.......F......|
--------F|......|
|........F......|
|..-----F|-.-----
--.......F.....| 
 |..|..........| 
 ---|....|.....| 
    ------------ 
]]);

des.levregion({ region = {07,08,07,08}, type = "branch" })
des.stair("up", 08,05)
des.region(selection.area(00,00,16,10),"lit");
des.non_diggable(selection.area(00,00,16,10));
des.non_passwall(selection.area(00,00,16,10));

des.object({ id = "statue", x=14, y=04, montype="white dragon", historic=1 })

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })
-- No ice on branch location
des.replace_terrain({ region={07,08,07,08}, fromterrain="I", toterrain="." })

-- Boulders
des.object("boulder", 03,02)
des.object("boulder", 05,02)
des.object("boulder", 10,02)
des.object("boulder", 10,03)
des.object("boulder", 13,03)
des.object("boulder", 14,04)
des.object("boulder", 13,05)
des.object("boulder", 11,07)
des.object("boulder", 12,08)
des.object("boulder", 13,08)
des.object("boulder", 06,07)
des.object("boulder", 05,08)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 02,05, 07,05 } });
des.trap("pit", 07,05)
des.trap("pit", 06,05)
des.trap("pit", 05,05)
des.trap("pit", 04,05)
des.trap("pit", 03,05)
des.trap("pit", 02,05)
des.exclusion({ type = "monster-generation", region = { 02,06, 02,07 } });
des.trap("pit", 02,06)
des.trap("pit", 02,07)
des.exclusion({ type = "monster-generation", region = { 03,07, 04,07 } });
des.trap("pit", 03,07)
des.trap("pit", 04,07)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- A little help
des.object("earth",02,08)
if percent(50) then
    des.object("earth",03,08)
end

-- One random mimic
des.monster("m")