-- NetHack 3.6	Cartomancer.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.8 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel");

des.map([[
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
LLLLL.............................LLLLL
LL...................................LL
LL...................................LL
LL...................................LL
L.....................................L
L.....................................L
L.................LLL.................L
L................LLLLL................L
L................LLLLL................L
L.................LLL.................L
L.....................................L
L.....................................L
LL...................................LL
LL...................................LL
LL...................................LL
LLLLL.............................LLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")

-- Stairs
des.stair("up", 19,01)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Objects
des.object({ id = "credit card", x=32, y=10,buc="blessed",name="The Holographic Void Lily" })
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
des.monster({id="Dal Zethire", x=32, y=10})
des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})
des.monster("assassin bug")
des.monster("assassin bug")
des.monster("assassin bug")
des.monster("assassin bug")
des.wallify()
