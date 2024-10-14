--
--	Sylvan Park
--
--	Upstream to the entry level, downstream to the castle.
--
-- MAZE: "leth-f",' '

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "hardfloor", "temperate", "noflip")

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
--123456789012345678901234567890123456789012345678901234567890123456789012345
--         1         2         3         4         5         6         7    7

-- Dungeon Description
des.region(selection.area(00,00,75,19),"lit")
des.region(selection.area(02,01,02,02),"lit")

-- Pending being able to specify cracked altars in LUA
-- des.region({ region={04,01,08,02}, lit=1, type="temple", filled=2 })
-- des.altar({ x=06,y=01,align=random, type="shrine" })

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
des.monster("Green-elf", 58,03)
des.monster("Green-elf", 64,02)
des.monster("Green-elf", 65,04)
des.monster("Green-elf", 61,05)
des.monster("Green-elf", 61,01)
des.monster("Woodland-elf", 55,04)
des.monster("Woodland-elf", 53,05)
des.monster("Woodland-elf", 56,06)
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
                des.object({ id = "wand of death" })
             end
});

des.object({ id = "statue", x=38, y=10, contents = 0 })

-- Deep one servitors for the temple of Poseidon
des.monster({ id = "deep one", x=65, y=14, asleep = 1 })
des.monster({ id = "deep one", x=65, y=16, asleep = 1 })
des.monster({ id = "deeper one", x=70, y=15, asleep = 1 })
des.object("chest", 69,12)
des.object("chest", 73,12)
--des.object("scroll of demonology"), (70,15), cursed,0

-- A stray amulet
des.object('"', 26,08)

-- A few random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()

-- Fishes in the river...
des.monster("giant eel", 23,15)
des.monster("giant eel", 19,11)
des.monster("giant eel", 16,09)
des.monster("giant eel", 21,06)
des.monster("electric eel", 28,05)
des.monster("electric eel", 34,06)
des.monster("electric eel", 38,08)
des.monster("jellyfish", 43,12)
des.monster("jellyfish", 50,15)
des.monster("jellyfish", 58,14)
des.monster(";", 65,09)
des.monster(";", 72,06)

-- A few random objects
des.object("!")
des.object("!")
des.object("!")
des.object("/")
des.object("*")
des.object("%")
des.object("%")
des.object("%")
des.object("%")
des.object()
des.object()
des.object()
