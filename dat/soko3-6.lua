--
-- Steve Melenchuk <smelenchuk@gmail.com>
-- Ported from GruntHack
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
  --------------------
  |..................|
  |.....------------.|
  --.----..--------|.|
----.--...........FF.|
----....-.....-...FF.|
 F.....-..-...-----|.|
 F.-......-.--------+|
 F..-.--.....| |.....|
 --......--.-- |.....|
  --.........| |.....|
   ---..---..- |.....|
     ---- |..| |.....|
          ---- |.....|
               |.....|
               -------
]]);

des.stair("down",07,11)
des.stair("up",18,11)
des.region(selection.area(00,00,21,15),"lit");
des.non_diggable(selection.area(00,00,21,15));
des.non_passwall(selection.area(00,00,21,15));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 20,07)

-- Boulders
des.object("boulder", 08,04)
des.object("boulder", 11,05)
des.object("boulder", 12,05)
des.object("boulder", 05,06)
des.object("boulder", 12,06)
des.object("boulder", 05,07)
des.object("boulder", 07,07)
des.object("boulder", 08,07)
des.object("boulder", 05,08)
des.object("boulder", 05,09)
des.object("boulder", 07,09)
des.object("boulder", 08,09)
des.object("boulder", 10,10)
des.object("boulder", 11,11)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 08,01, 19,01 } });
des.trap("hole", 08,01)
des.trap("hole", 09,01)
des.trap("hole", 10,01)
des.trap("hole", 11,01)
des.trap("hole", 12,01)
des.trap("hole", 13,01)
des.trap("hole", 14,01)
des.trap("hole", 15,01)
des.trap("hole", 16,01)
des.trap("hole", 17,01)
des.trap("hole", 18,01)
des.trap("hole", 19,01)

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