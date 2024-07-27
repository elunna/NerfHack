-- NetHack 3.7	mines.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.25 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Minetown variant 9
-- Lavender Town -- Minetown, but spooky!
-- By Kestrel Gregorich-Trevor

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip", "inaccessibles")

des.level_init({ style="mines", fg=".", bg="-", smoothed=true, joined=true,lit=1,walled=true })

des.map([[
.......................................
.-------------------------------------.
.|...................................|.
.|.------....------..-------------+-.|.
.|.|....+....|....|..+...|.........|.|.
.|.|....|....|....|..|...|.........|.|.
.|.|....|....|....|..--------------|.|.
.|.|....|....+....|......|.........|.|.
...------....------......+.........|...
.........................-----------...
.|...................................|.
.|................--+--..............|.
.|................|...|..............|.
.|------+-+---....+...+...-----------|.
.|.......|...|....|...|...+..........|.
.|.......|...|....--+--...|..........|.
.|.......|...|............|..........|.
.-------------------------------------.
.......................................
]]);

-- The town is creepy. Therefore, the town is dark.
des.region(selection.area(01,01,37,18), "unlit")
des.levregion({ type="stair-up", region={01,03,20,19}, region_islev=1,
		exclude={00,01,37,17} });
des.levregion({ type="stair-down", region={61,03,75,19}, region_islev=1,
		exclude={00,01,37,17} })

-- A few fountains.
des.feature("fountain",05,11)

-- The masouleum
des.region({ region={19,12, 21,14}, lit=1, type="temple", filled=1 })
des.altar({ x=20,y=13,align=align[1],type="shrine"})

-- The big graveyard
local graveyard;
graveyard = selection.floodfill(27,14);
des.region({ region={27,14, 36,16},lit=0,type="morgue",filled=0 })
des.grave({ coord = graveyard:rndcoord(1), text = "Buried Alive" });
des.grave({ coord = graveyard:rndcoord(1) });
des.grave({ coord = graveyard:rndcoord(1) });
des.grave({ coord = graveyard:rndcoord(1) });
des.grave({ coord = graveyard:rndcoord(1) });
des.grave({ coord = graveyard:rndcoord(1) });
des.grave({ coord = graveyard:rndcoord(1) });
des.monster({ id = "skeleton", coord=graveyard:rndcoord(1), peaceful = 0, asleep = 1})
-- In SpliceHack, there were 2 random Z, but these could generate something like
-- a ghoul mage or more skeletons. We'll limit the difficulty to an occasional giant zombie.
des.monster({ id = "human zombie", coord=graveyard:rndcoord(1), peaceful = 0, asleep = 1})
if percent(75) then
	des.monster({ id = "human zombie", coord=graveyard:rndcoord(1), peaceful = 0, asleep = 1})
else
	des.monster({ id = "giant zombie", coord=graveyard:rndcoord(1), peaceful = 0, asleep = 1})
end

-- Doors
des.door("closed",26,14)
des.door("closed",22,13)
des.door("closed",20,11)
des.door("closed",20,15)
des.door("locked",08,13)
des.door("closed",08,04)
des.door("closed",13,07)
des.door("closed",21,04)
des.door("closed",25,08)
des.door("closed",34,03)

-- The shops
des.region({ region={10,14, 12,16}, lit=1, type="tool shop", filled=1 })
des.region({ region={26,07, 34,08}, lit=1, type="shop", filled=1 })
des.region({ region={22,04, 24,05}, lit=1, type="candle shop", filled=1 })
des.region({ region={04,04, 07,07}, lit=1, type=monkfoodshop(), filled=1 })

-- Wary citizens
des.monster("dwarf")
des.monster("gnomish wizard")
des.monster("gnomish wizard")
des.monster("gnomish wizard")
des.monster("gnome")
des.monster("gnome ruler")

-- Boo!
des.monster("dwarf zombie")
des.monster("dwarf zombie")
des.monster("dwarf zombie")
des.monster("gnome zombie")
des.monster("gnome zombie")
des.monster("ghost")
des.monster("ghost")
des.monster("human zombie", 05, 05)

-- A ghoulish gravekeeper.
des.monster({ id = "ghoul", peaceful = 1 })

-- The Watch.
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watch captain", peaceful = 1 })