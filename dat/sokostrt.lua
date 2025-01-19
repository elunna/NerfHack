--
-- Angband-1
-- Copyright (c) 2009 by Patric Mueller
--
-- NetHack may be freely redistributed.  See license for details.
--

--
-- The filler levels for the Town branch.
-- Ported from UnNetHack
-- Converted to lua by hackemslashem
-- LEVEL:"sokostrt"
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor", "noflip")

des.message("You step into a desolate, frozen expanse.")
des.message("In the distance, an ornate tower rises, its shadow stretching across the icy wasteland.")

des.map([[
-----................................................................       
|........................................................................   
|.......................................................................... 
|...........................................................................
|...........................................................................
|...........................................................................
|.......................................................................... 
|.......................................................................... 
|...........................................................................
|...........................................................................
|...........................................................................
|.......................................................................... 
|.......................................................................... 
|.......................................................................... 
|.........................................................................  
|.........................................................................  
|.......................................................................... 
|.......................................................................... 
|.......................................................................... 
|........................................................................   
----------.............................................................     
]]);

-- Dungeon Description
des.region(selection.area(01,01,75,20), "lit")
des.levregion({ region={70,01,76,20}, type="branch" });
des.levregion({ region={01,01,10,20},  type="stair-up" });

local liquid = "}";
local ground = ".";

-- Add some rivers so that getting to the town level is a bit more
-- difficult and it makes for some nice scenery.
if percent(50) then
  local sel = selection.randline(selection.new(), 10,01, 20,20, 20)
  des.terrain(sel:percentage(90):grow(), liquid)
else
  local sel = selection.randline(selection.new(), 20,01, 10,20, 20)
  des.terrain(sel:percentage(90):grow(), liquid)
end

if percent(50) then
  local sel = selection.randline(selection.new(), 30,01, 40,20, 20)
  des.terrain(sel:percentage(90):grow(), liquid)

  local sel = selection.randline(selection.new(), 50,01, 40,20, 20)
  des.terrain(sel:percentage(90):grow(), liquid)
else
  local sel = selection.randline(selection.new(), 40,01, 30,20, 20)
  des.terrain(sel:percentage(90):grow(), liquid)

  local sel = selection.randline(selection.new(), 40,01, 50,20, 20)
  des.terrain(sel:percentage(90):grow(), liquid)
end

local sel = selection.randline(selection.new(), 60,01, 60,20, 20)
des.terrain(sel:percentage(90):grow(), liquid)

-- Pools surrounded by ice
local pools = selection.new()
for i = 1,7 do
   pools:set();
end
-- some bigger ones
for i = 1,3 do
  pools = pools | selection.grow(selection.set(selection.new()), "west")
  pools = pools | selection.grow(selection.set(selection.new()), "north")
  pools = pools | selection.grow(selection.set(selection.new()), "random")
end
des.terrain(pools:clone():grow("all"), "I")
des.terrain(pools, "P")


-- "broken" walls
if percent(90) then
  des.object("rock",05,00)
end
if percent(50) then
  des.object("rock",06,00)
end
if percent(50) then
  des.object("rock",07,00)
end
if percent(25) then
  des.object("rock",09,00)
end
if percent(90) then
  des.object("rock",10,20)
end
if percent(50) then
  des.object("rock",11,20)
end
if percent(50) then
  des.object("rock",12,20)
end
if percent(25) then
  des.object("rock",13,20)
end
-- Random objects
des.object()
des.object()
des.object()

-- Traps
-- Do not use random here because level teleport traps could
-- send the player up to a random Soko level!
des.trap("cold")
des.trap("cold")
des.trap("cold")
des.trap("pit")
des.trap("spiked pit")
des.trap("bear")
des.trap("spear")

-- Random monsters.
--[25%]: MONSTER: (':', "giant turtle"), random

des.monster()
des.monster()
des.monster()
des.monster()
des.monster()

-- random boulders
for i = 1,math.random(2, 6) do
  des.object("boulder")
end