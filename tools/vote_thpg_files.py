#!/usr/bin/env python3
"""Tier D file votes (plan section 5): which compilation unit each THUG2
function belongs to, by majority vote of Wii units from anchored neighbors.

Signals (weights):
  S1 shared-string co-reference (main signal): THUG2 func F references a
     string that Wii funcs of unit U also reference. Weight per string =
     1 / (# Wii funcs on that string) — unique strings dominate, format
     strings shared by dozens of funcs barely count.
  S2 call edges to VERIFIED-renamed functions (plan section 8 batches):
     callers and callees of a renamed function vote for its Wii unit at
     weight 1.0. Only verified renames anchor — shape-only hypotheses never
     propagate.
  S3 call edges to name-identical script commands: THUG2 ScriptFoo whose
     bare name exists as a Wii ScriptFoo method (plan Tier C stability proof,
     824 overlaps). Callers/callees vote for the Wii unit(s), split evenly
     across units at weight 1.0 total per edge (overloads dilute).

Confidence: high (top weight >= 2.0 and >= 2x runner-up), medium (top >= 1.0),
else low. Folders join via docs/thpg-file-list.tsv. Output:

  docs/thpg-file-votes.tsv: fn_addr | fn_name | unit | folder | votes | confidence

Metadata only — never renames, never moves sources (see plan section 10 for
the eventual folder split this table stages).

Usage:
  tools/venv/bin/python tools/vote_thpg_files.py --dol DOL --elf ELF --map MAP
      [--out docs/thpg-file-votes.tsv]
"""
import argparse
import bisect
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

FUNC_RE = re.compile(r"(\S+)\s*=\s*\.text:(0x[0-9A-Fa-f]+);\s*//\s*type:function\s+size:0x([0-9A-Fa-f]+)")
ROW_RE = re.compile(r"\s*\d+\s+([0-9a-fA-F]+)\s+(\d+)\s+(.*?)\s{2,}(.*)$")

# Verified renames anchor S2: THUG2 name -> Wii unit.
ANCHORS = {
    "MemAvailable": "region.o",
    "CompactPool_Free": "CompactPool.o",
    "sRenderWorld": "nx.o",
    "GetFreshId": "objtrack.o",
    "PoolManager_SSetupPool": "PoolManager.o",
    "NextRaceWaypoint": "RaceGoal.o",
    "SkaterGapComponent_end_gap": "SkaterGapComponent.o",
}


def load_dol(path):
    d = open(path, "rb").read()
    to = struct.unpack(">7I", d[0:28])
    ta = struct.unpack(">7I", d[72:100])
    ts = struct.unpack(">7I", d[144:172])
    do = struct.unpack(">11I", d[28:72])
    da = struct.unpack(">11I", d[100:144])
    ds = struct.unpack(">11I", d[172:216])
    return d, list(zip(to, ta, ts)) + list(zip(do, da, ds))


def section_bytes(d, secs, addr, size):
    for off, base, length in secs:
        if base and base <= addr < base + length and addr + size <= base + length:
            return d[off + addr - base:off + addr - base + size]
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--dol", required=True)
    ap.add_argument("--elf", required=True)
    ap.add_argument("--map", required=True)
    ap.add_argument("--out", default="docs/thpg-file-votes.tsv")
    args = ap.parse_args()

    from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
    cs = Cs(CS_ARCH_PPC, CS_MODE_32 + CS_MODE_BIG_ENDIAN)

    d, secs = load_dol(args.dol)
    funcs = []
    for line in open("config/G2TE52/symbols.txt"):
        m = FUNC_RE.match(line)
        if m:
            funcs.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    funcs.sort(key=lambda x: x[1])
    starts = [f[1] for f in funcs]

    def containing(addr):
        i = bisect.bisect_right(starts, addr) - 1
        if i >= 0 and addr < funcs[i][1] + funcs[i][2]:
            return funcs[i][0]
        return None

    # Call graph (caller -> callees), THUG2 side.
    callers_of = collections.defaultdict(set)
    callees_of = collections.defaultdict(set)
    for name, addr, size in funcs:
        code = section_bytes(d, secs, addr, size)
        if not code:
            continue
        for ins in cs.disasm(code, addr):
            if ins.mnemonic != "bl":
                continue
            m = re.match(r"0x([0-9a-fA-F]+)", ins.op_str)
            if not m:
                continue
            cal = containing(int(m.group(1), 16))
            if cal and cal != name:
                callees_of[name].add(cal)
                callers_of[cal].add(name)
    print("callers with edges: %d" % len(callees_of))

    votes = collections.defaultdict(lambda: collections.defaultdict(float))

    # S1: shared strings.
    n_s1 = 0
    with open("docs/thpg-string-xrefs.tsv", encoding="utf-8") as f:
        next(f)
        for line in f:
            p = line.rstrip("\n").split("\t")
            if len(p) < 5:
                continue
            tf = [x for x in p[2].split(",") if x]
            wf = [x for x in p[4].split(",") if x]
            if not tf or not wf:
                continue
            # Each Wii func on the string votes its unit at 1/n_wii, so a
            # unit's share is (# its funcs on the string) / n_wii.
            units = collections.Counter(x.split("::")[0] for x in wf)
            for t in tf:
                for u, c in units.items():
                    votes[t][u] += c / len(wf)
                n_s1 += 1
    # Simplify: each Wii func on the string votes its unit at 1/n_wii.
    print("strings feeding S1: %d" % n_s1)

    # S2: edges to verified anchors.
    n_s2 = 0
    for anchor, unit in ANCHORS.items():
        for c in sorted(callers_of.get(anchor, ())):
            votes[c][unit] += 1.0
            n_s2 += 1
        for c in sorted(callees_of.get(anchor, ())):
            votes[c][unit] += 1.0
            n_s2 += 1
    print("S2 edge votes: %d" % n_s2)

    # S3: edges to name-identical script commands.
    wii_script_units = collections.defaultdict(set)
    try:
        with open("docs/thpg-func-names.tsv", encoding="utf-8") as f:
            next(f)
            for line in f:
                p = line.rstrip("\n").split("\t")
                if len(p) >= 4 and p[2].startswith("Script") and len(p[2]) > 6:
                    wii_script_units[p[2][6:]].add(p[3])
    except OSError:
        pass
    n_s3 = 0
    for name, addr, size in funcs:
        if not name.startswith("Script"):
            continue
        bare = name[6:] if name.startswith("Script") else name
        units = wii_script_units.get(bare)
        if not units:
            # THUG2 ScriptX where the registry name already carried the prefix
            # (ScriptExists, ScriptWaitForEvent...): try the full name too.
            units = wii_script_units.get(name)
        if not units:
            continue
        w = 1.0 / len(units)
        for c in sorted(callers_of.get(name, ())):
            for u in sorted(units):
                votes[c][u] += w
            n_s3 += 1
        for c in sorted(callees_of.get(name, ())):
            for u in sorted(units):
                votes[c][u] += w
            n_s3 += 1
    print("S3 script-edge votes: %d (anchors: %d THUG2 Script fns)" % (
        n_s3, sum(1 for n, _, _ in funcs if n.startswith("Script"))))

    # Folders join.
    folders = {}
    with open("docs/thpg-file-list.tsv", encoding="utf-8") as f:
        next(f)
        for line in f:
            p = line.rstrip("\n").split("\t")
            if len(p) >= 3:
                folders[p[0]] = (p[1], p[2])

    rows = []
    for name, addr, size in funcs:
        if not name.startswith("fn_") or name not in votes:
            continue
        ranked = sorted(votes[name].items(), key=lambda kv: (-kv[1], kv[0]))
        top, topw = ranked[0]
        second = ranked[1][1] if len(ranked) > 1 else 0
        if topw >= 2.0 and topw >= 2 * second:
            conf = "high"
        elif topw >= 1.0:
            conf = "medium"
        else:
            conf = "low"
        folder, ev = folders.get(top, ("unknown", "unknown"))
        rows.append((addr, name, top, folder, topw, conf))

    with open(args.out, "w", encoding="utf-8") as f:
        f.write("fn_addr\tfn_name\tunit\tfolder\tvotes\tconfidence\n")
        for addr, name, unit, folder, w, conf in sorted(rows):
            f.write("0x%X\t%s\t%s\t%s\t%.2f\t%s\n" % (addr, name, unit, folder, w, conf))
    conf_count = collections.Counter(c for *_, c in rows)
    print("wrote %s (%d unnamed funcs with votes: %s)" % (args.out, len(rows), dict(conf_count)))


if __name__ == "__main__":
    main()
