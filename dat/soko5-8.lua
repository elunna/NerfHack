--
-- "One Weird Trick"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "sokoban", "premapped", "solidify", "cold");
des.map([[
----   ----   ---- 
|..-----..|----..| 
|...--....--.....| 
--............--.| 
 |.....--.....||.| 
 |......|...---|.| 
 ---..|.|.---  |.| 
   |..|...|    |.| 
   |..--.--    |.--
   --....|  ----..|
    |..---  |.....|
    ----    -------
]]);

des.levregion({ region = {01,01,01,01}, type = "branch" })
des.stair("up", 13,10)
des.region(selection.area(00,00,18,11),"lit");
des.non_diggable(selection.area(00,00,18,11));
des.non_passwall(selection.area(00,00,18,11));

des.object({ id = "statue", x=08, y=01, montype="white dragon", historic=1 })

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })
-- No ice on branch location
des.replace_terrain({ region={01,01,01,01}, fromterrain="I", toterrain="." })

-- Boulders
des.object("boulder",07,02)
des.object("boulder",03,03)
des.object("boulder",08,03)
des.object("boulder",10,03)
des.object("boulder",03,04)
des.object("boulder",04,04)
des.object("boulder",09,04)
des.object("boulder",11,04)
des.object("boulder",05,05)
des.object("boulder",05,07)
des.object("boulder",05,09)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 15,02, 14,02 } });
des.trap("pit",14,02)
des.trap("pit",15,02)
des.exclusion({ type = "monster-generation", region = { 16,03, 16,08 } });
des.trap("pit",16,03)
des.trap("pit",16,04)
des.trap("pit",16,05)
des.trap("pit",16,06)
des.trap("pit",16,07)
des.trap("pit",16,08)
des.exclusion({ type = "monster-generation", region = { 14,10, 15,10 } });
des.trap("pit",14,10)
des.trap("pit",15,10)

-- A little help
des.object("earth",15,01)
if percent(50) then
    des.object("earth",116,01)
end

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });