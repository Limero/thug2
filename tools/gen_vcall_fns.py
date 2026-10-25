#!/usr/bin/env python3
"""Auto-match small vcall-style helper families across the whole DOL.

Patterns (verified against ProDG 3.7 -O2 -G0, byte-compared per function):
  a: vcall-guard     17 insns  if (o) { t=*(o+TB); t[3](o+s16(t[4]), 3); } return 1;
  b: global-count    30 insns  if (g_cnt > 1) g_cnt--; else { if (g_obj) vcall;
                               g_cnt=0; g_obj=NULL; }   (two lis-globals)
  c: global-fnptr    13 insns  g_fnptr(CONST);          (crclr cr1eq quirk, parked)
  g: vcall-dispatch 12-17 insns stwu;mflr;stw; [0-4 stfs/stw/sth to r3];
                               lwz rX,V(r3); lha r0,H(rX); lwz rX,W(rX);
                               add r3,r3,r0; mtlr rX; blrl; epilogue
                               (replaces the old hardcoded 'f' float-setter;
                               fully parameterized over frame F, store list,
                               vtable offset V and dispatch slots H/W)

IMPORTANT: patterns with branches (a, b) must be compiled ONE FUNCTION PER
FILE — GCC 2.95.2 reuses .L3-style local labels across functions in the same
translation unit, and GNU as resolves the branches to the wrong label, so a
multi-function object's branch displacements don't match the DOL. (The
gen_dispatch patterns were all straight-line, which is why single-file
batches worked there.)

KNOWN LIMITS of pattern g:
  - The dispatch register must be r9: when the DOL uses r11 for the vtable
    pointer (observed at 0x8005C038/0x8005C338, both V=0x8), no C shape tried
    reproduces it — GCC 2.95.2 always picks r9. Those functions stay parked.
  - The instruction window must be truncated at the first 'blr' before
    matching: otherwise a 15-insn function leaks the next function's stwu
    into the window and the store-count check misreads it as a 16-insn one.
"""
import os
import re
import struct
import subprocess
import sys
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DOL = f"{ROOT}/orig/G2TE52/sys/main.dol"
C_DIR = f"{ROOT}/build/compilers/ProDG/3.7"
WIBO = f"{ROOT}/build/tools/wibo"
OBJDUMP = f"{ROOT}/build/binutils/powerpc-eabi-objdump"


def load_matched():
    """Skip functions already matched (from the objdiff report, or by a
    source file already present in src/ as a fallback)."""
    rep_path = f"{ROOT}/build/G2TE52/report.json"
    matched = set()
    if os.path.isfile(rep_path):
        import json
        rep = json.load(open(rep_path))
        for u in rep.get("units", []):
            for f in u.get("functions", []):
                if f.get("matches") or f.get("fuzzy_match_percent", 0) >= 100:
                    matched.add(int(f["metadata"]["virtual_address"]))
    # Fallback: any fn_XXXXXXXX defined in an existing src/*.c is matched.
    # (Kept in sync automatically — no hardcoded address list to drift.)
    if not matched:
        import glob
        for cpath in glob.glob(f"{ROOT}/src/*.c"):
            for mo in re.finditer(r"fn_[0-9A-F]{8}", open(cpath).read()):
                matched.add(int(mo.group(0)[3:], 16))
    return matched


d = open(DOL, "rb").read()
offs = struct.unpack_from(">18I", d, 0)
addrs = struct.unpack_from(">18I", d, 0x48)
sizes = struct.unpack_from(">18I", d, 0x90)

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.detail = False
md.skipdata = True


def insns_at(start, count):
    off = offs[1] + (start - addrs[1])
    return list(md.disasm(d[off:off + count * 4], start))


def tail8(m, op, i0):
    """Epilogue for an 8-byte frame: lwz r0,0xc(r1); mtlr r0; addi r1,r1,8; blr"""
    if m[i0:i0 + 4] != ["lwz", "mtlr", "addi", "blr"]:
        return False
    return (re.fullmatch(r"r0, (?:0x)?c\(r1\)", op[i0]) and op[i0 + 1] == "r0"
            and op[i0 + 2] == "r1, r1, 8")


def is_vcall_guard(insns):
    """Pattern a: 17 insns. Returns TB."""
    if len(insns) != 17:
        return None
    m = [x.mnemonic for x in insns]
    op = [x.op_str for x in insns]
    if m[0] != "stwu" or not re.fullmatch(r"r1, -8\(r1\)", op[0]):
        return None
    if m[1] != "mflr" or op[1] != "r0":
        return None
    if m[2] != "stw" or not re.fullmatch(r"r0, (?:0x)?c\(r1\)", op[2]):
        return None
    if m[3] != "or." or op[3] != "r11, r3, r3":
        return None
    if m[4] != "beq":
        return None
    mo = re.fullmatch(r"r9, (?:0x)?([0-9a-f]+)\(r11\)", op[5])
    if m[5] != "lwz" or not mo:
        return None
    tb = int(mo.group(1), 16)
    if m[6] != "li" or op[6] != "r4, 3":
        return None
    if m[7] != "lha" or not re.fullmatch(r"r3, (?:0x)?8\(r9\)", op[7]):
        return None
    if m[8] != "lwz" or not re.fullmatch(r"r0, (?:0x)?c\(r9\)", op[8]):
        return None
    if m[9] != "add" or op[9] != "r3, r11, r3":
        return None
    if m[10] != "mtlr" or op[10] != "r0":
        return None
    if m[11] != "blrl":
        return None
    if m[12] != "li" or op[12] != "r3, 1":
        return None
    if not tail8(m, op, 13):
        return None
    return ("a", tb)


def is_global_count(insns):
    """Pattern b: 30 insns, two lis-based globals. Returns (imm, off1, off2, vtb)."""
    if len(insns) != 30:
        return None
    m = [x.mnemonic for x in insns]
    op = [x.op_str for x in insns]
    if m[0] != "stwu" or op[0] != "r1, -0x10(r1)":
        return None
    if m[1] != "mflr" or op[1] != "r0":
        return None
    if m[2] != "stmw" or op[2] != "r30, 8(r1)":
        return None
    if m[3] != "stw" or op[3] != "r0, 0x14(r1)":
        return None
    mi = re.fullmatch(r"r31, (-?(?:0x)?[0-9a-f]+)", op[4])
    if m[4] != "lis" or not mi:
        return None
    imm = int(mi.group(1), 16)
    m1 = re.fullmatch(r"r9, (-?(?:0x)?[0-9a-f]+)\(r31\)", op[5])
    if m[5] != "lwz" or not m1:
        return None
    off1 = int(m1.group(1), 16)
    if m[6] != "cmplwi" or op[6] != "r9, 1":
        return None
    if m[7] != "ble":
        return None
    if m[8] != "addi" or op[8] != "r0, r9, -1":
        return None
    m9 = re.fullmatch(r"r0, (-?(?:0x)?[0-9a-f]+)\(r31\)", op[9])
    if m[9] != "stw" or not m9 or int(m9.group(1), 16) != off1:
        return None
    if m[10] != "b":
        return None
    if m[11] != "lis":
        return None
    m2 = re.fullmatch(r"r11, (-?(?:0x)?[0-9a-f]+)\(r30\)", op[12])
    if m[12] != "lwz" or not m2:
        return None
    off2 = int(m2.group(1), 16)
    if m[13] != "cmpwi" or op[13] != "r11, 0":
        return None
    if m[14] != "beq":
        return None
    mv = re.fullmatch(r"r9, (?:0x)?([0-9a-f]+)\(r11\)", op[15])
    if m[15] != "lwz" or not mv:
        return None
    vtb = int(mv.group(1), 16)
    if m[16] != "li" or op[16] != "r4, 3":
        return None
    if m[17] != "lha" or not re.fullmatch(r"r3, (?:0x)?8\(r9\)", op[17]):
        return None
    if m[18] != "lwz" or not re.fullmatch(r"r0, (?:0x)?c\(r9\)", op[18]):
        return None
    if m[19] != "add" or op[19] != "r3, r11, r3":
        return None
    if m[20] != "mtlr" or op[20] != "r0":
        return None
    if m[21] != "blrl":
        return None
    if m[22] != "li" or op[22] != "r0, 0":
        return None
    m23 = re.fullmatch(r"r0, (-?(?:0x)?[0-9a-f]+)\(r31\)", op[23])
    if m[23] != "stw" or not m23 or int(m23.group(1), 16) != off1:
        return None
    m24 = re.fullmatch(r"r0, (-?(?:0x)?[0-9a-f]+)\(r30\)", op[24])
    if m[24] != "stw" or not m24 or int(m24.group(1), 16) != off2:
        return None
    if m[25] != "lwz" or op[25] != "r0, 0x14(r1)":
        return None
    if m[26] != "mtlr" or op[26] != "r0":
        return None
    if m[27] != "lmw" or op[27] != "r30, 8(r1)":
        return None
    if m[28] != "addi" or op[28] != "r1, r1, 0x10":
        return None
    if m[29] != "blr":
        return None
    return ("b", imm, off1, off2, vtb)


def is_global_call(insns):
    """Pattern c: 13 insns, call through global fnptr with const arg."""
    if len(insns) != 13:
        return None
    m = [x.mnemonic for x in insns]
    op = [x.op_str for x in insns]
    if m[0] != "stwu" or not re.fullmatch(r"r1, -8\(r1\)", op[0]):
        return None
    if m[1] != "mflr" or op[1] != "r0":
        return None
    if m[2] != "stw" or not re.fullmatch(r"r0, (?:0x)?c\(r1\)", op[2]):
        return None
    mi = re.fullmatch(r"r9, (-?(?:0x)?[0-9a-f]+)", op[3])
    if m[3] != "lis" or not mi:
        return None
    imm = int(mi.group(1), 16)
    mc = re.fullmatch(r"r4, (-?(?:0x)?[0-9a-f]+)", op[4])
    if m[4] != "li" or not mc:
        return None
    const = int(mc.group(1), 16)
    mo = re.fullmatch(r"r0, (-?(?:0x)?[0-9a-f]+)\(r9\)", op[5])
    if m[5] != "lwz" or not mo:
        return None
    fpo = int(mo.group(1), 16)
    if m[6] != "mtlr" or op[6] != "r0":
        return None
    if m[7] != "crclr" or op[7] != "cr1eq":
        return None
    if m[8] != "blrl":
        return None
    if not tail8(m, op, 9):
        return None
    return ("c", imm, fpo, const)


def truncate_at_blr(insns):
    """Cut an instruction list at the first plain 'blr' (function end).
    Prevents over-read when the disasm window leaks into the next function
    (which used to break the store-count for 15-insn setters)."""
    m = [x.mnemonic for x in insns]
    try:
        e = m.index('blr')
        return insns[:e + 1]
    except ValueError:
        return insns


def is_vcall_store(insns):
    """Pattern g (generalized float/word/short setter + dispatch):
    stwu r1,-F(r1); mflr r0; stw r0,F+4(r1); [0-4 stores to r3];
    lwz rX,V(r3); lha r0,H(rX); lwz rX,W(rX); add r3,r3,r0;
    mtlr rX; blrl; lwz r0,F+4(r1); mtlr r0; addi r1,r1,F; blr
    Returns (F, stores, V, H, W, n) with stores=[(mnem, reg, off), ...].
    The dispatch register rX is captured but not enforced (register choice
    is checked empirically by the byte-compare)."""
    m = [x.mnemonic for x in insns]
    op = [x.op_str for x in insns]
    n = len(insns)
    if n < 12:
        return None
    fm = re.fullmatch(r"r1, -(?:0x)?([0-9a-f]+)\(r1\)", op[0])
    if m[0] != "stwu" or not fm:
        return None
    F = int(fm.group(1), 16)
    if F not in (8, 16):
        return None
    if m[1] != "mflr" or op[1] != "r0":
        return None
    sm = re.fullmatch(r"r0, (?:0x)?([0-9a-f]+)\(r1\)", op[2])
    if m[2] != "stw" or not sm or int(sm.group(1), 16) != F + 4:
        return None
    k = 3
    stores = []
    while k < n and m[k] in ("stfs", "stw", "sth"):
        mo = re.fullmatch(r"(f\d+|r\d+), (?:0x)?([0-9a-f]+)\(r3\)", op[k])
        if not mo:
            return None
        stores.append((m[k], mo.group(1), int(mo.group(2), 16)))
        k += 1
    if k >= n:
        return None
    mo = re.fullmatch(r"r(\d+), (?:0x)?([0-9a-f]+)\(r3\)", op[k])
    if m[k] != "lwz" or not mo:
        return None
    reg = int(mo.group(1))
    V = int(mo.group(2), 16)
    if m[k + 1] != "lha":
        return None
    ho = re.fullmatch(r"r0, (?:0x)?([0-9a-f]+)\(r%d\)" % reg, op[k + 1])
    if not ho:
        return None
    H = int(ho.group(1), 16)
    if m[k + 2] != "lwz":
        return None
    wo = re.fullmatch(r"r%d, (?:0x)?([0-9a-f]+)\(r%d\)" % (reg, reg), op[k + 2])
    if not wo:
        return None
    W = int(wo.group(1), 16)
    if m[k + 3] != "add" or op[k + 3] != "r3, r3, r0":
        return None
    if m[k + 4] != "mtlr" or op[k + 4] != "r%d" % reg:
        return None
    if m[k + 5] != "blrl":
        return None
    if m[k + 6:k + 10] != ["lwz", "mtlr", "addi", "blr"]:
        return None
    sm = re.fullmatch(r"r0, (?:0x)?([0-9a-f]+)\(r1\)", op[k + 6])
    if not sm or int(sm.group(1), 16) != F + 4:
        return None
    if op[k + 7] != "r0":
        return None
    if op[k + 8] != "r1, r1, %d" % F:
        return None
    return (F, tuple(stores), V, H, W, n)


# ---- scan ----
MATCHED = load_matched()
print(f"skipping {len(MATCHED)} already-matched functions")
fns = []
i = addrs[1]
text_end = addrs[1] + sizes[1]
while i < text_end:
    if i in MATCHED:
        i += 4
        continue
    r = is_vcall_store(truncate_at_blr(insns_at(i, 24)))
    if r:
        fns.append((i, "g", r))
        i += r[5] * 4
        continue
    r = is_vcall_guard(insns_at(i, 17))
    if r:
        fns.append((i, r[0], r[1]))
        i += 17 * 4
        continue
    r = is_global_count(insns_at(i, 30))
    if r:
        fns.append((i, r[0], r[1:]))
        i += 30 * 4
        continue
    r = is_global_call(insns_at(i, 13))
    if r:
        fns.append((i, r[0], r[1:]))
        i += 13 * 4
        continue
    i += 4

print(f"pattern functions found: {len(fns)}")
for a, k, p in fns:
    print(f"  0x{a:08X} {k} {p}")


# ---- C generation (one function per file) ----
def base_from_lis(imm):
    return (imm << 16) & 0xFFFFFFFF


def gen_one(addr, kind, p, seen_ext=None):
    """Return list of C lines for a single function (externs included)."""
    seen_ext = set() if seen_ext is None else seen_ext
    lines = []
    if kind == 'a':
        tb = p
        lines.append(f"s32 fn_{addr:08X}(void *o) {{")
        lines.append("    if (o) {")
        lines.append(f"        void **t = *(void ***)((char *)o + 0x{tb:X});")
        lines.append("        void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];")
        lines.append("        fp((char *)o + (signed short)((s16 *)t)[4], 3);")
        lines.append("    }")
        lines.append("    return 1;")
        lines.append("}")
    elif kind == 'b':
        imm, off1, off2, vtb = p
        a1 = (base_from_lis(imm) + off1) & 0xFFFFFFFF
        a2 = (base_from_lis(imm) + off2) & 0xFFFFFFFF
        for g in (a1, a2):
            if g not in seen_ext:
                seen_ext.add(g)
                lines.append(f"extern u32 lbl_{g:08X};")
        lines.append(f"void fn_{addr:08X}(void) {{")
        lines.append(f"    if (lbl_{a1:08X} > 1) {{")
        lines.append(f"        lbl_{a1:08X}--;")
        lines.append("    } else {")
        lines.append(f"        if (lbl_{a2:08X}) {{")
        lines.append(f"            void **t = *(void ***)((char *)lbl_{a2:08X} + 0x{vtb:X});")
        lines.append("            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];")
        lines.append(f"            fp((char *)lbl_{a2:08X} + (signed short)((s16 *)t)[4], 3);")
        lines.append("        }")
        # Store obj NULL FIRST, count SECOND: GCC 2.95.2 then emits the
        # count store (r31) before the obj store (r30), matching the DOL.
        lines.append(f"        lbl_{a2:08X} = NULL;")
        lines.append(f"        lbl_{a1:08X} = 0;")
        lines.append("    }")
        lines.append("}")
    elif kind == 'c':
        imm, fpo, const = p
        g = (base_from_lis(imm) + fpo) & 0xFFFFFFFF
        if g not in seen_ext:
            seen_ext.add(g)
            lines.append(f"extern void (*lbl_{g:08X})(s32);")
        lines.append(f"void fn_{addr:08X}(void) {{")
        lines.append(f"    lbl_{g:08X}({const});")
        lines.append("}")
    elif kind == 'g':
        F, stores, V, H, W, n = p
        argtypes = []
        for (mnem, reg, off) in stores:
            if mnem == 'stfs':
                argtypes.append('float')
            elif mnem == 'stw':
                argtypes.append('s32')
            else:  # sth
                argtypes.append('s16')
        argdecl = ", ".join("%s a%d" % (t, i) for i, t in enumerate(argtypes))
        head = "void fn_%08X(void *o%s)" % (addr, (", " + argdecl) if argdecl else "")
        lines.append(head + " {")
        lines.append("    void **t;")
        lines.append("    void (*fp)(void *);")
        for i, (mnem, reg, off) in enumerate(stores):
            ct = {'stfs': 'float', 'stw': 's32', 'sth': 's16'}[mnem]
            lines.append("    *(%s *)((char *)o + 0x%X) = a%d;" % (ct, off, i))
        lines.append("    t = *(void ***)((char *)o + 0x%X);" % V)
        lines.append("    fp = (void (*)(void *))t[0x%X / 4];" % W)
        lines.append("    fp((char *)o + (signed short)((s16 *)t)[0x%X / 2]);" % H)
        lines.append("}")
    lines.append("")
    return lines


size_of = {'a': 17, 'b': 30, 'c': 13}


def fn_size(kind, p):
    if kind == 'g':
        return p[5]  # instruction count (caller multiplies by 4)
    return size_of[kind] if kind in size_of else 13 + len(p)


# ---- compile each function separately, relocation-masked byte-compare ----
from elftools.elf.elffile import ELFFile

# PowerPC ELF relocation types
R_PPC_ADDR16_LO = 4
R_PPC_ADDR16_HA = 6
R_PPC_REL14 = 11
R_PPC_REL24 = 10


def reloc_masks(objp):
    """Return {insn_offset: 32-bit mask} for each relocated instruction, where
    the mask zeroes out the bytes the linker will overwrite (branch
    displacement field for REL14/REL24, 16-bit immediate for ADDR16_*).
    SN's assembler places ADDR16 relocations at field offset (insn+2); the
    masks are computed per instruction, so we tolerate that."""
    masks = {}
    with open(objp, "rb") as f:
        elf = ELFFile(f)
        relsec = elf.get_section_by_name(".rela.text")
        if relsec is None:
            relsec = elf.get_section_by_name(".rel.text")
        if relsec is None:
            return masks
        for rel in relsec.iter_relocations():
            p = rel["r_offset"]
            typ = rel["r_info_type"]
            if typ in (R_PPC_REL14, R_PPC_REL24):
                # branch: LI field bits 16-29 are linker-written
                insn = p & ~3
                masks[insn] = masks.get(insn, 0xFFFFFFFF) & 0xFFFF0003
            elif typ in (R_PPC_ADDR16_LO, R_PPC_ADDR16_HA):
                # d-form 16-bit immediate: bytes 2-3 of the instruction
                insn = (p - 2) & ~3
                masks[insn] = masks.get(insn, 0xFFFFFFFF) & 0xFFFF0000
    return masks


def masked_text(objp, size):
    """Return (bytes, masks) for the first `size` bytes of .text."""
    with open(objp, "rb") as f:
        elf = ELFFile(f)
        text = elf.get_section_by_name(".text")
        data = text.data()[:size]
    return data, reloc_masks(objp)


os.makedirs("/tmp/vcall", exist_ok=True)
env = dict(os.environ)
env["SN_NGC_PATH"] = C_DIR

exact = []  # structurally identical (masked compare)
near = []
for addr, kind, p in fns:
    fname = f"fn_{addr:08X}"
    srcp = f"/tmp/vcall/{fname}.c"
    objp = f"/tmp/vcall/{fname}.o"
    with open(srcp, "w") as f:
        f.write('#include "types.h"\n' + "\n".join(gen_one(addr, kind, p)))
    r = subprocess.run(
        [WIBO, f"{C_DIR}/ngccc.exe", "-O2", "-G0", "-mcpu=750", "-fno-common",
         "-I", f"{ROOT}/include", "-c", srcp, "-o", objp],
        cwd=ROOT, capture_output=True, text=True, env=env)
    if r.returncode != 0:
        print(f"COMPILE FAIL {fname}: {r.stderr[:300]}")
        continue
    size = fn_size(kind, p) * 4
    oo = offs[1] + (addr - addrs[1])
    orig_bytes = d[oo:oo + size]
    got, masks = masked_text(objp, size)
    if len(got) != size:
        near.append((addr, kind, p, abs(len(got) - size) + 999))
        continue
    match = True
    ndiff = 0
    for i in range(0, size, 4):
        ow = int.from_bytes(orig_bytes[i:i + 4], "big")
        gw = int.from_bytes(got[i:i + 4], "big")
        mask = masks.get(i, 0xFFFFFFFF)
        if (ow & mask) != (gw & mask):
            match = False
            for b in range(4):
                if orig_bytes[i + b] != got[i + b]:
                    ndiff += 1
    if match:
        exact.append((addr, kind, p))
    else:
        near.append((addr, kind, p, ndiff))

print(f"\n=== EXACT: {len(exact)} ===")
for a, k, p in exact:
    print(f"  0x{a:08X} {k} {p}")
print(f"\n=== NEAR (diff bytes): {len(near)} ===")
for a, k, p, nd in sorted(near, key=lambda t: t[3]):
    print(f"  0x{a:08X} {k} {p} diff={nd}")

# ---- write one src file per exact function (dtk build = one object each) ----
if exact:
    outp = f"{ROOT}/src/vcall.c"
    with open(outp, "w") as f:
        f.write('#include "types.h"\n'
                + "\n".join(ln for a, k, p in exact for ln in gen_one(a, k, p)))
    print(f"\nwrote {outp} with {len(exact)} functions (reference-only, not built)")

    print("\nSPLIT RANGES:")
    for a, k, p in sorted(exact, key=lambda t: t[0]):
        s = a
        e = a + fn_size(k, p) * 4
        print(f"\t.text       start:0x{s:X} end:0x{e:X}")

    for a, k, p in sorted(exact, key=lambda t: t[0]):
        fname = f"vcall_{a:08X}.c"
        with open(f"{ROOT}/src/{fname}", "w") as f:
            f.write("// Auto-generated from tools/gen_vcall_fns.py\n"
                    + f"// range 0x{a:X}-0x{a + fn_size(k, p) * 4:X} (1 function). Byte-identical.\n"
                    + '#include "types.h"\n'
                    + "\n".join(gen_one(a, k, p)))
    print(f"wrote {len(exact)} per-function files in src/")
