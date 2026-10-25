#!/usr/bin/env python3
"""Classify game functions by prologue style: FPR-saving (blocked by the +8
frame quirk), GPR-only, leaf (no saves) — to find matchable functions.

Usage: classify_fns.py <start_vaddr_hex> <count>  (functions after start)
"""
import os
import re
import struct
import sys

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

# map address -> index
by_addr = {insn.address: i for i, insn in enumerate(insns)}


def classify(start_idx):
    """Return (kind, frame, saves) for the function starting at insns[start_idx]."""
    frame = None
    fprs = []
    gprs = []
    lr = False
    for j in range(start_idx, min(start_idx + 16, len(insns))):
        op = insns[j]
        if op.mnemonic == "stwu" and re.search(r"-0x[0-9a-f]+\(r1\)", op.op_str):
            m = re.search(r"-0x([0-9a-f]+)\(r1\)", op.op_str)
            frame = int(m.group(1), 16)
        elif op.mnemonic == "stfd" and re.search(r"0x[0-9a-f]+\(r1\)", op.op_str):
            m = re.search(r"0x([0-9a-f]+)\(r1\)", op.op_str)
            fprs.append(int(m.group(1), 16))
        elif op.mnemonic == "stw" and re.match(r"r\d+,", op.op_str) and "(r1)" in op.op_str:
            m = re.match(r"r(\d+),\s*0x([0-9a-f]+)\(r1\)", op.op_str)
            if m:
                rn = int(m.group(1))
                if rn == 0:
                    lr = True
                elif rn >= 14:
                    gprs.append(int(m.group(2), 16))
        elif op.mnemonic == "stmw":
            gprs.append(-1)  # store-multiple marker
    return frame, fprs, gprs, lr


def main():
    start = int(sys.argv[1], 16)
    count = int(sys.argv[2])
    idx = by_addr.get(start)
    if idx is None:
        print(f"address 0x{start:X} not found")
        return
    # iterate from idx until we've seen `count` function boundaries
    seen = 0
    i = idx
    while i < len(insns) and seen < count:
        op = insns[i]
        if op.mnemonic == "stwu" and re.search(r"-0x[0-9a-f]+\(r1\)", op.op_str):
            frame, fprs, gprs, lr = classify(i)
            if fprs:
                kind = "FPR   (blocked)"
            elif gprs:
                kind = "GPR-only (ok)"
            else:
                kind = "leaf   (ok)"
            print(f"0x{op.address:08X} frame={frame and hex(frame)} fprs={len(fprs)} gprs={len(gprs)} lr={int(lr)} {kind}")
            seen += 1
            # skip to after this function: next stwu after an addi r1,r1,N / blr tail
            j = i + 1
            while j < len(insns):
                o = insns[j]
                if o.mnemonic == "blr":
                    i = j + 1
                    break
                j += 1
            else:
                i = j
        else:
            i += 1


if __name__ == "__main__":
    main()
