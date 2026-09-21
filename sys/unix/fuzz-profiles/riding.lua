-- Copyright (c) Erik Lunna, 2025-2026.
-- NetHack may be freely redistributed.  See license for details.
-- Fuzz profile: riding.  The hero carries saddles and a lance, and tame
-- rideable mounts appear on every level, with #ride/#apply(saddle)/#kick/
-- #jump favored.  steed.c (~15%) covers saddling, mounting and
-- dismounting, riding into things, kicking and jousting from the saddle,
-- and the steed being hurt, killed, scared or displaced out from under
-- the hero.
local mounts = { "pony", "horse", "warhorse" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_riding_inited") then
   nh.variable("fuzz_riding_inited", 1)
   for i = 1, 3 do u.giveobj(obj.new("saddle")) end
   u.giveobj(obj.new("lance"))                 -- jousting from the saddle
   u.giveobj(obj.new("ring of levitation"))    -- riding + levitation edges
   u.giveobj(obj.new("2 potions of confusion"))
   u.giveobj(obj.new("10 food rations"))
end
-- tame, rideable mounts (each carrying a saddle to apply), plus a couple
-- of hostile ones to fight and steal a saddle from
for i = 1, 2 + nh.random(3) do
   des.monster({ id = pick(mounts), peaceful = true, tame = true,
      inventory = function() des.object("saddle") end })
end
for i = 1, 1 + nh.random(2) do
   des.monster(pick(mounts))
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("ride", 4)
nh.fuzz_favor("apply", 3)   -- apply a saddle to an adjacent steed
nh.fuzz_favor("kick", 2)
nh.fuzz_favor("jump", 1)
nh.pline("fuzz profile: riding seeded")
