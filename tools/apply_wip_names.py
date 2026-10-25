#!/usr/bin/env python3
"""Apply real symbol names to WIP draft bodies (src/wip/fn_*.c).

Every src/wip draft is generated from the DOL disassembly, so its own
definition and every callee call site start life as fn_XXXXXXXX. m2c drafts
already pick up real names at generation time (fill_wip_drafts names calls via
gl.fn_name(), which reads symbols.txt scope:global entries), but drafts
generated before a rename, or renames applied after generation, can leave
stale fn_XXXXXXXX tokens in a body.

This tool sweeps ALL existing drafts and rewrites, in non-comment lines only:

  - the draft's own definition symbol (fn_XXXXXXXX -> RealName)
  - every callee reference (fn_XXXXXXXX( -> RealName()

when the address has a real (non-fn_) name in symbols.txt. Filenames stay
address-based (splits.txt/configure.py key off them — project convention).
Comment lines are untouched: the WIP header carries the address/size marker
and park notes and must stay faithful.

Safety: promote_wip.py and gen_leaves.compile_fn are name-agnostic — they
compile the body as-is and the symbol name does not affect code bytes, so
renaming is byte-safe. wip drafts are INERT (not in the build), so the DOL is
untouched by construction.

Idempotent: a fn_XXXXXXXX with no real name is left alone; an already-renamed
draft has no fn_ tokens left to replace.

Usage:  tools/venv/bin/python tools/apply_wip_names.py [--dry-run]
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

DRY = "--dry-run" in sys.argv

# ---- 1. build addr -> real-name map from symbols.txt ----
real_by_addr = {}   # int addr -> real name
for line in open("config/G2TE52/symbols.txt"):
    m = re.match(r"^([A-Za-z_][A-Za-z0-9_]*) = \.text:0x([0-9A-F]{8}); // type:function", line)
    if m and not m.group(1).startswith("fn_"):
        real_by_addr[int(m.group(2), 16)] = m.group(1)

# fn_XXXXXXXX (string) -> real name, for word-boundary replacement
fn_to_real = {}
for addr, name in real_by_addr.items():
    # keep compiler/linker artifacts out: the gpr save/restore helpers
    # (symbols.txt uses both _savegpr_NN and __save_gpr forms) and jumptable_
    # data labels are not game functions — renaming drafts to them adds noise.
    if re.match(r"^_{0,2}(save|restore)_?gpr", name) or name.startswith("jumptable_"):
        continue
    fn_to_real["fn_%08X" % addr] = name

pat = re.compile(r"\b(" + "|".join(re.escape(k) for k in sorted(fn_to_real, key=len, reverse=True)) + r")\b")

def apply(text):
    """Rewrite fn_ -> real name on non-comment lines. Returns (new, n)."""
    out = []
    n = 0
    for ln in text.splitlines(keepends=True):
        if ln.lstrip().startswith("//"):
            out.append(ln)
            continue
        new, k = pat.subn(lambda m: fn_to_real[m.group(1)], ln)
        out.append(new)
        n += k
    return "".join(out), n

total_files = 0
total_tokens = 0
touched = []
for fp in sorted(glob.glob("src/wip/fn_*.c")):
    t = open(fp).read()
    new, n = apply(t)
    if n:
        total_tokens += n
        total_files += 1
        touched.append(os.path.basename(fp))
        if not DRY:
            open(fp, "w").write(new)

print("real names available: %d" % len(fn_to_real))
print("drafts touched:       %d" % total_files)
print("tokens renamed:       %d" % total_tokens)
for b in touched:
    print("   %s" % b)
if DRY:
    print("(dry run — no files written)")
