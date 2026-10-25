# Issue 09 — Init-struct store order (GCC hoists a store out of source order)

**Status: STALE (verified 2026-08-23) — BOTH exemplars are MATCHED now
(fn_801C21BC and fn_80138F10 are promoted in src/; the volatile-store trick in
the M8.3x section below likely cracked them without this doc being updated).
Kept for the scheduling-class analysis.**

~~**Status:** PARKED (as of M4.9x; park set is a moving target — re-verify before trusting) (1 function: fn_801C21BC)~~

## The problem

fn_801C21BC (152 bytes) initializes a doubly-linked-list object with two
sub-objects at offsets +0x1C and +0x34. The game's compiler emits the stores
in a specific order; GCC 2.95.2 **hoists the `stw r11, 0x10(r11)` self-link
store before the `0xC` store** no matter the source order.

Original (excerpt, fn_801C21BC): the function opens with a 0x10-byte stack frame, saves the link register and registers r30 onward, and homes the incoming object pointer in r30. It then calls an init helper, materialises two rodata label addresses into r9 and r10, derives a sub-object pointer in r11 as the object plus 0x1C, stores the first label to offset 0x18 of the object, zeroes r7 and sets r6 to -1, stores the second label to offset 0x14 of the sub-object, and continues with the remaining initialisation stores (minus one to offset 4, zero to offset 8, self-links to offsets 0xC and 0x10, and so on).

Compiled: GCC schedules `stw r11,0x10(r11)` (the `p->0x10 = p` self-link)
**before** `stw r11,0xC(r11)` (the `p->0xC = p` self-link), and also moves
some stores relative to the address computations. A brute-force over **70
source statement orderings** achieved only 12 diffs at best — the compiler
re-orders independent stores to the same base pointer in a way no source
order forces.

## Why it's parked

- The function is a struct/object initializer with many independent stores
  to the same object (and two embedded list-head sub-structs).
- GCC 2.95.2's scheduler reorders same-base stores; the game compiler's
  order differs, and the 70-combination brute force shows the space is
  exhausted without a hit.
- Store-order swaps *are* usually fixable by swapping C statements (the
  project's most common fix, see AGENTS.md §4m pattern 9), but this specific
  pattern (self-referential `p->x = p` stores interleaved with constant
  stores and `li` loads) resists it.

## What was tried

- 70 source statement orderings of the stores.
- Pointer locals (`temp_r11 = arg0 + 0x1C`) vs direct field stores.
- The best result was 12 diff words — stuck.

> **Cross-clone note (2026-08, plan Items E/G):** Sims2DECOMP recorded the
> same wall class - mutually-exclusive store-order/hoist couplings in
> init sequences (their 100-budget permuter: 0 hits) - and classifies it
> structural. Their two legal source-side tools for it: volatile-store
> pinning (`volatile` on the specific moved store - forces the store to
> stay in source order) and the uniform `volatile int` ctor variant.
> Retry ONLY these two before re-grinding statement orders (the 70-form
> brute force is exhausted). Their `-fno-schedule-insns2`-removal fix
> does NOT apply (THUG2 default has no insns2; and the versions listed
> here already include the flag families).
>
> **crashwoc update (2026-08):** the
> planned `--flag-sweep --combos 2` mode (pairwise flag combinations
> with auto-score) is the untried lever here - single flags and the
> corrected ladder were tested, but PAIRWISE combos never were (e.g.
> `-fno-schedule-insns` + `-fno-schedule-insns2` on 80138F10).
> UPDATE 2026-09-10: the `-fno-move-all-movables`/`-fno-reduce-all-givs`/
> `-fno-caller-saves` half of that probe was proven codegen-inert
> repo-wide, so only unbuilt `--combos 2` automation remains (harness
> never built; spec: `~/ai/crashwoc/tools/ai_flag_sweep.py`). Run it
> before re-grinding source orders;
> also re-check fn_801C21BC and 80138F10 against the parked set (park
> is a moving target).

## Research directions for an external AI

1. The pattern `p->C = p; p->10 = p` (self-links) combined with `p->4 = -1;
   p->8 = 0` suggests an embedded doubly-linked-list head. The game compiler
   ordered stores by *memory offset in descending/ascending* order while GCC
   reorders by dependency/scheduling. Check GCC 2.95.2's `dbr_sched`/
   `sched.c` priority rules for stores to the same base register.
2. Compare against *matched* store-order functions in the same game: many
   were fixed by writing stores in the exact DOL order (e.g. fn_8009C7F4,
   fn_800034A0 ascending, the zero-store families). Determine what is
   structurally different here (two base pointers r11/r9 interleaved with
   `lis`/`addi` address materialization may confuse the scheduler).
3. Try splitting the two sub-object inits into two helper functions called
   in sequence — GCC may then emit each init's stores contiguously.

## Where to look

- Draft: `src/wip/fn_801C21BC.c` (has the full "PARKED" note).
- Matched store-order references: AGENTS.md §4m pattern 9, §4e 'g' family
  (out-of-order store offsets matched by writing stores in DOL order).
## 80138F10 (116B, 3 diffs) — cmpwi hoist over stores

WANT keeps all 4 init stores (a byte store of r0 to offset 0x2309, a halfword store of r9 to 0x230A, a byte store of r11 to 0x2308, and a word store of r30 to 0x230C) BEFORE the compare-against-zero test on r30; ngccc 3.9.3 hoists the compare-word-immediate between the 0x2308 byte store and the 0x230C word store regardless of source
statement order (v0-v13: 8 structural variants + -fschedule-insns2 /
-fno-schedule-insns / -fno-sched-spec / -mcpu=7400/7410/603/604 all
reproduce the hoist). The 3 diffs are exactly the cmpwi+2-store rotation.
Doc-09/12 family (store scheduling), not arg-setup.

## M8.3x: volatile-store trick solves pure-init functions (fn_800C74E8)

**Breakthrough (2026-08-20):** `volatile` on struct-member cast-stores pins
the GCC store order to the source statement order, solving the
independent-zero-store scheduling coin-flip that was the sole remaining
diff in pure-init functions.

**Example — fn_800C74E8 (36B, now EXACT):**

The WANT disasm stores 5 fields (4 zero, 1 float) in source order: it loads a float-constant address with a load-immediate-shifted, zeroes a register, loads the float constant, then stores zero to field A at offset 0x334, the float to field B at 0x324, and zero to fields C, D and E at offsets 0x32C, 0x330 and 0x328 respectively.

Without `volatile`, GCC freely reorders independent stores (stw 0x328
before the lfs+stfs, giving 8/9 diffs = 11%). With `volatile` on all
cast-stores, the compiler emits in source order → 0 diffs.

**Working source:**
```c
void fn_800C74E8(void *arg0) {
    float f = (f32) *(f32 *)&lbl_80299194;
    *(volatile s32 *)((char *)arg0 + 0x334) = 0;
    *(volatile f32 *)((char *)arg0 + 0x324) = f;
    *(volatile s32 *)((char *)arg0 + 0x32C) = 0;
    *(volatile s32 *)((char *)arg0 + 0x330) = 0;
    *(volatile s32 *)((char *)arg0 + 0x328) = 0;
}
```

**Scope:** this trick only helps when the ENTIRE diff is store-scheduling.
Functions with loop-control/computation ordering diffs (like 800C4734,
800C48A0, 800C2284) remain parked — volatile doesn't affect those.
Also does NOT fix the80138F10 cmpwi-hoist (volatile on the stores
PREVENTS the hoist in some compilers but not ngccc 2.95 — tested).

## 2026-09-13 — the search tool was half the problem; 3 more store-order promotions

**The `--combos 2` question is answered: it is a dead axis.** The "crashwoc
update" note above asked for pairwise flag combinations as the untried lever.
Two exhaustive sweeps closed it:

- all 1- and 2-subsets of a 13-flag vocabulary (`-fno-schedule-insns{,2}`,
  `-fno-sched-spec`, `-fno-sched-interblock`, `-fno-gcse`,
  `-fno-expensive-optimizations`, `-fno-strength-reduce`, `-fno-function-cse`,
  `-fno-delayed-branch`, `-fno-inline`, `-fomit-frame-pointer`, `-O1`, `-O3`)
  over every non-promoted draft >= 70% (353 drafts, 91 combos): **0 EXACT**, and
  **not one 2-flag combination beat its best single flag** — the 8 improvements
  found were all single flags;
- all 15 non-empty subsets of the four scheduling flags over every draft >= 85%
  (234 drafts): **0 EXACT**, 1 improvement, single flag.

~2,400 draft-combination evaluations, zero pairs. Combined with the earlier
finding that `-fno-move-all-movables` / `-fno-reduce-all-givs` /
`-fno-caller-saves` are codegen-inert repo-wide, flag space is closed; go back
to source orders.

**`tools/store_order_search.py` was scoring drafts under the wrong flags.**
It stripped every `//` line (including `// FLAG:`) and called
`test_one(addr, body)` with **no** `extra_flags`, so a draft carrying
`-mps-float` / `-fno-schedule-insns` / `-fno-gcse` was compared against a
different program. `--write` then persisted that body — on `fn_8020CAA4` it
"reordered" a 98.7% draft down to 22.2% and wrote it back. Both it and
`tools/stmt_perm_search.py` now mirror `promote_wip.draft_flags()` (validated
flag tokens + the `__ps_t`/`__builtin_ps_*` -> `-mps-float` rule).

**Three more of the family are EXACT and promoted** (DOL byte-identical
`ff6faeb0...`, one promote at a time):

| fn | size | fix |
|---|---|---|
| `fn_801AEE7C` | 152B | reverse one contiguous store/assignment run |
| `fn_80098B7C` | 160B | ascending reorder of one run |
| `fn_800F1448` | 160B | ascending reorder of one run |

The post-fix sweep over 585 drafts >= 50% also improved 48 more, best:
`fn_800BD96C` 97.8%, `fn_80153D54` 95.3%, `fn_800E4EB8` 92.9%,
`fn_80200B40` 91.7%. A full-permutation search (all permutations of runs of
<= 5 statements, `/tmp/perm_run.py`) added 20 more improvements but **no new
EXACT** — non-monotonic orderings are reachable and do help
(`fn_80221930` 97.6%, `fn_8018CC18` 97.3%, `fn_80227D64` 96.5%), they just do
not close the last 2-6 words.

## ADDENDUM 2026-09-17 — the same-base store run is emitted **rotated right by one**, and that IS forceable

The doc's headline verdict ("GCC re-orders independent stores to the same base
pointer in a way no source order forces"; the `fn_801C21BC` 70-ordering brute
force) is **too strong**. The reorder is not arbitrary: over a contiguous run of
independent stores to the *same base*, ngccc issues the run's **last store
first** and then the rest in written order — i.e. the emitted sequence is the
written sequence **rotated right by one**. Writing the run **rotated left by
one** therefore makes the emitted order match want exactly.

Evidence — `fn_800F3598` (120B), 73.33% → 90% → **100% EXACT, promoted**. Two
runs in the same function, both obeying the rule: the first run emits offsets 8, 0xC, 0x10 through base r9 from a written order of 0xC, 0x10, 8, and the second run emits offsets 0x28, 0x34, 8, 0x20, 0x24 through base r30 from a written order of 0x34, 8, 0x20, 0x24, 0x28.

The second run is decisive: the naive "write it in DOL order" body scored 73.33%
and the *only* change to reach 100% was that rotation (`rot_left(want)`); a
partial rotation (one run only) gives 80–83%, so both runs are independent.

Mechanics, from the draft's own A/B (all measured, same body):

| written order          | emitted                        | score |
|---|---|---|
| `8, 0xc, 0x10` / `0x28,0x34,8,0x20,0x24` (DOL order) | rotated right ×2 | 73.33 |
| run 1 rotated only                                    |                | 83.33 |
| run 2 rotated only                                    |                | 80.00 |
| both rotated (= `rot_left(want)`)                     | **= want**     | **100.00** |

Flag axis re-closed on this draft: `-fno-schedule-insns` 50%, `-fno-schedule-insns2`
63.3%, both 56.7%, `-fno-sched-spec` / `-fno-sched-interblock` / `-fno-gcse` /
`-fno-cse-follow-jumps` / `-fno-cse-skip-blocks` / `-fno-rerun-cse-after-loop` /
`-fno-delayed-branch` / `-fno-peephole` all 73.33% (no change);
`-fno-tree-dse`, `-fno-ipa-reference`, `-fno-peephole2` fail to compile. **Source
rotation is the only lever that works** — no flag reproduces want's order.

Recipe: when a near-miss differs from want *only* by a permutation **within a run
of stores to one base**, do not brute-force permutations and do not reach for
`volatile` (which pins source order, i.e. the *wrong* order here). Rotate the
written run **left by one** and re-score; if the run is the whole residual the
draft goes EXACT. Run boundaries are the C statement groups (the two runs above
split at the change of base register).

Scope caveat: verified on one function (2/2 runs). Treat it as the first thing to
try, not as a law — and if a member resists, check whether the run is broken by
an intervening non-store (address materialisation, a call, a trailing `mr`) —
`fn_800F45A4` (doc 55/60) shows a trailing return-value `mr` *splitting* two
stores, in which case the "run" is the statements on each side of the `mr`.

## Addendum 2026-09-19 (f): same rotation across DIFFERENT bases/globals

`fn_8024C5D4` (20B, PROMOTED byte-exact) shows the rotation is a property of the
store *list*, not of "one base": the run is three stores to three **distinct
sdata globals**

```c
void fn_8024C5D4(s32 arg0) {   /* FLAG: -msdata=eabi -G4 */
    lbl_803CA33C = arg0;
    lbl_803CA330 = 0;          /* written LAST first */
    lbl_803CA334 = 0;
}
```

Retail emits `33C, 334, 330`; the draft as originally written (`33C, 334, 330`)
emitted `33C, 330, 334` (40%). Writing the two zero stores **swapped** reproduces
retail exactly (the address `addi`-vs-indexed lever was a red herring here; the
per-object `-msdata=eabi -G4` route was the other half — see doc 43).

So the diagnostic generalises: a near-miss whose diff is *only* a permutation of
independent 4-byte stores (same base or not) is worth exactly one rotation of the
source statement run before any other hypothesis.
