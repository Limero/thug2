#!/usr/bin/env python3
import difflib
import inspect
import os
import re
import sys
import textwrap

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fill_wip_drafts as fw
from bisect_rules import make_limited_postprocess


def split_steps(body):
    parts = []
    cur = []
    for ln in body.split("\n"):
        cur.append(ln)
        if re.match(r"^    out = ", ln):
            parts.append("\n".join(cur))
            cur = []
    if cur:
        parts.append("\n".join(cur))
    return parts


pl = make_limited_postprocess()
addr = 0x800808EC
text = open(f"{ROOT}/src/wip/fn_{addr:08X}.c").read()
size = int(re.search(r"size=(\d+)B", text).group(1))
asm_lines, _ = fw.disasm_with_labels(addr, size)
raw = fw.run_m2c("\n".join(asm_lines) + "\n")

o30 = pl(raw, 30)

# build ns as the bisect does, exec chunks 1..30, then chunk 31 alone
ns = dict(fw.__dict__)
ns["out"] = raw
src = inspect.getsource(fw.postprocess)
body = src.split("\n", 1)[1]
parts = split_steps(body)
for chunk in parts[:30]:
    try:
        exec(textwrap.dedent(chunk), ns)
    except (IndentationError, SyntaxError):
        continue
    except Exception as e:
        print(f"chunk exec error: {e}")
assert ns["out"] == o30, "ns out != pl(raw,30)!"

chunk31 = parts[30]
print("=== chunk 31 source ===")
print(chunk31)
print()
try:
    exec(textwrap.dedent(chunk31), ns)
    out31 = ns["out"]
except Exception as e:
    print(f"chunk31 exec error: {type(e).__name__}: {e}")
    sys.exit(1)

print("=== diff o30 -> out31 ===")
for d in difflib.unified_diff(o30.splitlines(), out31.splitlines(), lineterm=""):
    if d.startswith(("+", "-")) and not d.startswith(("+++", "---")):
        print(d[:200])
