-- NetHack Monk Mon-filb.lua	$NHDT-Date: 1781994869 2026/06/20 22:34:29 $  $NHDT-Branch: NetHack-5.0 $:$NHDT-Revision: 1.2 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel","hardfloor");

des.level_init({ style="mines", fg=".", bg=" ", smoothed=true, joined=true, lit=0, walled=true })

--
des.stair("up")
des.stair("down")
--
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
--
des.trap()
des.trap()
des.trap()
des.trap()
--

des.monster({ class = "X", peaceful=0 })
des.monster({ class = "X", peaceful=0 })
des.monster({ class = "X", peaceful=0 })
des.monster({ class = "X", peaceful=0 })
des.monster({ class = "X", peaceful=0 })
des.monster({ class = "E", peaceful=0 })
des.monster({ id = "rock troll", peaceful=0 })
des.monster("earth elemental")
des.monster("earth elemental")
des.monster("earth elemental")
des.monster({ class = "E", peaceful=0 })
