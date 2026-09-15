-- Fuzz profile: game over.  The fuzzer normally life-saves the hero
-- through every death and refuses to climb out of the dungeon, so the
-- end-of-game code -- disclosure, dumplog (text and HTML), tombstone,
-- topten, memory teardown -- never runs under it.  Once the game has some
-- history worth dumping, let a share of deaths stand and now and then
-- send the hero back to level 1 to walk out.
if not nh.variable("fuzz_gameover_inited") then
   nh.variable("fuzz_gameover_inited", 1)
   -- a container with contents and a spellbook give the dumplog's
   -- inventory, container and spell sections something to print
   local sack = obj.new("sack")
   sack:addcontent(obj.new("2 potions of water"))
   sack:addcontent(obj.new("scroll of light"))
   u.giveobj(sack)
   u.giveobj(obj.new("spellbook of force bolt"))
end
if u.moves > 2000 then
   nh.fuzz_die(20)              -- every death from here on: 20% real
   if nh.random(25) == 0 then   -- one level change in 25: leave the dungeon
      nh.fuzz_escape()
   end
end
nh.fuzz_favor("read", 2)
nh.pline("fuzz profile: gameover seeded")
