-- NetHack Caveman Cav-loca.lua	$NHDT-Date: 1652196002 2022/05/10 15:20:02 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.2 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor", "noflip")

des.map([[
                                                                            
    .............                     ...........                           
   ...............                   .............                          
    ......}}}....                  ...............        ..........        
     ....}}}....                    .............      ...............      
        ...  }}                                ...   ..................     
         ...                ..........          ... ..................      
         }...              ....}}}.....          BBB...................     
           ... }            ..........          ......................      
   }}       ..... }}   }          ..      ....}B........................    
  ....       ...............      .  } .......}B..........................  
 ......     .. .............S..............         ..................      
  ....     ..  }   }}}       ...........             ...............        
     ..  ...                      }}}           ....................        
      ....                                      BB...................       
      }} .. }               ..                 ..  ...............          
          ..   .......     ....  .....  ....  ..     .......   }            
         } ......}}}...     ....... ..  .......       .....    ...  ....    
            }  .......       .....   ......                      .......    
                                                                            
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "unlit")
des.region({ region={52,06, 73,15}, lit=1, type="ordinary", irregular=1 })
-- Doors
des.door("locked",28,11)
-- Stairs
des.stair("up", 04,03)
des.stair("down", 73,10)
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- Objects
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
des.object()
-- Random traps
des.trap("pit")
des.trap("pit")
des.trap("pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("bear")
des.trap("bear")
des.trap("bear")
des.trap("spear")
des.trap("spear")
des.trap("spear")
des.trap()
des.trap()
-- Random monsters.
des.monster({ class = "h", peaceful=0 })
des.monster({ class = "H", peaceful=0 })
des.monster({ id = "hill giant", peaceful=0 })
des.monster({ id = "hill giant", peaceful=0 })
des.monster({ id = "hill giant", peaceful=0 })
des.monster({ id = "hill giant", peaceful=0 })
des.monster({ class = "H", peaceful=0 })


des.monster({ id = "electric eel", peaceful=0 })
des.monster({ id = "electric eel", peaceful=0 })
des.monster({ id = "electric eel", peaceful=0 })
des.monster({ id = "electric eel", peaceful=0 })
des.monster({ id = "giant eel", peaceful=0 })
des.monster({ id = "giant eel", peaceful=0 })
des.monster({ id = "giant eel", peaceful=0 })
des.monster({ id = "giant eel", peaceful=0 })

des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })

des.monster({ id = "monkey", peaceful=0 })
des.monster({ id = "monkey", peaceful=0 })
des.monster({ id = "monkey", peaceful=0 })
des.monster({ id = "monkey", peaceful=0 })

des.monster({ id = "python", peaceful=0 })
des.monster({ id = "python", peaceful=0 })
des.monster({ id = "python", peaceful=0 })
des.monster({ id = "python", peaceful=0 })

des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "weretiger tiger", peaceful=0 })
des.wallify()

--
--    The "goal" level for the quest.
--
--    Here you meet Tiamat your nemesis monster.  You have to
--    defeat Tiamat in combat to gain the artifact you have
--    been assigned to retrieve.
--
