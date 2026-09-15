-- Fuzz profile: pets.  A pack of tame monsters of every sort (and every
-- level adds more), saddles, leashes, whistles, food and pet-relevant
-- gear, so following between levels, stashing, leashes, riding,
-- displacement, pet abuse and pet death all get exercised.
local pets = { "kitten", "little dog", "pony", "housecat", "large dog",
   "warhorse", "gnome lord", "dwarf", "hill orc", "water nymph",
   "rock troll", "yellow light", "gas spore", "floating eye", "chameleon",
   "vampire", "master mind flayer", "purple worm", "leprechaun", "ki-rin" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_pets_inited") then
   nh.variable("fuzz_pets_inited", 1)
   u.giveobj(obj.new("3 leashes"))
   u.giveobj(obj.new("magic whistle"))
   u.giveobj(obj.new("2 saddles"))
   u.giveobj(obj.new("ring of conflict"))
   u.giveobj(obj.new("10 food rations"))
   u.giveobj(obj.new("5 tripe rations"))
   u.giveobj(obj.new("3 scrolls of taming"))
   u.giveobj(obj.new("bag of holding"))
end
for i = 1, 3 + nh.random(4) do
   des.monster({ id = pick(pets), tame = true, inventory = function()
      if nh.random(3) == 0 then
         des.object("sack")
      end
   end })
end
for i = 1, 2 + nh.random(3) do
   des.object(pick({ "corpse", "food ration", "tripe ration", "dagger",
                     "wand of striking" }))
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("ride", 2)
nh.fuzz_favor("chat", 1)
nh.fuzz_favor("loot", 1)
nh.pline("fuzz profile: pets seeded")
