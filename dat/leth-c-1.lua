--
--	The Ogre Stockade for the Lethe branch.
--
--	Upstream to the entry level, downstream to the castle.
--
--MAZE: "leth-c-1",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "hardfloor", "lethe", "noflip")

--0         1         2   	  3	      4	    5		  6	      7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                          }                                                 
          ..      ........}}|.......                                        
  ###  ##....   ...........}|..........           ......        .......     
  H ####  ...  ..T.........}|................#+#...........#+##....\..      
  .    ##...    ..........}}|................#+#.....{.....#+##....\.       
 ...      ...    ......    }        T.......    .........       .......     
 ...     ..     ....      }    }}     .....        ....                     
 ....          ...      T}}} }}}     ##..##                     ###.....    
  ...##       ...       }}} }..     ###  ####   #    .....    ###  .......  
      #   .......      }T   ...   ####    ####  +   .......####    .......  
      ............    }}   .... ....##    ##......   ....           .....   
       ...T}}}}}}}}}}}}}   ..........     ..........  +    #                
        }}}}}}}}}}}}}}}}}   .........    ................. +         ....   
       }}}}}}}}}}}}}}}}}}}    ......   #+.....T.............   #### .....   
}}}}}}}}}}}}     T...  }}}}           ..  .......{.....T.....###  ##......  
}}}}}}}}}    ..    H    }}}}       T....    ........T.......      # .....   
}}}}}}}}   .....   #     }}}}}}}}}}}}}}}}   .............         #  ....   
           ......###      }}}}}}}}}}}}}}}}   + + + + + +    ...####         
             ...           }}}}}}}}}}}}}}}}  # # # # # #   ....             
                                        }}}}                                
]]);

-- Initialize random monsters
local monster = { "D", "H", "q", "c", "T", "R" };
shuffle(monster)

-- Dungeon Description
des.region(selection.area(00,00,75,19),"lit")
des.region(selection.area(09,01,12,03),"unlit")
des.region(selection.area(30,10,36,14),"unlit")
des.region(selection.area(51,08,58,10),"unlit")

des.region({ region={63,02,70,05},lit=1,type="throne", filled=0 })

-- Pending ability to specify cracked altars
-- des.region({ region={67,07,73,10}, lit=1, type="temple", filled=2 })
-- des.altar({ x=70,y=09,align=random, type="altar" })

des.region(selection.area(68,12,73,16),"unlit")
des.region(selection.area(59,17,62,18),"unlit")

-- Stairs
des.stair("down", 59,18)
des.stair("up", 02,06)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- The drawbridge
des.drawbridge({dir="east",state="open",x=27,y=03})

-- Ogre Kings Throne Room
des.monster("ogre royal", 66,03)
des.monster("ogre royal", 66,04)

-- An advisor (original lethe patch has an Ogre Shaman)
--des.monster("ogre shaman", 65,04)
des.monster("ogre mage", 65,04)

-- The Guards
des.monster("spiked orc", 65,02)
des.monster("spiked orc", 67,02)
des.monster("spiked orc", 65,04)
des.monster("spiked orc", 67,04)

-- A petitioner
des.monster("kobold noble", 65,03)

-- His treasure
des.object("chest", 70,02)
des.object("chest", 70,05)

-- A few ogres
des.monster("ogre mage", 39,05)
des.monster("ogre", 45,12)
des.monster("ogre", 54,14)
des.monster("ogre", 54,09)
des.monster("ogre", 70,14)

des.monster("ogre mage")
des.monster("ogre mage")
des.monster("shadow ogre")
des.monster("shadow ogre")
des.monster("shadow ogre")

-- Compound guards
des.monster("ogre", 30,01)
des.monster("ogre", 30,04)
des.monster("ogre", 33,02)
des.monster("ogre", 34,02)
des.object("wand of striking", 34,02)
des.monster("ogre", 48,03)
des.monster("ogre", 48,04)
des.object("wand of fire", 48,04)

-- Temple guard
des.monster("ogre", 56,09)
des.object("wand of sleep", 56,09)

-- A surprise for those being nosy
des.monster("electric eel", 25,08)

-- Some doggies...
des.monster("d", 39,03)
des.monster("d", 43,12)
des.monster("d", 53,15)
des.monster("d", 50,11)

-- ...and a nasty ratty
des.monster("wererat", 61,18)

-- Some random pets...
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

if percent(50) then
    des.object("%", 71,16)
end
if percent(50) then
    des.object("[", 72,16)
end

des.monster("cave spider", 71,14)
des.monster("cave spider", 72,13)
des.monster("cave spider", 70,16)
des.monster("cave spider", 69,12)
des.monster({ id = "giant mimic", x=73, y=14, appear_as = "ter:staircase down" })

-- A little trap...
des.trap("level teleport",51,18)
des.trap("spiked pit", 24,02)
des.trap("spiked pit", 22,03)
des.trap("spiked pit", 19,02)
des.trap("grease")
des.trap("magic beam")
des.trap("spear")

-- Fishes in the river...
des.monster("electric eel", 09,13)
des.monster(";", 33,17)
des.monster(";", 22,12)
des.monster(";", 17,12)

-- A few random monsters to finish things off
des.monster("ogre")
des.monster("ogre")
des.monster("ogre")
des.monster()
des.monster()
des.monster()
des.monster()

-- Essential tools (assume they have a wand of striking)
des.object({ id = "scroll of earth", x=10,y=03, blessed })