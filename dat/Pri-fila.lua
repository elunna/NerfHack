-- NetHack Priest Pri-fila.lua	$NHDT-Date: 1652196008 2022/05/10 15:20:08 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.1 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
des.level_flags("graveyard", "hardfloor")

des.room({ type = "ordinary",
           contents = function()
              des.stair("up")
              des.object()
              des.monster("human zombie")
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.object()
              des.monster("human zombie")
           end
})

des.room({ type = "morgue",
           contents = function()
              des.stair("down")
              des.object()
              des.trap()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.trap()
              des.monster("wraith")
           end
})

des.room({ type = "morgue",
           contents = function()
              des.object()
              des.trap()
           end
})

des.random_corridors()
