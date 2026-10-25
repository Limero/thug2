#!/usr/bin/env python3
"""Batch variant tester: compile each C file (arg) against one DOL function.

usage: vtest.py <addr> <insns> <cfile> [<cfile> ...] [--flags "-O1 ..."]

Each C file is compiled standalone with ngccc (default -O2 -G0) and masked
byte-compared. Prints one line per variant: MATCH or DIFF(n) or SIZE.
"""
import os
import re
import struct
import subprocess
import sys
from elftools.elf.elffile import ELFFile

EXTRA_FLAGS = []
for a in list(sys.argv):
    if a.startswith("--flags="):
        EXTRA_FLAGS = a.split("=", 1)[1].split()
        sys.argv.remove(a)
    elif a == "--flags":
        i = sys.argv.index(a)
        EXTRA_FLAGS = sys.argv[i + 1].split()
        del sys.argv[i:i + 2]
        break

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DOL = f"{ROOT}/orig/G2TE52/sys/main.dol"
C_DIR = f"{ROOT}/build/compilers/ProDG/3.7"
WIBO = f"{ROOT}/build/tools/wibo"

addr = int(sys.argv[1], 16)
nins = int(sys.argv[2])
cfiles = sys.argv[3:]
if not cfiles:
    print("usage: vtest.py <addr> <insns> <cfile> [...]")
    sys.exit(1)

d = open(DOL, "rb").read()
offs = struct.unpack_from(">18I", d, 0)
addrs = struct.unpack_from(">18I", d, 0x48)
oo = offs[1] + (addr - addrs[1])
orig = d[oo:oo + nins * 4]

env = dict(os.environ)
env["SN_NGC_PATH"] = C_DIR

R_PPC_ADDR16_LO, R_PPC_ADDR16_HA, R_PPC_REL14, R_PPC_REL24 = 4, 6, 11, 10

for cp in cfiles:
    name = os.path.basename(cp).replace(".c", "")
    op = f"/tmp/vt_{name}.o"
    with open(cp) as f:
        src = f.read()
    sp = f"/tmp/vt_{name}.c"
    with open(sp, "w") as f:
        f.write('#include "types.h"\n' + src)
    r = subprocess.run(
        [WIBO, f"{C_DIR}/ngccc.exe"] + EXTRA_FLAGS + ["-G0", "-mcpu=750", "-fno-common",
         "-I", f"{ROOT}/include", "-c", sp, "-o", op],
        cwd=ROOT, capture_output=True, text=True, env=env)
    if r.returncode != 0:
        print(f"{name}: COMPILE FAIL {r.stderr[:200]}")
        continue
    masks = {}
    with open(op, "rb") as f:
        elf = ELFFile(f)
        relsec = elf.get_section_by_name(".rela.text") or elf.get_section_by_name(".rel.text")
        if relsec:
            for rel in relsec.iter_relocations():
                p = rel["r_offset"]
                typ = rel["r_info_type"]
                if typ in (R_PPC_REL14, R_PPC_REL24):
                    insn = p & ~3
                    masks[insn] = masks.get(insn, 0xFFFFFFFF) & 0xFFFF0003
                elif typ in (R_PPC_ADDR16_LO, R_PPC_ADDR16_HA):
                    insn = (p - 2) & ~3
                    masks[insn] = masks.get(insn, 0xFFFFFFFF) & 0xFFFF0000
    with open(op, "rb") as f:
        got = ELFFile(f).get_section_by_name(".text").data()
    if len(got) < len(orig):
        print(f"{name}: SIZE got={len(got)} want={len(orig)}")
        continue
    diffs = 0
    for i in range(0, len(orig), 4):
        ow = int.from_bytes(orig[i:i + 4], "big")
        gw = int.from_bytes(got[i:i + 4], "big")
        if (ow & masks.get(i, 0xFFFFFFFF)) != (gw & masks.get(i, 0xFFFFFFFF)):
            diffs += 1
    if diffs == 0:
        print(f"{name}: MATCH")
    else:
        print(f"{name}: DIFF({diffs})")
