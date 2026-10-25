#!/usr/bin/env python3
"""Generate WIP (non-matching) draft C for EVERY unmatched function in the
DOL. Drafts are inert: written to src/wip/, registered in WIP.md, NEVER
registered in splits.txt / configure.py, so the build stays byte-identical
and objdiff progress stays honest.

Sources of draft C, in order:
  1. gen_leaves.classify() + gen_one()  -> real best-guess C for the ~66
     recognized leaf families (even when the compiler can't reproduce the
     exact bytes — drafts don't need to match).
  2. New family matchers for the top "parked" families from the survey:
     subfic/adde bool idiom, conditional stores, HW-register access, etc.
3. Fallback: a bare documented stub (address/size marker only, no
      disassembly — repo policy: no game assembly in comments).

Usage:  tools/venv/bin/python tools/gen_wip_drafts.py [--max-size N]
"""
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl

ROOT = gl.ROOT
WIP_DIR = f"{ROOT}/src/wip"
REG = f"{ROOT}/WIP.md"

MAX_DISASM = 48  # cap the comment disasm for big functions

# ---------------------------------------------------------------------------
# new matchers for parked survey families (all produce best-guess C)
# ---------------------------------------------------------------------------

def match_survey(start):
    """Return (body_lines, family) or (None, None) for the top parked
    families that classify() doesn't cover."""
    ins = gl.insns_at(start, count=MAX_DISASM)
    m = [x.mnemonic for x in ins]
    op = [x.op_str for x in ins]
    if not m:
        return None, None
    try:
        e = m.index("blr")
    except ValueError:
        e = len(m) - 1
    m, op = m[:e + 1], op[:e + 1]
    n = len(m)
    nm = gl.fn_name(start)
    lines = []

    def mem(o):
        return gl.RE_OFF.search(o)

    # --- lwz r3,OFF(r3); xori r3,r3,M; subfic r0,r3,0; adde r3,r0,r3; blr
    #     (x ^ M) == 0 bool idiom (GC compiler emits subfic/adde for !=0 checks)
    if n == 5 and m[0] == "lwz" and m[1] == "xori" and m[2] == "subfic" \
       and m[3] == "adde" and op[0].startswith("r3, ") and op[2] == "r0, r3, 0" \
       and op[3] == "r3, r0, r3":
        ld = mem(op[0])
        if ld and int(ld.group(2)) == 3 and op[1].startswith("r3, r3, "):
            lines.append(f"s32 {nm}(void *o) {{")
            lines.append(f"    return (*(s32 *)((char *)o + 0x{gl.imm(ld.group(1)):X}) ^ {gl.imm(op[1][7:])}) == 0;")
            lines.append("}")
            return lines, "s1"
    # --- lwz r3,OFF(r3); subfic r0,r3,0; adde r3,r0,r3; blr (x==0 bool)
    if n == 4 and m[0] == "lwz" and m[1] == "subfic" and m[2] == "adde" \
       and op[0].startswith("r3, ") and op[1] == "r0, r3, 0" and op[2] == "r3, r0, r3":
        ld = mem(op[0])
        if ld and int(ld.group(2)) == 3:
            lines.append(f"s32 {nm}(void *o) {{")
            lines.append(f"    return *(s32 *)((char *)o + 0x{gl.imm(ld.group(1)):X}) == 0;")
            lines.append("}")
            return lines, "s2"
    # --- lis rX,HA; lwz r3,LO(rX); xori r3,r3,M; subfic r0,r3,0; adde r3,r0,r3; blr
    if n == 6 and m[0] == "lis" and m[1] == "lwz" and m[2] == "xori" \
       and m[3] == "subfic" and m[4] == "adde" and op[2].startswith("r3, r3, "):
        li = gl.RE_LIS.match(op[0])
        lo = mem(op[1])
        if li and lo and int(lo.group(2)) == int(li.group(1)) \
           and op[3] == "r0, r3, 0" and op[4] == "r3, r0, r3":
            g = ((gl.imm(li.group(2)) << 16) + gl.imm(lo.group(1))) & 0xFFFFFFFF
            lines.append(f"extern s32 lbl_{g:08X};")
            lines.append(f"s32 {nm}(void) {{")
            lines.append(f"    return (lbl_{g:08X} ^ {gl.imm(op[2][7:])}) == 0;")
            lines.append("}")
            return lines, "s3"
    # --- lwz rD,OFF1(r3); cmpwi rD,C; bne L; stw r5,OFF2(r3); L: blr (cond store)
    if n == 5 and m[0] == "lwz" and m[1] == "cmpwi" and m[2] == "bne" \
       and m[3] == "stw":
        dr = op[0].split(",", 1)[0].strip()[1:]
        cm = re.match(rf"r{dr}, (-?(?:0x)?[0-9a-fA-F]+)$", op[1])
        ld = mem(op[0])
        st = mem(op[3])
        if ld and st and cm and int(ld.group(2)) == 3 and int(st.group(2)) == 3 \
           and op[3].split(",", 1)[0].strip()[1:] == "5":
            lines.append(f"void {nm}(void *o, s32 v) {{")
            lines.append(f"    if (*(s32 *)((char *)o + 0x{gl.imm(ld.group(1)):X}) == {gl.imm(cm.group(1))})")
            lines.append(f"        *(s32 *)((char *)o + 0x{gl.imm(st.group(1)):X}) = v;")
            lines.append("}")
            return lines, "cs"
    # --- lis rX,HA; stb/sth/stw r3,LO(rX); blr (HW register store)
    if n == 3 and m[0] == "lis" and m[1] in ("stb", "sth", "stw") and m[2] == "blr":
        li = gl.RE_LIS.match(op[0])
        lo = mem(op[1])
        if li and lo and int(lo.group(2)) == int(li.group(1)):
            g = ((gl.imm(li.group(2)) << 16) + gl.imm(lo.group(1))) & 0xFFFFFFFF
            ctype = {"stb": "u8", "sth": "u16", "stw": "u32"}[m[1]]
            lines.append(f"void {nm}({ctype} v) {{")
            lines.append(f"    *(volatile {ctype} *)0x{g:08X} = v;")
            lines.append("}")
            return lines, "hws"
    # --- lis rX,HA; lhz/lwz rD,LO(rX); rlwinm r3,rD,0,MB,ME; blr (HW reg read)
    if n == 4 and m[0] == "lis" and m[1] in ("lhz", "lwz") and m[2] == "rlwinm":
        li = gl.RE_LIS.match(op[0])
        lo = mem(op[1])
        mk = re.match(r"r3, r(\d+), 0, (0x[0-9a-fA-F]+|[0-9]+), (0x[0-9a-fA-F]+|[0-9]+)$", op[2])
        if li and lo and mk and int(lo.group(2)) == int(li.group(1)):
            src = mk.group(1)
            if op[1].split(",", 1)[0].strip()[1:] == src:
                g = ((gl.imm(li.group(2)) << 16) + gl.imm(lo.group(1))) & 0xFFFFFFFF
                mask = gl.hw_mask(int(mk.group(2), 0), int(mk.group(3), 0))
                ctype = "u16" if m[1] == "lhz" else "u32"
                lines.append(f"u32 {nm}(void) {{")
                lines.append(f"    return (*(volatile {ctype} *)0x{g:08X}) & 0x{mask:X}u;")
                lines.append("}")
                return lines, "hwr"
    # --- mr r9,r3; li r0,V; stb r0,3(r9); stb r0,0(r9); stb r0,1(r9); stb r0,2(r9); blr
    if n == 7 and m[0] == "mr" and m[1] == "li" and m[2:6] == ["stb", "stb", "stb", "stb"]:
        mx = re.match(r"r(\d+), r3$", op[0])
        if mx and op[1].startswith("r0, "):
            vr = mx.group(1)
            offs = [mem(o) for o in op[2:6]]
            if all(o and o.group(2) == vr for o in offs) \
               and sorted(gl.imm(o.group(1)) for o in offs) == [0, 1, 2, 3]:
                val = gl.imm(op[1][4:]) & 0xFF
                lines.append(f"void {nm}(void *o) {{")
                lines.append(f"    *(u8 *)((char *)o + 0) = 0x{val:02X};")
                lines.append(f"    *(u8 *)((char *)o + 1) = 0x{val:02X};")
                lines.append(f"    *(u8 *)((char *)o + 2) = 0x{val:02X};")
                lines.append(f"    *(u8 *)((char *)o + 3) = 0x{val:02X};")
                lines.append("}")
                return lines, "bf4"
    # --- lwz r3,OFF(r13); blr  (r13/SDA2 global read)
    if n == 2 and m[0] == "lwz" and op[0].endswith("(r13)"):
        ld = mem(op[0])
        if ld:
            off = gl.imm(ld.group(1))
            lines.append(f"s32 {nm}(void) {{")
            lines.append(f"    s32 r;")
            lines.append(f"    __asm__ volatile(\"lwz %0, {off:#x}(13)\" : \"=r\"(r));")
            lines.append(f"    return r;")
            lines.append("}")
            return lines, "r13"
    return None, None


# ---------------------------------------------------------------------------
# stub fallback
# ---------------------------------------------------------------------------

def stub_draft(start, size):
    nm = gl.fn_name(start)
    # NOTE: bare stub only — never emit the original disassembly as comments
    # (README states the repo contains no game assets or assembly whatsoever;
    # see the hygiene rule in AGENTS.md §6). Address/size marker only.
    body = []
    body.append(f"// WIP DRAFT — stub (range 0x{start:X}-0x{start + size:X}, {size}B):")
    body.append("void " + nm + "(void) {")
    body.append("    // TODO: decompile")
    body.append("}")
    return "\n".join(body), "stub"


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------

def main():
    max_size = int(sys.argv[sys.argv.index("--max-size") + 1]) if "--max-size" in sys.argv else 0
    rep = json.load(open(f"{ROOT}/build/G2TE52/report.json"))
    matched = set()
    for cpath in glob.glob(f"{ROOT}/src/*.c"):
        for mo in re.finditer(r"fn_[0-9A-F]{8}", open(cpath).read()):
            matched.add(int(mo.group(0)[3:], 16))
    fninfo = {}
    for u in rep.get("units", []):
        # A unit counts as matched when the report says so: complete=True or
        # 100% fuzzy at unit level, or per-function 100% (partial units like
        # gx/GXInit.c wire only some functions). This covers DolphinLib
        # sources under libs/ (never scanned by the src/*.c grep above) and
        # promoted files whose function is real-named (renamed script
        # commands / SDK names — their address never appears as an fn_ token
        # anywhere in src/, so the grep alone resurrects drafts for them).
        u_md = u.get("metadata", {})
        unit_matched = (u_md.get("complete") is True
                        or u.get("measures", {}).get("fuzzy_match_percent") == 100.0)
        for fn in u.get("functions", []):
            a = int(fn["metadata"]["virtual_address"])
            fninfo[a] = int(fn["size"])
            if unit_matched or fn.get("fuzzy_match_percent") == 100.0:
                matched.add(a)

    os.makedirs(WIP_DIR, exist_ok=True)
    fam = {}
    total = 0
    with open(REG, "a") as reg:
        for a in sorted(fninfo):
            if a in matched or a in gl.PARKED:
                continue
            size = fninfo[a]
            if max_size and size > max_size:
                continue
            # skip existing drafts
            if os.path.isfile(f"{WIP_DIR}/fn_{a:08X}.c"):
                continue
            lines, family = None, None
            cls = gl.classify(a)
            if cls is not None:
                src = gl.gen_one(a, cls[0], cls[1:])
                if src:
                    lines = "\n".join(src)
                    family = cls[0]
            if lines is None:
                lines, family = match_survey(a)
                if lines is not None:
                    lines = "\n".join(lines)
            if lines is None:
                lines, family = stub_draft(a, size)
            with open(f"{WIP_DIR}/fn_{a:08X}.c", "w") as f:
                f.write("// WIP DRAFT (non-matching) — generated by tools/gen_wip_drafts.py\n"
                        + f"// family={family} range=0x{a:X}-0x{a + size:X} size={size}B\n"
                        + "// INERT: not registered in splits.txt/configure.py — never compiled,\n"
                        + "// not counted in objdiff progress. activate via tools/wip.py.\n"
                        + '#include "types.h"\n'
                        + lines + "\n")
            reg.write(f"| fn_{a:08X} | 0x{a:08X} | {family} |\n")
            fam[family] = fam.get(family, 0) + 1
            total += 1
    print(f"wrote {total} WIP drafts")
    for k, v in sorted(fam.items(), key=lambda kv: -kv[1]):
        print(f"  {k:8s} x{v}")


if __name__ == "__main__":
    main()
