--
--	The entry level for the Lethe branch.
--
--	Upstream to the dragons lair, downstream to the castle.
--
-- MAZE: "leth-b",' '
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "shortsighted", "noteleport", "hardfloor", "temperate", "noflip")

--0         1         2         3         4         5         6         7     
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
                                                                            
   ...            ###.......  ....            ....                          
  .....         ###   ...........           .......####                ...  
  ....      #####    ...}}}}}}}}}}}}}}     .......    ##         ....H....  
  ...   ##H##        .T}}}}}}}}}}}}}}}}     .....      ##       .....  ...  
   #    #   ###     ..}}}}}}}}}}}}}}}}}}       #        #        ...        
   #H####     #     .}}}}    ....    }}}}    ###     ....          ####     
     #        ####..}}}}.     ..      }}}}}..#    ......              #     
     #             }}}}..      #       }}}}}     ........      .......#     
     .  ..}}}}}}}}}}}}..   ..###      ...}}}}      .....    ....T....       
     ....}}}}}}}}}}}}     ...      ##....T}}}}...###       ..}}}}}}}}}}}}}} 
     ..T}}}}}}}}}}}}      .....#      .....}}}}}           .}.}}}}}}}}}}}}} 
     ..}}}}  ....          ...          .....}}}}          }}}.}}}}}}}}}}}} 
    ..}}}}      H           #             ...T}}}}}}}}}}}}}}}}}.            
}}}}}}}}}       .....     ###           ##. ...}}}}}}}}}}}}}}}.    ...      
}}}}}}}}.    ...........  # #  ....     #     . }}}}}}}}}}}}}.    .....     
}}}}}}}.    .............## ##.....     #     #   ....T......    ......     
   .....    ...........       ......#####     ###  ......         #         
            .....  ...         ....             ####  ....####H####         
                                                                            
]]);

-- Dungeon Description
des.region(selection.area(00,00,75,19),"lit")
des.region(selection.area(02,01,06,04),"unlit")
des.region(selection.area(12,14,24,18),"unlit")
des.region(selection.area(26,07,30,10),"unlit")
des.region(selection.area(30,15,35,18),"unlit")
des.region(selection.area(43,01,50,04),"unlit")
des.region(selection.area(49,06,56,09),"unlit")
des.region(selection.area(65,14,70,16),"unlit")
des.region(selection.area(64,03,68,05),"unlit")
des.region(selection.area(70,02,73,04),"unlit")

-- Arrival point
--des.levregion({ region = {32,16,33,17}, type = "branch" })

-- Stairs
des.stair("up", 04,02)
des.stair("down", 72,03)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Objects
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
if percent(75) then
    des.object()
end
if percent(75) then
    des.object()
end
if percent(50) then
    des.object()
end
if percent(25) then
    des.object()
end

-- Random traps
des.trap("rust")
des.trap("rust")
des.trap("rust")
des.trap("rust")
des.trap("grease")
des.trap("magic beam")
des.trap("spear")
des.trap()
des.trap()

des.monster("deeper one")
des.monster("deeper one")
des.monster("deeper one")
des.monster("deeper one")
des.monster("deeper one")
des.monster("deepest one")
des.monster("deepest one")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster(";")
des.monster(";")
des.monster(";")
if percent(50) then
    des.monster("thing from below")
end

-- Random monsters.
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster("B")
des.monster("B")

-- Entry chamber
des.monster("deep one", 31,16)
des.monster("deep one", 31,18)
des.monster("deep one", 33,18)

-- North gate
des.monster("deep one", 28,12)

-- Main chamber
des.monster("deep one", 22,16)
des.monster("deep one", 20,16)
des.monster("deep one", 20,17)
des.monster("deep one", 16,17)
des.monster("deeper one", 18,16)
des.monster("deeper one", 18,17)
des.object("chest" , 14,18)

-- A guard for the bridge
des.monster("electric eel", 62,13)

-- Treasure cave
des.monster({ class = 'T', x=67, y=15, asleep = 1 })
des.monster({ class = 'T', x=69, y=16, asleep = 1 })
des.object("chest" , 68,14)

-- Hard to reach caves
des.object({ id = "potion of water", x=43, y=03, buc="blessed" })
des.object("potion of gain ability", 49,08)
des.monster("iron piercer", 47,03)
des.monster("p", 52,08)