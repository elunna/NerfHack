--
--MESSAGE:"Escape Goat"
-- Steve Melenchuk <smelenchuk@gmail.com>
-- Ported from GruntHack
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
 ---------      
 |...|...|      
--.......|      
|..--....-------
|..--....|.....|
|..|..-..|.....|
|..|.--..|.....|
|........|.....|
----.--..|.....|
   |.--..|.....|
  --.--..|.....|
  |..---F--+---|
  |.........|   
  -----------   
]]);

des.stair("down",04,06)
des.stair("up",12,07)
des.region(selection.area(00,00,15,13),"lit");
des.non_diggable(selection.area(00,00,15,13));
des.non_passwall(selection.area(00,00,15,13));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("locked", 11,11)

-- Boulders
des.object("boulder", 06,02)
des.object("boulder", 07,02)
des.object("boulder", 02,03)
des.object("boulder", 05,03)
des.object("boulder", 06,04)
des.object("boulder", 07,04)
des.object("boulder", 02,06)
des.object("boulder", 07,06)
des.object("boulder", 03,07)
des.object("boulder", 07,09)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 04,08, 04,10 } });
des.trap("hole", 04,08)
des.trap("hole", 04,09)
des.trap("hole", 04,10)
des.exclusion({ type = "monster-generation", region = { 05,12, 10,12 } });
des.trap("hole", 05,12)
des.trap("hole", 06,12)
des.trap("hole", 07,12)
des.trap("hole", 08,12)
des.trap("hole", 09,12)
des.trap("hole", 10,12)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")