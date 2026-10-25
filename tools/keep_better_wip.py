#!/usr/bin/env python3
"""Keep the better of (HEAD, working tree) for every modified src/wip draft.

`tools/label_twin_fix.py --write` overwrites a draft with the twin-derived body.
That is usually better, but it is a blind batch write: it can also clobber a
draft that was already further along. Run this after any bulk rewrite of
src/wip/ — it scores both versions of every modified draft and `git checkout`s
the one with the lower score.

Usage:
  tools/keep_better_wip.py [--dry-run]
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TMP = "/tmp/wipcmp"


def score(path, addr):
    r = subprocess.run([f"{ROOT}/tools/venv/bin/python", f"{ROOT}/tools/score_body.py",
                        addr, path], capture_output=True, text=True, cwd=ROOT)
    m = re.search(r"(EXACT|NEAR|DIFF|FAIL)\s+([0-9.]+)%", r.stdout)
    return (float(m.group(2)), m.group(1)) if m else (-1.0, "FAIL")


def main():
    dry = "--dry-run" in sys.argv
    os.makedirs(TMP, exist_ok=True)
    files = [l.split()[-1] for l in subprocess.run(
        ["git", "status", "--short", "src/wip"], capture_output=True, text=True,
        cwd=ROOT).stdout.splitlines() if l.split()[0].strip() in ("M",)]
    keep, revert = [], []
    for f in files:
        name = os.path.basename(f)
        addr = "0x" + name[3:11]
        head = subprocess.run(["git", "show", f"HEAD:{f}"], capture_output=True,
                              text=True, cwd=ROOT).stdout
        if not head:
            continue
        with open(os.path.join(TMP, name), "w") as fh:
            fh.write(head)
        new_pct, new_k = score(os.path.join(ROOT, f), addr)
        old_pct, old_k = score(os.path.join(TMP, name), addr)
        if old_pct > new_pct:
            if not dry:
                subprocess.run(["git", "checkout", "--", f], cwd=ROOT)
            revert.append((name, f"{old_k} {old_pct}", f"{new_k} {new_pct}"))
        else:
            keep.append((name, f"{old_k} {old_pct}", f"{new_k} {new_pct}"))
    tag = "would revert" if dry else "reverted"
    print(f"kept new body: {len(keep)}   {tag}: {len(revert)}")
    for n, o, w in revert:
        print(f"  {tag} {n}  {o} > {w}")


if __name__ == "__main__":
    sys.exit(main())
