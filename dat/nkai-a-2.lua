--
-- An alternate introductory level...
--
-- MAZE: "nkai-a-2",' '
des.level_init({ style = "solidfill", fg = " " });
-- The whole gulf is dark and quiet
des.level_flags("mazelevel", "graveyard", "lethe", "noflip")

--         1         2         3         4         5         6         7    7
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
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
]]);

-- Stairs and Branch
des.stair("down", 57,08)
des.stair("up", 02,02)

-- BRANCH: (01,01,74,18), (45,04,68,15)
des.levregion({ region = {01,01,74,18}, exclude = {45,04,68,15}, type = "branch" })

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
des.monster("p")
des.monster("shoggoth")

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
