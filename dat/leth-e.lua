-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
--  Troll Bridge and Ruined Church
--
--  Upstream to the entry level, downstream to the Gulf.
--
--MAZE: "leth-e",' '

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "hardfloor", "lethe")

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                          TT###TT       ------- }}}}                        
           ...         -----###-----   --.....--}}}}   .........            
          ....         |...|###|...|   |.......|}}}} .............          
       ##.....###      |....###....|   |.......|}}}} ..............####     
       #  ....  #      |....###....|   |......}}}}}}  ............    # ... 
  ...  #   ...  #      |...|###|...|   |.....}}|}}}}    ........      ##... 
 .....##        #      -----###-----   |....}}}|}}}.        #           ..  
  ...         ###         TT###TT      -F-}}}-+-}}...      ##  ...          
              #           T.###.T     }}}}}}}}}}}.T #     ##   ....###....  
            ......######....###...   }}}}}}}}}}     ##    #    ...  #  ...  
           .......      ..  ###  .. }}}}}}}T...      #### #         #  ...  
          .........    ...  ###  ..}}}}}}}...#      ##  ######     ...      
         .......T}}}}}}}}}}}###}}}}}}}}}}    ###   ##        ###  ......    
}}}}}}}}}}}.T...}}}}}}}}}}}}###}}}}}}}}}       #  ##   .....   ##.........  
}}}}}}}}}}}}}}}}}}}}}}}}}}}}###}}}}}}}}      ######   .......     ........  
}}}}}}}}}}}}}}}}}}}}}}....  ###  T...      ###           H        ......    
       }}}}}}}}}}}}}    ....###....     ####       ........     #H....      
                       .....###.....#####  ##   ##..........H####           
                        ....###....         #####  ........                 
                            ###                                             
]]);

-- Dungeon Description

-- The ruined church was added in dnh
des.altar({ x=43,y=02,align="neutral", type="shrine", cracked=nh.rn2(2) })

des.region(selection.area(00,00,51,19),"lit")
des.region(selection.area(01,05,05,07),"unlit")
des.region(selection.area(09,01,13,05),"unlit")
des.region(selection.area(24,02,26,05),"unlit")
des.region(selection.area(31,02,34,05),"unlit")
des.region(selection.area(50,16,59,18),"unlit")
des.region(selection.area(54,13,60,14),"unlit")
des.region(selection.area(60,14,73,16),"lit")
des.region(selection.area(53,01,66,05),"lit")
des.region(selection.area(72,04,74,06),"unlit")
des.region(selection.area(63,07,66,09),"unlit")
des.region(selection.area(70,08,73,10),"unlit")

-- Stairs
des.stair("down", 73,04)
des.stair("up", 03,07)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Trolls
des.monster({ id = "troll", x=24,y=02, asleep = 1 })
des.monster({ id = "troll", x=26,y=02, asleep = 1 })
des.monster({ id = "troll", x=24,y=05, asleep = 1 })
des.monster({ id = "troll", x=26,y=05, asleep = 1 })
des.monster({ id = "troll", x=32,y=02, asleep = 1 })
des.monster({ id = "troll", x=34,y=02, asleep = 1 })
des.monster({ id = "troll", x=32,y=05, asleep = 1 })
des.monster({ id = "troll", x=34,y=05, asleep = 1 })
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")
des.monster("T")

-- Fishes in the river...
des.monster(";", 04,14)
des.monster(";", 16,15)
des.monster(";", 25,13)
des.monster(";", 35,13)
des.monster(";", 41,09)
des.monster(";", 48,06)
des.monster(";", 50,01)

-- Monsters
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()

-- Objects
des.object("potion of full healing")
des.object("potion of full healing")
des.object("potion of extra healing")
des.object("diamond")
des.object("diamond")
des.object("diamond")
-- des.object("%")
-- des.object("%")
-- des.object("%")
-- des.object("%")
-- des.object("%")
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()

-- Random traps
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")