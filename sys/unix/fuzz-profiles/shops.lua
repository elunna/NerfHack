-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: Minetown: shops, a temple and the watch.  Buying, selling, shoplifting, price-identifying, angering the watch and the priest, digging out of a shop, and everything shopkeepers do with the bill.
-- The hero is sent to the "minetn" level on turn 1; the profile then runs
-- again on every level the hero visits from there.
local function pick(t) return t[nh.random(#t) + 1] end
if not nh.variable("fuzz_shops_inited") then
   nh.variable("fuzz_shops_inited", 1)
   u.giveobj(obj.new("4000 gold pieces"))
   u.giveobj(obj.new("bag of holding"))
   u.giveobj(obj.new("pick-axe"))
   u.giveobj(obj.new("wand of digging"))
   u.giveobj(obj.new("2 wands of teleportation"))
   u.giveobj(obj.new("3 scrolls of teleportation"))
   u.giveobj(obj.new("5 potions of water"))
   u.giveobj(obj.new("3 scrolls of enchant armor"))
   u.giveobj(obj.new("magic marker"))
   nh.levelport("minetn")
   nh.pline("fuzz profile: shops heading for minetn")
   return
end
for i = 1, 2 + nh.random(3) do
   des.object("gold piece")
   des.object(pick({ "scroll of identify", "potion of water", "dagger",
                     "ring of protection", "wand of striking", "food ration" }))
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("pay", 2)
nh.fuzz_favor("chat", 1)
nh.pline(("fuzz profile: shops seeded (%s %d)"):format(nh.dnum_name(u.dnum), u.dlevel))
