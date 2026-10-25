#!/usr/bin/env python3
"""Idempotently register the gen_leaves-generated src/fn_*.c files (those
with a 'range 0x...-0x...' comment) into splits.txt + configure.py.

Only touches files carrying the generator's 'range' marker, so hand-written
fn_*.c files (which lack it) keep their existing entries untouched.

NEW: only adds entries that are missing — preserves existing entry order
in splits.txt and configure.py to avoid shifting the link layout.
"""
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# generated files = those with a "range 0x..." marker (also accept the
# WIP-draft "range=0x..." form used by src/wip/fn_*.c so manual copies
# register too)
files = []
for fp in sorted(glob.glob(f"{ROOT}/src/fn_*.c")):
    txt = open(fp).read()
    if re.search(r"range\s*=?\s*0x[0-9A-Fa-f]+-0x[0-9A-Fa-f]+", txt):
        files.append(fp)
print(f"found {len(files)} generated fn_ files")

names = {os.path.basename(f) for f in files}

# --- splits.txt ---
splitp = f"{ROOT}/config/G2TE52/splits.txt"
with open(splitp) as f:
    splits = f.read()

# Build expected blocks for each file
blocks_by_name = {}
for fp in files:
    name = os.path.basename(fp)
    m = re.search(r"range\s*=?\s*0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+)", open(fp).read())
    s = int(m.group(1), 16)
    e = int(m.group(2), 16)
    blocks_by_name[name] = f"{name}:\n\t.text       start:0x{s:X} end:0x{e:X}"

# Find which entries are missing from splits.txt
missing = [n for n in sorted(names) if n + ":" not in splits]
already = len(names) - len(missing)
print(f"splits.txt: {already} present, {len(missing)} missing")

if missing:
    new_blocks = "\n\n".join(blocks_by_name[n] for n in missing)
    splits = splits.rstrip() + "\n\n" + new_blocks + "\n"
    with open(splitp, "w") as f:
        f.write(splits)
    print(f"added {len(missing)} new entries to splits.txt")
else:
    print("splits.txt: no changes needed")

# --- configure.py ---
cfgp = f"{ROOT}/configure.py"
with open(cfgp) as f:
    cfg = f.read()

# Check which fn_ object lines are missing from configure.py
missing_cfg = []
for fp in files:
    name = os.path.basename(fp)
    # Check if this name already has an Object(Matching, ...) line
    if re.search(rf'Object\(Matching,\s*"{re.escape(name)}"', cfg):
        continue
    missing_cfg.append(fp)

print(f"configure.py: {len(names) - len(missing_cfg)} present, {len(missing_cfg)} missing")

if missing_cfg:
    def _obj_line(fp):
        # honor a // extra_cflags: marker in the source header
        try:
            head = open(fp, encoding="utf-8", errors="replace").read(400)
        except OSError:
            head = ""
        m = re.search(r"// extra_cflags:\s*([^\n]+)", head)
        if m:
            flags = [f.strip() for f in m.group(1).split(",") if f.strip()]
            quoted = ", ".join(f'"{f}"' for f in flags)
            return f'            Object(Matching, "{os.path.basename(fp)}", extra_cflags=[{quoted}]),'
        return f'            Object(Matching, "{os.path.basename(fp)}"),'

    objs = "\n".join(_obj_line(fp) for fp in missing_cfg)
    anchor = '            Object(Matching, "gen_dispatch_000.c"),'
    if anchor not in cfg:
        gd = re.findall(r'(            Object\(Matching, "gen_dispatch_\d+\.c"\),)\n', cfg)
        assert gd, "no gen_dispatch anchor found in configure.py"
        anchor = gd[0]
    assert anchor in cfg, "anchor line missing from configure.py"
    cfg = cfg.replace(anchor, anchor + "\n" + objs)
    with open(cfgp, "w") as f:
        f.write(cfg)
    print(f"added {len(missing_cfg)} new entries to configure.py")
else:
    print("configure.py: no changes needed")

print(f"configure.py now has {cfg.count('\"fn_')} fn_ object lines")
