#!/usr/bin/env python3
"""Trace which postprocess rule mangles a given m2c line — prints the FULL
body after each 'out = ...' step so the corruption point is visible."""
import difflib
import inspect
import re
import sys
import textwrap

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fill_wip_drafts as fw

ADDRS = [int(a, 16) for a in sys.argv[1:]] or [0x800BFDD8, 0x8002E34C, 0x800808EC]

# markers: only print steps that touch a line containing one of these
MARKERS = ["f32 *", "0x2F0", "0x14", "fn_80031EC8", "fn_8021B55C",
           "temp_r29", "var_r29", "0x80300000"]


def split_steps(body):
    parts = []
    cur = []
    for ln in body.split("\n"):
        cur.append(ln)
        if re.match(r"^    out = ", ln):
            parts.append("\n".join(cur))
            cur = []
    if cur:
        parts.append("\n".join(cur))
    return parts


def main():
    src = inspect.getsource(fw.postprocess)
    body = src.split("\n", 1)[1]
    parts = split_steps(body)

    for addr in ADDRS:
        fp = f"{ROOT}/src/wip/fn_{addr:08X}.c"
        text = open(fp).read()
        size = int(re.search(r"size=(\d+)B", text).group(1))
        asm_lines, _ = fw.disasm_with_labels(addr, size)
        raw = fw.run_m2c("\n".join(asm_lines) + "\n")
        print(f"########## 0x{addr:08X} ##########")
        touched = [l for l in raw.splitlines()
                   if any(k in l for k in MARKERS)]
        print("--- RAW m2c (marker lines) ---")
        for l in touched:
            print(f"  {l[:220]}")
        print("--- steps where marker lines change ---")
        ns = {"re": re, "out": raw, "fw": fw, "gl": fw.gl, "sorted": sorted,
              "set": set, "range": range, "len": len,
              "fix_ptr_index_first": fw.fix_ptr_index_first,
              "fix_ptr_literal_deref": fw.fix_ptr_literal_deref,
              "field_off": fw.field_off, "off_str": fw.off_str,
              "RE_FIELD": fw.RE_FIELD, "RE_CAST": fw.RE_CAST,
              "CAST_TYPES": fw.CAST_TYPES}
        prev = raw
        prev_touch = [l for l in prev.splitlines() if any(k in l for k in MARKERS)]
        stepno = 0
        for chunk in parts:
            stepno += 1
            try:
                exec(textwrap.dedent(chunk), ns)
            except (IndentationError, SyntaxError):
                continue
            except Exception as e:  # noqa: BLE001
                print(f"  step {stepno} EXEC ERROR: {type(e).__name__}: {str(e)[:120]}")
                continue
            out = ns["out"]
            now_touch = [l for l in out.splitlines() if any(k in l for k in MARKERS)]
            if now_touch != prev_touch:
                print(f"  -- step {stepno}: {chunk.strip().splitlines()[0][:90]}")
                for l in now_touch:
                    print(f"     {l[:220]}")
                prev_touch = now_touch
            prev = out
        print()


if __name__ == "__main__":
    main()

import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))