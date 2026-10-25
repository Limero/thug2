#!/usr/bin/env python3
"""Find wip drafts whose residual is a pure REORDER of the same instruction words.

Some residuals are not a scheduling coin and not a wrong operand: the same set
of words appears in want and got, just in a different order inside one small
window.  The common cause is a **wrong argument-class order at a call** -- e.g.
want stages the float args first and the integer arg last

    want  [fmr f1, f31][lwz r9, ...][fmr f2, f30][mr r4, r27][bl]
    got   [mr r4, r27][lwz r9, ...][fmr f1, f31][fmr f2, f30][bl]

which the draft produced because its function-pointer cast declared the integer
argument second instead of last.  Permuting the argument list *and* the matching
cast/prototype together fixes it (see fn_8002AEF4, 93.6 -> 100).

This scanner aligns want and got word-for-word (relocation-masked, so `lis`/
`ori`/`addi` halves of an address compare equal), then reports 'replace' hunks
whose two sides are the same multiset -- i.e. the words were merely reordered.
Branch/call targets are folded to opcode-only, because a reorder shifts every
target after it and would otherwise swamp the signal.

Prints `0xADDR reorder hunks=<n> biggest=<k> words=<want disasm>` for drafts
that have at least one qualifying hunk of >= 3 words, sorted by residual size.

Usage: printf 'ADDR\n' | tools/venv/bin/python tools/reorder_scan.py [--min N]
"""
import difflib
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl  # noqa: E402
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs  # noqa: E402

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
BRANCH = re.compile(r"^(b|bl|beq|bne|blt|bgt|ble|bge|bdnz|bdz|bc|bclr|bctrl)\b")


def words(b):
    return [int.from_bytes(b[i:i + 4], "big") for i in range(0, len(b) - 3, 4)]


def text_of(ws, addr):
    out = []
    for i, w in enumerate(ws):
        p = addr + i * 4
        ins = next(md.disasm(w.to_bytes(4, "big"), p), None)
        out.append("%s %s" % (ins.mnemonic, ins.op_str) if ins else ".word %08x" % w)
    return out


def key_of(w, mask):
    """Relocation-masked word; operands of a branch/call folded to opcode-only."""
    masked = w & mask
    ins = next(md.disasm(masked.to_bytes(4, "big"), 0), None)
    if ins is None:
        return "word%08x" % masked
    if BRANCH.match(ins.mnemonic):
        return ins.mnemonic
    return "%s %s" % (ins.mnemonic, ins.op_str)


def want_size(addr):
    for u in json.load(open("build/G2TE52/report.json")).get("units", []):
        for fn in u.get("functions", []):
            if int(fn["metadata"]["virtual_address"]) == addr:
                return int(fn["size"])
    return None


def scan(addr, minrun):
    fp = "src/wip/fn_%08X.c" % addr
    if not os.path.exists(fp):
        return None
    text = open(fp).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    flags = gl.draft_flags(text) or None
    got, masks = gl.compile_fn(addr, body, extra_flags=flags)
    if got is None:
        return None
    size = want_size(addr) or len(got)
    off = gl.t_off + (addr - gl.t_addr)
    orig = gl.d[off:off + size]
    ow, gw = words(orig), words(got)
    if not ow or not gw:
        return None
    nw = [key_of(w, masks.get(i * 4, 0xFFFFFFFF)) for i, w in enumerate(ow)]
    ng = [key_of(w, masks.get(i * 4, 0xFFFFFFFF)) for i, w in enumerate(gw)]
    n = min(len(nw), len(ng))
    resid = sum(1 for i in range(n) if nw[i] != ng[i])
    if resid == 0:
        return None
    ot, gt = text_of(ow, addr), text_of(gw, addr)
    # difflib often spells a small rotation as insert+delete rather than
    # replace, so merge every run of non-equal opcodes into one block first.
    blocks = []
    cur = None
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(
            a=nw, b=ng, autojunk=False).get_opcodes():
        if tag == "equal":
            if cur is not None:
                blocks.append(cur)
                cur = None
            continue
        if cur is None:
            cur = [i1, i2, j1, j2]
        else:
            cur[1], cur[3] = i2, j2
        if (cur[1] - cur[0]) + (cur[3] - cur[2]) > 16:
            blocks.append(cur)
            cur = None
    if cur is not None:
        blocks.append(cur)

    # a rotated word also splits a block in two when the rotation lands exactly
    # on one equal word (want [a][b][c] vs got [b][c][a] comes out as
    # insert(b,c) / equal(a) / delete(b,c)), so also test unions of adjacent
    # blocks that are separated by an equal run of at most two words.
    cands = [(i1, i2, j1, j2) for i1, i2, j1, j2 in blocks if i2 - i1 + 1 <= 16]
    for k in range(len(blocks) - 1):
        i1, i2, j1, j2 = blocks[k]
        i3, i4, j3, j4 = blocks[k + 1]
        if (i3 - i2) > 2 or (j3 - j2) > 2:
            continue
        if (i4 - i1) + (j4 - j1) > 16:
            continue
        cands.append((i1, i4, j1, j4))

    hunks = []
    for i1, i2, j1, j2 in cands:
        a, b = nw[i1:i2], ng[j1:j2]
        if len(a) < minrun or len(b) < minrun or sorted(a) != sorted(b):
            continue
        hunks.append((max(len(a), len(b)), i1, ot[i1:i1 + 4]))
    if not hunks:
        return None
    hunks.sort(reverse=True)
    return "0x%08X reorder hunks=%d biggest=%d resid=%d words=%s" % (
        addr, len(hunks), hunks[0][0], resid, " | ".join(hunks[0][2]))


def main():
    minrun = 3
    argv = [a for a in sys.argv[1:] if not a.startswith("--")]
    if "--min" in sys.argv:
        minrun = int(sys.argv[sys.argv.index("--min") + 1])
        argv = [a for a in argv if a != str(minrun)]
    for line in sys.stdin:
        a = line.strip()
        if not a or a.startswith("--"):
            continue
        try:
            r = scan(int(a, 16), minrun)
        except Exception as e:  # noqa
            r = "0x%s ERROR %s" % (a, e)
        if r:
            print(r, flush=True)


if __name__ == "__main__":
    main()
