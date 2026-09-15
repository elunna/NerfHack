-- Fuzz profile: corpses that come back.  Trolls, zombies, mummies and
-- wraiths on every level plus their corpses lying around, in ice boxes
-- and buried, so revive/zombify/rot/mold timers and every freeze, thaw,
-- burial and unearth path around them get exercised.
local undead = { "rock troll", "ice troll", "water troll", "Olog-hai",
   "troll", "gnome zombie", "human zombie", "elf zombie", "kobold zombie",
   "human mummy", "gnome mummy", "wraith", "vampire", "ettin" }
local bodies = { "rock troll", "ice troll", "water troll", "Olog-hai",
   "troll", "human zombie", "gnome zombie", "lizard", "lichen", "wraith",
   "newt", "ettin" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_revival_inited") then
   nh.variable("fuzz_revival_inited", 1)
   u.giveobj(obj.new("2 wands of undead turning"))
   u.giveobj(obj.new("wand of digging"))
   u.giveobj(obj.new("pick-axe"))
   u.giveobj(obj.new("3 scrolls of remove curse"))
end
for i = 1, 4 + nh.random(4) do
   des.monster(pick(undead))
end
for i = 1, 4 + nh.random(6) do
   des.object({ id = "corpse", montype = pick(bodies) })
end
for i = 1, 1 + nh.random(3) do
   des.object({ id = "ice box", contents = function()
      for j = 1, 1 + nh.random(4) do
         des.object({ id = "corpse", montype = pick(bodies) })
      end
   end })
end
for i = 1, 1 + nh.random(3) do
   local c = obj.new(pick(bodies) .. " corpse")
   c:placeobj(u.ux, u.uy)
   c:bury()
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("apply", 2)
nh.fuzz_favor("zap", 1)
nh.pline("fuzz profile: revival seeded")
