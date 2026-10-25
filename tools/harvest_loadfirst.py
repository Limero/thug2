#!/usr/bin/env python3
"""Harvest the lbl-load-first recipe (M7.19).

Pattern: WANT emits `lis r9, lbl_hi; lwz r0, off(r9)` (loading a global into
a temp) BEFORE the store `li r11, 1; stw r11` that follows in source. ngccc
schedules the store first. Fix: assign the store value to a NAMED temp
first (e.g. `newval = *(s32 *)&lbl_X + temp;` then store), forcing the load
before the store.

Usage: tools/venv/bin/python tools/harvest_loadfirst.py [--apply]
"""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '.'))
import gen_leaves as gl

APPLY = '--apply' in sys.argv


def masked_pct(orig, got, masks):
    n = min(len(orig), len(got)) // 4
    if n == 0:
        return 0.0
    hit = sum(1 for i in range(n)
              if (int.from_bytes(orig[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)) ==
                 (int.from_bytes(got[i*4:(i+1)*4], 'big') & masks.get(i*4, 0xFFFFFFFF)))
    return 100.0 * hit / n


def transform(text):
    """Hoist `*(s32 *)&lbl_X + temp_r3` store RHS into a named temp first."""
    # Pattern: `*(s32 *)((char *)ptr + (s32)0xNN) = (s32) (*(s32 *)&lbl_XXXX + temp_r3);`
    # Replace with: `newvalN = (s32) (*(s32 *)&lbl_XXXX + temp_r3);` then the store.
    pat = re.compile(
        r'(\s*)\*\s*\(s32 \*\)\(\(char \*\)([A-Za-z0-9_]+) \+ \(s32\)0x([0-9A-Fa-f]+)\) = \(s32\) \(\*\(s32 \*\)&lbl_([0-9A-F]+) \+ (temp_r3)\);')
    n = 0
    def repl(m):
        nonlocal n
        n += 1
        indent, ptr, off, lbl, tmp = m.groups()
        return ('%snewval%d = (s32) (*(s32 *)&lbl_%s + %s);\n'
                '%s*(s32 *)((char *)%s + (s32)0x%s) = newval%d;'
                % (indent, n, lbl, tmp, indent, ptr, off, n))
    new = pat.sub(repl, text)
    if n > 0:
        # declare the temps after the last #include
        lines = new.split('\n')
        last_inc = -1
        for i, l in enumerate(lines):
            if l.startswith('#include'):
                last_inc = i
        if last_inc >= 0:
            decls = '\n'.join('    s32 newval%d;' % (i + 1) for i in range(n))
            lines.insert(last_inc + 1, decls)
            new = '\n'.join(lines)
    return new, n > 0


def main():
    wins = []
    losses = []
    fails = []
    files = sorted(glob.glob('src/wip/fn_*.c'))
    for fp in files:
        txt = open(fp).read()
        if 'temp_r3' not in txt or 'lbl_' not in txt:
            continue
        new_txt, changed = transform(txt)
        if not changed:
            continue
        addr = int(re.search(r'fn_([0-9A-F]{8})', os.path.basename(fp)).group(1), 16)

        def pct(t):
            body = '\n'.join(l for l in t.splitlines()
                              if not l.startswith('//') and 'types.h' not in l)
            got, masks = gl.compile_fn(addr, body)
            if got is None:
                return -1.0
            orig = bytes(gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + len(got)])
            return masked_pct(orig, got, masks)

        base = pct(txt)
        newpct = pct(new_txt)
        if newpct > base:
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
    print('=== LOSSES ===')
    for f, b, n in losses[:10]:
        print('  %s: %.1f -> %.1f' % (f, b, n))
    print('=== NO-CHANGE ===')
    for f, b, n in fails[:10]:
        print('  %s: %.1f -> %.1f' % (f, b, n))
    print('wins=%d losses=%d nochg=%d %s' % (len(wins), len(losses), len(fails),
                                             'APPLIED' if APPLY else 'DRY-RUN'))


if __name__ == '__main__':
    main()
