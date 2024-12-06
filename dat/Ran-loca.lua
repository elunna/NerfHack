-- NetHack Ranger Ran-loca.lua	$NHDT-Date: 1652196010 2022/05/10 15:20:10 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor", "noflip")
--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00              .......  .........  .......
01     ...................       ...................
02  ....        .......             .......        ....
03...    .....     .       .....       .     .....    ...
04.   .......... .....  ...........  ..... ..........   .
05.  ..  ..... ..........  .....  .......... .....  ..  .
06.  .     .     .....       .       .....     .     .  .
07.  .   .....         .............         .....   .  .
08.  .  ................  .......  ................  .  .
09.  .   .....            .......            .....   .  .
10.  .     .    ......               ......    .     .  .
11.  .     ...........   .........   ...........     .  .
12.  .          ..........       ..........          .  .
13.  ..  .....     .       .....       .     .....  ..  .
14.   .......... .....  ...........  ..... ..........   .
15.      ..... ..........  .....  .......... .....      .
16.        .     .....       .       .....     .        .
17...   .......           .......           .......   ...
18  ..............     .............     ..............
19      .......  .......  .......  .......  .......
]]);

-- Places the wumpus can appear
places = { {17,01},{37,01},
           {09,04},{17,05},{27,04},{37,05},{45,04},
           {09,08},{27,08},{45,08},
           {17,11},{37,11},
           {09,14},{17,15},{27,14},{37,15},{45,14},
           {09,18},{27,18},{45,18} }
shuffle(places)

-- Dungeon Description
des.region(selection.area(00,00,54,19), "lit")
-- Stairs
des.stair("up", 25,05)
des.stair("down", 27,18)
-- Non diggable walls
des.non_diggable(selection.area(00,00,54,19))
-- Objects
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
-- Random traps
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("teleport")
des.trap("teleport")
des.trap("arrow")
des.trap("arrow")
des.trap("bear")
des.trap("bear")
des.trap("bear")
des.trap("bear")
-- Random monsters.
des.monster({ id = "wumpus", coord = places[1], peaceful=0, asleep=1 })
des.monster({ id = "giant bat", peaceful=0 })
des.monster({ id = "giant bat", peaceful=0 })
des.monster({ id = "giant bat", peaceful=0 })
des.monster({ id = "giant bat", peaceful=0 })
des.monster({ id = "forest centaur", peaceful=0 })
des.monster({ id = "forest centaur", peaceful=0 })
des.monster({ id = "forest centaur", peaceful=0 })
des.monster({ id = "forest centaur", peaceful=0 })
des.monster({ id = "mountain centaur", peaceful=0 })
des.monster({ id = "mountain centaur", peaceful=0 })
des.monster({ id = "mountain centaur", peaceful=0 })
des.monster({ id = "mountain centaur", peaceful=0 })
des.monster({ id = "mountain centaur", peaceful=0 })
des.monster({ id = "mountain centaur", peaceful=0 })
des.monster({ id = "mountain centaur", peaceful=0 })
des.monster({ id = "mountain centaur", peaceful=0 })
des.monster({ id = "scorpion", peaceful=0 })
des.monster({ id = "scorpion", peaceful=0 })
des.monster({ id = "scorpion", peaceful=0 })
des.monster({ id = "scorpion", peaceful=0 })
des.monster({ class = "s", peaceful=0 })
des.monster({ class = "s", peaceful=0 })

