#!/usr/bin/env python3
"""REGISTER-RENAME triage for WIP drafts.

A large share of the residual NEAR pool is a pure register-colour swap: the
two instruction streams are IDENTICAL except that one register name differs
(`lwz r9, 0x14(r11)` vs `lwz r8, 0x14(r11)`).  Those are exactly the drafts
a hard-register `register ... __asm__("rN")` pin can fix (AGENTS.md §6o-98,
§6y-124, §6ad-166, and the 0x801A8354 vcall-pin win), and they are invisible
in a plain ranked NEAR list because the score does not say WHY it is short.

This tool recompiles each draft, diffs the masked want|got streams, and
reports only the drafts whose EVERY differing pair is a register rename
(same mnemonic, same shape with the register numbers blanked), together with
the (want_regs > got_regs) pairs so the pin register can be chosen without
re-deriving it by hand.

usage: regdiff_scan.py <file-list> [lo] [hi]
prints:  pct<TAB>file<TAB>ndiff<TAB>pairs
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402
import gen_leaves as gl  # noqa: E402

REG = re.compile(r"\br(\d{1,2})\b")
RENAMABLE = {
    "lwz", "stw", "lbz", "stb", "lhz", "sth", "lha", "lwzx", "stwx",
    "lbzx", "stbx", "lhzx", "sthx", "add", "addi", "addis", "subf", "sub",
    "mr", "or", "ori", "andis", "and", "andi.", "xor", "xori", "cmpw",
    "cmpwi", "cmplw", "cmplwi", "rlwinm", "rlwimi", "slw", "srw", "srawi",
    "extsb", "extsh", "mulli", "mullw", "lfs", "stfs", "lfd", "stfd",
    "fmuls", "fadds", "fmr", "fadd", "fmul", "mtlr", "mtctr", "neg",
    "cntlzw", "sraw", "mflr", "mtspr", "mfspr", "not", "nor", "eqv",
}


def _shape(txt):
    return REG.sub("r#", txt)


def _mnem(txt):
    p = txt.split()
    return p[0] if p else ""


def _decode(word):
    import capstone
    cs = capstone.Cs(capstone.CS_ARCH_PPC,
                     capstone.CS_MODE_32 | capstone.CS_MODE_BIG_ENDIAN)
    for ins in cs.disasm(word.to_bytes(4, "big"), 0):
        return f"{ins.mnemonic} {ins.op_str}".strip()
    return ""


def one(fn):
    fn = os.path.basename(fn)
    path = os.path.join(ROOT, "src/wip", fn)
    addr = int(fn[3:-2], 16)
    raw = open(path).read()
    flags = T.gl.draft_flags(raw) or None
    body = "\n".join(l for l in raw.splitlines()
                     if not l.lstrip().startswith("//"))
    got, masks = gl.compile_fn(addr, body, extra_flags=flags)
    if got is None:
        return None
    want_sz = T._want_sizes().get(addr, len(got))
    if want_sz < len(got):
        want_sz = len(got)
    off = gl.t_off + (addr - gl.t_addr)
    orig = gl.d[off:off + want_sz]
    if len(orig) < want_sz:
        return None
    n = min(len(orig), len(got)) // 4
    pairs, nd = [], 0
    for i in range(n):
        m = masks.get(i * 4, 0xFFFFFFFF)
        w = int.from_bytes(orig[i * 4:i * 4 + 4], "big") & m
        g = int.from_bytes(got[i * 4:i * 4 + 4], "big") & m
        if w != g:
            nd += 1
            pairs.append((w, g))
    if not nd or n == 0:
        return None
    pct = 100.0 * (n - nd) / n
    if pct < 50.0:
        return None
    out = []
    for w, g in pairs:
        wt, gt = _decode(w), _decode(g)
        if (not wt or not gt or _mnem(wt) != _mnem(gt)
                or _mnem(wt) not in RENAMABLE
                or _shape(wt) != _shape(gt)):
            return None                      # not a pure-rename draft
        out.append(f"{','.join(REG.findall(wt))}>{','.join(REG.findall(gt))}")
    return (f"{pct:.2f}", fn, str(nd), ";".join(out))


if __name__ == "__main__":
    files = [l.strip() for l in open(sys.argv[1]) if l.strip()]
    lo = int(sys.argv[2]) if len(sys.argv) > 2 else 0
    hi = int(sys.argv[3]) if len(sys.argv) > 3 else len(files)
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="rd_")
    for r in map(one, files[lo:hi]):
        if r:
            print("\t".join(r), flush=True)
