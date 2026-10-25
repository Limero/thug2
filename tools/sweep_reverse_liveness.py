#!/usr/bin/env python3
"""Sweep for REVERSE liveness flips: WANT `or. rX,rX,rX` vs GOT `cmpwi rX, 0`.

WANT keeps the tested value live after the branch; the draft's source kills
it (usually a dropped trailing use: return value, store, or call arg).
Dumps WANT + GOT context windows around each flip for analysis.

Usage:
  python tools/sweep_reverse_liveness.py [--slice N/8] [--logs "glob"]
      [--min-rev N]   only report candidates with >= N rev flips (default 1)
"""
import re
import sys
import glob
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True

NEAR_RE = re.compile(r'NEAR +([a-z0-9]+) +0x([0-9A-F]+) +\(([0-9]+)B\) +([0-9.]+)%')


def candidates(logs_glob):
    seen = set()
    out = []
    for lp in sorted(glob.glob(logs_glob)):
        for line in open(lp, errors='ignore'):
            m = NEAR_RE.search(line)
            if m:
                a = m.group(2)
                if a not in seen:
                    seen.add(a)
                    out.append(a)
    return out


def disasm_at(data, base):
    return ['%08X  %s %s' % (ins.address, ins.mnemonic, ins.op_str)
            for ins in md.disasm(data, base)]


def rev_flip(w, g):
    """True if WANT or. rX,rX,rX vs GOT cmpwi rX, 0 (same X)."""
    wi = list(md.disasm(w.to_bytes(4, 'big'), 0))
    gi = list(md.disasm(g.to_bytes(4, 'big'), 0))
    if not wi or not gi:
        return None
    if wi[0].mnemonic != 'or.' or gi[0].mnemonic != 'cmpwi':
        return None
    m = re.match(r'r(\d+), r\1, r\1', wi[0].op_str)
    m2 = re.match(r'r(\d+), 0', gi[0].op_str)
    if m and m2 and m.group(1) == m2.group(1):
        return m.group(1)
    return None


def main():
    args = sys.argv[1:]
    slice_spec = None
    logs_glob = '/tmp/m9*.log'
    min_rev = 1
    if '--slice' in args:
        i = args.index('--slice')
        slice_spec = args[i+1]
    if '--logs' in args:
        i = args.index('--logs')
        logs_glob = args[i+1]
    if '--min-rev' in args:
        i = args.index('--min-rev')
        min_rev = int(args[i+1])

    cands = candidates(logs_glob)
    if slice_spec:
        n, d = map(int, slice_spec.split('/'))
        cands = cands[n::d]

    found = []
    epi = []
    for a in cands:
        fp = 'src/wip/fn_%s.c' % a
        if not os.path.exists(fp):
            continue
        addr = int(a, 16)
        text = open(fp).read()
        body = '\n'.join(l for l in text.splitlines() if not l.startswith('//'))
        got, masks = gl.compile_fn(addr, body)
        if got is None:
            continue
        want = gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + len(got)]
        flips = []
        for i in range(0, len(got), 4):
            w = int.from_bytes(want[i:i+4], 'big')
            g = int.from_bytes(got[i:i+4], 'big')
            m = masks.get(i, 0xFFFFFFFF)
            if (w & m) != (g & m):
                r = rev_flip(w, g)
                if r:
                    flips.append((i // 4, r))
        if len(flips) >= min_rev:
            found.append((a, flips))
        # epilogue comparison: WANT returns a value (mr r3,rX / li r3,K before blr)
        # that GOT's epilogue does not construct
        n = len(got) // 4
        if n >= 3:
            w_last = [list(md.disasm(want[i*4:(i+1)*4], addr + i*4)) for i in range(n - 3, n)]
            g_last = [list(md.disasm(got[i*4:(i+1)*4], addr + i*4)) for i in range(n - 3, n)]
            w_ret = [x for x in w_last if x and x[0].mnemonic in ('mr', 'li', 'addi', 'lwz', 'lhz', 'lbz')]
            g_ret = [x for x in g_last if x and x[0].mnemonic in ('mr', 'li', 'addi', 'lwz', 'lhz', 'lbz')]
            if w_ret and g_ret:
                wv = w_ret[-1][0]
                gv = g_ret[-1][0]
                if (wv.mnemonic == 'mr' and gv.mnemonic != 'mr') or \
                   (wv.mnemonic in ('li', 'addi') and gv.mnemonic not in ('li', 'addi')) or \
                   (wv.mnemonic in ('lwz', 'lhz', 'lbz') and gv.mnemonic not in ('lwz', 'lhz', 'lbz')):
                    epi.append((a, '%s %s' % (wv.mnemonic, wv.op_str), '%s %s' % (gv.mnemonic, gv.op_str)))

    # summary
    print('REVERSE-flip candidates (want>=%d): %d' % (min_rev, len(found)))
    for a, flips in found:
        print('%-8s rev=%d %s' % (a, len(flips), ' '.join('w%d(r%s)' % (w, r) for w, r in flips)))
    print('EPILOGUE-return-value candidates: %d' % len(epi))
    for a, wv, gv in epi:
        print('%-8s WANT-ret %-10s GOT-ret %s' % (a, wv, gv))

    # context dumps for the first 6 candidates
    for a, flips in found[:6]:
        addr = int(a, 16)
        print('\n################ %s ################' % a)
        body = '\n'.join(l for l in open('src/wip/fn_%s.c' % a).read().splitlines()
                         if not l.startswith('//'))
        got, masks = gl.compile_fn(addr, body)
        want = gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + len(got)]
        for woff, reg in flips[:2]:
            base = addr + woff * 4
            print('--- flip w%d (r%s) WANT window ---' % (woff, reg))
            for i in range(max(0, woff - 2), min(woff + 8, len(got) // 4)):
                ins = list(md.disasm(want[i*4:(i+1)*4], addr + i*4))
                mark = ' <<<' if i == woff else ''
                if ins:
                    print('  %08X  %s %s%s' % (ins[0].address, ins[0].mnemonic, ins[0].op_str, mark))
            print('--- same window GOT ---')
            for i in range(max(0, woff - 2), min(woff + 8, len(got) // 4)):
                ins = list(md.disasm(got[i*4:(i+1)*4], addr + i*4))
                mark = ' <<<' if i == woff else ''
                if ins:
                    print('  %08X  %s %s%s' % (ins[0].address, ins[0].mnemonic, ins[0].op_str, mark))


if __name__ == '__main__':
    main()
