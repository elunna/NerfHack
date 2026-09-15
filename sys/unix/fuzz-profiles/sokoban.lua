-- Fuzz profile: Sokoban: boulders, pits and holes, the prize, and every rule about pushing, squeezing and cheating.
-- The hero is sent to the "soko1" level on turn 1; the profile then runs
-- again on every level the hero visits from there.
local function pick(t) return t[nh.random(#t) + 1] end
if not nh.variable("fuzz_sokoban_inited") then
   nh.variable("fuzz_sokoban_inited", 1)
   u.giveobj(obj.new("wand of digging"))
   u.giveobj(obj.new("2 wands of striking"))
   u.giveobj(obj.new("scroll of earth"))
   u.giveobj(obj.new("ring of levitation"))
   u.giveobj(obj.new("3 potions of levitation"))
   nh.levelport("soko1")
   nh.pline("fuzz profile: sokoban heading for soko1")
   return
end
for i = 1, 1 + nh.random(2) do
   des.monster(pick({ "gnome lord", "dwarf", "jackal", "floating eye" }))
end
nh.pline(("fuzz profile: sokoban seeded (%s %d)"):format(nh.dnum_name(u.dnum), u.dlevel))
