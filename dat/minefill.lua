-- NetHack mines minefill.lua	$NHDT-Date: 1652196028 2022/05/10 15:20:28 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.3 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--

--    The "fill" level for the mines.
--
--    This level is used to fill out any levels not occupied by
--    specific levels.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.level_init({ style="mines", fg=".", bg=" ", smoothed=true, joined=true, walled=true })

-- Light variation
-- Copied from bigrm-2
if percent(7) then
   local darkness;

   local choice = math.random(0, 3)
   if choice == 0 then
      darkness = selection.area(01,07,22,09)
         | selection.area(24,01,50,05)
         | selection.area(24,11,50,16)
         | selection.area(52,07,73,09);
   elseif choice == 1 then
      darkness = selection.area(24,01,50,16);
   elseif choice == 2 then
      darkness = selection.area(01,01,22,16)
         | selection.area(52,01,73,16);
   end

   if darkness ~= nil then
      des.region(darkness,"unlit");
   end
end
   --
des.stair("up")
des.stair("down")
--
for i = 1,math.random(2, 5) do
   des.object("*")
end
des.object("(")
for i = 1,math.random(2, 4) do
   des.object()
end
if percent(75) then
   for i = 1,math.random(1, 2) do
      des.object("boulder")
   end
end
--
for i = 1,math.random(6, 8) do
   des.monster("gnome")
end
des.monster("gnome lord")
des.monster("dwarf")
des.monster("dwarf")
des.monster("G")
des.monster("G")
des.monster(percent(50) and "h" or "G")
--
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
