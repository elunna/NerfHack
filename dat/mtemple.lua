-- Lost Tomb
-- Copyright (c) 1989 by Jean-Christophe Collet
-- Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed. See license for details.

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

-- Ported from SLASH'EM by hackemslashem.
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

des.region({ region={08,01,41,07}, lit=1, type="temple", filled=2 })

des.region({ region={00,00,55,08}, lit=0, type="ordinary" })

-- the altar of Moloch (making four will make four priests....)
des.altar({ x=40, y=04, align="noalign",type="shrine" })
des.altar({ x=40, y=04, align="noalign",type="shrine" })
des.altar({ x=40, y=04, align="noalign",type="shrine" })
des.altar({ x=40, y=04, align="noalign",type="shrine" })

des.levregion({ region = {05,04,05,04}, type = "branch" })
des.stair("up", 05, 04)
des.door("locked", 7, 04)

-- flanking the doorway....
des.trap("spiked pit",06,03)
des.trap("spiked pit",06,05)

-- the treasure chamber!
des.object("chest", 52, 03)
des.object("wax candle", 52, 03)
des.gold({x = 52, y = 03})
des.gold({x = 52, y = 03})
des.object({x = 52, y = 03})
des.object({x = 52, y = 03})
des.object({x = 52, y = 03})

des.object("chest", 53, 03)
des.object("wax candle", 53, 03)
des.gold({x = 53, y = 03})
des.gold({x = 53, y = 03})
des.object({x = 53, y = 03})
des.object({x = 53, y = 03})
des.object({x = 53, y = 03})

des.object("chest", 54, 03)
des.object("wax candle", 54, 03)
des.gold({x = 54, y = 03})
des.gold({x = 54, y = 03})
des.object({x = 54, y = 03})
des.object({x = 54, y = 03})
des.object({x = 54, y = 03})

des.object("chest", 52, 04)
des.object("wax candle", 52, 04)
des.gold({x = 52, y = 04})
des.gold({x = 52, y = 04})
des.object({x = 52, y = 04})
des.object({x = 52, y = 04})
des.object({x = 52, y = 04})

des.object("chest", 53, 04)
des.object("wax candle", 53, 04)
des.gold({x = 53, y = 04})
des.gold({x = 53, y = 04})
des.object({x = 53, y = 04})
des.object({x = 53, y = 04})
des.object({x = 53, y = 04})

des.object("chest", 54, 04)
des.object("wax candle", 54, 04)
des.gold({x = 54, y = 04})
des.gold({x = 54, y = 04})
des.object({x = 54, y = 04})
des.object({x = 54, y = 04})
des.object({x = 54, y = 04})

des.object("chest", 52, 05)
des.object("wax candle", 52, 05)
des.gold({x = 52, y = 05})
des.gold({x = 52, y = 05})
des.object({x = 52, y = 05})
des.object({x = 52, y = 05})
des.object({x = 52, y = 05})

des.object("chest", 53, 05)
des.object("wax candle", 53, 05)
des.gold({x = 53, y = 05})
des.gold({x = 53, y = 05})
des.object({x = 53, y = 05})
des.object({x = 53, y = 05})
des.object({x = 53, y = 05})

des.object("chest", 54, 05)
des.object("wax candle", 54, 05)
des.gold({x = 54, y = 05})
des.gold({x = 54, y = 05})
des.object({x = 54, y = 05})
des.object({x = 54, y = 05})
des.object({x = 54, y = 05})

--  five gargoyles on either side, in the niches of the temple
-- all should start asleep
des.monster({id="gargoyle", x=15, y=01, peaceful=0})
des.monster({id="gargoyle", x=21, y=01, peaceful=0})
des.monster({id="gargoyle", x=27, y=01, peaceful=0})
des.monster({id="gargoyle", x=33, y=01, peaceful=0})
des.monster({id="gargoyle", x=39, y=01, peaceful=0})
des.monster({id="gargoyle", x=15, y=08, peaceful=0})
des.monster({id="gargoyle", x=21, y=08, peaceful=0})
des.monster({id="gargoyle", x=27, y=08, peaceful=0})
des.monster({id="gargoyle", x=33, y=08, peaceful=0})
des.monster({id="gargoyle", x=39, y=08, peaceful=0})

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