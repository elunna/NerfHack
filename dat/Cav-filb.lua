-- NetHack Caveman Cav-filb.lua	$NHDT-Date: 1652196001 2022/05/10 15:20:01 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.2 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.level_init({ style = "mines", fg = ".", bg = " ", smoothed=true, joined=true, walled=true })

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
des.object()
--
des.trap("pit")
des.trap("pit")
des.trap("pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("bear")
des.trap("bear")
des.trap("bear")
des.trap("spear")
des.trap("spear")
des.trap("spear")

--
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "tiger", peaceful=0 })
des.monster({ id = "weretiger", peaceful=0 })

des.monster({ id = "python", peaceful=0 })
des.monster({ id = "python", peaceful=0 })
des.monster({ id = "python", peaceful=0 })
des.monster({ id = "python", peaceful=0 })

des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })
des.monster({ id = "carnivorous ape", peaceful=0 })


des.monster({ class = "h", peaceful=0 })
des.monster({ class = "h", peaceful=0 })
des.monster({ id = "hill giant", peaceful=0 })
des.monster({ id = "hill giant", peaceful=0 })
