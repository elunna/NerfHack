-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
-- NetHack may be freely redistributed.  See license for details.
--
-- MAZE: "pvalley",' '

--       Pleaseant Valley.
--
--       Green hills, trees, sheep, nymphs and people.
--       Oh, and some of Vlad's minions.
--
des.level_init({ style = "solidfill", fg = " " });
des.message("You smell fresh air.")
des.level_flags("mazelevel", "noteleport", "hardfloor", "nommap", "temperate", "noflip");

--0         1         2         3         4         5         6         7     
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00                                       -----------------                    
01  ....            .,.T,.T,             |...|...|...|...|              ....  
02 ......    T,.,.T,,T,,..,,T,     ,T,...--.---.---.---.--.           ##..{.. 
03  ...    ..,.,T,,...,.T...,.,T,,..,....,.........,.......,T,      ###  ...  
04  #      ,  T.,.,.,,.,,....,.,,.,...,.,T,.......,T,.,.....,....   #         
05  ##    ,T,,.,.,.,.,.,.,.,,.,.,,...,.,.,..,......,.,.,...,....... ..        
06   #   ..,,.,.,.,.,.,,.T,....,.,....,....,.,.....,..,...,T,....,.....       
07 ....##.  .,.,.,.,.,,T,,,T,,T,,,,.....,...,..,..,.,......,....,T,....,.|---|
08 ....  .. .,.   .,,}}}}}}}}}}}}}},,,,,T,....,.,..,....,........,....,T.....|
09      ..,,,.  }}}}}}}}}}}}}}}}}}}}}}},,,.....,.......,.,........,....,.|---|
10}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}},,,......,....,..,.....,.,.........|
11}}}}}}}}}}}}}}}}}}},,,,,,,,,,}}}}}}}}}}}}}},},,.,T,.....,.,.....,...,..|---|
12}}}}}}}}}}}}}}},,,,..,,.,,,,.,,,}}}}}}}}}}w}w}w}w},,.....,.......,.,T,.....|
13  ---------------.,.,,.,,,,,.,.,,,,,,}}}}w}w}w}w}}w},,.....,....,T,.,..|---|
14  |.......|.....|,,.,.,..,.,,.,.,,...,,,,}w}w}}}}w}w}w},..,T,....,.........|
15  |.......+.....+.........................,}w}w}w}w}w}},.,.,..,........|---|
16  |.......|.....|----..,,,,,,.,,,.,,,,,..,.,}w}w}w}w}.,T,....,T,...,.......|
17  |.......------|...|.....,,.,,,...,.,,,,.,,.}}}}}}}}  ,......,...,T,..|---|
18  |...\...S.....S...|.         .,,,,.,,,..   .}}}}}}     ..........,.       
19  -------------------                          }}}}                         
]]);


-- Stairs and Branch
des.stair("down", 13,18)
des.stair("up", 03,02)
des.levregion({ type="branch", region={03,02,03,02} })

-- Branch location
--des.levregion({ type="branch", region={01,01,06,03} })
des.teleport_region({ region = {01,01,06,03}, dir="down" })

-- Randomize some monsters
local monster = { "V", "S", "E", "H", "M", "O", "R", "T", "&", "Z" }
shuffle(monster)

-- Regions
-- Entry Caves
des.region(selection.area(01,01,06,03),"unlit")
des.region(selection.area(01,07,04,08),"unlit")

-- The wild wood
des.region(selection.area(07,01,31,09),"lit")

-- North Eastern Fields
des.region(selection.area(32,02,70,18),"lit")

-- Fountain
des.region(selection.area(66,01,74,05),"unlit")

-- South Western Fields
des.region(selection.area(01,10,32,18),"lit")

-- Northern huts
des.region(selection.area(40,01,42,01),"unlit")
des.region(selection.area(44,01,46,01),"unlit")
des.region(selection.area(48,01,50,01),"unlit")
des.region(selection.area(52,01,54,01),"unlit")

-- Eastern Huts
des.region(selection.area(72,08,74,08),"unlit")
des.region(selection.area(72,10,74,10),"unlit")
des.region(selection.area(72,12,74,12),"unlit")
des.region(selection.area(72,14,74,14),"unlit")
des.region(selection.area(72,16,74,16),"unlit")

-- Tower
des.region(selection.area(11,14,15,16),"unlit")
des.region(selection.area(03,14,09,17),"unlit")
des.region(selection.area(11,18,15,18),"unlit")
des.region(selection.area(17,17,19,18),"unlit")

-- Doors
des.door("locked",16,15)
des.door("locked",10,15)
des.door("locked",10,18)
des.door("locked",16,18)

-- Sea monsters for the river
des.monster(";",03,11)
des.monster(";",11,11)
des.monster(";",21,09)
des.monster(";",30,10)
des.monster(";",36,11)
des.monster(";",42,13)
des.monster(";",47,14)
des.monster(";",49,17)

-- An assortment of nymphs
des.monster("n",37,04)
des.monster("n",42,07)
des.monster("n",41,09)
des.monster("n",47,13)
des.monster("n",51,16)
des.monster("n",31,06)
des.monster("n",54,13)
des.monster("n",31,07)
des.monster("n",25,03)
des.monster("n",20,02)
des.monster("n",18,06)
des.monster("n",13,04)

-- A few people
des.monster({ id = "healer", x=41,y=01, peaceful = 1 })
des.monster({ id = "rogue", x=46,y=01, peaceful = 1 })
des.monster({ id = "barbarian", x=49,y=01, peaceful = 1 })
des.monster({ id = "ranger", x=53,y=01, peaceful = 1 })
des.monster({ id = "wizard", x=73,y=08, peaceful = 1 })
des.monster({ id = "samurai", x=73,y=10, peaceful = 1 })
des.monster({ id = "knight", x=73,y=14, peaceful = 1 })
des.monster({ id = "valkyrie", x=73,y=16, peaceful = 1 })

-- A few sheep and and a couple of goats
des.monster({ id = "rothe", x=47,y=05, peaceful = 1 })
des.monster({ id = "little dog", x=48,y=06, peaceful = 1 })
des.monster({ id = "rothe", x=48,y=04, peaceful = 1 })
des.monster({ id = "rothe", x=55,y=06, peaceful = 1 })
des.monster({ id = "kitten", x=54,y=05, peaceful = 1 })
des.monster({ id = "rothe", x=57,y=04, peaceful = 1 })
des.monster({ id = "rothe", x=58,y=05, peaceful = 1 })
des.monster({ id = "rothe", x=56,y=06, peaceful = 1 })
des.monster({ id = "little dog", x=58,y=08, peaceful = 1 })
des.monster({ id = "horse", x=60,y=17, peaceful = 1 })
des.monster({ id = "horse", x=64,y=16, peaceful = 1 })
des.monster({ id = "rothe", x=63,y=12, peaceful = 1 })
des.monster({ id = "rothe", x=65,y=11, peaceful = 1 })
des.monster({ id = "rothe", x=64,y=09, peaceful = 1 })

-- Watch Dogs
des.monster({ id = "winter wolf", x=12,y=14, peaceful = 0, asleep = 1 })
des.monster({ id = "winter wolf", x=14,y=15, peaceful = 0, asleep = 1 })
des.monster({ id = "winter wolf", x=12,y=16, peaceful = 0, asleep = 1 })
des.monster({ id = "werewolf", x=11,y=15, peaceful = 0, asleep = 1 })

-- Monsters in the Throne Room
des.monster({ class = monster[0], x = 03, y = 14, peaceful = 0, asleep = 1 })
des.monster({ class = monster[1], x = 03, y = 15, peaceful = 0, asleep = 1 })
des.monster({ class = monster[2], x = 03, y = 16, peaceful = 0, asleep = 1 })
des.monster({ class = monster[3], x = 03, y = 17, peaceful = 0, asleep = 1 })
des.monster({ class = monster[4], x = 04, y = 14, peaceful = 0, asleep = 1 })
des.monster({ class = monster[5], x = 04, y = 15, peaceful = 0, asleep = 1 })
des.monster({ class = monster[6], x = 04, y = 16, peaceful = 0, asleep = 1 })
des.monster({ class = monster[7], x = 04, y = 17, peaceful = 0, asleep = 1 })
des.monster({ class = monster[8], x = 05, y = 14, peaceful = 0, asleep = 1 })
des.monster({ class = monster[9], x = 05, y = 15, peaceful = 0, asleep = 1 })
des.monster({ class = monster[0], x = 05, y = 16, peaceful = 0, asleep = 1 })
des.monster({ class = monster[1], x = 05, y = 17, peaceful = 0, asleep = 1 })
des.monster({ class = monster[2], x = 06, y = 14, peaceful = 0, asleep = 1 })
des.monster({ class = monster[3], x = 06, y = 15, peaceful = 0, asleep = 1 })
des.monster({ class = monster[4], x = 06, y = 16, peaceful = 0, asleep = 1 })
des.monster({ class = monster[5], x = 06, y = 17, peaceful = 0, asleep = 1 })
des.monster({ class = monster[6], x = 07, y = 14, peaceful = 0, asleep = 1 })
des.monster({ class = monster[7], x = 07, y = 15, peaceful = 0, asleep = 1 })
des.monster({ class = monster[8], x = 07, y = 16, peaceful = 0, asleep = 1 })
des.monster({ class = monster[9], x = 07, y = 17, peaceful = 0, asleep = 1 })
des.monster({ class = monster[0], x = 08, y = 14, peaceful = 0, asleep = 1 })
des.monster({ class = monster[1], x = 08, y = 15, peaceful = 0, asleep = 1 })
des.monster({ class = monster[2], x = 08, y = 16, peaceful = 0, asleep = 1 })
des.monster({ class = monster[3], x = 08, y = 17, peaceful = 0, asleep = 1 })
des.monster({ class = monster[4], x = 09, y = 14, peaceful = 0, asleep = 1 })
des.monster({ class = monster[5], x = 09, y = 15, peaceful = 0, asleep = 1 })
des.monster({ class = monster[6], x = 09, y = 16, peaceful = 0, asleep = 1 })
des.monster({ class = monster[7], x = 09, y = 17, peaceful = 0, asleep = 1 })

-- Custodians
des.monster({ id = "master lich", x=06,y=18, peaceful = 0, asleep = 1 })
--OBJECT:'?',"demonology",(06,18)
des.object("scroll of create monster",06,18)
des.object("ring of free action",06,18)

des.monster({ id = "vampire lord", x=04,y=18, peaceful = 0, asleep = 1 })
des.object("!",04,18)

des.monster({ id = "vampire lord", x=08,y=18, peaceful = 0, asleep = 1 })
des.object("!",08,18)

des.monster({ id = "iron golem", x=14,y=18, peaceful = 0, asleep = 1 })
des.monster({ id = "iron golem", x=19,y=18, peaceful = 0, asleep = 1 })

-- Musicians (should only be present on Sundays)

des.monster("monkey",15,02)
des.object("wooden harp",15,02)

des.monster("monkey",25,03)
des.object("bugle",25,03)

des.monster("monkey",19,06)
des.object("leather drum",19,06)

des.monster("monkey",29,04)
des.object("tooled horn",29,04)

-- Loot
des.object("chest", 15, 18)
des.object("%")
des.object("%")
des.object("%")
des.object("%")
des.object("%")
des.object()
des.object()
des.object()
des.object()
des.object()

-- Traps outside the door
des.trap("spiked pit", 17,14)
des.trap("spiked pit", 18,14)
des.trap("spiked pit", 20,15)
des.trap("magic", 21,14)
des.trap("magic", 29,16)
des.trap("magic", 19,12)
des.trap("magic", 25,13)
des.trap("magic", 33,15)
des.trap("magic", 39,16)
des.trap("magic", 27,17)
des.trap("anti magic", 15,15)
des.trap("pit", 26,03)
des.trap("pit", 21,06)
des.trap("pit", 30,05)
des.trap("board", 19,03)