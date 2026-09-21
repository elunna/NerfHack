#!/bin/bash
# Copyright (c) Erik Lunna, 2023-2026.
# NetHack may be freely redistributed.  See license for details.
#
# Renumber the shared tile source files so their "tile N" indices are
# consecutive again.  For each of win/share/{monsters,objects,other}.txt this
# runs win/share/tile-renumberer.awk -- which rewrites every "# tile N (name)"
# marker with a fresh sequential number, starting from 0 -- over the file in
# place.  Run it after adding, removing, or reordering monster or object tiles
# so the tile sources line up with the game's monster/object ordering again.
#
# Can be run from anywhere; it always operates on the repository's win/share.

# operate from the repository root, wherever this was invoked from
cd "$(dirname -- "$0")/../.." || exit 1

# Re-order monsters.txt
awk -f win/share/tile-renumberer.awk win/share/monsters.txt > win/share/mtmp.txt
rm -v win/share/monsters.txt
mv -v win/share/mtmp.txt win/share/monsters.txt

# Re-order objects.txt
awk -f win/share/tile-renumberer.awk win/share/objects.txt > win/share/otmp.txt
rm -v win/share/objects.txt
mv -v win/share/otmp.txt win/share/objects.txt

# Re-order other.txt
awk -f win/share/tile-renumberer.awk win/share/other.txt > win/share/rtmp.txt
rm -v win/share/other.txt
mv -v win/share/rtmp.txt win/share/other.txt
