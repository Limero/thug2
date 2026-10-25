#!/usr/bin/env python3
"""A/B helper: score variant draft bodies for a wip function vs the DOL.

Usage: tools/venv/bin/python tools/try_variants.py 0xADDR <<'EOF'
...variant C bodies separated by lines '# === variant name'...
EOF
"""
import struct
import sys

sys.path.insert(0, __import__('os').path.dirname(__import__('os').path.abspath(__file__)))
import gen_leaves as gl


def main():
    addr = int(sys.argv[1], 0)
    flags = sys.argv[2].split() if len(sys.argv) > 2 else []
    text = sys.stdin.read()
    parts = []
    cur_name = "base"
    cur = []
    for line in text.splitlines():
        if line.startswith("# ==="):
            parts.append((cur_name, "\n".join(cur)))
            cur_name = line[5:].strip()
            cur = []
        else:
            cur.append(line)
    parts.append((cur_name, "\n".join(cur)))

    import json
    rep = json.load(open("build/G2TE52/report.json"))
    want_size = None
    for u in rep.get("units", []):
        for fn in u.get("functions", []):
            if int(fn["metadata"]["virtual_address"]) == addr:
                want_size = int(fn["size"])
    if want_size is None or want_size > 0x200:
        # report size unreliable for this fn — use next symbol boundary heuristic
        want_size = None

    for name, body in parts:
        body = body.strip()
        if not body:
            continue
        got, masks = gl.compile_fn(addr, body, extra_flags=flags or None)
        if got is None:
            print(f"{name}: COMPILE FAIL: {masks}")
            continue
        # want: use 0x74 default unless resolved
        size = want_size or len(got)
        orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + size]
        n = min(len(orig), len(got)) // 4
        hit = 0
        misses = []
        for i in range(n):
            m = masks.get(i * 4, 0xFFFFFFFF)
            o = struct.unpack_from(">I", orig, i * 4)[0]
            g = struct.unpack_from(">I", got, i * 4)[0]
            ok = (o & m) == (g & m)
            hit += ok
            if not ok:
                misses.append(i)
        total = (len(orig) // 4) if len(orig) >= len(got) else n
        print(f"{name}: {hit}/{total} = {100.0*hit/total:.1f}%  (got {len(got)}B) first-miss@{misses[0] if misses else '-'}")


if __name__ == "__main__":
    main()
