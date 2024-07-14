-- NetHack 3.6	dungeon dungeon.lua	$NHDT-Date: 1652196135 2022/05/10 15:22:15 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.4 $
-- Copyright (c) 1990-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- The dungeon description file.
dungeon = {
   {
      name = "The Dungeons of Doom",
      bonetag = "D",
      base = 30,
      range = 5,
      alignment = "unaligned",
      themerooms = "themerms.lua",
      branches = {
         {
            name = "The Gnomish Mines",
            base = 2,
            range = 3
         },
         {
            name = "Sokoban",
            chainlevel = "oracle",
            base = 1,
            direction = "up"
         },
         {
            name = "The Quest",
            chainlevel = "oracle",
            base = 6,
            range = 2,
            branchtype = "portal"
         },
         {
            name = "The Lost Tomb",
            base = 15,
            range = 4,
            direction = "down",
         },
         {
            name = "The Temple of Moloch",
            base = 20,
            range = 10,
            direction = "down",
         },
         {
            name = "Fort Ludios",
            base = 18,
            range = 4,
            branchtype = "portal"
         },
         {
            name = "Gehennom",
            chainlevel = "castle",
            base = 0,
            branchtype = "no_down"
         },
         {
            name = "The Elemental Planes",
            base = 1,
            branchtype = "no_down",
            direction = "up"
         }
      },
      levels = {
         {
            name = "oracle",
            bonetag = "O",
            base = 5,
            range = 5,
            alignment = "neutral",
            nlevels = 3
         },
         {
            name = "bigrm",
            bonetag = "B",
            base = 10,
            range = 3,
            chance = 40,
            nlevels = 11
         },
         {
            name = "medusa",
            base = -8,
            range = 4,
            nlevels = 4,
            alignment = "chaotic"
         },
         {
            name = "wizard1",
            base = -4,
            range = 1
         },
         {
            name = "wizard2",
            bonetag = "X",
            chainlevel = "wizard1",
            base = 1
         },
         {
            name = "wizard3",
            bonetag = "Y",
            chainlevel = "wizard1",
            base = 2
         },
         
         {
            name = "castle",
            base = -1
         }
      }
   },
   {
      name = "Gehennom",
      bonetag = "G",
      base = 4,
      range = 3,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      branches = {
         {
            name = "Vlad's Tower",
            base = 2,
            range = 2,
            direction = "up"
         }
      },
      levels = {
         {
            name = "valley",
            bonetag = "V",
            base = 1
         },
         {
            name = "sanctum",
            base = -1
         },
      }
   },
   {
      name = "The Gnomish Mines",
      bonetag = "M",
      base = 8,
      range = 2,
      alignment = "lawful",
      flags = { "mazelike" },
      lvlfill = "minefill",
      levels = {
         {
            name = "minetn",
            bonetag = "T",
            base = 3,
            range = 2,
            nlevels = 11,
            flags = "town"
         },
         {
            name = "minend",
--          3.7.0: minend changed to no-bones to simplify achievement tracking
--          bonetag = "E"
            base = -1,
            nlevels = 7
         },
      }
   },
   {
      name = "The Quest",
      bonetag = "Q",
      base = 5,
      range = 2,
      levels = {
         {
            name = "x-strt",
            base = 1,
            range = 1
         },
         {
            name = "x-loca",
            bonetag = "L",
            base = 3,
            range = 1
         },
         {
            name = "x-goal",
            base = -1
         },
      }
   },
   {
      name = "Sokoban",
      base = 4,
      alignment = "neutral",
      flags = { "mazelike" },
      entry = -1,
      levels = {
         {
            name = "soko1",
            base = 1,
            nlevels = 3
         },
         {
            name = "soko2",
            base = 2,
            nlevels = 5
         },
         {
            name = "soko3",
            base = 3,
            nlevels = 5
         },
         {
            name = "soko4",
            base = 4,
            nlevels = 3
         },
      }
   },
   {
      name = "Fort Ludios",
      base = 1,
      bonetag = "K",
      flags = { "mazelike" },
      alignment = "unaligned",
      levels = {
         {
            name = "knox",
            bonetag = "K",
            base = -1
         }
      }
   },
   {
      name = "The Lost Tomb",
      base = 1,
      bonetag = "Z",
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         {
            name = "tomb",
            bonetag = "Z",
            base = -1
         }
      }
   },
   {
      name = "The Temple of Moloch",
      base = 1,
      bonetag = "Y",
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         {
            name = "mtemple",
            bonetag = "Y",
            base = -1
         }
      }
   },
   {
      name = "Vlad's Tower",
      base = 3,
      bonetag = "T",
      protofile = "tower",
      alignment = "chaotic",
      flags = { "mazelike" },
      entry = -1,
      levels = {
         {
            name = "tower1",
            base = 1
         },
         {
            name = "tower2",
            base = 2
         },
         {
            name = "tower3",
            base = 3
         },
      }
   },
   {
      name = "The Elemental Planes",
      bonetag = "E",
      base = 6,
      alignment = "unaligned",
      flags = { "mazelike" },
      entry = -2,
      levels = {
         {
            name = "astral",
            base = 1
         },
         {
            name = "water",
            base = 2
         },
         {
            name = "fire",
            base = 3
         },
         {
            name = "air",
            base = 4
         },
         {
            name = "earth",
            base = 5
         },
         {
            name = "dummy",
            base = 6
         },
      }
   },
   {
      name = "The Tutorial",
      base = 2,
      flags = { "mazelike", "unconnected" },
      levels = {
         {
            name = "tut-1",
            base = 1,
         },
         {
            name = "tut-2",
            base = 2,
         },
      }
   },
}
