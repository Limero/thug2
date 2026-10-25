# 84 — The memory-resident iterator struct (SOLVED: fn_800CC1D8 16.7% → 100%)

**Status:** SOLVED 2026-10-03. `fn_800CC1D8` (144B) is now a byte-exact
non-asm match. Not promoted (per this round's brief).

## The recipe

The THUG2 "list-walk leaf" functions all share one shape: a 12-byte stack
iterator with a *live* cursor slot and a *dead-ish* label/name slot, walked
until a sentinel, with the cursor re-read from memory every iteration.

Model it as **one real aggregate local** and write **both** fields in the
preheader *and* at every latch:

```c
typedef struct It { void *f0; s32 f4; void *f8; } It;   /* 12 bytes, r1+8 */

It it;
it.f0 = arg0->f44 ? arg0->f44->f4 : NULL;   /* f0 FIRST */
it.f8 = arg0->f44;
while (it.f0 != it.f8) {
    ... it.f0 = it.f0->f4;                   /* f0 then f8 */
        it.f8 = arg0->f44;
}
```

Two things make this work, and both are load-bearing:

1. **One aggregate local, not N pointer locals.** m2c splits the iterator into
   separate `sp8` / `sp10` scalars. ngccc happily scalarises those into
   scratch registers, the frame disappears, and the prologue changes
   (`stmw r29` instead of `stmw r30`). A single aggregate has no scalar
   promotion in ProDG cc1, so its fields stay at fixed frame offsets — which
   is exactly what the want's `lwz 8(r1)` / `stw 8(r1)` / `stw 0x10(r1)` does.
   The unused middle field is not padding for its own sake: it is what makes
   the struct 12 bytes so the two live fields land at +0 and +8.

2. **Field write order f0 → f8.** Writing `it.f8 = arg0->f44;` first makes
   ngccc hoist that store *above* the NULL-guard / `cmpwi` chain (83.3%, and
   the residual is precisely the six preheader words). The want computes the
   guarded cursor first, stores it, and only then stores the label.

Also: spell the guard as a ternary over the **original expression**
(`arg0->f44 ? arg0->f44->f4 : 0`), not over the already-stored `it.f8`. The
second `arg0->f44` is CSE'd into the first load's register, which reproduces
the want's `lwz r9,0x44(r31) | li r0,0 | cmpwi r9,0 | beq | lwz r0,4(r9)`
diamond exactly.

## What it fixed

`fn_800CC1D8`: 16.7% DIFF with a 24-byte-short object → **100% EXACT**,
144B size-exact, all three REL14/REL24 branch targets resolve identically
(verified by hand, since masked scoring hides branch displacements).

## What it does NOT fix (measured on the siblings)

The same struct spelling gets `fn_8022BB14` from 6.1% to a structurally correct
180B (vs 188B want), and `fn_8022B75C` to 128B (vs 180B). The residual is a
single structural feature all three share that plain C still does not
reproduce:

* **Three live `&it` webs.** The wants materialise `&it` in `r9` in the
  preheader, copy it `mr r8, r9`, then copy again `mr r10, r8` before the
  loop. That chain exists because the retail code reached the iterator through
  an inlined C++ `it.Next()` helper whose address argument was live in three
  places. Naming three separate pointer variables (`jp`, `ip`, `kq`) all
  initialised from `&it` gets the object to 180B but ngccc collapses them onto
  one register — the copies are not reproducible.
* **Loop rotation.** The wants keep the preheader advance and the in-loop
  advance as two *separate* copies of the same code. Every plain-C spelling
  lets ngccc see them as one expression, rotate the loop and emit a single
  copy — costing 8–14 words. `-fno-thread-jumps`, `-fno-crossjumping`,
  `-fno-gcse`, `-fno-schedule-insns`, `-fno-expensive-optimizations` are all
  no-ops or worse here.

So: use this recipe whenever the function has **no early-exit branch inside
the loop** (fn_800CC1D8's loop body is straight-line). When the loop carries a
`count == 0` / `found` arm, ngccc's rotation wins and the recipe only gets you
to a structurally-correct-but-misaligned body.

## Members

**Matched with this recipe:** `fn_800CC1D8`.

**Retested with this recipe (variant compiled + measured this round), still
parked:**

| function | clean-C struct spelling measured | want |
|---|---|---|
| `fn_8022BB14` | 180B (`It_Adv` helper form) | 188B |
| `fn_8022B75C` | 128B (`It_Adv` helper form) | 180B |
| `fn_8013E364` | 148B | 196B |

All three stop at loop rotation. Note the masked score is **meaningless** while
the length is off (AGENTS §6cs-1) — these are reported as sizes, not scores.

**Identified as same-family but NOT recompiled this round** — the recipe is
*not* expected to help, each has a different blocker:

- `fn_8013BC8C`, `fn_8013BD50` — twins of `fn_8013E364`.
- `fn_8000BB70`, `fn_8000BA88` — same 12-byte iterator at `r1+8`, but their
  blocker is the three-copies-of-the-advance plus a *surviving dead* `cmpwi`,
  which no source shape reproduces (plain C folds the dead compare away).

See also doc-33 (inlined-iterator volatile webs) and doc-42
(double-branch walker diamond) — this is the same neighbourhood, solved from
the aggregate side rather than the pass side.