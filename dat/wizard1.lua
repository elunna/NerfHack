-- # NetHack 3.6	yendor.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.10 $
-- #	Copyright (c) 1989 by Jean-Christophe Collet
-- #	Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- # NetHack may be freely redistributed.  See license for details.
-- #
-- # The top (real) wizard level.
-- MAZE:"wizard1",' '

-- Ported from EvilHack with major modifications
-- Converted to LUA by hackemslashem

des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "noteleport", "hardfloor", "nommap", "solidify", "shortsighted")
--0         1         2         3
--0123456789012345678901234567890
des.map({ halign = "center", valign = "center", map = [[
00          -------          
01          |.....|          
02         ---...---         
03         |.......|         
04         |.......|         
05     --F-----+-----F--     
06     |,,,,,.....PPPPP|     
07--FF-|,,,...._....PPP|-FF--
08|...LF,....|...|....PF....|
09|....FL....|...|....,FP...|
10--FF-|LLL...._....,,,|-FF--
11     |LLLLL.....,,,,,|     
12     --F-----+-----F--     
13         |.......|         
14         |.......|         
15         ---...---         
16          |.....|          
17          -------          
]] });

-- TELEPORT_REGION:(06,09,07,10),(00,00,00,00)

-- # random wandering monster locations
local places = { {13,01}, {13,16} }
shuffle(places)

-- # entire tower in a region, constrains monster migration
des.region({ region={00,00,79,19}, lit=0, type="ordinary", arrival_room=true })

-- # stairs down
des.ladder("down", 06,06)

des.object({ id = "chest", coord = places[2] })

-- # doors
des.door("locked",13,05)
des.door("locked",13,12)

-- # The wizard and his pet
des.monster({ id = "Wizard of Yendor", coord = places[1], waiting=1 })
des.monster({ id = "hell hound", coord = places[2], waiting=1 })

-- # The local treasure
des.object({ id = "Book of the Dead", coord = places[1] })

des.object({ id = "chest", trapped = 0, locked = 1, coord = places[1],
             contents = function()
                -- This is converted into a zappable scroll of wishing
                des.object("wand of wishing");
                des.object("full healing")
                des.object("?")
                des.object("?")
                des.object("+")
                des.object("+")
             end
});

-- # entry 
des.monster("infidel", 13,07)
des.monster("weredemon", 16,07)

-- # north room
des.monster("elven cleric", 10,03)
des.monster("elven cleric", 16,03)

-- # south room
des.monster("demilich", 10,14)
des.monster("demilich", 16,14)

-- # bridge
des.monster({ class = "H", x = 20, y = 11, asleep = 1, peaceful = 0 })

-- east wing
des.monster({ class = "D", x = 01, y = 08, peaceful = 0 })
des.monster({ class = "D", x = 02, y = 08, peaceful = 0 })
des.monster({ class = "D", x = 01, y = 09, peaceful = 0 })
des.monster({ class = "D", x = 02, y = 09, peaceful = 0 })

-- west wing
des.monster({ class = "D", x = 24, y = 08, peaceful = 0 })
des.monster({ class = "D", x = 25, y = 08, peaceful = 0 })
des.monster({ class = "D", x = 24, y = 09, peaceful = 0 })
des.monster({ class = "D", x = 25, y = 09, peaceful = 0 })

-- # none shall pass
des.non_diggable()
des.non_passwall()
