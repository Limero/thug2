#!/usr/bin/env python3
"""Simulate mwld SDA linking for a wip draft object and compare vs DOL bytes.
Usage: python3 /tmp/op/sda_verify.py 0xADDR src/wip/fn_XXXXXXXX.c [-msdata=eabi -G4]
Compiles the draft (extra flags allowed), resolves R_PPC_EMB_SDA21-type relocs
as (sym_vaddr - 0x803D2280), patches .text, compares against orig DOL bytes.
"""
import struct, subprocess, sys, os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from elftools.elf.elffile import ELFFile

ADDR = int(sys.argv[1], 16)
SRC = sys.argv[2]
FLAGS = sys.argv[3:] or ["-msdata=eabi", "-G4"]
SDA_BASE = 0x803D2280

text = open(SRC).read()
body = "\n".join(l for l in text.splitlines() if not l.startswith("//") and "types.h" not in l)
fname = f"fn_{ADDR:08X}"
sp, op = f"/tmp/leaf/{fname}_v.c", f"/tmp/leaf/{fname}_v.o"
os.makedirs("/tmp/leaf", exist_ok=True)
with open(sp, "w") as f:
    f.write('#include "types.h"\n' + body)
env = dict(os.environ); env["SN_NGC_PATH"] = gl.C_DIR
flags = ["-O2", "-G0", "-mcpu=750", "-fno-common", "-I", f"{gl.ROOT}/include"] + FLAGS
r = subprocess.run([gl.WIBO, f"{gl.C_DIR}/ngccc.exe"] + flags + ["-c", sp, "-o", op],
                   cwd=gl.ROOT, capture_output=True, text=True, env=env)
if r.returncode != 0:
    print("COMPILE FAIL:", r.stderr[:400]); sys.exit(1)

# The ngccc ninja rule retargets object-private FP constant pools to the DOL's
# lbl_* symbols via tools/fix_fp_pool.py (configure.py wires it into the rule).
# Mirror that step here so this verifier scores exactly what the build links;
# without it, any draft whose only residual is a resolvable pool site is
# unfairly refused by tools/promote_wip.py's gate.
subprocess.run([sys.executable, f"{gl.ROOT}/tools/fix_fp_pool.py", op],
               cwd=gl.ROOT, capture_output=True, text=True)

with open(op, "rb") as f:
    e = ELFFile(f)
    sec = e.get_section_by_name(".text"); got = bytearray(sec.data())
    symtab = e.get_section_by_name(".symtab")
    syms = {i: (s.name, s["st_value"], s["st_shndx"]) for i, s in enumerate(symtab.iter_symbols())}
    rels = []
    for rs in e.iter_sections():
        if rs.header.sh_type == "SHT_RELA":
            for rel in rs.iter_relocations():
                rels.append((rel["r_offset"], rel["r_info_type"], rel["r_info_sym"], rel["r_addend"]))
    # section vaddrs for addend-less local syms
    shndx_va = {}
    for i, s in enumerate(e.iter_sections()):
        shndx_va[i] = s.header.sh_addr

# resolve each reloc: we expect SDA-typed relocs whose disp = target - SDA_BASE
# figure out target vaddr per symbol: named lbl_XXXXXXXX -> parse addr from name;
# section symbols -> sh_addr + addend
for off, typ, symi, addend in rels:
    if typ in (10, 11):  # REL24/REL14: mask displacement like gen_leaves
        continue
    name, va, shndx = syms[symi]
    if name.startswith("lbl_"):
        target = int(name[4:], 16)
    elif name == "":
        target = shndx_va.get(shndx, 0) + addend
    else:
        print(f"UNRESOLVED reloc @{off:x} type={typ} sym={name}"); continue
    old = int.from_bytes(got[off:off+4], "big")
    if typ == 109:  # SDA21: linker rewrites BOTH disp AND rA (bits 16-20) to r13
        # The RELA addend holds the symbol-relative offset (e.g. +12 for
        # `((s32 *)&arr)[3]`); the assembler leaves the instruction's D-form
        # displacement at 0, so it MUST be folded in here or every array-member
        # access false-mismatches by the member offset (fixed 2026-10-09).
        disp = (target + addend - SDA_BASE) & 0xFFFF
        got[off:off+4] = ((old & 0xFFE00000) | (13 << 16) | disp).to_bytes(4, "big")
        print(f"reloc @{off:x} type={typ} {name}+{addend}->0x{target + addend:X} disp={disp:#06x} rA:=r13")
    elif typ in (4, 6):  # ADDR16_LO/HI: reloc offset points at the immediate
        # halfword (instruction_start + 2); patch the enclosing instruction word.
        word_off = off - 2
        old = int.from_bytes(got[word_off:word_off+4], "big")
        if typ == 6:  # ADDR16_HI (lis): mwld applies the +0x8000 HA adjustment
            val = ((target + addend + 0x8000) >> 16) & 0xFFFF
            label = "hi"
        else:  # ADDR16_LO (addi/ori): low 16 bits as-is
            val = (target + addend) & 0xFFFF
            label = "lo"
        got[word_off:word_off+4] = ((old & 0xFFFF0000) | val).to_bytes(4, "big")
        print(f"reloc @{off:x} type={typ} {name}->0x{target:X} {label}={val:#06x}")
    else:
        print(f"UNHANDLED reloc @{off:x} type={typ} sym={name}"); continue

dol = open(f"{gl.ROOT}/orig/G2TE52/sys/main.dol", "rb").read()
# text section mapping: file offset = t_off + (vaddr - t_addr); reuse gl table
base = gl.t_off + (ADDR - gl.t_addr)
want = bytearray(dol[base:base+len(got)])
# mask branch displacements exactly like gen_leaves.compile_fn
for off, typ, symi, addend in rels:
    if typ == 10:
        m = bytes.fromhex("FC000003")
    elif typ == 11:
        m = bytes.fromhex("FFFF0003")
    else:
        continue
    got[off:off+4] = bytes(a & b for a, b in zip(got[off:off+4], m))
    want[off:off+4] = bytes(a & b for a, b in zip(want[off:off+4], m))
if bytes(got) == want:
    print(f"LINK-SIM EXACT: {len(got)} bytes match DOL @ {ADDR:#x}")
else:
    for i in range(0, min(len(got), len(want)), 4):
        w = int.from_bytes(want[i:i+4], "big"); g = int.from_bytes(got[i:i+4], "big")
        if w != g:
            print(f"DIFF {i:04X}: want {w:08X} got {g:08X}")
    print(f"MISMATCH ({sum(1 for i in range(0,min(len(got),len(want)),4) if int.from_bytes(want[i:i+4],'big')!=int.from_bytes(got[i:i+4],'big'))} words)")
