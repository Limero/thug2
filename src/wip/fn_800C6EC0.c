// WIP DRAFT — hand reconstruction of fn_800C6EC0.
// Retail range 0x800C6EC0..0x800C70A4 = 0x1E4 = 484 bytes / 121 instructions.
//
// WHAT IT IS (recovered from the 484-byte body; this supersedes the earlier
// draft's reading, which had two wrong lane/offset facts — see FIXES below):
//   arg0 : transform object, f32[3] columns at +0xD0/+0xE0/+0xF0 (+0xD4/+0xE4/
//          +0xE8/+0xF4/+0xF8 the y/z of each) plus a scalar weight at +0x170.
//   arg1 : 16-byte vector {ax,ay,az,aw}   arg2 : {bx,by,bz,bw}  (both volatile:
//          the original loads arg2[1] twice, 0x6EF0 and 0x6F08)
//   1. c = arg1 x arg2, in two 2-component paired-single planes.
//      p13 = A*merge10(P,Q) - merge10(A,Bv)*P  with P = arg2[0],
//      mergeNN(X,Y) = { X.lo, X.hi } ^ NN[0] , { Y.lo, Y.hi } ^ NN[1]
//      -> p13.lo = ax*by - ay*bx (= cz of the cross product),
//         p13.hi = ay*bw - aw*by  (computed but never used)
//      [p68] = broadcast(p13.lo) , .hi = 1.0f     [p18] = merge10(p13, r)
//      where r = {b0*(az-ax), 0}, so [p18] = {p13.hi, 0} and [p18].hi is a
//      hard 0.0f — that is what makes the three `cy*Mk` products in step 2
//      evaluate to 0.0f (fmuls f1/f28/f0 with f0 = 0.0f), NOT a matrix row.
//   2. "Mv = M * c": with cx = [p18].lo = cz, cy = [p18].hi = 0, cz = [p20].lo,
//        m2' = cx*m2 + cy*m5 ;  m0' = cx*m0 + cy*m3 ;  m1' = cx*m1 + cy*m4
//        m6' = cz*m6 + m2' ;    m7' = cz*m7 + m0' ;    m8' = cz*m8 + m1'
//      stored as scalars at [p48]=m7', [p4c]=m8', [p50]=m6', [p54]=[p20].hi=cz_
//   3. paired-single reduction, reading the scalar pairs back as 8-byte slots:
//      t = (m6', [p54]); e0 = (m7', m8')
//      q  = merge10(e0,t) * A ;  r = e0*q - q ;  r = merge00(r,r)   (u, u)
//      [p78] = (u, 1.0f) ;  t = merge00(t,e0)*B - merge10(t2,t2)
//      e1 = [p10].lo*wgt + u ;  e2 = [p08]*wgt + merge10(r, t2)
//      return 1.0f / ps_sum0( P*e2 + merge00(Q*merge00(e1,[z]), [z]) )
//   dead stores at [p28],[p30],[p38],[p40],[p54],[p58],[p60] — the `volatile`
//   on FRM below is what keeps them (a plain struct lets GCC drop them).
//
// FIXES vs the previous draft (both were real bugs, both cost the 3.3%):
//   (a) `typedef union { f32 hi, lo; __ps_t ps; }` — under -mps-float BOTH f32
//       members land at offset 0 (verified by probe: `union{f32 lo,hi;__ps_t ps;}`
//       emits `stfs` at the SAME offset twice, while `f32[2]` is correct).  The
//       old frame template therefore put 0x6c/0x7c stores at 0x68/0x78.  All
//       two-lane slots are now `f32[N]` arrays.
//   (b) `m8` was used both for arg0->vF4 and for [p20].hi, so GCC
//       forward-propagated and never emitted `lfs f27, 0xf4(r3)`; they are now
//       separate variables (m8 keeps vF4, w2 holds [p20].hi).
//   (c) the old `return lbl_80299170 / m8` re-materialised the constant a third
//       time; it is now `return s / w1` reusing the ONE already in `s`.
//   (d) `extern volatile f32 lbl_80299170` — the original really does load it
//       twice (0x6F74 into f11 for [p68].hi and 0x7008 into f5 for [p78].hi +
//       the fdivs numerator); with a plain extern CSE merges them into one.
//
// PARKED 2026-10-02 (w75/0x800C6EC0): DIFF 3.3% — got 460 B / 115 insns vs
// retail 484 B / 121.  The opcode MULTISET is now identical except for
//   3 x ps_mr + 2 x fmr  (5 registers the original copies and gcc 2.95 copy-
//     propagates away in every spelling tried) and 1 x `addi r10,r1,8`;
// plus one unused 8-byte spill slot that pushes the frame 0xc8 vs 0xc0.
//   1. FRAME.  want 0xc0 = 0x08 linkage + 0x80 FRM + 0x38 FPR save area.
//      got 0xc8: gcc allocates an 8-byte slot it then never uses (7 stfd at
//      0x90..0xc0, i.e. 8 bytes past 0x88).  Recipes 4c: "want frame =
//      ngccc-native + 8 when a stack double exists" — here the +8 is ALREADY
//      applied (adding `volatile double _dummy;` makes it 0xd0), and the extra
//      8 is register pressure, not alignment: deleting one 8-byte FRM field
//      gives 0xc0 but costs 2 instructions, and removing any dead store does
//      not shrink it.  Tried: -fno-expensive-optimizations (worse), dummy
//      double (+8 too many), w2 reused via a dead scalar (2.5%), adjacent
//      load/store of [p54] (0xd0 + 8 stfd).
//   2. COPY ELIMINATION.  want keeps ps_mr at 0x6EF4 (f8=f0), 0x6F8C (f0=f12),
//      0x6F94 (f6=f13), 0x6FFC (f12=f0), 0x7038 (f0=f12) and fmr at 0x7028
//      (f12=f5), 0x7078 (f1=f13); got keeps only 3 ps_mr + 1 fmr.  These are
//      reload/reload-alias artefacts, not source-level copies: a probe with an
//      explicit `g = t;` between two `ps_muls0` emits no ps_mr, and reading a
//      volatile slot into two variables also emits none.  Tried: two distinct
//      variables fed from the same reload, PS->SF low-lane extraction for the
//      muls0 weight, moving the copy far from the store.
//   3. ADDRESSING.  want materialises r10 = r1+8 once and uses 8(r10) for both
//      [p10] accesses while keeping 8(r1) for [p08]; every construct tried
//      (`volatile __ps_t *q = &fs.p10`, byte-pointer arithmetic, `q10 += 1`)
//      is folded straight back to 16(r1).
//
// RE-CONFIRMED 2026-10-05: still DIFF 0.83% (score fell 3.3 -> 0.83 only
// because this run measured the bare body; the opcode multiset claim below is
// unchanged).  Four new measurements, all negative, that CLOSE OFF the obvious
// next ideas so nobody re-grinds them:
//   4. LOCALS CENSUS IS NOW EXACT — the want's stack traffic is
//      {0x18,0x1c,0x20,0x24} {0x48,0x4c,0x50,0x54} {0x6c,0x70,0x7c,0x80} plus
//      7 stfd; got hits the IDENTICAL set.  So the FRM template is right and
//      every slot lands on its retail offset.  The +8 frame is one genuinely
//      unused 8-byte slot that gcc allocates between FRM and the FPR save area.
//      The want is a straight-line body with ZERO calls, so every psq_st in it
//      is a real spill — there is no callee-frame explanation for the slot.
//   5. SINGLE-STATEMENT DROP SWEEP (76 statements, drop one at a time, score +
//      frame + size each): every one of the 14 drops that DOES reach frame
//      0xc0 also deletes a wanted instruction (best 0.41% vs base 0.83%), and
//      no drop reaches 484 B.  There is no free 8 bytes: the phantom slot is
//      not attributable to any single removable statement.
//   6. FRM SHRINK SWEEP: removing p80/p80-scalar/p08/p58/p60/p28/p30/p38/p40
//      gives 0xb8-0xd0 and never 0xc0 with a better score (best: no-p58p60 and
//      no-p28p30 both 0.83% but frame 0xb8 = 8 too FEW).  Removing exactly one
//      8-byte field overshoots by 8, confirming the slot count is 1 too high
//      and no field is individually responsible.
//   7. PS-TEMP ALIASING (13 pairwise merges of the 13 __ps_t temps): three
//      reach frame 0xc0 (e1<-e2, Z<-Q, e2<-g0) but all score 0.21% — the frame
//      fix costs more in lost copies than it gains.  No merge helps.
//   8. F32 DECLARATION ORDER IS NOT THE LEVER: 15 orders (reversed, rotated,
//      m0/m3-grouped, 12 seeded shuffles of the 9 matrix columns) all score
//      IDENTICALLY at 0.83% and only permute which of f25/f26 holds m0 vs m1.
//      ngccc's callee-saved FPR numbering is NOT source-declaration-driven
//      here, so "reorder the locals" cannot reach retail's {m1,m4,m8,m3,m0,m7,m6}.
//
// Residual is a register-allocation + scheduling chase on a 121-instruction
// paired-single body: got assigns the 7 callee-saved FPRs to
// {m2,m0,m1,m8,t,ONE,m3} where retail uses {m1,m4,m8,m3,m0,m7,m6}.
// family=m2c range=0x800C6EC0-0x800C70A4 size=484B
// FLAG: -mps-float
#include "types.h"

typedef struct {
    u8 pad0[0xD0];
    f32 vD0, vD4, vD8;
    u8 pad1[4];
    f32 vE0, vE4, vE8;
    u8 pad2[4];
    f32 vF0, vF4, vF8;
    u8 pad3[0x170 - 0xFC];
    f32 v170;
} S800C6EC0;

/* frame template: 0x80 bytes, every slot on its retail offset */
typedef struct {
    __ps_t p08;
    __ps_t p10;
    f32    p18[2];
    f32    p20[2];
    __ps_t p28;
    __ps_t p30;
    __ps_t p38;
    __ps_t p40;
    f32    p48[2];
    f32    p50[2];
    __ps_t p58;
    __ps_t p60;
    f32    p68[2];
    f32    p70[2];
    f32    p78[2];
    f32    p80[2];
} FRM;

extern volatile f32 lbl_80299170;
extern __ps_t lbl_80298F18[];

f32 fn_800C6EC0(S800C6EC0 *arg0, volatile __ps_t *arg1, volatile __ps_t *arg2)
{
    volatile FRM fs;
    __ps_t A, B, P, Q, Z, p, q, r, t, g0, e0, e1, e2;
    f32 s, m0, m1, m2, m3, m4, m5, m6, m7, m8, wgt, cx, cy, cz, w1, w2;

    /* ---- 1. c = arg1 x arg2 (two paired-single planes) ---- */
    e0 = arg2[0];
    B  = arg1[1];
    Q  = arg2[1];
    P  = e0;
    fs.p08 = e0;
    A  = arg1[0];
    p  = __builtin_ps_merge10(P, Q);
    e1 = arg2[1];
    q  = __builtin_ps_merge10(A, B);
    fs.p10 = e1;
    p  = __builtin_ps_mul(A, p);
    wgt = arg0->v170;
    e1 = __builtin_ps_mul(q, P);
    e2 = fs.p08;
    fs.p70[0] = wgt;
    p  = __builtin_ps_sub(p, e1);
    e1 = __builtin_ps_merge00(p, p);
    m3 = arg0->vE0;
    q  = __builtin_ps_merge00(P, Q);
    m4 = arg0->vE4;
    r  = __builtin_ps_merge00(B, A);
    m5 = arg0->vE8;
    r  = __builtin_ps_mul(r, q);
    m0 = arg0->vD0;
    m1 = arg0->vD4;
    q  = __builtin_ps_merge10(r, r);
    m2 = arg0->vD8;
    r  = __builtin_ps_sub(r, q);
    m6 = arg0->vF8;
    p  = __builtin_ps_merge10(p, r);
    m7 = arg0->vF0;
    B  = __builtin_ps_merge00(A, B);
    *(volatile __ps_t *)&fs.p68 = e1;
    m8 = arg0->vF4;
    fs.p68[1] = lbl_80299170;
    *(volatile __ps_t *)&fs.p18 = p;

    /* ---- 2. Mv = M * c ---- */
    s  = *(volatile __ps_t *)&fs.p68;
    t  = *(volatile __ps_t *)&fs.p70[0];
    e0 = s;
    *(volatile __ps_t *)&fs.p20 = e0;
    g0 = t;
    cy = fs.p18[1];
    e2 = __builtin_ps_muls0(e2, g0);
    e1 = *(volatile __ps_t *)&fs.p10;
    cx = fs.p18[0];
    m5 = cy * m5;
    cz = fs.p20[0];
    m3 = cy * m3;
    w2 = fs.p20[1];
    m2 = cx * m2 + m5;
    e1 = __builtin_ps_muls0(e1, g0);
    fs.p28 = e2;
    fs.p50[1] = w2;
    m4 = cy * m4;
    fs.p30 = e1;
    m0 = cx * m0 + m3;
    m1 = cx * m1 + m4;
    m6 = cz * m6 + m2;
    m7 = cz * m7 + m0;
    fs.p50[0] = m6;
    m8 = cz * m8 + m1;
    fs.p48[0] = m7;
    fs.p48[1] = m8;

    /* ---- 3. paired-single reduction ---- */
    t  = *(volatile __ps_t *)&fs.p50;
    e0 = *(volatile __ps_t *)&fs.p48;
    fs.p38 = e0;
    g0 = e0;
    fs.p40 = t;
    q  = __builtin_ps_merge10(g0, t);
    s  = lbl_80299170;
    q  = __builtin_ps_mul(q, A);
    r  = __builtin_ps_mul(g0, q);
    r  = __builtin_ps_sub(r, q);
    t  = __builtin_ps_merge00(t, g0);
    r  = __builtin_ps_merge00(r, r);
    *(volatile __ps_t *)&fs.p78 = r;
    w1 = s;
    fs.p78[1] = w1;
    t  = __builtin_ps_mul(t, B);
    g0 = *(volatile __ps_t *)&fs.p78;
    e1 = __builtin_ps_add(e1, g0);
    fs.p60 = g0;
    t  = __builtin_ps_merge10(t, t);
    *(volatile __ps_t *)&fs.p50 = e1;
    t  = __builtin_ps_sub(t, t);
    Q  = __builtin_ps_mul(Q, e1);
    r  = __builtin_ps_merge10(r, t);
    e2 = __builtin_ps_add(e2, r);
    fs.p58 = r;
    Z  = lbl_80298F18[0];
    Q  = __builtin_ps_merge00(Q, Z);
    *(volatile __ps_t *)&fs.p48 = e2;
    P  = __builtin_ps_madd(P, e2, Q);
    P  = __builtin_ps_sum0(P, P, P);
    *(volatile __ps_t *)&fs.p80 = P;
    m8 = fs.p80[0];
    w1 = m8;
    return s / w1;
}
