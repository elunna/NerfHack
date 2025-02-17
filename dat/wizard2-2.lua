-- NetHack sokoban soko1-2.lua	$NHDT-Date: 1652196034 2022/05/10 15:20:34 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.6 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify");

des.map([[
  WWWWWWWWWWWWWWWWWWWWWWWW
  W......................W
  W..WWWWWWWWWWWWWWWWWWW.W
WWWW.W    WWWWW        W.W
W..W.WW  WW...W        W.W
W.....W--W....W        W.W
W.....W..W....W        W.W
WW....W......WW        W.W
 W.......W...W   ------|.W
 W....W..W...W --|.....|.W
 W....W--W...W |.+.....|.W
 W.......W..WW |-|.....|.W
 WWWW....W.WW  |.+.....+.W
    WWW.WW.W   |-|.....|WW
     W.....W   |.+.....|  
     W..W..W   --|.....|  
     WWWWWWW     -------  
]]);

local place = selection.new();
place:set(16,10);
place:set(16,12);
place:set(16,14);

des.ladder("down", 06,15);
des.region(selection.area(00,00,25,16),"lit");
des.non_diggable();
des.non_passwall();

-- Boulders
des.object("boulder",04,04);
des.object("boulder",02,06);
des.object("boulder",03,06);
des.object("boulder",04,07);
des.object("boulder",05,07);
des.object("boulder",02,08);
des.object("boulder",05,08);
des.object("boulder",03,09);
des.object("boulder",04,09);
des.object("boulder",03,10);
des.object("boulder",05,10);
des.object("boulder",06,12);
--
des.object("boulder",07,14);
--
des.object("boulder",11,05);
des.object("boulder",12,06);
des.object("boulder",10,07);
des.object("boulder",11,07);
des.object("boulder",10,08);
des.object("boulder",12,09);
des.object("boulder",11,10);

-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 05,01, 22,01 } });
-- Traps
des.trap("hole",05,01)
des.trap("hole",06,01)
des.trap("hole",07,01)
des.trap("hole",08,01)
des.trap("hole",09,01)
des.trap("hole",10,01)
des.trap("hole",11,01)
des.trap("hole",12,01)
des.trap("hole",13,01)
des.trap("hole",14,01)
des.trap("hole",15,01)
des.trap("hole",16,01)
des.trap("hole",17,01)
des.trap("hole",18,01)
des.trap("hole",19,01)
des.trap("hole",20,01)
des.trap("hole",21,01)
des.trap("hole",22,01)

des.monster({ id = "giant mimic", appear_as = "obj:boulder" });
des.monster({ id = "giant mimic", appear_as = "obj:boulder" });

-- A little help
des.object("earth",06,15)
des.object("earth",06,15)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- Rewards?
des.door("locked",23,12)
des.door("closed",17,10)
des.door("closed",17,12)
des.door("closed",17,14)
des.region({ region={18,09, 22,15}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

local pt = selection.rndcoord(place);
des.engraving({ coord = pt, type = "burn", text = "Owlsbreath" });
des.object({ id = "scroll of amnesia", coord = pt, buc = "cursed" });

des.ladder({ dir = "up", coord = pt })
