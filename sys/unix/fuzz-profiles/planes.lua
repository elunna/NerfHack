-- Fuzz profile: the Planes: the hero carries the Amulet to the Plane of Earth and fuzzes upward through Air, Fire, Water and the Astral Plane -- bubbles, Riders, the altars and the invocation endgame code.
-- The hero is sent to the "earth" level on turn 1; the profile then runs
-- again on every level the hero visits from there.
local function pick(t) return t[nh.random(#t) + 1] end
if not nh.variable("fuzz_planes_inited") then
   nh.variable("fuzz_planes_inited", 1)
   u.giveobj(obj.new("Amulet of Yendor"))
   u.giveobj(obj.new("wand of digging"))
   u.giveobj(obj.new("ring of levitation"))
   u.giveobj(obj.new("amulet of magical breathing"))
   u.giveobj(obj.new("5 scrolls of fire"))
   u.giveobj(obj.new("3 potions of full healing"))
   nh.levelport("earth")
   nh.pline("fuzz profile: planes heading for earth")
   return
end
for i = 1, 2 + nh.random(3) do
   des.object(pick({ "corpse", "potion of water", "wax candle", "dagger" }))
end
nh.pline(("fuzz profile: planes seeded (%s %d)"):format(nh.dnum_name(u.dnum), u.dlevel))
