# 80 — a varargs callee's RETURN TYPE moves the last two pre-call instructions

**Found 2026-10-02 on `fn_800723F0` (396B, `src/wip/fn_800723F0.c`): 18.2% → EXACT.**

## The rule

A varargs call's **return type** — not just its argument list — changes the
*pattern* of the call insn, and that pattern changes how the rs6000 scheduler
orders the two or three instructions immediately before the call. Declaring
`void sprintf(char *, const char *, ...)` instead of the real
`int sprintf(char *, const char *, ...)` cost exactly **two words** and put the
body at a stubborn **98.0%** that no source-level restructure could move.

`cc1 -drtl` shows the mechanism precisely. Same source, same flags, only the
prototype's return type differs:

```
;; void sprintf(...)                    ;; int sprintf(...)
(call_insn 56 54 59 (parallel[          (call_insn 56 54 59 (parallel[
        (call (mem:SI ...sprintf) 0)            (set (reg:SI 3 r3)
            (const_int 0 [0x0]))                        (call (mem:SI ...sprintf) 0)
        (use (const_int 4 [0x4]))                            (const_int 0 [0x0]))
        (clobber (scratch:SI))                    (use (const_int 4 [0x4]))
    ])                                          (clobber (scratch:SI))
    (expr_list (use (reg:SI 5 r5)) …     ])     (expr_list (use (reg:SI 5 r5)) …
```

The LUIDs are identical (56 / 59 / 61 …) — only the *pattern* differs: with a
non-void return the call insn is a pseudo-**output** of r3, so r3 stops being a
plain hard reg in the block's dependency graph. The ready-list scheduler then
places the preceding `addi r3, r1, 0x10` (destination address) at the very end
of the pre-call group instead of in the middle:

With the correct integer return type the pre-call group orders the constant high-half load into r4, the move from r6 into r5, the completion of the constant with low half 0x5404, the destination-address computation into r3 from frame offset 0x10, a condition-clear and the branch, while the void-return spelling instead places the destination-address computation second and the register move third with the constant completion last, swapping two words and leaving nothing else in the 396-byte function moved.

2 words differ, nothing else in the 396-byte function moves.

## How to use it

* Whenever a draft is **size-exact and ~98% with a 2-instruction swap inside a
  call's argument-setup group**, before trying loop shapes / statement order /
  barriers, **check every callee's return type against the real prototype**.
  `void sprintf` (18 files under `src/`) and `void OSVReport` (8 files) are the
  known offenders; `int sprintf` already appears in 5. Real prototypes are also
  the *correct* C, so this is a semantics fix, not a codegen poke.
* The effect is **per call site**: `void OSVReport` is correct in
  `fn_800723F0` — flipping it to `int` just moves the same 2-word swap onto the
  `OSVReport` call. Fix one callee at a time and re-measure.
* Corollary for prototypes generally: `extern` declarations are not cosmetic.
  Arity changes the crclr (recipes item 16/27), and the **return type** changes
  the call insn's pattern and therefore scheduling.

## Two other load-bearing shapes from the same function (worth reusing)

1. **A varargs argument the format does not actually use is still real.**
   `fn_800723F0`'s first arm is
   `sprintf(buf, "Failed to allocate %d bytes on %s heap\n", arg0, arg1)`.
   Passing `arg1` is what forces it to get the callee-saved home `r6`
   (`mr r6, r4` in the prologue), which in turn produces the `mr r5, r6` in the
   `else if` arm. Drop it and the function drops to 22%. Same family as
   recipes §4p item "missing call argument".
2. **A variable that is only an operand of *some* of a call's arguments.**
   `MemAvailable(hi) / 1024`, `hi->unk0x8 / 1024` and
   `(hi->unk0xC - hi->unk0x4) / 1024` must be separate `s32` statements
   **before** the `sprintf`, not written inline in the argument list. Inline,
   GCC schedules them *after* the peak/used/frag divisions and the entire
   100-byte loop body reorders. The same "hoist some args into named locals"
   trick is what produces the exact callee-saved set (`r27` loop-invariant
   format address, `r28` global, `r29` name, `r30` cursor, `r31` sub-record) —
   one extra named local (`blocks`) adds a 6th (`r26`) and moves the save area
   from `0x94(r1)` to `0x90(r1)`.
