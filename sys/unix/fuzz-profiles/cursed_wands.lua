-- Fuzz profile: cursed wands.  Cursed wands in the hero's hands, in
-- monsters' packs and on the floor, so backfires, wand explosions (the
-- wand_explode family), engraving with them, breaking them and monsters
-- zapping them all happen constantly.
local wands = { "striking", "magic missile", "fire", "cold", "sleep",
   "lightning", "death", "digging", "polymorph", "teleportation",
   "cancellation", "make invisible", "speed monster", "slow monster",
   "undead turning", "create monster", "opening", "locking", "probing",
   "light", "secret door detection", "enlightenment", "nothing", "wonder",
   "poison gas", "corrosion", "draining", "wishing" }
local carriers = { "gnome lord", "dwarf", "hill orc", "Mordor orc",
   "Uruk-hai", "soldier", "Woodland-elf", "Grey-elf", "gnome king",
   "watchman", "lich", "master mind flayer", "vampire", "water nymph" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_cursed_wands_inited") then
   nh.variable("fuzz_cursed_wands_inited", 1)
   for i = 1, 8 do
      u.giveobj(obj.new("cursed wand of " .. pick(wands)))
   end
end
for i = 1, 4 + nh.random(5) do
   des.monster({ id = pick(carriers), inventory = function()
      des.object({ id = "wand of " .. pick(wands), buc = "cursed" })
      if nh.random(2) == 0 then
         des.object({ id = "wand of " .. pick(wands), buc = "cursed" })
      end
   end })
end
for i = 1, 3 + nh.random(4) do
   des.object({ id = "wand of " .. pick(wands), buc = "cursed" })
end
nh.pline("fuzz profile: cursed_wands seeded")
