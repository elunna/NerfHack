-- NetHack 3.6	dungeon dungeon.lua	$NHDT-Date: 1652196135 2022/05/10 15:22:15 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.4 $
-- Copyright (c) 1990-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- The dungeon description file.
dungeon = {
   {
      name = "The Dungeons of Doom",
      bonetag = "D",
      base = 40,
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
            name = "Head of the Lethe River",
            chainlevel = "leth-b",
            base = 0,
            direction = "up"
         },
         {
            name = "The Lost Tomb",
            base = 15,
            range = 4,
            direction = "down",
         },
         {
            name = "The Temple of Moloch",
            base = 21,
            range = 4,
            direction = "down",
         },
         {
            name = "Fort Ludios",
            base = 18,
            range = 4,
            branchtype = "portal",
         },
         {
            name = "Gehennom",
            chainlevel = "leth-z",
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
            base = 8,
            range = 4,
            alignment = "neutral",
            nlevels = 3
         },
         {
            name = "bigrm",
            bonetag = "B",
            base = 10,
            range = 3,
            chance = 40,
            nlevels = 21
         },
         {
            name = "bigrm",
            bonetag = "D",
            base = 23,
            range = 3,
            chance = 40,
            nlevels = 21
         },
         {
            name = "medusa",
            base = -12,
            range = 4,
            nlevels = 4,
            alignment = "chaotic"
         },
         {
            name = "castle",
            base = -8,
            nlevels = 3,
         },
         {
            name = "leth-b",
            base = -7
         },
         {
            name = "leth-c",
            base = -6,
            nlevels = 2,
            chance = 50
         },
         {
            name = "leth-d",
            base = -5,
            nlevels = 2,
            chance = 25
         },
         {
            name = "leth-e",
            base = -4,
            chance = 50
         },
         {
            name = "leth-f",
            base = -3,
            chance = 50,
         },
         {
            name = "leth-g",
            base = -2,
            chance = 25,
         },
         {
            name = "leth-z",
            base = -1
         },
      }
   },
   {
      name = "Gehennom",
      bonetag = "G",
      base = 24,
      range = 5,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      branches = {
         {
            name = "Vlad's Tower",
            base = 9,
            range = 5,
            direction = "up"
         },
         {
            name = "The Wizard's Tower",
            chainlevel = "nkai-b",
            base = 0,
            branchtype = "portal"
         },
      },
      levels = {
         {
            name = "valley",
            bonetag = "V",
            nlevels = 3,
            base = 1
         },
         {
            name = "bridge",
            bonetag = "E",
            base = 2
         },
         {
            name = "nkai-a",
            nlevels = 2,
            base = -5
         },
         {
            name = "nkai-b",
            base = -4
         },
         {
            name = "nkai-c",
            base = -3
         },
         {
            name = "nkai-z",
            base = -2
         },
         {
            name = "sanctm",
            nlevels = 2,
            base = -1
         },
         {
            name = "juiblex",
            bonetag = "J",
            base = 4,
            range = 4
         },
         {
            name = "geryon",
            bonetag = "G",
            nlevels = 2,
            base = 2,
            chance = 50,
            range = 16
         },
         {
            name = "mephisto",
            bonetag = "M",
            base = 2,
            chance = 50,
            range = 6
         },
         {
            name = "baalz",
            bonetag = "B",
            nlevels = 3,
            base = 6,
            range = 4
         },
         {
            name = "asmode",
            bonetag = "A",
            nlevels = 2,
            base = 2,
            range = 6
         },
         {
            name = "orcus",
            bonetag = "O",
            nlevels = 2,
            base = 10,
            range = 6
         },
         {
            name = "dispat",
            bonetag = "R",
            nlevels = 3,
            base = 10,
            chance = 50,
            range = 6
         },
         {
            name = "yeenog",
            bonetag = "Y",
            nlevels = 3,
            base = 10,
            chance = 50,
            range = 6
         },
         {
            name = "demo",
            bonetag = "D",
            nlevels = 3,
            base = 13,
            chance = 50,
            range = 6
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
      base = 6,
      alignment = "neutral",
      flags = { "mazelike" },
      entry = -1,
      levels = {
         {
            name = "soko1",
            base = 1,
            nlevels = 8
         },
         {
            name = "soko2",
            base = 2,
            nlevels = 6
         },
         {
            name = "soko3",
            base = 3,
            nlevels = 8
         },
         {
            name = "soko4",
            base = 4,
            nlevels = 8
         },
         {
            name = "soko5",
            base = 5,
            nlevels = 8
         },
         {
            name = "townfill",
            base = 6,
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
            base = -1,
            nlevels = 3,
         }
      }
   },
   {
      name = "Head of the Lethe River",
      base = 1,
      alignment = "chaotic",
      flags = { "mazelike" },
      entry = -1,
      levels = {
         {
            name = "leth-a",
            base = 1,
            nlevels = 2
         },
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
            base = -1,
            nlevels = 2,
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
            name = "temple",
            bonetag = "Y",
            base = -1,
            nlevels = 2,
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
      name = "The Wizard's Tower",
      bonetag = "W",
      base = 3,
      flags = { "mazelike" },
      alignment = "unaligned",
      entry = -1,
      levels = {
         {
            name = "wizard1",
            base = 1
         },
         {
            name = "wizard2",
            bonetag = "X",
            base = 2
         },
         {
            name = "wizard3",
            bonetag = "Y",
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
