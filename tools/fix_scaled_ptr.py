#!/usr/bin/env python3
"""Repair m2c's SCALED SCALAR-POINTER ARITHMETIC in wip drafts.

m2c sometimes emits

    *(s32 *)((s32 *)(X) + 0x14)

where X is an integer holding an address.  The `+ 0x14` then sits OUTSIDE the
cast, so C pointer arithmetic multiplies it by sizeof(s32) = 4 (0x50 bytes),
while the binary loads at byte 0x14.  The byte-correct spelling keeps the outer
dereference type and makes the base a char pointer:

    *(s32 *)((char *)(X) + 0x14)

`(s32 *)(X + 0xC)` — offset INSIDE the cast — is integer arithmetic and must be
left alone (it is correct and appears in hundreds of already-matching files).

Two patterns are repaired:
  SAME: `(T *)((T *)`   offset applied to a pointer obtained from a cast of the
                        same scalar type (the common shape).
  ANY:  `(T *)((S *)`   mixed scalar types (2nd pass; a much smaller yield).

Usage:
    tools/fix_scaled_ptr.py scan  [N] [jobs]   score current vs repaired, report
    tools/fix_scaled_ptr.py apply [min-delta]  rewrite the wip files in place
                                               (adds the UPDATED header note)

`scan` writes every row (both directions) to .scratch/scaledptr.txt and prints
the improving ones.  Both modes honour each draft's own `// FLAG:` line, and
`apply` uses the recorded scores for its note.
"""
import glob
import multiprocessing as mp
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
os.environ.setdefault("LEAF_TMPDIR", "/tmp/scaledptr")
import gen_leaves as gl  # noqa: E402
import test_wip_drafts as tw  # noqa: E402
import detect_structs as ds  # noqa: E402 (struct-class aliases)

TYPES = r"(?:s32|u32|s16|u16|s8|u8|f32|f64|Unk_[0-9A-Fa-f]+|%s)" % \
    "|".join(ds.ALIASES.values())
SAME = re.compile(r"\((%s) \*\)\(\(\1 \*\)" % TYPES)
ANY = re.compile(r"\((%s) \*\)\(\((%s) \*\)" % (TYPES, TYPES))
OUT = os.path.join(ROOT, ".scratch/scaledptr.txt")
ROW = re.compile(r"\s*([+-][\d.]+) 0x([0-9A-F]{8}) +([\d.]+) -> +([\d.]+) \((\d+) casts?\)")
NOTE = ("// UPDATED 2026-09-18: {a}% -> {b}%. m2c SCALED POINTER ARITHMETIC:\n"
        "// (T *)((S *)(X) + off) multiplies `off` by sizeof(S) because the offset sits\n"
        "// OUTSIDE the cast, while the binary uses a byte displacement ({k} cast(s) in\n"
        "// this body).  Recasing the base to char * keeps the deref type and makes the\n"
        "// arithmetic byte-wise; automated A/B via tools/fix_scaled_ptr.py.\n")


def rewrite(line, regexes):
    hits = 0
    for rx in regexes:
        line, c = rx.subn(lambda m: "(%s *)((char *)" % m.group(1), line)
        hits += c
        if c:
            break
    return line, hits


def body_of(text):
    return "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()


def score(addr, body, flags):
    fpr = tw.want_fpr_frame(addr)
    if fpr is not None and "volatile double" not in body:
        s0, p0, _ = tw.test_one(addr, body, flags)
        s1, p1, _ = tw.test_one(addr, tw.inject_dummy(body), flags)
        return (s1, p1) if s1 > s0 else (s0, p0)
    return tw.test_one(addr, body, flags)[:2]


def work(f):
    try:
        addr = int(os.path.basename(f)[3:11], 16)
        text = open(f).read()
        fixed, n = rewrite(body_of(text), (SAME, ANY))
        if n == 0:
            return None
        flags = gl.draft_flags(text) or None
        s0, p0 = score(addr, body_of(text), flags)
        s1, p1 = score(addr, fixed, flags)
        return p1 - p0, addr, p0, p1, n
    except Exception as e:  # noqa: BLE001
        return None if "want_fpr" in str(e) else (-999, 0, 0.0, f"ERR {e}", 0)


def candidates(limit=0):
    out = []
    for f in sorted(glob.glob(os.path.join(ROOT, "src/wip/fn_*.c"))):
        txt = open(f).read()
        if SAME.search(txt) or ANY.search(txt):
            out.append(f)
    return out[:limit] if limit else out


def do_scan(args):
    limit = int(args[0]) if args else 0
    jobs = int(args[1]) if len(args) > 1 else max(2, (os.cpu_count() or 4) - 1)
    files = candidates(limit)
    print(f"candidates={len(files)} jobs={jobs}", file=sys.stderr)
    with mp.Pool(jobs) as p:
        res = [r for r in p.map(work, files) if r]
    res.sort(reverse=True)
    rows = [f"{d:+7.1f} 0x{a:08X} {b:5.1f} -> {c:5.1f} ({k} casts)" for d, a, b, c, k in res]
    open(OUT, "w").write("\n".join(rows) + "\n")
    print("\n".join(r for r in rows if r.lstrip().startswith("+")))


def do_apply(args):
    min_delta = float(args[0]) if args else 0.1
    if not os.path.exists(OUT):
        sys.exit("run `scan` first")
    applied = 0
    for line in open(OUT):
        m = ROW.match(line)
        if not m or float(m.group(1)) < min_delta:
            continue
        addr, a, b, k = m.group(2), m.group(3), m.group(4), int(m.group(5))
        path = os.path.join(ROOT, f"src/wip/fn_{addr}.c")
        lines = open(path).read().splitlines()
        out, hits = [], 0
        for l in lines:
            if not l.startswith("//"):
                l, c = rewrite(l, (SAME, ANY))
                hits += c
            out.append(l)
        if not hits:
            continue
        i = 0
        while i < len(out) and (out[i].startswith("//") or out[i].strip() == ""):
            i += 1
        note = NOTE.format(a=a, b=b, k=k).rstrip("\n").splitlines()
        open(path, "w").write("\n".join(out[:i] + note + out[i:]) + "\n")
        applied += 1
    print(f"applied to {applied} file(s)")


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else "scan"
    if mode == "scan":
        do_scan(sys.argv[2:])
    elif mode == "apply":
        do_apply(sys.argv[2:])
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
