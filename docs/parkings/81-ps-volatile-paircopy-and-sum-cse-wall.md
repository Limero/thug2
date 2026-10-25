# 81 — `volatile __ps_t` forces per-use pair-copy reload; and a CSE'd sum-pseudo wall

Two findings from `fn_801F21A8` (376B, `-mps-float`, 94 words, best 12.8% DIFF).
The first is a **lever** (it reproduces retail's copy block verbatim); the second
is a **negative result** that saves ~20 compiles if you are about to grind the
same shape.

## 1. Lever: `volatile __ps_t local[n]` reproduces retail's NON-CSE'd pair-copy block

Retail copies one 16-byte pair into two 16-byte destinations with four independent paired-single load/store pairs, reloading the source pair instead of reusing the register: the first pair moves from frame offset 8 to offset 24 for the upper first element, the second moves from the pointer-base offset 8 to frame offset 32 for the upper second element, the third reloads from frame offset 8 to offset 40 for the lower first element, and the fourth loads from the pointer-base offset 8 into f13 then stores to offset 48 for the lower second element.

Plain C emits **six** words: cc1 CSEs the two source loads and feeds both stores
from one FPR. Declaring the copy source

```c
volatile __ps_t point[2];
```

blocks that and emits all eight words — *including retail's exact interleaving*,
with the unrelated `lfs/stfs` margin fixups sitting between the copy pairs
(`lfs f13,0x1c(r1)` between pairs 2 and 3, `stfs f13,0x1c(r1)` between pairs 3
and 4, `lfs/fsubs/stfs` around pair 4).

This is recipes **§6al-180** ("`volatile s32 spN` forces per-site `addi` remat of
`&spN`") generalised from *scalar address remat* to *paired-single pair-copy
reloads*. Practical rule:

> **want shows the same 8-byte `psq_l` twice from one source pair → declare that
> local `volatile __ps_t`.** It costs +2 words only if the rest of the body is
> otherwise size-exact, so always re-score: here it moved the official positional
> score **12.8% -> 5.3%** (the body grew 348B -> 356B against a 376B want, so
> every later word shifted). It is the right lever only once the length already
> matches; otherwise record it and leave the shorter body in place.

## 2. Wall: a computed `(char*)base + (index<<5) + K` address is ALWAYS CSE'd into
##    ONE callee-saved pseudo with K folded into the load/store displacement

Retail's shape for an array-of-records pointer that must be rebuilt after a call shifts the index left by 5 into callee-saved r29, copies the base into callee-saved r30, adds the two into r9 and biases r9 by 0x120, re-emitted at each of three use sites, with the paired-single loads and stores then using base r9 with displacements 0 and 8.

ngccc instead builds the sum once: it shifts the index left by 5 into r0, adds base and shift into callee-saved r30 as a single sum pseudo, folds the 0x120-class offsets into the paired-single displacements at 288 and 296 of r30, and only materializes the biased copy into r9 for the call argument.

i.e. 5 instructions shorter. The `stmw`/`lmw` span (retail 6 saved regs because
the *operands* `arg1<<5` and `arg0` are the long-lived values, ours 5 because the
*sum* is) and every callee-saved colour are consequences of this single
allocation decision — not separate defects.

**20 spellings, all byte-identical to the "one pseudo" form:** raw per-site deref
with no named pointer (recipes §6v-6's "let GCC pick per-region remat" lever does
*not* fire for a computed address, only for a symbol one — §6v-6b); a function-
scope pointer; block-local pointers in each arm; the constant before the index
(`(char*)arg0 + 0x120 + arg1`) and after; `((T*)((char*)arg0+(arg1<<5)))[9]`;
`&((T*)arg0)[9 + arg1]`; `arg1 * sizeof(T)`; `long`/`u32` integer arithmetic;
staged `base`/`off`/`p120` locals assigned before the call (recipes §7e-123); a
struct-member array at the +0x120 offset (that one switches to indexed
`psq_lx rD,rA+rB` and grows the frame — strictly worse); and a minimal probe with
only the call shape (proving it is not whole-function register pressure).
`volatile` on a pointer variable adds a store, not a remat.

**Diagnostic tell:** if retail's disassembly contains the same
`add rX,rY,rZ` + `addi rX,rX,K` pair in two or more blocks after a `bl`, GCC is
CSE-ing something retail rematerialised, and no source spelling of that *one*
expression will restore it — the fix has to come from a *different data path*
(an opaque anchor, docs 51/73, or a real second consumer). Confirmed at 12.8%
DIFF / 348B-vs-376B; body, frame (0x120), query layout (result at +0x88, link at
+0xA8) and control flow are all confirmed correct in the draft's park note.

Members: `fn_801F21A8` (376B).