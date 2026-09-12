-- NetHack gehennom baalz-1.lua	$NHDT-Date: 1652196020 2022/05/10 15:20:20 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.4 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
-- This level was inspired by the changes in UnNetHack
--
des.level_init({ style="mines", fg=".", bg="L", smoothed=true, joined=true, walled=true })

-- TODO FIXME: see baalz_fixup - the legs get removed currently.

des.level_flags("mazelevel")

-- the two pools are fakes used to mark spots which need special wall fixups
-- the two iron bars are eyes and spots to their left will be made diggable
--
-- The 7 leftmost columns are an antechamber in front of the locked west
-- door: a guaranteed floor area in the lava cave.  The "mines" fill's
-- cellular automaton updates in place while scanning left to right, so it
-- routinely leaves the far-left band of the level solid lava; the stair,
-- branch and teleport regions used to sit exactly there (inherited from
-- baalz-1's maze layout) and fixup_special() then had nowhere to put the
-- up staircase ("Couldn't place lregion").  Those regions now target the
-- antechamber, in map coordinates, so they can't be empty whatever the
-- cave does.  (baalz-1's des.mazewalk was also inherited; it does nothing
-- here since the walker only carves through stone, not lava.)
des.map({ halign = "right", valign = "center", map = [[
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFFLLLLLLLLLLLLLLLLLFFLLLLL
LLLLLLLLLLLLLLLLLFFLLLLLLLLFFFFLLLLLLLLLLLLLLLFFFFLLLLLL
LLLLLLLLLLFLLLLLLLFFFFLLLLLFLLLLL-----------LLFLLLLLLLLL
LLLLLLLLLFFFFFFLLLLLLFLL---------|.........|--PLLLLLLLLF
.......LLF....FLL-------|...........--------------LLLLFL
.......---....|--|..................S............|----LL
.......+...--....S..----------------|............S...|LL
.......---....|--|..................|............|----LL
.......LLF....FLL-------|...........-----S--------LLLLFL
LLLLLLLLLFFFFFFLLLLLLFLL---------|.........|--PLLLLLLLLF
LLLLLLLLLLFLLLLLLLFFFFLLLLLFLLLLL-----------LLFLLLLLLLLL
LLLLLLLLLLLLLLLLLFFLLLLLLLLFFFFLLLLLLLLLLLLLLLFFFFLLLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFFLLLLLLLLLLLLLLLLLFFLLLLL
]] });
-- arrival is in the antechamber (map-relative coordinates: columns 0-6,
-- the floor rows 4-8), never in the random cave
des.levregion({ region = {00,04,06,08}, type="stair-up" })
des.levregion({ region = {00,04,06,08}, type="branch" })
des.teleport_region({ region = {00,04,06,08} })

-- this actually leaves the farthest right column diggable
-- (the antechamber, columns 0-6, stays diggable and outside baalz_fixup()'s
-- nondiggable-bounded working area)
des.non_diggable(selection.area(07,00,54,12))
des.stair("down", 51,06)
des.door("locked",07,06)

-- The fellow in residence
des.monster("Baalzebub",42,06)

-- Some random weapons and armor.
des.object("[")
des.object("[")
des.object(")")
des.object(")")
des.object("*")
des.object("!")
des.object("!")
des.object("?")
des.object("?")
des.object("?")

-- Some traps.
des.trap("spiked pit")
des.trap("fire")
des.trap("sleep gas")
des.trap("anti magic")
des.trap("fire")
des.trap("magic")
des.trap("magic")

-- Random monsters.
des.monster("ghost",44,07)
des.monster("horned devil",39,05)
des.monster("barbed devil",45,07)
des.monster("weredemon")
des.monster("L")

-- Some Vampires for good measure
des.monster("V")
des.monster("V")
des.monster("V")

