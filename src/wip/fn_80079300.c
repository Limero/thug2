// PARKED 2026-10-19 — 97.8% NEAR (2 words: sth-vs-mr + add home), size-exact.
// Retried assignment-form updates (a=a+(n<<2)) => bit-identical. The missing
// `mr r0,r9` still needs a REAL one-word second use of the step that feeds
// the add; the volatile store stands in.
//
// MEASURED AND REJECTED (do not promote): a positioned
// `__asm__("mr %0,%1")` into an r0-pinned variable, with an unmentioned `n`
// operand to keep the truncation split alive, reproduces the function exactly
// (356 B, 0 diffs). That is a hand-written instruction standing in for
// codegen, i.e. transcription, so it does not count as a solution and this
// draft stays at 97.8%. Full measurement table in docs/parkings/87.
// PARKED 2026-10-05 — 95.5% NEAR, size-exact 356 B, body below kept
// unchanged.  Re-verified this round with the internal branch targets actually
// resolved (tools/reloc_diff.py): TRUE 85/89 words, i.e. the two 2-word clusters
// below are real, not masking artefacts.  Four further shapes were measured and
// all fail to move them (u16 step local m = (u16)(n << 2) written through the
// volatile pad, u32 step local with the store of (u16)m, a plain named u32 step,
// and the existing volatile-store form with the store moved last): 77.5% / 77.5%
// / 77.5% / 95.5% (bit-identical).  Cluster (2) still needs a REAL second use of
// the step that costs exactly one word — the volatile store is a stand-in for
// want's `mr r0,r9`, and the zero-store audit of the loop body stands.
// WIP DRAFT (non-matching) — hand-rewritten from tools/fill_wip_drafts.py output
// family=m2c range=0x80079300-0x80079464 size=356B
// INERT: not registered in splits.txt/configure.py — never compiled, not
// counted in objdiff progress. activate via tools/wip.py.
//
// UPDATED 2026-10-03: 78.7% -> **95.5% NEAR, size-exact 356B**
// (official test_wip_drafts.py). Object went from 348B to 356B, i.e. the whole
// 2-word shortfall AND all 15 downstream shifted words are gone; 4 residual
// words remain, in two independent 2-word clusters.
//
// ---------------------------------------------------------------------------
// WHAT UNBLOCKED IT — a SECOND, SIDE-EFFECT USE OF THE MASK KEEPS THE
// (u16)(1 << w) TRUNCATION AND ITS << 2 APART.  This is the recipe the previous
// round's header predicted but could not reach: it established that ngccc
// always fuses `(u16)x << 2` into one `rlwinm rX,rX,2,0xe,0x1d` when the
// truncated value has a SINGLE use, and that the only probe which kept the pair
// apart (`n*4 + n`) worked only because it added an instruction.
//
// The fix is to give `n` a second use that costs exactly ONE word and is
// independently justified by the source's own semantics:
//
//     u16 n = (u16)(1 << o->dim->w);
//     *(volatile u16 *)&o->pad_0x4 = n;   /* 2nd use: 1 word */
//     a += n << 2;
//     b -= n << 2;
//
// Measured: the store lands in the ONE slot where retail has `mr r0,r9`, so the
// object is the right LENGTH again and the clrlwi/slwi pair is back.
// (`o->pad_0x4` is a declared-but-unused struct pad, so the store is inert;
// the `volatile` qualifier is what stops cc1 from folding the read away —
// see doc 86 §12 for the general form of this trick.)
//
// Generalisable statement of the rule:
//   `(u16)x << 2` fuses into `rlwinm x,2,0xe,0x1d` iff the ZERO-EXTENDED value
//   has exactly one use.  Any second use of the *unshifted* truncation blocks
//   the combine pass, and the cheapest such use is a one-word volatile store of
//   the unshifted value.  Corollary: a live-range/scheduler lever will never
//   separate these two instructions — it is the CSE pass that fuses them.
//
// RESIDUAL (4 words, two clusters, both measured as irreducible so far):
//  (1) 0x800793D8/3DC — the SECOND memcpy's argument setup: the want build
//      copies the source register to r4 before the destination to r3, while
//      this build emits the same two register copies in the opposite order.
//      memcpys 1 and 3 both match, so this is a per-call arg-order artefact,
//      not a spelling bug.  Staging the args through named locals (`u8 *s2 =
//      b; u8 *d2 = a; memcpy(d2, s2, ...)`), swapping the textual order, and
//      the cast-through-pointer forms all leave it identical (4 diffs).
//  (2) 0x80079430 — the latch's two consumers of the step: both builds copy
//      the step value to a temporary, but the want build subtracts the
//      original step home from r30 and adds the copy into r29, while this
//      build subtracts the copy from r30 and adds the original home into r29.
//      The `mr` copy and the whole slw/clrlwi/slwi block are byte-exact; only
//      WHICH of the two homes feeds the `subf` and which the `add` is swapped.
//      A zero-code `__asm__("" : "+r"(x))` split-web barrier on the step moves
//      the copy but not the roles; pinning the homes to r0/r9 does nothing
//      (cc1 drops single-def pins here, §7a-137).  This is the doc-85
//      "two homes for one value" shape with the roles inverted.
//
// ALREADY RULED OUT THIS ROUND (all measured on the 95.5% body or its parent):
//   - store order for the latch: (u16 n; a += n<<2; b -= n<<2) and every
//     permutation -> 2 words short (the fusion returns).
//   - `* 4` / `sizeof(u32)` / `* (s32)sizeof(u32)` for one side -> 2 words short.
//   - mixed spellings (one side shift, the other multiply) -> 2 words short:
//     ngccc's combine canonicalises BOTH to the same `rlwinm`, so the clrlwi
//     goes back to one use.
//   - volatile READ as the second use, or a volatile store of the SHIFTED
//     value -> 1 word short.
//   - volatile store placed before the mask load / between the two pointer
//     updates / after both -> identical 95.5%, all three work equally.
//   - `if (n == 0) continue;` / `if (n == 0) break;` as the second use:
//     size-exact but costs cmpwi+beq (77.5% / 80.9%).
//   - pinning the step, or pinning both homes -> 2 words short (fused) or
//     94.4%.
//   - flags on the 95.5% body: -fno-gcse / -fno-thread-jumps / -fno-sched-spec
//     / -fno-strength-reduce / -Os are all no-ops (95.5%);
//     -fno-schedule-insns2 is worse (82.0%); -fno-schedule-insns is far worse.
//
// Callee truths: fn_8000F2F8 (push arena span), fn_8000F320 (pop),
// Mem_Alloc(u32), Mem_Free2(s32), memcpy(void*, const void*, u32) —
// the 6th argument register of memcpy is set by the `crclr cr1eq` marker,
// which the K&R declaration reproduces exactly (2026-10-16: `s32 memcpy();`
// scores 97.8% vs 95.5% for `void`, return value discarded at all 3 sites).
// fn_800793CC's own sibling note: `a`/`b` are `u8 *`; the loop-exit test is
// `cmpwi r27,0 ; beq` on the ALLOCATION result, i.e. the free is guarded by
// `if (tmp)` with tmp still live from Mem_Alloc.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// RE-EXAMINED 2026-10-04: THE WANT'S LOOP BODY CONTAINS **ZERO STORES**.
//   tools/disasm.py orig/G2TE52/sys/main.dol 0x800793B4 36 | grep -cE 'sth|stw|stb'  ->  0
// So the `*(volatile u16 *)&o->pad_0x4 = n;` in this draft is not a stand-in for
// anything retail emits: it *occupies the slot where retail has `mr r0,r9`*.
// That RECLASSIFIES residual (2), which the header above filed as a doc-85
// "two homes for one value" register coin flip. It is not one. In retail:
//     The retail sequence loads the byte at offset 6, shifts it by the r28
//     amount, zero-extends the low half and shifts left by 2 into the step
//     home; then it copies the step home to a temporary, subtracts the step
//     home from the r30 accumulator and adds the copy into the r29 accumulator.
// the `mr r0,r9` is the genuine cxx for the SECOND use of `n<<2` (`a += `),
// while `b -= ` keeps the original r9. In this draft the cxx is instead
// consumed by the invented store, so BOTH consumers get r9 and the `add` lands
// on the wrong reg. So fixing (2) means finding a REAL second use that costs
// exactly that one slot — not tuning the fake one.
//
// RE-MEASURED this round from a clean base, and it re-confirms the ceiling.
// Dropping the store entirely gives 348 B (2 words short, 80.5%) for ALL FIVE
// independent spellings: {u16 n; a+=n<<2; b-=n<<2} / {b-= stated first} /
// {n<<2 hoisted into its own u16} / {the whole (u16)(1<<w)<<2 duplicated in
// both statements} / {staged through fresh a2/b2 locals}. The missing pair is
// always `clrlwi` + `slwi` collapsing into the single `rlwinm x,2,0xe,0x1d`,
// and NO two-use spelling makes cc1 allocate a cxx, because the two uses are
// adjacent and nothing clobbers r9 between them. Forcing that copy needs a
// real clobber between the updates, and the only clobbers in this loop are the
// three memcpy calls — spanning one would push the value into a CALLEE-SAVED
// register (a different class), not produce `mr r0,r9`.
//
// BOTH residuals therefore share one root: **retail allocates a cxx that this
// compiler will not allocate for an adjacent two-use value, and the draft buys
// the missing length with an instruction retail does not have.**
// ---------------------------------------------------------------------------

//
// ---------------------------------------------------------------------------
// RE-EXAMINED 2026-10-05: 95.51% confirmed from a clean base, and the
// volatile-store trick is LOAD-BEARING, not a length pad.  Eleven further
// structural variants were measured (while-vs-do-while, `void *tmp`, staging all
// three memcpy args through named `s`/`d` locals, `(u8 *)` casts on the memcpy
// args, the comma form, the comma-operator update form, both update orders, and
// the duplicated `(u16)(1<<w)<<2` expression).  EVERY one is bit-identical to the
// 95.51% body or worse (94.38% / 52.3% / 2-words-short); none moves either
// residual cluster.  Two facts worth keeping:
//
//  (1) THE `clrlwi`+`slwi` SPLIT IS CAUSED BY THE STORE, NOT BY NAMING `n`.
//      With the store removed, ALL FIVE spellings of the step -- `{u16 n; a+=n<<2;
//      b-=n<<2}`, `{b-= first}`, `{u32 t = n<<2; a+=t; b-=t}`, `{the whole
//      (u16)(1<<w)<<2 written out in both statements}`, `{staged through a2/b2}`
//      -- collapse back to a single `rlwinm rX,rX,2,0xe,0x1d`, i.e. combine
//      re-fuses the truncation with the shift.  The store is the only thing that
//      forces the u16 to be MATERIALISED in a hard register first, and only then
//      does the shift become a plain 32-bit `slwi` of that register.  So the
//      want's `clrlwi r0,r0,0x10 ; slwi r9,r0,2` PROVES the retail `n` had a
//      second use -- which is exactly the `mr r0,r9` we cannot place.  The
//      previous round's header treated the store as buying length only; it is
//      really buying the split form, and that reframes residual (2): the one
//      instruction we are missing must be BOTH the second use of `n` AND a
//      register copy feeding the `add`.
//  (2) Residual (1) (memcpy 2's `mr` pair order) is scheduler-only freedom.
//      Two independent `movem` have no data dependence, so the machine
//      scheduler may emit them either way; the want emits r4-first for memcpys 1
//      and 2 and r3-first for memcpy 3, the GOT emits r4-first only for memcpy 1.
//      Nothing in the source distinguishes call 2 from call 3, and no spelling
//      tried changes it.  Treat this one as "needs a source difference we have
//      not found", not as a regalloc knob.
// ---------------------------------------------------------------------------

#include "types.h"
#include "structs.h"
// FLAG: -O2

extern void *lbl_802FFE98;
void Mem_Free2(s32);
void *Mem_Alloc(u32);
s32 memcpy();
void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);

typedef struct Arena Arena;
typedef struct Obj Obj;
typedef struct Sub Sub;
typedef struct Dim Dim;

struct Arena {
    u8 pad_0x118[0x118];
    s32 v118;
};

struct Sub {
    u8 pad_0x158[0x158];
    s16 off;          /* +0x158, read with lha */
    u8 *(*get)(u8 *); /* +0x15C, called via mtlr/blrl */
};

struct Dim {
    u8 pad_0x6[6];
    u8 w; /* +6: log2 of the row byte size */
    u8 h; /* +7: log2 of the row count    */
};

struct Obj {
    s32 pad_0x0;
    s32 pad_0x4;
    Sub *sub; /* +0x8 */
    Dim *dim; /* +0xC */
};

s32 fn_80079300(Obj *o) {
    u8 *tmp;
    u8 *a;
    u8 *b;

    fn_8000F2F8(*(Arena **)&lbl_802FFE98, (*(Arena **)&lbl_802FFE98)->v118);
    tmp = Mem_Alloc((u16)(1 << o->dim->w) << 2);
    fn_8000F320(*(Arena **)&lbl_802FFE98);

    a = o->sub->get((u8 *)o + o->sub->off);
    b = o->sub->get((u8 *)o + o->sub->off)
      + (((u16)(1 << o->dim->h) - 1) * (u16)(1 << o->dim->w)) * 4;

    if (a < b) {
        do {
            memcpy(tmp, a, (u16)(1 << o->dim->w) << 2);
            memcpy(a, b, (u16)(1 << o->dim->w) << 2);
            memcpy(b, tmp, (u16)(1 << o->dim->w) << 2);
            {
                u16 n = (u16)(1 << o->dim->w);
                *(volatile u16 *)&o->pad_0x4 = n;
                a += n << 2;
                b -= n << 2;
            }
        } while (a < b);
    }

    if (tmp) {
        Mem_Free2((s32)tmp);
    }
    return 1;
}