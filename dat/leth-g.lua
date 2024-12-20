-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
--  Honycombe Canyon
--
--  Upstream to the entry level, downstream to the castle.
--
--MAZE: "leth-g",' '

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "hardfloor", "lethe")

--0         1         2         3         4         5         6         7    7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
  ---------   ---     ---      ---      ---    ---    ---    ---      ------
  |.......|----.-------}--------.--------.------.------.------}-------|....|
  |.......+...........}}}}}}}}................................}}}}....+....|
  |.......|----.-------}}-------.--------.------.------.------}--}}}--|....|
  ---------   -S-     -}}}     ---      ---    -S-    ---    ---  }}  ------
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

des.region({ region={18,14,27,18},lit=0,type="migohive",filled=1 })
des.region({ region={44,06,53,09},lit=0,type="migohive",filled=1 })
des.region({ region={60,16,68,18},lit=0,type="migohive",filled=1 })

-- Stairs
des.stair("down", 73,02)
des.stair("up", 04,02)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

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
                des.object({ id = "unicorn horn", buc="cursed", spe=-3 })
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
des.trap("random")
des.trap("random")
des.trap("random")

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
des.object({ id = "levitation boots", x=73,y=12, buc="cursed" })

-- A few monsters (other than bees)
des.monster("t", 18,02)
des.monster("t", 44,02)
des.monster("t", 62,02)
des.monster("B", 06,16)
des.monster("B", 29,11)
des.monster("B", 48,12)
des.monster("B", 73,07)

-- A few fishies
des.monster(";", 05,13)
des.monster(";", 13,09)
des.monster(";", 23,07)
des.monster(";", 26,02)
des.monster(";", 31,10)
des.monster(";", 40,14)
des.monster(";", 48,17)
des.monster(";", 57,13)
des.monster(";", 64,10)
des.monster(";", 67,07)
des.monster(";")
des.monster(";")
des.monster(";")

-- A couple of random monsters to finish
des.monster()
des.monster()
des.monster()
