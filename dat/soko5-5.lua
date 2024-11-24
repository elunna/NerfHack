--
--LEVEL:"soko4-5"
-- "Thinking Rabbit"
-- Ported from UnNetHack
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify");
des.map([[
----             
|..|             
|..------------- 
|..............| 
|-.--FFFFFF---+| 
|..........F...| 
|...|......F...| 
---.|......F...| 
  |.|...|..F...| 
  |.|......F...| 
  |.|.|....F...| 
  |.|....------- 
  |.---..|       
  |....|.|       
  ----...|       
     -----       
]]);

des.levregion({ region = {08,13,08,13}, type = "branch" })
des.stair("up",13,10)
des.region(selection.area(00,00,15,15),"lit");
des.non_diggable(selection.area(00,00,15,15));
des.non_passwall(selection.area(00,00,15,15));

-- Ice
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })
-- No ice on branch location
des.replace_terrain({ region={08,13,08,13}, fromterrain="I", toterrain="." })

-- Doors
des.door("locked", 14,04)

-- Boulders
des.object("boulder", 02,04)
des.object("boulder", 02,05)
des.object("boulder", 04,05)
des.object("boulder", 06,07)
des.object("boulder", 07,07)
des.object("boulder", 09,07)
des.object("boulder", 09,08)
des.object("boulder", 06,09)
des.object("boulder", 07,09)
des.object("boulder", 08,10)
des.object("boulder", 09,10)
des.object("boulder", 07,11)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 03,03, 13,03 } });
des.trap("pit", 03,03)
des.trap("pit", 04,03)
des.trap("pit", 05,03)
des.trap("pit", 06,03)
des.trap("pit", 07,03)
des.trap("pit", 08,03)
des.trap("pit", 09,03)
des.trap("pit", 10,03)
des.trap("pit", 11,03)
des.trap("pit", 12,03)
des.trap("pit", 13,03)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- A little help
des.object("earth",01,01)
if percent(50) then
    des.object("earth",02,01)
end

-- One random mimic
des.monster("m")