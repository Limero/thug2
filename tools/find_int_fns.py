#!/usr/bin/env python3
"""Find pure-integer functions in the DOL: no FP/vector instructions, no
undecodable bytes, no calls. These are the reliable byte-identical matches
with ngccc (like the RNG cluster). Sorted by start address with sizes.
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

FP_RE = re.compile(r"^(lfs|lfd|stfs|stfd|fadd|fsub|fmul|fdiv|fmadd|fmsub|frsp|fmr|fneg|fcmp|fabs|fctiw|fctiwz|mtfs|mffs|mtfsf|ps_|v[a-z]|vs[a-z]|xx)", re.I)
CALL_RE = re.compile(r"^(bl|bcl)\b")


def classify(start_idx):
    """Return (size_insns, is_int, has_call, has_fp, undecodable) for fn at start_idx."""
    i = start_idx
    n = 0
    is_int = True
    has_call = False
    has_fp = False
    while i < len(insns):
        op = insns[i]
        i += 1
        n += 1
        if n > 4000:
            break
        if op.mnemonic == ".byte":
            return n, False, has_call, True, True
        if CALL_RE.match(op.mnemonic):
            has_call = True
            is_int = False
        if FP_RE.match(op.mnemonic):
            has_fp = True
            is_int = False
        if op.mnemonic == "blr":
            break
        if op.mnemonic == "stwu" and re.search(r"-0x[0-9a-f]+\(r1\)", op.op_str) and n > 1:
            break  # next function started
    return n, is_int, has_call, has_fp, False


results = []
i = 0
while i < len(insns):
    op = insns[i]
    if op.mnemonic == "stwu" and re.search(r"-0x[0-9a-f]+\(r1\)", op.op_str):
        size, is_int, has_call, has_fp, undec = classify(i)
        if is_int and size > 0:
            results.append((op.address, size, has_call, has_fp, undec))
        i += size if size > 1 else 1
    else:
        i += 1

print(f"total pure-integer functions: {len(results)}")
print(f"  (sizes: small first, nearest to 0x800034A0)")
by_size = sorted(results, key=lambda r: r[1])
print("smallest 25:")
for addr, size, call, fp, und in by_size[:25]:
    print(f"  0x{addr:08X}  {size:4d} insns  call={int(call)} fp={int(fp)} und={int(und)}")

start = int(sys.argv[1], 16) if len(sys.argv) > 1 else 0x800034A0
near = sorted(results, key=lambda r: abs(r[0] - start))
print(f"\nnearest to 0x{start:08X}:")
for addr, size, call, fp, und in near[:15]:
    print(f"  0x{addr:08X}  {size:4d} insns  call={int(call)} fp={int(fp)} und={int(und)}")
