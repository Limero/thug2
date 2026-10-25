# 81 — the DEAD `cmpwi` (ProDG block-merge leftover) and how to keep the body after it

Two findings from `fn_8009BAEC` (0x8009BAEC, 252B, DIFF 11.1% → NEAR 79.4%).

## 1. Reading ngccc's `rlwinm` mask constants (this bit me for an hour)

`rlwinm` fields are `opcode(31-26) rS(25-21) rD(20-16) SH(15-11) MB(10-6) ME(5-1) Rc(0)`.
MB/ME index bits of the **rotated** value, so for `SH == 0` a single-bit mask is
`MB = ME = 31 - k` for bit `k`:

| want text (capstone) | MB,ME | meaning |
|---|---|---|
| `rlwinm rD,rS,0,0,0`     | 0,0   | `x & 1` |
| `clrlwi r27,r30,0x1f`    | 31,31 | `x & 1` (capstone's alias is misleading) |
| `rlwinm rD,rS,0,0x1e`    | 0,30  | `x & 0x7FFFFFFF` |

So **`clrlwi rX, rY, 0x1f` is `& 1`, not `& 0x80000000`.** I initially wrote
`arg & 0x80000000` and chased the mask for a long time.

Related ProDG constant trap, measured on this object: **a mask constant with
bit 31 set is encoded as if bit 31 were clear.** `x & 0x80000000` compiles to
`rlwinm rX,rS,0,0,0` (= `x & 1`) and `x & 0x40000000` to `mb=me=1` (correct);
`x & 0xFFFFFFFE` encodes as `rlwinm r0,r0,0,0,30` + a separate `ori r0,r0,2`,
i.e. `x & 0x7FFFFFFF | 2`, not `x & 0xFFFFFFFE | 2`. Never spell a `&` mask with
bit 31 set; if want shows `0,0` (bit 0) or `0,30` (bit 31 dropped) that is a
ProDG constant-width artefact, and the *semantics* you want is the low-31 mask.

## 2. The dead compare, and the shape that reproduces it

`fn_8009BAEC`'s want contains `cmpwi r26,2` at 0x8009BB0C whose CR0 is
**overwritten by `cmpwi r0,1` two instructions later with no branch in
between** — a genuinely dead compare (823 such dead-CR0-setter sites exist in
the DOL; this function is one of the few where it sits in the prologue).

**Mechanism (measured).** ProDG/GCC 2.95 drops the *branch* of an `if` when
both arms become the same block, but leaves the `compare`:

* `if (c) { A } else { A }` with a **small, call-free** A → `cmpwi` survives,
  no branch. ✅
* same but the arm contains a **call** → GCC merges the code and leaves a
  *live* `bne` guard to the join (`cmpwi; bne END; <body>; END:`), or a stray
  `bl +4`. ❌
* `if (c) { }`, `if (c) ;`, `c == 2;`, `(void)(c == 2)`, `while (c) break;`,
  `switch (c) { case 2: break; }`, `switch (c) { case 2: default: B }`,
  `if (c) { } else if (d) { B }` → **nothing at all**. ❌

**The shape that works (0 instructions of asm, pure C).** Duplicating the
*whole* body in the two arms does not work, but **hoisting the shared decision
into a small call-free value and duplicating only that** does:

```c
s32 state;
if (c) { state = a->unk0xC; } else { state = a->unk0xC; }   /* identical arms */
if (state == 1) { /* the entire remaining body, calls and all */ }
```

The arms merge (dead `cmpwi`), the load hoists to the merge point, and the big
body is emitted *after* the compare — exactly want's
`cmpwi r26,2 / mr r30,r4 / mr r28,r6 / lwz r0,0xc(r31) / cmpwi r0,1 / bne`.
Got 252B = want 252B, 50/63 words, from a 212B/7-word draft.

Notes:
* Do **not** write `state = (c == 2) ? a->unk0xC : a->unk0xC;` — GCC folds the
  ternary completely and the compare disappears (verified: 9.5%).
* `switch (c) { case 2: state = ...; break; default: state = ...; break; }` and
  `if (c != 2) { state = ...; } else { state = ...; }` behave identically to
  the `if/else` form.
* The duplicated arms are load-bearing even though they are semantically a
  no-op; removing them costs exactly the 1 word + the whole downstream shift.

## 3. Residual on `fn_8009BAEC` (79.4%)

Everything else is exact. What is left is a single register-allocation coin
flip between two values that are both live across the `Mem_Alloc` call:
ngccc gives `count` (arg3) r29 and `base` (count*12) r28; want has count r28 and
base r29. Because the two `mr`s sit right after the dead `cmpwi`, the swap also
shifts that compare one slot later, which is why all 13 mismatches are the same
one-word shift.

The allocation is coupled to the **order of the three bit-guarded size
accumulations**: source order `&1, &2, &4` (want's emit order) always yields
count=r29, and order `&2, &1, &4` yields count=r28 but emits the `andi.`/`cr4`
tests in the wrong order. Ten-plus semantically identical spellings
(`+=` vs `= base +`, if/else vs ternary, decl order, `<<2/<<3`, no `base` local,
inline `arg3*12`, a separate `p` for the alloc result) all produce the *same*
object — 79.4% — so this looks like a genuine single-bit allocator decision I
could not steer from C. Worth a fresh attempt with `cc1 -drtl` diffing of the
want vs the two source orders.
