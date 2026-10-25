#!/usr/bin/env python3
"""Find unmatched small GPR-only blrl (indirect-call) functions and print
their instruction bodies grouped by structural signature, so we can build
more auto-generators for the next pattern family."""
import json
import struct
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

DOL = "orig/G2TE52/sys/main.dol"
d = open(DOL, "rb").read()
offs = struct.unpack_from(">18I", d, 0)
addrs = struct.unpack_from(">18I", d, 0x48)
sizes = struct.unpack_from(">18I", d, 0x90)

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.detail = False
md.skipdata = True

rep = json.load(open("build/G2TE52/report.json"))
matched = set()
matched_sizes = {}
for u in rep["units"]:
    for f in u.get("functions", []):
        if f.get("matches") or f.get("fuzzy_match_percent", 0) >= 100:
            va = int(f["metadata"]["virtual_address"])
            matched.add(va)
            matched_sizes[va] = int(f.get("size", 0))

def insns_at(addr, maxn):
    off = offs[1] + (addr - addrs[1])
    return list(md.disasm(d[off:off + maxn * 4], addr))

text_end = addrs[1] + sizes[1]
# Map matched function start -> its end, using actual sizes from the report.
matched_ext = {va: va + matched_sizes[va] for va in matched}

cand = []
i = addrs[1]
while i < text_end:
    if i in matched_ext:
        i = matched_ext[i]  # skip the whole matched function
        continue
    insns = insns_at(i, 64)
    if not insns or insns[0].address != i:
        i += 4
        continue
    n = len(insns)
    end = n
    for k in range(1, n):
        if insns[k].mnemonic == "stwu" and "r1" in insns[k].op_str:
            end = k
            break
    body = insns[:end]
    mn = [x.mnemonic for x in body]
    if "blrl" not in mn:
        i += 4
        continue
    if any(m.startswith(("stfd", "lfd", "fmr", "fadd", "fsub", "fmul", "fdiv",
                         "fcm", "frsp", "fctiw", "fctid", "ps_", "lfs", "stfs"))
           for m in mn):
        i += 4
        continue
    if "bl" in mn or "bctrl" in mn:
        i += 4
        continue
    cand.append((i, end))
    i += max(end, 1) * 4

print(f"unmatched small GPR-only blrl: {len(cand)}")
from collections import Counter
c = Counter(e for _, e in cand)
print("by size:", sorted(c.items()))

# Build a structural signature: mnemonic+op pattern of the body
from collections import defaultdict
groups = defaultdict(list)
for a, e in cand:
    insns = insns_at(a, e)
    sig = []
    for x in insns[:e]:
        op = x.op_str
        op = op.replace("0x", "")
        # normalize registers except r1 (frame) and r3/r4 (args)
        parts = op.split(",")
        norm = []
        for p in parts:
            p = p.strip()
            if p.startswith("r1"):
                norm.append("SP")
            elif p in ("r3", "r4", "r5", "r6", "r7", "r8"):
                norm.append(p)
            else:
                norm.append("R")
        sig.append(x.mnemonic + " " + ",".join(norm))
    groups[tuple(sig)].append((a, e))

print(f"distinct shapes: {len(groups)}")
for sig, lst in sorted(groups.items(), key=lambda kv: -len(kv[1]))[:12]:
    print(f"\n=== shape with {len(lst)} fns, e.g. 0x{lst[0][0]:08X} ({lst[0][1]} insns) ===")
    for x in insns_at(lst[0][0], lst[0][1]):
        print(f"   {x.mnemonic:10s} {x.op_str}")
    print("   members:", ", ".join(f"0x{a:X}" for a, _ in lst[:8]), 
          ("..." if len(lst) > 8 else ""))
