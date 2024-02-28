-- NetHack sokoban soko3-2.lua	$NHDT-Date: 1652196036 2022/05/10 15:20:36 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- https://nethackwiki.com/wiki/Sokoban_Level_1j

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
            ---------
------------|.....+.|
|...........|.....|.|
|.---.......|.....|.|
|...|.......|.....|.|
|...|---.---|.....|.|
|...--......|.....|.|
|...........-------.|
---.--...|..........|
  |.--...|--------..|
  |......|       ----
  ---.----           
    ---              
]]);

des.stair("down", 05,11)
des.stair("up", 15,05)
des.region(selection.area(00,00,20,12), "lit")
des.non_diggable(selection.area(00,00,20,12))
des.non_passwall(selection.area(00,00,20,12))

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

des.door("locked",18,01)

-- Boulders
des.object("boulder",06,03)
des.object("boulder",07,03)
des.object("boulder",06,04)
des.object("boulder",09,04)
des.object("boulder",03,05)
des.object("boulder",08,05)
des.object("boulder",02,06)
des.object("boulder",03,07)
des.object("boulder",04,07)
des.object("boulder",06,07)
des.object("boulder",07,08)
des.object("boulder",08,08)

-- Traps
des.trap("hole",19,02)
des.trap("hole",19,03)
des.trap("hole",19,04)
des.trap("hole",19,05)
des.trap("hole",19,06)
des.trap("hole",19,07)
des.trap("hole",12,08)
des.trap("hole",13,08)
des.trap("hole",14,08)
des.trap("hole",15,08)
des.trap("hole",16,08)
des.trap("hole",17,08)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")