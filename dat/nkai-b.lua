-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
-- The level with the wizards fortress...
--
--MAZE: "nkai-b",' '
des.level_init({ style = "solidfill", fg = " " });
-- The whole gulf is dark and quiet
des.level_flags("mazelevel", "graveyard", "noflip")

--         1         2         3         4         5         6         7    7
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                 LLLL                                       
 ..  ..   .     .. ....  .... ....LLLL.....  ...       .......     ....     
  .. .   ...   .  ......... ... .LLLL.L  .....      ....  .. ..   .   .   . 
   .... ..  . .     ....        L.LLLL.L           ..  ..    ......      .. 
 ...  ...    ...             ... L.LLL. L  ....  ...    ... ...   ...  ..   
  .    ....  .  ...    .........L.L L.LLL ........        ...       ...     
 ..  ...  ....   .   .... .....L L.L L...L... ...  ...     ..      ... .    
 ......  ..  .........      ... L L.L.....L.   ..... ..   ....     ..   ... 
  ... ....    ........ ...  .....LLL...  L..   ..     ...... ..  ...     .  
  ..    ...  .....   ... .......L.L L.  L.L ......      ...   ....  ...  .. 
   ..  .  .... ...   .    .. . L L.L.L L.L  ...  ...    ..    .....    ...  
    ...    ..  ..  ..  LL     ..L...L.L.L L.....   ... ..    .   ... ...    
   ....   ..   ....  .LLLLL    L.... L.L...L  ...   .....   ..  .. ... .    
 .... ..  .   ...   .LL---LL  L L.. L.L...L.   ...  ..  ..     ...     ..   
 ....  .. ......   .LLL|.|LLLL L L L.L L.L.   .......    ..   ......    .   
 ...    ... ...   . L---.---LL    L.L L.L      ......     .....    ..  ..   
   ......    ..    .L|.....|L..    LL..LL  ...  ..  ..     ...  ..  ....    
  ...   .......  .. L---.---LL.. ...LLLL  .......    ...  ..   ......  .. . 
   .       ...   .. L|.S.|LLL .... LLLL    ....        ....   .....     ... 
                    L-----LL       LLLL                                     
]]);

-- Stairs, Branches and the wizards portal
des.stair("down", 64,17)
des.stair("up", 03,17)

-- The new stairs to the Wizard's Tower
-- Moved from the fake wizard's levels
--BRANCH: (22,18,22,18), (00,00,00,00)
des.levregion({ region={22,18,22,18}, type="portal", name="wizard3" })

-- The wizard gets a drawbridge...
des.drawbridge({dir="west",state="closed",x=28,y=16})

-- One secret door
des.door("locked", 23,18)

-- One sneaky trap
des.trap("magic", 24,16)

-- The Wizard has some guards
des.monster({ id = "iron golem", 22,16, peaceful = 0, asleep = 1 })
des.monster({ id = "hell hound", 24,14, peaceful = 0, asleep = 1 })
des.monster({ id = "green slime", 24,18, peaceful = 0, asleep = 1 })
des.monster({ id = "skeleton", 26,16, peaceful = 0, asleep = 1 })

-- And a door bell...
des.trap("board", 29,16)

-- Sea monsters for the river
-- des.monster(";", 35,02)
-- des.monster(";", 35,08)
-- des.monster(";", 42,07)
-- des.monster(";", 39,12)
-- des.monster(";", 31,12)
-- des.monster(";", 38,17)
-- des.monster(";", 27,18)
-- des.monster("kraken", 28,15)
-- des.monster(";", 23,12)

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
des.monster("shoggoth")

-- A small tribe of ghouls
des.monster({ id = "gug", 43,16, peaceful = 0, asleep = 1 })
des.monster({ id = "gug", 44,17, peaceful = 0, asleep = 1 })
des.monster({ id = "gug", 45,18, peaceful = 0, asleep = 1 })
des.monster({ id = "gug", 43,18, peaceful = 0, asleep = 1 })
des.monster({ id = "gug", 45,16, peaceful = 0, asleep = 1 })

-- And some toys for them...
-- des.object("wand of death", 43,16)
--des.object("scroll of demonology"), (44,17), cursed,0
des.object({ id = "scroll of create monster", x=45, y=18, buc="cursed" })

-- A few traps
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("magic",31,17)
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
des.trap("board",47,17)


