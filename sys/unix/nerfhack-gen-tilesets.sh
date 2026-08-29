#!/bin/sh
# nerfhack-gen-tilesets.sh - generate NerfHack's larger tile sheets.
#
# NerfHack's tile artwork is authored at a fixed 16x16 pixels per tile (see
# TILE_X/TILE_Y in win/share/tile.h) - there is no separate, independently
# drawn higher-resolution source art. The larger tilesets/tiles_*.bmp files
# once shipped in this repo (removed as out-of-date) were produced by
# building the normal 16x16 sheet with tile2bmp and then nearest-neighbor
# upscaling it by an integer factor, so pixels stay crisp instead of
# blurring. This script reproduces that pipeline from current game data, so
# it never depends on separately-maintained documentation again. See
# sys/windows/nerfhack-gen-tilesets.bat for the Windows equivalent.
#
# Usage:
#   sys/unix/nerfhack-gen-tilesets.sh [factor ...]
#
# With no arguments, generates the traditional set: 16x16 (1x), 32x32 (2x),
# 64x64 (4x), 128x128 (8x). Pass one or more factors to generate only those,
# e.g. `sys/unix/nerfhack-gen-tilesets.sh 2 4` for just 32x32 and 64x64.
#
# Output goes to tilesets/tiles_<N>x<N>.bmp under the repo root.

set -e

REPO_ROOT=$(git rev-parse --show-toplevel 2>/dev/null) || {
    echo "nerfhack-gen-tilesets.sh: must be run from within the NerfHack git repository" >&2
    exit 1
}
cd "$REPO_ROOT"

if ! command -v python3 >/dev/null 2>&1; then
    echo "nerfhack-gen-tilesets.sh: python3 is required but not found on PATH." >&2
    exit 1
fi

if [ ! -f Makefile ]; then
    echo "nerfhack-gen-tilesets.sh: no configured Makefile found." >&2
    echo "Run setup first, e.g.: sh sys/unix/setup.sh sys/unix/hints/linux.500" >&2
    exit 1
fi

echo "Building tile2bmp..." >&2
make -C util tile2bmp >&2

mkdir -p tilesets
BASE_TILE_PX=16
BASE_BMP="tilesets/tiles_${BASE_TILE_PX}x${BASE_TILE_PX}.bmp"
RAW_BMP="tilesets/.tiles_${BASE_TILE_PX}x${BASE_TILE_PX}_raw.bmp"

echo "Generating base ${BASE_TILE_PX}x${BASE_TILE_PX} tile sheet..." >&2
(cd util && ./tile2bmp "../$RAW_BMP")

# tile2bmp sizes its canvas with slack, so the raw sheet's height usually
# isn't an exact multiple of the tile size - NetHack's tile_file loader
# requires it to be, or it rejects the file. Crop that off (factor 1 = no
# resize) before it becomes the base every other size is scaled from.
python3 sys/unix/nerfhack-scale-bmp.py 1 "$RAW_BMP" "$BASE_BMP"
rm -f "$RAW_BMP"

if [ "$#" -gt 0 ]; then
    factors="$*"
else
    factors="1 2 4 8"
fi

for factor in $factors; do
    if [ "$factor" = "1" ]; then
        continue  # that's BASE_BMP itself
    fi
    size=$((BASE_TILE_PX * factor))
    out="tilesets/tiles_${size}x${size}.bmp"
    python3 sys/unix/nerfhack-scale-bmp.py "$factor" "$BASE_BMP" "$out"
done

echo "Done. See tilesets/" >&2
