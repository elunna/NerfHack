-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: Fort Ludios: the vault guards, soldiers in formation and the treasury.
-- The hero is sent to the "knox" level on turn 1; the profile then runs
-- again on every level the hero visits from there.
local function pick(t) return t[nh.random(#t) + 1] end
if not nh.variable("fuzz_knox_inited") then
   nh.variable("fuzz_knox_inited", 1)
   u.giveobj(obj.new("wand of digging"))
   u.giveobj(obj.new("3 scrolls of teleportation"))
   u.giveobj(obj.new("bag of holding"))
   u.giveobj(obj.new("ring of conflict"))
   nh.levelport("knox")
   nh.pline("fuzz profile: knox heading for knox")
   return
end
for i = 1, 1 + nh.random(2) do
   des.object("gold piece")
end
nh.pline(("fuzz profile: knox seeded (%s %d)"):format(nh.dnum_name(u.dnum), u.dlevel))
