--
-- "Back At Ya"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
   --F-- ---------     -------
----...--|..|-...---- --.....F
|........|..|.......---.....--
F...........................| 
|.---|.|-----.....---......-- 
|.|  |.|    --....F --.....|  
|.|  |.|--   ------  |-----|  
|.---|...|           |.....|--
|........|           |.....+.|
|...|...-------------|.....|-|
---F|................+.....+.|
    -----------------|.....|-|
                     |.....+.|
                     |.....|--
                     -------  
]]);

des.stair("down",09,03)
des.region(selection.area(00,00,29,14),"lit");
des.non_diggable(selection.area(00,00,29,14));
des.non_passwall(selection.area(00,00,29,14));

-- Doors
des.door("locked", 27,08)
des.door("locked", 21,10)
des.door("locked", 27,10)
des.door("locked", 27,12)

-- Boulders
des.object("boulder", 02,02)
des.object("boulder", 05,02)
des.object("boulder", 10,02)
des.object("boulder", 14,02)
des.object("boulder", 17,02)
des.object("boulder", 26,02)
des.object("boulder", 10,03)
des.object("boulder", 15,03)
des.object("boulder", 16,03)
des.object("boulder", 19,03)
des.object("boulder", 23,03)
des.object("boulder", 26,03)
des.object("boulder", 14,04)
des.object("boulder", 23,04)
des.object("boulder", 25,04)
des.object("boulder", 26,04)
des.object("boulder", 02,08)
des.object("boulder", 04,08)
des.object("boulder", 07,08)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 06,02, 06,07 } });
des.trap("hole", 06,02)
des.trap("hole", 06,03)
des.trap("hole", 06,04)
des.trap("hole", 06,05)
des.trap("hole", 06,06)
des.trap("hole", 06,07)
des.exclusion({ type = "monster-generation", region = { 08,10, 19,10 } });
des.trap("hole", 08,10)
des.trap("hole", 09,10)
des.trap("hole", 10,10)
des.trap("hole", 11,10)
des.trap("hole", 12,10)
des.trap("hole", 13,10)
des.trap("hole", 14,10)
des.trap("hole", 15,10)
des.trap("hole", 16,10)
des.trap("hole", 17,10)
des.trap("hole", 18,10)
des.trap("hole", 19,10)

des.monster({ id = "giant mimic", appear_as = "obj:boulder" });
des.monster({ id = "giant mimic", appear_as = "obj:boulder" });

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- A pun on the name of the level:
des.object("ya")
des.object("ya")
des.object("ya")
des.object("ya")
des.object("ya")
des.object("ya")
des.object("ya")
des.object("ya")

-- Rewards
des.region({ region={22,07,26,13}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

-- Ice must be created after the zoo, otherwise it interferes with monster creation.
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Rewards

local place = selection.new();
place:set(28,08);
place:set(28,10);
place:set(28,12);

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
des.monster({ id = "Wintercloak", x = 22, y = 10, waiting = 1 });
