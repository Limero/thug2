#!/usr/bin/env python3
"""Sweep NEAR-tier drafts for the M8.26 void-return or./cmpwi fix.

Fingerprint (fn_8002FEF0): a draft whose diffs are ONLY
WANT `cmpwi rX, 0` vs GOT `or. rX, rX, rX` (call-result tests whose value is
kept alive by a trailing `return var_`). Changing the own signature to
`void` kills the liveness -> EXACT.

Candidates come from NEAR lines in sweep logs (freshest /tmp/m9*.log).

Usage:
  python tools/sweep_void_return.py [--slice N/8] [--logs "glob"]
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
OWN_SIG = re.compile(r'^(?:s32|int) (fn_[0-9A-F]{8})\(', re.M)


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


def diff_words(addr, got, masks):
    want = gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + len(got)]
    out = []
    for i in range(0, len(got), 4):
        w = int.from_bytes(want[i:i+4], 'big')
        g = int.from_bytes(got[i:i+4], 'big')
        m = masks.get(i, 0xFFFFFFFF)
        if (w & m) != (g & m):
            out.append((i, w, g))
    return out


def flip_kind(w, g):
    """Return 'void' if WANT cmpwi rX,0 / GOT or. rX,rX,rX (value kept alive
    wrongly -> void fix), 'rev' for the mirror (WANT or. / GOT cmpwi -> value
    wrongly dead, missing live use), else None."""
    wi = list(md.disasm(w.to_bytes(4, 'big'), 0))
    gi = list(md.disasm(g.to_bytes(4, 'big'), 0))
    if not wi or not gi:
        return None
    wm, gm = wi[0].mnemonic, gi[0].mnemonic
    if wm == 'cmpwi' and gm == 'or.':
        m = re.match(r'r(\d+), 0', wi[0].op_str)
        m2 = re.match(r'r(\d+), r\1, r\1', gi[0].op_str)
        if m and m2 and m.group(1) == m2.group(1):
            return 'void'
    if wm == 'or.' and gm == 'cmpwi':
        m = re.match(r'r(\d+), r\1, r\1', wi[0].op_str)
        m2 = re.match(r'r(\d+), 0', gi[0].op_str)
        if m and m2 and m.group(1) == m2.group(1):
            return 'rev'
    return None


def is_cmpwi_or_flip(w, g):
    return flip_kind(w, g) == 'void'


def main():
    args = sys.argv[1:]
    slice_spec = None
    logs_glob = '/tmp/m9*.log'
    if '--slice' in args:
        i = args.index('--slice')
        slice_spec = args[i+1]
    if '--logs' in args:
        i = args.index('--logs')
        logs_glob = args[i+1]

    cands = candidates(logs_glob)
    print('candidates: %d' % len(cands))
    if slice_spec:
        n, d = map(int, slice_spec.split('/'))
        cands = cands[n::d]

    hits = []
    improved = []
    checked = 0
    for a in cands:
        fp = 'src/wip/fn_%s.c' % a
        if not os.path.exists(fp):
            continue
        addr = int(a, 16)
        text = open(fp).read()
        body = '\n'.join(l for l in text.splitlines() if not l.startswith('//'))
        m = OWN_SIG.search(body)
        if not m:
            continue
        own = m.group(1)
        got, masks = gl.compile_fn(addr, body)
        if got is None:
            print('%-8s COMPILE FAIL' % own)
            continue
        checked += 1
        diffs = diff_words(addr, got, masks)
        if not diffs:
            continue
        flips = sum(1 for _, w, g in diffs if flip_kind(w, g) == 'void')
        revs = sum(1 for _, w, g in diffs if flip_kind(w, g) == 'rev')
        if flips == 0 and revs == 0:
            continue
        if flips == 0 and revs > 0:
            if revs == len(diffs):
                print('%-8s REVERSE-only (%d rev flips) - value wrongly dead' % (own, revs))
            continue
        body_v = body.replace('s32 %s(' % own, 'void %s(' % own, 1)
        got_v, masks_v = gl.compile_fn(addr, body_v)
        if got_v is None:
            print('%-8s void-compile FAIL (orig %d diffs)' % (own, len(diffs)))
            continue
        nv = len(diff_words(addr, got_v, masks_v))
        if nv == 0:
            hits.append(own)
            print('%-8s PROMOTABLE (was %d diffs, %d flips)' % (own, len(diffs), flips))
        elif nv < len(diffs):
            improved.append((own, len(diffs), nv))
            print('%-8s improved %d -> %d (flips %d)' % (own, len(diffs), nv, flips))
        else:
            print('%-8s no-change (%d diffs, %d flips)' % (own, len(diffs), flips))

    print('=== VOID-FIX HITS: %d ; improved: %d ; checked: %d ===' % (len(hits), len(improved), checked))


if __name__ == '__main__':
    main()
