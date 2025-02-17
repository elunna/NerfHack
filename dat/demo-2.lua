-- SCCS Id: @(#)gehennom.des	3.4	1996/11/09
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
-- Demogorgon's towers
--
-- Ported from GruntHack
-- Added puddles from EvilHack
-- Converted to lua by hackemslashem

des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor", "shortsighted")

des.level_init({ style="mines", fg=".", bg="}", smoothed=true, joined=true, walled=true })

--0       1         2         3         4         5         6         7     
--23456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "center", valign = "center", map = [[
}}u}}}}uu}}u}}u}}u}}}}}}}}}}}}}}}}}}}}}}}}}u}u}uu}}uu}}uu}uu
}uu}u}uuu}uuu}uu}u}}}u}}}}}}}}}}}}}u}}}u}}u}uuu}uu}u}}uu}uu}
uu---------------}}}}}}u}}}u}}}}}}}}}}}}}u}---------------}u
}}|.............|uu}}}}}}}}}}}}}}}}}}}}}u}}|....|.|...|..|u}
uu|S-----------.|u}u}}}}}}uu}}}u}}}}}}}}}uu|....S.|.|.S..|uu
}u|...........|.|}}}}u}}}}}}}}}u}}}u}}}uuu}|....|.|.----S|u}
u}|...........|.|uuuu}}}}}}}}}}}}}}}}}}}}uu|....|...|....|uu
}u----------S--S-}}u}}}}}}}}}}}}}}}}}}}}}}u----S-------S--}u
uu|..|--...|.|..|}}}}}}}}}}}}}}}}}}}}}}}}}}|..|.|...--...|u}
uu|....S...|.|..|}########################}|..|.|...S....Su}
}u|..|--...|.|..|}}}}}}}}}}}}}}}}}}}}}}}}}}|..|.|...--...|uu
u}--S-------S----}}}}}}}}}}}}}}}}}}}}}}}}}}-S--S----------}u
}u|....|...|....|}u}}}}}}}}}}}}}u}}}}}}}uuu|.|...........|u}
}}|S----.|.|....|u}}u}}}uu}}}}}}}}}u}}}u}}u|.|...........|uu
uu|..S.|.|.S....|u}u}}}}}}}}uu}}}}}}}}}}}}}|.-----------S|}u
uu|..|...|.|....|}u}}}}}}}}}}}}}u}}}}}}}}}}|.............|}}
}u---------------u}}}uuuu}}}}}}}}}}}}}}}}uu---------------uu
uuu}u}uuu}uuu}uu}u}}}}}u}}}}}}}}}}}}}u}}}}u}uuu}uu}u}uuu}uu}
}}}uu}}uuu}u}}u}u}}}}}}}}}}}}}}}}}}}}u}}}}}}}}uu}}u}uu}}}u}}
]] });

-- # who's in residence?
-- RANDOM_MONSTERS:'&','i',';'

-- stairs in the two towers
des.stair("up", 09,09)
des.stair("down", 50,09)

-- from above, land in the left tower; from below, land in the right tower
des.teleport_region({region={43,02,57,16}, exclude = {0,0,0,0}, dir="up" })
des.teleport_region({region={02,02,16,16}, exclude = {0,0,0,0}, dir="down" })

--des.levregion({ region = {01,00,15,20}, region_islev=1, exclude={15,1,70,16}, exclude_islev=1, type="stair-up" })
--des.levregion({ region = {01,00,15,20}, region_islev=1, exclude={15,1,70,16}, exclude_islev=1, type="branch" })

des.region(selection.area(00,00,59,18), "lit");
des.region(selection.area(02,02,16,16), "unlit");
des.region(selection.area(43,02,57,16), "unlit");

-- can't dig in the towers
des.non_diggable(selection.area(02,02,16,16))
des.non_diggable(selection.area(43,02,58,16))

-- bridge between the two towers
des.drawbridge({ dir="west", state="closed", x=17,y=09})
des.drawbridge({ dir="east", state="closed", x=42,y=09})

-- The fellow in residence
des.monster({id="Demogorgon", x=50, y=09})

-- some tough guards
des.monster("nalfeshnee",49,08)
des.monster("balrog",51,08)
des.monster("nalfeshnee",49,10)
des.monster("balrog",51,10)
des.monster("weredemon",50,08)
des.monster("elder minotaur",49,09)
des.monster("pit fiend",50,10)

-- and some other denizens
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
des.monster("i")

des.monster("kraken")
des.monster("kraken")
des.monster("kraken")
des.monster("kraken")
des.monster("kraken")

des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")

des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")

des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")

-- a bit of loot
des.object("[")
des.object("[")
des.object(")")
des.object(")")
des.object("*")
des.object("!")
des.object("?")


-- some traps
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
des.trap("magic")
des.trap("magic")