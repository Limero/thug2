#!/usr/bin/env python3
"""Find wip drafts whose called functions are never declared (implicit-int calls).

A called fn_XXXX with no prototype line in the draft forces GCC to treat it as
an implicit-int varargs-style call, which (a) inserts `crclr cr1eq` before the
call and (b) discards the struct-return ABI. Both are 4-byte frame errors.

Usage: tools/venv/bin/python tools/undecl_scan.py [--out FILE]
"""
import glob
import os
import re
import sys

WIP = "src/wip"
CALL_RE = re.compile(r"\bfn_[0-9A-Fa-f]{8}\s*\(")
DECL_RE = re.compile(r"\bfn_[0-9A-Fa-f]{8}\s*\([^;]*\)\s*;")
DEF_RE = re.compile(r"^(?:s32|void|f32|u32|s16|u8|char|u64|s64|f64|Unk_\w+ ?\*?|\w+ ?\*?)\s*fn_([0-9A-Fa-f]{8})\s*\(", re.M)


def scan_file(path):
    text = open(path).read()
    # strip comments
    body = re.sub(r"//[^\n]*", "", text)
    # declared names: prototype statements "ret fn_XXXX(...);"
    declared = set(m.group(0) for m in re.finditer(r"\bfn_[0-9A-Fa-f]{8}\s*\([^;{)]*\)\s*;", body))
    declared_names = set()
    for d in declared:
        m = re.match(r"\b(fn_[0-9A-Fa-f]{8})\s*\(", d)
        if m:
            declared_names.add(m.group(1))
    # function definition name (the draft's own fn)
    dm = DEF_RE.search(body)
    own = dm.group(1) if dm else None
    # called names
    called = set(m.group(1) for m in re.finditer(r"\b(fn_[0-9A-Fa-f]{8})\s*\(", body))
    missing = sorted(c for c in called if c not in declared_names)
    if own in missing:
        missing.remove(own)
    return missing


def main():
    out = None
    if "--out" in sys.argv:
        out = sys.argv[sys.argv.index("--out") + 1]
    rows = []
    for path in sorted(glob.glob(os.path.join(WIP, "fn_*.c"))):
        try:
            missing = scan_file(path)
        except Exception as e:
            print(f"{path}: ERR {e}", file=sys.stderr)
            continue
        if missing:
            rows.append((path, missing))
    lines = [f"{p}\t{','.join(ms)}" for p, ms in rows]
    for l in lines:
        print(l)
    print(f"# drafts with missing decls: {len(rows)}", file=sys.stderr)
    if out:
        with open(out, "w") as f:
            f.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
