#!/usr/bin/env python3
"""Flag-aware want|got diff. Usage: flagdiff.py 0xADDR [flags...]

diff_near.py takes no extra flags and test_wip_drafts.py ignores `// FLAG:`
lines in drafts - this is the verifier for flag-dependent drafts (e.g.
`// FLAG: -fno-schedule-insns2`): pass the flags as CLI args and it compiles
the draft with them and prints a masked want|got instruction diff.
"""
import os
import sys
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, f"{ROOT}/tools")
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)

def dis(w):
    out = next(md.disasm(struct.pack(">I", w), 0))
    return f"{out.mnemonic} {out.op_str}"

ADDR = int(sys.argv[1], 16)
flags = sys.argv[2:]
src = open(f"{ROOT}/src/wip/fn_{ADDR:08X}.c").read()
lines = [ln for ln in src.splitlines() if not ln.startswith("//") and "types.h" not in ln]
body = "\n".join(lines)
got, masks = gl.compile_fn(ADDR, body, extra_flags=flags or None)
if got is None:
    print("COMPILE FAIL:", masks); sys.exit(1)
dol = open(f"{ROOT}/orig/G2TE52/sys/main.dol", "rb").read()
def dol_off(va): return va - 0x800034A0 + 0x4A0
want = dol[dol_off(ADDR):dol_off(ADDR) + len(got)]
n = len(got)//4
match = 0
rows = []
for i in range(n):
    wv = struct.unpack(">I", want[i*4:i*4+4])[0]
    wg = struct.unpack(">I", got[i*4:i*4+4])[0]
    mv = masks.get(i*4)
    wvm = wv & mv if mv else wv
    wgm = wg & mv if mv else wg
    ok = wvm == wgm
    match += ok
    rows.append((i*4, ok, dis(wv), dis(wg)))
print(f"{match}/{n} match ({100.0*match/n:.1f}%)")
for off, ok, a, b in rows:
    if not ok:
        print(f"DIFF {off:04x}  {a:<38} | {b}")
