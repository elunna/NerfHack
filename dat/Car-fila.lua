-- NetHack 3.6	Cartomancer.des	$NHDT-Date: 1432512783 2015/05/25 00:13:03 $  $NHDT-Branch: master $:$NHDT-Revision: 1.8 $
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
des.level_flags("noflip")
--
des.room({type="ordinary", 
        contents=function()
            des.stair("up")
            des.object()
            des.monster({ class = "N", peaceful = 0 })
        end
});

des.room({type="ordinary", 
        contents=function()
          des.object()
          des.object()
          des.monster({ class = "N", peaceful = 0 })
        end
});

des.room({type="ordinary", 
        contents=function()
          des.object()
          des.trap()
          des.object()
          des.monster("cobra")
          des.monster("cobra")
        end
});

des.room({type="ordinary", 
        contents=function()
          des.stair("down")
          des.object()
          des.trap()
          des.monster({ class = "S", peaceful = 0 })
          des.monster("guardian naga")
        end
});

des.room({type="ordinary", 
        contents=function()
          des.object()
          des.object()
          des.trap()
          des.monster({ class = "S", peaceful = 0 })
        end
});

des.room({type="ordinary", 
        contents=function()
          des.object()
          des.trap()
          des.monster({ class = "N", peaceful = 0 })
        end
});

des.random_corridors()
