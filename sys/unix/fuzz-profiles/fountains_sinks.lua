-- Fuzz profile: fountains and sinks.  Fountains and sinks are scattered
-- on every level and the hero carries rings, gems, gear and potions to
-- quaff/dip/drop/kick, with those commands favored.  fountain.c is the
-- coldest gameplay file (~4%): quaffing (water demon/nymph/snake, curses,
-- gushes, gem gifts, dry-up), dipping (Excalibur, rust, dilution, oil),
-- sink kicking (rings and gear popping up, sink-to-fountain), and
-- fountain/sink dry-up all live there.
local rings = { "adornment", "protection", "levitation", "conflict",
   "polymorph", "teleportation", "aggravate monster", "free action",
   "slow digestion", "poison resistance", "invisibility", "see invisible",
   "searching", "stealth", "hunger", "warning" }
local gems = { "diamond", "ruby", "emerald", "sapphire", "luckstone",
   "loadstone", "touchstone", "flint", "worthless piece of green glass",
   "rock" }
local watermons = { "water moccasin", "water nymph", "water demon",
   "giant eel", "electric eel", "piranha" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_fountains_inited") then
   nh.variable("fuzz_fountains_inited", 1)
   for i = 1, 6 do u.giveobj(obj.new("ring of " .. pick(rings))) end
   for i = 1, 4 do u.giveobj(obj.new(pick(gems))) end
   u.giveobj(obj.new("long sword"))            -- dip for Excalibur
   u.giveobj(obj.new("3 potions of water"))    -- dip / dilute / holy water
   u.giveobj(obj.new("2 potions of fruit juice"))
   u.giveobj(obj.new("2 uncursed potions of object detection"))
   u.giveobj(obj.new("1000 gold pieces"))      -- gems from a fountain quaff
end
-- scatter fountains and sinks across the level
for i = 1, 4 + nh.random(4) do des.feature("fountain") end
for i = 1, 3 + nh.random(3) do des.feature("sink") end
-- water monsters to fight around them
for i = 1, 3 + nh.random(4) do des.monster(pick(watermons)) end
-- loose rings and gems to drop in fountains / kick out of sinks
for i = 1, 3 + nh.random(3) do
   des.object({ id = "ring of " .. pick(rings), buc = "uncursed" })
end
for i = 1, 2 + nh.random(3) do des.object(pick(gems)) end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("quaff", 4)
nh.fuzz_favor("dip", 3)
nh.fuzz_favor("kick", 2)
nh.fuzz_favor("sit", 1)
nh.pline("fuzz profile: fountains_sinks seeded")
