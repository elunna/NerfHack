--
--
-- The New Asmodeus Level
--
-- Ported from SpliceHack
-- Original design seems to come from the Lethe Patch, author unknown.
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "cold")
-- First part
--0       1         2         3         4         5         6         7     
--23456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "half-left", valign = "center", map = [[
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL}}}}LLLLLLLLLLLLLLLLLLLLLLLLLL----
--------------------LLLL-------         |}}}}--LLLLLLLLLLLLLLLLLLLLLLLLL|..|
|............S.....|LLLL|.....|------   --}}}}--------------LLLLLLL#####+..|
|---+-----------...|LLLL|.....|.....|------}}}}|...........|LLLLLLL#LLLL|..|
|.....|........|-+------|.....|.....|.....F}}}}F...........|LLLL---+--- ----
|..---|........|........|.....|.....|.....|}}}}|..{..{..{..|LLLL|.....|     
|..|..S........|..........................|}..}|...........+##H#S.....S#    
|..|..|........|........|.....|.....|.....|}}}}|..{..{..{..|LLLL|.....|     
|..|..|........|-+------|.....|.....|.....F}}}}F...........|LLLL---+---     
|..|..-----S----...|LLLL|.....|.....|------}}}}|...........|LLLLLLLH        
|..S.....|...|.....|LLLL|.....|------LLLL|}}}}--------------LLLLLLLH        
---------|...|------LLLL-------LLLLLLLLL--}}}}LLL--------LLLLLLLLLLH        
LLLLLLLLL|...|LLLLLLLLLLLL###LLLLLLLLLLL|}}}}----|......|LLLLLLLLLL#        
LLLLLLLLL|...|LLLLLLLLLLLLLL#LL###LLLLLLL}}}}|L|.+......+###########        
LLLLL-----+++-----LLLL####LL#LL#LLLLLLLLL}}}}LL|.+......+###########        
LLLLL|...........|LLLL#LLLLL######LL----LL}}}}L--|......|LLLLLLLLLL#        
LLLLL|...........S#####LLLLL#LLLL#LL|..|LL}}}}LLL--------LLLLLLL---+---     
LLLLL|...........|LLLL#LLLLL#LLLL###+..|LLL}}}}LLLLLLLLLLLLLLLLL|.....|     
LLLLL|.....\.....|LLLL#######LLLLLLL|..|LLL}}}}LLLLLLLLLLLLLLLLL|.....|     
LLLLL-------------LLLLLLLLLLLLLLLLLL----LLL}}}LLLLLLLLLLLLLLLLLL-------     
]] });

local terrains = { "P", "L", "-", "I" };
local tidx = math.random(1, #terrains);
local toterr = terrains[tidx];

if percent(50) then
    des.replace_terrain({ fromterrain="L", toterrain=toterr, chance=100 })
end

des.stair("up", 65,17)
des.stair("down", 11,16)

des.levregion({ region = {73,01,74,03}, exclude = {00,00,00,00}, type="branch" })
des.teleport_region({region={60,12,65,14}})

-- Doors
des.door("locked",67,16)
des.door("locked",56,14)
des.door("locked",56,13)
des.door("locked",49,14)
des.door("locked",49,13)
des.door("locked",67,08)
des.door("locked",67,04)
des.door("locked",72,02)
des.door("locked",64,06)
des.door("locked",70,06)
des.door("locked",17,08)
des.door("locked",17,04)
des.door("locked",13,02)
des.door("locked",04,03)
des.door("locked",03,10)
des.door("locked",06,06)
des.door("locked",11,09)
des.door("closed",10,14)
des.door("closed",11,14)
des.door("closed",12,14)
des.door("locked",17,16)
des.door("locked",36,17)

-- Drawbridges
des.drawbridge({dir="east",state="closed",x=46,y=06})
des.drawbridge({dir="west",state="closed",x=43,y=06})

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Regions of light and dark
des.region(selection.area(00,00,75,19), "unlit")
des.region({region={25,02,29,05},lit=0,"lemurepit",filled=1})
des.region({region={31,03,35,05},lit=0,"lemurepit",filled=1})
des.region({region={37,04,41,05},lit=0,"lemurepit",filled=1})
des.region({region={37,07,41,08},lit=0,"lemurepit",filled=1})
des.region({region={31,07,35,09},lit=0,"lemurepit",filled=1})
des.region({region={25,07,29,10},lit=0,"lemurepit",filled=1})
des.region(selection.area(48,03,58,09), "lit")
des.region(selection.area(06,15,16,18), "lit")

-- The fellow in residence
des.monster({id="Asmodeus", x=11, y=16})

-- His close friends
des.monster({id="marilith", x=08, y=16,name="Voran" })
des.monster({id="marilith", x=09, y=17,name="Joggeruuth" })
des.monster({id="succubus", x=14, y=16 })
des.monster({id="succubus", x=13, y=17 })
des.monster({id="incubus", x=11, y=18 })
des.monster({id="barbed devil", x=10, y=13,name="Gogmelon" })
des.monster({id="barbed devil", x=12, y=13,name="Ulgaxicus" })

-- A few traps on the way in
des.trap("board",10,12)
des.trap("board",11,12)
des.trap("board",12,12)
des.trap("fire",11,11)
des.trap("fire",10,10)
des.trap("fire",12,10)
des.trap("cold")
des.trap("cold")
des.trap("cold")
des.trap("cold")
des.trap("cold")
des.trap("cold")
des.trap("cold")

-- The 'fake' throne room
des.monster({class="&", x=07, y=04})
des.monster({class="&", x=14, y=04})
des.monster({class="&", x=17, y=08})
des.monster({class="&", x=14, y=08})

des.monster({id="killer mimic", x=11, y=06, appear_as = "ter:staircase down"})
des.trap("magic",09,06)
des.trap("magic",13,06)
des.trap("magic",11,05)
des.trap("magic",11,07)

-- Some random weapons and armor.
des.object("[")
des.object("[")
des.object(")")
des.object(")")
des.object("*")
des.object("!")
des.object("?")

-- Traps in the outer chambers
des.trap("spiked pit",02,08)
des.trap("anti magic",21,06)
des.trap("sleep gas",19,05)
des.trap("fire",56,06)
des.trap("rust",53,06)
des.trap("spiked pit",50,03)
des.trap("polymorph",69,02)

-- Traps in the inner spiral
des.trap("magic",22,14)
des.trap("anti magic",26,18)
des.trap("fire",28,13)
des.trap("spiked pit",32,13)

-- Treasure room
des.gold({amount=500,x=38,y=16})
des.gold({amount=500,x=38,y=17})
des.gold({amount=500,x=38,y=18})


des.object({id="diamond", x=38, y=16,buc="cursed",name="The Tears of Koth"})
des.object({id="ruby", x=38, y=17,buc="cursed",name="The Heart of Cassanova"})
des.object({id="emerald", x=38, y=18,"cursed",name="The Eye of Hera"})
des.monster({class="&", x=38, y=16})
des.monster({class="&", x=38, y=17})
des.monster({class="&", x=38, y=18})

-- Outer Trap Room
des.gold({amount=1,x=48,y=13})
des.gold({amount=1,x=48,y=14})

des.trap("magic",48,13)
des.trap("land mine",48,14)
des.gold({amount=1,x=51,y=12})
des.gold({amount=1,x=50,y=14})
des.gold({amount=1,x=52,y=15})
des.gold({amount=1,x=53,y=13})
des.trap("fire",54,13)
des.trap("fire",54,14)
des.trap("magic",52,12)
des.trap("magic beam",52,15)
des.trap("spiked pit",51,13)
des.trap("anti magic",50,14)

-- Guardians in the fountain room
des.monster({class="&", x=49, y=04})
des.monster({class="&", x=49, y=08})
des.monster({class="&", x=52, y=04})
des.monster({class="&", x=52, y=08})
des.monster({class="V", x=55, y=04})
des.monster({class="V", x=55, y=08})

-- Guardians in the outer chamber
des.monster({id="hell hound", x=67, y=06})
des.monster({id="hell hound", x=69, y=06})
des.monster({id="hell hound", x=68, y=05})
des.monster({id="hell hound", x=68, y=07})

-- Guardian in the branch chamber
des.monster({id="blue jelly", x=73, y=02})

-- Greeting in the outer chamber
des.monster({id="imp", 69, 17})
des.object({id="loadstone", x=65, y=18,buc="cursed"})

-- TODO: Salamanders when they can swim in lava.