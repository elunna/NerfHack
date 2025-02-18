-- NetHack 3.6	Cartomancer.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.8 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
-- File created 2/01/18 by NullCGT
--
--    The "start" level for the quest.
--
--    Here you meet your (besieged) class leader, Shaman Karnov
--    and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel");

des.level_flags("noteleport", "hardfloor", "noflip")
des.map([[
..................T...T........T.T....TT.....T..............................
..............TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.........................
..............TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.........................
..............TT.................................TT.........................
..............TT.|---------------++------------|.TT.........................
..............TT.|}.............+..+..........}|.TT.........................
..............TT.|..............|..|...........|.TT.........................
..............TT.|..............|..|...........|.TT.........................
..............TT.|..............|..|...........|.TT.........................
..............TT.|---+----------|..|...........|.TT.........................
..............TT.|..............S..S...........|.TT.........................
..............TT.|..............|..|...........|.TT.........................
..............TT.|..............|..|...........|.TT.........................
..............TT.|..............|..|...........|.TT.........................
..............TT.|}.............|..|..........}|.TT.........................
..............TT.|---------------++------------|.TT.........................
..............TT.................................TT.........................
..............TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.........................
..............TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.........................
.................T..T......T.....T..............TT..........................
]]);

-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")

des.replace_terrain({ region={00,00, 13,19}, fromterrain=".", toterrain="T", chance=20 })
des.replace_terrain({ region={50,00, 75,19}, fromterrain=".", toterrain="T", chance=20 })
-- Guarantee free spot for the portal
des.terrain({72,18}, ".")

-- Stairs
des.stair("down", 20,07)

-- Portal arrival point
des.levregion({ region = {72,18,72,18}, exclude = {0,0,0,0}, type="branch" })

-- Doors
des.door("locked",21,09)

des.door("locked",33,04)
des.door("locked",34,04)

des.door("locked",32,05)
des.door("locked",35,05)

des.door("locked",33,15)
des.door("locked",34,15)

-- The Lord of the Cards
des.monster({id="King of Games", x=43, y=10})

-- The treasure of the Lord of the Cards
des.object("chest", 43, 07)

-- students of the card training school
des.monster({id="duelist", x=43, y=07})
des.monster({id="duelist", x=43, y=13})
des.monster({id="duelist", x=20, y=07})
des.monster({id="duelist", x=21, y=13})
des.monster({id="duelist", x=22, y=07})
des.monster({id="duelist", x=23, y=13})
des.monster({id="duelist", x=24, y=07})
des.monster({id="duelist", x=25, y=13})

-- Non diggable walls
des.non_diggable(selection.area(17,04,47,15))

-- Random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()

-- Monsters summoned by Dal Zethire.
des.monster({id="guardian naga", x=21, y=03,peaceful=0})
des.monster({id="guardian naga", x=25, y=03,peaceful=0})
des.monster({id="guardian naga", x=21, y=16,peaceful=0})
if percent(50) then
    des.monster({id="assassin bug",x=25, y=16,peaceful=0})
else
    des.monster({id="ha-naga",x=25, y=16,peaceful=0})
end

des.monster({id="cobra", x=08, y=20,peaceful=0})

des.monster({id="cobra", x=03, y=14,peaceful=0})
des.monster({id="cobra", x=05, y=14,peaceful=0})
des.monster({id="cobra", x=07, y=14,peaceful=0})
des.monster({id="cobra",peaceful=0})
des.monster({id="cobra",peaceful=0})
des.monster({id="cobra",peaceful=0})
des.monster({id="cobra",peaceful=0})
des.monster({id="giant anaconda",peaceful=0})
des.monster({id="giant anaconda",peaceful=0})

des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})




--
--    The "locate" level for the quest.
--
--    Here you have to find the arena to go
--    further towards your assigned quest.
--
