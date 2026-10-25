# 84 — A loop-exit ("fail") block placed INSIDE the loop body

**Status: SOLVED (2026-10-03) — `fn_8011E0E4` (`SetTrackForbiddenStatus`,
468B) went NEAR 80.3% → EXACT, no flags, no dummies, `.text` length-exact at
0x1D4.**

The general lesson: **`reorder_basic_block` can only SINK a block, it can
never hoist it into a loop.** So a loop-exit block that retail keeps *between*
the last test and the latch is unreproducible until its **source position is
inside the loop body** — then the fall-through edge out of the last test
prevents the sinking entirely.

## The shape

Want keeps the fail block inside the loop body between the last test and the latch: the first test branches forward to a fail label, the second test branches to the latch to skip the fail block, the fail store to offset 0xCA8 sits in the body followed by a branch to the epilogue, and the latch (counter increment, compare, loop-back branch) follows. Every return, out-of-line goto, continue, volatile-store and empty-asm-padding spelling of the fail arm (20-plus forms, all length-exact) instead sank the fail block out of the loop, wedging the shared store-plus-epilogue-branch between two unrelated else halves with both tests branching to that sunk address.

## The fix — inverted-condition `goto` INSIDE the loop body

```c
do {
    if (bad1(i)) goto fail;
    if (!bad2(i - 64)) goto next;   /* false -> jump over the fail block */
fail:
    base->unk0xCA8 = res;
    return;
next:
    i = i + 1;
} while (i < cnt);
```

Source block order is `[t1][t2][fail][incr]`, so:

- the fail block is never a sinking candidate (nothing reorders it out of the
  loop), and
- `next:` is the body's tail block, so `i++` merges with the `do-while`
  condition into ONE latch block (`addi/cmpw/blt`) — no extra branch — and
- the 2nd test becomes `beq <latch>` (skipping the fall-through fail block)
  while the 1st keeps a forward `bne`.

That is byte-for-byte retail, including every REL14 target.

## Related

- Supersedes the "shared fail block is always sinkable" reading of
  `docs/parkings/15` + AGENTS 6ep/6bz/6dv: sinkability is conditional on the
  block's source position being outside the loop.
- The other lever this function needed (two *address webs* for the loop count
  so ngccc keeps both the entry-guard load and the latch operand) is
  documented in the draft header.