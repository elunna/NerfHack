-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
-- NetHack may be freely redistributed.  See license for details.

-- The Yeenoghu level

-- Based upon Tom Proudfoots Slash'Em Yeenoghu level
-- 
-- Yeenoghu is the demon lord of the Gnolls, a secretive, silent
-- race of mountain dwelling creatures.
-- MAZE:"yeenoghu",random
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor")

--0       1         2         3         4         5         6         7     
--23456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "center", valign = "center", map = [[
       }}}}       .....  ..    ----------- ------------               ...   
  ....  }}}}    ...   H ....  .|....|....| |......S...-------------- ..}... 
 ......  }}}}   H   .H......H..|....|....| |FFFFFF|...S..........+.|  ... . 
  ....  }}}}   ...H..  .....   |....|S--S---..........|...--------------  . 
   . H }}}}  .....      ...  ---....|..F.......{......|S--|............|--S-
   H ..}}}}H......H..    ..H........|..F......{.{.....F...+.........\..S...|
 ...   }}}}  ....   ...      ---....|..F.......{......|---|............|----
......  }}}}        .....  ..H.|....|---S---..........|...--------------  . 
.......F}}}}   ..    ...  ... .|....|....| |FFFFFF|...S..........+.| .. ... 
 ......FFFFF.....H..     ....H.|....S....| |......S...--------------  ......
  ..   }}}}F.  .. .....H.. ..  ----------- ------------...   .... ..H.. ..  
   .  }}}}  ..  . ...    H  ..     .....     ...H.....H. H .H.  ...   H  .H.
   H   }}}}  .  .  .  .H..   .H.    .....   ...          ...   ...  ...    .
   ..   }}}}  H H    .. ...    ...  ...... .....H. .H........   H  .....  ..
 .....   }}}} .... .H.  ....  .. .H....... H ..  ... ...... .H. ..H....  ...
  ....H..}.}.H...... ..  ...  H     ......H.    ..    ....    ...     .H... 
 ....   }.}.   ....   .. ...H...     ..... .H......  ......H.H.....     ..  
       }}}}            .H..    .....H...      ...     ....     ...          
]] });

-- Branch and teleport points
des.levregion({ region = {01,00,15,20}, region_islev=1, exclude={15,1,70,16}, exclude_islev=1, type="stair-up" })
des.levregion({ region = {00,11,75,17}, region_islev=1, exclude={00,00,00,00}, exclude_islev=1, type="branch" })
des.teleport_region({region={00,11,75,17}, exclude = {00,00,00,00} })

--Protect the walls
des.non_diggable(selection.area(00,00,75,17))
des.non_passwall(selection.area(29,00,75,10));

-- Regions
des.region(selection.area(00,00,67,17),"unlit")
des.region(selection.area(68,00,75,17),"unlit")
des.region(selection.area(59,04,70,06),"lit")

-- Stairs up and down
des.stair("up", 69,13)
des.stair("down", 73,05)

-- Doors
des.door("locked",36,09)
des.door("locked",37,03)
des.door("locked",40,03)
des.door("locked",40,07)
des.door("locked",50,01)
des.door("locked",50,09)
des.door("locked",54,08)
des.door("locked",54,02)
des.door("locked",55,04)
des.door("locked",58,05)
des.door("locked",65,02)
des.door("locked",65,08)
des.door("locked",71,05)
des.door("locked",74,04)

-- The fellow in residence
des.monster({id="Yeenoghu", x=35, y=06})

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
des.trap("grease")
des.trap("grease")
des.trap("magic")
des.trap("magic")
des.trap("magic")
des.trap("magic")
des.trap("spear")
des.trap("spear")
des.trap("spear")
des.trap("spear")

-- Random monsters.
des.monster("ghoul")
des.monster("ghoul")
des.monster("ghoul")
des.monster("ghoul")
des.monster("ghoul")
des.monster("ghoul")
des.monster("ghoul")
des.monster("ghoul")

-- des.monster("ghast")
-- des.monster("ghast")
-- des.monster("ghast")
-- des.monster("ghast")
-- des.monster("ghast")
-- des.monster("ghast")
des.monster("ghoul mage")
des.monster("ghoul mage")
des.monster("ghoul mage")
des.monster("ghoul mage")
des.monster("ghoul mage")
des.monster("ghoul mage")

des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
des.monster("gnoll")
