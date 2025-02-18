--
--       The "goal" level for the quest.
--
--       Here you meet Count Dracula your nemesis monster.  You have to
--       defeat Count Dracula in combat to gain the artifact you have
--       been assigned to retrieve.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor", "graveyard")

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
00T...T|..|---|.F.......F.|...|---|---|                                  
01..T..||.S...|-|.......|-|...+...|...|       -----                      
02.T.T..|.|...|.F.......F.|...|...|...|    ----...-----                  
03.T...T|.|...|-|.......|-|----...|...|--|--.-.....-..------             
04...T..|||...|.F.......F.|...|...|...|..|...-.....-.......------        
05..T....||...|-|.......|-|...+...|...S.--...--...--............|-----   
06....T..||...|.F.......F.|...|...|...|.|.....--S--..---|.....---....--- 
07...T...--+F-------+-----------+--F+--||..........---..|-...--........--
08....T..|.............................S.........---.....|.|||..........|
09..T..T.S.............................|.........S.......S.+++..........|
10..TTT..|.............................S.........---.....|.|||..........|
11..T..T.--+F-------S--------+-----F+--||..........---..|-...--........--
12.......||...|L.......L|{.......{|...|.|.....--S--..---|.....---....--- 
13...T...||...|...-+-...|--+---+--|...S.--...--...--............|-----   
14......|||...|..-###-..|....|....|...|..|...-.....-.......------        
15....T.|.|...|.|##}##|.|....|....|...|--|--.-.....-..------             
16.T.T..|.|...|.+#}{}#+.|....|....|...|    ----...-----                  
17.....||.S...|.|##}##|.|....|....|...|       -----                      
18..T..|..|---|L.-###-.L|---------|---|                                  
19            |---------|                                                
]]);
-- Dungeon Description
local place = { {14,04}, {13,07} }
local placeidx = math.random(1, #place);

des.region(selection.area(00,00,25,10), "unlit")
-- Stairs
des.stair("up", 04,18)

-- Many morgues

des.region({ region={09,01,11,06}, lit=0, type="morgue", filled=1 })
des.region({ region={09,12,11,17}, lit=0, type="morgue", filled=1 })

des.region({ region={33,01,35,06}, lit=0, type="morgue", filled=1 })
des.region({ region={33,12,35,17}, lit=0, type="morgue", filled=1 })

des.region({ region={23,14,26,17}, lit=0, type="morgue", filled=1 })
des.region({ region={28,14,31,17}, lit=0, type="morgue", filled=1 })

des.region({ region={25,00,27,02}, lit=0, type="morgue", filled=1 })
des.region({ region={25,04,27,06}, lit=0, type="morgue", filled=1 })

--des.region({ region={46,04,46,04}, lit=1, type="temple", filled=1, irregular=1 })
des.altar({ x=46,y=03, align=align[1], type="shrine", cracked=1 })

--des.region({ region={46,14,46,14}, lit=1, type="temple", filled=1, irregular=1 })
des.altar({ x=46,y=15, align=align[2], type="shrine", cracked=1 })

--des.region({ region={51,09,51,09}, lit=1, type="temple", filled=1, irregular=1 })
des.altar({ x=52,y=09, align=align[3], type="shrine", cracked=1 })

--des.region({ region={64,09,64,09}, lit=1, type="temple", filled=1, irregular=1 })
--des.altar({ x=65,y=09, align="noalign", type="shrine", cracked=1 })

if percent(50) then
  local sel = selection.randline(selection.new(), 40,00, 56,20, 20)
  des.terrain(sel:percentage(90):grow(), "L")
else
  local sel = selection.randline(selection.new(), 40,00, 72,20, 20)
  des.terrain(sel:percentage(90):grow(), "L")
end

-- guarantee space around nemesis
des.terrain(selection.area(64,08, 66,10),".")

-- Shops
des.door("random",30,07)
des.door("random",27,11)
des.door("random",28,01)
des.door("random",28,05)
des.door("random",25,13)
des.door("random",29,13)

-- Prison
des.door("random",18,07)

-- Barracks
des.door("random",09,07)
des.door("random",09,11)
des.door("random",34,07)
des.door("random",34,11)

-- Objects [note: eroded=-1 => obj->oerodeproof=1]
des.object({ id = "amulet of reflection",  x=65, y=09,
             buc="blessed", spe=0, eroded=-1, name="The Argent Cross" })
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
des.object()
des.object()

-- Random traps
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("board",08,08)
des.trap("board",08,09)
des.trap("board",08,10)
des.trap()

-- These poor souls
des.monster({ id = "prisoner", x=13, y=00, peaceful=1 })
des.monster({ id = "prisoner", x=13, y=02, peaceful=1, asleep=1 })
des.monster({ id = "prisoner", x=13, y=04, peaceful=1 })
des.monster({ id = "prisoner", x=13, y=06, peaceful=1, asleep=1 })
des.monster({ id = "prisoner", x=23, y=00, peaceful=1 })
des.monster({ id = "prisoner", x=23, y=02, peaceful=1, asleep=1 })
des.monster({ id = "prisoner", x=23, y=04, peaceful=1 })
des.monster({ id = "prisoner", x=23, y=06, peaceful=1, asleep=1 })

des.monster({ class = "U", x=17, y=02, peaceful=0 })
des.monster({ class = "U", x=18, y=02, peaceful=0 })
des.monster({ class = "U", x=19, y=02, peaceful=0 })

-- Random monsters.
des.monster("The First Evil",65,09)

des.monster("U", 57,09)
des.monster("U", 58,09)
des.monster("U", 59,09)
for i = 1, 8 do
   des.monster("human mummy");
end

des.monster("M")
des.monster("M")
des.monster("vampire")
des.monster("vampire")
des.monster("vampire")
des.monster("vampire")

des.monster("U")
des.monster("U")
des.monster("V")
des.monster("V")
