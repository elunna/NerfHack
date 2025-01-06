-- Mik Clarke, January 21st, 2001
-- Ported from the Lethe Patch
-- Converted to lua by hackemslashem (with modifications)
--
--  The Lichs Manse
--
--  Upstream to the entry level, downstream to the castle.
--
--MAZE: "leth-d-2",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "hardfloor", "lethe")

--0         1         2         3         4         5         6         7    
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
 ------------------------------------   }}}}              -----             
 |..................................|    }}}}             |...|             
 |..................................|  ..}}}}..           |...|             
 |..................................| ...}}}}...          --+--         ..  
 |..................................|...}}}}}}...|  -----   #          .... 
 |..................................|..}}}}}}}}..|  |...|   #        ##.... 
 |..................................+..}}}}}}}}..+##S...+####        # .... 
 |..................................|..}}}}}}}}..|  |...|            #  ..  
 |..........-----------------------S|...}}}}}}...|  -----            ##     
 |....}}....|.........|..|.|..|.....-------------------  ....         ##    
 |...u}}u...|.........|+--+--+|.....|..........|.|....| ..}}}}}}       H    
 |...u}}u...|.........|.......|.....|............|....S#.}}}}}}}}}}}   ..   
 |...u}}u...|.........|.......|.....|..........|.S....| .}}}}}}}}}}}} ....  
 |...u}}u...-----+--------+------+---..........-----+--  }}}}}}}}}}}}}}}}}}}
 |...u}}u...+.......................+.........\..| |.|    }}}}}}..}}}}}}}}}}
 |...u}}u...-----+--------+------+---..........-----+--      .......}}}}}}}}
 |...u}}u...|.........|.......|.....|..........|.S....|          #          
 |....}}....|.........|.......|.....|............|....S###########          
 |..........|.........|.......|.....|..........|.|....|                     
 ------------------------------------------------------                     
]]);

-- Dungeon Description

des.region(selection.area(02,01,35,07),"lit")
des.replace_terrain({ region={02,01,35,07}, fromterrain=".", toterrain="u", chance=80 })
des.replace_terrain({ region={02,01,35,07}, fromterrain=".", toterrain="P", chance=5 })

des.region({ region={03,02,10,06},lit=1,type="fungusfarm",filled=1 })
des.region({ region={13,01,20,03},lit=1,type="fungusfarm",filled=1 })
des.region({ region={13,05,20,07},lit=1,type="fungusfarm",filled=1 })
des.region({ region={23,02,26,06},lit=1,type="fungusfarm",filled=1 })
des.region({ region={29,01,32,02},lit=1,type="fungusfarm",filled=1 })
des.region({ region={29,04,32,04},lit=1,type="fungusfarm",filled=1 })
des.region({ region={29,06,32,07},lit=1,type="fungusfarm",filled=1 })

des.region(selection.area(02,08,11,18),"lit")
des.region(selection.area(37,01,48,08),"lit")
des.region(selection.area(53,05,55,07),"lit")
des.region(selection.area(59,01,61,02),"lit")
des.region({ region={13,09,21,11},lit=1,type="morgue",filled=1 })

des.region(selection.area(13,16,21,18),"lit")
des.region(selection.area(23,11,29,12),"unlit")
des.region(selection.area(23,09,24,09),"unlit")
des.region(selection.area(26,09,26,09),"unlit")
des.region(selection.area(28,09,29,09),"unlit")
des.region(selection.area(23,16,29,18),"lit")
des.region(selection.area(31,09,35,12),"lit")
des.region(selection.area(31,16,35,18),"lit")
des.region(selection.area(13,14,35,14),"lit")

-- Throne Room, in two parts
des.region({ region={38,10,45,13},lit=1,type="morgue",filled=1 })
des.region({ region={38,15,45,18},lit=1,type="morgue",filled=1 })

des.region(selection.area(48,10,48,12),"lit")
des.region(selection.area(47,14,48,14),"lit")
des.region(selection.area(48,16,48,18),"lit")
des.region(selection.area(50,10,53,12),"unlit")
des.region(selection.area(50,16,53,18),"unlit")
des.region(selection.area(52,14,52,14),"unlit")
des.region(selection.area(56,09,75,15),"lit")
des.region(selection.area(71,03,74,07),"unlit")

-- Stairs
des.stair("down", 73,05)
des.stair("up", 60,01)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Doors
des.door("locked", 60,03)
des.door("locked", 56,06)
des.door("locked", 52,06)
des.door("locked", 49,06)
des.door("locked", 36,06)
des.door("locked", 35,08)
des.door("random", 12,14)
des.door("random", 17,13)
des.door("random", 17,15)
des.door("random", 26,13)
des.door("random", 26,15)
des.door("random", 23,10)
des.door("random", 26,11)
des.door("random", 29,10)
des.door("locked", 33,13)
des.door("random", 33,15)
des.door("locked", 36,14)
des.door("locked", 49,16)
des.door("locked", 49,12)
des.door("locked", 54,11)
des.door("locked", 54,17)
des.door("random", 52,13)
des.door("random", 52,15)

-- Monsters in the garden
des.monster("locust", 02,15)
des.monster("locust", 02,16)
des.monster("locust", 03,15)
des.monster("locust", 03,16)
des.monster({ id = "troll mummy", x=10, y=13  })
des.monster({ id = "troll mummy", x=10, y=15  })

-- Replacement 'trees' in the garden
des.monster({ id = "shrieker", x=03, y=11  })
des.monster({ id = "shrieker", x=10, y=11  })
des.monster({ id = "shrieker", x=03, y=14  })
des.monster({ id = "shrieker", x=10, y=14  })
des.monster({ id = "shrieker", x=03, y=17  })
des.monster({ id = "shrieker", x=10, y=17  })

-- Traps
des.trap("polymorph",35,09)
des.trap("board",35,14)
des.trap("magic",34,06)
des.trap("magic",53,17)

-- Fishes in the river...
des.monster("giant eel", 42,02)
des.monster("giant eel", 44,06)
des.monster("shark", 41,07)
des.monster("giant eel", 59,12)
des.monster("electric eel", 66,12)
des.monster("kraken", 71,15)

-- One security guard
des.monster({ id = "black dragon", x=26, y=11  })

-- Treasure
des.object("chest", 24,09)
des.object("chest", 26,09)
des.object("chest", 28,09)

-- Throne Room Extras
-- Stronger monsters from dnh than the original lethe.
des.monster({ id = "lich", x=45, y=11  })
des.object("wand of lightning", 45,11)
des.object("chest", 48,12)

des.monster("master lich", 46,14)
if percent(25) then
    des.object("wand of cancellation", 46,14)
end

des.trap("magic", 47,14)
des.object("chest", 48,14)
des.monster({ id = "succubus", x=46, y=13  })
des.monster({ id = "succubus", x=46, y=15  })
des.monster({ id = "lich", x=45, y=17  })
des.object("wand of sleep", 45,17)
des.object("chest", 48,16)

-- Decorations
des.object({ id = "statue", x=47, y=08, contents = 0 })
des.object({ id = "statue", x=38, y=08, contents = 0 })
des.object({ id = "statue", x=26, y=18, contents = 0 })

-- Monsters
des.monster()
des.monster()
des.monster()

-- Objects
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()

-- Random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
