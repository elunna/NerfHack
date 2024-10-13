
--
-- A third gulf level...
--
--MAZE: "nkai-c",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "temperate", "noflip")

--         1         2         3         4         5         6         7    7
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                 }}}}                                       
  ...   ...            ...      }}}}   ....        .    .       ..... ....  
  ...  .......       ... ...  ...}}}}   .......     .   ...    ..   ....... 
  . ..  ...  ..    ...     .....}}}}}}        ..    ..    ......       ...  
     ....     ...  .    .... ..}}}}}}}}}       ......    ....  ...          
      . ..   .. ....  ...    }}}}}}}}}}}}..    .. ..   ...    .. ...   ..   
      .  .. ..     ....      }}}}}}}}}}}}}... ..  ... .. ......    .. ..    
     ..   ...       ..      }}}}}}}.}}}}}}}}...   .....   ..  .     ....    
   ...     ..        ..  .}}}}}}}}-.--}}}}}       ....   ..        .. ...   
  .. ..  .....      .......}}}}}}......}}}}}}}.    ....   ...    ...    ..  
 ..   ....   ..    .. .  }}}}}}}.|...|}}}}}}}...   ....    .... ..       .. 
  ..   ..     ..  .. ...  }}}}}}}--...}}}}}}.. ..  ....       ...       ..  
   .. ..       ....    .    }}}}}}...}}}}}}}.   .. ....      .. ...     ..  
   ......    ... ..    ...   }}}}}}.}}}}}}}      .....     ...    ..    ..  
   H .. ..  ..   ..   ..       }}}}}}}}}}}.       ....    .. ...   ......   
  ..     ....     .. ..   ....  }}}}}}}}....      ....  ...    .....        
   ....    ..      ....  ..  .. .}}}}}}. ...     ...... .    ...   ......   
  ......    ....  ..  .. ..   ....}}}}}.  ...  ...    ...  ... ..    ...... 
   ....        ....    .....    ..}}}}.     ....        ....    ..    ....  
                                   }}}}                                     
]]);
--123456789012345678901234567890123456789012345678901234567890123456789012345
--         1         2         3         4         5         6         7    7

-- Regions
-- The whole gulf is dark and quiet
des.region({ region={01,01,75,19},lit=0,type="morgue",filled=0 })

-- Stairs and Branch
des.stair("down", 05,17)
des.stair("up", 72,02)

BRANCH: (01,01,74,18), (30,06,40,14)

-- Sea monsters for the river
des.monster(";", 35,02)
des.monster(";", 35,08)
des.monster(";", 42,09)
des.monster(";", 39,12)
des.monster(";", 31,12)
des.monster(";", 38,17)

-- Some random flappy things
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")

-- Some not so random flappy things
des.monster("nightgaunt")
des.monster("nightgaunt")
des.monster("nightgaunt")
des.monster("byakhee")
des.monster("byakhee")
des.monster("byakhee")
des.monster("byakhee")
des.monster("byakhee")

-- A few undead
des.monster("gug"), random
des.monster("gug"), random
des.monster("gug"), random
des.monster("gug"), random
des.monster("gug"), random
des.monster("Z", random
des.monster("Z", random
des.monster("Z", random
des.monster('W', random
des.monster('V', random

-- A couple of slithy things
des.monster("p", random
des.monster("p", random
des.monster("shoggoth"), random
des.monster("shoggoth"), random
des.monster("shoggoth"), random

-- Something on the island
des.monster({ id = "black dragon", x=35,y=09, peaceful = 0, asleep = 1 })
des.monster({ id = "black dragon", x=34,y=10, peaceful = 0, asleep = 1 })
des.monster({ id = "black dragon", x=36,y=11, peaceful = 0, asleep = 1 })
des.monster({ id = "baby black dragon", x=34,y=09, peaceful = 0, asleep = 1 })
des.monster({ id = "baby black dragon", x=35,y=10, peaceful = 0, asleep = 1 })
des.monster({ id = "baby black dragon", x=36,y=10, peaceful = 0, asleep = 1 })
des.monster({ id = "baby black dragon", x=37,y=09, peaceful = 0, asleep = 1 })

-- Being black dragon, there's not much loot
des.gold(35,09)
des.gold(34,10)
des.gold(36,10)

-- One little door bell
des.trap("board", 36,09)

-- Fungi on the beaches
des.monster("shrieker", 30,03)
des.monster("shrieker", 25,09)
des.monster("shrieker", 32,17)
des.monster("shrieker", 43,06)
des.monster("shrieker", 45,11)
des.monster("shrieker", 41,15)

-- Some random objects (no potions or food)
des.object("?")
des.object("?")
des.object("+")
des.object("/")
des.object("(")
des.object("(")
des.object(")")
des.object(")")
des.object("[")
des.object("[")
des.object("[")
des.object("*")
des.object("*")
des.object("*")
des.object("*")

-- A few traps
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("magic")
des.trap("magic")
des.trap("magic")
des.trap("magic")
des.trap("anti magic")
des.trap("anti magic")
des.trap("anti magic")
des.trap("pit")
des.trap("pit")
des.trap("pit")
des.trap("board")
des.trap("board")
des.trap("board")