#!/usr/bin/env python3
"""Write improved variant bodies back into src/wip drafts.

Sweeps like tools/label_arg_scan.py / drop_phantom_arg.py / noflag_score.py
save the winning body to /tmp/<tag>_<ADDR>.c but leave the draft alone.  This
tool splices that body into the draft: the existing `//` header is kept, the
old body is replaced, and an `UPDATED` note records the score movement.

Usage: tools/venv/bin/python tools/apply_better.py <results.txt> <glob-of-variants> [--note "text"]
  results.txt lines:  0xADDR  old% -> new%   <== BETTER
"""
import glob
import os
import re
import sys

TAG = "2026-09-15 (e)"


def main():
    results, pattern = sys.argv[1], sys.argv[2]
    note = ""
    if "--note" in sys.argv:
        note = sys.argv[sys.argv.index("--note") + 1]
    variants = {}
    for p in glob.glob(pattern):
        m = re.search(r"fn_([0-9A-Fa-f]{8})", os.path.basename(p))
        if not m:
            m = re.search(r"_([0-9A-Fa-f]{8})\.c$", os.path.basename(p))
        if m:
            variants[int(m.group(1), 16)] = p
    done = 0
    for line in open(results):
        m = re.match(r"0x([0-9A-Fa-f]{8})\s+([\d.]+)\s*->\s*(?:EXACT|NEAR|DIFF)?\s*([\d.]+)\s+<== BETTER", line)
        if not m:
            continue
        addr, old, new = int(m.group(1), 16), m.group(2), m.group(3)
        vp = variants.get(addr)
        if not vp:
            print(f"0x{addr:08X}: no variant file, skipped")
            continue
        path = f"src/wip/fn_{addr:08X}.c"
        text = open(path).read()
        hdr = [l for l in text.splitlines() if l.startswith("//")]
        body = open(vp).read().strip()
        # Variants come from the sweep helpers, whose bodies already had the
        # `#include "types.h"` line stripped (compile_fn re-adds it).
        # promote_wip.py keeps the draft body verbatim, so it must be restored
        # here or the promoted src/fn_*.c fails to compile (no f32/f64/s32).
        body = "\n".join(l for l in body.splitlines()
                          if "types.h" not in l).strip()
        note_line = f"// UPDATED {TAG}: {old}% -> {new}%."
        if note:
            note_line += " " + note
        out = "\n".join(hdr) + "\n" + note_line + '\n#include "types.h"\n' + body + "\n"
        open(path, "w").write(out)
        done += 1
    print(f"applied {done} improved bodies")


if __name__ == "__main__":
    main()
