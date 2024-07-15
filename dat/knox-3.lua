-- NetHack knox knox-3.lua	$NHDT-Date: 1652196027 2022/05/10 15:20:27 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.5 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1992 by Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
--"Minas Tirith?" by Patric Mueller <bhaak@gmx.net>

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "shortsighted", "noflip")
-- Fort's entry is via a secret door rather than a drawbridge;
-- the moat must be manually circumvented.
des.map([[
----------------------------------------------------------------------------
|........|.......}|F|}.......}F|F|F}......+..................|.|   |.|   |.|
|........|.......}|.|}.......}F.|.F}......F...........|--F--+|.|   |.|   |.|
|-S----S--......}F|||F}......}F.|.F}......+.....|--F--|...}F.|.|   |.|   |.|
| #   |.........}F.|.F}......}F|F|F}......|--F--|.........}|.|S-----S-----S-
| #   |.........}F|||F}.......}|.|}.......................}F.|..............
| # |--.........}|...|}......}F|F|F}......................}|.|............. 
| # |...........}F|||F}......}F.|.F}......................}F.|...........   
| # |...........}F.|.F}......}F.|.F}......................}|.|.........     
|-S----.........}F|||F}......}F|F|F}..........{{{.........}F.|.......       
|.....|..........}|.|}.......}|...|}..........{T{.........}|.|......        
|.....+.........}F|||F}......}F|F|F}..........{{{.........}F.|---S-         
|.....|.........}F.|.F}......}F.|.F}......................}|.|.......       
|.....|.........}F|||F}......}F.|.F}......................}F.|........      
|..-S----.......}|...|}......}F|F|F}......................}|.S....\......   
|..|....|.......}F|||F}.......}|.|}.......................}F.|..............
|..|....|.......}F.|.F}......}F|F|F}......|--F--|.........}|.|S-----S-----S-
|----------.....}F|||F}......}F.|.F}......+.....|--F--|...}F.|.|   |.|   |.|
|         |......}|.|}.......}F.|.F}......F...........|--F--+|.|   |.|   |.|
|         |......}|F|}.......}F|F|F}......+..................|.|   |.|   |.|
----------------------------------------------------------------------------
]]);
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- everything's lit
des.region(selection.area(00,00,75,19),"lit")

-- Portal arrival point
des.levregion({ region = {06,16,06,16}, type="branch" });

-- accessible via ^V in wizard mode; arrive near the portal
des.teleport_region({ region = {06,15,09,16}, dir="up" })
des.teleport_region({ region = {06,15,09,16}, dir="down" })

--   Throne room, with Croesus on the throne
des.region({ x1=62,y1=12,x2=75,y2=15, lit=1, type="throne", filled=1, irregular=1 })
des.monster({ id = "Croesus", x=66, y=14, peaceful = 0 })

--   50% chance each to move fort's entry secret door up one row
if percent(50) then
   des.terrain(61,13, "S")
   des.terrain(61,14, "|")
end

--   The Vault
function treasure_spot(x,y)
   des.gold({ x = x, y = y, amount = 600 + math.random(0, 300) });
   if (math.random(0,2) == 0) then
      if (math.random(0,2) == 0) then
         des.trap("spiked pit", x,y);
      else
         des.trap("land mine", x,y);
      end
   end
end

des.region({ region={62,05,75,10}, lit=1, type="ordinary" })
local treasury = selection.area(62,05,75,10);
treasury:iterate(treasure_spot);

--   Vault entrance also varies
if percent(50) then
   des.terrain(65,11, "|")
   des.terrain(64,11, "S")
end

--   A welcoming committee
des.region({ region={01,10,05,13},lit=1,type="zoo",filled=1,irregular=1 })

--   arrival chamber; needs to be a real room to control migrating monsters,
--   and `unfilled' is a kludge to force an ordinary room to remain a room
des.region({ region={04,15,07,16},lit=0,type="ordinary",arrival_room=true })

-- TODO: Double check this, does it match knox-1??

--   3.6.2:  Entering level carrying a lit candle would show the whole entry
--   chamber except for its top right corner even though some of the revealed
--   spots are farther away than that is.  This is because the lit treasure zoo
--   is forcing the walls around it to be lit too (see light_region(sp_lev.c)),
--   and lit walls show up when light reaches the spot next to them.  The unlit
--   corner is beyond candle range and isn't flagged as lit so it doesn't show
--   up until light reaches it rather than when light gets next to it.
--
--   Force left and top walls of the arrival chamber to be unlit in order to
--   hide this lighting quirk.
des.region(selection.area(05,14,05,17),"unlit")
des.region(selection.area(05,14,09,14),"unlit")
--   (Entering the treasure zoo while blind and then regaining sight might
--   expose the new oddity of these walls not appearing when on the lit side
--   but that's even less likely to occur than the rare instance of entering
--   the level with a candle.  They'll almost always be mapped from the arrival
--   side before entering the treasure zoo.
--
--   A prior workaround lit the top right corner wall and then jumped through
--   hoops to suppress the extra light in the 3x3 lit area that produced.
--   This is simpler and makes the short range candle light behave more like
--   it is expected to work.)

--   Barracks
des.region({ region={43,01,44,02},lit=1,type="barracks",filled=1,irregular=1 })
des.region({ region={43,17,44,17},lit=1,type="barracks",filled=1,irregular=1 })

-- Drawbridges of first ringwall
des.drawbridge({ dir="east", state="closed", x=30,y=05})
des.drawbridge({ dir="west", state="closed", x=34,y=05})
des.drawbridge({ dir="east", state="closed", x=29,y=10})
des.drawbridge({ dir="west", state="closed", x=35,y=10})
des.drawbridge({ dir="east", state="closed", x=30,y=15})
des.drawbridge({ dir="west", state="closed", x=34,y=15})

-- Guards of first ringwall, with possible offensive wands
-- TODO: Maybe use a list of coords instead?
des.monster("C",31,02)
if percent(50) then
   des.object("/",31,02)
end
des.monster("C",31,03)
if percent(50) then
   des.object("/",31,03)
end
des.monster("C",31,07)
if percent(50) then
   des.object("/",31,07)
end
des.monster("C",31,08)
if percent(50) then
   des.object("/",31,08)
end
des.monster("C",31,12)
if percent(50) then
   des.object("/",31,12)
end
des.monster("C",31,13)
if percent(50) then
   des.object("/",31,13)
end
des.monster("C",31,17)
if percent(50) then
   des.object("/",31,17)
end
des.monster("C",31,18)
if percent(50) then
   des.object("/",31,18)
end
des.monster("C",33,02)
if percent(50) then
   des.object("/",33,02)
end
des.monster("C",33,03)
if percent(50) then
   des.object("/",33,03)
end
des.monster("C",33,07)
if percent(50) then
   des.object("/",33,07)
end
des.monster("C",33,08)
if percent(50) then
   des.object("/",33,08)
end
des.monster("C",33,12)
if percent(50) then
   des.object("/",33,12)
end
des.monster("C",33,13)
if percent(50) then
   des.object("/",33,13)
end
des.monster("C",33,17)
if percent(50) then
   des.object("/",33,17)
end
des.monster("C",33,18)
if percent(50) then
   des.object("/",33,18)
end

-- Drawbridges of second ringwall
des.drawbridge({ dir="east", state="closed", x=16,y=06})
des.drawbridge({ dir="west", state="closed", x=22,y=06})
des.drawbridge({ dir="east", state="closed", x=17,y=10})
des.drawbridge({ dir="west", state="closed", x=21,y=10})
des.drawbridge({ dir="east", state="closed", x=16,y=14})
des.drawbridge({ dir="west", state="closed", x=22,y=14})

-- Guards of second ringwall, with possible offensive wands
des.monster("C",18,04)
if percent(50) then
   des.object("/",18,04)
end
des.monster("C",20,04)
if percent(50) then
   des.object("/",20,04)
end

des.monster("C",18,08)
if percent(50) then
   des.object("/",18,08)
end
des.monster("C",20,08)
if percent(50) then
   des.object("/",20,08)
end

des.monster("C",18,12)
if percent(50) then
   des.object("/",18,12)
end
des.monster("C",20,12)
if percent(50) then
   des.object("/",20,12)
end

des.monster("C",18,16)
if percent(50) then
   des.object("/",18,16)
end
des.monster("C",20,16)
if percent(50) then
   des.object("/",20,16)
end

-- Doors
des.door("closed",04,14)
des.door("closed",07,03)
des.door("locked",06,11)
-- barrack doors
des.door("closed",60,02)
des.door("closed",60,18)
des.door("closed",42,01)
des.door("closed",42,03)
des.door("closed",42,17)
des.door("closed",42,19)

-- elves
des.monster("Grey-elf",    60,03)
des.monster("Woodland-elf",60,04)
des.monster("Green-elf",   60,05)
des.monster("Grey-elf",    60,06)
des.monster("elven wizard",60,07)
des.monster("Green-elf",   60,08)
des.monster("Grey-elf",    60,09)
des.monster("Woodland-elf",60,10)

des.monster("Elvenking",   60,11)
des.monster("Grey-elf",    60,12)
des.monster("elven wizard",60,13)
des.monster("Green-elf",   60,14)
des.monster("elf lord",    60,15)
des.monster("Grey-elf",    60,16)
des.monster("Woodland-elf",60,17)

-- Soldiers guarding the fort
des.monster("soldier",12,14)
des.monster("soldier",12,13)
des.monster("soldier",11,10)
des.monster("soldier",13,15)
des.monster("soldier",14,04)
des.monster("soldier",12,18)
des.monster("soldier",13,12)
des.monster("soldier",14,08)
des.monster("lieutenant",12,08)

des.monster("soldier",28,16)
des.monster("soldier",24,17)
des.monster("soldier",25,09)
des.monster("soldier",25,15)
des.monster("soldier",26,13)
des.monster("soldier",27,04)
des.monster("soldier",28,10)
des.monster("soldier",23,03)
des.monster("lieutenant",26,08)

-- Four dragons guarding the fort
des.monster("D",42,09)
des.monster("D",50,09)
des.monster("D",49,08)
des.monster("D",46,12)

-- Eels in the moat
des.monster("giant eel",16,04)
des.monster("giant eel",22,15)
des.monster("giant eel",29,07)
des.monster("giant eel",35,14)

-- Some companions for Croesus...
des.monster("mermaid")
des.monster("mermaid")
des.monster("mermaid")
des.monster("mermaid")

-- The corner rooms treasures
des.object("diamond",62,17)
des.object("diamond",62,18)
des.object("diamond",62,19)
des.object("emerald",74,17)
des.object("emerald",74,18)
des.object("emerald",74,19)
des.object("ruby",62,01)
des.object("ruby",62,02)
des.object("ruby",62,03)
des.object("amethyst",74,01)
des.object("amethyst",74,02)
des.object("amethyst",74,03)