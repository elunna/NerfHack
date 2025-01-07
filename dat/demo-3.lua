-- SCCS Id: @(#)gehennom.des	3.4	1996/11/09
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
-- The Demogorgon level
--
-- Based upon Tom Proudfoots Slash'em Demogorgon level
--
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem
--
-- Don't be fooled by Demogorgons apparently greek name, he was
-- created during the 12th century by a transcription error.
-- He is very loosly associated with power, might and dark
-- underground forces.
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor")


des.map({ halign = "center", valign = "center", map = [[
                                  LLLL  ......   LLL    .LLLL  LLL          
   ..        ......LLL           LLLL  ..... . LLLLLL  .LLLLLLLLLLLLLLLL    
  ....    .....LLLL.....        LLLL     ... ..LLLLLLLLLLLLL .LLLLL LLLLL.  
 ....      ...L      ...        LLLL  .-----  ...LLL    LLL   ..LL   LLL.   
  ..        .      ....          LLLL..|...|------------FFF-         ....   
   .     ....      .           ..LLLL..S...|...S...........|----------S---  
   ..   ......   .....        ....LLLL.---+-FF.|....}}}....S...|L...L|...|  
    ......LL... ..  ...      .....LLLL..L|...F.|....}}}....|--S|..\..S...|  
   ..  ...LLL....  ......     ....LLLL..L|...F.|...........|...|.....|--+-  
  ..    ......    ...L..     ....LLLL...L|FFFF.|------------...|.....|...|  
 .....   ...    ....LL.... .....LLLL....L|.....|    |...S..S...|L...L|----  
  ....   .        ...... ... ..LLLL....---+----- . |..-------|---S----      
  ..   ...       ..          .LLLL.....S...|   LLL |.........|.......|      
 ..   ..         .    ..      LLLL.....|...|  LL   |--FFF----|.......|      
 .  ...       .....  ...L      LLLL....---S-   LLL    LLL    ----S----      
 ....L..    ....  .....LL       LLLL      .     LLL  LLLLL     LL.LL        
  ...LL......      ...LLLLL  LLLLLLL      ..   LLLLLLLLLLLLLL LLLL.LL       
   ......           .LLL  LLLL  LLLL       ....LLLLL.....LLLLLL...LL        
                                 LLLL         ......LLLLL......LLLL         
]] });

-- Regions
des.region(selection.area(00,00,75,18), "unlit");

-- Branch and teleport points
des.levregion({ region = {00,00,24,18}, region_islev=1, exclude={00,00,00,00}, exclude_islev=1, type="branch" })
des.teleport_region({region={00,00,24,18}, exclude = {00,00,00,00} })

-- Protect the walls
des.non_diggable(selection.area(35,00,75,18))
des.non_passwall(selection.area(35,00,75,18));

-- Stairs up and down
des.stair("up",02,03)
des.stair("down",41,01)

-- Doors
des.door("locked",39,05)
des.door("locked",39,12)
des.door("locked",42,06)
des.door("locked",42,11)
des.door("locked",42,14)
des.door("locked",47,05)
des.door("locked",59,06)
des.door("locked",62,07)
des.door("locked",59,10)
des.door("locked",56,10)
des.door("locked",65,14)
des.door("locked",65,11)
des.door("locked",69,07)
des.door("locked",72,08)
des.door("locked",70,05)

des.drawbridge({ dir="east", state="closed", x=40,y=08})

-- A few random demons
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")

-- A few random traps
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")

des.trap("magic")
des.trap("magic")
des.trap("magic")

des.trap("anti magic")
des.trap("anti magic")

-- Outer defences
des.monster({ id = "xorn", x = 10, y = 05, peaceful=0, asleep=1 })
des.monster({ id = "xorn", x = 02, y = 10, peaceful=0, asleep=1 })
des.monster({ id = "xorn", x = 11, y = 09, peaceful=0, asleep=1 })
des.monster({ id = "xorn", x = 16, y = 01, peaceful=0, asleep=1 })
des.monster({ id = "xorn", x = 22, y = 08, peaceful=0, asleep=1 })

des.monster({ id = "fire giant", x = 03, y = 15, peaceful=0, asleep=1 })
des.monster({ id = "fire giant", x = 04, y = 17, peaceful=0, asleep=1 })
des.monster({ id = "fire giant", x = 06, y = 14, peaceful=0, asleep=1 })
des.monster({ id = "fire giant", x = 06, y = 17, peaceful=0, asleep=1 })
des.monster({ id = "fire giant", x = 08, y = 16, peaceful=0, asleep=1 })

des.monster({ id = "fire elemental", x = 11, y = 08, peaceful=0, asleep=1 })
des.monster({ id = "fire elemental", x = 05, y = 16, peaceful=0, asleep=1 })
des.monster({ id = "fire elemental", x = 17, y = 02, peaceful=0, asleep=1 })
des.monster({ id = "fire elemental", x = 20, y = 10, peaceful=0, asleep=1 })
des.monster({ id = "fire elemental", x = 22, y = 17, peaceful=0, asleep=1 })
des.monster({ id = "fire elemental", x = 24, y = 15, peaceful=0, asleep=1 })

des.monster({ id = "hell hound", x = 21, y = 08, peaceful=0, asleep=1 })
des.monster({ id = "hell hound", x = 19, y = 10, peaceful=0, asleep=1 })
des.monster({ id = "hell hound", x = 23, y = 09, peaceful=0, asleep=1 })
des.monster({ id = "hell hound", x = 21, y = 11, peaceful=0, asleep=1 })

des.monster({ id = "red dragon", x = 12, y = 15, peaceful=0, asleep=1 })

des.trap("board",06,07)
des.trap("board",01,14)
des.trap("board",09,11)
des.trap("board",12,04)
des.trap("board",18,06)
des.trap("board",19,05)
des.trap("board",11,16)
des.trap("board",17,13)
des.trap("board",19,15)

-- Guardians at the crossing
des.monster({ class = "B", x = 32, y = 05, peaceful=0, asleep=1 })
des.monster({ class = "B", x = 35, y = 06, peaceful=0, asleep=1 })
des.monster({ class = "B", x = 30, y = 12, peaceful=0, asleep=1 })
des.monster({ class = "B", x = 34, y = 11, peaceful=0, asleep=1 })

des.monster({ id = "hezrou", x = 31, y = 08, peaceful=0, asleep=1 })
des.monster({ id = "hezrou", x = 29, y = 12, peaceful=0, asleep=1 })
des.monster({ id = "hezrou", x = 33, y = 08, peaceful=0, asleep=1 })
des.monster({ id = "hezrou", x = 31, y = 07, peaceful=0, asleep=1 })

des.monster({ id = "nalfeshnee", x = 37, y = 09, peaceful=0, asleep=1 })
des.monster({ id = "nalfeshnee", x = 35, y = 12, peaceful=0, asleep=1 })
des.monster({ id = "nalfeshnee", x = 39, y = 10, peaceful=0, asleep=1 })

des.monster({ id = "fire elemental", x = 35, y = 04, peaceful=0, asleep=1 })
des.monster({ id = "fire elemental", x = 32, y = 14, peaceful=0, asleep=1 })

des.trap("board",28,10)
des.trap("board",32,07)

-- The cage trap
des.monster("black dragon", 43,09)
des.monster("pit fiend",41,05)
des.monster("pit fiend",41,12)
des.monster("nalfeshnee",46,10)
des.monster("bone devil",46,08)
des.monster("bone devil",44,05)
des.monster("bone devil",46,05)

-- The water room
des.monster("water demon",50,06)
des.monster("water demon",51,08)
des.monster("water demon",55,08)
des.monster("water demon",56,05)
des.monster("water nymph",48,06)
des.monster("water nymph",49,08)
des.monster("water nymph",56,08)
des.monster("water nymph",58,06)
des.monster("water nymph",53,05)
des.monster("water nymph",53,08)

des.monster("nalfeshnee",58,08)

des.monster("gremlin",48,08)

-- Secret rooms and passages are empty

-- Gallery
des.monster({ id = "arch-lich", x = 56, y = 12, peaceful=0, asleep=1 })
des.monster("nalfeshnee",55,12)
des.monster("nalfeshnee",54,12)
des.monster("blue dragon",59,12)

des.trap("board",54,10)

-- Southern Lava Walk
des.monster("fire elemental",48,16)
des.monster("fire elemental",55,17)
des.monster("fire elemental",63,16)
des.monster("salamander",52,17)
des.monster("salamander",62,18)
des.monster("fire vampire",68,16)
des.monster("red dragon",49,11)

des.object("chest",49,11)
des.object("ruby",49,11)
des.object("ruby",49,11)
des.object("*",49,11)
des.object("*",49,11)
des.object("*",49,11)
des.object("*",49,11)
des.object("*",49,11)
des.object("*",49,11)

-- GOLD:random,(49,11)

-- Antichamber and throne room
des.monster("random",65,12)
des.monster("random",64,12)
des.monster("random",66,12)

des.monster("nalfeshnee",62,13)
des.monster("nalfeshnee",68,13)

des.trap("board",65,13)
des.trap("magic",64,13)
des.trap("magic",66,13)

-- The fellow in residence
des.monster({id="Demogorgon", x=66, y=07})

des.monster("pit fiend",65,08)
des.monster("balrog",67,08)
des.monster("marilith",64,09)
des.monster("nalfeshnee",68,09)
des.monster("succubus",67,07)
des.monster("succubus",65,07)

des.monster("fire vampire",66,18)

des.object("chest",66,06)
des.object("chest",64,08)
des.object("chest",68,08)

-- Fake stairs
des.monster({ id = "giant mimic", x = 71, y = 09, appear_as = "ter:staircase down" })

-- Northern Lava Walk
des.monster("fire elemental",64,02)
des.monster("fire elemental",57,02)
des.monster("fire elemental",50,01)
des.monster("salamander",54,02)
des.monster("salamander",67,01)
des.monster("fire vampire",57,00)

-- Exit chamber
des.monster({ id = "pit fiend", x = 42, y = 01, peaceful=0, asleep=1 })

des.trap("board",45,01)