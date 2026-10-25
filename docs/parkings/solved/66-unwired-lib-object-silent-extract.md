# 66 — Unwired lib module object: the code silently comes from the EXTRACTED original

**Status: FIXED 2026-09-19 (odemuexi2, 17 units / 23 functions / 2820 bytes credited).
Class: verification hazard — the DOL identity proves nothing in this state.**

## Symptom

A lib module in `configure.py` looks correctly wired (`Object(Matching, ...)`,
`src_dir`, `mw_version`, `cflags`, `progress_category`) and its sources exist, yet:

- `PROGRESS.md` shows the units as **`⏳ assembly`** even though the built DOL is
  byte-identical;
- `report.json` gives those units a `total_code` but **no `fuzzy_match_percent`
  and no `matched_code`** (the tell: every other unit has both);
- `objdiff.json` has **no `base_path` and no `scratch`** for those units (compare a
  working lib unit — `main/db/db`, `main/libgcc/__divdi3` — which have both);
- `build.ninja` has **no `build/G2TE52/src/<lib>/<file>.o` rule**, and the *link*
  pulls `build/G2TE52/obj/<lib>/<file>.o`;
- a configure run prints `Missing configuration for <lib>/<file>.c`.

`obj/` is the **target** side (dtk's extraction of the original machine code);
`src/` is the **base** side (our C, compiled by `configure.py`'s rules). A module
object that dtk cannot pair with a split falls through to the *unmatched* path:
the split's bytes are provided by the extracted original and linked as-is. The
DOL stays byte-identical **vacuously** — no C was compiled, nothing was verified,
and objdiff has no object to compare (hence no score).

## Root cause

dtk matches a module `Object(...)` to a split **by name**, and lib splits carry
the lib-dir prefix. odemuexi2's module listed bare names while its splits were
prefixed:

```python
# BROKEN — dtk finds no split named "DBGFlushBuffer.c"
Object(Matching, "DBGFlushBuffer.c")
```

```
# splits.txt
odemuexi2/DBGFlushBuffer.c:
	.text       start:0x8028D340 end:0x8028D36C
```

Compare the libs that work — `libgcc`:

```python
Object(Matching, "libgcc/__divdi3.c", source="__divdi3.c", extra_cflags=[...])
```

i.e. **object name = the split name (lib-dir-prefixed)**, `source=` = the file
name inside `src_dir` (defaults to the basename, so it is usually redundant but
harmless).

## Fix

```python
Object(Matching, "odemuexi2/DBGFlushBuffer.c", source="DBGFlushBuffer.c"),
```

for all 18 entries (`DebuggerDriver.c` stays `NonMatching` — its code is meant to
come from the extracted side). Reconfigure and confirm all five tells flip:
new `src/odemuexi2/*.o` rules appear, `objdiff.json` gains `base_path` + `scratch`,
the `Missing configuration` line disappears, and `cmp` still says IDENTICAL — this
time meaningfully.

## Why this matters beyond odemuexi2

Any `Matching` object whose name does not equal a split name is *silently* the
extracted original. It looks like progress (bytes match, the file is wired) but
contributes nothing and is not compared. Two habits that catch it:

- trust `objdiff.json`'s `base_path` (and the report's `matched_code`), **never
  `cmp` alone**, when validating that a lib/source file is really being built;
- treat `Missing configuration for <lib>/<file>.c` as an error, not noise.

Sweep for the class:

```python
# every Object(...) name in configure.py vs every split name in splits.txt
# 2026-09-19 result: odemuexi2 (18, of which 1 intentionally NonMatching) and
# Runtime.PPCEABI.H (2 objects with no split at all — those functions are not in
# this build's split ranges, so nothing is linked for them either way).
```
