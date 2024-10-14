--
--	Honycombe Canyon
--
--	Upstream to the entry level, downstream to the castle.
--
--MAZE: "leth-g",' '

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "hardfloor", "temperate", "noflip")

--0         1         2         3         4         5         6         7    7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
  ---------   ---     ---      ---      ---    ---    ---    ---      ------
  |.......|----.-------}--------.--------.------.------.------.-------|....|
  |.......+...........}}}}}}}}........................................+....|
  |.......|----.-------}}-------.--------.------.------.------.-------|....|
  ---------   -S-     -}}}     ---      ---    -S-    ---    ---      ------
               # ...}}}}}}}}                    H                 }}}       
               ...}}}}}}}}}}}}}     ###      .......             }}}}}}...  
              ..}}}}}}}}}}}}}}}}.   H ######..........        ..}}}}}}}}}.. 
              }}.}}}}}}}}}}}}}}}}....        .........H##### ..}}}}}}}}}}}} 
           }}}}}}.}...    }}}}}}}}....        ......       ...}}}}}}}}}}}}}}
       }}}}}}}}}....       ..}}}}}.}...         #         ..}}}}}}}}}}}}}}}}
  }}}}}}}}}}}     H         ...}}.}}}}}         H         }}.}}}}}}}}}}}}}}}
}}}}}}}}}}}    ####          ....}}}}}}}}}}}  ......  }}}}}}}.}}}}}}}}....  
}}}}}}}}}}   ###              #   }}}}}}}}}}}}}}}}}}}}}}}}}}}}.}..      #   
}}}}}}}}}   ##        ...     ##  .}}}}}}}}}}}}}}}}}}}}}}}}}}....      ##   
  }}}}... ###      ........    #   .}}}}}}}}}}}}}}}}}}}}}}    H       ##    
    ....### H     ..........H###   .}}}}}}}}}}}}}}}}}}}}}    ........H#     
     ..     ###  #..........     ##..}}}}}}}}}}}}}}}}}}}}   .........   ..  
              ####  ...  ...H#####  ....}}}}}}}}}}}}}}}}      .......H#...  
                                          }}}}}}}}}}}}                      
]]);

-- Dungeon Description
des.region(selection.area(00,00,75,19),"lit")
des.region(selection.area(03,01,09,03),"lit")
des.region(selection.area(11,01,69,03),"unlit")
des.region(selection.area(71,01,74,03),"lit")

-- Pending implementation of migos, migohives
-- REGION: (18,14,27,18), unlit, "migohive"
-- REGION: (44,06,53,09), unlit, "migohive"
-- REGION: (60,16,68,18), unlit, "migohive"

-- Stairs
des.stair("down", 73,02)
des.stair("up", 04,02)

-- Doors
des.door("locked", 10,02)
des.door("locked", 15,04)
des.door("locked", 48,04)
des.door("locked", 70,02)

-- A few statues
des.object({ id = "statue", x = 04, y = 01, montype = "bone devil", historic = true });
des.object({ id = "statue", x = 04, y = 03, montype = "bone devil", historic = true });
des.object({ id = "statue", x = 06, y = 01, montype = "ice devil", historic = true });
des.object({ id = "statue", x = 06, y = 03, montype = "ice devil", historic = true });
des.object({ id = "statue", x = 08, y = 01, montype = "balrog", historic = true });
des.object({ id = "statue", x = 08, y = 03, montype = "balrog", historic = true });

-- Long hall
des.object({ id = "statue", x = 15, y = 01, montype = "knight", historic = true });
des.object({ id = "statue", x = 15, y = 03, montype = "barbarian", historic = true });
--des.object({ id = "statue", x = 23, y = 01, montype = "fool", historic = true });
--des.object({ id = "statue", x = 23, y = 03, montype = "Rodney", historic = true });
des.object({ id = "statue", x = 32, y = 01, montype = "wizard", historic = true });
des.object({ id = "statue", x = 32, y = 03, montype = "priest", historic = true });
des.object({ id = "statue", x = 41, y = 01, montype = "ranger", historic = true });
des.object({ id = "statue", x = 41, y = 03, montype = "rogue", historic = true });
des.object({ id = "statue", x = 48, y = 01, montype = "caveman", historic = true });
des.object({ id = "statue", x = 48, y = 03, montype = "samurai", historic = true });
des.object({ id = "statue", x = 55, y = 01, montype = "monk", historic = true });
des.object({ id = "statue", x = 55, y = 03, montype = "valkyrie", historic = true });
des.object({ id = "statue", x = 62, y = 01, montype = "healer", historic = true });

des.object({ id = "statue", x = 62, y = 03, montype = "Pestilence", historic = true,
             contents = function()
                des.object({ id = "unicorn horn", buc="cursed", spe=3 })
             end
});

des.object({ id = "statue", x = 0, y = 0, montype = "C", historic = true });

-- Final Room
des.object({ id = "statue", x = 72, y = 01, montype = "marilith", historic = true });
des.object({ id = "statue", x = 72, y = 03, montype = "marilith", historic = true });

des.object({ id = "statue", x=74,y=02, montype="Asmodeus", historic=1,
             contents = function()
                des.object({ id = "ring of aggravate monster", buc="cursed" })
             end
});

des.object("fortune cookie", 71,02)

-- A few traps
des.trap("pit",21,02)
des.trap("pit",30,02)
des.trap("board",19,17)
des.trap("board",46,07)
des.trap("board",62,14)
des.trap()
des.trap()
des.trap()

-- Some random objects
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()

-- A little incentive for the last hive
des.object("potion of full healing", 73,17)
des.object("potion of full healing", 73,18)
des.object({ id = "flying boots", x=73,y=12, buc="cursed" })

-- A few monsters (other than bees)
des.monster("T", 18,02)
des.monster("T", 44,02)
des.monster("T", 62,02)
des.monster("B", 06,16)
des.monster("B", 29,11)
des.monster("B", 48,12)
des.monster("B", 73,07)

-- A few fishies
des.monster("giant eel", 05,13)
des.monster("giant eel", 13,09)
des.monster("giant eel", 23,07)
des.monster("electric eel", 26,02)
des.monster("electric eel", 31,10)
des.monster("electric eel", 40,14)
des.monster("electric eel", 48,17)
des.monster("jellyfish", 57,13)
des.monster("jellyfish", 64,10)
des.monster(";", 67,07)
des.monster(";")'
des.monster(";")'
des.monster(";")'

-- A couple of random monsters to finish
des.monster()
des.monster()
des.monster()
