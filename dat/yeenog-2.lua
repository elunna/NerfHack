
-- new GruntHack levels.
-- Yeenoghu's realm
-- MAZE:"yeenoghu", random

des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "hardfloor", "noflip")

des.level_init({ style="mines", fg=".", bg="}", smoothed=true, joined=true, walled=true })

des.map({ halign = "right", valign = "center", map = [[
}}}w}}wwwww}}}}}}}}}}}
}---------------w}}w}}
w|..|...|..|...|..w}}}
.-S----+--+-+--|.w}w}}
.|..+..........|..w}}}
.|..|..........|.w}w}}
.----+------S---.w}w}}
.+.......|.....|..ww}}
.+.......|..\..|.w}}w}
.+.......|.....|..ww}}
.----+------S---..w}}}
.|..|..........|.w}w}}
.|..+..........|..w}w}
.-S----+--+-+---..w}}}
w|..|...|..|...|.w}w}}
}---------------www}}}
}}w}wwwww}w}ww}}}}}}}}
]] });

-- RANDOM_MONSTERS:'&','i','T','G','d','@'

des.levregion({ region = {01,01,19,19}, exclude={01,01,01,01}, region_islev=1, exclude_islev=1, type="stair-up" })

-- BRANCH:levregion(01,01,19,19),levregion(01,01,01,01)
des.levregion({ region = {01,01,19,19}, exclude={01,01,01,01}, region_islev=1, exclude_islev=1, type="branch" })

-- Stairs
des.stair("down", 14,08)

des.door("locked",07,03)
des.door("locked",10,03)
des.door("locked",12,03)
des.door("locked",04,04)
des.door("locked",05,06)
des.door("locked",01,07)
des.door("locked",01,08)
des.door("locked",01,09)
des.door("locked",05,10)
des.door("locked",04,12)
des.door("locked",07,13)
des.door("locked",10,13)
des.door("locked",12,13)

des.region(selection.area(00,00,21,16),"lit")

des.region({ region={10,07,14,09},lit=1,type="throne", filled=0 })

-- Non diggable walls
des.non_diggable(selection.area(01,01,15,15))

-- the owner of the mansion
des.monster({id="Yeenoghu", x=12, y=08})

-- his minions
des.monster("hell hound",11,08)
des.monster("hell hound",13,08)
des.monster("Olog-hai",11,07)
des.monster("Olog-hai",11,09)
des.monster("Olog-hai",13,07)
des.monster("Olog-hai",13,09)
des.monster("G",10,08)
des.monster("G",14,12)

-- his slaves
des.monster("@")
des.monster("@")
des.monster("@")
des.monster("@")
des.monster("@")
des.monster("@")
des.monster("@")
des.monster("@")
des.monster("@")
des.monster("@")

-- other denizens
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

des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")

des.monster("d")
des.monster("d")
des.monster("d")
des.monster("d")
des.monster("d")

des.monster("G")
des.monster("G")
des.monster("G")
des.monster("G")
des.monster("G")

-- the throne room loot
des.object("chest",13,08)

-- some wasteland-ish stuff
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")

-- other loot
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

-- traps
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
