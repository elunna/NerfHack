-- Lethe Patch
-- -----------
--
-- Mik Clarke, Janrary 21st, 2001
--
--  The head of the river.
--
--  The river starts at the top of the gorge with a big pool.
--  There are a few interesting things hidden around the place.
--
-- MAZE: "leth-a-1",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "hardfloor", "lethe", "noflip")

--0         1         2         3         4         5         6         7     
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                                                             
   -------                #######H...............#####      ...       ....   
   |.....|               ##         .......   ...    #####.......    ......  
   |..{..+###           ##              #      H     H     .......   .....   
   |.....|  #############  #########.....      .     ##      ....     ...    
   ---S---                 #         ......           ###     #        ....  
      #                ........  }}}}}}}}}}}}}    ....  #     ##     ##....  
                    ........}}}}}}}}}}}}}}}}}}}}}}}T....#      #     #  ..   
             #####H.....T.}}}}}}}}}}}}}}}}}}}}}}}}}}}}...    ###     #       
             #      ...}}}}}}}}}}...........}}}}}}}}}}}}}}   #       ###     
          ####       .}}}}}}}}}}.....T........}}}}}}}}}}}}}  H         #     
          #             }}}}}}}}}}}......T...}}}}}}}}}}}}}}}...        #     
        .....         }}}}}}}}}}}}}}}}}}}}}}}}}}}}  ##  }}}}}.....   .....   
       .......       }}}}}}}}}}}}}}}}}}}}}}}}}}}...#####..}}}}}}......T....  
     ........}}}      }}}}}}}}}}}}}}}}}}}}}}}}....        .}}}}}}}}}}}}}}}}} 
     .........}         ..}}}}}}   }}}}}}}T.....           ..}}}}}}}}}}}}}}} 
      .......       ###.....         ........T      ....     ..}}}}}}}}}}}}} 
         .....########     ####         #          ......      ...........T  
                              ###########           .....###H#........       
                                                                             
]]);

-- Altar to Nodens
if percent(50) then
    des.altar({ x=35,y=10,align="noalign", type="shrine", cracked=nh.rn2(2) })
else
    for i = 1,math.random(8, 17) do
        des.object("rock", 35,10)
     end
end
-- Dungeon Description
des.region(selection.area(00,00,75,19),"lit")
des.region(selection.area(04,02,08,04),"lit")
des.region(selection.area(05,12,17,15),"unlit")
des.region(selection.area(34,01,48,02),"unlit")
des.region(selection.area(58,01,65,04),"unlit")
des.region(selection.area(69,01,74,07),"unlit")
des.region(selection.area(51,16,56,18),"unlit")

-- Stairs
des.stair("down", 72,02)
des.stair("up", 50,17)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Doors
des.door("locked", 09,03)
des.door("locked", 06,05)

-- Dragons
des.monster({ id = "red dragon", x=10, y=13, asleep = 1 })
des.monster({ id = "red dragon", x=11, y=16, asleep = 1 })

-- The Dragons Hoard
des.object("chest", 05,14)
des.object({ id = "egg", x=05, y=15, montype="red dragon" });
des.object({ id = "egg", x=06, y=14, montype="red dragon" });
des.object({ id = "egg", x=06, y=15, montype="red dragon" });
des.object({ id = "egg", x=06, y=16, montype="red dragon" });
des.object({ id = "egg", x=07, y=14, montype="red dragon" });
des.object({ id = "egg", x=07, y=15, montype="red dragon" });
des.object("/", 06,14)
des.object("*", 06,14)
des.object("*", 06,15)
des.object("*", 06,15)
des.object("*", 07,13)
des.object("luckstone", 05,15)

des.gold({ x = 05, y = 14, amount = 300 + math.random(0, 300) });
des.gold({ x = 05, y = 15, amount = 300 + math.random(0, 300) });
des.gold({ x = 06, y = 14, amount = 300 + math.random(0, 300) });
des.gold({ x = 06, y = 15, amount = 300 + math.random(0, 300) });
des.gold({ x = 06, y = 16, amount = 300 + math.random(0, 300) });
des.gold({ x = 07, y = 13, amount = 300 + math.random(0, 300) });
des.gold({ x = 07, y = 14, amount = 300 + math.random(0, 300) });
des.gold({ x = 07, y = 15, amount = 300 + math.random(0, 300) });
des.gold({ x = 07, y = 16, amount = 300 + math.random(0, 300) });
des.gold({ x = 08, y = 15, amount = 300 + math.random(0, 300) });
des.gold({ x = 08, y = 16, amount = 300 + math.random(0, 300) });
des.trap("board", 10,12)

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

-- Gargoyles living on the island
des.monster({ id = "winged gargoyle", x=35,y=10, asleep = 1})
des.monster({ id = "winged gargoyle", x=42,y=10, asleep = 1})
des.monster({ id = "winged gargoyle", x=38,y=09, asleep = 1})
des.monster({ id = "winged gargoyle", x=40,y=11, asleep = 1})

-- And some (empty) decorations
des.object({ id = "statue", x=33, y=10, contents = 0 })
des.object({ id = "statue", x=35, y=09, contents = 0 })
des.object({ id = "statue", x=44, y=10, contents = 0 })
des.object({ id = "statue", x=36, y=11, contents = 0 })

-- And even some treasure
des.object({ id = "chest", locked = 1, x = 39, y = 10 ,
             contents = function()
                -- Original patch has a magic lamp, not in NerfHack...
                des.object("oil lamp");
                des.object("potion of oil")
             end
});

-- A few random flapping things
des.monster("vampire bat")
des.monster("raven")
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")

-- Random traps
des.trap("rust")
des.trap("rust")
des.trap("rust")
des.trap("pit")
des.trap("pit")
des.trap()
des.trap()
des.trap()

-- Hidden in the corridor
if percent(50) then
    des.object({ id = "leather armor", x=47,y=04, buc="blessed", spe=2 })
end
if percent(50) then
    des.object({ id = "leather armor", x=47,y=04, buc="cursed", spe=-2 })
end
-- The fountain room
des.monster({ id = "clay golem", x=04,y=03, asleep = 1})
des.monster({ id = "clay golem", x=07,y=03, asleep = 1})
des.object({ id = "scroll of teleportation", x=06,y=06, buc="cursed" })
des.object({ id = "scroll of amnesia", x=06,y=06 })

-- Second dragon (note; this guy is awake)
des.monster("D", 55,18)

-- Second dragons hoard
des.gold({ x = 51, y = 17, amount = 300 + math.random(0, 300) });
des.gold({ x = 52, y = 17, amount = 300 + math.random(0, 300) });
des.gold({ x = 52, y = 16, amount = 300 + math.random(0, 300) });
des.gold({ x = 53, y = 16, amount = 300 + math.random(0, 300) });

des.object('/', 51,17)
des.object("*", 51,17)
des.object("*", 52,17)
des.object("*", 52,16)
des.object( '*', 53,16)
des.object("scroll of enchant weapon", 52,16)

-- Monsters in the dark
des.monster("trapper", 62,03)
des.monster("lurker above", 43,01)
