-- NetHack sokoban soko4-2.lua	$NHDT-Date: 1652196036 2022/05/10 15:20:36 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.2 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
--  https://nethackwiki.com/wiki/Sokoban_Level_1f
-- authorship may be Hiroyuki Imabayashi, the original 1982 sokoban developer
-- thinking rabbit republished sokoban in 1988, and added some levels

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "premapped", "solidify");
des.map([[
-----------------
|.......|...--..|
|.-----.|.......|
|.---...|.......|
|...........--..|
|......--...||..|
|FFFFF-------|.-|
|...........|-..|
|.....-------...|
|..L............|
|.....-------...|
|.....|     |...|
-------     -----
]]);

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=20 })

des.levregion({ region = {01,05,01,05}, type = "branch" })
des.stair("up", 11,07)
des.region(selection.area(00,00,16,12),"lit")
des.non_diggable(selection.area(00,00,16,12))
des.non_passwall(selection.area(00,00,16,12))

-- A little help
des.object("earth",14,01)
if percent(50) then
    des.object("earth",15,01)
end

-- Boulders
des.object("boulder",12,02)
des.object("boulder",06,03)
des.object("boulder",12,03)
des.object("boulder",06,04)
des.object("boulder",07,04)
des.object("boulder",14,04)
des.object("boulder",14,07)
des.object("boulder",02,09)
des.object("boulder",12,09)
des.object("boulder",13,09)
des.object("boulder",14,10)

-- Traps
des.trap("pit",06,07)
des.trap("pit",07,07)
des.trap("pit",08,07)
des.trap("pit",09,07)
des.trap("pit",10,07)
des.trap("pit",06,09)
des.trap("pit",07,09)
des.trap("pit",08,09)
des.trap("pit",09,09)
des.trap("pit",10,09)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")