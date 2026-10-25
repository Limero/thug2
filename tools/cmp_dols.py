#!/usr/bin/env python3
"""Compare two DOLs: report differing file ranges and disassemble the first few."""
import struct
import sys

from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

HDR = 0x100


def read_dol(path):
    with open(path, "rb") as f:
        data = f.read()
    offs = struct.unpack_from(">18I", data, 0)
    addrs = struct.unpack_from(">18I", data, 0x48)
    sizes = struct.unpack_from(">18I", data, 0x90)
    return data, offs, addrs, sizes


def off_to_vaddr(offs, addrs, sizes, off):
    for i in range(18):
        if offs[i] <= off < offs[i] + sizes[i]:
            return addrs[i] + (off - offs[i])
    return None


def main():
    a_path, b_path = sys.argv[1], sys.argv[2]
    a, a_offs, a_addrs, a_sizes = read_dol(a_path)
    b, b_offs, b_addrs, b_sizes = read_dol(b_path)
    if len(a) != len(b):
        print(f"size mismatch: {len(a)} vs {len(b)}")

    # collect differing word-aligned ranges
    n = min(len(a), len(b))
    diff_off = [i for i in range(HDR, n, 4) if a[i:i+4] != b[i:i+4]]
    print(f"total differing words: {len(diff_off)}")

    # group into ranges
    ranges = []
    start = prev = None
    for o in diff_off:
        if start is None:
            start = prev = o
        elif o == prev + 4:
            prev = o
        else:
            ranges.append((start, prev))
            start = prev = o
    if start is not None:
        ranges.append((start, prev))
    print(f"differing ranges: {len(ranges)}")
    for r in ranges[:15]:
        va = off_to_vaddr(a_offs, a_addrs, a_sizes, r[0])
        va_end = off_to_vaddr(a_offs, a_addrs, a_sizes, r[1])
        print(f"  file 0x{r[0]:X}-0x{r[1]:X} vaddr {va and hex(va)}-{va_end and hex(va_end)}")

    # disassemble first differing range in both
    if ranges:
        r = ranges[0]
        md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
        va = off_to_vaddr(a_offs, a_addrs, a_sizes, r[0])
        if va is None:
            va = 0x80000000
        # round down to 4
        off = r[0] & ~3
        print("\n--- first differing range (original) ---")
        for insn in md.disasm(a[off:r[1]+4], va - (r[0] - off)):
            print(f"0x{insn.address:08X}: {insn.mnemonic:12s} {insn.op_str}")
        print("\n--- (built) ---")
        for insn in md.disasm(b[off:r[1]+4], va - (r[0] - off)):
            print(f"0x{insn.address:08X}: {insn.mnemonic:12s} {insn.op_str}")


if __name__ == "__main__":
    main()
