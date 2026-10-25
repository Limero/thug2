#!/usr/bin/env python3
"""Check a WIP draft's *control flow*, which the masked scorer cannot see.

tools/test_wip_drafts.py (and objdiff) mask the displacement of every
REL14/REL24 branch, because ngccc emits branches as relocations.  A draft whose
`if`/`switch` structure is wrong therefore still scores 100% while the linked
DOL differs (the promote step's `cmp orig/G2TE52/sys/main.dol` catches it, but
only after a full rebuild).

This resolves the branch relocations the way the linker does — target =
function_base + symbol_value + addend — and compares every branch that lands
inside the function against the same instruction in the retail DOL.

Usage:
  tools/venv/bin/python tools/br_targets.py 0x801689C8 [size]
"""
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402
from elftools.elf.elffile import ELFFile  # noqa: E402

R_PPC_REL24, R_PPC_REL14 = 10, 11

_SYMBOLS = None


def link_symbols():
    """Real link addresses from symbols.txt, for externs that are undefined
    in the standalone draft object.  An UND symbol has st_value 0, so resolving
    it as base+0+addend fabricates a branch to the function's own base (a
    `b ext` tail wedge reads back as a self-loop and the draft is wrongly
    refused).  The linker would use the real address instead, so do that."""
    global _SYMBOLS
    if _SYMBOLS is None:
        _SYMBOLS = {}
        for line in open(f"{gl.ROOT}/config/G2TE52/symbols.txt"):
            m = re.match(r"(\S+)\s*=\s*\.(?:text|init):(0x[0-9A-Fa-f]+)", line)
            if m:
                _SYMBOLS[m.group(1)] = int(m.group(2), 16)
    return _SYMBOLS


def reloc_target(sym, addend, base):
    """Link-accurate relocation target, or None if unresolvable pre-link.
    Defined syms keep the old base+st_value+addend rule (including the
    mtctr-placeholder form that must resolve to base).  Undefined syms use
    their real symbols.txt address; truly unknown ones resolve to nothing
    and their branch sites are skipped (no phantom self-branch)."""
    if sym["st_shndx"] in (0, "SHN_UNDEF"):
        addr = link_symbols().get(sym.name)
        return None if addr is None else addr + addend
    return base + sym["st_value"] + addend


def body_of(addr):
    text = open(f"{gl.ROOT}/src/wip/fn_{addr:08X}.c").read()
    marker = re.search(r"range=0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+) size=(\d+)B", text)
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l)
    flags = []
    for line in text.splitlines():
        m = re.match(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", line)
        if m:
            # Valid flag tokens only (same rule as test_wip_drafts).
            flags += [t for t in m.group(1).split() if gl.FLAG_TOKEN_RE.match(t)]
    # Mirror promote_wip.draft_flags()/test_wip_drafts: a paired-single body
    # ALWAYS needs -mps-float, even when the header forgot the FLAG line.
    # Without this the control-flow check compiles SCALAR code (different
    # length/registers) and reports bogus branch diffs against a PS draft.
    if ("__ps_t" in text or "__builtin_ps_" in text) and "-mps-float" not in flags:
        flags.append("-mps-float")
    size = int(marker.group(3)) if marker else None
    return body, (list(dict.fromkeys(flags)) or None), size


def want_size(addr):
    rep = json.load(open(f"{gl.ROOT}/build/G2TE52/report.json"))
    for u in rep["units"]:
        for fn in u.get("functions", []):
            if int(fn["metadata"]["virtual_address"]) == addr:
                return int(fn["size"])
    return None


def compile_obj(addr, body, flags):
    tmpdir = f"/tmp/br_targets_{os.getpid()}"
    os.makedirs(tmpdir, exist_ok=True)
    sp, op = f"{tmpdir}/fn_{addr:08X}.c", f"{tmpdir}/fn_{addr:08X}.o"
    with open(sp, "w") as f:
        f.write('#include "types.h"\n' + body)
    env = dict(os.environ)
    env["SN_NGC_PATH"] = gl.C_DIR
    fl = (["-O2", "-G0", "-mcpu=750", "-fno-common", "-I", f"{gl.ROOT}/include"]
          + list(flags or []))
    r = subprocess.run([gl.WIBO, f"{gl.C_DIR}/ngccc.exe"] + fl + ["-c", sp, "-o", op],
                       cwd=gl.ROOT, capture_output=True, text=True, env=env)
    if r.returncode != 0:
        raise SystemExit("compile failed:\n" + r.stderr[:400])
    return op


def got_targets(obj, base, lo, hi):
    """address -> (mnemonic, target) for branches resolved like the linker.

    Two populations, and BOTH must be collected or the comparison is
    asymmetric:

      * conditionals the compiler emits with an already-resolved displacement
        (`bdnz`, `bne`, the `b` of an if/else).  These carry no relocation, so
        they are decoded straight out of the object's .text exactly the way
        want_targets() decodes retail.  Without this pass every retail spin
        loop reads as `got None` and the draft is wrongly refused: a `mtctr N`
        + `bdnz .` empty loop (0x42000000) is byte-identical on both sides but
        got_targets() only saw the call relocations, so fn_801BA464 /
        fn_801B9FD0 / fn_801B7C80 / fn_801B99A8 / fn_801B8678 were all
        refused as "internal branch target(s) differ" while their only
        non-masked difference was zero words.
      * REL14/REL24 branches, whose stored displacement is zero in the object
        and is filled in by the linker, so they must be resolved from .rela
        (these are also the ones the masked scorer cannot see).
    """
    out = {}
    md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
    with open(obj, "rb") as f:
        elf = ELFFile(f)
        text_idx = elf.get_section_index(".text")
        text = elf.get_section_by_name(".text").data()
        symtab = elf.get_section_by_name(".symtab")
        rela = elf.get_section_by_name(".rela.text")
        # REL24/REL14 displacements are filled in by the linker, so collect
        # their resolved targets first.  Two flavours live in these objects:
        #   * a real local branch -- symbol value + addend is the final target
        #     (e.g. `ble ... addend 0x170` for a branch to base+0x170), and
        #   * a PLACEHOLDER emitted next to `mtctr N` + `bdnz .` (an empty
        #     loop, 0x42000000) that points at the section symbol and resolves
        #     to the function's own base.  For that one the encoded field is
        #     the truth (retail's field is 0 too), so it must NOT be resolved.
        relocated = {}
        if rela is not None:
            for rel in rela.iter_relocations():
                if rel["r_info_type"] not in (R_PPC_REL24, R_PPC_REL14):
                    continue
                sym = symtab.get_symbol(rel["r_info_sym"])
                # None = undefined symbol with no known address: skip the site
                # (it cannot be validated pre-link); None != base so pass 1
                # treats it as deferred, and pass 2 drops it below.
                relocated[rel["r_offset"]] = reloc_target(sym, rel["r_addend"], base)
        # pass 1 -- CONDITIONALS, decoded from the object's own bytes, exactly
        # the way want_targets() decodes retail.  Relocated sites are deferred
        # to pass 2 (a zero field there would decode as a branch to itself).
        # Without this pass want's `bdnz .` reads as `got None` and a
        # byte-identical draft is refused -- that is how fn_801BA464 /
        # fn_801B8678 (and 801B9FD0 / 801B7C80 / 801B99A8, whose real residue
        # is a couple of REL14 conditionals) all came up as "internal branch
        # target(s) differ" with zero non-masked word differences.
        for i in range(0, len(text) - 3, 4):
            if i in relocated and relocated[i] != base:
                continue
            for ins in md.disasm(text[i:i + 4], base + i):
                # same rule as want_targets(): skip calls / indirect branches
                if ins.mnemonic in ("bl", "bla", "blr", "bctr", "bctrl", "bclrl"):
                    continue
                if not ins.mnemonic.startswith("b"):
                    continue
                tgt = None
                for tok in ins.op_str.split(","):
                    tok = tok.strip()
                    if tok.startswith("0x"):
                        try:
                            tgt = int(tok, 16)
                        except ValueError:
                            pass
                if tgt is not None and lo <= tgt < hi:
                    out[base + i] = (ins.mnemonic, tgt)
        if rela is None:
            return out
        # pass 2 -- the relocated branches themselves.
        for rel in rela.iter_relocations():
            if rel["r_info_type"] not in (R_PPC_REL24, R_PPC_REL14):
                continue
            sym = symtab.get_symbol(rel["r_info_sym"])
            if sym["st_shndx"] in (0, "SHN_UNDEF"):
                # External branch (e.g. a `b ext_target` tail wedge): resolve
                # to the real link address so it filters as external instead
                # of fabricating a self-loop.  Defined-symbol sites keep the
                # old rule below.
                tgt = reloc_target(sym, rel["r_addend"], base)
                if tgt is None or not (lo <= tgt < hi):
                    continue
            else:
                if sym["st_shndx"] != text_idx:
                    continue
                tgt = base + sym["st_value"] + rel["r_addend"]
                if not (lo <= tgt < hi):
                    continue
            off = rel["r_offset"]
            for ins in md.disasm(text[off:off + 4], base + off):
                # A SELF-recursive call resolves to the function's own base and
                # is a `bl`, which want_targets() deliberately SKIPS ("skip
                # calls and indirect branches; keep conditionals").  Without
                # this the two sides are asymmetric and every recursive
                # function is reported as a control-flow mismatch
                # (e.g. fn_800421D4).  Calls to addresses strictly inside the
                # function are still compared.
                if tgt == base and ins.mnemonic in ("bl", "bla"):
                    continue
                out[base + off] = (ins.mnemonic, tgt)
    return out


def want_targets(base, size):
    """Branches in the retail function whose target is inside it.

    Decoded word by word: capstone's streaming disassembler stops at the first
    word it cannot decode (data or padding inside the range), which would hide
    every later branch and silently limit the comparison.
    """
    out = {}
    md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
    o = gl.t_off + (base - gl.t_addr)
    for i in range(0, size - 3, 4):
        for ins in md.disasm(gl.d[o + i:o + i + 4], base + i):
            # skip calls and indirect branches; keep conditionals (blt, bne, ...)
            if ins.mnemonic in ("bl", "bla", "blr", "bctr", "bctrl", "bclrl"):
                continue
            if not ins.mnemonic.startswith("b"):
                continue
            tgt = None
            for tok in ins.op_str.split(","):
                tok = tok.strip()
                if tok.startswith("0x"):
                    try:
                        tgt = int(tok, 16)
                    except ValueError:
                        pass
            if tgt is not None and base <= tgt < base + size:
                out[ins.address] = (ins.mnemonic, tgt)
    return out


def internal_branch_diffs(addr, size=None, body=None, flags=None):
    """Return the internal-branch mismatches for a draft ([] = control flow ok).

    Importable so other tools (e.g. tools/promote_wip.py) can refuse a draft
    that only *looks* byte-exact because branch displacements are masked.
    """
    if body is None:
        body, flags, hdr_size = body_of(addr)
        size = size or hdr_size
    if not size:
        size = want_size(addr)
    if not size or size < 0x40:          # empty/short auto stub: nothing to check
        return []
    got = got_targets(compile_obj(addr, body, flags), addr, addr, addr + size)
    want = want_targets(addr, size)
    diffs = []
    for a in sorted(set(want) | set(got)):
        w, g = want.get(a), got.get(a)
        if w and g and w[1] == g[1]:
            continue
        diffs.append((a, w, g))
    return diffs


def main():
    addr = int(sys.argv[1], 0)
    body, flags, size = body_of(addr)
    if len(sys.argv) > 2:
        size = int(sys.argv[2], 0)
    if not size:
        size = want_size(addr)
    if not size:
        raise SystemExit(f"no size for 0x{addr:08X} — pass it explicitly")
    if size < 0x40:            # empty/short auto stub: nothing to check
        print(f"SKIP: size {size}B")
        return 0
    diffs = internal_branch_diffs(addr, size, body, flags)
    for a, w, g in diffs:
        print(f"  {a:#x}: want {w} got {g}")
    n_want = len(want_targets(addr, size))
    print(f"{'OK' if not diffs else 'MISMATCH'}: {len(diffs)} internal-branch"
          f" difference(s); {n_want} internal branches ({size}B)")
    return 1 if diffs else 0


if __name__ == "__main__":
    sys.exit(main())
