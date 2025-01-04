-- "Sneak Preview"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
           ----
 -----------..|
 |............|
 |.--.-------.|
--......|...|.|
|.......+...|.|
|.......|...|.|
|-+--.--|FFF-+|
|...|...|.....|
|...|.|.|K....|
|...|.|.|.....|
----|...-----F|
    |......--.|
    |.--....|.|
    |.....-.|.|
    |.-.-...|.|
    |.......-S|
    -----.....|
        --....|
         ------
]]);

des.stair("up",11,09)
des.stair("down",11,18)
des.region(selection.area(00,00,14,19),"lit");
des.non_diggable(selection.area(00,00,14,19));
des.non_passwall(selection.area(00,00,14,19));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("closed", 08,05)
des.door("closed", 02,07)
des.door("locked", 13,07)
des.door("locked", 13,16)

-- Boulders
des.object("boulder", 04,02)
des.object("boulder", 10,05)
des.object("boulder", 02,09)
des.object("boulder", 05,10)
des.object("boulder", 06,11)
des.object("boulder", 07,12)
des.object("boulder", 08,13)
des.object("boulder", 09,14)
des.object("boulder", 10,15)
des.object("boulder", 08,16)
des.object("boulder", 11,16)
des.object("boulder", 12,17)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 06,02, 11,02 } });
des.trap("hole", 06,02)
des.trap("hole", 07,02)
des.trap("hole", 08,02)
des.trap("hole", 09,02)
des.trap("hole", 10,02)
des.trap("hole", 11,02)
des.exclusion({ type = "monster-generation", region = { 13,03, 13,06 } });
des.trap("hole", 13,03)
des.trap("hole", 13,04)
des.trap("hole", 13,05)
des.trap("hole", 13,06)

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