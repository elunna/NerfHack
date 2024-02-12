-- NetHack sokoban soko2-2.lua	$NHDT-Date: 1652196035 2022/05/10 15:20:35 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- https://nethackwiki.com/wiki/Sokoban_Level_3f
-- "Thinking Rabbit"

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
        ---------    
        |...|...---- 
        |...+......| 
        |...|.|..|.| 
  -----------....|.| 
  |................| 
  |.|.|..--.|.|..|.| 
  |...|.....|....|.| 
 --.|...-------+-|.| 
--......|....|...|.| 
|....|..F....F...|.| 
|......-|....|...|.--
|..-----|....|----..|
|..|....+....+......|
---------------------
]]);

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=40 })

des.stair("down", 01,13)
des.stair("up", 04,13)
des.region(selection.area(00,00,20,14), "lit");
des.non_diggable(selection.area(00,00,20,14));
des.non_passwall(selection.area(00,00,20,14));

des.door("locked",12,02)
des.door("locked",15,08)
des.door("locked",08,13)
des.door("locked",13,13)

-- Boulders
des.object("boulder",10,02)
des.object("boulder",13,03)
des.object("boulder",18,04)
des.object("boulder",09,05)
des.object("boulder",08,06)
des.object("boulder",07,07)
des.object("boulder",03,08)
des.object("boulder",06,08)
des.object("boulder",05,09)
des.object("boulder",04,10)
des.object("boulder",15,10)
des.object("boulder",03,11)
des.object("boulder",02,12)

-- Traps
des.trap("hole",18,06)
des.trap("hole",18,07)
des.trap("hole",18,08)
des.trap("hole",18,09)
des.trap("hole",18,10)
des.trap("hole",18,11)
des.trap("hole",05,13)
des.trap("hole",06,13)
des.trap("hole",07,13)
des.trap("hole",14,13)
des.trap("hole",15,13)
des.trap("hole",16,13)
des.trap("hole",17,13)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")