-- # The middle wizard level.
-- MAZE:"wizard2",' '

des.level_init({ style="mazegrid", bg ="-" });
des.level_flags("mazelevel", "noteleport", "hardfloor", "nommap", "solidify")

--0         1         2         3         4         5         6         7    7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
local wiz2 = des.map({ halign = "center", valign = "center", map = [[
          -------------------          
       ----.................----       
    ----.....-------------.....----    
  ---.....----...........----.....---  
  ||....---.................---....||  
  |...---.|..--------------------...|  
--|..||...|--|wwwwwS.FL.........||..|--
|.F..|....|...wwwww|-|L..........|..F.|
|.|..|....|...wwwwwS.FL..........|..F.|
|.F..|....|...wwwww|-|L..........|..F.|
--|..||...|--|wwwwwS.FL.........||..|--
  |...---.|..--------------------...|  
  ||....---.................---....||  
  ---.....----...........----.....---  
    ----.....-------------.....----    
       ----.................----       
          -------------------          
]] });

-- TELEPORT_REGION:(01,07,01,07),(00,00,00,00)

-- # entire tower in a region, constrains monster migration
des.region({ region={00,00,38,16}, lit=0, type="ordinary", arrival_room=true })

-- # random wandering monster locations
local places = { {07,04}, {19,01}, {19,04}, {31,04}, {31,12},
                 {19,12}, {19,15}, {07,12}, {24,07}, {24,09},
                 {08,08} }
shuffle(places)

-- # various captive monsters
local bars = { {20,06}, {20,08}, {20,10}, {37,08} }
shuffle(bars)

-- # stairs
des.ladder("up",11,08)
des.ladder("down",01,08)

-- # random corridor path / secret doors
if percent(50) then
  des.terrain({03,05}, "-")
  des.terrain({04,05}, "-")
  des.terrain({05,05}, "-")
  des.terrain({07,05}, "S")
else
  des.terrain({03,11}, "-")
  des.terrain({04,11}, "-")
  des.terrain({05,11}, "-")
  des.terrain({07,11}, "S")
end

if percent(50) then
  des.terrain({18,11}, "S")
  des.terrain({10,05}, "S")
else
  des.terrain({18,05}, "S")
  des.terrain({10,11}, "S")
end

-- # doors
des.door("locked", 02,08);
des.door("locked", 24,05);
des.door("locked", 24,11);

-- # captive monsters
des.monster({ id = "angel", coord = bars[1] })
des.monster({ id = "third eye", coord = bars[2], peaceful = 0 })
des.monster({ class = "D", coord = bars[3], peaceful = 0 })
des.monster({ class = "D", coord = bars[4], peaceful = 0 })

-- # roaming monsters
des.monster({ class = "D", coord = places[1], peaceful = 0 })
des.monster({ class = "&", coord = places[2], peaceful = 0 })
des.monster({ class = "J", coord = places[3], peaceful = 0 })
des.monster({ class = "L", coord = places[4], peaceful = 0 })
des.monster({ class = "T", coord = places[5], peaceful = 0 })
des.monster({ class = "N", coord = places[6], peaceful = 0 })

des.monster({ id = "elven cleric", coord = places[7], peaceful = 0 })
des.monster({ id = "elven cleric", coord = places[8], peaceful = 0 })
des.monster({ id = "ogre mage", coord = places[9], peaceful = 0 })
des.monster({ id = "elven cleric", coord = places[10], peaceful = 0 })
des.monster({ id = "elven cleric", coord = places[11], peaceful = 0 })

-- # wizard apprectices
des.monster({ id = "apprentice", x = 29, y = 07, peaceful = 0 })
des.monster({ id = "apprentice", x = 29, y = 09, peaceful = 0 })
des.monster({ id = "apprentice", x = 30, y = 07, peaceful = 0 })
des.monster({ id = "apprentice", x = 30, y = 09, peaceful = 0 })

-- # trice nest
des.monster({ id = "cockatrice", x = 14, y = 06, peaceful = 0 })
des.monster({ id = "cockatrice", x = 14, y = 08, peaceful = 0 })
des.monster({ id = "cockatrice", x = 14, y = 10, peaceful = 0 })
des.monster({ id = "cockatrice", x = 15, y = 07, peaceful = 0 })
des.monster({ id = "cockatrice", x = 15, y = 09, peaceful = 0 })
des.monster({ id = "cockatrice", x = 16, y = 06, peaceful = 0 })
des.monster({ id = "cockatrice", x = 16, y = 10, peaceful = 0 })
des.monster({ id = "cockatrice", x = 17, y = 07, peaceful = 0 })
des.monster({ id = "cockatrice", x = 17, y = 09, peaceful = 0 })
des.monster({ id = "cockatrice", x = 18, y = 06, peaceful = 0 })
des.monster({ id = "cockatrice", x = 18, y = 08, peaceful = 0 })
des.monster({ id = "cockatrice", x = 18, y = 10, peaceful = 0 })
des.monster({ id = "basilisk", x = 16, y = 08, peaceful = 0 })
des.monster({ id = "gorgon hulk", x = 16, y = 07, peaceful = 0 })
des.monster({ id = "gorgon hulk", x = 16, y = 09, peaceful = 0 })

-- # loot
des.object("chest", 20,06)
des.object("chest", 20,08)
des.object("chest", 20,10)

-- # traps
des.trap("random", 12,07)
des.trap("random", 12,08)
des.trap("random", 12,09)
des.trap("random", 24,06)
des.trap("random", 24,10)

-- # none shall pass
des.non_diggable()
des.non_passwall()
