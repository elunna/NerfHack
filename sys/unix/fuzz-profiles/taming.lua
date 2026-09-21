-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: scrolls of taming and create monster.  Pets made and
-- unmade in bulk, hostile crowds summoned around the hero, monsters
-- reading create monster themselves, so pet bookkeeping (edog, leashes,
-- following, stashing), peaceful/hostile flips and overcrowding get
-- exercised.
local bucs = { "blessed", "uncursed", "cursed" }
local crowd = { "gnome lord", "dwarf", "hill orc", "soldier", "water nymph",
   "leprechaun", "rock troll", "yellow light", "chameleon", "vampire",
   "lich", "human zombie", "ettin", "wraith", "large mimic", "jackal" }
local readers = { "gnome lord", "Grey-elf", "soldier", "lich", "vampire",
   "master mind flayer", "Uruk-hai", "gnome king" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_taming_inited") then
   nh.variable("fuzz_taming_inited", 1)
   for _, b in ipairs(bucs) do
      u.giveobj(obj.new("4 " .. b .. " scrolls of taming"))
      u.giveobj(obj.new("4 " .. b .. " scrolls of create monster"))
   end
   u.giveobj(obj.new("2 potions of confusion"))
   u.giveobj(obj.new("2 leashes"))
   u.giveobj(obj.new("magic whistle"))
   u.giveobj(obj.new("10 food rations"))
end
for i = 1, 6 + nh.random(6) do
   des.monster({ id = pick(crowd), peaceful = (nh.random(3) == 0) })
end
for i = 1, 3 + nh.random(3) do
   des.monster({ id = pick(readers), inventory = function()
      des.object({ id = "scroll of create monster", buc = pick(bucs) })
      des.object({ id = "scroll of taming", buc = pick(bucs) })
      if nh.random(2) == 0 then
         des.object("sack")
      end
   end })
end
for i = 1, 2 + nh.random(3) do
   des.object({ id = "scroll of taming", buc = pick(bucs) })
   des.object({ id = "scroll of create monster", buc = pick(bucs) })
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("read", 3)
nh.fuzz_favor("wizgenesis", 2)
nh.fuzz_favor("chat", 1)
nh.pline("fuzz profile: taming seeded")
