-- NetHack Samurai Sam-fila.lua	$NHDT-Date: 1781994873 2026/06/20 22:34:33 $  $NHDT-Branch: NetHack-5.0 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-92 by M. Stephenson, P. Winner
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor");

des.level_init({ style="mines", fg=".", bg="P", smoothed=true, joined=true, walled=true })

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
--
des.monster("d")
des.monster("wolf")
des.monster("wolf")
des.monster("wolf")
des.monster("wolf")
des.monster("wolf")
des.monster("stalker")

des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("jellyfish")
des.monster("shark")
des.monster("shark")
des.monster("shark")
des.monster("shark")
--
des.trap()
des.trap()
des.trap()
des.trap()
