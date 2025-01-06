-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
--  Sylvan Park
--
--  Upstream to the entry level, downstream to the castle.
--
-- MAZE: "leth-f",' '

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel","hardfloor", "lethe")

--         1         2         3         4         5         6         7    7
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
 ---------                                                            ------
 |.S.....|    .........    ######                        ......T......|....|
 |.|.....|..............H###    #######      #####   .......T.....T...+....|
 -----+---......T.......              ###.....   ##.....T.............------
    ..................}}}}}}}}}}}}}}}    ..}..     ..T........T....T....    
  .................}}}}}}}}}}}}}}}}}}}    ...       ............T....}}}}}}}
 .....T.....T....}}}}}}}}}}}}}}}}}}}}}}     ###      ....T.........}}}}}}}}}
 ....T.........}}}}}}}}  ...... }}}}}}}}      #       .......T...}}}}}}}}}}}
  ............}}}}}}}}    ..  #  }}}}}}}}}    ##...    ...T....}}}}}}}}}}}} 
   .......T..}}}}}}}}         ##  }}}}}}}}}}    ....    .....}}}}}}}}}}     
     ..T.....}}}}}}}}}.        ###.}}}..}}}}..   ....    T..}}}}}}}}        
       .......}}}}}}}}}.           .}}}..}}}}}.. # ...    }}}}}}    ------- 
       #   ....T.}}}}}}..           .}}.T.}}}}}...       }}}}}      |.....| 
      ##   # ......}}}}}.            ..}}..}}}.}}T..    }}}}}  --------S--- 
     ##    #        }}}}..       ###  }}.}}}}..}}}}}.} }}}}}   |...{....|   
     #   #H##  ....  }}}}.#####  H ##  .}.}}}.}.}}}}}.}}}}}    |..{.{...|   
    ....H#  ##.....  }}}}.    .. .  ###..}.}.}}}.}}}}}.}}..####+...{....|   
  .....       ....   }}}}   ......      ..}. T}}}.}}}}}..      ----------   
   .....       ...  }}}}    .....                                           
                   }}}}                                                     
]]);

-- Dungeon Description
des.region(selection.area(00,00,75,19),"lit")
des.region(selection.area(02,01,02,02),"lit")

des.altar({ x=06,y=01,align=random, type="shrine", cracked=nh.rn2(2) })

des.region(selection.area(02,16,07,18),"unlit")
des.region(selection.area(14,15,18,18),"unlit")
des.region(selection.area(28,16,33,18),"unlit")
des.region(selection.area(41,03,45,05),"unlit")
des.region(selection.area(48,08,53,11),"unlit")
des.region(selection.area(71,01,74,02),"lit")
des.region(selection.area(64,14,71,16),"lit")
des.region(selection.area(69,12,73,12),"lit")

-- Stairs
des.stair("down", 73,01)
des.stair("up", 30,17)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Doors
des.door("closed", 06,03)
des.door("locked", 03,01)
des.door("closed", 70,02)
des.door("locked", 63,16)
des.door("closed", 71,13)

-- Centaurs in the west
des.monster("C", 13,03)
des.monster("C", 09,06)
des.monster("C", 06,09)
des.monster("C", 13,12)
des.monster("C", 22,03)
des.monster("C", 02,07)

-- Chief Centaur and hareem
des.monster("mountain centaur", 16,16)
des.object("chest", 18,15)
des.object({ id = "bow", x=16,y=16, buc="blessed", spe=2 })
des.monster("mountain centaur", 04,17)
des.monster("mountain centaur", 05,18)
des.object("chest", 03,18)

-- Elves in the east
des.monster("elven monarch", 58,03)
des.monster("elven monarch", 64,02)
des.monster("elven cleric", 65,04)
des.monster("elven cleric", 61,05)
des.monster("elven cleric", 61,01)
des.monster("elf-noble", 55,04)
des.monster("elf-noble", 53,05)
des.monster("elf-noble", 56,06)
des.monster("Woodland-elf", 57,08)
des.monster("Woodland-elf", 59,10)

-- Nymphs in the middle!
des.monster("n", 39,10)
des.monster("n", 48,13)
des.monster("n", 48,16)
des.monster("n", 44,16)
des.monster("n", 40,14)
des.monster("n", 41,17)
des.monster("n", 34,10)
des.monster("n", 48,12)
des.monster("n", 54,16)
des.monster("n", 45,10)

-- A couple of trolls guarding the door
des.monster("troll", 30,16)
des.monster("troll", 30,17)

-- A monster in the middle darkness...
des.monster("kraken", 43,04)
des.monster("p", 49,09)
des.monster("p", 41,10)

-- A couple of extra random monsters...
des.monster()
des.monster()
des.monster()

-- A few statues
des.object({ id = "statue", x=05, y=04, montype="mountain nymph",
             contents = 0 })
des.object({ id = "statue", x=07, y=04, montype="mountain nymph",
             contents = 0 })
des.object({ id = "statue", x=69,y=01, montype="Death", historic=1,
             contents = function()
             des.object({ id = "wand of death" })
             end
});

-- des.object({ id = "statue", x=67, y=15, montype="Poseidon",
--             contents = 0 })

-- Was a statue of a giant crab
des.object({ id = "statue", x=67,y=15, montype="kraken", historic=1,
             contents = function()
              des.object("amulet of magical breathing")
             end
});

des.object({ id = "statue", x=69,y=01, montype="kraken", historic=1,
             contents = function()
              if percent(15) then
                des.object({ id = "wand of death" })
              else
                des.object({ id = "wand of lightning" })
              end
             end
});

des.object({ id = "statue", x=38, y=10, contents = 0 })

-- Deep one servitors for the temple of Poseidon
des.monster({ id = "deep one", x=65, y=14  })
des.monster({ id = "deep one", x=65, y=16  })
des.monster({ id = "deeper one", x=70, y=15  })
des.object("chest", 69,12)
des.object("chest", 73,12)

--des.object("scroll of demonology"), (70,15), cursed,0
des.object({ id="scroll of fire", x=70, y=15, buc="cursed" })

-- A stray amulet
des.object('"', 26,08)

-- A few random traps
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")
des.trap("random")


-- Fishes in the river...
des.monster(";", 23,15)
des.monster(";", 19,11)
des.monster(";", 16,09)
des.monster(";", 21,06)
des.monster(";", 28,05)
des.monster(";", 34,06)
des.monster("electric eel", 38,08)
des.monster(";", 43,12)
des.monster(";", 50,15)
des.monster(";", 58,14)
des.monster(";", 65,09)
des.monster(";", 72,06)

-- A few random objects
des.object("!")
des.object("!")
des.object("!")
des.object("/")
des.object("*")
des.object()
des.object()
des.object()
