-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: the Wizard's Tower: Rodney, his spell list, the Amulet chase and covetous-monster code.
-- The hero is sent to the "wizard1" level on turn 1; the profile then runs
-- again on every level the hero visits from there.
local function pick(t) return t[nh.random(#t) + 1] end
if not nh.variable("fuzz_wiztower_inited") then
   nh.variable("fuzz_wiztower_inited", 1)
   u.giveobj(obj.new("blessed +5 speed boots"))
   u.giveobj(obj.new("3 potions of full healing"))
   u.giveobj(obj.new("wand of digging"))
   u.giveobj(obj.new("amulet of life saving"))
   u.giveobj(obj.new("cloak of magic resistance"))
   nh.levelport("wizard1")
   nh.pline("fuzz profile: wiztower heading for wizard1")
   return
end
for i = 1, 1 + nh.random(3) do
   des.monster(pick({ "lich", "master lich", "vampire lord", "nalfeshnee" }))
end
nh.pline(("fuzz profile: wiztower seeded (%s %d)"):format(nh.dnum_name(u.dnum), u.dlevel))
