--
-- "The Snake"
-- (Adapted from Slash'em.)
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
  ---------                 
 --.......--                
 |..--.--..|                
 |.........|     FFFFF      
 F..-|.|-..F     F...F      
---..|.|..---    F.{.F      
|...........|    F...F      
|..|.....|..|  ----S----    
|-.F.-F-.F.-|  |.......|    
|..|.....|..|  |.......|    
|...........|  |.......|    
---.--.--.---  |.......|    
  F.......F    |.......|    
  ---...---    ----+----    
    |...|         |.|       
    |...-----------.|       
    |...............|       
    -----------------       
]]);

des.stair("up",19,10)
des.stair("down",06,13)
des.region(selection.area(00,00,27,17),"lit");
des.non_diggable(selection.area(00,00,27,17));
des.non_passwall(selection.area(00,00,27,17));

des.object({ id = "statue", x=19, y=10, montype="white dragon", historic=1 })


-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 19,13)
des.door("locked", 19,07)

-- Boulders
des.object("boulder", 03,03)
des.object("boulder", 05,03)
des.object("boulder", 07,03)
des.object("boulder", 09,03)
des.object("boulder", 06,06)
des.object("boulder", 06,07)
des.object("boulder", 02,08)
des.object("boulder", 04,08)
des.object("boulder", 08,08)
des.object("boulder", 10,08)
des.object("boulder", 06,09)
des.object("boulder", 06,10)

-- Traps
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 09,16, 18,16 } });
des.trap("hole", 09,16)
des.trap("hole", 10,16)
des.trap("hole", 11,16)
des.trap("hole", 12,16)
des.trap("hole", 13,16)
des.trap("hole", 14,16)
des.trap("hole", 15,16)
des.trap("hole", 16,16)
des.trap("hole", 17,16)
des.trap("hole", 18,16)

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