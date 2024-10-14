--
--	Troll Bridge and Ruined Church
--
--	Upstream to the entry level, downstream to the Gulf.
--
--MAZE: "leth-e",' '

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "hardfloor", "temperate", "noflip")

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                          TT###TT               }}}}                        
           ...         -----###-----            }}}}   .........            
          ....         |...|###|...|            }}}} .............          
       ##.....###      |....###....|           }}}}} ..............####     
       #  ....  #      |....###....|          }}}}}}  ............    # ... 
  ...  #   ...  #      |...|###|...|         }}}}}}}    ........      ##... 
 .....##        #      -----###-----        }}}}}}}.        #           ..  
  ...         ###         TT###TT      }}}}}}}}}}}...      ##  ...          
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
--0123456789012345678901234567890123456789012345678901234567890123456789012345
--0         1         2         3         4         5         6         7
-- Dungeon Description

-- The ruined church was added in dnh, but not NerfHack
-- des.region({ region={39,00,47,07}, lit=1, type="temple", filled=2 })
-- des.altar({ x=43,y=02,align="neutral", type="shrine" })


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
des.monster("giant eel", 04,14)
des.monster("giant eel", 16,15)
des.monster("giant eel", 25,13)
des.monster("electric eel", 35,13)
des.monster("electric eel", 41,09)
des.monster("electric eel", 48,06)
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
des.object("%")
des.object("%")
des.object("%")
des.object("%")
des.object("%")
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()

-- Random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()