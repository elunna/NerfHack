-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
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
-- The whole gulf is dark and quiet
des.level_flags("mazelevel", "graveyard", "noflip")

--0         1         2         3         4         5         6         7    
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                 LLLL                                       
   ..      ......        ....   LLLL  ..........  ......  ...... ....     . 
 .. ... ... .. .. ...  ...  ... LLL L ... . .. ... .. ..  ... ... ..... ... 
 .... ... .. ..  ..  ...  ..   LL LL L..     ...     ... ... ..  ..   ...   
   ..  ..  ...  ..  ..   ..  .L LL.L..L..  ...  ..  ..   ..   .. ..  ..   . 
    ....  ..   ..    ..  .. ..L..LL.LL..  ..     ....   ....   ...  .... .. 
   ..    ....   ..  ..   ....  L..LLL.L  ....  ...  ... .. .. .. .. ..  ..  
  ..   ...  .. ..  .... ..  ..L  ..LLL.L  ....  ...  ....  ....   ...  ...  
 .... ..     ...  ..  ...   .L.  .LL.LL. ..  .... ....  ....  .. .. ....    
  .....   .... .. ..   ... ...L..LL...L...  ..      ... .. ....  ..  ..     
    .... ..     ...      .... .L.L.L.L..  ...   ..  . ...   ..   ...  ..    
   ..  ...    ... ..    ..  .  L LL.L.L  ..   ...  ....    ....   ..   ..   
  ..  .. ..  ..    ..  ..   ..  LL.L L  .... ...    ....  ..  .. ....  ...  
   ....   .. ..   .... ... .... .LL L L ...... ... ..  ....    .... .  .... 
    .... ..  ...   ..   ....  ..LL.L L L.....    ...    ..      ... .. .... 
  .... ...     .....     .......L.L.L.L.L...    .. .... ...   ...   .. ...  
 ....   ....  ... ...   .........L.L.L.L...    ...   .....   .....   ...    
  .... ... ....     ......  ......L.L.LL..   ....      ........  ...     .. 
    .....    .....    ...     ...  L.LLL.   ......       ....      .......  
                                   LLLL                                     
]]);

-- Stairs and Branch
des.stair("down", 03,08)
des.stair("up", 73,14)

-- BRANCH: (01,01,74,18), (00,00,00,00)
des.levregion({ region = {01,01,74,18}, exclude = {00,00,00,00}, type = "branch" })

-- Sea monsters for the river
-- des.monster(";", 34,02)
-- des.monster(";", 35,08)
-- des.monster(";", 39,07)
-- des.monster(";", 37,12)
-- des.monster(";", 32,14)
-- des.monster(";", 38,18)

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


