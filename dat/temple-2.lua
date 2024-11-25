-- Lost Tomb
-- Copyright (c) 1989 by Jean-Christophe Collet
-- Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed. See license for details.

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "solidify", "noflip");

-- Ported from SlashTHEM
-- Converted to lua by hackemslashem
-- Author unknown
--
-- This is the Temple of Moloch.
-- Within lie priests, demons, and, most importantly.... candles!
--0         1         2         3         4         5     
--01234567890123456789012345678901234567890123456789012345
des.map([[
            ----- ----- ----- ----- -----               
    ---     |...| |...| |...| |...| |...|   --------    
   -|.|-----FFFFF-FFFFF-FFFFF-FFFFF-FFFFF-| |......|    
  -|...|..................................--|......|---|
 -|....|...........................................|...|
 |.....+...........................................S...|
 -|....|...........................................|...|
  -|...|..................................--|......|---|
   -|.|-----FFFFF-FFFFF-FFFFF-FFFFF-FFFFF-| |......|    
    ---     |...| |...| |...| |...| |...|   --------    
            ----- ----- ----- ----- -----               
]]);

-- RANDOM_MONSTERS: '&','Z'

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

des.region({ region={06,01,48,09}, lit=1, type="temple", filled=2 })

des.region({ region={00,00,55,08}, lit=0, type="ordinary" })

-- the altar of Moloch (making four will make four priests....)
des.altar({ x=47, y=05, align="noalign",type="shrine" })
des.altar({ x=47, y=05, align="noalign",type="shrine" })
des.altar({ x=47, y=05, align="noalign",type="shrine" })
des.altar({ x=47, y=05, align="noalign",type="shrine" })

des.levregion({ region = {03,05,03,05}, type = "branch" })
--des.stair("up", 04,05)
des.door("locked", 07, 05)

-- flanking the doorway....
des.trap("spiked pit",06,04)
des.trap("spiked pit",06,06)

-- the treasure chamber!
des.object({ id = "chest", x = 52, y = 03,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});
des.object({ id = "chest", x = 53, y = 03,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});
des.object({ id = "chest", x = 54, y = 03,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});
des.object({ id = "chest", x = 52, y = 04,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});
des.object({ id = "chest", x = 53, y = 04,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});
des.object({ id = "chest", x = 54, y = 04,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});
des.object({ id = "chest", x = 52, y = 05,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});
des.object({ id = "chest", x = 53, y = 05,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});
des.object({ id = "chest", x = 54, y = 05,
             contents = function()
                des.object("wax candle")
                des.gold()
                des.gold()
                des.object()
                des.object()
                des.object()
             end
});

--  five gargoyles on either side, in the niches of the temple
-- all should start asleep
des.monster({id="glowing eye", x=14, y=01, peaceful=0})
des.monster({id="glowing eye", x=14, y=09, peaceful=0})
des.monster({id="pyrolisk", x=20, y=01, peaceful=0})
des.monster({id="pyrolisk", x=20, y=09, peaceful=0})
des.monster({id="pyrolisk", x=26, y=01, peaceful=0})
des.monster({id="pyrolisk", x=26, y=09, peaceful=0})
des.monster({id="red dragon", x=32, y=01, peaceful=0})
des.monster({id="red dragon", x=32, y=09, peaceful=0})
des.monster({id="pyrolisk", x=38, y=01, peaceful=0})
des.monster({id="pyrolisk", x=38, y=09, peaceful=0})

-- demons down by the altar...
-- Replaced the babau with an ice devil
des.monster({id="bone devil",   x=37, y=03, peaceful=0})
des.monster({id="vrock",        x=37, y=07, peaceful=0})
des.monster({id="ice devil",    x=38, y=03, peaceful=0})
des.monster({id="horned devil", x=38, y=07, peaceful=0})
des.monster({id="barbed devil", x=39, y=03, peaceful=0})
des.monster({id="hezrou",       x=39, y=07, peaceful=0})

-- 2 more ghoul mages for good measure...
des.monster({id="ghoul mage", x=32, y=04, peaceful=0})
des.monster({id="ghoul mage", x=32, y=06, peaceful=0})

-- a horde of zombies is also inside....

des.monster({class="Z", x=17, y=04, peaceful=0})
des.monster({class="Z", x=18, y=04, peaceful=0})
des.monster({class="Z", x=19, y=04, peaceful=0})
des.monster({class="Z", x=20, y=04, peaceful=0})
des.monster({class="Z", x=21, y=04, peaceful=0})
des.monster({class="Z", x=22, y=04, peaceful=0})
des.monster({class="Z", x=23, y=04, peaceful=0})

des.monster({class="Z", x=17, y=05, peaceful=0})
des.monster({class="Z", x=18, y=05, peaceful=0})
des.monster({class="Z", x=19, y=05, peaceful=0})
des.monster({class="Z", x=20, y=05, peaceful=0})
des.monster({class="Z", x=21, y=05, peaceful=0})
des.monster({class="Z", x=22, y=05, peaceful=0})
des.monster({class="Z", x=23, y=05, peaceful=0})

des.monster({class="Z", x=17, y=06, peaceful=0})
des.monster({class="Z", x=18, y=06, peaceful=0})
des.monster({class="Z", x=19, y=06, peaceful=0})
des.monster({class="Z", x=20, y=06, peaceful=0})
des.monster({class="Z", x=21, y=06, peaceful=0})
des.monster({class="Z", x=22, y=06, peaceful=0})
des.monster({class="Z", x=23, y=06, peaceful=0})

des.engraving({06,04}, "engrave", "Those Not of Moloch, Begone!")