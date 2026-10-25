#!/usr/bin/env python3
"""Full WIP range audit: every src/wip/fn_*.c vs symbols.txt function extents.

For each draft, find the containing function symbol (any name, .text/.init):
  - draft addr == function start: marker is REQUIRED and must match the
    symbol extent exactly (start, size).
  - draft addr inside a function (not at start): FRAGMENT -- any canonical
    marker is fabricated (it can only describe an arbitrary sub-span) and
    is reported; never promotable.
  - no containing function: UNLABELED -- code region no symbol claims.

Exit 1 if any AT-START draft has a missing/defective marker (the dangerous
class: promote would build a wrong-size object).

Usage: tools/venv/bin/python tools/audit_wip_ranges.py
"""
import bisect
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

MARKER = re.compile(r'family=(\S+) range=0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+) size=(\d+)B')

# all function-type symbols regardless of name (fn_* and SDK/script names)
funcs = {}
for line in open('config/G2TE52/symbols.txt'):
    m = re.match(r'(\w+) = \.(?:text|init):0x([0-9A-Fa-f]+);.*type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        funcs[int(m.group(2), 16)] = (m.group(1), int(m.group(3), 16))
starts = sorted(funcs)


def containing(addr):
    i = bisect.bisect_right(starts, addr) - 1
    if i >= 0:
        s = starts[i]
        name, size = funcs[s]
        if addr < s + size:
            return s, name, size
    return None


bad, fragments, unlabeled = [], [], []
n_checked = 0
for fp in sorted(glob.glob('src/wip/fn_*.c')):
    addr = int(os.path.basename(fp)[3:11], 16)
    txt = open(fp).read()
    n_checked += 1
    m = MARKER.search(txt)
    cont = containing(addr)
    if cont is None:
        unlabeled.append((addr, m.groups() if m else None))
        continue
    cstart, cname, csize = cont
    if addr != cstart:
        # fragment inside a real function: never promotable
        if m:
            mend = int(m.group(3), 16)
            why = 'MARKER CROSSES PARENT END' if mend > cstart + csize else 'marker claims fragment'
            fragments.append((addr, cname, csize, why))
        else:
            fragments.append((addr, cname, csize, None))
        continue
    # at-start draft: marker must match symbol extent
    if not m:
        bad.append((addr, cname, csize, 'NO MARKER'))
        continue
    fam, ms, me, msz = m.group(1), int(m.group(2), 16), int(m.group(3), 16), int(m.group(4))
    why = None
    if ms != addr:
        why = f'START {ms:#x} != {addr:#x}'
    elif me != addr + csize:
        why = f'END {me:#x} != {addr + csize:#x} (symbols {csize:#x})'
    elif msz != csize:
        why = f'SIZE {msz} != symbols {csize:#x}'
    if why:
        bad.append((addr, cname, csize, why))

print(f'checked {n_checked} drafts against {len(funcs)} function symbols')
print(f'{len(fragments)} fragments (inside a parent function), {len(unlabeled)} unlabeled')
if fragments:
    print('fragments:')
    for addr, cname, csize, why in sorted(fragments):
        print(f'  fn_{addr:08X}: inside {cname} ({csize:#x})' + (f' -- {why}' if why else ''))
if unlabeled:
    print('unlabeled (no containing function symbol):')
    for addr, g in sorted(unlabeled):
        print(f'  fn_{addr:08X}: ' + (f'marker {g}' if g else 'NO MARKER'))
if bad:
    print(f'{len(bad)} BAD at-start markers:')
    for addr, cname, csize, why in sorted(bad):
        print(f'  fn_{addr:08X} ({cname}, {csize:#x}): {why}')
    sys.exit(1)
print('all at-start markers OK')
