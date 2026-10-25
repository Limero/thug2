#!/usr/bin/env python3
"""Idempotently write per-function split entries + configure.py Object lines for
the vcall_*.c files (one file per function — patterns with branches must be one
function per TU because GCC 2.95.2 reuses .L3 labels across functions)."""
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

files = sorted(glob.glob(f"{ROOT}/src/vcall_*.c"))
print(f"found {len(files)} per-function files")

# --- splits.txt: strip any existing vcall blocks, then append fresh ---
splitp = f"{ROOT}/config/G2TE52/splits.txt"
with open(splitp) as f:
    splits = f.read()
splits = re.sub(r"\n\nvcall(?:_[0-9A-Fa-f]+)?\.c:.*?(?=\n\n\S|\Z)", "\n", splits, flags=re.S)
splits = re.sub(r"\n{3,}", "\n\n", splits).rstrip() + "\n"

blocks = []
for fp in files:
    name = os.path.basename(fp)
    m = re.search(r"range 0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+)", open(fp).read())
    s = int(m.group(1), 16)
    e = int(m.group(2), 16)
    blocks.append(f"{name}:\n\t.text       start:0x{s:X} end:0x{e:X}")
splits += "\n" + "\n\n".join(blocks) + "\n"
with open(splitp, "w") as f:
    f.write(splits)
print(f"wrote {len(blocks)} entries to splits.txt")

# --- configure.py: strip existing vcall object lines, then add fresh ---
cfgp = f"{ROOT}/configure.py"
with open(cfgp) as f:
    cfg = f.read()
cfg = re.sub(r'            Object\(Matching, "vcall_[^"]*"\),\n', "", cfg)
objs = "\n".join(f'            Object(Matching, "{os.path.basename(fp)}"),'
                  for fp in files)
anchor = '            Object(Matching, "gen_dispatch_129.c"),'
if anchor not in cfg:
    # fallback: anchor after the last gen_dispatch object line
    gd = re.findall(r'(            Object\(Matching, "gen_dispatch_\d+\.c"\),)\n', cfg)
    assert gd, "no gen_dispatch anchor found in configure.py"
    anchor = gd[-1]
assert anchor in cfg, f"anchor line missing from configure.py — cannot register vcall objects"
cfg = cfg.replace(anchor, anchor + "\n" + objs)
with open(cfgp, "w") as f:
    f.write(cfg)
n_objs = cfg.count('"vcall_')
print(f"configure.py now has {n_objs} vcall object lines")
