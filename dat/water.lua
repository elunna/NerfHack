-- NetHack endgame water.lua	$NHDT-Date: 1652196038 2022/05/10 15:20:38 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1992,1993 by Izchak Miller, David Cohrs,
--                      and Timo Hakulinen
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor", "shortsighted", "noflip")
des.message("You find yourself suspended in an air bubble surrounded by water.")
-- The player lands upon arrival to an air bubble
-- within the leftmost third of the level.  The
-- portal to the next level is randomly located in an air
-- bubble within the rightmost third of the level.
-- Bubbles are generated by special code in mkmaze.c for now.
des.map([[
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
]]);
des.teleport_region({ region = {0,0,25,19} })
des.levregion({ type="portal", region={51,0,75,19}, name="astral" })
-- A fisherman's dream...
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("giant eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("electric eel")
des.monster("kraken")
des.monster("kraken")
des.monster("kraken")
des.monster("kraken")
des.monster("kraken")
des.monster("kraken")
des.monster("kraken")
des.monster("kraken")
des.monster("thing from below")
des.monster("thing from below")
des.monster("thing from below")
des.monster("thing from below")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("deepest one")
des.monster("deepest one")
des.monster("deepest one")
des.monster("deepest one")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster(";")
des.monster(";")
des.monster(";")
des.monster(";")
-- These guys feel like home here
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
des.monster({ id = "water elemental", peaceful = 0 })
