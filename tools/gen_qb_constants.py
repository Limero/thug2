#!/usr/bin/env python3
"""Generate include/qb_constants.h — QB_<NAME> defines for magic
0xXXXXXXXX constants found in src/ and src/wip/ that resolve to Neversoft
QB script hashes (tools/qb_hash.py, dictionary built from .prg plaintext).

The QB hash is the game's string-hash function (fn_8000A778): tricks
("Ollie"), script names, anim paths, etc. are passed around as opaque u32s.
This tool names the ones that actually appear as 8-digit hex literals in our
sources so the code reads as the game intended:

    fn_801A5210(temp_r31, 0x9B65D7B8)  ->  fn_801A5210(temp_r31, QB_OLLIE)

Byte-safe: every constant is a #define expanding to the identical literal.
Only values OUTSIDE the DOL address range (0x80000000..0x803FFFFF) are
candidates — in-range literals are pointers/globals, not hashes. After the
sweep (tools/apply_qb_constants.py) replaces literals with QB_ macros, this
tool keeps every still-referenced constant alive by tracking macro usages too,
so regeneration is stable (idempotent with the sweep).

Usage:
    tools/venv/bin/python tools/gen_qb_constants.py [--check]
      --check: exit 1 if the header would change (for CI / reproducibility)

Requires build/G2TE52/report.json (run tools/ninja once first) —
resolve_qb_hashes imports gen_leaves, which reads the report at import.

Name sources: .prg binaries (pre/*.pr*), compiled QB scripts
(levels/**/*.qb), the DOL .rodata2 registry TSV + .rodata2 string slice, and
inner QB scripts decoded from the LZSS pre archives (tools/qb_extract.py)
— all embed plaintext symbol names the game hashes.
"""
import argparse
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from qb_hash import load_table, constants_map  # noqa: E402
from resolve_qb_hashes import (  # noqa: E402
    build_dict, merge_dbg_names, merge_dol_hash_records, merge_dol_tokens,
    merge_qb_file_names)
import qb_extract  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

DOL_PATH = "orig/G2TE52/sys/main.dol"
PRE_DIR = "orig/G2TE52/disc/files/pre"
QB_GLOB = "orig/G2TE52/disc/files/levels/**/*.qb"  # compiled QB scripts (M6.86)
REGISTRY_TSV = "docs/rodata2-script-command-registry.tsv"  # DOL .data registry names
DOL_RODATA2 = DOL_PATH  # build_dict's .dol branch scans the .rodata2 slice
OUT = "include/qb_constants.h"

# DOL address space: values in here are pointers/globals, not hashes
DOL_LO, DOL_HI = 0x80000000, 0x803FFFFF

LIT_RE = re.compile(r"\b0x([0-9A-Fa-f]{8})U?\b")
MACRO_RE = re.compile(r"\b(QB_[A-Za-z0-9_]+)\b")


def _code_only(text):
    """Return `text` with string literals, // line comments and /* */ block
    comments masked out (spaces), leaving code text intact. Stateful per
    character (strings/comments may span lines)."""
    out = list(text)
    i = 0
    n = len(text)
    state = 0  # 0=code, 1=string, 2=block comment, 3=line comment
    while i < n:
        c = text[i]
        if state == 0:
            if c == '"':
                state = 1
                out[i] = ' '
            elif c == '/' and i + 1 < n and text[i + 1] == '/':
                state = 3
                out[i] = out[i + 1] = ' '
                i += 1
            elif c == '/' and i + 1 < n and text[i + 1] == '*':
                state = 2
                out[i] = out[i + 1] = ' '
                i += 1
            # else: code char — leave intact
        elif state == 1:
            out[i] = ' '
            if c == '\\' and i + 1 < n:
                out[i + 1] = ' '
                i += 1
            elif c == '"':
                state = 0
        elif state == 2:
            out[i] = ' '
            if c == '*' and i + 1 < n and text[i + 1] == '/':
                out[i + 1] = ' '
                i += 1
                state = 0
        elif state == 3:
            out[i] = ' '
            if c == '\n':
                state = 0
        i += 1
    return ''.join(out)


def referenced_values():
    """(vals, used_macros): magic values referenced in src+wip either as
    non-address 8-digit hex literals OR as QB_ macros (post-sweep the
    literals are gone but the macros keep the constants alive).

    Only code regions count: literals inside string literals (e.g. inline-asm
    ".long 0x7C0903A6" opcode words, which subst_qb_constants deliberately
    leaves alone) or comments would otherwise create unreferenced placeholders.
    """
    vals = {}
    used = set()
    for fp in glob.glob("src/*.c") + glob.glob("src/wip/*.c"):
        code = _code_only(open(fp, errors="ignore").read())
        for m in LIT_RE.finditer(code):
            v = int(m.group(1), 16)
            if DOL_LO <= v <= DOL_HI:
                continue
            vals.setdefault(v, 0)
            vals[v] += 1
        for m in MACRO_RE.finditer(code):
            used.add(m.group(1))
    return vals, used


def macro_name(raw, used):
    """QB_<NAME> from a plaintext name; disambiguate collisions with _N."""
    base = "QB_" + re.sub(r"[^A-Za-z0-9]", "_", raw).upper()
    name = base
    i = 2
    while name in used:
        name = "%s_%d" % (base, i)
        i += 1
    return name


# Verified NON-QB constants that appear as literals in src but are provably
# not QB script hashes. Named from their usage context alone (game-file
# evidence): ASCII file-format magics (the streamed-file chunk tags the
# fn_8012xxxx parser compares against buffer reads), PRNG constants
# (state*0x41C64E6D + 0x3039 LCG step in rand), SWAR/bit-reversal
# masks, GX color words, and write-only object/boot magic sentinels. These are
# checked BEFORE the dict so a coincidental hash can never steal the name.
# M6.87e/M6.88b: replaces QB_UNKNOWN_0x placeholders for this verified subset
# (the M6.87c "never name non-hash literals" rule is relaxed for these).
MANUAL_NAMES = {
    # value: (fixed macro name, comment)
    0x48454144: ("QB_FOURCC_HEAD", 'ASCII "HEAD" — streamed-file header chunk tag'),
    0x56494431: ("QB_FOURCC_VID1", 'ASCII "VID1" — streamed-file chunk tag'),
    0x4652414D: ("QB_FOURCC_FRAM", 'ASCII "FRAM" — streamed-file chunk tag'),
    0x56415544: ("QB_FOURCC_VAUD", 'ASCII "VAUD" — streamed-file chunk tag'),
    0x41C64E6D: ("QB_RNG_LCG_MULT", "PRNG LCG multiplier: state*0x41C64E6D + 0x3039 (rand)"),
    # all-ones (also the QB-hash + CRC init value, fn_8000A778/fn_8000A6D4)
    0xFFFFFFFF: ("QB_UINT32_MAX", "all-ones: UINT32_MAX / -1 — also QB-hash + CRC init"),
    # streamed-file format tags (same fn_8012xxxx parser family)
    0x41554444: ("QB_FOURCC_AUDD", 'ASCII "AUDD" — streamed-file audio-data chunk tag'),
    0x41554448: ("QB_FOURCC_AUDH", 'ASCII "AUDH" — streamed-file audio-header chunk tag'),
    0x56494444: ("QB_FOURCC_VIDD", 'ASCII "VIDD" — streamed-file video-data chunk tag'),
    0x56494448: ("QB_FOURCC_VIDH", 'ASCII "VIDH" — streamed-file video-header chunk tag'),
    0x4E4F4E45: ("QB_STREAM_STATE_NONE", 'ASCII "NONE" — streamed-file loader state: no chunk loaded'),
    # GX immediate-mode color words / color-field masks
    0x080808FF: ("QB_COLOR_GRAY8", "RGBA gray (8,8,8,255) — GX color word (fn_80099B2C)"),
    0x404040FF: ("QB_COLOR_GRAY64", "RGBA gray (64,64,64,255) — GX color word (fn_800903F0)"),
    0x0000FF00: ("QB_MASK_BYTE1", "mask: bits 8-15 (byte 1 of a u32 color word)"),
    0x00FF0000: ("QB_MASK_BYTE2", "mask: bits 16-23 (byte 2 of a u32 color word)"),
    # SWAR / bit-reversal masks (provable from the shift/mask structure in
    # fn_802556C4 palette/LUT builder + fn_80258254)
    0xFF00FF00: ("QB_BITREV_MASK_BYTE_HI", "bit-reverse: high byte of each halfword"),
    0x0F0F0F0F: ("QB_BITREV_MASK_NIBBLE_LO", "bit-reverse: low nibble of each byte"),
    0xF0F0F0F0: ("QB_BITREV_MASK_NIBBLE_HI", "bit-reverse: high nibble of each byte"),
    0x33333333: ("QB_BITREV_MASK_2BIT_LO", "bit-reverse: low 2-bit group of each nibble"),
    0xCCCCCCCC: ("QB_BITREV_MASK_2BIT_HI", "bit-reverse: high 2-bit group of each nibble"),
    0x55555555: ("QB_BITREV_MASK_BIT_LO", "bit-reverse: even-indexed bits"),
    0xAAAAAAAA: ("QB_BITREV_MASK_BIT_HI", "bit-reverse: odd-indexed bits"),
    0x01010101: ("QB_SWAR_ONES", "SWAR: byte-lane add const — DETECTNULL idiom (fn_8026B3A4)"),
    0x10101010: ("QB_RNG_STEP", "PRNG state-step subtract const (rng.c fn_800034E4/fn_8000353C)"),
    # write-only magic sentinels (init markers, never compared)
    0x1234ABCD: ("QB_OBJ_MAGIC", "object-header magic written at struct+0 on init"),
    0xDEADBEEF: ("QB_MAGIC_DEADBEEF", "write-only field magic (fn_8003F608)"),
    0xDEADDEAD: ("QB_MAGIC_DEADDEAD", "write-only field magic (fn_80010AC0)"),
    0xFADEBABE: ("QB_BOOT_SENTINEL_1", "boot-init sentinel magic #1 (fn_8000EE70)"),
    0xFACCED00: ("QB_BOOT_SENTINEL_2", "boot-init sentinel magic #2 (fn_8000EE70)"),
    0xCACCFACC: ("QB_BOOT_SENTINEL_3", "boot-init sentinel magic #3 (fn_8000EE70)"),
    # classic int->double conversion trick: 2^52 written as the hi word
    0x43300000: ("QB_INT_TO_DOUBLE_BIAS", "int->double conversion bias 2^52 (cvt-union hi word)"),
}

# QB_UNKNOWN_0x… placeholder comments (M6.88a). These values are referenced in
# src/wip but no string on the disc or in THPG's debugger table hashes to
# them. The comment records what the value provably IS from its usage context
# (not a guess at a hash name): fdlibm float/double bit patterns (the
# fn_8026/7 math library: floor/pow/log/exp/cos/sin/tan/atan/sqrt/rem_pio2),
# GameCube MMIO register addresses, and single-bit object-state flags. Values
# whose role is NOT provable keep the plain `unknown` comment.
#
# The fdlibm list below is verified: each value appears ONLY inside libm
# files (identified in their headers) as an f32 compare constant, an f64
# hi-word, or an IEEE-754 field mask. Because the same numeric pattern can be
# an f32 literal in one routine and an f64 hi-word in another, comments name
# the *math meaning* and only claim f32/f64 when the usage is unambiguous.
UNKNOWN_COMMENTS = {
    # --- fdlibm IEEE-754 bit patterns ---
    # f64 hi-word of an exact value (low word 0): value is unambiguous
    0x3FF00000: "f64 hi-word of 1.0 — fdlibm pow/log (ix == 1.0 check)",
    0xBFF00000: "f64 hi-word of -1.0 — fdlibm floor (fn_80270290)",
    0x3FE00000: "f64 hi-word of 0.5 — fdlibm pow/sqrt halving",
    0x40100000: "f64 hi-word of 4.0 — fdlibm floor double-round",
    0x7FF00000: "f64 hi-word of +inf — fdlibm inf/nan guard (ix == inf)",
    0xFFF00000: "f64 hi-word of -inf — fdlibm ldexp overflow guard",
    0x7FEFFFFF: "f64 hi-word of DBL_MAX — fdlibm overflow guard",
    # f64 hi-word of a range-reduction constant (verified in source comments)
    0x3FE921FB: "f64 hi-word ~π/4 — fdlibm sin/cos range reduction",
    0x3FF921FB: "f64 hi-word ~π/2 — fdlibm rem_pio2 (fn_802715E4)",
    0x4002D97B: "f64 hi-word ~2π/3 — fdlibm rem_pio2 (fn_802715E4)",
    0x413921FB: "f64 hi-word ~100·π/2 — fdlibm rem_pio2 huge-arg bound",
    # fdlibm f64 field masks / exponent constants (bit patterns, not floats)
    0x000FFFFF: "f64 mantissa low-20 mask — fdlibm floor/log/pow bit work",
    0x00100000: "f64 implicit-bit (2^20) — fdlibm exponent field",
    0x00200000: "f64 1-exponent step (2^21) — fdlibm k_cos",
    0x433FFFFF: "f64 hi-word ≤ 2^52+1 bound — fdlibm pow int-check",
    0x41E00000: "f64 hi-word of 2^31 — fdlibm pow big-int bound",
    0x43F00000: "f64 hi-word of 2^64 — fdlibm pow exp bound",
    0xBF700000: "f64 hi-word (~-2^-8) — fdlibm pow rounding const",
    # fdlibm poly/range bounds — approximate hi-word of the named constant
    0x3E3FFFFF: "f64 hi-word bound ~2^-28 — fdlibm k_cos/k_sin tiny-arg",
    0x3FD33332: "f64 hi-word ~0.3 — fdlibm k_cos poly split",
    0x3FE90000: "f64 hi-word ~0.78 — fdlibm k_cos poly split",
    0x3FDBFFFF: "f64 hi-word ~0.4375 — fdlibm tanh poly split",
    0x3FE5FFFF: "f64 hi-word ~0.6875 — fdlibm tanh poly split",
    0x3FF2FFFF: "f64 hi-word ~1.1875 — fdlibm tanh/exp poly split",
    0x3E1FFFFF: "f64 hi-word ~2^-29 — fdlibm tanh tiny-arg bound",
    0x3E999999: "f32 ~0.3 (poly split) — fdlibm f32 poly (fn_80271948)",
    0x3F480000: "f32 0.78125 — fdlibm f32 poly split (fn_80271948)",
    0x3F490FD8: "f32 ~π/4 (0.785398) — fdlibm cosf/sinf reduction bound",
    0x3FC90FD0: "f32 ~π/2 (1.570796) — fdlibm f32 arg reduction (fn_80271CF4)",
    0x317FFFFF: "f32 ~2^-28 — fdlibm f32 atan2 small-arg bound (fn_80271AE0)",
    0x3F2CA13F: "f32 ~0.6743 — fdlibm f32 atan2 poly split (fn_80271AE0)",
    0x4016CBE3: "f32 ~2.356 (3π/4) — fdlibm f32 arg reduction (fn_80271CF4)",
    0x43490F80: "f32 ~201 (poly domain end) — fdlibm f32 arg reduction",
    0x7FFFFF00: "f32 exponent-field mask — fdlibm fp-class check (fn_80271CF4)",
    0x7FFFFFF0: "f32 top-28-bit mask — fdlibm f32 arg reduction (fn_80271CF4)",
    0xFFF9EB86: "f64 hi-word NaN pattern — fdlibm log NaN check",
    0x3F6F3400: "f64 hi-word ~0.9344 — fdlibm pow poly const",
    0x3FEFFFFE: "f64 hi-word just <1.0 — fdlibm pow |x|≈1 bound",
    0x3FEFFFFF: "f64 hi-word just <1.0 — fdlibm pow |x|<1 bound",
    0x3F2FFFFF: "f64 hi-word bound ~0.6866 — fdlibm f64 trig (fn_80270D9C)",
    # --- GameCube MMIO register addresses (dolphin SDK / VI/EXI/AI regs) ---
    0xCC000000: "MMIO: GC CP (command processor) status reg",
    0xCC00206E: "MMIO: GC SI (serial interface) status reg",
    0xCC003000: "MMIO: GC EXI (external interface) reg",
    0xCC004010: "MMIO: GC EXI control reg",
    0xCC006000: "MMIO: GC AI (audio interface) reg",
    0xCC008000: "MMIO: GC write-only hardware reg (PE/CP fifo)",
    # --- structural bit patterns (role provable from the value + usage) ---
    0xFFFF0000: "mask: high 16 bits (field insert/extract, NaN-reject test)",
    0x80808080: "pattern: high-bit-per-byte (SWAR DETECTNULL; also RGBA gray 128,128,128,128)",
    0x7FFFFFFF: "mask: clear bit 31 (abs value / state-word bit clear)",
    0x3FFFFFFF: "mask: clear top 2 bits (state-word bit clear, fn_8012F360)",
    0x1FFFFFFF: "mask: clear top 3 bits (fn_8028D788)",
    0x0FFFFFFF: "mask: low 28 bits (packed field extract, fn_8017B094)",
    # single-bit object-state flags (struct-word &/| with shifts; some also
    # appear as f64 hi-words in libm — the flag use dominates)
    0x00400000: "flag bit: object-state word (fn_80026AA8)",
    0x01000000: "flag bit: object-state word (widely used; also fp pattern in libm)",
    0x02000000: "flag bit: object-state word (fn_8018B6F8 etc.)",
    0x04000000: "flag bit: object-state word (fn_8012F68C etc.)",
    0x08000000: "flag bit: object-state word (fn_8012EFCC etc.)",
    0x10000000: "flag bit: object-state word (widely used)",
    0x20000000: "flag bit: object-state word (widely used)",
    0x40000000: "flag bit: object-state word (widely used)",
    0x01020304: "pattern: 1,2,3,4 byte sequence (vector/test field, fn_8010E820)",
}


def render_header(resolved, used, unknown=(), manual=()):
    lines = [
        "/* AUTO-GENERATED by tools/gen_qb_constants.py - DO NOT EDIT.         */",
        "/* QB script-hash constants (Neversoft hash, tools/qb_hash.py) that    */",
        "/* appear as magic 0xXXXXXXXX literals or QB_ refs in src/wip.   */",
        "/* come from the .prg plaintext dictionary (trick names, script names, */",
        "/* anim paths). QB_UNKNOWN_0xXXXXXXX placeholders mark referenced      */",
        "/* literals no string on the disc (or THPG debugger table) hashes to — */",
        "/* rename them when a name is identified. Where the value's role is    */",
        "/* provable from usage (fdlibm fp bit patterns, GC MMIO regs) the      */",
        "/* comment says so; the rest are likely QB hashes whose name never     */",
        "/* shipped as data. Regenerate: tools/venv/bin/python                  */",
        "/* tools/gen_qb_constants.py */",
        "#ifndef QB_CONSTANTS_H",
        "#define QB_CONSTANTS_H",
        "",
    ]
    # manual first (fixed names, highest priority — a dict collision must not
    # override a context-verified non-QB name)
    for v in sorted(manual):
        name, comment = manual[v]
        used.add(name)
        lines.append("#define %-28s 0x%08X /* %s */" % (name, v, comment))
    for v in sorted(resolved):
        name = macro_name(resolved[v], used)
        used.add(name)
        lines.append("#define %-28s 0x%08X /* %s */" % (name, v, resolved[v]))
    for v in sorted(unknown):
        name = "QB_UNKNOWN_0x%08X" % v
        used.add(name)
        comment = UNKNOWN_COMMENTS.get(v, "unknown")
        lines.append("#define %-28s 0x%08X /* %s */" % (name, v, comment))
    lines += ["", "#endif /* QB_CONSTANTS_H */", ""]
    return "\n".join(lines)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true",
                    help="exit 1 if the header would change")
    args = ap.parse_args()

    table = load_table(open(DOL_PATH, "rb").read())
    d = build_dict(PRE_DIR, table,
                   extra_globs=[QB_GLOB, REGISTRY_TSV, DOL_RODATA2])
    # Q2: the pre/*_scripts.pr* payloads are LZSS-compressed PRE archives;
    # decoding each inner .qb script recovers its embedded symbol names
    # (VertStickerSlap, WallPlant, ...) that no raw scan can see.
    qb_extract.merge_archive_names(d, table)
    # all lowest-priority gap-fills (never override a script name): DOL
    # data-section tokens (NTSC -> 0x86137A88, "FS " -> 0x73989B82),
    # inner-script tokens (fixblend -> 0x18B98905), raw .qb/.qb.ngc files,
    # hash-validated [u32][name] records (ngc_pal60 -> 0x84BF17AB), then
    # THPG's debugger name table (noextramemory -> 0xAF11B50F, ...).
    merge_dol_tokens(d, table)
    qb_extract.merge_inner_tokens(d, table)
    merge_qb_file_names(d, table)
    merge_dol_hash_records(d, table)
    merge_dbg_names(d, table)
    vals, used_macros = referenced_values()
    cmap = constants_map()  # existing header: value -> macro name
    # macro usages keep their values alive with their EXISTING names
    for macro in used_macros:
        for v, n in cmap.items():
            if n == macro:
                vals.setdefault(v, 0)
    resolved = {}
    unknown = set()
    manual = {}
    for v in vals:
        if v in MANUAL_NAMES:
            manual[v] = MANUAL_NAMES[v]  # context-verified non-QB name (M6.87e)
        elif v in d:
            resolved[v] = d[v]
        elif v in cmap and not cmap[v].startswith('QB_UNKNOWN_0x'):
            resolved[v] = cmap[v]  # still referenced as a macro
        else:
            unknown.add(v)  # no disc string hashes to it — placeholder macro

    used = set()
    text = render_header(resolved, used, unknown, manual)
    total = len(resolved) + len(unknown)

    if os.path.exists(OUT):
        old = open(OUT).read()
        if old == text:
            print("qb_constants.h: %d defines, unchanged" % total)
            return 0
        if args.check:
            print("qb_constants.h: %d defines, WOULD CHANGE (stale)" % total)
            return 1
    open(OUT, "w").write(text)
    print("qb_constants.h: %d defines written (%d resolved literals across src+wip)"
          % (total, sum(vals[v] for v in resolved) + sum(vals[v] for v in unknown)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
