#!/usr/bin/env python3
"""Harvest MMIO drafts: rewrite literal `*(T *)0xCC00XXXX = v` accesses to
`*(volatile T *)&lbl_CC00XXXX` (named extern) and keep only drafts that gain.

Mirrors the M6.72 lbl-symbol harvest: per-draft compile+compare, keep only
improvements (ideally 100%). Usage:
    tools/venv/bin/python tools/harvest_mmio.py [--apply] [--min-gain 0]
"""
import glob
import re
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '.'))
import gen_leaves as gl

APPLY = '--apply' in sys.argv
MIN_GAIN = 0.0
if '--min-gain' in sys.argv:
    MIN_GAIN = float(sys.argv[sys.argv.index('--min-gain') + 1])

# (literal type, volatile replacement type) for store accesses
WIDTHS = [
    (r'volatile\s+u8', 'volatile u8'),
    (r'volatile\s+u16', 'volatile u16'),
    (r'volatile\s+u32', 'volatile u32'),
    (r'u8', 'volatile u8'),
    (r'u16', 'volatile u16'),
    (r'u32', 'volatile u32'),
    (r's8', 'volatile u8'),
    (r's16', 'volatile u16'),
    (r's32', 'volatile u32'),
]


def masked_pct(orig, got, masks):
    n = min(len(orig), len(got)) // 4
    if n == 0:
        return 0.0
    hit = sum(1 for i in range(n)
              if (int.from_bytes(orig[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)) ==
                 (int.from_bytes(got[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)))
    return 100.0 * hit / n


def transform(text):
    """Rewrite literal MMIO store accesses to named-extern volatile form."""
    changed = False
    # map address literal -> extern decl (dedupe)
    addrs = set(re.findall(r'\*\([^)]*?\)0x(CC[0-9A-Fa-f]{6})', text))
    for a in sorted(addrs):
        sym = 'lbl_%s' % a.upper()
        if not re.search(r'\b%s\b' % sym, text):
            text = 'extern char %s[];\n' % sym + text
            changed = True
        for lit, rep in WIDTHS:
            # *(...lit...)0xCC008000  (store or load; loads only via the
            # pointer-cast pattern, stores are the primary target)
            pat = re.compile(r'\*\(\s*%s\s*\*\)0x%s\b' % (lit, a), re.I)
            new = text
            text = pat.sub(lambda m: '*(%s *)&%s' % (rep, sym), text)
            if text != new:
                changed = True
    return text, changed


def main():
    wins = []
    losses = []
    fails = []
    files = sorted(glob.glob('src/wip/fn_*.c'))
    for fp in files:
        txt = open(fp).read()
        if '0xCC00' not in txt:
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
        mark = '100.0' if n == 100.0 else ''
        print('  %s: %.1f -> %.1f %s' % (f, b, n, mark))
    print('=== LOSSES (reverted) ===')
    for f, b, n in losses[:15]:
        print('  %s: %.1f -> %.1f' % (f, b, n))
    print('=== NO-CHANGE ===')
    for f, b, n in fails[:10]:
        print('  %s: %.1f -> %.1f' % (f, b, n))
    print('wins=%d losses=%d nochg=%d %s' % (len(wins), len(losses), len(fails),
                                             'APPLIED' if APPLY else 'DRY-RUN'))


if __name__ == '__main__':
    main()
