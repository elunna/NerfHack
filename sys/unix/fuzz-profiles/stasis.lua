-- Fuzz profile: scrolls of stasis.  Nothing but stasis scrolls in every
-- state, read by the hero and carried by monsters, over a crowd of
-- monsters with timers, light and worn gear, so whatever stasis
-- suspends and resumes gets suspended and resumed a great deal.
local bucs = { "blessed", "uncursed", "cursed" }
local crowd = { "gnome lord", "dwarf", "hill orc", "soldier", "water nymph",
   "leprechaun", "rock troll", "yellow light", "fire vortex", "chameleon",
   "vampire", "lich", "master mind flayer", "human zombie", "floating eye",
   "gas spore", "wraith", "shrieker", "large mimic" }
local readers = { "gnome lord", "Grey-elf", "soldier", "lich", "vampire",
   "master mind flayer", "Uruk-hai" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_stasis_inited") then
   nh.variable("fuzz_stasis_inited", 1)
   for _, b in ipairs(bucs) do
      u.giveobj(obj.new("4 " .. b .. " scrolls of stasis"))
   end
   u.giveobj(obj.new("2 potions of confusion"))
   u.giveobj(obj.new("3 wax candles"))
end
for i = 1, 6 + nh.random(6) do
   des.monster(pick(crowd))
end
for i = 1, 3 + nh.random(3) do
   des.monster({ id = pick(readers), inventory = function()
      des.object({ id = "scroll of stasis", buc = pick(bucs) })
      if nh.random(2) == 0 then
         des.object({ id = "oil lamp", lit = true })
      end
   end })
end
for i = 1, 3 + nh.random(3) do
   des.object({ id = "scroll of stasis", buc = pick(bucs) })
   des.object({ id = "corpse", montype = pick({ "gecko", "rock troll",
                                                 "lizard", "human zombie" }) })
end
nh.pline("fuzz profile: stasis seeded")
