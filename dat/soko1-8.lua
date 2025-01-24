--
-- "Running Rings Around"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
       ----        
    ----..----     
    |........|     
  ---.|......|     
  F...|......|     
  F....-..-..----- 
  --.............| 
   |..-....--....| 
   |.....----....| 
   |---|.|-------| 
 ---|  |.||.....---
 |..----..|.....+.|
 |........|.....|-|
 |.|------|.....+.|
-|.|      |.....|-|
F..|------|.....+.|
F.........+.....|--
-----------------  
]]);

des.stair("down",05,04)
des.region(selection.area(00,00,18,17),"lit");
des.non_diggable(selection.area(00,00,18,17));
des.non_passwall(selection.area(00,00,18,17));

-- Doors
des.door("locked", 16,11)
des.door("locked", 16,13)
des.door("locked", 16,15)
des.door("locked", 10,16)

-- Boulders
des.object("boulder", 06,02)
des.object("boulder", 09,03)
des.object("boulder", 11,03)
des.object("boulder", 08,04)
des.object("boulder", 10,04)
des.object("boulder", 05,05)
des.object("boulder", 08,05)
des.object("boulder", 09,05)
des.object("boulder", 12,05)
des.object("boulder", 07,06)
des.object("boulder", 14,06)
des.object("boulder", 05,07)
des.object("boulder", 07,07)
des.object("boulder", 08,07)
des.object("boulder", 09,07)
des.object("boulder", 13,07)
des.object("boulder", 15,07)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 08,09, 08,10 } });
des.trap("hole", 08,09)
des.trap("hole", 08,10)
des.exclusion({ type = "monster-generation", region = { 04,12, 07,12 } });
des.trap("hole", 04,12)
des.trap("hole", 05,12)
des.trap("hole", 06,12)
des.trap("hole", 07,12)
des.exclusion({ type = "monster-generation", region = { 02,13, 02,15 } });
des.trap("hole", 02,13)
des.trap("hole", 02,14)
des.trap("hole", 02,15)
des.exclusion({ type = "monster-generation", region = { 03,16, 09,16 } });
des.trap("hole", 03,16)
des.trap("hole", 04,16)
des.trap("hole", 05,16)
des.trap("hole", 06,16)
des.trap("hole", 07,16)
des.trap("hole", 08,16)
des.trap("hole", 09,16)

des.monster({ id = "giant mimic", appear_as = "obj:boulder" });
des.monster({ id = "giant mimic", appear_as = "obj:boulder" });

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- Rewards
des.region({ region={11,10,15,16}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

-- Ice must be created after the zoo, otherwise it interferes with monster creation.
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Rewards

local place = selection.new();
place:set(17,11);
place:set(17,13);
place:set(17,15);

local pt = selection.rndcoord(place);


des.object({ id = "sack", coord = pt, buc="uncursed",
             contents = function()
                des.object({ id = "magic marker" })
                des.object({ id = "ring of teleport control" })
                des.object({ id = "ring of polymorph control" })
                if percent(75) then
                    des.object("=")
                end
                if percent(25) then
                   des.object("=")
                end

             end
});

des.engraving({ coord = pt, type = "burn", text = "Elbereth" });
des.object({ id = "scroll of scare monster", coord = pt, buc = "cursed" });

-- Ruling steward of Sokoban
des.monster({ id = "Wintercloak", x = 11, y = 16, waiting = 1 });
