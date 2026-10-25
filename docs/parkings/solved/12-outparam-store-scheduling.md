# Issue 12 — Out-param store scheduling (store before address-compute)

**Status: STALE — RESOLVED (verified 2026-08-23): ALL FIVE family members**
**(80198E4C/8F3C/8F7C/FBC/FFC) are MATCHED and promoted in src/.** The
"unreproducible" verdict was wrong — a later round found the shape without
updating this doc. Do not re-open; kept for the store-scheduling analysis.

~~**Status:** PARKED (as of M4.9x; park set is a moving target — re-verify before trusting) (5 functions: 80198E4C, 80198F3C, 80198F7C, 80198FBC,
80198FFC)~~

## The problem

A 5-function family of out-param wrappers (64B each, byte-identical except
for the callee and a magic constant) with exactly ONE diff each: a
2-instruction schedule swap in the out-param initialization.

Original (fn_80198E4C): the function opens with a 0x10-byte frame, saves the link register, initialises the stack out-slot at offset 8 with the constant 3 BEFORE computing the adjusted object address, then materialises the magic constant, takes the address of the stack slot, zeroes the final argument register, calls the callee with the adjusted pointer plus magic plus slot address plus zero, and returns the callee-modified slot value. The key ordering fact is that the out-slot store precedes the arg0-plus-4 address computation. Compiled (every source form tried): GCC emits the address computation before the out-slot store — the two instructions swap.

## Why it's parked

The C is trivially:

```c
s32 sp8 = 3;
fn(arg0 + 4, 0xCE87E4E3, &sp8, 0);
return sp8;
```

but GCC 2.95.2 places the `addi r3,r3,4` (arg0+4) before the store of sp8 in
**every** shape tried. The want's ordering (store before address compute)
needs a register-pressure context — likely the function was compiled as part
of a larger TU where the scheduler had different freedom, or a sibling
inline — that a standalone function cannot reproduce.

## What was tried (13 variants, all identical)

- decl-init (`s32 sp8 = 3;`), separate store statement
- pointer local, ptr-arith (`arg0 + 1` on `s32*`), `(char*)arg0 + 4` cast
- magic as separate variable, two-statement split
- `volatile` sp8, explicit `*p = 3` store through a pointer

## Research directions for an external AI

> **Cross-clone note (2026-08, plan Items E/G):** Sims2DECOMP's wall
> catalog has the identical class - out-param `stw` before a dependent
> `addi`, "compiled as part of a larger function then split" - and it
> stayed locked through their store-pinning catalog (their volatile-
> store pinning recipes apply to the doc-09/16 families, not this one).
> Treat as structural (mutually-exclusive store/hoist coupling, same as
> docs 09/15): do NOT re-grind the 13 source variants; park until a
> stw-before-addi sibling shape appears (research direction 2), then
> copy its source. Their register-coloring fixes (Item E) target role
> swaps, which this family does not have.

1. This is a pure scheduler order swap of two independent instructions
   (store to stack slot vs `addi` on r3). GCC 2.95.2's `sched.c` priority
   heuristics place the `addi` first because it feeds the `bl` argument
   chain; the game compiler emitted the store first (possibly because its
   scheduler processed the prologue-adjacent store early).
2. If another function in the same DOL shows the same `stw r0,8(r1)`-before-
   `addi r3,r3,4` schedule, copy its exact source shape (that's the fastest
   un-park). Search the DOL for `li rX,N; lis rY,..; stw rX,8(r1); addi
   r3,r3,4; ori rY,..` patterns.
3. Investigate whether compiling the wrapper with an extra volatile read of
   sp8 *between* the store and the call (e.g. `(void)sp8;`) changes the
   schedule — untried.
4. Consider matching via the parent TU: if these wrappers belong to a
   larger source file, matching the whole file (multi-function object) might
   reproduce the scheduler's context.

## Where to look

- Drafts: `src/wip/fn_80198E4C.c` (and 8F3C/8F7C/FBC/FFC).
- History: `AGENTS.md` §4p (full analysis, 13 variants, "don't retry unless
  you find a matching stw-before-addi sibling").
