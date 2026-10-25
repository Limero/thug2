# 87 — `(u16)x << 2` fuses into `rlwinm` iff the truncated value has ONE use; the two-use latch also needs a step copy C will not emit

**Status: WALL.** `fn_80079300` stays parked at **97.75 %** (356 B, 2 words: the
copy and the home that consumes it). The truncation half of the shape is solved;
the copy half is not reachable from C, and writing it as inline asm reproduces
the bytes but is instruction transcription, not a decompilation — see
"the asm route is not a solution" below.

## The rule

ProDG/ngccc's `combine` pass rewrites

```
(zext<subreg u16> X) << 2      ==>     rlwinm  X, 2, 0xe, 0x1d
```

i.e. `(u16)x * 4`, `(u16)x << 2`, `(u16)x * sizeof(u32)` and
`(u32)(u16)x * 4` all become the **single** instruction
`rlwinm rX, rX, 2, 0xe, 0x1d`. **This fusion happens if and only if the
zero-extended value has exactly one use.**

Corollary that saves a lot of compiles: **no register pin, no store-order
permutation, and no scheduling flag can separate these two instructions.** The
pair is joined by CSE/combine, not by the scheduler. If a want shows a standalone
halfword-clear truncation followed by a separate shift-left-by-2, then retail's
source had a second use of the unshifted truncation, and the question is only
what that second use cost in words.

## The full latch shape (`fn_80079300`)

Retail's loop latch, after the `lbz`/`slw` that computes `1 << w`:

```
clrlwi r0, r0, 0x10      ; n  = (u16)(1 << w)
slwi   r9, r0, 2         ; step = n << 2
mr     r0, r9            ; copy of step
subf   r30, r9, r30      ; b -= step      (original)
add    r29, r29, r0      ; a += step      (copy)
```

Six words, and the body contains **no stores at all**, so the second use of `n`
is not a store and the `mr` is a genuine second home for `step`. Plain C
collapses it in both directions: one register for both consumers, or the fused
`rlwinm` back.

## The second use of `n`: a one-word volatile store (95.5 %)

The cheapest second use that keeps the split is a `volatile` store of the
*unshifted* value into a declared-but-unused struct pad:

```c
u16 n = (u16)(1 << o->dim->w);
*(volatile u16 *)&o->pad_0x4 = n;   /* the 2nd use — 1 word, and it is inert */
a += n << 2;
b -= n << 2;
```

It lands in the slot where retail has the `mr`, so the object is size-exact and
`clrlwi`/`slwi` are separate again. `volatile` is load-bearing (a dead
non-volatile store is removed); do **not** aim it at a live field, or it
re-colours the surrounding allocation. Placement is free (before the mask load,
between the updates, after both) — all 95.5 %.

## The copy: what plain C produces instead

With the split in place, both consumers read the same register, so the body is
2 words from exact (97.75 %). Retail's `subf` takes the original `r9` and the
`add` takes the copy `r0`. Measured attempts to get that split out of C:

| spelling | result |
|---|---|
| both consumers on `step` (the 95.5 % body) | 97.75 %, homes swapped |
| statement order reversed (`b -= step` first) | swapped the other way, same 2 words |
| assignment forms `a = a + step` / `b = b - step` | bit-identical |
| `u32 step` staged through a second named local | coalesced, identical |
| copies / `+r`/`+f`-style barriers on the step | copy moves, roles do not |
| pins on the two homes | dropped by cc1 (derived webs) |
| 10 scheduling/optimisation flags | neutral or worse (82 % / 52 %) |

A copy survives only when the two webs genuinely interfere (doc 88's named
pointers work because a call separates the live ranges). Here nothing sits
between the two updates, so local-alloc is free to use one register.

## The asm route is not a solution

A positioned `__asm__("mr %0,%1")` into an r0-pinned variable, with an
unmentioned `n` operand to keep the truncation alive, makes the function
**100.0 %, 0 diffs**. That is the measurement, and it is recorded so it is not
re-derived as a "finding": it is a hand-written instruction standing in for
codegen, i.e. transcribing the original assembly one word at a time. Under this
project's matching-decompilation standard a function only counts when the C
source is what produces the bytes, so this draft stays parked and the promotion
was withdrawn.

## Measured table (whole latch, default `-O2 -G0`)

| form | object | score |
|---|---|---|
| single `u32 step = (u16)(1 << w) << 2` | 348 B (2 short) | 80.5% |
| volatile store of `n` as 2nd use | 356 B | 95.5% |
| same, after the `memcpy` arg-order fix | 356 B | 97.8% |
| hand-written `mr` copy (asm) | 356 B | 100.0% — **not promotable** |
| `if (n == 0) continue;` as 2nd use | 356 B | 77.5% |
| `* 4` / `sizeof(u32)` for one side, shift for the other | 348 B | 80.5% |
| volatile **read** as 2nd use, or store of the **shifted** value | 352 B | 92.1% |

Why the mixed shift/multiply spelling fails: ngccc canonicalises **both** to the
same `rlwinm`, so the `clrlwi` is back to one use. The two spellings have to
differ *below* the shift.

Flag sweep on the 95.5% body: `-fno-gcse`, `-fno-thread-jumps`,
`-fno-sched-spec`, `-fno-strength-reduce`, `-Os` are all no-ops;
`-fno-schedule-insns2` is worse (82.0%), `-fno-schedule-insns` far worse. That
the split is invisible to `-fno-gcse` confirms this is a **combine/CSE**
phenomenon, not a scheduling one.

## Applies to

any THUG2 function whose want contains a `clrlwi rX, rY, 0x10` immediately
followed by `slwi`/`rlwinm` of the same value — the giveaway that retail's
`(u16)` cast had two uses. Search the want for `rlwinm` with MB=0xe, ME=0x1d
(shift 2, mask 0x3c): each hit is either already-fused `(u16)x*4`, and each
*unfused* neighbour pair (`clrlwi` then `slwi`) is a two-use truncation site.
If the site is followed by an `mr` of the shifted value, expect the same copy
wall.

## DOL-wide scan: where else this rule applies

`<scratch> walks every word of `.text` and reports a width
truncation (`clrlwi` / `extsh` / `extsb` / `extsw`) whose **destination is the
source of the next shift/rotate** — i.e. an unfused `(T)x << k`. 38 sites in the
whole DOL, of which **16 fall inside a `src/wip/` draft**:

| draft | site | shape |
|---|---|---|
| `fn_80072E4C` | 0x80073070 | `clrlwi r9,r9,0x18 ; slwi r0,r9,0x18` (`(u8)x << 24`) |
| `fn_80073A5C` | 0x800751A0, 0x80075268 | `clrlwi r11,r11,0x10 ; rlwinm r0,r11,8,0x10,0x17` (`(u16)x << 8`) |
| `fn_80079300` | 0x80079420 | `(u16)x << 2`, plus the step copy (this doc) |
| `fn_800C3E48` | 0x800C405C | `extsb r0,r0 ; slwi r0,r0,2` (`(s8)x << 2`) |
| `fn_800F198C` | 0x800F19D0 | `clrlwi r30,r28,0x12 ; slwi r31,r30,2` |
| `fn_801168CC` | 0x80116A60 | `clrlwi r0,r0,0x19 ; rlwimi r9,r0,0x10,...` |
| `fn_8012D62C` | 0x8012DB20 | same shape |
| `fn_8017C2CC` | 0x8017C4B4 | `extsb r0,r0 ; sraw r0,r0,r29` |
| `fn_80238314` | 0x802383D4 | `clrlwi r10,r7,0x18 ; slwi r5,r10,4` |
| `fn_80251490` | 0x80251614 | `clrlwi r16,r11,0x1e ; slwi r16,r16,3` |
| `fn_80251B70` | 0x80251E00 | same shape |
| `fn_80027720` / `fn_80029A30` / `fn_8002AFB0` | 3 sites | `extsh ; rlwinm ...,0,0x10,0x10` (sign-extend, different idiom) |

Caveat found while working the list: **the site must be one where got actually
fuses.** `fn_80072E4C` already matches at 0x80073070 with its current body, so
the rule has nothing to fix there. Check the site against `want_got.py` before
spending compiles — the list is a shortlist, not a work order: the remaining
members are 9–84% overall, i.e. their truncation site is not their only
residual.

Reusable form of the scan: *a want instruction that ngccc would fuse into one is
a "retail had two uses" marker.* The same reasoning applies to any combine rule
you meet (address folding, `x*4`, sign-extend+shift); the fix is always to find
the second use and make it cost the number of words retail spends on it.

## Body traps specific to this exemplar (carried over from doc 80)

* **m2c decodes `rlwinm rX,rX,2,0xe,0x1d` as `((x * 4) & 0x3FFFC)`** and that
  spelling folds the other way (`li 4 / slw / rlwinm r3,r3,0,0xe,0x1d`). The
  working spelling is a narrowing cast on the shift's operand,
  `(u16)(1 << dim->w) << 2`.
* **A draft's `// FLAG: -Os` is often just wrong** — this body wants plain
  `-O2 -G0` (`-Os` 65.5%, `-O1` 16.9%). Re-measure the flag on the rewritten
  body.
* **`*(Arena **)&lbl_X` beats a bare `(T *)0xADDR` literal**: the address-of a
  `SYMBOL_REF` gives retail's `lis %ha / lwz %l(rX)` pair with the HI16 CSE'd
  across later uses, while the literal folds to `lis`+`ori` and, once indexed,
  splits into two base registers (doc 51).
* **`void memcpy();` must stay unprototyped** when the want has `crclr cr1eq`
  before the call (recipes §4n item 21). Every other callee here must stay
  prototyped — that mix gets all three `crclr`s and the four crclr-free calls
  at once.
* The second `memcpy`'s `mr r4`-before-`mr r3` order is a scheduler tie; source
  argument order was left as written (calls 1 and 3 agree with retail either
  way).

## The opposite failure, for contrast

`fn_8015BCB4` (96.0%, size-exact) is the mirror image and is worth recording
because it saves a flag sweep. want's canonical arg-setup order at every call brackets the two halves of the 64-bit constant around the r3 setup: the r5 operand and the constant high half come first, then the r3 operand, then the constant low-half completion, which is what a ready-list scheduler emits when the completion depends on the high half and the r3 instruction is independent, while ngccc emits high half, low half then r3 in sequence. Doc 80 says a callee's **return
type** decides this (non-void makes r3 a pseudo-OUTPUT and pushes it to the end
of the group) — and that is confirmed live here: `void AddInteger(...)` makes
call #1 bracket correctly. But the *same* declaration then breaks call #3, and
`s32` fixes #3 while breaking #1.

**So: when two calls to the SAME callee in one function want opposite arg-setup
orders, the difference is per-call-site LUID, not the callee's prototype, and the
swap is unreachable from C.** Do not sweep flags, casts or return types there.
