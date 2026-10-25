#!/usr/bin/env python3
"""Apply QB constant names to src/ and src/wip/ magic 0xXXXXXXXX literals.

The game passes QB script hashes (trick names, script names, ...) around as
opaque u32s; decompiled C shows them as bare 8-digit hex literals:

    fn_801A5210(temp_r31, 0x9B65D7B8)   ->   fn_801A5210(temp_r31, QB_OLLIE)

tools/gen_qb_constants.py produces include/qb_constants.h with a
QB_<NAME> define per hash that (a) appears as a literal in src+wip and
(b) resolves to a plaintext name in the .prg dictionary. This tool rewrites
the literals to the constants (non-comment lines only) and inserts the
include after the types.h include when a file gains any constant.

Byte-safe: constants are #defines expanding to the identical literal, so
promoted (src/) files rebuild to identical bytes; wip drafts are INERT.
Idempotent: an already-rewritten file has no matching literals left.

Usage:
    tools/venv/bin/python tools/apply_qb_constants.py [--dry-run]
    tools/venv/bin/python tools/apply_qb_constants.py --addr 0x801A6070
"""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from qb_hash import subst_qb_constants, subst_qb_placeholders  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

DRY = "--dry-run" in sys.argv
ADDR = None
if "--addr" in sys.argv:
    ADDR = int(sys.argv[sys.argv.index("--addr") + 1], 16)

INCLUDE_LINE = '#include "qb_constants.h"'


def ensure_include(text):
    """Insert the qb_constants include after the types.h include if missing.
    Returns (new_text, inserted)."""
    if "qb_constants.h" in text:
        return text, False
    lines = text.split("\n")
    out = []
    inserted = False
    for ln in lines:
        out.append(ln)
        if not inserted and ln.strip() == '#include "types.h"':
            out.append(INCLUDE_LINE)
            inserted = True
    if not inserted:
        # no types.h include to anchor on — prepend both includes
        out = ['#include "types.h"', INCLUDE_LINE] + out
        inserted = True
    return "\n".join(out), inserted


def candidates():
    files = sorted(glob.glob("src/*.c")) + sorted(glob.glob("src/wip/*.c"))
    if ADDR is not None:
        files = [f for f in files if ("fn_%08X" % ADDR) in f]
    return files


total_files = 0
total_tokens = 0
total_renames = 0
touched = []
for fp in candidates():
    t = open(fp).read()
    new, n = subst_qb_constants(t)
    new, r = subst_qb_placeholders(new)
    if n or r:
        new, _ins = ensure_include(new)
        total_tokens += n
        total_renames += r
        total_files += 1
        touched.append(os.path.basename(fp))
        if not DRY:
            open(fp, "w").write(new)

print("files touched:       %d" % total_files)
print("literals rewritten: %d" % total_tokens)
print("placeholders renamed: %d" % total_renames)

for b in touched:
    print("   %s" % b)
if DRY:
    print("(dry run — no files written)")
