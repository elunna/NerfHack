--
-- Steve Melenchuk <smelenchuk@gmail.com>
-- Ported from GruntHack
-- Converted to lua by hackemslashem
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
  -----                        
  F...------  -----   -------  
  |........----...| ---.....|  
 --..--.--.--.....F |.+.....|  
 |................| ---.....|--
--.....--.--....--- |.+.....+.|
F...-----.-----.-   ---.....|.|
|.....--..-----.--  |.+.....|.|
--....---.---....|  ---.....|.|
 ---..---...-....F    ------|.|
   |......-......F          |.|
   F..--...-.....|          |.|
   ------..-----------------|.|
       -......................|
       -...--------------------
       -----                   
]]);

des.stair("down",08,07)
des.region(selection.area(00,00,30,15),"lit");
des.non_diggable(selection.area(00,00,30,15));
des.non_passwall(selection.area(00,00,30,15));

-- Doors
des.door("locked", 28,05)
des.door("closed", 22,03)
des.door("closed", 22,05)
des.door("closed", 22,07)

-- Boulders
des.object("boulder", 04,02)
des.object("boulder", 06,02)
des.object("boulder", 08,02)
des.object("boulder", 16,03)
des.object("boulder", 03,04)
des.object("boulder", 06,04)
des.object("boulder", 12,04)
des.object("boulder", 14,04)
des.object("boulder", 14,05)
des.object("boulder", 02,06)
des.object("boulder", 03,06)
des.object("boulder", 15,07)
des.object("boulder", 04,08)
des.object("boulder", 09,08)
des.object("boulder", 15,08)
des.object("boulder", 15,09)
des.object("boulder", 05,10)
des.object("boulder", 06,10)
des.object("boulder", 12,10)
des.object("boulder", 14,10)
des.object("boulder", 15,10)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 11,13, 28,13 } });
des.trap("hole", 11,13)
des.trap("hole", 12,13)
des.trap("hole", 13,13)
des.trap("hole", 14,13)
des.trap("hole", 15,13)
des.trap("hole", 16,13)
des.trap("hole", 17,13)
des.trap("hole", 18,13)
des.trap("hole", 19,13)
des.trap("hole", 20,13)
des.trap("hole", 21,13)
des.trap("hole", 22,13)
des.trap("hole", 23,13)
des.trap("hole", 24,13)
des.trap("hole", 25,13)
des.trap("hole", 26,13)
des.trap("hole", 27,13)
des.trap("hole", 28,13)

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

des.region({ region={23,02,27,08}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

-- Ice must be created after the zoo, otherwise it interferes with monster creation.
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Rewards

local place = selection.new();
place:set(21,03);
place:set(21,05);
place:set(21,07);

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
des.monster({ id = "Wintercloak", x = 27, y = 5, waiting = 1 });
