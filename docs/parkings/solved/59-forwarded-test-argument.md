# 59 — m2c drops the argument an `if` guard was testing

**Status: SOLVED (2026-09-15) — 9 functions promoted byte-identical to the
retail DOL in one session, ~40 more drafts improved.**
Scanner: `tools/forwarded_test_scan.py`, prefilter `tools/cmp0_home_scan.py`.

## Symptom

A load that is *only* compared homes in **r0** instead of a real GPR, and the
call it guards has one argument too few: want loads offset 0x190 into a real argument register, compares it against zero, branches on zero, and branches to the callee with no further setup since the value is already in place, while got loads the same offset into r0 for the compare-only test and likewise branches with nothing to pass.

## Root cause

```c
if ((s32) arg0->unk0x190 != 0) {
    fn_80009AAC();                 /* m2c dropped it */
}
```

The retail source passes the tested value through:

```c
if ((s32) arg0->unk0x190 != 0) {
    fn_80009AAC((void *) arg0->unk0x190);
}
```

Because MWCC can keep the loaded value in the argument register it already
occupies, the `bl` needs **no** further setup — and the very fact that the
value is live past the compare is what stops it being homed in r0. Both
symptoms are the same single missing argument.

## Cheapest tell

`lwz r0, d(rB)` / `lhz` / `lbz` / `lha` **immediately followed by**
`cmpwi r0, 0` in the *got* object code (`tools/cmp0_home_scan.py`). 501 of the
1,763 no-park drafts carry at least one such pair.

## The insertion position is the interesting part

The forwarded value goes where the DOL's register block says it goes, and that
is **not always the last** slot:

| fn | m2c draft | real call | evidence |
|---|---|---|---|
| `fn_8004238C` | `fn_80009AAC()` | `fn_80009AAC(arg0->unk0x190)` | `lwz r3,0x190(r31)` then `bl` |
| `fn_8005C944` | `fn_8005C9A8(1)` | `fn_8005C9A8(arg0, 1)` | `li r4,1` and r3 untouched |
| `fn_800685A4` | `fn_8000F9C4(g)` | `fn_8000F9C4(g, arg0->unk0xC)` | `lwz r4,0xc(r31)` then `bl` |
| `fn_8018BED8` | `fn_8012701C(3)` | `fn_8012701C(arg0->unk0x20, 3)` | `lwz r3,0x20(r31)` + `li r4,3` |
| `fn_80242528` | `fn_80241548(arg1)` | `fn_80241548(fn_80240C80(...), arg1)` | result of the preceding call stays in r3 |

`tools/forwarded_test_scan.py` therefore tries **every** argument position,
adjusting the callee prototype (`s32` inserted at the same index; `void *` and
`s32` pass identically on PPC so only the count matters) and keeps the best
A/B per address.

**Scope it tightly.** The sweep only considers a call that is the *first*
statement of the `if` body — i.e. nothing but the opening `{` between the `if`
condition and the call. Letting it insert into any call in the block produced
hundreds of large regressions (`memcpy`, `memset`, the destructor call
`fn_80009AAC`, …) because the tested value is *not* still live by then. Even
scoped, most insertions are neutral or worse; this is an A/B lever, not a
patch.

## Members promoted (DOL `cmp`-verified byte-identical)

| fn | size | score |
|---|---|---|
| `fn_8004238C` | 100B | 46.2 → 100 |
| `fn_8005C944` | 100B | 42.3 → 100 |
| `fn_800685A4` | 116B | 89.7 → 100 |
| `fn_80242528` | 104B | 80.8 → 100 |
| `fn_8018BED8` | 212B | 73.6 → 100 |
| `fn_80126E28` | 116B | 79.3 → 100 |
| `fn_800EDEB4` | 200B | 41.7 → 100 | insertion slot **1**, not 0 |
| `fn_800A8288` | 84B | 47.6 → 100 | the tested field is the **first** argument |
| `fn_801F93F8` | 80B | 85.0 → 100 | **two** arguments: tested field first, the enclosing `arg1` second |

`fn_800EDEB4`, `fn_800A8288` and `fn_801F93F8` came from the *wide* sweep
(the full 501-address `cmp0` prefilter set): its two EXACTs appeared in the
first 60 addresses and nothing in the remaining 269, so the lever is exhausted
in this pool.

`fn_80126E28` and `fn_80242528` are the variant where the forwarded value is
the **result of the immediately preceding call**: retail emits no `mr r3` at
all, so the argument list simply nests the calls
(`fn_80126BF0(fn_801291FC(arg0), a, b, c)`). `fn_8005C944`/`fn_800685A4`
also show the load moving to r3/r4 as a side effect.

## Relation to other docs

- Doc 52 / doc 58 — m2c's *phantom* arguments (extra). This is the mirror
  image: m2c **dropping** an argument. Both come from the same place — m2c
  guessing the register that the `bl` consumes.
- Doc 60 — the other half of the same root cause: the dropped argument is the
  **enclosing function's own parameter** rather than a value loaded in the
  guard. That symptom is `li r4,LIT` in want vs `li r3,LIT` in got.
- Doc 53 — the `lha` half of `fn_800F21E8` / `fn_800A1AE8`.
- Doc 56 — `bl` + `crclr`/`crset`: the *other* reason a `bl`'s argument setup
  can be wrong. Check doc 56 first if a `crclr` word is present.

## Addendum 2026-09-15 (n) — re-run over the 1,338 newly exposed addresses

This lever was reported exhausted earlier the same day, but that verdict was
measured against an incomplete pool (1,748 of 3,031 sweepable drafts — see doc
62).  Re-running it over the addresses the old pool never held
(`cmp0_home_scan.py` over 1,335 -> **407** candidates) produced **29 more
improvements, no regressions, no EXACT**:

`fn_802394F8` 83.3 -> 87.5 · `fn_80131E50` 70.0 -> 75.0 ·
`fn_800E2A18` 34.8 -> 72.7 · `fn_800E2A70` 34.8 -> 72.7 ·
`fn_800E2AC8` 34.8 -> 72.7 · `fn_8022BD5C` 38.3 -> 66.0 ·
`fn_800E28F8` 40.0 -> 56.0 · `fn_800E2958` 40.0 -> 56.0 ·
`fn_800E29B8` 40.0 -> 56.0 · `fn_8012C8F0` 36.4 -> 42.2 ·
`fn_8023E724` 37.1 -> 37.5 · `fn_801695A0` 25.6 -> 29.2 ·
`fn_800E08C4` 24.5 -> 27.3 · `fn_800E270C` 18.5 -> 22.2 ·
`fn_80173024` 21.5 -> 22.2 · `fn_80196EF8` 11.3 -> 14.9 ·
`fn_80103BC4` 11.8 -> 14.1 · `fn_800E4F90` 9.3 -> 12.8 (via doc 60) ·
`fn_80145C14` 10.1 -> 12.1 · `fn_800E9D50` 9.1 -> 10.5 · and 9 smaller.

**Apply note (cost a real debugging detour).**  `fn_800E2A70`'s header is an
m2c shape whose `// FLAG: -fno-expensive-optimizations` line sits *inside* the
body, after the includes and just above the function — not in the header block.
The first apply pass rebuilt the file as "original header + winner body" and
dropped that line, so the draft was then scored without its flag and the 72.7 %
win looked like a 17.4 % regression.  `tools/apply_scan_winner.py` now keeps
*every* original comment line and warns when the flag set changes across a
splice; always confirm with `tools/score_addrs.py` afterwards.

Whole-pool status: **38 promotions** with this lever, and the remainder of the
new candidate set is low-value (best remaining 70.0 -> 75.0).
