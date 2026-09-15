-- Fuzz profile: containers everywhere.  Ice boxes, chests and bags with
-- corpses, eggs, tins and lit candles inside, many of them carried by
-- monsters, so freeze/thaw timers, monster stashing and looting, #tip,
-- container nesting and bag-of-holding explosions get exercised.
local corpses = { "gecko", "newt", "jackal", "lichen", "lizard", "rock troll",
   "ice troll", "water troll", "human zombie", "gnome zombie", "kobold zombie",
   "gnome lord", "dwarf", "floating eye", "red mold", "yellow light" }
local carriers = { "gnome lord", "dwarf", "hill orc", "bugbear", "soldier",
   "hobbit", "water nymph", "gnome king", "watchman", "Uruk-hai" }
local bags = { "sack", "oilskin sack", "bag of holding", "ice box",
   "large box", "chest" }
local function pick(t) return t[nh.random(#t) + 1] end
local function stuff()
   for j = 1, 1 + nh.random(6) do
      local r = nh.random(10)
      if r < 5 then
         des.object({ id = "corpse", montype = pick(corpses) })
      elseif r == 5 then
         des.object("egg")
      elseif r == 6 then
         des.object("tin")
      elseif r == 7 then
         des.object({ id = "wax candle", lit = true })
      elseif r == 8 then
         des.object({ id = "oil lamp", lit = (nh.random(2) == 0) })
      else
         des.object("potion of water")
      end
   end
end

if not nh.variable("fuzz_containers_inited") then
   nh.variable("fuzz_containers_inited", 1)
   u.giveobj(obj.new("bag of holding"))
   u.giveobj(obj.new("oilskin sack"))
   u.giveobj(obj.new("2 sacks"))
   u.giveobj(obj.new("5 wax candles"))
end
for i = 1, 3 + nh.random(4) do
   des.object({ id = pick(bags), contents = stuff })
end
for i = 1, 4 + nh.random(5) do
   des.monster({ id = pick(carriers), inventory = function()
      des.object({ id = pick(bags), contents = stuff })
      if nh.random(2) == 0 then
         des.object({ id = "corpse", montype = pick(corpses) })
      end
   end })
end
for i = 1, 4 + nh.random(6) do
   des.object({ id = "corpse", montype = pick(corpses) })
end
nh.pline("fuzz profile: containers seeded")
