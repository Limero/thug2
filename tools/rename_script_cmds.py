#!/usr/bin/env python3
"""Rename script-command functions to their real names.

Default (matched-only): every registry row with decompiled=Y and an existing
src/fn_XXXX.c gets renamed. With --all, EVERY non-stub registry handler is
renamed in symbols.txt even when not matched yet (real names from game data:
rows are {name, handler} pairs read out of DOL .data) - so future matches
auto-name (gl.fn_name reads scope:global) and wip drafts show real names.

For every rename:
  1. symbols.txt : fn_XXXX -> Script<Name> (add scope:global so tooling picks
     it up). Script-prefixed so the handler family is greppable as one group
     (M6.77).
  2. src/fn_XXXX.c (when matched): rename the definition symbol + insert
     '// Name @ 0xADDR'
  3. all src/*.c and src/wip/*.c : word-boundary rename of callers/externs
Filenames stay address-based (splits.txt / configure.py untouched).
Idempotent: already-Script-prefixed symbols are skipped. Stub handlers
(stub=Y, 8-byte li/blr placeholders for commands stripped on GC) are NEVER
renamed - their fn_ address is not a real command implementation. Same for
placeholder rows (sym='-', commands stripped on GC): sym must match
^fn_[0-9A-F]{8}$ or the row is skipped (M6.87 regression guard).

Usage:  tools/venv/bin/python tools/rename_script_cmds.py [--all]
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

# ---- 1. build rename map from the registry ----
ALL = "--all" in sys.argv

rows = []
for line in open("docs/rodata2-script-command-registry.tsv"):
    if line.startswith("#") or not line.strip():
        continue
    p = line.rstrip("\n").split("\t")
    if len(p) < 6:
        continue
    rows.append(dict(name=p[0], addr=p[1], sym=p[2], size=p[3], dec=p[4], stub=p[5]))

# first-name-wins for multi-name symbols; stubs AND placeholder rows never
# renamed. A placeholder sym (e.g. '-' for commands stripped on GC) keyed the
# map with '-' and the word-boundary regex matched EVERY '-' in src+wip
# (M6.87 regression - 27,831 replacements, reversed via sed). Robust guard:
# only accept real fn_ symbols + non-empty names, so ANY malformed/placeholder
# value (not just '-') is skipped.
rename = {}  # fn_sym -> (name, addr)
for r in rows:
    nm = r["name"].strip()
    if r["stub"] == "Y" or not nm or not re.match(r"^fn_[0-9A-F]{8}$", r["sym"]):
        continue
    if not ALL:
        if r["dec"] != "Y" or not os.path.exists("src/%s.c" % r["sym"]):
            continue
    if r["sym"] not in rename:
        # some registry names already carry the Script prefix (ScriptExists,
        # ScriptAssert, ScriptWaitForEvent...) - never double-prefix
        nm = r["name"] if r["name"].startswith("Script") else "Script" + r["name"]
        rename[r["sym"]] = (nm, r["addr"])

print("symbols to rename (%s):" % ("--all" if ALL else "matched-only"), len(rename))

# ---- 2. symbols.txt ----
symlines = open("config/G2TE52/symbols.txt").read().splitlines(keepends=True)
changed = 0
out = []
for ln in symlines:
    m = re.match(r"^(fn_[0-9A-F]{8}) = (\S+); // (.*)$", ln.rstrip("\n"))
    if m and m.group(1) in rename:
        name, addr = rename[m.group(1)]
        assert name != m.group(1), "self-rename?!"
        rest = m.group(3)
        if "scope:global" not in rest:
            rest = rest.rstrip() + " scope:global"
        out.append("%s = %s; // %s\n" % (name, m.group(2), rest))
        changed += 1
    else:
        out.append(ln)
open("config/G2TE52/symbols.txt", "w").writelines(out)
print("symbols.txt lines changed:", changed)

# ---- 3. source renames: find all files referencing any fn_ token ----
syms = list(rename.keys())
pat = re.compile(r"\b(" + "|".join(re.escape(s) for s in syms) + r")\b")

def files_with(pattern, paths):
    hit = []
    for fp in paths:
        try:
            t = open(fp).read()
        except OSError:
            continue
        if pattern.search(t):
            hit.append(fp)
    return hit

src_files = ["src/%s" % f for f in sorted(os.listdir("src")) if f.endswith(".c")]
wip_files = ["src/wip/%s" % f for f in sorted(os.listdir("src/wip")) if f.endswith(".c")]

src_hit = files_with(pat, src_files)
wip_hit = files_with(pat, wip_files)
print("src/*.c files to touch:", len(src_hit), " wip files to touch:", len(wip_hit))

# word-boundary replace per file
def rewrite(fp):
    t = open(fp).read()
    def sub(m):
        return rename[m.group(1)][0]
    t2, n = pat.subn(sub, t)
    if n:
        open(fp, "w").write(t2)
    return n

total = 0
for fp in src_hit + wip_hit:
    total += rewrite(fp)
print("total token replacements:", total)

# ---- 4. address comments above each definition (matched files only) ----
for sym, (name, addr) in rename.items():
    fp = "src/%s.c" % sym
    if not os.path.exists(fp):
        continue  # unmatched: renamed in symbols.txt only
    t = open(fp).read()
    lines = t.splitlines(keepends=True)
    # find the definition line: first line containing \bName\s*\(
    idx = None
    for i, ln in enumerate(lines):
        if re.search(r"\b%s\s*\(" % re.escape(name), ln):
            idx = i
            break
    if idx is None:
        print("WARN: no definition line for", sym, name)
        continue
    comment = "// %s @ %s\n" % (name, addr)
    # don't double-insert
    if idx > 0 and comment.strip() in lines[idx - 1]:
        continue
    lines.insert(idx, comment)
    open(fp, "w").writelines(lines)

print("done")
