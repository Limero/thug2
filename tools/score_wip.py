#!/usr/bin/env python3
"""Strict scorer for a wip draft: masked byte compare clamped to the symbol
size AND the internal-branch gate that tools/promote_wip.py enforces.

Usage: tools/venv/bin/python tools/score_wip.py 0xADDR file.c [flags...]

Unlike the scratch scorers this one never compares past the end of the
function (a draft that compiles LONGER than the symbol would otherwise be
scored against the NEXT function's retail bytes, which silently reports a
garbage percentage).
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
import br_targets  # noqa: E402


def symbol_size(addr):
    with open(os.path.join(ROOT, "config/G2TE52/symbols.txt")) as fh:
        for line in fh:
            m = re.match(r"^\S+\s*=\s*\.text:0x([0-9A-Fa-f]+);.*size:0x([0-9A-Fa-f]+)", line)
            if m and int(m.group(1), 16) == addr:
                return int(m.group(2), 16)
    return None


def main():
    addr = int(sys.argv[1], 16)
    path = sys.argv[2]
    flags = [a for a in sys.argv[3:] if a.startswith("-")]
    raw = open(path).read()
    body = "\n".join(l for l in raw.splitlines() if not l.lstrip().startswith("//"))
    size = symbol_size(addr)
    os.environ["LEAF_TMPDIR"] = tempfile.mkdtemp(prefix="sw_")
    if ("__ps_t" in body or "__builtin_ps_" in body) and "-mps-float" not in flags:
        flags = flags + ["-mps-float"]
    got, masks = gl.compile_fn(addr, body, extra_flags=flags or None)
    if got is None:
        print("COMPILE FAIL:", masks)
        sys.exit(1)
    off = gl.t_off + (addr - gl.t_addr)
    want = gl.d[off:off + (size or len(got))]
    if size and len(got) > size:
        print(f"!! got {len(got)}B > symbol {size}B — score is clamped, fix the size first")
    n = min(len(want), len(got)) // 4
    nd = 0
    lines = []
    for i in range(n):
        a = addr + i * 4
        gw = int.from_bytes(want[i * 4:i * 4 + 4], "big")
        gg = int.from_bytes(got[i * 4:i * 4 + 4], "big")
        m = masks.get(i * 4, 0xFFFFFFFF)
        if (gw & m) != (gg & m):
            nd += 1
            lines.append(f"{a:08X}  W:{gw:08x}  G:{gg:08x}")
    pct = 100.0 * (n - nd) / max(1, n)
    print(f"{pct:.2f}%  sym {size}B want {len(want)}B got {len(got)}B diffs {nd}/{n}"
          f"  flags={' '.join(flags) or 'none'}")
    for l in lines[:40]:
        print("  " + l)
    if size and size >= 0x40:
        try:
            bd = br_targets.internal_branch_diffs(addr, size, body, flags or None)
        except SystemExit as e:
            print("BRCHECK compile fail:", e)
            bd = []
        if bd:
            print(f"BRANCH MISMATCH ({len(bd)}):")
            for a, w, g in bd[:8]:
                print(f"  {a:#x}: want {w} got {g}")
        else:
            print("branches OK")


if __name__ == "__main__":
    main()
