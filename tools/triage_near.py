#!/usr/bin/env python3
"""Triage NEAR drafts: compile each, show the first few WANT-vs-GOT diff
instruction pairs so patterns can be spotted quickly. Reads addr list from
/tmp/near_list.txt (addr size pct). Optional --max-size N to filter."""
import sys, re
sys.path.insert(0, 'tools')
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs
md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True

max_size = None
if '--max-size' in sys.argv:
    max_size = int(sys.argv[sys.argv.index('--max-size') + 1])
limit = None
if '--limit' in sys.argv:
    limit = int(sys.argv[sys.argv.index('--limit') + 1])

rows = []
for line in open('/tmp/near_list.txt'):
    parts = line.split()
    if len(parts) < 3:
        continue
    a = int(parts[0], 16)
    sz = int(parts[1])
    pct = float(parts[2].rstrip("%"))
    if max_size and sz > max_size:
        continue
    rows.append((a, sz, pct))

rows.sort(key=lambda r: r[1])
if limit:
    rows = rows[:limit]

for a, sz, pct in rows:
    fp = 'src/wip/fn_%08X.c' % a
    try:
        body = open(fp).read()
    except FileNotFoundError:
        continue
    flags = gl.draft_flags(body) or None
    body = '\n'.join(l for l in body.splitlines() if not l.startswith('//'))
    got, masks = gl.compile_fn(a, body, extra_flags=flags)
    if got is None:
        print('%08X: FAIL' % a)
        continue
    WANT = gl.d[gl.t_off + (a - gl.t_addr):gl.t_off + (a - gl.t_addr) + len(got)]
    n = min(len(got), len(WANT))
    d = [i for i in range(0, n - 3, 4)
         if (int.from_bytes(got[i:i+4], 'big') & masks.get(i, 0xFFFFFFFF)) !=
            (int.from_bytes(WANT[i:i+4], 'big') & masks.get(i, 0xFFFFFFFF))]
    w = list(md.disasm(WANT, a))
    g = list(md.disasm(got, a))
    print('===== %08X (%dB, %.1f%%, %d diffs) =====' % (a, sz, pct, len(d)))
    shown = 0
    for wi, gi in zip(w, g):
        off = gi.address - a
        if off in d:
            print('  W: %08X %-8s %-18s | G: %s %s' % (wi.address, wi.mnemonic, wi.op_str, gi.mnemonic, gi.op_str))
            shown += 1
            if shown >= 6:
                break
