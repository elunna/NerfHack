--
--	The Gulf of N'Kai
--
--	A dark, bare place haunted by Night gaunts, Byakhee, Demons
--	and Gugs.  A suitably dire place for the wizard to hide his
--	tower.  Beware of the shuggoths.
--
--	Unlike the other lethe levels, these are not a hardfloor
--	level, allowing the player to fall through to deeper
--	levels of the gulf.
--

--
-- An introductory level...
--
-- MAZE: "nkai-a-1",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "temperate", "noflip")

--0         1         2         3         4         5         6         7    
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                 }}}}                                       
   ..      ......        ....   }}}}  ..........  ......  ...... ....     . 
 .. ... ... .. .. ...  ...  ... }}} } ... . .. ... .. ..  ... ... ..... ... 
 .... ... .. ..  ..  ...  ..   }} }} }..     ...     ... ... ..  ..   ...   
   ..  ..  ...  ..  ..   ..  .} }}.}..}..  ...  ..  ..   ..   .. ..  ..   . 
    ....  ..   ..    ..  .. ..}..}}.}}..  ..     ....   ....   ...  .... .. 
   ..    ....   ..  ..   ....  }..}}}.}  ....  ...  ... .. .. .. .. ..  ..  
  ..   ...  .. ..  .... ..  ..}  ..}}}.}  ....  ...  ....  ....   ...  ...  
 .... ..     ...  ..  ...   .}.  .}}.}}. ..  .... ....  ....  .. .. ....    
  .....   .... .. ..   ... ...}..}}...}...  ..      ... .. ....  ..  ..     
    .... ..     ...      .... .}.}.}.}..  ...   ..  . ...   ..   ...  ..    
   ..  ...    ... ..    ..  .  } }}.}.}  ..   ...  ....    ....   ..   ..   
  ..  .. ..  ..    ..  ..   ..  }}.} }  .... ...    ....  ..  .. ....  ...  
   ....   .. ..   .... ... .... .}} } } ...... ... ..  ....    .... .  .... 
    .... ..  ...   ..   ....  ..}}.} } }.....    ...    ..      ... .. .... 
  .... ...     .....     .......}.}.}.}.}...    .. .... ...   ...   .. ...  
 ....   ....  ... ...   .........}.}.}.}...    ...   .....   .....   ...    
  .... ... ....     ......  ......}.}.}}..   ....      ........  ...     .. 
    .....    .....    ...     ...  }.}}}.   ......       ....      .......  
                                   }}}}                                     
]]);
--0123456789012345678901234567890123456789012345678901234567890123456789012345
--         1         2         3         4         5         6         7    

-- Regions
-- The whole gulf is dark and quiet
des.region({ region={01,01,75,19},lit=0,type="morgue",filled=0 })

-- Stairs and Branch
des.stair("down", 03,08)
des.stair("up", 73,14)

BRANCH: (01,01,74,18), (00,00,00,00)

-- Sea monsters for the river
des.monster(";", 34,02)
des.monster(";", 35,08)
des.monster(";", 39,07)
des.monster(";", 37,12)
des.monster(";", 32,14)
des.monster(";", 38,18)

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
des.monster("P")
des.monster("shoggoth")

-- Some random objects (no potions or food)
des.object("?")
des.object("?")
des.object('+')
des.object('/')
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


