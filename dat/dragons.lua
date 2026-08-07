--       SCCS Id: @(#)caves.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- Ported from SLASH'EM
-- Converted to lua by hackemslashem
--
--    This level is used to fill out any levels not occupied by
--    specific levels.
--
--MAZE: "dragons" , ' '
--INIT_MAP: '.' , ' ' , true , true , random , true
--NOMAP

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noflip");
des.level_init({ style="mines", fg=".", bg=" ", smoothed=true, joined=true, walled=true })

--RANDOM_MONSTERS: 'D','w'
des.stair("up")

for i = 1,28 do
   des.object("*")
end

des.object("(")
des.object("(")
des.object("(")

des.object(")")
des.object(")")
des.object(")")
des.object(")")

des.object("!")
des.object("!")
des.object("!")
des.object("!")
des.object("!")

des.object("?")
des.object("?")
des.object("?")
des.object("?")

des.object()
des.object()
des.object()
des.object()
des.object()

for i = 1,14 do
   des.monster('D')
end

-- Guarantee at least 10 adult dragons appear
local dragons = { "gray dragon", "gold dragon", "silver dragon",
                  "red dragon", "white dragon", "orange dragon",
                  "black dragon", "blue dragon", "green dragon",
                  "yellow dragon", "shimmering dragon" };
for i = 1,10 do
    shuffle(dragons)
    des.monster({ id = dragons[1], peaceful=0 })
end

des.monster('w')
des.monster('w')
des.monster('w')
des.monster('w')

des.monster('rot worm')
des.monster('rot worm')
des.monster('rot worm')
des.monster('rot worm')
des.monster('rot worm')

des.monster({ id = "rot worm", peaceful = 0 })
des.monster({ id = "rot worm", peaceful = 0 })
des.monster({ id = "rot worm", peaceful = 0 })
des.monster({ id = "rot worm", peaceful = 0 })
des.monster({ id = "rot worm", peaceful = 0 })

des.trap()
des.trap()
des.trap()
des.trap()