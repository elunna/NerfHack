-- Fuzz profile: thrones and toilets.  Thrones and toilets are scattered
-- on every level and the hero carries gold, amulets and a rich, varied
-- pack, with #sit favored (and dropping amulets onto toilets).  sit.c
-- (~30%) covers the throne effects -- blessing/cursing/charging and
-- identifying the pack, gold, teleport, the rare wish, the throne
-- vanishing -- and the toilet effects, and dropping an amulet onto a
-- toilet runs dotoiletamulet() (do.c).
local amulets = { "amulet of ESP", "amulet of reflection",
   "amulet of life saving", "amulet versus poison", "amulet of change",
   "amulet of unchanging", "amulet of flying", "amulet of guarding" }
local rings = { "adornment", "protection", "levitation", "teleportation",
   "conflict", "invisibility", "free action", "polymorph" }
local wands = { "striking", "cold", "sleep", "cancellation", "polymorph",
   "teleportation", "make invisible", "nothing" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_thrones_inited") then
   nh.variable("fuzz_thrones_inited", 1)
   u.giveobj(obj.new("4000 gold pieces"))    -- throne gold / gold effects
   for i = 1, 3 do u.giveobj(obj.new(pick(amulets))) end  -- drop in toilets
   for i = 1, 4 do u.giveobj(obj.new("ring of " .. pick(rings))) end
   for i = 1, 4 do u.giveobj(obj.new("wand of " .. pick(wands))) end
   u.giveobj(obj.new("2 uncursed scrolls of identify"))
   u.giveobj(obj.new("3 potions of water"))
   u.giveobj(obj.new("bag of holding"))       -- throne prefers containers
   u.giveobj(obj.new("10 food rations"))
end
-- thrones and toilets scattered about the level
for i = 1, 2 + nh.random(3) do des.feature("throne") end
for i = 1, 2 + nh.random(3) do des.feature("toilet") end
-- loose amulets to pick up and drop onto a toilet
for i = 1, 2 + nh.random(3) do des.object(pick(amulets)) end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("sit", 5)
nh.fuzz_favor("drop", 3)   -- drop an amulet onto a toilet -> dotoiletamulet
nh.fuzz_favor("loot", 1)
nh.pline("fuzz profile: thrones_toilets seeded")
