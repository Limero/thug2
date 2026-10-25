# Issue 11 — Copy-propagation/coalescing in a linked-list index lookup

**Status: STALE (verified 2026-08-23) — the exemplar fn_801AFD88 is MATCHED**
**(promoted in src/).** Kept for the copy-prop/coalesce class analysis.

~~**Status:** PARKED (as of M4.9x; park set is a moving target — re-verify before trusting) (1 function: fn_801AFD88)~~

## The problem

fn_801AFD88 (80 bytes) is a linked-list index lookup with a "deleted marker"
(-1) sentinel. The game's compiler copy-propagates `r9` into `r3` with an
`or. r3,r9,r9` test; GCC coalesces the loop variable differently, producing
a register-role swap that no C shape fixes.

Original (fn_801AFD88): the function loads the list head from offset 0x10 of the object into r9, loads the node's id field at offset 4 into r0, and compares it against the -1 deleted-marker. On a match it nulls the node register and zeroes the loop index in r11. It then copy-propagates the node into the return register with a record-or that also tests it, early-outs on null, compares the index against the incoming index argument with a mid-loop conditional return, advances to the next pointer at offset 0xC on the miss path, re-checks the sentinel on the new node (nulling on -1), increments the index, repeats the copy-and-test into the return register for the loop-back test, and falls through to a null return.

Compiled: GCC keeps the loop node in a single register (coalescing the
`r9 → r3` copy into one register), so the `or. r3,r9,r9` copy-test becomes a
plain test on one register, and the `cmpw r11,r4` / `beqlr` scheduling
shifts. The draft (`src/wip/fn_801AFD88.c`, a goto-loop with `var_r9` /
`var_r3`/`var_r9_2`) is 80B but the register roles and the loop-back branch
placement differ ("copy-prop r9/r3 coalesce" per its header).

## Why it's parked

- The game compiler did NOT coalesce `r9`→`r3` (it kept the copy so the
  `or.` test works on r3), while GCC 2.95.2 does coalesce — so the 
  instruction *sequence* differs by more than register names.
- C source that forces the extra copy (e.g. two distinct pointer variables
  with a dead intermediate) gets optimized away.

## What was tried

- goto-loop and while-loop forms, two-variable node tracking, explicit
  sentinel handling — all coalesce away.

> **Cross-clone note (2026-08, plan Item G):** this is the SAME wall class
> as Sims2DECOMP's copy-prop walls in early-return/merge loop flows
> (their `EAHeap::MallocFromHeap` family) - their 100-budget permuter
> scored 0 hits and they classify it STRUCTURAL, not shape-fixable. The
> non-coalescing copy-test is a register-pressure artifact of the game's
> (distinct, never-installed) build. Do NOT re-grind source shapes here;
> only retry flags per the corrected ladder (defaults first,
> `-fno-schedule-insns` alone, then `-fno-peephole`) if a new NEAR
> crop ever surfaces one.
>
> **crashwoc update (2026-08):**
> the "100-budget permuter" above is Sims2's FLAG permuter - their
> decl-order catalog never permuted declarations on this class, and
> crashwoc (same GCC 2.95.2 generation) automates exactly that
> (`ai_decl_permute.py`: local declaration order as an RA tiebreaker).
> The `or. r3,r9,r9` copy-test coalesce here IS a register-role swap -
> the planned `--decl-permute` mode of `tools/test_wip_drafts.py` is the
> untried legal shape for fn_801AFD88 (declaring `node`/`i`/`d` in
> different orders changes which register survives the coalesce).
> Also worth a `--combos 2` flag-sweep probe (Item C2):
> `-fno-move-all-movables`, `-fno-reduce-all-givs`, `-fno-caller-saves`
> were never tried on this park.
> UPDATE 2026-09-10: the decl-permute half above is retired repo-wide
> (tried 2026-08-23, zero effect on m2c bodies; README item 10)
> and the three flag knobs were proven codegen-inert — do
> neither here; only an unbuilt `--combos 2` automation remains.

## Research directions for an external AI

1. The `or. r3,r9,r9` pattern is a **`-fno-...`-dependent copy-test**: GCC
   emits `or.` for `if (node)` when the value arrives via copy; if coalesced,
   it emits `cmpwi`. The game compiler's non-coalescing suggests a different
   register pressure / `-fexpensive-optimizations` state. Check what source
   shape (e.g. `return` inside loop vs at end) prevents the coalesce.
   > **Day-0 A/B caveat (2026-08, cross-clone):** not a point-version issue —
   > all four installed ProDG versions are codegen-identical (Sims2DECOMP
   > A/B, 609 fns x 4). A "different game SN build" hypothesis (as in docs
   > 01/03) applies here only if it is a distinct, never-installed build.
2. Compare with the *matched* linked-list lookups in the same game (family
   of ~19 promoted in M4.4x, e.g. 8000E638, 800A1BB4): those were fixed with
   `while(…) return 0` restructures. Diff their asm against 801AFD88 to find
   the structural difference (the -1 sentinel + `beqlr` mid-loop return).
3. Try the canonical form `for (i = 0, node = head; node; i++, node =
   node->next) { if (i == idx) return node; } return 0;` with the sentinel
   handled via a helper getter.

## Where to look

- Draft: `src/wip/fn_801AFD88.c`.
- Matched references: AGENTS.md §4m pattern 6 (linked-list lookup family,
   "redundant trailing return block" fix).
