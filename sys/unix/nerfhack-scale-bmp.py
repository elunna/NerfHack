#!/usr/bin/env python3
"""Nearest-neighbor integer upscale of an 8-bit indexed Windows BMP.

Used to generate NerfHack's larger tile sheets (32x32, 64x64, ...) from the
base 16x16 tiles.bmp that `tile2bmp` produces at build time. Every source
pixel is replicated into an NxN block, so the palette and every color index
are preserved exactly - this is a pure pixel-duplication scale, not a smooth
resample, matching how the original tilesets/ bitmaps were produced (see
sys/unix/nerfhack-gen-tilesets.sh).

Only supports the uncompressed 8-bit indexed BMP format that tile2bmp.c
(win/share/tile2bmp.c) writes: BITMAPFILEHEADER + 40-byte BITMAPINFOHEADER +
256-entry RGBQUAD palette + BI_RGB pixel data, rows padded to 4 bytes.

Usage:
    nerfhack-scale-bmp.py <factor> <input.bmp> <output.bmp>
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
    new_width, new_height, _new_row_bytes, new_pixels = scale_nearest_neighbor(
        width, height, row_bytes, pixels, factor)
    write_bmp(out_path, new_width, new_height, palette, new_pixels)

    sys.stderr.write(
        f"{in_path}: {width}x{height} -> {out_path}: {new_width}x{new_height} "
        f"({factor}x)\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
