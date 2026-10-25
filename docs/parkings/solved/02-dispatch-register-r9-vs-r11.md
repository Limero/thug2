# Issue 02 — Vtable-dispatch register allocation: r9 vs r11

**Status: NEARLY CLOSED (2026-08-23).** fn_8005C038 promoted (M9.21);
**fn_8005C338 SOLVED** at 100.0% — the M9.21 recipe transfers verbatim MINUS
the barrier step (no `*(o)=arg1` store precedes the vtable load here, so only
the r11 pin + `-ffixed-r9` are needed):

```c
// fn_8005C338 (52B) — 100.0% with // extra_cflags: -ffixed-r9
void fn_8005C338(void *arg0) {
    register void *r11 asm("r11");
    r11 = *(void **)((char *)arg0 + 8);
    ((s32 (*)(void *))*(s32 *)((char *)r11 + 0xAC))(arg0 + *(s16 *)((char *)r11 + 0xA8));
}
```

**fn_800CC358 IMPROVED 91.2% → 94.1%**: the tail select CAN be forced into r3
via a tail-only `register s32 sel asm("r3")` pin fed inside the branch arm
(pinning from a pointer expression remaps the whole web onto the pin — feed
pins only loads/constants/branch arms). Residual 2 words are exactly the
M8.35 "test-then-materialize" subfamily of doc 15 (want `cmpwi r9,0; li r3,0`
vs got reversed) — do not re-grind source shapes or schedule flags; revisit
only if a new scheduling lever appears. Best source: `src/wip/fn_800CC358.c`
(updated in place by the 2026-08-23 session); structure = NULL-guarded node walk
with `p = (n2 == NULL) ? NULL : (char *)n2 - 4;` staging + tail pin.

---

# ORIGINAL ANALYSIS (historical)

**Status:** PARKED (as of M4.9x; park set is a moving target — re-verify before trusting) (2 functions: fn_8005C038, fn_8005C338)

## The problem

In a family of indirect-call ("vtable dispatch") helper functions, the game's
compiler loads the vtable pointer into **r11**, but GCC 2.95.2 (all ProDG
builds) always chooses **r9** for every C shape tried (11 variants).

Original (fn_8005C038): the function creates an 8-byte stack frame, saves the link register via r0 to frame offset 0xc, stores incoming arg1 into the object at offset 0, loads the vtable pointer from object offset 8 into r11, loads a signed halfword offset from table offset 0x20 into r0, loads the function pointer from table offset 0x24 reusing r11, adds that offset to the object base in r3, transfers the function pointer to the link register for an indirect branch-link call, then restores the link register from frame offset 0xc, tears down the 8-byte frame and returns.

Compiled (any C form): the same shape loads the vtable from object offset 8 into r9 instead of r11, with the signed-halfword load from offset 0x20 and the function-pointer load from offset 0x24 both following through r9, and is otherwise identical in ordering and offsets.

## Why it's parked

This is a pure register-allocation difference with **identical semantics** —
r9 vs r11 are both caller-saved scratch registers. GCC 2.95.2's allocator
picks r9 because the expression uses a two-step `t[off/2]` pattern that it
assigns to its preferred scratch. There is no C source construct that forces
the compiler to emit r11 for this temporary. (The sibling functions that DO
match — e.g. fn_8005C2F8 — happen to use r9 naturally.)

## What was tried

- All 11 C source shapes for the dispatch expression (direct field access,
  temp variables, pointer-to-pointer chains, `s16` offset loads).
- Both ProDG C and C++ modes.

## Research directions for an external AI

> **Cross-clone note (2026-08, plan Item G):** Sims2DECOMP's wall catalog
> records the SAME class - a this-alias/vtable-pointer register choice
> (their r11/r9 coloring wall) - and cracked it by REMOVING
> `-fno-schedule-insns2` from their defaults (register COLORING, not
> emission order; their catalog: default flags first, then
> `-fno-schedule-insns` alone). THUG2's default build has no
> `-fno-schedule-insns2` to remove, so the retry priority here is:
> (a) default flags (current), (b) `-fno-schedule-insns` ALONE,
> (c) `-fno-peephole` (their register-swap walls), (d) volatile-store/vt
> pinning source tricks - LOW priority, but NOT a permanent park per
> their evidence. Do not re-grind the 11 source shapes; flags only.
> See `docs/parkings/README.md` background (technique catalog).
>
> **crashwoc update (2026-08):** the
> r9-vs-r11 vtable-ptr choice is ALSO the class Sims2's catalog cracked
> with var-declaration-order (their r11/r9 coloring wall) - and
> declaration-order permutation is a NEW legal lever never tried on the
> 11 source shapes (it is neither a source shape nor a flag; the
> "flags only" verdict above predates it). crashwoc automates it
> (`ai_decl_permute.py`: GCC 2.95.x declaration-order RA tiebreaker).
> The planned `--decl-permute` mode in `tools/test_wip_drafts.py`
> sweeps the docs 02/03/09-class parks first - re-try fn_8005C038/
> 8005C338 with it before keeping the park.
> UPDATE 2026-09-10: moot on both counts — both exemplars matched
> without it (see doc header), and decl-permute was tried 2026-08-23
> and retired repo-wide (720 perms, zero effect on m2c bodies;
> README item 10).

1. This is likely a GCC 2.95.2 register-allocation quirk: the vtable pointer
   temporary gets r9 when the RTL for `*(o+8)` is generated inside the call
   setup, vs r11 when hoisted. Investigate **expression evaluation order**
   and whether computing the vtable load *before* the `stw r4, 0(r3)` store
   (or after) changes the allocation.
2. Compare with the matched sibling fn_8005C2F8 (which uses r9): diff the two
   instruction sequences to find what semantic difference (extra arg, store
   order) selects the register.
3. GCC 2.95.2's `rs6000` backend prefers specific registers for
   indirect-call targets (`mtlr rX; blrl`); check `CALL_USED_REGISTERS` and
   the reload choices for the `*call_indirect` pattern.

## Where to look

- Drafts: `src/wip/fn_8005C038.c` (and fn_8005C338, same shape).
- Matched reference: `src/fn_8005C2F8.c` (uses r9, matches).
- History: `AGENTS.md` §4e ("dispatch register must be r9" gotcha).

## M8.3x sweep re-confirmation (2026-08-20)

Full 4-slice re-sweep with the fixed harness (test_wip_drafts now scores
against the full WANT size — the old prefix-compare false-EXACT is gone;
zero EXACT found, so the 3 promoted EXACTs of this round were the real
ones). The entire fresh NEAR tier top is already-parked territory:

| addr | pct | class | doc |
|---|---|---|---|
| 801270B4 | 97.0 | loop-bottom test reg coalesce | 17 |
| 8009A5B4 | 95.1 | call-arg setup order | 15 |
| 8005529C | 94.7 | call-arg setup order | 15 |
| 80076F8C | 93.7 | call-arg setup order | 15 |
| 8009ED14 | 93.1 | call-arg setup order | 15 |
| 801F50B0 | 92.6 | call-arg setup order | 15 |
| 8007BDC8 | 91.3 | call-arg setup order | 15 |
| 800CC358 | 91.2 | return-reg vs temp naming (r3/r11) | this doc |
| 80076EEC | 90.0 | (see sweep) | |
| 80138F10 | 89.7 | init-struct store order | 09 |
| 8005C038 | 71.4 | r9 vs r11 dispatch | this doc |

New case this round: **fn_800CC358** (136B, 3 words) — a NULL-guarded
node walk where WANT computes the final `node-4` address in **r3** (the
return register): `li r3,0; addi r3,r9,-4; lwz r3,0x38(r3)`. Every C form
(including the m2c double-NULL-check shape) makes ngccc use a temp (r11)
instead. Same class as this doc's r9/r11 case: the allocator's temp
register choice for a value that WANT happens to place in the return reg.

No flag combination (schedule-insns/2, peephole, sched-spec, O1/O3/O4)
flips any of the above; all remain parked.

## M8.3x breakthrough: `register asm` declarations solve r9↔r11 (fn_8000F2F8)

**Breakthrough (2026-08-20):** The r9↔r11 register-naming coin-flip can
be solved with GCC's `register ... asm("rN")` declarations (a standard
GCC extension, NOT inline asm) combined with step-by-step assignments.

**Example — fn_8000F2F8 (40B, now EXACT):**

The m2c draft was structurally perfect (same instruction sequence, same
semantics) but used r11 for address computation and r9 for the increment
— the reverse of WANT. Without flags: 9/10 diffs. With `-ffixed-r9`: 6/10
(increment matches but address moves to r10). With `register asm`
declarations: 5/10 (increment matches, address computation still uses r11
as a temp).

**The key insight:** breaking the address computation into 4 separate
statements, each assigning to the register-declared variable, forces GCC
to keep the value in that register throughout:

```c
void fn_8000F2F8(void *arg0, s32 arg1) {
    register void *r9 asm("r9");
    register s32 r11 asm("r11");
    r9 = *(s32 *)((char *)arg0 + 0x110);  // load → r9
    r9 = (s32)r9 << 2;                     // shift → r9
    r9 = (s32)r9 + (s32)arg0;              // add base → r9
    r9 = (s32)r9 + 0xD0;                   // add offset → r9
    *(s32 *)((char *)arg0 + 0xCC) = (s32)r9;  // store addr (r9)
    *(s32 *)((char *)r9) = arg1;              // store val via r9
    r11 = *(s32 *)((char *)arg0 + 0x110) + 1;  // increment → r11
    *(s32 *)((char *)arg0 + 0x110) = r11;       // store increment
}
```

This gives 0/10 diffs — byte-exact. The technique generalizes: any
r9↔r11 coin-flip where WANT uses r9 for one computation and r11 for
another can be solved by declaring both as `register asm` and breaking
the computation into step-by-step assignments.

**Transferable technique:** `register asm` + step-by-step.
Scope: works when the entire diff is register naming, not when there are
additional scheduling/ordering diffs (like 8005C038's dispatch case).
**M9.21 breakthrough for 8005C038 (2026-08-20):** the parking doc was
wrong — the r9↔r11 dispatch CAN be solved for fn_8005C038 with the
combination of three tricks. Promoted to EXACT.

1. **`register ... asm("r11")` declaration** pins the vtable-ptr temp to
   r11 (the WANT register choice), so both `lwz r11,8(r3)` and
   `lwz r11,0x24(r11)` reuse the same register.

2. **`-ffixed-r9`** per-object flag (via `// FLAG: -ffixed-r9` in the
   WIP header; promoted tool honors it). Reserves r9 so the only
   caller-saved temp available for the lwz pair is r11.

3. **`asm volatile ("" ::: "memory")`** between the `stw r4,0(r3)` and
   `lwz r11,8(r3)`. Without it, GCC hoists the vtable load above the
   `*(o) = arg1` store (move-safe, no alias). The empty asm barrier
   inserts zero instructions but pins the source order, so the GOT
   emits the WANT's stw-then-lwz sequence at +0x0C/+0x10.

Combined: 14/14 EXACT, DOL byte-identical on rebuild.

**Transferable recipe for vtable-dispatch coin-flips:**
- declare the vtable temp as `register ... asm("rN")` with the WANT register
- add `// FLAG: -ffixed-rM` for the WANT-and-source-swap register (the
  one the GCC keeps picking — reserve it out of the pool)
- if the source has a store-before-load that GCC would reorder through
  the vtable reload, insert `asm volatile ("" ::: "memory")` between
  them

## 2026-09-06 — NEW MEMBER SOLVED: fn_80054E40 (walker-register coin, 60.9% → EXACT)

fn_80054E40 (84B, find-first-idle-object walking the global list
lbl_80364C28; parked at 60.9% "walk-pointer coin — want keeps the walk in
r11, GCC coalesces the walk into r3") cracks with exactly the recipe above,
plus one placement refinement:

1. Walker pin: `register Unk_2EF06E12 *var_r11 __asm__("r11");`
2. `// FLAG: -ffixed-r11` (reserves GCC's preferred walk reg from the pool)
3. **Single-return while-form**: rewrite the goto-loop/early-return shape as
   a plain `while (walker != NULL) { ...; if (cond) return cand; walker =
   next; } return NULL;`. This is what GCC needs to keep the shared
   epilogue return as want's materialized `li r3,0`; with the old
   goto-loop + two-NULL-return shape GCC coalesced the epilogue to
   `mr r3,r11` (2 diffs) even with the pin. With both: 21/21 → promoted.

Lesson: the pin alone fixes the walk-reg COLOR; the single-return while-form
is what keeps the RETURN-BLOCK shape (li-vs-mr) — apply both together on
walker-coin parks that end in a shared `li r3,0; blr`.
