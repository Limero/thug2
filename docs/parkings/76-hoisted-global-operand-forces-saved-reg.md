# doc 76 — a global operand of a `* callee()` expression is sunk by `preexpand_calls`; hoist it into a local to force a saved GPR (and with it the whole frame)

**Status:** NEW LEVER, found 2026-10-02. First member `fn_800142FC`
(0x800142FC, 400 B): **9.5% DIFF → 87.0% NEAR**, and the frame/stack-temp
layout went from "wrong at every offset" to byte-exact. Read this before
grinding a park whose residual is *only* `stwu/stfd/stmw/lwz r0` frame
offsets plus the `0x18/0x1c` int→float temp-pair offsets.

## The shape

A global scalar is read as one operand of an arithmetic expression whose
*other* operand chain ends in a call:

```c
*(f32 *)B + 4 = *(f32 *)B / (f32)g_divisor * fn_800144D4();
```

want: the global divisor page high half -0x7fd1 is loaded into r9 with the divisor word loaded from offset -0x194 into callee-saved r30 before the call to fn_800144d4, alongside spill stores, and after the call the divisor is consumed with a sign-flip xor, so the value must survive the call in a callee-saved register.

ngccc with the expression inlined emits the load after the call to fn_800144d4, materializing a zero page base into r11 and loading the divisor word from offset 0 into r0, a caller-saved register free at that point, so the value never needs a saved register.

Why: GCC 2.95's `expand_expr` calls `preexpand_calls (exp)` for the
arithmetic node before expanding its operands, which hoists every call in
the expression to the front. The scheduler cannot move a load back across a
call, so the RTL order is fixed at expand time — the sink is *not* a
scheduling artifact and no flag moves it.

## The lever (pure C, one extra local)

Read the global in its own statement immediately before the consuming store:

```c
    n = g_divisor;                                             /* NEW */
    *(f32 *)B + 4 = *(f32 *)B / (f32)n * fn_800144D4();
```

`n` is now live across the call, so it is homed in a callee-saved GPR
(`r30` here) and the load stays before the call — exactly the want shape.
Cost: one named local. Do NOT try to get the same effect by splitting the
*arithmetic* into two statements (`t = a / b; *p = t * f();`) — that births
an f32 stack temp and cost 14 points on `fn_800142FC` (41% vs 55%).

## Why one saved register is worth 46 points here

The number of saved GPRs sets the size of the register save area, and every
stack offset in the function follows from it. With the divisor hoisted,
`fn_800142FC` saves 5 GPRs and the frame snaps into place:

| | want | before the hoist | after |
|---|---|---|---|
| `stwu` | -0x40 | -0x30 | **-0x40** |
| `stfd f31` | 0x38 | 0x28 | **0x38** |
| `stmw` | r27, 0x24 | r28, 0x18 | **r27, 0x24** |
| `stw r0` (LR) | 0x44 | 0x34 | **0x44** |
| int→float temp pair | 0x18/0x1c | 0x10/0x14 | **0x18/0x1c** |

18 of the 100 words are prologue/epilogue + the repeated `stw/lfd ...,0x18(r1)`
of the temp pair, so a single saved register is worth ~18% there and the
temp-pair offsets are worth another ~14 (they are NOT relocation-masked).

## Corollary — issue-01 dummy counts are only valid at a fixed regalloc

AGENTS-recipes §4h item 63 says dummies = (want_frame − native_frame)/8.
That is only true while the saved-register count is fixed. Measured on
`fn_800142FC` (want frame 0x40, int→float temp pair at 0x18/0x1c):

* 2 saved GPRs → 3–4 `volatile double` dummies reach frame 0x40, but the
  temp pair lands at 0x20/0x24 or 0x28/0x2c (wrong);
* 1 dummy + 5 saved GPRs → frame 0x40 **and** the pair at 0x18/0x1c.

The 4-byte slot that sits between the temp pair and the register save area
in the want only materialises when 5 GPRs are saved — with a smaller save
area ngccc puts the pair flush under it. **Re-measure the dummy count after
any change that alters the saved-register count**, not before.

Measurement recipe (no new tool needed): compile the body, then read off
`stwu` frame, `stfd f<fsave>`, `stmw` base+count, `stw r0` (LR), and the
first `stw rX, 0xNN(r1)` immediately after the loop's `xoris` (= the
temp-pair low word). If the frame is right but the pair is not, you are on
the regalloc axis, not the dummy axis.

## Bonus lever from the same function: split the address space

The same body needed the three float fields addressed through the **symbol**
while every int/timestamp field went through a **pointer** local:

```c
    *(f32  *)lbl_803142B8              = ...;   /* HI16 reload  -> split form */
    *(f64  *)((char *)lbl_803142B8 + 8) = ...;   /* address reg r27 + disp 8  */
    *(f32  *)((char *)lbl_803142B8 + 4) = ...;   /* address reg r27 + disp 4  */
```

All-pointer gives ONE address register for every access (the split
HI16/LO16 form never appears); all-symbol gives a fresh page `lis` per
access. The want uses all three forms at once, and only this split
reproduces it. Same class as doc 73 (HI16 reload colouring) but on the
*address* pseudos rather than the constant anchors — and this one is
fixable from C.

## Residual on the first member

13 words, both pure register-ROLE coin flips that survived 13 source
variants (operand order, explicit temporaries, `(s32)` truncation of the
64-bit delta, `u32` index, `p[0]+p++`, pointer bump in the loop tail,
`p=` in the for-header, countdown/while loop shapes, swapped declaration
order): (a) the two low halves of the delta want `cur.lo` in r11 and
`prev.lo` in r0, got is reversed; (b) the loop induction pair wants the
walking pointer in r9 and `v` in r11, got swaps them. If a future agent
cracks either, the natural next lever is the reload-pin technique of
doc 75 / recipes §7e-2, not more source shapes.
