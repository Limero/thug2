#!/usr/bin/env python3
"""Compile a wip draft and print per-instruction diffs vs the DOL (reloc-masked).

Usage:
  tools/venv/bin/python tools/my_diff.py 0x80119578 [extra cflags...]
"""
import re
import struct
import sys

sys.path.insert(0, __import__('os').path.dirname(__import__('os').path.abspath(__file__)))
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs


def disasm(code, addr):
    md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
    out = []
    for ins in md.disasm(code, addr):
        out.append(f"{ins.mnemonic} {ins.op_str}")
    return out


def main():
    addr = int(sys.argv[1], 0)
    argv = sys.argv[2:]
    body_file = f"src/wip/fn_{addr:08X}.c"
    if argv and argv[0] == "--body":
        body_file = argv[1]
        argv = argv[2:]
    extra = argv[0].split() if argv else None
    text = open(body_file).read()
    # honour a per-draft `// FLAG: ...` line (same syntax test_wip_drafts uses)
    if extra is None:
        flags = []
        for l in text.splitlines():
            m = re.match(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", l)
            if m:
                flags += [t for t in m.group(1).split() if t.startswith("-")]
        extra = flags or None
    body_lines = [l for l in text.splitlines()
                  if not l.startswith("//") and "types.h" not in l]
    body = "\n".join(body_lines).strip()

    got, masks = gl.compile_fn(addr, body, extra_flags=extra)
    if got is None:
        print("FAIL: compile error")
        return
    # want = full report size
    import json
    rep = json.load(open("build/G2TE52/report.json"))
    want = None
    for u in rep.get("units", []):
        for fn in u.get("functions", []):
            if int(fn["metadata"]["virtual_address"]) == addr:
                want = int(fn["size"])
    if want is None:
        want = len(got)
    if want < len(got):
        want = len(got)
    orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + want]
    n = len(orig) // 4
    print(f"want size {want}B, got {len(got)}B, n={n} words")
    ow = disasm(orig, addr)
    gw = disasm(got, addr)
    hit = 0
    for i in range(n):
        m = masks.get(i * 4, 0xFFFFFFFF)
        o = struct.unpack_from(">I", orig, i * 4)[0]
        # A shorter compile (dead-code elimination, or a body that is still
        # missing words) leaves trailing WANT words with no GOT counterpart.
        # Count them as misses instead of crashing (this used to raise
        # `struct.error: unpack_from requires a buffer of at least ...`).
        gb = got[i * 4:i * 4 + 4]
        g = struct.unpack_from(">I", gb, 0)[0] if len(gb) == 4 else None
        ok = g is not None and (o & m) == (g & m)
        if ok:
            hit += 1
        marker = "  " if ok else "!!"
        oo = ow[i] if i < len(ow) else "<none>"
        gg = gw[i] if i < len(gw) else "<none>"
        print(f"{marker} {addr+i*4:08X}: want {oo:35s} | got {gg}")
    print(f"score: {hit}/{n} = {100.0*hit/n:.1f}%")


if __name__ == "__main__":
    main()
