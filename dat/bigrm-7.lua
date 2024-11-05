-- NetHack bigroom bigrm-7.lua	$NHDT-Date: 1652196023 2022/05/10 15:20:23 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.0 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1990 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel");

des.map([[
                                                        -----              
                                                ---------...---            
                                        ---------.........L...---          
                                ---------.......................---        
                        ---------.................................---      
                ---------...........................................---    
        ---------.....................................................---  
|--------...............................................................--|
|.........................................................................|
|.L.....................................................................L.|
|.........................................................................|
|--...............................................................--------|
  ---.....................................................---------        
    ---...........................................---------                
      ---.................................---------                        
        ---.......................---------                                
          ---...L.........---------                                        
            ---...---------                                                
              -----                                                        
]]);

local terrain = { "L", "T", "{", "." };
local tidx = math.random(1, #terrain);
des.replace_terrain({ region={00,00, 74,18}, fromterrain="L", toterrain=terrain[tidx] });

-- Some grass
local sel = selection.match("."):percentage(2):grow();
des.replace_terrain({ selection=sel, fromterrain=".", toterrain="g" });

des.region(selection.area(01,01,73,17), "lit");

des.stair("up");
des.stair("down");

des.non_diggable();

for i = 1,15 do
   des.object();
end

for i = 1,6 do
   des.trap();
end

for i = 1,28 do
  des.monster();
end
