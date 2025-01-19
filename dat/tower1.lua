-- NetHack tower tower1.lua	$NHDT-Date: 1717178759 2024/05/31 18:05:59 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989 by Jean-Christophe Collet
-- NetHack may be freely redistributed.  See license for details.
--
--
-- Upper stage of Vlad's tower
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor", "solidify", "noflip")
des.map({ halign = "half-left", valign = "center", map = [[
  --- --- ---  
  |.| |.| |.|  
---S---S---S---
|.......+.+...|
---+-----.-----
  |...\.|.+.|  
---+-----.-----
|.......+.+...|
---S---S---S---
  |.| |.| |.|  
  --- --- ---  
]] });

local niches = { {03,01}, {03,09}, {07,01}, {07,09}, {11,01}, {11,09} };
shuffle(niches);

des.ladder("down", 11,05)
-- The lord and his court
des.monster("Vlad the Impaler", 06, 05)
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
-- The doors
des.door("closed",08,03)
des.door("closed",10,03)
des.door("closed",03,04)
des.door("locked",10,05)
des.door("locked",08,07)
des.door("locked",10,07)
des.door("closed",03,06)
-- treasures
des.object({ id = "chest", x = 07, y = 05,
            contents = function()
               -- This is converted into a zappable scroll of wishing
               des.object("wishing");
            end
});

des.object("chest",niches[6])
des.object("chest",niches[1])
des.object("chest",niches[2])
des.object("chest",niches[3])
des.object({ id = "chest", coord=niches[4],
             contents = function()
                des.object({ id = "rock", quantity=math.random(4,8) })
             end
});
des.object({ id = "chest", coord=niches[5],
             contents = function()
                des.object({ id = "flint", quantity=math.random(4,8) })
             end
});
-- We have to protect the tower against outside attacks
des.non_diggable(selection.area(00,00,14,10))
