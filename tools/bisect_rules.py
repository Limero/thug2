#!/usr/bin/env python3
"""Bisect which postprocess step first corrupts a target line.

Copies fill_wip_drafts.postprocess(), injects a step counter before every
top-level 'out = ' statement, and runs it with increasing step limits. Prints
the first step at which the corruption marker appears in the output.
"""
import inspect
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fill_wip_drafts as fw

CORRUPT = {
    0x8002E34C: "0x80300000), 1;",          # deref close paren swallowed
    0x800808EC: ")*(s32 *)",                 # s32 * pointer multiply
}


def make_limited_postprocess():
    src = inspect.getsource(fw.postprocess)
    lines = src.split("\n")
    out = []
    doc_done = False
    for ln in lines:
        if not doc_done and ln.startswith('    """'):
            out.append(ln)
            out.append("    __step = 0")
            doc_done = True
            continue
        if re.match(r"^    out = ", ln):
            out.append("    __step += 1")
            out.append("    if __step > __limit:")
            out.append("        return out")
        out.append(ln)
    src2 = "\n".join(out)
    src2 = src2.replace("def postprocess(out):", "def postprocess_limited(out, __limit):", 1)
    ns = dict(fw.__dict__)  # module globals: re, helper fns, constants
    exec(src2, ns)
    return ns["postprocess_limited"]


def main():
    pl = make_limited_postprocess()
    for addr, marker in CORRUPT.items():
        text = open(f"{ROOT}/src/wip/fn_{addr:08X}.c").read()
        size = int(re.search(r"size=(\d+)B", text).group(1))
        asm_lines, _ = fw.disasm_with_labels(addr, size)
        raw = fw.run_m2c("\n".join(asm_lines) + "\n")
        src = inspect.getsource(fw.postprocess)
        n_steps = len(re.findall(r"(?m)^    out = ", src))
        print(f"########## 0x{addr:08X} (marker: {marker!r}) ##########")
        prev = ""
        for limit in range(1, n_steps + 1):
            out = pl(raw, limit)
            if marker in out:
                if marker not in prev:
                    print(f"  marker appears at step {limit}")
                    src_lines = src.split("\n")
                    stepno = 0
                    for i, ln in enumerate(src_lines):
                        if re.match(r"^    out = ", ln):
                            stepno += 1
                            if stepno == limit:
                                print(f"  step code: {src_lines[i-2].strip()[:80]}")
                                print(f"             {src_lines[i-1].strip()[:80]}")
                                print(f"             {src_lines[i].strip()[:90]}")
                                break
                break
            prev = out
        else:
            print("  marker never appears")
        print()


if __name__ == "__main__":
    main()
