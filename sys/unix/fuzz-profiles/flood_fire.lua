-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: scrolls of flood and fire.  Terrain-changing and
-- item-destroying scrolls read by the hero and by monsters, with plenty
-- of flammable and dilutable loot lying around and monsters standing on
-- it, so terrain changes under objects/monsters/engravings, burning and
-- water damage in packs and containers, and drowning get exercised.
local bucs = { "blessed", "uncursed", "cursed" }
local loot = { "scroll of light", "spellbook of force bolt", "potion of water",
   "potion of oil", "wax candle", "ring mail", "sack", "tin", "egg",
   "corpse" }
local crowd = { "gnome lord", "dwarf", "hill orc", "soldier", "red mold",
   "gas spore", "fire vortex", "rock troll", "water troll", "lich",
   "vampire", "yellow light", "shrieker" }
local readers = { "gnome lord", "Grey-elf", "soldier", "lich", "vampire",
   "master mind flayer", "Uruk-hai", "gnome king" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_flood_fire_inited") then
   nh.variable("fuzz_flood_fire_inited", 1)
   for _, b in ipairs(bucs) do
      u.giveobj(obj.new("3 " .. b .. " scrolls of flood"))
      u.giveobj(obj.new("3 " .. b .. " scrolls of fire"))
   end
   u.giveobj(obj.new("2 potions of confusion"))
   u.giveobj(obj.new("ring of fire resistance"))
end
for i = 1, 5 + nh.random(6) do
   des.monster(pick(crowd))
end
for i = 1, 3 + nh.random(3) do
   des.monster({ id = pick(readers), inventory = function()
      des.object({ id = "scroll of fire", buc = pick(bucs) })
      des.object({ id = "scroll of flood", buc = pick(bucs) })
      des.object(pick(loot))
   end })
end
for i = 1, 8 + nh.random(8) do
   des.object(pick(loot))
end
for i = 1, 2 + nh.random(3) do
   des.object({ id = "scroll of fire", buc = pick(bucs) })
   des.object({ id = "scroll of flood", buc = pick(bucs) })
   des.engraving({ type = "engrave", text = "Elbereth" })
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("read", 4)
nh.pline("fuzz profile: flood_fire seeded")
