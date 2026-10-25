#!/usr/bin/env python3
"""Idempotently write per-range split entries + configure.py Object lines for
the gen_dispatch_*.c files (one file per contiguous range, to avoid dtk
link-order cycles). Safe to run repeatedly."""
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

files = sorted(glob.glob(f"{ROOT}/src/gen_dispatch_*.c"))
print(f"found {len(files)} per-range files")

# --- splits.txt: strip any existing gen_dispatch blocks, then append fresh ---
splitp = f"{ROOT}/config/G2TE52/splits.txt"
with open(splitp) as f:
    splits = f.read()
splits = re.sub(r"\n\ngen_dispatch(?:_\d+)?\.c:.*?(?=\n\n\S|\Z)", "\n", splits, flags=re.S)
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

# --- configure.py: strip existing gen_dispatch object lines, then add fresh ---
cfgp = f"{ROOT}/configure.py"
with open(cfgp) as f:
    cfg = f.read()
cfg = re.sub(r'            Object\(Matching, "gen_dispatch[^"]*"\),\n', "", cfg)
objs = "\n".join(f'            Object(Matching, "{os.path.basename(fp)}"),'
                  for fp in files)
anchor = '            Object(Matching, "fn_8005F28C.c"),'
assert anchor in cfg, f"anchor line missing from configure.py — cannot register gen_dispatch objects"
cfg = cfg.replace(anchor, anchor + "\n" + objs)
with open(cfgp, "w") as f:
    f.write(cfg)
n_objs = cfg.count('"gen_dispatch_')
print(f"configure.py now has {n_objs} gen_dispatch object lines")
