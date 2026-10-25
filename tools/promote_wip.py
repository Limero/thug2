#!/usr/bin/env python3
"""Promote byte-exact WIP drafts into registered src/fn_*.c files.

Given the addresses that tools/test_wip_drafts.py reported as EXACT, this:
1. Reads src/wip/fn_XXXX.c, strips the WIP header comment, and rewrites the
   file into src/fn_XXXX.c with the standard gen_leaves-style header
   (including the 'range 0x...-0x...' marker add_gen_leaves.py keys on).
2. Runs tools/add_gen_leaves.py to register all src/fn_*.c into
   splits.txt + configure.py (idempotent, established tool).
3. Reconfigures, rebuilds the DOL, and verifies byte-identity.

Usage:
  tools/venv/bin/python tools/promote_wip.py [addr ...]
  (no args = use the built-in EXACT list from the last test run)
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, f"{ROOT}/tools")
import gen_leaves as gl  # noqa: E402 — for compile_fn (exact ngccc cmd + masks)

def masked_pct(orig, got, masks):
    """Fraction of instruction words that match under the reloc masks."""
    n = len(orig) // 4
    if n == 0:
        return 0.0
    hit = 0
    for i in range(n):
        ow = int.from_bytes(orig[i * 4:(i + 1) * 4], "big")
        gw = int.from_bytes(got[i * 4:(i + 1) * 4], "big")
        if (ow & masks.get(i * 4, 0xFFFFFFFF)) == (gw & masks.get(i * 4, 0xFFFFFFFF)):
            hit += 1
    return 100.0 * hit / n

# .text section (DOL section 1) bounds — only these can be split as .text
TEXT_START = 0x800034A0
TEXT_END = 0x8028E040

# From tools/test_wip_drafts.py run: 38 byte-exact drafts (family, addr)
EXACT = [
    ("e", 0x80003464), ("s2", 0x8000DDA0), ("gs", 0x8001DC08),
    ("s1", 0x800F3740),
    ("s3", 0x8010CF70), ("s3", 0x8010CF88), ("s3", 0x8010CFA0),
    ("s3", 0x8010CFB8), ("s3", 0x8010CFD0),
    ("s3", 0x80119398), ("s3", 0x801193B0), ("s3", 0x801193C8),
    ("s2", 0x8012729C), ("s1", 0x8012F030), ("s2", 0x801CDDF4),
    ("s2", 0x801F1418), ("s1", 0x801F1428), ("s1", 0x801F143C),
    ("s1", 0x801F1450), ("s1", 0x801F1464), ("s1", 0x801F1478),
    ("s2", 0x802157E8), ("s1", 0x802157F8), ("s1", 0x8021580C),
    ("s1", 0x80215820), ("s1", 0x80215834),
    ("mfs", 0x80261DD4), ("mts", 0x80261DDC), ("mts", 0x80261DE4),
    ("r13", 0x80262FB8), ("r13", 0x80262FC0), ("r13", 0x8026E5A4),
    ("r13", 0x80277D60), ("r13", 0x8027904C), ("r13", 0x80280C24),
    ("r13", 0x8028699C), ("r13", 0x802869A4), ("r13", 0x802869AC),
]

ADDRS = [int(a, 16) for a in sys.argv[1:]] if len(sys.argv) > 1 else [a for _, a in EXACT]


def draft_flags(txt):
    """Return the per-object flags recorded in a WIP header."""
    flags = []
    for line in txt.splitlines()[:120]:
        m = re.search(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", line)
        if m:
            # Valid flag tokens only — the line carries trailing prose and
            # informal variant names, and a bogus token makes ngccc abort
            # (same rule as test_wip_drafts / br_targets).
            flags.extend(t for t in m.group(1).replace(",", " ").split()
                         if gl.FLAG_TOKEN_RE.match(t))
    # PS bodies always need -mps-float. Match the `__builtin_ps_*` name too:
    # a body can call the PS builtins without ever naming the `__ps_t` type,
    # and it would then be built (and compared) as scalar code.
    if ("__ps_t" in txt or "__builtin_ps_" in txt) and "-mps-float" not in flags:
        flags.append("-mps-float")
    return list(dict.fromkeys(flags))


def draft_code(txt):
    """The compilable part of a draft: drop the leading comment block(s).

    The old extraction (``txt.split("\n", 1)[1]`` + strip leading ``//``)
    corrupted two draft header styles: a file whose header is a ``/* ... */``
    block lost its ``/*`` opener (the comment leaked into the code), and the
    commented-out first line of a plain ``//`` header was required to be a
    comment.  It also assumed the draft carried its own
    ``#include "types.h"`` — ``gen_leaves.compile_fn`` always
    prepends that include, so a draft without it (or with prototypes before
    the include) verified EXACT offline but failed to build once promoted.
    """
    lines = txt.splitlines()
    i = 0
    while i < len(lines):
        s = lines[i].strip()
        if s.startswith("//"):
            i += 1
        elif s.startswith("/*"):
            while i < len(lines) and "*/" not in lines[i]:
                i += 1
            i += 1  # skip the line that closes the block
        elif s == "":
            i += 1
        else:
            break
    body = "\n".join(lines[i:]).strip()
    if "types.h" not in body:
        body = '#include "types.h"\n' + body
    return body + "\n"


def obj_has_payload(body, addr, extra_flags=None):
    """Compile the body and reject new allocatable sections outside .text.

    WIP drafts with static data, constants, or compiler-generated pools can
    pass a masked text compare but shift the linked DOL. Existing data remains
    in the auto-assembly units, so a promoted function object must contribute
    text only.
    """
    import subprocess as sp
    fname = "fn_%08X" % addr
    os.makedirs("/tmp/leaf", exist_ok=True)
    spth = "/tmp/leaf/%s.c" % fname
    with open(spth, "w") as f:
        f.write('#include "types.h"\n' + body)
    env = dict(os.environ)
    env["SN_NGC_PATH"] = gl.C_DIR
    flags = ["-O2", "-G0", "-mcpu=750", "-fno-common", "-I", f"{ROOT}/include"]
    if extra_flags:
        flags += list(extra_flags)
    r = sp.run([gl.WIBO, f"{gl.C_DIR}/ngccc.exe"] + flags + ["-c", spth,
                "-o", "/tmp/leaf/%s.o" % fname], cwd=ROOT,
               capture_output=True, text=True, env=env)
    if r.returncode != 0:
        return False
    # FP constant pools (int->double cast magics) are retargeted to existing
    # DOL lbl_* symbols by tools/fix_fp_pool.py (same step the ninja ngccc
    # rule runs); a pool that resolves is not a payload.
    sp.run([f"{ROOT}/tools/venv/bin/python", f"{ROOT}/tools/fix_fp_pool.py",
            "/tmp/leaf/%s.o" % fname], cwd=ROOT, capture_output=True, text=True)
    try:
        rd = sp.run([f"{ROOT}/build/binutils/powerpc-eabi-readelf", "-W", "-S",
                     "/tmp/leaf/%s.o" % fname], cwd=ROOT,
                    capture_output=True, text=True).stdout
    except OSError:
        return False
    for line in rd.splitlines():
        # readelf -W -S prints the [Nr] field as two whitespace-separated
        # tokens ("[" and "2]") on this toolchain, so locate the section
        # name/type instead of relying on fixed columns.
        fields = line.split()
        if len(fields) < 8:
            continue
        try:
            name_idx = next(i for i, field in enumerate(fields) if field.startswith("."))
        except StopIteration:
            continue
        name = fields[name_idx]
        if name in (".text", ".rela.text", ".comment", ".debug_info",
                    ".debug_abbrev", ".debug_line", ".debug_frame", ".symtab",
                    ".strtab", ".shstrtab"):
            continue
        try:
            size = int(fields[name_idx + 4], 16)
        except (IndexError, ValueError):
            continue
        if size:
            return True
    return False


# ASM_FUNC guard (2026-09-22): refuse lazy whole-body asm transcriptions.
# objdiff compares compiled object bytes, so a C file whose body is the
# original asm assembles to identical bytes and scores 100% while nothing is
# decompiled. Sanctioned small wedges (single-insn barriers, lis/lfs anchors,
# doc-30 bdnz windows, stwbrx/mtspr ops with no C form) are a few lines each;
# a transcription carries a large share of the function in a few big blocks.
# Thresholds were calibrated against the 2026-09-22 audit: 13 demoted
# violations all had a 97+ insn block and 72-100% asm share, while every
# legitimate promoted file stays under a 24-insn block and 24 total insns.
ASM_MAX_SHARE = 0.30  # max fraction of the function's insns emitted from asm
ASM_MIN_COUNT = 24    # absolute floor: fewer asm insns than this always pass
ASM_MAX_BLOCK = 24    # max emitted insns in any single __asm__ template


def _asm_template_counts(body):
    """Yield the emitted-insn count of each __asm__ template in body.

    Only the FIRST string literal of each __asm__ (the template) is scanned,
    so output/input/clobber operands ('=r', 'r', 'memory') never count — and
    neither do register-var pins (__asm__("r31")), which are excluded
    explicitly. Multi-instruction templates are the '\\n\\t'-joined blocks
    the audit found these violations through.
    """
    counts = []
    # __asm__ [volatile] ( template : ... ) — template = first "..." literal
    # PLUS any immediately-adjacent literals: whole-body transcriptions are
    # written as one literal per line (".long 0x....\n\t" "..."), so reading
    # only the first literal would see a single insn per block.
    lit_re = re.compile(r'\s*"((?:[^"\\]|\\.)*)"')
    for m in re.finditer(
            r'__asm__\s*(?:volatile\s*|__volatile__\s*)?\(\s*"((?:[^"\\]|\\.)*)"',
            body):
        template = m.group(1)
        pos = m.end()
        while True:
            m2 = lit_re.match(body, pos)
            if not m2:
                break
            template += m2.group(1)
            pos = m2.end()
        n = 0
        for part in template.split("\\n"):
            for sub in part.split("\\t"):
                p = sub.strip().rstrip(";").strip()
                if not p:
                    continue
                # register-pin declarations and bare constraint names
                if re.match(r"^(r\d+|f\d+|fr\d+|cr\d+|cc|memory)$", p):
                    continue
                # an instruction word, a .long/.word raw word, or an asm
                # label belonging to a transcribed window (e.g. '8:')
                if re.match(r"^[A-Za-z.][\w.]*(:|\s|$)", p):
                    n += 1
        counts.append(n)
    return counts


def asm_string_dollar(body):
    """True if a '$' sits inside an asm template literal.

    Such a '$' is a self-target local label: it assembles, but the linker
    sees an undefined symbol '$' (doc-30 `bdnz $` form). A '$' anywhere else
    is ordinary C (character constants like `case '$':`, string literals in
    the encoding/shift-JIS analyzers) and is not a link hazard, so the scan
    is scoped to the parenthesised argument of each asm statement.
    """
    for m in re.finditer(r"\b(__asm__|asm)\b", body):
        j = body.find("(", m.end())
        if j < 0:
            continue
        depth = 0
        k = j
        while k < len(body):
            c = body[k]
            if c == '"':
                k += 1
                start = k
                while k < len(body) and body[k] != '"':
                    k += 2 if body[k] == "\\" else 1
                if "$" in body[start:k]:
                    return True
            elif c == "'":
                k += 1
                while k < len(body) and body[k] != "'":
                    k += 2 if body[k] == "\\" else 1
            elif c == "(":
                depth += 1
            elif c == ")":
                depth -= 1
                if depth == 0:
                    break
            k += 1
    return False


def asm_transcription_refusal(body, size):
    """Return a REFUSE reason if body is mostly transcribed asm, else None."""
    counts = _asm_template_counts(body)
    if not counts:
        return None
    nins = max(size // 4, 1)
    total = sum(counts)
    biggest = max(counts)
    if biggest > ASM_MAX_BLOCK:
        return (f"largest __asm__ block emits {biggest} insns "
                f"(limit {ASM_MAX_BLOCK}); whole-body asm transcriptions "
                f"fake the objdiff match — decompile in C, keeping asm to "
                f"small sanctioned wedges (see recipe 180)")
    if total > ASM_MAX_SHARE * nins and total > ASM_MIN_COUNT:
        return (f"__asm__ templates emit {total}/{nins} insns "
                f"({100.0 * total / nins:.0f}% > {ASM_MAX_SHARE:.0%}); "
                f"whole-body asm transcriptions fake the objdiff match — "
                f"decompile in C, keeping asm to small sanctioned wedges "
                f"(see recipe 180)")
    return None


def owned_source(addr):
    """Path of the already-matching source owning addr, or None.
    A draft for an owned address must never become a src/fn_*.c: when the
    owner lives under libs/ (runtime/dolphin/...) the orphan twin is never
    compiled (add_gen_leaves keys on basenames already registered for the
    lib), and when it is a named game unit (vcall_*, ...) promoting would
    overlap its split range. Ownership comes from the source tree first
    (fresh even when report.json is stale/missing after a cold rebuild),
    then from the build report via gl.build_matched_addrs()."""
    import glob
    name = f"fn_{addr:08X}"
    for fp in glob.glob(f"{ROOT}/libs/*/src/{name}.c"):
        return os.path.relpath(fp, ROOT)
    owned = gl.build_matched_addrs()
    if addr in owned:
        return f"report unit {owned[addr]}"
    return None


def promote(addr):
    name = f"fn_{addr:08X}"
    src = f"{ROOT}/src/wip/{name}.c"
    dst = f"{ROOT}/src/{name}.c"
    if os.path.exists(dst):
        print(f"SKIP {dst}: already promoted")
        return False
    owner = owned_source(addr)
    if owner is not None:
        print(f"SKIP 0x{addr:08X}: already matched as {owner} — stays in WIP")
        return False
    txt = open(src).read()

    # extract start/end/size from the WIP header comment
    m = re.search(r"range=0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+) size=(\d+)B", txt)
    assert m, f"no range marker in {src}"
    start, end, size = int(m.group(1), 16), int(m.group(2), 16), int(m.group(3))
    assert start == addr, f"marker start {start:#x} != {addr:#x}"
    assert end - start == size, (
        f"marker range {start:#x}-{end:#x} is inconsistent with size {size}"
    )

    # re-verify byte-exactness before wiring into the build
    body_lines = [l for l in txt.splitlines()
                  if not l.startswith("//") and "types.h" not in l]
    body = "\n".join(body_lines).strip()
    extra = draft_flags(txt)
    if any(flag.startswith("-msdata=") for flag in extra):
        verify = subprocess.run(
            [f"{ROOT}/tools/venv/bin/python", f"{ROOT}/tools/sda_verify.py",
             f"0x{addr:08X}", src] + extra,
            cwd=ROOT, capture_output=True, text=True,
        )
        if "LINK-SIM EXACT" not in verify.stdout:
            raise SystemExit(
                f"REFUSE 0x{addr:08X}: SDA link-sim is not exact — "
                f"{verify.stdout[-240:].strip()}"
            )
    else:
        got, masks = gl.compile_fn(addr, body, extra_flags=extra or None)
        assert got is not None, f"{src}: compile failed — not promoting"
        orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + len(got)]
        if len(orig) < len(got) or masked_pct(orig, got, masks) < 100.0:
            raise SystemExit(f"REFUSE 0x{addr:08X}: draft is NOT byte-exact — do not promote")
    if obj_has_payload(body, addr, extra):
        print(f"SKIP 0x{addr:08X}: object emits allocatable data outside .text — "
              f"promoting would shift the DOL; stays in WIP")
        return False
    # Control flow: the masked compare ignores every branch displacement, so a
    # draft whose if/switch structure is wrong still scores 100%.  Check it here
    # instead of discovering it in the DOL diff after the full rebuild
    # (tools/br_targets.py resolves branch relocations like the linker does).
    import br_targets
    bdiffs = br_targets.internal_branch_diffs(addr, size, body, extra or None)
    if bdiffs:
        detail = "; ".join(f"{a:#x} want {w} got {g}" for a, w, g in bdiffs[:3])
        raise SystemExit(
            f"REFUSE 0x{addr:08X}: {len(bdiffs)} internal branch target(s) differ "
            f"from retail — masked score hides control-flow mismatches "
            f"(see WIP.md recipe 26). {detail}"
        )
    # An inline '$' inside an asm string is a self-target local label that
    # compiles fine but links as an undefined symbol '$' (doc-30 bdnz $ form).
    # Screen on the comment-stripped body, and only inside the asm template
    # literals: a plain '$' elsewhere is ordinary C (e.g. `case '$':` in the
    # Shift-JIS/encoding analyzers) and must not trip this check.
    if asm_string_dollar(re.sub(r"//.*", "", body)):
        raise SystemExit(
            f"REFUSE 0x{addr:08X}: asm string contains '$' (self-target local "
            f"label — links as undefined symbol '$'); needs plain-C loop form"
        )
    # Lazy whole-body asm transcriptions score 100% (assembled bytes equal
    # retail bytes) while decompiling nothing. Screen on the comment-stripped
    # body: headers legitimately discuss asm shapes and sizes.
    refusal = asm_transcription_refusal(re.sub(r"//.*", "", body), size)
    if refusal:
        raise SystemExit(f"REFUSE 0x{addr:08X}: {refusal}")

    # strip the WIP header comment block; keep the compilable code
    body = draft_code(txt)

    extra_note = ("// extra_cflags: " + " ".join(extra) + "\n") if extra else ""
    header = (
        "// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)\n"
        f"// range 0x{start:X}-0x{end:X} ({size}B). Byte-identical.\n"
        "// Link-level exactness was verified against the full linked DOL.\n"
        + extra_note
    )
    open(dst, "w").write(header + body)
    print(f"promoted {dst}")
    # NOTE: the WIP draft is intentionally NOT removed here. The final DOL
    # byte-identity check in main() may still fail (stale build state, section
    # shifts, ...) and the revert path removes src/fn_*.c — deleting the draft
    # here would lose the verified source. It is removed in main() only after
    # the DOL is confirmed byte-identical.
    return True


def main():
    promoted = 0
    skipped = []
    created = []
    splitp = f"{ROOT}/config/G2TE52/splits.txt"
    cfgp = f"{ROOT}/configure.py"
    original_splits = open(splitp).read()
    original_cfg = open(cfgp).read()
    for a in ADDRS:
        if not (TEXT_START <= a < TEXT_END):
            skipped.append(a)
            print(f"SKIP 0x{a:08X}: outside .text (init/data section) — stays in WIP")
            continue
        if promote(a):
            created.append(a)
        promoted += 1
    print(f"promoted {promoted}, skipped {len(skipped)}")
    # register all src/fn_*.c (with range markers) into splits + configure
    subprocess.run([f"{ROOT}/tools/venv/bin/python",
                    f"{ROOT}/tools/add_gen_leaves.py"], cwd=ROOT, check=True)
    # Reconfigure first so every existing generated object is registered;
    # then force the link inputs fresh. A stale incremental main.elf can move
    # SDA addresses and make patch_dol reject an otherwise valid promotion.
    subprocess.run(["python3", "configure.py", "--dtk", "tools/dtk",
                    "--ninja", "tools/ninja", "--compilers", "build/compilers"],
                   cwd=ROOT, capture_output=True, check=True)
    subprocess.run(["rm", "-f", "build/G2TE52/main.elf", "build/G2TE52/main.dol"],
                   cwd=ROOT)
    r = subprocess.run(["tools/ninja", "build/G2TE52/main.dol"], cwd=ROOT,
                       capture_output=True, text=True)
    print(r.stdout[-800:] if r.stdout else "")
    ok = subprocess.run(["cmp", "-s", "orig/G2TE52/sys/main.dol",
                         "build/G2TE52/main.dol"], cwd=ROOT).returncode == 0
    if ok:
        # success: drop WIP drafts + WIP.md rows ONLY for addresses whose
        # src/fn_*.c actually exists (promoted this run or already promoted).
        # Skipped addresses (outside .text, .rodata-emitting, refused) keep
        # their WIP drafts — nothing was promoted for them.
        for a in ADDRS:
            dst = f"{ROOT}/src/fn_{a:08X}.c"
            if not os.path.exists(dst):
                continue
            src = f"{ROOT}/src/wip/fn_{a:08X}.c"
            if os.path.exists(src):
                os.remove(src)
            wip_md = f"{ROOT}/WIP.md"
            if os.path.exists(wip_md):
                lines = open(wip_md).read().split("\n")
                out = [l for l in lines
                       if not (l.startswith(f"| fn_{a:08X}") or l.startswith(f"|fn_{a:08X}"))]
                open(wip_md, "w").write("\n".join(out))
        print("DOL BYTE-IDENTICAL")
        return 0
    print("!!! DOL DIFFERS !!! — reverting this batch's registrations")
    # Debug aid: report WHERE the DOL differs before reverting. The first
    # differing byte usually identifies the real cause (a pool/data shift, a
    # sibling function's relayout, or an alignment/padding change) far faster
    # than re-promoting one address at a time.
    try:
        a = open(f"{ROOT}/orig/G2TE52/sys/main.dol", "rb").read()
        b = open(f"{ROOT}/build/G2TE52/main.dol", "rb").read()
        if len(a) != len(b):
            print(f"  size: orig {len(a)} vs built {len(b)}")
        n = 0
        first = None
        for i in range(min(len(a), len(b))):
            if a[i] != b[i]:
                n += 1
                if first is None:
                    first = i
        print(f"  differing bytes: {n}; first at file offset {first:#x}"
              + (f" (DOL vaddr {0x80003100 + first:#x})" if first is not None else ""))
        if first is not None:
            lo = max(0, first - 32)
            print(f"  orig[{lo:#x}:{first+32:#x}] {a[lo:first+32].hex()}")
            print(f"  built[{lo:#x}:{first+32:#x}] {b[lo:first+32].hex()}")
    except OSError as exc:
        print(f"  (diff report failed: {exc})")
    if os.environ.get("KEEP_DIFF"):
        print("KEEP_DIFF set — leaving the built DOL and registrations in place "
              "for diagnosis (revert with: git checkout -- config/G2TE52/splits.txt "
              "configure.py && rm src/fn_*.c)")
        return 1
    # Restore only this invocation's registration snapshot. Do not use git:
    # earlier successful promotion batches may be uncommitted in these files.
    open(splitp, "w").write(original_splits)
    open(cfgp, "w").write(original_cfg)
    for a in created:
        subprocess.run(["rm", "-f", f"{ROOT}/src/fn_{a:08X}.c"], cwd=ROOT)
    print("reverted src/fn_*.c + splits/configure; DOL identity preserved")
    print("WIP drafts kept in src/wip/ for re-promotion after fixing")
    return 1


if __name__ == "__main__":
    sys.exit(main())
