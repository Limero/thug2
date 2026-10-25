#!/usr/bin/env python3
"""Scan the DOL text section for function prologues that save f31 and tabulate
(frame size, f31 offset) to determine the game's frame layout rule.

Hypothesis being tested: the game's compiler frames = 8 (backchain) + 8*nFPR
+ locals + 8, and the double/local slot sits directly below the FPR area at
the top of the frame; ngccc produces 8 fewer bytes.
"""
import os
import re
import struct
import sys
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

code = data[t_off:t_off + t_size]
insns = list(md.disasm(code, t_addr))
print(f"insns: {len(insns)}")

# find function starts: stwu r1, -N(r1) is the classic prologue
starts = []
for i, insn in enumerate(insns):
    if insn.mnemonic == "stwu" and "r1," in insn.op_str and "-0x" in insn.op_str:
        starts.append(i)
print(f"stwu prologues: {len(starts)}")

# for each prologue, inspect the next 8 insns for stfd f31/f30.. and mflr/stw r0
layout = Counter()
examples = {}
for si in starts:
    m = re.search(r"-0x([0-9a-fA-F]+)\(r1\)", insns[si].op_str)
    frame = int(m.group(1), 16) if m else None
    if frame is None:
        continue
    fprs = []
    has_lr = False
    for j in range(si + 1, min(si + 10, len(insns))):
        op = insns[j]
        if op.mnemonic == "stfd" and "(r1)" in op.op_str:
            m = re.search(r"0x([0-9a-fA-F]+)\(r1\)", op.op_str)
            if m:
                fprs.append(int(m.group(1), 16))
        elif op.mnemonic == "stw" and "r0," in op.op_str and "(r1)" in op.op_str:
            has_lr = True
        elif op.mnemonic == "mr" or op.mnemonic == "fmr":
            pass
    if not fprs:
        continue
    nfpr = len(fprs)
    key = (frame, tuple(sorted(fprs)), has_lr)
    layout[key] += 1
    if key not in examples:
        examples[key] = hex(insns[si].address)

print("\n(frame, fpr_offsets, lr_saved_in_frame) -> count, example")
for key, cnt in sorted(layout.items(), key=lambda kv: -kv[1]):
    print(f"  frame={key[0]:#5x} fprs={[hex(o) for o in key[1]]} lr={key[2]} : {cnt:5d}  e.g. {examples[key]}")
