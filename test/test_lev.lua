
-- Test all of the special levels

function saferequire(file)
   if (not pcall(require, file)) then
       nh.pline("Cannot load level file '" .. file .. "'.");
       if (nhc.DLB == 1) then
           nh.pline("Maybe due to compile-time option DLB.")
       end
       return false;
   end
   return true;
end;

local special_levels = {
"air",
"asmode-1",
"asmode-2",
"astral",
"baalz-1",
"baalz-2",
"baalz-3",
"bigrm-1",
"bigrm-2",
"bigrm-3",
"bigrm-4",
"bigrm-5",
"bigrm-6",
"bigrm-7",
"bigrm-8",
"bigrm-9",
"bigrm-10",
"bigrm-11",
"bigrm-12",
"bigrm-13",
"bigrm-14",
"bigrm-15",
"bigrm-16",
"bigrm-17",
"bigrm-18",
"bigrm-19",
"bigrm-20",
"bigrm-21",
"castle-1",
"castle-2",
"castle-3",
"demo-1",
"demo-2",
"demo-3",
"dispat-1",
"dispat-2",
"dispat-3",
"earth",
"fakewiz1",
"fakewiz2",
"fire",
"geryon-1",
"geryon-2",
"juiblex",
"knox-1",
"knox-2",
"knox-3",
"medusa-1",
"medusa-2",
"medusa-3",
"medusa-4",
"minefill",
"minend-1",
"minend-2",
"minend-3",
"minend-4",
"minend-5",
"minend-6",
"minend-7",
"minetn-1",
"minetn-2",
"minetn-3",
"minetn-4",
"minetn-5",
"minetn-6",
"minetn-7",
"minetn-8",
"minetn-9",
"minetn-10",
"minetn-11",
"minetn-12",
"temple-1",
"temple-2",
"oracle",
"orcus-1",
"orcus-2",
"sanctm-1",
"sanctm-2",
"sanctm-3",
"soko1-1",
"soko1-2",
"soko1-3",
"soko1-4",
"soko1-5",
"soko1-6",
"soko1-7",
"soko1-8",
"soko2-1",
"soko2-2",
"soko2-3",
"soko2-4",
"soko2-5",
"soko2-6",
"soko3-1",
"soko3-2",
"soko3-3",
"soko3-4",
"soko3-5",
"soko3-6",
"soko3-7",
"soko3-8",
"soko4-1",
"soko4-2",
"soko4-3",
"soko4-4",
"soko4-5",
"soko4-6",
"soko4-7",
"soko4-8",
"soko5-1",
"soko5-2",
"soko5-3",
"soko5-4",
"soko5-5",
"soko5-6",
"soko5-7",
"soko5-8",
"tomb",
"tower1",
"tower2",
"tower3",
"valley-1",
"valley-2",
"valley-3",
"water",
"wizard1",
"wizard2",
"wizard3",
"yeenog-1",
"yeenog-2",
"yeenog-3",
}

local roles = { "Arc", "Bar", "Car", "Cav", "Hea", "Kni", "Mon", "Pri",
                "Ran", "Rog", "Sam", "Tou", "Und", "Val", "Wiz" }
local questlevs = { "fila", "filb", "goal", "loca", "strt" }

for _,role in ipairs(roles) do
   for _,qlev in ipairs(questlevs) do
      local lev = role .. "-" .. qlev
      table.insert(special_levels, lev)
   end
end

for _,lev in ipairs(special_levels) do
   des.reset_level();
   if (not saferequire(lev)) then
      error("Cannot load a required file.");
   end
   des.finalize_level();
end
