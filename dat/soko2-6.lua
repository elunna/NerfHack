--
-- "Four Wings"
--MAZE: "soko3-17",' '
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
           ----           
          --..--          
         --....--         
         |......|         
      ---|......----      
      |..|..-----..|      
   ---|.....|......|---   
 ---..|.---.|..---.|..--- 
--....|.| |.--.| |.|....--
|.....|.| |..|.| |.|.....|
|.....|.--|..|.| |.|.....|
--....|..||..|.| |.|....--
 ---.....--..|.--|.+..--- 
   ----..........------   
      |............|      
      ----......----      
         |-.....|         
         --....--         
          ------          
]]);

des.stair("down",12,09)
des.stair("up",22,09)
des.region(selection.area(00,00,25,18),"lit");
des.non_diggable(selection.area(00,00,25,18));
des.non_passwall(selection.area(00,00,25,18));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 19,12)

-- Boulders
des.object("boulder", 12,03)
des.object("boulder", 12,04)
des.object("boulder", 09,06)
des.object("boulder", 05,08)
des.object("boulder", 03,10)
des.object("boulder", 04,10)
des.object("boulder", 05,10)
des.object("boulder", 11,10)
des.object("boulder", 03,11)
des.object("boulder", 12,11)
des.object("boulder", 11,12)
des.object("boulder", 15,13)
des.object("boulder", 09,14)
des.object("boulder", 10,14)
des.object("boulder", 11,14)
des.object("boulder", 11,16)
des.object("boulder", 12,16)

-- Traps
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 17,06, 15,06 } });
des.trap("hole", 15,06)
des.trap("hole", 16,06)
des.trap("hole", 17,06)
des.exclusion({ type = "monster-generation", region = { 14,07, 14,12 } });
des.trap("hole", 14,07)
des.trap("hole", 14,08)
des.trap("hole", 14,09)
des.trap("hole", 14,10)
des.trap("hole", 14,11)
des.trap("hole", 14,12)
des.exclusion({ type = "monster-generation", region = { 18,07, 18,12 } });
des.trap("hole", 18,07)
des.trap("hole", 18,08)
des.trap("hole", 18,09)
des.trap("hole", 18,10)
des.trap("hole", 18,11)
des.trap("hole", 18,12)

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