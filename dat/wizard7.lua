-- # The bottom wizard level.
-- MAZE:"wizard3",' '

des.level_init({ style="mazegrid", bg ="-" });
des.level_flags("mazelevel", "noteleport", "hardfloor", "nommap", "solidify")

--0         1         2         3         4         5         6         7    7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
local wiz2 = des.map({ halign = "center", valign = "center", map = [[
00                                                                            
01                 ---------------------------------------------              
02                 |....|L...LL.....LLL|...|LLLLL....L...L|....|              
03           --FF--|....|LL.L...LL....L|...|LLL....L...L.L|....|--FF--        
04           |...|-|....|LL...L....L..L-----L...LL.....LLL|....|-|...|        
05           F...F......|LL......LL...LLLLLLL.........LL.L|......F...F        
06           |...F......|L...LLL....LLL...L.....LLLL.....L|......F...|        
07           |...|--S-----------------------------------------S--|...|        
08           F...F..........|.......|.........|.......|..........F...F        
09           F...F..........|.......|...T.T...|.......|..........F...F        
10           |...F..........|.......S..T...T..S.......|..........F...|        
11           |...F..........|.......|...T.T...|.......|..........F...|        
12           F...F..........|.......|.........|.......|..........F...F        
13           |...|-----..---|.-----.|FFFF-FFFF|.-----.|---..-----|...|        
14           --FF--|................|...F.F...|................|--FF--        
15                 |................|...F.F...|................|              
16                 -----------F---F-------------F---F-----------              
17                                                                            
18                                                                            
19                                                                            
]] });

-- TELEPORT_REGION:(00,00,02,02),(00,00,00,00)
-- # constrains monster migration
des.region({ region={01,00,79,20}, lit=0, type="ordinary" })
des.region({ region={16,02,62,15}, lit=0, type="ordinary" })
des.region({ region={12,04,14,13}, lit=0, type="ordinary" })
des.region({ region={64,04,66,13}, lit=0, type="ordinary" })

-- ladders
des.ladder("down", 39,15)
des.ladder("up", 39,02)

-- # doors
des.door("locked",26,09)
des.door("locked",26,11)
des.door("locked",39,13)
des.door("locked",52,09)
des.door("locked",52,11)
des.door("closed",39,04)

-- # random door
if percent(50) then
    des.door("locked",22,04)
else
    des.door("locked",56,04)
end

-- # random secret doors
if percent(20) then
  des.terrain({62,03}, "S")
  des.terrain({62,04}, "S")
end


-- # barracks / soldier areas
des.region({ region={27,08,33,12},lit=1,type="migohive", filled=1 })
des.region({ region={45,08,51,12},lit=1,type="migohive", filled=1 })


-- West wing
des.monster("orb weaver",13,05)
des.monster("orb weaver",13,12)
des.monster("third eye",13,08)
des.monster("third eye",13,09)

-- East wing
des.monster("orb weaver",65,05)
des.monster("orb weaver",65,12)
des.monster("eye of fear and flame",65,08)
des.monster("eye of fear and flame",65,09)

-- Cold compartment (west)

des.monster("ice devil",28,14)
des.monster("ice devil",28,15)
des.monster("ice devil",29,14)
des.monster("ice devil",29,15)
des.monster("ice devil",30,14)
des.monster("ice devil",30,15)
des.monster("ice troll",31,14)
des.monster("ice troll",31,15)

-- Cold compartment (east)

des.monster("ice devil",  46,14)
des.monster("ice devil",  46,15)
des.monster("ice devil",  47,14)
des.monster("ice devil",  47,15)
des.monster("ice vortex", 48,14)
des.monster("ice vortex", 48,15)
des.monster("frost giant",49,14)
des.monster("frost giant",49,15)

-- # mage quarters (left)
des.monster("ghoul mage",19,03)
des.monster("ghoul mage",19,04)
des.monster("ghoul mage",20,04)
des.monster("ghoul queen",20,05)

-- # mage quarters (right)
des.monster("ghoul mage",59,03)
des.monster("ghoul mage",59,04)
des.monster("ghoul mage",58,04)
des.monster("ghoul queen",58,05)

-- # lava room
local lava = { 
    {23,02}, {26,02}, {30,02}, {34,02},
    {43,02}, {46,02}, {51,02}, {54,02},
    {24,04}, {32,04}, {44,04}, {49,04},
    {23,06}, {27,06}, {32,06}, {36,06},
    {42,06}, {48,06}, {53,06}, {55,06}
}
shuffle(lava)

-- TODO: Add other firey? fire vampire, vulpy?
des.monster({ id = "red dragon", coord = lava[1], peaceful = 0 })
des.monster({ id = "red dragon", coord = lava[2], peaceful = 0 })
des.monster({ id = "lava demon", coord = lava[3], peaceful = 0 })
des.monster({ id = "lava demon", coord = lava[4], peaceful = 0 })
des.monster({ id = "flaming sphere", coord = lava[5], peaceful = 0 })
des.monster({ id = "flaming sphere", coord = lava[6], peaceful = 0 })
des.monster({ id = "salamander", coord = lava[7], peaceful = 0 })
des.monster({ id = "salamander", coord = lava[8], peaceful = 0 })
des.monster({ id = "salamander", coord = lava[9], peaceful = 0 })
des.monster({ id = "salamander", coord = lava[10], peaceful = 0 })
des.monster({ id = "salamander", coord = lava[11], peaceful = 0 })
des.monster({ id = "salamander", coord = lava[12], peaceful = 0 })
des.monster({ id = "fire elemental", coord = lava[13], peaceful = 0 })
des.monster({ id = "fire elemental", coord = lava[14], peaceful = 0 })
des.monster({ id = "balrog", coord = lava[15], peaceful = 0 })
des.monster({ id = "balrog", coord = lava[16], peaceful = 0 })
des.monster({ id = "pit fiend", coord = lava[17], peaceful = 0 })
des.monster({ id = "pit fiend", coord = lava[18], peaceful = 0 })
des.monster({ id = "barbed devil", coord = lava[19], peaceful = 0 })
des.monster({ id = "barbed devil", coord = lava[20], peaceful = 0 })

-- Some prisoners
des.monster({ id = "prisoner", x = 36,y = 15, peaceful = 1 })
des.monster({ id = "prisoner", x = 43,y = 15, peaceful = 1 })

des.object("chest", 18,02)
des.object("chest", 60,02)

-- # none shall pass
-- NON_PASSWALL:(11,01,67,16)
des.non_diggable()
des.non_passwall()
