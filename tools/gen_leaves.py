#!/usr/bin/env python3
"""Auto-match tiny leaf functions (no frame, no calls, no branches) across
the whole DOL. Uses the objdiff report's function boundaries, so every
candidate is a real function start (no mid-function false positives).

Patterns (each verified by masked byte-compare with ngccc -O2 -G0):
  c:    li r3,IMM; blr                      -> return IMM
  c32:  lis r3,HA; addi/ori r3,r3,LO; blr   -> return 32-bit const
  g:    lwz/lhz/lha/lbz r3,OFF(rB); blr     -> read field (sized load)
  eb:   lbz r3,OFF(rB); extsb r3,r3; blr    -> signed byte getter
  eh:   lhz r3,OFF(rB); extsh r3,r3; blr    -> signed halfword getter
  neg:  lwz r3,OFF(rB); neg r3,r3; blr      -> negate field
  not:  lwz r3,OFF(rB); nor r3,r3,r3; blr   -> bitwise NOT field
  p:    addi r3,r3,IMM; blr                 -> return (char*)o + IMM
  m:    mr r3,rV; blr                       -> return argV
  s:    stw/sth/stb rV,OFF(rB); blr         -> write field (arg reg rV)
  k:    li rX,IMM; stw rX,OFF(r3); blr      -> set field to const
  kret: li rX,IMM; stw rX,OFF(r3); li r3,IMM2; blr -> set const + return IMM2
  k2:   li rX,IMM; stw rX,OFF1; stw rX,OFF2; blr
  k3:   li rX,IMM; stw rX,OFF1; stw rX,OFF2; stw rX,OFF3; blr
  cp:   lwz rV,OFF1(rB); stw rV,OFF2(rB); blr -> copy field
  da:   lwz r3,OFF(rB); addi r3,r3,IMM; blr  -> deref pointer + offset
  rl:   lwz r3,OFF(rB); rlwinm r3,r3,SH,MB,ME; blr -> masked field read
  sl:   lwz r3,OFF(rB); slwi/srwi/srawi r3,r3,N; blr -> shifted field read
  lg:   lis rX,HA; lwz r3,LO(rX); blr        -> return global
  kk:   li rV,IMM; stw rV,OFF1(r3); li rW,IMM2; stw rW,OFF2(r3); blr
  kk2:  li rV,IMM1; li rW,IMM2; stw rV,OFF1(r3); stw rW,OFF2(r3); blr

Writes one src/fn_XXXXXXXX.c per exact match (registered via add_gen_leaves).
"""
import glob
import json
import os
import re
import struct
import subprocess
import sys
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DOL = f"{ROOT}/orig/G2TE52/sys/main.dol"
# Compiler version must track configure.py's game-lib "mw_version" (the first
# ProDG entry — GC runtime libs don't match the ProDG/ prefix). The build and
# the draft sweep MUST use the same compiler: byte-identical for non-PS code,
# but 3.9.3 adds paired-single support used by per-object -mps-float cflags.
# NGCCC_DIR overrides the compiler for a single scoring/promotion run; the
# per-object `mw_version` in configure.py is what the build itself uses, so a
# draft that only matches under an older ProDG must be promoted with both.
_mw = re.search(r'"mw_version":\s*"ProDG/([\d.]+)"', open(f"{ROOT}/configure.py").read())
C_DIR = os.environ.get("NGCCC_DIR") or \
    f"{ROOT}/build/compilers/ProDG/{_mw.group(1) if _mw else '3.7'}"
WIBO = f"{ROOT}/build/tools/wibo"

# Addresses excluded from leaf generation. 0x8025254C was parked here under
# the old "mwldeppc drops objects at auto-asm boundaries" theory (2026-08-08);
# doc-13 later proved the real cause is reachability-based dead-strip GC and
# the mitigation (config.yml force_active) was executed 2026-09-02 — the leaf
# now links as a normal C unit. Keep the set only for future genuine cases.
# 2026-10-08: three phantom gap spans the draft generator misread as functions
# (all symbols.txt lbl_, all family=stub parked, drafts deleted — see
# docs/parkings/62-unsweepable-draft-classes.md "phantom gap spans"):
# 0x8024FD8C = float 0.5 pool word, 0x802575C4 = (-1.0,+1.0) paired-single
# pair owned by fn_802575CC, 0x8025AD34 = hand-asm rfi restore routine head.
PARKED = {0x8024FD8C, 0x802575C4, 0x8025AD34,
          0x802572C4, 0x8028E038}

def build_matched_addrs():
    """addr -> owning unit name for functions already matched in the build.
    A function counts as matched when report.json says its unit is complete,
    the unit is 100% fuzzy, or the function itself is 100% fuzzy — the same
    predicate tools/gen_wip_drafts.py uses. This covers libs/ units
    (runtime/dolphin/...) and renamed game units (vcall_*, real-named SDK
    fns) whose address never appears as an fn_ token in src/. The WIP sweep
    (test_wip_drafts) skips these and promote_wip refuses them, so a draft
    for an already-owned address can never become an orphan src/fn_*.c twin
    of a libs/ source. Returns {} when report.json is missing (cold build).
    """
    rep_path = f"{ROOT}/build/G2TE52/report.json"
    if not os.path.isfile(rep_path):
        return {}
    rep = json.load(open(rep_path))
    owned = {}
    for u in rep.get("units", []):
        u_md = u.get("metadata", {})
        unit_matched = (u_md.get("complete") is True
                        or u.get("measures", {}).get("fuzzy_match_percent") == 100.0)
        for fn in u.get("functions", []):
            if unit_matched or fn.get("fuzzy_match_percent") == 100.0:
                owned[int(fn["metadata"]["virtual_address"])] = u.get("name", "?")
    return owned

# SDK-named global functions (scope:global in symbols.txt) whose real names
# other asm files reference (e.g. bl PPCMfhid2). When matching one of these
# addresses, the generated C must define the SDK name or the link breaks.
SDK_NAMES = {}
_symp = f"{ROOT}/config/G2TE52/symbols.txt"
if os.path.isfile(_symp):
    for _ln in open(_symp):
        _m = re.match(r"([A-Za-z_][A-Za-z0-9_]*) = \.text:0x([0-9A-Fa-f]+).*scope:global", _ln)
        if _m and not _m.group(1).startswith(("fn_", "lbl_")):
            SDK_NAMES[int(_m.group(2), 16)] = _m.group(1)

d = open(DOL, "rb").read()
offs = struct.unpack_from(">18I", d, 0)
addrs = struct.unpack_from(">18I", d, 0x48)
sizes = struct.unpack_from(">18I", d, 0x90)
t_off, t_addr, t_size = offs[1], addrs[1], sizes[1]
# .rodata2 (sec 8, 0x8028FB60) — read-only string data; exported for the QB
# constant dict sources (tools/resolve_qb_hashes.py scans its plaintext names).
r2_off, r2_addr, r2_size = offs[8], addrs[8], sizes[8]

# --- load matched set ---
matched = set()
rep_path = f"{ROOT}/build/G2TE52/report.json"
if os.path.isfile(rep_path):
    rep = json.load(open(rep_path))
    for u in rep.get("units", []):
        for fn in u.get("functions", []):
            if fn.get("matches") or fn.get("fuzzy_match_percent", 0) >= 100:
                matched.add(int(fn["metadata"]["virtual_address"]))
if not matched:
    for cpath in glob.glob(f"{ROOT}/src/*.c"):
        for mo in re.finditer(r"fn_[0-9A-F]{8}", open(cpath).read()):
            matched.add(int(mo.group(0)[3:], 16))

# --- all function boundaries ---
rep = json.load(open(rep_path))
fns = sorted({int(fn["metadata"]["virtual_address"])
              for u in rep.get("units", []) for fn in u.get("functions", [])})

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.detail = False
md.skipdata = True


def insns_at(start, count=10):
    off = t_off + (start - t_addr)
    return list(md.disasm(d[off:off + count * 4], start))


def imm(v):
    v = v.strip()
    return int(v, 0) if v.startswith(("0x", "-0x", "0X", "-0X")) else int(v)


RE_IMM = re.compile(r"(-?(?:0x)?[0-9a-fA-F]+)")
RE_OFF = re.compile(r"(-?(?:0x)?[0-9a-fA-F]+)\(r(\d+)\)")
RE_LIS = re.compile(r"r(\d+), (-?(?:0x)?[0-9a-fA-F]+)")
RE_MASK = re.compile(r"r(\d+), r\1, (-?(?:0x)?[0-9a-fA-F]+), (-?(?:0x)?[0-9a-fA-F]+), (-?(?:0x)?[0-9a-fA-F]+)")

BASE2ARG = {3: 1, 4: 2, 5: 3, 6: 4, 7: 5}  # base reg -> parameter position
VREG2ARG = {4: 2, 5: 3, 6: 4, 7: 5}        # value reg -> parameter position


def hw_mask(mb, me):
    """Decode a PPC rlwinm mask field (MB..ME are MSB-numbered, bit 0 = MSB)
    into an LSB-numbered u32 mask value."""
    if me >= mb:
        return ((1 << (me - mb + 1)) - 1) << (31 - me)
    return ((1 << (32 - mb)) - 1) | (0xFFFFFFFF << (31 - me))


def bpad(br):
    """dummy-arg prefix for a non-r3 base register."""
    pos = BASE2ARG.get(br)
    if pos is None:
        return None
    if pos == 1:
        return ""
    return ", ".join("s32 d%d" % i for i in range(2, pos)) + ", "


def classify(start):
    """Return (kind, params) or None."""
    ins = insns_at(start)
    m = [x.mnemonic for x in ins]
    op = [x.op_str for x in ins]
    if not m:
        return None
    # --- pure trampoline: stwu; mflr; stw r0,X; bl T; lwz r0,X; mtlr; addi r1,N; blr ---
    # Only emitted when the target is a *defined* matched function (src file
    # exists): the extern must resolve at link time, and asm-covered targets
    # don't define fn_* symbols in the ELF. Checked in the main loop, not here.
    if m[0] == "stwu" and len(m) >= 8:
        if m[1] == "mflr" and m[2] == "stw" and m[3] == "bl" and m[4] == "lwz" \
           and m[5] == "mtlr" and m[6] == "addi" and m[7] == "blr":
            fr = re.match(r"r1, -(0x[0-9a-fA-F]+|[0-9]+)\(r1\)$", op[0])
            st0 = re.match(r"r0, (0x[0-9a-fA-F]+|[0-9]+)\(r1\)$", op[2])
            ld0 = re.match(r"r0, (0x[0-9a-fA-F]+|[0-9]+)\(r1\)$", op[4])
            ad = re.match(r"r1, r1, (-?0x[0-9a-fA-F]+|-?[0-9]+)$", op[6])
            if fr and st0 and ld0 and ad and st0.group(1) == ld0.group(1):
                x = int(st0.group(1), 0)
                n = int(fr.group(1), 0)
                if ad.group(1) == str(n) or int(ad.group(1), 0) == n:
                    tgt = re.search(r"0x[0-9a-fA-F]+", op[3])
                    if tgt and len(m) >= 8 and m[4:8] == ["lwz", "mtlr", "addi", "blr"]:
                        return ("tp", int(tgt.group(0), 16))
        return None  # other frame functions not handled here
    # --- empty function: starts with blr (match just the first 4 bytes) ---
    if m[0] == "blr":
        return ("e",)
    try:
        e = m.index("blr")
    except ValueError:
        return None
    m, op = m[:e + 1], op[:e + 1]
    n = len(m)
    if n < 2 or n > 10:
        return None

    def mem(operand):
        mo = RE_OFF.search(operand)
        return mo

    # --- lis rX,HA; li rY,IMM; stw rY,LO(rX); blr (const store to extern global) ---
    if n == 4 and m[0] == "lis" and m[1] == "li" and m[2] == "stw":
        li0 = RE_LIS.match(op[0])
        li1 = RE_LIS.match(op[1])
        st = mem(op[2])
        if li0 and li1 and st and int(st.group(2)) == int(li0.group(1)) \
           and li1.group(1) == op[2].split(",", 1)[0].strip()[1:]:
            g = ((imm(li0.group(2)) << 16) + imm(st.group(1))) & 0xFFFFFFFF
            return ("ks", g, imm(li1.group(2)))
    # --- lwz rD,OFF(r3); li r3,A; cmpwi rD,IMM; beqlr; li r3,B; blr (early-ret boolean) ---
    if n == 6 and m[0] == "lwz" and m[1] == "li" and m[2] == "cmpwi" and m[3] in ("beqlr", "bnelr") \
       and m[4] == "li" and m[5] == "blr" and op[1].startswith("r3, "):
        ld = mem(op[0])
        cm = re.match(r"r(\d+), (-?(?:0x)?[0-9a-fA-F]+)$", op[2])
        if ld and cm and int(ld.group(2)) == 3 and int(cm.group(1)) == 0 \
           and op[1][0] == op[4][0] == "r":
            return ("bg", imm(ld.group(1)), imm(cm.group(2)), m[3], imm(op[1][4:]), imm(op[4][4:]))
    # --- lwz r9,OFF(r3); li r3,A; lwz r0,OFF2(r9); cmpwi r0,IMM; beqlr; li r3,B; blr (double-deref boolean) ---
    if n == 7 and m[0] == "lwz" and m[1] == "li" and m[2] == "lwz" and m[3] == "cmpwi" \
       and m[4] in ("beqlr", "bnelr") and m[5] == "li" and m[6] == "blr" and op[1].startswith("r3, "):
        ld1 = mem(op[0])
        ld2 = mem(op[2])
        cm = re.match(r"r(\d+), (-?(?:0x)?[0-9a-fA-F]+)$", op[3])
        if ld1 and ld2 and cm and int(ld1.group(2)) == 3 and int(cm.group(1)) == 0 \
           and op[0].split(",", 1)[0].strip()[1:] == "9" and op[2].split(",", 1)[0].strip()[1:] == "0":
            return ("bg2", imm(ld1.group(1)), imm(ld2.group(1)), imm(cm.group(2)),
                    m[4], imm(op[1][4:]), imm(op[5][4:]))
    # --- cmpwi rD,IMM; li r3,A; beqlr; li r3,B; blr (early-ret boolean on an arg) ---
    if n == 5 and m[0] == "cmpwi" and m[1] == "li" and m[2] in ("beqlr", "bnelr") \
       and m[3] == "li" and m[4] == "blr" and op[1].startswith("r3, "):
        cm = re.match(r"r(\d+), (-?(?:0x)?[0-9a-fA-F]+)$", op[0])
        if cm and int(cm.group(1)) in (3, 4, 5, 6, 7):
            return ("bga", int(cm.group(1)), imm(cm.group(2)), m[2], imm(op[1][4:]), imm(op[3][4:]))
    # --- lwz rD,OFF(r3); oris/ori rD,rD,IMM; stw rD,OFF(r3); blr (or-mask store) ---
    if n == 4 and m[0] == "lwz" and m[1] in ("oris", "ori") and m[2] == "stw":
        ld = mem(op[0])
        st = mem(op[2])
        om = re.match(r"r(\d+), r\d+, (-?(?:0x)?[0-9a-fA-F]+)$", op[1])
        vr = op[0].split(",", 1)[0].strip()[1:]
        if ld and st and om and int(ld.group(2)) == 3 and int(st.group(2)) == 3 \
           and imm(ld.group(1)) == imm(st.group(1)) and vr == op[2].split(",", 1)[0].strip()[1:]:
            return ("os", m[1], imm(ld.group(1)), imm(om.group(2)))
    # --- lwz r0,OFF(r3); li r3,1; andi./andis. r9,r0,M; bnelr; li r3,0; blr (masked boolean) ---
    if n >= 6 and m[0] == "lwz" and m[1] == "li" and m[2] in ("andi.", "andis.") \
       and m[3] == "bnelr" and m[4] == "li" and m[5] == "blr" \
       and op[1].startswith("r3, ") and op[4].startswith("r3, "):
        ld = mem(op[0])
        am = re.match(r"r\d+, r\d+, (-?(?:0x)?[0-9a-fA-F]+)$", op[2])
        if ld and am and int(ld.group(2)) == 3:
            mval = imm(am.group(1))
            if m[2] == "andis.":
                mval = (mval << 16) & 0xFFFFFFFF
            if imm(op[1][4:]) == 1 and imm(op[4][4:]) == 0:
                return ("mb", imm(ld.group(1)), mval)
    # --- lis rX,HA; lfs f1,LO(rX); blr (global float getter) ---
    if n == 3 and m[0] == "lis" and m[1] == "lfs" and m[2] == "blr":
        li = RE_LIS.match(op[0])
        lo = mem(op[1])
        if li and lo and int(lo.group(2)) == int(li.group(1)):
            g = ((imm(li.group(2)) << 16) + imm(lo.group(1))) & 0xFFFFFFFF
            return ("gf", g)
    # --- lis rX,HA; stfs f1,LO(rX); blr (global float setter) ---
    if n == 3 and m[0] == "lis" and m[1] == "stfs" and m[2] == "blr":
        li = RE_LIS.match(op[0])
        lo = mem(op[1])
        if li and lo and int(lo.group(2)) == int(li.group(1)):
            g = ((imm(li.group(2)) << 16) + imm(lo.group(1))) & 0xFFFFFFFF
            return ("gs", g)
    # --- lis rX,HA; lwz rY,LO(rX); addi rY,rY,-1; stw rY,LO(rX); blr (global dec) ---
    if n == 5 and m[0] == "lis" and m[1] == "lwz" and m[2] == "addi" and m[3] == "stw":
        li = RE_LIS.match(op[0])
        ld = mem(op[1])
        st = mem(op[3])
        vr = op[1].split(",", 1)[0].strip()[1:]
        if li and ld and st and int(ld.group(2)) == int(li.group(1)) and int(st.group(2)) == int(li.group(1)) \
           and imm(ld.group(1)) == imm(st.group(1)) and op[2].startswith(f"r{vr}, r{vr}, -1"):
            g = ((imm(li.group(2)) << 16) + imm(ld.group(1))) & 0xFFFFFFFF
            return ("gd", g)
    # --- lis rX,HA; addi rX,rX,LO; lwz r3,0(rX); lwz r4,4(rX); blr (u64 global read) ---
    if n == 5 and m[0] == "lis" and m[1] == "addi" and m[2] == "lwz" and m[3] == "lwz":
        li = RE_LIS.match(op[0])
        if li and op[1].startswith(f"r{li.group(1)}, r{li.group(1)}, "):
            base = int(li.group(1))
            l0 = mem(op[2])
            l4 = mem(op[3])
            if l0 and l4 and int(l0.group(2)) == base and int(l4.group(2)) == base \
               and imm(l0.group(1)) == 0 and imm(l4.group(1)) == 4 \
               and op[2].startswith("r3, ") and op[3].startswith("r4, "):
                g = ((imm(li.group(2)) << 16) + imm(op[1][len(f"r{base}, r{base}, "):])) & 0xFFFFFFFF
                return ("g64", g)
    # --- lis rX,HA; li r0,V; stw r0,LO(rX); li r3,R; blr (global const store + return) ---
    if n == 5 and m[0] == "lis" and m[1] == "li" and m[2] == "stw" and m[3] == "li" \
       and op[3].startswith("r3, ") and op[1].startswith("r0, "):
        li = RE_LIS.match(op[0])
        st = mem(op[2])
        if li and st and int(st.group(2)) == int(li.group(1)) and li.group(1) != "0" \
           and op[2].split(",", 1)[0].strip()[1:] == "0":
            g = ((imm(li.group(2)) << 16) + imm(st.group(1))) & 0xFFFFFFFF
            return ("gcs", g, imm(op[1][4:]), imm(op[3][4:]))
    # --- lis rX,HA; li r3,1; lwz r0,LO(rX); cmpwi r0,0; bnelr; li r3,0; blr (global bool) ---
    if n == 7 and m[0] == "lis" and m[1] == "li" and m[2] == "lwz" and m[3] == "cmpwi" \
       and m[4] == "bnelr" and m[5] == "li" and m[6] == "blr" \
       and op[1].startswith("r3, ") and op[5].startswith("r3, "):
        li = RE_LIS.match(op[0])
        lo = mem(op[2])
        cm = re.match(r"r(\d+), 0$", op[3])
        if li and lo and cm and int(cm.group(1)) == 0 and int(lo.group(2)) == int(li.group(1)) \
           and imm(op[1][4:]) == 1 and imm(op[5][4:]) == 0:
            g = ((imm(li.group(2)) << 16) + imm(lo.group(1))) & 0xFFFFFFFF
            return ("gbt", g)
    # --- lis rX,HA; lwz rY,LO(rX); addi rY,rY,1; stw rY,LO(rX); blr (global inc) ---
    if n == 5 and m[0] == "lis" and m[1] == "lwz" and m[2] == "addi" and m[3] == "stw":
        li = RE_LIS.match(op[0])
        ld = mem(op[1])
        st = mem(op[3])
        vr = op[1].split(",", 1)[0].strip()[1:]
        if li and ld and st and int(ld.group(2)) == int(li.group(1)) and int(st.group(2)) == int(li.group(1)) \
           and imm(ld.group(1)) == imm(st.group(1)) and op[2].startswith(f"r{vr}, r{vr}, 1"):
            g = ((imm(li.group(2)) << 16) + imm(ld.group(1))) & 0xFFFFFFFF
            return ("ginc", g)
    # --- stfs f1,OFF(r3); blr (float field setter) ---
    if n == 2 and m[0] == "stfs" and op[0].startswith("f1, "):
        mo = mem(op[0])
        if mo and int(mo.group(2)) == 3:
            return ("ffs", imm(mo.group(1)))
    # --- lfs f1,OFF(r3); blr (float field getter) ---
    if n == 2 and m[0] == "lfs" and op[0].startswith("f1, "):
        mo = mem(op[0])
        if mo and int(mo.group(2)) in (3, 4, 5, 6, 7):
            return ("ffg", imm(mo.group(1)), int(mo.group(2)))
    # --- slwi r4,r4,2; addi r3,r3,OFF; lwzx r3,r3,r4; blr (array index read) ---
    if n == 4 and m[0] == "slwi" and m[1] == "addi" and m[2] == "lwzx":
        sl = re.match(r"r4, r4, (0x[0-9a-fA-F]+|[0-9]+)$", op[0])
        ad = re.match(r"r3, r3, (-?0x[0-9a-fA-F]+|-?[0-9]+)$", op[1])
        if sl and ad and imm(sl.group(1)) == 2 and op[2] == "r3, r3, r4" \
           and imm(ad.group(1)) > 0 and imm(ad.group(1)) % 4 == 0:
            return ("ai", imm(ad.group(1)))
    # --- lwz r9,OFF(r3); li r0,1; slw r0,r0,r4; li r3,1; and. r11,r9,r0; bnelr; li r3,0; blr (bit test) ---
    if n == 8 and m[0] == "lwz" and m[1] == "li" and m[2] == "slw" and m[3] == "li" \
       and m[4] == "and." and m[5] == "bnelr" and m[6] == "li" and m[7] == "blr" \
       and op[1].startswith("r0, ") and op[3].startswith("r3, ") and op[6].startswith("r3, "):
        ld = mem(op[0])
        if ld and int(ld.group(2)) == 3 and imm(op[1][4:]) == 1 and imm(op[3][4:]) == 1 and imm(op[6][4:]) == 0:
            return ("bt", imm(ld.group(1)))
    # --- lwz r9,OFF(r3); li r0,1; slw r0,r0,r4; or r9,r9,r0; stw r9,OFF(r3); blr (bit set) ---
    if n == 6 and m[0] == "lwz" and m[1] == "li" and m[2] == "slw" and m[3] == "or" and m[4] == "stw":
        ld = mem(op[0])
        st = mem(op[4])
        if ld and st and int(ld.group(2)) == 3 and int(st.group(2)) == 3 \
           and imm(ld.group(1)) == imm(st.group(1)) and imm(op[1][4:]) == 1:
            return ("bs", imm(ld.group(1)))
    # --- mr r9,r3; li r0,V; stb r0,3(r9); stb r0,0(r9); stb r0,1(r9); stb r0,2(r9); blr (byte fill 4) ---
    if n == 7 and m[0] == "mr" and m[1] == "li" and m[2:6] == ["stb", "stb", "stb", "stb"]:
        mx = re.match(r"r(\d+), r3$", op[0])
        if mx:
            vr = mx.group(1)
            offs = [mem(o).group(1) if mem(o) else None for o in op[2:6]]
            bases = [mem(o).group(2) if mem(o) else None for o in op[2:6]]
            if all(o is not None and b == vr for o, b in zip(offs, bases)) \
               and sorted(imm(o) for o in offs) == [0, 1, 2, 3]:
                return ("bf", imm(op[1][4:]))
    # --- lfs f0,OFF1(r3); lfs f1,OFF2(r3); fmuls f1,f0,f1; blr (float mul getter) ---
    if n == 4 and m[0] == "lfs" and m[1] == "lfs" and m[2] == "fmuls" and op[2] == "f1, f0, f1":
        l0 = mem(op[0])
        l1 = mem(op[1])
        if l0 and l1 and int(l0.group(2)) == 3 and int(l1.group(2)) == 3 \
           and op[0].startswith("f0, ") and op[1].startswith("f1, "):
            return ("fm", imm(l0.group(1)), imm(l1.group(1)))
    # --- cmpwi r4,0; beq L; lwz r0,OFF(r3); ori r0,r0,1; stw r0,OFF(r3); L: blr (cond or-store) ---
    if n == 6 and m[0] == "cmpwi" and m[1] == "beq" and m[2] == "lwz" and m[3] == "ori" and m[4] == "stw":
        cm = re.match(r"r4, 0$", op[0])
        ld = mem(op[2])
        st = mem(op[4])
        om = re.match(r"r0, r0, (-?(?:0x)?[0-9a-fA-F]+)$", op[3])
        if cm and ld and st and om and int(ld.group(2)) == 3 and int(st.group(2)) == 3 \
           and imm(ld.group(1)) == imm(st.group(1)):
            return ("cos", imm(ld.group(1)), imm(om.group(1)))
    # --- mulli r4,r4,0xc; lwz r0,OFF(r3); add r4,r4,r0; stfs f1,4(r4); blr (indexed float set) ---
    if n == 5 and m[0] == "mulli" and m[1] == "lwz" and m[2] == "add" and m[3] == "stfs":
        ml = re.match(r"r4, r4, (0x[0-9a-fA-F]+|[0-9]+)$", op[0])
        ld = mem(op[1])
        if ml and ld and int(ld.group(2)) == 3 and imm(ml.group(1)) == 0xc \
           and op[2] == "r4, r4, r0" and op[3] == "f1, 4(r4)":
            return ("ifs", imm(ld.group(1)))
    # --- mulli r4,r4,0xc; lwz r0,OFF(r3); add r4,r4,r0; stfs f1,8(r4); blr (indexed float set +2) ---
    if n == 5 and m[0] == "mulli" and m[1] == "lwz" and m[2] == "add" and m[3] == "stfs":
        ml = re.match(r"r4, r4, (0x[0-9a-fA-F]+|[0-9]+)$", op[0])
        ld = mem(op[1])
        if ml and ld and int(ld.group(2)) == 3 and imm(ml.group(1)) == 0xc \
           and op[2] == "r4, r4, r0" and op[3] == "f1, 8(r4)":
            return ("if2", imm(ld.group(1)))
    # --- mulli r4,r4,0xc; lwz r9,OFF(r3); stfsx f1,r4,r9; blr (indexed float set, stfsx) ---
    if n == 4 and m[0] == "mulli" and m[1] == "lwz" and m[2] == "stfsx":
        ml = re.match(r"r4, r4, (0x[0-9a-fA-F]+|[0-9]+)$", op[0])
        ld = mem(op[1])
        if ml and ld and int(ld.group(2)) == 3 and imm(ml.group(1)) == 0xc \
           and op[2] == "f1, r4, r9":
            return ("ifsz", imm(ld.group(1)))
    # --- lwz r9,OFF1(r3); cmpwi r9,0; beq L; li r0,0; stw r0,OFF2(r9); li r3,1; blr (guarded zero-store) ---
    if n == 7 and m[0] == "lwz" and m[1] == "cmpwi" and m[2] == "beq" and m[3] == "li" \
       and m[4] == "stw" and m[5] == "li" and m[6] == "blr" \
       and op[1] == "r9, 0" and op[3].startswith("r0, ") and op[5].startswith("r3, "):
        ld = mem(op[0])
        st = mem(op[4])
        if ld and st and int(ld.group(2)) == 3 and int(st.group(2)) == 9 \
           and op[0].split(",", 1)[0].strip()[1:] == "9" and op[4].split(",", 1)[0].strip()[1:] == "0" \
           and imm(op[3][4:]) == 0 and imm(op[5][4:]) == 1:
            return ("gz", imm(ld.group(1)), imm(st.group(1)))
    # --- slwi r9,r4,1; lwz r0,OFF(r3); add r9,r9,r4; slwi r9,r9,2; add r9,r9,r0; lfs f1,4(r9); blr (indexed float get) ---
    if n == 7 and m[0] == "slwi" and m[1] == "lwz" and m[2] == "add" and m[3] == "slwi" \
       and m[4] == "add" and m[5] == "lfs":
        ld = mem(op[1])
        if ld and int(ld.group(2)) == 3 and op[0] == "r9, r4, 1" and op[2] == "r9, r9, r4" \
           and op[3] == "r9, r9, 2" and op[4] == "r9, r9, r0" and op[5] == "f1, 4(r9)":
            return ("ifg", imm(ld.group(1)))
    # --- lis rA,GHA; lis rB,THA; lwz rD,GI(rA); addi rB,rB,TLO; slwi rD,rD,2; lwzx rX,rB,rD; [lwz r3,F(rX)]; blr (ptr table read) ---
    if n in (7, 8) and m[0] == "lis" and m[1] == "lis" and m[2] == "lwz" and m[3] == "addi" \
       and m[4] == "slwi" and m[5] == "lwzx":
        liA = RE_LIS.match(op[0])
        liB = RE_LIS.match(op[1])
        ld = mem(op[2])
        ad = re.match(r"r(\d+), r(\d+), (-?(?:0x)?[0-9a-fA-F]+)$", op[3])
        sl = re.match(r"r(\d+), r(\d+), 2$", op[4])
        if liA and liB and ld and ad and sl:
            ra = liA.group(1)
            rb = liB.group(1)
            rd = op[2].split(",", 1)[0].strip()[1:]  # lwz dest = scaled index reg
            if int(ld.group(2)) == int(ra) and ad.group(1) == rb and ad.group(2) == rb \
               and sl.group(1) == rd and sl.group(2) == rd:
                lx = re.match(rf"r(\d+), r{rb}, r{rd}$", op[5])
                if lx:
                    g = ((imm(liA.group(2)) << 16) + imm(ld.group(1))) & 0xFFFFFFFF
                    t = ((imm(liB.group(2)) << 16) + imm(ad.group(3))) & 0xFFFFFFFF
                    vr = lx.group(1)
                    if n == 7 and m[6] == "blr":
                        return ("pt", g, t)
                    if n == 8 and m[6] == "lwz" and m[7] == "blr" and op[6].startswith("r3, "):
                        fld = mem(op[6])
                        if fld and int(fld.group(2)) == int(vr):
                            return ("ptf", g, t, imm(fld.group(1)))
    # --- lhz r0,OFF2(r3); lhz r3,OFF1(r3); slwi r0,r0,16; or r3,r0,r3; blr (halfword combine) ---
    if n == 5 and m[0] == "lhz" and m[1] == "lhz" and m[2] == "slwi" and m[3] == "or":
        l1 = mem(op[0])
        l2 = mem(op[1])
        if l1 and l2 and int(l1.group(2)) == 3 and int(l2.group(2)) == 3 \
           and op[0].startswith("r0, ") and op[1].startswith("r3, ")\
           and op[2] == "r0, r0, 0x10" and op[3].startswith("r3, r0, r3"):
            return ("hc", imm(l1.group(1)), imm(l2.group(1)))
    # --- 2-insn leafs ---
    if n == 2:
        if m[0] == "li" and op[0].startswith("r3, "):
            return ("c", imm(op[0][4:]))
        if m[0] in ("lwz", "lhz", "lha", "lbz", "lwzu", "lhzu") and op[0].startswith("r3, "):
            mo = mem(op[0])
            if mo and int(mo.group(2)) in (3, 4, 5, 6, 7):
                return ("g", m[0], imm(mo.group(1)), int(mo.group(2)))
        if m[0] in ("stw", "sth", "stb"):
            mo = mem(op[0])
            if mo:
                vr = op[0].split(",", 1)[0].strip()
                if vr.startswith("r") and int(mo.group(2)) in (3, 4, 5, 6, 7):
                    return ("s", m[0], vr[1:], imm(mo.group(1)), int(mo.group(2)))
        if m[0] == "addi" and op[0].startswith("r3, r3, "):
            return ("p", imm(op[0][8:]))
        if m[0] == "mr" and op[0].startswith("r3, r"):
            return ("m", op[0][4:])
        if m[0] == "lis" and op[0].startswith("r"):
            return None  # 2-insn lis+blr isn't a meaningful leaf
    # --- lbz r3,OFF(rB); extsb r3,r3; blr (signed byte getter) ---
    if n == 3 and m[0] == "lbz" and m[1] == "extsb" and op[0].startswith("r3, "):
        mo = mem(op[0])
        if mo and int(mo.group(2)) in (3, 4, 5, 6, 7):
            return ("eb", imm(mo.group(1)), int(mo.group(2)))
    # --- lhz r3,OFF(rB); extsh r3,r3; blr (signed halfword getter) ---
    if n == 3 and m[0] == "lhz" and m[1] == "extsh" and op[0].startswith("r3, "):
        mo = mem(op[0])
        if mo and int(mo.group(2)) in (3, 4, 5, 6, 7):
            return ("eh", imm(mo.group(1)), int(mo.group(2)))
    # --- lwz r3,OFF(rB); neg r3,r3; blr ---
    if n == 3 and m[0] == "lwz" and m[1] == "neg" and op[0].startswith("r3, "):
        mo = mem(op[0])
        if mo and int(mo.group(2)) in (3, 4, 5, 6, 7):
            return ("neg", imm(mo.group(1)), int(mo.group(2)))
    # --- lwz r3,OFF(rB); nor r3,r3,r3; blr (bitwise NOT) ---
    if n == 3 and m[0] == "lwz" and m[1] == "nor" and op[1].startswith("r3, r3, r3") and op[0].startswith("r3, "):
        mo = mem(op[0])
        if mo and int(mo.group(2)) in (3, 4, 5, 6, 7):
            return ("not", imm(mo.group(1)), int(mo.group(2)))
    # --- lis r3,HA; addi/ori r3,r3,LO; blr (32-bit constant return) ---
    if n == 3 and m[0] == "lis" and m[1] in ("addi", "ori") and op[0].startswith("r3, "):
        li = RE_LIS.match(op[0])
        if li and li.group(1) == "3" and op[1].startswith("r3, r3, "):
            hi = imm(li.group(2))
            lo = imm(op[1][7:])
            if m[1] == "addi":
                v = ((hi << 16) + lo) & 0xFFFFFFFF
            else:
                v = ((hi << 16) | (lo & 0xFFFF)) & 0xFFFFFFFF
            return ("c32", v)
    # --- lis rX,HA; lwz r3,LO(rX); blr (global read) ---
    if n == 3 and m[0] == "lis" and m[1] == "lwz" and op[1].startswith("r3, "):
        li = RE_LIS.match(op[0])
        lo = mem(op[1])
        if li and lo and int(lo.group(2)) == int(li.group(1)):
            g = ((imm(li.group(2)) << 16) + imm(lo.group(1))) & 0xFFFFFFFF
            return ("lg", g)
    # --- li rX,IMM; stw rX,OFF(r3); li r3,IMM2; blr (const store + return) ---
    if n == 4 and m[0] == "li" and m[1] == "stw" and m[2] == "li" and op[2].startswith("r3, "):
        li = RE_LIS.match(op[0])
        st = mem(op[1])
        if li and st and int(st.group(2)) == 3 and op[0][1] == op[1].split(",", 1)[0].strip()[1:]:
            return ("kret", imm(li.group(2)), imm(st.group(1)), imm(op[2][4:]))
    # --- li rX,IMM; stw rX,OFF1(r3); stw rX,OFF2(r3); blr (k2) ---
    if n == 4 and m[0] == "li" and m[1] == "stw" and m[2] == "stw":
        li = RE_LIS.match(op[0])
        s1, s2 = mem(op[1]), mem(op[2])
        vr = op[0][1]
        if li and s1 and s2 and vr == op[1].split(",", 1)[0].strip()[1:] == op[2].split(",", 1)[0].strip()[1:] \
           and int(s1.group(2)) == 3 and int(s2.group(2)) == 3:
            return ("k2", imm(li.group(2)), imm(s1.group(1)), imm(s2.group(1)))
    # --- li rX,IMM; stw rX,OFF1(r3); stw rX,OFF2(r3); stw rX,OFF3(r3); blr (k3) ---
    if n == 5 and m[0] == "li" and m[1] == "stw" and m[2] == "stw" and m[3] == "stw":
        li = RE_LIS.match(op[0])
        s1, s2, s3 = mem(op[1]), mem(op[2]), mem(op[3])
        vr = op[0][1]
        if li and s1 and s2 and s3 and vr == op[1].split(",", 1)[0].strip()[1:] == op[2].split(",", 1)[0].strip()[1:] == op[3].split(",", 1)[0].strip()[1:] \
           and int(s1.group(2)) == 3 and int(s2.group(2)) == 3 and int(s3.group(2)) == 3:
            return ("k3", imm(li.group(2)), imm(s1.group(1)), imm(s2.group(1)), imm(s3.group(1)))
    # --- li rX,IMM; stw rX,OFF(r3); blr (const store) ---
    if n == 3 and m[0] == "li" and m[1] == "stw":
        li = RE_LIS.match(op[0])
        st = mem(op[1])
        if li and st and int(st.group(2)) == 3 and li.group(1) == op[1].split(",", 1)[0].strip()[1:]:
            return ("k", imm(li.group(2)), imm(st.group(1)))
    # --- lwz rV,OFF1(rB); stw rV,OFF2(rB); blr (copy field) ---
    if n == 3 and m[0] == "lwz" and m[1] == "stw":
        ld, st = mem(op[0]), mem(op[1])
        vr0 = op[0].split(",", 1)[0].strip()[1:]
        vr1 = op[1].split(",", 1)[0].strip()[1:]
        if ld and st and vr0 == vr1 and ld.group(2) == st.group(2) and int(ld.group(2)) in (3, 4, 5, 6, 7):
            return ("cp", imm(ld.group(1)), imm(st.group(1)), int(ld.group(2)))
    # --- lwz r3,OFF(rB); addi r3,r3,IMM; blr (deref + offset) ---
    if n == 3 and m[0] == "lwz" and m[1] == "addi" and op[0].startswith("r3, "):
        ld = mem(op[0])
        if ld and int(ld.group(2)) in (3, 4, 5, 6, 7) and op[1].startswith("r3, r3, "):
            return ("da", imm(ld.group(1)), imm(op[1][8:]), int(ld.group(2)))
    # --- lwz r9,OFF(r3); slwi r4,r4,2; lwzx r3,r4,r9; blr (field-pointer indexed read) ---
    if n == 4 and m[0] == "lwz" and m[1] == "slwi" and m[2] == "lwzx":
        ld = mem(op[0])
        sl = re.match(r"r4, r4, (0x[0-9a-fA-F]+|[0-9]+)$", op[1])
        if ld and sl and int(ld.group(2)) == 3 and imm(sl.group(1)) == 2 \
           and op[0].split(",", 1)[0].strip()[1:] == "9" and op[2] == "r3, r4, r9":
            return ("fir", imm(ld.group(1)))
    # --- lwz r0,OFF(r4); stw r0,OFF2(r3); blr (cross-base copy) ---
    if n == 3 and m[0] == "lwz" and m[1] == "stw":
        ld, st = mem(op[0]), mem(op[1])
        vr0 = op[0].split(",", 1)[0].strip()[1:]
        vr1 = op[1].split(",", 1)[0].strip()[1:]
        if ld and st and vr0 == vr1 and int(ld.group(2)) == 4 and int(st.group(2)) == 3:
            return ("cc", imm(ld.group(1)), imm(st.group(1)))
    # --- lwz r9,OFF1(r3); cmpwi r9,0; li r3,0; beqlr; lwz r3,OFF2(r9); blr (null-check getter) ---
    if n == 6 and m[0] == "lwz" and m[1] == "cmpwi" and m[2] == "li" and m[3] == "beqlr" \
       and m[4] == "lwz" and m[5] == "blr":
        ld = mem(op[0])
        ld2 = mem(op[4])
        if ld and ld2 and int(ld.group(2)) == 3 and int(ld2.group(2)) == 9 \
           and op[0].split(",", 1)[0].strip()[1:] == "9" and op[4].split(",", 1)[0].strip()[1:] == "3" \
           and op[1] == "r9, 0" and op[2] == "r3, 0":
            return ("nc", imm(ld.group(1)), imm(ld2.group(1)))
    # --- mr r9,r3; lwz r0,OFF(r9); li r3,1; ori r0,r0,1; stw r0,OFF(r9); blr (flag set + return) ---
    if n == 6 and m[0] == "mr" and m[1] == "lwz" and m[2] == "li" and m[3] == "ori" \
       and m[4] == "stw" and m[5] == "blr":
        ld = mem(op[1])
        st = mem(op[4])
        if ld and st and op[0] == "r9, r3" and op[1].startswith("r0, ") and op[2] == "r3, 1" \
           and op[3] == "r0, r0, 1" and op[4].startswith("r0, ")\
           and int(ld.group(2)) == 9 and int(st.group(2)) == 9 \
           and imm(ld.group(1)) == imm(st.group(1)):
            return ("fs1", imm(ld.group(1)))
    # --- addi r3,r3,BASE; lfs fA,OFF1(r3); stfs fA,0(r4); lfs fB,OFF2(r3); stfs fB,0(r5); blr (float copy pair) ---
    if n == 6 and m[0] == "addi" and m[1] == "lfs" and m[2] == "stfs" and m[3] == "lfs" \
       and m[4] == "stfs" and m[5] == "blr":
        ad = re.match(r"r3, r3, (0x[0-9a-fA-F]+)$", op[0])
        if ad and op[2].endswith("(r4)") and op[4].endswith("(r5)"):
            l1 = mem(op[1])
            l2 = mem(op[3])
            if l1 and l2 and int(l1.group(2)) == 3 and int(l2.group(2)) == 3 \
               and imm(l1.group(1)) % 4 == 0 and imm(l2.group(1)) % 4 == 0 \
               and op[1].split(",", 1)[0].strip() == op[2].split(",", 1)[0].strip() \
               and op[3].split(",", 1)[0].strip() == op[4].split(",", 1)[0].strip():
                return ("fc1", imm(ad.group(1)), imm(l1.group(1)), imm(l2.group(1)))
    # --- stfs f1,OFF(r3); addi r3,r3,OFF; stfs f3,8(r3); stfs f2,4(r3); blr (3-float store) ---
    if n == 5 and m[0] == "stfs" and m[1] == "addi" and m[2] == "stfs" and m[3] == "stfs" \
       and m[4] == "blr":
        s0 = mem(op[0])
        ad = re.match(r"r3, r3, (0x[0-9a-fA-F]+)$", op[1])
        if s0 and ad and int(s0.group(2)) == 3 and imm(s0.group(1)) == imm(ad.group(1)) \
           and imm(s0.group(1)) % 4 == 0 and op[0].startswith("f1, ")\
           and op[2] == "f3, 8(r3)" and op[3] == "f2, 4(r3)":
            return ("fs3", imm(s0.group(1)))
    # --- mtspr SPR,r3; blr (special-purpose register write) ---
    if n == 2 and m[0] == "mtspr" and op[0].endswith(", r3"):
        sp = re.match(r"(0x[0-9a-fA-F]+|[0-9]+), r3$", op[0])
        if sp:
            return ("mts", imm(sp.group(1)))
    # --- mfspr r3,SPR; blr (special-purpose register read) ---
    if n == 2 and m[0] == "mfspr" and op[0].startswith("r3, "):
        sp = re.match(r"r3, (0x[0-9a-fA-F]+|[0-9]+)$", op[0])
        if sp:
            return ("mfs", imm(sp.group(1)))
    # --- lwz r3,OFF(rB); rlwinm r3,r3,SH,MB,ME; blr ---
    if n == 3 and m[0] == "lwz" and m[1] == "rlwinm" and op[0].startswith("r3, "):
        ld = mem(op[0])
        mk = RE_MASK.search(op[1])
        if ld and int(ld.group(2)) in (3, 4, 5, 6, 7) and mk:
            return ("rl", imm(ld.group(1)), int(mk.group(2), 0), int(mk.group(3), 0),
                    int(mk.group(4), 0), int(ld.group(2)))
    # --- lwz rV,OFF(r3); rlwinm rV,rV,0,MB,ME; stw rV,OFF(r3); blr (and-mask store) ---
    if n == 4 and m[0] == "lwz" and m[1] == "rlwinm" and m[2] == "stw":
        ld = mem(op[0])
        st = mem(op[2])
        mk = RE_MASK.search(op[1])
        vr = op[0].split(",", 1)[0].strip()[1:]
        if ld and st and mk and int(ld.group(2)) == 3 and int(st.group(2)) == 3 \
           and imm(ld.group(1)) == imm(st.group(1)) and int(mk.group(2), 0) == 0 \
           and vr == op[2].split(",", 1)[0].strip()[1:]:
            return ("am", imm(ld.group(1)), int(mk.group(3), 0), int(mk.group(4), 0))
    # --- li rX,IMM; stw rV,OFF1(r3); stw rX,OFF2(r3); blr (arg + const stores) ---
    if n == 4 and m[0] == "li" and m[1] == "stw" and m[2] == "stw":
        li = RE_LIS.match(op[0])
        s1, s2 = mem(op[1]), mem(op[2])
        vr1 = op[1].split(",", 1)[0].strip()[1:]
        vr2 = op[2].split(",", 1)[0].strip()[1:]
        if li and s1 and s2 and int(s1.group(2)) == 3 and int(s2.group(2)) == 3 \
           and vr1 != li.group(1) and vr2 == li.group(1) and int(vr1) in (4, 5, 6, 7):
            return ("kv", int(vr1), imm(li.group(2)), imm(s1.group(1)), imm(s2.group(1)))
    # --- stw rV,OFF(r3); li r3,IMM; blr (store arg + return const) ---
    if n == 3 and m[0] == "stw" and m[1] == "li" and op[1].startswith("r3, "):
        st = mem(op[0])
        vr = op[0].split(",", 1)[0].strip()[1:]
        if st and int(st.group(2)) == 3 and int(vr) in (4, 5, 6, 7):
            return ("sr", int(vr), imm(st.group(1)), imm(op[1][4:]))
    # --- stw rV,OFF1(r3); stw rW,OFF2(r3); stw rU,OFF3(r3); blr (three arg stores) ---
    if n == 4 and m[0] == "stw" and m[1] == "stw" and m[2] == "stw":
        s1, s2, s3 = mem(op[0]), mem(op[1]), mem(op[2])
        vr1 = op[0].split(",", 1)[0].strip()[1:]
        vr2 = op[1].split(",", 1)[0].strip()[1:]
        vr3 = op[2].split(",", 1)[0].strip()[1:]
        if s1 and s2 and s3 and int(s1.group(2)) == 3 and int(s2.group(2)) == 3 and int(s3.group(2)) == 3 \
           and len({vr1, vr2, vr3}) == 3 and all(int(v) in (4, 5, 6, 7) for v in (vr1, vr2, vr3)):
            return ("ss3", (int(vr1), imm(s1.group(1))), (int(vr2), imm(s2.group(1))),
                    (int(vr3), imm(s3.group(1))))
    # --- mr rX,r3; lwz r0,OFF(rX); li r3,IMM; rlwinm r0,r0,0,MB,ME; stw r0,OFF(rX); blr ---
    if n == 6 and m[0] == "mr" and m[1] == "lwz" and m[2] == "li" and m[3] == "rlwinm" and m[4] == "stw" and op[2].startswith("r3, "):
        mx = re.match(r"r(\d+), r3$", op[0])
        ld = mem(op[1])
        st = mem(op[4])
        mk = RE_MASK.search(op[3])
        if mx and ld and st and mk and int(mk.group(2), 0) == 0 \
           and int(ld.group(2)) == int(mx.group(1)) and int(st.group(2)) == int(mx.group(1)) \
           and imm(ld.group(1)) == imm(st.group(1)) and op[1].startswith("r0, ") and op[4].startswith("r0, "):
            return ("amr", imm(ld.group(1)), int(mk.group(3), 0), int(mk.group(4), 0), imm(op[2][4:]))
    # --- stw rV1,OFF1(r3); stw rV2,OFF2(r3); blr (two arg stores) ---
    if n == 3 and m[0] == "stw" and m[1] == "stw":
        s1, s2 = mem(op[0]), mem(op[1])
        vr1 = op[0].split(",", 1)[0].strip()[1:]
        vr2 = op[1].split(",", 1)[0].strip()[1:]
        if s1 and s2 and int(s1.group(2)) == 3 and int(s2.group(2)) == 3 \
           and int(vr1) in (4, 5, 6, 7) and int(vr2) in (4, 5, 6, 7) and vr1 != vr2:
            return ("ss", int(vr1), int(vr2), imm(s1.group(1)), imm(s2.group(1)))
    # --- stw rV,OFF(rW); stw rW,OFF(rV); blr (cross-base pointer swap store) ---
    if n == 3 and m[0] == "stw" and m[1] == "stw":
        s1, s2 = mem(op[0]), mem(op[1])
        vr1 = op[0].split(",", 1)[0].strip()[1:]
        vr2 = op[1].split(",", 1)[0].strip()[1:]
        if s1 and s2 and imm(s1.group(1)) == imm(s2.group(1)) \
           and int(s1.group(2)) in (4, 5, 6, 7) and int(s2.group(2)) in (4, 5, 6, 7) \
           and vr1 == s2.group(2) and vr2 == s1.group(2) and vr1 != vr2:
            return ("sx", int(s1.group(2)), int(s2.group(2)), imm(s1.group(1)))
    # --- lwz r3,OFF(rB); slwi/srwi/srawi r3,r3,N; blr ---
    if n == 3 and m[0] == "lwz" and m[1] in ("slwi", "srwi", "srawi") and op[0].startswith("r3, "):
        ld = mem(op[0])
        if ld and int(ld.group(2)) in (3, 4, 5, 6, 7) and op[1].startswith("r3, r3, "):
            return ("sl", m[1], imm(ld.group(1)), imm(op[1][8:]), int(ld.group(2)))
    # --- li rV,IMM; stw rV,OFF1(r3); li rW,IMM2; stw rW,OFF2(r3); blr (kk) ---
    if n == 5 and m[0] == "li" and m[1] == "stw" and m[2] == "li" and m[3] == "stw":
        l1, s1 = RE_LIS.match(op[0]), mem(op[1])
        l2, s2 = RE_LIS.match(op[2]), mem(op[3])
        if l1 and s1 and l2 and s2 and l1.group(1) == op[1].split(",", 1)[0].strip()[1:] \
           and l2.group(1) == op[3].split(",", 1)[0].strip()[1:] \
           and int(s1.group(2)) == 3 and int(s2.group(2)) == 3:
            return ("kk", (imm(l1.group(2)), imm(s1.group(1))),
                    (imm(l2.group(2)), imm(s2.group(1))))
    # --- li rV,IMM1; li rW,IMM2; stw rV,OFF1(r3); stw rW,OFF2(r3); blr (kk2) ---
    if n == 5 and m[0] == "li" and m[1] == "li" and m[2] == "stw" and m[3] == "stw":
        l1, l2 = RE_LIS.match(op[0]), RE_LIS.match(op[1])
        s1, s2 = mem(op[2]), mem(op[3])
        if l1 and l2 and s1 and s2 and l1.group(1) == op[2].split(",", 1)[0].strip()[1:] \
           and l2.group(1) == op[3].split(",", 1)[0].strip()[1:] \
           and int(s1.group(2)) == 3 and int(s2.group(2)) == 3:
            return ("kk2", (imm(l1.group(2)), imm(s1.group(1))),
                    (imm(l2.group(2)), imm(s2.group(1))))
    return None


# ---- C generation ----
SIZE2C = {"lwz": "s32", "lhz": "u16", "lha": "s16", "lbz": "u8", "lwzu": "s32", "lhzu": "u16"}
STORE2C = {"stw": "s32", "sth": "s16", "stb": "s8"}


def fn_name(addr):
    """C symbol name for a function address (SDK name if it has one)."""
    return SDK_NAMES.get(addr, f"fn_{addr:08X}")


def gen_one(addr, kind, p):
    lines = []
    nm = fn_name(addr)
    if kind == "tp":
        tgt = p[0]
        tnm = fn_name(tgt)
        lines.append(f"extern void {tnm}(void);")
        lines.append(f"void {nm}(void) {{ {tnm}(); }}")
    elif kind == "e":
        lines.append(f"void {nm}(void) {{\n}}")
    elif kind == "ks":
        g, val = p
        lines.append(f"extern s32 lbl_{g:08X};")
        lines.append(f"void fn_{addr:08X}(void) {{ lbl_{g:08X} = {val}; }}")
    elif kind == "bg":
        off, immv, cond, a, b = p
        op = "==" if cond == "beqlr" else "!="
        lines.append(f"s32 fn_{addr:08X}(void *o) {{")
        lines.append(f"    if (*(s32 *)((char *)o + 0x{off:X}) {op} {immv}) return {a};")
        lines.append(f"    return {b};")
        lines.append("}")
    elif kind == "bg2":
        off1, off2, immv, cond, a, b = p
        op = "==" if cond == "beqlr" else "!="
        lines.append(f"s32 fn_{addr:08X}(void *o) {{")
        lines.append(f"    if (*(s32 *)(*(s32 *)((char *)o + 0x{off1:X}) + 0x{off2:X}) {op} {immv}) return {a};")
        lines.append(f"    return {b};")
        lines.append("}")
    elif kind == "bga":
        reg, immv, cond, a, b = p
        pos = 1 if reg == 3 else VREG2ARG.get(reg, None)
        if pos is None:
            return None
        dummies = ", ".join("s32 d%d" % i for i in range(1, pos))
        args = "s32 x" + (", " + dummies if dummies else "")
        op = "==" if cond == "beqlr" else "!="
        lines.append(f"s32 fn_{addr:08X}({args}) {{")
        lines.append(f"    if (x {op} {immv}) return {a};")
        lines.append(f"    return {b};")
        lines.append("}")
    elif kind == "os":
        mnem, off, immv = p
        val = immv << 16 if mnem == "oris" else immv
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(u32 *)((char *)o + 0x{off:X}) |= 0x{val:X}u;")
        lines.append("}")
    elif kind == "hc":
        off2, off1 = p
        lines.append(f"u32 fn_{addr:08X}(void *o) {{")
        lines.append(f"    return (*(u16 *)((char *)o + 0x{off2:X}) << 16) | *(u16 *)((char *)o + 0x{off1:X});")
        lines.append("}")
    elif kind == "mb":
        off, mval = p
        # if-form (not !=0 ternary): for single-bit masks ngccc emits
        # `rlwinm` for the ternary but `andi.` for the if-form. Verified.
        lines.append(f"s32 fn_{addr:08X}(void *o) {{")
        lines.append(f"    if (*(u32 *)((char *)o + 0x{off:X}) & 0x{mval:X}u) return 1;")
        lines.append(f"    return 0;")
        lines.append("}")
    elif kind == "mts":
        sp = p[0]
        lines.append(f"void {nm}(u32 v) {{")
        lines.append(f"    __asm__ volatile(\"mtspr 0x{sp:X}, %0\" : : \"r\"(v));")
        lines.append("}")
    elif kind == "mfs":
        sp = p[0]
        lines.append(f"u32 {nm}(void) {{")
        lines.append(f"    u32 r;")
        lines.append(f"    __asm__ volatile(\"mfspr %0, 0x{sp:X}\" : \"=r\"(r));")
        lines.append(f"    return r;")
        lines.append("}")
    elif kind == "c":
        lines.append(f"s32 fn_{addr:08X}(void) {{ return {p[0]}; }}")
    elif kind == "c32":
        g = p[0]
        lines.append(f"extern char lbl_{g:08X}[];")
        lines.append(f"u32 fn_{addr:08X}(void) {{ return (u32)lbl_{g:08X}; }}")
    elif kind == "g":
        ctype = SIZE2C[p[0]]
        pad = bpad(p[2])
        if pad is None:
            return None
        lines.append(f"{ctype} fn_{addr:08X}({pad}void *o) {{")
        lines.append(f"    return *({ctype} *)((char *)o + 0x{p[1]:X});")
        lines.append("}")
    elif kind == "eb":
        pad = bpad(p[1])
        if pad is None:
            return None
        lines.append(f"s32 fn_{addr:08X}({pad}void *o) {{")
        lines.append(f"    return (s8)*(s8 *)((char *)o + 0x{p[0]:X});")
        lines.append("}")
    elif kind == "eh":
        pad = bpad(p[1])
        if pad is None:
            return None
        lines.append(f"s32 fn_{addr:08X}({pad}void *o) {{")
        lines.append(f"    return (s16)*(s16 *)((char *)o + 0x{p[0]:X});")
        lines.append("}")
    elif kind == "neg":
        pad = bpad(p[1])
        if pad is None:
            return None
        lines.append(f"s32 fn_{addr:08X}({pad}void *o) {{")
        lines.append(f"    return -(*(s32 *)((char *)o + 0x{p[0]:X}));")
        lines.append("}")
    elif kind == "not":
        pad = bpad(p[1])
        if pad is None:
            return None
        lines.append(f"s32 fn_{addr:08X}({pad}void *o) {{")
        lines.append(f"    return ~(*(s32 *)((char *)o + 0x{p[0]:X}));")
        lines.append("}")
    elif kind == "p":
        lines.append(f"void *fn_{addr:08X}(void *o) {{ return (char *)o + 0x{p[0]:X}; }}")
    elif kind == "m":
        vr = int(p[0][1:])
        pos = VREG2ARG.get(vr, None)
        if pos is None:
            return None
        dummies = ", ".join("void *d%d" % i for i in range(1, pos))
        args = "void *o" + (", " + dummies if dummies else "")
        lines.append(f"void *fn_{addr:08X}({args}) {{ return o; }}")
    elif kind == "s":
        mnem, vr, off, br = p
        if int(br) != 3:
            return None  # setters with non-r3 base are rare; skip
        ctype = STORE2C[mnem]
        pos = VREG2ARG.get(int(vr), None)
        if pos is None:
            return None
        dummies = ", ".join("s32 d%d" % i for i in range(2, pos))
        args = "void *o" + (", " + dummies if dummies else "") + f", {ctype} v"
        lines.append(f"void fn_{addr:08X}({args}) {{")
        lines.append(f"    *({ctype} *)((char *)o + 0x{off:X}) = v;")
        lines.append("}")
    elif kind == "k":
        val, off = p
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off:X}) = {val};")
        lines.append("}")
    elif kind == "kret":
        val, off, ret = p
        lines.append(f"s32 fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off:X}) = {val};")
        lines.append(f"    return {ret};")
        lines.append("}")
    elif kind == "k2":
        val, off1, off2 = p
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off1:X}) = {val};")
        lines.append(f"    *(s32 *)((char *)o + 0x{off2:X}) = {val};")
        lines.append("}")
    elif kind == "k3":
        val, off1, off2, off3 = p
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off1:X}) = {val};")
        lines.append(f"    *(s32 *)((char *)o + 0x{off2:X}) = {val};")
        lines.append(f"    *(s32 *)((char *)o + 0x{off3:X}) = {val};")
        lines.append("}")
    elif kind == "cp":
        off1, off2, br = p
        if int(br) != 3:
            return None
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off2:X}) = *(s32 *)((char *)o + 0x{off1:X});")
        lines.append("}")
    elif kind == "da":
        off, add, br = p
        pad = bpad(br)
        if pad is None:
            return None
        lines.append(f"void *fn_{addr:08X}({pad}void *o) {{")
        lines.append(f"    return (char *)*(void **)((char *)o + 0x{off:X}) + 0x{add:X};")
        lines.append("}")
    elif kind == "fir":
        off = p[0]
        lines.append(f"void *fn_{addr:08X}(void *o, s32 i) {{")
        lines.append(f"    void **a = *(void ***)((char *)o + 0x{off:X});")
        lines.append(f"    return a[i];")
        lines.append("}")
    elif kind == "cc":
        off1, off2 = p
        lines.append(f"void fn_{addr:08X}(void *o, void *s) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off2:X}) = *(s32 *)((char *)s + 0x{off1:X});")
        lines.append("}")
    elif kind == "rl":
        off, sh, mb, me, br = p
        pad = bpad(br)
        if pad is None:
            return None
        mask = hw_mask(mb, me)
        if sh == 0:
            lines.append(f"s32 fn_{addr:08X}({pad}void *o) {{")
            lines.append(f"    return (s32)((*(u32 *)((char *)o + 0x{off:X})) & 0x{mask:X}u);")
            lines.append("}")
        elif mask & (mask - 1) == 0:
            # single-bit mask with rotation: use a 1-bit bitfield read
            L = (32 - sh) % 32  # LSB position of the field
            P = 31 - L          # pad bits above it (MSB-first packing)
            padb = f"unsigned pad : {P}; " if P else ""
            lines.append(f"s32 fn_{addr:08X}({pad}void *o) {{")
            lines.append(f"    struct S {{ {padb}unsigned f : 1; }};")
            lines.append(f"    return ((struct S *)((char *)o + 0x{off:X}))->f;")
            lines.append("}")
        else:
            lines.append(f"s32 fn_{addr:08X}({pad}void *o) {{")
            lines.append(f"    return (s32)((*(u32 *)((char *)o + 0x{off:X})) << {sh} & 0x{mask:X}u);")
            lines.append("}")
    elif kind == "am":
        off, mb, me = p
        mask = hw_mask(mb, me)
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(u32 *)((char *)o + 0x{off:X}) &= 0x{mask:X}u;")
        lines.append("}")
    elif kind == "kv":
        vr, val, off1, off2 = p
        pos = VREG2ARG.get(vr, None)
        if pos is None:
            return None
        dummies = ", ".join("s32 d%d" % i for i in range(2, pos))
        args = "void *o" + (", " + dummies if dummies else "") + ", s32 v"
        lines.append(f"void fn_{addr:08X}({args}) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off1:X}) = v;")
        lines.append(f"    *(s32 *)((char *)o + 0x{off2:X}) = {val};")
        lines.append("}")
    elif kind == "ss":
        vr1, vr2, off1, off2 = p
        p1, p2 = VREG2ARG.get(vr1), VREG2ARG.get(vr2)
        if p1 is None or p2 is None:
            return None
        maxp = max(p1, p2)
        argnames = {}
        arglist = ["void *o"]
        for i in range(2, maxp + 1):
            if i == p1:
                argnames[p1] = "v1"
                arglist.append("s32 v1")
            elif i == p2:
                argnames[p2] = "v2"
                arglist.append("s32 v2")
            else:
                arglist.append(f"s32 d{i}")
        # mwcc emits the two stores in REVERSE source order
        lines.append(f"void fn_{addr:08X}({', '.join(arglist)}) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off2:X}) = {argnames[p2]};")
        lines.append(f"    *(s32 *)((char *)o + 0x{off1:X}) = {argnames[p1]};")
        lines.append("}")
    elif kind == "sr":
        vr, off, ret = p
        pos = VREG2ARG.get(vr, None)
        if pos is None:
            return None
        dummies = ", ".join("s32 d%d" % i for i in range(2, pos))
        args = "void *o" + (", " + dummies if dummies else "") + ", s32 v"
        lines.append(f"s32 fn_{addr:08X}({args}) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{off:X}) = v;")
        lines.append(f"    return {ret};")
        lines.append("}")
    elif kind == "ss3":
        (vr1, off1), (vr2, off2), (vr3, off3) = p
        reg2arg = {}
        arglist = ["void *o"]
        for i, (vr, off) in enumerate(sorted(((vr1, off1), (vr2, off2), (vr3, off3)))):
            pos = VREG2ARG.get(vr, None)
            if pos is None:
                return None
            reg2arg[pos] = (vr, off)
        maxp = max(reg2arg)
        anames = {}
        for i in range(2, maxp + 1):
            if i in reg2arg:
                anames[i] = f"v{i}"
                arglist.append(f"s32 v{i}")
            else:
                arglist.append(f"s32 d{i}")
        # mwcc emits the three stores in a scrambled order; the source form
        # `off_ascending = arg_by_reg` reproduces the original bytes (verified)
        lines.append(f"void fn_{addr:08X}({', '.join(arglist)}) {{")
        for (vr, off) in sorted(((vr1, off1), (vr2, off2), (vr3, off3)), key=lambda t: t[1]):
            lines.append(f"    *(s32 *)((char *)o + 0x{off:X}) = {anames[VREG2ARG[vr]]};")
        lines.append("}")
    elif kind == "amr":
        off, mb, me, ret = p
        mask = hw_mask(mb, me)
        lines.append(f"s32 fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(u32 *)((char *)o + 0x{off:X}) &= 0x{mask:X}u;")
        lines.append(f"    return {ret};")
        lines.append("}")
    elif kind == "sx":
        br1, br2, off = p  # br1 = base of store 1 (== value reg of store 2)
        # dummy first arg so a/b land in r4/r5 like the original
        lines.append(f"void fn_{addr:08X}(void *d0, void *a, void *b) {{")
        lines.append(f"    *(s32 *)((char *)a + 0x{off:X}) = (s32)b;")
        lines.append(f"    *(s32 *)((char *)b + 0x{off:X}) = (s32)a;")
        lines.append("}")
    elif kind == "sl":
        mnem, off, n, br = p
        pad = bpad(br)
        if pad is None:
            return None
        lines.append(f"s32 fn_{addr:08X}({pad}void *o) {{")
        if mnem == "slwi":
            lines.append(f"    return *(s32 *)((char *)o + 0x{off:X}) << {n};")
        else:
            lines.append(f"    return (s32)((u32)*(s32 *)((char *)o + 0x{off:X}) >> {n});")
        lines.append("}")
    elif kind == "lg":
        g = p[0]
        lines.append(f"extern s32 lbl_{g:08X};")
        lines.append(f"s32 fn_{addr:08X}(void) {{ return lbl_{g:08X}; }}")
    elif kind == "gf":
        g = p[0]
        lines.append(f"extern float lbl_{g:08X};")
        lines.append(f"float fn_{addr:08X}(void) {{ return lbl_{g:08X}; }}")
    elif kind == "gs":
        g = p[0]
        lines.append(f"extern float lbl_{g:08X};")
        lines.append(f"void fn_{addr:08X}(float v) {{ lbl_{g:08X} = v; }}")
    elif kind == "gd":
        g = p[0]
        lines.append(f"extern s32 lbl_{g:08X};")
        lines.append(f"void fn_{addr:08X}(void) {{ lbl_{g:08X}--; }}")
    elif kind == "g64":
        g = p[0]
        lines.append(f"extern u64 lbl_{g:08X};")
        lines.append(f"u64 fn_{addr:08X}(void) {{ return lbl_{g:08X}; }}")
    elif kind == "gcs":
        g, val, ret = p
        lines.append(f"extern s32 lbl_{g:08X};")
        lines.append(f"s32 fn_{addr:08X}(void) {{ lbl_{g:08X} = {val}; return {ret}; }}")
    elif kind == "gbt":
        g = p[0]
        lines.append(f"extern s32 lbl_{g:08X};")
        lines.append(f"s32 fn_{addr:08X}(void) {{ if (lbl_{g:08X}) return 1; return 0; }}")
    elif kind == "ginc":
        g = p[0]
        lines.append(f"extern s32 lbl_{g:08X};")
        lines.append(f"void fn_{addr:08X}(void) {{ lbl_{g:08X}++; }}")
    elif kind == "ffs":
        off = p[0]
        lines.append(f"void fn_{addr:08X}(void *o, float v) {{")
        lines.append(f"    *(float *)((char *)o + 0x{off:X}) = v;")
        lines.append("}")
    elif kind == "ffg":
        off, br = p
        pad = bpad(br)
        if pad is None:
            return None
        lines.append(f"float fn_{addr:08X}({pad}void *o) {{")
        lines.append(f"    return *(float *)((char *)o + 0x{off:X});")
        lines.append("}")
    elif kind == "ai":
        off = p[0]
        lines.append(f"typedef struct {{ char _pad[0x{off:X}]; s32 _arr[64]; }} S_{addr:08X};")
        lines.append(f"s32 fn_{addr:08X}(S_{addr:08X} *o, s32 i) {{")
        lines.append(f"    return o->_arr[i];")
        lines.append("}")
    elif kind == "bt":
        off = p[0]
        lines.append(f"s32 fn_{addr:08X}(void *o, s32 i) {{")
        lines.append(f"    u32 m = 1u << i;")
        lines.append(f"    if (*(u32 *)((char *)o + 0x{off:X}) & m) return 1;")
        lines.append(f"    return 0;")
        lines.append("}")
    elif kind == "bs":
        off = p[0]
        lines.append(f"void fn_{addr:08X}(void *o, s32 i) {{")
        lines.append(f"    *(u32 *)((char *)o + 0x{off:X}) |= 1u << i;")
        lines.append("}")
    elif kind == "bf":
        v = p[0]
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    s8 v = {v};")
        lines.append(f"    ((s8 *)o)[0] = v; ((s8 *)o)[1] = v; ((s8 *)o)[2] = v; ((s8 *)o)[3] = v;")
        lines.append("}")
    elif kind == "fm":
        off0, off1 = p  # orig: lfs f0,OFF0; lfs f1,OFF1; fmuls f1,f0,f1
        # mwcc loads the SECOND source operand into f0 first, so write the
        # product with off1 as the left operand to reproduce the load order.
        lines.append(f"float fn_{addr:08X}(void *o) {{")
        lines.append(f"    return *(float *)((char *)o + 0x{off1:X}) * *(float *)((char *)o + 0x{off0:X});")
        lines.append("}")
    elif kind == "cos":
        off, val = p
        lines.append(f"void fn_{addr:08X}(void *o, s32 v) {{")
        lines.append(f"    if (v) *(u32 *)((char *)o + 0x{off:X}) |= 0x{val:X}u;")
        lines.append("}")
    elif kind == "ifs":
        off = p[0]
        lines.append(f"void fn_{addr:08X}(void *o, s32 i, float v) {{")
        lines.append(f"    float *a = *(float **)((char *)o + 0x{off:X});")
        lines.append(f"    a[i * 3 + 1] = v;")
        lines.append("}")
    elif kind == "ifg":
        off = p[0]
        lines.append(f"float fn_{addr:08X}(void *o, s32 i) {{")
        lines.append(f"    float *a = *(float **)((char *)o + 0x{off:X});")
        lines.append(f"    return a[i * 3 + 1];")
        lines.append("}")
    elif kind == "ifsz":
        off = p[0]
        lines.append(f"void fn_{addr:08X}(void *o, s32 i, float v) {{")
        lines.append(f"    float *a = *(float **)((char *)o + 0x{off:X});")
        lines.append(f"    a[i * 3] = v;")
        lines.append("}")
    elif kind == "if2":
        off = p[0]
        lines.append(f"void fn_{addr:08X}(void *o, s32 i, float v) {{")
        lines.append(f"    float *a = *(float **)((char *)o + 0x{off:X});")
        lines.append(f"    a[i * 3 + 2] = v;")
        lines.append("}")
    elif kind == "gz":
        off1, off2 = p
        lines.append(f"s32 fn_{addr:08X}(void *o) {{")
        lines.append(f"    void *p = *(void **)((char *)o + 0x{off1:X});")
        lines.append(f"    if (p) *(s32 *)((char *)p + 0x{off2:X}) = 0;")
        lines.append(f"    return 1;")
        lines.append("}")
    elif kind == "nc":
        off1, off2 = p
        lines.append(f"void *fn_{addr:08X}(void *o) {{")
        lines.append(f"    void *p = *(void **)((char *)o + 0x{off1:X});")
        lines.append(f"    if (!p) return 0;")
        lines.append(f"    return *(void **)((char *)p + 0x{off2:X});")
        lines.append("}")
    elif kind == "fs1":
        off = p[0]
        lines.append(f"s32 fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(u32 *)((char *)o + 0x{off:X}) |= 1;")
        lines.append(f"    return 1;")
        lines.append("}")
    elif kind == "fc1":
        base, off1, off2 = p
        lines.append(f"void fn_{addr:08X}(void *o, float *p, float *q) {{")
        lines.append(f"    float *b = (float *)((char *)o + 0x{base:X});")
        lines.append(f"    *p = b[0x{off1:X} / 4];")
        lines.append(f"    *q = b[0x{off2:X} / 4];")
        lines.append("}")
    elif kind == "fs3":
        off = p[0]
        lines.append(f"void fn_{addr:08X}(void *o, float a, float b, float c) {{")
        lines.append(f"    float *p = (float *)((char *)o + 0x{off:X});")
        lines.append(f"    p[0] = a; p[1] = b; p[2] = c;")
        lines.append("}")
    elif kind == "pt":
        g, t = p
        lines.append(f"extern s32 lbl_{g:08X};")
        lines.append(f"extern void *lbl_{t:08X}[];")
        lines.append(f"void *fn_{addr:08X}(void) {{ return lbl_{t:08X}[lbl_{g:08X}]; }}")
    elif kind == "ptf":
        g, t, fld = p
        lines.append(f"extern s32 lbl_{g:08X};")
        lines.append(f"extern void *lbl_{t:08X}[];")
        lines.append(f"s32 fn_{addr:08X}(void) {{")
        lines.append(f"    return *(s32 *)((char *)lbl_{t:08X}[lbl_{g:08X}] + 0x{fld:X});")
        lines.append("}")
    elif kind == "kk":
        (v1, o1), (v2, o2) = p
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{o1:X}) = {v1};")
        lines.append(f"    *(s32 *)((char *)o + 0x{o2:X}) = {v2};")
        lines.append("}")
    elif kind == "kk2":
        (v1, o1), (v2, o2) = p
        lines.append(f"void fn_{addr:08X}(void *o) {{")
        lines.append(f"    *(s32 *)((char *)o + 0x{o1:X}) = {v1};")
        lines.append(f"    *(s32 *)((char *)o + 0x{o2:X}) = {v2};")
        lines.append("}")
    lines.append("")
    return lines


# ---- compile + masked compare ----
from elftools.elf.elffile import ELFFile

R_PPC_ADDR16_LO, R_PPC_ADDR16_HA, R_PPC_REL14, R_PPC_REL24 = 4, 6, 11, 10

# wibo occasionally deadlocks when many instances run concurrently, wedging the
# whole `subprocess.run` forever and stalling every bulk sweep that shares the
# pool. A normal compile is ~0.2s, so a hard cap turns a rare hang into one FAIL
# row instead of an unbounded stall. Override with NGCCC_TIMEOUT (seconds).
COMPILE_TIMEOUT = float(os.environ.get("NGCCC_TIMEOUT", "120"))

# A draft's `// FLAG:` line is free-form prose, so a naive "every token starting
# with -" parse picks up garbage. fn_8026EAAC's line is
#   // FLAG: -fno-regmove (trialed: ..., -fno-regmove+pin 30/191, ...)
# which yielded the tokens `-fno-regmove`, `-fno-regmove+pin` and a bare `-`;
# ngccc then aborted on the latter two ("unknown command line option") and the
# draft was reported as a bare FAIL — invisible to every score ranking. Only
# accept well-formed flag tokens, and never `+` (an informal "variant+pin"
# name, not a compiler option).
FLAG_TOKEN_RE = re.compile(r"^-[A-Za-z][A-Za-z0-9=,._/:-]*$")


def draft_flags(text):
    """Per-object flags recorded in a WIP draft's header.

    Single source of truth for every tool that compiles a draft: promote_wip,
    test_wip_drafts, br_targets, store_order_search, stmt_perm_search,
    which_words and want_vs_got all need the SAME answer, or a draft is scored
    against a different program depending on which tool you asked.

    Two rules:
      * only well-formed flag tokens from `// FLAG:` / `// extra_cflags:`
        lines (see FLAG_TOKEN_RE for why), and
      * a body that touches the paired-single interface (`__ps_t` or
        `__builtin_ps_*`) ALWAYS needs `-mps-float`, even when the header
        forgot to say so — otherwise the whole PS population is built (and
        diffed) as scalar code.
    """
    flags = []
    for line in text.splitlines()[:120]:
        m = re.match(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", line)
        if m:
            flags.extend(t for t in m.group(1).replace(",", " ").split()
                         if FLAG_TOKEN_RE.match(t))
    if ("__ps_t" in text or "__builtin_ps_" in text) and "-mps-float" not in flags:
        flags.append("-mps-float")
    return list(dict.fromkeys(flags))


def compile_fn(addr, src, extra_flags=None):
    """Compile draft body for fn at addr; returns (got_bytes, reloc_masks).
    extra_flags appends to the standard ngccc flags (e.g. ["-mps-float"] for
    paired-single drafts — per-object only, never global)."""
    fname = f"fn_{addr:08X}"
    # LEAF_TMPDIR lets parallel callers (sweeps, permutation searches) give each
    # worker its own scratch dir.  Without it two processes compiling the same
    # address race on one .c/.o pair and read a half-written object.
    tmpdir = os.environ.get("LEAF_TMPDIR") or "/tmp/leaf"
    sp = f"{tmpdir}/{fname}.c"
    op = f"{tmpdir}/{fname}.o"
    os.makedirs(tmpdir, exist_ok=True)
    with open(sp, "w") as f:
        f.write('#include "types.h"\n' + src)
    env = dict(os.environ)
    env["SN_NGC_PATH"] = C_DIR
    flags = ["-O2", "-G0", "-mcpu=750", "-fno-common",
             "-I", f"{ROOT}/include"] + list(extra_flags or [])
    try:
        r = subprocess.run(
            [WIBO, f"{C_DIR}/ngccc.exe"] + flags + ["-c", sp, "-o", op],
            cwd=ROOT, capture_output=True, text=True, env=env,
            timeout=COMPILE_TIMEOUT)
    except subprocess.TimeoutExpired:
        return None, f"compile timeout after {COMPILE_TIMEOUT:.0f}s (wibo hang?)"
    if r.returncode != 0:
        return None, r.stderr[:200]
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
                    # REL24: mask = opcode(6) + AA + LK (0xFC000003); REL14: keep
                    # opcode+BO+BI (0xFFFF0003). The old 0xFFFF0003 for REL24 kept
                    # the top 10 bits of the displacement, which break backward
                    # branches (sign-extended LI in the upper word bits).
                    m = 0xFFFF0003 if typ == R_PPC_REL14 else 0xFC000003
                    masks[insn] = masks.get(insn, 0xFFFFFFFF) & m
                elif typ in (R_PPC_ADDR16_LO, R_PPC_ADDR16_HA):
                    insn = (p - 2) & ~3
                    masks[insn] = masks.get(insn, 0xFFFFFFFF) & 0xFFFF0000
    with open(op, "rb") as f:
        sec = ELFFile(f).get_section_by_name(".text")
        got = sec.data() if sec is not None else b""
    return got, masks


# ---- main loop ----
def main():
    print(f"skipping {len(matched)} matched; {len(fns)} total fns")
    results = []   # (addr, kind, p, size_bytes)
    uncl = {}
    for start in fns:
        if start in matched or start in PARKED or start < t_addr or start >= t_addr + t_size:
            continue
        cls = classify(start)
        if cls is None:
            continue
        kind = cls[0]
        p = cls[1:]
        # Trampolines only link when the target function is already decompiled
        # (its src file exists and defines the fn_* symbol).
        if kind == "tp" and not os.path.isfile(f"{ROOT}/src/fn_{p[0]:08X}.c"):
            continue
        # Global-access kinds: skip addresses in hardware/IPL regions (no ELF
        # symbol exists for MMIO at 0xCC00xxxx, IPL at 0x80000xxx, etc.)
        if kind in ("gf", "gs", "gd", "g64", "gcs", "gbt", "ginc", "lg", "ks", "c32"):
            g = p[0]
            if 0xCC000000 <= g < 0xCC010000 or 0x80000000 <= g < 0x80004000 \
               or 0xFFF00000 <= g < 0xFFFFFFFF:
                continue
        lines = gen_one(start, kind, p)
        if lines is None:
            uncl.setdefault((kind, str(p)), []).append(start)
            continue
        ins = insns_at(start)
        try:
            e = [x.mnemonic for x in ins].index("blr")
        except ValueError:
            continue
        size = (e + 1) * 4
        orig = d[t_off + (start - t_addr): t_off + (start - t_addr) + size]

        def try_src(src):
            got, masks = compile_fn(start, src)
            if got is None or len(got) < size:
                return False
            for i in range(0, size, 4):
                ow = int.from_bytes(orig[i:i + 4], "big")
                gw = int.from_bytes(got[i:i + 4], "big")
                if (ow & masks.get(i, 0xFFFFFFFF)) != (gw & masks.get(i, 0xFFFFFFFF)):
                    return False
            return True

        variants = ["\n".join(lines)]
        # k2/k3: try all store-order permutations (ngccc keeps source order)
        if kind in ("k2", "k3"):
            import itertools
            offs = p[1:]
            for perm in itertools.permutations(range(len(offs))):
                if perm == tuple(range(len(offs))):
                    continue
                ol = ["void fn_{addr:08X}(void *o) {{".format(addr=start)]
                for i in perm:
                    ol.append(f"    *(s32 *)((char *)o + 0x{offs[i]:X}) = {p[0]};")
                ol.append("}")
                variants.append("\n".join(ol))
        # ss: also try the natural (non-reversed) source order
        if kind == "ss":
            vr1, vr2, off1, off2 = p
            p1, p2 = VREG2ARG.get(vr1), VREG2ARG.get(vr2)
            if p1 is not None and p2 is not None:
                maxp = max(p1, p2)
                argnames = {}
                arglist = ["void *o"]
                for i in range(2, maxp + 1):
                    if i == p1:
                        argnames[p1] = "v1"; arglist.append("s32 v1")
                    elif i == p2:
                        argnames[p2] = "v2"; arglist.append("s32 v2")
                    else:
                        arglist.append(f"s32 d{i}")
                ol = [f"void fn_{start:08X}({', '.join(arglist)}) {{"]
                ol.append(f"    *(s32 *)((char *)o + 0x{off1:X}) = {argnames[p1]};")
                ol.append(f"    *(s32 *)((char *)o + 0x{off2:X}) = {argnames[p2]};")
                ol.append("}")
                variants.append("\n".join(ol))
        # ss3: also try descending-offset and emit-order source variants
        if kind == "ss3":
            (vr1, off1), (vr2, off2), (vr3, off3) = p
            reg2arg = {}
            for vr, off in ((vr1, off1), (vr2, off2), (vr3, off3)):
                reg2arg[VREG2ARG[vr]] = (vr, off)
            maxp = max(reg2arg)
            arglist = ["void *o"]
            for i in range(2, maxp + 1):
                arglist.append(f"s32 v{i}" if i in reg2arg else f"s32 d{i}")
            orders = []
            # desc: descending offsets
            orders.append(sorted(((vr1, off1), (vr2, off2), (vr3, off3)), key=lambda t: -t[1]))
            # emit: original emission order
            orders.append([(vr1, off1), (vr2, off2), (vr3, off3)])
            for order in orders:
                ol = [f"void fn_{start:08X}({', '.join(arglist)}) {{"]
                for vr, off in order:
                    ol.append(f"    *(s32 *)((char *)o + 0x{off:X}) = v{VREG2ARG[vr]};")
                ol.append("}")
                variants.append("\n".join(ol))
        # sx: also try the reversed store order
        if kind == "sx":
            br1, br2, off = p
            ol = [f"void fn_{start:08X}(void *d0, void *a, void *b) {{"]
            ol.append(f"    *(s32 *)((char *)b + 0x{off:X}) = (s32)a;")
            ol.append(f"    *(s32 *)((char *)a + 0x{off:X}) = (s32)b;")
            ol.append("}")
            variants.append("\n".join(ol))

        ok = False
        matched_src = variants[0]
        for src in variants:
            if try_src(src):
                ok = True
                matched_src = src
                break
        if ok:
            results.append((start, kind, p, size, matched_src))
        else:
            uncl.setdefault(("DIFF", kind, str(p)), []).append(start)
            if kind == "c32" and len(uncl[("DIFF", kind, str(p))]) <= 2:
                dbg = insns_at(start)
                print(f"  [dbg] c32 DIFF {start:#x}: " + "; ".join(f"{x.mnemonic} {x.op_str}" for x in dbg[:4]))

    print(f"\n=== EXACT: {len(results)} ===")
    for a, k, p, sz, msrc in sorted(results):
        print(f"  0x{a:08X} {k} {p} ({sz}B)")
    print(f"\n=== unclassified/DIFF: {sum(len(v) for v in uncl.values())} ===")
    for key, lst in sorted(uncl.items(), key=lambda kv: -len(kv[1]))[:15]:
        print(f"  {key}: x{len(lst)}")

    # ---- write src files ----
    if results:
        for a, k, p, sz, msrc in results:
            fname = f"fn_{a:08X}"
            e = a + sz
            with open(f"{ROOT}/src/{fname}.c", "w") as f:
                f.write("// Auto-generated from tools/gen_leaves.py\n"
                        + f"// range 0x{a:X}-0x{e:X} ({sz}B). Byte-identical.\n"
                        + '#include "types.h"\n'
                        + msrc)
        print(f"\nwrote {len(results)} files in src/")
        print("\nSPLIT RANGES:")
        for a, k, p, sz, msrc in sorted(results):
            print(f"\t.text       start:0x{a:X} end:0x{a + sz:X}")


if __name__ == "__main__":
    main()
