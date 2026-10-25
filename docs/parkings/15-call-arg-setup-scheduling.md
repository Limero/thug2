# Issue 15 — Call-argument setup scheduling (compound-constant interleave)

**Status: OPEN but much smaller (2026-08-23 round).** M8.31–8.33 cracked the
biggest sub-family (callee-return-type flip, AGENTS.md recipe 51); 800D4D30,
80041F8C, 8002CA8C, 801B301C, 800F4CC4 and 80215848 have since matched.

2026-09-24 round result (isolated candidates, not promotions):

- **fn_8013A93C CANDIDATE-EXACT (masked 100.0%, relocation-checked).** The
  remaining two-word independent-load order is fixed by a zero-code memory
  clobber:
  ```c
  temp_r9 = *(u32 *)lbl_8029F3F8;
  __asm__ volatile("" ::: "memory");
  var_r4 = (u32)temp_ra - *((s32 *)temp_r29);
  ```
  Independently re-scored as `EXACT 100.0%` with the expected seven
  relocations. It has not yet been copied into `src/wip/` or promoted.
- **fn_80169CE4 CANDIDATE-EXACT (masked and local link-simulation 100.0%).**
  C-only staging could not place the stack store between the two zero
  call arguments. The retained candidate uses a three-instruction semantic
  window:
  ```c
  __asm__ volatile("li %0,0" : "=r"(z4));
  __asm__ volatile("stw %0,16(1)" : : "r"(scopy) : "memory");
  __asm__ volatile("li %0,0" : "=r"(z5));
  ```
  Independently re-scored as masked `EXACT 100.0%`; the local link check
  reports all 128 bytes matching. It has not yet been promoted.
- **fn_80252C90 LINK-SIMULATION CANDIDATE-EXACT (236/236 bytes).** The
  standalone masked score is `NEAR 98.3%` only because its sole remaining
  word is the expected `R_PPC_EMB_SDA21` relocation. A two-instruction
  dependency/order window plus hard argument pins fixes the
  `[mr r5][addi r4][mr r3]` order. Promotion needs manual small-data
  registration and the ordinary linked-DOL check because the standard sweep
  cannot validate that SDA word.
- `fn_80173D30` remains parked at the documented 99.5% ceiling.
- `fn_80060BB0` is not a productive Issue 15 target in its current draft:
  its re-scored result is approximately 2.3%, not the older parked state.

2026-09-21 round result (second pass, batch A):

- **fn_801F3910 SOLVED (86.6% → 100.0%) + PROMOTED.** The residual was NOT a
  pure scheduler tie — it had a SEMANTIC half. want's first `fn_80127684` call
  passes the `fn_80126EAC` RESULT as arg1 (r3 is never reloaded: the preceding
  `mr r31,r3` left it live), and `fn_801277E4` is 3-arg `(obj, s32, s32)` with
  the QB key in **r5** and `0` in r4 — `fn_801277E4(temp_r31, 0,
  QB_REQUIRE_PERFECT)`, the inverse of the natural (obj, KEY, 0) spelling and
  of the m2c 2-arg form. New tell: when want emits a call argument in r3 with
  NO setup at all, the value is the previous call's return still sitting in r3
  (`bl A; mr r31,r3; ...; bl B` with B's arg1 == r31). Companion: check the
  key/value POSITION on every 3-arg QB notifier before assuming (obj,KEY,val).
- **fn_80252C90 PARKED at 93.2% (was 38.1%).** Not a call-site shape at all —
  m2c's `s32 *arg0` scaled every `arg0 + N` by 4 (r27 was arg0+0x30 instead of
  +0xC) and the `saved_reg_r13` hack was really an **r13 small-data global**
  (`lbl_803CA340` = 0x803D2280-0x7F40) needing `-msdata=eabi -G4` (doc 43
  route). Residual = the classic single-call arg-emission order at the
  fn_80253BF0 site: want `[mr r5,r25][addi r4,r26,0x88][mr r3,r30]` vs got
  `[mr r3,r30][mr r5,r25][addi r4,r26,0x88]`; staging the address, a named `a3`
  local, `void *arg3` and `-fno-schedule-insns{,2}` (42.4/86.4) all resist.
  Its 4th diff word is a HARNESS artifact: `lwz r3,-0x7f40(r13)` vs the
  object's SDA21 form, which `gen_leaves.compile_fn` does not mask
  (`R_PPC_EMB_SDA21` is not in its reloc list) — verify with `sda_verify.py`.
- **fn_80137E30 PARKED at 75.6% (was 73.3%).** Two wants: (1) want copies+
  tests arg4 in r6 (`mr r6,r7) … cmpwi r6,0`) while ngccc always coalesces
  `s32 a4 = arg4; if (a4 != 0)` back onto r7 (copy disappears; 4 placements /
  decl orders failed); (2) the prologue store/test interleave
  `[stw 0x4][mr r6,r7][sth spA][cmpwi r5,0][stw 0xC][beq]`. Structural fixes
  that landed: arg0's tail fields are a BYTE (want `stb r9,0(r31)`) and a u16
  (`sth`), and the `Mem_Alloc`/`memcpy` size loads are `lhz` (spA used
  unsigned). Both members join the doc-15 list below.
- **fn_80060BB0 PARKED (rebuilt).** A regalloc spill, not arg order: want
  spills BOTH walk pointers (`stw r9,8(r1)` head, `stw r0,0x10(r1)` cur) and
  reloads them at the loop top/bottom, saving only r30/r31 (stmw r30, frame
  -0x20); ngccc keeps head/cur in r28/r29 (stmw r28, frame -0x18) and drops
  the stores + reloads (152B vs 176B). Non-volatile C cannot make the
  allocator spill (local struct / array / all loop spellings keep them in
  regs); `volatile` on both overshoots (196B, extra reloads). Its semantic
  fix: `fn_800F2AD8` is 3-arg `(global, obj->unk0x10, 1)`.

2026-09-21 round result (first pass):

- **fn_8000DAB8 SOLVED (87.5% → 100.0%).** NEW lever — **guard as an if/ELSE**.
  WANT hoists two independent arg-moves above the guard compare
  (`mr r3,r6` = the callee's arg1 copy, then `mr r5,r7` = its arg3) and emits
  the *result* copy FIRST; m2c's `var_r3 = arg3; if (cond) var_r3 = call(...)`
  emits it LAST (r5 then r3). Writing the guard with the fallback value in the
  **else arm** —
  ```c
  if (arg1 == 3) { var_r3 = fn_8000D984(arg3, arg0, arg4, arg2); }
  else           { var_r3 = arg3; }
  ```
  — reorders the pair with zero bytes added. Prior failures (~6 shapes):
  pre-computed locals for arg3/arg4 in both assignment orders, the value in a
  declaration initializer, void/struct-pointer proto flips for the moved args,
  and the m2c ternary shape. Statement-order/decl-order permutations remain
  inert for this sub-family (consistent with the 2026-08-23 finding).
  Companion tell: fn_8000DAB8's 8011A258 sibling was the *opposite* kind of
  stale-data bug — its recorded `// FLAG: -O1` masked an already-exact body
  (61.9% with the flag, 100.0% without; see doc 55).

2026-08-23 round results:

- **fn_8005529C SOLVED (94.7% → 100.0%).** NEW recipe — **"+r" emission-point
  barrier**: when WANT emits `li rX,K` BEFORE an independent test (`or.`/`and.`/
  `cmpw`) that follows a `bl`, and GOT sinks the li below the test, insert
  `__asm__("" : "+r"(var));` between the assignment and the test. Zero bytes;
  forces the emission point. Cracked it after ~20 prior source shapes failed:
  ```c
  temp_r3_2 = strstr(arg1, (s32)lbl_8029315C);
  var_r0 = 1;
  __asm__("" : "+r"(var_r0));
  if (temp_r3_2 == NULL) {
      var_r0 = 0;
  }
  ```
- **fn_80076F8C IMPROVED 93.65% → 95.24%.** WANT leaves r6/r7 untouched at the
  `bl fn_80269F4C` ⇒ args 4/5 are pass-through; writing them explicitly (the
  earlier "semantically correct 5-arg form") is what forced the early mr-copies.
  The honest **3-arg call** `fn_80269F4C((s32)sp8, (s32)lbl_80295718, arg0)`
  fixes words 7–8. NEW corollary: **varargs pass-through args must stay
  unwritten at the call site; explicit passthrough args inject mr-copies into
  arg setup** (want-r6/r7-untouched is the tell). Remaining 3 words: want
  `[mr r27,r6; mr r26,r7; addi r3,r1,8]` vs got `[addi; mr; mr]`.
- **fn_8009A5B4 / fn_8009ED14 / fn_8007BDC8 DEAD-END-CONFIRMED** with an
  exhaustive sweep: all of `-fno-move-all-movables`, `-fno-reduce-all-givs`,
  `-fno-caller-saves` EXIST in this cc1 but are codegen-inert per-object
  (+0.00 alone, in all pairs, as a triple); `-fno-schedule-insns2` alone
  REGRESSES 4/5 (−10..−20); the nfsmw combo (`-O1 -fschedule-insns
  -fschedule-insns2 -fgcse -fexpensive-optimizations -fforce-addr`) is
  byte-identical to -O2 on all five (only `-fschedule-insns2` is load-bearing;
  plain `-O1` collapses everything — Sims2's "-O1==-O2" holds here too);
  automated decl-order permutation (24/24/6/24/2 orders × flag sets) has ZERO
  effect on any member — retire decl-permute as a lever for m2c-shaped bodies.
  Also probed and neutral: ±rerun-loop-opt/cse-after-loop, ±force-addr/
  force-mem, ±thread-jumps, ±unroll, -fno-gcse/-expensive-opt/
  -strength-reduce/-function-cse/-defer-pop. Nonexistent: `-fgcse-sm`,
  `-fgcse-las`.

Still parked: fn_8009A5B4→**SOLVED 2026-09-28 (see below — the flag sweep above
was correct but the wall is escapable)**, fn_8005529C→promoted,
fn_8009ED14→**SOLVED+promoted 2026-08-31 (not_if lever, see member list above)**,
fn_80076F8C (95.24), fn_8007BDC8 (91.3), plus doc-02's fn_800CC358 residual
(94.1, non-constant arms — not_if does not transfer, see above).
**Draft-status note (2026-08-26 audit):** the wip drafts for fn_8007BDC8 and
fn_801270B4 (see member section at bottom) were removed in commit b7cf86e9;
both functions remain unmatched auto-asm — regenerate drafts before retrying.

## 2026-09-28 round: three members escaped, one "fixed ngccc choice" retracted

None of these were new functions — all three were already in this doc or in
AGENTS.md as exhausted. The levers below are the ones that actually worked.

### fn_8009A5B4 — SOLVED: the 3-`li` arg-setup permutation (95.1% → EXACT)

WANT `li r3,0; li r5,0; li r4,5; bl fn_80096588`; every C spelling emits
ascending `li r3; li r4; li r5`. This was re-proved unreachable *very*
thoroughly before being escaped: all five ProDG versions, `-O0/-O1/-O3/-Os`,
**every one of the 134 `-f…` flags cc1.exe advertises**, ~30 callee-prototype
param-type combos per position, 14 arg-value combos, and every call spelling
(K&R, variadic, fn-pointer, comma-staged, M8.31 s32-return, the C++ frontend).
All ascending. Register pins do not help: the compiler folds the constant SETS
into the CALL insn.

Two findings:

1. **The permutation is per-CALLEE and systematic, not local.** A whole-`.text`
   census of `li;li;li;bl` triples: 20 sites of `(3,5,4)` — *all* of them
   `fn_80096588` with arg0==arg2 — against 97 ascending ones (e.g.
   fn_8001f28c). So a future member of the same callee will hit the same wall;
   a different callee's member probably will not.
2. **Escape hatch: a 3-instruction volatile-asm window with hard-register
   outputs**, keeping the `bl` itself in C:
   ```c
   register s32 a0 __asm__("r3");
   register s32 a2 __asm__("r5");
   register s32 a1 __asm__("r4");
   __asm__ volatile("li %0,0\n\tli %1,0\n\tli %2,5" : "=r"(a0), "=r"(a2), "=r"(a1));
   fn_80096588(a0, a1, a2);
   ```
   3/41 instructions = 7.3% asm, well under the 30% ASM_FUNC law, and it is
   strictly better than the 4-insn version in `src/fn_80019958.c` because the
   `bl` stays real C. **Trap:** the callee must be prototyped `(s32,s32,s32)`
   here — with a byte-typed third arg ngccc inserts `clrlwi r5,r5,0x18`
   (16.7% DIFF), because asm-supplied register variables are no longer
   constant-folded into the arg.

### fn_800A31EC — SOLVED: an arg-slot pin closes a lone transposed `li` (93.9% → EXACT)

Signature: one `li rX,imm` transposed against an adjacent store, everything
else exact. WANT hoists the *second* call's `li r3,0xc` one slot **above** the
`lbl_8037BB64 = 0` store; ngccc sank it below. An **arg-slot register pin**,
assigned at want's slot, forces the `li` to emit there:
`register s32 n2 __asm__("r3");` + `n2 = 0xC;` placed after the
`lbl_8037BB58 = t1` store. AGENTS §6az-241 / §6an-3 record this lever for
*emission position*; this is the first doc-15 member it closed outright.
Two requirements: pin **only the out-of-position call** (pinning both sizes
with one var collapses to 69.7% — the single r3 pin cannot serve two
lifetimes), and use `s32`, never `u8` (AGENTS §74-161a).
A 29-flag × 11-barrier-gap sweep (373 variants) never beat 93.9%, so the
*order-only* form is a dead end; the pin is the lever.

### fn_800B0214 — RETRACTION: never a doc-15 member (73.5% → EXACT)

AGENTS.md M8.36 filed this as a "dual `li r3,0` sites" doc-15 coin flip with
"15+ structural variants resisted". Wrong diagnosis; two ordinary semantic
bugs:

1. **A `(void)` prototype on a callee that really takes an argument.** m2c
   drafted `fn_800ADCD4()` as zero-arg, so the call inherited a dead r3. WANT
   passes `arg0->unk0x3C` in r3 — the guard's own `lwz r3,0x3c(r31)` left live
   across the `beq` into the call. (73.5% → 79.4%.)
2. **`var_r3 = 0;` as a prologue initialiser.** It keeps a live 0 in r3 for the
   whole function, so ngccc hoists the `li r3,0` to *entry* and shifts the
   first 7 words. WANT has no entry `li`: its 0 is the branch SHADOW of the
   0x1C test plus a separate out-of-line `li r3,0`. Deleting the initialiser
   and writing the 0 **explicitly inside** the `unk0x1C != 0` arm reproduces
   both sites at zero byte cost. (79.4% → 100%.)

Two transferable signatures:
- **"GOT hoists an entry `li` that WANT places in a branch shadow"** — look for
  a draft-level `var = 0;` initialiser, not for scheduling.
- **A call with a `(void)` proto whose WANT `bl` has no preceding arg setup is
  a MISSING ARGUMENT, not a leftover.** Add this to the doc-10 callee audit
  (AGENTS §6ap-132 already extends that audit past `blr` stubs to dead-code
  callees; this extends it to *m2c-invented* zero-arg protos).

### fn_800A9CE8 (292B, 95.9%): NEW HARD-WALL SIGNATURE — preheader own-insn always first

Not arg-setup order, so filed here only as a "do not grind" marker. The only
residual is a 3-word rotation in the loop preheader: WANT
`cmpwi cr4,r25,0 ; lis r24,-0x7fd6 ; li r29,0`, got `li r29,0 ; cmpwi ; lis`.
The `cmpwi` and `lis` are CSE-hoisted loop invariants; the `li` is the
preheader's own statement. GCC's loop CSE records a preheader's *own* insns
before the hoisted invariants, and the own insn has the lower LUID, so it
always lands first. Exhausted: 9 source shapes (do-while+if, while-condition
assignment, decl-init, init above the guard, for/while init, goto state
machine, `off = count`, `__asm__("li %0,0")` and a volatile twin) × 6 flags ×
**all five ProDG versions** × `-O1`/`-O3` — identical preheader every time.
Proof there is no C construct: the only block whose single successor is the
loop header *is* the preheader, so any other placement moves the `li` earlier.
An asm preheader is not a fix either (GCC still hoists its own copies). DOL
census: `lis` immediately followed by `li` occurs **nowhere else** in `.text`.

## The problem

For multi-argument calls where one argument is a 32-bit constant
materialized as `lis rX, hi; ori rX, lo` (or where simple `li` constants and
an address `addi` share the setup block), the *game compiler* and *ngccc
3.9.3* emit the argument-setup instructions in a different order. Every
other instruction in the function matches byte-for-byte; only the ordering
of 2–3 setup instructions differs. The masked comparison flags them with
mask `FFFFFFFF` (no mask), so they are genuine differences, not placeholders.

### Concrete example: `fn_800D4D30`

Source (obviously-correct C, all variants tried):
```c
s32 sp8;
sp8 = 0;
fn_801286D0(arg1, 0xA1DC81F9, &sp8, 0);
```

WANT (game): the zero constant is materialized in r0 for the stack slot, the high half -0x5e24 of the 0xA1DC81F9 constant is loaded into r4, the zero is stored to frame offset 8, the low half 0x81f9 completes the constant in r4 first, then the arg1 value is moved from r29 into r3 after the constant completes, the spill address is materialized as frame offset 8 into r5, zero is loaded into r6, and the call to fn_801286D0 follows.

GOT (ngccc 3.9.3 — same for every source variant tried): the same zero, high-half, spill-store, address and zero moves appear, but the arg1 move from r29 into r3 is emitted before the low-half completion of the constant in r4, so the constant completes after the register move rather than before.

### The rule the game compiler appears to follow

Once a `lis` half of a compound constant is issued, the game scheduler
issues the `ori` (completing the constant) before emitting a *register move*
(`mr`) for an earlier argument. ngccc instead treats the `mr` as ready and
issues it first. The same pattern appears with `li`/`addi` pairs:

- `fn_8002CA8C`: WANT `li r4,0; li r5,0xf0; addi r3,r30,4` (both `li`s
  first, address last); GOT `li r4,0; addi r3,r30,4; li r5,0xf0`.
- `fn_80041F8C`: WANT `lis; addi r5; ori; mr r3; li r6`; GOT `lis; mr r3;
  ori; addi r5; li r6`.

In all three, the constant(s) finish (or are emitted) before the first
argument's `mr`/`addi` in the game binary.

## Evidence that it is NOT a source-form problem

`fn_800D4D30` was compiled with (each producing **identical** GOT output):
- plain literal `0xA1DC81F9`
- cast `(u32)0xA1DC81F9`
- `arg1` declared `u32`
- constant via local `s32 c = 0xA1DC81F9;`
- constant + pointer staged through locals
- `volatile s32 c = ...` (changed codegen entirely — wrong)
- the real build flags `-O2 -G0 -mcpu=750 -fno-common` (ProDG 3.9.3),
  raw byte comparison

None of these move the `ori` before the `mr r3`.

## The counter-example (why it is solver-relevant)

11 promoted functions contain the sequence `ori rX, rX, lo; mr rY, r0; bl`
e.g. `fn_8009E96C`:
```c
fn_801277E4(*(s32 *)((char *)arg2 + 0x18), 0x0830ECAF, *(s32 *)((char *)arg0 + 0x18));
```
compiles to `lwz r0,0x18(r3); lis r4,0x830; lwz r3,0x18(r5); ori r4,r4,0xecaf;
mr r5,r0; bl`. Here the `ori` also lands **before** the final `mr`. The
distinguishing feature: in the promoted case the argument moves are
*memory loads* (`lwz`) and the final `mr` is a *late* arg, so both
schedulers agree. The stuck cases all have a **trivial register move
(`mr r3, r29`) as the FIRST argument** — that is where the schedulers
diverge.

## M8.26 sweep — 8 more members confirmed at 2–4 word diffs

Re-diffed the fresh NEAR tier (post-8002FEF0 promotion); all remaining
2–4-diff candidates below are this family. WANT/GOT word-level patterns
(masks unset — genuine diffs):

- `8003DB0C` (2): 4-arg call `mr r4, r28` before `mr r3, r31` (WANT) vs
  swapped (GOT) — plain mr/mr order, no constants.
- `8009A5B4` (2): `li r3,0; li r5,0; li r4,5` (WANT) vs `li r3,0; li r4,5;
  li r5,0` (GOT) for `f(0,5,0)`.
  **SECOND, INDEPENDENT CONFIRMATION (2026-09-17):** the callee is
  `fn_80096588` and the *same* call appears again inside a completely
  unrelated loop body at `fn_80019958` (0x8001A078) with the byte-identical
  WANT order `li r3,0; li r5,0; li r4,5` and the byte-identical ngccc GOT
  order. `fn_8009A5B4` makes it as its FOURTH instruction (no preceding
  context at all), `fn_80019958` as the 31st inside a do-while. Two functions,
  same callee, same argument tuple ⇒ the interleave is a property of the
  (callee signature, arg-constant) expansion, **not** of the call site or of
  the surrounding block — so no source shape at the *call site* can reach it.
  `fn_80019958` also re-confirms the flag side of this doc: DEFAULT flags give
  97.1% (2 words = this call only) while `-fno-gcse` (its stale header flag)
  scores 17.4%, and `-fno-schedule-insns{,2}`/`-fno-peephole`/`-fno-sched-*`
  all stay ≤ 97.1% — i.e. the flags are exhausted, the residual is exactly
  this bullet. Parked at 97.1% (draft carries the full analysis).
- `8005529C` (2): `li r0,1` before `or. r3,r3,r3` (WANT) vs after (GOT)
  for `var_r0=1; if (ret==NULL) var_r0=0;` after the 2nd call.
- `80151534` (2): `addi r4,r4,0x7d28` (completes lbl const) before
  `mr r3,r30` (WANT) vs after (GOT).
- `801B301C` (2): `lwz r3,0x34(r31)` before `lwz r6,0xc(r31)` (WANT) vs
  swapped (GOT) — two memory-load args.
- `80076F8C` (4): `lis r4; addi r4` (lbl const) before `mr r27,r6;
  mr r26,r7` (WANT) vs after (GOT).
- `8009ED14` (2): `and. r0,r28,r29` before `li r3,1` (WANT) vs after (GOT)
  for `var_r3=1; if (!(t28 & t29)) var_r3=0;`.
  **SOLVED 2026-08-31 (promoted, DOL byte-identical) — the not_if lever.**
  Rewrite the init-if as an explicit **inverted if/else with constant arms**:
  `if (!(t28 & t3)) { var_r3 = 0; } else { var_r3 = 1; }` emits the WANT
  order `[test; li r3,1; bne END; li r3,0]` exactly. The general rule this
  reveals (GCC 2.95 expansion of explicit if/else with single assignments
  to the same var): **`if (C) var = A; else var = B;` emits `[test(C);
  B; branch-if-!C-to-merge; A]`** — the ELSE arm's value is materialized
  first and the THEN arm on fallthrough. So any want shape
  `[test; T; bcc-to-END; F]` is written as `if (!cond_T) var = F; else var = T;`
  (NOT the ternary — `var = cond ? T : F` hoists T ABOVE the test and is a
  different expansion; and NOT the init-if `var = F; if (cond) var = T;`
  which emits `[F; test; branch]`). The plain ternary and the notted
  ternary both still emit li-first here. **Does NOT transfer when an arm
  depends on a register**: fn_800CC358's tail (arms 0 vs node-4) coalesces
  node into r3 under every branchy form (50/38/79/91% measured) — the
  init-if + sel-r3 pin at 94.1% stays its best (doc-02).
- `80013410` (2): `lis r9` (lbl addr) before `li r11,1` (WANT) vs after.
- `800A4E74` (2): `li r5,1` before `ori r3,r3,0xb220` (WANT) vs after —
  compound-constant completed LAST.

Recipe-57 temp-first was re-tried on all of these (named temps for the
first-evaluated args/loads/consts, pointer temps, all-args temps, statement
reordering, if/else and ternary forms): every variant reproduces GOT — the
schedulers diverge exactly on the trivial-move/const/li-vs-test placement.
Worth re-testing with per-object flag variants in THIS priority order
(Sims2DECOMP - same ProDG family, 10,967 flagged files - puts
`-fno-schedule-insns` first: ~94% of their corpus uses it alone):
DEFAULT flags FIRST, then `-fno-schedule-insns` ALONE (store-order/
reg-choice; never auto-pair it), then volatile-store source casts,
then `-fno-peephole` (Sims2 technique 9, register-swap walls), then
`-fno-sched-spec -fno-sched-interblock` (THUG2-proven §4r pair; note
Sims2's corpus never used these two - they are NOT Sims2-proven).
CORRECTED 2026-08: `-fno-schedule-insns2` alone made things WORSE in
Sims2 (their r11/r9 coloring wall cracked by REMOVING insns2 from
defaults) - keep it only for THUG2's own re-proven cases (§4p recipes
48/49: call-arg/prologue ORDER, arg0-home); their `-O1 == -O2` for
tested shapes.
See `docs/parkings/README.md` background.

> **crashwoc update (2026-08):** the
> doc-15 family (fn_8002CA8C, fn_8009A5B4, fn_8005529C, fn_800D4D30,
> fn_80041F8C + the M8.16/M8.26 members above) is the planned validation
> target for the `--flag-sweep` + `--combos 2` mode of
> `tools/test_wip_drafts.py` (automates the ladder sequence above with
> auto-scoring and pairwise combos - pairwise was never run on this
> family). UPDATE 2026-09-10: the three GCC 2.95.2 knobs
> (`-fno-move-all-movables`, `-fno-reduce-all-givs`, `-fno-caller-saves`)
> were probed 2026-08-23 and proven codegen-inert, so the harness remainder
> is automation only; declaration-order permutation (ex-C1) was tried
> and retired on this family (720 perms, zero effect) — do NOT re-try
> it on 80076F8C/801B301C.

> **Validated structural (2026-08, Item G):** Sims2's same-wall evidence:
> their mutually-exclusive store-order/hoist couplings (the exact
> lis+ori-const-before-mr interleave) never cracked with source forms or
> the 100-budget permutation sweep - matches the argument-setup interleave
> here. Their `-O1 == -O2` finding also explains why the nfsmw-style -O1
> experiment (Item D) is expected to NOT flip anything: the scheduler
> flags, not the -O tier, are the lever. Do not re-grind source shapes on
> the M8.26 members; re-test flags only per the corrected ladder + Item D.

## Research directions (for an external solver)

1. **Compiler archaeology**: the game was built with a ProDG/SN GCC that
   schedules the `ori` (compound-constant completion) ahead of an
   unrelated `mr`. Search other GCC 2.95.x PowerPC backend revisions for
   `rs6000` scheduler changes ("move vs ori priority", "pair-scheduling
   of li/ori"). A `-fschedule-insns` vs `-fschedule-insns2` difference or
   a specific `-mcpu` scheduler table (750 vs 7400/7410) may explain it.
   The project currently builds with `-mcpu=750`; the game's real flags are
   unknown beyond that.
   > **Day-0 A/B caveat (2026-08, cross-clone):** the scheduler difference
   > is NOT a point-version issue — Sims2DECOMP proved all four installed
   > ProDG versions (3.5–3.9.3) codegen-identical (609 fns x 4, zero
   > flips). It is either a per-object FLAG difference (priority order:
   > DEFAULT flags first, then `-fno-schedule-insns` alone, then
   > volatile-store casts, then `-fno-peephole`, then
   > `-fno-sched-spec`/`-fno-sched-interblock` pair; CORRECTED 2026-08:
   > `-fno-schedule-insns2` alone was WORSE in Sims2 - removal-fix, not
   > addition, except §4p recipes 48/49 cases), a `-mcpu`
   > scheduler-table choice, or a genuinely distinct game SN build. A
   > full era-authentic alternative: nfsmw (same ProDG family) built its
   > whole game at `-O1` with BOTH scheduling passes ON
   > (`-fschedule-insns -fschedule-insns2 -fgcse -fexpensive-optimizations
   > -fforce-addr`) - try that per-object combo on this family
   > (plan Item D). EXPECTATION (Sims2): their `-O1 == -O2` for tested
   > shapes, so the scheduling flags are the real lever, not the -O tier.
2. **Inline-helper trick**: wrap the call in a `static inline` function and
   reorder parameter declarations; GCC's call setup for inlined helpers can
   change scheduling. (Not yet tested — all tested variants were inline.)
3. **Reordering the call in the source** so the constant is the *last*
   evaluated expression (e.g., assign args to temporaries in the order
   r5, r4, r3) — tested via `v_stage`, no effect.
4. Accept a **non-matching workaround**: keep the NEAR draft and add the
   function to the project's "known-scheduling-diff" exemption list if the
   project ever adopts one.

## How to reproduce

```sh
# draft + standalone masked test
tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800D4D30
# real-compiler raw compare (see tools/ or /tmp scripts)
SN_NGC_PATH=build/compilers/ProDG/3.9.3 build/tools/wibo \
  build/compilers/ProDG/3.9.3/ngccc.exe -O2 -G0 -mcpu=750 -fno-common \
  -I include -I build/G2TE52/include -DNDEBUG=1 -DVERSION_G2TE52 \
  -c src/wip/fn_800D4D30.c -o /tmp/x.o
```

Environment: decomp project of "Tony Hawk's Underground 2" (G2TE52),
PowerPC big-endian, ngccc 3.9.3 under wibo, DOL must stay byte-identical.

### 8007BDC8 (92B, 2 word diffs, words 4-5) - loop-preheader hoist-order flip

Distinct from the arg-setup members above: WANT hoists the loop-invariant
label-base `lis` to the START of the preheader, BEFORE the count init:

    WANT: lis r30, -0x7fd0 ; li r31, 0xa
    GOT:  li r31, 0xa      ; lis r30

The label (lbl_803009EC) is accessed inline in the loop body (ha/lo
displacement form `lwz r0, 0x9ec(r30)`, same as promoted sibling
fn_8005DC6C). 32 variants tried: loop forms (for/while/goto/while(1)+break),
count types (s32/u32/u8/register), typed extern (void*/void**/s32),
staged `void **head` (breaks -> lis+addi+0(r30), 19 diffs), absolute
address literal, pre/post decrement conditions, body reorders,
-fno-sched-spec/-fno-sched-interblock (both alone and paired). All keep GOT
order.

**RETRACTED 2026-09-28 — the order is NOT a fixed ngccc choice.** fn_800AB604
(520B, now EXACT) is the *same* symptom in two preheaders, and it gives the
rule this member was missing. The governing rule is:

> ngccc emits a preheader as **[the preheader block's OWN statements, in source
> order]** then **[the hoisted loop-invariants, in body order]**.

So to get a constant **before** the hoists it must not be a hoisted invariant
— it must be a statement of the preheader block:

1. **Turn a hoisted `li r,0` into an own-statement** by assigning it to a
   **named local as the preheader's FIRST statement** (`z = 0;` before the
   loop-base `addi`). This alone flips fn_800AB604's first preheader.
2. **Turn a hoisted `lis` page-anchor into an own-statement** with the
   documented 1-insn anchor (AGENTS §6u-3):
   `__asm__ volatile("lis %0,%1@ha" : "=r"(anc) : "s"(lbl_80301B48));`
   placed in the preheader, with the body reading
   `*(s32 *)((char *)anc + 0x1B48)` and `register s32 anc __asm__("r26")`.
   1/130 instructions of asm (0.8%).
3. Each extra preheader statement can steal a callee-saved slot, so re-check
   the prologue afterwards (`register s32 var_r30 __asm__("r30")` undid an
   r30/r31 swap in fn_800AB604; AGENTS §6a-6 / §70-130).

Related: doc-47 (in-body base ⇒ IV init placed after the hoists) is the
*mirror* of this rule — the base must go **in the body** when you want it
**after** the hoists, and in the **preheader** when you want it before.
fn_800AB604's dead ends, for the record: an affine/indexed in-body base (right
order, but strength-reduces to `0x2c58` + `lwzu`, 66–93%); a preheader
`char *pg = (char *)&lbl_80301B48` *used by the body* (⇒ `lis+addi` +
`lwz 0(reg)`, 57%); the same unused (⇒ DCE, 96.2%); one zero variable shared
by both loops (the zero webs overlap and loop 1's steals r26, 94.6%); a r31
pin on the walker (89.2%). 23 single flags + 3 pairs on the solved body: none
beats default. `docs/parkings/solved/47` is the adjacent solved doc.

### 800F4CC4 (140B, 3 word diffs, words 16-18) + 80215848 (84B, 2 word diffs)

800F4CC4: `fn_800F36C8(arg0..arg5)` arg-copy order - WANT copies the
low args `mr r4,r26; mr r5,r25` BEFORE `mr r3,r27` (the computed a0 =
arg0+*(s16*)(r9+0x70) stays in r27 and is copied last); GOT copies
r3,r4,r5 in order. Same shape as the documented 8002CA8C member
(li r4/li r5 before addi r3). Named-temp a0, named fn ptr, and
-fno-sched-spec/-fno-sched-interblock (alone and paired) all keep GOT.

80215848: `fn_80127684(temp_r29, 0x5AB23CC9, lbl+fn()-temp_r30)` - WANT
schedules `mr r3,r29` (arg1 copy) BETWEEN the arg3 `add r5,r5,r3` and the
final `subf r5,r30,r5`; GOT finishes subf before the mr. Named-temp v3
forces subf earlier (GOT); flags don't change it. Both resist every form.

## members confirmed (2026-08-23)

Four more drafts hit the same wall and are parked on it (all hand-rebuilt
to ground truth first, all other diffs closed):

| Address | Size | Best | Residual |
|---|---|---|---|
| fn_801410E0 | 668B | 98.2% (`// FLAG: -fno-schedule-insns2`) | prologue param-save order: WANT copies arg1/arg0 before the t-load lis pair; ngccc sinks the pinned-arg0 copy after it in every shape tried (pin init/two-step/+r & memory barriers/stmt order/5 flags) |
| fn_80141B08 | 192B | 95.8% | `lfs f1` / `lwz r3` sched swap at first fn_801812B8 site; staged temps, "+f" pin, mem barrier, 13 flag combos resist |
| fn_80143B7C | 280B | 94.3% | site-1 `lfs f1` fills the `lwz r9` delay slot instead of landing above `li r4/stw`; float-first proto (f32,s32,s32), store-as-arg2 fold, named-temp base, shared-zero var, volatile load, "=r" staging, 13 flag combos resist |
| fn_801414F0 | 128B | 93.8% | scaled-index scratch r11 vs WANT r0 for a struct-member stfsx; register-var pins + -fno-strength-reduce resist |

Also adjacent (same class, entry-block flavor): fn_801439C0
(59.7%) — WANT keeps `lis r25` (lbl @ha) before the first bl and `li
r28,0` inside the loop; ngccc hoists the zero pre-loop (+1 shift cascade).

## members confirmed (2026-08-23)

Three more drafts hit the same wall (script-command zone 0x80155E44+;
all hand-rebuilt to ground truth first, every other diff closed):

| Address | Size | Best | Residual |
|---|---|---|---|
| fn_80156220 | 128B | 93.8% | single 2-insn swap at 2nd call site (`li r6,0` vs `ori r4` completion); staged-ret form (`ret = fn(); f(sp8,spC,ret)`) flipped 44→93.8%; proto flips + schedule flags resist |
| fn_801587C8 | 128B | 93.8% | `li r6,0`/`li r4,0` emission-order swap at 3rd call site; all schedule flags, void↔s32 return flips (each + both), old-style protos, decl reorder, zero-staging resist |
| fn_801575E0 | 1444B | 98.9% | TWIN SetProp triples with OPPOSITE want orders — mr r3,r30-first at 0x80157A0C, li r5,0-first at 0x80157A80; got emits the inverse at both sites; per-site register pins, UID barriers, 40 decl permutations resist. Strongest evidence yet these are per-site expand_call artifacts, not source-reachable |

See AGENTS.md §6v-121 for the twin-site analysis.

## members confirmed (2026-08-23)

Script-wrapper batch (30/34 EXACT); three parks land here:

| Address | Size | Best | Residual |
|---|---|---|---|
| fn_8015BCB4 | 200B | 96% | **Proto tension (new)**: fn_80127684 called twice — `void` return fixes site A's `[mr r3,r30\|ori r4]` order, breaks site B (`lbz/lwz` swap); `s32` vice-versa. ~40-combo proto matrix + staging + pins + 9 flag configs + all five ProDG versions resist. Byte-twin fn_8015BB78 IS EXACT with the same callee (fresh-load args) |
| fn_8015B25C | 168B | 92.9% | at the fn_80128E34 call WANT emits `mr r3,r31` LAST; ngccc hoists it first from every shape tried (s32/void/void* protos × 4 flag combos) |
| fn_8015BA18 | 204B | 92.2% (`// FLAG: -fno-schedule-insns`) | twin-site opposite-order signature (recipe 121 class): site #2 wants `mr r5` before `li r4`, site #1 inverse; sp8 reload before `cmpw r3,r4` lands in r0/r9/r11 but never r4 (that lwz/cmpw pair occurs exactly once in .text) |

Related near-park fn_8015B698 (81.8% w/ `-fno-schedule-insns2`) is BOTH
doc-15 role-swap AND issue #28 CR-liveness — see there.

## members confirmed (2026-08-23)

Script-zone batch fn_80173C5C–fn_8017792C (13/24 EXACT); four parks land here:

| Address | Size | Best | Residual |
|---|---|---|---|
| fn_80173D30 | 864B | 99.1% | TWO 1-insn artifacts: (1) want `li r4,0` vs got `mr r4,r30` — the r30-pin fixing arg0/temp roles makes GCC copy the branch-proven-zero reg instead of rematerializing (pin side-effect, AGENTS.md §6y-125); (2) lis tie-break order at the fn_800A3778 callback cluster (want [lis r9][lis r4][lwz][addi], got cb-page first) |
| fn_8017503C | 380B | 95.8% | want splits [lis lbl][addi &sp-birth][addi lbl@l][li 0][mr r31,r11] and emits next-call arg-setup AFTER both stores; got emits birth-before-lis and sinks [mr r3,r29] between them. Two-web pointer prologue (§6s-1), pins, const staging, 6 flag combos all ≤95.8% |
| fn_80173C5C | 160B | 95% | entry-copy coin-flip: want `[lis][fmr f31,f3][lfs][mr r3,r4]` vs got mr-first. Mixed-ABI sig `(s32 unused, s32, f32, f32, f32)` verified; float pins cur→fr13/mn→fr12/step→fr0/farg2→fr31 correct; cond polarity NaN-safe `<=` (cror+bns) vs plain `>` both required — only the entry-copy order remains |
| fn_80175690 | ScriptChangeLevel, 724B | ~12% | whole-function callee-saved role rotation (also doc-32); want recomputes &fr.sp58 in-loop while ngccc hoists it into an 11th saved reg. Structurally complete (9-arg calls incl stack arg, chains, frame holes, two-web pointers) |


## addition (2026-08-23)

- fn_80184558 (96B, 62.5%): walk-loop ENTRY-block layout artifact — body and
  exit are byte-exact (after real protos, chained-r3 tail call, char*
  stride fix), but want duplicates the loop-head `mr r3,r31` with an
  entry-`b` bypass around it. Tried param reassignment, while/do-while/goto
  forms, assignment-in-condition, r4/r9/r0 pins, "=r" wedge, "+r" staging
  (got body exact; entry layout still resisted), schedule flags.

## update — register-role-swap members CRACKABLE via pin-a-copy (2026-08-23)

**Status update: the r29/r30-style saved-reg swap class is no longer a pure
coin-flip.** Pinning a COPY of the param to the exact callee-saved reg WANT
homes it in forces both the prologue `mr` order AND the body restores:

```c
register s32 a0 __asm__("r29");   /* the reg WANT uses */
a0 = arg0;                        /* a COPY — never pin the call result you pass on */
/* ... body uses a0 ... */
```

Cleared byte-exact this round: fn_80188FEC ScriptGoalManager_HasGoalPoints
(80B, previously cited in AGENTS.md §6a-6 as an unfixable straggler) and
fn_80188F98 SpendGoalPoints (verbatim same fix). AGENTS.md §6a-6 has been
rewritten accordingly.

Retry hint superseded: declaration-order permutation and the flags ladder
(above) are now SECONDARY levers for register-role-swap members — try
pin-a-copy FIRST. Full-web variants apply when allocation rotates: pin every
value explicitly (partial pins ROTATE the remaining assignment order), and
reassigning the SAME pinned variable to its next role models WANT's register
recycling (§70-130). Still-unfixed role swaps where the value is NOT a
param copy (e.g. born-late webs, call results that must pass onward) may
genuinely resist — pins are live-from-entry and cannot model those.

## update — nine new members (2026-08-23, script zone 0x8015Cxxx–0x80161xxx)

All verified parked with best-match bodies in src/wip/ (see
AGENTS.md §6y). Signatures observed this round:

| fn | % | signature |
|---|---|---|
| fn_8015D6B0 | 94.6 | single `stw spC` vs `mr r3,r31` swap; 12 flag configs, comma-folds, proto flips, r3-clobber barrier resist |
| fn_8015F308 | 89.2 | twin-call-site artifact (§6v-121): want copies r3→r30 before cmpwi in ONE structurally-identical arm and chains bare r3 in the other |
| fn_8015F670 | 96.2 (98.5 w/ -fno-schedule-insns) | pinned-reg home-copy `mr r30,r3` sinks below next statement's constant `lis`; "+r" barriers fix position but break raw-r3 passthrough at call 1 |
| fn_801603C0 | 93.5 | want orders pre-call loads [global; spC], every C form emits [spC; global]; -fno-schedule-insns fixes order but swaps @ha anchor regs |
| fn_801609DC | ~69 | &spN address-web CSE variant (same class as fn_80151228/fn_8013157C §6t-7); GCC hoists one addi into r26 web, cascade shifts every home. Array lvalue shapes + anti-CSE flags tested, resist |
| fn_80161274 / fn_80161354 | 96.4 / 96.1 | 2-insn transposition of two independent address computes (`addi r11,symbol` vs `addi r3,&msg`); register pins r3/r4/r11/r24/r25/r30, asm barriers, full schedule-flag matrix resist |
| fn_80161420 | 94.9 (92.3 flagless) | same transposition; `-fno-schedule-insns2` is the best single flag (kept as header FLAG) |
| fn_8015D4E4 | ~26 | NOT arg-order: LICM hoists four single-use loop constants into saved regs while retail rematerializes lis/ori-in-r0 per site — new adjacent root cause (AGENTS.md §6y-126), listed here because it masquerades as one |

Retry hints for this crop: pin-a-copy FIRST for role swaps (per the
 section above) was tried and over-constrains on the
address-compute transposition members (pins are live-from-entry; the two
adds are born mid-block). The [global; spC] load-order member is the
cleanest repro target if a future emission-order lever appears.

## members confirmed (2026-08-23, ScriptTODManager zone 0x8016Exxx–0x80173xxx)

| fn | % | signature |
|---|---|---|
| fn_80173910 | 98.0 | page-anchor init placement: want hoists `lis r28,lbl_80305EB8@ha` ABOVE `bl fn_80019D08`; ngccc always sinks it post-call. Register-pin to r28 fixes lis position but shifts arg homes + breaks displaced-load form (76%); extern decl forms and 7 flag configs resist; all five ProDG versions identical |
| fn_80172A90 | 93.6 (w/ -fno-schedule-insns) | sched1 interleave: GCC floats the {4330-lis, dbl-anchor, div-anchor, f2v-pair} web around two int→float cvt stores in a different order than want; ~6 pin/asm-split/barrier reshuffles each fix some slots and break others |
| fn_80170444 | 72.9 (w/ -fno-branch-count-reg -fno-schedule-insns2) | arg1's saved-reg home is time-shared with a pinned pointer web after its last use; every pin/decl-order variant over-constrains; call-arg moves also hoist above staged copy blocks |

Note fn_80173910 is the cleanest repro of the class if an emission-order
lever for pre-call address materialization ever appears — everything else
in it is EXACT.

## members confirmed (2026-08-24, memcard script zone 0x801687D0+)

| fn | match % | remaining diff |
|---|---|---|
| fn_801689C8 | 98.1 (362/369) | two emission-order artifacts: sum constant-fold target (`addi r0,r25` vs want `addi r0,r22`) + mode-load/store interleave at buf-header stores; 8 source shapes × 4 flags resist. NOTE: its long-range CR machinery (doc 28) fell out of plain C for free |
| fn_80169F04 | 97.5 (79/81) | one arg-setup swap at the 2nd fn_80127684 call (`[ori]` vs want `[mr r5,r26]`); hidden arg0 passthrough + chained fn_80165E58 arg0 + volatile-asm sandwich around `t30 += 0x2C54` all landed; this last swap resists |
| fn_8016D52C | 95.6 | pre-call window: `mr r3,r29` hoist position + `li r28`/`mr r25` pair order; 3 statement orders × 5 flag combos resist. All 9 saved-reg homes pinned to want's exact r23–r31 map |
| fn_80169CE4 | 93.8 (1 word) | want interleaves `li r4,0` between staged `mr r0,r3` copy and sp10 store; ~15 shapes + all sched flags resist |
| fn_80169E00 | 93.5 (29/31) | single swap of independent `{li r3,call-arg}` vs `{stw}` before bl |
| fn_80169D64 | 89.7 | same interleave ×2 (top-of-fn `li r3,0`/store swap + CE4 pattern); frame via 16B struct + triple reg homing + volatile-struct dead stores landed |
| fn_80169E7C | 88.2 (30/34) | prologue scheduler swaps — `{addi p1 ↔ addi p2}` emission order; decl-order pins collapse webs |
| fn_8016D930 | 78.0 | ngccc births the arg0+0x160 walker PRE-if vs want's post-if scratch+`mr` homing pair; u32 switch tree/indexed addressing/zero-store chain otherwise exact |
| fn_8016E0D8 | 22.2 | saved-reg HOME swap: want arg0→r31/result→r29, ngccc insists result→r31; 15+ shapes incl. register pins resist (allocator tie-break) |
| fn_801695A0 | ~25 | wholesale register-role rotation across 17 callee-saved regs (doc-15 at full scale); decl permutations/web splits/pins/flags shift but never converge |

Zone signature ground truth harvested alongside (use before prototyping here):
fn_8012701C AND fn_80172858 are **2-arg `(s32 value, s32 flag)`** with the value
staying live in r3 across the guard compare (m2c passes a literal only);
fn_80015870 is **1-arg** (m2c invents a phantom 0x80290000); fn_80015A58 is
**3-arg** with arg0 chained from fn_80015870's return; fn_80015B94 1-arg;
fn_800158D8 0-arg; fn_8013157C **10-arg** (args 9/10 in CALLER stack r1+8/r1+0xC).

## addition (2026-08-23)

- fn_80186DF8 (248B, 96.8%): single entry-ordering artifact — want emits
  `lis r9,lbl@ha` BEFORE arg0's home copy `mr r28,r3`; every compile puts
  mr first because param homes insert at entry top. Required+best flags:
  `-fno-strength-reduce -fno-schedule-insns2`; adding insns/spec/interblock/
  regmove/gcse/expensive-opt/delayed-branch/thread-jumps/cse-follow-jumps/
  function-cse gained nothing or regressed. r30 pin fixed the r30/r31 role
  swap; split staging temps fixed word-5; separate loop-count var fixed
  scratch-clamp homing — only the lis/mr order remains.
- fn_80187C14 (1240B, ~60%): mixed doc-15 arg-scheduling + doc-28 residue
  after a full hand rebuild (12% → 60%); state-machine gotos, per-arm
  manager vars, page-anchor pin and third-object split all applied — see
  the file's PARKED block for the remaining site list.

## members confirmed (2026-08-24)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_80161A00 | 192B | 95.8% | last store pair want `[stb f10; sth f2]` vs got rotate `[sth; stb]`; source swap collapses regalloc + DCEs the sth; volatile lvalues, memory barrier, comma-in-call-arg resist |
| fn_80161F24 | 184B | 95.7% | want `li r31,0` sits between arg setup and bl#1; ngccc sinks it past the bl from every form (r30/r31 role swap itself fixed by a0 pin; pins both ways, comma-in-arg staging, "+r"/volatile barriers, decl moves, 8 flag configs resist) |
| fn_80162CB4 | 280B | 91.4% (`// FLAG: -fno-schedule-insns`) | expand_call permutation want `[ori; li r6; mr r3]` vs got `[mr r3; ori; li r6]` around one captured-result call — result is consumed so the M8.31 return-type flip is unavailable |
| fn_801628FC | 456B | 86.8% | const binding inverted (want binds the 0x80-page const to r9 and 0 to r0, got the inverse) + pb birth direction (`addi r5;mr` vs home-first) + final-call arg-load rotation; inline-& CSE rematerializes instead of preserving |

## members (2026-08-24, skater-state zone 0x80177D1C–0x8017EBFC)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_8017DD54 | 716B | 98.9% | prologue save-order coin-flip: want `mr r29,r4` BEFORE `mr r28,r3`, ngccc emits the opposite from every shape; resists 15+ flag combos, param decl-inits, register pins, asm clobbers. Frame/aliasing otherwise exact (`arr[count++]` postincrement fix landed) |
| fn_80178888 / fn_80178520 | 308B / 460B | 97.4% / 93.0% (`-fno-gcse`) | twin residual: one `li r0,0` ↔ copy-prop `mr r24,r11` swap; frame-template struct + iter pin + two-web "+r" barrier landed on both |
| fn_8017A3F8 | 192B | 93.8% | want interleaves `extsb r4,r0` between cmpwi/bne and keeps plain `li r5,0` where ngccc emits branch-proven `mr r5,r9`; loop shape cracked via literal goto-blocks + r9 walker pin + untied wedge |
| fn_8017B444 | 936B | 91.1% (`-mps-float`) | &sp8[0] computed EARLY in want, &sp8[2] LATE; ngccc emits the inverse from every named-ptr/array/barrier/proto-permutation shape (expand_call artifact, same class as §6t twins) |
| fn_8017AC00 | 1172B | 44.0% | head-block interleave + per-branch msg-store order; frame-template layout exact, full pin set applied |
| fn_8017C1A8 | 292B | 20.0% | want materializes a const into r30 with DIRECT stw + xor temps in r0; every pin/permutation shifts the allocation elsewhere; zero callers/data refs in retail (lowest retry priority) |
| fn_8017981C | 3036B | 6.7% (flags) | instruction COUNT matches exactly under `-fno-schedule-insns -fno-schedule-insns2` but saved-reg homes {msgType:r30, arg18:r31, obj:r29} unreachable; resisted decl order/type, CSE chains, u32/s32 pins, all 5 ProDG versions. DIAGNOSTIC worth reusing: matching counts ⇒ pure home-assignment park |
| fn_8017E6A4 | 1288B | 5.3% | FPR-web variant: want keeps call results in scratch f1/f0 across branch merges; ngccc forces fmr copies/stack slots; ~10 dead anchor-copy `mr`s are want-extra dead insns (§6x-89 dead-code asymmetry) |

Zone note: several EXACTs needed the §6y-130 switch-tree
tail-duplication shape and §6y-132 dead-code-callee arity rule — check those
before treating arg-setup swaps here as callee-signature problems.

## update — pin-a-copy confirmed on home turf; two new members (2026-08-23)

The doc-15 pin-a-copy lever was independently re-proven in its
source zone on fn_8018AF70/fn_8018B098/fn_8018D120 (EXACT; D120 needed
full-web pinning PLUS same-variable reassignment through the call chain,
see AGENTS.md §6z-130). Limits mapped:

| fn | % | signature |
|---|---|---|
| fn_8018CC18 | 94.5 | NINE-reg full-web pinning (wp r4, arg0 r25, &st-home r26, sent-pin r27, head r28, horse r29, anchor r24, t30 r30, sentinel→node recycling); two 2-insn transpositions remain, all flags/reorders resist |
| fn_8018BC14 | ~70 | want SINKS the getter result-save below an independent entry load ([bl][lwz][mr]); got always save-first. The BD34-template fix (load coalescing onto dying arg0 home) is impossible here because arg0 stays live across the body — needs a post-bl save-delay / soft anti-coalescing lever GCC doesn't expose |

Note also fn_8018BC9C (97.4%) is NOT this doc: single rotated-loop entry
test `or. r9,r9,r9` vs `cmpwi r9,0` = M4.18 pattern-10 unparkable class.

## members (2026-08-24, entity/iterator zone 0x801A867C–0x801ACF84)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_801AA158 | 380B | 97.9% | single 2-insn schedule tie (`mr r4,r29` vs chase-load swap) in an otherwise byte-exact body incl. FPR frame, staged floats, asm @ha anchor pinned r11/r10 |
| fn_801AACA4 | 496B | 92.7% | prologue mr-pair swap + `fn_80060490` arg-setup interleave; chained 3-arg fn_801277E4, vcall passthrough arg2, 9th stack arg, string-lbl forms and a 576-combo staged-float permutation search all landed first |
| fn_801A9388 | 168B | 92.9% | final increment/call window: want loads `lwz r4` 2 slots later than ngccc from every shape; resists 7 increment shapes + staged temps + barriers + 4 flag configs |
| fn_801A8E5C | 892B | 37.7% | prologue register-home shifts (arg1→r18 vs r20, arg3→r21 vs r23), count-web split (`mr r29,r5`+`mr r26,r29`) stealing a saved reg, store interleaves around both memcpys; volatile f1C/f828 readback REQUIRED for the lwz+slwi reload pairs (§6z-143); full resist list in header |
| fn_801AB08C | 3364B | 17.2% (-mps-float) | full disasm rebuild from statics-DCE stub (frame 0x140 exact, entry-store permutations, bool RMW blocks, element-wise __ps_t copies); wall = saved-reg home assignment (arg2=r24/entry=r31/bool=r29/&A=r22/&rot=r23) resisting full-web pins, 2-pin configs, file-scope register vars, "+r" barriers; diagonal A[i][i] fuses to mulli×20 vs want's dual-slwi |

Note: fn_801A8A6C (876B, 6.8%) is a doc-28 CR member (mfcr r30/mtcrf 0x80
mid-function around cr0; ngccc parks the test in callee-saved cr4 shifting
all GPR roles).

## members confirmed (2026-08-24, goal-manager zone 0x80196xxx+)

| fn | match % | remaining diff |
|---|---|---|
| fn_80197DB8 | 78.2 (NEAR) | 27 words: ProDG left-to-right arg-eval vs ngccc right-to-left sink across the fn_80128228 call block; slots/regalloc/recycling all correct after volatile inline mgr loads killed CSE caching |
| fn_801996BC | 61.6 (NEAR) | two-phase checker fully rebuilt; residual = prologue micro-weave + GCC placing ret1 tail-blocks AFTER the walk phase where WANT keeps them between (linear block order) |
| fn_801979CC | 40.8 (DIFF) | body fully reconstructed (chained allocs, union-slot float dance w/ inline-asm fctiwz reuse, 10-arg call); ProDG interleaves hash/entry setup INSIDE cvt stores + keeps a dead `mr r5,r9` (recipe-89 residue) |
| fn_80196EF8 | ~11 (DIFF, 2.7KB hand-rebuilt, ~45 call sites audited) | regalloc/scheduling only: f31-hoist vs frsp-caching tradeoff, saved-reg role rotation across r14–r31 web, cr4 `(created1 != NULL)` cache live across UI blocks 1–3 (mfcr/mtcrf), zero-reg choices — see also doc 28 |

## members confirmed (2026-08-24)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_801A2584 | 96B | 54.2% | got emits `mr r9,r4` (switch-index copy) + hoists `mr r4,r5` (next call's arg setup) ABOVE the compare tree; want compares r4 in place with the mr inside case A. Switch/if-chain/goto/ternary-comma, u32 index, const-first operands, void↔s32 flips, full sched-flag matrix resist |
| fn_801A4B88 | 224B | ~40% | want hops EVERY call result through scratch r0 before homing (`[bl][mr r0,r3][lis][mr r30,r0]`, both fn_80129C08 sites, results feed 2-3 consumers); GCC consumes directly in every shape. Retry hint: sibling with multi-consumer result webs. Resisted compound +=, comma staging, decl-init, web splits, pins, sched flags, all five ProDG versions |
| fn_801A3E4C | 1620B | 48.9% | GPR save window: want `stmw r27` (5 regs) vs every shape 7 (r27-r30 pins make GCC burn r25/r26 as dance scratch; without pins two webs split); dance store order want `[lo][hi]` vs got `[hi][lo]` across 3 orders + clobbers; block-B/F hash results f31/f30 swapped (call-result frN pins ignored, AGENTS.md §6ae-9). Semantics fully reconstructed incl. f32 return + chained calls |

## members (2026-08-24, zone 0x8019D2E0-0x801A1BAC)

19/39 EXACT this batch; the parks landing here:

| Address | Best | Residual |
|---|---|---|
| fn_8019DB68 | 97.9% | single 2-insn transposition in the lbl_80305EEC counter block (want mask-before-inc-store); 5 flags + 7 shapes + pin + memory clobber + staging resisted |
| fn_801A1150 | 87.5% (`-fno-schedule-insns`) | else-arm float arg-load order: want subtrahend lbl->f1 BEFORE dup const->f2 + fsubs-before-fmr; ngccc loads arg2's const first + fmr-first; prologue/stores/path-A byte-exact |
| fn_8019E770 | 83.8% | 6x fn_80139510 sites emit r3-setup FIRST vs want LAST (3 proto flips, 6 flag combos, volatile reloads, ptr-scaling, all five ProDG versions byte-identical) + 1 dest-in-rA add canonicalization swap |
| fn_801A1998 | 83.1% | anchor regs want r11/r10 vs got r9/r11 + [addi r9]/store-triple placement around call #1; pins fixed pointer webs (+32%) | (stale 2026-10-09: 87.7% via const-float §7n, still parked) |
| fn_8019E194 | 78.7% | loop body byte-exact incl mulli 0x94 stride; pairwise swaps in [prologue..first bl] resist all |
| fn_801A11D0 / fn_801A1AAC / fn_801A1B2C | 65-69% | r9-recycle mid-float-setup store placement; staged float temps add fmr copies vs direct arg loads; zero-store+mr hoisting — see files | (stale 2026-10-09: fn_801A1B2C promoted via const-float §7n; the other two still parked) |

Mixed doc-15/doc-28 residue: fn_8019EB40 (62.4%), fn_801A0824 (50.4%),
fn_801A058C (52%), fn_801A0A28 (26%), fn_8019D62C (19.7%).

## members (2026-08-24, script-wrapper zone II 0x801B6004–0x801BB4A0)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_801B6EB8 | 144B | 86.1% | two rodata anchor `lis` interleave with their lfd/lfs loads; volatile-union dance + lis asm wedge made the int→float dance byte-exact otherwise |
| fn_801B8DE0 | 672B | 41.0% (-mps-float) | want's live-range-SPLIT `&buf` web: scratch-r11 birth pre-call + saved-r30 home at exactly 2 post-call sites; ~9 shapes incl. pins/wedges/barriers resist |
| fn_801B7A90 | 496B | 35.4% (-mps-float -fno-schedule-insns2) | call-result homed r23 vs want r31 (pin kills the fused or. copy-test); obuf +8 slot gap; per-site lha/lbz order |
| fn_801B6A60 | 1112B | 15.0% (-mps-float) | big-function allocator wall: want stmw r18–r31 + exact FPR roles/frame 0x150 vs ngccc's r15-base set; insn sequence ~1:1, __builtin_ps_madds0 chains correct |
| fn_801B7484 | 1476B | 6.0% (-mps-float) | f29/f30/f31 const caching across bl + frame −0x40; structure complete (entry bdnz$ spin via solved doc-30 recipe, branchy mag guards, rsqrte splits) |

Zone note: fn_801B608C/61B0 cracked the int→float-dance INTERLEAVE wall with
volatile cvt halves + "+f" barriers (§6aa-146) — try that before parking any
sinf/cosf-series twin on "scheduler" grounds.

## members confirmed (2026-08-25)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_801FDE4C | 284B | ~80% (-mps-float) | PS tail fully decoded + byte-matched (ps_mul/madd/sum0/rsqrte/muls0); residual = ctx-copy (`mr r3,r30`) placement at 4 identical call sites + one psq_l/st spill swap; flags, barriers, pins, recycling, proto flips resist |
| fn_801FDC38 | 336B | ~51% | dispatch layout cracked via if-chain+goto (switch can't give want's test-order≠body-order); residual = lfs-const sunk vs want's mid-psq position |
| fn_801FF1D4 | 568B | 54.2% | everything through the 2nd hash gate byte-matches; walls = per-arm @ha anchor duplication (want rematerializes, GCC CSEs) + `fmr f12,f0` copy-back after product (self-assign folds in-place; fr12 pin computes INTO f12) |
| fn_80201CCC | 428B | DIFF (~90% mnemonic-aligned) | want rematerializes compare constant B67CFF14 inline per iteration where GCC hoists all 3 to saved regs → want's 12-web `stmw r20` span never reached (every shape lands 13 = stmw r19) with cascading role shifts; all 6 case-order permutations tested |
| fn_801FE6F0 / fn_802001BC / fn_80201B6C | 164-164B | ~48.8% trio | want recycles tbl's r11 for the ext word (got reuses dead idx-r0) and two-steps the method ptr (`lwz r12; mr r9`) vs got's direct load (4B shorter → cascade). Same signature as fn_801D0BCC. ~10 shapes resisted incl. 8-byte struct-copy REC form |

## members (2026-08-25, 0x801F34F4–0x801F6684)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_801F4858 | 616B | 90.9% | rotate-right emission order of each arm's independent run around the duplicated tail compare; `volatile` union slot at `r1+8` + `+dummy`/`+f` barriers landed → proven framing fix, residual is scheduling |
| fn_801F50B0 | 216B | 96.3% | **improved `50/54 → 52/54`** via `M8.31` + `r27/r28` pins; lone `li r27,0` vs `bl` transposition remains — classic `doc-15` entry (now at the scheduling-order ceiling) |
| fn_801F5374 | 320B | 40.0% | retail splits `i`/`next_i` into two saved-reg webs `r29/r31`; every C shape coalesces them — whole map shifts |
| fn_801F56F0 | 124B | 22.6% | `stmw r30` vs `stw r31` + page-anchor `lis` choice; 10 `lbl` forms resist |
| fn_801F5A0C | 152B | 94.7% | `mcrf`/`li` order swap — scheduler artifact, 6 permutations + `-fno-sched*` + `__asm__` barriers all keep `li` before `mcrf` |
| fn_801F3D30 | 1016B | 48.2% -> 55.5% | switch tree NOW MATCHES (stale note; value-canonical). Fixed: single-counter loops (stmw r25->r26), u8 field reads @0x336, lbl_802AE2D4 fmt string (HA/LO pair, lis hoisted). Residual: arg1 in r26 vs r27 + per-site mr/addi CSE coins. Retail's crclr cr1eq before fn_80269F4C hints the original call was implicit/variadic |
| fn_801F5CC0 | 304B | 13.2% | PS-normalize `ps_sub/mul/merge00/madd/sum0/rsqrte/res` all emittable — residual is preamble hash-`lis` interleave, not PS wall |

## members confirmed (2026-08-25)

| fn | % | signature |
|---|---|---|
| fn_801903B8 | 98.6 | single 2-word swap at first call: want orders `lis r4` (hash-hi) BEFORE the field load; staging/reorder/flags all score worse |
| fn_8018DFE0 | 67.0 (w/ -fno-schedule-insns) | t27/count saved-reg role swap (want r27=chain-result/r28=count; ngccc exact reverse) + &spC cache placement inside loop1 vs hoisted |
| fn_801F23F0 | 93.1 | single r29-r30 role rotation between page-anchor web and list-handle web birth order; every anchor-ordering route const-propagates or rotates other roles |
| fn_801F21A8 | 23.4 (-mps-float) | PS pair-copy wrapper: prologue store span + K-load position + f13-vs-f0 pair-move colors resist pins/wedges/permutations |

Also catalogued adjacent walls: dual-base-web sequential same-reg reuse
(fn_801F2AE0 @87.8%, sibling of parked fn_801F4C88 — see §6al-183's wedge
for the cracked half).

## members confirmed (2026-08-25)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_80221C00 | 180B | 97.8% | ONE residual word: advance-call arg1 emits `mr r4,r30` vs want's fresh `addi r4,r1,8` — CSE park class (per-site forms, char* cast, "+r" split, pins resist). Rest byte-exact incl. 1-arg fn_80219698 + loop-head "m" pad frame |
| fn_80221930 | 332B | 84.3% | flat 4-arm hash chain (else-if ≡ goto ≡ ternary ≡ nested — layout insensitive); want keeps cell web in r9 w/ clrlwi-from-reg + b55c AFTER stores; got picks r0 + lbz reload; r9 pin perturbs allocation (61%), split-stmt forms fuse rlwimi or sink b55c |
| fn_8022053C | 260B | 55.4% | structure verified (msg@8 w/ embedded out-ptr to {arg2,arg1}@0x40, search_t ctx@0x30); residual = want's two-web ctx (birth→d454, home→d4e8-only) + mixed displacement/birth stores; every wedge/per-site form collapses allocation further |
| fn_802206AC / fn_802209C4 | 384B | 94.8% twins | prologue scheduler interleave only: recurring 5-word residue `[const-pg lis][mr r30][const-lo ori][&slot addi]` = entry-param-home copy before the const pair where want has it inside. Dropping the over-constraining lblc→r25 pin gained +4.2%; statement perms/anchor sandwiches/flags resist. fn_8022082C same family at 77.5% (+ pay-store encoding) |

## update — two new members (2026-08-25, skater script-state zone)

| fn | % | signature |
|---|---|---|
| fn_8023E33C | 83 | want [lbz byte→r9][cmpwi][lhz→r11] holds BOTH loads in regs across stores + mid-block extsb + arg2 homed r10; got loads hword first, sinks byte load into arg setup, arg2→r11. Staging, pins, barriers, 7 flag configs resist |
| fn_8023DE60 | 70.9 | LRA birth-direction variant: want births `&fr.buf` INTO the call-arg reg then home-copies mid-setup (`[addi r3][mr r29,r3]`), reuses that cache for site #2 but takes a FRESH addi at site #1 — one value web split two ways standalone C cannot express (inlined-TU smell); plus fn_80240B0C li-window slot + frame +8 |

Zone note: sibling EXACTs fn_8023D788/D848/D990 fell to `-fno-expensive-
optimizations` + M8.31 flip together (AGENTS.md §6ao-165) — try that pair
on any member whose GOT homes an `&spN` web in a saved reg where WANT has
fresh `addi rX,r1,K` per site.

## members (2026-08-25, Script*-command zone 0x80222660–0x802273FC)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_802241F0 | 584B | 96.6% | ctx template + out78:r29 pin + chained A4B88(74AB8(...)) + volatile cnt50 landed; residual = 2 doc-15 transpositions |
| fn_802245A4 | 304B | 96.1% | 3 scratch-color words (r0/r4 vs want r11/r0) at walker sites; double-pin + asm-mr wedge + shared-tail gotos cracked structure |
| fn_80223FA0 | 592B | 92.6% | arg-setup transpositions at BF0/strncpy/DEE0#2 + else-store interleave |
| fn_802266AC | 472B | 93.2% | doc-15 expand_call interleave on the 9-arg fn_8021FAB4 tail; everything else matched incl. stack arg |
| fn_802227E0 / fn_80224BB4 | 184B / 308B | 87.0% / 87.0% | [li r4,0][mr r3,r28] swaps; BB4 caps at EXACTLY 87.0% across full-web pins, -fno-gcse, -fno-rerun-cse-after-loop |
| fn_802268C0 | 1352B | 56.2% | E70/E84-site ties; recycled pinned-r30 across all retail roles landed |
| fn_802273FC | 352B | 43.2% (SIZE-MM −20B) | rlwinm store-forward dance on slot halfword pair |

Zone note: fn_80225E70 exposed a NEW hazard — QB_* macros can diverge from
bare hash literals under hard-reg pin contexts (AGENTS.md §6ar-222); if a
hash site resists, swap the macro back to the bare literal.

## members (2026-08-26, skater-physics PS zone 0x8020CDF0–0x802159C4)

| Function | Size | Final % | Notes |
|---|---|---|---|
| fn_8021546C | 656B | 96.3% (-mps-float) | genuine switch(1/2/3) + chained fn_801282E0(fn_80125954()) pairs + vtable dispatch + staged division temps all match; single residue ×3: call-result home copy `mr r30,r3` schedules AFTER the independent `lis QB_SPEED` constant where want has it BEFORE. `"+r"` barrier collapses the whole allocation (→25%); staging/flags/decl perms resist |
| fn_802159C4 | 264B | 87.9% | hash if/else-if chain + CC038 f32-const arg + own-arg passthrough final call all match; residue ×2 = `[lis page][li K][lfs const][stw]` interleave — got swaps the lfs/stw slots vs want at two of three sites; comma-in-arg placement + sched flags resisted |

Zone context: both are -mps-float drafts whose everything-else is byte-exact;
see AGENTS.md §6at for the batch's zone template (fn_80125954/fn_801282E0
chained pairs) and §6at-4 for a recipe that un-parked one earlier regalloc
draft in this zone.

## fn_801270B4 — loop-bottom test-source binding (merged 2026-08-26 from the former standalone doc "17-loop-bottom-test-register-coalesce")

Parked at 97.0% (132B — one word diff). A singly-linked-list unlink (head at
`arg0+0x4`, `key` at `node+0x4`, `next` at `node+0xC`); AGENTS.md M8.16/M8.33
classify it "genuine doc-15". Every structural/type variant tried compiles to
the same 1-word diff: the do-while loop-bottom condition tests the *copy
destination* register instead of the *fresh load* register.

### The problem

At addresses 0x80127118 through 0x80127120 the loop bottom first advances the walker by copying r30 into r31, then retail tests the fresh load register r30 against zero while the compiler build instead tests the copy-destination register r31, before branching back on non-zero. Only that one word differs.

Only w26 differs. The source is the standard guarded do-while:

```c
var_r31 = *(s32 *)((char *)arg0 + 0x4);
var_r28 = NULL;
if (var_r31 != NULL) {
    do {
        temp_r30 = *(s32 *)((char *)var_r31 + 0xC);   // fresh load
        if (*(s32 *)((char *)var_r31 + 0x4) == arg1) {
            if (var_r28 != NULL) *(s32 *)((char *)var_r28 + 0xC) = temp_r30;
            else                 *(s32 *)((char *)arg0 + 0x4)   = temp_r30;
            fn_801266EC(var_r31);
            fn_80117E28(var_r31);
        } else {
            var_r28 = var_r31;
        }
        var_r31 = temp_r30;                    // copy
    } while (temp_r30 != NULL);                // condition reads temp_r30
}
```

### What was tried (all 1 diff — never 0)

- **Loop forms:** guarded do-while (baseline), plain `while`, `for(;;)+break`,
  goto-form, `while(1)`+break. The plain-while/cond-on-loopvar forms
  RESTRUCTURE (14 diffs) — MWCC merges the entry guard `if (var_r31 != NULL)`
  with the loop condition when both test the same variable, so the guard must
  stay on a *different* variable than the condition (do-while with
  cond-on-temp is the only shape that preserves WANT's layout).
- **Condition expressions:** `temp_r30 != NULL`, bare `temp_r30`, `!= 0`,
  `&& 1`, `(var_r31 = temp_r30) != NULL`, dual `var_r31 != NULL && temp_r30`.
- **Types:** `void*`, `s32`, `void**` deref, struct-typed node
  (`Node { +0x0 pad, +0x4 key, +0x8 pad, +0xC next }`), pointer-cast head
  field, early-advance-in-body, cast on the advance copy.
- **Callee args (doc-10 recipe):** both callees verified 1-arg in WANT
  (`mr r3, r31; bl 0x801266ec` / `bl 0x80117e28`) — no missing-arg trick.
- **Flags:** schedule-flag matrix failed per AGENTS.md §5p ("15 C variants +
  flags all fail"). NOT yet tried: `-O4p`/`-O4s` via per-object
  `extra_cflags` (the mechanism is documented in AGENTS.md M6.11).

### Analysis

MWCC copy-coalesces `var_r31 = temp_r30` (the `mr r31, r30` at the join),
then binds the condition's read of `temp_r30` to the copy destination r31
(the register live across the back edge, used at the loop head). To emit
`cmpwi r30, 0` WANT's source must keep `temp_r30`'s value alive in r30 at the
bottom test — i.e. a use of `temp_r30` between the copy and the condition
that the allocator binds to the source register. No C formulation found so
far produces that. Register map elsewhere is identical (r29=arg0, r27=arg1,
r28=prev, r31=cur, r30=next), so it is *not* a global allocation swap —
it is literally the last test instruction's source register.

### Revisit ideas

> **Cross-clone note (2026-08, plan Items E/G):** the register-role/temp
> test-source class (same family as AGENTS.md M8.37 doc-10 role swaps,
> 8000E104/801A4F84/80055134) stayed locked in Sims2 as well - their
> register-coloring catalog cracked this-alias and this-arg choices via
> var-declaration-order (first local -> r31, second -> r30...) and
> volatile-store pinning, but NOT the loop-bottom test-source binding.
> (The var-declaration-order recipe was tried repo-wide 2026-08-23 and
> retired — see the crashwoc note below; park as structural.)
>
> **crashwoc update (2026-08):**
> automation for that recipe was proposed but never built — and is now
> retired before birth: decl-permute was tried 2026-08-23 (720 perms,
> zero effect on m2c bodies; README item 10). Do NOT re-try decl order
> on the M8.37 parks named here (8000E104/801A4F84/80055134).

- Check the debug-map/symbols for a named loop variable that might hint at
  the original field/struct layout.
- Compare with promoted twin list-unlinks (fn_8003A46C style: they test the
  loop var; this one tests the temp — find a promoted example that tests the
  temp and copy its exact idiom).

**Draft status note (2026-08-26 audit):** the wip draft
(`src/wip/fn_801270B4.c`) was removed in commit b7cf86e9 during a src/wip
cleanup; the function remains unmatched auto-asm. Regenerate the draft
(`tools/fill_wip_drafts.py --addr 0x801270B4 --force` or hand-rebuild per the
source above) before retrying any lever.

## members confirmed (2026-08-26, network/lobby zone 0x8022xxxx)

| fn | % | signature |
|---|---|---|
| fn_80229A70 | 96.6 | prologue `[ori][mr r3,r30][stw]` vs got `[ori][stw][mr]` — expand_call arg-move vs independent-store tie; both statement orders, "+r" barriers, sched flags singles+pairs resist; RMW-first variant scores 93.2% (aliasing sinks load). Phantom empty `case 0:` DID steer the compare tree ✓ |
| fn_8022A21C | 90.2 | TWO sched2 slot-fill windows: (a) prologue want interleaves `[lis r4][mr r26,r11][addi r4@l]`, homing copy emits 3 slots early; (b) branch-A splits `[lis r3][li r4][ori r3]` mid-window vs sunk ori completion. ~12 shapes incl. anchor sandwich + `-fno-schedule-insns2` (worse) | (update 2026-10-09: window (b) SOLVED by `extern const s32` on lbl_80305F9C — now 95.5%, want_got confirms the lis/li/ori/li run matches; window (a) remains, draft carries const) |
| fn_80229770 / fn_802297C0 | 90.0 / 47.6 | fused `or. r0,r3,r3` + shadow-li after call vs `[mr][cmpwi]` (+1 insn) combine-pass ordering wall; ~25 shapes/flags on the twins |

Also cracked this round via pin-to-ARG-register blocks emitting each
lis/ori/mr/li manually in want's interleave order: fn_8022A510 EXACT
(§6az-241) — a NEW lever against doc-15 windows where expand_call batching
resists statement reordering.

## 2026-08-31 — fn_80169E00 / fn_80169E7C no-barrier negative

Tested removing the draft `__asm__("" : : "r"(p1), "r"(p2))` barrier on both
twins (mirroring the fn_80178888 promotion recipe, where a `+r` barrier was the
CAUSE of a li/mr swap). Here the barrier is NOT the cause: the no-barrier build
keeps the same real residual (`{addi p1 ↔ addi p2}` emission order + `{li r3
call-arg ↔ stw msg}` order = 4 real words on E7C). So the doc-15 sched2 window
holds even fully un-barriered; the pin-to-ARG route (§6az-241) is the remaining
pursuit for these two members.

## 2026-08-31 — two new levers confirmed by promotion

### Lever: register-reuse bool tail (cracked fn_8007A230, 100%, DOL byte-identical)

Chained-call wrappers ending in a bool (`ScriptSetXxxState`-class): the
`if/else` producing the return bool must write back into the **SAME variable
that holds the call result** — `temp_r3 = fn(...); if (cond) { ...; temp_r3 = 1; }
else { temp_r3 = 0; }`. Register reuse then emits the want tail
`[stw; cmpw; li 1; bne; li 0]` exactly. Assigning the bool to a *separate*
local parks the value in r0 and shifts the whole tail (+1 insn, wrong regs).
Related polarity lever (cracked fn_8004D704): `if (res) {fn; return 1;} return 0`
vs `if (!res) return 0` — materialize-the-then-arm-first beats the notted form.

### Lever: shared case/default arm forces the lower-bound check (cracked fn_80073828, 100%, DOL byte-identical)

A switch whose `case 1:` and `default:` share one body (case 1/default
fallthrough) makes GCC insert `ble -> default` (the r0<2 lower-bound check,
covering case 1 and below) into the compare chain, yielding
`[lis; or.; lwz; beq; mr; cmpwi 2; beq; ble; cmpwi 3; beq; bl default; b;
bl case2; b; bl case3]`. Without the phantom `case 1:` label the compiler
emits only `cmpwi 2 beq; cmpwi 3 beq; bl default` (86.4% residual). Also:
globals read via `extern s32 lbl_X;` (lis+lwz-displacement) — a literal
pointer `*(s32*)0x80301668` adds an extra `ori`. Switch source order
default-first with case 2/3 after (body layout D,c2,c3).

## 2026-08-31 — bitfield-store lever (rlwimi) + li-sinking residue (fn_80130E88, 89.5%, parked)

**NEW LEVER — bitfield store forces rlwimi.** For field updates
`(v & 0x0FFFFFFF) | (bits << 28)`, GCC 2.95 canonicalizes every plain
mask+shift+or spelling to `clrlwi; or` (two insns). The single-insn
`rlwimi r0, r8, 0x1c, 0, 3` only appears when the write is a **bitfield
store**: `((struct { u32 hi : 4; u32 lo : 28; } *)ptr)->hi = bits;`
(hi-first member = top nibble; lo-first = bottom nibble — the member order
picks the mask). Anonymous struct cast inline works; no named type needed.
Also confirmed on the same fn: nested `if/if` guard emits NO `crclr`
(the `&&` short-circuit form does), and a plain `while` with memory
condition gives the want skeleton (li counter; cmpw; bge; count re-read at
bottom) — no `>0` pre-guard.

**Residue (parked at 89.5%):** got schedules `[li r8,0; li r10,0]` (loop-var
inits) BEFORE the entry test; want has them sunk AFTER the `bge`. All init
orders tried ([i;o;b],[i;b;o],[b;o;i],[o;b;i]) and flag matrix
(`-fno-schedule-insns2`, `-fno-schedule-insns`, both, `-fno-move-loop-invariants`)
keep the same placement — the pair stays above the branch. Sched2-sinking
below the entry branch not reproduced; revisit if a doc lever for
"loop-var init sinking below entry test" is found.

## SOLVED MEMBER — the LabelObjectCtor "r9/r11 label-address web coin" was NOT a coin (2026-09-06)

Five members parked under this doc's "two rodata label addresses — ngccc
assigns the reverse register pair regardless of decl/compute order" banner:
`fn_80087E18`/`fn_80088824`/`fn_8008B994`/`fn_8008CFD0` (85.7-88.6%) and the
 twin `fn_8008C2C0` (88.6%). All five body shapes:

```c
handle = lbl_80366478;          // ← ROOT CAUSE: the HOIST
a8  = (s32)lbl_XXXX8;
a20 = (s32)lbl_XXXX20;
arg0->unk0x20 = a20;
arg0->unk0x8 = a8;
...
temp_r3 = fn_8005CF80((void *)handle, arg3);
```

**Root cause:** the hoisted handle local forces GCC's PRE to compute
`lbl_80366478` into a register at the cluster start; the allocator then
colors the two label-address webs in REVERSE (the +0x20 label gets r11, the
+8 label gets r9) while still emitting the lis/addi pairs in want's slot
order. Every order/permutation probe (assignment order, store order,
decl order, register-asm pins doc-02-style, 7 flag configs) only SEE-SAWS
— either colors match and order flips, or order matches and colors flip.
That see-saw is the signature of a hidden competing web, not a coin.

**Fix (5 words × 5 fns, all EXACT, DOL byte-identical):** pass the handle
global INLINE to the lookup call — `fn_8005CF80((Unk_9994C3F5
*)lbl_80366478, (void *)arg3)` — and delete the named `handle` temp.
Without the hoist, GCC's scheduler splits the handle `lis+lwz` pair
between the two label `lis` exactly as the original did, and the natural
web colors (r9 = +0x20 label web — the FIRST store — r11 = +8 label web)
fall out without any pin. The lis tie-break then follows source order.

**Transferable lesson:** when a label/global web color "coin" resists
order permutations AND register pins, look for a THIRD global whose hoisted
local (named-local habit) is competing for the caller-saved
pool — un-hoist it (inline the single use) before concluding scheduler gap.
Promoted: 0x80087E18, 0x80088824, 0x8008B994, 0x8008CFD0, 0x8008C2C0
(2026-09-06; family rename suggestion LabelObjectCtor).

## PARKED MEMBER — fn_80126310 heap-init: page-anchor birth-order triple-swap (2026-09-12)

Draft `src/wip/fn_80126310.c` reaches 30/36 (83.3%) masked DIFF, size-exact
144B: frame (`stwu -0x18`, `stmw r29`), countdown zero-fill loop
(`lis r9,0xa; mtctr; lwz r9,3258(r29); stw/stw/addi/bdnz`), and `stb` tail
all byte-exact. Remaining 6 words are three independent scheduler birth-order
swaps around the two malloc calls (`fn_800105CC(0x500000)` /
`fn_800105CC(5000000)`, three global stores to `lbl_80303258/5C/60`):

Remaining 6 words are three independent scheduler birth-order swaps around the two allocation calls: retail emits the 0x50 constant load into r3 before the page load into r29 ahead of the branch while the build reverses that pair, retail emits the page load into r30 before the store of r3 to offset 3258 while the build stores first, and retail emits the page load into r9 before the store of r3 to offset 325c while the build again stores first.

The two saved page webs are built by construction (`pg1`/`pg2` literal
`0x80300000` inits + `__asm__("" : "+r"(...))` split barriers: pg1=r29 for
store#1+loop reload, pg2=r30 for store#2) — the barriers are load-bearing
(removing/moving either merges the webs, 136B collapse). Exhausted without
effect: statement/decl/arg-var orders, volatile/combined/memory barriers
(all regress or add `mr` copies), volatile `lis` births, s32 pg vars,
hard-reg pins (frame blowup to 148B), 8 scheduler flag sets, all five ProDG
versions (identical 30/36 — not a version artifact), `char[]`+`&` addressing
forms (22/36). Retry hint: the barrier-adjacent birth pins early while the
independent arg/store floats over it; a construction whose births are
*forced* late (use-driven) without merging the webs would crack all three
swaps at once.

## 2026-09-13 — a working lever for the `mr` birth order: pin BOTH argument registers

`fn_801F9EB8` (116B) was parked at 89.66% with exactly two residual words —
the classic two-argument setup swap:

At offsets 0x40, 0x44 and 0x48 retail moves r30 into r4 then r31 into r3 before the call, while the build moves r31 into r3 then r30 into r4 before the same call, swapping the two argument-setup moves.

Nothing that only *names* the values moved it: temporaries for one or both
arguments (`s32 a4 = var_r30;`), an evaluated-once `void *a3 = var_r31;`, a
`(s32)` cast, and both-orderings of the source expression all compiled to the
same two words in the same wrong order.

What does work is pinning **both** argument registers, declared in the order
retail fills them:

```c
do {
    register s32 a4 __asm__("r4");
    register void *a3 __asm__("r3");
    a4 = var_r30;
    a3 = var_r31;
    fn_801F9498(a3, a4);
    ...
```

That is 100.00% (29/29) — promoted, DOL byte-identical. (`-O1` was needed for a
different word in the same draft: `cmpwi r9,0` -> `cmpwi r0,0`.)

**Why it works:** unnamed argument pseudos are born in gcc's call-setup order
and then coalesced into r3/r4 by the allocator, which is free to emit the two
`mr`s in either order. An explicit `register ... __asm__("rN")` for each
argument makes the birth order the *source* order, so the `mr`s are emitted in
that order too. Note this is the opposite of the usual pin advice: pinning only
one argument, or pinning the callee-saved receiver (`o`/`t` in the
`fn_80224BB4` shape) does not help — the pair must both be pinned, r3 first if
retail fills r3 first.

**Where it does NOT work:** `fn_80224BB4` (308B, 6-word residue) is the same
shape with a three-way rotation (`mr r3,r31 ; mr r4,r11 ; mr r29,r11`) and
pinning the r3/r4 pair there regressed it to 89.6% (the r29 store is a separate
statement, not an argument, so the rotation is not purely call setup).

## 2026-09-13 — the pin recipe inverted: pin a *callee-saved* argument home

`fn_800DF004` (352B) reached 95.5% with the same recipe run backwards. Retail
keeps the two incoming arguments in **different** callee-saved registers:
`arg1 -> r29` and `arg2->unk0x60 -> r28`. ngccc gave the first-created value the
lower register, i.e. `arg1 -> r28`, `unk0x60 -> r29`, and every consumer of both
(including a `fn_800DF24C(a0,a1,unk0x60,...)` argument list) was transposed.

Pinning a local copy of the *parameter* fixes it:

```c
register void *var_r29 __asm__("r29");
...
var_r29 = arg1;            /* once, at function entry */
...  return fn_800DF24C(arg0, var_r29, var_r28 /*unk0x60*/, ...);
```

Pinning worked here where the older note says it fails for `fn_80224BB4`: the
pinned value is a *parameter homed once at entry*, not a value born inside a
loop. Pinning a loop-local (`var_r31` in `fn_800CB4D8`, `var_r9` variants)
regressed, exactly as that note predicts.

Two follow-ups in the same draft are worth knowing before parking anything in
this family:

- the residual shrank to **one scheduler swap repeated at both call sites**
  (`want lwz r28,0x60(r31); or. r11,r3,r3` vs `got or.; lwz`). 56 flags and 21
  two-flag combos do not move it (recipe 62);
- `fn_800CBF00` needed a **3-arg prototype**: with none, mwcc emits the varargs
  `crclr cr1eq`, which is an extra word and shifts the whole frame (recipe 60).

## Not every member of this family is a *scheduling* wall — check the ARGUMENT CLASS ORDER first

2026-09-16 round. Two drafts parked under this issue were **not** scheduling
coins at all; they had the integer and float arguments in the **wrong class
order in the prototype**, which is a plain source defect that always looks like
the same one-move rotation.

### fn_8002AEF4 — PROMOTED (93.6% → 100%) after ~15 failed source shapes

The draft declared a vtable method through a bare cast:

```c
/* got: integer staged first, floats after */
((s32 (*)(void *, s32, f32, f32))temp_r9->unk0x14)(self, arg2, temp_f31, temp_f30);
```

But retail stages the float arguments first and the integer last: it copies f31 into f1, loads the table pointer, copies f30 into f2, then moves r27 into r4 before the call, while the build moves r27 into r4 first and emits the float copies afterward in the same window.

Reason: the real method takes `(void *, f32, f32, s32)` — **the integer is the
LAST argument**. Both the cast and the argument list have to be permuted
together:

```c
((s32 (*)(void *, f32, f32, s32))temp_r9->unk0x14)(self, temp_f31, temp_f30, arg2);
```

All 6 argument permutations x matching prototypes were A/B'd: only int-last is
EXACT (95.7% for the two "integer in the middle" forms, 93.6% for int-first).
The tell is that the register→value **mapping** is right while the *emission
order* is wrong: `r4` holds the value want puts in `r4`, but want emits it
after the `fmr`s.

### fn_8010B7EC — IMPROVED (94.8% → 97.4%), same cause at one call site

```c
/* got */  void fn_8010B920(s32, void *, f32);  ... fn_8010B920(arg0, sp8p, farg0);
/* want */ void fn_8010B920(s32, f32, void *);  ... fn_8010B920(arg0, farg0, sp8p);
```

want emits `fmr f1,f31` before `mr r4,r31`; with the pointer declared second
the compiler stages the GPR first. Only the pointer-last class order removes
the pair (all 4 class permutations A/B'd); the remaining 2 words are a genuine
`lfs` scheduling coin that no store permutation moves.

### Recipe

A one-move rotation in a call's argument setup, where the value that lands in
each register is already correct but the **order** is not, is a *class order*
question before it is a scheduling question:

1. Read want's setup block and write down which register each argument's value
   lands in.
2. If the GPR args and FPR args are *grouped* on one side (all GPRs then all
   FPRs, or FPRs first), the prototype's parameter classes almost certainly
differ from what the draft has: MWCC emits argument setup in source order, so
   the prototype fixes the register and the call site fixes the emission order.
3. Permute the prototype's float/int parameter positions **and** reorder the
   argument expressions to keep the same register→value mapping. Never permute
   only one of the two — that silently changes which register holds what and
   looks like an unrelated regression.
4. Only if every class permutation ties should the draft be parked as
   scheduling. Note that a *grouped* want (all GPR setup, then all FPR) can
   also mean the float parameters are declared **after** the integers in the
   real signature — the same trick, one level up.

### Measurement hazards found in the same round

Three separate tools were returning numbers that did not describe the build the
park note was about. All three are fixed; the pattern is worth knowing because
each one produced a *confident wrong conclusion*.

**1. Address-keyed scratch object (parallel races).** `tools/score_body.py`
(and any script calling `gen_leaves.compile_fn` directly) compiles to
`$LEAF_TMPDIR/<addr>.o` — the name depends on the **address only**. Two workers
scoring the SAME address share that object and each can report the other's
score. A six-variant sweep of `fn_8010B7EC` under `xargs -P` reported 97.4% for
a body that really scores 62.3%. `score_body.py` now defaults `LEAF_TMPDIR` to a
per-PID directory; any other harness fanning variants out must do the same (or
score sequentially). **A parallel sweep over many addresses is safe; a parallel
sweep over many variants of one address is not.**

**2. Header flags ignored.** `score_body.py` and `diff_near.py` both compiled
the draft body with DEFAULT flags and ignored the draft's own
`// FLAG:` / `// extra_cflags:` line (`pool_score.py`, `stmt_perm_search.py` and
`ps_diff.py` already honored it). Two drafts were affected badly in this round:
`fn_800E3520` reads 87.1% without its `-fno-schedule-insns2` and **100.0% with
it** (it had been sitting parked, already solved), and `fn_80124110` does not
compile at all under default flags, so `diff_near.py` answered `COMPILE FAIL`
for a draft that scores 54.1%. Both tools now read the header line and accept a
`--flags` / positional override.

**3. Silent truncation at undecodable words.** `diff_near.py` fed each region
to `md.disasm` in one call — but capstone's generator **stops at the first word
it cannot decode**, and paired-single code (opcode 4, `psq_l`/`ps_*`) is
exactly that. It never passed `-mps-float` either, so for any PS draft it both
compiled the wrong build and stopped decoding after a handful of words.
`fn_801DA420` (688B, 172 words, `// FLAG: -mps-float`) printed
`25/25 match (100.0%)` — a plain lie; it is really 163/172 (94.8%), which is
what `score_body.py` says. `diff_near.py` now decodes word-by-word, falls back
to `.word`, uses the **registered** want size from `report.json` instead of
`len(got)` (so it cannot read into the next function), and prints
`# flags:` / `# size:` headers. **Before trusting a diff, check those headers,
and cross-check the percentage against `tools/score_body.py` — the two now
agree for every draft tried.**

## 2026-09-20 — SOLVED MEMBERS: the FLOAT-FIRST prototype lever

Two functions in this class were closed by re-ordering the **callee's
prototype** rather than by touching the call site. When the ONLY residue is
that want emits the FPR argument move (`fmr f1, fN`) BEFORE the GPR moves
(`mr r3,..` / `mr r4,..`) while ngccc emits the GPR moves first, the fix is to
declare the callee float-FIRST and pass the float argument first: ngccc's
register-parameter loader walks the argument list in source order, so the
prototype position decides both the register and the emission slot.

- **fn_8011A908** (0x8011A908, 84B): want is `fmr f1,f31; mr r3,r31; mr r4,r30`.
  `fn_8011F3A4(s32, s32, f32)` + `fn_8011F3A4(arg1, arg2, farg0)` scores 85.7%
  (FPR move last); declaring `fn_8011F3A4(f32, s32, s32)` and calling
  `fn_8011F3A4(farg0, arg1, arg2)` is **EXACT 100%**. The register mapping is
  identical (f1 / r3 / r4), so this is ABI-neutral — only the emission order
  changes. The already-matched sibling `fn_8011F308` scores EXACT under BOTH
  spellings (its `lfs` gets hoisted either way), so cross-checking a solved
  sibling does NOT always discriminate the two forms; trust the want disasm.
- The same function also needed its OWN signature corrected to a 4-parameter
  `(s32 arg0, f32 farg0, s32 arg1, s32 arg2)` with an **unused r3**: want
  forwards r4/r5 + f1, so m2c's `(s32, s32, f32)` (r3/r4/f1) saved the wrong
  pair of registers. When a prologue saves r4/r5 but the source has only two
  integer params, an unused leading integer (or a float in the middle) is the
  likely original shape.
- **fn_800246B4** (0x800246B4, 112B) — a different, also-transferable
  member of this family: the `if (cond) return call(...);` spelling makes ngccc
  move the call block OUT of line (`bne` + body inline, 27.6%); writing it as
  `if (cond == K) { body; return 1; } else { return call(...); }` reproduces
  want's `beq`-to-body layout byte-exactly. Both the missing-prototype `crclr
  cr1eq` insertions (doc-56) and this layout inversion had to be fixed
  together before the function scored 100%.

## 2026-09-20 — a *load* "scheduling coin" is usually a SINK defect: stage the deref in a named local

The mirror image of the LabelObjectCtor lesson above. There, a **named** handle
local had to be **un-hoisted** (inlined) because its extra web competed for the
caller-saved pool. Here the opposite holds: when want evaluates a pointer
dereference **unconditionally at the top of a block** and the draft has that
same deref **sunk into the last statement that uses it**, ngccc reproduces
want's whole load/emit group only if the deref is given a named local of its
own. m2c habitually sinks it; the resulting 2–N word rotation reads exactly
like a scheduler tie-break and is routinely parked as one.

The tell: want's deref emits **before** the stores/tests that surround it in
the draft's source order, and the operand addresses match — only the *slot*
moved. Re-attack order: (1) is the deref's value used in more than one source
statement? (2) if not, hoist it anyway into a local read at the top of the
block — `T v = *p;` / `**(s32 **)&x` — and keep the later consumer reading the
local, not re-dereferencing.

- **fn_8013A93C** (0x8013A93C, 132B): **66.7% → 93.9%.** Parked as a
  "load/schedule window" with the note "no source shape tried". want issues
  `lwz r9,0xc(r31)` + `lwz r3,0(r9)` (i.e. `**(s32 **)&arg0->unk0xC`) BEFORE
  the `cmpw r11,r0` inner test; the draft had the deref in the last statement.
  Adding `s32 temp_ra = **((s32 * *)&arg0->unk0xC);` as the FIRST statement of
  the outer body aligns the entire tail (`subf` block, clamp, call). The
  residual dropped from 11 words to 2.
- **fn_8000901C** (0x8000901C, BitStream_Read, 212B): **71.7% → 75.5%.** Its
  refill arm has the same shape — want's `*walker` read emits before the three
  `arg0` stores. Staging it as `u32 *p; u32 v;` inside the `if (arg0[3]==0)`
  block (declared in-block, read before use) rotates the whole refill group
  into want's order.

**Where it does NOT work (same round, all still parked):** the lever only
fixes *which slot* the deref occupies, not the colour of the temporary it lands
in. `fn_8000901C`'s remaining 13 words are a pure `r0`/`r11` colour swap in
that same refill arm plus the slow path keeping `arg1` in `r4` where want
overwrites it (`subf r4,r5,r4`). `fn_800D94E4` / `fn_8010B7EC` (both 93.3%
/ 97.4%) are the same *appearance* — two adjacent `lfs` loads swapped — but a
real tie: their load pairs are independent, same-base, and the source order is
already want's, so hoisting/staging changes nothing. Distinguish by checking
whether want's early load is **feedable from a source statement that could move
up**; two already-adjacent same-base loads with no intervening statement are a
genuine coin.

## 2026-09-20 — `-Os` de-hoists loop-invariant ADDRESSES: read the frame/callee-save set first

A whole-function *shape* defect, not a per-statement one: at default `-O2`
ngccc hoists the address of every `extern char lbl_[]` referenced inside a loop
into a callee-saved register for the loop's whole lifetime. That inflates the
callee-save set and hence the frame, and the residue then looks like an
unrelated "wrong function" (dead registers, `lis r21..r24` before the loop).

- **fn_801AFA18** (0x801AFA18, 540B): at `-O2` the body scores 62.2% and emits
  `stwu -0x48` + `stmw r21` with four `lis rNN, 0` hoisted above the walker
  loop (the four `lbl_802ABC*` format-string addresses). Adding **`-Os`**
  drops the hoist, restores `stwu -0x38` + `stmw r25`, and re-materialises each
  label per call (`lis/ori`) exactly as want does → **74.1%**, size- and
  frame-exact, at no source change at all. Parked there: the residue is one
  `or. r31,r9,r9`/`cmpwi` pair per walker test (ngccc's copy coalescing eats
  want's record-form copy — same class as the `mr` copy-shape wall earlier in
  this doc, and NOT fixable by assignment-in-condition or by a `void *walk`
  type change) plus a one-register arg-home shift.
- **Read the frame/`stmw` range BEFORE treating a low score as a decode error.**
  `want stmw r25` vs `got stmw r21` with the same instruction count is a
  hoisting/callee-save symptom, i.e. a flags lever, not 4 missing source
  statements. Cheap decision procedure: score the body at `-Os` (and
  `-Os -fno-schedule-insns`) before rebuilding anything by hand.
- **Check both directions.** The same `-Os` lever *hurts* elsewhere in this
  round: fn_8016D698 53.7% → 13.0% and fn_801C7FF0 61.9% → 31.1%, while
  fn_80124110 (54.1%) is flag-insensitive. `-Os` is a per-function coin like
  any other flag, so score it, never assume it.
- **`-Os` is not only a hoist lever.** **fn_8013157C** (0x8013157C, 348B,
  SOLVED 2026-09-20) went 52.2% → 92.0% on the union-bitfield rewrite of its
  0xCC flag word (recipe 110) and then 92.0% → **EXACT** on `-Os`, which is
  what collapsed its two stacked loads into want's single `r9` reuse
  (`lwz r9,0x38(r1); rlwimi; lwz r9,0x3c(r1); rlwimi`). When the whole block
  matches except for one register-reuse pattern, try `-Os` before rewriting.

## 2026-09-21 — random no-park sweep: 4 EXACT (2 recipes new here) + 1 arg-copy park

Random pool sample (48 addresses, `tools/sweepable_pool.py` → shuffle → rank).
Four drafts solved to 100% and promoted (DOL byte-identical):

- **fn_801A6E0C** (0x801A6E0C, 88B) 39.1 → **100**. Two m2c defects:
  (a) the helper `fn_801A6820` is **one argument** — declaring it 2-arg made
  ngccc pass a phantom `r4` (`addi r4,r31,4`) retail never has; (b) the two
  loads are a **struct array at offset 4, stride 0x20**, not byte-pointer
  arithmetic — m2c's `*((s32 *)base + idx)` scaled the index (slwi 5→7) and
  folded `arg0` into the index register, which also flipped the r29/r31
  home. Writing `((Outer *)arg0)->e[var_r4].unk0/.unk4` fixes both at once.
- **fn_8012EA18** (0x8012EA18, 164B) 41.9 → **100**. Declare the callees
  (2 doc-56 `crclr` words = the exact 8B size gap) **and** replace m2c's
  `loop_7:` goto with a plain bottom-tested `while (1)` — the binary rotates
  the entry branch over the body, which only the natural loop shape emits.
- **fn_8013AB54** (0x8013AB54, 324B) 38.6 → **100**. m2c emitted the six
  handler addresses as **integer literals** (`0x80139BDC`), which ngccc
  materialises `lis+ori` per call; the binary passes them as **symbol
  pointers** (`lis r29,-0x7fec` cached once, `@ha/@l` addi per call) → declare
  the targets and pass the function names (same family as doc-51, but here the
  literal is a *code* pointer, not a `lbl_*` data symbol). Plus doc-56 for
  `fn_80139600`, and a store-order brute force (7! permutations) found the
  unique 100% order: **0x1844 first, 0x1804 LAST**.
- **fn_8012788C** (0x8012788C, 168B) 38.0 → **100**. (a) the three float args
  were stored through `s32 *` (m2c field type) → fctiwz conversion dance;
  they are plain **f32** (`stfs`). (b) that shrank the frame; the binary needs
  **three** 8-byte dummy slots, not the usual one `volatile double`. (c) the
  `(x & ~0x7F0000) | 0x60000` update compiled `rlwinm+oris`, but retail uses a
  single **`rlwimi`** — a **bitfield insert** reproduces it exactly, and the
  big-endian PPC field run must lead with **9** bits (`u32 a:9; u32 b:7;
  u32 c:16;`): a 16-bit lead field silently moves the insert to LSB 9..15 and
  still scores 97.6%, which is the tell that the field position is wrong.

- **fn_80129B84** (0x80129B84, 132B) PARKED 45.5% (best). Tail 0x58..0x80 is
  word-exact; only the arg-setup/RA block 0x10..0x54 differs. The binary's
  prologue routes `arg0` through volatile `r9` and `arg2` through `r0→r28`, so
  it homes `arg2→r28` and `arg4→r31`; ngccc homes `arg2→r31`, `arg4→r28`
  (the two callee-saved temps are **swapped**) and keeps `arg0` in `r0`. Every
  semantic word is identical. Tried, all identical 45.5%: either local decl
  order; `arg2` s32 vs u32; `> 4U` vs `>= 5U`; helper returning `void *`
  with cast; `-O1`, `-Os`, `-mno-sched-prolog`, `-fno-omit-frame-pointer`,
  `-fno-schedule-insns2`. Declaring the callees removes the accidental
  `crclr` coincidence and scores *worse* (12.1%). Pure copy-prop/RA ordering.

### 2026-09-21 (sample 2) — 1 more EXACT + 1 arg-forwarding park

- **fn_8019BC6C** (0x8019BC6C, 160B) 42.5 → **100**, PROMOTED. (a) `*(s32
  *)0x80305EAC` raw literal → registered `lbl_80305EAC` declared as its REAL
  object type (`extern s32`, bare use) so the address folds into the load
  displacement; `extern char lbl_X[]` would still cost an `addi` (doc-61).
  (b) m2c's `loop_2:`/goto → `for (i = 0; i <= 7; i++) { ...; if (...) break; }`,
  the only shape that emits the rotated `b cond; inc; cond:` layout.
  (c) `fn_80125814` takes `(void *msg, s32)` — m2c dropped the leading
  `lbl_802AAB9C` string argument.
- **fn_800F2BA8** (0x800F2BA8, 264B) PARKED **72.7%** (from 43.9). Five
  stacked fixes, transferable: doc-56 prototypes (3 `crclr`); the vtable
  displacements are **s16** (`lha` not `lwz`); `fn_800F34F0` is a **3-arg**
  call (m2c prepended a phantom `arg0`, doc-52); **`fn_800F2628` takes TEN
  args** — m2c dropped the two caller-stack params, and forwarding them
  (`arg_sp8`/`arg_spC`) is what restores the -0x38 frame with
  sp10@0x10/sp8@0x8/spC@0xC (they are outgoing stack args, not dead locals —
  the classic "8-byte frame gap" tell); m2c's `loop_5:` → `while (call() == 0)
  { fn_800137C4(0); }` for the rotated entry jump.  Residual 18 words are a
  pure callee-saved **home swap**: want homes `arg0→r30` / result→`r31`,
  ngccc the reverse — same wall as fn_80129B84, unaffected by 3 local-decl
  orders or a `temp_r30` rename.

## 2026-09-21 — SOLVED MEMBER: do NOT bind a local for a pointer used
as an argument now and again later (`fn_80010434`, 272 B, 52.2 % → 100 %)

Retail materialises the copy-once value into the argument register first and then copies it out to the long-lived home: it derives the pointer by adding 0xC to var_r31 directly in r3, which is itself the call argument, stores the incoming eighth register to offset eight of var_r31, copies r3 into the long-lived r27 home so the value survives the calls, branches to strcpy, and later passes r27 on to fn_8000F95C.

Writing a C local (`ptr = var_r31 + 0xC; ptr2 = ptr;`) makes ngccc allocate the
long-lived home first and copy backwards — `addi r27,r31,0xc; mr r3,r27` — which
is 2 words different and unreachable by renaming: two locals, swapped
declaration order, `s32`-instead-of-pointer types, and moving the copy across the
`stw` all give the same 97.1 %.

**The fix is to remove the locals entirely and write the expression twice**:

```c
    ((Unk_2EF06E12 *)var_r31)->unk0x8 = arg1;
    strcpy((char *)var_r31 + 0xC, arg3);
    ... fn_8000F95C(arg0, ..., 1, (char *)var_r31 + 0xC);
```

CSE turns the second occurrence into the `mr`, but the *first* occurrence is what
picks the register, so the addi lands in r3. This is the same "m2c invents a
local that costs a callee-saved register" shape as doc 57's read-back recipe —
worth trying whenever a 2-word residue is an `addi/mr` transposition.

## 2026-09-22 round — the "no r3 setup" tell, three new SOLVED members

A pool-wide scan of the 1063 no-park drafts that looked for **a `bl` whose r3 is
never set anywhere earlier in the function** produced 40+ candidates; triage
converted three of them to EXACT. The tell already listed above (r3 = the previous
call's return) has a second, larger form:

### (a) r3 = the function's OWN incoming arg0 (pass-through), PAST the 4th arg

m2c recovers a call's arity from the IR, and when the first argument is simply the
enclosing function's first parameter it emits a *short* prototype, which makes
ngccc materialise r3 at every call site and shifts every following word.

- **fn_80235000 (ScriptEnableParkEdCursor) 41.7% → EXACT + PROMOTED.** want's
  prologue is `li r0,0; li r4,0; stw r0,8(r1); addi r5,r1,8; li r6,0; bl` — the
  callee really is 4-arg `fn_80128228(arg0, 0, &sp8, 0)`. m2c's 3-arg call put
  `&sp8` in r4 and needed a `li r3,0`, so the frame was one word short of
  matching and every branch target moved. Bonus tell in the same function:
  `fn_8023E09C(fn_8023C598(1), 1)` — the *first* argument of the second call is
  the nested return, so no second `li r3,1` is emitted.
- **fn_80127E70 36.4% → EXACT + PROMOTED.** A 5-arm switch where every arm has
  the same shape: want does `mr r5,r6; bl` (r3/r4 untouched). Real callees are
  3-arg `fn_XXXX(arg0, arg1, arg3)`; m2c's 1-arg prototypes made ngccc emit a
  `mr r3,<something>` per arm. Extra lever on the same body: the `case 2` float
  must be a **stack reinterpretation** (`sp8 = arg3; fn_8012772C(*((f32 *)&sp8))`
  → `stw r6,8(r1); lfs f0,8(r1)`), not `(f32)arg3`, which is an int→float
  conversion and pulls in the float-pool helper.

### (b) WRONG LOCAL SIZE — a buffer modelled as `s32`

**fn_8005D6C8 33.3% → EXACT + PROMOTED.** Two m2c errors compounded: the dropped
pass-through arg (a) *and* `s32 sp208` / `s32 sp8` where retail has two
**`char[0x200]`** buffers — the frame was 0x420 in want and 0x20 in got, so every
offset matched nothing. After sizing them:

- the buffer handed to the *first* call is the **first declared** array: ngccc
  gives the first-declared array the LOW address (+8 here), so declare the array
  used by the earlier call first;
- the trailing `ori r4,r4,0x3924` vs want's `addi r4,r4,0x3924` was the **string
  literal vs string symbol** tell — pass `extern char lbl_80293924[];` (the
  "%s.tex" symbol) instead of the raw literal `0x80293924`, otherwise ngccc picks
  `ori` for the constant's low half.

**Diagnostics for both classes** (throwaway, ~90 s for the whole pool):

1. *frame-size scan* — compile every no-park draft, compare word 0 (`stwu`'s
   negative immediate) with want's. A 0x4x8-style delta (> ~0x100) is almost
   always a mis-sized buffer/enum/struct, not a scheduling issue.
2. *no-r3-setup scan* — for each draft, walk the `bl` list of got and want in
   parallel; flag calls where got sets r3 in the 3 instructions before the `bl`
   and want does not. (Capstone + `gen_leaves.compile_fn`, and remember the
   `bl` displacements are masked, so match call sites by ORDER, not address.)
3. *single-insertion scan* — compare got against want under a one-word shift;
   a 1.00 shifted match over the whole tail means the residual is confined to a
   short prefix (that is how the fn_8005D6C8 frame bug surfaced).

### (c) Parked: r3 pass-through that does NOT want the nested return

**fn_801845B8 (32.1%, unchanged).** want decodes as

```c
while (sp8 < fn_80184168(arg0)) {
    fn_8018BE00(fn_8018B4C0(arg0 + 4, &sp8, &spC), 0, 0);
    sp8 += 1;
}
return arg0 + 4;
```

i.e. m2c dropped `arg0+4`, `&sp8` and `&spC` from the first call and the
pass-through r3 (want's loop head consumes r3=arg0+4, r4=&sp8, r5=&spC). The
correct decode scores **27.6%** — *worse* than the wrong m2c body's 32.1% —
because ngccc hoists the three `addi` argument stagings into the loop HEAD while
retail keeps them once in the condition/test block (112B vs 116B). Separate
statements, a named `r` local and a `for` form are all identical. The m2c body is
kept as the best-scoring revision; the decode above is recorded in the draft
header for whoever finds the hoist lever.

---

## 2026-09-28 round 2: four more members escaped (or proved walls)

### fn_800C70A4 (400B) — SOLVED: a loop-fill `fmr` is a PREHEADER-BLOCK + LUID problem, not an FPR-allocator one

86.0% → byte-exact, no emitted asm. Three changes, in order of contribution:

1. **Peel the first iteration** so the preheader is its OWN basic block:
   `if (cnt-- != 0) { <preheader>; do { body } while (cnt-- != 0); }`. This
   gives retail's exact 3-word guard (a plain `if (cnt)` gives 2, and
   `if (cnt != 1)` lets GCC prove the `if` redundant).
2. **Materialise the pre-decremented byte offset as a real source variable**
   (`a = cnt*16; b = a - cnt; k = b*32;` then `k -= 480;`). With the index
   written *inside* the body, iv.c's hoisted multiply chain gets HIGHER LUIDs
   than any pre-loop statement, so the fill's definition always schedules
   first. Staging it in the preheader restores source-order LUIDs and lands
   the copy mid-chain, where retail has it.
3. **One zero-code `__asm__("" : "+f"(fill);)`** keeps `fill` a distinct
   pseudo from the quad-store zero. Without it both share f13 and **no `fmr`
   is emitted at all** (the object comes out 396B, 4 bytes short).

Plus offset-first addressing for the last word (§6k-66):
`*(f32 *)((char *)(k + (s32)base) + 0xA4)` gives want's `add r9,r10,r9`;
`base + k` gives `add r9,r9,r10`.

Dead ends, for the record: hard-FPR pins on `fill` (fr0/1/12/13, and zero) push
the copy 16 words early (83%); `volatile "fmr %0,%1"` emits the right
instruction but the scheduler puts it in the guard's `lwz` delay slot (95%);
`--cnt != -1` scores 84%; `-fno-gcse` 4%; `-fno-expensive-optimizations` puts
the `fmr` in the right slot but bloats the object to 416B.

### fn_8001E248 (180B) — SOLVED: ngccc hoists the HI16 pseudo to the block top AND DRAGS ITS DEPENDENT LOAD UP

91.1% → byte-exact with 3 volatile-asm instructions (6.7%, generic arithmetic —
no transcribed control flow). The residual was a pure list-scheduler order
tie: ngccc gives address formation "constant" priority, so the `@ha` pseudo
lands at the block top and its dependent load is pulled up to sit directly
under it — which means a **third instruction can never sit between them from
C**. The two reachable positions were 91.1% (mask before the pair) and 95.6%
(mask after the pair).

Fix: anchor the page yourself and split the straddling ops:

```c
__asm__ volatile("lis %0,%1@ha" : "=r"(pg) : "s"(&lbl_80300288));
id0 = *(u16 *)((char *)pg + 0x288);            /* literal disp == want's encoding */
__asm__ volatile("clrlwi %0,%1,0x1e" : "=r"(id0) : "r"(arg0_pin));
__asm__ volatile("addi %0,%1,0x100e" : "=r"(idf) : "r"(id0));   /* u16 output */
```

Two traps: the asm output's **type is load-bearing** — a plain `s32` output
loses the range info and ngccc re-inserts a spurious `clrlwi r3,r3,0x10`
(60.9%), so declare the output `u16`; and **ngccc gives a parse error on a
declaration after an `__asm__` statement** — declare first, assign after.

### fn_8001EE4C (148B) — 86.5% → 91.9%: the indirect-call tail

New recipe for the arg-ORI / callee-LWZ order flip (the AGENTS §4p-21/§4p-25
neighbourhood): **stage the indirect-call argument in a named var, put a
VOLATILE empty `"+r"` barrier on it, and register-pin the call target.** All
three are load-bearing and **zero instructions are emitted**:

```c
register s32 tgt __asm__("r11");
cmd = arg0->unk0x…;
__asm__ volatile("" : "+r"(cmd));
((RET (*)(s32, …))tgt)(cmd);
```

Residual: 3 words, one IRA coin flip — retail's `or` destination is always the
*dying* shift term's register, so the accumulator dies and r0 is recycled.

### fn_801F5A0C (152B) — 94.7%, `mcrf` position proven INVARIANT to the preheader

Extends this doc's fn_800A9CE8 entry. The residual is 2 words: want
`li r29,0 | mcrf cr4,cr0 | li r30,0x32` vs got
`li r29,0 | li r30,0x32 | mcrf cr4,cr0`. The `mcrf` is GCC's cr4 cache of the
loop-invariant `arg1 == 0` test and ngccc emits it at the **end** of the
entry/preheader block. ~65 shapes (loop forms, latch forms, counter types,
goto-walk, `&&` vs nested-if, the call duplicated into both `||` arms, pins,
barriers, asm-born `li`, decl/statement permutations) all leave it there, and
24 ProDG flags are no-ops. **The position is invariant to preheader content** —
two barriers, phi-forcing copies and an asm-born `li` still leave `li r30`
first. The next angle is to **kill the cr4 cache** by spelling the invariant
test as a materialised bool, not to reorder the block. Template to look at:
`src/fn_801F59CC.c` (MATCHED, same 0x32/0x370 loop skeleton).

### fn_800C4560 (468B) and fn_800BD674 (252B) — see docs 74 and 73

Both are new walls, not doc-15 members. fn_800BD674's residual is 5 words in
the 8-word rodata page-anchor block: retail wants anchor colours r9, r10, r11,
r9 and ngccc's reload set is only `{r9, r11}` (doc 73). fn_800C4560's 4-word
residual is the float pre-copy mirror (doc 74).

---

## 2026-09-28 round 3: eight more members escaped — and the #1 cause is CALLEE ARITY

21 of 25 drafts byte-exact this round. The distribution is the headline:
**the single most common root cause of a "register-allocation / scheduling"
park in this project is a wrong callee arity**, and it keeps masquerading as an
alloc tie-break.

### The #1 lesson — a local-alloc tie-break is usually a wrong arity

* **fn_80130344** (85.7% → EXACT): `u8 *fn_8012B2A0(void);` → `u8 *fn_8012B2A0(u8 *)`.
  The callee really reads r3 (`lbz r0,0(r3)`). With the arg typed, the
  loop-carried cursor pseudo gains an arg0-r3 preference, GCC coalesces the
  arg move away, and the reload is coloured r3 instead of r9 — fixing all four
  residual words at once. **One line.** The previous session had tried ~3200
  source spellings, 864 loop shapes, 45 flag combinations, 5 compiler versions
  and register pins, all chasing an alloc "tie-break" that was never free. (Its
  own sibling `src/wip/fn_801303B4.c` already had the correct 1-arg prototype —
  m2c guesses 0-arg only sometimes.)
* **fn_80116840** (88.6% → EXACT): `s32 Mth_Rnd(void);` → `s32 Mth_Rnd(s32);`
  (the real one does `mullw r10,r10,r3; srawi r3,r10,0x10`). The arg is the
  element count — which is *also* the `cmpwi` guard operand, and that is exactly
  why want loads it into **r3** (the arg register) rather than r0. Also fixed
  `GetChecksum`'s 2nd param to `s32` (it is an array index, `slwi r9,r4,2`).

> **Audit every unprototyped or no-arg callee in a body BEFORE any
> allocation or scheduling work.** A `(void)` proto on a callee that reads r3
> leaves the calling web unpinned in colour selection. Add this to the doc-10
> audit recipe (which already extends past `blr` stubs to dead-code callees
> and m2c-invented zero-arg protos).

### fn_80173C5C — SOLVED: a hoisted entry `mr` is a RETURN-STATEMENT shape

Filed at 95% as a "0.95 doc-15 member (entry-copy order coin-flip)". Wrong.
**GOT hoists a `mr rX,rY` to the TOP of the entry block but WANT places it
LAST, after the `lis`/`lfs` it interleaves** ⇒ the source has a **single exit
with a return VARIABLE assigned at entry**, not two `return` statements:

```c
s32 ret;
ret = arg1;                              /* first entry statement */
... ret = fn_80131154(arg1, 0, 0, 0);    /* update path */
return ret;                              /* ONE exit, at the end */
```

With two returns, ngccc's jump pass hoists the copy into the entry block with
*higher* list-scheduler priority than the parm home copy. L4 (C literals
`0.01f`/`0.2f` instead of the extern symbols) was also required — the extern
spelling caps the same function at 85–87.5% even after the structural fix.
The four `register f32 __asm__("frN")` pins the draft carried were inert
(unchanged 95%→100% with them removed); `volatile double _dummy` was NOT
(dropping it costs 12%).

### fn_800F2270 — SOLVED: WHERE a cold label is written decides where its block lands

62.2% → EXACT with no flags. The old park was a `maybe_reorder_blocks`
inversion ("retry only with a new block-ordering lever") — this IS that lever.
**A label written textually between a `goto` and its target opens a THIRD
basic block in the branch's fall-through slot**, which is exactly the physical
gap want has:

```c
if (*p == '.') goto ext;     /* cmpwi ; beq <ext>          */
goto nf;                     /* b <ret0>                    */
match:  return e->val;        /* lwz r3,4(r30) ; b <epilogue> */
ext:                          /* lis r9,...   <- branch TARGET */
```

Block-creation order is what the reorder pass sorts on, so a label's *textual
position* is the control. Second (95.6% → 100%): **do not stage the walk
terminator** (`e++; if (e->name == 0) break;` inline, not `n = e->name;`) so
ngccc picks r0 rather than the dead strcasecmp register r3.

### fn_801587C8 — SOLVED: a 2-word `li`/`li` transposition needs a NON-VOLATILE asm window

93.8% → EXACT. WANT `li r6,0; li r4,0` before the call; ngccc always emits
`li r4,0; li r6,0`. ~22 pure-C shapes (param-type matrix, return-type flips,
casts, memory clobber, pin-as-statement) all produce the identical 2-word
residual. The fix is a **non-volatile** 2-instruction asm window with the
outputs hard-pinned to the arg registers — and the volatile/non-volatile
distinction is load-bearing: volatile makes the window a scheduling barrier
that sinks the `li`s ahead of the `addi r5` (81.2%); non-volatile is freely
scheduled and lands on retail's order. Pins must be `s32` (cc1 drops
pointer/`u8` register vars).

### fn_8004A800 — SOLVED: the "deferred arg0" call window (1480B, 98.4% → EXACT)

A new class: sched2 always hoists arg0's `mr r3,r28` to position 2 of a 5-insn
call window, while retail emits the four arg insns in RTL order and defers
arg0's copy LAST. Fix: one volatile-asm block per affected switch arm freezing
the window's ORDER in template order. Two side requirements, both load-bearing:
* a hard `register s32 flag __asm__("r29")` pin (pins flag to retail's r29 and
  gives the window's last insn a home — without it r28/r29 swap, −24 words);
* an empty `__asm__("" : : "m"(sp1C));` pin, or the address-taken out-param slot
  dies and the **frame shrinks 8–12 bytes**.

### Three more, all with a named residual

* **fn_801A9388** (92.9% → EXACT): **a comma-expression in the LAST argument
  is the only place ngccc will emit a store between two arg-setup insns** —
  `fn_801A9494(arg0, t, (self->unk0x4 += 1, t))` puts the addi/stw pair exactly
  where want has it. The remaining store-vs-copy tie needs a hard
  `register s32 t __asm__("r4")` pin on the staged value (unpinned, the CSE'd
  copy out-prioritises the store and `mr r5,r4` lands before the `stw`).
* **fn_80010D04** (97.2% → EXACT): filed as a doc-15 register-home coin-flip;
  the cause was **local_cse**, not scheduling. A `volatile "+r"` barrier on the
  *copy* pointer stops it folding the second store's address into p instead of
  the hard-pinned r11 birth web. General: when want keeps a birth web AND its
  copy for disjoint later uses, barrier the copy.
* **fn_80152CD0** (95.6% → EXACT): **to push a hard-reg-pinned copy AFTER an
  independent def, feed that def's pseudo as an extra INPUT to the pinning
  `__asm__`** — `__asm__("" : "+r"(var_r9) : "r"(var_r0), "r"(temp_r11));`.
  The plain 1-operand barrier lets the allocator materialise the copy right
  after r11's def, above the independent load. Both inputs load-bearing (a
  tied `"0"` operand is a compile FAIL in cc1 2.95). Same one-line change is
  the next move for the sibling `fn_80152C00`.
* **fn_8006A1DC** (86.2% → EXACT): the L5 opaque `lis %0,%1@ha` anchor **plus
  two load-bearing companions** — a hard-pin PAIR to fix the r9/r10/r11 roles,
  and an explicit 1-insn `mr %0,%1` for the return-value copy, whose LUID is
  unbeatable by source reordering (as plain C it has the block's highest LUID,
  so the scheduler hoists it above the `lfs`).

### Already-known shapes that still cost rounds

* **fn_80121CD0** (86.4% → EXACT): clean-run store rotation is **per STORE
  CLASS, not per run** — here four zero-stores rotated right inside a 6-store
  run whose two data stores stayed put. So "source = want rotated left by one"
  must be applied to the class, not the whole run. Second: a doloop preheader's
  `li`-order pair is a **birth-order** artefact — give the loop-invariant store
  value its own named local assigned BEFORE the IV init to reverse the order
  (as statements, not a declaration initialiser — that is the L3 hazard).
* **fn_80143B7C / fn_80108E94 / fn_800AF844 / fn_80173C5C**: L4 (C literal
  instead of the extern FP symbol) — see §L4 below.
* **fn_8018BC9C** (97.4%, still parked): the compare is now right
  (`or. r9,r9,r9`, recipe from `src/fn_800CC268.c` — a pointer NULL test emits
  `or.` for a call result / incoming param / a variable **copy-assigned** from
  another pointer, but `cmpwi` for a fresh load), and only a 1-word
  branch-thread remains. That "b lands on another branch reusing its CR0" form
  occurs in **0 of 8223 promoted functions**, so treat it as a genuine
  1-instruction wall. AGENTS §6z-133's M4.18 pattern-10 verdict is retracted
  as to the compare.

## Round 4 (2026-09-28) — 4 more EXACT, and the arity scan's false-positive rate

All four are ordinary doc-15 residents. Nothing here needs a new lever; the point
is that the winning edit was a *semantic* one in every case.

* **fn_8021805C** (900B, 96.9% → EXACT): the **shared QB hash variable** was
  the residual, not the call. Draft had `temp = QB_xxx; if (a) call(temp);
  else if (b) call(temp);` — GCC folds `temp` into r3 and emits
  `li r3,H; bl` per arm, which looks right. The match needs the hash
  *materialised into a named local inside each arm* so each arm gets its own
  `lis`/`ori` pair: want has `[lis][ori][bl]` **per arm** with the constant
  re-birthed inside each one, and once that is true GCC's crossjump merges
  them back into the single `bl` that want has. So this is §6u-1 /
  earlier-§70-134 (duplication as a lever) running in reverse: the fix is to
  duplicate the constant too, and let crossjump build the shared call. Pure C,
  no emitted asm.
* **fn_8011A56C** (316B, 96.2% → EXACT) — **a new general recipe, worth
  reusing**: taking the address of an *incoming float parameter*
  (`&farg0` rather than `f32 t = farg0;`) makes the parameter
  memory-resident, so the compiler's parm spill becomes a real prologue
  `stfs` in parm order, and want has exactly that. A body-local copy does not
  spill and cannot match. Generalises to any incoming-parameter escape. Six
  DOL sites share the shape.
* **fn_8011D788** (124B, 93.5% → EXACT): the draft routed **every** access to
  `lbl_802FFE54` through one shared pointer + a hard `r29` pin, which forced
  the same web to be recomputed per site. Writing the single access as a
  direct `*(s32 *)&lbl_802FFE54` store, and staging only the *callee's*
  result, reproduced want. Both callees here are **0-arg** — the proto fix was
  score-neutral, the de-sharing was the whole win.
* **fn_80136338** (276B, 88.4% → EXACT): materialise the **modulo operand into
  a named `u32`** (`u32 m = x; m = (m + 1U) % 10U;`) instead of writing
  `(x + 1) % 10` inline. Inline, GCC picks the wrong operand order for the
  `divw`; the named `u32` both pins signedness (`divw` vs `divwu`) and fixes
  the operand colour. Same family as the earlier "name the operand" findings.

### The arity scan is a *candidate* generator, not a diagnosis

A heuristic that flags "this callee's body touches r3-r10" was run over the
parked corpus. It is worth running — but of the first 12 hits, only ~4 were
real. The three recurring false causes:

* **The callee overwrites r3 itself.** `fn_800145AC` does
  `lis r9,0x8029; mr r6,r3; ...; lwz r3,...` — the `r3` read is a dead
  scratch write of a *different* value, and the function is genuinely
  `s32 fn_800145AC(void)` (promoted byte-identical). Confirmed from four
  separate call sites.
* **r10 is not an incoming arg register.** The scanner's rA-ranges match
  r3-r10, but a call site may leave r10 holding the *caller's* value.
  `fn_800145AC` is a 2-arg-style `(global, s32)` call with only r3 set.
* **A frameless leaf has no arg registers at all** (`fn_80119470`).

Also settle the shared ground truth: `fn_8011BC38` and `fn_8011BC60` are
**0-arg `s32`** (old-style `s32 fn_8011BC38();` declarable and correct), and
`fn_800137C4` is genuinely 1-arg. `fn_80033538` reads r3 and r4 but individual
call sites may pass only one live argument — **per-caller**, as usual
(earlier §6be).

## update — dual-"+r" barrier with staged field args SOLVED fn_801FB550 (2026-10-20)

Signature: want `[lwz r6][addi r4][lwz r7][mr r5][addi r3]` at a 7-arg call;
every plain-C shape emitted the `addi r4` (a hoisted pinned `temp_r4`) either
last (pos3, 97.75%) or, with a lone `"+r"(temp_r4)` barrier, first (overshoot
above the `lwz r6`, still 97.75%). Fix: stage the two field args into locals
on either side of ONE barrier that constrains both values —
```c
a34 = arg0->unk0x34;
temp_r4 = (char *)gp_item + (s32)8;
__asm__("" : "+r"(temp_r4), "+r"(a34));
a30 = arg0->unk0x30;
fn_...(..., a34, a30, ...);
```
The taller use-chain (a34, live to the call) emits its lwz before the
barrier-near addi; the post-barrier read lands third. 97.75% → EXACT,
promoted DOL-identical. General rule: a single-"+r" barrier on the hoisted
value alone over-hoists; constraining the EARLIER load in the same barrier
lets list-scheduling priority order the pair. (Bare reads DCE away — the
staged values must be bound to locals passed to the call.)

## update — compiler-version sweep: the residual is NOT a version artefact (negative result)

The walls in this doc (transposed independent store/load/copy pairs, rotated
constant webs) look like a different ProDG *build*, so that was measured
directly: five compiler versions in `build/compilers/ProDG/` (3.5, 3.5b140,
3.7, 3.8.1, 3.9.3) were used to compile the same drafts of twelve parked
members (2-word transpositions at 94–99%). Every version that compiles a given
draft produces **byte-identical output**, i.e. the same transposition and the
same differing word count; the only version differences seen were header
parse errors in the older front ends. (`ngccc.orig.exe` in the same directory
is not a working alternative driver — it rejects the project's argument
form.)

Same round, same members, no lever moved any of them:

- flag sweep over 95 near-miss drafts × 10 flags (`-G8`, `-G256`,
  `-fno-schedule-insns2`, `-Os`, `-fno-strength-reduce`, `-fno-inline`,
  `-fno-expensive-optimizations`, `-fno-thread-jumps`,
  `-fno-rerun-cse-after-loop`, `-fno-gcse`): no draft reached 100%, and the
  best score per draft never improved on the default flags.
- `-fno-schedule-insns` / `-fno-schedule-insns2` / both, plus `-fno-regmove`,
  `-fno-caller-saves`, `-fdelayed-branch`, `-fno-delayed-branch`,
  `-fno-function-cse`, `-fno-inline-functions` on a single member: identical
  word count every time. (The flags do work in general — `-fno-schedule-insns`
  demonstrably changes load order on a hand-written test — so the drafting
  conclusion is that these functions' insn order is decided *before* sched1.)
- automated statement-order hill climbing (all adjacent swaps plus all
  single-statement moves, iterated to a fixed point) and declaration-order
  search over the same bodies: no improvement at all, i.e. the parked source
  order is already the local optimum for this compiler.
- a clean rewrite of a 72-byte member (fn_80250E24) from scratch reproduces
  the size and the register assignment exactly but still differs in the same
  three-word head order, so the gap survives losing every line of the
  inherited draft.

Practical consequence: for this family, re-spelling the source is exhausted;
a draft that sits at 94–99% with an adjacent transposition should be parked
with the sub-family signature rather than re-derived. The two things that DO
still move members are semantic (type/width/prototype of a callee or field)
and the barrier tricks documented above.
