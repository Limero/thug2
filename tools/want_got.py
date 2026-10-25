#!/usr/bin/env python3
"""Dump want|got for a wip draft, side by side, in one process.

    tools/venv/bin/python tools/want_got.py 0xADDR [flags...]
    tools/venv/bin/python tools/want_got.py 0xADDR --file /tmp/variant.c

Why this exists: `tools/want_vs_got.py` IGNORES its file argument and always
reads `src/wip/fn_ADDR.c`.  Diagnosing a variant body with it silently diffs
the stale parked draft instead (this has already mis-diagnosed a whole family
as "GCC will not emit `mr r11,r3`" when the copy was in the variant all
along).  This tool takes the body from `--file`, or from the draft, and
compiles it fresh through `gen_leaves.compile_fn` — so it never reads a stale
object either.

Lines marked `>>>` differ after relocation masking (the same comparison
`test_wip_drafts.py` scores, so `100.0%` here means EXACT).

Caveat: this tool does NOT do `test_wip_drafts.py`'s `volatile double _dummy;`
dual-test for FPR-saving wants, so its percentage can be well below the
official verdict on those drafts (e.g. 62% here vs 96.6% reported for
fn_80043800).  It is a *diff* tool — take the verdict from
`test_wip_drafts.py --addr 0x...`.

LENGTH: `want` is the REAL function size (from the draft's `range=` marker, else
`config/G2TE52/symbols.txt` `size:`), NOT `len(got)`.  An earlier version sliced
want to the compiled object's length, so it always printed `want == got` and
silently hid a short object — which is precisely the failure mode AGENTS §6es
warns about (a 4-word shortfall drives the masked score to ~2% even when 80+
instructions are byte-identical, and the tool gave no hint of it).  A SIZE
MISMATCH line is now printed whenever the object is not the exact size, and the
want stream runs to the real end so the missing tail is visible.
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import gen_leaves as gl  # noqa: E402


def real_want_size(addr, path):
    """Bytes of `addr`'s function in the DOL: draft `range=` marker first, then
    symbols.txt.  Returns None if neither is available."""
    for cand in (path, os.path.join(ROOT, "src/wip", f"fn_{addr:08X}.c")):
        if not cand or not os.path.exists(cand):
            continue
        m = re.search(r"^//\s*family=\S+\s+range=0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+)",
                      open(cand, errors="ignore").read(), re.M)
        if m and int(m.group(1), 16) == addr:
            return int(m.group(2), 16) - addr
    try:
        syms = open(os.path.join(ROOT, "config/G2TE52/symbols.txt"),
                    errors="ignore").read()
    except OSError:
        return None
    m = re.search(r"^fn_%08X = \.text:0x[0-9A-Fa-f]+;.*?size:0x([0-9A-Fa-f]+)" % addr,
                  syms, re.M)
    return int(m.group(1), 16) if m else None


def main() -> int:
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    addr = int(sys.argv[1], 16)
    args = sys.argv[2:]
    path = None
    if "--file" in args:
        i = args.index("--file")
        path = args[i + 1]
        del args[i:i + 2]
    flags = args

    if path is None:
        path = os.path.join(ROOT, "src/wip", f"fn_{addr:08X}.c")
    raw = open(path).read()
    body = "\n".join(l for l in raw.splitlines()
                     if not l.lstrip().startswith("//"))

    # Honour the draft's own header flags, exactly like test_wip_drafts.py:
    # `// FLAG:` lines carry trailing prose, so filter with FLAG_TOKEN_RE or
    # the "(measured" text reaches ngccc.
    import re
    for line in raw.splitlines():
        m = re.match(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", line)
        if m:
            flags += [t for t in m.group(1).split() if gl.FLAG_TOKEN_RE.match(t)]

    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="wantgot_")
    if "__ps_t" in body and "-mps-float" not in flags:
        flags = flags + ["-mps-float"]
    got, masks = gl.compile_fn(addr, body, extra_flags=flags or None)
    off = gl.t_off + (addr - gl.t_addr)
    wsize = real_want_size(addr, path)
    if wsize is None:
        wsize = len(got)
        print(f"# WARNING: no `range=` marker or symbols.txt size for 0x{addr:08X}"
              f" — falling back to len(got)={len(got)}B (AGENTS §6cs-1: verify the"
              f" length before reading any diff)")
    want = gl.d[off:off + wsize]
    # keep `got` masks meaningful; masks is keyed by byte offset and the object
    # is the only thing that carries relocations.
    if len(got) > wsize:
        got = got[:wsize]

    try:
        from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs
        cs = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
        wmap = {addr + k * 4: i for k, i in enumerate(cs.disasm(want, addr))}
        gmap = {addr + k * 4: i for k, i in enumerate(cs.disasm(got, addr))}
    except Exception:
        wmap = gmap = {}

    ndiff = 0
    for i in range(min(len(want), len(got)) // 4):
        a = addr + i * 4
        gw = int.from_bytes(want[i * 4:i * 4 + 4], "big")
        gg = int.from_bytes(got[i * 4:i * 4 + 4], "big")
        # masks is keyed by BYTE offset (compile_fn stores `p & ~3`) and holds
        # the bits TO COMPARE (0xFC000003 = opcode+AA+LK for REL24,
        # 0xFFFF0000 = the ADDR16 displacement-free part for HA/LO), not the
        # bits to ignore.
        m = masks.get(i * 4, 0xFFFFFFFF)
        same = (gw & m) == (gg & m)
        ndiff += not same
        w = wmap.get(a)
        g = gmap.get(a)
        wt = f"{w.mnemonic} {w.op_str}".strip() if w else "?"
        gt = f"{g.mnemonic} {g.op_str}".strip() if g else "?"
        flag = "   " if same else ">>>"
        print(f"{a:08X} {flag} W:{wt:34s} G:{gt}")
    pct = 100.0 * (min(len(want), len(got)) // 4 - ndiff) / max(1, min(len(want), len(got)) // 4)
    print(f"# source {path}  want {len(want)}B got {len(got)}B  diffs {ndiff}  {pct:.2f}%"
          f"  flags={' '.join(flags) or 'none'}")
    dw = len(want) - len(got)
    if dw:
        print(f"# SIZE MISMATCH: object is {abs(dw)}B ({abs(dw) // 4} word"
              f"{'s' if abs(dw) // 4 != 1 else ''}) "
              f"{'SHORT of' if dw > 0 else 'LONG vs'} want — per AGENTS §6cs-1 /"
              f" §6es the index-aligned score above is MEANINGLESS until the length"
              f" matches; the missing tail is printed as `?` (got has no code there).")
    print("# NOTE: no _dummy dual-test here; official verdict = test_wip_drafts.py --addr")
    return 0


if __name__ == "__main__":
    sys.exit(main())
