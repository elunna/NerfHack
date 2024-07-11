-- NetHack 3.6	Cartomancer.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.8 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor", "noteleport")
des.level_init({ style="mines", fg=".", bg=" ", smoothed=true, joined=true, lit=1, walled=true })

-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")

-- Stairs
des.stair("up")
des.stair("down")

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Objects
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
des.object()
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

-- Random monsters.
des.monster({id="guardian naga", x=17, y=07,peaceful=0})
des.monster({id="guardian naga", x=18, y=08,peaceful=0})
des.monster({id="guardian naga", x=18, y=09,peaceful=0})
des.monster({id="guardian naga", x=17, y=10,peaceful=0})
des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})
des.monster({class="N",peaceful=0})
des.monster({class="S",peaceful=0})
des.monster({class="S",peaceful=0})
des.monster({class="S",peaceful=0})
des.monster({class="S",peaceful=0})
des.monster({class="S",peaceful=0})
des.monster({class="S",peaceful=0})
des.monster({class="S",peaceful=0})
des.monster({id="assassin bug",peaceful=0})
des.monster({id="assassin bug",peaceful=0})

des.monster({id="skeleton",peaceful=0})
des.monster({id="skeleton",peaceful=0})
des.monster({id="human zombie",peaceful=0})

des.object({ id="corpse",montype="duelist" })
des.object({ id="corpse",montype="duelist" })
des.object({ id="corpse",montype="duelist" })
des.object({ id="corpse",montype="duelist" })
des.object({ id="corpse",montype="cartomancer" })
des.object({ id="corpse",montype="cartomancer" })

--
--	The "goal" level for the quest.
--
--	Here you meet Dal Zethire your nemesis monster.  You have to
--	defeat Dal Zethire in combat to gain the artifact you have
--	been assigned to retrieve.
--
