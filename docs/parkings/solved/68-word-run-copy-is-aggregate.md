# 68 — a run of word moves with all loads hoisted is an AGGREGATE copy, not N assignments

**Status: SOLVED 2026-09-20 — `fn_80050428` 58.6 % → 100 % EXACT, promoted
(DOL byte-identical).**

## The shape

m2c transcribes a 24-byte struct copy as six independent assignments
(`*(s32 *)(d + 0) = *(s32 *)(s + 0); ...`). Retail was compiled from one
aggregate assignment, and sched2 emits it differently: it loads the first source word, derives the source base, loads the third source word at offset 8, derives the destination base, loads the fourth word at offset 0xC and the second word at offset 4 (load order 0, 8, 0xC, 4), then stores in order 0, 4, 8, 0xC, and finishes with the final two words loaded in reverse (0x14 then 0x10) and stored likewise.

Two tells, and either one alone is enough:

1. **All loads are hoisted above all stores.** Six separate C assignments
   compile to `lwz / stw` pairs — `-fno-schedule-insns2` (which the draft was
   carrying) gives one load, one store, one load, one store. No flag combination
   gets from the per-statement form to the hoisted form.
2. **Load order ≠ store order.** The loads come out 0,8,c,4 while the stores
   come out 0,4,8,c — impossible for six statements in any order (statement
   order fixes the load order). It is a block move whose registers were
   allocated by the scheduler.

## The fix

Model the run as one aggregate:

```c
typedef struct { s32 w[6]; } S24;
if (arg1 == 0) {
    *(S24 *)(arg0 + 0x498) = *(S24 *)(arg0 + 0x480);
}
```

100 % at **default flags** — the `// FLAG: -fno-schedule-insns2` the draft was
carrying was only helping the wrong (per-statement) form and must be removed.
`(S24)` vs six statements: 100 % vs 58.6 %.

Note the tail: the last two words are NOT part of the block (the copy is
`0x480..0x494` → `0x498..0x4AC`, six words), and the struct must be exactly
24 bytes so the run boundary matches.

## Related

- [doc 09](09-init-struct-store-order.md) (same-base store runs rotate) and
  [doc 12](12-outparam-store-scheduling.md) (outparam store scheduling) — those
  are about a *broken* order within independent stores; this one is the
  opposite direction (an aggregate the draft had split).
- [doc 37](../37-inline-memset-doloops.md) is the fixed-size *clear* sibling.
