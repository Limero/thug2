#!/usr/bin/env python3
"""Repair m2c's SCALED SCALAR-POINTER ARITHMETIC when the base is a BARE NAME.

tools/fix_ptr_arith.py and tools/fix_scaled_ptr.py both key on a cast that sits
*inside* the parentheses:

    *(s32 *)(X) + 0x14            (fix_ptr_arith:  `(s32 *)(`)
    *(s32 *)((s32 *)X) + 0x14     (fix_scaled_ptr: `(T *)((T *)`)

m2c also emits the identical defect with a whole VARIABLE as the base, which
neither tool matches:

    *((s32 *)temp_r9 + (arg1 * 0x10)) = arg2;

`temp_r9` is an integer holding an address, so `(s32 *)temp_r9 + k` multiplies
the offset by sizeof(s32) = 4.  When the offset is a BYTE offset that is simply
wrong; when the base really points into an s32 array the scaling is right.

    fn_80174558: stride 0x10 read as 0x40 (want `slwi r0,r4,4` + `stwx`)
    fn_8016D698: stride 0x190 read as 0x640, field 0x15C read as 0x570

Nothing is rewritten blindly: every candidate is compiled and SCORED BOTH WAYS
with the same scorer `tools/score_addrs.py` uses (per-draft `// FLAG:` line and
the FPR-dummy best-of), and a file is only rewritten when the repair gains at
least `min-delta` points.  Genuine s32-array indexing therefore keeps its
scaling: its rewrite scores worse and is dropped.

A candidate site is one whose offset contains a hex constant >= 0x20 (a byte
offset -- real array indices come out of m2c in decimal) or any `*` product
(a scaled stride).  `+ 0x04`-style small offsets are left alone.

Usage:
    tools/venv/bin/python tools/fix_scaled_ptr_ident.py scan  [i n] [min-delta]
    tools/venv/bin/python tools/fix_scaled_ptr_ident.py apply [i n] [min-delta]

    i n         optional slice (run `for i in 0..n-1` in parallel to fan out)
    min-delta   points the repair must gain to be kept (default 0.05)
"""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
import scan_score  # noqa: E402

# Shape 1 (this tool's own gap): the base is a BARE NAME.
PAT = re.compile(r'\(\((s32|u32|f32|s16|u16|s8|u8) \*\)'
                 r'([A-Za-z_][A-Za-z_0-9]*)'
                 r'((?: \+ [^()]*(?:\([^()]*\))?[^()]*)+)\)')
# Shape 2 (same defect, cast inside the parens): `(s32 *)(X) + 0x14`.  Included
# here so the whole class is swept with ONE flag-aware, FPR-dummy-aware
# scorer; tools/fix_ptr_arith.py measures with tools/gen_leaves.py's raw
# match counter instead, which ignores each draft's `// FLAG:` line.
PAT2 = re.compile(r'\(\((s32|u32|f32|s16|u16|s8|u8) \*\)'
                  r'\(([^()]*)\)'
                  r'((?: \+ [^()]*(?:\([^()]*\))?[^()]*)+)\)')
HEX = re.compile(r'0x[0-9A-Fa-f]+')


def interesting(off):
    hx = [int(x, 16) for x in HEX.findall(off)]
    if hx and max(hx) >= 0x20:
        return True
    return '*' in off


def repair(text):
    """Rewrite every *interesting* scaled-pointer site of either shape.
    Returns (new_text, sites_fixed)."""
    edits = []
    for m in PAT.finditer(text):
        if interesting(m.group(3)):
            edits.append((m.start(), m.end(),
                          '((%s *)((char *)%s%s))'
                          % (m.group(1), m.group(2), m.group(3))))
    for m in PAT2.finditer(text):
        if interesting(m.group(3)):
            edits.append((m.start(), m.end(),
                          '((%s *)((char *)(%s)%s))'
                          % (m.group(1), m.group(2), m.group(3))))
    edits.sort()
    out = []
    last = 0
    n = 0
    for start, end, new in edits:
        if start < last:  # overlapping (PAT matched inside PAT2's base)
            continue
        out.append(text[last:start])
        out.append(new)
        last = end
        n += 1
    out.append(text[last:])
    return ''.join(out), n


def body_of(text):
    return "\n".join(l for l in text.splitlines()
                     if not l.startswith('//') and 'types.h' not in l).strip()


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else 'scan'
    args = sys.argv[2:]
    slice_idx, num_slices = 0, 1
    min_delta = 0.05
    if len(args) >= 2 and args[0].isdigit() and args[1].isdigit():
        slice_idx, num_slices = int(args[0]), int(args[1])
        args = args[2:]
    if args:
        min_delta = float(args[0])

    files = sorted(glob.glob('src/wip/fn_*.c'))[slice_idx::num_slices]
    rows = 0
    kept = 0
    for fp in files:
        text = open(fp).read()
        if not (PAT.search(text) or PAT2.search(text)):
            continue
        new_text, nsite = repair(text)
        if nsite == 0:
            continue
        addr = int(os.path.basename(fp)[3:11], 16)
        flags = gl.draft_flags(text) or None
        _, before = scan_score.score(addr, body_of(text), flags)
        _, after = scan_score.score(addr, body_of(new_text), flags)
        if after == 0.0 and before == 0.0:
            continue
        delta = after - before
        rows += 1
        if delta >= min_delta:
            kept += 1
            print('%-18s %6.1f -> %6.1f  (%+5.1f)  %d site(s)'
                  % (os.path.basename(fp), before, after, delta, nsite))
            if mode == 'apply':
                open(fp, 'w').write(new_text)
    print('slice %d/%d done: %d candidate file(s), %d over threshold'
          % (slice_idx, num_slices, rows, kept))


if __name__ == '__main__':
    main()
