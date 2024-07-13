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
des.object("chest", 40, 09)
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.gold({x = 40, y = 09})
des.object("?", 40, 09)
des.object("?", 40, 09)
des.object("?", 40, 09)
des.object("?", 40, 09)
des.object("!", 40, 09)
des.object("!", 40, 09)
des.object("!", 40, 09)
des.object({x = 40, y = 09})
des.object({x = 40, y = 09})
des.object({x = 40, y = 09})
des.object()

-- Stash spot 2
des.object("chest", 16, 01)
des.object({x = 16, y = 01})
des.object({x = 16, y = 01})
des.object({x = 16, y = 01})

-- Stash spot 3
des.object("chest", 17, 18)
des.object({x = 17, y = 18})
des.object({x = 17, y = 18})
des.object({x = 17, y = 18})

-- Stash spot 4
des.object("chest", 40, 10)
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.gold({x = 40, y = 10})
des.object("?", 40, 10)
des.object("?", 40, 10)
des.object("?", 40, 10)
des.object("?", 40, 10)
des.object("+", 40, 10)
des.object("+", 40, 10)
des.object("+", 40, 10)
des.object("+", 40, 10)
des.object({x = 40, y = 10})
des.object({x = 40, y = 10})
des.object({x = 40, y = 10})
des.object({x = 40, y = 10})
des.object({x = 40, y = 10})

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