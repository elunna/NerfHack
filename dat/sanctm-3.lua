-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
-- Cthulhu's Sanctum
--
-- Cthulhu was the high priest of the old ones, the mediator
-- between them and their arcane gods.  For nethack, it seems
-- reasonable to cast him as the great priest of Moloch, to whom
-- the amulet has been entrusted for safe keeping.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor", "nommap", "noflip")

--        1         2         3         4         5         6         7    7
--23456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                .........         }}...          -----  }}}}}}}}}---------}}
  .......     ...............    ...}}}..        |...|...}}}}}}..|.......|.}
 ....}}...###S................   ...}}.  .       |...+...}}}}}...+.......+.}
  .......     ...........   ...         .        |...|..}}}}}}}..|.......|.}
                .......      ...  ----- .  ----- -----}}}}}}}}}..---------}}
     ........   ++            ..  |...|-S--|...|    |}}}}}}}}}}..}}}}}}}}}}}
    ... .. .......     ...... ..  |...|....|...|    |}}}}}}..............}}}
   ..................      -S-++--|...|....|...|    |}}}}...........--------
 }}... .}}. ... ... ....   |......|-+----+---+------|}}}............|}}....|
 }.....}}}}............... |..}}..+.................|}..............+......|
 }.....}}}}............... |..}}..+.................|}..............+......|
 }}... .}}. ... ... ....   |......|S--+----+--+-----|}}}............|}}....|
   ..................      -S-++---.|...|....|..|   |}}}}...........--------
    ... .. .......     ...... ..   .|...|....|..|   |}}}}}}..............}}}
     ........   ++            ..   .|...|----|..|   |}}}}}}}}}}..}}}}}}}}}}}
                .......      ...   .-----    ---------}}}}}}}}}..---------}}
  .......     ...........   ...    .      ...    |...|..}}}}}}}..|.......|.}
 ....}}...###S................      ...  ..}..   |...+...}}}}}...+.......+.}
  .......     ...............          .. ...    |...|...}}}}}}..|.......|.}
                .........                        -----  }}}}}}}}}---------}}
]]);


-- Random Places for Cthulhu to be with the Amulet
local places = { {04,09},{04,10},{03,02},{03,17},
                 {34,02},{44,17},{16,02},{16,17} }
shuffle(places)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Invisible barrier separating the left & right halves of the level
des.non_passwall(selection.area(48,00,49,19))

-- Regions
--
-- Temple interior
des.region(selection.area(00,00,52,19), "unlit")

-- Outer landing
des.region(selection.area(53,00,75,19), "lit")

-- Outside Chambers
des.region(selection.area(66,01,72,03), "unlit")
des.region(selection.area(69,08,74,11), "unlit")
des.region(selection.area(66,16,72,18), "unlit")

-- Main Temple
des.region({ region={01,05,23,14}, lit=1, type="temple", filled=2 })
des.altar({ x=04, y=09, align="noalign", type="sanctum" })
des.altar({ x=04, y=10, align="noalign", type="sanctum" })

-- Northern Temple (Inner)
des.region({ region={01,01,09,03}, lit=0, type="temple", filled=1 })
des.altar({ x=03,y=02, align="noalign", type="shrine" })

-- Northern Temple (Outer)
des.region({ region={14,00,26,04}, lit=1, type="temple", filled=1 })
des.altar({ x=16,y=02, align="noalign", type="shrine" })

-- Souther Temple (Inner)
des.region({ region={01,16,09,18}, lit=1, type="temple", filled=1 })
des.altar({ x=03,y=17, align="noalign", type="shrine" })

-- Southern Temple (Outer)
des.region({ region={14,15,26,19}, lit=1, type="temple", filled=1 })
des.altar({ x=16,y=17, align="noalign", type="shrine" })

-- North Eastern Temple
des.region({ region={33,00,39,02}, lit=1, type="temple", filled=1 })
des.altar({ x=36,y=01, align="noalign", type="shrine" })

-- South Eastern Tample
des.region({ region={40,16,45,18}, lit=1, type="temple", filled=1 })
des.altar({ x=44,y=17, align="noalign", type="shrine" })

-- Stairs
des.stair("up", 73,09)

-- Drawbridges
des.drawbridge({ dir="west", state="closed", x=53,y=09})
des.drawbridge({ dir="west", state="closed", x=53,y=10})

-- Doors
des.door("closed",68,09)
des.door("closed",68,10)
des.door("closed",53,02)
des.door("closed",53,17)
des.door("closed",36,08)
des.door("closed",41,08)
des.door("closed",45,08)
des.door("closed",38,11)
des.door("closed",43,11)
des.door("closed",46,11)
des.door("locked",65,02)
des.door("locked",73,02)
des.door("locked",65,17)
des.door("locked",73,17)
des.door("locked",35,11)
des.door("locked",40,05)
des.door("locked",34,09)
des.door("locked",34,10)
des.door("locked",16,05)
des.door("locked",17,05)
des.door("locked",16,14)
des.door("locked",17,14)
des.door("locked",30,07)
des.door("locked",31,07)
des.door("locked",30,12)
des.door("locked",31,12)
des.door("locked",13,02)
des.door("locked",13,17)
des.door("locked",28,07)
des.door("locked",28,12)

-- Sea monsters for the river
des.monster({ class = ";", x=59,y=01})
des.monster({ class = ";", x=57,y=04})
des.monster({ class = ";", x=54,y=07})
des.monster({ class = ";", x=54,y=13})
des.monster({ class = ";", x=58,y=15})
des.monster({ class = ";", x=60,y=18})
des.monster({ class = ";", x=70,y=05})
des.monster({ class = ";", x=72,y=14})

-- Platform Guardians
des.monster({ id = "master lich", x=52,y=02,peaceful=0,asleep=1 })

des.object("wand of lightning",52,02)
des.object({ id = "chest", x = 51, y = 02})
des.monster({ id = "nightgaunt", x=56,y=01,peaceful=0,asleep=1 })
des.monster({ id = "master lich", x=52,y=17,peaceful=0,asleep=1 })
des.object("wand of lightning",52,17)
des.object({ id = "chest", x = 51, y = 17})
des.monster({ id = "nightgaunt", x=56,y=18,peaceful=0,asleep=1 })

-- Landing Guards
des.monster({ id = "deepest one", x=56,y=08,peaceful=0,asleep=1 })
des.object({ class = "!", x = 56, y = 08})
des.monster({ id = "deepest one", x=61,y=08,peaceful=0,asleep=1 })
des.object({ class = "/", x = 61, y = 08})
des.monster({ id = "deepest one", x=56,y=11,peaceful=0,asleep=1 })
des.object({ class = "!", x = 56, y = 11})
des.monster({ id = "deepest one", x=61,y=13,peaceful=0,asleep=1 })
des.object({ class = "/", x = 61, y = 13})

-- Northern barracks
des.monster({ id = "deeper one", x=67,y=01,peaceful=0,asleep=1 })
des.object("chest",68,01)
des.monster({ id = "deeper one", x=69,y=01,peaceful=0,asleep=1 })
des.object("chest",70,01)
des.monster({ id = "deeper one", x=71,y=01,peaceful=0,asleep=1 })
des.monster({ id = "deeper one", x=67,y=03,peaceful=0,asleep=1 })
des.object("chest",68,03)
des.monster({ id = "deeper one", x=69,y=03,peaceful=0,asleep=1 })
des.object("chest",70,03)
des.monster({ id = "deeper one", x=71,y=03,peaceful=0,asleep=1 })

-- Southern barracks
des.monster({ id = "deeper one", x=67,y=16,peaceful=0,asleep=1 })
des.object("chest",68,16)
des.monster({ id = "deeper one", x=69,y=16,peaceful=0,asleep=1 })
des.object("chest",70,16)
des.monster({ id = "deeper one", x=71,y=16,peaceful=0,asleep=1 })
des.monster({ id = "deeper one", x=67,y=18,peaceful=0,asleep=1 })
des.object("chest",68,18)
des.monster({ id = "deeper one", x=69,y=18,peaceful=0,asleep=1 })
des.object("chest",70,18)
des.monster({ id = "deeper one", x=71,y=18,peaceful=0,asleep=1 })

-- Traps on the landing
des.trap("board",65,08)
des.trap("board",65,11)
des.trap("board",61,08)
des.trap("board",61,11)
des.trap("board",58,08)
des.trap("board",58,11)
des.trap("board",63,02)
des.trap("board",63,17)
des.trap("board",55,02)
des.trap("board",55,17)

-- Guardians one the inner temples
des.monster({ id = "mind flayer", x=47,y=09,peaceful=0, asleep=1})
des.object("wand of striking",47,09)
des.monster({ id = "mind flayer", x=49,y=10,peaceful=0, asleep=1})
des.object("wand of striking",49,10)

-- Priests, in the chambers before the temple
des.monster({ id = "aligned cleric", x=35,y=06,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=37,y=06,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=39,y=06,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=42,y=06,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=44,y=05,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=46,y=15,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=37,y=13,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=39,y=12,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=41,y=12,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=44,y=13,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=46,y=12,align="noalign",peaceful=0 })
des.monster({ id = "aligned cleric", x=47,y=13,align="noalign",peaceful=0 })

-- Door bell for the inner temple
des.trap("board",35,09)
des.trap("board",35,10)

-- Guardians one the inner temples
des.monster({ id = "marilith", x=33,y=08,peaceful=0,asleep=1 })
des.monster({ id = "marilith", x=33,y=11,peaceful=0,asleep=1 })
des.monster({ id = "marilith", x=28,y=08,peaceful=0,asleep=1 })
des.monster({ id = "marilith", x=28,y=11,peaceful=0,asleep=1 })
des.monster({ id = "kraken", x=29,y=09,peaceful=0,asleep=1 })

-- Main Temple
des.trap("fire",15,06)
des.trap("magic",16,06)
des.trap("fire",17,06)
des.trap("fire",15,13)
des.trap("magic",16,13)
des.trap("fire",17,13)

des.monster({ id = "kraken", x=09,y=10,peaceful=0,asleep=1 })
des.monster({ class = "B", x=05,y=07,peaceful=0,asleep=1})
des.monster({ class = "B", x=05,y=10,peaceful=0,asleep=1})
des.monster({ class = "B", x=08,y=14,peaceful=0,asleep=1})
des.monster({ class = "B", x=10,y=08,peaceful=0,asleep=1})
des.monster({ class = "B", x=13,y=06,peaceful=0,asleep=1})
des.monster({ class = "B", x=14,y=09,peaceful=0,asleep=1})
des.monster({ class = "B", x=15,y=12,peaceful=0,asleep=1})
des.monster({ class = "B", x=18,y=10,peaceful=0,asleep=1})
des.monster({ class = "B", x=21,y=08,peaceful=0,asleep=1})

des.object({ id = "chest", x = 02, y = 09})
des.object({ id = "chest", x = 02, y = 10})

-- Northern Temple (Outer)
des.trap("fire",25,01)
des.trap("fire",25,02)
des.trap("magic",26,01)
des.trap("magic",26,02)
des.trap("fire",27,01)
des.trap("fire",27,02)

des.monster({ id = "aligned cleric", x=20,y=01,align="noalign",peaceful=0,asleep=1 })
des.monster({ id = "aligned cleric", x=19,y=03,align="noalign",peaceful=0,asleep=1 })
des.monster({ id = "wererat", x=19,y=03,peaceful=0,asleep=1 })
des.object({ id = "chest", x = 14, y = 02})

-- Northern Temple (Inner)
des.trap("board",09,02)

des.monster({ id = "kraken", x=05,y=02,peaceful=0,asleep=1 })
des.monster({ id = "shoggoth", x=04,y=02,peaceful=0,asleep=1 })
des.object({ id = "chest", x = 01, y = 02})

-- Southern Temple (Outer)
des.trap("fire",25,17)
des.trap("fire",25,18)
des.trap("magic",26,17)
des.trap("magic",26,18)
des.trap("fire",27,17)
des.trap("fire",27,18)

des.monster({ id = "aligned cleric", x=20,y=16,align="noalign",peaceful=0,asleep=1 })
des.monster({ id = "aligned cleric", x=19,y=18,align="noalign",peaceful=0,asleep=1 })
des.monster({ id = "werewolf", x=17,y=17,peaceful=0,asleep=1 })
des.object({ id = "chest", x = 14, y = 17})

-- Southern Temple (Inner)
des.trap("board",09,17)
des.monster({ id = "kraken", x=05,y=17,peaceful=0,asleep=1 })
--des.monster({ id = "star vampire", x=04,y=17,peaceful=0,asleep=1 })
des.monster({ id = "vampire mage", x=04,y=17,peaceful=0,asleep=1 })

des.object({ id = "chest", x = 01, y = 17})

-- North Eastern Temple
des.trap("board",39,01)
des.monster({ id = "kraken", x=36,y=01,peaceful=0,asleep=1 })
des.monster({ id = "iron golem", x=35,y=02,peaceful=0,asleep=1 })
des.monster({ id = "green slime", x=38,y=02,peaceful=0,asleep=1 })
des.object({ id = "chest", x = 33, y = 01})

-- South Eastern Temple
des.trap("board",37,17)
des.monster({ id = "kraken", x=43,y=17,peaceful=0,asleep=1 })
des.monster({ id = "shoggoth", x=42,y=16,peaceful=0,asleep=1 })
des.monster({ id = "green slime", x=42,y=18,peaceful=0,asleep=1 })
des.object({ id = "chest", x = 45, y = 17})

-- Cthulhu is in one of the temples (he is generated with the amulet)
-- MONSTER:'&',random,places[0],asleep,hostile
-- No Cthulhu in NerfHack - you get an alhoon instead.
des.monster({ id = "alhoon", loc=places[0],peaceful=0,asleep=1 })

-- Northern Shuggoth Run
des.trap("teleport",28,06)
des.monster({ id = "shoggoth", x=27,y=06,peaceful=0,asleep=1 })
des.monster({ id = "shoggoth", x=25,y=06,peaceful=0,asleep=1 })
des.monster({ id = "shoggoth", x=23,y=06,peaceful=0,asleep=1 })

-- Southern Shuggoth Run
des.trap("teleport",28,13)
des.monster({ id = "shoggoth", x=27,y=13,peaceful=0,asleep=1 })
des.monster({ id = "shoggoth", x=25,y=13,peaceful=0,asleep=1 })
des.monster({ id = "shoggoth", x=23,y=13,peaceful=0,asleep=1 })