--
-- Steve Melenchuk <smelenchuk@gmail.com>
-- Ported from GruntHack
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
---------                
|.......|                
--.....--                
 --...-------------------
  --.--.................|
  |......---F----------+|
  |..--..---F-    |.....|
  |.....--...|    |.....|
 --...---....|    |.....|
 |....F.....--    |.....|
 |....-.....|     |.....|
 --.........F     |.....|
  |...-...---     |.....|
  --..F...F       -------
   |..-----              
   ----                  
]]);

des.stair("down",04,05)
des.stair("up",21,09)
des.region(selection.area(00,00,24,15),"lit");
des.non_diggable(selection.area(00,00,24,15));
des.non_passwall(selection.area(00,00,24,15));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 23,05)

-- Boulders
des.object("boulder", 05,02)
des.object("boulder", 04,03)
des.object("boulder", 03,06)
des.object("boulder", 04,07)
des.object("boulder", 05,07)
des.object("boulder", 03,08)
des.object("boulder", 10,08)
des.object("boulder", 03,09)
des.object("boulder", 11,09)
des.object("boulder", 05,10)
des.object("boulder", 08,10)
des.object("boulder", 03,11)
des.object("boulder", 07,11)
des.object("boulder", 09,11)
des.object("boulder", 10,11)
des.object("boulder", 04,12)
des.object("boulder", 08,12)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 09,04, 22,04 } });
des.trap("hole", 09,04)
des.trap("hole", 10,04)
des.trap("hole", 11,04)
des.trap("hole", 12,04)
des.trap("hole", 13,04)
des.trap("hole", 14,04)
des.trap("hole", 15,04)
des.trap("hole", 16,04)
des.trap("hole", 17,04)
des.trap("hole", 18,04)
des.trap("hole", 19,04)
des.trap("hole", 20,04)
des.trap("hole", 21,04)
des.trap("hole", 22,04)

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