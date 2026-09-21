-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: the Castle: the drawbridge and moat, the storerooms, soldiers and the wand of wishing.
-- The hero is sent to the "castle" level on turn 1; the profile then runs
-- again on every level the hero visits from there.
local function pick(t) return t[nh.random(#t) + 1] end
if not nh.variable("fuzz_castle_inited") then
   nh.variable("fuzz_castle_inited", 1)
   u.giveobj(obj.new("tooled horn"))
   u.giveobj(obj.new("2 wands of striking"))
   u.giveobj(obj.new("wand of opening"))
   u.giveobj(obj.new("wand of locking"))
   u.giveobj(obj.new("ring of levitation"))
   u.giveobj(obj.new("3 scrolls of earth"))
   u.giveobj(obj.new("wand of digging"))
   nh.levelport("castle")
   nh.pline("fuzz profile: castle heading for castle")
   return
end
for i = 1, 2 + nh.random(3) do
   des.monster(pick({ "soldier", "sergeant", "lieutenant", "water troll" }))
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("apply", 1)
nh.pline(("fuzz profile: castle seeded (%s %d)"):format(nh.dnum_name(u.dnum), u.dlevel))
