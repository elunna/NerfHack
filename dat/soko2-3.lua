--
-- "Boulder Halls of Zim"
--MAZE:"soko3-12",' '
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
                -----------
   ---------    |.........|
  --.......|    |.........|
  |........--   |.........|
  ---..---..|   |.........|
    |..| |..|   |.........|
 ----.----..|   |.........|
 |.......|..|   |.........|
 |..........|   |.........|
 |..........-------------+|
 --.....--................|
  --.....------------------
   ---.....|               
     -------               
]]);

des.stair("down",07,12)
des.stair("up",21,05)
des.region(selection.area(00,00,26,13),"lit");
des.non_diggable(selection.area(00,00,26,13));
des.non_passwall(selection.area(00,00,26,13));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 25,09)

-- Boulders
des.object("boulder", 05,03)
des.object("boulder", 07,03)
des.object("boulder", 09,03)
des.object("boulder", 03,07)
des.object("boulder", 05,07)
des.object("boulder", 07,07)
des.object("boulder", 03,09)
des.object("boulder", 05,09)
des.object("boulder", 05,11)
des.object("boulder", 07,09)
des.object("boulder", 09,09)
des.object("boulder", 10,08)
des.object("boulder", 11,08)
des.object("boulder", 11,06)

-- Traps
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 12,10, 24,10 } });
des.trap("hole", 12,10)
des.trap("hole", 13,10)
des.trap("hole", 14,10)
des.trap("hole", 15,10)
des.trap("hole", 16,10)
des.trap("hole", 17,10)
des.trap("hole", 18,10)
des.trap("hole", 19,10)
des.trap("hole", 20,10)
des.trap("hole", 21,10)
des.trap("hole", 22,10)
des.trap("hole", 23,10)
des.trap("hole", 24,10)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")