-- NetHack 3.6	Cartomancer.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.8 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip", "hot");

des.map([[
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLL................LLLLLLLLLLLLLLLLLLLLLLLLLLLLL
LLLLLLLLLLLLLLLLLLLLL................................LLLLLLLLLLLLLLLLLLLLL
LLLLLLLLLLLLLLL............................................LLLLLLLLLLLLLLL
LLLLLLLLLL......................................................LLLLLLLLLL
LLLLLLL............................................................LLLLLLL
LLLLL.......................LLLLLLLLLLLLLLLLLL.......................LLLLL
LLL....................LLLLLLLLLLLLLLLLLLLLLLLLLLL.....................LLL
L....................LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL....................L
L....................LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL....................L
L....................LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL....................L
LLL....................LLLLLLLLLLLLLLLLLLLLLLLLLLL.....................LLL
LLLLL.......................LLLLLLLLLLLLLLLLLL.......................LLLLL
LLLLLLL............................................................LLLLLLL
LLLLLLLLLL......................................................LLLLLLLLLL
LLLLLLLLLLLLLLL............................................LLLLLLLLLLLLLLL
LLLLLLLLLLLLLLLLLLLLL................................LLLLLLLLLLLLLLLLLLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLL................LLLLLLLLLLLLLLLLLLLLLLLLLLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")

-- Stairs
des.stair("up", 11, 10)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Objects
des.object({ id = "credit card", x=60, y=10,buc="blessed",name="The Holographic Void Lily" })
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()


-- Rubble
for i = 1,math.random(2, 6) do
    des.object("boulder")
end
for i = 1,math.random(5, 7) do
    des.object("rock")
end

des.object({ id="corpse",montype="duelist" })
des.object({ id="corpse",montype="duelist" })
des.object({ id="corpse",montype="duelist" })
des.object({ id="corpse",montype="duelist" })
des.object({ id="corpse",montype="cartomancer" })
des.object({ id="corpse",montype="cartomancer" })

-- traps
des.trap()
des.trap()
des.trap()

-- monsters.
des.monster({id="Dal Zethire", x=60, y=10})
des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})

if percent(50) then
    des.monster({id="assassin bug",peaceful=0})
else
    des.monster({id="ha-naga",peaceful=0})
end

if percent(50) then
    des.monster({id="assassin bug",peaceful=0})
else
    des.monster({id="ha-naga",peaceful=0})
end
des.wallify()
