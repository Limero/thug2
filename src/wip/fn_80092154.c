// WIP DRAFT (non-matching) — hand-rebuilt head of fn_80092154.
// family=m2c range=0x80092154-0x80092DD4 size=3200B
// extra_cflags: -mps-float
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------------------
// WHAT WAS PROVEN THIS ROUND (2026-10-03)
// ---------------------------------------------------------------------------
// * SIGNATURE / types.  arg0 (r3) is a pointer to a 16-byte object read as two
//   W0/I0 psq_l pairs (`psq_l f13,0(r31)` + `psq_l f0,8(r31)`), i.e. two
//   8-byte fields; arg1 (r4) goes straight to the s32 global at 0x803017F0.
//   It is NOT a `float` — the m2c draft's `s32 arg0` is right by accident only.
// * BODY LAYOUT.  Single loop; the ONLY X-form PS ops are absent — every PS op
//   is A-form opcode 4: ps_mul(62) ps_add0(91) ps_madd0_sg(61) ps_sum0(30)
//   ps_merge10(21) ps_madd(21) ps_madd0(10) ps_res_0x18(10), plus 8-byte
//   psq_l/psq_st (W0 I0) only.  So the element type is `__ps_t` (8 bytes), not
//   a 16-byte vec_float4.
// * RECORD TYPE.  r10 = 0x803B92D8 is the walk pointer and steps by 0x60 = 96,
//   matching `mulli r10,r8,0x60` in the sibling fn_80091DD4.  Element = 96 B =
//   { 4-byte pointer; __ps_t v[11]; } (4 + 88 rounds up to 96 at 8-byte
//   align) — every q read is at +0..+88 and every store at +8..+80.
// * `lwz r9,0(r10)` then q+0..+88 => field 0 is a 32-bit POINTER to another
//   96-byte record.
// * PREHEADER / control flow.  Guard is `li rI,0 / lwz r0,0x17f4(r9) /
//   cmplw rI,r0 / bge exit` — i.e. the `i=0` init sits INSIDE the rotated
//   entry block.  The five preheader words are two 0x8029xxxx anchors (one for
//   &lbl_80297174, one for the lbl_802971A8 float load — deliberately NOT
//   CSE'd because they are different reload classes), `addi r7 = &lbl_80297174`,
//   `lfs f6 = lbl_802971A8`, and `lis r9 = 0x80380000` for the 0x803B92D8 walk.
//   Loop head is exactly 3 words: `psq_l f5,0(r7)` (k), `addi r10,r9,-0x6d28`
//   (&lbl_803B92D8), `lwz r9,0(r10)` (q).  Latch reloads the count from memory
//   every iteration — consistent with no -fstrict-aliasing in GCC 2.95 and a
//   store through `e` inside the body.
// * The body is TEN hand-unrolled copies of one ~76-instruction block (ten
//   `fcmpu/bns`+`ble` float guards at 0x80092200/0x800922D0/0x800923F8/
//   0x80092520/0x80092648/0x80092770/0x8009289C/0x800929C4/0x80092AEC/
//   0x80092C14/0x80092D3C, and PS spills at sp+0xD0,0xD8,...,0x148 in order).
//   MEASURED: an explicit `for (j = 0; j < 10; j++)` loop is NOT unrolled by
//   ngccc at the project flags (-O2 -G0 -mcpu=750 -fno-common, no -funroll-*),
//   so the original source really is unrolled text.
// * FRAME.  0x158 with no FPR saves at all: the loop has no calls, so nothing
//   needs a non-volatile FPR home.  (Hoisting k/lim/a0/a1 above the two calls
//   makes cc1 emit stfd f29-f31 + stmw r30 — 0x188 frame — so those loads must
//   stay inside the loop / preheader.)  41 volatile doubles take the natural
//   0x10 frame to 0x158.
// ---------------------------------------------------------------------------
#include "types.h"

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSU;

typedef struct {
    __ps_t a;
    __ps_t b;
} V4;

typedef struct {
    __ps_t *q;
    __ps_t v[11];
} Rec;

extern f32 lbl_802971A8;
extern f32 lbl_802971AC;
extern s32 lbl_803017F0;
extern s32 lbl_803017F4;
extern s32 lbl_803B92D8;
extern __ps_t lbl_80297174;

void fn_80091DD4();
void fn_800920A4(s32, s32);

void fn_80092154(V4 *arg0, s32 arg1) {
    volatile double _dummy0;
    volatile double _dummy1;
    volatile double _dummy2;
    volatile double _dummy3;
    volatile double _dummy4;
    volatile double _dummy5;
    volatile double _dummy6;
    volatile double _dummy7;
    volatile double _dummy8;
    volatile double _dummy9;
    volatile double _dummy10;
    volatile double _dummy11;
    volatile double _dummy12;
    volatile double _dummy13;
    volatile double _dummy14;
    volatile double _dummy15;
    volatile double _dummy16;
    volatile double _dummy17;
    volatile double _dummy18;
    volatile double _dummy19;
    volatile double _dummy20;
    volatile double _dummy21;
    volatile double _dummy22;
    volatile double _dummy23;
    volatile double _dummy24;
    volatile double _dummy25;
    volatile double _dummy26;
    volatile double _dummy27;
    volatile double _dummy28;
    volatile double _dummy29;
    volatile double _dummy30;
    volatile double _dummy31;
    volatile double _dummy32;
    volatile double _dummy33;
    volatile double _dummy34;
    volatile double _dummy35;
    volatile double _dummy36;
    volatile double _dummy37;
    volatile double _dummy38;
    volatile double _dummy39;
    volatile double _dummy40;
    s32 i;
    Rec *e;

    lbl_803017F0 = arg1;
    fn_80091DD4();
    fn_800920A4((s32)arg0, (s32)arg0);
    e = (Rec *)&lbl_803B92D8;
    for (i = 0; i < (u32)lbl_803017F4; i++, e++) {
        __ps_t *q = e->q;
        f32 lim = lbl_802971A8;
        __ps_t k = lbl_80297174;
        __ps_t a0 = arg0->a;
        __ps_t a1 = arg0->b;
        PSU u0, u1, u2, u3, u4, u5, u6, u7, u8, u9;
        __ps_t p0, p1, p2, p3, p4, p5, p6, p7, p8, p9;
        __ps_t m0, m1, m2, m3, m4, m5, m6, m7, m8, m9;
        f32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;
        // Block 1 is transcribed from 0x800921B0..0x800927CC: q[2]/q[3] go
        // through two chained ps_mul, m0 = a0*a0 + a0, lo(m0) is tested
        // against lim with the `!(t >= lim)` / fcmpu+cror+bns polarity, and
        // v[1] receives p0 + k.  Blocks 2..10 are STRUCTURAL GUESSES (correct
        // shape, not verified operand-by-operand).
        p0 = __builtin_ps_mul(__builtin_ps_mul(a0, q[2]), q[3]);
        m0 = __builtin_ps_madd(a0, a0, a0);
        u0.ps = m0; t0 = u0.flt.lo;
        if (!(t0 >= lim)) t0 = lbl_802971AC;
        e->v[1] = __builtin_ps_add(p0, k);
        p1 = __builtin_ps_mul(__builtin_ps_mul(a0, q[4]), q[5]);
        m1 = __builtin_ps_madd(a1, a1, a1);
        u1.ps = m1; t1 = u1.flt.lo;
        if (!(t1 >= lim)) t1 = lbl_802971AC;
        e->v[3] = __builtin_ps_add(p1, k);
        p2 = __builtin_ps_mul(__builtin_ps_mul(a0, q[6]), q[7]);
        m2 = __builtin_ps_madd(a0, a1, a1);
        u2.ps = m2; t2 = u2.flt.lo;
        if (!(t2 >= lim)) t2 = lbl_802971AC;
        e->v[4] = __builtin_ps_add(p2, k);
        p3 = __builtin_ps_mul(__builtin_ps_mul(a0, q[8]), q[9]);
        m3 = __builtin_ps_madd(a1, a0, a0);
        u3.ps = m3; t3 = u3.flt.lo;
        if (!(t3 >= lim)) t3 = lbl_802971AC;
        e->v[6] = __builtin_ps_add(p3, k);
        p4 = __builtin_ps_mul(__builtin_ps_mul(a1, q[2]), q[3]);
        m4 = __builtin_ps_madd(a1, a1, a0);
        u4.ps = m4; t4 = u4.flt.lo;
        if (!(t4 >= lim)) t4 = lbl_802971AC;
        e->v[8] = __builtin_ps_add(p4, k);
        p5 = __builtin_ps_mul(__builtin_ps_mul(a1, q[4]), q[5]);
        m5 = __builtin_ps_madd(a1, a0, a1);
        u5.ps = m5; t5 = u5.flt.lo;
        if (!(t5 >= lim)) t5 = lbl_802971AC;
        e->v[10] = __builtin_ps_add(p5, k);
        p6 = __builtin_ps_mul(__builtin_ps_mul(a0, q[10]), q[10]);
        m6 = __builtin_ps_madd(a0, a0, a0);
        u6.ps = m6; t6 = u6.flt.lo;
        if (!(t6 >= lim)) t6 = lbl_802971AC;
        e->v[2] = __builtin_ps_add(p6, k);
        p7 = __builtin_ps_mul(__builtin_ps_mul(a1, q[8]), q[9]);
        m7 = __builtin_ps_madd(a1, a1, a0);
        u7.ps = m7; t7 = u7.flt.lo;
        if (!(t7 >= lim)) t7 = lbl_802971AC;
        e->v[5] = __builtin_ps_add(p7, k);
        p8 = __builtin_ps_mul(__builtin_ps_mul(a0, q[4]), q[5]);
        m8 = __builtin_ps_madd(a0, a1, a0);
        u8.ps = m8; t8 = u8.flt.lo;
        if (!(t8 >= lim)) t8 = lbl_802971AC;
        e->v[7] = __builtin_ps_add(p8, k);
        p9 = __builtin_ps_mul(__builtin_ps_mul(a1, q[6]), q[7]);
        m9 = __builtin_ps_madd(a1, a1, a1);
        u9.ps = m9; t9 = u9.flt.lo;
        if (!(t9 >= lim)) t9 = lbl_802971AC;
        e->v[9] = __builtin_ps_add(p9, k);
    }
}

// PARKED 2026-10-03: 1.63% official (13 masked-matching words out
// of 800), object 368B vs symbol 3200B; index-aligned first-24-word score went
// 29.17% -> 54.17% and the whole 13-word head (frame 0x158, stw r31/stw r0,
// lis+stw r4 @0x803017F0, both bl + their two mr r31 arg moves, lis, lwz
// 0x803017F4) is byte-exact under masking.
//
// BLOCKER (specific, not "it doesn't match"):
//   1. The body is 772 instructions of ten HAND-UNROLLED ~76-word blocks.  I
//      measured that ngccc does NOT unroll a `for (j = 0; j < 10; j++)` loop
//      at the project flags, so matching it requires recovering the original
//      unrolled text word for word - not expressible as a loop.
//   2. Even the head cannot be finished, because two of the remaining head
//      residues are functions of the body's register pressure, not of the
//      source's control flow:
//        - the loop counter must be r6; every reconstruction lands it on
//          r8/r10 at the same body sizes, and it moves only when the body is
//          the real one;
//        - the want builds the two 0x8029xxxx anchors and `addi r7 = &k`
//          AFTER the `bge`, while cc1's LICM parks them BEFORE it (a duplicate
//      anchor pair).  That is a scheduler/block choice, not a statement order
//      I could fix from C.
//   3. Because the body length must be exact before the latch and epilogue
//      (0x80092DA8..0x80092DD0, 11 words, all of which are plain
//      li/addi/lwz/cmplw/blt/stw/mtlr and would otherwise match) line up,
//      there is no partial-credit path into the tail.
//   4. cc1 ICEs (optabs.c:4116, -mps-float) on `t = tt.flt.lo;` for an
//      SN_PS_type fed by a __ps_t STRUCT FIELD read (`tt.ps = arg0->a;`) —
//      the same union idiom of recipes 7d-10/6ai-154 only survives when the
//      PS value comes from a local __ps_t, not a struct member.  Worked around
//      with the local PSU `uN.ps = mN;` form used above.
//
// Next step for a real attempt: the ten blocks differ only in which q[]
// pair they read, which v[] slot they store, and the m = a*b+c fma inputs, so
// the transcription is mechanical once block 1's semantics are trusted; block
// 1's `m0 = a0*a0 + a0` (ps_madd with all four registers = f13) is the one
// operation whose source form I could not explain and would need verifying
// against the game's vector math before scaling the other nine.