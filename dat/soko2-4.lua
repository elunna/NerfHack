
-- "Two-Phase"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
----------                
|........|                
|........|                
|........|------------    
|........F.....|.....-----
|........F.....+.........|
|..-FF-+-|.....|.........|
|---..|.--.---.----.----.|
|.....|.|....-..| |......|
|..|..|.F.......---......|
--.|....F.....-..........|
 |.|....|.---...---.------
 |.------............|    
 |..............------    
 |..-------------         
 ----                     
]]);

des.stair("down",12,04)
des.stair("up",04,03)
des.region(selection.area(00,00,25,15),"lit");
des.non_diggable(selection.area(00,00,25,15));
des.non_passwall(selection.area(00,00,25,15));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 07,06)
des.door("locked", 15,05)

-- Boulders
des.object("boulder", 10,06)
des.object("boulder", 11,05)
des.object("boulder", 12,06)
des.object("boulder", 13,05)
des.object("boulder", 14,06)
des.object("boulder", 14,09)
des.object("boulder", 10,10)
des.object("boulder", 10,12)
des.object("boulder", 19,10)
des.object("boulder", 22,08)
des.object("boulder", 16,05)
des.object("boulder", 17,05)
des.object("boulder", 18,05)
des.object("boulder", 20,05)
des.object("boulder", 20,06)
des.object("boulder", 23,06)
des.object("boulder", 06,10)

-- Traps
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 04,13, 08,13 } });
des.trap("hole", 08,13)
des.trap("hole", 07,13)
des.trap("hole", 06,13)
des.trap("hole", 05,13)
des.trap("hole", 04,13)
des.exclusion({ type = "monster-generation", region = { 02,09, 02,12 } });
des.trap("hole", 02,12)
des.trap("hole", 02,11)
des.trap("hole", 02,10)
des.trap("hole", 02,09)
des.exclusion({ type = "monster-generation", region = { 03,08, 04,08 } });
des.trap("hole", 03,08)
des.trap("hole", 04,08)
des.exclusion({ type = "monster-generation", region = { 07,08, 07,10 } });
des.trap("hole", 07,10)
des.trap("hole", 07,09)
des.trap("hole", 07,08)

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