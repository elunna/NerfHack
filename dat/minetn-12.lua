-- NetHack 3.7	mines.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.25 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Minetown variant 12
-- Forge Town -- Minetown

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip", "inaccessibles")
des.message("You hear the clang of hammers on anvils.");
des.level_init({ style="mines", fg=".", bg="-", smoothed=true, joined=true,lit=1,walled=true })

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00|----------------------.---------------    ...................|  ----
01|....|.....|..........|.|.............|.................+.....S##....
02|S---|.....|..........|.|.............|................-|.....|  |...
03|....|.....|..........+.|.............|-........|.......|.....|  ....
04|....|.....|..........|.|.............|.........--|.....|.....S####  
05|--+-----+-------------.----------+----....T......|.....------|   #  
06..............................|...................|.....|.....|   ###
07|+--------------------|.......+.|---+-----S------------+|.....|     #
08......................|...T...|.|......|  ##########  |.|.....|     #
09..---+---.............|.......|.|......| ###########  |.+.....|     #
10..|.....|.............|.....---.|------|L###########  |.|.....|  ####
11..|.....|.....|+|-----|.....|...|....|  L############ |+------|  #   
12..|-----|.....|.......|.....|.|-|....|  L###########  |.......| .#...
13..............|.......|.....|.+K|....|   L#########   |....uuu| .....
14..............|.......|.....-.---....-----------------|..uu.}}}}.....
15..............+.......+..............}}}}}}}}}}}}}}}}}}}}}}}}}}}u....
16...............................uuu}}}}}}}}--}}-}}}}-}}}}}-}}}}}}}}}}}
]]);

des.region(selection.area(01,01,60,15), "lit")

des.stair("up", 67,01)
des.stair("down", 66,14)

-- A few fountains.
des.feature("fountain",19,09)
des.feature("fountain",03,14)

if percent(50) then
    des.feature("forge", 43,09)
    des.feature("forge", 48,12)
else
    des.feature("forge", 43,12)
    des.feature("forge", 48,09)
end
-- The masouleum
--des.region({ region={14,11, 22,16}, lit=1, type="temple", filled=1 })
-- Not very religious folk...
des.altar({ x=18, y=13, align=align[1], type="altar", cracked=1 })
-- The priest gave up...
des.monster({ id = "aligned cleric", x = 18, y = 13, peaceful = 1 })

-- Doors
des.door("closed",56,01)
des.door("closed",30,07)
des.door("closed",55,07)
des.door("locked",15,11)
des.door("closed",55,11)
des.door("closed",14,15)
des.door("closed",22,15)

-- shop doors
des.door("closed",09,05)
des.door("closed",22,03)
des.door("closed",34,05)
des.door("closed",36,07)
des.door("closed",56,09)

-- The shops
if percent(50) then
    des.region({ region={12,01, 21,04}, lit=1, type="armor shop", filled=1 })
else
    des.region({ region={57,06, 61,10}, lit=1, type="armor shop", filled=1 })
end
des.region({ region={06,01, 10,04}, lit=1, type="tool shop", filled=1 })
des.region({ region={25,01, 37,04}, lit=1, type="weapon shop", filled=1 })
des.region({ region={03,10, 07,11}, lit=1, type="candle shop", filled=1 })
des.region({ region={33,08, 38,09}, lit=1, type=monkfoodshop(), filled=1 })

-- Wary citizens
des.monster("dwarf")
des.monster("dwarf")
des.monster("dwarf")
des.monster("dwarf")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("gnome")
des.monster("dwarf lord")
des.monster("dwarf ruler")

-- The Watch.
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watch captain", peaceful = 1 })

-- What's this guy doing here?? (And where are all the hammers?)
des.monster("k", 1, 3)
des.object({ id = "chest", locked = 1, x = 2, y = 1 });
des.object({ id = "chest", locked = 1, x = 3, y = 1 });
des.object({ id = "chest", locked = 1, x = 4, y = 1 });