#!/usr/bin/env python3
"""Diff a WIP draft against the DOL at instruction granularity.

Usage: diff_near.py 0x802327E0 [--all] [--flags "-mps-float ..."]
Compiles the draft body, disassembles both the original DOL region and the
compiled bytes, prints mismatched instructions (original vs compiled).

The draft's own `// FLAG:` / `// extra_cflags:` line is honored, exactly like
`tools/pool_score.py` and `tools/stmt_perm_search.py` do.  Without it a flagged
draft is diffed against a compile made with DEFAULT flags, which is not the
build the parked score refers to -- `fn_80124110` does not even compile that
way and `fn_800E3520` shows 24 wrong words instead of its real 1.  Pass
`--flags` to override.
"""
import json
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.detail = False


def insns(data, addr):
    # Decode word-by-word instead of feeding the whole buffer to md.disasm:
    # capstone's generator STOPS at the first undecodable word, and paired-single
    # code (opcode 4 / psq_*) is exactly what it cannot decode.  A whole-buffer
    # decode therefore silently truncates, e.g. fn_801DA420 (688B, 172 words)
    # reported only 25 words as "25/25 match (100.0%)".  Fall back to `.word`.
    out = []
    for off in range(0, len(data) - 3, 4):
        w = data[off:off + 4]
        ins = next(md.disasm(w, addr + off), None)
        if ins is None:
            out.append(".word %s" % w.hex())
        else:
            out.append("%s %s" % (ins.mnemonic, ins.op_str))
    return out


def want_size(a):
    """Registered size of the function, so the want window stops at its end."""
    try:
        rep = json.load(open("build/G2TE52/report.json"))
    except Exception:
        return None
    for u in rep.get("units", []):
        for fn in u.get("functions", []):
            if int(fn["metadata"]["virtual_address"]) == a:
                return int(fn["size"])
    return None


def main():
    a = int(sys.argv[1], 16)
    show_all = "--all" in sys.argv
    flags = None
    if "--flags" in sys.argv:
        flags = sys.argv[sys.argv.index("--flags") + 1].split()
    fp = "src/wip/fn_%08X.c" % a
    text = open(fp).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l)
    if flags is None:
        flags = gl.draft_flags(text) or None
        if flags:
            print("# flags: %s" % " ".join(flags))
    got, masks = gl.compile_fn(a, body, extra_flags=flags)
    if got is None:
        print("COMPILE FAIL")
        return
    size = want_size(a) or len(got)
    span = max(size, len(got))
    orig = gl.d[gl.t_off + (a - gl.t_addr): gl.t_off + (a - gl.t_addr) + span]
    oi = insns(orig, a)
    gi = insns(got, a)
    if len(got) != size:
        print("# size: want %dB got %dB" % (size, len(got)))
    n = min(max(len(oi), len(gi)), span // 4)
    hit = 0
    mism = 0
    for i in range(n):
        ow = int.from_bytes(orig[i * 4:(i + 1) * 4], "big")
        gw = int.from_bytes(got[i * 4:(i + 1) * 4], "big")
        if len(got) < (i + 1) * 4:
            mism += 1
            print("DIFF %04X  %-38s | <EOF>" % (i * 4, oi[i]))
            continue
        m = (ow & masks.get(i * 4, 0xFFFFFFFF)) == (gw & masks.get(i * 4, 0xFFFFFFFF))
        if m:
            hit += 1
            if show_all:
                print("OK  %04X  %-38s | %s" % (i * 4, oi[i], gi[i]))
        else:
            mism += 1
            print("DIFF %04X  %-38s | %s" % (i * 4, oi[i], gi[i]))
    print("=== %d/%d match (%.1f%%), %d mismatches" % (hit, n, 100.0 * hit / n, mism))


if __name__ == "__main__":
    main()
