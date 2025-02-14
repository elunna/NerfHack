-- NetHack gehennom orcus-2.lua	$NHDT-Date: 1652196033 2022/05/10 15:20:33 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
-- Copyright (c) 1989 by Jean-Christophe Collet
-- Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
-- Mik Clarke, January 21st, 2001
-- Ported from UnNetHack, original source is the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
-- The New Orcus Level
-- A ghost town

des.level_init({ style="mazegrid", bg ="-" });
-- INIT_MAP:solidfill,' '
des.level_flags("mazelevel", "shortsighted")

--0       1         2         3         4         5         6         7     
--23456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
 -----                        --------------------                          
 |...|..       .............. |.......|.....|....|     |..........----------
 |...|...........----------.. |.......|.....|....|.....|..........|........|
 |...+...........|........|...|.......|--+-----+--.....B..........|........|
 -----..---+---..|........+...----+----.............{..B..........+......\.|
 |...+..|.....|..|........|.................------.....B..........|........|
 |...|..|.....|..----------..}}}}}}}........+....|.....|..........|........|
 |...|..--...--.........}}}}}}}}}}}}}}}}}...|....|.....|..........------S---
 -----}}}}.}.}}}}...}}}}}}}}}}}}}}}}}}}}}}}}------.....---------+--   |...| 
}}}}}}}}}}}.}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}..............   |...| 
}}}}}}}}}}.}.}}}}}}}}}}}}}}}-----------}}}}}}}}}}}}}}}}}............  ----- 
}}}}}}}}--...--}}}}}}}}.....|.........|..}}}}}}}}}}}}}}}}}}}}}.......       
}}}}....|.....|.............|.........+......}}}}}}}}}}}}}}}}}}}}}}}}}}}    
-------.|.....|..----B----..|.........|................}}}}}}}}}}}}}}}}}}}}}
|.....|.---+---..|.......|..-----------..-----+----..............}}}}}}}}}}}
|.....|..........B.......B...............|........|..-------...........}}}}}
|--+--|...----+---.......-----+----------|........|..|.....-----...--+----- 
   ...... |......|.......|........|......+........|..+.....|...+.. |......| 
          |......|.......|........|......|........|  |.....|...|   |......| 
          -----------------------------------------  -----------   -------- 
]]);

-- Entire main area
des.region(selection.area(01,00,75,19),"unlit")
des.stair("down", 71,04)
des.stair("up", 61,18)

des.teleport_region({ region = {26,17,40,18}, dir="down" })

-- Doors
des.door("random",03,16)
des.door("random",05,03)
des.door("locked",11,04)
des.door("closed",11,14)
des.door("random",14,16)
des.door("nodoor",26,04)
des.door("random",30,16)
des.door("random",34,04)
des.door("closed",38,12)
des.door("random",41,03)
des.door("locked",41,17)
des.door("random",44,06)
des.door("random",46,14)
des.door("random",53,17)
des.door("random",63,17)
des.door("locked",64,08)
des.door("closed",66,04)
des.door("random",69,16)
des.door("locked",72,07)

-- Special rooms
des.altar({ x=31,y=12,align="noalign",type="sanctum" })

des.region({ region={18,14,24,18},lit=0,type="morgue",filled=1 })
des.region({ region={56,01,65,07},lit=0,type="morgue",filled=1 })
des.region({ region={01,14,05,15},lit=0,type="shop",filled=1 })
des.region({ region={39,01,43,02},lit=0,type="shop",filled=1 })

-- REGION:(18,03,25,05),unlit,"temple"

des.door("random",05,05)

--ALTAR:(20,04),noncoaligned,altar
--OBJECT:('%',"corpse"),(23,03),montype:"priest",0

-- Some traps.
des.trap("spiked pit")
des.trap("sleep gas")
des.trap("anti magic")
des.trap("anti magic")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("magic")
des.trap("magic")
des.trap("magic")
des.trap("rust")

-- Some random objects
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()

-- The resident nasty
des.monster("Orcus",71,04)
--OBJECT:('/',"death")

-- And its preferred companions
des.monster("human zombie",69,03)
des.monster("shade",67,06)
des.monster("shade",73,02)

des.monster("vampire",73,05)
des.monster("vampire",69,04)
des.monster("vampire lord",70,05)
des.monster("vampire lord",72,06)
des.monster("vampire royal")
des.monster("vampire royal")

-- Some loot...
des.object({ id = "chest", locked = 1, x = 71, y = 09,
             contents = function()
                des.object("!")
                des.object("?")
             end
});

des.object({ id = "chest", locked = 1, x = 72, y = 09,
             contents = function()
                des.object("potion of sickness")
                des.object("amulet of strangulation")
             end
});

des.object({ id = "chest", locked = 1, x = 73, y = 09,
             contents = function()
                des.object("potion of blindness")
                des.object("scroll of create monster")
             end
});

-- # ...and a guardian
des.monster("green slime",71,08)
des.monster("green slime",73,08)

-- # ...and one final trap
des.trap("sleep gas",72,08)

-- Randomly placed companions
des.monster("skeleton")
des.monster("skeleton")
des.monster("skeleton")
des.monster("skeleton")
des.monster("skeleton")
des.monster("shade")
des.monster("shade")
des.monster("shade")
des.monster("shade")
des.monster("giant zombie")
des.monster("giant zombie")
des.monster("giant zombie")
des.monster("ettin zombie")
des.monster("ettin zombie")
des.monster("ettin zombie")
des.monster("human zombie")
des.monster("human zombie")
des.monster("human zombie")
des.monster("vampire")
des.monster("vampire")
des.monster("vampire")
des.monster("vampire lord")
des.monster("vampire lord")

-- A few more for the party
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()