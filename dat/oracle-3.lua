-- Version 3: Ported from SpliceHack

des.level_flags("noflip");

des.room({ type ="delphi", lit = 1, x=3, y=3, xalign="center", yalign="center", w=11, h=9,
           contents = function()
               -- Make a squarish ring of pools around the Oracle, 3 spaces out
               local ring = selection.rect(2,1,8,7)
               -- cut corners
               ring:set(2,1, 0)
               ring:set(2,7, 0)
               ring:set(8,1, 0)
               ring:set(8,7, 0)

               -- Close off three of the four passages into the center; there are also only
               -- three fountains; make sure that no fountain is aligned with the open square
               orthopool = { {5,1}, {2,4}, {8,4}, {5,7} }
               fountain = { {5,2}, {3,4}, {7,4}, {5,6} }
               local dir = math.random(1, #orthopool)
               for i=1,#orthopool do
                  if i == dir then
                     ring:set(orthopool[i][1], orthopool[i][2], 0)
                  else
                     des.feature("fountain", fountain[i][1], fountain[i][2])
                  end
               end

               -- now actually make the ring
               if percent(99) then
                  des.terrain({ selection=ring, typ="}", lit=1 })
               else
                  des.terrain({ selection=ring, typ="L", lit=1 })
               end

               -- four trees
               des.feature("tree", 3,2)
               des.feature("tree", 3,6)
               des.feature("tree", 7,2)
               des.feature("tree", 7,6)

               statuelocs = { {0,0}, {10,0}, {0,8}, {10,8} }
               shuffle(statuelocs)
               des.object({ id = "statue", coord = statuelocs[1], montype = "snake", historic = 1 })
               des.object({ id = "statue", coord = statuelocs[2], montype = "guardian naga", historic = 1 })
               des.object({ id = "statue", coord = statuelocs[3], montype = "shark", historic = 1 })
               des.object({ id = "statue", coord = statuelocs[4], montype = "water nymph", historic = 1 })

               des.monster("Oracle", 5, 4)

               des.monster()
               des.monster()
            end
})

des.room({ contents = function()
                 des.stair("up")
                 des.object()
              end
})

des.room({ contents = function()
                 des.stair("down")
                 des.object()
                 des.trap()
                 des.monster()
                 des.monster()
              end
})

des.room({ contents = function()
                 des.object()
                 des.object()
                 des.monster()
              end
})

des.room({ contents = function()
                 des.object()
                 des.trap()
                 des.monster()
              end
})

des.room({ contents = function()
                 des.object()
                 des.trap()
                 des.monster()
              end
})

-- Keep thy enemies close...
des.object({ id = "statue", montype = "woodchuck", historic = 1 })

des.random_corridors()
