"""Draws the ProjectorScaler icon and writes ProjectorScaler.ico plus a preview PNG.

Pure standard library (no Pillow): every size is rasterised on its own with 4x4
supersampling, so small sizes stay crisp instead of being a blurred 256 px downscale.

Design: a navy rounded tile (the panel's banner colour) holding a projector screen
outline; inside it an amber picture that is smaller than the screen, with white
corner handles at 32 px and up - "the projected image, scaled and draggable".

Usage:  python -I make_icon.py  ->  ProjectorScaler.ico, preview.png next to this file
"""
import os
import struct
import zlib

SIZES = [16, 20, 24, 32, 40, 48, 64, 256]
SS = 4  # supersampling per axis

NAVY_TOP = (36, 70, 110)
NAVY_BOTTOM = (19, 40, 68)
SCREEN = (214, 230, 245)
AMBER = (245, 166, 35)
WHITE = (255, 255, 255)
HANDLE_EDGE = (19, 46, 78)


def in_rrect(x, y, x0, y0, x1, y1, r):
    if x < x0 or x > x1 or y < y0 or y > y1:
        return False
    cx = min(max(x, x0 + r), x1 - r)
    cy = min(max(y, y0 + r), y1 - r)
    return (x - cx) ** 2 + (y - cy) ** 2 <= r * r


def shapes_for(size):
    """Shapes in pixel units for this size: list of (test, colour) painted in order."""
    s = float(size)
    small = size < 32
    out = []

    # Tile with a vertical gradient.
    m, rad = s * 0.03, s * 0.20
    def tile(x, y):
        return in_rrect(x, y, m, m, s - m, s - m, rad)
    out.append((tile, "gradient"))

    # Screen outline; stroke never thinner than one pixel.
    sx0, sy0, sx1, sy1 = s * 0.14, s * 0.18, s * 0.86, s * (0.76 if small else 0.70)
    sw = max(1.0, s * 0.05)
    sr = s * 0.05
    def screen(x, y):
        return in_rrect(x, y, sx0, sy0, sx1, sy1, sr) and not in_rrect(
            x, y, sx0 + sw, sy0 + sw, sx1 - sw, sy1 - sw, max(0.0, sr - sw))
    out.append((screen, SCREEN))

    if not small:
        # Stand: a short neck and a base, so the outline reads as a screen.
        def stand(x, y):
            neck = s * 0.47 <= x <= s * 0.53 and sy1 <= y <= s * 0.80
            base = in_rrect(x, y, s * 0.34, s * 0.78, s * 0.66, s * 0.83, s * 0.02)
            return neck or base
        out.append((stand, SCREEN))

    # The projected picture: smaller than the screen, off-centre to suggest it moved.
    if small:
        ix0, iy0, ix1, iy1 = s * 0.30, s * 0.34, s * 0.70, s * 0.62
    else:
        ix0, iy0, ix1, iy1 = s * 0.29, s * 0.31, s * 0.67, s * 0.56
    def picture(x, y):
        return in_rrect(x, y, ix0, iy0, ix1, iy1, s * 0.02)
    out.append((picture, AMBER))

    if not small:
        hs = s * 0.034  # half side of a handle
        edge = max(1.0, s * 0.014)
        corners = [(ix0, iy0), (ix1, iy0), (ix0, iy1), (ix1, iy1)]
        def handle_edge(x, y):
            return any(abs(x - cx) <= hs + edge and abs(y - cy) <= hs + edge for cx, cy in corners)
        def handle(x, y):
            return any(abs(x - cx) <= hs and abs(y - cy) <= hs for cx, cy in corners)
        out.append((handle_edge, HANDLE_EDGE))
        out.append((handle, WHITE))
    return out


def render(size):
    """Returns rows of (r, g, b, a) tuples, top row first."""
    shapes = shapes_for(size)
    rows = []
    for py in range(size):
        row = []
        for px in range(size):
            acc = [0.0, 0.0, 0.0, 0.0]  # premultiplied
            for sy in range(SS):
                for sx in range(SS):
                    x = px + (sx + 0.5) / SS
                    y = py + (sy + 0.5) / SS
                    col = None
                    for test, colour in shapes:
                        if test(x, y):
                            if colour == "gradient":
                                t = y / size
                                col = tuple(NAVY_TOP[i] + (NAVY_BOTTOM[i] - NAVY_TOP[i]) * t for i in range(3))
                            else:
                                col = colour
                    if col is not None:
                        acc[0] += col[0]; acc[1] += col[1]; acc[2] += col[2]; acc[3] += 1
            n = SS * SS
            a = acc[3] / n
            if a > 0:
                r, g, b = (acc[i] / acc[3] for i in range(3))
            else:
                r = g = b = 0
            row.append((round(r), round(g), round(b), round(a * 255)))
        rows.append(row)
    return rows


def png_bytes(rows):
    h, w = len(rows), len(rows[0])
    raw = b"".join(b"\x00" + bytes(c for px in row for c in px) for row in rows)
    def chunk(tag, data):
        return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF)
    return (b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
            + chunk(b"IDAT", zlib.compress(raw, 9)) + chunk(b"IEND", b""))


def dib_bytes(rows):
    """32-bit BGRA DIB as stored inside an .ico (height doubled, bottom-up, AND mask)."""
    size = len(rows)
    mask_stride = ((size + 31) // 32) * 4
    header = struct.pack("<IiiHHIIiiII", 40, size, size * 2, 1, 32, 0, 0, 0, 0, 0, 0)
    pixels = b"".join(bytes((b, g, r, a)) for row in reversed(rows) for (r, g, b, a) in row)
    mask = bytearray()
    for row in reversed(rows):
        bits = bytearray(mask_stride)
        for x, (_, _, _, a) in enumerate(row):
            if a == 0:
                bits[x // 8] |= 0x80 >> (x % 8)
        mask += bits
    return header + pixels + bytes(mask)


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    images = {size: render(size) for size in SIZES}
    blobs = [(size, png_bytes(images[size]) if size >= 256 else dib_bytes(images[size])) for size in SIZES]
    offset = 6 + 16 * len(blobs)
    directory, data = b"", b""
    for size, blob in blobs:
        dim = 0 if size >= 256 else size
        directory += struct.pack("<BBBBHHII", dim, dim, 0, 0, 1, 32, len(blob), offset + len(data))
        data += blob
    with open(os.path.join(here, "ProjectorScaler.ico"), "wb") as f:
        f.write(struct.pack("<HHH", 0, 1, len(blobs)) + directory + data)

    # Preview: 256 px, then each small size at 1:1 and enlarged 4x, on a light strip.
    big = images[256]
    pad, strip_h = 16, 256 + 2 * 16
    widths = [256] + [s * 4 for s in (16, 24, 32, 48)]
    total_w = pad + sum(w + pad for w in widths)
    canvas = [[(239, 243, 248, 255)] * total_w for _ in range(strip_h)]
    def paste(img, x0, y0, scale=1):
        for y, row in enumerate(img):
            for x, (r, g, b, a) in enumerate(row):
                for dy in range(scale):
                    for dx in range(scale):
                        br, bg_, bb, _ = canvas[y0 + y * scale + dy][x0 + x * scale + dx]
                        al = a / 255
                        canvas[y0 + y * scale + dy][x0 + x * scale + dx] = (
                            round(r * al + br * (1 - al)), round(g * al + bg_ * (1 - al)),
                            round(b * al + bb * (1 - al)), 255)
    x = pad
    paste(big, x, pad); x += 256 + pad
    for s in (16, 24, 32, 48):
        paste(images[s], x, pad + 256 - s * 4, 4); x += s * 4 + pad
    with open(os.path.join(here, "preview.png"), "wb") as f:
        f.write(png_bytes(canvas))
    print("ok", [s for s, _ in blobs])


if __name__ == "__main__":
    main()
