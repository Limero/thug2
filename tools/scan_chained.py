#!/usr/bin/env python3
"""Scan wip drafts for call sites where WANT loads r4/r5/r6 but never r3.

Two families (both mean the draft is missing arg0 or has the wrong proto):

1. CHAINED: r3 holds a PREVIOUS call's return (kept in r3 by ngccc) that the
   callee takes as arg0 -> draft should be fn(fnPrev(...), ...) or pass the
   saved temp.
2. OWN-ARG-PASS: r3 holds THIS function's own arg that was moved to a callee
   register (mr r31,r3) but the callee call site never reloads r3 because
   the source passes the arg variable directly -> the draft's call is missing
   that arg (callee is 1-arg-more than drafted).

Detection: walk WANT asm; for each `bl`, check whether r4/r5/r6 were written
after the last r3 write. If so, and r3 hasn't been written within the last 8
insns, report. Classify by checking whether the r3 value source is a previous
bl (chained) or the function's saved arg (own-pass).
"""
import sys, re, glob, os
sys.path.insert(0, 'tools')
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True

sizes = {}
for line in open('config/G2TE52/symbols.txt'):
    m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]{8}); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        sizes[int(m.group(1), 16)] = int(m.group(2), 16)

WRITE_RE = re.compile(r'^(mr|li|lis|addi|add|subf|lwz|lha|lhz|lbz|or|ori|rlwinm|extsh|extsb|clrlwi|clrrwi|sth|and|andc|srawi|slwi|srwi|neg|mullw|mulli|divw|lwzu|lwzx|lbzx|stwu|stw|stb|sth)')

cands = []
for fp in sorted(glob.glob('src/wip/fn_*.c')):
    addr = int(os.path.basename(fp)[3:11], 16)
    body = '\n'.join(l for l in open(fp).read().splitlines() if not l.startswith('//'))
    try:
        got, masks = gl.compile_fn(addr, body)
    except Exception:
        continue
    if got is None:
        continue
    sz = sizes.get(addr, len(got))
    orig = bytes(gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + min(sz, len(got))])
    n = min(len(orig), len(got)) // 4
    if n == 0:
        continue
    hit = sum(1 for i in range(n) if (int.from_bytes(orig[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)) == (int.from_bytes(got[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)))
    pct = 100.0 * hit / n
    if pct < 85.0:
        continue
    lastw = {}
    insns = list(md.disasm(orig, addr))
    hits = []
    for idx, ins in enumerate(insns):
        if ins.mnemonic == 'bl':
            r3_set = lastw.get(3, -10)
            args_set = [r for r in (4, 5, 6, 7, 8, 9) if lastw.get(r, -10) > r3_set]
            if args_set and r3_set < idx - 6:
                # classify: was r3's last write a bl (chained)?
                # find what wrote r3 last
                src = 'unknown'
                if r3_set >= 0 and r3_set < len(insns):
                    w = insns[r3_set]
                    if w.mnemonic == 'bl':
                        src = 'chained'
                    elif w.mnemonic == 'mr':
                        src = 'ownarg(%s)' % w.op_str.split(',')[1].strip()
                    else:
                        src = w.mnemonic
                hits.append((ins.address, args_set, src))
        m = WRITE_RE.match(ins.mnemonic)
        if m:
            mm = re.match(r'^r(\d+)', ins.op_str)
            if mm:
                lastw[int(mm.group(1))] = idx
    if hits:
        cands.append((addr, pct, hits))

cands.sort(key=lambda x: -x[1])
print('=== %d candidates ===' % len(cands))
for addr, pct, hits in cands[:50]:
    h = hits[0]
    print('%08X %.1f%% bl@0x%X args=r%s src=%s' % (addr, pct, h[0], ','.join(str(a) for a in h[1]), h[2]))
