-- Fuzz profile: the Oracle: centaurs, fountains, the consultation code and Delphi's peaceful crowd.
-- The hero is sent to the "oracle" level on turn 1; the profile then runs
-- again on every level the hero visits from there.
local function pick(t) return t[nh.random(#t) + 1] end
if not nh.variable("fuzz_oracle_inited") then
   nh.variable("fuzz_oracle_inited", 1)
   u.giveobj(obj.new("1000 gold pieces"))
   u.giveobj(obj.new("5 potions of water"))
   u.giveobj(obj.new("3 scrolls of remove curse"))
   u.giveobj(obj.new("wand of digging"))
   nh.levelport("oracle")
   nh.pline("fuzz profile: oracle heading for oracle")
   return
end
for i = 1, 1 + nh.random(3) do
   des.monster({ id = pick({ "forest centaur", "plains centaur", "water nymph" }),
                 peaceful = (nh.random(2) == 0) })
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("chat", 3)
nh.pline(("fuzz profile: oracle seeded (%s %d)"):format(nh.dnum_name(u.dnum), u.dlevel))
