-- SCCS Id: @(#)gehennom.des	3.4	1996/11/09
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
-- the city of Dis
-- Ported from GruntHack
-- Converted to lua by hackemslashem
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor", "shortsighted")

des.level_init({ style="mines", fg=".", bg="L", smoothed=true, joined=true, walled=true })

--0       1         2         3         4         5         6         7     
--23456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "center", valign = "center", map = [[
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
LLLLLLLL.....................LLLLLLLL
LLLLL....-------------------....LLLLL
LL....----.................----....LL
L..----.....-------------.....----..L
..--.....----...........----.....--..
.||....---....----S----....---....||.
.|....--....---.......---....--....|.
.|...||...---..I-----I..---...||...|.
.|...|....|...I|-...-|I...|....|...|.
.|...S....|...IS.....SI...|....S...|.
.|...|....|...I|-...-|I...|....|...|.
.|...||...---..I-----I..---...||...|.
.|....--....---.......---....--....|.
.||....---....----S----....---....||.
..--.....----...........----.....--..
L..----.....-------------.....----..L
LL....----.................----....LL
LLLLL....-------------------....LLLLL
LLLLLLLL.....................LLLLLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
]] });

-- #RANDOM_MONSTERS:'&','i','M','Z','V','W'

des.levregion({ region = {01,01,79,20}, region_islev=1, exclude={21,1,59,20}, exclude_islev=1, type="stair-up" })
des.stair("down", 18,10)
-- des.levregion({ region = {01,00,15,20}, region_islev=1, exclude={15,1,70,16}, exclude_islev=1, type="branch" })
-- des.teleport_region({region={01,00,15,20}, exclude = {15,01,70,16} })

des.mazewalk(18,01,"north")
des.mazewalk(18,19,"south")

des.drawbridge({ dir="south", state="closed", x=18,y=01})
des.drawbridge({ dir="north", state="closed", x=18,y=19})

-- Non diggable walls
des.non_diggable(selection.area(00,00,36,20))

-- the guy in charge
des.monster({id="Dispater", x=18, y=10})

-- his minions
des.monster("iron golem",18,09)
des.monster("pit fiend",18,11)
des.monster("bone devil",17,10)
des.monster("bone devil",19,10)

-- their subordinates
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")

des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")
des.monster("i")

-- the damned
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")

des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")

des.monster("V")
des.monster("V")
des.monster("V")
des.monster("V")
des.monster("V")

des.monster("wraith")
des.monster("wraith")
des.monster("wraith")
des.monster("wraith")
des.monster("wraith")

-- a bit of loot
des.object("[")
des.object("[")
des.object(")")
des.object(")")
des.object("*")
des.object("!")
des.object("?")

-- traps!
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")

des.trap("magic")
des.trap("magic")
des.trap("magic")

des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")
