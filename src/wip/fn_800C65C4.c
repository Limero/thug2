// WIP DRAFT (non-matching) — full hand rebuild from disasm.
// family=m2c range=0x800C65C4-0x800C6860 size=668B
// extra_cflags: -mps-float
//
// === PARKED (2026-10-01) ===
// Score DIFF, masked 10.8% (18 of 167 want words).  Object .text = 632 B /
// 158 words vs want 668 B / 167 — 9 words (36 B) SHORT, so per §6cs-1 the
// index-aligned pct is not yet meaningful; a length-exact body is a
// prerequisite for any further score reading.
//   * The SEMANTICS ARE NOW PROVEN CORRECT.  An op-class multiset diff of
//     want vs this object (decode both with the PS-aware scorer) shows the
//     two bodies are IDENTICAL except for 9 register-copy instructions that
//     retail keeps and GCC coalesces away: five pair moves (at 0x6680,
//     0x66C8, 0x671C, 0x67E8 and 0x67F4, each a load into one register then
//     a copy into another), three scalar copies (at 0x66B8, 0x670C and
//     0x67C4, the last from lbl_80299150) and one GPR copy at 0x65F8 (want
//     keeps the frame base in r27; GCC forms it directly into r28).
//     Every ps_add / ps_mul / ps_muls0 / ps_madd / ps_sum0 / ps_merge00 /
//     ps_sub / psq_l / psq_st / lfs / stfs is 1:1, all four branches, all
//     three exits, the exact symbol set and the exact frame.
//   * PARK REASON: the residual is (a) those 9 copies and (b) the ORDER of
//     ~100 independent psq_l/psq_st/stfs inside the two hot blocks.  Both
//     are GCC-2.95 regalloc/sched2 outputs, i.e. strictly BELOW the front
//     end — the C below already yields the right instruction graph.  That
//     is the §7 dead end (a sched2 cheapest-ready tie / HI16-anchor-class
//     wall), not a semantics gap.
//   * MEASURED AND REJECTED (each re-measured on this body, masked %):
//     base 10.8.  Flags all inert-or-worse: -fno-sched-interblock 10.8,
//     -fno-sched-spec 10.8, -fno-thread-jumps 10.8, -fno-branch-count-reg
//     10.8, -fno-schedule-insns2 10.2, -fno-schedule-insns 3.0, -fno-gcse
//     2.4, -fno-rerun-cse-after-loop 6.0.  Zero-code `__asm__ __volatile__("")`
//     layout barriers at 5 phase boundaries of the exit-1 block: every subset
//     tested scored 8.4-10.2 (worse).  Statement-order permutations of the
//     ob-member / self-member / f8 pre-load block (5 hand-chosen orders):
//     all 10.8.  Swapping `fr.e0`/`fr.d8` at the top (chosen because it puts
//     two more prologue positions byte-exact) : 10.8 either way.
//   * NOT TRIED: (1) `register __ps_t u __asm__("fr0")`-style FPR pins on the
//     three P108/P118/P120 temps — the natural way to force the 5 `ps_mr`,
//     but pinning is a guess at want's colouring and every pin tried on
//     other functions has been a coin flip.  (2) rewriting the exit-1 body
//     as `goto`-labelled straight-line segments to change sched2's region
//     boundaries (barriers only *hurt*).  (3) a `-fno-schedule-insns2` +
//     barrier combination.
//
// ROUND HISTORY
//   2026-09-27 (r4): DIFF 7.2%, object 612 B / 153 words.  That body was
//   built on a WRONG A-form field map (it claimed "ps_add x8, ps_sub x4,
//   ps_mul x2 …" and read `8(r9)` as sp+8), so several expressions were
//   mis-derived.
//   2026-10-01 (r5): DIFF 10.8%, object 632 B / 158 words.  Fixed the field
//   map, the two wrong frame-member reads, the pass-1/pass-2 operand order
//   and the p120-vs-p128 scale factors.  Op-class multiset now exact.
//
// TWO TRANSFERABLE FINDINGS FROM THIS ROUND
// (1) THE PAIRED-SINGLE A-FORM FIELD MAP (what r4 got wrong).  Gekko A-form
//     is  opcode(6) frD(5) frA(5) frC(5) frB(5) xo5(5) Rc(1)  — i.e. bits
//     25-21 = D, 20-16 = A, 15-11 = C, 10-6 = B, 5-1 = xo5, and the
//     10-bit XO = bits 10-1 = B<<5 | xo5.  Assembler OPERAND ORDER per
//     family is NOT uniform:
//        ps_add / ps_sub / ps_div          D,A,B
//        ps_mul / ps_muls0 / ps_muls1      D,A,C
//        ps_madd / ps_msub / ps_nmadd / ps_nmsub / ps_sel   D,A,C,B
//        ps_sum0 / ps_sum1                 D,A,B,C
//        ps_mr / ps_abs / ps_nabs / ps_neg D,B
//     Use tools/ps_diff.py's `dec()` (probe-verified mnemonic-by-mnemonic
//     against cc1.exe) instead of hand-rolling it; the naive "D=25-21
//     A=20-16 B=15-11 C=21-25" reading makes every ps_mr look like a
//     4-operand ps_sel and silently rewrites the arithmetic.
// (2) `addi rN, r1, K` IN THE PROLOGUE + `off(rN)` MUCH LATER means rN is
//     the AGGREGATE BASE, not the member.  Here `addi r9, r1, 8` (early) is
//     `&fr`, and the late `psq_l f0, 8(r27)` is sp+0x10 = fr.b, while the
//     `psq_st f13, 8(r1)` in the same block is sp+0x08 = fr.a.  Reading
//     `off(rN)` as `sp+off` swaps the two frame members and produces a
//     plausible-looking body that can never match.  Diagnostic: if a want
//     has an `addi rN, r1, <frame-ish constant>` in the first ~8 words and
//     an `off(rN)` with a NON-ZERO off much later, rN is the frame struct
//     pointer.
// (3) HAZARD — the batch-assigned LEAF_TMPDIR was NOT private: it already
//     held ~500 stale .o files from a prior run AND had a concurrent
//     writer, which produced phantom scores (a barrier variant "measured"
//     12.6% and the identical no-barrier body "measured" 10.8/10.2 in three
//     runs of the SAME file).  A per-agent SUBdirectory
//     ($LEAF_TMPDIR=<private dir>) is deterministic —
//     three runs, three identical numbers.  This is exactly the race
//     score_body.py's docstring warns about, so always verify a surprising
//     result by re-running it.
//
// INERT: not registered in splits.txt/configure.py — never compiled by the
// real build, not counted in objdiff progress.  activate via tools/wip.py.
#include "types.h"

typedef union {
    __ps_t ps;
    struct { f32 hi; f32 lo; } flt;
} PSU;

/* receiver: 0x20..0x3F is one 4-float block read as two P2 pairs (a0..a3),
   0x50..0x5F likewise (b0/b1), 0x134C is the s32 handed to fn_800B6578.
   File-local because the shared Unk_* class types every slot s32, which turns
   each f32 load into an xoris/0x4330 int->double dance and gets the whole f32
   body DCE'd. */
typedef struct {
    char pad_000[0x20];
    __ps_t a0, a1, a2, a3;
    char pad_040[0x10];
    __ps_t b0, b1;
    char pad_060[0x12EC];
    s32 f134C;
} S65C4;

/* the object fn_80107998 fills and fn_80107B20 bakes (lives at sp18).
   n80 is read with lfs (scalar lane only) but fr.f8 mirrors it into a PSU. */
typedef struct {
    __ps_t p00, p08;
    PSU p10;
    __ps_t p18;
    char pad_020[0x60];
    PSU n80;
    __ps_t n88, n90, n98, nA0;
    s32 link;
    char pad_AC[4];
} O65C4;

/* frame template: &fr == sp8, so every displacement is retail's.  Members end
   at 0x130; the five saved registers (retail's r27..r31) top the locals up to
   0x134 => stmw r27 @0x134, LR @0x14c, frame 0x148.  Adding explicit tail
   padding here BREAKS the frame (masked 7.2% -> 5.4%): the 5th saved register
   is what supplies the size. */
typedef struct {
    __ps_t a;       /* sp08  <- self->a0, read back at 0x67C8 as 8(r1)  */
    __ps_t b;       /* sp10  <- self->a1, read back at 0x67B0 as 8(r27) */
    O65C4 ob;       /* sp18  <- &ob is r30/r28 in retail                   */
    char pad_0C8[0x10];
    __ps_t d8;      /* spD8 */
    __ps_t e0;      /* spE0 */
    __ps_t e8;      /* spE8 */
    __ps_t f0;      /* spF0 */
    PSU f8;         /* spF8 */
    PSU p100;
    PSU p108;
    PSU p110;
    PSU p118;
    PSU p120;
    PSU p128;
} FR65C4;

extern __ps_t lbl_80298F18;      /* {-17.125, -13.8125} */
extern f32 lbl_80299148;          /* 0x7C601A14 */
extern f32 lbl_8029914C;          /* 32.0f */
extern f32 lbl_80299150;          /* 0xE0030000 */

void *fn_80107998(O65C4 *, __ps_t *, __ps_t *);
s32 fn_80107B20(O65C4 *, s32, s32);
s32 fn_800B6578(s32, void *, s32, f32);
void CObject_RemoveRefLink(void *, void *);

void fn_800C65C4(S65C4 *self, __ps_t *mat) {
    FR65C4 fr;
    __ps_t A, B, C, D, E, F, M0, M1, R, s0, s1, s2, t, u;
    /* declaration-level hoist, no asm: this is what makes GCC home the
       frame base in a callee-saved register (retail's r27, used as
       `8(r27)` = &fr.b) and reach 5 saved regs / frame 0x148. */
    FR65C4 *pfr = &fr;

    /* matrix add, staged so retail's psq_l/ps_add/psq_st order falls out */
    fr.a = self->a0;
    fr.b = self->a1;
    fr.e0 = __builtin_ps_add(self->a1, mat[1]);
    fr.d8 = __builtin_ps_add(self->a0, mat[0]);
    fn_80107998(&fr.ob, &self->a0, &fr.d8);

    if (fn_80107B20(&fr.ob, 0, 0) != 0) {
        C = fr.ob.n88;
        D = fr.ob.n90;
        A = fr.ob.n98;
        B = fr.ob.nA0;
        E = self->a2;
        F = self->a3;
        M1 = mat[1];
        M0 = mat[0];
        fr.f8.flt.hi = fr.ob.n80.flt.hi;   /* scalar: only lane 0 is defined */

        self->a0 = __builtin_ps_add(C, A);
        self->a1 = __builtin_ps_add(D, B);
        /* pass 1: dot-ish scalar, doubled, subtracted back out of mat[] */
        s1 = __builtin_ps_muls0(M1, fr.f8.ps);
        s2 = __builtin_ps_muls0(M0, fr.f8.ps);
        s0 = __builtin_ps_mul(s1, B);
        s0 = __builtin_ps_merge00(s0, lbl_80298F18);
        s0 = __builtin_ps_madd(s2, A, s0);
        fr.p100.ps = __builtin_ps_sum0(s0, s0, s0);

        t = __builtin_ps_mul(F, B);
        fr.p108.flt.hi = fr.p100.flt.hi + fr.p100.flt.hi;
        u = fr.p108.ps;
        s1 = __builtin_ps_muls0(B, u);
        s2 = __builtin_ps_muls0(A, u);
        M1 = __builtin_ps_sub(M1, s1);
        M0 = __builtin_ps_sub(M0, s2);
        fr.e0 = M1;
        fr.d8 = M0;
        self->a0 = __builtin_ps_add(self->a0, M0);
        self->a1 = __builtin_ps_add(self->a1, M1);
        /* pass 2: same shape off the (E,F)/(A,B) pair, scaled by lbl_80299148 */
        s0 = __builtin_ps_merge00(t, lbl_80298F18);
        s0 = __builtin_ps_madd(E, A, s0);
        fr.p110.ps = __builtin_ps_sum0(s0, s0, s0);
        fr.p118.flt.hi = fr.p110.flt.hi * lbl_80299148;
        u = fr.p118.ps;
        fr.f0 = __builtin_ps_muls0(B, u);
        fr.e8 = __builtin_ps_muls0(A, u);
        self->a2 = __builtin_ps_sub(E, fr.e8);
        self->a3 = __builtin_ps_sub(F, fr.f0);
    } else {
        self->a0 = __builtin_ps_add(self->a0, mat[0]);
        self->a1 = __builtin_ps_add(self->a1, mat[1]);
    }

    /* re-bake: p10 FIRST so ngccc's store rotation emits 0x28,0x18,0x20,0x2C,
       0x30 exactly like retail (recipe 274 / §6j store rotation). */
    fr.ob.p10.ps = self->a0;
    fr.ob.p00 = self->a0;
    fr.ob.p08 = self->a1;
    fr.ob.p10.flt.lo = fr.ob.p10.flt.lo - lbl_8029914C;
    fr.ob.p18 = self->a1;

    if (fn_80107B20(&fr.ob, 0, 0) == 0) {
        fr.p128.flt.hi = lbl_80299150;
        fr.p120.flt.hi = lbl_80299150;
        self->a1 = pfr->b;
        self->a0 = fr.a;
        self->a3 = __builtin_ps_muls0(self->a3, fr.p120.ps);
        self->b1 = __builtin_ps_muls0(self->b1, fr.p128.ps);
        self->a2 = __builtin_ps_muls0(self->a2, fr.p120.ps);
        self->b0 = __builtin_ps_muls0(self->b0, fr.p128.ps);
    } else {
        fn_800B6578(self->f134C, &fr.ob, 1, lbl_80299150);
    }

    if (fr.ob.link != 0) {
        CObject_RemoveRefLink((void *)fr.ob.link, &fr.ob.link);
        fr.ob.link = 0;
    }
}
