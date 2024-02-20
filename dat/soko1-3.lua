-- NetHack sokoban soko1-2.lua	$NHDT-Date: 1652196034 2022/05/10 15:20:34 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.6 $
--	Copyright (c) 1998-1999 by Kevin Hugo
-- NetHack may be freely redistributed.  See license for details.
--
-- Ported from NetHack Fourk
-- https://nethackwiki.com/wiki/The_Dragon_of_Bactria

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "premapped", "sokoban", "solidify", "cold");
des.map([[
 -----   ----                  
 |...----|..---       -------  
 |............|   ----|.....|--
--.......|....|   |...+.....+.|
|........|....|   |.--|.....|-|
|........|....|   |.| |.....+.|
|---.------.----  |.| |.....|-|
|.......|......|  |.| |.....+.|
|.......|......|  |.| |.....|--
|..............|  |.| -------  
|.......|.....--  |.|          
|.......|.....|   |.|          
|-.--------...|   |.|          
|-.|      -----   |.|          
|..----------------.|          
|...................|          
------------------..|          
                 ----          
]]);

local place = selection.new();
place:set(29,03);
place:set(29,05);
place:set(29,07);

des.stair("down", 02,12);
des.region(selection.area(00,00,30,17),"lit");
des.non_diggable(selection.area(00,00,30,17));
des.non_passwall(selection.area(00,00,30,17));

des.door("locked",22,03)
des.door("locked",28,03)
des.door("locked",28,05)
des.door("locked",28,07)

-- Boulders
des.object("boulder",02,02);
des.object("boulder",03,02);
des.object("boulder",05,02);
des.object("boulder",08,02);
des.object("boulder",04,03);
des.object("boulder",06,03);
des.object("boulder",05,04);
des.object("boulder",08,04);
des.object("boulder",02,05);
des.object("boulder",06,05);
des.object("boulder",02,07);
des.object("boulder",04,07);
des.object("boulder",05,07);
des.object("boulder",10,07);
des.object("boulder",12,07);
des.object("boulder",03,08);
des.object("boulder",05,08);
des.object("boulder",10,08);
des.object("boulder",12,08);
--
des.object("boulder",02,09);
des.object("boulder",05,09);
des.object("boulder",07,09);
des.object("boulder",11,09);
des.object("boulder",13,09);
--
des.object("boulder",03,10);
des.object("boulder",06,10);
des.object("boulder",07,10);
des.object("boulder",10,10);
des.object("boulder",12,10);
des.object("boulder",02,11);
des.object("boulder",03,11);
des.object("boulder",11,11);

-- Traps
des.trap("hole",19,04)
des.trap("hole",19,05)
des.trap("hole",19,06)
des.trap("hole",19,07)
des.trap("hole",19,08)
des.trap("hole",19,09)
des.trap("hole",19,10)
des.trap("hole",19,11)
des.trap("hole",19,12)

des.trap("hole",02,13)
des.trap("hole",19,13)
des.trap("hole",02,14)
des.trap("hole",19,14)

des.trap("hole",03,15)
des.trap("hole",04,15)
des.trap("hole",05,15)
des.trap("hole",06,15)
des.trap("hole",07,15)
des.trap("hole",08,15)
des.trap("hole",09,15)
des.trap("hole",10,15)
des.trap("hole",11,15)
des.trap("hole",12,15)
des.trap("hole",13,15)
des.trap("hole",14,15)
des.trap("hole",15,15)
des.trap("hole",16,15)
des.trap("hole",17,15)

des.monster({ id = "giant mimic", appear_as = "obj:boulder" });
des.monster({ id = "giant mimic", appear_as = "obj:boulder" });

-- Random objects
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "%" });
des.object({ class = "=" });
des.object({ class = "/" });

des.region({ region={23,02, 27,08}, lit = 1, type = "zoo", filled = 1, irregular = 1 });

-- Ice must be created after the zoo, otherwise it interferes with monster creation.
des.replace_terrain({ region={0,0, 28,19}, fromterrain=".", toterrain="I", chance=50 })

-- Rewards

local pt = selection.rndcoord(place);

if percent(50) then
   des.object({ id="bag of holding", coord=pt,
		buc="not-cursed", achievement=1 });
else
   des.object({ id="amulet of reflection", coord=pt,
		buc="not-cursed", achievement=1 });
end
des.engraving({ coord = pt, type = "burn", text = "Elbereth" });
des.object({ id = "scroll of scare monster", coord = pt, buc = "cursed" });

des.monster({ id = "green dragon",  coord=pt});
