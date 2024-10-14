--
--	The Undead Stockade for the Lethe branch.
--
--	Upstream to the entry level, downstream to the castle.
--
--MAZE: "leth-c-2",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "hardfloor", "lethe", "noflip")

--0         1         2   	   3	     4	       5		 6	       7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                          }                                                 
          ..      ........}}|.......                                        
       ##....   ...........}|..........           ......        .......     
  H#####  ...  ..T.........}|................#+#...........#+##....\..      
  .             ..........}}|................#+#.....{.....#+##....\.       
 ...             ......    }        T.......    .........       .......     
 ...            ....       }          .....        ....                     
 ....          ...      T}}T         ##..##                     ###.....    
  ...##       ...       }}          ###  ####   #    .....    ###  .......  
      #   .......      }T         ####    ####  +   .......####    .......  
      ............    }}        ....##    ##......   ....           .....   
       ...T}}}}}}}}}}}}}      .......     ..........  +    #                
        }}}}}}}}}}}}}}}}}     .......    ................. +         ....   
       }}}}}}}}}}}}}}}}}}}     .....   #+.....T.............   #### .....   
}}}}}}}}}}}}     T...  }}}}           ..  .......{.....T.....###  ##......  
}}}}}}}}}    ..    H    }}}}       T....    ........T.......      # .....   
}}}}}}}}   .....   #     }}}}}}}}}}}}}}}}   .............         #  ....   
           ......###      }}}}}}}}}}}}}}}}   + + + + + +    ...####         
             ...           }}}}}}}}}}}}}}}}  # # # # # #   ....             
                                        }}}}                                
]]);

-- Some random pets...
local monster = { "D", "Z", "M", "c", "T", "R" };
shuffle(monster)

-- Dungeon Description
des.region(selection.area(00,00,75,19),"lit")
des.region(selection.area(09,01,12,03),"unlit")
des.region(selection.area(01,04,04,08),"unlit")
des.region(selection.area(30,10,36,14),"unlit")
des.region(selection.area(51,08,58,10),"unlit")

-- Pending ability to specify cracked altars
-- des.region({ region={67,07,73,10}, lit=1, type="temple", filled=2 })
-- des.altar({ x=70,y=09,align=random, type="altar" })

des.region(selection.area(68,12,73,16),"unlit")
des.region(selection.area(59,17,62,18),"unlit")

des.region({ region={63,02,70,05},lit=1,type="morgue",filled=0 })

-- Stairs
des.stair("down", 59,18)
des.stair("up", 02,06)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Doors
des.door("locked", 46,03)
des.door("locked", 46,04)
des.door("locked", 60,03)
des.door("locked", 60,04)
--#DOOR: locked, (54,11)
--#DOOR: closed, (48,09)
--#DOOR: closed, (40,13)
--#DOOR: closed, (45,17)
--#DOOR: closed, (47,17)
--#DOOR: closed, (49,17)
--#DOOR: closed, (51,17)
--#DOOR: closed, (53,17)
--#DOOR: closed, (55,17)
--#DOOR: closed, (59,12)

-- The drawbridge
des.drawbridge({dir="east",state="open",x=27,y=03})

-- Lich Kings Throne Room
-- The King
des.monster("master lich", 66,03)
des.object("wand of death", 66,03)
-- The Queen
des.monster("lich", 66,04)
des.object("wand of lightning", 66,04)

-- The Guards
des.monster("ettin mummy", 65,02)
des.monster("ettin mummy", 67,02)
des.monster("ettin mummy", 65,04)
des.monster("ettin mummy", 67,04)

-- A petitioner or two
des.monster("ghoul", 65,03)

-- des.monster("ghoul magii", 65,04)      # (original lethe patch)
-- des.monster("gnoll ghoul"), (65,04) # (from dnh)
des.monster("ghoul mage", 65,04)

-- His treasure
des.object("chest", 70,02)
des.object("chest", 70,05)

-- A few mummies
des.monster("human mummy", 39,05)
des.monster("human mummy", 45,12)
des.monster("elf mummy", 54,14)
des.monster("elf mummy", 54,09)
des.monster("elf mummy", 70,14)

-- Compound guards
des.monster("giant zombie", 30,01)
des.monster("giant zombie", 30,04)
des.monster("Z", 33,02)
des.monster("Z", 34,02)
des.monster("Z", 48,03)
des.monster("Z", 48,04)

-- Temple guard
des.monster("skeleton", 56,09)

-- A surprise for those being nosy
des.monster("electric eel", 25,08)

-- Some doggies...
des.monster("hell hound", 39,03)
des.monster("hell hound", 43,12)
des.monster("hell hound", 53,15)
des.monster("hell hound", 50,11)

-- ...and a nasty ratty
des.monster("wererat", 61,18)

-- In the compound
des.monster(monster[1], 31,11)
des.monster(monster[1], 33,13)
des.monster(monster[1], 34,11)

-- Hidden over the river
des.monster(monster[2], 13,17)
des.monster(monster[2], 14,15)
des.monster(monster[2], 15,18)

des.object("*", 13,17)
des.object("!", 15,16)
des.object("?", 14,15)

-- Some things in the store room...
des.object("%", 69,12)
des.object("%", 70,12)
des.object("%", 71,13)
des.object("(", 72,14)
des.object("%", 70,13)
des.object(")", 71,13)
des.object("%", 72,13)
des.object("%", 71,14)
des.object("(", 72,14)
des.object("%", 70,15)
des.object("%", 71,15)
des.object("%", 72,15)
des.object("(", 69,16)
des.object("%", 70,16)
des.object("%", 71,16)
des.object("[", 72,16)

des.monster("cave spider", 71,14)
des.monster("cave spider", 72,13)
des.monster("cave spider", 70,16)
des.monster("cave spider", 69,12)
des.monster({ id = "giant mimic", x=73, y=14, appear_as = "ter:staircase down" })

-- A little trap...
des.trap("level teleport",51,18)
des.trap("spiked pit",24,02)
des.trap("spiked pit",22,03)
des.trap("spiked pit",19,02)
des.trap("grease")
des.trap("magic beam")
des.trap("spear")

-- Fishes in the river...
des.monster("giant eel", 09,13)
des.monster("giant eel", 33,17)
des.monster("shark", 22,12)
des.monster("kraken", 17,12)

-- A few random monsters to finish things off
des.monster("human mummy")
des.monster("human mummy")
des.monster("elf mummy")
des.monster("elf mummy")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")
des.monster("Z")

-- Essential tools (assume they have a wand of striking)
des.object({ id = "scroll of earth", x=10,y=03, buc="blessed" })

-- Random items (from dnh)
des.object()
des.object()
des.object()
if percent(50) then
    des.object()
end
if percent(50) then
    des.object()
end
if percent(50) then
    des.object()
end
if percent(25) then
    des.object()
end
if percent(25) then
    des.object()
end
if percent(25) then
    des.object()
end
