-- # Intermediate stage of Vlad's tower
-- MAZE:"tower2",' '

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "solidify")

--0         1         2         3
--0123456789012345678901234567890
des.map({ halign = "half-left", valign = "center", map = [[
00  --- ---   ------   --- ---  
01  |.| |.|  -|....|-  |.| |.|  
02---S---S---|......|---S---S---
03|..........S......S..........|
04|..........|......|..........|
05-FF---FFF---FF++FF---FFF---FF-
06 ..|......................|.. 
07 ..F......................F.. 
08 ..F......................F.. 
09 ..|......................|.. 
10-FF---FFF---FF++FF---FFF---FF-
11|..........|......|..........|
12|..........S......S..........|
13---S---S---|......|---S---S---
14  |.| |.|  -|....|-  |.| |.|  
15  --- ---   ------   --- ---  
]] });

-- # Random places are the 8 niches
local place = { {03,01}, {07,01}, {22,01}, {26,01},
                {03,14}, {07,14}, {22,14}, {26,14} }
shuffle(place)

des.ladder("up", 28,12)
des.ladder("down", 01,03)

-- Locked doors
-- Do we really want all doors locked?
des.door("locked",03,02)
des.door("locked",07,02)
des.door("locked",22,02)
des.door("locked",26,02)
des.door("locked",03,13)
des.door("locked",07,13)
des.door("locked",22,13)
des.door("locked",26,13)
des.door("locked",14,10)
des.door("locked",15,10)
des.door("locked",14,05)
des.door("locked",15,05)

-- # Monsters and objects in the niches
des.monster("&",place[1])
des.monster("&",place[2])

des.monster("hell hound",place[3])
des.monster("hell hound",place[4])
des.monster("J",place[5])


des.object({ id = "chest", coord = place[6],
             contents = function()
                if percent(50) then
                    des.object("amulet of life saving")
                else
                    des.object("amulet of change")
                end
             end
});

des.object({ id = "chest", coord = place[7],
             contents = function()
                if percent(50) then
                    des.object("amulet of strangulation")
                else
                    des.object("amulet of restful sleep")
                end
             end
});

if percent(60) then
    des.object("water walking boots",place[3])
end
if percent(60) then
    des.object("crystal plate mail",place[4])
end

if percent(60) then
    local spbooks = {
       "spellbook of invisibility",
       "spellbook of cone of cold",
       "spellbook of create familiar",
       "spellbook of clairvoyance",
       "spellbook of charm monster",
       "spellbook of stone to flesh",
       "spellbook of polymorph"
    }
    shuffle(spbooks);
    des.object(spbooks[1],place[5])
end

-- # Random noncorporeal undead
des.monster(" ", 05,04)
des.monster(" ", 24,04)
des.monster(" ", 05,11)
des.monster(" ", 24,11)

-- # Vampire nests with demonic pets
des.monster("&", 06,07)
des.monster("&", 06,08)

des.monster("vampire lord", 07,07)
des.monster("vampire lord", 07,08)
des.monster("vampire lord", 08,07)
des.monster("vampire lord", 08,08)
des.monster("vampire lord", 09,07)
des.monster("vampire lord", 09,08)
des.monster("vampire lord", 20,07)
des.monster("vampire lord", 20,08)
des.monster("vampire lord", 21,07)
des.monster("vampire lord", 21,08)
des.monster("vampire lord", 22,07)
des.monster("vampire lord", 22,08)

des.monster("&", 23,07)
des.monster("&", 23,08)

-- More vampires
des.monster("vampire mage", 12,13)
des.monster("vampire mage", 14,14)
des.monster("vampire royal", 15,14)
des.monster("vampire royal", 17,13)

-- What is Vlad keeping in the closet??
local prisoners = {
    "orb weaver", "third eye", "glowing eye", "prisoner",
    "couatl", "eye of fear and flame", "pyrolisk", "barghest",
    "monstrous spider", "worm that walks", "hunger hulk",
    "black dragon", "green dragon", "yellow dragon", "shimmering dragon",
 };
shuffle(prisoners)
des.monster({ id = prisoners[1], x = 01, y = 07, peaceful=0 })
des.monster({ id = prisoners[2], x = 01, y = 08, peaceful=0 })
des.monster({ id = prisoners[3], x = 28, y = 07, peaceful=0 })
des.monster({ id = prisoners[4], x = 28, y = 08, peaceful=0 })

-- Random corpses of past adventurers
des.object({ id="corpse",montype="cavewoman" })
des.object({ id="corpse",montype="knight" })
des.object({ id="corpse",montype="wizard" })
des.object({ id="corpse",montype="rogue" })
des.object({ id="corpse",montype="cartomancer" })
des.object({ id="corpse",montype="undead slayer" })


-- Walls in the tower are non diggable
des.non_diggable(selection.area(00,00,29,15))
