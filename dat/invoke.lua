
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "noflip");

local tmpbounds = selection.match("-");
local bnds = tmpbounds:bounds();
local bounds2 = selection.fillrect(bnds.lx, bnds.ly + 1, bnds.hx - 2, bnds.hy - 1);

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
local vibsq = des.map({ halign = "center", valign = "center", map = [[
00                PPPPPPPPPPPPPPPSPPPPPPPPP                
01          PPPPPPPP#####################PPPPPPPP          
02     PPPPPP#############LLLLLLLLL#############PPPPPP     
03  PPPP###########LLLLLLLL.......LLLLLLLL###########PPPP  
04PPP#######LLLLLLLLL........}}}........LLLLLLLLL#######PPP
05PP###LLLLLL...............}}}}}...............LLLLLL###PP
06P###LL...................}}}.}}}...................LL###P
07PP###LLLLLL...............}}}}}...............LLLLLL###PP
08PPP#######LLLLLLLLL........}}}........LLLLLLLLL#######PPP
09  PPPP###########LLLLLLLL.......LLLLLLLL###########PPPP  
10     PPPPPP#############LLLLLLLLL#############PPPPPP     
11          PPPPPPPP#####################PPPPPPPP          
12                PPPPPPPPPPPPPPPPPPPPPPPPP                
]], contents = function(rm)
     des.levregion({ region={01,00,79,20}, region_islev=1, exclude={0,0,56,12}, type="stair-up" })
     des.mazewalk(01,03,"west")
    
end
});
des.trap({ type = "vibrating square", x = 39, y = 11 })

local protected = bounds2:negate() | vibsq;
hell_tweaks(protected);

