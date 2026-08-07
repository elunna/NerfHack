-- NetHack sokoban soko1-1.lua	$NHDT-Date: 1652196034 2022/05/10 15:20:34 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.6 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "premapped", "solidify", "hot");
des.map([[
ZZZZZZZZZZZZZZZZZZZZZZZZZZ
Z........................Z
Z.......ZZZZZZZZZZZZZZZZ.Z
ZZZZZZZ.ZZZZZZ         Z.Z
 Z...........Z         Z.Z
 Z...........Z         Z.Z
ZZZZZZZZ.ZZZZZ         Z.Z
Z............Z         Z.Z
Z............Z         Z.Z
ZZZZZ.ZZZZZZZZ   ------|.Z
 Z..........Z  --|.....|.Z
 Z..........Z  |.+.....|.Z
 Z.........ZZ  |-|.....|.Z
ZZZZZZZ.ZZZZ   |.+.....+.Z
Z........Z     |-|.....|ZZ
Z........Z     |.+.....|  
Z...ZZZZZZ     --|.....|  
ZZZZZ            -------  
]]);

place = selection.new();
place:set(16,11);
place:set(16,13);
place:set(16,15);

des.ladder("down", 01, 01);
des.region(selection.area(00,00,25,17),"lit");
des.non_diggable()
des.non_passwall()

-- Boulders
des.monster({ id = "boulderer", x=03, y=05, asleep=1 })
des.monster({ id = "boulderer", x=05, y=05, asleep=1 })
des.monster({ id = "boulderer", x=07, y=05, asleep=1 })
des.monster({ id = "boulderer", x=09, y=05, asleep=1 })
des.monster({ id = "boulderer", x=11, y=05, asleep=1 })
--
des.monster({ id = "boulderer", x=04, y=07, asleep=1 })
des.monster({ id = "boulderer", x=04, y=08, asleep=1 })
des.monster({ id = "boulderer", x=06, y=07, asleep=1 })
des.monster({ id = "boulderer", x=09, y=07, asleep=1 })
des.monster({ id = "boulderer", x=11, y=07, asleep=1 })
--
des.monster({ id = "boulderer", x=03, y=12, asleep=1 })
des.monster({ id = "boulderer", x=04, y=10, asleep=1 })
des.monster({ id = "boulderer", x=05, y=12, asleep=1 })
des.monster({ id = "boulderer", x=06, y=10, asleep=1 })
des.monster({ id = "boulderer", x=07, y=11, asleep=1 })
des.monster({ id = "boulderer", x=08, y=10, asleep=1 })
des.monster({ id = "boulderer", x=09, y=12, asleep=1 })
--
des.monster({ id = "boulderer", x=03, y=14, asleep=1 })




-- prevent monster generation over the (filled) holes
des.exclusion({ type = "monster-generation", region = { 08,01, 23,01 } });
-- Traps
des.trap("random", 08, 01);
des.trap("random", 09, 01);
des.trap("random", 10, 01);
des.trap("random", 11, 01);
des.trap("random", 12, 01);
des.trap("random", 13, 01);
des.trap("random", 14, 01);
des.trap("random", 15, 01);
des.trap("random", 16, 01);
des.trap("random", 17, 01);
des.trap("random", 18, 01);
des.trap("random", 19, 01);
des.trap("random", 20, 01);
des.trap("random", 21, 01);
des.trap("random", 22, 01);
des.trap("random", 23, 01);

des.monster({ id = "giant mimic", appear_as = "obj:boulder" });
des.monster({ id = "giant mimic", appear_as = "obj:boulder" });

-- A little help
des.object("earth",01,02)
des.object("earth",01,02)

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

-- Rewards?
des.door("locked", 23, 13);
des.door("closed", 17, 11);
des.door("closed", 17, 13);
des.door("closed", 17, 15);

des.region({ region={18,10, 22,16}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

local pt = selection.rndcoord(place);
des.engraving({ coord = pt, type = "burn", text = "Owlsbreath" });
des.object({ id = "scroll of amnesia", coord = pt, buc = "cursed" });

des.ladder({ dir = "up", coord = pt })
