#!/usr/bin/env python3
"""Apply named return-type flips to wip drafts IN PLACE and re-verify.

usage: rt_apply.py [--apply] <file.c> <name:s32->void> [<file.c> <name:...>] ...
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402

argv = sys.argv[1:]
apply = "--apply" in argv
argv = [a for a in argv if a != "--apply"]
pairs = list(zip(argv[0::2], argv[1::2]))

for fn, flip in pairs:
    name, _, change = flip.partition(":")
    old_ty, new_ty = change.split("->")
    path = os.path.join(ROOT, "src/wip", fn)
    addr = int(fn[3:-2], 16)
    raw = open(path).read()
    fl = T.gl.draft_flags(raw)
    lines = raw.splitlines()
    body = "\n".join(l for l in lines if not l.lstrip().startswith("//"))
    pat = re.compile(rf"^(extern\s+)?{old_ty}\s+{re.escape(name)}\s*\(", re.M)
    out, n = pat.subn(lambda m: f"{m.group(1) or ''}{new_ty} {name}(", body)
    if not n:
        print(f"{fn}: pattern {old_ty} {name}( not found")
        continue
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="rta_")
    st, pct, err = T.test_one(addr, out, extra_flags=fl or None)
    print(f"{fn}  {st} {pct:.2f}  ({n} site(s), {name} {old_ty}->{new_ty})")
    if not apply:
        continue
    idx = [i for i, l in enumerate(lines) if not l.lstrip().startswith("//")]
    for i, nl in zip(idx, out.splitlines()):
        lines[i] = nl
    note = (f"// RETURN-TYPE FIX 2026-09-25: `{name}` declared `{old_ty}` here, but\n"
            f"// its result is discarded at every call site in this body.  With the\n"
            f"// result live, ngccc's expand_call reorders the arg setup (doc-15);\n"
            f"// declaring it `{new_ty}` restores retail's order.\n"
            f"// Lever: automated sweep, M8.31 / AGENTS 4q.1.  Now {pct:.2f}% {st}.\n")
    if "RETURN-TYPE FIX 2026-09-25" not in "\n".join(lines):
        for j, l in enumerate(lines):
            if l.startswith("// family="):
                lines[j:j] = note.rstrip("\n").split("\n")
                break
    open(path, "w").write("\n".join(lines) + "\n")
    print("   applied")
