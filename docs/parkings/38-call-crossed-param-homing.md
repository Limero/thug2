# 38 — Call-crossed-param homing residue (callee-saved home + save with no call in range)

**Status: OPEN (2026-08-26).** Single member so far; detection
signature matters more than the count.

## The shape

fn_802451A4 (372B, ScriptZone) contains **no calls at all**, yet WANT:

- homes its arg1 web in **callee-saved r31** despite ≤6 live webs vs ≥8 free
  volatile registers (GCC 2.95 never picks callee-saved under that pressure), and
- emits the corresponding prologue save (`stw r31,0x14(r1)`, frame 0x18).

## Why ngccc cannot reproduce it

Every mechanism that puts a web IN r31 emits **no save**:

- local hard-reg pin (`register s32 a1 __asm__("r31")`) — web lands in r31,
  prologue unchanged;
- file-scope register var — same, no save;
- asm-input barrier / empty-asm clobber (plain and volatile) — same;
- `-fno-gcse`, `-x c++` — same.

Everything ELSE matches shift-aligned once pinned: switch tree root, case
order 0/3/2/1, register map (`var_r4→r4`, `var_r12→r12`, `a1→r31`). The sole
residual is the missing `stw r31` + frame delta.

## Root-cause hypothesis

The retail TU likely had a CALL crossing arg1's live range (e.g. this
function's body was compiled as part of a larger function before splitting,
or an inline expanded into it). The call forces GCC to spill r31; after
splitting/inlining only the spill survives. Same class as M4.91's
80198Exx "needs larger-function context" out-param store-scheduling park
(AGENTS.md §4p) and doc 35's suspected larger-function-split origin.

## Detection signature (before grinding)

A small function whose WANT prologue saves exactly one more callee-saved reg
than any live web requires, where that reg holds a value with no
inter-procedural reason to survive a call (there are no calls). Check: count
live webs; if ≤ number of free volatiles AND want still saves one → this class.

## Retry hints

- Search the DOL for an adjacent/containing retail function whose body
  crosses arg1's range (inlining-partner hunt) — reproducing THAT source
  shape is the only credible route.
- `-x c++` was tried (no change); per-object cflags affecting ra (none known).
- Do NOT re-grind pins/clobbers — all emit the home without the save.

## UPDATE 2026-10-02 (batch w75) — the r31 home + save IS reachable; a DIFFERENT wall remains

The member above is **only half true**. From a *correctly decoded* plain-C body,
fn_802451A4 emits the whole want prologue — `stwu r1,-0x18(r1)`, **`stw r31,0x14(r1)`**,
`mr r31,r4`, plus an 0x18 frame — with **no pin, no clobber, no larger-function
context**. The pins are not needed; what was missing was the *semantics*, which
m2c had wrong in four ways (all now fixed in `src/wip/fn_802451A4.c`):

1. the four bounds bytes at arg0+7/+8/+9/+A are **byte** loads (`lbz`), not
   `*(s32*)` (`lwz`) — `u8` locals, not m2c's `s32` puns;
2. the three case-arm writes at arg2+3/+4/+5 are **byte** stores (`stb`);
   m2c's `*(s32*)(arg2+4)` turned case 1 into a bogus `stw`;
3. case 1's arm0 expression uses the corner byte at **+4**, not +6 (m2c decode
   slip) — with (1)+(2) fixed the whole switch tree, block layout (source case
   order 0,3,2,1) and every arm body become right;
4. the epilogue's 8-byte stack local is `{s32 w; u16 h;}` and is re-read as
   **byte 0** of `w` (not `(u8)w`, which truncates to byte 3). That local is
   what makes the frame 0x18 rather than 0x10 — delete it and you get
   `stwu -0x10` / `stw r31,0xc(r1)` with everything else intact.

Score went 28.0% → **44.1%** and the residue is NOT this class: it is a pure
**3-cycle** of the last three volatile GPRs in the entry block — {switch mode,
half(lo0,hi0), half(lo1,hi1)} land in r7/r6/r8 where the original has
r8/r7/r6. That is invariant to statement order, local types (u8/s32/u32) and
flags (checked ~25 shapes), and it cascades into every `cmpwi`/case arm.

Reusable decode facts from the same body (ngccc 3.9.3):

- **`void *` arithmetic is a BYTE offset** (GNU C rule, same as mwcc/gcc):
  m2c's `temp = arg0 + 1` is +1 byte, so the want's `addi rX,r3,1` +
  `lbz 3(rX)` / `lbz 5(rX)` pair is reproduced exactly by
  `u8 *q = (u8 *)arg0 + 1; … q[3] … q[5];`.
- **A pointer local is never rematerialised into the arms.** The want computes
  `addi rX,r3,1` inside *all four* case blocks; that only happens with a
  per-case `u8 *q` (m2c's shape). One hoisted pointer stays in the prologue
  and costs 3 words (the body comes out 12B short and the score collapses to
  5%).
- **`store 1` into a byte in an arm where the switch value is already 1**: write
  the literal `1`, not the switch variable — GCC then reuses the *switch
  value's own register* for the constant and emits the want's `stb rX,4(r5)`.
  Writing the switch variable instead makes GCC fold `(u8)m == 1` and emit a
  **word** store, which the original never does.
- The sibling fn_80245128 (EXACT, next door, same TU) uses the identical
  `((u32)(a->f7 + a->f9) >> 1U)` idiom, so the mid-point arithmetic itself is
  certainly right; only the register map is not.
