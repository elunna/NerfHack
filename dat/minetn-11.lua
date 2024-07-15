-- NetHack mines minetn-5.lua	$NHDT-Date: 1652196031 2022/05/10 15:20:31 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.5 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- "Creek Town" by L.
-- No fountains in this town, for obvious reasons.
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.map([[
                ----            ---         |PPP|                 ---       
                |..----         |.-----  ----PPP|                --.--  --- 
     ----  ---- |.....----------|.....-- |..PPP--                |...----.--
 ----|..|  |..|------..................---.PPP--        ---      --...||...|
 |...+..----..|.....|---...................PP.| ---------.-----   |...-|..--
 |...|....|...+.....|..|.-----------+-....P.P.---.............|   --...|..| 
 |...|........|.....|..|.|..|..|.....|....PP......--------+--.--------....| 
 |---|........-------+--.|F+-F+|.....|...PPPP.....|.....|...|..--..| --...--
 |  |....................|.....|-----|..PPPPP.....|.....|...|......----....|
 | --...........-+-----+-|.....| |...|.PPPPPP.....|.....|---|.|...........--
 ---...---+---..|..|..|..|.....| |...|.PPPPP......--+---|...|.|--.......--- 
|--....|.....|..|..|..|..--+-----|...|..PPPPP...........|...|.|...--....|   
|......|.....|..----+-----.......|...|.PPPPPPP..........--+--.|.----.|..--  
|.T....|.....|..................--+---.PPPPPPP-+---+-...........|  ----..|  
|......|.....|...------...............PP..PPPP|..|..|.........------- --.-- 
--..T..--------..+....|.....------...PP..PPPP.|..|..|....----.......|  ---  
 --.........-----|....|.....+..| |..P.P..PPPP.-------...--..--......---     
---.----.....----------.....|..| |.PPP....PPP................|........--    
|...| |.....................|-----PPP.....PPP.----------.----.....--...|    
----- -----------------------  --PPP.---.PPPP.| |      ---  --.|..|-----    
                               |PPP--- ---PPPP| |            ------         
]]);

des.region(selection.area(01,01,75,20),"lit")
des.region({ region={2,4,4,6}, lit=1, type="candle shop", filled=1 })
des.region({ region={15,4,19,6}, lit=1, type="shop", filled=1 })
des.region({ region={34,9,36,12}, lit=1, type="scroll shop", filled=1 })
des.region({ region={51,07,55,09}, lit=1, type="food shop", filled=1 })
-- Temple
des.region({ region={8,11,12,14}, lit=1, type="temple", filled=1 })
des.altar({ x=10,y=13, align=align[0], type="shrine" })
-- Protect the watch-house walls
des.non_diggable(selection.area(25,5,31,11))

des.levregion({ type="stair-up", region={60,12,75,19}, region_islev=1, exclude={0,0,15,20} })
des.levregion({ type="stair-down", region={60,03,75,11}, region_islev=1, exclude={0,0,15,20} })

des.door("closed",05,04)
des.door("closed",14,05)
des.door("closed",10,10)

des.door("locked",17,09)
des.door("locked",20,12)
des.door("locked",21,07)
des.door("locked",23,09)
des.door("locked",17,15)
des.door("locked",27,07)
des.door("locked",30,07)

des.door("open",27,11)
des.door("locked",28,16)
des.door("locked",36,05)
des.door("closed",34,13)
des.door("locked",47,13)
des.door("closed",52,10)
des.door("closed",51,13)
des.door("locked",58,06)
des.door("locked",58,12)

-- Traps
-- Loose floorboard
des.trap("board")

-- Furniture
des.object("chest", 18, 11)
des.object("chest", 20, 10)
des.object("chest", 21, 15)
des.object({ id = "statue", x=8, y=7, montype="gnome king", historic=1 })
des.object("chest", 47, 15)

-- Junk
des.object()
des.object()
des.object()

-- Guards
des.monster({ id = "watch captain", peaceful = 1 })
des.monster({ id = "watchman", x=27,y=9, peaceful = 1 })
des.monster({ id = "watchman", x=8,y=7, peaceful = 1 })
des.monster({ id = "watchman", x=25,y=14, peaceful = 1 })
des.monster({ id = "watchman", x=50,y=15, peaceful = 1 })

-- Watchdog
des.monster({ id = "wolf", x=30,y=08, peaceful = 1 })

-- Citizens
des.monster({ id = "gnome", x=17,y=10, peaceful = 0 })
des.monster({ id = "gnome royal", x=20,y=16, peaceful = 0 })
des.monster({ id = "gnome", x=47,y=14 })
des.monster("gnome")
des.monster("gnome")
des.monster("gnome lord")
des.monster("gnome lord")
des.monster("gnome lord")
des.monster("gnome lord")
des.monster("hobbit")
des.monster("bugbear")
des.monster("bugbear")
des.monster("dwarf")
-- thieves
des.monster("mountain nymph")
des.monster("mountain nymph")

-- River feeders
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("piranha")
des.monster("piranha")
des.monster("piranha")
des.monster("piranha")
des.monster("piranha")