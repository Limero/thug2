#!/usr/bin/env python3
"""Apply a named callee-arity change to a wip draft IN PLACE and re-verify.

usage: arity_apply.py [--apply] <file.c> <NAME:drop-last|drop-first|+arg> ...

The arity lever is the hidden-leading-arg / dead-arg family (AGENTS.md
§6e-32, §6o-99, §6t-3, §6w-119, §6y-132, §6ab-136): m2c drops or invents
parameters, and one extra/missing argument reorders the whole expand_call
arg setup.
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402
import arity_sweep as A  # noqa: E402

argv = sys.argv[1:]
apply = "--apply" in argv
argv = [a for a in argv if a != "--apply"]

for fn, spec in zip(argv[0::2], argv[1::2]):
    name, _, mode = spec.partition(":")
    path = os.path.join(ROOT, "src/wip", fn)
    addr = int(fn[3:-2], 16)
    raw = open(path).read()
    fl = T.gl.draft_flags(raw)
    lines = raw.splitlines()
    body = "\n".join(l for l in lines if not l.lstrip().startswith("//"))

    out = None
    for m in A.PROTO.finditer(body):
        if m.group(3) != name:
            continue
        plist = A.split_params(m.group(4))
        if mode == "drop-last":
            newparams = ", ".join(plist[:-1]) or "void"
        elif mode == "drop-first":
            newparams = ", ".join(plist[1:]) or "void"
        elif mode == "+arg":
            newparams = (", ".join(plist) + ", s32") if plist else "s32"
        else:
            raise SystemExit(f"bad mode {mode!r}")
        new = m.group(0).replace("(" + m.group(4) + ")",
                                "(" + newparams + ")", 1)
        pat = re.compile(r"^" + re.escape(m.group(0).rstrip()) + r"\s*$", re.M)
        cand, n = pat.subn(lambda _m: new, body)
        if n:
            out = cand
            break
    if out is None:
        print(f"{fn}: prototype for {name} not found")
        continue

    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="ara_")
    st, pct, err = T.test_one(addr, out, extra_flags=fl or None)
    print(f"{fn}  {st} {pct:.2f}  ({name} {mode})", flush=True)
    if not apply or st == "FAIL":
        continue
    idx = [i for i, l in enumerate(lines) if not l.lstrip().startswith("//")]
    for i, nl in zip(idx, out.splitlines()):
        lines[i] = nl
    note = (f"// ARITY FIX 2026-09-26: callee `{name}` was declared with the\n"
            f"// wrong parameter count here ({mode}).  m2c drops hidden leading\n"
            f"// pass-through args and invents phantom trailing ones; one extra\n"
            f"// or missing argument reorders the whole expand_call arg setup\n"
            f"// (doc-15).  Lever: automated arity sweep, AGENTS.md §6e-32 family.\n"
            f"// Now {pct:.2f}% {st}.\n")
    if "ARITY FIX 2026-09-26" not in "\n".join(lines):
        for j, l in enumerate(lines):
            if l.startswith("// family="):
                lines[j:j] = note.rstrip("\n").split("\n")
                break
    open(path, "w").write("\n".join(lines) + "\n")
    print("   applied", flush=True)
