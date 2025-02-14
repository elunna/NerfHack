-- NetHack 3.6	tower.des	$NHDT-Date: 1432512784 2015/05/25 00:13:04 $  $NHDT-Branch: master $:$NHDT-Revision: 1.9 $
--	Copyright (c) 1989 by Jean-Christophe Collet
-- NetHack may be freely redistributed.  See license for details.
--
-- Upper stage of Vlad's tower
-- MAZE:"tower1",' '
-- Ported from EvilHack
-- Converted to LUA by hackemslashem

des.level_init({ style = "solidfill", fg = " " });
des.level_flags("mazelevel", "noteleport", "hardfloor", "solidify")

--0         1         2         3
--0123456789012345678901234567890
des.map({ halign = "half-left", valign = "center", map = [[
00  --- ---   ------   --- ---  
01  |.| |.|  -|....|-  |.| |.|  
02---S---S---|-FFFF-|---S---S---
03|..........S......|.........\|
04|..........|......|..........|
05-FF-....-FF|--++--|FF--++--FF-
06 ..F....F..|......|..F....F.. 
07 . |....|..F......F..|....| . 
08 . |....|..F......F..|....| . 
09 ..F....F..|......|..F....F.. 
10-FF--++--FF|--++--|FF-....-FF-
11|..........|......|..........|
12|..........|......S..........|
13---S---S---|-FFFF-|---S---S---
14  |.| |.|  -|....|-  |.| |.|  
15  --- ---   ------   --- ---  
]] });

-- Random 8 niches
local niches = { {03,01}, {07,01}, {22,01}, {26,01},
                 {03,14}, {07,14}, {22,14}, {26,14} }
shuffle(niches);
des.ladder("down", 01,12)

-- The lord and his court
des.monster("Vlad the Impaler", 28,03)

des.monster("V",niches[1])
des.monster("V",niches[2])
des.monster("V",niches[3])

-- The brides; they weren't named in Bram Stoker's original _Dracula_
-- and when appearing in umpteen subsequent books and movies there is
-- no consensus for their names.  According to the Wikipedia entry for
-- "Brides of Dracula", the "Czechoslovakian TV film Hrabe Drakula (1971)"
-- gave them titles rather than (or perhaps in addition to) specific names
-- and we use those titles here.  Marking them as 'waiting' forces them to
-- start in vampire form instead of vampshifted into bat/fog/wolf form.
local Vgenod = nh.is_genocided("vampire");
local Vnames = { nil, nil, nil };
if (not Vgenod) then
   Vnames = { "Madame", "Marquise", "Countess" };
end
des.monster({ id="vampire lady", coord=niches[4], name=Vnames[1], waiting=1 })
des.monster({ id="vampire lady", coord=niches[5], name=Vnames[2], waiting=1 })
des.monster({ id="vampire lady", coord=niches[6], name=Vnames[3], waiting=1 })
des.monster("&",niches[8])


-- MONSTER:('U',"shambling horror"),(14,01)
-- MONSTER:('U',"shambling horror"),(15,14)
des.monster("U", 14,01)
des.monster("U", 15,14)

-- MONSTER:('z',"skeleton warrior"),(13,07)
-- MONSTER:('z',"skeleton warrior"),(13,08)
-- MONSTER:('z',"skeleton warrior"),(16,07)
-- MONSTER:('z',"skeleton warrior"),(16,08)
des.monster("skeleton", 13,07)
des.monster("skeleton", 13,08)
des.monster("skeleton", 16,07)
des.monster("skeleton", 16,08)

des.monster("vampire royal", 14,07)
des.monster("vampire royal", 15,07)

des.monster("vampire mage", 14,08)
des.monster("vampire mage", 15,08)

des.monster("hell hound", 23,04)
des.monster("hell hound", 24,04)

-- What is Vlad keeping in the closet??
local prisoners = {
    "orb weaver", "third eye", "glowing eye", "prisoner",
    "couatl", "eye of fear and flame", "pyrolisk", "barghest",
    "monstrous spider", "worm that walks", "hunger hulk",
    "black dragon", "green dragon", "yellow dragon", "shimmering dragon",
 };
shuffle(prisoners)
des.monster({ id = prisoners[1], x = 02, y = 06, peaceful=0 })
des.monster({ id = prisoners[2], x = 09, y = 06, peaceful=0 })
des.monster({ id = prisoners[3], x = 20, y = 06, peaceful=0 })
des.monster({ id = prisoners[4], x = 27, y = 06, peaceful=0 })
des.monster({ id = prisoners[5], x = 02, y = 09, peaceful=0 })
des.monster({ id = prisoners[6], x = 09, y = 09, peaceful=0 })
des.monster({ id = prisoners[7], x = 20, y = 09, peaceful=0 })
des.monster({ id = prisoners[8], x = 27, y = 09, peaceful=0 })

-- Locked doors
des.door("locked",05,10)
des.door("locked",06,10)
des.door("locked",14,05)
des.door("locked",15,05)
des.door("locked",14,10)
des.door("locked",15,10)
des.door("locked",23,05)
des.door("locked",24,05)

-- treasures
des.object({ id = "chest", x = 28, y = 04,
            contents = function()
               -- This is converted into a zappable scroll of wishing
               des.object("wishing");
            end
});

des.object("chest", 13,01)
des.object("chest", 16,14)
des.object("chest",niches[1])
des.object("chest",niches[2])
des.object("chest",niches[3])
des.object("chest",niches[4])
des.object("chest",niches[5])

des.object({ id = "chest", coord=niches[6],
             contents = function()
                des.object({ id = "rock", quantity=math.random(4,8) })
             end
});
des.object({ id = "chest", coord=niches[7],
             contents = function()
                des.object({ id = "flint", quantity=math.random(4,8) })
             end
});
des.object("chest",niches[8])

-- Random corpses of past adventurers
-- note: no priest(esse)s or monks - maybe Moloch has a *special*
--       fate reserved for members of *those* classes.
des.object({ id="corpse",montype="caveman" })
des.object({ id="corpse",montype="healer" })
des.object({ id="corpse",montype="wizard" })
des.object({ id="corpse",montype="rogue" })
des.object({ id="corpse",montype="archeologist" })
des.object({ id="corpse",montype="tourist" })
des.object({ id="corpse",montype="samurai" })
des.object({ id="corpse",montype="ranger" })

-- Walls in the tower are non diggable and non passable
des.non_diggable(selection.area(00,00,29,15))
-- NON_PASSWALL:(00,00,29,15)
