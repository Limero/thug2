#!/usr/bin/env python3
"""Rewrite .rodata symbol labels to .rodata2 for addresses >= the second rodata section start."""
import re
import sys

path = sys.argv[1]
threshold = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x8028FB60

pat = re.compile(r"\.rodata:(0x[0-9A-Fa-f]+)")

with open(path) as f:
    lines = f.readlines()

out = []
changed = 0
for line in lines:
    m = pat.search(line)
    if m:
        addr = int(m.group(1), 16)
        if addr >= threshold:
            line = line.replace(".rodata:", ".rodata2:", 1)
            changed += 1
    out.append(line)

with open(path, "w") as f:
    f.writelines(out)
print(f"rewrote {changed} symbols to .rodata2")
