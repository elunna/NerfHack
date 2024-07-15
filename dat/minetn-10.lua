-- NetHack 3.7	mines.des
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.

-- "Mini-Castle Town" - Original author unknown
-- Ported to lua by Erik Lunna (NerfHack/Hack'EM)
des.level_flags("noflip")
des.level_init({ style="mines", fg=".", bg="-", smoothed=true, joined=true,lit=1,walled=true })
des.map([[
----...}}}}}}}}}}}}}}}}}}}}}}}.--.---
--.....}---------------------}..-..--
-.----.}|........|.....|..|.|}......-
..|..|.}|.-----..|.....S.K|.|}.......
..|..|.}|.|...|..|.....|..|.|}.......
..|..|.}|.|...+..---+------.|}.......
..--+-.}|.|...|.............|}......-
.......}|.-----..T...{...T..|}......-
..{....}|...................|}.......
.......}|.--+--.-----.-----.|}.......
.......}|.|...--|...|.|...|.|}.......
.......}|.|...S.|...+.+...|.|}.......
..-....}|.|...|.|...|.|...|.|}.-+--..
---....}|.-----------.-----.|}.|..|..
-......}|...................|}.|....-
--..-..}---------------------}......-
------.}}}}}}}}}}}}}}}}}}}}}}}..-----
]]);

des.region({ region={00,00,36,16}, lit=1, type="ordinary" })

des.non_diggable(selection.area(8,1,28,15))
des.levregion({ type="stair-up", region={01,01,20,20}, region_islev=1, exclude={0,0,36,16} })
des.levregion({ type="stair-down", region={60,1,78,20}, region_islev=1, exclude={0,0,36,16} })

des.region({ region={3,3,4,5}, lit=1, type="food shop", filled=1 })
des.region({ region={11,4,13,6}, lit=1, type="candle shop", filled=1 })
des.region({ region={18,2,22,4}, lit=1, type="temple", filled=1 })
des.altar({ x=20,y=3,align=align[1],type="shrine"})

des.region({ region={24,2,25,4}, lit=1, type="ordinary" })
des.region({ region={11,10,12,12}, lit=1, type="ordinary" })
des.region({ region={14,11,15,12}, lit=0, type="ordinary" })

des.region({ region={17,10,19,12}, lit=1, type="tool shop", filled=1 })
des.region({ region={23,10,25,12}, lit=1, type="shop", filled=1 })

des.door("closed",4,6)
des.door("closed",14,5)
des.door("closed",20,5)
des.door("locked",23,3)
des.door("locked",12,9)
des.door("locked",14,11)
des.door("closed",20,11)
des.door("closed",22,11)
des.door("locked",32,12)

des.drawbridge({ dir="east", state="open", x=07,y=08})
des.drawbridge({ dir="west", state="open", x=29,y=08})

des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watchman", peaceful = 1 })
des.monster({ id = "watch captain", peaceful = 1 })

des.monster({id="gnomish wizard", x=25, y=03, peaceful=0})
des.monster({id="gnomish wizard", x=24, y=03, peaceful=0})
des.monster({id="gnome lord", x=11, y=12, peaceful=0})
des.monster({id="gnome", x=12, y=12, peaceful=0})
des.monster({id="gnome", x=11, y=11, peaceful=0})
des.monster({id="skeleton", x=15, y=12, peaceful=0})
des.monster({id="ogre", x=33, y=13, peaceful=0})
des.monster({id="ogre", x=32, y=13, peaceful=0})
des.monster({id="ogre", x=33, y=14, peaceful=0})

des.object({ id="boulder", x=34, y=14 })

des.monster("gnome")
des.monster("dwarf")
des.monster("dwarf lord")
des.monster("gnome lord")