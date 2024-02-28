-- NetHack sokoban soko4-2.lua	$NHDT-Date: 1652196036 2022/05/10 15:20:36 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.2 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- authorship may be Joseph L Traub

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "sokoban", "premapped", "solidify");
des.map([[
       ----------- 
       |.........| 
       |.........| 
------ |...-----.| 
|....-----....--.| 
|................| 
|-.|.......--.--.| 
|-.|---.----|.||.| 
|..------...|.--.--
|...........F.....|
---------...|.....|
        -----------
]]);

des.levregion({ region = {07,07,07,07}, type = "branch" })
des.stair("up", 10,09)
des.region(selection.area(00,00,18,11),"lit")
des.non_diggable(selection.area(00,00,18,11))
des.non_passwall(selection.area(00,00,18,11))

des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })
des.replace_terrain({ region={07,07,07,07}, fromterrain="I", toterrain="." })

-- A little help
des.object("earth",01,08)
if percent(50) then
    des.object("earth",01,09)
end

-- Boulders
des.object("boulder",12,02)
des.object("boulder",14,02)
des.object("boulder",09,03)
des.object("boulder",11,04)
des.object("boulder",16,04)
des.object("boulder",08,05)
des.object("boulder",10,05)
des.object("boulder",14,09)

-- Traps
des.trap("pit",02,06)
des.trap("pit",02,07)
des.trap("pit",04,09)
des.trap("pit",05,09)
des.trap("pit",06,09)
des.trap("pit",07,09)
des.trap("pit",08,09)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- One random mimic
des.monster("m")