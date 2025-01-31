-- NetHack sokoban soko3-1.lua	$NHDT-Date: 1652196035 2022/05/10 15:20:35 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- https://nethackwiki.com/wiki/Sokoban_Level_1c
-- authorship may be Thinking Rabbit
-- with edits from paxed/patr
-- Ported from SpliceHack, original source SLASH'EM
-- Converted to lua by Kestrel Gregorich-Trevor
--
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
|..--FF-FF------
|.........|     
-----------     
]]);

des.stair("down", 6,5)
des.stair("up", 9,9)
des.region(selection.area(00,00,15,10),"lit")
des.non_diggable(selection.area(00,00,15,10))
des.non_passwall(selection.area(00,00,15,10))

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

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
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 02,06, 02,07 } });
des.trap("hole",02,06)
des.trap("hole",02,07)
des.exclusion({ type = "monster-generation", region = { 04,09, 08,09 } });
des.trap("hole",04,09)
des.trap("hole",05,09)
des.trap("hole",06,09)
des.trap("hole",07,09)
des.trap("hole",08,09)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")