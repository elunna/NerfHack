-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
-- The bottom of the gulf (so look for the vibrating square)...
--
-- This level is hardfloor, as it's over the sanctum.  Players need to
-- be able to dig on this level, as the vibrating square might be hidden
-- somewhere inaccessible (without dropping a lot of thie kit).
--
--MAZE: "nkai-z",' '
des.level_init({ style = "solidfill", fg = " " });
-- The whole gulf is dark and quiet
des.level_flags("mazelevel", "graveyard", "hardfloor")


--         1         2         3         4         5         6         7    7
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                 LLLL                                       
  ....   ...   ........ ....    LLL LL      . .....              .......    
  ..       .  ......  ... ..   LL LL LL    . ........          ....    ..   
   ......  .... ..         ...LL L..L.LL. .   ....  ...       ...     ....  
     L  ....     ......     .L.LL.LL.LL.L.            ......L...  .  .....  
    ..LL..            ......L.L..L..L. L.L.        .......LL...  ...  ...   
   ..  .LLL....      ..  .LL..L L.LL.L  L L...  .......LLL  ..L   ......    
   ...    .LLLLL... ..LLLL...L..L.LL..L L  LL.....LLLLL ..LLLL         .    
     ...      ..LLLLLL.    LL..L..LL.L. L.   LLLLL          ..LL   ....     
    .. ..  ..LLL.     ...LL  .L   LL...  L. .     LL.        ...L.....      
   ..   ...LL.   .LL..LLL   .L    LL     .LLL... ...L...    ..  ....        
  ...   ..L..     ..LL.     L.   LLLL     .L.L ... .L .L   ....  ......     
   ..    ...     ..L.. .   L L. LLLLLL   ..L..   .   LL.  .....    ......   
    .  ...      ..L..   .    L. LLLLLL   .L.L   ....  .L   ..    ..         
    . ....      ....   ...  L. .LLLLLL   . .L  ....    .L      .....        
     ..  ..      ..   ..... .    LLLL.     ..           .   .....LL......   
    ...   .. .. ..   .....  .     .....     .    ....  .........LLLL......  
   .....   ......     .... .... ..... ...  .... .......    ....LLL......    
   ....      ...         ...  ......    ....   ......         .......       
                                                                            
]]);

-- Stairs and Branch
des.stair("up", 17,01)

--BRANCH: (01,01,74,18), (00,00,00,00)
des.levregion({ region = {01,01,74,18}, exclude = {00,00,00,00}, type = "branch" })

-- Sea monsters for the river
-- des.monster(";", 34,02)
-- des.monster(";", 35,08)
-- des.monster(";", 40,07)
-- des.monster(";", 34,12)
-- des.monster(";", 33,14)
-- des.monster(";", 23,07)

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
des.monster("gug")
des.monster("gug")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("W")
des.monster("V")

-- A couple of slithy things
des.monster("P")
des.monster("P")
des.monster("shoggoth")
des.monster("shoggoth")
des.monster("shoggoth")
--des.monster("giant shoggoth")
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
des.trap("vibrating square")