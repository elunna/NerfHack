-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: thrown and fired objects.  The hero carries stacks of
-- everything throwable, levels are full of things that explode, ooze or
-- shoot back, so throw_obj()/thitmonst()/breakobj() dispositions and the
-- missile-in-limbo family get exercised at volume.
local targets = { "gas spore", "red mold", "yellow light", "black light",
   "floating eye", "volatile mushroom", "shrieker", "flaming sphere",
   "fire vortex", "water nymph", "leprechaun", "rock troll" }
local archers = { "hill orc", "Mordor orc", "Uruk-hai", "orc-captain",
   "soldier", "Woodland-elf", "Grey-elf", "gnome lord" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_missiles_inited") then
   nh.variable("fuzz_missiles_inited", 1)
   u.giveobj(obj.new("20 daggers"))
   u.giveobj(obj.new("40 darts"))
   u.giveobj(obj.new("20 shuriken"))
   u.giveobj(obj.new("10 gold daggers"))
   u.giveobj(obj.new("20 gold darts"))
   u.giveobj(obj.new("3 boomerangs"))
   u.giveobj(obj.new("10 javelins"))
   u.giveobj(obj.new("crossbow"))
   u.giveobj(obj.new("40 crossbow bolts"))
   u.giveobj(obj.new("sling"))
   u.giveobj(obj.new("30 rocks"))
   u.giveobj(obj.new("6 cream pies"))
   u.giveobj(obj.new("4 eggs"))
   u.giveobj(obj.new("5 potions of water"))
   u.giveobj(obj.new("cockatrice corpse"))
end
for i = 1, 5 + nh.random(6) do
   des.monster(pick(targets))
end
for i = 1, 3 + nh.random(3) do
   des.monster({ id = pick(archers), inventory = function()
      if nh.random(2) == 0 then
         des.object("orcish bow")
         des.object({ id = "orcish arrow", quantity = 20 + nh.random(20) })
      else
         des.object({ id = "dagger", quantity = 5 + nh.random(6) })
         des.object({ id = "dart", quantity = 10 + nh.random(20) })
      end
   end })
end
for i = 1, 2 + nh.random(3) do
   des.object({ id = "dagger", quantity = 3 + nh.random(5) })
   des.object({ id = "dart", quantity = 5 + nh.random(10) })
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("throw", 4)
nh.fuzz_favor("fire", 2)
nh.pline("fuzz profile: missiles seeded")
