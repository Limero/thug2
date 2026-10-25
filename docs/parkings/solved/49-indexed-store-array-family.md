# 49 — Indexed-store object-array family (indexed lwzx/stwx base-folding)

**Status: CLOSED (2026-09-02) — all members solved.** First catalogued on
`fn_8000F95C` (array-push) and `fn_8000F320` (stack-pop); `fn_8000F9C4`
(array-remove) shares the loop half. **fn_8000F320 promoted 2026-08-31,
fn_800F164C (load half) promoted 2026-08-31, fn_8000F9C4 EXACT in wip
2026-09-02 (`-fno-gcse`), fn_8000F95C EXACT in wip 2026-09-02 (no flags)** —
see §2026-09-02 below. These are the allocator/pool-subsystem array accessors
just above the fn_8000F10C dispatch family. The two 2026-09-02 EXACTs are
INERT (the .sdata2 +0x40 promotion blocker applies).

## The shape (push = fn_8000F95C, 10/26)

Want keeps the array base (self plus 4) in a dedicated base register, reloads the count, scales the index as count times 4 into r0, performs the indexed store of the object with base-plus-index addressing, and only then increments the count and writes it back. Got (every source form) instead folds the scaled index into the base with an add and emits a plain displaced word store with no indexed addressing.

## Why ngccc cannot reproduce it

- want keeps the array base (`self + 4`) in a **dedicated register** and
  emits an **indexed `stwx`/`lwzx`** with the scaled index in the *other*
  register. ngccc strength-reduces `base[index]` into `add base,idx` + a
  plain `stw` `disp(base)`.
- The store/increment order is second-class: want increments the count AFTER
  the store; ngccc hoists the increment. Both are register-allocation
  scheduling artifacts (route: doc-47 preheader / doc-48 store-group).
- For the remove (fn_8000F9C4) the loop is **identical** to want except the
  array-base `addi r11,r3,4` is computed after the entry guard — that is
  precisely doc-47. Using a live count **field** in the loop condition
  (`i < *(s32 *)((char *)self + 0xc4)`) gets 24/36 with the removal swap and
  vtable dispatch byte-identical; the residue is the base placement.
- Best attempts: F95C 10/26, F9C4 24/36, F320 ~1/15 (F320 also reloads
  self->0x110 and recomputes the 0xcc top in a base/index coin).

## Known members / scale

- **fn_8000F95C** (0x68, 10/26) — array-push of a 0xb8 object (fn_800098F4 +
  fn_80011CA4 init), then `arr[count]=obj; count++`.
- **fn_8000F9C4** (0x90, 24/36) — array remove-by-value + optional vtable
  dispatch; the doc-47 loop-base residue.
- **fn_8000F320** (0x3C, ~1/15) — stack/top-pointer pop with indexed stwx.

## Route not found / open ideas

- The indexed `stwx` is emitted when the base is a **named non-folded
  register** — a `register`-qualified `void **arr` local that ngccc must keep
  live across the increment has not produced the wanted rA/rB split yet; a
  `__asm__("" : "+r"(arr))` pin (recipe-99 style) on the base register is the
  untested next lever.

## 2026-08-31 — PROMOTED member: fn_800F164C (indexed lwzx via struct-element access)

**fn_800F164C was promoted (124B, DOL byte-identical) — the first solved
member of this family.** It is the LOAD half (lwzx) of the indexed-access
wall, and it cracked with a source-shape lever the doc didn't try:

- WANT computes the row base `arg0 + 0x10010` into a dedicated register
  (`addis r9,r29,1; addi r9,r9,0x10`), scales the index `arg1` by the
  12-byte element stride (`mulli r0,r28,0xc`), and combines them with an
  indexed `lwzx r30,r9,r0`.
- **GOT-with-flat-cast** (the original draft, and what every pointer
  arithmetic form did): folds index×stride into the base register and emits a
  plain `lwz` with displacement — `mulli r9,r28,0x30; add r9,r9,r29; addis
  r9,r9,1; lwz r30,0x10(r9)` (draft, 74.2%).
- **The lever**: declaring the pointer as a **struct-element array** and
  accessing element field 0 of the first word — `typedef struct { s32 p; s32
  q; s32 r; } Ent; trial = ((Ent *)((char *)arg0 + 0x10010))[arg1].p;` —
  makes ngccc emit the exact `mulli`-scale + dedicated-base + `lwzx` want
  (8-word addressing residue dropped to 0). A flat byte arithmetic cast
  (`*(void **)((char *)arg0 + 0x10010 + arg1*0xC)`) folds the index instead.
- **Second requirement after the addressing match**: the loop bound must not
  be a named var if want re-loads it per-iteration in *different* registers
  (guard `lwz r11,4(r30)` vs back-edge `lwz r0,4(r30)`). Writing the bound as
  a direct memory expression `*(u32*)((char*)temp_r30 + 4)` in both the
  peeled guard and the do-while condition reproduces want; CSEing it into a
  `u32 n` collapses the loop to a branch-to-bottom-test and shuffles the
  whole tail.**Takeaway for doc-49**: try a struct-element-typed array access on the load
    members before assuming the indexed form is unreachable — ngccc WILL emit
    rA/rB `lwzx` for `arr[i].f0` when `arr` is an element-typed pointer, where
    flat casts fold the stride into the base. Whether the same holds for the
    `stwx` (store) members (F95C/F9C4/F320) is untested.

## 2026-08-31 — indexed-order coin: base/index in wrong rA/rB slots (OPEN)

The remaining doc-49 members (F9C4, F320) crack the *addressing* but hit a
second, harder wrinkle: ngccc emits the indexed `lwzx`/`stwx` with the base
and index registers in the OPPOSITE operand slots to want.

- **F9C4 (94.4%, was 24/36 = 66.7%):** the doc-47 base-placement residue
  closes by declaring the array base as a NAMED pointer INSIDE the loop body
  (`void **arr = (void**)((char*)self+4);` first stmt of the for-body) so
  ngccc places `addi r11,r3,4` where want has it (in-loop, right before its
  first use), not hoisted to the prologue. That leaves exactly 2 REAL words:
  `lwzx r0,{rA},{rB}` (word 15) and `stwx r9,{rA},{rB}` (word 22) encode
  (base,index) as want's (r11,r10) vs got's (r10,r11) — same registers, swapped
  rA/rB. Resisted: i as u32, precomputed removal-index `m`, intptr_t cast,
  void* value temp, explicit `i*4` byte-pointer indexing, and named-pins of
  base(r11)/idx(r10). Registers hold identical values; only the encoding slot
  differs.
- **F320 (~1/15 → front-9 WORDS EXACT via named pointer):** a named
  `void **stack = (s32*)(self + 0xd0); stack[count] = -1;` variable (as in the
  fn_800F164C lever) makes ngccc emit want's indexed `stwx r10,r11,r0` exactly
  (words 0-9 = prologue + reload + stwx all byte-identical). Residue is now
  only the tail: want merges the `if(count) ptr : 0` stores into ONE
  `stw r9,0xcc(r3)` by reusing count's r9 for the pointer build and `beq`
  skipping to a shared store; ngccc insists on a 2nd block / the pointer built
  into a scratch `r8` instead of r9. The register-ROLE (build into r9 not r8,
  one store) is the doc-46 regalloc-home wall.

**SOLVED 2026-08-31 — fn_8000F320 promoted to EXACT (60B, DOL byte-identical).**
The r9 role came from pinning count to r9 (`register s32 count __asm__("r9")`
+ the named-pointer stwx, front-9 done), and the LAST word (want `add r9,r9,r3`
vs got `add r9,r3,r9`) was flipped by spelling the tail build with an UNSIGNED
shift term: `count=(s32)((s32)((unsigned)count<<2)+(s32)self+0xcc)`. The signed
`count*4` forms rank self ahead of the scaled term in add's operand slots
(bind self to rB → `add r9,r3,r9`); the unsigned-shift form ranks the scaled
term first (rA) = want's binding. Lesson: in this family a one-word
commutative-add rA/rB flip can be coerced by switching the scaled term from
signed `*4` to `(unsigned)<<2`.

Remaining member **fn_8000F9C4** (array-remove, 94.4%): its 2 residual words are
the SAME indexed `lwzx/stwx` rA↔rB swap (base r11 / index r10 vs swapped) with
NO count pin available (count changes in the loop, can't live in one reg). Still
parked — the F320 rA/B lesson doesn't transfer to an lwzx/stwx base/index swap.

## 2026-09-02 — fn_8000F9C4 SOLVED: byte-biv indexing + `-fno-gcse` (EXACT 144/144)

**fn_8000F9C4 is now byte-EXACT in `src/wip/` (reloc-masked 36/36, flagdiff
verified 2026-09-02). Not promoted — the current .sdata2 +0x40 link state
auto-reverts new ngccc promotions (WIP.md 2026-09-02 blocker).** The slot coin
was NOT a regalloc coin: it is which register the address-plus puts in rA.
Two levers combine (both required):

1. **Source-level byte biv, not an element-index mult.** With `arr[i]`
   (element counter), loop.c strength-reduces `i*4` into a giv and REBUILDS
   the address as `(giv,base)` → the giv lands in rA (the park: got
   `lwzx r0,r10,r11`). Indexing the SAME base with a real byte counter
   (`for (i=0,k=0; i<count; i++,k+=4)` + `*(void **)(arr + k)`) keeps the
   tree order `(base,k)` → base in rA = want's `lwzx r0,r11,r10`, with the
   latch `addi r10,r10,4` now coming from the source `k += 4`. The r8
   element counter (`addi r8,r8,1`) + per-iteration count reload + in-loop
   `addi r11,r3,4` (named `char *arr = self+4` as first body stmt, doc-47
   lever) all stay byte-identical.
2. **`// FLAG: -fno-gcse` is REQUIRED.** Without it ngccc's GCSE turns the
   `base + k` addressing into a walking `lwzu` and PEELS the first
   iteration, duplicating the whole remove body (180B vs 144B).
   `-fno-strength-reduce` / `-fno-peephole` / `-fno-unroll-loops` /
   `-fno-function-cse` / volatile-base / increment placement all FAIL to
   suppress the peel (byte-identical 180B or worse); `-fno-gcse` alone
   yields want's exact 144B. `-fno-gcse` is a known-good per-object flag
   (6 promoted objects in configure.py, AGENTS.md 177/223).

The doc's earlier "untested next lever" — the recipe-99 `__asm__("" :
"+r"(arr))` base pin — was tried and is a dead end: it collapses the
allocator (8.3%, 140B). Do not retry. The full winning body + recipe notes
are in the draft header (`src/wip/fn_8000F9C4.c`).

**2026-09-02 — fn_8000F95C SOLVED too (EXACT 104/104, NO flags).** The push's
wall was NOT the fold (the indexed `stwx` already appeared) but TWO hidden
requirements, both pure source shape:

1. **The function RETURNS the pushed object** (`void *` + `return obj;`).
   Want's extra `mr r11,r3` (home the call result) is only emitted when obj
   is a return value live to the end — a `void` signature makes ngccc store
   straight from r3 (`stwx r3,...`), 25 words vs want's 26. Register pins on
   obj/count did NOT reproduce it; only the return-value web forces the
   home copy. (Callers store the result into fields/globals — consistent.)
2. **Increment by REASSIGNING the variable** (`count++;` then store
   `count`), not by storing the inline expression `count + 1`. The inline
   form makes ngccc compute `addi r9,r9,1` early, before the `stwx`; the
   reassignment form emits it after, matching want's exact tail
   `[stwx r11,r10,r0][addi r9,r9,1][stw r9,0xc4(r30)]`.

Rest of the body (named-arr decl order, count reload `lwz r9,0xc4` before
`mr r11,r3`, base `addi r10,r30,4`, `slwi r0,r9,2`, indexed `stwx r11,r10,r0`)
match from the old draft. `-fno-gcse` and all sched flags are no-ops on the
winning form. Full body in `src/wip/fn_8000F95C.c`; flagdiff 26/26 (100%).

## Batch-promotion caveat (SDA2 pool, separate from this wall)

Per-function EXACT (relocation-masked) is NOT a link outcome. Batch-promoting
many new objects can shift mwld's `_SDA2_BASE_` (observed 0x803D2F80 →
0x803D2F60), tripping `tools/patch_dol.py`'s `Init r2 setup computes 0x…,
expected 0x803D2F80` fail-fast; and hand-asm drafts referencing exact-address
labels with no registered symbol (`lbl_802B1CD8 @ 0x802B1CD8` for
`__cvt_fp2unsigned`) or anonymous asm branches (`bdnz $`) are undefined in the
link. Verify a draft links before batch-promoting it; keep them WIP otherwise.
## 2026-09-13 — the family's rA/rB store half is still open; one adjacent coin is NOT a coin

Re-verified this session with a **pool-wide diff classifier** (`/tmp/opswap.py`:
compile every NEAR draft, decode each mismatching word with capstone, and report
diffs that are pure commutations of a commutative op's last two operands). Only
four members exist, and all four are the *store/index* half of this doc:

| fn | diffs | residue |
|---|---|---|
| `fn_80091C88` | 1 | want `stwx r10,r9,r11`, got `stwx r10,r11,r9` |
| `fn_800A1B5C` | 1 | want `stwx r4,r11,r9`, got `stwx r4,r9,r11` |
| `fn_80206F7C` | 2 | two `stwx`, each with the slots swapped |
| `fn_801A6FB4` | 2 | `lwzx` + `stwx`, both slots swapped |

The doc's "untested next lever" (an asm pin on the base register) was tried on
`fn_800A1B5C`: `__asm__("" : "+r"(a54))` costs 2 words elsewhere, and the
struct-element array form regresses to 6/22 (it folds the field offset and
callee-saves the anchor — the same failure mode doc 49 records for
`fn_801A6FB4`). **Conclusion: the indexed-store rA/rB half remains closed to
every source shape tried in two sessions.**

The related-looking `fn_800D521C` fadds residue is **not** in this family and is
**not** a coin: a named `f32` temporary pins the operand order (recipe 58 in
WIP.md). Floating-point commutativity and integer addressing commutativity do
not respond to the same lever.

## 2026-09-14 — THE rA/rB STORE HALF IS SOLVED: byte-typed base + inline shift

Three of the four members above now match byte-exactly, and the family is
closed. `fn_801A6FB4` was promoted 2026-09-14 first; `fn_80091C88` (112B) and
`fn_800A1B5C` (88B) followed and were promoted the same day (DOL verified
byte-identical). The lever is a **byte-typed base pointer plus a byte offset
written as an inline shift** — and, critically, *where* the base is born.

**The lever (fn_801A6FB4, previously parked at 80%)**

```c
/* fails — index-first `stwx r9,r11,r3` (want `stwx r9,r3,r11`) */
u32 *p = (u32 *)(arg0 + 0x5F0);
p[arg1 >> 5] &= ~(1u << (arg1 & 0x1F));

/* WORKS — pointer becomes rA */
char *p = (char *)(arg0 + 0x5F0);
*(u32 *)(p + ((arg1 >> 5) << 2)) &= ~(1u << (arg1 & 0x1F));
```

Bisected on the solved function (all variants scored against 0x801A6FB4):
the flip needs **both** a byte-addressed pointer **and** the scale expressed
as a *shift* in the index expression. `(char *)p + (i >> 5) * 4` (multiply)
scores 80%; a `u32 *p` base with the explicit `<< 2` scores 70%; an `s32`
base holding the raw address (`s32 b = arg0 + 0x5F0;`) also reaches 100%.
So the invariant is *the memory operand's index register carries a byte
offset computed by a shift*, not a scaled element index.

**`fn_80091C88` (doc-49 store half; was 96.4%, 1 word)** — the table base
must be a **separate `char *p` local, assigned INSIDE the guard, after the
scaled index temp is computed**:

```c
char *p;
s32 temp_r11_2;
u32 temp_r11;

temp_r11 = *(u32 *)&lbl_803017F4;
if (temp_r11 <= 7U) {
    temp_r11_2 = temp_r11 * 0x60;
    p = (char *)lbl_803792D8;
    *(s32 *)(p + temp_r11_2) = arg0;   /* want `stwx r10,r9,r11` */
    ...
}
```

Initialising `p` at its declaration (`char *p = (char *)lbl_803792D8;`) or
fusing the byte arithmetic into the index regresses to **57.1%** (the base
re-folds and the slots swap back). The `char *p;` declaration must also come
FIRST in the declaration block.

**`fn_800A1B5C` (was 95.5%, 1 word)** — same idea, no index local at all:

```c
char *a54 = (char *)arg0 + 0x54;
char *a58 = (char *)arg0 + 0x58;

*(s32 *)(a54 + (arg0->unk0x50 << 3)) = arg1;   /* want `stwx r4,r11,r9`  */
*(s32 *)(a58 + (arg0->unk0x50 << 3)) = arg2;   /* want `stwx r5,r10,r0`  */
```

The inline `<< 3` is load-bearing: `idx * 8`, `(s32 *)idx * 2` and a named
`idx` local all stay index-first (95.5% / 63.6%). This version also removes
the `register ... __asm__("r9")` pins the parked draft used — the whole
r9/r0/r11/r10 assignment falls out of plain C.

**`fn_80206F7C` remains parked** (two words) and is the boundary of the
lever: its stride is `0x18` (`= 3 << 3`), not a power of two, so no inline
shift spelling exists. want is base-first at all four sites while ngccc is
base-first only where the `mulli` product lands in r0 (sites 0x54/0x80) and
flips index-first when the product is in r9 (0x74/0x8C) — same registers,
same EA. Every non-power-of-two spelling tried (see the file's header)
scores 95.6% or worse, so it is left in `src/wip` as the stand-alone park.

**Transfer checklist for a parked `stwx`/`lwzx` slot swap**

1. Is the base a *byte* pointer (`char *` / `u8 *`) rather than an element
   pointer? If not, retype it.
2. Is the byte offset a **shift of the field/index** (`f << k`), written
   inline? If the stride is a power of two, yes; if not, this lever is out.
3. Does the base need to be a named local born *after* the index temp /
   inside the guard, declared first? Try both births before parking.
4. Only then reach for asm register pins (and expect a 2-word cost).
