-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: shape changes.  Chameleons, doppelgangers, sandestins
-- and mimics on every level, polymorph traps, and wands and potions of
-- polymorph in the hero's and monsters' hands, so newcham(), poly_obj(),
-- polymon() and every light/worn-mask/timer fixup around them gets hit.
local shifters = { "chameleon", "doppelganger", "sandestin", "small mimic",
   "large mimic", "giant mimic", "vampire", "vampire lord" }
local carriers = { "gnome lord", "dwarf", "hill orc", "soldier", "Uruk-hai",
   "Woodland-elf", "master mind flayer", "lich" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_shapeshifters_inited") then
   nh.variable("fuzz_shapeshifters_inited", 1)
   u.giveobj(obj.new("3 wands of polymorph"))
   u.giveobj(obj.new("ring of polymorph control"))
   u.giveobj(obj.new("ring of polymorph"))
   u.giveobj(obj.new("4 potions of polymorph"))
   u.giveobj(obj.new("wand of undead turning"))
end
for i = 1, 4 + nh.random(5) do
   des.monster(pick(shifters))
end
for i = 1, 3 + nh.random(3) do
   des.monster({ id = pick(carriers), inventory = function()
      des.object("wand of polymorph")
      if nh.random(2) == 0 then
         des.object("potion of polymorph")
      end
   end })
end
for i = 1, 3 + nh.random(3) do
   des.trap("polymorph")
end
des.object("wand of polymorph")
des.object("potion of polymorph")
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("polyself", 4)
nh.fuzz_favor("wizgenesis", 2)
nh.fuzz_favor("zap", 2)
nh.pline("fuzz profile: shapeshifters seeded")
