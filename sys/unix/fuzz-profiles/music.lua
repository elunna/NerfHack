-- Fuzz profile: instruments.  The hero carries every instrument and a
-- crowd of monsters is around to charm, scare, awaken and calm, with
-- #apply favored.  music.c (~25%) covers the improvised tunes -- scaring
-- with a horn, charming with a harp or flute, awakening with a bugle or
-- drum, the drum of earthquake -- and their per-monster effects.
local instruments = { "pea whistle", "magic whistle", "cheap flute",
   "magic flute", "cheap harp", "magic harp", "tooled horn", "fire horn",
   "frost horn", "bugle", "war drum", "drum of earthquake" }
local crowd = { "gnome lord", "dwarf", "hill orc", "soldier", "jackal",
   "sewer rat", "giant bat", "gnome", "kobold", "hobbit", "acid blob",
   "floating eye", "yellow light", "water moccasin", "gnome king" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_music_inited") then
   nh.variable("fuzz_music_inited", 1)
   for _, m in ipairs(instruments) do
      u.giveobj(obj.new(m))
   end
   u.giveobj(obj.new("2 potions of confusion")) -- confused instrument use
end
-- a crowd to charm/scare/awaken/calm with the tunes
for i = 1, 6 + nh.random(8) do
   des.monster(pick(crowd))
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("apply", 5)
nh.pline("fuzz profile: music seeded")
