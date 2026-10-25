#!/usr/bin/env python3
""" mwcc verify harness.

Compiles a C file with mwcc (GC/1.2.5n via wibo) using the dolphin-lib flags
from configure.py, extracts the object's .text, and relocation-mask-compares
it against the DOL bytes at a given address.

Usage:
  python3 mwcc_verify.py <addr> <cfile> [extra mwcc flags...]

Prints: EXACT / DIFF (n mismatched words) + first mismatches (want|got).
Exit code 0 on EXACT.
"""
import sys, os, subprocess, struct

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CC = f"{ROOT}/build/compilers/GC/1.2.5n/mwcceppc.exe"
WIBO = f"{ROOT}/build/tools/wibo"
DOL = f"{ROOT}/orig/G2TE52/sys/main.dol"
WORK = "<scratch>"

# DOL .text mapping: vaddr 0x800034A0 -> file off 0x4A0
TEXT_VA = 0x800034A0
TEXT_OFF = 0x4A0

BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "off", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "off",
    "-str", "reuse", "-multibyte",
    "-ir", "libs/dolphin/src",
    "-i", "libs/dolphin/include",
    "-i", "libs/dolphin/include/dolphin",
    "-i", "libs/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include",
    "-i", "include",
    "-i", "build/G2TE52/include",
    "-char", "unsigned",
    "-D__GEKKO__", "-DSDK_REVISION=2", "-DNDEBUG=1",
]

# ELF PPC reloc types seen in mwcc objects
R_PPC_ADDR16_LO = 3
R_PPC_ADDR16_HI = 4
R_PPC_ADDR16_HA = 6
R_PPC_REL24 = 10
R_PPC_REL14 = 11
R_PPC_EMB_SDA21 = 109  # mwcc uses this for sda21


def mask_for(t):
    if t == R_PPC_REL24:
        return 0xFC000003
    if t in (R_PPC_REL14,):
        return 0xFFFF0003
    if t in (R_PPC_ADDR16_LO, R_PPC_ADDR16_HI, R_PPC_ADDR16_HA):
        return 0xFFFF0000
    if t == R_PPC_EMB_SDA21:
        return 0xFFFF0000
    return 0x00000000  # unknown: compare nothing


def dol_slice(addr, size):
    with open(DOL, "rb") as f:
        f.seek(addr - TEXT_VA + TEXT_OFF)
        return f.read(size)


def parse_elf(data):
    assert data[:4] == b"\x7fELF"
    ei_class, ei_data = data[4], data[5]
    assert ei_class == 1 and ei_data == 2  # 32-bit BE
    e_shoff, = struct.unpack_from(">I", data, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from(">HHH", data, 0x2E)
    secs = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        name, styp, flags, addr, offset, size, link, info, align, entsz = struct.unpack_from(">IIIIIIIIII", data, off)
        secs.append(dict(name=name, typ=styp, flags=flags, addr=addr, offset=offset, size=size,
                         link=link, info=info, entsz=entsz))
    shstr = secs[e_shstrndx]
    def sname(n):
        end = data.index(b"\0", shstr["offset"] + n)
        return data[shstr["offset"] + n:end].decode()
    for s in secs:
        s["sname"] = sname(s["name"])
    return secs


def compile_obj(cfile, outdir, extra):
    os.makedirs(outdir, exist_ok=True)
    cmd = [WIBO, CC] + BASE_FLAGS + list(extra) + ["-c", cfile, "-o", outdir + "/"]
    env = dict(os.environ)
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, env=env)
    objs = [f for f in os.listdir(outdir) if f.endswith(".o") or f.endswith(".obj")]
    return r, objs


def main():
    addr = int(sys.argv[1], 16)
    cfile = sys.argv[2]
    extra = sys.argv[3:]
    os.makedirs(WORK, exist_ok=True)
    # clean workdir
    for f in os.listdir(WORK):
        os.unlink(os.path.join(WORK, f))
    r, objs = compile_obj(cfile, WORK, extra)
    if r.returncode != 0 or not objs:
        print("COMPILE FAIL:")
        print(r.stderr[-3000:])
        sys.exit(2)
    objpath = os.path.join(WORK, objs[0])
    data = open(objpath, "rb").read()
    secs = parse_elf(data)
    text = next((s for s in secs if s["sname"] == ".text"), None)
    if text is None:
        print("NO .text SECTION")
        sys.exit(2)
    got = bytearray(data[text["offset"]:text["offset"] + text["size"]])

    # symtab + section vaddrs for SDA21 simulation
    SDA_BASE = 0x803D2280
    syms = {}
    shndx_va = {}
    symtab = next((s for s in secs if s["typ"] == 2), None)
    if symtab:
        strtab = secs[symtab["link"]]
        n = symtab["size"] // 16
        for i in range(n):
            off = symtab["offset"] + i * 16
            st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from(">IIIBBH", data, off)
            end = data.index(b"\0", strtab["offset"] + st_name)
            name = data[strtab["offset"] + st_name:end].decode()
            syms[i] = (name, st_value, st_shndx)
    for i, s in enumerate(secs):
        shndx_va[i] = s.get("addr", 0)

    masks = {}
    sda_patches = []  # (insn_off, target)
    for s in secs:
        if s["typ"] not in (4, 9):
            continue
        tgt = secs[s["info"]]
        if tgt["sname"] != ".text":
            continue
        ent = 12 if s["typ"] == 4 else 8
        n = s["size"] // ent
        for i in range(n):
            off = s["offset"] + i * ent
            r_offset, = struct.unpack_from(">I", data, off)
            r_info, = struct.unpack_from(">I", data, off + 4)
            addend = struct.unpack_from(">i", data, off + 8)[0] if ent == 12 else 0
            typ = r_info & 0xFF
            symi = r_info >> 8
            insn = r_offset & ~3
            if typ == R_PPC_EMB_SDA21:
                name, va, shndx = syms.get(symi, ("", 0, 0))
                if name.startswith("lbl_"):
                    target = int(name[4:], 16)
                else:
                    target = shndx_va.get(shndx, 0) + addend
                sda_patches.append((insn, target))
                continue
            m = mask_for(typ)
            if m:
                masks[insn] = masks.get(insn, 0xFFFFFFFF) & m

    # simulate SDA21 link: set rA=r13, disp=target-SDA_BASE
    for insn, target in sda_patches:
        disp = (target - SDA_BASE) & 0xFFFF
        w = struct.unpack_from(">I", got, insn)[0]
        w = (w & 0xFFE0FFFF) | (13 << 16) | disp
        struct.pack_into(">I", got, insn, w)

    want = dol_slice(addr, len(got))
    if len(want) != len(got):
        print(f"SIZE MISMATCH: want {len(want)}B got {len(got)}B")
    gbytes = bytes(got)
    n = min(len(want), len(got)) // 4
    bad = []
    for i in range(n):
        wv = struct.unpack_from(">I", want, i * 4)[0]
        gv = struct.unpack_from(">I", gbytes, i * 4)[0]
        m = masks.get(i * 4, 0xFFFFFFFF)
        if (wv & m) != (gv & m):
            bad.append((i * 4, wv, gv, m))
    total = max(len(want), len(got)) // 4
    pct = 100.0 * (total - len(bad)) / total if total else 0.0
    if not bad and len(want) == len(got):
        print(f"EXACT ({len(got)}B)")
        sys.exit(0)
    print(f"DIFF {len(bad)}/{total} words ({pct:.1f}%) size want={len(want)} got={len(got)}")
    for off, wv, gv, m in bad[:24]:
        print(f"  +{off:04x}: want {wv:08x} got {gv:08x} (mask {m:08x})")
    # also report non-empty non-.text sections (data! bss!) — matters at promote time
    for s in secs:
        if s["sname"] in (".text", ".comment", ".shstrtab", ".symtab", ".strtab", ".rela.text", ".rel.text"):
            continue
        sz = s["size"]
        nonzero = any(data[s["offset"]:s["offset"] + sz]) if sz else False
        if sz and (nonzero or s["typ"] in (1, 8)):
            print(f"  section {s['sname']}: size {sz:#x} type {s['typ']} nonzero={nonzero}")
    sys.exit(1)


if __name__ == "__main__":
    main()
