#!/usr/bin/env python3
"""Find all unmatched short functions (no frame prologue, <= 7 insns, no
unconditional-branch callouts) that gen_leaves currently misses, grouped by
their instruction signature."""
import glob
import json
import os
import re
import struct
from collections import Counter
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
d = open(f"{ROOT}/orig/G2TE52/sys/main.dol", "rb").read()
offs = struct.unpack_from(">18I", d, 0)
addrs = struct.unpack_from(">18I", d, 0x48)
t_off, t_addr = offs[1], addrs[1]

rep = json.load(open(f"{ROOT}/build/G2TE52/report.json"))
fns = sorted({int(fn["metadata"]["virtual_address"])
              for u in rep["units"] for fn in u.get("functions", [])})
matched = set()
for c in glob.glob(f"{ROOT}/src/*.c"):
    for mo in re.finditer(r"fn_[0-9A-F]{8}", open(c).read()):
        matched.add(int(mo.group(0)[3:], 16))

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.detail = False
md.skipdata = True

cnt = Counter()
samples = {}
total = 0
for start in fns:
    if start in matched or start < t_addr:
        continue
    off = t_off + (start - t_addr)
    ins = list(md.disasm(d[off:off + 0x40], start))
    if not ins:
        continue
    m = [x.mnemonic for x in ins]
    if m[0] == "stwu" or m[0] == "stfd" or m[0] == "stmw":
        continue  # has a frame
    if "bl" in m:
        continue
    try:
        e = m.index("blr")
    except ValueError:
        continue
    if e > 7:
        continue
    total += 1
    key = " ".join(m[:e + 1])
    cnt[key] += 1
    samples.setdefault(key, start)

print(f"total short frameless unmatched: {total}")
for key, n in cnt.most_common(40):
    s = samples[key]
    off = t_off + (s - t_addr)
    ins = list(md.disasm(d[off:off + 0x40], s))
    print(f"  {n:4d}  {key}   sample={s:#x}: "
          + " ; ".join(f"{x.mnemonic} {x.op_str}" for x in ins[:8]))
