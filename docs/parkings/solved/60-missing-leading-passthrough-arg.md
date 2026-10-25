# 60 — m2c drops a leading *pass-through* argument

**Status: SOLVED (2026-09-15) — 3 functions promoted byte-identical, ~23 more
drafts improved in one session.**
Scanner: `tools/lead_arg_scan.py`, prefilter `tools/slot_low_scan.py`.

## Symptom

The call's whole argument block sits **one register slot low**: want saves arg0 into r31 and loads the constant 1 into r4 before the branch, while got saves arg0 the same way but loads the constant into r3 instead. Every word of the argument block mismatches, but the *function* is otherwise
identical — which is why these drafts sit at 70–90% instead of 0%.

## Root cause

m2c has no way to know a wrapper is *forwarding* its own incoming register, so
it emits the call with the arguments it can see:

```c
void fn_8005C944(Unk_2EF06E12 *arg0, s32 arg1) {
    ...
    fn_8005C9A8(1);                       /* m2c */
    fn_8005C9A8(arg0, 1);                 /* retail: r3 is still arg0 */
```

Retail simply never moves r3: the value is already in the argument register
from entry, so the `bl` only has to set up r4.

## Second form: the parameter list order is wrong

`fn_800A1AE8` shows the same root cause one level up. m2c emitted its
parameters in the order it *found* them, not the order the ABI assigns them:

```c
/* m2c:  r3=arg1, r4=arg2, r5=arg3, r6=arg0  -- every home one register low */
void *fn_800A1AE8(Unk_2EF06E12 *arg1, Unk_C7387A53 *arg2, s32 arg3, s32 arg0);

/* real: r3=arg0, r4=arg1, r5=arg2, r6=arg3 */
void *fn_800A1AE8(s32 arg0, Unk_2EF06E12 *arg1, Unk_C7387A53 *arg2, s32 arg3);
```

**m2c's own parameter names are the tell**: when they read `arg1, arg2, arg3,
arg0` (or `arg1, arg0`) but the declaration order is not a permutation that
matches the register order, the whole body is shifted. Same family as
`tools/fix_missing_lead_arg0.py`, which detects it from the WANT prologue (the
first arg register that is *read before written*).

## Cheapest tell

`tools/slot_low_scan.py`: compile the draft, disassemble WANT and GOT
position by position, and count words where **WANT writes `rN` and GOT writes
the same instruction kind to `r(N-1)`** (N in 4..10, `li`/`mr`/`lis`/`ori`/
`addi`/`lwz`/`lfs`). Two or more such words in one function is a reliable
signal; 401 of the 1,763 no-park drafts have at least one.

## Scanner

`tools/lead_arg_scan.py` walks every call site, tries prepending each of the
**enclosing function's own parameters** (cast to `s32` so the value is not
re-loaded) at every argument position, fixes the callee prototype, and keeps
the best A/B per address. Two traps already hit and fixed:

- the "own function" regex must require a `{` — otherwise it matches the first
  *prototype* in the file and the parameter list comes out empty;
- prototype lines must be excluded from the call regex, or `void fn_X(s32);`
  is read as a call to `fn_X` with the argument `s32`.

## Members promoted (DOL `cmp`-verified byte-identical)

| fn | size | score | notes |
|---|---|---|---|
| `fn_8005C944` | 100B | 42.3 → 100 | `fn_8005C9A8(arg0, 1)` + `fn_8005D194(arg0->unk0x8, 3)` (also doc 59) |
| `fn_800F21E8` | 136B | 85.3 → 100 | `fn_800F2CF0(arg0, 1)` + the doc-53 `s16` view type |
| `fn_800A1AE8` | 116B | 74.3 → 100 | parameter-list reorder + `fn_8009FCD8(temp_r31, arg2)` + `s16` view |

Best partials: `fn_800A33E4` 74.3 → 94.3, `fn_8018BED8` 73.6 → 88.7,
`fn_80126E28` 79.3 → 86.2, `fn_80127C14` / `fn_80127AAC` 74.2 → 77.4.

## One stop-loss on a look-alike

`fn_800F45A4` (78.0%) carries the `li r4,0` tell at two sites but is **not**
this defect: retail's `li r4,0` follows two *virtual calls* whose results stay
in r3. The scanner's only candidate (`fn_80054C6C(arg0, 0)`) makes it worse
(→ 40.5), and nesting the vcall as the first argument collapses the whole
function (→ 16.7%). Its residual is a register-home/scheduling question.

## Note: the parameter *type* matters for float

The scanner inserts `s32`, which is correct for integer-like slots (a float
slot would need the real float type and a matching `lfs`). It skips any
parameter whose name starts with `f` for that reason. Always sanity-check the
inserted argument's type before promoting.

## Addendum 2026-09-15 (n) — re-run over the 1,338 newly exposed addresses

Same story as doc 59: the "remainder is low-value" verdict was formed on a pool
that was missing 44 % of the corpus (doc 62).  Over the never-scored addresses
(`slot_low_scan.py` -> 105 candidates with >= 2 hits, `lead_arg_scan.py` over
those) the lever produced **12 more improvements, no regressions, no EXACT**:

`fn_80116840` 43.2 -> 51.4 · `fn_80206554` 31.2 -> 50.0 ·
`fn_80118A84` 35.5 -> 36.4 · `fn_800D68B8` 14.5 -> 34.4 ·
`fn_801147F8` 7.6 -> 18.1 · `fn_800E5EFC` 12.1 -> 17.2 ·
`fn_80118704` 13.8 -> 15.8 · `fn_800E4F90` 12.8 -> 14.0 ·
`fn_800E9F8C` 12.4 -> 13.2 · `fn_80117220` 7.1 -> 10.3 ·
`fn_8011562C` 5.0 -> 10.1 · `fn_80234264` 2.9 -> 3.4.

No new member reached EXACT, so the doc's promotion count is unchanged; the
lever now stands at 3 EXACT + 35 improved.

## Addendum 2026-09-16 (o) — third form: the argument is the PREVIOUS call's return

**`fn_800EFDC0` SOLVED (87.0 -> 100.0), promoted.** Same symptom as the doc's
main form — want `li r4, 8` / got `li r3, 8`, rest of the function fine — but
the missing argument is not the enclosing function's parameter: it is the
**return value of the call right before it**, i.e. the two calls are NESTED:

```c
// draft (both calls read as independent statements -> 8 lands in r3)
fn_80009A44(0x18);
arg0->unk0x4 = fn_800F10F0(8);
// want: r3 is passed through unchanged, so arg1 IS the allocator's result
arg0->unk0x4 = (s32) fn_800F10F0(fn_80009A44(0x18), 8);
```

The tell is want's `bl CalleeA` / `li r4,K` / `bl CalleeB` with **r3 never
written between the two calls**. That shape cannot be produced by a statement
sequence, so a draft that scores in the high 80s with this setup has a
*missing nesting*, not a scheduling residual.

Two further levers mattered here, both worth trying on every member of this
doc:

1. **`reorder_scan.py` is the prefilter.** The draft was surfaced by
   `tools/reorder_scan.py` ("reorder hunks=1 biggest=3 resid=12"), not by
   `slot_low_scan.py`. Rule of thumb confirmed on this draft and then used to
   re-check the other 18 reorder hits: **a reorder hunk whose GOT side carries
   an extra `crclr cr1eq` is an undeclared callee with a WRONG ARGUMENT COUNT**
   (docs 56 + 60 at once), not a coin. None of the other 18 had it, so the
   tell is rare but decisive.
2. **The surviving store order is the source order.** want emitted
   `[stw 0xc(r30)][mr r3,r30][stw 8(r30)]`; the draft's `0xC` then `0x8` scored
   89.5%, swapping them to `0x8` then `0xC` was EXACT — the trailing
   return-value `mr` splits the two stores, so the *second* store in source is
   the one after the mr.

**Same-day follow-ups — the recipe is now at 2 promotions + 2 decoded sites.**

| draft | was | fix |
|---|---|---|
| `fn_80173B98` | 56.7 | **100.0, promoted** — TWO nested calls: `fn_8009FDD8(fn_8017471C(...), QB_TRICK)` and `fn_801EF978(fn_8009FDD8(temp_r30, QB_SKATERENDRUN), 0)` |
| `fn_802359A4` | 56.45 (see artifact note) -> 45.2 honest | site 1 `fn_80129068(fn_80128F94(), 0xEA6, 1)`; site 2 `fn_801F50B0(fn_801F672C(), QB_LOAD_SK5ED, temp_r30)`. Still parked for an unrelated register-home residual |

Two additions to the doc's own procedure:

* **The tell is a constant in the wrong register** (`want li r4,K` / `got
  li r3,K`) OR a `bl` immediately following another `bl` with **no r3 write in
  between**. The second form is the one to look for in want's disassembly
  directly: it cannot be produced by a statement sequence at all.
* **Check the callee's promoted definition first.** `fn_8009FDD8`, `fn_801EF978`,
  `fn_801F10F0` and `fn_801FAC10` are all promoted, so their real arities were
  read off `src/fn_<addr>.c` instead of guessed — that turns the fix from a
  coin flip into a one-liner (and it is how `fn_801FAC10(fn_801FC0E0(), arg1)`
  was found in `fn_802359A4`: the real signature is 2 arguments, not 1).

**Score artifact warning (found while parking `fn_802359A4`).** That draft's
recorded 56.45% was **two compensating errors**: a spurious `crclr cr1eq`
(missing prototype, +1 word) against retail's `mr r0,r3` double copy the draft
never emitted (-1 word). The two cancel, so *every word after the damage site
lines up by accident* and the score looks like a near miss. Removing only the
prototype drops it to 27.4%. Before trusting a high score on a draft with a
known missing prototype, fix that prototype FIRST and re-measure.

Type note (the doc's own warning, now with a concrete case): the inserted
argument's type must be real. Here the nested callee forwards to the allocator
`fn_8000F10C` (`char *`) and its promoted definition said `void` only because
the decompiler dropped the unused return, so `src/fn_80009A44.c` was retyped
to return the struct it allocates — that retype alone is byte-identical
(re-scored EXACT) and makes the passthrough legal C instead of a cast.

## Addendum 2026-09-17 — the purest tell yet: a `bl` with **zero** argument setup

`fn_800F3598` (120B) — **50% → 100% EXACT, promoted.** Its `bl 0x800f3684` is
preceded by nothing at all: r3 still holds the incoming arg0 (the function only
did `mr r30, r3`) and **r4 is never written**, so the callee's arguments are the
caller's own two incoming registers. That means the wrapper is 2-argument and
forwards both:

```c
void *fn_800F3598(Unk_A9157FE7 *arg0, s32 arg1) { ... fn_800F3684(arg0, arg1); }
```

m2c had emitted a 1-argument `fn_800F3684(temp_r9, -1)` — wrong arity *and* the
wrong first argument (the +0x38 sub-structure instead of arg0).

This is the strongest form of the doc's tell because it needs no register-slot
arithmetic: **if want's `bl` has an empty argument block, count how many
argument registers the caller received and forward all of them.** The word-count
check cannot catch it (both sides are 120B here), and neither can a score — the
draft sat at exactly 50%.

Sequence used, all measured on the same body: 1-arg `(temp_r9, -1)` 50% →
1-arg `(arg0, (s32)temp_r9)` 48.4% → 2-arg passthrough **73.33%** → then the
store-run rotation of doc 09 (2026-09-17 addendum) closed the remaining three
words to 100%. Two levers from two different docs, stacked.
