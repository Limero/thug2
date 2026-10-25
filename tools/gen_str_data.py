#!/usr/bin/env python3
"""Convert .rodata2 data:string labels into real C data (string-data tier).

For every maximal run of consecutive strings (no foreign symbol between),
emits src/str_<START>.c:
    char lbl_X[] __attribute__((section(".rodata2"))) = "...";
plus static u8 pads copying the exact inter-string/edge padding bytes.

Codegen facts (probed on ngccc 3.9.3, do NOT "simplify"):
- section(".rodata2") is load-bearing: without it the object emits .rodata,
  which links into section 7 instead of section 8.
- char[] initialized from a string literal is ALWAYS 4-aligned with its
  size rounded up to 4 (aligned(1) does not override this). u8 pads pack
  tightly. Hence every string must sit at a 4-relative offset and every
  claim length must be a multiple of 4 (section addralign 4 pads the
  link contribution). Runs violating either stay asm.
- dtk refuses bare pad gaps adjacent to carved ranges ("Unsplit data"),
  so each claim extends to ambient symbol boundaries [S, E), absorbing
  edge pads explicitly. Interior/edge pad bytes are copied verbatim
  (all zero except the section-start 0xFFFFFFFF word).

Every run is layout-SIMULATED against the DOL before writing; failures are
SKIPPED (stay asm). dtk carves each claimed range out of the auto-asm blob
and interleaves the new object by address, so the DOL stays byte-identical
(verified via cmp + ok check).

mwld dead-strips standalone objects for strings nothing references (verified:
the lone unreferenced string's object vanished from main.elf and shifted the
layout). --sync-force-active runs an ELF census over all str_*.c symbols and
rewrites the managed force_active block in config/G2TE52/config.yml with the
missing ones (the project-sanctioned keep-alive, cf. the orphan-fn entries).

Usage:
  tools/venv/bin/python tools/gen_str_data.py [--apply] [--batch i/n]
  tools/venv/bin/python tools/gen_str_data.py --sync-force-active
  Without --apply: dry-run summary only. --batch selects a contiguous slice
  of runs (address order) for batched wire-up + verification.
  Splits.txt and configure.py updates are strip-and-rewrite (idempotent);
  stale str_*.c files from runs that no longer convert are deleted.
"""
import bisect
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

DOL = "orig/G2TE52/sys/main.dol"
SYMBOLS = "config/G2TE52/symbols.txt"
SPLITS = "config/G2TE52/splits.txt"
CONFIGURE = "configure.py"
SRC = "src"

SEC_BASE = 0x8028FB60
SEC_END = SEC_BASE + 0x22840
SEC_OFF = 0x28CB60  # file offset of SEC_BASE in main.dol


def al4(x):
    return (x + 3) & ~3


def c_esc(raw):
    """C-escape string bytes sans trailing NUL (the literal re-adds it)."""
    out = []
    for c in raw:
        if c == 0x22:
            out.append('\\"')
        elif c == 0x5C:
            out.append("\\\\")
        elif c == 0x0A:
            out.append("\\n")
        elif c == 0x0D:
            out.append("\\r")
        elif c == 0x09:
            out.append("\\t")
        elif c == 0x3F:
            out.append("\\?")  # dodge trigraphs (none present, but safe)
        elif 0x20 <= c <= 0x7E:
            out.append(chr(c))
        else:
            out.append("\\%03o" % c)  # fixed 3 digits: unambiguous parse
    return "".join(out)


def pad_decl(addr, raw):
    return ("static unsigned char _pad_%08X[%d] "
            '__attribute__((section(".rodata2"))) = {%s};'
            % (addr, len(raw), ", ".join("0x%02X" % c for c in raw)))


def str_decl(nm, raw):
    return ('char %s[] __attribute__((section(".rodata2"))) = "%s";'
            % (nm, c_esc(raw)))


def load_symbols():
    syms = []
    for line in open(SYMBOLS):
        if ".rodata2" not in line:
            continue
        m = re.match(r"(\S+) = \.rodata2:0x([0-9A-Fa-f]+); // (.*)", line.strip())
        if not m:
            continue
        name, addr, rest = m.groups()
        sz = re.search(r"size:0x([0-9A-Fa-f]+)", rest)
        if not sz:
            continue
        syms.append((int(addr, 16), int(sz.group(1), 16), name, "data:string" in rest))
    syms.sort()
    return syms


def build_runs(syms):
    """Maximal string runs with no foreign symbol start strictly between."""
    strs = [s for s in syms if s[3]]
    foreign = sorted(s[0] for s in syms if not s[3])
    runs = []
    cur = None
    for a, sz, nm, _ in strs:
        if cur is None:
            cur = [(a, sz, nm)]
        else:
            pa = cur[-1][0]
            i = bisect.bisect_left(foreign, pa)
            j = bisect.bisect_left(foreign, a)
            if i == j:
                cur.append((a, sz, nm))
            else:
                runs.append(cur)
                cur = [(a, sz, nm)]
    if cur is not None:
        runs.append(cur)
    return runs


def convert_runs(syms, data):
    """Returns (converted, skipped). converted items: (S, E, decls)."""
    runs = build_runs(syms)
    converted, skipped = [], []
    eprev = None
    for mem in runs:
        base = mem[0][0]
        prevs = [s for s in syms if s[0] < base]
        S = prevs[-1][0] + prevs[-1][1] if prevs else SEC_BASE
        if eprev is not None and eprev > S:
            S = eprev
        nxt = [s for s in syms if s[0] > mem[-1][0]]
        E = nxt[0][0] if nxt else SEC_END
        reason = None
        if S % 4 != 0:
            reason = "claim start not 4-aligned (linker would pad)"
        elif not all((a - S) % 4 == 0 for a, _, _ in mem):
            reason = "string not at 4-relative offset"
        elif (E - S) % 4 != 0:
            reason = "claim length not multiple of 4"
        else:
            # layout simulation: strings auto-4-align+round, pads explicit
            cur = S
            decls = []
            if base > S:
                decls.append(pad_decl(S, data[SEC_OFF + (S - SEC_BASE):
                                                 SEC_OFF + (base - SEC_BASE)]))
                cur = base
            ok = True
            for idx, (a, sz, nm) in enumerate(mem):
                if cur % 4 != 0 or cur != a:
                    ok = False
                    reason = "simulation drift at %s" % nm
                    break
                raw = data[SEC_OFF + (a - SEC_BASE):SEC_OFF + (a - SEC_BASE) + sz]
                if len(raw) != sz or raw[-1:] != b"\x00" or b"\x00" in raw[:-1]:
                    ok = False
                    reason = "bad string bytes at %s" % nm
                    break
                if data[SEC_OFF + (a - SEC_BASE) + sz:
                        SEC_OFF + (a - SEC_BASE) + al4(sz)] != b"\x00" * (al4(sz) - sz):
                    ok = False
                    reason = "nonzero compiler pad at %s" % nm
                    break
                decls.append(str_decl(nm, raw[:-1]))
                cur += al4(sz)
                nxt_a = mem[idx + 1][0] if idx + 1 < len(mem) else E
                if nxt_a > cur:
                    decls.append(pad_decl(cur, data[SEC_OFF + (cur - SEC_BASE):
                                                           SEC_OFF + (nxt_a - SEC_BASE)]))
                    cur = nxt_a
            if ok and cur != E:
                ok = False
                reason = "simulation end mismatch"
            if not ok:
                skipped.append((base, len(mem), reason))
                continue
            converted.append((S, E, decls))
            eprev = E
            continue
        skipped.append((base, len(mem), reason))
    return converted, skipped


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

    data = open(DOL, "rb").read()
    syms = load_symbols()
    converted, skipped = convert_runs(syms, data)
    for base, n, reason in skipped:
        print("SKIP 0x%08X (%d strings): %s" % (base, n, reason))
    print("convertible: %d runs (%d strings)" % (
        len(converted), sum(_count_strings(syms, S, E) for S, E, _ in converted)))

    if batch:
        b, n = batch
        k = (len(converted) + n - 1) // n
        converted = converted[(b - 1) * k:b * k]
        print("batch %d/%d: %d runs" % (b, n, len(converted)))
    if not apply:
        print("(dry run; pass --apply to write)")
        return

    # write sources (rewrite deterministically; skip unchanged files so
    # re-runs don't churn mtimes and trigger rebuilds)
    want_files = set()
    for S, E, decls in converted:
        fp = "%s/str_%08X.c" % (SRC, S)
        want_files.add(fp)
        text = (
            "// Game strings as real C data (generated by tools/gen_str_data.py).\n"
            "// .rodata2 range 0x%08X-0x%08X. section(\".rodata2\") routes the\n"
            "// object into section 8; string literals self-align to 4 with\n"
            "// 4-rounded sizes, pads are explicit. Do not hand-edit.\n" % (S, E)
            + "\n".join(decls) + "\n")
        if not os.path.exists(fp) or open(fp).read() != text:
            open(fp, "w").write(text)
    # delete stale str_ files only in full-set mode (batched runs must
    # not touch sibling batches' files)
    if batch is None:
        for f in sorted(os.listdir(SRC)):
            if (re.match(r"str_[0-9A-F]{8}\.c$", f)
                    and os.path.join(SRC, f) not in want_files):
                os.remove(os.path.join(SRC, f))
                print("removed stale", f)

    # splits: drop blocks whose source is gone; refresh current scope
    # (batch-safe: sibling batches' blocks are untouched)
    def block_for(S, E):
        # align:4 is load-bearing, not cosmetic: dtk's default data align
        # is 8, which makes it SKIP auto-gap creation when the next split
        # sits exactly at the aligned address ("Unsplit data" error).
        # Our objects genuinely need 4 (string literals self-align to 4).
        return ("str_%08X.c:\n\t.rodata2    start:0x%08X end:0x%08X align:4\n"
                % (S, S, E))

    split_txt = open(SPLITS).read()
    for m in re.finditer(r"\nstr_([0-9A-F]{8})\.c:\n(?:\t[^\n]*\n)+", split_txt):
        if not os.path.exists("%s/str_%s.c" % (SRC, m.group(1))):
            split_txt = split_txt.replace(m.group(0), "\n", 1)
    # refresh in place (order-preserving); append only truly new blocks
    appended = 0
    for S, E, _ in converted:
        fn = "str_%08X.c" % S
        pat = re.compile(r"\n%s:\n((?:\t[^\n]*\n)+)" % re.escape(fn))
        m = pat.search(split_txt)
        if m and m.group(1) == "\t.rodata2    start:0x%08X end:0x%08X align:4\n" % (S, E):
            continue  # already exact; leave in place
        split_txt = pat.sub("\n", split_txt)
        split_txt = (split_txt.rstrip("\n") + "\n\n" + block_for(S, E).rstrip("\n")
                     + "\n")
        appended += 1
    if appended:
        open(SPLITS, "w").write(split_txt)

    # configure: drop lines whose source is gone; add missing current-scope
    conf_txt = open(CONFIGURE).read()
    for m in set(re.findall(r'Object\(Matching, "str_([0-9A-F]{8})\.c"\)', conf_txt)):
        if not os.path.exists("%s/str_%s.c" % (SRC, m)):
            conf_txt = re.sub(r'^[ \t]*Object\(Matching, "str_%s\.c"\),\n' % m,
                              "", conf_txt, flags=re.M)
    objs = sorted('            Object(Matching, "str_%08X.c"),\n' % S
                  for S, E, _ in converted)
    missing_o = [o for o in objs if o not in conf_txt]
    if missing_o:
        anchor = '            Object(Matching, "vcall_80230C54.c"),\n'
        assert anchor in conf_txt, "configure anchor moved!"
        conf_txt = conf_txt.replace(anchor, anchor + "".join(missing_o), 1)
    open(CONFIGURE, "w").write(conf_txt)
    print("wrote %d src files, splits/configure synced" % len(converted))


def _count_strings(syms, S, E):
    return sum(1 for a, _, _, isstr in syms if isstr and S <= a < E)


def sync_force_active():
    """Census str_*.c symbols against main.elf; rewrite managed block."""
    import glob
    import subprocess
    defined = {}
    for fp in sorted(glob.glob("%s/str_*.c" % SRC)):
        for m in re.finditer(r"char (lbl_8[0-9A-F]{7})\[\]", open(fp).read()):
            defined[m.group(1)] = fp
    elf = "build/G2TE52/main.elf"
    if not os.path.exists(elf):
        print("no main.elf; skipping force_active sync")
        return
    nm = subprocess.run(
        ["build/binutils/powerpc-eabi-objdump", "-t", elf],
        capture_output=True, text=True).stdout
    present = set(re.findall(r"(lbl_8[0-9A-F]{7})", nm))
    missing = sorted(s for s in defined if s not in present)
    print("str symbols: %d defined, %d missing from ELF" % (len(defined), len(missing)))
    for s in missing:
        print("  missing:", s, "(kept alive via force_active)")
    yml = "config/G2TE52/config.yml"
    txt = open(yml).read()
    begin = "# --- managed by tools/gen_str_data.py: BEGIN (do not hand-edit) ---\n"
    end = "# --- managed by tools/gen_str_data.py: END ---\n"
    assert begin in txt and end in txt, "managed markers missing from config.yml!"
    # Monotonic: the census runs on a build WITH keep-alive active, so it can
    # only discover newly-stripped symbols, never retire entries. Union with
    # the existing block (retiring an entry would re-break the build).
    old_block = txt[txt.index(begin):txt.index(end)]
    keep = sorted(set(re.findall(r"- (lbl_8[0-9A-F]{7})", old_block)) | set(missing))
    block = (begin
             + "# Unreferenced game strings: mwld dead-strips their standalone objects\n"
             + "# (verified: missing from main.elf + shifted layout without the entry).\n"
             + "# Synced from an ELF census; re-run the tool to refresh.\n"
             + "".join("- %s\n" % s for s in keep)
             + end)
    txt = (txt[:txt.index(begin)] + block
           + txt[txt.index(end) + len(end):])
    open(yml, "w").write(txt)
    print("force_active synced: %d entries" % len(keep))


if __name__ == "__main__":
    main()
