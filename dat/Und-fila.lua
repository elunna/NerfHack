--
--       The "fill" levels for the quest.
--
--       These levels are used to fill out any levels not occupied by specific
--       levels as defined above. "filla" is the upper filler, between the
--       start and locate levels, and "fillb" the lower between the locate
--       and goal levels.
--
des.level_flags("graveyard", "hardfloor")

des.room({ type = "ordinary",
           contents = function()
              des.stair("up")
              des.object()
              des.monster("human mummy")
              des.monster("vampire")
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.monster("human mummy")
              des.monster("vampire")
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.object()
              des.monster("human mummy")
              des.monster("vampire")
           end
})

des.room({ type = "morgue",
           contents = function()
              des.stair("down")
              des.object()
              des.trap()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.trap()
              des.monster("human mummy")
              des.monster("vampire")
           end
})

des.room({ type = "morgue",
           contents = function()
              des.object()
              des.trap()
           end
})

des.random_corridors()
