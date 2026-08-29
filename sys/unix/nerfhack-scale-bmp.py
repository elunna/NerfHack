#!/usr/bin/env python3
"""Nearest-neighbor integer upscale of an 8-bit indexed Windows BMP.

Used to generate NerfHack's larger tile sheets (32x32, 64x64, ...) from the
base 16x16 tiles.bmp that `tile2bmp` produces at build time. Every source
pixel is replicated into an NxN block, so the palette and every color index
are preserved exactly - this is a pure pixel-duplication scale, not a smooth
resample, matching how the original tilesets/ bitmaps were produced (see
sys/unix/nerfhack-gen-tilesets.sh).

tile2bmp.c sizes its canvas with deliberate slack (room for a full extra
tile row, plus rounding in its own row/column math) rather than tightly to
the tile grid, so the sheet's height generally is NOT an exact multiple of
the tile size - only its width reliably is, since tiles are always laid out
40 per row. NetHack's own custom tile_file loader (initMapTiles() in
win/win32/mswproc.c) requires both dimensions to divide evenly by
tile_width/tile_height, or it rejects the file outright ("Tiles bitmap does
not match tile_width and tile_height options"). Before scaling, this script
crops away that trailing blank padding down to a clean multiple of the tile
size, so every sheet it produces - including a 1x "fix in place" pass on the
base sheet itself - is directly usable via tile_file. Tiles are written
top-aligned (tile 0 at the visual top), so the padding is always a
contiguous blank region that can be safely identified by content and
trimmed without touching any real tile.

Only supports the uncompressed 8-bit indexed BMP format that tile2bmp.c
(win/share/tile2bmp.c) writes: BITMAPFILEHEADER + 40-byte BITMAPINFOHEADER +
256-entry RGBQUAD palette + BI_RGB pixel data, rows padded to 4 bytes.

Usage:
    nerfhack-scale-bmp.py <factor> <input.bmp> <output.bmp>

factor 1 crops without changing the tile size - use it to fix up the base
sheet before scaling it further.
"""
import struct
import sys


def read_bmp(path):
    with open(path, "rb") as f:
        data = f.read()

    bfType, bfSize, _r1, _r2, bfOffBits = struct.unpack_from("<2sIHHI", data, 0)
    if bfType != b"BM":
        raise ValueError(f"{path}: not a BMP file")

    biSize, = struct.unpack_from("<I", data, 14)
    if biSize != 40:
        raise ValueError(f"{path}: unsupported header size {biSize} "
                          "(expected 40-byte BITMAPINFOHEADER)")

    (biWidth, biHeight, biPlanes, biBitCount, biCompression,
     biSizeImage) = struct.unpack_from("<iiHHII", data, 18)
    if biBitCount != 8:
        raise ValueError(f"{path}: unsupported bit depth {biBitCount} "
                          "(expected 8-bit indexed)")
    if biCompression != 0:
        raise ValueError(f"{path}: unsupported compression {biCompression} "
                          "(expected BI_RGB/uncompressed)")
    if biHeight <= 0:
        raise ValueError(f"{path}: top-down BMPs are not supported")

    palette = data[54:54 + 256 * 4]
    row_bytes = ((biWidth * 8 + 31) & ~31) // 8
    pixels = data[bfOffBits:bfOffBits + row_bytes * biHeight]
    if len(pixels) != row_bytes * biHeight:
        raise ValueError(f"{path}: truncated pixel data")

    return biWidth, biHeight, palette, row_bytes, pixels


def crop_to_tile_multiple(width, height, row_bytes, pixels):
    """Trim trailing blank rows so height is an exact multiple of the tile
    size (tiles are always laid out 40 per row, so width already is)."""
    tile_size = width // 40

    # BMPs are stored bottom-up: file row 0 is the visual bottom. tile2bmp
    # writes tiles top-aligned, ending exactly at the last file row, so any
    # padding is a single contiguous blank region starting at file row 0.
    # Find the first file row (scanning up from 0) that has any non-zero
    # (non-background) byte - that's where real tile content begins.
    first_content_row = height
    for r in range(height):
        row = pixels[r * row_bytes: r * row_bytes + width]
        if any(b != 0 for b in row):
            first_content_row = r
            break

    needed_height = height - first_content_row
    remainder = needed_height % tile_size
    if remainder != 0:
        # keep a few extra (still-blank, already verified) rows so the
        # result lands exactly on a tile-size boundary
        needed_height += tile_size - remainder

    crop_rows = height - needed_height
    if crop_rows <= 0:
        return height, pixels

    return needed_height, pixels[crop_rows * row_bytes:]


def scale_nearest_neighbor(width, height, row_bytes, pixels, factor):
    new_width = width * factor
    new_height = height * factor
    new_row_bytes = ((new_width * 8 + 31) & ~31) // 8
    out = bytearray(new_row_bytes * new_height)

    for src_y in range(height):
        src_row = pixels[src_y * row_bytes: src_y * row_bytes + width]
        # replicate each source pixel `factor` times horizontally, once
        scaled_row = bytearray(new_width)
        pos = 0
        for value in src_row:
            scaled_row[pos:pos + factor] = bytes((value,)) * factor
            pos += factor
        # then replicate the resulting row `factor` times vertically
        for dy in range(factor):
            dst_y = src_y * factor + dy
            out[dst_y * new_row_bytes: dst_y * new_row_bytes + new_width] = scaled_row

    return new_width, new_height, new_row_bytes, bytes(out)


def write_bmp(path, width, height, palette, pixels):
    header_size = 14 + 40 + len(palette)
    bfSize = header_size + len(pixels)

    with open(path, "wb") as f:
        f.write(struct.pack("<2sIHHI", b"BM", bfSize, 0, 0, header_size))
        f.write(struct.pack(
            "<IiiHHIIiiII",
            40, width, height, 1, 8, 0, len(pixels), 0, 0,
            len(palette) // 4, 0))
        f.write(palette)
        f.write(pixels)


def main():
    if len(sys.argv) != 4:
        sys.stderr.write(
            "usage: nerfhack-scale-bmp.py <factor> <input.bmp> <output.bmp>\n")
        return 1

    factor = int(sys.argv[1])
    in_path, out_path = sys.argv[2], sys.argv[3]
    if factor < 1:
        sys.stderr.write("factor must be a positive integer\n")
        return 1

    width, height, palette, row_bytes, pixels = read_bmp(in_path)
    cropped_height, cropped_pixels = crop_to_tile_multiple(
        width, height, row_bytes, pixels)
    new_width, new_height, _new_row_bytes, new_pixels = scale_nearest_neighbor(
        width, cropped_height, row_bytes, cropped_pixels, factor)
    write_bmp(out_path, new_width, new_height, palette, new_pixels)

    sys.stderr.write(
        f"{in_path}: {width}x{height} (cropped to {width}x{cropped_height}) "
        f"-> {out_path}: {new_width}x{new_height} ({factor}x)\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
