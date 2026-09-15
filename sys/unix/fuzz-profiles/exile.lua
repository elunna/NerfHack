-- Fuzz profile: scrolls of exile.  Read in every state by the hero and
-- carried by monsters, with plenty of nearby targets of all kinds
-- (pets, peacefuls, shapeshifters, light emitters, things carrying gear
-- and containers), so removing a monster from play in the middle of its
-- own bookkeeping gets exercised.
local bucs = { "blessed", "uncursed", "cursed" }
local crowd = { "gnome lord", "dwarf", "hill orc", "soldier", "water nymph",
   "leprechaun", "rock troll", "yellow light", "fire vortex", "chameleon",
   "doppelganger", "vampire", "vampire lord", "lich", "master mind flayer",
   "human zombie", "ettin", "wraith", "large mimic", "floating eye" }
local readers = { "gnome lord", "Grey-elf", "soldier", "lich", "vampire",
   "master mind flayer", "Uruk-hai" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_exile_inited") then
   nh.variable("fuzz_exile_inited", 1)
   for _, b in ipairs(bucs) do
      u.giveobj(obj.new("5 " .. b .. " scrolls of exile"))
   end
   u.giveobj(obj.new("2 potions of confusion"))
   u.giveobj(obj.new("2 scrolls of taming"))
end
for i = 1, 6 + nh.random(6) do
   des.monster({ id = pick(crowd), peaceful = (nh.random(4) == 0),
                 inventory = function()
      if nh.random(3) == 0 then
         des.object({ id = "sack", contents = function()
            des.object("corpse")
         end })
      elseif nh.random(3) == 0 then
         des.object({ id = "oil lamp", lit = true })
      end
   end })
end
for i = 1, 3 + nh.random(3) do
   des.monster({ id = pick(readers), inventory = function()
      des.object({ id = "scroll of exile", buc = pick(bucs) })
   end })
end
for i = 1, 3 + nh.random(3) do
   des.object({ id = "scroll of exile", buc = pick(bucs) })
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("read", 4)
nh.pline("fuzz profile: exile seeded")
