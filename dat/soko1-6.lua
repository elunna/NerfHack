--
-- "Collecting Marbles"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
   ------------------------
   |......................|
   |..-------------------.|
 ----.--   ----         |.|
 |.....-----..|         |.|
 |............|         |.|
 --.......F...|         |.|
  --......F...|         |.|
   |.FF--.--.-|   ------|.|
  --...--.....| --|.....|.|
  |...........| |.+.....|.|
  |...---.--.-| |-|.....|.|
  |...|.......| |.+.....+.|
 --.---.......| |-|.....|--
 |............| |.+.....|  
 |....|.......| --|.....|  
 --------------   -------  
]]);

des.stair("down",03,15)
des.region(selection.area(00,00,26,16),"lit");
des.non_diggable(selection.area(00,00,26,16));
des.non_passwall(selection.area(00,00,26,16));

-- Doors
des.door("locked", 24,12)
des.door("closed", 18,10)
des.door("closed", 18,12)
des.door("closed", 18,14)

-- Boulders
des.object("boulder", 03,14)
des.object("boulder", 06,14)
des.object("boulder", 08,14)
des.object("boulder", 10,14)
des.object("boulder", 12,14)
des.object("boulder", 12,13)
des.object("boulder", 09,13)
des.object("boulder", 08,12)
des.object("boulder", 11,12)
des.object("boulder", 03,11)
des.object("boulder", 05,11)
des.object("boulder", 05,09)
des.object("boulder", 04,08)
des.object("boulder", 11,09)
des.object("boulder", 03,04)
des.object("boulder", 04,06)
des.object("boulder", 08,07)
des.object("boulder", 08,05)
des.object("boulder", 11,05)
des.object("boulder", 12,05)
des.object("boulder", 12,06)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 06,01, 23,01 } });
des.trap("hole", 06,01)
des.trap("hole", 07,01)
des.trap("hole", 08,01)
des.trap("hole", 09,01)
des.trap("hole", 10,01)
des.trap("hole", 11,01)
des.trap("hole", 12,01)
des.trap("hole", 13,01)
des.trap("hole", 14,01)
des.trap("hole", 15,01)
des.trap("hole", 16,01)
des.trap("hole", 17,01)
des.trap("hole", 18,01)
des.trap("hole", 19,01)
des.trap("hole", 20,01)
des.trap("hole", 21,01)
des.trap("hole", 22,01)
des.trap("hole", 23,01)

des.monster({ id = "giant mimic", appear_as = "obj:boulder" });
des.monster({ id = "giant mimic", appear_as = "obj:boulder" });

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });


-- The marbles
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")

-- Rewards

des.region({ region={19,09,23,15}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

-- Ice must be created after the zoo, otherwise it interferes with monster creation.
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Rewards

local place = selection.new();
place:set(17,10);
place:set(17,12);
place:set(17,14);

local pt = selection.rndcoord(place);
local prizes = { { id = "bag of holding" },
                 { id = "amulet of reflection"},
                 { id = "cloak of magic resistance"},
                 { id = "magic marker"} }
shuffle(prizes)
des.object({ id = prizes[1].id, coord=pt, buc="not-cursed", achievement=1 });
des.engraving({ coord = pt, type = "burn", text = "Elbereth" });
des.object({ id = "scroll of scare monster", coord = pt, buc = "cursed" });

-- Ruling steward of Sokoban
des.monster({ id = "Wintercloak", x = 23, y = 12, waiting = 1 });
