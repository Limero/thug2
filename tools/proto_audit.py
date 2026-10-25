#!/usr/bin/env python3
"""Audit every WIP draft's *declared* callee prototypes against the promoted
`src/<name>.c` definitions.

m2c invents a prototype for every callee it can't see.  When that guess is
wrong the draft passes/sets up arguments the wrong way, which shows up as
unrelated register-allocation noise.  This tool reports the mismatches so
they can be attacked deliberately (arity first, then per-argument type, then
return type).

  ARITY   declared parameter count != real        -> tools/fix_call_arity.py
  VOIDARG real function is `f(void)` but the draft
          passes arguments                        -> tools/fix_void_calls.py
  TYPES   same arity, different argument shapes

Usage:
  tools/venv/bin/python tools/proto_audit.py               # summary
  tools/venv/bin/python tools/proto_audit.py --list ARITY  # the drafts
  tools/venv/bin/python tools/proto_audit.py --file F      # only these addrs
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

DECL = re.compile(r"^[ \t]*(?:static\s+)?[\w \t\*]*?\b(fn_[0-9A-F]{8})\s*\(([^;{}]*)\)\s*;", re.M)
DEF = re.compile(r"^(\w[\w \t\*]*?)\s*\b(fn_[0-9A-F]{8})\(([^)]*)\)\s*\{", re.M)


def params(text):
    """Split a parameter list into normalised type strings."""
    out = []
    for a in text.split(","):
        a = a.strip()
        if not a or a == "void":
            continue
        a = re.sub(r"\s*\b\w+\s*$", "", a).strip() or "s32"
        out.append(re.sub(r"\s+", " ", a))
    return out


def real_defs():
    defs = {}
    for p in glob.glob(os.path.join(ROOT, "src/fn_*.c")):
        name = os.path.basename(p)[:-2]
        m = DEF.search(open(p).read())
        if m:
            defs[name] = (m.group(1).strip(), params(m.group(3)))
    return defs


def main():
    args = sys.argv[1:]
    defs = real_defs()
    only = None
    if args[:1] == ["--file"]:
        only = set()
        for l in open(args[1]):
            l = l.strip()
            if l:
                only.add("fn_%08X" % int(l.split()[0], 16))
    findings = {"ARITY": [], "VOIDARG": [], "TYPES": []}
    files = sorted(glob.glob(os.path.join(ROOT, "src/wip/fn_*.c")))
    for p in files:
        name = os.path.basename(p)[:-2]
        if only and name not in only:
            continue
        text = open(p).read()
        if "family=stub" in text:
            continue
        for m in DECL.finditer(text):
            callee, declared = m.group(1), params(m.group(2))
            if callee not in defs:
                continue
            _, real = defs[callee]
            if not real and declared:
                findings["VOIDARG"].append((name, callee, declared, real))
            elif len(declared) != len(real):
                findings["ARITY"].append((name, callee, declared, real))
            elif declared != real:
                findings["TYPES"].append((name, callee, declared, real))
    if args[:1] == ["--list"]:
        kind = args[1]
        for name, callee, declared, real in findings[kind]:
            print("%s  %s: (%s) vs real (%s)" % (name, callee, ",".join(declared), ",".join(real)))
        return
    for kind in ("ARITY", "VOIDARG", "TYPES"):
        drafts = {f[0] for f in findings[kind]}
        print("%-8s %4d declaration mismatches across %d drafts"
              % (kind, len(findings[kind]), len(drafts)))


if __name__ == "__main__":
    main()
