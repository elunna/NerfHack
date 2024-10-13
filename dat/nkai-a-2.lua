--
-- An alternate introductory level...
--
MAZE: "nkai-a-2",' '
#FLAGS: lethe
GEOMETRY: center, center

--         1         2         3         4         5         6         7    7
--123456789012345678901234567890123456789012345678901234567890123456789012345
MAP
                                 }}}}                                       
 ...    .....            ...    }}..}}  ....        .....       .....   ... 
 ...  ....  ..     ... ... ....}.}..}.}   ...    ..........   ...   .....   
  .  ...     ...  .. ...    ..}.}....}.}    . .......    .......    ..  ..  
  ....         .....   .... .}.}.....}..}   ....     ...      .......  ..   
    ...   .... .. ..    ..  }..}....}...}. ...     ...... ....      ....    
   .. ..... ....   ..  ..  }....}..}...}.....    .....  ...   ...   . ...   
  ..    ..   ..     ....  }.}..}.}..}.}..      ....  ........  .... .   ..  
 ..    ....   ...  .. ... .}....}}}..}}}...  ...     ...........  ...    .  
  ..   .. ..    ....   ....}...}.}}}}}.}} ...  .... ........  ..   ..    .  
  ... ..   ...  .. ...   ...}.}...}}}...}  ..    ....  ...     .. ...    .. 
    ...      ....    ...  ..}..}...}}}...}   ...   ..    ...    ....    ... 
   .....    ..  ...    ....  }}...}}}...}..    ..   ..     ..  ..  ..   ..  
  ... ...    ..  ..     ..   .}....}}}...}..   ...   .... ... ... ..    .   
 ...    ...   ....  ...  ......}....}}}.}. .. .. ...   .... ... ...   ...   
 ...     ... ... ..   .....  ...}....}}}.   ...   .....      ..    ....     
  ...     ....     ..  ...    ...}..}}}.     .    .   .....      .... ..    
   ....  ....  ...  ....    ...   }..}}}... .... ... ..   ........     ...  
  ... ....  .... .....    ....     }}}.}  ... .... ...    .   ......    ... 
                                   }}}}                                     
ENDMAP
--123456789012345678901234567890123456789012345678901234567890123456789012345
--         1         2         3         4         5         6         7    7

-- Regions
-- The whole gulf is dark and quiet
-- TODO: Mark the level as graveyard instead?
des.region({ region={01,01,75,195},lit=0,type="morgue",filled=0 })

-- Stairs and Branch
des.stair("down", 57,08)
des.stair("up", 02,02)

BRANCH: (01,01,74,18), (45,04,68,15)

-- Sea monsters for the river
des.monster(";", 33,02)
des.monster(";", 36,08)
des.monster(";", 39,07)
des.monster(";", 37,12)
des.monster(";", 31,14)
des.monster(";", 37,17)

-- Some random flappy things
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")
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
des.monster("gug")
des.monster("gug")
des.monster("gug")
des.monster("gug")
des.monster("gug")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("W")
des.monster("V")

-- A couple of slithy things
des.monster("P")
des.monster("p",)
des.monster("shoggoth")

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
