-- NetHack mines minend-1.lua	$NHDT-Date: 1652196029 2022/05/10 15:20:29 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Mine end level variant 7
-- "Boulder Bonanza"
-- Ported from SlashTHEM by hackemslashem

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.map([[
                        ---------  ----                        
                ---------.......-.--..--   ---                 
                -..........----S---....-- --.--       ---      
    ----------  --.....-----  -.........---...-       -.---    
  ---........--  -...---     --....-...--.....----   --...---  
 --...........-- -...-     ---....--.............--  -......-- 
--.....---.....---...-     -.....--...............- --....---  
-......--..........---     --..........----.....--- -.....-    
-..................-      --...........-  -....--   -.....--   
--.............-----      -............-- --....-  --......-   
 --..........---     ------....----.....- .--...----.......-   
  --........--      --.........-  ---...----..............--   
   ---...----       -...-......-    -.....................-    
     -----          -..---....--    --.......---..........-    
                    -...--...--      -....---- --.......---    
                    --......--     ---...--     --.....--      
                     --------      -.....-       -------       
                                   --...--                     
                                    -----                      
]]);

-- Dungeon Description
local places = { {01,07}, {03,06}, {04,05}, {06,04}, {07,09},
                 {10,09}, {12,05}, {13,08}, {14,07}, {16,08} }
shuffle(places)

des.non_diggable(selection.area(00,00,62,18))
des.stair("up", 56,04)
des.door("locked",31,02)

des.trap("rolling boulder")
des.trap("rolling boulder")
des.trap("rolling boulder")
des.trap()
des.trap()
des.trap()
des.trap("falling rock")
des.trap("falling rock")
des.trap("falling rock")
des.trap("falling rock")
des.trap("board", 17,07)

-- Mindless critters
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")

-- Guard for the marker
des.monster({ class = "Z", x=42, y=10 })

des.monster({ class = "'", coord=places[0] })
des.monster({ class = "'", coord=places[1] })
des.monster({ class = "'", coord=places[2] })
des.monster({ class = "'", coord=places[3] })
des.monster({ class = "'", coord=places[4] })
des.monster({ class = "'", coord=places[5] })
des.monster({ id = "stone golem", coord=places[6] })
des.monster({ class = "'", coord=places[7] })
des.monster({ class = "'", coord=places[8] })
des.monster({ class = "'", coord=places[9] })

-- Many, many boulders and rocks
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")
des.object("boulder")

des.object("rock",02,09)
des.object("rock",04,11)
des.object("rock",06,08)
des.object("rock",09,07)
des.object("rock",11,11)
des.object("rock",13,06)
des.object("rock",15,08)
des.object("rock",09,10)
des.object("rock",07,04)
des.object("rock",10,04)

des.object("flint",01,08)
des.object("flint",03,05)
des.object("flint",07,12)
des.object("flint",08,11)
des.object("flint",12,09)
des.object("flint",16,07)
des.object("flint",12,10)

des.object({ id="flint", coord=places[0] })
des.object({ id="flint", coord=places[2] })
des.object({ id="flint", coord=places[3] })
des.object({ id="flint", coord=places[6] })
des.object({ id="flint", coord=places[9] })

des.object("loadstone",05,10)
des.object("loadstone",10,10)
des.object("loadstone",14,09)
des.object("loadstone",04,10)
des.object("loadstone",08,05)
des.object({ id="loadstone", coord=places[1] })
des.object({ id="loadstone", coord=places[4] })
des.object({ id="loadstone", coord=places[5] })
des.object({ id="loadstone", coord=places[7] })
des.object({ id="loadstone", coord=places[8] })

des.object({ id="luckstone", coord=places[6], buc="blessed", achievement=1 })

des.object({ id="diamond", coord=places[0] })
des.object({ id="diamond", coord=places[2] })
des.object({ id="emerald", coord=places[4] })
des.object({ id="emerald", coord=places[6] })
des.object({ id="emerald", coord=places[8] })
des.object({ id="ruby", coord=places[0] })
des.object({ id="ruby", coord=places[2] })
des.object({ id="amethyst", coord=places[3] })
des.object({ id="amethyst", coord=places[5] })

des.object({ class="*", coord=places[1] })
des.object({ class="*", coord=places[3] })
des.object({ class="*", coord=places[5] })
des.object({ class="*", coord=places[7] })
des.object({ class="*", coord=places[9] })
des.object({ class="*", coord=places[1] })
des.object({ class="*", coord=places[4] })
des.object({ class="*", coord=places[8] })
des.object({ class="*", coord=places[9] })
des.object({ class="*", coord=places[7] })

-- Marker in a tricky spot
des.object("magic marker",42,10)

des.object("(")
des.object("(")
des.object()
des.object()
des.object()
