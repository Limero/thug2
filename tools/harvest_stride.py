#!/usr/bin/env python3
"""Harvest the s32*-stride family: drafts where m2c emitted
`(s32 *)(*(void * *)&lbl_X) + 0xNN` but WANT's load uses byte offset 0xNN
(the `(s32 *)` cast multiplies the offset by 4: 0x154 -> 0x550).

Rewrite to `(s32 *)((char *)(*(void * *)&lbl_X) + (s32)0xNN)` and keep only
drafts that gain (ideally 100%). Usage:
    tools/venv/bin/python tools/harvest_stride.py [--apply] [--min-gain 0]
"""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '.'))
import gen_leaves as gl

APPLY = '--apply' in sys.argv
MIN_GAIN = 0.0
if '--min-gain' in sys.argv:
    MIN_GAIN = float(sys.argv[sys.argv.index('--min-gain') + 1])

PAT = re.compile(
    r'\(s32 \*\)\(\* ?\(void \* ?\*\)&(lbl_[0-9A-F]+)\) \+ (0x[0-9A-Fa-f]+)')


def masked_pct(orig, got, masks):
    n = min(len(orig), len(got)) // 4
    if n == 0:
        return 0.0
    hit = sum(1 for i in range(n)
              if (int.from_bytes(orig[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)) ==
                 (int.from_bytes(got[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)))
    return 100.0 * hit / n


def transform(text):
    """Rewrite one pattern occurrence per line (all lines) to char* byte offset."""
    def sub(m):
        return '(s32 *)((char *)(*(void * *)&%s) + (s32)%s)' % (m.group(1), m.group(2))
    new = PAT.sub(sub, text)
    return new, new != text


def main():
    wins = []
    losses = []
    fails = []
    files = sorted(glob.glob('src/wip/fn_*.c'))
    for fp in files:
        txt = open(fp).read()
        if '(s32 *)(*' not in txt or '+ 0x' not in txt:
            continue
        if not PAT.search(txt):
            continue
        addr = int(re.search(r'fn_([0-9A-F]{8})', os.path.basename(fp)).group(1), 16)
        body0 = '\n'.join(l for l in txt.splitlines()
                          if not l.startswith('//') and 'types.h' not in l)
        got0, masks0 = gl.compile_fn(addr, body0)
        base = masked_pct(gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + len(got0)], got0, masks0) if got0 else -1.0

        new_txt, changed = transform(txt)
        if not changed:
            continue
        body1 = '\n'.join(l for l in new_txt.splitlines()
                          if not l.startswith('//') and 'types.h' not in l)
        got1, masks1 = gl.compile_fn(addr, body1)
        newpct = masked_pct(gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + len(got1)], got1, masks1) if got1 else -1.0

        if newpct > base + MIN_GAIN:
            wins.append((os.path.basename(fp), base, newpct))
            if APPLY:
                open(fp, 'w').write(new_txt)
        elif newpct < base:
            losses.append((os.path.basename(fp), base, newpct))
        else:
            fails.append((os.path.basename(fp), base, newpct))

    print('=== WINS (kept) ===')
    for f, b, n in sorted(wins, key=lambda x: -x[2]):
        mark = ' <<< 100%' if n == 100.0 else ''
        print('  %s: %.1f -> %.1f%s' % (f, b, n, mark))
    print('=== LOSSES (reverted) ===')
    for f, b, n in losses[:10]:
        print('  %s: %.1f -> %.1f' % (f, b, n))
    print('=== NO-CHANGE ===')
    for f, b, n in fails[:10]:
        print('  %s: %.1f -> %.1f' % (f, b, n))
    print('wins=%d losses=%d nochg=%d %s' % (len(wins), len(losses), len(fails),
                                             'APPLIED' if APPLY else 'DRY-RUN'))


if __name__ == '__main__':
    main()
