--
-- "Joseph L Traub"
-- Ported from UnNetHack
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
  -------------    
--|...........|    
|.+...........|    
|.|...........|----
|.|FFFFFFFFFFF|...|
|.F...........|...|
|.F.--............|
|.F..|.-----.--...|
|.F..|.....|.||...|
|.F.--.---.|.--...|
|.F....---........|
|.-FF-.......--...|
|............|-----
|..---.......|     
---- ------..|     
          ----     
]]);

des.stair("up",12,02)
des.stair("down", 11,14)
des.region(selection.area(00,00,18,15),"lit");
des.non_diggable(selection.area(00,00,18,15));
des.non_passwall(selection.area(00,00,18,15));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })
-- No ice on branch location
des.replace_terrain({ region={11,14,11,14}, fromterrain="I", toterrain="." })

-- Doors
des.door("locked", 02,02)

-- Boulders
des.object("boulder", 08,06)
des.object("boulder", 10,06)
des.object("boulder", 15,06)
des.object("boulder", 16,06)
des.object("boulder", 16,07)
des.object("boulder", 06,08)
des.object("boulder", 07,08)
des.object("boulder", 12,08)
des.object("boulder", 16,08)
des.object("boulder", 15,09)
des.object("boulder", 11,10)
des.object("boulder", 13,10)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 01,03, 01,10 } });
des.trap("pit", 01,03)
des.trap("pit", 01,04)
des.trap("pit", 01,05)
des.trap("pit", 01,06)
des.trap("pit", 01,07)
des.trap("pit", 01,08)
des.trap("pit", 01,09)
des.trap("pit", 01,10)
des.exclusion({ type = "monster-generation", region = { 03,12, 05,12 } });
des.trap("pit", 03,12)
des.trap("pit", 04,12)
-- leave a spare boulder
--des.trap("pit", 05,12)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });
des.object({ id = "statue", x=08, y=02, montype="white dragon", historic=1 })

-- A little help
des.object("earth",01,13)
des.object("earth",02,13)

-- One random mimic
des.monster("m")