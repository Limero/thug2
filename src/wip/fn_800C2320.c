// WIP DRAFT (non-matching) — hand-rebuilt from the retail disassembly.
// family=m2c range=0x800C2320-0x800C29B4 size=1684B
//
// VERDICT 2026-10-07: vC+p8 rewrite, got 1684B = want 1684B (length EXACT).
// Frame 0x68 + f31 + stmw r30/r31 + LR slot now EXACT. Structural model rebuilt
// from PS decodes:
//  - Obj struct fixed (_pFC 0x14, was 0x114 shifting post-0xFC by +0x100)
//  - matrix values fixed (m78 = p7+p6, not p8+p12; p7 dual-use kills fmsubs)
//  - 9 stack slots are volatile Pair unions; single-read discipline via t/u
//  - VPair *p8 = &sp8 forces r30=r1+8 base for all 8 sp10 reloads (8(r30))
//  - Obj/node pair loads/stores + ps_add/ps_muls0 builtins + ps_mr copies
//  - loop1: int off + i-- != 0 (n trips); loop2: i-- != 0 (2 trips); n2--
//  - node 2nd-pair stores are sp10 (not sp8); iC0/iC8 are pair stores
// RESIDUAL: matrix scheduler order/regs (r10/r11 bases, mul order); missing
//   ps_mr's; dead-operand fields of ps ops; hoisted addis; 4 fwd sp10 loads.
// See AGENTS-recipes park notes for the full derivation.
//
// PARKED 2026-10-07: re-measured 28/421 words (6.7%),
// length + frame still EXACT.  I re-derived the whole body against
// build/b34pkt/fn_800C2320.psdiff.txt and the divergence is NOT semantic: the
// magnitude test (nested fmuls/fmadds), the v/m matrix, block 2
// (q160..q16C -> sp18/sp20 -> p110/p118) and both node loops compute the same
// expressions as the want.  It is one EARLY ORDERING difference that cascades:
//   At offset 0x20 retail derives the v40 address into r10 from r31 plus
//   0x40, while the build derives the sp8 address into r30 from r1 plus 8.
//   At offset 0x28 retail derives the m70 address into r11 from r31 plus
//   0x70, while the build only materialises the v40 address at offset 0x60,
//   then reuses r9 for the m70 address at 0x8C and folds the first vector
//   element to 0x40(r31).
// so want keeps BOTH matrix base pointers live across the magnitude branch while
// cc1 materialises the stack base there instead.  THIS ROUND: `v = &arg0->v40;
// m = &arg0->m70;` were hoisted above the magnitude `if` (they used to sit just
// after it) -- the only source-level difference that can explain want's
// 0x20/0x28 pair.  UNVERIFIED (this worker is terminal-less): measure via
// `tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800C2320`; if it is
// not > 6.65%, move the two lines back below the `if` -- nothing else changed.
// Still open after that (all scheduler-class, no source fix identified):
//  4 fwd sp10 reloads; the ps_mr copies into a scratch FPR before the pair
//  stores (want 0x194/0x200/0x324/...); loop2's `addi r9,r31,0x250` preheader.
// Do NOT try further register/permutation sweeps on the matrix store order --
// the draft already emits the want's 0xD8..0x124 order.
//
// 2026-10-07 (worker, continuation): the FIRST real
// divergence is one extra ENTRY-BLOCK instruction.  Re-reading the packet with
// the earlier v/m hoist in place, got is byte-identical to want through 0x40
// and then emits `addi r30, r1, 8` at 0x44 where want's 0x44 is already the
// magnitude `fmadds`.  Everything from 0x44 on is then offset by one word, and
// a second divergence (got's `mr r3,r31` call setup at 0x9C vs want's at 0xB0)
// follows from the same allocation change.  Cause: `VPair *p8 = &sp8;` sat in
// the declaration block, so cc1 materialised the stack base in the entry block;
// want forms the identical `addi r30,r1,8` at 0xA8, in a later block.  FIX:
// the initialiser was removed and `p8 = &sp8;` now sits at the pointer's first
// use (just before the `{ f32 e0, e1, e9; }` block).  `p8` is only ever read as
// `p8[1]` (= `sp10`), so the r1+8 base the note above describes is preserved.
// UNVERIFIED (terminal-less worker): measure with
// `tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800C2320`; if it does
// not beat 8.08%, restore `VPair *p8 = &sp8;` in the declaration block and drop
// the standalone assignment -- nothing else changed.
//
#include "types.h"

extern f32 lbl_80299058; /* 0.0f */
extern f32 lbl_8029905C; /* 2.0f */
extern f32 lbl_80299060; /* 1.0f */

void fn_800C2D08(void *);
void fn_800C31E0(void *);

typedef struct Obj {
    char _p00[0x20];
    f32 p20, p24, p28, p2C;
    f32 v30, v34, v38, v3C;
    f32 v40, v44, v48, v4C;
    f32 v50, v54, v58, v5C;
    char _p60[0x10];
    f32 m70, m74, m78;
    char _p7C[4];
    f32 m80, m84, m88;
    char _p8C[4];
    f32 m90, m94, m98;
    char _p9C[4];
    f32 gA0, gA4, gA8, gAC;
    f32 hB0, hB4, hB8, hBC;
    f32 iC0, iC4, iC8, iCC;
    f32 kD0, kD4, kD8;
    char _pDC[4];
    f32 kE0, kE4, kE8;
    char _pEC[4];
    f32 kF0, kF4, kF8;
    char _pFC[0x14];
    f32 p110, p114, p118, p11C;
    char _p120[0x40];
    f32 q160, q164, q168, q16C, q170;
    char _p174[0x38];
    s32 n1AC;
    char _p1B0[0x140];
    s32 *nodes2F0;
} Obj;

typedef struct N1 {
    f32 n40, n44, n48, n4C;
    char _p50[0x50];
    f32 n80, n84, n88, n8C;
    f32 n90, n94, n98, n9C;
    char _pA0[8];
    f32 nA8, nAC, nB0, nB4;
    char _pB8[8];
    f32 nC0, nC4, nC8;
} N1;

typedef struct N2 {
    f32 p00, p04, p08, p0C;
    f32 p10, p14, p18, p1C;
    f32 p20, p24, p28, p2C;
    f32 p30, p34;
    f32 p38, p3C;
    f32 p40, p44, p48, p4C;
    f32 r50, r54, r58, r5C;
    f32 r60, r64, r68, r6C;
    f32 r70, r74, r78, r7C;
    f32 s80, s84;
} N2;

typedef volatile union { f32 f[2]; __ps_t p; } VPair;

void fn_800C2320(Obj *arg0) {
    VPair sp8, sp10, sp18, sp20, sp28, sp30, sp38, sp40, sp48;
    VPair *p8;
    __ps_t t, u;
    f32 sc;
    f32 zero;
    s32 n, i;
    s32 off;
    N1 *n1;
    N2 *n2;
    f32 *v;
    f32 *m;

    /* HOISTED ABOVE THE TEST 2026-10-07: want materialises the two
       matrix base pointers at 0x20/0x28 -- live across the magnitude branch
       and used up to the matrix stores at 0xD8..0x124 -- exactly as these two
       initialisers written BEFORE the `if` do.  Written after it (the previous
       body) cc1 instead put `addi r30,r1,8` (&sp8) at 0x20 and only formed
       &v40 at 0x60.  UNVERIFIED (terminal-less worker): if the measured score
       does not improve, move these two lines back below the `if`. */
    v = &arg0->v40;
    m = &arg0->m70;

    if (arg0->v4C * arg0->v4C
        + (arg0->v48 * arg0->v48
         + (arg0->v40 * arg0->v40 + arg0->v44 * arg0->v44)) > lbl_80299058) {
        sc = lbl_8029905C
           / (arg0->v4C * arg0->v4C
            + (arg0->v48 * arg0->v48
             + (arg0->v40 * arg0->v40 + arg0->v44 * arg0->v44)));
    } else {
        sc = lbl_80299058;
    }
    {
        f32 p4, p10, p0, p8, p12, p11, p7, p2, p6, p9, p13, pm44;
        f32 t5812;
        p4 = v[0] * sc;
        p10 = v[1] * sc;
        p0 = v[2] * sc;
        p8 = v[0] * p4;
        p12 = v[1] * p10;
        p11 = v[2] * p0;
        p7 = v[0] * p0;
        pm44 = v[3] * p4;
        t5812 = p8 + p12;
        p2 = v[3] * p0;
        p6 = v[3] * p10;
        p9 = v[1] * p0;
        p13 = v[0] * p10;
        m[2] = p7 + p6;
        m[6] = p9 - pm44;
        m[1] = p13 - p2;
        m[8] = p7 - p6;
        m[9] = p9 + pm44;
        m[0] = lbl_80299060 - (p12 + p11);
        m[5] = lbl_80299060 - (p8 + p11);
        m[10] = lbl_80299060 - t5812;
        m[4] = p13 + p2;
    }
    zero = lbl_80299058;
    {
        f32 *g = &arg0->gA0;
        g[0] = zero;
        g[3] = lbl_80299060;
        g[1] = zero;
        g[2] = zero;
    }

    /* MOVED TO ITS FIRST USE 2026-10-07: this was `VPair *p8 = &sp8;` in the
       declaration block, which put `addi r30,r1,8` in the ENTRY block (got
       emits it at 0x44, right after the two matrix `addi r7/r8`), shifting
       every following instruction by one word.  want forms the same base at
       0xA8, i.e. in a later block -- so the pointer's definition belongs at
       its first use.  `p8` is only ever read as `p8[1]`, i.e. `&sp8 + 8` ==
       `sp10`, so the base is still forced to r1+8 for those reads. */
    p8 = &sp8;

    {
        f32 e0, e1, e9;
        e0 = arg0->q160 * arg0->m70 + arg0->q164 * arg0->m80;
        e1 = arg0->q160 * arg0->m74 + arg0->q164 * arg0->m84;
        e9 = arg0->q160 * arg0->m78 + arg0->q164 * arg0->m88;
        sp18.f[0] = arg0->q168 * arg0->m90 + e0;
        sp18.f[1] = arg0->q168 * arg0->m94 + e1;
        sp20.f[0] = arg0->q168 * arg0->m98 + e9;
        t = sp18.p;
        sp8.p = t;
        *(__ps_t *)&arg0->p110 = t;
        sp20.f[1] = arg0->q16C;
        sp10.p = sp20.p;
        *(__ps_t *)&arg0->p118 = p8[1].p;
    }
    fn_800C2D08(arg0);

    {
        f32 a54E0, a54E4, a54E8, e0, e1, t9, iC0t, iC4t, iC8t;
        __ps_t h1, h0;
        a54E0 = arg0->v54 * arg0->kE0;
        a54E4 = arg0->v54 * arg0->kE4;
        a54E8 = arg0->v54 * arg0->kE8;
        sp38.f[0] = arg0->q170;
        t = sp38.p;
        e0 = arg0->v50 * arg0->kD0 + a54E0;
        e1 = arg0->v50 * arg0->kD4 + a54E4;
        t9 = arg0->v50 * arg0->kD8 + a54E8;
        u = t;
        iC0t = arg0->v58 * arg0->kF0 + e0;
        iC8t = arg0->v58 * arg0->kF8 + t9;
        iC4t = arg0->v58 * arg0->kF4 + e1;
        sp18.f[1] = iC4t;
        h1 = __builtin_ps_muls0(*(__ps_t *)&arg0->v38, u);
        sp18.f[0] = iC0t;
        h0 = __builtin_ps_muls0(*(__ps_t *)&arg0->v30, u);
        sp20.f[0] = iC8t;
        sp20.f[1] = arg0->v5C;
        sp8.p = sp18.p;
        *(__ps_t *)&arg0->hB8 = h1;
        *(__ps_t *)&arg0->hB0 = h0;
        *(__ps_t *)&arg0->iC0 = sp18.p;
        sp10.p = sp20.p;
        arg0->hBC = zero;
        *(__ps_t *)&arg0->iC8 = sp20.p;
    }

    n = arg0->n1AC;
    i = n - 1;
    if (n != 0) {
        off = i * 0x1E0;
        do {
            n1 = (N1 *)((char *)arg0->nodes2F0 + off);
            off -= 0x1E0;
            sp28.f[0] = n1->nB0 * arg0->m90
                    + (n1->nA8 * arg0->m70 + n1->nAC * arg0->m80);
            sp28.f[1] = n1->nB0 * arg0->m94
                    + (n1->nA8 * arg0->m74 + n1->nAC * arg0->m84);
            sp30.f[0] = n1->nB0 * arg0->m98
                    + (n1->nA8 * arg0->m78 + n1->nAC * arg0->m88);
            t = sp28.p;
            sp8.p = __builtin_ps_add(*(__ps_t *)&arg0->p20, t);
            sp30.f[1] = n1->nB4;
            u = t;
            sp18.p = u;
            u = sp30.p;
            sp20.p = u;
            sp10.p = __builtin_ps_add(*(__ps_t *)&arg0->p28, u);
            *(__ps_t *)&n1->n80 = sp8.p;
            *(__ps_t *)&n1->n88 = p8[1].p;
            *(__ps_t *)&n1->n90 = *(__ps_t *)&n1->nA8;
            *(__ps_t *)&n1->n98 = *(__ps_t *)&n1->nB0;
            n1->n94 = n1->n94 + (n1->nC0 - n1->nC8);
            sp28.f[0] = n1->n98 * arg0->m90
                    + (n1->n90 * arg0->m70 + n1->n94 * arg0->m80);
            sp28.f[1] = n1->n98 * arg0->m94
                    + (n1->n90 * arg0->m74 + n1->n94 * arg0->m84);
            sp30.f[0] = n1->n98 * arg0->m98
                    + (n1->n90 * arg0->m78 + n1->n94 * arg0->m88);
            t = sp28.p;
            sp18.p = t;
            u = t;
            sp30.f[1] = n1->n9C;
            sp8.p = __builtin_ps_add(*(__ps_t *)&arg0->p20, u);
            u = sp30.p;
            sp20.p = u;
            sp10.p = __builtin_ps_add(*(__ps_t *)&arg0->p28, u);
            *(__ps_t *)&n1->n90 = sp8.p;
            *(__ps_t *)&n1->n98 = p8[1].p;
        } while (i-- != 0);
    }

    i = 1;
    n2 = (N2 *)((char *)arg0 + 0x250);
    do {
        sp28.f[0] = n2->p08 * arg0->m90
                + (n2->p00 * arg0->m70 + n2->p04 * arg0->m80);
        sp28.f[1] = n2->p08 * arg0->m94
                + (n2->p00 * arg0->m74 + n2->p04 * arg0->m84);
        sp30.f[0] = n2->p08 * arg0->m98
                + (n2->p00 * arg0->m78 + n2->p04 * arg0->m88);
        sp30.f[1] = n2->p0C;
        t = sp28.p;
        sp18.p = t;
        u = sp30.p;
        sp20.p = u;
        sp8.p = __builtin_ps_add(*(__ps_t *)&arg0->p20, t);
        sp10.p = __builtin_ps_add(*(__ps_t *)&arg0->p28, u);
        *(__ps_t *)&n2->p30 = sp8.p;
        *(__ps_t *)&n2->p38 = p8[1].p;
        sp18.f[0] = n2->p18 * arg0->m90
                + (n2->p10 * arg0->m70 + n2->p14 * arg0->m80);
        sp18.f[1] = n2->p18 * arg0->m94
                + (n2->p10 * arg0->m74 + n2->p14 * arg0->m84);
        sp20.f[0] = n2->p18 * arg0->m98
                + (n2->p10 * arg0->m78 + n2->p14 * arg0->m88);
        sp20.f[1] = n2->p1C;
        t = sp18.p;
        sp8.p = t;
        *(__ps_t *)&n2->p40 = t;
        u = sp20.p;
        sp10.p = u;
        *(__ps_t *)&n2->p48 = p8[1].p;
        sp18.f[0] = n2->p28 * arg0->m90
                + (n2->p20 * arg0->m70 + n2->p24 * arg0->m80);
        sp18.f[1] = n2->p28 * arg0->m94
                + (n2->p20 * arg0->m74 + n2->p24 * arg0->m84);
        sp20.f[0] = n2->p28 * arg0->m98
                + (n2->p20 * arg0->m78 + n2->p24 * arg0->m88);
        sp20.f[1] = n2->p2C;
        t = sp18.p;
        sp8.p = t;
        u = sp20.p;
        sp10.p = u;
        sp40.f[0] = lbl_80299060 / n2->s80;
        sp48.f[0] = lbl_80299060 / n2->s84;
        t = sp40.p;
        u = t;
        *(__ps_t *)&n2->r60 = __builtin_ps_muls0(*(__ps_t *)&n2->p40, u);
        *(__ps_t *)&n2->r58 = p8[1].p;
        sp10.p = __builtin_ps_muls0(*(__ps_t *)&n2->p48, u);
        sp8.p = *(__ps_t *)&n2->r60;
        u = sp48.p;
        *(__ps_t *)&n2->r70 = __builtin_ps_muls0(t, u);
        sp10.p = __builtin_ps_muls0(sp10.p, u);
        *(__ps_t *)&n2->r68 = p8[1].p;
        *(__ps_t *)&n2->r50 = sp8.p;
        sp8.p = *(__ps_t *)&n2->r70;
        *(__ps_t *)&n2->r78 = p8[1].p;
        n2--;
    } while (i-- != 0);

    fn_800C31E0(arg0);
}
