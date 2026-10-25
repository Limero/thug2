#!/usr/bin/env python3
"""Disassemble a region of a GameCube DOL using capstone (PPC/MPC750)."""
import struct
import sys

from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

DOL_HEADER = 0x100


def read_dol(path):
    with open(path, "rb") as f:
        data = f.read()
    n_sections = 18
    offs = struct.unpack_from(">18I", data, 0)
    addrs = struct.unpack_from(">18I", data, 0x48)
    sizes = struct.unpack_from(">18I", data, 0x90)
    bss_addr = struct.unpack_from(">I", data, 0xD8)[0]
    bss_size = struct.unpack_from(">I", data, 0xDC)[0]
    entry = struct.unpack_from(">I", data, 0xE0)[0]
    return data, offs, addrs, sizes, bss_addr, bss_size, entry


def vaddr_to_offset(data, offs, addrs, sizes, vaddr):
    for i in range(18):
        if addrs[i] <= vaddr < addrs[i] + sizes[i]:
            return offs[i] + (vaddr - addrs[i])
    return None


def main():
    if len(sys.argv) < 4:
        print(f"usage: {sys.argv[0]} <dol> <vaddr_hex> <count>")
        sys.exit(1)
    dol = sys.argv[1]
    start = int(sys.argv[2], 16)
    count = int(sys.argv[3])

    data, offs, addrs, sizes, bss_addr, bss_size, entry = read_dol(dol)
    print(f"entry: 0x{entry:08X}  bss: 0x{bss_addr:08X}+0x{bss_size:X}")
    for i in range(18):
        if sizes[i]:
            print(f"sec {i:2d}: off=0x{offs[i]:08X} vaddr=0x{addrs[i]:08X} size=0x{sizes[i]:X}")

    off = vaddr_to_offset(data, offs, addrs, sizes, start)
    if off is None:
        print(f"vaddr 0x{start:X} not in any section")
        sys.exit(1)

    md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
    md.detail = False
    end_off = min(off + count * 4, len(data))
    code = data[off:end_off]
    for insn in md.disasm(code, start):
        print(f"0x{insn.address:08X}: {insn.mnemonic:12s} {insn.op_str}")


if __name__ == "__main__":
    main()
