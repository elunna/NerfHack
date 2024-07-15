-- NetHack knox knox.lua	$NHDT-Date: 1652196027 2022/05/10 15:20:27 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.5 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1992 by Izchak Miller
-- NetHack may be freely redistributed.  See license for details.
--
--
-- "Winterly Fort Ludios" by Patric Mueller <bhaak@gmx.net>

des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "shortsighted", "noflip")
-- Fort's entry is via a secret door rather than a drawbridge;
-- the moat must be manually circumvented.
des.map([[
--------------------}}I-----------------------------------------------------
| |........|.........}II...................................................|
| |........|.........}II.............}}}}}}}....................}}}}}}}....|
| --S----S--..........}II............}-----}....................}-----}....|
|   #   |..............}III..........}|...|}}}}}}}}}}}}}}}}}}}}}}|...|}....|
|   #   |.............}}II...........}---S------------------------S---}....|
|   # ---.............}}II...........}}}|...............|..........|}}}....|
|   # |................II..............}|...............S..........|}......|
|   # |................}II.............}|...............|......\...S}......|
| --S----..............}III..........}}}|...............|..........|}}}....|
| |.....|.............}}IIII.........}---S------------------------S---}....|
| |.....+..............}}II..........}|...|}}}}}}}}}}}}}}}}}}}}}}|...|}....|
| |.....|...............}}I..........}-----}....................}-----}....|
| |.....|................}}I.........}}}}}}}....................}}}}}}}....|
| |..-S----...............}II..............................................|
| |..|....|..............}IIII.....|--+--|...........................|--+--|
| |..|....|.............}}}.IIII...|.....|..........|--+--|..........|.....|
| -----------..........}}}...III...+.....|----------|.....|----------|.....|
|           |.........}}}...III....|.......................................|
----------------------}}}----III--------------------------------------------
]]);
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- Portal arrival point
des.levregion({ region = {08,16,08,16}, type="branch" });
-- accessible via ^V in wizard mode; arrive near the portal
des.teleport_region({ region = {06,15,09,16}, dir="up" })
des.teleport_region({ region = {06,15,09,16}, dir="down" })

--   Throne room, with Croesus on the throne
des.region({ x1=57,y1=06,x2=66,y2=09, lit=1, type="throne", filled=1 })

--   50% chance each to move throne and/or fort's entry secret door up one row
if percent(50) then
   des.monster({ id = "Croesus", x=63, y=08, peaceful = 0 })
else
   des.monster({ id = "Croesus", x=63, y=07, peaceful = 0 })
   des.terrain(63,07, "\\")
   des.terrain(63,08, ".")
end
if percent(50) then
   des.terrain(67,07, "S")
   des.terrain(67,08, "|")
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

des.region({ region={41,06,55,09}, lit=1, type="ordinary" })
local treasury = selection.area(41,06,55,09);
treasury:iterate(treasure_spot);

--   Vault entrance also varies
if percent(50) then
   des.terrain(56,07, "|")
   des.terrain(56,18, "S")
end


--   Corner towers
des.region(selection.area(39,04,41,04),"lit")
des.region(selection.area(66,04,68,04),"lit")
des.region(selection.area(39,11,41,11),"lit")
des.region(selection.area(66,11,68,11),"lit")

--   A welcoming committee
des.region({ region={03,10,07,13},lit=1,type="zoo",filled=1,irregular=1 })


--   arrival chamber; needs to be a real room to control migrating monsters,
--   and `unfilled' is a kludge to force an ordinary room to remain a room
des.region({ region={06,15,09,16},lit=0,type="ordinary",arrival_room=true })

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
des.region({ region={36,16,36,18},lit=1,type="barracks",filled=1,irregular=1 })

-- Doors
des.door("closed",06,14)
des.door("closed",09,03)
des.door("locked",08,11)

-- barrack doors
des.door("closed",35,17)
des.door("closed",38,15)
des.door("closed",55,16)
des.door("closed",72,15)

-- # Soldier in watchtower
-- #MONSTER: '@', "lieutenant",(19,07),hostile
-- #OBJECT:'/',"fire",(19,07)

-- Soldiers guarding the fort
des.monster("soldier",12,14)
des.monster("soldier",12,13)
des.monster("soldier",11,10)
des.monster("soldier",13,02)
des.monster("soldier",14,03)
des.monster("soldier",20,02)
des.monster("soldier",30,02)
des.monster("soldier",40,01)
des.monster("soldier",30,16)
des.monster("soldier",32,16)
des.monster("soldier",36,08)
des.monster("soldier",54,15)
des.monster("soldier",54,13)
des.monster("soldier",53,12)
des.monster("soldier",71,10)
des.monster("soldier",57,03)
des.monster("lieutenant",15,08)

-- Possible source of a boulder
des.monster("stone giant",03,01)

-- Four dragons guarding each side
des.monster("D",32,09)
des.monster("D",49,02)
des.monster("D",50,12)
-- this one isn't where he's supposed to be
des.monster("D",25,03)

-- Eels in the moat
des.monster("giant eel",50,04)
des.monster("giant eel",60,04)
des.monster("giant eel",43,12)
des.monster("giant eel",68,09)

-- The corner rooms treasures
des.object("diamond",39,04)
des.object("diamond",40,04)
des.object("diamond",41,04)
des.object("emerald",39,11)
des.object("emerald",40,11)
des.object("emerald",41,11)
des.object("ruby",66,04)
des.object("ruby",67,04)
des.object("ruby",68,04)
des.object("amethyst",66,11)
des.object("amethyst",67,11)
des.object("amethyst",68,11)
