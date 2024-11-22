-- SCCS Id: @(#)gehennom.des	3.4	1996/11/09
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
-- [Tom]
-- The Dispater level
--
-- Ported from SLASH'EM
-- Author: Unknown
-- Converted to lua by hackemslashem
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor", "noflip")

des.map({ halign = "right", valign = "center", map = [[
-------------------------------------------------
| ----------------------------------------|--    
| |.....|.....................|...|...|...S.|    
| |.--|.|.-------------------.|.|.|.|.|.|.|.|    
| |...|.|...................|.|.|.|.|.|.|.|.|    
----|.|.|-----------------|.|.|.|.|.|.|.|.|S---  
....|.|.|.................|.|.|.|.|.|.|.|.|...|  
---.|.|.|.|--------------.|.|.|.|.|.|.|.|.|----  
| |.|.|.|.|...............|.|.|.|.|.|.|.|.| |    
| |.|.|.|.|.--------------|.|.|.|.|.|.|.|.| |    
| |...|...|.................|...|...|...|.| |    
| -------------------------------------------    
-------------------------------------------------
]] });

des.levregion({ region = {01,00,15,20}, region_islev=1, exclude={15,1,70,16}, exclude_islev=1, type="stair-up" })
des.levregion({ region = {01,00,15,20}, region_islev=1, exclude={15,1,70,16}, exclude_islev=1, type="branch" })
des.teleport_region({region={01,00,15,20}, exclude = {15,01,70,16} })

-- Non diggable walls
des.non_diggable(selection.area(00,00,46,12))
des.non_passwall(selection.area(00,00,46,12));

des.mazewalk(00,06,"west")

des.stair("down", 44,06)

-- The fellow in residence
des.monster({id="Dispater", x=18, y=06})

-- Some random weapons and armor.
des.object("[")
des.object("[")
des.object(")")
des.object(")")
des.object("*")
des.object("!")
des.object("!")
des.object("?")
des.object("?")
des.object("?")

-- Some traps.
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")

-- Random monsters.
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")

des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")
des.monster("imp")

des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")
des.monster("nupperibo")

des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")

des.monster("bone devil")
des.monster("bone devil")
des.monster("bone devil")
des.monster("bone devil")
des.monster("bone devil")
des.monster("bone devil")
des.monster("bone devil")
des.monster("bone devil")
des.monster("bone devil")
