--
-- "Ringing Endorsement"
-- Ported from NetHack Fourk
-- Converted to lua by hackemslashem
--

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
--------      -------------- 
|...|..|---   |............| 
|......F..|   |...--------+--
--.--..|..---F--.--   |.....|
 |.....--...|..|.|  --|.....|
 |.|....|......|.|  |.+.....|
 |...|.....---.|.|  |-|.....|
 |.....--..---.|.|  |.+.....|
 ---...F.......|.|  |-|.....|
   ---.|...--..|.|  |.+.....|
    |......||....|  --|.....|
    |.....-----..|    |.....|
    -------   ----    -------
]]);

des.stair("down",08,03)
des.region(selection.area(00,00,28,12),"lit");
des.non_diggable(selection.area(00,00,28,12));
des.non_passwall(selection.area(00,00,28,12));

-- Doors
des.door("locked", 26,02)
des.door("locked", 22,05)
des.door("locked", 22,07)
des.door("locked", 22,09)

-- Boulders
des.object("boulder", 02,02)
des.object("boulder", 05,03)
des.object("boulder", 04,04)
des.object("boulder", 06,04)
des.object("boulder", 09,04)
des.object("boulder", 06,05)
des.object("boulder", 10,05)
des.object("boulder", 03,06)
des.object("boulder", 06,06)
des.object("boulder", 10,07)
des.object("boulder", 05,08)
des.object("boulder", 10,08)
des.object("boulder", 10,09)
des.object("boulder", 07,10)
des.object("boulder", 08,10)

-- Traps
-- prevent monster generation over the (filled) pits
des.exclusion({ type = "monster-generation", region = { 18,01, 25,01 } });
des.trap("hole", 18,01)
des.trap("hole", 19,01)
des.trap("hole", 20,01)
des.trap("hole", 21,01)
des.trap("hole", 22,01)
des.trap("hole", 23,01)
des.trap("hole", 24,01)
des.trap("hole", 25,01)
des.exclusion({ type = "monster-generation", region = { 16,04, 16,09 } });
des.trap("hole", 16,04)
des.trap("hole", 16,05)
des.trap("hole", 16,06)
des.trap("hole", 16,07)
des.trap("hole", 16,08)
des.trap("hole", 16,09)

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

des.region({ region={23,03,27,11}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

-- Ice must be created after the zoo, otherwise it interferes with monster creation.
des.replace_terrain({ region={0,0, 75,19}, fromterrain=".", toterrain="I", chance=15 })

-- Rewards

local place = selection.new();
place:set(21,05);
place:set(21,07);
place:set(21,09);

local pt = selection.rndcoord(place);

-- Instead of the standard prize selection, this level guarantees
-- a sack with both control rings, and up to two bonus rings.

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
des.monster({ id = "Wintercloak", x = 26, y = 3, waiting = 1 });
