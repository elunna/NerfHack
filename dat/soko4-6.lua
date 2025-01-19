--
-- "Joseph L Traub"
-- Ported from UnNetHack
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
-------       --------
|.....|-------|......|
|.....|....|..--FF-..|
|.....|........|..F.--
|.....|....--..|..F.| 
|.....|-.......+..F.| 
|-.|..||.------|..F.| 
|-.|..--.......|..F.| 
|..|...........-FF-.| 
|...................| 
|.....--.|.....---..| 
---------------- ---- 
]]);

des.stair("down",08,10)
des.stair("up",15,01)
des.region(selection.area(00,00,21,11),"lit");
des.non_diggable(selection.area(00,00,21,11));
des.non_passwall(selection.area(00,00,21,11));

des.object({ id = "statue", x=17, y=05, montype="white dragon", historic=1 })

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 15,05)

-- Boulders
des.object("boulder", 02,03)
des.object("boulder", 10,03)
des.object("boulder", 12,03)
des.object("boulder", 03,04)
des.object("boulder", 09,04)
des.object("boulder", 02,05)
des.object("boulder", 03,05)
des.object("boulder", 08,05)
des.object("boulder", 10,05)
des.object("boulder", 04,08)
des.object("boulder", 04,09)
des.object("boulder", 05,09)
des.object("boulder", 16,04)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 16,01, 18,01 } });
des.trap("hole", 16,01)
des.trap("hole", 17,01)
des.trap("hole", 18,01)
des.exclusion({ type = "monster-generation", region = { 19,03, 19,08 } });
des.trap("hole", 19,03)
des.trap("hole", 19,04)
des.trap("hole", 19,05)
des.trap("hole", 19,06)
des.trap("hole", 19,07)
des.trap("hole", 19,08)
des.exclusion({ type = "monster-generation", region = { 17,09, 15,09 } });
des.trap("hole", 15,09)
des.trap("hole", 16,09)
des.trap("hole", 17,09)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")