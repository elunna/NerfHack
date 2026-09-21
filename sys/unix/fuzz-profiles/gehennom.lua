-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: Orcus Town in Gehennom: undead town with shops and a temple, demon lords, and the hellish terrain rules.
-- The hero is sent to the "orcus" level on turn 1; the profile then runs
-- again on every level the hero visits from there.
local function pick(t) return t[nh.random(#t) + 1] end
if not nh.variable("fuzz_gehennom_inited") then
   nh.variable("fuzz_gehennom_inited", 1)
   u.giveobj(obj.new("ring of fire resistance"))
   u.giveobj(obj.new("2000 gold pieces"))
   u.giveobj(obj.new("3 wands of undead turning"))
   u.giveobj(obj.new("wand of digging"))
   u.giveobj(obj.new("amulet of life saving"))
   nh.levelport("orcus")
   nh.pline("fuzz profile: gehennom heading for orcus")
   return
end
for i = 1, 2 + nh.random(3) do
   des.monster(pick({ "human zombie", "vampire", "wraith", "ghoul", "lich" }))
end
nh.pline(("fuzz profile: gehennom seeded (%s %d)"):format(nh.dnum_name(u.dnum), u.dlevel))
