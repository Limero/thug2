#!/usr/bin/env python3
"""Compile every non-stub WIP draft and byte-compare it against the DOL.

The non-stub drafts in src/wip/ contain real best-guess C — but they were
generated as *drafts* and never compiled+compared. Some may match the
original exactly (and can be promoted to real matches), others may be one
tweak away. This tool reports:

  EXACT  — compiled bytes match the DOL (relocation-masked) → promotable
  NEAR   — >50% matching instruction words (worth investigating)
  DIFF   — doesn't match, low similarity
  FAIL   — doesn't compile

Issue-01 FPR handling (M5.0b, extended 2026-09-13): for ANY want whose
prologue saves FPRs (an `stfd` in the first 16 insns after `stwu`), the
draft is tested BOTH as-is and with a `volatile double _dummy;` injected as
the first local — the best verdict wins and EXACT/NEAR rows are tagged
`[dummy]` when the injected variant won. This covers both frame classes:
16-aligned wants are the classic +8 quirk (`pad8`), while 8-aligned wants
are AMBIGUOUS (quirk-on-native-16 vs genuinely-native-8) and must be tried
both ways — see want_fpr_frame(). Non-FPR and already-dummied drafts
(`volatile double` present) are tested as-is.

Usage:
  tools/venv/bin/python tools/test_wip_drafts.py [--family s1] [--addr 0x...]
  tools/venv/bin/python tools/test_wip_drafts.py --addr-file F --extra-cflags "-mps-float"
        # paired-single drafts: compile with -mps-float (per-object only).
        # NOTE: this is applied AUTOMATICALLY for any body containing `__ps_t`
        # (same rule as promote_wip.draft_flags), so the manual flag is only
        # needed for PS-syntax edge cases that don't name the interface.

Reuses gen_leaves.compile_fn (the exact ngccc command + relocation masks).
"""
import glob
import json
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl

ROOT = gl.ROOT
WIP_DIR = f"{ROOT}/src/wip"


def want_fpr_frame(addr):
    """Inspect the original DOL function's prologue to classify its FPR frame.

    Returns (class, frame) where class is:
      'pad8'   — 16-aligned stwu frame with the first stfd at frame-8: the
                 game's +8 headroom (issue-01). The draft needs a
                 `volatile double` dummy to reproduce it.
      'ambig8' — 8-aligned stwu frame (frame % 16 == 8): AMBIGUOUS. Issue-01
                 arithmetic makes an 8-aligned want either a quirk on a
                 native-16 frame (16 + 8 → 24) or a genuinely native 8-aligned
                 frame — the two are indistinguishable from the DOL alone, so
                 the draft must be tried BOTH as-is and with the dummy and the
                 better-scoring variant wins.
    Returns None when the prologue saves no FPRs (no stfd found), or for
    non-stwu (exotic) prologues, which are tested as-is only.
    """
    off = gl.t_off + (addr - gl.t_addr)
    code = gl.d[off:off + 64]
    if len(code) < 12:
        return None
    w0 = struct.unpack_from(">I", code, 0)[0]
    if (w0 >> 26) != 37:  # stwu
        return None
    imm = w0 & 0xFFFF
    if imm & 0x8000:
        imm -= 0x10000
    frame = -imm
    stfd_off = None
    # Scan the whole 64-byte window (not just the first 8 insns): the first
    # stfd is the FPR-save evidence, and multi-double frames put it well below
    # frame-8 (after the other saves). Any stfd proves the frame may carry the
    # +8 quirk, which is all we need for the 8-aligned ambiguous class.
    for k in range(1, len(code) // 4):
        w = struct.unpack_from(">I", code, 4 * k)[0]
        if (w >> 26) == 54:  # stfd
            stfd_off = w & 0xFFFF
            if stfd_off & 0x8000:
                stfd_off -= 0x10000
            break
    if stfd_off is None:
        return None  # not FPR-saving: no frame quirk to reproduce
    if frame % 16 == 8:
        # 8-aligned: quirk-or-native — the caller tries both ways.
        return ("ambig8", frame)
    if stfd_off == frame - 8:
        return ("pad8", frame)
    return None


def inject_dummy(body):
    """Insert `volatile double _dummy;` as the first local of the body."""
    i = body.find("{")
    if i < 0:
        return body
    return body[:i + 1] + "\nvolatile double _dummy;" + body[i + 1:]


def masked_pct(orig, got, masks):
    """Fraction of instruction words that match under the reloc masks.
    Scored over len(orig) words (the WANT range); a shorter GOT leaves
    trailing words as misses, so a dead-code-eliminated compile can never
    reach 100%."""
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


_WANT_SIZES = None


def _want_sizes():
    """addr -> true function size from report.json (cached)."""
    global _WANT_SIZES
    if _WANT_SIZES is None:
        _WANT_SIZES = {}
        rep = json.load(open(f"{ROOT}/build/G2TE52/report.json"))
        for u in rep.get("units", []):
            for fn in u.get("functions", []):
                _WANT_SIZES[int(fn["metadata"]["virtual_address"])] = int(fn["size"])
    return _WANT_SIZES


def test_one(addr, body, extra_flags=None):
    """Compile draft body for fn at addr; return (status, pct, err).
    The compiled .text length IS the function length ngccc produced; if the
    DOL has the same bytes (reloc-masked) at that offset, it's a match —
    whatever remains of the report size belongs to the next function."""
    got, masks = gl.compile_fn(addr, body, extra_flags=extra_flags)
    if got is None:
        return "FAIL", 0.0, "compile error (see gen_leaves output)"
    # Score against the FULL WANT size from report.json, never just len(got):
    # a shorter compile (e.g. dead code after a noreturn call) must not be
    # able to report EXACT against a prefix of the real function.
    want = _want_sizes().get(addr, len(got))
    if want < len(got):
        want = len(got)  # defensive: never truncate the GOT
    orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + want]
    if len(orig) < want:
        return "FAIL", 0.0, "beyond text section"
    pct = masked_pct(orig, got, masks)
    if pct >= 100.0:
        return "EXACT", 100.0, ""
    if pct >= 50.0:
        return "NEAR", pct, ""
    return "DIFF", pct, ""


def main():
    fam_filter = None
    addr_filter = None
    sl = None  # (index, count) for --slice i/m
    addr_set = None  # set of addresses from --addr-file
    extra_flags = None  # e.g. "-mps-float" for paired-single drafts
    if "--family" in sys.argv:
        fam_filter = sys.argv[sys.argv.index("--family") + 1]
    if "--addr" in sys.argv:
        addr_filter = int(sys.argv[sys.argv.index("--addr") + 1], 0)
    if "--addr-file" in sys.argv:
        addr_set = {int(l.strip(), 16) for l in open(sys.argv[sys.argv.index("--addr-file") + 1]) if l.strip()}
    if "--slice" in sys.argv:
        i, m = sys.argv[sys.argv.index("--slice") + 1].split("/")
        sl = (int(i), int(m))
    if "--extra-cflags" in sys.argv:
        extra_flags = sys.argv[sys.argv.index("--extra-cflags") + 1].split()

    rep = json.load(open(f"{ROOT}/build/G2TE52/report.json"))
    fninfo = {}
    for u in rep.get("units", []):
        for fn in u.get("functions", []):
            fninfo[int(fn["metadata"]["virtual_address"])] = int(fn["size"])

    # skip drafts for functions already promoted to src/fn_*.c
    promoted = {int(os.path.basename(p)[3:11], 16)
                for p in glob.glob(f"{ROOT}/src/fn_*.c")}
    # ... and for functions already matched under libs/ (runtime/dolphin/
    # ...) or as named game units (vcall_*, ...): sweeping them wastes time
    # and promote_wip refuses them, so they never leave WIP (gl helper
    # shares the predicate with gen_wip_drafts.py)
    owned = {a for a in gl.build_matched_addrs() if a not in promoted}

    from collections import Counter
    stats = Counter()
    rows = []
    files = sorted(glob.glob(f"{WIP_DIR}/fn_*.c"))
    if sl:
        n = len(files)
        lo = n * sl[0] // sl[1]
        hi = n * (sl[0] + 1) // sl[1]
        files = files[lo:hi]
        print(f"(slice {sl[0]}/{sl[1]}: files {lo}-{hi} of {n})")
    for f in files:
        addr = int(os.path.basename(f)[3:11], 16)
        text = open(f).read()
        if "family=stub" in text or "family=tp" in text:
            continue  # no C body to test
        fam = re.search(r"family=([a-z0-9]+)", text)
        fam = fam.group(1) if fam else "?"
        if fam_filter and fam != fam_filter:
            continue
        if addr_filter and addr != addr_filter:
            continue
        if addr_set and addr not in addr_set:
            continue
        if addr in promoted:
            stats["promoted"] += 1
            continue
        if addr in owned:
            stats["owned"] += 1
            continue
        if addr not in fninfo:
            stats["no-boundary"] += 1
            continue
        size = fninfo[addr]
        # strip header comments + include line; keep just the C body
        body_lines = [l for l in text.splitlines()
                      if not l.startswith("//") and "types.h" not in l]
        body = "\n".join(body_lines).strip()
        # per-draft cflags: a `// FLAG: <flags>` line in the draft header
        # (same syntax promote_wip.py parses) applies only to this draft —
        # needed for -mps-float / -fno-gcse etc. Drafts whose compile differs
        # under a global --extra-cflags keep the global for all drafts.
        draft_flags = list(extra_flags) if extra_flags else []
        for l in text.splitlines():
            m = re.match(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", l)
            if m and not extra_flags:
                # only VALID flag-shaped tokens: the line carries trailing prose
                # and informal variant names, and a bogus token (bare `-`,
                # `-fno-regmove+pin`) makes ngccc abort -> a bare FAIL that no
                # score ranking can see (fn_8026EAAC).
                draft_flags += [t for t in m.group(1).split()
                                if gl.FLAG_TOKEN_RE.match(t)]
        # PS drafts must be built with -mps-float (per-object only). Mirror
        # promote_wip.draft_flags(): a body that uses the paired-single
        # `__ps_t` / `__builtin_ps_*` interface ALWAYS needs it, even when the
        # draft header forgot a `// FLAG: -mps-float` line — without this the
        # whole PS population is scored against the wrong (scalar) codegen.
        # The `__builtin_ps_*` name check matters on its own: a body that
        # calls the PS builtins without naming the `__ps_t` type would
        # otherwise FAIL to compile (or compile scalar) and be mis-reported.
        if ("__ps_t" in text or "__builtin_ps_" in text) and "-mps-float" not in draft_flags:
            draft_flags.append("-mps-float")
        dflags = draft_flags or None
        # issue-01: FPR wants may need the +8 frame. For ANY FPR-saving want
        # (pad8 OR ambig8), test the draft both as-is and with a volatile-double
        # dummy injected and keep the BEST verdict. 16-aligned wants ('pad8')
        # need the dummy outright; 8-aligned wants ('ambig8') are genuinely
        # ambiguous, so the dual test is the only honest way to decide — the
        # losing variant (e.g. a dummy that overshoots a native frame, or a
        # draft that already carries its own stack double) is discarded.
        # Already-dummied drafts (the substring guard) and non-FPR drafts are
        # tested as-is only.
        # NOTE: the guard is a substring check — a `volatile double` appearing
        # only in a /* */ block comment would skip injection (harmless).
        fpr = want_fpr_frame(addr)
        if fpr is not None and "volatile double" not in body:
            s0, p0, e0 = test_one(addr, body, dflags)
            s1, p1, e1 = test_one(addr, inject_dummy(body), dflags)
            # Strictly better only: a genuine frame change always moves the
            # stwu immediate (and every stack offset), so a tie means the
            # dummy changed nothing (e.g. -mps-float already forced the frame)
            # and the as-is variant is the honest winner.
            if p1 > p0:
                status, pct, err, needed_dummy = s1, p1, e1, True
            else:
                status, pct, err, needed_dummy = s0, p0, e0, False
        else:
            status, pct, err, needed_dummy = (*test_one(addr, body, dflags), False)
        stats[status] += 1
        rows.append((status, fam, addr, size, pct, err, needed_dummy))

    print(f"=== results: {dict(stats)} ===")
    for status, fam, addr, size, pct, err, nd in sorted(rows, key=lambda r: -r[4]):
        suffix = " [dummy]" if nd else ""
        if status == "EXACT":
            print(f"  EXACT {fam:4s} 0x{addr:08X} ({size}B){suffix}")
        elif status == "NEAR":
            print(f"  NEAR  {fam:4s} 0x{addr:08X} ({size}B) {pct:.1f}%{suffix}")
    if stats["EXACT"]:
        print("\n=== EXACT (promotable):")
        for status, fam, addr, size, pct, err, nd in rows:
            if status == "EXACT":
                suffix = "  # needs dummy" if nd else ""
                print(f"  0x{addr:08X}{suffix}")
    if stats["FAIL"]:
        print("\n=== FAIL (compile errors):")
        for status, fam, addr, size, pct, err, nd in rows:
            if status == "FAIL":
                print(f"  0x{addr:08X} {fam}: {err[:120]}")


if __name__ == "__main__":
    main()
