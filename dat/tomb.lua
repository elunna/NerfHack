-- Lost Tomb
-- Copyright (c) 1989 by Jean-Christophe Collet
-- Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed. See license for details.

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel");

des.map([[
             --------                     
             |......|                     
             |......|                     
             |---.--|                     
                 #                        
                 #                        
            |----S---|           --------|
|------|    |........|           |.......|
|......------........|------------.......|
|......+.............+...........+.......|
|......+.............+...........+.......|
|......------........|------------.......|
|------|    |........|           |.......|
            |---S----|           --------|
                #                         
                #                         
             |--.---|                     
             |......|                     
             |......|                     
             --------                     
]]);

--
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

-- Stash spot 1
des.object({ id = "chest", trapped = 0, locked = 1, x = 40, y = 09,
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
                des.object("?")
                des.object("!")
                des.object("!")
                des.object("!")
                des.object()
                des.object()
                des.object()
                des.object()
             end
});

-- Stash spot 2
des.object({ id = "chest", trapped = 0, locked = 1, x = 16, y = 01,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});

-- Stash spot 3
des.object({ id = "chest", trapped = 0, locked = 1, x = 17, y = 18,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});

-- Stash spot 4
des.object({ id = "chest", trapped = 0, locked = 1, x = 40, y = 10,
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
                des.object("?")
                des.object("+")
                des.object("+")
                des.object("+")
                des.object("+")
                des.object()
                des.object()
                des.object()
                des.object()
             end
});

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