-- NetHack bigroom bigrm-3.lua	$NHDT-Date: 1652196021 2022/05/10 15:20:21 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1990 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noflip");

des.map([[
---------------------------------------------------------------------------
|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|
|.........................................................................|
|.........................................................................|
|.........................................................................|
|..............---.......................................---..............|
|...............|.........................................|...............|
|.....|.|.|.|.|---|.|.|.|.|...................|.|.|.|.|.|---|.|.|.|.|.....|
|.....|--------   --------|...................|----------   --------|.....|
|.....|.|.|.|.|---|.|.|.|.|...................|.|.|.|.|.|---|.|.|.|.|.....|
|...............|.........................................|...............|
|..............---.......................................---..............|
|.........................................................................|
|.........................................................................|
|.........................................................................|
|.........................................................................|
|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|
---------------------------------------------------------------------------
]]);

-- Dungeon Description
des.region(selection.area(01,01,73,16), "lit");

-- replace some walls
if percent(66) then
   local sel = selection.match("[.w.]");
   local terrains = { "F", "T", "W", "Z", "u" };
   local choice = terrains[math.random(1, #terrains)];
   des.terrain(sel, choice);
end

-- Stairs
des.stair("up");
des.stair("down");

-- Non diggable walls
des.non_diggable();

for i = 1,15 do
   des.object();
end

for i = 1,6 do
   des.trap();
end

des.monster({ x = 01, y = 01 });
des.monster({ x = 13, y = 01 });
des.monster({ x = 25, y = 01 });
des.monster({ x = 37, y = 01 });
des.monster({ x = 49, y = 01 });
des.monster({ x = 61, y = 01 });
des.monster({ x = 73, y = 01 });
des.monster({ x = 07, y = 07 });
des.monster({ x = 13, y = 07 });
des.monster({ x = 25, y = 07 });
des.monster({ x = 37, y = 07 });
des.monster({ x = 49, y = 07 });
des.monster({ x = 61, y = 07 });
des.monster({ x = 67, y = 07 });
des.monster({ x = 07, y = 09 });
des.monster({ x = 13, y = 09 });
des.monster({ x = 25, y = 09 });
des.monster({ x = 37, y = 09 });
des.monster({ x = 49, y = 09 });
des.monster({ x = 61, y = 09 });
des.monster({ x = 67, y = 09 });
des.monster({ x = 01, y = 16 });
des.monster({ x = 13, y = 16 });
des.monster({ x = 25, y = 16 });
des.monster({ x = 37, y = 16 });
des.monster({ x = 49, y = 16 });
des.monster({ x = 61, y = 16 });
des.monster({ x = 73, y = 16 });
