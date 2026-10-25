#!/usr/bin/env python3
"""Build the Wii call-graph table (plan follow-up: symmetric caller queries).

Disassembles the linked ELF .text, resolves every `bl` target to its
containing function from the linker map, and emits one edge per line:

  docs/thpg-callgraph.tsv: caller\tcallee   (both `unit::name`)

Only map-contained targets become edges (PLT/external calls are skipped);
self-edges are dropped. Output is sorted, deterministic. Read-only toward
the decomp — a mining aid, never an input to renaming by itself.

Usage:
  tools/venv/bin/python tools/build_thpg_callgraph.py --elf ELF --map MAP
      [--out docs/thpg-callgraph.tsv]
"""
import argparse
import bisect
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROW_RE = re.compile(r"\s*\d+\s+([0-9a-fA-F]+)\s+(\d+)\s+(.*?)\s{2,}(.*)$")


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--elf", required=True)
    ap.add_argument("--map", required=True)
    ap.add_argument("--out", default="docs/thpg-callgraph.tsv")
    args = ap.parse_args()

    from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
    from elftools.elf.elffile import ELFFile

    cs = Cs(CS_ARCH_PPC, CS_MODE_32 + CS_MODE_BIG_ENDIAN)

    funcs = []
    lines = open(args.map, encoding="utf-8", errors="replace").read().splitlines()
    fi = next(i for i, l in enumerate(lines) if l.strip().startswith("FUNCTIONS"))
    for line in lines[fi + 3:]:
        if not line.strip():
            break
        m = ROW_RE.match(line)
        if m:
            funcs.append((int(m.group(1), 16), int(m.group(2)),
                          m.group(3).strip(), m.group(4).strip()))
    funcs.sort()
    starts = [f[0] for f in funcs]
    print("map functions: %d" % len(funcs))

    def containing(addr):
        i = bisect.bisect_right(starts, addr) - 1
        if i >= 0 and addr < funcs[i][0] + funcs[i][1]:
            return "%s::%s" % (funcs[i][2], funcs[i][3])
        return None

    with open(args.elf, "rb") as f:
        elffile = ELFFile(f)
        text = elffile.get_section_by_name(".text")
        tv, td = text["sh_addr"], text.data()

    edges = set()
    for addr, size, unit, name in funcs:
        off = addr - tv
        if not (0 <= off and off + size <= len(td)):
            continue
        me = "%s::%s" % (unit, name)
        for ins in cs.disasm(td[off:off + size], addr):
            if ins.mnemonic != "bl":
                continue
            m = re.match(r"0x([0-9a-fA-F]+)", ins.op_str)
            if not m:
                continue
            cal = containing(int(m.group(1), 16))
            if cal and cal != me:
                edges.add((me, cal))

    with open(args.out, "w", encoding="utf-8") as f:
        f.write("caller\tcallee\n")
        for caller, callee in sorted(edges):
            f.write("%s\t%s\n" % (caller, callee))
    print("wrote %s (%d edges)" % (args.out, len(edges)))


if __name__ == "__main__":
    main()
