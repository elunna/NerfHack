--
-- MESSAGE:"Corner Pocket"
-- "Thinking Rabbit"
-- Ported from UnNetHack 
-- Converted to lua by hackemslashem
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
       ------------
-------|..........|
|...|..|FF------..|
|......F..|    |.--
--.--..F..-----|.| 
 |.....--...|..|.| 
 |.|....|......|.| 
 |...|.....---.|.| 
 |.....--..---.|.| 
 ---...|.......|.| 
   ---.|...--..|.| 
    |......||....| 
    |.....-----..| 
    -------   ---- 
]]);

des.stair("down",08,04)
des.stair("up",08,01)
des.region(selection.area(00,00,18,13),"lit");
des.non_diggable(selection.area(00,00,18,13));
des.non_passwall(selection.area(00,00,18,13));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Boulders
des.object("boulder", 02,03)
des.object("boulder", 05,04)
des.object("boulder", 04,05)
des.object("boulder", 06,05)
des.object("boulder", 09,05)
des.object("boulder", 06,06)
des.object("boulder", 10,06)
des.object("boulder", 03,07)
des.object("boulder", 06,07)
des.object("boulder", 10,08)
des.object("boulder", 05,09)
des.object("boulder", 10,09)
des.object("boulder", 10,10)
des.object("boulder", 07,11)
des.object("boulder", 08,11)

-- Traps
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 09,01, 15,01} });
des.trap("hole", 09,01)
des.trap("hole", 10,01)
des.trap("hole", 11,01)
des.trap("hole", 12,01)
des.trap("hole", 13,01)
des.trap("hole", 14,01)
des.trap("hole", 15,01)
des.exclusion({ type = "monster-generation", region = { 16,03, 16,10} });
des.trap("hole", 16,03)
des.trap("hole", 16,04)
des.trap("hole", 16,05)
des.trap("hole", 16,06)
des.trap("hole", 16,07)
des.trap("hole", 16,08)
des.trap("hole", 16,09)
des.trap("hole", 16,10)

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