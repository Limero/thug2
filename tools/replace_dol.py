#!/usr/bin/env python3
"""Replace the boot main.dol inside a GameCube ISO, in place.

The GC disc header stores the file offset of the boot DOL at offset 0x420.
We overwrite the DOL bytes there directly. The built DOL for G2TE52 is
byte-identical to the original (same size), so no FST / layout surgery is
needed; if a future DOL is smaller, the remainder is zero-padded.

Usage: replace_dol.py <game.iso> <new_main.dol>
Note: the input must be a plain ISO. Convert RVZ first, e.g. with
Dolphin's CLI:  dolphin-tool convert -i game.rvz -o game.iso -f iso
"""
import os
import struct
import sys


def dol_size(data: bytes) -> int:
    """Total file size of a DOL from its header: max(file_off[i] + size[i])
    over all 18 sections present in the file (file offset != 0)."""
    offs = struct.unpack_from(">18I", data, 0)
    sizes = struct.unpack_from(">18I", data, 0x90)
    return max(o + s for o, s in zip(offs, sizes) if o != 0)


def main() -> None:
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)
    iso_path, dol_path = sys.argv[1], sys.argv[2]

    with open(iso_path, "r+b") as iso:
        total = os.path.getsize(iso_path)
        iso.seek(0)
        header = iso.read(0x440)

        boot_off = struct.unpack_from(">I", header, 0x420)[0]
        if not (0x2460 <= boot_off < total):
            print(f"ERROR: boot DOL offset 0x{boot_off:X} looks invalid", file=sys.stderr)
            sys.exit(1)

        iso.seek(boot_off)
        old_head = iso.read(0x100)
        old_size = dol_size(old_head)
        if old_size <= 0 or boot_off + old_size > total:
            print(f"ERROR: stored DOL size {old_size} invalid", file=sys.stderr)
            sys.exit(1)

        with open(dol_path, "rb") as f:
            new = f.read()
        if len(new) > old_size:
            print(
                f"ERROR: new DOL is {len(new)} bytes but only {old_size} are stored; "
                f"cannot grow in place",
                file=sys.stderr,
            )
            sys.exit(1)

        iso.seek(boot_off)
        iso.write(new)
        if len(new) < old_size:
            iso.write(b"\x00" * (old_size - len(new)))
        iso.flush()
        print(f"OK: wrote {len(new)} bytes at 0x{boot_off:X} (stored region {old_size})")
        print(f"    {dol_path} -> {iso_path}")


if __name__ == "__main__":
    main()
