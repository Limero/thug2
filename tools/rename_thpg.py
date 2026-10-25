#!/usr/bin/env python3
"""Rename functions from Wii Proving Ground symbol evidence (plan §6/§6a).

Proposal format (explicit — the analyst applies the §6a C-name rules, the
tool only validates and applies):
  ADDR:CName:TIER   e.g. 0x80010A00:MemAvailable:A  0x80012154:CompactPool_Free:A

For every proposal:
  1. symbols.txt : fn_XXXX -> CName (+ scope:global). Guards: ADDR must be a
     real ^fn_[0-9A-F]{8}$ .text function; CName must be a valid C identifier;
     CName must not collide with any existing symbol OR another proposal
     (REFUSE on collision — overloads must be pre-suffixed _2, _3 by the
     analyst per §6a rule 2); the method part should exist in
     docs/thpg-func-names.tsv (WARN only — evidence lives in the plan, not here).
  2. src/fn_XXXX.c (when matched): rename the definition + insert
     '// Name @ 0xADDR' (plan §6 step 4 marker).
  3. all src/*.c and src/wip/*.c : word-boundary rename of callers/externs.
Filenames stay address-based (splits.txt / configure.py untouched).
Idempotent: already-renamed symbols are skipped.

DEFAULT IS DRY-RUN: prints exactly what would change and exits 0 without
writing anything. Pass --apply to write (still refuses on any collision).

Usage:
  tools/venv/bin/python tools/rename_thpg.py 0x80010A00:MemAvailable:A [...]
  tools/venv/bin/python tools/rename_thpg.py --dry-run 0x80010A00:MemAvailable:A [...]
  tools/venv/bin/python tools/rename_thpg.py --apply 0x80010A00:MemAvailable:A [...]
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

APPLY = "--apply" in sys.argv
args = [a for a in sys.argv[1:] if a not in ("--apply", "--dry-run")]

proposals = []
seen_cname = {}
errors = []
for a in args:
    p = a.split(":")
    if len(p) != 3:
        errors.append("bad proposal (want ADDR:CName:TIER): %r" % a)
        continue
    addr_s, cname, tier = p
    m = re.match(r"^0x([0-9A-Fa-f]{8})$", addr_s)
    if not m:
        errors.append("bad address: %r" % addr_s)
        continue
    addr = "0x" + m.group(1).upper()
    fn = "fn_" + m.group(1).upper()
    if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", cname or ""):
        errors.append("bad C name: %r" % cname)
        continue
    if tier not in ("A", "B", "C"):
        errors.append("bad tier (want A/B/C): %r" % a)
        continue
    if cname in seen_cname:
        errors.append("collision in batch: %s claimed by %s and %s"
                      % (cname, seen_cname[cname], addr))
        continue
    seen_cname[cname] = addr
    proposals.append((fn, addr, cname, tier))

if errors:
    print("REFUSED:")
    for e in errors:
        print("  " + e)
    sys.exit(1)

if not proposals:
    print("no proposals given")
    sys.exit(1)

# ---- load symbols.txt ----
symlines = open("config/G2TE52/symbols.txt").read().splitlines(keepends=True)
symmap = {}  # name -> full line pieces
existing = set()
for ln in symlines:
    m = re.match(r"^(\S+) = (\S+); // (.*)$", ln.rstrip("\n"))
    if m:
        existing.add(m.group(1))
        symmap[m.group(1)] = (m.group(2), m.group(3))

# ---- load Wii corpus method vocabulary (warn-only cross-check) ----
wii_methods = set()
try:
    with open("docs/thpg-func-names.tsv", encoding="utf-8") as f:
        next(f)
        for line in f:
            p = line.rstrip("\n").split("\t")
            if len(p) >= 4:
                wii_methods.add(p[2])  # method column
except OSError:
    pass

rename = {}  # fn -> (cname, addr, tier)
for fn, addr, cname, tier in proposals:
    if fn not in symmap:
        print("REFUSED: %s not in symbols.txt" % fn)
        sys.exit(1)
    scope, rest = symmap[fn]
    if not scope.startswith(".text:"):
        print("REFUSED: %s is not a .text function (%s)" % (fn, scope))
        sys.exit(1)
    if cname in existing:
        print("REFUSED: collision with existing symbol %s (wanted by %s %s)"
              % (cname, fn, addr))
        sys.exit(1)
    # method cross-check: last _-segment should be a known Wii method
    meth = cname.split("_")[-1]
    if wii_methods and meth not in wii_methods and cname not in wii_methods:
        print("WARN: %s looks unknown to thpg-func-names.tsv "
              "(evidence must be in the plan)" % cname)
    rename[fn] = (cname, addr, tier)


print("proposals: %d  mode: %s" % (len(rename), "APPLY" if APPLY else "DRY-RUN"))

# ---- 1. symbols.txt preview / apply ----
changed = 0
out = []
for ln in symlines:
    m = re.match(r"^(fn_[0-9A-F]{8}) = (\S+); // (.*)$", ln.rstrip("\n"))
    if m and m.group(1) in rename:
        cname, addr, tier = rename[m.group(1)]
        rest = m.group(3)
        if "scope:global" not in rest:
            rest = rest.rstrip() + " scope:global"
        new = "%s = %s; // %s\n" % (cname, m.group(2), rest)
        if APPLY:
            out.append(new)
        else:
            out.append(ln)
            print("  symbols.txt: %s  ->  %s" % (ln.rstrip("\n"), new.rstrip("\n")))
        changed += 1
    else:
        out.append(ln)
if APPLY:
    open("config/G2TE52/symbols.txt", "w").writelines(out)
print("symbols.txt lines %s: %d" % ("changed" if APPLY else "would change", changed))

# ---- 2+3. source sweep preview / apply ----
pat = re.compile(r"\b(" + "|".join(re.escape(s) for s in rename) + r")\b")
src_files = ["src/%s" % f for f in sorted(os.listdir("src")) if f.endswith(".c")]
wip_files = ["src/wip/%s" % f for f in sorted(os.listdir("src/wip")) if f.endswith(".c")]


def hits(paths):
    out = []
    for fp in paths:
        try:
            t = open(fp).read()
        except OSError:
            continue
        n = len(pat.findall(t))
        if n:
            out.append((fp, n))
    return out


for label, paths in (("src", src_files), ("wip", wip_files)):
    for fp, n in hits(paths):
        print("  %s: %s (%d tokens%s)" % (label, fp, n, "" if APPLY else " would rename"))

if APPLY:
    def sub(m):
        return rename[m.group(1)][0]
    total = 0
    for fp in src_files + wip_files:
        try:
            t = open(fp).read()
        except OSError:
            continue
        t2, n = pat.subn(sub, t)
        if n:
            open(fp, "w").write(t2)
            total += n
    print("total token replacements:", total)

    # ---- 4. address comments above each definition ----
    for sym, (name, addr, tier) in rename.items():
        fp = "src/%s.c" % sym
        if not os.path.exists(fp):
            continue
        t = open(fp).read()
        lines = t.splitlines(keepends=True)
        idx = None
        for i, ln in enumerate(lines):
            if re.search(r"\b%s\s*\(" % re.escape(name), ln):
                idx = i
                break
        if idx is None:
            print("WARN: no definition line for", sym, name)
            continue
        comment = "// %s @ %s\n" % (name, addr)
        if idx > 0 and comment.strip() in lines[idx - 1]:
            continue
        lines.insert(idx, comment)
        open(fp, "w").writelines(lines)

print("done (%s)" % ("APPLIED" if APPLY else "DRY-RUN, nothing written"))
