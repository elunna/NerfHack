-- NetHack sokoban soko3-1.lua	$NHDT-Date: 1652196035 2022/05/10 15:20:35 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- https://nethackwiki.com/wiki/Sokoban_Level_1c
-- authorship may be Thinking Rabbit
-- with edits from paxed/patr

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
 --------       
 |......|       
 |......-----   
 |---.......|   
 |..--.|....|   
 |.....|.|.-----
 |.--..........|
--.||..|...|...|
|..-------------
|.........|     
-----------     
]]);

des.stair("down", 6,5)
des.stair("up", 9,9)
des.region(selection.area(00,00,15,10),"lit")
des.non_diggable(selection.area(00,00,15,10))
des.non_passwall(selection.area(00,00,15,10))

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=30 })

-- Boulders
des.object("boulder",4,2)
des.object("boulder",8,3)
des.object("boulder",6,4)
des.object("boulder",9,4)
des.object("boulder",6,6)
des.object("boulder",8,6)
des.object("boulder",10,6)
des.object("boulder",11,6)

-- Traps
des.trap("hole",2,6)
des.trap("hole",2,7)
des.trap("hole",4,9)
des.trap("hole",5,9)
des.trap("hole",6,9)
des.trap("hole",7,9)
des.trap("hole",8,9)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")