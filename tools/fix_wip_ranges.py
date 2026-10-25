#!/usr/bin/env python3
"""Fix WIP draft range markers flagged by tools/audit_wip_ranges.py.

Classes handled:
  1. at-start drafts with NO canonical marker: upgrade an existing prose
     "// range A-B (...)" or "range=A-B" line in place, else insert a
     canonical line after the first line. Values always come from
     symbols.txt, never from the prose.
  2. at-start drafts with a canonical marker whose end/size disagree with
     symbols.txt: rewrite the range=.../size=... substring.
  3. fragment drafts with a marker crossing the parent end: replace the
     marker with a FRAGMENT note (never promotable).
  4. unlabeled drafts: leave, unless a marker claims a region no symbol
     owns (report only).

family= is preserved when present, else 'm2c' (promote_wip.py only parses
range=... and size=..., check_markers.py only start+size).

Usage:  tools/venv/bin/python tools/fix_wip_ranges.py [--dry-run]
Run tools/audit_wip_ranges.py afterwards to verify.
"""
import bisect
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

MARKER = re.compile(r'family=(\S+) range=0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+) size=(\d+)B')
PROSE = re.compile(r'//\s*range=?\s*0x([0-9A-Fa-f]{8})\s*-\s*0x([0-9A-Fa-f]{8})')
PROSE_SIZE = re.compile(r'size=(\d+)B')

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


def canonical(addr, size, fam):
    return f'family={fam} range=0x{addr:X}-0x{addr + size:X} size={size}B'


dry = '--dry-run' in sys.argv
n_fix = n_frag = n_skip = 0
for fp in sorted(glob.glob('src/wip/fn_*.c')):
    addr = int(os.path.basename(fp)[3:11], 16)
    txt = open(fp).read()
    orig = txt
    cont = containing(addr)
    m = MARKER.search(txt)
    if cont is None:
        if m:
            print(f'SKIP unlabeled fn_{addr:08X}: canonical marker claims region '
                  f'0x{m.group(2)}-0x{m.group(3)} no symbol owns')
            n_skip += 1
        continue
    cstart, cname, csize = cont
    if addr != cstart:
        # fragment: any canonical marker is fabricated (a sub-span of the
        # parent can never be a compilable unit) -- replace with a note
        if m:
            line_re = re.compile(r'^.*family=\S+ range=0x[0-9A-Fa-f]+-0x[0-9A-Fa-f]+ size=\d+B.*$', re.M)
            note = (f'// FRAGMENT: address lies inside {cname} ({csize:#x}B) — '
                    f'not an independent function; no range marker.')
            new = line_re.sub(note, txt, count=1)
            if new != txt and not dry:
                open(fp, 'w').write(new)
            print(f'FIX fragment fn_{addr:08X}: marker inside parent {cname} -> note')
            n_frag += 1
        continue
    want = canonical(addr, csize, m.group(1) if m else 'm2c')
    if m:
        if (int(m.group(2), 16), int(m.group(3), 16), int(m.group(4))) == (addr, addr + csize, csize):
            continue
        txt = MARKER.sub(want, txt, count=1)
        why = 'values != symbols'
    else:
        pm = PROSE.search(txt)
        if pm:
            # upgrade only the "range 0xA-0xB" span; rebuild the line as
            # canonical marker + original annotation tail (minus any stale
            # size=NB token) so the inserted size is never clobbered
            line_end = txt.index('\n', pm.start())
            tail = txt[pm.end():line_end]
            tail = PROSE_SIZE.sub('', tail, count=1)
            txt = txt[:pm.start()] + f'// {want}{tail}' + txt[line_end:]
        else:
            # insert after the first line
            i = txt.index('\n')
            txt = txt[:i + 1] + f'// {want}\n' + txt[i + 1:]
        why = 'NO MARKER' if not pm else 'prose only'
    if txt != orig:
        if not dry:
            open(fp, 'w').write(txt)
        print(f'FIX fn_{addr:08X} ({cname}, {csize:#x}B): {why} -> {want}')
        n_fix += 1

print(f'\n{n_fix} at-start markers fixed, {n_frag} fragments neutralized, {n_skip} unlabeled skipped'
      + (' (dry run)' if dry else ''))
