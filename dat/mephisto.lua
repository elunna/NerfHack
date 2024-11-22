-- Mephisto's lair
-- Ported from SpliceHack
-- Author: Kestrel Gregorich-Trevor'
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor");

des.map([[
.......................---------------------------.........................
...-------.............|.........................|..............-------....
...|LLLLL|..........---|.LLLLLLLLLLLLLLLLLLLLLLL.|---...........|LLLLL|....
...|LLLLL|.............|.L.....................L.|..............|LLLLL|....
...|LLLLL|.............|.L..--------..-------..L.|..............|LLLLL|....
...|LLLLL|.............|.L..|......|..|.....|..L.|..............|LLLLL|....
...|LLLLL|......-----..|.L..|......|..|.....|..L.|..-----.......|LLLLL|....
...---L---......|......|.L..|...............|..L.|......|.......---L---....
....|LLL|.......|......|.L..|......LLLL.....|..L.|......|........|LLL|.....
....|LLL|.......|......|.L..|......LLLL.....|..L.|......|........|LLL|.....
.....LLL........|L.....|.L..|......LLLL.....|..L.|.....L|.........LLL......
.....LLL........-------|.L..|......LLLL.....|..L.|-------.........LLL......
......LLL..............|.L..|--...........--|..L.|...............LLL.......
......LLL..............|.L..|...............|..L.|...............LLL.......
.....LLLLL.............|.L..-----------------..L.|..............LLLLL......
.....LLLLL..........---|.LLL.................LLL.|---...........LLLLL......
...LLL..LLL.....----|LL|.LLLLLLLLLLLLLLLLLLLLLLL.|LL|----......LLL..LLL....
...LLL...LLLLLLL|LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL|LLLLLLLL...LLL....
LLLLL...........----|LL---------------------------LL|----............LLLLLL
LLL.................---LLLLLLLLLLLLLLLLLLLLLLLLLLL---..................LLLL
]]);

des.non_diggable(selection.area(00,00,75,19))
des.non_passwall(selection.area(00,00,75,19));

des.region(selection.area(00,00,75,19), "unlit")

des.stair("down", 36,12)
des.stair("up", 22,00)

des.door("locked",36,04)
des.door("locked",37,04)

des.drawbridge({ dir="east", state="closed", x=15,y=17 });
des.drawbridge({ dir="west", state="closed", x=57,y=17 });
--
des.monster({id="lava demon", x=06, y=04})
des.monster({id="lava demon", x=67, y=04})
des.monster("lava demon")
des.monster("lava demon")
des.monster("lava demon")
des.monster("lava demon")
-- des.monster("magma elemental")
des.monster("fire elemental")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
des.monster("&")
--
des.monster({id="pit fiend", x=35, y=12, name="The Left Horn"})
des.monster({id="pit fiend", x=37, y=12, name="The Right Horn"})
des.monster({id="hezrou", x=32, y=07})
des.monster({id="hezrou", x=41, y=07})
des.monster({id="hezrou", x=33, y=08})
des.monster({id="hezrou", x=40, y=08})
des.monster({id="Mephistopholes", x=36, y=12})
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
des.trap("land mine")
des.trap("land mine")
des.trap("land mine")
des.trap("land mine")
des.trap("land mine")
des.trap("land mine")
des.trap("land mine")
des.trap("land mine")
des.trap("land mine")
des.trap("land mine")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()