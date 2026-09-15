-- Fuzz profile: artifacts in play.  The hero starts with a few; every
-- level gets monsters carrying or wearing others, so monster-side
-- artifact handling (worn-only light sources, worn masks, theft, death
-- drops, artifact blasts, #wizmakemap teardown) is exercised constantly.
local artifacts = {
   { "Carnwennan", "knife" }, { "Demonbane", "mace" },
   { "Excalibur", "long sword" }, { "Grayswandir", "saber" },
   { "Mortality Dial", "morning star" }, { "Skullcrusher", "club" },
   { "Pridwen", "large shield" }, { "Oathfire", "bracers" },
   { "Quick Blade", "short sword" }, { "Serenity", "spear" },
   { "Snickersnee", "katana" }, { "Sunsword", "long sword" },
   { "Cleaver", "battle-axe" }, { "David's Sling", "sling" },
   { "Deluder", "cloak of displacement" }, { "Disrupter", "mace" },
   { "Giantslayer", "spear" }, { "Magicbane", "quarterstaff" },
   { "Mirrorbright", "shield of reflection" },
   { "Thunderfists", "gauntlets of force" }, { "Mjollnir", "war hammer" },
   { "Mouser's Scalpel", "rapier" }, { "Snakeskin", "robe" },
   { "The End", "scythe" }, { "Vorpal Blade", "long sword" },
   { "Whisperfeet", "speed boots" }, { "Acidfall", "long sword" },
   { "The Amulet of Storms", "amulet of flying" },
   { "Angelslayer", "trident" }, { "Blackshroud", "cloak of invisibility" },
   { "Doomblade", "short sword" }, { "Grimtooth", "orcish dagger" },
   { "Hellfire", "crossbow" }, { "Mayhem", "stomping boots" },
   { "Plague", "bow" }, { "Poseidon's Trident", "trident" },
   { "Serpent's Tongue", "dagger" }, { "Sting", "elven dagger" },
   { "Stormbringer", "runesword" }, { "Orcrist", "elven broadsword" },
   { "Glamdring", "long sword" }, { "Dragonbane", "broadsword" },
   { "Drowsing Rod", "quarterstaff" }, { "Fire Brand", "long sword" },
   { "Frost Brand", "long sword" }, { "Load Brand", "heavy sword" },
   { "Ogresmasher", "war hammer" }, { "Origin", "quarterstaff" },
   { "The Lenses of Truth", "lenses" }, { "Trollsbane", "morning star" },
   { "Werebane", "saber" },
}
local carriers = { "gnome lord", "dwarf", "dwarf lord", "hill orc",
   "Mordor orc", "Uruk-hai", "orc-captain", "bugbear", "soldier",
   "Woodland-elf", "Grey-elf", "hobbit", "gnome king", "watchman", "ogre",
   "water nymph", "vampire", "human mummy", "wraith" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_artifacts_inited") then
   nh.variable("fuzz_artifacts_inited", 1)
   for i = 1, 4 do
      u.giveobj(obj.new(pick(artifacts)[1]))
   end
end
-- an artifact that already exists elsewhere just yields a plain named item
for i = 1, 6 + nh.random(6) do
   local a = pick(artifacts)
   des.monster({ id = pick(carriers), inventory = function()
      des.object({ id = a[2], name = a[1] })
      if nh.random(3) == 0 then
         des.object({ id = "gold dragon scales" })
      end
   end })
end
for i = 1, 2 + nh.random(3) do
   local a = pick(artifacts)
   des.object({ id = a[2], name = a[1] })
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("wizwish", 3)
nh.fuzz_favor("wizmakemap", 1)
nh.pline("fuzz profile: artifacts seeded")
