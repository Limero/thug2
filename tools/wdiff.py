#!/usr/bin/env python3
"""Show an instruction-level want-vs-got diff for a wip draft.

Usage: wdiff.py <hexaddr> [extra flags...]
"""
import sys, json, importlib
sys.path.insert(0, 'tools')
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

addr = int(sys.argv[1], 16)
flags = sys.argv[2:] or None
rep = json.load(open('build/G2TE52/report.json'))
sizes = {int(fn['metadata']['virtual_address']): int(fn['size'])
         for u in rep.get('units', []) for fn in u.get('functions', [])}
want_sz = sizes[addr]
orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + want_sz]

src = open(f'src/wip/fn_{addr:08X}.c').read()
got, masks = gl.compile_fn(addr, src, extra_flags=flags)
if got is None:
    print('compile FAILED'); sys.exit(1)

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
def dis(blob, base):
    out = {}
    for ins in md.disasm(blob, base):
        out[(ins.address - base) // 4] = f"{ins.mnemonic} {ins.op_str}"
    return out
w = dis(orig, addr); g = dis(got, addr)
n = max(len(w), len(g), len(orig)//4, len(got)//4)
print(f"addr={addr:08X} want_sz={want_sz} got_sz={len(got)} words={n}")
miss = 0
for i in range(n):
    ow = int.from_bytes(orig[i*4:(i+1)*4], 'big') if i*4 < len(orig) else 0
    gw = int.from_bytes(got[i*4:(i+1)*4], 'big') if i*4 < len(got) else 0
    m = masks.get(i*4, 0xFFFFFFFF)
    ok = (ow & m) == (gw & m)
    if not ok: miss += 1
    mark = '  ' if ok else '**'
    print(f"{i:>3} {ow:08x} {gw:08x}{mark} | {(w.get(i,'?')):<28} | {g.get(i,'?')}")
print(f"--- misses: {miss}/{n}  ({100.0*(n-miss)/n:.1f}%)")
