-- NetHack bigroom bigrm-16.lua	$NHDT-Date: 1652196021 2022/05/10 15:20:21 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1990 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Ported from UnNetHack
-- Converted to lua by hackemslashem
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noflip");

des.map([[
---------------------------------------------------------------------------
|.........................................................................|
|.........................................................................|
|...........................................................-----.........|
|...........................................................|   |.........|
|............-----..........................................|   |.........|
|............|   |...........................-----..........-----.........|
|............|   |...........................|   |........................|
|............-----...........................|   |........................|
|............................................-----........................|
|.........................................................................|
|.........................-----...........................................|
|.........................|   |...........................................|
|.........................|   |...........................................|
|.........................-----...........................................|
|.........................................................................|
|.........................................................................|
---------------------------------------------------------------------------
]]);

-- Overgrown forest
des.replace_terrain({ region={00,00, 25,19}, fromterrain=".",
                      toterrain=percent(50) and "T" or "g", chance=15 })
des.replace_terrain({ region={26,00, 50,19}, fromterrain=".",
                      toterrain=percent(50) and "T" or "g", chance=35 })
des.replace_terrain({ region={51,00, 75,19}, fromterrain=".",
                      toterrain=percent(50) and "T" or "g", chance=55 })

des.region(selection.area(01,01, 73, 16), "lit");

des.stair("up");
des.stair("down");

-- Level needs to be diggable because of the trees...

for i = 1,15 do
   des.object();
end

for i = 1,6 do
   des.trap();
end

for i = 1,28 do
  des.monster();
end
