#!/usr/bin/env python3
"""Build a machine-readable ledger of the still-unmatched functions.

One row per function that is not matched yet: address, size, symbol, draft
family, the score recorded in the draft header, the draft's own flags, the
`docs/parkings/` issues it quotes (with the doc's current status), and whether
the draft carries any park note at all.

The ledger is the batch filter for the pool. It turns "work the remaining
functions" into lists a sweep can take, for example:

  * drafts quoting a doc that has since moved to `docs/parkings/solved/`
    (the blocker recipe is already written down — re-test before re-deriving),
  * drafts with no park note (never worked, not walled),
  * functions with no draft at all,
  * the population of one blocker doc, one zone or one family.

Recorded scores are read from the draft header and are NOT re-measured here.
Re-score with `tools/test_wip_drafts.py`, which honours each draft's own
`// FLAG:` / `// extra_cflags:` line; `tools/score_wip_all.py` does not, so a
score taken from that tool is not comparable with a header score.

Usage:
  tools/venv/bin/python tools/wip_ledger.py                  # TSV to stdout
  tools/venv/bin/python tools/wip_ledger.py -o build/wip_ledger.tsv
  tools/venv/bin/python tools/wip_ledger.py --summary
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
WIP = os.path.join(ROOT, "src/wip")
PARK = os.path.join(ROOT, "docs/parkings")

COLS = ["addr", "size", "name", "unit", "draft", "family", "score",
        "flags", "docs", "doc_status", "park_note", "state"]


def doc_status():
    """Map issue number -> 'solved' | 'open' | 'missing'."""
    status = {}
    for base, tag in ((os.path.join(PARK, "solved"), "solved"), (PARK, "open")):
        if not os.path.isdir(base):
            continue
        for fn in os.listdir(base):
            m = re.match(r"(\d+)-", fn)
            if not m or not fn.endswith(".md"):
                continue
            n = int(m.group(1))
            # solved/ wins over a stale open-file of the same number
            if status.get(n) != "solved":
                status[n] = tag
    return status


def symbols():
    """name -> address for every function symbol."""
    out = {}
    for line in open(os.path.join(ROOT, "config/G2TE52/symbols.txt")):
        m = re.match(r"(\S+) = \S*:(0x[0-9A-Fa-f]+);.*?type:function", line)
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


def drafts_by_addr():
    out = {}
    for fn in os.listdir(WIP):
        m = re.match(r"fn_([0-9A-Fa-f]{8})\.c$", fn)
        if m:
            out[int(m.group(1), 16)] = os.path.join(WIP, fn)
    return out


def remaining():
    """Unmatched functions as (addr, size, name, unit, state).

    `state` separates the two populations the report mixes:

    * `remaining` — no source is registered; the function is still asm-backed.
    * `uncounted` — the unit HAS a `source_path` (it is compiled from `src/`)
      and the linked DOL is byte-identical, but objdiff still scores the
      function below 100 %.  With a byte-identical DOL the object must match
      retail; the residue is a relocation-form difference (e.g. an `@l` field
      in the original object vs a folded immediate in ours), which objdiff
      counts as a partial argument mismatch.  These are not work items for the
      C pool — the draft is gone (promoted) and there is nothing to re-derive.
    """
    rep = json.load(open(os.path.join(ROOT, "build/G2TE52/report.json")))
    rows = []
    for unit in rep.get("units", []):
        m = unit.get("measures") or {}
        if m.get("matched_functions_percent", 0.0) >= 100.0:
            continue
        src = (unit.get("metadata") or {}).get("source_path")
        state = "uncounted" if src else "remaining"
        for fn in unit.get("functions") or []:
            meta = fn.get("metadata") or {}
            va = meta.get("virtual_address")
            if va is None:
                continue
            rows.append((int(va), int(fn["size"]), fn["name"], unit["name"], state))
    return rows


def parse_draft(path):
    text = open(path, errors="ignore").read()
    head = text[:3000]
    fam = re.search(r"family=([a-z0-9_]+)", text)
    fam = fam.group(1) if fam else ""
    score = ""
    pcts = re.findall(r"(\d{1,3}(?:\.\d+)?)\s*%", head)
    if pcts:
        score = pcts[-1]
    flags = ""
    m = re.search(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", text, re.M)
    if m:
        flags = m.group(1).strip()
    docs = sorted({int(d) for d in
                   re.findall(r"(?:parkings/|doc[ -]?)(\d{1,2})\b", head)})
    return {
        "family": fam,
        "score": score,
        "flags": flags.replace("\t", " "),
        "docs": ",".join(str(d) for d in docs),
        "park_note": "yes" if re.search(r"park", head, re.I) else "no",
        "len": len(text),
    }


def main():
    out_path = None
    if "-o" in sys.argv:
        out_path = sys.argv[sys.argv.index("-o") + 1]
    status = doc_status()
    sym = symbols()
    wip = drafts_by_addr()
    rows = []
    for addr, size, name, unit, state in remaining():
        path = os.path.join(WIP, name + ".c")
        if not os.path.exists(path):
            a = sym.get(name)
            path = wip.get(a) if a is not None else None
        info = parse_draft(path) if path and os.path.exists(path) else None
        if info is None:
            rows.append([f"0x{addr:08X}", str(size), name, unit, "", "", "",
                         "", "", "", "no-draft", state])
            continue
        ds = [status.get(int(d), "missing") for d in info["docs"].split(",") if d]
        rows.append([f"0x{addr:08X}", str(size), name, unit,
                     os.path.basename(path), info["family"], info["score"],
                     info["flags"], info["docs"], ",".join(ds),
                     info["park_note"], state])
    # the report can list the same address in two overlapping units
    seen = set()
    uniq = []
    for r in rows:
        if r[0] in seen:
            continue
        seen.add(r[0])
        uniq.append(r)
    rows = uniq
    rows.sort(key=lambda r: -int(r[1]))
    lines = ["\t".join(COLS)] + ["\t".join(r) for r in rows]
    text = "\n".join(lines) + "\n"
    if out_path:
        os.makedirs(os.path.dirname(out_path), exist_ok=True)
        open(out_path, "w").write(text)
    else:
        sys.stdout.write(text)

    if "--summary" in sys.argv:
        def count(pred):
            return sum(1 for r in rows if pred(r))
        solved = sum(1 for r in rows if "solved" in r[9].split(","))
        no_note = sum(1 for r in rows if r[10] == "no")
        no_draft = sum(1 for r in rows if r[10] == "no-draft")
        unc = [r for r in rows if r[11] == "uncounted"]
        rem = [r for r in rows if r[11] != "uncounted"]
        print(f"remaining {len(rem)} functions / "
              f"{sum(int(r[1]) for r in rem)} bytes", file=sys.stderr)
        print(f"  draft present            {len(rem) - sum(1 for r in rem if r[10] == 'no-draft')}", file=sys.stderr)
        print(f"  no draft                 {sum(1 for r in rem if r[10] == 'no-draft')}", file=sys.stderr)
        print(f"  no park note             {sum(1 for r in rem if r[10] == 'no')}", file=sys.stderr)
        print(f"  quotes a SOLVED doc      "
              f"{sum(1 for r in rem if 'solved' in r[9].split(','))}", file=sys.stderr)
        print(f"  quotes an open doc       "
              f"{count(lambda r: 'open' in r[9].split(','))}", file=sys.stderr)
        print(f"uncounted (linked, objdiff <100%): {len(unc)} functions / "
              f"{sum(int(r[1]) for r in unc)} bytes", file=sys.stderr)


if __name__ == "__main__":
    main()
