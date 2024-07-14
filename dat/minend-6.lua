-- NetHack mines minend-1.lua	$NHDT-Date: 1652196029 2022/05/10 15:20:29 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Mine end level variant 6
-- Gnome King's Apiary (Kelly Bailey)
-- Ported to 3.7 by hackemslashem

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

-- ############################################################################

local place = { {08,16},{13,07},{21,08},{41,14},{50,04},{50,16},{66,01} }
shuffle(place)

-- make the entry chamber a real room; it affects monster arrival
des.region({ region={26,01,32,01}, lit=0, type="ordinary", irregular=1, arrival_room=true })

-- Secret doors
des.door("locked",07,16)
des.door("locked",22,08)
des.door("locked",26,08)
des.door("locked",40,14)
des.door("locked",50,03)
des.door("locked",51,16)
des.door("locked",66,02)
-- Stairs
des.stair("up", 36,04)
-- Non diggable walls

-- Niches
-- Note: place[6] empty
des.object("diamond",place[7])
des.object("emerald",place[7])
des.object("worthless piece of violet glass",place[7])
des.monster({ class="m", coord=place[7], appear_as="obj:luckstone" })
des.object("worthless piece of white glass",place[1])
des.object("emerald",place[1])
des.object("amethyst",place[1])
des.monster({ class="m", coord=place[1], appear_as="obj:loadstone" })
des.object("diamond",place[2])
des.object("worthless piece of green glass",place[2])
des.object("amethyst",place[2])
des.monster({ class="m", coord=place[2], appear_as="obj:flint" })
des.object("worthless piece of white glass",place[3])
des.object("emerald",place[3])
des.object("worthless piece of violet glass",place[3])
des.monster({ class="m", coord=place[3], appear_as="obj:touchstone" })
des.object("worthless piece of red glass",place[4])
des.object("ruby",place[4])
des.object("loadstone",place[4])
des.object("ruby",place[5])
des.object("worthless piece of red glass",place[5])
des.object({ id="luckstone", coord=place[5], buc="not-cursed", achievement=1 })
-- Random objects
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("(")
des.object("(")
des.object()
des.object()
des.object()
-- Random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
-- Random monsters
des.monster("gnome king")
des.monster("gnome lord")
des.monster("gnome lord")
des.monster("gnome lord")
des.monster("gnomish wizard")
des.monster("gnomish wizard")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("hobbit")
des.monster("hobbit")
des.monster("dwarf")
des.monster("dwarf")
des.monster("dwarf")
des.monster("h")
