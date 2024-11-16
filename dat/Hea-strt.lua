-- NetHack Healer Hea-strt.lua	$NHDT-Date: 1652196004 2022/05/10 15:20:04 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.2 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991, 1993 by M. Stephenson, P. Winner
-- NetHack may be freely redistributed.  See license for details.
--
--
--    The "start" level for the quest.
--
--    Here you meet your (besieged) class leader, Hippocrates
--    and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor", "noflip")

des.map([[
PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
PPPPu......uPPPPu...uPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPuPuuPPPPPu....uPPPPPPPP
PPPu........uPPPPuuuPPPPPuuuuuuuuuuuuuuuuuuuuuuuuuPPPPuuPPPPPu......uPPPPPPP
PPu..........uPPPPPPPPu............................uPPP...PPPPu....uPPPPPPPP
PuuuuuPPPPPPPPPPPPPPPu..............................uPPPPPPPPPPPPPPPPPPPPPPP
PPPPuuuuPPPPPPPPPPPPu.................................uPPPPPuPPPPPPPPPPPPPPP
PPPPu......uPPPPPu........-----------------------.......uPPuuuPPPPPPPu...uPP
PPPu..........uPPPPPu...--|.|......S..........S.|--....uPPPPuPPPPPPPu.....uP
PPPPu........uPPPPPu....|.S.|......-----------|S|.|.....uPPPPPPuPPPu.....uPP
PPPPPPu....uPPPPPPu.....|.|.|......|...|......|.|.|....uPPPPPPuuuPPu.....uPP
PPPPPPPPPPPPPPPPPPPu....+.|.|......S.\.S......|.|.+.....uPPPPPPuPPPPu.....uP
PPPuuuPPPPPuuuPPPPu.....|.|.|......|...|......|.|.|......uPPPPPPPPPPPu...uPP
PPu...uPPPu...uPPPu.....|.|S|-----------......|.S.|.....uPPPPPPPPPPPPPPPPPPP
PPPuuPPPPPuuuPPPPu......--|.S..........S......|.|--....uPPPPPPPPPuuuuPPPPPPP
PPPPPPPPPPPPPPPPu.........-----------------------.........uPPPPPu........uPP
PPPPPPPPPPPPPPPPPu......................................uPPPPPPu..........uP
PPPu...........uPPPPu.................................uPPP..PPPPu........uPP
PPu.............uPPPPPuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuPPPP...PPPPu......uPPP
PPPu...........uPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPu..uPPPPPP
PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
]]);

des.replace_terrain({ region={01,01, 74,18}, fromterrain="P", toterrain=".", chance=10 })

-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
-- Stairs
des.stair("down", 37,9)
-- Portal arrival point
des.levregion({ region = {04,12,04,12}, type="branch" })
-- altar for the Temple
des.altar({ x=32,y=09,align="neutral",type="altar", cracked=nh.rn2(2) })
-- Doors
des.door("locked",24,10)
des.door("closed",26,08)
des.door("closed",27,12)
des.door("locked",28,13)
des.door("closed",35,07)
des.door("locked",35,10)
des.door("locked",39,10)
des.door("closed",39,13)
des.door("locked",46,07)
des.door("closed",47,08)
des.door("closed",48,12)
des.door("locked",50,10)
-- Hippocrates
des.monster({ id = "Hippocrates", coord = {37, 10}, inventory = function()
   des.object({ id = "silver dagger", spe = 5 });
end })
-- The treasure of Hippocrates
des.object("chest", 37, 10)
-- intern guards for the audience chamber
des.monster("attendant", 29, 08)
des.monster("attendant", 29, 09)
des.monster("attendant", 29, 10)
des.monster("attendant", 29, 11)
des.monster("attendant", 40, 09)
des.monster("attendant", 40, 10)
des.monster("attendant", 40, 11)
des.monster("attendant", 40, 13)
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- Random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
-- Monsters on siege duty.
des.monster("rat")
des.monster("rat")
des.monster("rat")
des.monster("rat")
des.monster("rat")
des.monster("rat")
des.monster("rat")
des.monster("rat")
des.monster("wererat")
des.monster("wererat")
des.monster("giant eel")
des.monster("shark")
des.monster(";")

-- Guarantee adult dragons appear
local dragons = { "gray dragon", "gold dragon", "silver dragon",
                  "red dragon", "white dragon", "orange dragon",
                  "black dragon", "blue dragon", "green dragon",
                  "yellow dragon", "shimmering dragon" };
shuffle(dragons)
-- 5 adults
des.monster({ id = dragons[1], peaceful=0 })
des.monster({ id = dragons[2], peaceful=0 })
des.monster({ id = dragons[3], peaceful=0 })
des.monster({ id = dragons[4], peaceful=0 })
des.monster({ id = dragons[5], peaceful=0 })

des.monster({ class = "D", peaceful=0 })
des.monster({ class = "D", peaceful=0 })
des.monster({ class = "D", peaceful=0 })
des.monster({ class = "D", peaceful=0 })
des.monster({ class = "D", peaceful=0 })

des.monster({ class = "S", peaceful=0 })
des.monster({ class = "S", peaceful=0 })
des.monster({ class = "S", peaceful=0 })
des.monster({ class = "S", peaceful=0 })
des.monster({ class = "S", peaceful=0 })
