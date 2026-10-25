# doc 75 — a reload/arg register pin fixes TWO "independent" residuals at once; and `lwz r0` vs `lwz r4` at a post-call reload is an allocator artefact, not a scheduling one

**Status:** NEW LEVER, found 2026-10-01. Two EXACTs (`fn_80191E8C`,
`fn_8016D52C`) plus one 83.3% -> 95.8% gain (`fn_8022BA54`) and a first corpus
sweep win (`fn_8023B1B8` 52.8% -> 57.9%) in a single sitting. Read this BEFORE
grinding any park whose residual contains (a) a post-call reload of an
out-param slot, or (b) a `mr r3,<home>` that want places at the TOP of a
pre-call window. Automated by `tools/reload_pin_sweep.py`.

## The shape

A pre-call or post-call window has a residual made of what look like two or three unrelated scheduling problems: for fn_80191E8C retail stores r3 to frame offset 8, loads constant high 0x2d7 into r4, completes it with low 0xe03d, moves r31 into r3, builds the spill address at frame offset 8 into r5, zeroes r6, calls, then reloads frame offset 8 into r4 and tests r4 against zero, while the build moves r31 into r3 before completing the constant and reloads into r0 instead of r4 for the test; for fn_8016D52C retail moves r29 into r3 first, derives r24 as r29 plus 0x158, zeroes r28, accumulates with r26, copies r24 into r25, stores to offset 0x340 of r29, derives r27 as r29 plus 0x190 and calls, while the build emits the r24 derivation before the r3 move and orders the r25 copy, zeroing, accumulation and store differently around the same call.

`fn_80191E8C`'s four words were previously parked as "GCC scheduling
coin-flips (ori/mr order + lwz r4 vs r0 for sp8 reload) that resist void<->s32,
param-type, staging, and all schedule flags". `fn_8016D52C`'s four words were
parked as "a doc-15 arg-setup scheduling artifact ... 3 statement orders x 5
flag combos resist".

## The fix — ONE declaration pin, ZERO semantic change

`fn_80191E8C` (95.1% -> **EXACT**, 82/82, object exactly 328B):

```c
    register s32 sp8r4 __asm__("r4");   /* the GetChecksum_2 out-param reload */
    ...
        sp8 = temp_r3;
        GetChecksum_2(temp_r31, QB_TRIGGER_OBJ_ID, &sp8, 0);
        sp8r4 = sp8;
        if (sp8r4 != 0) { ... }
```

`fn_8016D52C` (95.6% -> **EXACT**, 91/91, object exactly 364B):

```c
    register void *carg __asm__("r3");   /* the call's argument */
    ...
        carg = a0;
        var_r24 = (char *)a0 + 0x158;
        var_r28 = 0;
        ...
        fn_8016E1B4(carg);
```

`fn_8022BA54` (83.3% -> 95.8%): `register void *pv9 __asm__("r9");` on the
second reload of `sub->unk0x10`.

These are DECLARATION pins, not inline asm — the sanctioned lever. No
statement order, no flag, no type change, no prototype change.

## Why one pin clears several residuals

ngccc's `reload` colours a reload pseudo by scanning for a free register. At a
**post-call reload, r0 is always free**, so r0 always wins and the reload is
always `lwz r0`. Pinning that one reload to `r4`:

1. gives the `lwz` its want-side register;
2. **reserves r4 across the whole call-setup window**, so r4 can no longer be
   the home of the QB constant — the constant materialises in r4 and the
   arg0 `mr r3,r31` is finally emitted *after* the `ori`, i.e. in ARG ORDER,
   which is what want has.

Same mechanism in `fn_8016D52C`: pinning the call's argument to r3 reserves r3
across the window, which hoists `mr r3,r29` to the window top *and* pushes the
r25 callee-saved home copy (`mr r25,r24`) past the `li r28,0`.

And in `fn_8022BA54`: the window needs THREE registers (r10 anchor, r0 first
reload, r9 second reload); unpinned, ngccc only ever uses two, collapsing the
reloads onto r10 and pushing the anchor into r9. Pinning the second reload to
r9 splits them.

**The residuals were never independent.** They were two views of one
register-allocation decision, and the pin is the lever on that decision.

## Corollary for the road (this is the reusable bit)

Recipes §7e-2 says "a product web and its offset web need SEPARATE pins"
(`fn_800AC9B4`). This is the mirror image: **one pin on a reload or an argument
fixes a reload residual AND an arg-order residual, because the pin's register
was previously squatting on a different value.** So:

> Before grinding a doc-15 "arg-setup order" residual, work out which register
> the *other* value (the constant, the anchor, the home copy) is squatting in.
> Pinning the reload to that same register re-flows the whole window for free.

This is strictly cheaper than the alternatives, all of which were measured
byte-neutral on `fn_80191E8C`: the M8.31/§7e-1 return-type hypothesis
(`GetChecksum_2` void vs s32), the 3rd param as `volatile s32 *`, the constant
as a named local / built from halves / pinned, the call written with a
`s32 *p8 = &sp8` pointer arg or `(sp8 = temp_r3, 0)` comma-folded into arg3,
`sp8` as `volatile s32`, and pinning temp_r31's arg0 copy into r3. 32
prototype x call-shape x local-type variants, all byte-identical.

## The tool, and two implementation traps

`tools/reload_pin_sweep.py` automates this. It pins, for every local of a
draft, each of r0/r3-r12 in turn, retypeing the WHOLE web. Two traps cost most
of the build time and are worth not repeating:

1. **The pin must cover the whole web.** Renaming only the assignment
   (`prev_pin = *EXPR;`) while the uses still say `prev` pins nothing — the
   positive control reported a uniform, false "0 wins". `build_variant`
   retypes the declaration and every subsequent use.
2. **Pointer types must stay pointers.** Deriving the pin's type from a
   name-to-scalar table turns `void *prev` into `register s32 prevpin`, which
   both changes the arithmetic and lets cc1 drop the pin. `pin_type()` keeps
   `*`.

Also worth knowing: `gen_leaves.compile_fn` writes
`<LEAF_TMPDIR>/fn_ADDR.c|.o`, and `LEAF_TMPDIR` only guards across
*processes*. A `ThreadPoolExecutor` inside one sweeper races on the same
address and the failure surfaces as an `ELFParseError` from elftools, which
reads like a corrupt toolchain rather than a race. The sweeper splits a scratch
dir per thread (`_scratch()`).

## Positive control (recipes §7e)

The first three cuts of the sweeper all reported "none" on `fn_8022BA54` —
including after its body was correct — and each was a bug in the sweeper, not a
real null result. Only stripping the known-good pin from the draft and
confirming the sweeper **rediscovers** it made the tool trustworthy. Do that
before trusting any "0 wins" run from it.

## What it does NOT fix

* `fn_801A1B2C` (90.0%, size-exact): residual is `li r0,0` vs `lfs f4` order —
  a constant-materialisation tie. Pinning r0 (the zero), r3, r4, r5 and r3+r4
  are all 90.0%. Genuine wall, already documented in the draft.
* UPDATE 2026-10-09: that wall fell to a non-pin lever — `extern const f32`
  on both rodata loads lets sched2 sink the `lfs` past the zero-store tie
  (90.0→EXACT, promoted; recipes §7n). Lesson: run the const-sweep before
  declaring a constant-order tie genuine. The other two non-fixes stand.
* `fn_8004F6B8` (94.3%): residual is 6 words and ALL of them are the frame size
  (0x20 vs 0x28). Pinning the cursor pointer to r28 gives 40.0%. The frame
  needs a genuine 12-byte object AND a register-form address for the two link
  clears, and those are still mutually exclusive; every padding shape
  (`volatile double` before or after the cursor, a 12-byte struct declared
  after it, a whole-web `cp` pin) is byte-neutral at 94.3%.
* `fn_8022BA54` residual (a), the `strncpy` arg-move order: pinning dst to r3,
  src to r4, or both is byte-neutral at 95.8%. It is a doc-15 wall.
* `fn_8022BA54` residual (b/c), the `lbl_802FFE98` anchor wanting r10: this is
  docs/parkings/73 (HI16 reload set is `{r9, r11}`); pinning the anchor
  variable directly is much worse (79.2% / 75.0%) because it forces the
  address through a register instead of a `symbol_ref` MEM. Still parked: the
  anchor and its load split into two asm blocks (`lis 10,@ha` early,
  `lwz %0,@l(10)` at the use) reproduces the bytes exactly, but those are
  hand-written instructions, so it is not a source solution and is not
  promoted. See docs/parkings/solved/73 §"The lone-anchor case".

## Score ledger for this sitting

| fn | before | after | note |
|---|---|---|---|
| `fn_80191E8C` | 95.1% | **EXACT** | r4 reload pin |
| `fn_8016D52C` | 95.6% | **EXACT** | r3 arg pin |
| `fn_8022BA54` | 83.3% | 95.8% | r9 second-reload pin |
| `fn_800F4450` | 90.6% | 94.1% | not a pin — see below |
| `fn_8023B1B8` | 52.8% | 57.9% | r4 swap-temp pin (sweeper) |

`fn_800F4450` is a counter-example worth keeping: no pin helps it at all
(-Os/-O2/no-flag/-fno-sched-interblock are all 94.1%, and the pin sweep reports
none). Its 3.5% came from two plain **arithmetic** bugs — a scaled-pointer
stride (`var_r9 += 0x18` on an `s32 *` compiles to `+0x60`) and a loop counter
of `0x30` where want has `0x48`. Its old park note blamed "doloop CTR
strength-reduction"; that diagnosis was wrong, and the note is corrected in
place. Reminder: re-derive the arithmetic before grinding the scheduler.
## 2026-10-08: the pin also closes a HIDDEN branch-target gate — `fn_8013A7D4` EXACT + promoted

Third sitting on this lever, two new results.

**1. A local pointer web that the sweep finds, not a reload**: `fn_8013A7D4`
(252 B) sat at 95.24% (60/63) parked as an "allocno preference, not a source
shape" wall: the small-delta arm's `arg0->unk0xC` pointer web was coalesced
onto r11 (the colour blocks 10/12 use) while want has r10. `tools/reload_pin_sweep.py`
does not need the value to be a *reload* — any `NAME = EXPR;` site counts:
site `temp_r10_2 -> r10`, one declaration edit
(`register Unk_BDBFA817 *temp_r10_2 __asm__("r10");`, pointer type kept)
took the masked score to **100.00%**. The 3-word residual closed exactly.

**2. The masked 100% was NOT the match — `promote_wip.py` refused it.**
`REFUSE: 1 internal branch target(s) differ — 0x8013a81c want ('beq',
0x8013a8b8) got ('beq', 0x8013a8b4)`. The REL14 mask keeps only opcode+BO+BI,
so a jump that lands 4 bytes off (one instruction) is invisible to every
score in `test_wip_drafts`/`diff_near`/`want_got`. Want's `p->0x4930 == 0`
edge jumps **past** the `lwz r11,0x10(r3)` reload, i.e. that path still uses
the value loaded at 0x3c; the reload exists only for the block_11 fall-through.
The compiler puts a single reload at the join, so every "natural" body jumps
*to* it. Fix = SOURCE SHAPE, not a flag:

```c
    if (temp_r0 != 0) {
        ...
        if (d > 1) {
            if (d > 0x1388U) { ...; goto ret; }
            temp_r10_2 = *((Unk_BDBFA817 **)&arg0->unk0xC);
            temp_r10_2->unk0x17F8 += d - 1;
            temp_r11 = *((void **)&arg0->unk0x10);   /* reload lives HERE, */
        } else {                                      /* ...in the arm     */
            goto block_13;
        }
    } else {
        goto store;             /* jumps PAST the reload → the beq target */
    }
store:                          /* shared diamond: the store has no load */
    temp_r11->unk0x4930 = *temp_r8;
    goto ret;
block_13:
    temp_r11->unk0x4930 = temp_r9_2;
ret:
    return 1;
```

Two details are load-bearing: the `store:` label must be the target of the
`p->0x4930 == 0` goto (that is what makes the beq skip the reload), and the
tail must be written in the literal order `[store][goto ret][block_13][ret]`
— moving `block_13` after `ret:` re-orders the whole tail (93.7%).

**Road rule (corollary to §"Corollary for the road" above)**: after any pin
sweep that reports a draft at 100.0%, run the promotion check *before*
believing it. The masked score cannot see REL14 targets; expect the win to
be "pin + one hidden branch-target shape". `fn_80174D1C` in the same sitting
went 79.49% -> 97.44% on one pin (`var_r9 -> r9`) and is now a single word
(`or. r3,r3,r3` vs want's `cmpwi r3,0` on a `||`-short-circuited call result)
from EXACT.

## 2026-10-08: the pin also fixes reload picks at *compare* sites

`fn_801B3220` (756B) was parked at 98.94% with TWO differing words: at address 0x801B33C4 retail reloads stack offset 0x20 into register r3 while the build loads it into r9, and at address 0x801B33D0 retail compares r3 against r0 while the build compares r9 against r0.

— the reload of `sp20` (the `&sp20` out-param of `GetChecksum_2`) feeding
`if (sp20 == QB_WAIT_ANIM_FINISHED)`. The parked note had concluded "the house
fallback is banned for this pass (no `__asm__`)"; that was a self-imposed rule.
The lever is the same declaration pin, applied to the **loaded value**:

```c
    register s32 vw __asm__("r3");            /* function-scope decl */
    ...
    if (GetChecksum_2(sp1C, QB_EXIT_STATE_ACTION, &sp20, 0) != 0) {
        vw = sp20;                            /* <- the reload, homed r3 */
        if (vw == QB_WAIT_ANIM_FINISHED) {
```

Result: 100.00% masked, 0 diffs, size EXACT, promoted (DOL byte-identical).
r3 is free there (the callee's result was just consumed by `cmpwi r3,0`) and
the pinned temp dies at the compare, so nothing else moves.

**Two things worth carrying forward:**

* Pin the *value*, never the memory variable. `register s32 sp20 __asm__("r3")`
  on the stack slot would force the whole variable into a register and break
  the address-taken out-param.
* `tools/reload_pin_sweep.py` cannot see this site class: its regex covers
  `NAME = EXPR;` and first-arg call sites, not operands of a compare, a
  `switch`, or the callee-position of a nested call. When a parked draft's
  residual is a *single-word reload register pick* (`lwz rN,off(r1)` /
  `lfs fN,...` differing only in N, or `addi rN,r1,off`), hand-write the
  named-temp pin even though the sweeper reports "none". Finding the rest of
  this class: `tools/regdiff_scan.py` flags any draft whose differing words
  are all register renames (its `RENAMABLE` set already includes
  `lwz`/`lfs`/`cmpw`/...) — a hit there is a pin candidate, not just an
  allocator wall.

**Also closed this round (negative, do not re-spend):** `fn_80195B14`'s
"next lever (a)" (disable/reorder ProDG's `addressof` pass) is dead —
`strings` on `cc1.exe` finds bare `addressof` at 0x1B33C8 only inside the
RTX-code-name table (`rtx_name[]`, between `queued` and `symbol_ref`) and
`.addressof` as the `-da` dump name; the `f_options` table has no entry, and
GCC 2.95 strips the `no-` prefix and matches the remainder against that table,
so `-fno-addressof` cannot exist.
