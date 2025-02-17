--
--
-- The New Baalzebub level
--
-- Ported from SpliceHack
-- Original design seems to come from the Lethe Patch, author unknown.
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel")
des.map([[
      }}   }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}                  
  ..}}...} ...}}....}}}}.....}}...}}.}..}.}.}....}}.}  }}.}}...    .....    
 .}}..}}}..}}}...}}}....}}.F...}}}..}.}}.}.}..F.}..}.}}}...  }}. #.......   
 }..  }}}}}}}}.F.}}}}}}}}FFF}}}}}}}}}}}}}}}FFFF}}}}.}....}}.}... # ......   
 .}}}}}}}}}}}}}FFFF}}}}}}F}}}------------}}F}}}}}}}}.}}.}..... }.#          
  .}}}FFFFFF}}}}}}F}}--------|..........|FFF}}}}}}}}}}.....}}}...  .}...    
 .}}}}F....F}}-------|...........--------------}}}}}}}}}}.....  }... .}.}   
 }.}---....|--|..................S............|----}}}}}...}.} ...}......   
 ..}|...--....S..----------------|..........\.S...|}}}}}}}.....}}...  }..}  
 .}}---....|--|..................|............|----}}}}}}}}}.....}}.....}.  
  .}}}F....F}}-------|...........-----S--------}}}}}}}}}.....}}.....} }..   
 .}.}}FFFFFF}}}}}}F}}--------|..........|FFF}}}}}}}}  }....}..}}..  ....}}  
 }.}.}}}}}}}}}}FFFF}}}}}F}}}}------------}}F}}}}}}}   ..}}...}...}... }.    
 }}.}.}}}}}}}}.F.}}}}}}}FFF}}}}}}}}}}}}}}}}FFFF}}... }...}.....}}.}} ...}   
  .  }..}}}}}}...}}}}}}}}.F.}}}}}....}}}}}}}}.F....}...}...}....}...} ...}  
 }}. . ..}}}}}}}.}}}}...}...}}...}}....}}}}}}...}}..}....}...}...}}...}     
 }..}.}.}..  .}.}.}...}..}}...}}...}}}...}}...}.....}.}..}...}}..}  .}..    
 }}..}.}.}.. }.}.}.}..}.}.}}....}}}...}}}....}}...}}......}}... .}} .....   
   }}.}}..}}..}}}...}...}}....}}}}}}}}....}}......}....}}}..}}.}......      
      }}}   }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}    }}}          
]]);
-- Regions
des.region(selection.area(00,00,75,19), "unlit")
des.region(selection.area(68,01,72,03), "lit")

-- Stairs
des.stair("up", 69,02)
des.stair("down", 48,08)

des.levregion({ region = {16,15,75,19}, exclude = {00,00,00,00}, type="branch" })
des.teleport_region({region={16,15,75,19}})

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Doors
des.door("locked",14,08)
des.door("locked",38,10)
des.door("locked",33,07)
des.door("locked",46,08)

-- Drawbridges
des.drawbridge({dir="east",state="closed",x=03,y=08})

-- The fellow in residence
des.monster({id="Baalzebub", x=44, y=08})

-- Some random weapons and armor.
des.object("[")
des.object("[")
des.object(")")
des.object(")")
des.object("*")
des.object("!")
des.object("?")

-- Some traps.
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("fire")
des.trap("fire")
des.trap("sleep gas")
des.trap("sleep gas")
des.trap("anti magic")
des.trap("anti magic")
des.trap("rust")
des.trap("rust")
des.trap("rust")
des.trap("magic")
des.trap("magic")
des.trap("magic")
des.trap("magic")

-- Random monsters.
des.monster({id="ghost", x=39, y=08})
des.monster({id="horned devil", x=29, y=06})
des.monster({id="barbed devil", x=29, y=10})
des.monster("weredemon")
des.monster("L")
des.monster("ghost")
des.monster("ghost")
des.monster("shade")
des.monster("shade")
des.monster("&")
des.monster("&")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("horned devil")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")
des.monster("lemure")

-- Some Vampires for good measure
des.monster("V")
des.monster("V")
des.monster("V")

-- And a few blobby things, borrowed from Big J.
des.monster("F")
des.monster("F")
des.monster("F")
des.monster({id="green slime",name="Glurrz, emissary of Juiblex"})
des.monster("P")
des.monster("P")
des.monster("P")
