# 25 — Call-accumulator register choice (r0 vs arg home register)

**Status: STALE — RESOLVED (2026-08-23 verification).** The wip draft
`src/wip/fn_80108114.c` now compiles **EXACT (100%)** under the plain default
flags (verified with the standard masked sweep); the accumulator question
below was answered by an earlier round without updating this doc. Keep the
analysis for the general "value feeding a call arg-slot" class.

**Status:** OPEN (single exemplar; parked 2026-08-22, round)
**Affected:** `fn_80108114` (68 B RGBA-color setter wrapper), best 64.7%

## Symptom

`fn_80108114(a, r, g, b)` calls the empty leaf `fn_8003EF4C` with four
arguments (`r3 = arg0` untouched passthrough, `r4 = a+0x10`, `r5 = color`,
`r6 = color`). WANT builds the color **inside arg1's home register**: it shifts arg1 left by 24 into r4, shifts the next channel left by 16 into r5 and ors it into the accumulator, shifts the third channel left by 8 and ors it in, ors in the 0xFF alpha, copies the finished color out to r5 first, only then reuses r4 for the pointer argument (object plus 0x10), mirrors the color into r6, and branches to the leaf. ngccc 3.9.3 always materializes such chains into **r0** whenever the consuming call needs r4/r5 as argument slots: it performs the same shift-or-ori chain in r0, computes the pointer argument first with no copy-from-r4 needed, and moves the color out of r0 into the argument registers.

## What was tried (all fail on the accumulator choice)

- Single `|` chain, sequential `|=`, multi-temp, reversed or-chain,
  `*` instead of `|`, u32 types, reusing `arg1` itself as the temp.
- `__asm__("" : "+r"(t))` barriers between every step — these DO fix the
  shift evaluation order (want slwi-r4 first) but the chain still lands in
  r0.
- `-fno-schedule-insns2 -fno-schedule-insns`: fixes shift order too (9/9
  color words match) but not the register choice.
- Explicit local register vars `register s32 t __asm__("r4");` — GCC 2.95
  dead-code-eliminates the whole computation when the var feeds a plain C
  call (only guaranteed for inline asm consumers).

## Retry hints

- The pattern scan found NO sibling in `.text` today (the slwi-24/slwi-16/or/
  slwi-8/or/ori-0xff sequence with r4-first order is unique), so this may be
  a one-off until another color setter shows up.
- A working form must make GCC believe the color's only available home IS
  r4 at chain time while still consuming r4 later — maybe an ABI-visible
  trick (struct-in-registers first arg?) or a postprocess/permuter approach.
- If cracked, sweep the `<< 0x18 | << 0x10 | << 8 | 0xFF` shape across all
  wip drafts.
