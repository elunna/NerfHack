--
-- MAZE:"soko2-8",' '
-- MESSAGE:"No Way Out"
-- "Joseph L Traub"
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
         ----------
    -----|........|
 ----...-|.-----..|
 |.......-F-...|.--
 |.............|.| 
 |.|.---F-F--.-|.| 
 |.|.....|.....|.| 
 |.|.....|.|...|.| 
--.|...|.|.----|.| 
|..--....|.....|.| 
|......|.|.......| 
-----.--.........| 
   |.............| 
   |...---.......| 
   ----- --------- 
]]);

des.stair("down",04,04)
des.stair("up",10,02)
des.region(selection.area(00,00,18,14),"lit");
des.non_diggable(selection.area(00,00,18,14));
des.non_passwall(selection.area(00,00,18,14));

-- Boulders
des.object("boulder", 04,03)
des.object("boulder", 03,04)
des.object("boulder", 05,04)
des.object("boulder", 07,04)
des.object("boulder", 12,04)
des.object("boulder", 04,05)
des.object("boulder", 06,06)
des.object("boulder", 05,07)
des.object("boulder", 07,07)
des.object("boulder", 06,08)
des.object("boulder", 05,10)
des.object("boulder", 05,12)

-- Traps
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 11,01, 15,01 } });
des.trap("hole", 11,01)
des.trap("hole", 12,01)
des.trap("hole", 13,01)
des.trap("hole", 14,01)
des.trap("hole", 15,01)
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 16,03, 16,09 } });
des.trap("hole", 16,03)
des.trap("hole", 16,04)
des.trap("hole", 16,05)
des.trap("hole", 16,06)
des.trap("hole", 16,07)
des.trap("hole", 16,08)
des.trap("hole", 16,09)

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