# Issue 16 — Branchy-boolean shadow allocation: var_r3 in r3 vs r31 (two chained booleans)

**Status: SOLVED (2026-08-23) — fn_8009CF2C byte-exact at 100.0% masked match.**
The missing shape: write each shadow constant assignment (`var_r3 = K;`) BEFORE
the positive-condition test `if (temp == 0) goto L;` with the call result in a
NAMED temp — the scheduler sinks the `li` between `cmpwi` and `beq` exactly as
WANT shows, and because `var_r3` is reassigned after every call it is never
live across one, so GCC keeps it in r3 (no saved-reg home). Every prior attempt
used inverted conditions (`temp != 0`, §6b form) or a pre-loop init that made
var_r3 live across calls.

## Solution (2026-08-23, 100.0%, plain flags)

```c
extern s32 fn_8009CFA0(void);
extern s32 fn_8013E2BC(void);
s32 fn_8009CF2C(void *arg0) {
    s32 var_r3;
    s32 temp;
    temp = fn_8009CFA0();
    var_r3 = 0;
    if (temp == 0) goto epi;
    var_r3 = *(s32 *)((char *)arg0 + 8);
    if (var_r3 == 0) goto check_c;
    temp = fn_8013E2BC();
    var_r3 = 1;
    if (temp == 0) goto epi;
check_c:
    var_r3 = *(s32 *)((char *)arg0 + 0xC);
    if (var_r3 == 0) goto done;
    temp = fn_8013E2BC();
    var_r3 = 1;
    if (temp == 0) goto epi;
done:
    var_r3 = 0;
epi:
    return var_r3;
}
```

Why it works (generalizable recipe — "shadow-li via pre-test assignment"):
- WANT's `cmpwi rX,0; li rY,K; beq L` is produced by source order
  `temp = call(); var = K; if (temp == 0) goto L;` — the assignment is written
  before the test and the scheduler fills the compare's shadow slot with it.
  The branch direction must be POSITIVE (== 0), matching WANT's beq.
- Field loads into r3 (`lwz r3,8(r31)` words 09/16) come free from
  `var_r3 = *(field); if (var_r3 == 0) ...` — the return variable IS the test
  operand, so no scratch register appears.
- The direct-call form (`if (fn() == 0)` without named temp) FAILS (33%) — the
  named temp is what lets the assignment sit between the call and the test.

---

# ORIGINAL ANALYSIS (historical)

**Status:** PARKED (as of M6.59; park set is a moving target — re-verify before trusting) (1 function: fn_8009CF2C)

## The problem

`fn_8009CF2C` (29 words, 116B, range 0x8009CF2C–0x8009CFA0) is a small wrapper
around two back-to-back boolean checks. Its WANT (the game's original bytes)
materializes the return boolean **in r3 with the `li` in branch shadows**, using
the "branchy boolean" idiom (see AGENTS.md §6b recipe 1: `cmpwi; li r3,1; beq L;
li r3,0` — as opposed to ngccc's arithmetic `subfic/adde` fold). The wrapper
calls a no-arg callee `fn_8013E2BC` **twice**, and each call is immediately
followed by `cmpwi r3,0; li r3,1; beq <epilogue>` — i.e. the boolean is
computed from the callee's return value in r3 itself, so the whole function
never needs a callee-saved register for the boolean.

No C source shape tried reproduces both halves of this at once:

- The m2c `||`-chain form reproduces the **branch shapes** (the `beq` targets
  line up) but ngccc allocates the boolean variable to **r31** (prologue gains
  `stw r31` / `stmw`), and the return path becomes `mr r3, r31`.
- The goto-based forms (which force the boolean into r3, per the §6b recipe)
  fix the allocation but **invert the middle branches** — ngccc reorders the
  `beq` targets, so the branch offsets no longer match.

The two requirements (right branch targets AND r3 allocation) never co-occur in
any of the ~16 structural variants tested (M6.59).

## The WANT (original bytes, described)

The function uses a 16-byte GPR-only frame with no FPR quirk. It saves r31 (used as the arg0 base, not for the boolean) and the link register, homes arg0 in r31, then calls the first helper. The return value is compared against zero with the zero constant assigned into r3 in the branch shadow after the call, branching to the epilogue when the first result is zero. The non-zero path loads offset 8 of arg0 into r3, compares it against zero, and branches to the check_c block on zero. There it calls the second helper a first time, again comparing the result against zero with the one constant assigned into r3 in the shadow, branching to the epilogue when zero. The check_c block loads offset 0xC of arg0 into r3, compares against zero, and branches to the done block on zero. The fall-through path calls the second helper a second time, again assigning the one constant into r3 in the shadow after the compare and branching to the epilogue on zero. The done block zeroes r3 and falls through into the shared epilogue, which restores the link register and r31, tears down the 0x10 frame, and returns.

Key structural facts an external researcher should note:

- The boolean is **never spilled and never lives in a callee-saved register** —
  it is computed in r3 immediately before each branch, and the epilogue reads
  whatever r3 holds. That is the whole difficulty: `var_r3 = 1` (words 14/21)
  sits **between** the `cmpwi` and the `beq` — in the branch shadow — and the
  `var_r3 = 0` init (word 7) sits in the shadow after the **first call**.
- `li r3,0` (word 23, the `done` block) is reached by fall-through from word 22
  (C2 != 0) AND by the `beq` at word 18 (arg0->0xC == 0). So `done` is a shared
  `return 0` tail.
- Branch targets: `0x8009cf6c` = word 16 (check_c), `0x8009cf88` = word 23
  (done), `0x8009cf8c` = word 24 (epilogue). All three land in the same function
  (no cross-function tail merge, issue 08 N/A).
- Semantics (from the bytes — the source logic may look odd, it is a game):
  - `A == 0` → return 0
  - `arg0->0x8 != 0 && B == 0` → return 1, then fall into check_c
  - check_c: `arg0->0xC == 0` → return 0; `C2 == 0` → return 1; else return 0.

## The draft (best so far, 19/29 — `src/wip/fn_8009CF2C.c`, M6.59)

```c
s32 fn_8009CFA0(void);
s32 fn_8013E2BC(void);
s32 fn_8009CF2C(void *arg0) {
    s32 temp_r3;
    s32 var_r3;

    var_r3 = 0;
    if (fn_8009CFA0() != 0) {
        if (*(s32 *)((char *)arg0 + (s32)0x8) == 0) {
            goto check_c;
        }
        temp_r3 = fn_8013E2BC();
        var_r3 = 1;
        if (temp_r3 != 0) {
            goto check_c;
        }
        return var_r3;
    }
    goto done;
check_c:
    if (*(s32 *)((char *)arg0 + (s32)0xC) != 0) {
        temp_r3 = fn_8013E2BC();
        var_r3 = 1;
        if (temp_r3 != 0) {
            goto done;
        }
        return var_r3;
    }
done:
    var_r3 = 0;
    return var_r3;
}
```

## What was tried (all in M6.59, compile-and-compare vs WANT)

Compiler: ProDG 3.9.3 `ngccc.exe` (GCC 2.95.2 derivative), `-O2 -G0 -mcpu=750
-fno-common`, standalone via `tools/gen_leaves.py compile_fn` (branch targets
reloc-masked, so only branch SHAPE — which direction/condition — matters, not
the absolute offsets).

| Form | Result |
|---|---|
| m2c `||` chain (`var_r3=0; if (A!=0 && (arg0->8==0 \|\| (B=fn_8013E2BC())!=0) && ...)`) | right branch shapes, boolean alloc'd to r31 (`stw r31` prologue, `mr r3,r31` returns) |
| goto-block_4 recipe (AGENTS.md §6b item 1: `temp = call(); var_r3 = 1; if (temp != 0) goto block_4; } else { block_4: var_r3 = 0; }`) | r3 allocation correct, middle branches inverted |
| Early-return / nested-if restructures (ret_1 / ret_0 / check_c block orders) | all converge to the same 19/29 with the same 10-word diff |
| `-fno-schedule-insns2` / scheduling flag variants via compile_fn extra_flags | no effect |
| Temp comma-clause forms, declaration-init ordering variants | regressions (38–45/58) or same 19/29 |
| goto-heavy mirror of WANT's exact block order (ret_0 / ret_1 / check_c) | GCC reorders the ret blocks, different layout |

The persistent diff signature: words 07/14/21/23 (the `li r3,{0,1}` shadow
constants) and the two middle `beq` directions (words 15/22) disagree — exactly
the "right branches XOR right register" conflict.

> **Cross-clone note (2026-08, plan Items E/G):** Sims2DECOMP's equivalent
> wall (their ENodeList::GetSizeRev 2-step bool materializer,
> `li rX,1; bne; li rX,0` shadow-allocation across chained booleans)
> ALSO stayed uncracked there - confirms this is a structural
> allocator limit, not a missing shape. Their catalog's closest legal
> tool (volatile-store pinning / var-declaration-order register
> forcing) targets SINGLE-boolean allocation; the chained shadow case
> resisted both. Re-try ONLY when a new sibling with the same shape
> surfaces in the NEAR crop; otherwise keep the retry hints below
> as-is.
>
> **crashwoc update (2026-08):** the
> manual "declaration-init ordering variants" above were a handful of
> hand-chosen orders; crashwoc's `ai_decl_permute.py` automates the
> EXHAUSTIVE top-level-decl permutation (GCC 2.95.x declaration-order
> RA tiebreaker, permute cap 20-100 covering the full decl set, not
> hand-picked swaps). UPDATE 2026-09-10: superseded — this function
> matched without it (see doc header), and decl-permute was tried
> 2026-08-23 and retired repo-wide (zero effect on m2c bodies; README
> item 10). Do not build `--decl-permute` for this class.

## Retry hints (not yet exhausted)

1. **Extern-symbol / global field loads.** The draft loads `arg0->0x8` /
   `arg0->0xC` via `(char *)arg0 + 8` casts. The WANT's `lwz r3, 8(r31)` form
   suggests the source may have been `arg0->field8` struct members (register
   + displacement, no `addi`). Restructuring the loads as typed struct field
   reads could change ngccc's scheduling enough to let the branch shape match
   — this is the untested lead from AGENTS.md §6b ("likely needs the lbl/global
   form on its `lwz` field loads").
2. **A helper function.** Wrapping each `fn_8013E2BC() == 0` boolean in a tiny
   `static inline` helper (as was done for the missing-arg families, §4p item
   17) may force the r3 result to stay live in r3 across the two call sites.
3. **Two separate boolean variables.** Declare `b1` and `b2` distinctly instead
   of one reused `var_r3`; the game's compiler may have merged them after
   codegen rather than in source.
4. Re-check whether `fn_8009CFA0` / `fn_8013E2BC` take a hidden first argument
   (r3 pass-through, §4p items 17/26) — the WANT sets NO register before either
   `bl`, consistent with true no-arg calls, but verify each callee's prologue
   before assuming.

## Related recipes (already in AGENTS.md, reusable elsewhere)

- AGENTS.md §6b item 1 — the goto-block_4 branchy boolean (works when there is
  ONE boolean; this function's two chained booleans are the hard case).
- AGENTS.md §6b item 4 / §4p items 17, 26 — ground-truth arity from callee
  prologues.
- The `subfic/adde` arithmetic fold is the same compiler behavior that §6b
  recipe 1 defeats; see also issue docs 01/10 (solved) for related regalloc
  coin-flips that turned out to be something else (frame size, missing args).
