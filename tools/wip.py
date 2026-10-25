#!/usr/bin/env python3
"""WIP (non-matching) function workflow.

Parked functions (FPR-frame quirk, GC-compiler idioms, cross-function tail
merges, ...) cannot be matched with the available compilers. Writing them as
"plain C files that contain asm" would FAKE the objdiff match count (objdiff
compares compiled object bytes against the original — a C file whose body is
the original asm assembles to identical bytes and reports 100% matched, so
progress would jump to ~100% while nothing is actually decompiled).

Instead, keep best-guess C drafts for parked functions in src/wip/:

  - NOT registered in splits.txt / configure.py  -> never compiled
  - the DOL stays byte-identical (drafts are inert)
  - objdiff progress stays honest (no object = no match score)
  - the C is versioned, readable, and ready to activate the moment a
    blocker (e.g. a fixed compiler build) is solved.

Usage:
  tools/wip.py list                       show all WIP drafts
  tools/wip.py add  <addr> <draft.c>      register a draft (copies into
                                          src/wip/, records in WIP.md)
  tools/wip.py activate <addr>            copy draft to src/, wire into
                                          splits.txt + configure.py, rebuild.
                                          The DOL will DIFFER if it doesn't
                                          match — that's the point (iterate
                                          against objdiff until it does).
  tools/wip.py deactivate <addr>          unwire (remove src file + splits +
                                          configure), rebuild -> byte-identical
                                          asm coverage restored.
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
WIP_DIR = f"{ROOT}/src/wip"
SPLITS = f"{ROOT}/config/G2TE52/splits.txt"
CONFIG = f"{ROOT}/configure.py"
REG = f"{ROOT}/WIP.md"


def read_sizes():
    """{addr: size} from the objdiff report's function boundaries."""
    rep = json.load(open(f"{ROOT}/build/G2TE52/report.json"))
    sizes = {}
    for u in rep.get("units", []):
        for fn in u.get("functions", []):
            sizes[int(fn["metadata"]["virtual_address"])] = int(fn["size"])
    return sizes


def norm_addr(a):
    return int(a, 16) if isinstance(a, str) else a


def block_name(addr):
    return f"fn_{addr:08X}.c"


def next_fn_addr(addr, sizes):
    addrs = sorted(a for a in sizes if a > addr)
    return addrs[0] if addrs else addr + sizes.get(addr, 0)


def find_block(text, name):
    m = re.search(
        rf"(?m)^(?:{re.escape(name)}):\n\s*\.text\s+start:(0x[0-9A-Fa-f]+) end:(0x[0-9A-Fa-f]+)",
        text,
    )
    if not m:
        return None
    return int(m.group(1), 16), int(m.group(2), 16)


def remove_block(text, name):
    text = re.sub(
        rf"(?m)^(?:{re.escape(name)}):\n\s*\.text\s+start:[^\n]+\n?", "", text
    )
    return re.sub(r"\n{3,}", "\n\n", text).rstrip() + "\n"


def add_configure(name):
    cfg = open(CONFIG).read()
    line = f'            Object(Matching, "{name}"),\n'
    if line in cfg:
        return
    anchor = '            Object(Matching, "gen_dispatch_000.c"),'
    if anchor not in cfg:
        gd = re.findall(r'(            Object\(Matching, "gen_dispatch_\d+\.c"\),)\n', cfg)
        assert gd, "no gen_dispatch anchor found in configure.py"
        anchor = gd[0]
    cfg = cfg.replace(anchor, anchor + "\n" + line)
    open(CONFIG, "w").write(cfg)


def remove_configure(name):
    """Remove any Object(Matching, "fn_XXXXXXXX") entry, with or without .c.
    The bare form (no .c) can be left behind by broken activate attempts."""
    cfg = open(CONFIG).read()
    cfg = re.sub(
        rf'            Object\(Matching, "{re.escape(name[:-2])}(?:\.c)?"\),\n',
        "", cfg)
    open(CONFIG, "w").write(cfg)


def reconfigure():
    subprocess.run(
        ["python3", "configure.py", "--dtk", "tools/dtk",
         "--ninja", "tools/ninja", "--compilers", "build/compilers"],
        cwd=ROOT, capture_output=True)
    subprocess.run(["rm", "-f", "build/G2TE52/config.json"], cwd=ROOT)
    subprocess.run(["tools/ninja", "build/G2TE52/config.json"], cwd=ROOT,
                   capture_output=True)


def build_dol():
    subprocess.run(["rm", "-f", "build/G2TE52/main.elf", "build/G2TE52/main.dol"],
                   cwd=ROOT)
    r = subprocess.run(["tools/ninja", "build/G2TE52/main.dol"], cwd=ROOT,
                       capture_output=True, text=True)
    return subprocess.run(["cmp", "-s", "orig/G2TE52/sys/main.dol",
                           "build/G2TE52/main.dol"], cwd=ROOT).returncode == 0, r.stdout[-1500:]


def objdiff_score(name):
    """Build the single object and report its objdiff match vs the original."""
    obj = name[:-2] + ".o"
    r = subprocess.run(["tools/ninja", f"build/G2TE52/src/{obj}"],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print(f"error: ninja failed to build {obj}:")
        print(r.stderr[-800:])
        return None, None
    subprocess.run(["rm", "-f", "build/G2TE52/report.json"], cwd=ROOT)
    subprocess.run(["build/tools/objdiff-cli", "report", "generate",
                    "-o", "build/G2TE52/report.json"], cwd=ROOT,
                   capture_output=True, text=True)
    rep = json.load(open(f"{ROOT}/build/G2TE52/report.json"))
    for u in rep.get("units", []):
        if u.get("name", "").endswith(name[:-2]):
            for fn in u.get("functions", []):
                return fn.get("matches"), fn.get("fuzzy_match_percent")
    return None, None


def cmd_list(_):
    if not os.path.isdir(WIP_DIR):
        print("no WIP drafts yet (src/wip/ is empty)")
        return
    for f in sorted(os.listdir(WIP_DIR)):
        if f.endswith(".c"):
            print(f"  {f}")


def cmd_add(args):
    addr = norm_addr(args.addr)
    name = f"fn_{addr:08X}"
    os.makedirs(WIP_DIR, exist_ok=True)
    dst = f"{WIP_DIR}/{name}.c"
    if os.path.abspath(args.draft) == os.path.abspath(dst):
        print(f"{name} already in {dst}")
    else:
        if not os.path.isfile(args.draft):
            print(f"error: draft {args.draft} not found")
            sys.exit(1)
        shutil.copyfile(args.draft, dst)
        print(f"copied draft -> {dst}")
    line = f"| {name} | 0x{addr:08X} | {args.note or ''} |\n"
    if os.path.isfile(REG):
        txt = open(REG).read()
        txt = re.sub(rf"(?m)^\| {name} \|.*$\n", "", txt)
        if not txt.endswith("\n"):
            txt += "\n"
        txt += line
        open(REG, "w").write(txt)
    else:
        open(REG, "w").write(line)
    print(f"registered {name} in WIP.md")


def cmd_activate(args):
    addr = norm_addr(args.addr)
    name = block_name(addr)
    draft = f"{WIP_DIR}/fn_{addr:08X}.c"
    if not os.path.isfile(draft):
        print(f"error: no WIP draft at {draft}; use `wip.py add` first")
        sys.exit(1)
    sizes = read_sizes()
    if addr not in sizes:
        print(f"error: 0x{addr:X} not a function boundary")
        sys.exit(1)
    end = next_fn_addr(addr, sizes)
    sp = open(SPLITS).read()
    if find_block(sp, name):
        print(f"already activated ({name})")
        return
    # 1. copy draft into src/ so dtk compiles it
    shutil.copyfile(draft, f"{ROOT}/src/{name}")
    # 2. splits.txt block (dtk auto-fills every other gap with asm)
    sp = sp.rstrip() + f"\n\n{name}:\n\t.text       start:0x{addr:X} end:0x{end:X}\n"
    open(SPLITS, "w").write(sp)
    # 3. configure.py object line
    add_configure(name)
    print(f"activated {name} (0x{addr:X}-0x{end:X}); reconfigure + compile...")
    reconfigure()
    matched, fuzzy = objdiff_score(name)
    if matched:
        print(f">>> {name} MATCHES (objdiff 100%{'' if fuzzy is None else ''}) <<<")
        print("    It's byte-identical — keep it and remove it from WIP.md!")
    else:
        print(f">>> {name} does NOT match yet (objdiff fuzzy {fuzzy}) <<<")
        print("    The DOL build will also fail at patch_dol.py (layout shift)")
        print("    until it matches — that is expected and honest.")
        print("    Iterate on src/wip/fn_XXXXXXXX.c and re-run:")
        print("      tools/ninja build/G2TE52/src/fn_XXXXXXXX.c")
        print("      build/tools/objdiff-cli report generate -o build/G2TE52/report.json")
        print("    (objdiff GUI: open objdiff.json) then `deactivate` when done.")


def cmd_deactivate(args):
    addr = norm_addr(args.addr)
    name = block_name(addr)
    sp = open(SPLITS).read()
    if not find_block(sp, name):
        print(f"not activated ({name})")
        return
    sp = remove_block(sp, name)
    open(SPLITS, "w").write(sp)
    remove_configure(name)
    srcp = f"{ROOT}/src/{name}"
    if os.path.isfile(srcp):
        os.remove(srcp)
    print(f"deactivated {name}; reconfigure + rebuild DOL...")
    reconfigure()
    ok, err = build_dol()
    if ok:
        print(">>> DOL BYTE-IDENTICAL <<<")
    else:
        print(">>> DOL DIFFERS (unexpected) <<<")
        print(err)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("list")
    a = sub.add_parser("add")
    a.add_argument("addr")
    a.add_argument("draft")
    a.add_argument("--note", default="")
    for c in ("activate", "deactivate"):
        p = sub.add_parser(c)
        p.add_argument("addr")
    args = ap.parse_args()
    {"list": cmd_list, "add": cmd_add,
     "activate": cmd_activate, "deactivate": cmd_deactivate}[args.cmd](args)


if __name__ == "__main__":
    main()
