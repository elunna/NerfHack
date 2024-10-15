-- SCCS Id: @(#)gehennom.des	3.4	1996/11/09
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
-- [Tom]
-- The Demogorgon level
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor", "noflip")
des.map({ halign = "right", valign = "center", map = [[
-------------------------------------------------
| ------------|------------------                
| |}}}}}}}}}}}|}...}......}}}}}}|--------------  
| |}}}}}}}}}}}|....}}...}...}}}}S...|.........|  
| |-----}}-----...}...}.......}}|--S-----S-...|  
---....}}}}...|.....}}....}..}}}|...|.....|--S-  
.......}}}}...|-S----------------...|.....|...|  
---..}}}}}}...|}..|      |...S..S...|.....|----  
| |-}}}--------...|      |...-------|--S-----    
| |}}}}|......S...|      |..........S.......|    
| |}}}}S......|..}|      |----------|.......|    
| ------------|----                 ---------    
-------------------------------------------------
]] });

-- Stairs
des.stair("down", 44,06)

des.levregion({ region = {01,00,15,20}, region_islev=1, exclude={15,1,70,16}, exclude_islev=1, type="stair-up" })
des.levregion({ region = {01,00,15,20}, region_islev=1, exclude={15,1,70,16}, exclude_islev=1, type="branch" })
des.teleport_region({region={01,00,15,20}, exclude = {15,01,70,16} })

des.mazewalk(00,06,"west")

-- Non diggable walls
des.non_diggable(selection.area(00,00,46,12))
des.non_passwall(selection.area(00,00,46,12));

-- The fellow in residence
des.monster({id="Demogorgon", x=06, y=06})

-- Some random weapons and armor.
des.object("*")
des.object("!")
des.object("!")
des.object("!")
des.object("!")
des.object("!")
des.object("!")
des.object("?")
des.object("?")
des.object("?")

-- Random monsters.
des.monster("P")
des.monster("P")
des.monster("P")
des.monster("P")
des.monster("P")
des.monster("P")
des.monster("P")
des.monster("P")
des.monster("P")

des.monster("j")
des.monster("j")
des.monster("j")
des.monster("j")
des.monster("j")
des.monster("j")
des.monster("j")

des.monster("F")
des.monster("F")
des.monster("F")
des.monster("F")
des.monster("F")

des.monster("hezrou")
des.monster("hezrou")
des.monster("hezrou")
des.monster("hezrou")
des.monster("hezrou")
des.monster("hezrou")
des.monster("hezrou")
des.monster("hezrou")
des.monster("hezrou")
des.monster("hezrou")

des.monster("vrock")
des.monster("vrock")
des.monster("vrock")
des.monster("vrock")
des.monster("vrock")
des.monster("vrock")

des.monster("shoggoth")
des.monster("shoggoth")
des.monster("shoggoth")
des.monster("shoggoth")

des.trap("grease")
des.trap("grease")
des.trap("grease")
des.trap("grease")
des.trap("grease")
des.trap("grease")
des.trap("grease")
des.trap("grease")
