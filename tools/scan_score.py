#!/usr/bin/env python3
"""One scorer for every sweep scanner, matching tools/score_addrs.py exactly.

Sweep scanners used to call `tw.test_one` directly, which is *not* what
`tools/score_addrs.py` reports: for functions whose want prologue has an FPR
frame, `score_addrs.py` also tries the body with a `volatile double` dummy
injected and keeps the better of the two (issue-01's +8 headroom, and the
`ambig8` case where an 8-aligned want frame is indistinguishable as-is from
dummy-injected).  A scanner that skips that step reports deltas the real scorer
does not reproduce — `fn_80089368` was applied as "1.4 -> 1.6" and measured
1.4 -> 1.1 (the dummy variant was the 1.6).

Use `score(addr, body, flags)` everywhere instead of `tw.test_one`.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import test_wip_drafts as tw  # noqa: E402


def score(addr, body, flags=None):
    """Return (status, pct) as tools/score_addrs.py would report it."""
    fpr = tw.want_fpr_frame(addr)
    if fpr is not None and "volatile double" not in body:
        s0, p0, _ = tw.test_one(addr, body, flags)
        s1, p1, _ = tw.test_one(addr, tw.inject_dummy(body), flags)
        return (s1, p1) if p1 > p0 else (s0, p0)
    s, p, _ = tw.test_one(addr, body, flags)
    return s, p


def pct(addr, body, flags=None):
    """Numeric score only (EXACT folds to 100.0)."""
    s, p = score(addr, body, flags)
    return 100.0 if s == "EXACT" else p
