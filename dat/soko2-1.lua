--
-- "Daedalus Delicatessen"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");

--0         1         2         3         4         5         6         7     
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00       -------              ------- 
01    ---|.....|---           |.....| 
02  ---..|.....|..---        --.....--
03 --....|.....+....--  -----|.......|
04 |.....|.....|.....|  |....F.......|
05------+---------+------....F.......|
06|........................--|.......|
07--.....|......---..----|.| |.......|
08 |.........--..--..|   |.| -------+|
09 --....|...--.....--   |.|       |.|
10  ---..|........---    |.---------.|
11    ---|....-----      |...........|
12       -------         -------------
]]);

des.stair("down",01,06)
des.stair("up",31,04)
des.region(selection.area(00,00,35,12),"lit");
des.non_diggable(selection.area(00,00,35,12));
des.non_passwall(selection.area(00,00,35,12));

-- Ice (avoid the deli)
des.replace_terrain({ region={00,00, 06,12}, fromterrain=".", toterrain="I", chance=15 })
des.replace_terrain({ region={14,00, 36,12}, fromterrain=".", toterrain="I", chance=15 })
des.replace_terrain({ region={07,06, 13,12}, fromterrain=".", toterrain="I", chance=15 })

-- Doors
des.door("closed", 13,03)
des.door("random", 06,05)
des.door("locked", 16,05)
des.door("locked", 34,08)

-- Boulders
des.object("boulder", 05,06)
des.object("boulder", 09,06)
des.object("boulder", 13,06)
des.object("boulder", 06,07)
des.object("boulder", 10,07)
des.object("boulder", 11,07)
des.object("boulder", 07,08)
des.object("boulder", 04,09)
des.object("boulder", 08,09)
des.object("boulder", 09,10)
des.object("boulder", 13,10)

-- Traps
-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 19,06, 24,06 } });
des.trap("hole", 19,06)
des.trap("hole", 20,06)
des.trap("hole", 21,06)
des.trap("hole", 22,06)
des.trap("hole", 23,06)
des.trap("hole", 24,06)
des.exclusion({ type = "monster-generation", region = { 24,07, 24,10 } });
des.trap("hole", 24,07)
des.trap("hole", 24,08)
des.trap("hole", 24,09)
des.trap("hole", 24,10)

-- No free food here, but you can buy some from the deli.
des.object({ class = "=" });
des.object({ class = "/" });

-- The delicatessen:
des.region({ region={08,01,12,04}, lit=1, type="food shop", filled=1 })

-- Two random mimics!
des.monster("m")
des.monster("m")