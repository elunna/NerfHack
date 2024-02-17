-- NetHack sokoban soko2-2.lua	$NHDT-Date: 1652196035 2022/05/10 15:20:35 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- SLASHEM 3g
-- https://nethackwiki.com/wiki/Sokoban_Level_3g

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
           ----       
  ---------|..|       
---...|...--..|---    
|.....|.......|..|    
|.|...|...--.....|    
|.|...|....|..--.|    
|.|.----.|.--F--.|--- 
|.|..|--.|..|.|..|..| 
|.|..|....|.|.|.....| 
|.........|.|.--F--.--
|.|..---.--.|..|..|..|
|.----......F..F.....|
|......-----|..|.-----
--------    |.--..|   
            |.....|   
            |..----   
            ----      
]]);

des.stair("down", 12,01)
des.stair("up", 13,07)
des.region(selection.area(00,00,21,16), "lit");
des.non_diggable(selection.area(00,00,21,16));
des.non_passwall(selection.area(00,00,21,16));

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=40 })

-- Boulders
des.object("boulder",12,02)
des.object("boulder",03,03)
des.object("boulder",04,03)
des.object("boulder",12,03)
des.object("boulder",12,04)
des.object("boulder",08,05)
des.object("boulder",09,05)
des.object("boulder",03,07)
des.object("boulder",06,09)

-- Traps
des.trap("hole",14,04)
des.trap("hole",16,05)
des.trap("hole",16,06)
des.trap("hole",17,08)
des.trap("hole",19,09)
des.trap("hole",18,11)
des.trap("hole",16,12)
des.trap("hole",13,13)
des.trap("hole",15,14)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")