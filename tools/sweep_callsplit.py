#!/usr/bin/env python3
"""sweep_callsplit: automated WA-split sweep over src/wip drafts.

Targets the f78c-call-speculation pattern proven in fn_8021F120:
WANT schedules a load in between a call and the store of that call's
result, while GCC emits the store first (source order). Countermeasure:
delay the call-result store one simple statement later so the load lands
before the store.

Transformation (semantics-preserving same-BB):
  BEFORE                        AFTER
  DEST = fn_X(...);             fs_tN = fn_X(...);
  <simple non-call stmt>        <simple non-call stmt>
                                DEST = fs_tN;
Temp var fs_tN is declared right after the function's opening '{'.

Usage:
  tools/venv/bin/python tools/sweep_callsplit.py [--slice i/m] [--apply] [--min-hit N]
"""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl

ROOT = gl.ROOT
WIP_DIR = f"{ROOT}/src/wip"

ASSIGN_CALL = re.compile(
    r'^([ \t]*)([A-Za-z_][\w\[\]\->\*\.]*)\s*=\s*(fn_[0-9A-Fa-f]{8}\s*\([^;]*?\));$'
)
CONTROL = re.compile(r'^\s*(if|for|while|do|switch|case|default|return|goto|break|continue)\b')
CALL_ANY = re.compile(r'\bfn_[0-9A-Fa-f]{8}\s*\(')


def body_of(text):
    if "#include" in text:
        rest = text.split("#include", 1)[1]
        rest = "#include" + rest
    else:
        rest = text
    return "\n".join(l for l in rest.splitlines()
                     if not l.startswith("//") and "types.h" not in l)


def prefix_decl(text, decl):
    """Insert `decl` as the first statement after the function signature '{'.
    Idempotent: no-op if the decl text is already present."""
    if decl.strip() in text:
        return text
    lines = text.split("\n")
    depth = 0
    fnbrace = None
    for i, l in enumerate(lines):
        if l.strip().startswith("//"):
            continue
        depth += l.count("{") - l.count("}")
        if depth >= 1 and fnbrace is None and ")" in l and "fn_" in l:
            fnbrace = i
            break
    if fnbrace is None:
        return None
    lines.insert(fnbrace + 1, decl)
    return "\n".join(lines)


def gen_variants(text):
    out = []
    lines = text.split("\n")
    for i in range(len(lines) - 1):
        m = ASSIGN_CALL.match(lines[i])
        if not m:
            continue
        indent, dest, callexpr = m.group(1), m.group(2), m.group(3)
        if dest.startswith("fs_t"):
            continue  # already split in a prior wave
        nxt = lines[i + 1]
        lp = nxt.strip()
        if not lp or lp.startswith("//") or CONTROL.match(lp) \
           or CALL_ANY.search(lp) or lp.rstrip().endswith("{"):
            continue
        nametag = "%03d_%s" % (i, callexpr[3:7])
        out.append((nametag, indent, dest, callexpr, nxt))
    return out


def match(addr, body):
    got, masks = gl.compile_fn(addr, body)
    if got is None:
        return None
    off = gl.t_off + (addr - gl.t_addr)
    orig = gl.d[off:off + len(got)]
    n = min(len(orig), len(got)) // 4
    hit = sum(1 for k in range(n)
              if (int.from_bytes(orig[k*4:(k+1)*4], "big") & masks.get(k*4, 0xFFFFFFFF)) ==
                 (int.from_bytes(got[k*4:(k+1)*4], "big") & masks.get(k*4, 0xFFFFFFFF)))
    return (hit, n)


def main():
    slice_idx, num_slices, applyit, min_hit = 0, 1, False, 0
    args = sys.argv[1:]
    i = 0
    while i < len(args):
        a = args[i]
        if a == "--min-hit":
            min_hit = int(args[i + 1]); i += 2; continue
        if a.startswith("--min-hit="):
            min_hit = int(a.split("=")[-1]); i += 1; continue
        if a == "--apply":
            applyit = True; i += 1; continue
        if a == "--slice":
            m = re.match(r"(\d+)/(\d+)", args[i + 1])
            if m:
                slice_idx, num_slices = int(m.group(1)), int(m.group(2))
            else:
                slice_idx = int(args[i + 1])
                num_slices = int(args[i + 2])
                i += 1
            i += 2; continue
        m = re.match(r"--slice(\d+)/(\d+)", a)
        if m:
            slice_idx, num_slices = int(m.group(1)), int(m.group(2))
        i += 1
    files = sorted(glob.glob(f"{WIP_DIR}/fn_*.c"))
    mine = files[slice_idx::num_slices]
    print("slice %d/%d: %d drafts" % (slice_idx, num_slices, len(mine)))
    improved = 0
    for fp in mine:
        name = os.path.basename(fp)[3:11].upper()
        addr = int(name, 16)
        text = open(fp).read()
        body = body_of(text)
        base = None
        try:
            base = match(addr, body)
        except Exception:
            base = None
        if base is None or base[0] < min_hit:
            continue
        bhit, bn = base
        best, bestv = None, None
        for vtag, indent, dest, callexpr, nxt in gen_variants(text):
            tmp = "fs_t"
            vtext = text  # build variant text
            lines = text.split("\n")
            # find the assignment line (it exists verbatim because gen parsed text)
            # reconstruct: replace each candidate line by tagged rewrite
            # (simplify: operate on a copy and substitute by index-match)
            vlines = lines[:]
            # locate exact line to guard
            aindex = None
            for k, ln in enumerate(lines):
                if ASSIGN_CALL.match(ln) and callexpr in ln:
                    aindex = k
                    break
            if aindex is None:
                continue
            vlines[aindex] = "%s%s = %s;" % (indent, tmp, callexpr)
            vlines[aindex + 1] = nxt + "\n%s%s = %s;" % (indent, dest, tmp)
            vtext = "\n".join(vlines)
            vtext = prefix_decl(vtext, "s32 fs_t;")
            if vtext is None:
                continue
            vbody = body_of(vtext)
            try:
                r = match(addr, vbody)
            except Exception:
                r = None
            if r and (best is None or r[0] > best[0]):
                best, bestv = r, vtext
        if best and best[0] > bhit:
            improved += 1
            if applyit:
                # inject temp declaration before first use
                out = prefix_decl(bestv, "    s32 fs_t;")
                if out:
                    open(fp, "w").write(out)
                else:
                    open(fp, "w").write(bestv + "\n")
            print("IMPROVED %s %d/%d -> %d/%d" % (name, bhit, bn, best[0], best[1]))
    print("slice done: improved=%d" % improved)


if __name__ == "__main__":
    main()