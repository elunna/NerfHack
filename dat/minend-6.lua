-- NetHack mines minend-6.lua	$NHDT-Date: 1652196029 2022/05/10 15:20:29 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Mine end level variant 6
-- Gnome King's Apiary (Kelly Bailey)
-- Ported to 3.7 (from SlashTHEM) by hackemslashem

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.map([[
-----                                ------------------------------------  
|...|--   ---------------------------|..................................|  
|.....|---|.............................................................|  
|..|..........-----------------------------------..------------S-----...|  
|..----.......|  |...............| ||.||...S...............-..|.|   |...|  
|.......------|---...---|....|...| --.--...|...........--.....|.| ---...|  
----....|.....|......|  |....|...--|...|-----.-----------------.| |...{.|  
   --...|.........------|.-----..|.......|  -B-----------------S------..|  
..  |.....---------|....|.....|--|.......|--|.........B..........|...|----|
..  |--...|   |....|...---....+.............+.........B..........S...+.S..|
      |..---| |...............|--|.......|--|.........B..........|...|----|
|-----|.....|-|.|..---|...-----  |.......|  -B-----------------S------..|  
|...........|.|.|.....|...|  ------|...|-----.-----------------.| |...{.|  
|......-----|...|.....-----  |.....--.--...|..-..........-....|.| ---...|  
|..|............|.........|  |.....||.||...S.........--.......|.|   |...|  
|..|..|.....-------------------..----------------..------------S-----...|  
|-----|.................................................................|  
      |..|---------------------------|..................................|  
      ----                           ------------------------------------  
]]);
-- Dungeon Description
des.region(selection.area(00,00,74,18),"unlit")
des.region({ region={45,08,53,10}, lit=1, type="beehive", filled=1 })

-- Normal Doors
des.door("closed",30,09)
des.door("closed",44,09)
des.door("locked",69,09)
-- Secret Doors
des.door("locked",43,04)
des.door("locked",43,14)
des.door("locked",63,03)
des.door("locked",63,07)
des.door("locked",63,11)
des.door("locked",63,15)
des.door("locked",71,09)

-- Stairs
des.stair("up", 37,09)

des.engraving({ x=41, y=09, type = "engrave", text = "The Gnome King's Royal Apiary" });
des.engraving({ x=42, y=09, type = "engrave", text = "Keep Out!" });

-- No digging
des.non_diggable(selection.area(00,00,74,18))

-- Statues
des.object({ id = "statue", x=49, y=09, montype="queen bee", historic=1 })
des.object({ id = "statue", x=55, y=09, montype="killer bee", historic=1 })
des.object({ id = "statue", x=61, y=09, montype="gnome king", historic=1 })

-- Treasure chamber
-- Darshan - since we need room for the downstairs,
--          shifted these gems over to the same square
--          as those above
des.object("luckstone",72,09)
des.object("diamond",72,09)
des.object("diamond",72,09)
des.object("emerald",72,09)
des.object("emerald",72,09)
des.object("emerald",72,09)
des.object("amethyst",72,09)
des.object("amethyst",72,09)
des.object("ruby",72,09)
des.object("ruby",72,09)

des.object("*",72,09)
des.object("*",72,09)
des.object("*",72,09)
des.object("*",72,09)
des.object("*",72,09)
des.object("*",72,09)
des.object("*",72,09)

--Random objects
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("(")
des.object("(")
des.object("wand of death",01,08)
des.object()
des.object()
des.object()

--Monsters
des.monster({ id = "air elemental", x=0, y=8, peaceful=0 })
des.monster({ id = "air elemental", x=0, y=9, peaceful=0 })
des.monster({ id = "air elemental", x=1, y=8, peaceful=0 })
des.monster({ id = "air elemental", x=1, y=9, peaceful=0 })

des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")
des.monster("a")

des.monster("F")
des.monster("F")
des.monster("F")
des.monster("F")
des.monster("F")
des.monster("F")

des.monster({ id = "gnomish wizard", x=45, y=8, peaceful=0 })
des.monster({ id = "black light", x=36, y=9, peaceful=0 })

des.trap("spear", 68,08)
des.trap("spear", 68,09)
des.trap("spear", 68,10)
des.trap("grease", 67,08)
des.trap("grease", 67,09)
des.trap("grease", 67,10)
des.trap("falling rock", 66,08)
des.trap("falling rock", 66,09)
des.trap("falling rock", 66,10)

des.trap("land mine", 38,09)
des.trap("board", 43,09)
des.trap("polymorph", 45,09)
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()