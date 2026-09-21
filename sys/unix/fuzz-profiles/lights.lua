-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: light sources.  Lit lamps and candles on the floor and in
-- monsters' packs, light-emitting monsters, and monsters wearing gear
-- that only glows while worn, so light source creation, movement,
-- snuffing and the worn-only cases stay under constant pressure.
local emitters = { "yellow light", "black light", "fire vortex",
   "flaming sphere", "shrieker" }
local carriers = { "gnome lord", "dwarf", "dwarf lord", "hill orc",
   "soldier", "hobbit", "watchman", "Woodland-elf", "water nymph",
   "leprechaun" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_lights_inited") then
   nh.variable("fuzz_lights_inited", 1)
   u.giveobj(obj.new("3 oil lamps"))
   u.giveobj(obj.new("lantern"))
   u.giveobj(obj.new("10 wax candles"))
   u.giveobj(obj.new("10 tallow candles"))
   u.giveobj(obj.new("5 potions of oil"))
end
for i = 1, 3 + nh.random(4) do
   des.object({ id = (nh.random(2) == 0) and "oil lamp" or "wax candle",
                lit = true })
end
for i = 1, 3 + nh.random(4) do
   des.monster({ id = pick(carriers), inventory = function()
      des.object({ id = (nh.random(2) == 0) and "oil lamp" or "lantern",
                   lit = true })
      if nh.random(3) == 0 then
         des.object({ id = "gold dragon scales" })
      elseif nh.random(4) == 0 then
         des.object({ id = "shield of reflection", name = "Mirrorbright" })
      end
   end })
end
for i = 1, 3 + nh.random(4) do
   des.monster(pick(emitters))
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("apply", 3)
nh.pline("fuzz profile: lights seeded")
