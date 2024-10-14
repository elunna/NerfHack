--
--	The gates of Gehennom.
--
--	The river flows through an impressive gates guarded by angels and
--	demons and thence into the depths of Gehennom itself.
--
--MAZE: "leth-z",' '

des.level_init({ style="mazegrid", bg ="-" });
des.level_flags("mazelevel", "noteleport", "noflip")

--0         1         2   	  3	      4	    5		  6	      7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                                        ---------           
        .....                                           |.......|    }      
      .....T...                                   }     |.......|   }}}     
     .........T..........T..              .      .}}    |.......|  .}}      
    ..T........................           ...   ...}}}  |.......| ...}      
    ......T....          .T.....T..      ..T.. .....}...|.......|....       
-----........    -------      .........T...... .........--+-+-+--....       
|...|......      |..\..|         ..T........-----...................        
|...+.....   ----|.....---------  .......T..|   |................-----------
|...|...T    |...+.....+.......|   .........-----........}.......|.....|...|
-----....    |...------|.......|    T...T...............}}}......+.....S.}.|
    .....H###S...+.....|.......+####....................}}.......|.....|...|
    .T...    |...|\....+.......|    ..T.....-----.........}......-----------
   .......   ----|.....|.......|    T.....T.|   |.............}}}}}}}}      
}}}}}}}}}}}}     ---------------   }}}}}}}}}-----}}}}}}}}}}}}}}}}}}}}}}}    
}}}}}}}}}}}}}}                   }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}   
}}}}}}}}}}}}}}}}}}}           }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}   
        }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}-----}}}}}}}}}}}}}}}}}}}}}}}    
            }}}}}}}}}}}}}}}}}}}}}}}}        |   |             }}}}}}}}      
               }}}}}}}}}}}}}}}}}}}          -----                           
]]);

-- Dungeon Description
-- dnh added these holes
des.trap("trap door", 70,13)
des.trap("trap door", 72,14)
des.trap("trap door", 73,15)
des.trap("trap door", 73,16)
des.trap("trap door", 72,17)
des.trap("trap door", 70,18)

des.region(selection.area(00,00,46,19),"lit")
des.region(selection.area(47,00,75,19),"unlit")
des.region(selection.area(01,07,03,09),"lit")
des.region(selection.area(14,09,16,12),"unlit")
des.region(selection.area(18,07,22,09),"unlit")
des.region(selection.area(18,11,22,13),"unlit")
des.region({ region={24,09,29,13},lit=1,type="barracks", filled=1 })
des.region({ region={59,01,63,05},lit=0,type="morgue",filled=1 })
des.region(selection.area(66,09,70,11),"unlit")
des.region(selection.area(72,09,74,11),"unlit")

-- Stairs
--BRANCH: (74,10,74,10), (0,0,0,0)
des.stair("up", 02,08)
des.stair("down", 69,10)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Doors
des.door("locked", 04,08)
des.door("locked", 13,11)
des.door("closed", 17,09)
des.door("closed", 17,11)
des.door("closed", 23,09)
des.door("closed", 23,12)
des.door("closed", 31,11)
des.door("closed", 58,06)
des.door("closed", 60,06)
des.door("closed", 62,06)
des.door("locked", 65,10)
des.door("locked", 71,10)

-- Watch Dog
-- des.monster({ id = "Cerberus", x=68,y=10, asleep = 1, peaceful = 0 })

-- Sea monsters for the river
des.monster("giant eel", 03,15)
des.monster("giant eel", 09,15)
des.monster("giant eel", 15,17)
des.monster("electric eel", 24,18)
des.monster("electric eel", 33,17)
des.monster("electric eel", 40,15)
des.monster("electric eel", 51,15)
des.monster("jellyfish", 59,16)
des.monster("jellyfish", 64,14)
des.monster(";", 68,16)
des.monster(";")
des.monster(";")
des.monster(";")

-- Some guards
-- (the original patch has orcs here, but deep ones from dnh are more fitting)
des.monster("deep one", 07,12)
des.monster("deep one", 08,07)
des.monster("deep one", 05,04)
des.monster("deep one", 16,04)
des.monster("deep one", 24,03)
des.monster("deeper one", 31,06)

-- And a few things for them to use

-- TODO: Port potion of amnesia?
-- des.object("potion of amnesia", 20,03)
-- des.object("potion of amnesia", 04,11)

des.object("wand of fire", 05,04)
des.object("wand of lightning", 13,05)
des.object("scroll of create monster", 27,04)
--des.object("demonology", 27,04)

-- Guardians for the dark
-- The original patch has a different set of monsters, but keeping the dnh version.
des.monster({ id = "nightgaunt", x=67,y=04, asleep = 1 })
des.monster({ id = "nightgaunt", x=68,y=05, asleep = 1 })
des.monster({ id = "horned devil", x=53,y=07, asleep = 1 })
des.monster({ id = "horned devil", x=54,y=09, asleep = 1 })
des.monster({ id = "nightgaunt", x=54,y=11, asleep = 1 })
des.monster({ id = "horned devil", x=52,y=13, asleep = 1 })
des.monster({ id = "horned devil", x=50,y=06, asleep = 1 })
des.monster({ id = "barbed devil", x=51,y=09, asleep = 1 })
des.monster({ id = "barbed devil", x=51,y=12, asleep = 1 })
des.monster({ id = "deeper one", x=48,y=10, asleep = 1 })
des.monster({ id = "deeper one", x=48,y=11, asleep = 1 })
des.monster({ id = "deeper one", x=51,y=10, asleep = 1 })

-- Guardians under the hill
des.monster({ id = "deep one", x=18,y=09, asleep = 1 })
des.monster({ id = "deep one", x=19,y=09, asleep = 1 })
des.monster({ id = "deep one", x=20,y=09, asleep = 1 })
des.monster({ id = "deep one", x=21,y=09, asleep = 1 })
des.monster({ id = "deep one", x=22,y=09, asleep = 1 })
des.monster({ id = "deeper one", x=20,y=07, asleep = 1 })

--des.object({ id = "deep long sword", x=20, y=07, buc="cursed", spe=12, name="The Sword of the Deeps" })
des.object({ id = "long sword", x=20,y=07, buc="blessed", spe=2, name = "The Sword of Albion" })

-- Garrison 2
-- Original patch has 5 wizards here, the deep ones seem beter.
des.monster({ id = "deep one", x=19,y=11, asleep = 1 })
des.monster({ id = "deep one", x=21,y=12, asleep = 1 })
des.monster({ id = "deep one", x=22,y=13, asleep = 1 })
des.monster({ id = "deep one", x=19,y=13, asleep = 1 })
des.monster({ id = "deep one", x=18,y=12, asleep = 1 })

des.object("/", 19,11)
des.object("/", 21,12)
des.object("/", 22,13)
des.object("/", 19,13)
des.object("wand of sleep", 18,12)
des.object("wand of lightning", 18,12)
des.object("amulet of life saving", 18,12)
des.object({ id = "ring of protection", x=18, y=12, buc="blessed", spe=3 })

-- Garrison 3
des.monster({ id = "deep one", x=15,y=09, asleep = 1 })
des.monster({ id = "deep one", x=15,y=10, asleep = 1 })
des.monster({ id = "deep one", x=15,y=11, asleep = 1 })
des.monster({ id = "deep one", x=15,y=12, asleep = 1 })
des.monster({ id = "deep one", x=16,y=10, asleep = 1 })

-- A statue for the entrance area
des.object({ id = "statue", x=67,y=15, montype="purple worm", name = "Shudde M'ell", historic=1,
             contents = function()
                des.object({ id = "drum of earthquake", buc="cursed",spe=8 })
             end
});

-- A little still life
des.object({ id = "statue", x=59,y=10, montype="knight", historic=1,
             contents = function()
                des.object({ id = "long sword", buc="blessed", spe=2 })
             end
});
des.object({ id = "statue", x=58,y=09, montype="Angel", historic=1,
             contents = function()
                des.object({ id = "potion of full healing", buc="blessed", spe=0 })
             end
});
des.object({ id = "statue", x=58,y=11, montype="pit fiend", historic=1,
             contents = function()
                des.object({ id = "scroll of taming", buc="blessed", spe=0 })
             end
});

-- A scattering of corpses
des.object({ id="corpse",x=52, y=08,montype="knight" })
des.object({ id="corpse",x=61, y=12,montype="wizard" })
des.object({ id="corpse",x=65, y=07,montype="rogue" })
des.object({ id="corpse",x=62, y=08,montype="priest" })
des.object({ id="corpse",x=56, y=13,montype="ranger" })

-- A few random flapping things
des.monster("vampire bat")
des.monster("vampire bat")
des.monster("vampire bat")
des.monster("raven")
des.monster("raven")
des.monster("B")
des.monster("B")
des.monster("B")
des.monster("B")

-- Random traps
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("rust")
des.trap("rust")
des.trap("magic")
des.trap("magic")
des.trap("magic")
des.trap("grease")
des.trap("magic beam")
des.trap("spear")
des.trap("board",60,08)
des.trap("board",64,10)
des.trap("board",46,10)
des.trap("board",46,11)

des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()

-- (This is from the original patch)
-- An old joke, borrowed from Eric!
des.engraving({ type="engrave", x=15, y=04, text="I did it for the children" })
des.engraving({ type="engrave", x=21, y=03, text="It'll hurt me more than it will you" })
des.engraving({ type="engrave", x=29, y=04, text="I just wanted it to be right" })
des.engraving({ type="engrave", x=32, y=06, text="It wasn't supposed to happen that way" })
des.engraving({ type="engrave", x=35, y=08, text="I wanted to help" })
des.engraving({ type="engrave", x=41, y=09, text="It was her or me" })
des.engraving({ type="engrave", x=40, y=11, text="I thought she would understand" })
des.engraving({ type="engrave", x=44, y=10, text="Now we can be together" })
des.engraving({ type="engrave", x=44, y=11, text="This is for your own good" })
