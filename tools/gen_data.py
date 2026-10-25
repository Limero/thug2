#!/usr/bin/env python3
"""Convert remaining .rodata2 / .rodata / .data labels into real C data.

Companion to tools/gen_str_data.py (which owns the string runs in
src/str_*.c; those ranges are never touched here). This tool converts every
other data symbol in .rodata2 + .rodata, plus writable .data: float/double spans (decimal literals, round-trip
verified), 4byte/2byte spans (hex words), byte/object spans (verbatim hex
bytes). Pointer words are deliberately literalized as u32 hex (byte-exact
today; the 5 known vtables live in .data, not here, so no tier-2 runway is
blocked).

One file per maximal convertible run: src/r2d_<S>.c (.rodata2) /
src/rd_<S>.c (.rodata). Filenames carry the claim start.

Probed ngccc 3.9.3 codegen rules (do NOT "simplify"):
- section(".rodata2") / section(".rodata") routes the object (module
  .rodata would land in section 7 either way; explicit is documentation).
- EVERY array object is 4-aligned with 4-rounded size, static or global,
  any element type (probed: u8[1]/[2]/[3]/[5] all land on 4-multiples;
  doubles/u64 are 8-aligned). There is no packed form: odd gaps and
  4-inconsistent spans cannot be expressed and stay asm.
- float/u32: 4-aligned; double/u64: 8-aligned (rel 4-mod-8 doubles render
  as u32 pairs: identical bytes, address unchanged); u16: 4-aligned minimum.
- File addralign = 8 iff any double/u64 else 4; claims need
  (S-SEC)%aa == 0 and (E-S)%aa == 0 (assembler pads section tails).
- Per-split align:4 (dtk default data align 8 skips auto-gap creation at
  exact-fit boundaries -> "Unsplit data" error; our objects truly need 4,
  doubles are placed exactly by the guards).
- mwld dead-strips unreferenced standalone objects: --sync-force-active
  runs an ELF census over ALL generated data symbols (any name, incl.
  hand-named ones like ClampRegion) and maintains the managed block
  (shared with gen_str_data.py via the same BEGIN/END markers; monotonic).

Gates (a run converts only if ALL pass):
1. layout simulation vs DOL bytes (offsets, compiler-inserted zero pads,
   NUL termination, no foreign symbols in spans);
2. object verification: compile with the exact cflags_game and byte-compare
   the section against the DOL slice (catches float-parse drift etc.).
Failures stay asm (unwired, file deleted).

Usage:
  tools/venv/bin/python tools/gen_data.py [--apply]
  tools/venv/bin/python tools/gen_data.py --verify [--batch i/n]
  tools/venv/bin/python tools/gen_data.py --sync-force-active
Splits/configure updates are idempotent. Writable .data uses
the same rules (plain initialized globals); .sdata/.bss/.sbss are OUT OF
SCOPE (small-data needs per-object -msdata handling; bss has no bytes).
"""
import glob
import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from gen_str_data import c_esc  # noqa: E402 (single source for the escaper)

DOL = "orig/G2TE52/sys/main.dol"
SYMBOLS = "config/G2TE52/symbols.txt"
SPLITS = "config/G2TE52/splits.txt"
CONFIGURE = "configure.py"
YML = "config/G2TE52/config.yml"

SECS = {
    # name: (base, end, fileoff, srcprefix, csect)
    ".rodata2": (0x8028FB60, 0x8028FB60 + 0x22840, 0x28CB60, "r2d", ".rodata2"),
    ".rodata": (0x8028E040, 0x8028E040 + 0x1B20, 0x28B040, "rd", ".rodata"),
    ".data": (0x802B23A0, 0x802B23A0 + 0x5E740, 0x2AF3A0, "dd", ".data"),
}
DAT_PREFIXES = tuple(p for _, _, _, p, _ in SECS.values())
SEC_BY_PREFIX = {p: sec for sec, (_, _, _, p, _) in SECS.items()}
CFLAGS = ["-O2", "-G0", "-mcpu=750", "-fno-common", "-I", "include",
          "-I", "build/G2TE52/include", "-DNDEBUG=1", "-DVERSION_G2TE52"]
NGCCC = "build/compilers/ProDG/3.9.3/ngccc.exe"
WIBO = "build/tools/wibo"
OBJDUMP = "build/binutils/powerpc-eabi-objdump"
SN_PATH = "build/compilers/ProDG/3.9.3"


def al4(x):
    return (x + 3) & ~3


def dol_bytes(addr, n):
    if n == 0:
        return b""
    for sec, (b, e, o, p, c) in SECS.items():
        if b <= addr < e:
            with open(DOL, "rb") as f:
                f.seek(o + (addr - b))
                return f.read(n)
    raise AssertionError(hex(addr))


def load_symbols():
    syms = []
    for line in open(SYMBOLS):
        m = re.match(r"(\S+) = \.([a-z0-9]+):0x([0-9A-Fa-f]+); // (.*)", line.strip())
        if not m:
            continue
        name, sec, addr, rest = m.groups()
        sec = "." + sec
        if sec not in SECS:
            continue
        sz = re.search(r"size:0x([0-9A-Fa-f]+)", rest)
        if not sz:
            continue
        syms.append((int(addr, 16), int(sz.group(1), 16), name, rest, sec))
    syms.sort()
    return syms


def owned_ranges():
    """Foreign C-claimed data ranges [(S, E)]: str_ files (other tool),
    hand-maintained units (dvd/*.c etc.). Our own dat_ claims are
    deliberately EXCLUDED (they're recomputed outputs; treating them as
    obstacles makes re-runs see a different world than the first run).
    New runs never touch any of these."""
    out = []
    txt = open(SPLITS).read()
    for m in re.finditer(r"(?m)^(\S+):$\n((?:\t[^\n]*\n?)*)", txt):
        name, body = m.group(1), m.group(2)
        if not name.endswith(".c"):
            continue
        if re.match(r"(?:r2d|rd|dd)_[0-9A-F]{8}\.c$", name):
            continue
        for dm in re.finditer(
                r"\.(?:rodata2?|data|sdata2?|sbss?|bss)\s+start:0x([0-9A-Fa-f]+)"
                r" end:0x([0-9A-Fa-f]+)", body):
            out.append((int(dm.group(1), 16), int(dm.group(2), 16)))
    return sorted(out)


PTR_LO, PTR_HI = 0x80003100, 0x803D0000  # static address space (text..sbss)


def has_pointer(syms_by_addr, addr, sz, raw):
    """True if any 4-byte word looks like a relocated pointer: value in
    static address space AND a symbol starts exactly there. Such words are
    reference-graph edges (vtable slots, registry handlers, callbacks);
    literalizing them orphans code and mwld dead-strips it (verified:
    2224 functions stripped incl. matched ones). Strings are exempt (char
    literals emit no relocations, so they hold no edges); pads are zeros
    outside the range by construction."""
    for i in range(0, sz - 3, 4):
        w = int.from_bytes(raw[i:i + 4], "big")
        if PTR_LO <= w <= PTR_HI and w in syms_by_addr:
            return True
    return False


def float_lit(raw4):
    import math
    v = struct.unpack(">f", raw4)[0]
    if not math.isfinite(v):
        return None  # inf/nan have no C89 decimal spelling (-> u32 hex)
    s = repr(float(v))
    if struct.pack(">f", float(s)) != raw4:
        return None
    return s + "f"


def double_lit(raw8):
    import math
    v = struct.unpack(">d", raw8)[0]
    if not math.isfinite(v):
        return None
    s = repr(v)
    if struct.pack(">d", float(s)) != raw8:
        return None
    return s


def sym_decl(addr, sz, name, rest, raw, csect):
    """Returns (decl, align, rounded) or None if unrepresentable."""
    attr = '__attribute__((section("%s")))' % csect
    if "data:string" in rest:
        if len(raw) != sz or raw[-1:] != b"\x00" or b"\x00" in raw[:-1]:
            return None
        return ('char %s[] %s = "%s";' % (name, attr, c_esc(raw[:-1])), 4, al4(sz))
    if "data:float" in rest:
        if sz % 4 or sz == 0:
            return None
        lits = [float_lit(raw[i:i + 4]) for i in range(0, sz, 4)]
        if any(l is None for l in lits):
            ws = ["0x%s" % raw[i:i + 4].hex().upper() for i in range(0, sz, 4)]
            return ("unsigned int %s[%d] %s = {%s};"
                    % (name, len(ws), attr, ", ".join(ws)), 4, sz)
        return ("float %s[%d] %s = {%s};"
                % (name, len(lits), attr, ", ".join(lits)), 4, sz)
    if "data:double" in rest:
        if sz % 8 or sz == 0:
            return None
        lits = [double_lit(raw[i:i + 8]) for i in range(0, sz, 8)]
        if any(l is None for l in lits):
            ws = [raw[i:i + 8].hex().upper() + "ULL" for i in range(0, sz, 8)]
            return ("unsigned long long %s[%d] %s = {%s};"
                    % (name, len(ws), attr, ", ".join(ws)), 8, sz)
        return ("double %s[%d] %s = {%s};"
                % (name, len(lits), attr, ", ".join(lits)), 8, sz)
    if "data:4byte" in rest:
        if sz % 4 or sz == 0:
            return None
        ws = ["0x%s" % raw[i:i + 4].hex().upper() for i in range(0, sz, 4)]
        return ("unsigned int %s[%d] %s = {%s};"
                % (name, len(ws), attr, ", ".join(ws)), 4, sz)
    if "data:2byte" in rest:
        if sz % 2 or sz == 0:
            return None
        ws = ["0x%s" % raw[i:i + 2].hex().upper() for i in range(0, sz, 2)]
        # arrays align 4 minimum (probed), even u16
        return ("unsigned short %s[%d] %s = {%s};"
                % (name, len(ws), attr, ", ".join(ws)), 4, al4(sz))
    if sz == 0:
        return None
    # data:byte + untyped object spans: verbatim bytes. Arrays align 4
    # minimum with 4-rounded size (probed), like every other array.
    ws = ["0x%02X" % c for c in raw]
    return ("unsigned char %s[%d] %s = {%s};"
            % (name, len(raw), attr, ", ".join(ws)), 4, al4(sz))


def pad_decl(addr, raw, csect):
    return ("static unsigned char _pad_%08X[%d] "
            '__attribute__((section("%s"))) = {%s};'
            % (addr, len(raw), csect, ", ".join("0x%02X" % c for c in raw)))


def u32pair_decl(nm, raw, csect):
    """Double/u64 span rendered as u32 words: same bytes, 4-aligned."""
    attr = '__attribute__((section("%s")))' % csect
    ws = ["0x%s" % raw[i:i + 4].hex().upper() for i in range(0, len(raw), 4)]
    return ("unsigned int %s[%d] %s = {%s};"
            % (nm, len(ws), attr, ", ".join(ws)), 4, len(raw))


def block_for(prefix, S, E, csect):
    # align:4 is load-bearing (see docstring); our objects truly need 4,
    # doubles are placed exactly by the (S-SEC)%8/(E-S)%8 guards.
    return ("%s_%08X.c:\n\t%s    start:0x%08X end:0x%08X align:4\n"
            % (prefix, S, csect, S, E))


def convert_runs(syms, owned):
    """Returns (converted, skipped). converted items: (prefix,S,E,decls,csect).

    S = first symbol's start (leading gaps stay auto-covered). E would
    ideally be next_sym.start, but the claim length must satisfy the file
    addralign (8 with doubles/u64, else 4: the assembler pads section
    tails), so E is the largest 8/4-consistent symbol start (or E_max).
    Tiling is automatic: dtk fills every inter-claim gap itself.
    """
    # Pointer-target universe: EVERY section (code pointers dominate).
    # A data-only set here once missed all .text targets and let 2224
    # functions get dead-stripped.
    addrs = set()
    for line in open(SYMBOLS):
        m = re.match(r"\S+ = \.[a-z0-9]+:0x([0-9A-Fa-f]+);", line.strip())
        if m:
            addrs.add(int(m.group(1), 16))
    cand = [s for s in syms if not any(o_s <= s[0] < o_e for o_s, o_e in owned)]
    by_sec = {}
    for s in cand:
        by_sec.setdefault(s[4], []).append(s)
    converted, skipped = [], []
    for sec in sorted(by_sec):
        SECB, SECE, SECOFF, PREFIX, CSECT = SECS[sec]
        # maximal runs: no owned-range intersection inside
        runs, cur = [], None
        for s in by_sec[sec]:
            if cur is None:
                cur = [s]
            else:
                lo, hi = cur[-1][0], s[0]
                if any(o_s < hi and o_e > lo for o_s, o_e in owned):
                    runs.append(cur)
                    cur = [s]
                else:
                    cur.append(s)
        if cur is not None:
            runs.append(cur)
        for mem in runs:
            S = mem[0][0]
            nxt = [s for s in syms if s[4] == sec and s[0] > mem[-1][0]]
            E_max = nxt[0][0] if nxt else SECE
            # clamp E at the next owned claim (never overlap dvd/str/etc.)
            for o_s, o_e in owned:
                if o_s > S and o_s < E_max:
                    E_max = o_s
            # split run at pointer-bearing non-string symbols: barrier
            # symbols stay auto (edges preserved); clean sub-spans convert.
            # Each piece records elim: the bound its claim may not cross
            # (next barrier's start, else the run's E_max). Letting E cross
            # a barrier covers an undefined symbol (link error) AND
            # literalizes its pointer words (dead-strip avalanche).
            pieces, curpiece = [], []
            for s in mem:
                a, sz, nm, rest, _ = s
                if ("data:string" not in rest
                        and has_pointer(addrs, a, sz, dol_bytes(a, sz))):
                    if curpiece:
                        pieces.append((curpiece, a))
                        curpiece = []
                else:
                    curpiece.append(s)
            if curpiece:
                pieces.append((curpiece, E_max))
            if not pieces:
                skipped.append((mem[0][0], len(mem), "all pointer words"))
                continue
            for piece, elim in pieces:
                ok_piece, why = convert_piece(syms, sec, SECB, SECE, CSECT,
                                              elim, piece)
                if ok_piece is None:
                    skipped.append((piece[0][0], len(piece), why))
                    continue
                converted.append(ok_piece)
    return converted, skipped


def convert_piece(syms, sec, SECB, SECE, CSECT, E_max, mem):
    """Convert one pointer-free run piece.

    Returns ((PREFIX, S, E, decls, CSECT), None) or (None, reason).
    S = first start; E = largest aa-consistent symbol start (or E_max);
    trail pad explicit. Callers guarantee no pointer words in mem.
    """
    PREFIX = SECS[sec][3]
    S = mem[0][0]
    # pass 1: symbols + interior pads (E-independent). Entries carry
    # spans so E-truncation below cuts on boundaries.
    entries, rel, ok, reason = [], 0, True, None
    for idx, (a, sz, nm, rest, _) in enumerate(mem):
        raw = dol_bytes(a, sz)
        d = sym_decl(a, sz, nm, rest, raw, CSECT)
        if d is None:
            ok = False
            reason = "unrepresentable symbol %s" % nm
            break
        text, align, rounded = d
        if align == 8 and rel % 8 != 0:
            # Double/u64 at 4-mod-8 rel: render as u32 words
            # (identical bytes, 4-aligned; address unchanged).
            if sz % 4 != 0:
                ok = False
                reason = "unfallback-able span %s" % nm
                break
            text, align, rounded = u32pair_decl(nm, raw, CSECT)
        if rel % align != 0 or S + rel != a:
            ok = False
            reason = "misaligned symbol %s" % nm
            break
        if a + rounded > SECE:
            ok = False
            reason = "compiler pad overruns section end at %s" % nm
            break
        if dol_bytes(a + sz, rounded - sz) != b"\x00" * (rounded - sz):
            ok = False
            reason = "nonzero compiler pad at %s" % nm
            break
        entries.append((text, S + rel, S + rel + rounded))
        rel += rounded
        if idx + 1 < len(mem):
            nxt_a = mem[idx + 1][0]
            gap = nxt_a - (S + rel)
            if gap < 0:
                ok = False
                reason = "overlap at %s" % nm
                break
            # Explicit pads are arrays too (4-align + 4-round); a gap
            # with size%4 != 0 cannot be expressed.
            if gap % 4 != 0:
                ok = False
                reason = "4-inconsistent gap at %s" % nm
                break
            if gap > 0:
                entries.append((pad_decl(S + rel, dol_bytes(S + rel, gap), CSECT),
                                S + rel, nxt_a))
                rel += gap
    if not ok:
        return None, reason
    has8 = any(t.startswith("double ") or t.startswith("unsigned long long ")
               for t, _, _ in entries)
    aa = 8 if has8 else 4
    if (S - SECB) % aa != 0:
        return None, "claim start misaligned for addralign %d" % aa
    cands = [s[0] for s in mem[1:]] + [E_max]
    Eb = [E for E in cands if E > S and (E - S) % aa == 0]
    if not Eb:
        return None, "no valid claim end"
    E = max(Eb)
    kept = [(t, s, e) for (t, s, e) in entries if s < E]
    decls = [t for (t, s, e) in kept]
    tail = E - (kept[-1][2] if kept else S)
    if tail > 0:
        decls.append(pad_decl(E - tail, dol_bytes(E - tail, tail), CSECT))
    elif tail < 0:
        return None, "truncation overrun"
    return (PREFIX, S, E, decls, CSECT), None
def file_text(prefix, S, E, decls, csect):
    return (
        "// Game data as real C data (generated by tools/gen_data.py).\n"
        "// %s range 0x%08X-0x%08X. Pointer words are deliberate u32\n"
        "// literals (byte-exact; vtables live in .data). Do not hand-edit.\n"
        % (csect, S, E) + "\n".join(decls) + "\n")


def wire(converted):
    """Write sources + splits/configure updates. Returns files.

    Single source of truth: the current converted set. Stale blocks,
    object lines, and source files from runs that no longer convert are
    removed (a leftover claim overlapping a fresh one breaks dtk with
    "overlaps with previous split"). Idempotent; --apply always wires the
    full set (--batch only scopes --verify).
    """
    import glob
    wantfiles = set("src/%s_%08X.c" % (p, S) for p, S, E, d, c in converted)
    pre = "(?:%s)" % "|".join(DAT_PREFIXES)
    for pat in ["src/%s_*.c" % p for p in DAT_PREFIXES]:
        for fp in glob.glob(pat):
            if fp not in wantfiles:
                os.remove(fp)
                print("removed stale", fp)
    split_txt = open(SPLITS).read()
    # Fixpoint strip: adjacent blocks share their boundary newline, so one
    # pass only removes every other block. Blank-line separation on append
    # (below) keeps future strips single-pass, but loop regardless.
    pat = re.compile(r"\n(?:%s)_[0-9A-F]{8}\.c:\n(?:\t[^\n]*\n)+" % pre)
    while True:
        split_txt, n = pat.subn("\n", split_txt)
        if n == 0:
            break
    files = []
    for prefix, S, E, decls, csect in converted:
        fp = "src/%s_%08X.c" % (prefix, S)
        files.append(fp)
        text = file_text(prefix, S, E, decls, csect)
        if not os.path.exists(fp) or open(fp).read() != text:
            open(fp, "w").write(text)
    blocks = [block_for(prefix, S, E, csect).rstrip("\n")
              for prefix, S, E, decls, csect in converted]
    split_txt = split_txt.rstrip("\n") + "\n\n" + "\n\n".join(blocks) + "\n"
    open(SPLITS, "w").write(split_txt)
    # self-check: no overlapping claims (dtk would reject the build)
    claims = []
    for m in re.finditer(
            r"((?:%s)_[0-9A-F]{8}|str_[0-9A-F]{8})\.c:\n"
            r"\t\.(?:rodata2?|data)\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)"
            % pre, split_txt):
        claims.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    claims.sort(key=lambda x: x[1])
    bad = [(a, b) for a, b in zip(claims, claims[1:]) if a[2] > b[1]]
    assert not bad, "overlapping claims remain: %s" % bad[:3]
    conf_txt = open(CONFIGURE).read()
    conf_txt = re.sub(r'^[ \t]*Object\(Matching, "(?:%s)_[0-9A-F]{8}\.c"\),\n' % pre,
                      "", conf_txt, flags=re.M)
    objs = sorted('            Object(Matching, "%s_%08X.c"),\n' % (prefix, S)
                  for prefix, S, E, decls, csect in converted)
    anchor = '            Object(Matching, "vcall_80230C54.c"),\n'
    assert anchor in conf_txt, "configure anchor moved!"
    conf_txt = conf_txt.replace(anchor, anchor + "".join(objs), 1)
    open(CONFIGURE, "w").write(conf_txt)
    return files


def verify(files):
    """Compile each file with cflags_game; byte-compare section vs DOL.

    Returns (ok_files, bad_files). Bad files are UNWIRED (claims + objects
    removed, file deleted) so the link never sees them.
    """
    import tempfile
    ok, bad = [], []
    for fp in files:
        m = re.match(r"src/((?:%s)_[0-9A-F]{8})\.c$" % "|".join(DAT_PREFIXES), fp)
        prefix = m.group(1).split("_")[0]
        S = int(m.group(1).split("_")[1], 16)
        csect = SEC_BY_PREFIX[prefix]
        SECB, SECE, SECOFF, _, _ = SECS[csect]
        with tempfile.TemporaryDirectory() as td:
            obj = os.path.join(td, "t.o")
            env = dict(os.environ, SN_NGC_PATH=SN_PATH)
            r = subprocess.run([WIBO, NGCCC] + CFLAGS + ["-c", fp, "-o", obj],
                               capture_output=True, env=env)
            if r.returncode != 0:
                print("VERIFY COMPILE-FAIL %s" % fp)
                bad.append(fp)
                continue
            r = subprocess.run([OBJDUMP, "-s", "-j", csect, obj],
                               capture_output=True, text=True)
            got = bytearray()
            for line in r.stdout.splitlines():
                mm = re.match(r"^\s*[0-9a-f]+ ([0-9a-f ]+?)(?:\s{2,}.*)?$", line)
                if mm:
                    got += bytes.fromhex(mm.group(1).replace(" ", ""))
            want = dol_bytes(S, len(got))
            # section may carry trailing link padding; compare content prefix
            # and require exact size match via the claim instead
            if bytes(got) != want[:len(got)]:
                print("VERIFY CONTENT-DIFF %s (%d bytes)" % (fp, len(got)))
                bad.append(fp)
                continue
            # exact-size check: object section size must equal claim length
            r = subprocess.run([OBJDUMP, "-h", obj], capture_output=True, text=True)
            mh = re.search(r"%s\s+([0-9a-f]+)" % re.escape(csect), r.stdout)
            if not mh:
                print("VERIFY NO-SECTION %s" % fp)
                bad.append(fp)
                continue
            # claim length lookup
            E = None
            for mm in re.finditer(
                    r"%s_%08X\.c:\n\t%s    start:0x[0-9A-F]+ end:0x([0-9A-F]+)"
                    % (prefix, S, re.escape(csect)), open(SPLITS).read()):
                E = int(mm.group(1), 16)
            if E is None or int(mh.group(1), 16) != E - S:
                print("VERIFY SIZE-DIFF %s (obj %s, claim %s)" % (fp, mh.group(1) if mh else "?", E - S if E else "?"))
                bad.append(fp)
                continue
            ok.append(fp)
    for fp in bad:
        m = re.match(r"src/((?:%s)_[0-9A-F]{8})\.c$" % "|".join(DAT_PREFIXES), fp)
        fn = m.group(1)
        txt = open(SPLITS).read()
        txt = re.sub(r"\n%s:\n(?:\t[^\n]*\n)+" % re.escape(fn), "\n", txt)
        open(SPLITS, "w").write(txt)
        txt = open(CONFIGURE).read()
        txt = re.sub(r'^[ \t]*Object\(Matching, "%s"\),\n' % re.escape(fn + ".c"),
                     "", txt, flags=re.M)
        open(CONFIGURE, "w").write(txt)
        os.remove(fp)
        print("unwired + deleted %s" % fp)
    print("verify: %d ok, %d bad" % (len(ok), len(bad)))
    return ok, bad


def sync_force_active():
    """Census ALL generated data symbols vs main.elf; rewrite managed block."""
    defined = {}
    pats = ["src/str_*.c"] + ["src/%s_*.c" % p for p in DAT_PREFIXES] + ["src/vt_*.c"]
    fps = []
    for pat in pats:
        fps.extend(sorted(glob.glob(pat)))
    for fp in fps:
        for m in re.finditer(
                r"^(?:const )?(?:unsigned long long|unsigned int|unsigned short"
                r"|unsigned char|char|float|double|void\s*\*|struct\s+\w+)\s*(\w+)(?:\[|\s*=)",
                open(fp).read(), re.M):
            if m.group(1).startswith("_pad_"):
                continue
            defined[m.group(1)] = fp
    elf = "build/G2TE52/main.elf"
    if not os.path.exists(elf):
        print("no main.elf; skipping force_active sync")
        return
    nm = subprocess.run([OBJDUMP, "-t", elf], capture_output=True, text=True).stdout
    present = set(re.findall(r" ([A-Za-z_]\w*)", nm))
    missing = sorted(s for s in defined if s not in present)
    print("data symbols: %d defined, %d missing from ELF" % (len(defined), len(missing)))
    for s in missing:
        print("  missing:", s, "(kept alive via force_active)")
    begin = "# --- managed by tools/gen_str_data.py: BEGIN (do not hand-edit) ---\n"
    end = "# --- managed by tools/gen_str_data.py: END ---\n"
    txt = open(YML).read()
    assert begin in txt and end in txt, "managed markers missing!"
    old_block = txt[txt.index(begin):txt.index(end)]
    # Line-anchored parse (an inline "- (\w+)" once matched "- managed" in
    # the BEGIN marker and poisoned force_active). Intersect with defined
    # symbols so junk can never persist: entries must come from our files.
    old_entries = set(re.findall(r"^- ([A-Za-z_]\w*)$", old_block, re.M))
    keep = sorted((old_entries & set(defined)) | set(missing))
    block = (begin
             + "# Unreferenced game data: mwld dead-strips standalone objects\n"
             + "# (verified: missing from main.elf + shifted layout without it).\n"
             + "# Synced from an ELF census (tools/gen_data.py); monotonic.\n"
             + "".join("- %s\n" % s for s in keep)
             + end)
    txt = txt[:txt.index(begin)] + block + txt[txt.index(end) + len(end):]
    open(YML, "w").write(txt)
    print("force_active synced: %d entries" % len(keep))


def main():
    if "--sync-force-active" in sys.argv:
        sync_force_active()
        return
    apply = "--apply" in sys.argv
    batch = None
    if "--batch" in sys.argv:
        i = sys.argv.index("--batch")
        b, n = sys.argv[i + 1].split("/")
        batch = (int(b), int(n))
    if "--verify" in sys.argv:
        syms = load_symbols()
        owned = owned_ranges()
        converted, _ = convert_runs(syms, owned)
        if batch:
            b, n = batch
            k = (len(converted) + n - 1) // n
            converted = converted[(b - 1) * k:b * k]
        # same slices as --apply: derive files from runs, keep existing ones
        files = ["src/%s_%08X.c" % (p, S) for p, S, E, d, c in converted]
        files = [f for f in files if os.path.exists(f)]
        verify(files)
        return
    syms = load_symbols()
    owned = owned_ranges()
    converted, skipped = convert_runs(syms, owned)
    for base, n, reason in skipped:
        print("SKIP 0x%08X (%d syms): %s" % (base, n, reason))
    print("convertible: %d runs" % len(converted))
    if batch:
        print("(note: --batch only scopes --verify; --apply always wires the full set)")
    if not apply:
        print("(dry run; pass --apply to write)")
        return
    files = wire(converted)
    print("wrote %d src files, splits/configure synced" % len(files))


if __name__ == "__main__":
    main()
