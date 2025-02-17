-- Lost Tomb
-- Copyright (c) 1989 by Jean-Christophe Collet
-- Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed. See license for details.
-- Ported from SLASH'EM
-- Converted to lua by hackemslashem
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "solidify", "noteleport");
--0         1         2         3         4         5         6         7     
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00             --------              -----    
01  -----      |......|              |...|    
02  |...|      |......|              |...S####
03  |...|      |---.--|              |---|   #
04  |---|          #                         #
05                 #                         #
06            |----S---|           --------| #
07|------|    |........|           |.......| #
08|......------........|------------.......| #
09|......+.............+...........+.......| #
10|......+.............+...........+.......| #
11|......------........|------------.......| #
12|------|    |........|           |.......| #
13            |---S----|           --------| #
14                #                          #
15  |---|         #                          #
16  |...|      |--.---|              |---|   #
17  |...|      |......|              |...S####
18  -----      |......|              |...|    
19             --------              -----    
]]);

local place = selection.new();
place:set(03,02);
place:set(37,01);
place:set(03,17);
place:set(37,18);
place:set(16,01);
place:set(17,18);

-- Make the path somewhat unpredictable

-- Upper left room
if percent(50) then
    des.terrain(selection.line(04,05, 04,06), 'B')
    des.terrain({ x=04, y=04, typ='S' })
    des.terrain({ x=04, y=07, typ='S' })
else
    des.terrain(selection.line(07,02, 12,02), 'B')
    des.terrain({ x=06, y=02, typ='S' })
    des.terrain({ x=13, y=02, typ='S' })
end

-- Lower left room
if percent(50) then
    des.terrain(selection.line(04,13, 04,14), 'B')
    des.terrain({ x=04, y=12, typ='S' })
    des.terrain({ x=04, y=15, typ='S' })
else
    des.terrain(selection.line(07,17, 12,17), 'B')
    des.terrain({ x=06, y=17, typ='S' })
    des.terrain({ x=13, y=17, typ='S' })
end

-- Upper right room
if percent(50) then
    des.terrain(selection.line(37,04, 37,05), 'B')
    des.terrain({ x=37, y=03, typ='S' })
    des.terrain({ x=37, y=06, typ='S' })
else
    des.terrain(selection.line(21,01, 34,01), 'B')
    des.terrain({ x=20, y=01, typ='S' })
    des.terrain({ x=35, y=01, typ='S' })
end

-- Lower right room
if percent(50) then
    des.terrain(selection.line(37,14, 37,15), 'B')
    des.terrain({ x=37, y=13, typ='S' })
    des.terrain({ x=37, y=16, typ='S' })
else
    des.terrain(selection.line(21,18, 34,18), 'B')
    des.terrain({ x=20, y=18, typ='S' })
    des.terrain({ x=35, y=18, typ='S' })
end

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

des.levregion({ region = {01,09,01,09}, type = "branch" })

des.stair("up", 01, 09)

des.door("locked", 7, 09)
des.door("locked", 7, 10)
des.door("locked", 21, 09)
des.door("locked", 21, 10)
des.door("locked", 33, 09)
des.door("locked", 33, 10)

des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")

-- Main cache #1
des.object({ id = "chest", x = 40, y = 09,
             contents = function()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.object("?")
                des.object("?")
                des.object("?")
                des.object("!")
                des.object("!")
                des.object()
             end
});

-- Main cache #2
des.object({ id = "chest", x = 40, y = 10,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.gold()
                des.object("?")
                des.object("?")
                des.object("?")
                des.object("+")
                des.object("+")
                des.object()
             end
});

-- A couple more chests, some empty, one with a nice prize.

local loc = place:rndcoord(1);
des.object({ id = "chest", locked = 1, coord = loc ,
             contents = function()
                 if percent(30) then
                    des.object('magic lamp') -- even if not a wish dlord
                 elseif percent(30) then
                    des.object('magic marker')
                 elseif percent(30) then
                    des.object({ class='/', id='death' })
                 else
                    des.object({ id='gold piece', quan=1 })
                 end
             end
});

local loc = place:rndcoord(2);
des.object({ id = "chest", locked = 1, trapped = 1, coord = loc ,
             contents = function()
                -- nothing
             end
});

local loc = place:rndcoord(3);
des.object({ id = "chest", locked = 1, trapped = 1, coord = loc ,
             contents = function()
                -- nothing
             end
});

local loc = place:rndcoord(4);
des.object({ id = "chest", locked = 1, coord = loc });

local loc = place:rndcoord(5);
des.object({ id = "chest", locked = 1, coord = loc });

local loc = place:rndcoord(6);
des.object({ id = "chest", locked = 1, coord = loc });

-- monsters
des.monster("L", 40, 9)
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")
des.monster("shadow")

des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")

des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")
des.monster("M")