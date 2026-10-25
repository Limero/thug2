#!/usr/bin/env python3
"""Verify the new cluster rules on real FAIL functions."""
import sys, re, os
sys.path.insert(0, 'tools')
import gen_leaves as gl
import fill_wip_drafts as fw

# one from each cluster
addrs = [0x8002C638, 0x80103044, 0x8012D190, 0x80103F10, 0x80083564,
         0x8001E248, 0x8001E5DC, 0x800BFDD8, 0x8012A958,
         0x800B16FC, 0x80155FF8, 0x8005742C, 0x800945F8, 0x8000D150,
         0x80014BC4, 0x8001E3CC, 0x8009A8CC, 0x800B8178, 0x8002E34C,
         0x8000B23C, 0x80076778, 0x800808EC]
ok = fail = 0
for a in addrs:
    fp = 'src/wip/fn_%08X.c' % a
    if not os.path.isfile(fp):
        print('0x%08X: NO FILE' % a)
        continue
    text = open(fp).read()
    size = int(re.search(r'size=(\d+)B', text).group(1))
    asm_lines, _ = fw.disasm_with_labels(a, size)
    raw = fw.run_m2c('\n'.join(asm_lines) + '\n')
    if raw is None:
        print('0x%08X: m2c FAILED' % a)
        continue
    body = fw.postprocess(raw)
    got, err = gl.compile_fn(a, body)
    if got is not None:
        ok += 1
        print('0x%08X: OK' % a)
    else:
        fail += 1
        print('0x%08X: FAIL' % a)
        for l in (err or '').splitlines()[:5]:
            print('   ', l[:150])
print('=== %d OK, %d FAIL ===' % (ok, fail))
