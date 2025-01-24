-- NetHack sokoban soko1-1.lua	$NHDT-Date: 1652196034 2022/05/10 15:20:34 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.6 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- "J Franklin Mentzer <wryter@aol.com>"
-- https://nethackwiki.com/wiki/Sokoban_Level_4d
-- Ported from SpliceHack, original source SLASH'EM
-- Converted to lua by Kestrel Gregorich-Trevor
--
-- NerfHack enlarged the zoo slightly
--
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
------------      
|.+........F      
|-|........-------
|.+........+.....|
|-|........----..|
|.+........F  |.--
|-------------|.| 
|.....|...|...|.| 
|.............|.| 
|....------.|.|.| 
|....|...|....|.| 
|....|.......-|.| 
-----|.--..---|.| 
 |...|.....+..F.| 
 |........-|..F.| 
 |-.----.---FF-.| 
 |..............| 
 |...|...-----..| 
 ---------   ---- 
]]);

des.stair("down", 06, 10);
des.region(selection.area(00,00,17,18),"lit");
des.non_diggable(selection.area(00,00,17,18));
des.non_passwall(selection.area(00,00,17,18));

des.door("locked", 02, 01);
des.door("locked", 02, 03);
des.door("locked", 02, 05);
des.door("locked", 11, 03);
des.door("locked", 11, 13);

-- Boulders
-- des.object("boulder", 02, 08);
des.object("boulder", 03, 08);
des.object("boulder", 06, 08);
des.object("boulder", 10, 08);
des.object("boulder", 12, 08);
des.object("boulder", 03, 09);
des.object("boulder", 02, 10);
des.object("boulder", 03, 10);
des.object("boulder", 12, 10);
des.object("boulder", 08, 11);
des.object("boulder", 06, 12);
des.object("boulder", 07, 13);
des.object("boulder", 06, 14);
des.object("boulder", 04, 16);
des.object("boulder", 08, 16);
des.object("boulder", 09, 16);

-- Traps
-- prevent monster generation over the (filled) holes
-- des.trap("hole", 10, 03);
-- des.trap("hole", 11, 03);
des.exclusion({ type = "monster-generation", region = { 12,03, 14,03 } });
des.trap("hole", 12, 03);
des.trap("hole", 13, 03);
des.trap("hole", 14, 03);
des.exclusion({ type = "monster-generation", region = { 15,05, 15,15 } });
des.trap("hole", 15, 05);
des.trap("hole", 15, 06);
des.trap("hole", 15, 07);
des.trap("hole", 15, 08);
des.trap("hole", 15, 09);
des.trap("hole", 15, 10);
des.trap("hole", 15, 11);
des.trap("hole", 15, 12);
des.trap("hole", 15, 13);
des.trap("hole", 15, 14);
des.trap("hole", 15, 15);

des.monster({ id = "giant mimic", appear_as = "obj:boulder" });
des.monster({ id = "giant mimic", appear_as = "obj:boulder" });

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

des.region({ region={03,01,10,05}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

-- Ice must be created after the zoo, otherwise it interferes with monster creation.
des.replace_terrain({ region={0,6, 75,19}, fromterrain=".", toterrain="I", chance=15 })
des.replace_terrain({ region={3,1, 75,06}, fromterrain=".", toterrain="I", chance=15 })

-- Rewards

place = selection.new();
place:set(01,01);
place:set(01,03);
place:set(01,05);

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
des.monster({ id = "Wintercloak", x = 10, y = 3, waiting = 1 });
