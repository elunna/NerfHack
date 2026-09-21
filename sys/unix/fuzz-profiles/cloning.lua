-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: scrolls of cloning and transmogrify.  Read by the hero
-- (blessed, uncursed, cursed, confused) and by monsters, with a crowd of
-- assorted monsters to clone or transmogrify, so the copy/transform
-- bookkeeping (inventory, ids, light, worn masks, uniques) gets hammered.
local bucs = { "blessed", "uncursed", "cursed" }
local crowd = { "gnome lord", "dwarf", "hill orc", "soldier", "water nymph",
   "leprechaun", "rock troll", "yellow light", "small mimic", "chameleon",
   "vampire", "lich", "master mind flayer", "human zombie", "ettin",
   "floating eye", "gas spore", "wraith" }
local readers = { "gnome lord", "Grey-elf", "soldier", "lich", "vampire",
   "master mind flayer", "Uruk-hai" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_cloning_inited") then
   nh.variable("fuzz_cloning_inited", 1)
   for _, b in ipairs(bucs) do
      u.giveobj(obj.new("3 " .. b .. " scrolls of cloning"))
      u.giveobj(obj.new("3 " .. b .. " scrolls of transmogrify"))
   end
   u.giveobj(obj.new("2 potions of confusion"))
end
for i = 1, 5 + nh.random(6) do
   des.monster(pick(crowd))
end
for i = 1, 3 + nh.random(3) do
   des.monster({ id = pick(readers), inventory = function()
      des.object({ id = "scroll of cloning", buc = pick(bucs) })
      des.object({ id = "scroll of transmogrify", buc = pick(bucs) })
   end })
end
for i = 1, 2 + nh.random(3) do
   des.object({ id = "scroll of cloning", buc = pick(bucs) })
   des.object({ id = "scroll of transmogrify", buc = pick(bucs) })
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("read", 4)
nh.pline("fuzz profile: cloning seeded")
