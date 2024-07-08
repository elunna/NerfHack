-- NetHack 3.6	Cartomancer.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.8 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
-- File created 2/01/18 by NullCGT
--
--	The "start" level for the quest.
--
--	Here you meet your (besieged) class leader, Shaman Karnov
--	and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel");

des.level_flags("noteleport", "hardfloor")
des.map([[
............................................................................
............................................................................
............................................................................
...................................|..|.....................................
............|-----------------------++-----------------------|..............
............|......................+..+......................|..............
............|......................|..|.}}}}}}}}}}}}}}}}}}}}.|..............
............|......................|..|.}..................}.|..............
............|......................|..|.}..................}.|..............
............|-----------+----------|..|.}..................}.|..............
............|......................S..S....................}.|..............
............|......................|..|.}..................}.|..............
............|......................|..|.}..................}.|..............
............|......................|..|.}..................}.|..............
............|......................|..|.}}}}}}}}}}}}}}}}}}}}.|..............
............|......................|..|......................|..............
............|-----------------------++-----------------------|..............
...................................|..|.....................................
............................................................................
............................................................................
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
-- Stairs
des.stair("down", 17,07)
-- Portal arrival point
des.levregion({ region = {07,17,07,17}, exclude = {0,0,0,0}, type="branch" })
-- Doors
des.door("locked",24,09)
des.door("locked",36,04)
des.door("locked",37,04)
des.door("locked",33,05)
des.door("locked",38,05)
des.door("locked",33,10)
des.door("locked",38,10)
des.door("locked",36,16)
des.door("locked",37,16)
-- The Lord of the Cards
des.monster({id="King of Games", x=17, y=08})
-- The treasure of the Lord of the Cards
des.object("chest", 18, 05)

-- students of the card training school
des.monster({id="duelist", x=47, y=07})
des.monster({id="duelist", x=47, y=13})
des.monster({id="duelist", x=18, y=07})
des.monster({id="duelist", x=19, y=13})
des.monster({id="duelist", x=20, y=07})
des.monster({id="duelist", x=21, y=13})
des.monster({id="duelist", x=22, y=07})
des.monster({id="duelist", x=23, y=13})
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- Random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
-- Monsters summoned by Dal Zethire.
des.monster({id="guardian naga", x=22, y=08,peaceful=0})
des.monster({id="cobra", x=08, y=20,peaceful=0})
des.monster({id="guardian naga", x=21, y=08,peaceful=0})
des.monster({id="cobra", x=03, y=14,peaceful=0})
des.monster({id="cobra", x=05, y=14,peaceful=0})
des.monster({id="cobra", x=07, y=14,peaceful=0})
des.monster({id="cobra",peaceful=0})
des.monster({id="guardian naga", x=55, y=15,peaceful=0})
des.monster({id="cobra",peaceful=0})
des.monster({id="cobra",peaceful=0})
des.monster({id="cobra",peaceful=0})
des.monster({id="cobra",peaceful=0})

--
--	The "locate" level for the quest.
--
--	Here you have to find the arena to go
--	further towards your assigned quest.
--
