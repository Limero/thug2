#!/usr/bin/env python3
"""Scan the DOL for functions that save GPRs (r30/r31) but NO FPRs, and
tabulate (frame, gpr offsets) to determine whether GPR-only functions follow
the plain formula frame = 8 + 4*nGPR + locals (matching ngccc) or the +8
quirk of FPR-saving functions.

This decides whether GPR-only functions are matchable with our ngccc builds.
"""
import os
import re
import struct
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

DOL = os.path.join(ROOT, "orig/G2TE52/sys/main.dol")
with open(DOL, "rb") as f:
    data = f.read()
offs = struct.unpack_from(">18I", data, 0)
addrs = struct.unpack_from(">18I", data, 0x48)
sizes = struct.unpack_from(">18I", data, 0x90)

t_off, t_addr, t_size = offs[1], addrs[1], sizes[1]
md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.detail = False
md.skipdata = True
insns = list(md.disasm(data[t_off:t_off + t_size], t_addr))

# function starts
starts = [i for i, insn in enumerate(insns)
          if insn.mnemonic == "stwu" and re.search(r"-0x[0-9a-f]+\(r1\)", insn.op_str)]
print(f"prologues: {len(starts)}")

layout = Counter()
examples = {}
gpr_only = 0
fpr_saving = 0
for si in starts:
    m = re.search(r"-0x([0-9a-f]+)\(r1\)", insns[si].op_str)
    frame = int(m.group(1), 16)
    gprs = []
    fprs = []
    for j in range(si + 1, min(si + 14, len(insns))):
        op = insns[j]
        if op.mnemonic == "stw":
            mm = re.match(r"r(\d+),\s*0x([0-9a-f]+)\(r1\)", op.op_str)
            if mm:
                rn = int(mm.group(1))
                off = int(mm.group(2), 16)
                if rn == 0:
                    pass  # LR save (r0)
                elif 14 <= rn <= 31:
                    gprs.append((rn, off))
        if op.mnemonic == "stfd":
            mm = re.match(r"f\d+,\s*0x([0-9a-f]+)\(r1\)", op.op_str)
            if mm:
                fprs.append(int(mm.group(1), 16))
        if op.mnemonic == "mr" and "r31, r1" in op.op_str:
            break  # frame pointer setup starts locals
    gprs = [o for _, o in sorted(gprs)]
    if fprs:
        fpr_saving += 1
        continue
    if not gprs:
        continue
    gpr_only += 1
    key = (frame, tuple(gprs))
    layout[key] += 1
    if key not in examples:
        examples[key] = hex(insns[si].address)

print(f"fpr-saving fns (blocked): {fpr_saving}")
print(f"gpr-only fns: {gpr_only}")
print("\n(frame, gpr_offsets) -> count, example")
for key, cnt in sorted(layout.items(), key=lambda kv: -kv[1])[:18]:
    print(f"  frame={key[0]:#5x} gprs={[hex(o) for o in key[1]]} : {cnt:5d}  e.g. {examples[key]}")
