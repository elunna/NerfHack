-- The Bridge of Khazad-dûm
-- (Why lava? Because holes look ugly.)

-- LEVEL: "moria2-1"

-- Ported from UnNetHack.
-- Converted to lua by hackemslashem
-- Not exactly the same level, but serves as a nasty choke point.

des.level_flags("mazelevel", "noteleport", "hardfloor", "hot", "fumaroles")
des.map([[
---------------------------------------------------------------------------
|.LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL|
|...LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL.|
|.....LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL..|
|......LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL...|
|.......LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL..---
------....LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL..---  
    -----..LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL..---   
 ------.....LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL...------
 |........................................................................|
 ------.....LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL...------
  ------...LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL..---   
----.......LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL..---  
|.......LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL..---
|.....LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL..|
|....LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL.|
|.LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL|
|LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL|
---------------------------------------------------------------------------
]]);

des.region(selection.area(01,01,73,18),"lit")

des.teleport_region({ region = {01,01,10,17}, region_islev=1, exclude={0,0,0,0} })

-- Non diggable walls
des.non_diggable(selection.area(00,00,74,17))

-- MON_GENERATION:60%, (7, "deep orc"), (3, 'o')

des.stair("up", 73,09)
des.stair("down", 2,09)

des.door("open", 04,09)
des.door("open", 71,09)

des.trap("hole", 35,09)
des.trap("hole", 36,09)

if percent(20) then
  des.replace_terrain({ region={11,01,75,17}, fromterrain="L", toterrain=".", chance=5 })
end

des.object({ id = "corpse", x=37,y=09, montype = "wizard" })
des.object({ id = "quarterstaff", x=37,y=09, eroded=2 })
des.object({ id = "robe", x=37,y=09, eroded=1 })

-- Where is Durin's Bane??

for i = 1,math.random(2, 5) do
  des.object()
end

for i = 1,math.random(2, 4) do
  des.object({ id = "corpse", montype = "dwarf" })
end

for i = 1,math.random(2, 2) do
  des.object({ id = "dwarvish mithril-coat", buried = true, buc = "cursed" })
end

--Branch flavor
des.object({ id = "scroll of teleportation", buc="cursed",name = "Word of Recall" })
des.object({ id = "scroll of teleportation", buc="cursed",name = "Word of Recall" })
