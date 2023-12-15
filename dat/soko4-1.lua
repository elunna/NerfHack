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

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "premapped", "solidify");
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
des.levregion({ region = {13,6,13,6}, type = "branch" })
des.stair("up", 26,6)
des.region(selection.area(00,00,28,12),"lit")
des.non_diggable(selection.area(00,00,28,12))
des.non_passwall(selection.area(00,00,28,12))

-- A little help
des.object("earth",16,3)
if percent(50) then
    des.object("earth",16,9)
end

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

des.trap("pit",15,6)
des.trap("pit",16,6)
des.trap("pit",17,6)
des.trap("pit",18,6)
des.trap("pit",19,6)
des.trap("pit",20,6)
des.trap("pit",21,6)
des.trap("pit",22,6)
des.trap("pit",23,6)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")