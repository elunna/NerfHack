-- # NetHack 3.6	yendor.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.10 $
-- #	Copyright (c) 1989 by Jean-Christophe Collet
-- #	Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- # NetHack may be freely redistributed.  See license for details.
-- #
-- # The top (real) wizard level.
-- MAZE:"wizard1",' '

-- Ported from EvilHack
-- Converted to LUA by hackemslashem

des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "noteleport", "hardfloor", "nommap", "solidify", "shortsighted")
--0         1         2         3         4         5         6         7    7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "center", valign = "center", map = [[
                                                                            
         -------                                                            
         |.....|                                                            
        ---LLL---                                                           
        |.......|                                                           
        |.......|                                                           
    --F-----------F--                                                       
    |...............|                                ..t                    
    F...............|-FF--                         .......                  
    |...|.......|...|....|L..........     ..........|.....t                 
    |...|.......|...|....|L..    ...........  ..  ..|......                 
    F...............|-FF--                         ..t....                  
    |...............|                                ...                    
    --F-----------F--                                                       
        |.......|                                                           
        |.......|                                                           
        ---LLL---                                                           
         |.....|                                                            
         -------                                                            
                                                                            
]] });

-- TELEPORT_REGION:(06,09,07,10),(00,00,00,00)

-- # entire tower in a region, constrains monster migration
des.region({ region={00,00,79,19}, lit=0, type="ordinary", arrival_room=true })

-- # random wandering monster locations
local places = { {03,02}, {03,17}, {24,04}, {24,15},
                 {40,06}, {40,13}, {61,02}, {61,17} }
shuffle(places)

-- # stairs down
des.ladder("down", 05,09)

-- # drawbridges
des.drawbridge({ dir="west", state="closed", x=26,y=09})
des.drawbridge({ dir="west", state="closed", x=26,y=10})

des.object("chest", 56, 10)

-- # doors
des.door("locked",12,06)
des.door("locked",12,13)
des.door("locked",20,09)
des.door("locked",20,10)

-- # The wizard and his pet
des.monster({ id = "Wizard of Yendor", x=55, y=10, waiting=1 })
des.monster({ id = "hell hound", x=55, y=09, waiting=1 })

-- # The local treasure
des.object("Book of the Dead", 55, 10)

des.object({ id = "chest", trapped = 0, locked = 1, x = 55, y = 09,
             contents = function()
                -- This is converted into a zappable scroll of wishing
                des.object("wand of wishing");
                des.object("full healing")
             end
});

-- # defenders inside the tower
des.monster("infidel", 12,08)
des.monster("weredemon", 12,11)
des.monster("elven cleric", 09,04)
des.monster("elven cleric", 15,04)
des.monster("demilich", 15,15)
des.monster("demilich", 09,15)

-- # bridge
des.monster({ class = "H", x = 39, y = 10, asleep = 1, peaceful = 0 })

-- # flying monsters outside
des.monster({ class = "D", coord = places[1], peaceful = 0 })
des.monster({ class = "D", coord = places[2], peaceful = 0 })
des.monster({ class = "D", coord = places[3], peaceful = 0 })
des.monster({ class = "D", coord = places[4], peaceful = 0 })

des.monster({ class = "V", coord = places[5], peaceful = 0 })
des.monster({ class = "V", coord = places[6], peaceful = 0 })
des.monster({ class = "e", coord = places[7], peaceful = 0 })
des.monster({ class = "e", coord = places[8], peaceful = 0 })

-- # loot
des.object("?",11,02)
des.object("?",12,02)
des.object("?",13,02)
des.object("?",11,17)
des.object("?",12,17)
des.object("?",13,17)

des.object("+",10,02)
des.object("+",14,02)
des.object("+",10,17)
des.object("+",14,17)

-- # none shall pass
des.non_diggable()
des.non_passwall()
