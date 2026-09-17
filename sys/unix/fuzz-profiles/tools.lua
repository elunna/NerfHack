-- Fuzz profile: tools.  The hero carries the full applyable tool kit and
-- some monsters carry tools too, with #apply/#loot/#tip/#force favored, so
-- apply.c (~24%, dozens of never-run functions) gets exercised: whistles,
-- horns, flutes, drums, leash, mirror, camera, lamps, candles, bags,
-- stethoscope, tinning kit, grease, towel, pick-axe, bullwhip, unicorn
-- horn, land mine and bear trap, plus looting/tipping/force-locking the
-- containers.
local tools = { "magic whistle", "pea whistle", "fire horn", "frost horn",
   "tooled horn", "bugle", "cheap flute", "magic flute", "cheap harp",
   "magic harp", "war drum", "drum of earthquake", "leash", "magic marker",
   "mirror", "blindfold", "towel", "unicorn horn", "stethoscope",
   "tinning kit", "can of grease", "pick-axe", "bullwhip",
   "expensive camera", "lantern", "oil lamp", "tallow candle",
   "wax candle", "land mine", "beartrap", "horn of plenty" }
local carriers = { "gnome lord", "dwarf", "hill orc", "soldier",
   "Woodland-elf", "gnome king", "captain", "kobold shaman" }
local function pick(t) return t[nh.random(#t) + 1] end

if not nh.variable("fuzz_tools_inited") then
   nh.variable("fuzz_tools_inited", 1)
   for _, t in ipairs(tools) do
      u.giveobj(obj.new(t))
   end
   u.giveobj(obj.new("bag of holding"))
   u.giveobj(obj.new("bag of tricks"))
   u.giveobj(obj.new("oilskin sack"))
   u.giveobj(obj.new("7 wax candles"))
   u.giveobj(obj.new("5 food rations")) -- for the tinning kit / horn of plenty
end
-- containers on the floor to loot, tip and force
for i = 1, 3 + nh.random(3) do
   des.object({ id = "chest", contents = function()
      des.object("wax candle")
      des.object("ring of adornment")
      if nh.random(2) == 0 then des.object("tallow candle") end
   end })
end
for i = 1, 2 + nh.random(3) do des.object("sack") end
-- monsters carrying tools
for i = 1, 3 + nh.random(4) do
   des.monster({ id = pick(carriers), inventory = function()
      des.object("tooled horn")
      des.object(pick({ "leash", "mirror", "bugle", "pick-axe",
                        "oil lamp", "war drum" }))
   end })
end
-- lean the random command choice toward this profile's commands
nh.fuzz_favor("apply", 4)
nh.fuzz_favor("loot", 3)
nh.fuzz_favor("tip", 2)
nh.fuzz_favor("force", 1)
nh.pline("fuzz profile: tools seeded")
