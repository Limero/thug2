#!/usr/bin/env python3
"""Auto-match small GPR-only indirect-call patterns across the whole DOL.

Patterns (all verified byte-identical with ProDG 3.7 -O2 -G0):
  d: table-dispatch      (13 insns) t=*(o+BASE); fp(t[off+4]); fp(o+t[off/2] as s16)
  f: field-fnptr call    (11 insns) fp=*(o+OFF); fp(o)
  s: store+dispatch      (14 insns) *(o+STORE)=arg; then 'd' with BASE/OFF
  l: li+dispatch         (14 insns) fp(o+off, CONST)

Generates src/gen_dispatch_XXX.c (one per contiguous range) plus writes the
master src/gen_dispatch.c, byte-compares every function against the DOL, and
prints split ranges.
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
    """Load already-matched function addresses from the objdiff report so
    re-runs skip them (instead of a hardcoded set that drifts)."""
    rep_path = f"{ROOT}/build/G2TE52/report.json"
    matched = set()
    if os.path.isfile(rep_path):
        import json
        rep = json.load(open(rep_path))
        for u in rep.get("units", []):
            for f in u.get("functions", []):
                if f.get("matches") or f.get("fuzzy_match_percent", 0) >= 100:
                    matched.add(int(f["metadata"]["virtual_address"]))
    # Hardcoded fallback (report missing): the 10 hand-written matches.
    if not matched:
        matched = {
            0x800034A0, 0x800034E4, 0x8000353C,
            0x8000B680,
            0x8013F734, 0x8013F74C, 0x8013F764,
            0x8005C2F8,
            0x800575DC,
            0x8005F28C,
        }
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


def tail_ok(insns, m, op, i0):
    """Check the standard epilogue for an 8-byte frame:
       lwz r0, 0xc(r1); mtlr r0; addi r1, r1, 8; blr"""
    k = i0
    if m[k] != "lwz" or op[k] != "r0, 0xc(r1)":
        return False
    if m[k + 1] != "mtlr" or op[k + 1] != "r0":
        return False
    if m[k + 2] != "addi" or op[k + 2] != "r1, r1, 8":
        return False
    if m[k + 3] != "blr":
        return False
    return True


def is_dispatch(insns):
    """Pattern d: table-dispatch. Returns (BASE, OFF)."""
    if len(insns) != 13:
        return None
    m = [x.mnemonic for x in insns]
    op = [x.op_str for x in insns]
    if m[0] != "stwu" or not re.fullmatch(r"r1, -8\(r1\)", op[0]):
        return None
    if m[1] != "mflr" or op[1] != "r0":
        return None
    if m[2] != "stw" or op[2] != "r0, 0xc(r1)":
        return None
    mo = re.fullmatch(r"r9, (?:0x)?([0-9a-f]+)\(r3\)", op[3])
    if m[3] != "lwz" or not mo:
        return None
    base = int(mo.group(1), 16)
    mo2 = re.fullmatch(r"r0, (?:0x)?([0-9a-f]+)\(r9\)", op[4])
    if m[4] != "lha" or not mo2:
        return None
    off = int(mo2.group(1), 16)
    mo3 = re.fullmatch(r"r9, (?:0x)?([0-9a-f]+)\(r9\)", op[5])
    if m[5] != "lwz" or not mo3 or int(mo3.group(1), 16) != off + 4:
        return None
    if m[6] != "add" or op[6] != "r3, r3, r0":
        return None
    if m[7] != "mtlr" or op[7] != "r9":
        return None
    if m[8] != "blrl":
        return None
    if not tail_ok(insns, m, op, 9):
        return None
    return (base, off)


def is_fpcall(insns):
    """Pattern f: field-fnptr call. Returns OFF."""
    if len(insns) != 11:
        return None
    m = [x.mnemonic for x in insns]
    op = [x.op_str for x in insns]
    if m[0] != "stwu" or not re.fullmatch(r"r1, -8\(r1\)", op[0]):
        return None
    if m[1] != "mflr" or op[1] != "r0":
        return None
    if m[2] != "stw" or op[2] != "r0, 0xc(r1)":
        return None
    if m[3] != "mr" or op[3] != "r9, r3":
        return None
    mo = re.fullmatch(r"r0, (?:0x)?([0-9a-f]+)\(r9\)", op[4])
    if m[4] != "lwz" or not mo:
        return None
    off = int(mo.group(1), 16)
    if m[5] != "mtlr" or op[5] != "r0":
        return None
    if m[6] != "blrl":
        return None
    if not tail_ok(insns, m, op, 7):
        return None
    return off


def is_setdispatch(insns):
    """Pattern s: store arg + dispatch. Returns (STORE, BASE, OFF)."""
    if len(insns) != 14:
        return None
    m = [x.mnemonic for x in insns]
    op = [x.op_str for x in insns]
    if m[0] != "stwu" or not re.fullmatch(r"r1, -8\(r1\)", op[0]):
        return None
    if m[1] != "mflr" or op[1] != "r0":
        return None
    if m[2] != "stw" or op[2] != "r0, 0xc(r1)":
        return None
    ms = re.fullmatch(r"r4, (?:0x)?([0-9a-f]+)\(r3\)", op[3])
    if m[3] != "stw" or not ms:
        return None
    store = int(ms.group(1), 16)
    mo = re.fullmatch(r"r9, (?:0x)?([0-9a-f]+)\(r3\)", op[4])
    if m[4] != "lwz" or not mo:
        return None
    base = int(mo.group(1), 16)
    mo2 = re.fullmatch(r"r0, (?:0x)?([0-9a-f]+)\(r9\)", op[5])
    if m[5] != "lha" or not mo2:
        return None
    off = int(mo2.group(1), 16)
    mo3 = re.fullmatch(r"r9, (?:0x)?([0-9a-f]+)\(r9\)", op[6])
    if m[6] != "lwz" or not mo3 or int(mo3.group(1), 16) != off + 4:
        return None
    if m[7] != "add" or op[7] != "r3, r3, r0":
        return None
    if m[8] != "mtlr" or op[8] != "r9":
        return None
    if m[9] != "blrl":
        return None
    if not tail_ok(insns, m, op, 10):
        return None
    return (store, base, off)


def is_li_dispatch(insns):
    """Pattern l: dispatch with const arg. Returns (BASE, OFF, CONST)."""
    if len(insns) != 14:
        return None
    m = [x.mnemonic for x in insns]
    op = [x.op_str for x in insns]
    if m[0] != "stwu" or not re.fullmatch(r"r1, -8\(r1\)", op[0]):
        return None
    if m[1] != "mflr" or op[1] != "r0":
        return None
    if m[2] != "stw" or op[2] != "r0, 0xc(r1)":
        return None
    mo = re.fullmatch(r"r9, (?:0x)?([0-9a-f]+)\(r3\)", op[3])
    if m[3] != "lwz" or not mo:
        return None
    base = int(mo.group(1), 16)
    mc = re.fullmatch(r"r4, (-?0x[0-9a-f]+|-?[0-9]+)", op[4])
    if m[4] != "li" or not mc:
        return None
    const = int(mc.group(1), 0)
    mo2 = re.fullmatch(r"r0, (?:0x)?([0-9a-f]+)\(r9\)", op[5])
    if m[5] != "lha" or not mo2:
        return None
    off = int(mo2.group(1), 16)
    mo3 = re.fullmatch(r"r9, (?:0x)?([0-9a-f]+)\(r9\)", op[6])
    if m[6] != "lwz" or not mo3 or int(mo3.group(1), 16) != off + 4:
        return None
    if m[7] != "add" or op[7] != "r3, r3, r0":
        return None
    if m[8] != "mtlr" or op[8] != "r9":
        return None
    if m[9] != "blrl":
        return None
    if not tail_ok(insns, m, op, 10):
        return None
    return (base, off, const)


# ---- scan ----
MATCHED = load_matched()
print(f"skipping {len(MATCHED)} already-matched functions")
fns = []  # (addr, kind, base, off, extra)
i = addrs[1]
text_end = addrs[1] + sizes[1]
while i < text_end:
    if i in MATCHED:
        i += 4
        continue
    head = insns_at(i, 14)
    if not head or head[0].address != i:
        i += 4
        continue
    r = is_dispatch(insns_at(i, 13))
    if r:
        fns.append((i, 'd', r[0], r[1], 0))
        i += 13 * 4
        continue
    r = is_fpcall(insns_at(i, 11))
    if r:
        fns.append((i, 'f', 0, r, 0))
        i += 11 * 4
        continue
    r = is_setdispatch(head)
    if r:
        fns.append((i, 's', r[1], r[2], r[0]))  # base, off, store
        i += 14 * 4
        continue
    r = is_li_dispatch(head)
    if r:
        fns.append((i, 'l', r[0], r[1], r[2]))
        i += 14 * 4
        continue
    i += 4

print(f"pattern functions found: {len(fns)}")
for a, k, b, o, x in fns:
    print(f"  0x{a:08X} {k} base=0x{b:X} off=0x{o:X} extra=0x{x:X}")

# ---- generate C ----
def gen_c(fns):
    lines = [
        "// Auto-generated from tools/gen_dispatch_fns.py",
        "// (table-dispatch / field-fnptr / set-dispatch / const-dispatch helpers).",
        '#include "types.h"',
        "",
    ]
    for addr, kind, base, off, extra in fns:
        if kind == 'd':
            lines.append(f"void fn_{addr:08X}(void *o) {{ /* d base=0x{base:X} off=0x{off:X} */")
            lines.append(f"    void **t = *(void ***)((char *)o + 0x{base:X});")
            lines.append(f"    void (*fp)(void *) = (void (*)(void *))t[0x{(off + 4) >> 2:x}];")
            lines.append(f"    fp((char *)o + (signed short)((s16 *)t)[0x{off >> 1:x}]);")
        elif kind == 'f':
            lines.append(f"void fn_{addr:08X}(void *o) {{ /* f off=0x{off:X} */")
            lines.append(f"    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x{off:X});")
            lines.append(f"    fp(o);")
        elif kind == 's':
            lines.append(f"void fn_{addr:08X}(void *o, u32 v) {{ /* s store=0x{extra:X} base=0x{base:X} off=0x{off:X} */")
            lines.append(f"    void **t;")
            lines.append(f"    void (*fp)(void *);")
            lines.append(f"    *(u32 *)((char *)o + 0x{extra:X}) = v;")
            lines.append(f"    t = *(void ***)((char *)o + 0x{base:X});")
            lines.append(f"    fp = (void (*)(void *))t[0x{(off + 4) >> 2:x}];")
            lines.append(f"    fp((char *)o + (signed short)((s16 *)t)[0x{off >> 1:x}]);")
        elif kind == 'l':
            lines.append(f"void fn_{addr:08X}(void *o) {{ /* l base=0x{base:X} off=0x{off:X} const={extra} */")
            lines.append(f"    void **t = *(void ***)((char *)o + 0x{base:X});")
            lines.append(f"    void (*fp)(void *, int) = (void (*)(void *, int))t[0x{(off + 4) >> 2:x}];")
            lines.append(f"    fp((char *)o + (signed short)((s16 *)t)[0x{off >> 1:x}], {extra});")
        lines.append("}")
        lines.append("")
    return "\n".join(lines)


src = gen_c(fns)
os.makedirs("/tmp/gendisp", exist_ok=True)
srcp = "/tmp/gendisp/gen.c"
objp = "/tmp/gendisp/gen.o"
with open(srcp, "w") as f:
    f.write(src)
env = dict(os.environ)
env["SN_NGC_PATH"] = C_DIR
r = subprocess.run(
    [WIBO, f"{C_DIR}/ngccc.exe", "-O2", "-G0", "-mcpu=750", "-fno-common",
     "-I", f"{ROOT}/include", "-c", srcp, "-o", objp],
    cwd=ROOT, capture_output=True, text=True, env=env)
if r.returncode != 0:
    print("COMPILE FAIL", r.stderr[:2000])
    sys.exit(1)

# ---- byte-compare ----
out = subprocess.run([OBJDUMP, "-d", objp], capture_output=True, text=True).stdout
size_of = {'d': 13, 'f': 11, 's': 14, 'l': 14}
exact = []
near = []
for addr, kind, base, off, extra in fns:
    fname = f"fn_{addr:08X}"
    size = size_of[kind] * 4
    oo = offs[1] + (addr - addrs[1])
    orig_bytes = d[oo:oo + size]
    block = out.split(f"<{fname}>:")[1].split("\n\n")[0]
    got = bytearray()
    for l in block.splitlines()[1:size_of[kind] + 1]:
        hx = l.split("\t")[1].strip()
        got += bytes.fromhex(hx)
    if bytes(got) == orig_bytes:
        exact.append((addr, kind, base, off, extra))
    else:
        ndiff = sum(1 for a, b in zip(got, orig_bytes) if a != b)
        near.append((addr, kind, base, off, extra, ndiff))

print(f"\n=== EXACT: {len(exact)} ===")
for a, k, b, o, x in exact:
    print(f"  0x{a:08X} {k} base=0x{b:X} off=0x{o:X} extra=0x{x:X}")
print(f"\n=== NEAR (diff bytes): {len(near)} ===")
for a, k, b, o, x, nd in sorted(near, key=lambda t: t[5])[:30]:
    print(f"  0x{a:08X} {k} base=0x{b:X} off=0x{o:X} extra=0x{x:X} diff={nd}")

# ---- write master + per-range files ----
outp = f"{ROOT}/src/gen_dispatch.c"
if exact:
    # NOTE: this master file is a reference-only listing — it is NOT in
    # configure.py or splits.txt (multi-range files cause dtk link-order
    # cycles). The per-range gen_dispatch_XXX.c files below are the build
    # inputs. Keep it or delete it freely; it never gets compiled.
    with open(outp, "w") as f:
        f.write(gen_c(exact))
    print(f"\nwrote {outp} with {len(exact)} functions (reference-only, not built)")

    addr_sorted = sorted(exact, key=lambda t: t[0])
    ranges = []
    start, prev = addr_sorted[0][0], addr_sorted[0][0]
    prev_end = start + size_of[addr_sorted[0][1]] * 4
    for t in addr_sorted[1:]:
        a = t[0]
        if a == prev_end:
            prev = a
            prev_end = a + size_of[t[1]] * 4
        else:
            ranges.append((start, prev_end))
            start = prev = a
            prev_end = a + size_of[t[1]] * 4
    ranges.append((start, prev_end))
    print("\nSPLIT RANGES:")
    for s, e in ranges:
        print(f"\t.text       start:0x{s:X} end:0x{e:X}")

    idx = 0
    for s, e in ranges:
        fns_in = sorted((t for t in exact if s <= t[0] < e), key=lambda t: t[0])
        fname = f"gen_dispatch_{idx:03d}.c"
        lines = [
            "// Auto-generated from tools/gen_dispatch_fns.py",
            f"// range 0x{s:X}-0x{e:X} ({len(fns_in)} functions). Byte-identical.",
            '#include "types.h"',
            "",
        ]
        for addr, kind, base, off, extra in fns_in:
            if kind == 'd':
                lines.append(f"void fn_{addr:08X}(void *o) {{")
                lines.append(f"    void **t = *(void ***)((char *)o + 0x{base:X});")
                lines.append(f"    void (*fp)(void *) = (void (*)(void *))t[0x{(off + 4) >> 2:x}];")
                lines.append(f"    fp((char *)o + (signed short)((s16 *)t)[0x{off >> 1:x}]);")
            elif kind == 'f':
                lines.append(f"void fn_{addr:08X}(void *o) {{")
                lines.append(f"    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x{off:X});")
                lines.append(f"    fp(o);")
            elif kind == 's':
                lines.append(f"void fn_{addr:08X}(void *o, u32 v) {{")
                lines.append(f"    void **t;")
                lines.append(f"    void (*fp)(void *);")
                lines.append(f"    *(u32 *)((char *)o + 0x{extra:X}) = v;")
                lines.append(f"    t = *(void ***)((char *)o + 0x{base:X});")
                lines.append(f"    fp = (void (*)(void *))t[0x{(off + 4) >> 2:x}];")
                lines.append(f"    fp((char *)o + (signed short)((s16 *)t)[0x{off >> 1:x}]);")
            elif kind == 'l':
                lines.append(f"void fn_{addr:08X}(void *o) {{")
                lines.append(f"    void **t = *(void ***)((char *)o + 0x{base:X});")
                lines.append(f"    void (*fp)(void *, int) = (void (*)(void *, int))t[0x{(off + 4) >> 2:x}];")
                lines.append(f"    fp((char *)o + (signed short)((s16 *)t)[0x{off >> 1:x}], {extra});")
            lines.append("}")
            lines.append("")
        with open(f"{ROOT}/src/{fname}", "w") as f:
            f.write("\n".join(lines))
        idx += 1
    print(f"wrote {idx} per-range files in src/")
