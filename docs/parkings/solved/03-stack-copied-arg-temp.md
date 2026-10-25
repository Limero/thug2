# Issue 03 — Table-dispatch with stack-copied arg: r0 vs r11 temp + store deferral

**Status: SOLVED (2026-08-23) — all three functions byte-exact at 100% masked match
via the "r0-wedge spill" recipe below. The doc's premise was stale: the store-deferral
half was already correct in the matched sibling's shape, and the only real divergence
(temp r11 vs want r0) is fixed by a `register u32 tmp asm("r0")` pin assigned FIRST.
No flags, no barriers needed.**

## Solution (2026-08-23)

Winning recipe (identical shape ×3, plain `-O2 -G0 -mcpu=750 -fno-common`):

1. `register u32 tmp asm("r0");` declared first; `tmp = *arg;` as the FIRST statement
   (pin supplies want's r0 choice).
2. Table load `t = *(void ***)(o + 8);` second.
3. `local = tmp;` AFTER the table-load statement (plain local copy supplies the exact
   pre-`lha` spill schedule — the "store deferral" half of this doc was never broken;
   the sibling fn_8005C2F8 already proved that shape matches).
4. Call through the fn-ptr cast with `(char *)o + (s16)*(s16 *)((char *)t + OFF)` and
   `&local` last.

Arity note: the incoming arg-pointer register (r4/r7/r8 across the trio) IS the
outgoing `&spill` slot — each wrapper forwards its own params through the call, so
arity = load-register position (`lwz rX, 0(rN)` with N ≥ r4 ⇒ wrapper forwards N−1 own
params + `&spill` in slot N). Validated byte-exact on two fresh signatures.

```c
// fn_8005C174 — wrapper (o, u32 *arg), offsets 0x68/6C — 100.0%
void fn_8005C174(void *o, u32 *arg) {
    register u32 tmp asm("r0");
    u32 local;
    void **t;
    tmp = *arg;
    t = *(void ***)((char *)o + 8);
    local = tmp;
    ((void (*)(void *, u32 *))*(void **)((char *)t + 0x6c))((char *)o + (s16)*(s16 *)((char *)t + 0x68), &local);
}

// fn_8005C2B8 — wrapper (o, x1, x2, x3, u32 *arg), offsets 0x98/9C — 100.0%
void fn_8005C2B8(void *o, s32 x1, s32 x2, s32 x3, u32 *arg) {
    register u32 tmp asm("r0");
    u32 local;
    void **t;
    tmp = *arg;
    t = *(void ***)((char *)o + 8);
    local = tmp;
    ((void (*)(void *, s32, s32, s32, u32 *))*(void **)((char *)t + 0x9c))((char *)o + (s16)*(s16 *)((char *)t + 0x98), x1, x2, x3, &local);
}

// fn_8005C3A0 — wrapper (o, x1..x4, u32 *arg), offsets 0xB8/BC — 100.0%
void fn_8005C3A0(void *o, s32 x1, s32 x2, s32 x3, s32 x4, u32 *arg) {
    register u32 tmp asm("r0");
    u32 local;
    void **t;
    tmp = *arg;
    t = *(void ***)((char *)o + 8);
    local = tmp;
    ((void (*)(void *, s32, s32, s32, s32, u32 *))*(void **)((char *)t + 0xbc))((char *)o + (s16)*(s16 *)((char *)t + 0xb8), x1, x2, x3, x4, &local);
}
```

(Passthrough param types s32 vs void* are codegen-neutral — both flavors scored 100.0.)

---

# ORIGINAL ANALYSIS (historical)

## The problem

A sibling of the EngineX-style table-dispatch family (see Issue 02) takes a
**stack-copied argument**: it loads a `u32` from `*arg`, spills it to the
stack, and passes `&spill` to the indirect callee. The game's compiler
allocates the temporary and schedules the spill differently than every ngccc
build.

Original (fn_8005C2B8, offsets 0x98/0x9C): the function builds a 0x10-byte frame, saves the link register via r0 to frame offset 0x14, loads the incoming word through r7 offset 0 into r0 as the stack-copied temp, loads the table pointer from object offset 8 into r9, materializes the spill address as frame offset 8 into r7, stores the temp to frame offset 8 before the vtable offset loads, then loads the signed halfword offset 0x98 and the function pointer at 0x9c through r9, biases the object base in r3, and indirect-calls through the link register with the spill address as argument.

Compiled with ngccc: the argument temp is instead homed in r11 with the load from offset 0 through r7, and the spill store of r11 to frame offset 8 is deferred until after the halfword and function-pointer table loads at 0x98/0x9c through r9, reversing the retail store-before-load order.

## Why it's parked

Two coupled divergences that no C shape reproduces:
1. **Register choice** r0 vs r11 for the stack-copied temp (cf. Issue 02 —
   same unreproducible-allocation class).
2. **Store scheduling**: the game stores the spilled temp before the vtable
   offset loads; ngccc defers the store to just before the call. Writing the
   C in "load arg, spill, then dispatch" order does not change ngccc's
   scheduler decision.

This is the same "unreproducible-allocation class" as the FPR frame quirk
(Issue 01): the game's compiler build differs from every available ProDG
build in its register allocation / scheduling for this pattern.

> **Day-0 A/B caveat (2026-08, cross-clone):** this is NOT a point-version
> difference. Sims2DECOMP (same ProDG family) proves all four installed
> ProDG point-versions (3.5–3.9.3; 609 functions x 4) are codegen-identical.
> If the game build differs, it is a genuinely distinct SN build with no
> installed counterpart — version swaps cannot fix this class. Levers:
> source shape or scheduling flags, tried in priority order - DEFAULT
> flags first, then `-fno-schedule-insns` ALONE (Sims2's 94%-corpus
> workhorse; never auto-pair it), then volatile-store source casts, then
> `-fno-peephole`, then the `-fno-sched-spec` + `-fno-sched-interblock`
> pair (THUG2-proven in AGENTS.md §4r, NOT Sims2-proven - their matched
> corpus never used it). CORRECTED 2026-08 (Sims2 evidence):
> `-fno-schedule-insns2` alone made things WORSE there (their r11/r9
> coloring wall cracked by REMOVING insns2 from defaults) - only use it
> when THUG2's own re-proven cases apply (§4p recipes 48/49).
> See `docs/parkings/README.md` background (corrected flag ladder).

> **Validated structural (2026-08, Item G):** Sims2's locked-wall class
> "compiler emits BETTER code than original" (their r0-arg-scratch
> preservation) is the same wall as this r0-vs-r11 temp class - their
> 100-budget permuter got 0 hits on it. The r0 choice here is the
> register-ALLOCATION side (their coloring-wall catalog cracked r11/r9
> via insns2-removal on OTHER shapes, not this one). Do not re-grind
> source shapes; retest flags only per the corrected ladder above.
>
> **crashwoc update (2026-08):**
> declaration-order permutation (GCC 2.95.x RA tiebreaker, automated by
> crashwoc's `ai_decl_permute.py` -> planned `--decl-permute` mode in
> `tools/test_wip_drafts.py`) is a NEW legal shape never tried here -
> the r0-vs-r11 temp choice is a register-ALLOCATION decision, so
> reordering the temp/table local declarations is the untried lever
> (same class as Issue 02). The flag retests above are automated by the
> planned `--flag-sweep` + `--combos 2` mode (Item C2, pairwise combos
> never run on this family). Docs 02/03/09-class parks are C1's named
> sweep targets.
> UPDATE 2026-09-10: C1 retired repo-wide (tried 2026-08-23, zero
> effect on m2c bodies) and the three flag knobs proven codegen-inert —
> neither prescription above applies anymore; only an unbuilt
> `--combos 2` automation remains.

## What was tried

- Every ordering of the store vs. the vtable loads in C source.
- Temp variables of every width (`u32`, `s32`, pointer).
- Passing the spill address vs. the value.

## Research directions for an external AI

1. Find a GCC 2.95.x scheduler rule that would place an independent
   `stw` (of a just-loaded value) **before** two dependent loads
   (`lha`/`lwz` on a different register) — this is a load-delay/scheduling
   policy difference between the game's compiler and ngccc.
2. Determine whether the r0 choice is a consequence of the game compiler
   evaluating the *argument expression* (`*arg`) before the vtable setup,
   while ngccc evaluates the vtable first. Test C that computes the arg
   temp into a named local *before* touching `o->table`.
3. If the store-before-lha order is a ProDG `-mregnames`/scheduling flag
   difference, locate the flag in the game's build.

## Where to look

- Drafts: none kept (only noted in the matched sibling's header).
- Matched reference: `src/fn_8005C2F8.c` — its header documents the parked
  siblings (off 0x68/0x6C for fn_8005C174, 0x98/0x9C for fn_8005C2B8,
  0xB8/0xBC for fn_8005C3A0).
- History: `AGENTS.md` §4c ("same unreproducible-allocation class").
