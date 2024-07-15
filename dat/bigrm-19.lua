-- NetHack bigroom bigrm-19.lua	$NHDT-Date: 1652196021 2022/05/10 15:20:21 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1990 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Ported from UnNetHack
-- Converted to LUA by hackemslashem
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noflip");

des.map([[
-----------                                                     -----------
|IIIIIIIII|                                                     |IIIIIIIII|
|II......I|-----------|                             |-----------|I......II|
|-|I......IIIIIIIIIIII|----------|       |----------|IIIIIIIIIIII......I|-|
  -|I.................IIIIIIIIIII|-------|IIIIIIIIIII.................I|-  
   -|I...........................IIIIIIIII...........................I|-   
    -|I.............................................................I|-    
     -|I...........................................................I|-     
      -|I.........................................................I|-      
      -|I.........................................................I|-      
     -|I...........................................................I|-     
    -|I.............................................................I|-    
   -|I...........................IIIIIIIII...........................I|-   
  -|I.................IIIIIIIIIII|-------|IIIIIIIIIII.................I|-  
|-|I......IIIIIIIIIIII|----------|       |----------|IIIIIIIIIIII......I|-|
|II......I|-----------|                             |-----------|.......II|
|IIIIIIIII|                                                     |IIIIIIIII|
-----------                                                     -----------
]]);

des.region({ region={1,01,73,16}, lit=0, type="morgue", filled=0 })

des.stair("up");
des.stair("down");

des.non_diggable();

des.feature("fountain", 05,02);
des.feature("fountain", 05,15);
des.feature("fountain", 69,02);
des.feature("fountain", 69,15);

for i = 1,15 do
   des.object();
end

for i = 1,6 do
   des.trap();
end

for i = 1,18 do
  des.monster();
end

for i = 1,18 do
   des.monster("Z");
 end
