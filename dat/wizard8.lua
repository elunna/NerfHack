-- # Bottom level of Sheol
-- LEVEL: "palace_e"

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "solidify")

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "center", valign = "center", map = [[
00                                                                            
01           -------------------------------------------------                
02         ---...............................................-----            
03        --..........................................ZZZZZZ.....----         
04        |.....--........--......................ZZZZZ....ZZZZZ....---       
05        |....|  |......|  |.....-............ZZZZ............ZZZZ...---     
06      ---....|  |......|  |....| |..--.T...ZZZ.....T...T...T....ZZZ...--    
07      |.......--...T....--...T..-...--...ZZZ......................ZZZ..--   
08   ----.................................ZZ..........................ZZ..-   
09   |...............{.........{.........ZZ....................\.......ZZ.-   
10   ----.................................ZZ..........................ZZ..-   
11      |.......--...T....--...T..-...--...ZZZ......................ZZZ..--   
12      ---....|  |......|  |....| |..--.T...ZZZ.....T...T...T....ZZZ...--    
13        |....|  |......|  |.....-............ZZZZ............ZZZZ...---     
14        |.....--........--......................ZZZZZ....ZZZZZ....---       
15        --..........................................ZZZZZZ.....----         
16         ---...............................................-----            
17           -------------------------------------------------                
18                                                                            
19                                                                            
]] });

des.levregion({ type="branch", region={04,09,04,09} })
des.ladder("up", 55,09)

des.non_diggable()
des.non_passwall()
   
des.monster({ id = "Executioner", x=61, y=09, asleep=1 })

if percent(50) then
    if percent(50) then
        des.terrain({39,09}, ".")
        des.terrain({40,09}, ".")
    else
        des.terrain({69,09}, ".")
        des.terrain({70,09}, ".")
    end
else
    if percent(50) then
        des.terrain({54,03}, ".")
        des.terrain({55,03}, ".")
    else
        des.terrain({54,15}, ".")
        des.terrain({55,15}, ".")
    end
end


des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()

-- # Binding of Isaac
if percent(10) then
    des.grave({ text = "Isaac - Sacrificed by Mother" });
end
if percent(30) then
    des.grave({ text = "Guppy - Beloved by Flies" });
end

-- # Some serious slimy fun, these should freeze the player in place
-- # while the Executioner slices them into little pieces.
-- In UnNetHack these were blue slimes
des.monster("green slime")
des.monster("green slime")
des.monster("green slime")
des.monster("green slime")

des.monster("green slime")
des.monster("green slime")
des.monster("green slime")
des.monster("green slime")

-- white nagas replaced with white dragons
des.monster("white dragon")
des.monster("white dragon")
des.monster("white dragon")
des.monster("white dragon")

-- ice golems replaced with iron and glass
des.monster("iron golem")
des.monster("iron golem")
des.monster("glass golem")
des.monster("glass golem")

des.monster("dark Angel")
des.monster("dark Angel")
des.monster("dark Angel")

des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
des.monster()
