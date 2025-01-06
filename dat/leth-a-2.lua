-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
--  Alternate river head - Vampires and Byakhee
--
-- MAZE: "leth-a-2",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "hardfloor", "lethe")

--0         1         2         3         4         5         6         7     
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                                                             
   -------                #######H...............#####      ...       ....   
   |.....|               ##         .......   ...    #####.......    ......  
   |...}.+###           ##              #      H     H     .......   .....   
   |.....|  ####H########  #########.....      .     ##      ....     ...    
   ---S---       #         #         ......           ###     #        ....  
      #         ##     ........  }}}}}}}}}}}}}    ....  #     ##     ##....  
      H         H   ........}}}}}}}}}}}}}}}}}}}}}}}T....#      #     #  ..   
      #      #####H.....T.}}}}}}}}}}}}}}}}}}}}}}}}}}}}...    ###     #       
             #      ...}}}}}}}}}}...........}}}}}}}}}}}}}}   #       ###     
          ####       .}}}}}}}}}}.....T........}}}}}}}}}}}}}  H         #     
          #             }}}}}}}}}}}......T...}}}}}}}}}}}}}}}...        #     
        .....         }}}}}}}}}}}}}}}}}}}}}}}}}}}}  ##  }}}}}.....   .....   
       .......   }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}...#####..}}}}}}......T....  
     ........}}}}}    }}}}}}}}}}}}}}}}}}}}}}}}....        .}}}}}}}}}}}}}}}}} 
     .........}         ..}}}}}}   }}}}}}}T.....           ..}}}}}}}}}}}}}}} 
      .......       ##H.....         ........T      ....     ..}}}}}}}}}}}}} 
         .....########     ####         #          ......      ...........T  
                              ###########           .....###H#........       
                                                                             
]]);

-- Altar to Nodens
des.altar({ x=35,y=10,align="noalign", type="shrine", cracked=nh.rn2(2) })

-- Dungeon Description
des.region(selection.area(00,00,75,19),"lit")
des.region(selection.area(04,02,08,04),"lit")
des.region(selection.area(05,12,17,15),"unlit")
des.region(selection.area(34,01,48,02),"unlit")
des.region(selection.area(58,01,65,04),"unlit")
des.region(selection.area(69,01,74,07),"unlit")
des.region(selection.area(51,16,56,18),"unlit")

-- Stairs
des.levregion({ region={72,02,72,02}, type="branch" });

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Sea monsters for the lake
des.monster(";", 63,13)
des.monster(";", 28,07)
des.monster(";", 22,10)
des.monster(";", 59,14)
des.monster(";", 39,06)
des.monster(";", 26,15)
des.monster("electric eel", 53,08)
des.monster("electric eel", 45,14)
des.monster(";", 29,12)
des.monster(";", 30,12)
des.monster(";", 28,11)
des.monster(";", 52,10)
des.monster(";", 69,15)

-- 'Trices living on the island
des.monster({ id = "cockatrice", x=34,y=09 })
des.monster({ id = "pyrolisk", x=42,y=10 })
des.monster(";",38,11)
des.monster(";",39,09)
des.monster(";",34,10)
des.monster(";",43,10)

-- And some (empty) decorations
des.object({ id = "statue", x=33, y=10, contents = 0 })
des.object({ id = "statue", x=35, y=09, contents = 0 })
des.object({ id = "statue", x=44, y=10, contents = 0 })
des.object({ id = "statue", x=36, y=11, contents = 0 })

-- And even some treasure
if percent(50) then
    des.object({ id = "chest", locked = 1, x = 39, y = 10 ,
                 contents = function()
                    des.object({ id = "magic lamp", buc = "cursed" });
                    des.object("potion of oil")
                 end
    });
else
    -- Ruins of a library
    des.object({ id = "chest", locked = 1, x = 38, y = 10 ,
                 contents = function()
                    des.object({ id = "magic marker", buc = "random" });
                    if percent(50) then
                        des.object("scroll of blank paper");
                    end
                    if percent(50) then
                        des.object("scroll of blank paper");
                    end
                    if percent(50) then
                        des.object("spellbook of blank paper");
                    end
                    if percent(50) then
                        des.object("spellbook of blank paper");
                    end
                 end
    });
end

-- Byakhee in the big caves
des.monster({ id = "byakhee", x=09,y=14, peaceful = 0 })
des.monster({ id = "byakhee", x=12,y=15, peaceful = 0 })
des.monster({ id = "byakhee", x=09,y=16, peaceful = 0 })
des.monster({ id = "byakhee", x=11,y=12, peaceful = 0 })
des.monster({ id = "byakhee", x=14,y=14, peaceful = 0 })

-- A little loot
des.object("luckstone", 05,15)
des.object("*", 05,14)
des.object("*", 07,13)
des.object("*", 08,16)
des.object({ x = 11, y = 13 })
des.object({ x = 12, y = 16 })
des.object({ x = 06, y = 15 })
des.object({ x = 09, y = 13 })

-- And a door bell
des.trap("board",12,10)
des.trap("board",17,17)

-- A sweeper upper...
des.monster("ochre jelly",12,16)
des.monster("ochre jelly",08,12)

-- A few random flapping things
des.monster("vampire bat")
des.monster("raven")
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")

-- Vampire the first
des.monster({ id = "vampire", x=62,y=03, peaceful = 0 })
des.object("potion of speed", 62,03)

-- Minions
des.monster({ class = "o", x=62,y=04, peaceful = 0 })
des.monster({ class = "o", x=62,y=02, peaceful = 0 })
des.monster({ class = "o", x=61,y=03, peaceful = 0 })
des.monster({ class = "o", x=63,y=03, peaceful = 0 })

-- And his door bells
des.trap("board",62,05)
des.trap("board",56,02)

-- Hidden in the corridor
des.object({ id = "leather armor", x=47,y=04, buc="cursed", spe=-2 })

-- Zombie beyond
des.monster("Z",46,01)
des.monster("Z",44,01)
des.monster("Z",42,01)
des.monster("Z",40,01)
des.monster("Z",38,01)
des.monster("Z",36,01)

-- The fountain room
des.monster({ id = "vampire lord", x=05,y=03, peaceful = 0 })
des.object({ id = "scroll of create monster", x=06,y=06, buc="cursed" })
des.object({ id = "potion of full healing", x=06,y=06 })

-- Slaves
des.monster({ id = "vampire", x=06,y=03, peaceful = 0 })
des.monster({ id = "vampire", x=04,y=03, peaceful = 0 })
des.monster({ id = "vampire", x=05,y=02, peaceful = 0 })
des.monster({ id = "vampire", x=05,y=04, peaceful = 0 })

-- Door bell
des.trap("board",10,03)

-- Loot
des.object("scroll of teleportation", 06,06)
--des.object("potion of amnesia", 06,06)
des.object("potion of reflection", 06,06)
des.object("potion of sickness", 06,06)

-- Real loot
des.object('chest', 06,08)
des.gold({ x = 06, y = 08, amount = 300 + math.random(0, 300) });

-- Stray Vampire
des.monster({ id = "vampire lord", x=53,y=17, peaceful = 0 })
des.object("wand of fire", 53,17)
des.object("wand of slow monster", 53,17)

-- Guardians
des.monster({ id = "warg", x=54,y=17, peaceful = 0 })
des.monster({ id = "warg", x=52,y=18, peaceful = 0 })
des.monster({ id = "winter wolf", x=53,y=16, peaceful = 0 })
des.monster({ id = "winter wolf", x=52,y=17, peaceful = 0 })

-- Loot
des.gold({ x = 51, y = 17, amount = 300 + math.random(0, 300) });
des.gold({ x = 52, y = 16, amount = 300 + math.random(0, 300) });
des.object({ x = 52, y = 17 })
des.object({ x = 53, y = 16 })

-- Random traps
des.trap("rust")
des.trap("magic")
des.trap("magic")
des.trap("pit")
des.trap("pit")
des.trap()
des.trap()
des.trap()