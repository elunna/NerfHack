-- SCCS Id: @(#)gehennom.des	3.4	1996/11/09
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
-- the isle of Erytheia, Geryon's domain
-- Ported from GruntHack
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor", "noflip")

des.level_init({ style="mines", fg=".", bg="}", smoothed=true, joined=true, walled=true })

--0       1         2         3         4         5         6         7     
--23456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "center", valign = "center", map = [[
}}}}}}}}}}}}u.......T...........................u}}}}}}}}}}}
}}}uuuu}}}uuu....................................uuuuu}}}}}}
}uu....uu}}}}u..........FFFFFFFFFF....................uuuu}}
u........uuu}}u.........F........F......T.................uu
...........Tu}}u........F........F..........................
.............u}}u.......F........F...........----------.....
..............u}}}uuu...F........F...........|...|....|.....
...............uu}}}}u..FFFF++FFFF...........|...|....|.....
.................uuu}u.......................|...|....|.....
....T..............u}}uuuuuuuuuuuuu..........+...|....|....T
....................u}}u}}}}}}}}}}}uuu.......--+----+--.....
.....................u}#}uuuuuuuuu}}}}uuuuuuu|........|.....
.................T....uuuuuuuuuuuuuuu}}}}}}}}|........|.....
...................uuuuuu}}}}}uu}}}}}}uuuuuuu----------.....
...............uuuu}}}}}}}uuu}u}}uuuuu.T....................
uuuu........T.u}}}}}}uuuuu..uuuuu......................uuuuu
}}}}uuuu..uuuu}}uuuuu.................................u}}}}}
}}}}}}}}uu}}}}}u..............T....................uuu}}}}}}
}}}}}}}}}}}}uuuuu........................uuuuuuuuuu}}}}}}}}}
}}}}}}}}}}}}}}}}}u...T..................u}}}}}}}}}}}}}}}}}}}
]] });

-- Stairs
des.stair("down", 50,07)

des.levregion({ region = {01,01,20,19}, region_islev=1, exclude_islev=1, type="stair-up" })
--des.levregion({ region = {01,01,20,19}, region_islev=1, exclude={00,00,59,19}, exclude_islev=1, type="branch" })
des.teleport_region({region={01,01,20,19}, dir="down" })

des.region(selection.area(00,00,59,19),"lit")
des.region(selection.area(46,06,53,12),"unlit")

-- Non diggable walls
des.non_diggable(selection.area(45,05,54,13))

des.door("closed",28,07)
des.door("closed",29,07)
des.door("locked",45,09)
des.door("closed",47,10)
des.door("closed",52,10)

-- The fellow in residence
des.monster({id="Geryon", x=51, y=08})

-- his herd
des.monster("q",25,03)
des.monster("q",27,03)
des.monster("q",29,03)
des.monster("q",31,03)
des.monster("q",26,04)
des.monster("q",28,04)
des.monster("q",30,04)
des.monster("q",32,04)
des.monster("q",25,05)
des.monster("q",27,05)
des.monster("q",29,05)
des.monster("q",31,05)
des.monster("q",26,06)
des.monster("q",28,06)
des.monster("q",30,06)
des.monster("q",32,06)

-- its guard
des.monster("hell hound",28,08)

-- the eponymous residents
des.monster("n")
des.monster("n")
des.monster("n")
des.monster("n")
des.monster("n")
des.monster("n")
des.monster("n")
des.monster("n")
des.monster("n")
des.monster("n")

-- some other denizens
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

-- a bit of loot
des.object("[")
des.object("[")
des.object(")")
des.object(")")
des.object("(")

des.object("/")
des.object("=")
des.object("?")
des.object("?")
des.object("!")
des.object("!")

des.object("*")
des.object("*")
des.object("*")
des.object("*")

des.object("*")
des.object("*")
des.object("*")
des.object("*")

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
