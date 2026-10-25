# Issue 10 — Pure regalloc coin flip (saved-register assignment swap)

**Status: ✅ SOLVED (M4.93) — fn_80201C80 promoted, DOL byte-identical.** The "coin flip" was not pure regalloc: the draft's call `fn_802010FC()` was **missing its argument**. The real call is `fn_802010FC(arg0)` — the callee does `mr r30, r3; lwz r0, 0xa9c(r30)`, proving it reads r3 as an object pointer. Passing arg0 extends arg0's live range across the call (used before as the argument, after in the stores), which flips GCC's saved-register allocation to the game's exact mapping.

## The problem

fn_80201C80 (76 bytes) is a small guarded setter. The game assigns the saved
registers as **r31 = arg0, r30 = arg2**; GCC assigns **r30 = arg0, r31 =
arg2** — a pure allocation swap with identical semantics.

Original (fn_80201C80): the function opens with a 0x18-byte stack frame, saves the link register and registers r29 onward, and homes the three incoming arguments into saved registers with the game's mapping (arg0 into r31, arg1 into r29, arg2 into r30). It then calls the helper, tests the call result against zero with an early-out branch, reloads offset 0xA20 through the arg0 home, compares arg2 (via r30) against that field with a second early-out branch, and on the taken path stores arg1 to offset 0xA1C of the object before falling through to the epilogue.

Compiled: `mr r30, r3; mr r29, r4; mr r31, r5` — r30/r31 swapped. 5 masked
diffs, 8 total; the C is correct, only the register roles differ.

## Why it was parked

- C source was believed to be: `if (fn() && arg2 != o->0xA20) o->0xA1C =
  arg1;`
- With `fn()` called with no arguments, every declaration/statement ordering
  produced the same swap — GCC 2.95.2 allocates r30 to the *first* saved arg
  (arg0) and r31 to the *last*, while the game compiler did the opposite
  (r31 = first-saved). 5 masked diffs / 8 total.

## What was tried (all failed to flip the allocation)

- Reordering arg uses, renaming variables, different comparison directions,
  `register` hints, typed pointers, inline helpers, ternary coercion,
  explicit `asm("rX")` register variables, nested-if structures, live-range
  extension via a dummy trailing store (that last one *did* flip the
  allocation to the game's mapping but added an extra store instruction).
- **Declaration-order permutation was NOT tried** - the class crashwoc
  automates (see note below).

## The actual cause (M4.93)

The m2c draft declared the call as `fn_802010FC()` with **no argument**, but
`fn_802010FC` really takes `arg0`: at its entry it copies the incoming r3 into r30 and shortly after loads offset 0xA9C through that register, proving r3 is an object pointer.

The want code at 0x80201C90 does `mr r31, r3` *before* `bl 0x802010fc` — r3
still holds arg0 at the call. Passing arg0 into the call makes arg0 live
**across** the call (argument before, pointer derefs after), which raises its
allocator priority and flips the mapping to the game's exact
`r31=arg0 / r30=arg2 / r29=arg1`.

```c
s32 fn_802010FC(void *);
void fn_80201C80(void *arg0, s32 arg1, s32 arg2) {
    if ((fn_802010FC(arg0) != 0) && (arg2 != *(s32 *)((char *)arg0 + 0xA20))) {
        *(s32 *)((char *)arg0 + 0xA1C) = arg1;
    }
}
```

→ **100% byte-exact (76B), promoted, DOL byte-identical (2689/11431).**

## Lesson for future drafts

A "pure regalloc swap" may really be a **missing call argument**: before
parking on regalloc, disassemble every callee and check whether it reads r3
(or any caller-saved register) as a value that the call site still holds.
The m2c call reconstruction drops arguments when it cannot resolve the
callee signature.

## Harvest sweep (M4.93 → M4.94)

An automated sweep of `src/wip/fn_*.c` looked for drafts that call
`fn_XXXXXXXX()` with no arguments while the callee's first ~8 instructions
copy r3 to a register and load through it (the fn_802010FC pattern).

- **M4.93 first pass was broken**: the draft-body extractor split on the
  string `#include`, leaving a stray `"types.h"` in the compiled
  source → every draft "failed to compile", 764 were skipped, 0 tested.
- **M4.94 fixed the extractor** (strip `//` and `#include` lines) and
  cleared the compile-FAIL backlog (60 real failures → 0, 58 via generic
  postprocess rules + 2 per-address), then reran: **all 8725 drafts compile;
  112 tested; 4 improved** (fn_80127370 +22.4, fn_8019C1F4 +5.4,
  fn_801B2EAC +5.2, fn_8020D530 +3.7). All 4 callees verified to read r3 as
  a pointer; injections written back to the drafts.
- **Why so few improved**: the naive "add arg0 to every no-arg call" is
  wrong for most candidates — those callees legitimately take no args, and
  the injected arg changes codegen (most candidates *regressed*). Only
  where the callee provably derefs r3 does the injection help, and even
  then the drafts are dominated by other diffs (so they improve but don't
  reach EXACT).

Lesson: the callee-signature check (disasm the callee, look for `mr rX, r3`
+ load) is the *necessary* filter; only inject when it passes.

## Remaining members + the decl-order lever (M8.37, 2026-08)

The remaining register-role-swap members of this family (M8.37: 8000E104,
801A4F84, 80055134, 80076EEC/8021D454, 8007DCD8 - and the doc-10 audit tail
in AGENTS.md §6h/4p) pass the callee check clean and resist every
rename/ordering/asm trick. **Declaration-order permutation was tried
2026-08-23 and retired** - automated 720-perm sweeps (plus flag sets
per permutation) have ZERO effect on m2c-shaped bodies
(`docs/parkings/README.md` technique-table item 10,
`docs/parkings/15-call-arg-setup-scheduling.md:39`). crashwoc's
`ai_decl_permute.py` recipe (Sims2's r11/r9 coloring-wall fix) does not
transfer to this class; decl-permute retired repo-wide (README item 10,
doc15:39) — do not build
`--decl-permute` for these members.

### 800CC358 (136B, 3 word diffs) - select-coalesce tail flip

WANT tail materializes the final select **in the return register r3** with an
inline default-0: it compares the node pointer in r9 against zero, sets the return to 0 first, branches past the adjustment when the node is null, otherwise subtracts 4 from the node into the return register, then loads the result from offset 0x38 of that adjusted pointer and returns. Every GOT variant instead materializes the select into a scratch register and duplicates the return-0 epilogue: the null branch skips to a separate block that zeroes the return after the load path, with the adjusted address held in r11 rather than the return register and the load feeding r3 from there.

Tried ~35 variants (V1-V78): ternary return, named ret var, direct return of
select, struct member access with -4 arithmetic, scaled index `[0xE]`,
char* arithmetic, default-0 then conditional assign, if/else split, folded
0x34 vs split -4/+0x38. ALL keep the r11+shared-epilogue form or restructure
the head (7+ diffs). WANT's head (words 0-26) matches perfectly; only the
final 3 words resist. Same family as 800689D4/80068A98 (AGENTS recipe-2) and
doc-10. Source form is settled at V67 (checked into src/wip/fn_800CC358.c).

### 8000A6D4 (92B) — SOLVED 2026-08-31 via temp DECLARATION ORDER

Byte-wide table CRC (`crc = TBL[(u8)crc ^ data[i]] ^ (crc>>8)`). The two
residual diffs were the loop's middle-register web choice: WANT masks crc
into r9 (`clrlwi r9,r3,0x18`) and loads the data byte into r0 (`lbzx r0`);
GCC reversed them (mask→r0, load→r9). Both semantically identical →
classic doc-10 style flip.

**Breakthrough: it's the order the two u8 temps are DECLARED.**

```c
for (i = 0; i < len; i++) {
    unsigned int b = (unsigned char)data[i];  // want r0  (declare FIRST)
    unsigned int lo = (unsigned char)crc;      // want r9  (declare SECOND)
    crc = lbl_802FFA3C[lo ^ b] ^ (crc >> 8);
}
```

The prior draft declared `lo` first (`unsigned char lo = (u8)crc; ...
TBL[lo ^ (u8)data[i]]`) which folded the byte load into r9 and mask into r0.
Swapping the two declaration statements selects the WANT web allocation →
EXACT 23/23, promoted. Register-pinning r0/r9 instead collapses to 4/23
(changes prologue/scheduling globally), so declaration order, not pins, is
the lever here.

Success pattern to retry on other doc-10 regalloc flips where the two
temporaries feed one xor/select: vary the local declaration ORDER before
trying pins, since ngccc's web allocator walks locals in declaration order.

## 2026-09-24 — two more doc-10 flip levers (both promoted EXACT)

### (a) Pin a SCRATCH-WEB walker to its want register (fn_80054DC4)

`fn_80054DC4` (88B, list search by key) sat at 59.1% for two sessions with a
note claiming the residue was "a pure 2-register colour swap ... not reachable
from the source shape at all" — every plain/typed spelling really did compile
to the identical object.

want: `mr r10,r3` (arg0 home) + cursor kept in **r11** (`lwz r11,...`);
got: arg0 in r11 and the cursor in **r3** (coalescing with the `void *` return
register).  The lever that cracks it is the §6y-124 scratch-web pin:

```c
register s32 cur __asm__("r11");   /* s32 alias — a void *-typed pin is
                                      silently dropped by cc1 (§76-178) */
cur = (s32)*(void **)&lbl_80364C28;
...
cur = (s32)var_r9;
```

→ EXACT 100% in one edit.  Pinning the *other* web (arg0 → r10) only reaches
68.2%, so pin the WALKER, not the key.  Reusable rule: when a doc-10 flip is
about which register a loop cursor lives in and the cursor is re-loaded from
memory (or handed to a call) every iteration, a hard-register pin on the
cursor is a first-class lever — it is NOT "unreachable from the source shape";
it is unreachable from *spellings* of the source.

### (b) r0-pinned scaled index forces the indexed-store operand slots
### (fn_80174558)

want scales the index in r0 and stores indexed with base r9 and index r0 (base in rA, index in rB) while got scales in place in r4 and stores indexed with the operand slots swapped. r0 is only legal in the **rB** slot of an
indexed access (rA==r0 means a literal zero base), so the addressing printer
swaps an r0 operand into rB — but the allocator only chooses r0 for the shift
destination if the index web is *pinned* there:

```c
register s32 off __asm__("r0");
off = arg1 * 0x10;
*(s32 *)(base + off) = (s32)arg2;
```

→ EXACT 100%.  Named `off`, `arg1 << 4`, typed-index (`((s32 *)base)[arg1*4]`),
struct-row-array and offset-first spellings all still colour r4 (63–91%).
Reusable rule: an indexed load/store whose want form has an r0 operand and a
non-r0 base is fixed by pinning the *scaled index* to r0; do not chase the
expression shape.

### fn_800F3BB0 — SOLVED as a regalloc flip too: hoist-vs-reload of a pointer member (2026-10-02)

`fn_800F3BB0` (460B) was reported `DIFF 11.3%` and reached **`NEAR 96.5%`**,
exact 460-byte `.text`, no private `.rodata`. Two of the residuals looked like
independent walls; they were **one** edit — the draft's local pointer temp:

```c
CStruct *ent = arg0->unk0x20;          /* WRONG: kills the reloads */
ent->unk0x10 = arg3;
ent->unk0x10 |= 8;
fn_80013294(arg0->unk0x20, fn_800F39DC, arg0, 0);
```

vs. the WANT form (which also fixes the saved-reg allocation):

```c
typedef struct { char pad[0x20]; CStruct *unk0x20; /* POINTER member */ ... } Obj;
arg0->unk0x20->unk0x10 = arg3;
arg0->unk0x20->unk0x10 |= 8;
```

* `ent` in a register lets GCC fold `x = a; x |= 8` into one `x = a | 8` and
  reuse r9 as the base, producing `li r0,8 ; stw r0,0x10(r9)` — 2 instructions
  short. Writing `arg0->unk0x20->…` **three times** forces the reload of
  `arg0+0x20` before each use (the store to `->unk0x10` may alias the pointer
  member itself), which is exactly the want's
  `lwz r9,0x20(r31) … lwz r9,0x20(r31) … lwz r3,0x20(r31)` triple.
* The same edit **flipped r28/r29** (want `r28 = arg3`, `r29 = arg2`; got the
  swap) — so this "pure regalloc coin flip" was again a downstream symptom, in
  the same family as fn_80201C80 above. The lever was never a rename or an
  ordering: it was *removing a redundant local* so the reloads (and the extra
  live range that goes with them) exist.

**Reusable rule:** when a want shows the SAME `arg0->OFFSET` reloaded 2-3 times
around stores through `arg0->OFFSET->FIELD`, the draft must (a) declare that
member with a POINTER type and (b) index through `arg0->OFFSET->FIELD` at every
use with **no local pointer temp**. A local temp is not a stylistic choice — it
removes the aliasing reloads that define the want. Also expect the saved-reg
mapping (doc-10 flips) to correct itself once the reloads are back; don't chase
the register swap first.

Sibling residual still parked there: the doc-15 `expand_call` window
`li r4,0; li r5,0; li r6,0; li r7,0` vs ngccc's `li r7,0` hoisted above the
other three — identical to fn_801587C8, resistant to every pure-C spelling and
to 18 optimisation flags.
