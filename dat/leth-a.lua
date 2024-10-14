-- Lethe Patch
-- -----------
--
-- Mik Clarke, Janrary 21st, 2001
--
--	The head of the river.
--
--	The river starts at the top of the gorge with a big pool.
--	There are a few interesting things hidden around the place.
--
-- MAZE: "leth-a",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "hardfloor", "temperate", "noflip")

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
-- TODO: Add this if we can customize it as cracked
--des.altar({ x=35,y=10,align="noalign", type="shrine" })

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

-- A little loot
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

-- Sea monsters for the lake
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")

des.monster("electric eel", 53,08)
des.monster("electric eel", 45,14)
des.monster("jellyfish")
des.monster("jellyfish")
des.monster(";")
des.monster(";")
des.monster(";")

if percent(50) then
    des.monster("thing from below")
end

-- Original lethe patch has winged gargoyles
-- Nightgaunts living on the island
des.monster("nightgaunt", 34,09)
des.monster("nightgaunt", 42,10)
des.monster("nightgaunt", 38,11)
des.monster("nightgaunt", 39,09)
des.monster("nightgaunt", 34,10)
des.monster("nightgaunt", 43,10)

des.monster({ id = "nightgaunt", x=35,y=10, asleep = 1})
des.monster({ id = "nightgaunt", x=42,y=09, asleep = 1})
des.monster({ id = "nightgaunt", x=38,y=09, asleep = 1})
des.monster({ id = "nightgaunt", x=40,y=11, asleep = 1})

-- And some (empty) decorations
des.object({ id = "statue", x=33, y=10, contents = 0 })
des.object({ id = "statue", x=35, y=09, contents = 0 })
des.object({ id = "statue", x=44, y=10, contents = 0 })
des.object({ id = "statue", x=36, y=11, contents = 0 })

-- And even some treasure
des.object({ id = "chest", locked = 1, x = 39, y = 10 ,
             contents = function()
                -- Original patch has a magic lamp, not in NerfHack...
                -- des.object("magic lamp");
                des.object("oil lamp");
                des.object("potion of oil")
             end
});

-- Ruins of a library (from dnh)
des.object("magic marker")
if percent(50) then
    des.object("scroll of blank paper", 37,10)
end
if percent(50) then
    des.object("scroll of blank paper", 37,10)
end
if percent(50) then
    des.object("scroll of blank paper", 41,11)
end
if percent(50) then
    des.object("scroll of blank paper", 41,11)
end

-- A few random flapping things
des.monster("vampire bat")
des.monster("raven")
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")

-- Random traps
des.trap("board", 10,12)
des.trap("rust")
des.trap("rust")
des.trap("rust")
des.trap("pit")
des.trap("pit")
des.trap("grease")
des.trap("magic beam")
des.trap("spear")
des.trap()
des.trap()
des.trap()
-- door bells
des.trap("board", 10,03)
des.trap("board", 12,10)
des.trap("board", 17,17)
des.trap("board", 62,05)
des.trap("board", 56,02)

-- Hidden in the corridor
if percent(50) then
    des.object({ id = "leather armor", x=47,y=04, buc="blessed", spe=2 })
end
if percent(50) then
    des.object({ id = "leather armor", x=47,y=04, buc="cursed", spe=-2 })
end

-- The fountain room
if percent(50) then
    des.monster({ id = "clay golem", x=04,y=03, asleep = 1})
    des.monster({ id = "clay golem", x=07,y=03, asleep = 1})
    des.object({ id = "scroll of teleportation", x=06,y=06, buc="cursed" })
    des.object({ id = "scroll of amnesia", x=06,y=06 })
else
    des.monster({ id = "vampire noble", x=05,y=03, asleep = 1, peaceful = 0 })
    des.object({ id = "scroll of create monster", x=06,y=06, buc="cursed" })
    des.object("potion of full healing", 06,06)
end

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
