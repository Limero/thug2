#!/usr/bin/env python3
"""Rename Dolphin SDK functions in thug2's DOL to their real SDK names.

Strategy: thug2 links the same SDK 0x2301 library as zeldaret/tp (tp's is a
~2004 superset).  Within a module the function ORDER and (almost always) the
SIZE are preserved, so we match thug2's unnamed fn_XXXX functions against tp's
named functions by a size-sequence alignment, then rename.

For each module in MODULES:
  1. tp list  = functions in tp's address range (from tp splits.txt source
     files + tp symbols.txt), in address order: [(name, size), ...]
  2. th list  = thug2 functions in [th_start, th_end), in address order:
                [(addr, size, name), ...]
  3. Align the two lists (order-preserving, exact-size confirm).  Exact size
     matches rename fn_XXXX -> tp name (with scope:global).  Anything that
     does not line up (extra thug2 function, tp function dead-code-eliminated,
     or size drift) is reported and LEFT AS fn_ for manual review.
  4. Word-boundary rename of callers in src/*.c and src/wip/*.c, so game code
     that calls these SDK functions reads real names.

The module table is hardcoded (determined once from the named anchors in
symbols.txt + the reference splits.txt); add modules as their ranges are verified.

CAVEAT (GX): thug2's GXFifo.c DCE'd __GXCleanGPFifo + GXSetCurrentGXThread
(tww keeps them), which shifts the size-sequence alignment and can produce
WRONG renames in the GXFifo.c tail (the three 0x8 getters). Do not blindly
apply the GX output; verify against the tww GXFifo.c source / the wiring pass.
The getter trio is now hand-corrected in symbols.txt (GXGetCurrentGXThread /
GXGetCPUFifo / GXGetGPFifo at 0x8028699C/A4/AC).

Usage:
  tools/venv/bin/python tools/rename_sdk_functions.py --dry-run
  tools/venv/bin/python tools/rename_sdk_functions.py            # apply

Idempotent: already-named thug2 functions are verified (name must match tp's)
and never rewritten.  Only fn_XXXX symbols are renamed.
"""
import os
import re
import sys

TH_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TP_ROOT = os.environ.get("TP_ROOT", os.path.join(os.path.dirname(TH_ROOT), "tp"))
# tww (Dec 2002) is the SAME SDK 0x2301 build as thug2 ("Sep 5 2002 (0x2301)"),
# so its GX sizes/order match thug2 far better than tp's 2004 build. Use tww as
# the reference for GX; tp for the older, less-drifted modules.
TWW_ROOT = os.environ.get("TWW_ROOT", os.path.join(os.path.dirname(TH_ROOT), "tww"))
TWW_CONFIG = "GZLE01"
TP_CONFIG = "GZ2E01"

DRY = "--dry-run" in sys.argv

# (th_start, th_end, [tp source file paths in tp splits.txt])
# th_start inclusive, th_end exclusive.  Ranges verified against the named
# anchors in config/G2TE52/symbols.txt (see the module boundary comments).
MODULES = [
    # SI: SIBusy (0x80281678) .. SIRefreshSamplingRate (0x80282E4C, ends 0x80282E70).
    # tp: si/SIBios.c + si/SISamplingRate.c.
    ("si", 0x80281678, 0x80282E70, "tp", ["dolphin/si/SIBios.c", "dolphin/si/SISamplingRate.c"]),
    # EXI: SetExiInterruptMask (0x80282E70) .. WriteUARTN (0x80284C04, 0x21C, ends 0x80284E20).
    # tp: exi/EXIBios.c + exi/EXIUart.c.
    ("exi", 0x80282E70, 0x80284E20, "tp", ["dolphin/exi/EXIBios.c", "dolphin/exi/EXIUart.c"]),
    # PAD: ClampStick (0x80268128) .. __PADDisableRecalibration (0x80269E34, ends 0x80269EB0).
    # tp: pad/Padclamp.c + pad/Pad.c.
    ("pad", 0x80268128, 0x80269EB0, "tp", ["dolphin/pad/Padclamp.c", "dolphin/pad/Pad.c"]),
    # AR: ARRegisterDMACallback (0x80274BEC) .. __ARChecksize (0x80274EDC, ends 0x802766D0).
    # tp: ar/ar.c.
    ("ar", 0x80274BEC, 0x802766D0, "tp", ["dolphin/ar/ar.c"]),
    # ARQ: __ARQServiceQueueLo (0x802766D0) .. ARQPostRequest (0x8027691C, ends 0x80276A78).
    # tp: ar/arq.c.
    ("arq", 0x802766D0, 0x80276A78, "tp", ["dolphin/ar/arq.c"]),
    # AI: AIRegisterDMACallback (0x80276AB0) .. __AI_SRC_INIT (0x802771BC, ends 0x802773A0).
    # tp: ai/ai.c.
    ("ai", 0x80276AB0, 0x802773A0, "tp", ["dolphin/ai/ai.c"]),
    # GX: GXInit (0x80285050) .. end of GXPerf (0x8028D494, where game vtable
    # methods begin).  Reference = tww (same SDK 0x2301); tp drifts too much.
    ("gx", 0x80285050, 0x8028D494, "tww", [
        "dolphin/gx/GXInit.c", "dolphin/gx/GXFifo.c", "dolphin/gx/GXAttr.c",
        "dolphin/gx/GXMisc.c", "dolphin/gx/GXGeometry.c", "dolphin/gx/GXFrameBuf.c",
        "dolphin/gx/GXLight.c", "dolphin/gx/GXTexture.c", "dolphin/gx/GXBump.c",
        "dolphin/gx/GXTev.c", "dolphin/gx/GXPixel.c", "dolphin/gx/GXStubs.c",
        "dolphin/gx/GXDisplayList.c", "dolphin/gx/GXTransform.c", "dolphin/gx/GXPerf.c"]),
]


def parse_symbols(path, lo, hi):
    """Return [(addr, size, name, scope)] for .text functions in [lo, hi), sorted.
    scope is 'global', 'local', or None (no annotation)."""
    out = []
    for line in open(path):
        m = re.match(
            r"([A-Za-z_][A-Za-z0-9_]*) = \.text:(0x[0-9A-Fa-f]+); "
            r"// type:function size:(0x[0-9A-Fa-f]+)(.*)", line)
        if not m:
            continue
        a = int(m.group(2), 16)
        if lo <= a < hi:
            rest = m.group(4)
            scope = "local" if "scope:local" in rest else ("global" if "scope:global" in rest else None)
            out.append((a, int(m.group(3), 16), m.group(1), scope))
    out.sort()
    return out


def ref_module_ranges(ref):
    """Map reference source path -> (start, end) from the reference splits.txt."""
    root = TWW_ROOT if ref == "tww" else TP_ROOT
    cfg = TWW_CONFIG if ref == "tww" else TP_CONFIG
    ranges = {}
    cur = None
    for line in open(f"{root}/config/{cfg}/splits.txt"):
        line = line.rstrip("\n")
        if line.endswith(":") and not line.startswith(("\t", " ")):
            cur = line[:-1]
        elif cur and line.startswith("\t.text"):
            m = re.search(r"start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)", line)
            if m:
                ranges[cur] = (int(m.group(1), 16), int(m.group(2), 16))
    return ranges


def ref_symbols_path(ref):
    root = TWW_ROOT if ref == "tww" else TP_ROOT
    cfg = TWW_CONFIG if ref == "tww" else TP_CONFIG
    return f"{root}/config/{cfg}/symbols.txt"


def main():
    os.chdir(TH_ROOT)
    ref_ranges = {r: ref_module_ranges(r) for r in ("tp", "tww")}

    th_funcs_all = parse_symbols("config/G2TE52/symbols.txt", 0x80200000, 0x80300000)

    rename = {}  # thug2 fn_sym -> tp name
    reports = []  # (module, kind, detail)

    for mod_name, th_lo, th_hi, ref, tp_sources in MODULES:
        tp_ranges = ref_ranges[ref]
        # reference function list (in order) for this module's source files
        tp_funcs = []
        for src in tp_sources:
            if src not in tp_ranges:
                reports.append((mod_name, "MISSING-REF-SOURCE", src))
                continue
            lo, hi = tp_ranges[src]
            tp_funcs += [(s, n, sc) for a, s, n, sc in parse_symbols(
                ref_symbols_path(ref), lo, hi)]
        # thug2 function list (in order) for this module
        th_funcs = parse_symbols("config/G2TE52/symbols.txt", th_lo, th_hi)

        i = j = 0
        while i < len(tp_funcs) and j < len(th_funcs):
            t_sz, t_nm, t_sc = tp_funcs[i]
            th_a, th_sz, th_nm, _th_sc = th_funcs[j]
            # strong anchor: an already-named thug2 function pins the alignment.
            # Look ahead in tp's list for the same name and skip any tp functions
            # in between (inlined/DCE'd out of thug2's older SDK build), so the
            # size-sequence match resumes at the correct position even when the
            # function count differs across SDK revisions.
            if not th_nm.startswith("fn_"):
                k = i
                while k < len(tp_funcs) and k - i < 50 and tp_funcs[k][1] != th_nm:
                    k += 1
                if k < len(tp_funcs) and tp_funcs[k][1] == th_nm:
                    for m in range(i, k):
                        ms, mn, _ = tp_funcs[m]
                        reports.append((mod_name, "DCE-TP",
                                        f"{mn} size 0x{ms:X} absent from thug2"))
                    i = k + 1
                    j += 1
                    continue
                reports.append((mod_name, "NAME-MISMATCH",
                                f"{th_nm} (0x{th_sz:X}) not found in tp remainder"))
                i += 1
                j += 1
                continue
            if t_sz == th_sz:
                if th_nm.startswith("fn_"):
                    rename["fn_%08X" % th_a] = (t_nm, t_sc)
                elif th_nm != t_nm:
                    reports.append((mod_name, "NAME-MISMATCH",
                                    f"{th_nm} (0x{th_sz:X}) vs tp {t_nm}"))
                i += 1
                j += 1
                continue
            # sizes differ: look ahead to classify
            th_extra = (j + 1 < len(th_funcs) and th_funcs[j + 1][1] == t_sz)
            tp_extra = (i + 1 < len(tp_funcs) and tp_funcs[i + 1][0] == th_sz)
            if th_extra:
                reports.append((mod_name, "EXTRA-TH",
                                f"0x{th_funcs[j][0]:08X} size 0x{th_sz:X} not in tp"))
                j += 1
            elif tp_extra:
                reports.append((mod_name, "DCE-TP",
                                f"{t_nm} size 0x{t_sz:X} absent from thug2"))
                i += 1
            else:
                reports.append((mod_name, "SIZE-DRIFT",
                                f"0x{th_funcs[j][0]:08X} 0x{th_sz:X} vs tp {t_nm} 0x{t_sz:X}"))
                i += 1
                j += 1

    print("renames proposed:", len(rename))
    for (m, k, d) in reports:
        print(f"  [{m:6s}] {k:14s} {d}")

    if DRY:
        # show a sample of the renames
        items = sorted(rename.items(), key=lambda kv: kv[0])
        for sym, (nm, sc) in items:
            print(f"  {sym} -> {nm} [{sc or 'default'}]")
        print("DRY-RUN: no changes written")
        return

    if not rename:
        print("nothing to rename")
        return

    # ---- apply to symbols.txt ----
    symlines = open("config/G2TE52/symbols.txt").read().splitlines(keepends=True)
    changed = 0
    out = []
    for ln in symlines:
        m = re.match(r"^(fn_[0-9A-F]{8}) = (\S+); // (.*)$", ln.rstrip("\n"))
        if m and m.group(1) in rename:
            name, scope = rename[m.group(1)]
            rest = m.group(3)
            if scope in ("global", "local"):
                rest = re.sub(r"\s*scope:(global|local)", "", rest).rstrip()
                rest = rest.rstrip() + " scope:" + scope
            out.append("%s = %s; // %s\n" % (name, m.group(2), rest))
            changed += 1
        else:
            out.append(ln)
    open("config/G2TE52/symbols.txt", "w").writelines(out)
    print("symbols.txt lines changed:", changed)

    # ---- word-boundary rename of callers in src/ and src/wip/ ----
    syms = list(rename.keys())
    pat = re.compile(r"\b(" + "|".join(re.escape(s) for s in syms) + r")\b")

    def files_with(paths):
        hit = []
        for fp in paths:
            try:
                t = open(fp).read()
            except OSError:
                continue
            if pat.search(t):
                hit.append(fp)
        return hit

    src_files = ["src/%s" % f for f in sorted(os.listdir("src")) if f.endswith(".c")]
    wip_files = ["src/wip/%s" % f for f in sorted(os.listdir("src/wip")) if f.endswith(".c")]
    hits = files_with(src_files) + files_with(wip_files)
    total = 0
    for fp in hits:
        t = open(fp).read()
        t2, n = pat.subn(lambda m: rename[m.group(1)][0], t)
        if n:
            open(fp, "w").write(t2)
            total += n
    print("caller files touched:", len(hits), "token replacements:", total)
    print("done")


if __name__ == "__main__":
    main()
