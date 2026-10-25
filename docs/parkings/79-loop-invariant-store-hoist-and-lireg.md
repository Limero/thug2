# 79 — ngccc relocates a loop-invariant stack-slot store out of the loop; re-derive the pointer INSIDE the body to keep it

**Date:** 2026-10-02 · **Found on:** `fn_80009D88` (308 B, 23.4% → **74.0% NEAR**, object
now size-exact) · **Applies to:** any want whose loop body *starts* with one or more
stores to a stack local and whose back edge targets that store (the classic C++-ish
"construct / destruct stamp the base-class vtable every iteration" pattern — the whole
`0x80009B04–0x8000A0A8` container family: `fn_80009CF4`, `fn_80009EBC`, `fn_80009F64`).

## The signature

The signature is that both builds contain the same two stores but place one differently: with a single-pointer spelling the build hoists one invariant store to the preheader and keeps only the second stamp in the loop with the first stamp reappearing at the latch, while retail keeps both stamps at the loop top starting at the store that the back edge targets, and ends the loop by repeating the first stamp before the non-zero branch.

Both want and got contain **the same two stores**; ngccc's loop pass simply moves one
of them out of the loop body (into the preheader, or to the loop latch) because its
address and value are loop-invariant and the local's address does not escape. Which of
the pair it moves depends on the loop form (`do/while` moved stamp 1, a `goto` loop
moved stamp 2, `for(;;)+break` moved stamp 1) — so it looks like a statement-order
problem and is not.

## The fix (pure C, no asm, no flag)

Re-derive the object pointer **inside** the loop body:

```c
for (;;) {
    ip = &s;                 /* <-- the lever */
    ip->vtable = lbl_8028FF40;
    ip->next = h;
    ...
}
```

The loop pass then creates a loop-invariant register for `&s`, emits the copy
**`mr r25, r29` in the preheader** (exactly want's instruction), and leaves **both**
stores in the loop body. This single change moved `fn_80009D88` 16.9% → 32.5% *and*
shifted the whole register allocation one slot down (`stmw r24` instead of `stmw r25`,
`li r24,0` for the loop-invariant zero, `a`→r30 / `sp`→r29), because want's extra live
loop-invariant register is what makes the frame 0x38 with 8 saved GPRs.

A separate local pointer assigned **before** the loop (`ip = &s;` hoisted out) is
folded by local_cse back onto `sp` and changes nothing — the copy must be taken from
*inside* the body.

## Dead ends measured on the same body (do not re-sweep these)

| Lever | Result |
|---|---|
| `volatile` on the stamp field | store still hoisted |
| `volatile` on the whole local object | store still hoisted |
| storing `&s` into a local array to make the address "escape" | store still hoisted |
| `-fno-gcse`, `-fcse-follow-jumps`, `-fcse-skip-blocks`, `-fno-thread-jumps`, `-fno-rerun-loop-opt`, `-fno-rerun-cse-after-loop`, `-fno-expensive-optimizations`, `-fno-regmove`, `-fno-peephole`, `-fno-branch-count-reg` | byte-neutral |
| `-fno-sched-interblock`, `-fno-schedule-insns2`, `-fno-sched-spec`, `-fno-defer-pop` | byte-neutral |
| `ip = &s;` hoisted before the loop | folded away, byte-neutral |

**ProDG `ngccc` moves a `volatile` stack-slot store out of a loop.** That is the
load-bearing negative here: `volatile` is normally the way to pin a store, and in this
compiler family it does not work for a local's own slot. (`volatile` *does* still work
for doc 78's slot-order race, where the point is that the frame MEM exists at all.)

## Companion lever that also mattered here (already recipes 28 / 118)

The loop-invariant zero used by a store inside the loop (`a->dirty = 0`) lands in the
preheader in the position want wants only if the source materializes it as a named
local assigned **before** the preheader's address computes:

```c
sp = &s;
z = 0;                        /* li r24,0 goes HERE */
h = (void *)((char *)a + 8);  /* addi r28, r30, 8 after it */
```

32.5% → 35.1% here.

## Residual of `fn_80009D88` (20 words, honest)

1. The **first** list-walk advance in the want is *unthreaded*:
   `cmpwi r9,0 | bne L | li r9,0 | b M | L: lwz r9,4(r9)` — the else-arm's `li` was not
   sunk into the test block, and the load's destination pseudo reused the tested
   register. Every C spelling (ternary, if/else, arms swapped, init-then-if, explicit
   `goto`+label, temp seeded from the tested pointer) produces ngccc's sunk
   `cmpwi | li r0,0 | beq | lwz r0,4(r9)` with the load destination in r0. The **same**
   advance inside the inner loop already matches want's sunk 4-word shape, so only this
   one site is unthreaded in the original.
2. The inner loop wants three distinct temps (`r9` = `sp->next`, `r10` = element,
   `r11` = folded node); got coalesces the `sp->next` temp with the folded node and puts
   the element in `r11`. Splitting them in C (two variables) makes GCC emit a redundant
   `lwz r9,0(r9)` and scores worse. The untried lever is a zero-code `"+r"` barrier on
   the walk pointer.