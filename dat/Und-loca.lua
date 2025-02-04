--
--       The "locate" level for the quest.
--
--       Here you have to locate the Crypt of The First Evil to go
--       further towards your assigned quest.
--

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor", "graveyard", "noflip")
-- This is a kludge to init the level as a lit field.
-- des.level_init({ style="mines", fg=".", bg=".", smoothed=false, joined=false, lit=1, walled=false })

des.level_init({ style = "mazegrid", bg = "-" });
des.mazewalk({ coord = {01,10}, dir = "east", stocked = false});

des.map({ halign = "center", valign = "top", map = [[
........................................
........................................
..........----------+----------.........
..........|........|.|........|.........
..........|........|.|........|.........
..........|----.----.----.----|.........
..........+...................+.........
..........+...................+.........
..........|----.----.----.----|.........
..........|........|.|........|.........
..........|........|.|........|.........
..........----------+----------.........
........................................
........................................
]]});
--# Random Monsters
-- RANDOM_MONSTERS: 'Z', 'W', 'V', 'M'

-- Dungeon Description
des.region({ region={00,00, 09,13}, lit=0, type="morgue", filled=1 })
des.region({ region={09,00, 30,01}, lit=0, type="morgue", filled=1 })
des.region({ region={09,12, 30,13}, lit=0, type="morgue", filled=1 })
des.region({ region={31,00, 39,13}, lit=0, type="morgue", filled=1 })
des.region({ region={11,03, 29,10}, lit=1, type="temple", filled=1, irregular=1 })
-- The altar inside the temple
des.altar({ x=20,y=07, align="noalign", type="shrine", cracked=nh.rn2(2) })
des.monster({ id = "aligned cleric", x=20, y=07, align="noalign", peaceful = 0 })

-- Doors
des.door("locked",10,06)
des.door("locked",10,07)
des.door("locked",20,02)
des.door("locked",20,11)
des.door("locked",30,06)
des.door("locked",30,07)
-- Stairs
-- Note:  The up stairs are *intentionally* off of the map.
des.levregion({ region = {01,00,05,20}, region_islev=1, exclude={0,0,62,16}, type="stair-up" })

des.stair("down", 20,06)
-- Non diggable walls
des.non_diggable(selection.area(10,02,30,13))

-- Objects (inside the antechambers).
des.object({ coord = { 14, 03 } })
des.object({ coord = { 15, 03 } })
des.object({ coord = { 16, 03 } })
des.object({ coord = { 14, 10 } })
des.object({ coord = { 15, 10 } })
des.object({ coord = { 16, 10 } })
des.object({ coord = { 17, 10 } })
des.object({ coord = { 24, 03 } })
des.object({ coord = { 25, 03 } })
des.object({ coord = { 26, 03 } })
des.object({ coord = { 27, 03 } })
des.object({ coord = { 24, 10 } })
des.object({ coord = { 25, 10 } })
des.object({ coord = { 26, 10 } })
des.object({ coord = { 27, 10 } })
-- Random traps
des.trap({ coord = { 15,04 } })
des.trap({ coord = { 25,04 } })
des.trap({ coord = { 15,09 } })
des.trap({ coord = { 25,09 } })
des.trap()
des.trap()

des.object({ id="corpse",montype="undead slayer" })
des.object({ id="corpse",montype="undead slayer" })
des.object({ id="corpse",montype="undead slayer" })
des.object({ id="corpse",montype="undead slayer" })
des.object({ id="corpse",montype="undead slayer" })
des.object({ id="corpse",montype="undead slayer" })
des.object({ id="corpse",montype="exterminator" })
des.object({ id="corpse",montype="exterminator" })
des.object({ id="corpse",montype="exterminator" })
des.object({ id="corpse",montype="exterminator" })
des.object({ id="corpse",montype="exterminator" })
des.object({ id="corpse",montype="exterminator" })

-- No random monsters - the morgue generation will put them in.