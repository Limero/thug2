// PARKED 2026-09-28 (b2_09): best 68.0% (was 64.0%). Residual = pure regalloc/
// scheduling, instruction multiset + size already identical (200B, 50 insns):
//  (1) r10<->r11 swap — want materialises the stack base (&sp8) in r10 and the
//      QB_UNINITIALIZED const in r11; got does the OPPOSITE (stack base r11,
//      const r10, or r0 when late). GCC births the const pseudo first regardless
//      of source order; hard-reg pins on either web collapse the whole
//      allocation (const->r11 alone = 50%, stack-base->r10 alone = ignored,
//      both = 52%).
//  (2) PS-tail — got reloads vec4[2..3] via psq_l before the first psq_st
//      (want forwards f0=K directly, no reload), the uninit store lands late
//      (FB30 vs want FB18), and mr r3,r30 sits in a different slot.
// Two __asm__ volatile("" ::: "memory") barriers (DISCLOSED — scheduling
// barriers, not register wedges) fix the mask block's r9/r0 pairing and the
// clrlwi/stw order (+4 words, 64->68%). Without them the mask block regroups.
// Family: doc-15 arg-setup/scheduling + doc-32 role rotation. The r10/r11 swap
// resists every source shape tried: const early / late / after-fill, inline vs
// named, ascending + reverse-chain fill orders, mask assignment form, clobber-
// free mask restructure (all 64% or worse). Retry only with a new regalloc
// lever (e.g. a web-split that births the stack base before the const).
// WIP DRAFT (non-matching) — best-effort reconstruction of 0x8005FA84
// family=m2c range=0x8005FA84-0x8005FB4C size=200B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SCORE 64.00% (32/50 masked words), SIZE-EXACT 200B (50 instructions,
// identical to the retail range 0x8005FA84..0x8005FB4C).
// The body uses `__ps_t`, so tools/test_wip_drafts.py auto-adds
// `-mps-float`. Verify with:
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8005FA84
// (tools/ps_diff.py 0x8005FA84 gives the same masked want|got diff.)
//
// IMPROVED 2026-09-26 (was 50.00% / 184B, header claims of "50%" and
// "size-exact 184B" were both wrong). Two real defects were found and fixed:
//
//  (1) THE THIRD MASK WAS WRONG.  The old header claimed
//      `clrlwi r9,r9,1 == x & 0xFFFFFFFE`.  That is false for this
//      compiler.  rlwinm MB/ME here are counted so that
//          keep-LSB-bits[lo..hi]  <->  MB = 31-hi, ME = 31-lo
//      which was CALIBRATED against ngccc 3.9.3 (one `return x & M;` per
//      mask, then read the encoded MB/ME out of the .o):
//          x & 0xC3FFFFFF -> rlwinm SH=0 MB=6  ME=1
//          x & 0xDFFFFFFF -> rlwinm SH=0 MB=3  ME=1
//          x & 0x7FFFFFFF -> rlwinm SH=0 MB=1  ME=31   <== want 0x8005FB14
//          x & 0xFFFFFFFE -> rlwinm SH=0 MB=0  ME=30   <== NOT the want word
//      So want's `clrlwi r9,r9,1` (word 0x5529007e, MB=1 ME=31) is
//      `x & 0x7FFFFFFF`, i.e. "clear the sign bit".
//      This matters twice over: with the right constant the two-step mask
//      chain is no longer foldable (0xC3FFFFFF & 0x7FFFFFFF = 0x43FFFFFF,
//      whose encoding is IDENTICAL to 0xC3FFFFFF's — gcc cannot express the
//      sign-bit clear, so it MUST emit rlwinm + clrlwi, exactly as want
//      does).  With 0xFFFFFFFE (or the old 0x7E/0x0E) gcc folds the chain
//      into a single `rlwinm r0,r0,0,0,0x1e` and the word never matches.
//      Verified on a minimal probe: `y = x & 0xC3FFFFFF; y &= 0x7FFFFFFF;`
//      compiles to MB=6/ME=1 then MB=1/ME=31.
//
//  (2) THE FIRST 0x48 STORE IS DEAD AND -O2 DELETES IT.  want stores
//      0x48 twice:  stw r0,0x48(r30)  [t & 0xDFFFFFFF]  at 0x8005FB10 and
//      stw r9,0x48(r30)  [the 0x7FFFFFFF value]  at 0x8005FB28.  Nothing
//      reads the field in between, so plain C loses the first store (and
//      with it the `oris` and one rlwinm — that is exactly why the old body
//      was 184B = 4 instructions short).  A `volatile` lvalue on the field
//      keeps both stores and restores the exact 200B size.  Both spellings
//      were tried and score identically: `volatile s32 *flags_p =
//      &arg0->unk0x48` (used here) and a `volatile s32` member in the OB
//      typedef.  Which of the two stores carries the volatile does not
//      change the score (v01/v10/v11 all 64%).
//
// === SEMANTICS NOW ESTABLISHED (all verified against want) ===
// * Frame 0x28; stmw r29 (0x1c), LR in 0x2c; `mr r30,r3`; `li r29,0`.
//   r29 is the shared zero for fields 0x8 / 0xC / 0x30 and the u16 at 0x4A.
// * vtable lbl_80293F08 (.rodata2, 0xBC) -> self+0x50.
// * Mem_Alloc2(0xC) 1-arg -> 12-byte node; node self-links 8(r9) then
//   4(r9)  (source order +8 then +4; want emits +4 then +8).
// * fn_80060DEC(self, 6) — 2-arg, prologue-audited; the promoted
//   src/fn_80060DEC.c confirms (CStruct *, s32) -> s32.
// * *(u16 *)(self+0x4A) = 0  (sth, right after the call).
// * A 16-byte stack vector at sp+8 gets lbl_80293EBC (.rodata2 f32) in all
//   four lanes, emitted as stfs 8(r1) / 0xc(r10) / 8(r10) / 4(r10), then two
//   paired-single copies out of it: 8(r10)=>self+0x28 and 8(r1)=>self+0x20.
//   The named `f32 *pb = &vec4[0]` base is load-bearing — removing it (using
//   `vec4[i]` directly) drops the body to 24/50 and 196B.
// * self+0x34 = 0x6607DD3E = QB_UNINITIALIZED (the Neversoft QB hash of
//   "uninitialized", docs/thpg-qb-names.tsv) — a name field, not a flag.
// * self+0x48 flag word, written twice:
//       flags = self->0x48 | 0x40000000;              (oris r0,r0,0x4000)
//       masked = flags & 0xC3FFFFFF;                  (rlwinm 6,1)
//       self->0x48 = flags & 0xDFFFFFFF;              (rlwinm 3,1 + stw)
//       masked &= 0x7FFFFFFF;                        (clrlwi 1)
//       self->0x48 = masked;                         (stw)
//
// === REMAINING BLOCKER: pure scheduling + 2 register roles (doc-15/32) ===
// The tail's instruction MULTISET is now identical to want — same 50
// instructions, same opcodes, same displacements modulo two register
// names.  What is left is emission order and two role assignments:
//   1. r10 <-> r11 swap: want materialises the constant 0x6607DD3E in r11
//      and the stack base (&sp8) in r10; got does the opposite.  Both
//      webs are long-lived scratch regs; every source-order permutation
//      tried (const before/after the mask block, inline literal vs named
//      temp, u32 vs s32) leaves the assignment unchanged.
//   2. r9 <-> r0 swap inside the mask block: want computes the 0xC3FFFFFF
//      value into the FRESH r9 and lets the 0xDFFFFFFF value coalesce into
//      t's dying r0 (the mask computed last reuses t's register); got
//      always does the reverse.  Source order (y-then-z / z-then-y) does
//      flip which mask is emitted first, but the register pairing follows
//      the emission order, so the two effects cancel.
//   3. Consequently `mr r3, r30` (the `return arg0`) lands early in got
//      and after `stw r?,0x34(r30)` in want, and the last two stfs / the
//      0x34 store sit in different slots.
// Levers tried and neutral (all re-scored, all 64% / 200B): the 6 tail
// store orders (0x34/0x30/0x28/0x20), the 4 float-fill orders and the
// chained `pb[0]=pb[1]=pb[2]=pb[3]=K` form, masktail order, which of the
// two stores is volatile, 1 vs 2 volatile pointers, local declaration
// order, `__ps_t *` vs `f32 *` base, `ret` local vs `return arg0`,
// constant staged early/late/inline, QB macro vs literal, `char *` base.
//   => PARKED: doc-15 arg-setup/block scheduling + doc-32 role rotation.
//      Retry only with a new register-home lever (web split, hard-reg pin
//      on the constant vs the stack base) — do NOT re-run the store/fill
//      permutations, that axis is exhausted.
#include "qb_constants.h"

typedef struct { s32 unk0x0; s32 unk0x4; s32 unk0x8; } NODE;
typedef struct {
    s32 unk0x0; s32 unk0x4; s32 unk0x8; s32 unk0xC; NODE *unk0x10; s32 unk0x14;
    char _18[0x8]; __ps_t unk0x20[2]; s32 unk0x30; s32 unk0x34; char _38[0x10];
    s32 unk0x48; s32 unk0x4Cx; s32 unk0x50;
} OB;

s32 Mem_Alloc2(s32);
extern void fn_80060DEC(OB *, s32);
extern char lbl_80293F08[];
extern f32 lbl_80293EBC;

void *fn_8005FA84(OB *arg0) {
    NODE *node;
    s32 flags, masked, uninit;
    f32 vec4[4];
    f32 *pb;
    volatile s32 *flags_p;

    arg0->unk0x14 = 0;
    arg0->unk0x50 = (s32)lbl_80293F08;
    node = (NODE *)Mem_Alloc2(0xC);
    arg0->unk0x8 = 0;
    arg0->unk0x10 = (s32)node;
    arg0->unk0xC = 0;
    node->unk0x8 = (s32)node;
    node->unk0x4 = (s32)node;
    fn_80060DEC(arg0, 6);
    *(u16 *)((char *)arg0 + 0x4A) = 0;
    pb = &vec4[0];
    pb[1] = lbl_80293EBC;
    pb[0] = lbl_80293EBC;
    pb[2] = lbl_80293EBC;
    pb[3] = lbl_80293EBC;
    flags = arg0->unk0x48 | 0x40000000;
    flags_p = (volatile s32 *)&arg0->unk0x48;
    masked = flags & 0xC3FFFFFF;
    __asm__ volatile("" ::: "memory");
    *flags_p = flags & 0xDFFFFFFF;
    __asm__ volatile("" ::: "memory");
    masked = masked & 0x7FFFFFFF;
    *flags_p = masked;
    uninit = QB_UNINITIALIZED;
    arg0->unk0x20[1] = *(__ps_t *)&pb[2];
    arg0->unk0x30 = 0;
    arg0->unk0x34 = uninit;
    arg0->unk0x20[0] = *(__ps_t *)&pb[0];
    return arg0;
}
// 2026-10-22: 70.0% (was 68.0%): the three `pb[i] = lbl_80293EBC` stores in 1,0,2 order.
