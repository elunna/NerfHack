-- NetHack mines minend-5.lua	$NHDT-Date: 1652196029 2022/05/10 15:20:29 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Mine end level variant 5
-- "Orc Temple" by Khor
-- Ported to 3.7 LUA (from EvilHack) by hackemslashem
-- In this variant of the mines' end a group of orcs have found a randomly
-- generated figurine of a demon and worship it. Slightly modified from
-- the original.

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.map([[
                                                                   |-----|  
                                             -------        ----- |-LLLLL-| 
                         ---------------     |.....|        |...||-LL...LL-|
                        -|..|..........|     |.....|        |...||LL.....LL|
                       -|...F..........|     |.....|        |...||L.......L|
         |-------|    -|....|-+------+-|    ----+----       |LLL||L.......L|
        |-.......-|  -|.....F..........|----|.......|---------S---L.......L|
 -------|.........|--|.....--...............F.......F.....||.....|LL.....LL|
-|........................-|..............................--.....|-LL...LL-|
|............{............+...............................+......||-LL.LL-| 
-|........................-|..............................--.....| |--S--|  
 -------|.........|--|.....--...............F.......F.....||.....|    .     
        |-.......-|  -|.....F..........|----|.......|---------S---          
         |-------|    -|....|-+------+-|    ----+----         .             
                       -|...F..........|     |.....|                        
                        -|..|..........|     |.....|                        
                         ---------------     |.....|                        
                                             -------                     ...
                                                                         ...
                                                                        ...{
]]);

local stones = { {0,18},{0,12},{2,18},{12,14},{22,14},
                 {16,16},{72,18},{52,14},{44,14} }

shuffle(stones)

des.region({ region={0,0,75,19}, lit=1, type="ordinary", irregular=1 })
des.non_diggable(selection.area(00,00,75,19))
des.stair("up", 1,9)

-- SOME ORCS (The religious kind)
-- Hostile to anyone, regardless of race, who disturbs their sacred temple
des.monster("goblin")
des.monster("orc captain")
des.monster("goblin")
des.monster("orc captain")
des.monster("hill orc")
des.monster("hill orc")
des.monster("hill orc")
des.monster("hill orc")
des.monster("hill orc")
des.monster("hill orc")
des.monster("hill orc")
des.monster("hill orc")

des.monster("Mordor orc")
des.monster("Mordor orc")
des.monster("Mordor orc")
des.monster("Mordor orc")
des.monster("Mordor orc")
des.monster("Mordor orc")
des.monster("Mordor orc")
des.monster("Mordor orc")

des.monster("o")
des.monster("o")
des.monster("o")
des.monster("o")
des.monster("o")
des.monster("o")
des.monster("o")
des.monster("o")
des.monster("o")
des.monster("o")

-- SECRET CAVE
des.mazewalk({ x=62, y=15, dir="south", stocked=false })

des.altar({ x=70, y=05, align="noalign",type="shrine" })
des.door("closed",62,12)
des.door("closed",70,10)
des.object({ id="scroll of scare monster", x=70,y=05, buc="cursed" })
des.engraving({ x=70, y=05, type = "burn", text = "Moloch" });
des.object({ id="figurine", buc="cursed", montype="balrog", x=70,y=05 })

-- random placement of gems/stones
-- one location will always be empty
des.object({ id="luckstone", coord=stones[0], buc="not-cursed", achievement=1 })
des.object("flint", stones[1])
des.object("*", stones[2])
des.object("*", stones[3])
des.object("*", stones[4])
des.object("*", stones[5])
des.object("*", stones[6])
des.object("*", stones[7])

-- shamans guarding the inner temple/figurine
des.monster({ id = "orc shaman", x=69, y=3, peaceful=0 })
des.monster({ id = "orc shaman", x=71, y=3, peaceful=0 })
des.monster({ id = "orc shaman", x=68, y=4, peaceful=0 })
des.monster({ id = "orc shaman", x=72, y=4, peaceful=0 })
des.monster({ id = "orc shaman", x=68, y=6, peaceful=0 })
des.monster({ id = "orc shaman", x=72, y=6, peaceful=0 })
des.monster({ id = "orc shaman", x=69, y=7, peaceful=0 })
des.monster({ id = "orc shaman", x=71, y=7, peaceful=0 })

-- TEMPLE
des.engraving({ x=55, y=09, type = "burn", text = "Blessed are the destroyers of false hope, for they are the true Messiahs." });
des.monster({ id = "orc shaman", x=55, y=9, peaceful=0 })
des.engraving({ x=48, y=03, type = "burn", text = "Why should you not hate your enemies. If you love them does that not place you at their mercy?" });
des.monster({ id = "orc shaman", x=48, y=3, peaceful=0 })
des.engraving({ x=48, y=15, type = "burn", text = "Cursed are the god-adorers, for they shall be shorn sheep!" });
des.monster({ id = "orc shaman", x=48, y=15, peaceful=0 })
des.engraving({ x=25, y=09, type = "burn", text = "Dagul protects our doors. Dagul protects our souls." });
des.monster({ id = "orc shaman", x=25, y=09, peaceful=0 })

des.object({ id = "statue", x=56, y=8, montype="orc shaman", historic=1 })
des.object({ id = "statue", x=56, y=10, montype="orc-captain", historic=1 })
des.object({ id = "statue", x=50, y=3, montype="hill orc", historic=1 })
des.object({ id = "statue", x=46, y=3, montype="hill orc", historic=1 })
des.object({ id = "statue", x=50, y=15, montype="Mordor orc", historic=1 })
des.object({ id = "statue", x=46, y=15, montype="Mordor orc", historic=1 })
des.object({ id = "statue", x=29, y=03, montype="Mordor orc", historic=1 })
des.object({ id = "statue", x=32, y=03, montype="hill orc", historic=1 })
des.object({ id = "statue", x=35, y=03, montype="orc-captain", historic=1 })
des.object({ id = "statue", x=38, y=03, montype="orc shaman", historic=1 })
des.object({ id = "statue", x=29, y=15, montype="Mordor orc", historic=1 })
des.object({ id = "statue", x=32, y=15, montype="hill orc", historic=1 })
des.object({ id = "statue", x=35, y=15, montype="orc-captain", historic=1 })
des.object({ id = "statue", x=38, y=15, montype="orc shaman", historic=1 })

des.object("chest", 61, 2)
des.object("chest", 63, 2)

-- des.altar({ x=48, y=02, align="noalign",type="shrine" })
-- des.altar({ x=48, y=16, align="noalign",type="shrine" })
-- des.altar({ x=56, y=09, align="noalign",type="shrine" })

des.object({ id = "statue", x=48, y=02, montype="horned devil", historic=1 })
des.object({ id = "statue", x=48, y=16, montype="pit fiend", historic=1 })
des.object({ id = "statue", x=56, y=56, montype="vrock", historic=1 })

-- A hidden elven temple from the days of old before this
-- site had been overrun by orcs. Chance that some elves
-- are barracaded inside.
-- des.altar({ x=62, y=02, align="noncoaligned",type="shrine" })
des.object({ id = "statue", x=56, y=56, montype="Elvenking", historic=1 })
des.engraving({ x=62, y=02, type = "burn", text = "Elbereth" });

des.monster({ id = "elven cleric", x=61, y=03 })
des.monster({ id = "green-elf", x=63, y=03 })

des.feature("forge", 48,09)

des.door("closed",58,09)
des.door("closed",26,09)
des.door("closed",30,05)
des.door("closed",37,05)
des.door("closed",48,05)

des.door("locked",62,06)
des.door("closed",30,13)
des.door("closed",37,13)
des.door("closed",48,13)

-- Wake the shamans if anyone tries to take the figurine:
des.trap("board", 69,04)
des.trap("board", 69,05)
des.trap("board", 69,06)
des.trap("board", 70,04)
des.trap("board", 70,06)
des.trap("board", 71,04)
des.trap("board", 71,05)
des.trap("board", 71,06)

-- Random traps (a little different from EvilHack)
des.trap("spear")
des.trap("spear")

-- Orcs love their grease...
des.trap("grease")
des.trap("grease")
des.trap("grease")
des.trap("grease")
des.trap("grease")