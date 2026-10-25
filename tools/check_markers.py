#!/usr/bin/env python3
"""Verify every src/wip/fn_*.c range marker matches the real function size.

Run before promoting batches: a wrong size marker makes the split misalign
and the linked DOL differs (auto-revert at promote time).

Only drafts AT a function start need markers (promotable units). Drafts
whose address lies inside another function are splitter fragments — they
are never compiled, so no marker is required (see tools/audit_wip_ranges.py
for the full fragment/unlabeled classification).

Usage: tools/venv/bin/python tools/check_markers.py

Also checks for orphan sources: a .c file on disk under a registered
src_dir that owns no Object() entry is never compiled.
"""
import bisect
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

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


drafts = glob.glob('src/wip/fn_*.c')
bad = []
n_checked = n_frag = 0
for fp in drafts:
    addr = int(os.path.basename(fp)[3:11], 16)
    txt = open(fp).read()
    n_checked += 1
    cont = containing(addr)
    if cont is None:
        continue  # unlabeled region: bookkeeping draft, no promotable unit
    cstart, cname, csize = cont
    if addr != cstart:
        n_frag += 1  # fragment inside a function: never compiled
        continue
    m = re.search(r'range=0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+) size=(\d+)B', txt)
    if not m:
        bad.append((addr, 0, 'NO MARKER'))
        continue
    start = int(m.group(1), 16)
    size = int(m.group(3))
    want_size = csize
    if start != addr:
        bad.append((addr, size, f'START MISMATCH {start:#x}'))
    elif size != want_size:
        bad.append((addr, size, f'SIZE {size} != symbols {want_size:#x}'))

print(f'checked {n_checked} drafts ({n_frag} fragments skipped)')
failed = False
if bad:
    print(f'{len(bad)} BAD markers:')
    for addr, size, why in sorted(bad):
        print(f'  fn_{addr:08X}: {why}')
    failed = True
else:
    print('all markers OK')

# Phase 2: orphan sources — a .c file on disk under a registered src_dir
# that owns no Object() entry is never compiled. Move batches (game module
# -> libs/runtime) that leave the old src/fn_*.c behind create basename
# twins the rest of the tooling cannot tell apart: add_gen_leaves sees the
# basename in splits.txt/configure.py and reports "present", so edits to the
# dead twin never reach the build.
# Reference-only masters that are deliberately never compiled:
ALLOW_UNREGISTERED = {
    # (src_dir, basename)
    ('src', 'gen_dispatch.c'),  # gen_dispatch_fns.py master listing (note there)
    ('src', 'vcall.c'),          # gen_vcall_fns.py master listing
}

cfg_lines = open('configure.py').read().splitlines()
cur_lib, cur_src = None, 'src'
registered = {}  # (src_dir, object path) -> lib
for line in cfg_lines:
    m = re.search(r'"lib":\s*"([^"]+)"', line)
    if m:
        cur_lib, cur_src = m.group(1), 'src'
    m = re.match(r'\s*DolphinLib\(\s*"([^"]+)"', line)
    if m:
        cur_lib, cur_src = m.group(1), 'libs/dolphin/src'
    m = re.search(r'"src_dir":\s*"([^"]+)"', line)
    if m:
        cur_src = m.group(1)
    for om in re.finditer(r'Object\(\s*\w+,\s*"([^"]+)"', line):
        registered.setdefault((cur_src, om.group(1)), cur_lib)

by_base = {}
for (srcdir, name) in registered:
    by_base.setdefault(name.split('/')[-1], []).append(srcdir)

orphans = []
for srcdir in sorted({s for s, _ in registered}):
    if not os.path.isdir(srcdir):
        continue  # external/untracked source tree (e.g. libs/dolphin/src)
    regd = {n.split('/')[-1] for (s, n) in registered if s == srcdir}
    for fp in sorted(glob.glob(f'{srcdir}/*.c')):
        base = os.path.basename(fp)
        if base in regd or (srcdir, base) in ALLOW_UNREGISTERED:
            continue
        owners = [s for s in by_base.get(base, []) if s != srcdir]
        hint = f' (SHADOW: live copy registered under {owners[0]})' if owners else ''
        orphans.append(f'{fp}{hint}')

if orphans:
    print(f'{len(orphans)} ORPHAN sources (on disk, never compiled):')
    for o in orphans:
        print(f'  {o}')
    failed = True
else:
    print('no orphan sources')

sys.exit(1 if failed else 0)
