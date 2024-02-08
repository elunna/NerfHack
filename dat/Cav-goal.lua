-- NetHack Caveman Cav-goal.lua	$NHDT-Date: 1652196002 2022/05/10 15:20:02 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.map([[
                                                                            
                          .....................                             
                         .......................                            
                        .........................                           
                       ...........................                          
                      .............................                         
                     ...............................                        
                    .................................                       
                   ...................................                      
                  .....................................                     
                 .......................................                    
                  .....................................                     
                   ...................................                      
                    .................................                       
                     ...............................                        
                      .............................                         
                       ...........................                          
                        .........................                           
                         .......................                            
                                                                            
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
-- Stairs
des.stair("up")
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- Objects
des.object({ id = "mace", x=23, y=10, buc="blessed", spe=0, name="The Sceptre of Might" })
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()

-- Traps (no spears though!)
des.trap("pit")
des.trap("pit")
des.trap("pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")

-- monsters.
des.monster({ id = "Chromatic Dragon", x=23, y=10, asleep=1 })
des.monster("shrieker", 26, 13)
des.monster("shrieker", 25, 8)
des.monster("shrieker", 45, 11)
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "weretiger", peaceful=0 })
des.wallify()
