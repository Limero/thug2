#!/usr/bin/env python3
"""Compile a body variant for a WIP draft and print the want|got diff.

Usage: vtry.py ADDR [--file V.c] [flags...]
Keeps the draft's `dolphin/*.h` includes and its `// FLAG:` lines, appends the
variant body, then runs tools/want_got.py.  Unlike want_got.py --file (which
loses both), this re-injects the draft's flags so a variant is scored under the
same conditions as the parked body.

If ngccc rejects the variant, the compiler's stderr is printed and the exit
code is 1 (want_got.py otherwise dies with a TypeError on `got = None`).
"""
import os
import re
import subprocess
import sys

ADDR = int(sys.argv[1], 16)
args = sys.argv[2:]
path = None
if "--file" in args:
    i = args.index("--file")
    path = args[i + 1]
    del args[i:i + 2]
flags = args

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
draft = os.path.join(ROOT, "src/wip", f"fn_{ADDR:08X}.c")
raw = open(draft).read()

includes = "\n".join(l for l in raw.splitlines() if l.startswith("#include"))
flaglines = [l for l in raw.splitlines() if re.match(r"^//\s*(?:FLAG|extra_cflags):", l)]
for l in flaglines:
    m = re.match(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", l)
    for t in m.group(1).split():
        if re.match(r"^-", t) and t not in flags:
            flags.append(t)

out = "<scratch>"
with open(out, "w") as f:
    f.write("\n".join(flaglines) + "\n" + includes + "\n" + open(path).read() + "\n")

sys.path.insert(0, os.path.join(ROOT, "tools"))
import gen_leaves as gl  # noqa: E402

body = "".join(l + "\n" for l in open(out) if not l.lstrip().startswith("//"))
if "__ps_t" in body and "-mps-float" not in flags:
    flags = flags + ["-mps-float"]
os.environ["LEAF_TMPDIR"] = "<scratch>"
os.makedirs(os.environ["LEAF_TMPDIR"], exist_ok=True)
probe, err = gl.compile_fn(ADDR, body, extra_flags=flags or None)
if probe is None:
    print(f"COMPILE FAILED: {err}")
    sys.exit(1)

cmd = [f"{ROOT}/tools/venv/bin/python", f"{ROOT}/tools/want_got.py", f"{ADDR:08X}",
       "--file", out] + flags
sys.exit(subprocess.call(cmd))