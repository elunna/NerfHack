-- "Open at the Top"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
 ------------------    ----
 |................------..|
 |........................|
 |...........----.-------.|
 |--.---FFFFF|....|     |.|
 |.....|.....|....|     |.|
 |.....|..........|     |.|
 |............-----     |.|
 |.....|......|         |.|
 |.....--.....|         |.|
 -----.--FFF---   ------|.|
  |.........|   --|.....|.|
  |.........|   |.+.....|.|
  |-.----...|   |-|.....|.|
  |........--   |.+.....+.|
  |........|    |-|.....|--
  |.....----    |.+.....|  
  -------       --|.....|  
                  -------  
]]);

des.stair("down",04,15)
des.region(selection.area(00,00,26,18),"lit");
des.non_diggable(selection.area(00,00,26,18));
des.non_passwall(selection.area(00,00,26,18));

-- Doors
des.door("locked", 24,14)
des.door("closed", 18,12)
des.door("closed", 18,14)
des.door("closed", 18,16)

-- Boulders
des.object("boulder", 05,14)
des.object("boulder", 08,15)
des.object("boulder", 09,14)
des.object("boulder", 04,11)
des.object("boulder", 05,12)
des.object("boulder", 07,11)
des.object("boulder", 08,12)
--des.object("boulder", 10,12)
des.object("boulder", 14,06)
des.object("boulder", 13,08)
des.object("boulder", 12,08)
des.object("boulder", 11,06)
des.object("boulder", 10,08)
des.object("boulder", 09,08)
des.object("boulder", 08,06)
des.object("boulder", 06,09)
des.object("boulder", 06,06)
des.object("boulder", 06,07)
des.object("boulder", 03,07)
des.object("boulder", 04,04)
des.object("boulder", 04,03)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 18,02, 24,02 } });
des.trap("hole", 18,02)
des.trap("hole", 19,02)
des.trap("hole", 20,02)
des.trap("hole", 21,02)
des.trap("hole", 22,02)
des.trap("hole", 23,02)
des.trap("hole", 24,02)
des.exclusion({ type = "monster-generation", region = { 25,03, 25,13 } });
des.trap("hole", 25,03)
des.trap("hole", 25,04)
des.trap("hole", 25,05)
des.trap("hole", 25,06)
des.trap("hole", 25,07)
des.trap("hole", 25,08)
des.trap("hole", 25,09)
des.trap("hole", 25,10)
des.trap("hole", 25,11)
des.trap("hole", 25,12)
des.trap("hole", 25,13)

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

des.region({ region={19,11,23,17}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

-- Ice must be created after the zoo, otherwise it interferes with monster creation.
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Rewards

local place = selection.new();
place:set(17,12);
place:set(17,14);
place:set(17,16);

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
des.monster({ id = "Wintercloak", x = 23, y = 14, waiting = 1 });
