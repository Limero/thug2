# Issue 04 — Dead `li rX,4; stw rX,8(r1)` stack store in bit-flag setters

**Status: SOLVED (2026-08-23) — all three family members byte-exact at 100%.**
The "dead store" was never a compiler artifact: a `volatile s32 sp8; sp8 = K;`
local with ZERO readers emits exactly `li r9,K; stw r9,8(r1)` under ngccc (the
doc's earlier "volatile doesn't match" verdict failed only because the sibling
shapes ALSO needed the fixes below). Address correction: doc said 0x8003F708/
0x8003F77C — symbols.txt has **fn_8013F708** (0x2C, its wip draft was already
EXACT) and **fn_8013F77C**.

## Solutions

**fn_8013F6E4 (36B) — 100.0%.** Two extra keys beyond the volatile store:
(a) named-temp flags load FIRST in source; (b) the REAL mask is `& ~1`, not
`& ~4` — capstone prints `rlwinm r0,r0,0,0,0x1e` which is MSB-first MB/ME =
mask 0xFFFFFFFE (recipe §6p-115). With `& ~4` ngccc folds `(x&~4)|4 → ori`
alone and the whole shape collapses:

```c
void fn_8013F6E4(void *arg0) {
    volatile s32 sp8;
    s32 temp_r0;

    temp_r0 = *(s32 *)((char *)arg0 + 0x68);
    sp8 = 4;
    temp_r0 = (temp_r0 & ~1) | 4;
    *(s32 *)((char *)arg0 + 0x68) = temp_r0;
}
```

**fn_8013F77C (124B) — 100.0%.** Same volatile-sp8 trick (`sp8 = 2`) plus:
named `temp_r9` flags load first (an inline field-read in the if-condition
folds to andi. and steals registers); prototype `s32 fn_8013F74C(void *);`
(kills crclr); the value web `v` defined only AFTER the call so it stays in
r3 (pre-initializing before the call pushes it into a saved reg + widens the
stmw span — §4t corollary):

```c
s32 fn_8013F74C(void *);

s32 fn_8013F77C(s32 arg0) {
    volatile s32 sp8;
    s32 temp_r9;
    s32 var_r11;
    s32 v;
    s32 temp_r0;

    temp_r9 = *(s32 *)((char *)arg0 + (s32)0x68);
    var_r11 = 1;
    sp8 = 2;
    if (!(temp_r9 & 2)) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        return 0x3E8;
    }
    if (fn_8013F74C((void *)arg0) == 0) {
        v = *(s32 *)((char *)arg0 + (s32)0x20B4);
    } else {
        v = 0;
    }
    temp_r0 = v * 2;
    v = 0x1F4;
    if (temp_r0 > 0x1F3) {
        v = temp_r0;
    }
    return v;
}
```

---

# ORIGINAL ANALYSIS (historical)

**Status:** PARKED (as of M4.9x; park set is a moving target — re-verify before trusting) (3 functions: fn_8013F6E4, fn_8003F708, fn_8003F77C)

## The problem

A family of tiny bit-flag setter functions contains a **dead stack store**
that the game compiler emits but no available ngccc build reproduces.

Original (fn_8013F6E4 — sets bit 2 of the flags field at offset 0x68): the function opens a 0x10-byte frame, loads the flags word from object offset 0x68 into r0, materializes constant 4 in r9 and stores it to unused stack slot 8(r1) as the dead store, then masks with the rotate-and-mask covering all but bit 0 (capstone prints the word for mask 0xFFFFFFFE), ORs in constant 4, and stores the result back to object offset 0x68.

The `li r9,4; stw r9,8(r1)` pair writes the constant 4 to a stack slot that is
never read again. This is a leftover from the original source (a local
variable that was inlined away except for its store, or a debug/assert value).
ngccc will never emit a store to an unused stack slot from ordinary C — dead
stores are eliminated.

## Why it's parked

- The C equivalent (`o->flags |= 4;`) compiles to just `lwz/rlwinm/ori/stw`
  without the dead store.
- Adding a fake `volatile` local writes *through* the stack but with different
  register/scheduling (and adds a frame), so it still doesn't match.
- This is classified in-repo as the same unreproducible-codegen class as the
  FPR frame quirk (Issue 01) — the game compiler kept an artifact that ngccc
  removes.

> **Day-0 A/B caveat (2026-08, cross-clone):** "All available ngccc builds"
> is a closed set — Sims2DECOMP (same ProDG family) proves the four
> installed point-versions (3.5–3.9.3) are codegen-identical (609 fns x 4,
> zero flips), so no point-version swap reproduces this. The dead store is a
> source-style artifact (see research direction 1, e.g. a helper-inline that
> left `*(s32*)(sp) = 4` behind) or a distinct game SN build.

> **Cross-clone note (2026-08, plan Item G):** Sims2's locked-wall class
> "compiler emitted a store/artifact ngccc removes" (dead-store and
> r0/r1-adjacent scratch preservation) confirms this family as
> structural-preservation - their catalog has no legal C shape or flag
> that re-emits a dead stack store either. Park; revisit only if a
> `-fno-dse`/`-fkeep-*`-equivalent flag is ever found (research
> direction 3) or a sibling source style surfaces (direction 1).

## What was tried

- Plain bit-set forms (`|=`, read-modify-write, temp variable).
- `volatile` locals, unused locals assigned 4, attribute tricks.
- All available ngccc builds and flag sets.

## Research directions for an external AI

1. Determine why the original compiler emitted a dead store. Common causes:
   (a) the value 4 was previously passed through a helper that got inlined;
   (b) the source wrote `o->unk = 4` where `unk` is a union member that was
   later not read; (c) the source had `*(s32*)(sp) = 4` for a value read by a
   sibling call that GCC couldn't prove dead at -O2.
2. Since the middle instruction stream matches, consider whether a **partially
   matching** approach works: match everything except the dead store and
   accept a 1-2 instruction diff, or find a sibling function in the same game
   whose compiled form retains the store.
3. If a GCC 2.95.x `-fno-dse`/`-fkeep-*` flag (or a ProDG-specific
   `-Xdlcom`/`-Xc` option) forces retention of dead stores, that flag would
   un-park the whole family.

## Where to look

- Noted in the matched getter family: `src/fn_8013F734.c` header ("nearby
  setters … parked — they contain a `li rX,4; stw rX,8(r1)` dead-store we
  can't reproduce").
- Related bit-flag getters (matched): fn_8013F734, fn_8013F74C, fn_8013F764.
