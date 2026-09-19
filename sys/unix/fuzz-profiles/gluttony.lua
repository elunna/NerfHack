-- Fuzz profile: gluttony.  A hero buried in corpses, tins, eggs and special
-- foods with 'eat' favored, so eat.c's rarely-reached surface runs hard:
-- eatcorpse()'s huge intrinsic/resistance/petrify/slime/hallucinate switch,
-- opentin()/tin_variety(), eatspecial(), food poisoning from corpses that rot
-- in the pack, vomiting, and choking-to-death from overeating.  The random
-- command stream almost never picks 'eat' (and rarely with the right food on
-- hand), so eat.c is one of the coldest large subsystems -- no other profile
-- exercises it, and revival only *seeds* corpses without ever eating them.
local corpses = {
   -- intrinsic / telepathy / speed / stun granters
   "floating eye", "quantum mechanic", "mind flayer", "master mind flayer",
   "stalker", "tengu", "giant bat", "gnome", "newt", "bat",
   -- resistances (dragons)
   "red dragon", "white dragon", "blue dragon", "green dragon",
   "orange dragon", "yellow dragon", "black dragon", "gray dragon",
   "silver dragon",
   -- dangerous / special-effect corpses
   "cockatrice", "chickatrice", "acid blob", "green slime", "kobold",
   "killer bee", "yellow mold", "green mold", "brown mold", "red mold",
   "werewolf", "wererat", "werejackal", "human zombie", "gnome zombie",
   "giant mimic", "lizard", "lichen", "wraith",
}
local tins = { "tin of spinach", "tin" }
local foods = { "food ration", "lembas wafer", "cram ration", "K-ration",
   "C-ration", "tripe ration", "egg", "cockatrice egg", "apple", "pear",
   "banana", "orange", "melon", "carrot", "clove of garlic",
   "sprig of wolfsbane", "eucalyptus leaf", "slime mold", "kelp frond",
   "fortune cookie", "candy bar", "cream pie", "lump of royal jelly",
   "pancake", "meatball", "meat stick", "huge chunk of meat" }
local function pick(t) return t[nh.random(#t) + 1] end

-- restock the pack (and the floor) every level, so there is always something
-- to eat no matter where the fuzzer wanders
for i = 1, 10 + nh.random(8) do
   u.giveobj(obj.new(pick(corpses) .. " corpse"))
end
for i = 1, 3 + nh.random(3) do
   u.giveobj(obj.new(pick(tins)))
end
for i = 1, 4 + nh.random(4) do
   u.giveobj(obj.new(pick(foods)))
end
for i = 1, 4 + nh.random(4) do
   des.object({ id = "corpse", montype = pick(corpses) })
end
-- lean the random command choice hard toward eating
nh.fuzz_favor("eat", 12)
nh.pline("fuzz profile: gluttony seeded")
