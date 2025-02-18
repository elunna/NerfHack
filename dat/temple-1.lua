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
des.map([[
            ----- ----- ----- ----- -----               
            |...| |...| |...| |...| |...|               
   ----------...---...---...---...---...|-|        -----
   |...|..................................|        |...|
   |...+..................................S########S...|
   |...|..................................|        |...|
   ----------...---...---...---...---...|-|        -----
            |...| |...| |...| |...| |...|               
            ----- ----- ----- ----- -----               
]]);

-- RANDOM_MONSTERS: '&','Z'

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

des.region({ region={08,01,41,07}, lit=1, type="temple", filled=2 })

des.region({ region={00,00,55,08}, lit=0, type="ordinary" })

-- the altar of Moloch
des.altar({ x=40, y=04, align="noalign",type="shrine" })

-- We need to generate these separately, otherwise they all tend the same altar.
-- If an orc/ or unaligned player converts the altar only one of the priests
-- would get angry.
des.monster({ id = "aligned cleric", x=40, y=03, align="noalign", peaceful=0 })
des.monster({ id = "aligned cleric", x=40, y=05, align="noalign", peaceful=0 })
des.monster({ id = "aligned cleric", x=41, y=04, align="noalign", peaceful=0 })

des.levregion({ region = {05,04,05,04}, type = "branch" })
des.stair("up", 05, 04)
des.door("locked", 7, 04)

-- flanking the doorway....
des.trap("spiked pit",06,03)
des.trap("spiked pit",06,05)

function chest_fill()
    des.object("wax candle")
    des.gold()
    des.gold()
    des.object()
    if percent(50) then
        des.object()
    end
    if percent(25) then
        des.object()
    end
end

-- the treasure chamber!
des.object({ id = "chest", x = 52, y = 03, contents = chest_fill });
des.object({ id = "chest", x = 53, y = 03, contents = chest_fill });
des.object({ id = "chest", x = 54, y = 03, contents = chest_fill });
des.object({ id = "chest", x = 52, y = 04, contents = chest_fill });
des.object({ id = "chest", x = 53, y = 04, contents = chest_fill });
des.object({ id = "chest", x = 54, y = 04, contents = chest_fill });
des.object({ id = "chest", x = 52, y = 05, contents = chest_fill });
des.object({ id = "chest", x = 53, y = 05, contents = chest_fill });
des.object({ id = "chest", x = 54, y = 05, contents = chest_fill });

--  five gargoyles on either side, in the niches of the temple
-- all should start asleep
des.monster({id="gargoyle", x=14, y=01, peaceful=0})
des.monster({id="gargoyle", x=14, y=07, peaceful=0})

des.monster({id="gargoyle", x=20, y=01, peaceful=0})
des.monster({id="gargoyle", x=20, y=07, peaceful=0})

des.monster({id="gargoyle", x=26, y=01, peaceful=0})
des.monster({id="gargoyle", x=26, y=07, peaceful=0})

des.monster({id="winged gargoyle", x=32, y=01, peaceful=0})
des.monster({id="winged gargoyle", x=32, y=07, peaceful=0})

des.monster({id="winged gargoyle", x=38, y=01, peaceful=0})
des.monster({id="winged gargoyle", x=38, y=07, peaceful=0})

-- demons down by the altar...
des.monster({id="bone devil",   x=37, y=02, peaceful=0})
-- Replaced the babau with an ice devil
des.monster({id="ice devil",    x=38, y=02, peaceful=0})
des.monster({id="barbed devil", x=39, y=02, peaceful=0})
des.monster({id="vrock",        x=37, y=06, peaceful=0})
des.monster({id="horned devil", x=38, y=06, peaceful=0})
des.monster({id="hezrou",       x=39, y=06, peaceful=0})

-- a horde of zombies is also inside....
des.monster({class="Z", x=17, y=03, peaceful=0})
des.monster({class="Z", x=18, y=03, peaceful=0})
des.monster({class="Z", x=19, y=03, peaceful=0})
des.monster({class="Z", x=20, y=03, peaceful=0})
des.monster({class="Z", x=21, y=03, peaceful=0})
des.monster({class="Z", x=22, y=03, peaceful=0})
des.monster({class="Z", x=23, y=03, peaceful=0})

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

-- 2 more ghoul mages for good measure...
des.monster({id="ghoul mage", x=34, y=04, peaceful=0})
des.monster({id="ghoul mage", x=35, y=04, peaceful=0})

des.engraving({06,04}, "engrave", "Those Not of Moloch, Begone!")