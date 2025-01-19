-- NetHack sokoban soko4-1.lua	$NHDT-Date: 1652196036 2022/05/10 15:20:36 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.2 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
--
-- In case you haven't played the game Sokoban, you'll learn
-- quickly.  This branch isn't particularly difficult, just time
-- consuming.  Some players may wish to skip this branch.
--
-- The following actions are currently permitted without penalty:
--   Carrying or throwing a boulder already in inventory
--     (player or nonplayer).
--   Teleporting boulders.
--   Digging in the floor.
-- The following actions are permitted, but with a luck penalty:
--   Breaking boulders.
--   Stone-to-fleshing boulders.
--   Creating new boulders (e.g., with a scroll of earth).
--   Jumping.
--   Being pulled by a thrown iron ball.
--   Hurtling through the air from Newton's 3rd law.
--   Squeezing past boulders when naked or as a giant.
--   Enabling the "do_not_flip_soko" option when generating a new puzzle.
-- These actions are not permitted:
--   Moving diagonally between two boulders and/or walls.
--   Pushing a boulder diagonally.
--   Picking up boulders (player or nonplayer).
--   Digging or walking through walls.
--   Teleporting within levels or between levels of this branch.
--   Using cursed potions of gain level.
--   Escaping a pit/hole (e.g., by flying, levitation, or
--     passing a dexterity check).
--   Bones files are not permitted.

--## Bottom (first) level of Sokoban ###

-- https://nethackwiki.com/wiki/Sokoban_Level_1c
-- authorship may be J Franklin Mentzer, with edits from paxed/patr
-- Ported from SpliceHack, original source SLASH'EM
-- Converted to lua by Kestrel Gregorich-Trevor
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "sokoban", "premapped", "solidify", "cold");
des.map([[
     -------                 
     |..|..|     --------    
------.....--- ---......---  
|......---...| |..........|  
|.|.|......|.--|........|.---
|.|.--..|..|...-F-F-F-F--...|
|.......|...................|
|.|.--..|..|...-F-F-F-F--...|
|.|.|......|.--|........|.---
|......---...| |..........|  
------.....--- ---......---  
     |..|..|     --------    
     -------                 
]]);

des.stair("up", 26,6)
des.stair("down", 13,06)
des.region(selection.area(00,00,28,12),"lit")
des.non_diggable(selection.area(00,00,28,12))
des.non_passwall(selection.area(00,00,28,12))

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })
-- No ice on branch location
des.replace_terrain({ region={13,6,13,6}, fromterrain="I", toterrain="." })

-- Boulders
des.object("boulder",8,2)
des.object("boulder",8,4)
des.object("boulder",3,5)
des.object("boulder",6,6)
des.object("boulder",7,6)
des.object("boulder",9,6)
des.object("boulder",10,6)
des.object("boulder",3,7)
des.object("boulder",8,8)
des.object("boulder",8,10)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 15,06, 23,06 } });
des.trap("pit",15,06)
des.trap("pit",16,06)
des.trap("pit",17,06)
des.trap("pit",18,06)
des.trap("pit",19,06)
des.trap("pit",20,06)
des.trap("pit",21,06)
des.trap("pit",22,06)
des.trap("pit",23,06)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });
des.object({ id = "statue", x=20, y=03, montype="white dragon", historic=1 })
des.object({ id = "statue", x=20, y=09, montype="white dragon", historic=1 })

-- A little help
des.object("earth",16,3)
des.object("earth",16,9)

-- One random mimic
des.monster("m")