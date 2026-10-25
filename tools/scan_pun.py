#!/usr/bin/env python3
"""Scan the whole DOL text section for the int->double pun pattern
(`lis rX, 0x4330` used for the xoris trick) and report the stack offsets
used for the conversion temp — to determine whether the game's compiler
aligns stack doubles to 16 bytes globally or per-function.
"""
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

DOL_HEADER = 0x100
DOL = os.path.join(ROOT, "orig/G2TE52/sys/main.dol")

with open(DOL, "rb") as f:
    data = f.read()

offs = struct.unpack_from(">18I", data, 0)
addrs = struct.unpack_from(">18I", data, 0x48)
sizes = struct.unpack_from(">18I", data, 0x90)

# text is section 1 (vaddr 0x800034A0, size 0x28ABA0) — find it generically
text_idx = 1
if text_idx >= len(offs) or sizes[text_idx] == 0:
    print("no text section")
    sys.exit(1)
t_off = offs[text_idx]
t_addr = addrs[text_idx]
t_size = sizes[text_idx]

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.detail = False
md.skipdata = True

code = data[t_off:t_off + t_size]
insns = list(md.disasm(code, t_addr))
print(f"total insns in text: {len(insns)}")

# find every `lis rX, 0x4330`
offsets_16 = []
offsets_8 = []
other = []
count = 0
for i, insn in enumerate(insns):
    if insn.mnemonic == "lis" and "0x4330" in insn.op_str:
        count += 1
        # window: 4 before, 4 after
        win = insns[max(0, i - 3):i + 5]
        text = " | ".join(f"{w.mnemonic} {w.op_str}" for w in win)
        # find stw/lfd stack offsets in window
        stws = [w.op_str for w in insns[max(0, i - 4):i + 6]
                if w.mnemonic in ("stw", "lfd") and "(r1)" in w.op_str]
        offs_used = [o for o in stws]
        # classify: any 0x10(r1)/0x18(r1) style 16-aligned vs 8(r1)
        aligned16 = any("0x10(r1)" in o or "0x18(r1)" in o or "0x20(r1)" in o for o in offs_used)
        if aligned16:
            offsets_16.append(insn.address)
        elif any("0x8(r1)" in o or "0xc(r1)" in o for o in offs_used):
            offsets_8.append(insn.address)
        else:
            other.append(insn.address)
        if count <= 12:
            print(f"0x{insn.address:08X}: {text}")

print()
print(f"total 0x4330 pun sites: {count}")
print(f"  16-aligned slot: {len(offsets_16)}  e.g. {[hex(a) for a in offsets_16[:8]]}")
print(f"  8-aligned slot:  {len(offsets_8)}  e.g. {[hex(a) for a in offsets_8[:8]]}")
print(f"  other/unknown:   {len(other)}  e.g. {[hex(a) for a in other[:8]]}")
