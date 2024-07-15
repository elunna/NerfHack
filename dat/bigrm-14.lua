-- NetHack bigroom bigrm-14.lua	$NHDT-Date: 1652196021 2022/05/10 15:20:21 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1990 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Two streams
-- Ported from UnNetHack
-- Converted to LUA by hackemslashem
des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noflip");

des.map([[
        |------------------------       -------------------------        
        |.......................|       |.......................|        
        |.......................|       |................}}.....|        
|-------|......}}}}.............|--------.....}}.}.....}}}}.....--------|
|}}}......}}..}}}}}}..........}}}..........}}}..}.....}....}.}}..}}}}}}}|
|}}}....}}.}}}.....}....}}...}...}}}....}.}...........}.....}}.}}....}}}|
|}}}}}}}............}}}}..}}}.......}}}}}}}............}..............}}|
|}}}}}...............}}...............}}...}............}...........}}}}|
|-------|.......................|--------...}.........}}}.......--------|
        |.......................|       |...}}......}}.}........|        
|--------........LLLL....LL.....--------|....}}...}}............|-------|
|LLL..........LLL.........LLL......LLL........}.}}}}.......LLL.........L|
|LLLL........LLL.............L...LL..LLLLLL....}}.}.....LLL...LLL....LLL|
|LLLLLLLL..LLL.LLLLLL.........LLL......LLLLL.........LLLL........LLLLLLL|
|LLLLLL..LLL........LLL...LLLL............LLLLL..LLLL.LLLLL........LLLLL|
|--------..............LLL......--------|.....LLL....LLLLLL.....|-------|
        |.......................|       |...............LL......|        
        |.......................|       |.......................|        
        -------------------------       -------------------------        
]]);

des.region(selection.area(01,01, 72, 17), "lit");
des.stair("up");
des.stair("down");
des.non_diggable();

for i = 1,15 do
   des.object();
end

des.object("tallow candle")
des.object("tallow candle")

for i = 1,6 do
   des.trap();
end

for i = 1,28 do
  des.monster();
end
