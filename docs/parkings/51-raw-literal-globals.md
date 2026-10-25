# 51 — bare-literal globals → registered-symbol references (raw-lit recipe)

**Status: OPEN family — recipe proven, 7 promotions + ~370 draft upgrades (2026-09-06)**

Full-tree mechanical sweep: 870 candidate files, 4,702 rewrites applied,
every file A/B-gated (post >= pre keep, post < pre git-revert). Result: ~370
kept (best jump: hash-insert siblings 58.5→85.0), ~368 reverted, **5 new
EXACTs promoted directly by the patch** (fn_800150EC, fn_800553EC, the QB
callback trio fn_8020432C/fn_802053AC/fn_8020686C) — 7 family promotions
total including the hand-done fn_801A9528/fn_80121A78.

## Symptom

m2c drafts carry raw numeric address literals for the next pass.sdata/.sbss/.rodata2/.bss
globals instead of references to registered `lbl_XXXXXXXX` symbols:

```c
mgr = (char *)0x8039BA58;          // draft  (lis+ori after -c)
mgr = lbl_8039BA58;                // want   (lis+addi via sdata relocations)
```

The literal compiles to `lis rX,0x8039; ori rX,rX,0xBA58` (2 words, hi/lo
split), while the symbol reference compiles to `lis rX,0x803A; addi rX,rX,-...`
(@ha/@l, signed-low) — plus different relocation masking. Word streams diverge
from the very first touch of the global.

## Proven recipe (fn_801A9528, fn_80121A78 — both promoted)

1. Look the address up in `config/G2TE52/symbols.txt` — every game-side
   address is registered as `lbl_XXXXXXXX` (or `fn_*` for functions).
2. Replace the literal with the symbol name. A load-bearing cast may stay:
   `(s32 *)lbl_8031349C`; plain `char *` holders need no cast (`mgr = lbl_...`).
3. Declare the symbols in the draft: `extern char lbl_XXXXXXXX[];` — one line
   per symbol, placed **after** the `#include` block. Without the declaration
   the draft fails to compile under ngccc `-c`.
4. Function-address arguments use the `fn_XXXXXXXX` symbol directly (no cast
   needed if the callee is prototyped; `(s32)fn_*` if unprototyped).

## Full-tree sweep (tools/fix_raw_lit.py + tools/ab_raw_lit.py --auto, 2026-09-06)

- Pattern classes patched: `(T *)0xADDR` casts and bare `0xADDR` call args
  (→ `(s32)sym`), symbol-gated against symbols.txt, decls auto-injected.
- **A/B-tested before keeping anything** (tools/ab_raw_lit.py: compile+score
  git-HEAD body vs patched body). Results: 34 files kept (6 hash-family
  members 58.5→85.0, fn_80012AD8 42.5→50.0 crossed to NEAR, 5 more +2..10
  points), 9 regressors reverted. The patch is NOT uniformly positive —
  raw literals were sometimes *coincidentally right* (e.g. when want itself
  emits lis+ori for address-constant folding); always A/B.
- `.bak` files in `src/wip/` break addr extraction everywhere — backups go to
  `/tmp/`, or delete them immediately.

## Family members (patched 2026-09-06, see WIP.md rows)

fn_8000E6D4, fn_80025EA8, fn_800532B4, fn_80053A58, fn_800579C4, fn_8005D380
(hash-insert siblings, 85.0 each), fn_80012AD8 (50.0), fn_80010910,
fn_80011EA8, fn_80011F64, fn_80013144, fn_80012170, fn_80012754, fn_80012948,
fn_80012A34, fn_80003BE8, fn_80006C64, fn_8000A990, fn_8000AB40, fn_8000AC98,
fn_8000B348, fn_8000B6F8, fn_8000FF18, fn_800101A0, fn_8000EE70, fn_80012E88,
fn_800130AC, fn_80058184.

## Residuals after the patch

- fn_800874DC/fn_8000EBF4 twins + hash family: arg-home color swap (doc-15
  class) remains at 85.0 — separate wall, unchanged by this recipe.
- Known regressor classes (reverted): drafts where the literal sits inside
  `case` labels or comparisons against negative-@ha addresses — patcher now
  skips unknown/special contexts, but re-verify with the A/B tool.

## fn-ptr call-cast variants (2026-09-06, dispatch-setter zone)

The same lis/addi-vs-lis/ori choice applies to calls through sdata fn-ptr
tables (lbl_80300278/80/88/8C). Four spellings, four byte streams:

| spelling | codegen | use when want shows |
|---|---|---|
| `(*(s32 (*)())lbl)` | `bl` to the label itself | never (wrong semantics) |
| `(*(s32 (**)())lbl)(...)` | `lwz`+`mtlr`+`crclr`+`blrl` | crclr present, unprototyped call |
| `(*(s32 (**)(T,args))lbl)(...)` | `lwz`+`mtlr`+`blrl` | no crclr, prototyped call |
| direct call w/ prototype | normal `bl` | plain call, not via table |

Promoted with the prototyped `(**)(...)` spelling: fn_8001EF84, fn_8001EFBC,
fn_8001F068. The 6-member 0x8001B6A8..87C thunk family used the unprototyped
`(**)()` form (want HAS crclr there) — always check want's blrl site for the
crclr before choosing.

## ADDENDUM 2026-09-15: mid-argument literals (the `,` blind spot)

The original sweep (`tools/fix_raw_lit.py`) rewrote two shapes only:

  - `(TYPE *)0xADDR` casts
  - literals that sit at the **end** of an argument list (`0xADDR)`)

That left the common third shape untouched: a literal in the **middle** of an
argument list, i.e. followed by a comma. `fn_8006A8C0` had exactly this —

    fn_8006A960(0x80366590, &sp8);            // 91.3%
    fn_8006A960((s32)lbl_80366590, &sp8);     // 100%

Retail is `lis r3, -0x7fca` + **`addi r3, r3, 0x6590`**; the literal spelling
gives `ori r3, r3, 0x6590`. Same low half, different instruction — and because
`ori`/`addi` carries no relocation, the masked scorer still charges every byte
of it.

Scanner: `tools/raw_sym_scan.py` (reads addresses on stdin). For each draft it
tries every symbol-able literal site at once *and* each site on its own (first
six), keeps the best, and writes the winner to `/tmp/rawsym_<ADDR>.c`;
`tools/apply_better.py` splices that back into the draft with an `UPDATED` note.

Two passes over the tree (all literal positions, not just commas):

| pass | candidates | improvements | promotions |
|---|---|---|---|
| 1 (comma positions) | 240 | 82 | `fn_800DF3F0` (83.3→100) |
| 2 (every position)  | 722 | 151 | `fn_800872FC` (7.4→100), `fn_800144EC` (31.6→100) |
| 3 (re-scan)         | 633 | 13 (all ≤ 0.7pt) | — |

`fn_800DF3F0` had been parked with the diagnosis *"lis+ori vs lis+addi
addressing differs from original compiler"* — the observation was right, the
lever just had not been applied. Anything parked with that wording is worth
re-checking with this scanner.

Note both promoted FP functions (`fn_800872FC`, `fn_800144EC`) needed the
`fix_fp_pool.py` ninja step to retarget their int→float magic pool at an
existing DOL label; `promote_wip.py` refuses such bodies if the pool cannot be
resolved.

Lesson (same as doc 55): the sweep result is a *cache*, not a proof. The
literal→symbol rewrite is not uniformly positive (most sites are neutral or
worse) — always keep the A/B gate.

## ADDENDUM 2026-09-18: absolute addresses (MMIO / OS low memory) — the `ldscript` symbol recipe

The sweeps above only ever converted literals that have an entry in
`symbols.txt`.  Addresses that belong to **no section** — the GX/FIFO window at
`0xCC00xxxx` and the OS/IPL page at `0x80000xxx` — cannot be registered there,
so every draft touching them kept its literal and could not match, because:

| spelling | ngccc | retail |
|---|---|---|
| `*(T *)0x800000F8` | `lis r11,0x8000` + `ori r11,r11,0xf8` + `lwz r0,0(r11)` | `lis r11,-0x8000` + `lwz r0,0xf8(r11)` |
| `*(volatile u8 *)0xCC008000 = v` | `lis r9,0xCC00` + `ori r9,r9,0x8000` + `stb r0,0(r9)` | `lis r9,-0x33ff` + `stb r0,-0x8000(r9)` |

The literal is always split **logically** (`hi = value >> 16`, `lo = value &
0xFFFF`, then `ori`), which never folds into a displacement; the *sign-adjusted*
`@ha`/`@l` split that retail uses is produced only for a **symbol reference**.
Verified experimentally: eight literal spellings (`s32` cast, negative int,
`((char *)0x…)`, pointer variable, `u32` sum, index form, …) all compile to
`lis`+`ori`; the symbol form is the only one that folds.

The fix is one line per address in `config/G2TE52/ldscript.tpl` (the project had
already done this twice for `lbl_CC008000` and `lbl_CC006828`):

```
    lbl_CC008000 = 0xCC008000; /* GP fifo write register */
    lbl_800000F8 = 0x800000F8; /* OS bus clock */
```

then declare `extern char lbl_CC008000[];` / `extern u32 lbl_800000F8;` in the
draft.  An absolute symbol definition cannot move anything, so the DOL stays
byte-identical — and the *linked* bytes are then correct as well, because the
linker resolves `@ha`/`@l` back to the retail `lis`/disp pair.

Payoff in one session: **3 MMIO leaves promoted** (`fn_8001DC98` / `fn_8001DCBC`
/ `fn_8001DD04`, GX `LOAD_INDX_A/B/D`, completing the 4-leaf family whose member
`fn_8001DCE0` was promoted from the same recipe earlier), 2 tick-helper twins
(`fn_80098E64`, `fn_8007E89C`), one **unparking** (`fn_80120924`, see doc 32
addendum (b) — a misdiagnosed regalloc wall), and one latent link bug fixed
(`fn_80120924` called `fn_80267848()` where the symbol is `OSGetTick`).

Caveats: `volatile` is still required for consecutive MMIO stores, and the
*load* side of the MMIO family (doc solved-07, `hwr`) is still parked on top of
this — the symbol fixes the address form, but its 16-byte
`__ARGetInterruptStatus` exemplar still needs the mwcc route for the address-base
colour.  Census over the no-park corpus found only ~10 drafts that touch a
low-memory/hardware literal, so this is a small family, but it is a two-line fix
per member and worth a scan before any "folded address" draft is redrafted by
hand.

## 2026-09-22 re-run (pool drift) — 59 more kept

The 2026-09-06 sweep is not a one-shot: the wip pool is rewritten in place by
the struct-ification sweep, `store_order_search.py` and the m2c re-drafts, all of
which re-introduce raw address literals. A fresh greedy re-run over the 1059
no-park drafts (look every `0x80XXXXXX` literal up in `symbols.txt`, substitute
the `lbl_*`/`fn_*` symbol + `extern char sym[];`, accept only if the masked
score strictly rises, repeat up to 5 rounds per file) found **61 drafts that
had drifted back**; after the `ab_raw_lit.py --auto` keep/revert pass
(**60 better / 2 same / 1 worse-reverted**), **59 remain improved**.

Best jumps this round:

| addr | before → after | symbol |
|---|---|---|
| `fn_800173D0` | 26.5 → 50.0 | `0x8025E774` |
| `fn_800964EC` | 15.2 → 43.6 | `0x8025E260` + 2 |
| `fn_80009F64` | 11.4 → 40.9 | `0x8028FF40` |
| `fn_8000F36C` | 29.0 → 31.5 | `0x802903EC` + 4 |
| `fn_801232EC` | 16.4 → 25.5 | `0x8039BA58`, `0x8039BE9C` |
| `fn_8000A3DC` | 44.2 → 45.5 | `0x8028FF88` |
| `fn_8001908C` | 9.6 → 12.3 | `0x80300134` + 3 |

Note the multi-round behaviour: most of the wins above are the SECOND or THIRD
symbol in a file (substituting one literal re-scores the file and can unlock the
next), so a single-pass sweep under-reports.

**Tool caveat:** `ab_raw_lit.py`'s `body_of()` only strips *leading* comment
lines and passes the body with NO draft flags, so drafts carrying
`// extra_cflags:` / `// FLAG:` lines (e.g. `fn_801227CC`, which needs
`-Ilibs/dolphin/include`) report `pre:FAIL post:FAIL` there while
`score_addrs.py` — which honours `draft_flags()` — scores them fine. Always
cross-check a FAIL from that tool against `tools/score_addrs.py`, and do not
let it "revert" on that basis.

Also: the same recipe cracked a fresh EXACT this round —
**`fn_8001F0F8` promoted**; its literal `0x80300278` folds into the base
register (`lis; ori r30,r30,0x278; lwz r9,0(r30)`) instead of want's
`lis; lwz r9,0x278(r30)`. Use `extern char lbl_80300278[];` and the
`(*(T (**)(args))lbl_...)` table spelling from the section above.

## CORRECTION 2026-09-25: `extern char lbl[]` is the WRONG decl for scalar-width access

Every recipe above (step 3 of the "Proven recipe", plus the fn-ptr and
2026-09-22 sections) tells you to declare a data symbol as
`extern char lbl_XXXXXXXX[];`. That is correct **only for the pointer use
case** (`mgr = lbl_8039BA58;` — you want the *address*). It is wrong for the
**scalar load/store** case, which is the most common one in the corpus:

```c
extern char lbl_80301A38[];          /* array  */
temp = *(s32 *)&lbl_80301A38;        /* want: lis r9,@ha ; lwz r3,0x138(r9)      */
                                    /* got : lis r9,@ha ; addi r9,r9,0x138 ;
                                               lwz r3,0(r9)   (3 words, lis+ori) */
```

An *array* object is not a scalar, so ngccc cannot fold the low half into the
load displacement; it materialises the full address first. Declaring the symbol
with the **access width** restores the fold:

```c
extern s32 lbl_80301A38;             /* scalar */
temp = *(s32 *)&lbl_80301A38;        /* lis r9,@ha ; lwz r3,0x138(r9)  — 2 words */
```

This is the same pass as `tools/apply_structs.py --lbl-types` (M6.89o) and
AGENTS recipe 53; the doc-51 sweeps just never got round to it because they
were gated on finding a *literal*, and these drafts already had the symbol.

**Keep the `*(T *)&lbl` cast.** 4-variant isolation on `fn_8009FB20` (parked
at 91.3% since 2026-08-31 as a doc-15 scheduler coin):

| variant | result |
|---|---|
| `extern char lbl[]` + `*(s32 *)&lbl` (the old form) | NEAR 91.3% |
| `extern char lbl[]` + cast **dropped** | DIFF 12.5% |
| `extern s32 lbl;` + **cast kept** | **EXACT 100.0%** |
| `extern s32 lbl;` + cast dropped | (not needed) |

Dropping the cast is actively harmful — the address then decays through the
scalar and the store/load loses its width. An earlier sweep did *both* at once,
which is why it looked exhausted (1 hit in 1144 files) when the real lever was
the decl alone.

### Census (do not re-run expecting more)

Signature scan (`extern char lbl_X[];` + a `*(s32|u32|f32|void *)&lbl_X` read,
ignoring comments) over `src/wip`: **376 drafts**. Retype-decl-only, A/B scored,
8-way parallel:

| outcome | count |
|---|---|
| EXACT after retype | 1 — `fn_8004F4E4` (85.5 → 100.0, promoted) |
| improved DIFF, then closed by a dead-arg fix | 1 — `fn_800CC9A8` (21.7 → 100.0, promoted) |
| improved DIFF, left parked | 5 — `fn_800D61C4` +0.9, `fn_80024774` +0.7, `fn_80210F58` +0.3, `fn_801E4178`/`fn_801E72F0` +0.1 (not applied; noise) |
| neutral (delta 0.0) | 325 |
| **regressed to compile-FAIL** | 2 — `fn_8022EA0C`, `fn_801354B4` (symbol used as both array and scalar in one TU) |

`fn_8004F4E4` was parked as *"doc-15 call-setup emission order, 2 probes"* and
`fn_800CC9A8` as *"ngccc's lis-grouping schedule"* — both were this decl type,
not scheduling. `fn_800CC9A8` additionally needed `fn_80119FB4` prototyped
**2-arg at this site** (m2c's phantom third `(s32)lbl_80299658` arg forced a
spurious `mr r5,r9`): recipe AGENTS §6y-132.

Guard for the FAIL class: skip a file where the same `lbl_` is declared or used
both as an array base and as a scalar elsewhere.

## fn_800A234C (2026-09-28): ONE HI16 pseudo per SYMBOL per function → stmw, not scheduling

61.4% → **96.5%**, size-exact 228B / 57 insns, with the residual down to 2
words. Two findings for the "lis-grouping schedule" family:

1. **ngccc 2.95 allocates ONE `HI16` address pseudo per symbol for the WHOLE
   function, spanning calls.** A global read in two different blocks forces
   the page address to stay live across a `bl` ⇒ a callee-saved register and
   an extra `stmw` slot ⇒ a cascade of downstream register permutations. Retail
   re-materialises the page per use (3× `lis -0x7fd0` here). Fix: give ONE of
   the reads an **opaque** page anchor so it is no longer the same web, leaving
   the other a single-use scratch reload:
   ```c
   __asm__ volatile("lis %0,%1@ha" : "=r"(pg) : "s"(&lbl_80301A44));
   v = *(s32 *)((char *)pg + 0x1A44);
   ```
   1 instruction of 57 (1.8%). Also load-bearing on that fn: `volatile` on the
   two block-1 loads (pins order + register roles, ~+7% each), the rem chain as
   three separate statements (fuses `mullw` dest into the accumulator, +2%), and
   re-reading the field for the divide.
2. **TRAP (a masked 100% cannot catch it): the `"s"` operand must be
   `&lbl` on the REAL symbol.** An aliased extern name (a second extern
   pointing at the same address) makes ngccc drop the `LO` reloc, and the
   object links against a dead name — recipe 277's link trap, reached from a
   different direction. Always `readelf -r` the object and confirm the `LO`
   entry names the symbol you meant.

Dead ends (all ≤ 96.5%): ~16 flags (`-O1/-O3`, `-fno-gcse`,
`-fno-cse-follow-jumps`, `-fno-thread-jumps`, `-fexpensive-optimizations`,
`-fno-sched-spec/-interblock/-spec-load`, `-fno-schedule-insns{,2}`) either
drop to ≤70.2% or are no-ops; the global decl form (`u32`/`s32`/`char[]`+cast),
cast vs plain lvalue, `volatile` on the global, a memory-clobber `asm` between
blocks, pointer/nested-scope `"memory"`/`"+r"` barriers, and local + file-scope
register pins on the address (which instead give the full `lis`+`addi` form) all
land on the same 2-word residue: a constant `set` hoisting into the gap between
two `volatile` loads.

Residual, 2 words: the `lis r11` (HI16 of `lbl_80290628`) is scheduled one slot
early, into the gap between the two `volatile` block-1 loads; making it an asm
pair just moves the residue to 0x23BC/0x23C0 (the `lwz` then sinks past the
`divwu`). Every combination tops out at 96.5%.

### fn_800963F8 (2026-09-28): same family, one step further — a POINTER-valued global

96.7% → **EXACT**. The 2026-09-25 sweep above retypes *scalar* globals
(`extern char lbl_X[]` + `*(T *)&lbl_X` ⇒ `extern T lbl_X`). fn_800963F8 is the
**pointer-valued** member: `lbl_802FFE98` holds a pointer, and the fix is the
same retyped declaration one level deeper:

```c
/* was */ extern char lbl_802FFE98[];
         *(s32 *)((char *)(*(void **)lbl_802FFE98) + 0x11C)
/* now */ extern Unk_9994C3F5 *lbl_802FFE98;
         lbl_802FFE98->unk0x11C
```

Isolated A/B: the declaration form alone is the entire fix (the old decl with
`lbl_802FFE98`'s callee protos still gave 96.7%). It re-shapes the two global
reads so the *second* reload pseudo outranks the `stw r3,0x14(r31)` in the
scheduler, giving want's `bl; lwz -0x168(r30); stw; lwz 0x11c` order. A
file-local `CardAllocStack` typedef scores identically — only the *pointer*
declaration is load-bearing, not the field type.

**Six sibling drafts may still be parked on this exact residual** — worth
re-checking their own `lbl_802FFE98` declaration form before grinding them:
`fn_800914C4`, `fn_800F6610`, `fn_8001666C`, `fn_8007ADB8`, `fn_8007EE94`,
`fn_8021CEC0`. (A DOL-wide scan of the 5-word window found 9 sites; the other
two were already promoted and were the answer — `src/fn_80023F94.c` and
`src/fn_80016448.c` — which is where this recipe came from.)

Link note for the eventual promote: the body already includes
`structs.h` and the promoted sibling uses it for this same global.
Per-TU arity differences vs other promoted files (`s32` vs `void *` params on
`fn_80010D94`/`fn_80010E78`) both score 100% and link independently.

---

## L1 CORRECTED 2026-09-28: it is the declaration **and the read** — five more members

Round 2 applied the `fn_800963F8` recipe to the rest of the `lbl_802FFE98`
family and got **five more byte-exact**, which also produced a correction that
matters more than the wins:

> **You must BOTH declare the symbol a pointer AND read it directly.**
> Changing only the declaration is not enough, and is sometimes far *worse*:
> on `fn_800588A8` the pointer declaration + the old `*(void **)lbl_X` cast
> scores **23.5%**, against a 95.9% baseline for the old spelling and 100.0%
> for pointer-decl + direct read. Isolated A/B on that function:
>
> | spelling | score |
> |---|---|
> | `extern char lbl[]` + `*(void **)lbl` (old park) | 95.9% |
> | `extern T *lbl` + `*(void **)lbl` cast kept | **23.5%** |
> | `extern T *lbl` + `lbl` direct use | **100.0%** |
> | `extern void *lbl` + `lbl` direct use | 100.0% |
>
> The pointee type is still irrelevant (any file-local struct with a member at
> the right offset works; no `Unk_*` edit needed). But the READ must be the
> bare symbol — keeping the cast keeps the separate address web that the whole
> recipe exists to remove.

Members (all EXACT, all left in `src/wip/`, not promoted):

| addr | was | extra ingredients beyond L1 |
|---|---|---|
| `fn_800963F8` | 96.7% | — (the exemplar) |
| `fn_800588A8` | 95.9% | file-local `Elem` typedef, `s16` vtable offset, per-store re-read of `arg0->unk0x4` |
| `fn_8009B4B0` | 94.6% | — (declaration + 2 expression edits only) |
| `fn_8001666C` | 23.5% | callee-signature audit (m2c invented a 6-arg `Mem_Alloc_3`), m2c scaled-pointer bug, `else if` block shape so crossjump rebuilds the shared `bl`, pin-a-copy for the {arg1,rem,chunk} rotation |
| `fn_800427AC` | 13.8% | `strlen` proto + its 2nd call re-pointed, a 4-arg callee widened with the guard forwarded, `len1 = len+1` hoisted, and **duplicating the shared `dst++` into every loop arm so crossjump rebuilds one block** (97.9 → 100) |
| `fn_800CB098` | 64.3% | callee audit (undeclared `Mem_NewZero`, a 4-arg callee with the result **chained** into arg0, `s16` vtable offset), plus: the first read must be **its own local that dies at the next call** (sharing one local with a later read homes it in r30 → 64.3%), plus a 1-insn `mr` recycling wedge |

Mechanism recap: m2c's chain keeps a second address web alive, so ngccc's
reload pseudo loses its priority slot to an adjacent store/load group and the
pool-head load lands one slot early or late. Retyping the declaration *and*
reading the symbol directly merges the webs.

**Still un-attempted siblings** (same `lbl_802FFE98` family, worth re-checking
their declaration + read form before grinding anything else):
`fn_800914C4`, `fn_800F6610`, `fn_8007ADB8`, `fn_8007EE94`, and `fn_8021CEC0`
(where L1 applies and is load-bearing but the function is only at 94.9% for
an unrelated entry-block schedule reason).

**Diagnostic to add to the "scheduling park" triage:** a 90-99% residual that
is ONE load emitted one slot early/late against an adjacent load group, or a
2-word `lis`/store transpose with a named global on both sides of the gap, is a
declaration-form smell — check for a `*(void **)lbl_X` chain before touching
source order or flags.

---

## Round-3 update: the `lbl_802FFE98` sibling list is essentially closed

| addr | before | after | note |
|---|---|---|---|
| `fn_800F6610` | 98.1% | **EXACT** | L1 was the *entire* residual, first try. Old park blamed a "2-insn scheduler slot-swap after `bl Mem_Alloc_3`" — that is the L1 symptom exactly. |
| `fn_800914C4` | 4.2% (DIFF) | 69.7% NEAR, 1596B | full hand-rebuild. **L1 was applied and worth 0.0** — a 1-word lever cannot help a 400-instruction structural break. The rebuild needed a frame-template struct local, three per-phase web splits, and two statements m2c had dropped entirely. |
| `fn_8007EE94` | 16.0% (DIFF) | 88.6% NEAR, 176B | L1 got 16.0 → 45.5; the other 43 points came from splitting the alloc/result web into two locals, a file-scope never-read `register s32 g31 __asm__("r31")` to reserve retail's DEAD 7th saved slot, and a callee-arity fix. The working spelling here is `extern Unk_9994C3F5 *lbl_802FFE98;` + `mgr = lbl_802FFE98;` + `mgr->unk0x118`, with the **second** read left inline. |
| `fn_8021CEC0` | 9.8% | 94.9% | round 2. |
| `fn_8007ADB8` | — | not attempted | last one on the list |

**Two facts the earlier rebuilds produced that belong here:**

1. **A frame-template struct local is what reproduces an 8-aligned slot map,
   spilled-pointer slots and a CR-save area *simultaneously*** — and struct
   sizes must be a multiple of 8, or ngccc pads them and every downstream
   offset shifts (fn_800914C4 lost a day to a missing pad byte before 0x124).
2. **`L1 alone is worth 0.0 on a structurally broken body.** Apply it (it is the
   correct spelling either way) but do not read a null result as "L1 is
   inapplicable" — on fn_8007EE94 it was worth +29.5 and the remaining 43 points
   came from elsewhere.

Round 3 also added two members to the *diagnostic* half of this doc, which is
now the more valuable half: "one load moves one slot past an adjacent store,
both words otherwise correct" is a declaration-form candidate, not a scheduling
wall (see also the two doc-15 members cracked this round by the same reasoning).
