// WIP DRAFT (non-matching) — m2c decomposition with types + calls repaired.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 1.3201% -> 2.1429% `volatile` keyword(s) removed from the body
// family=m2c range=0x800C1E60-0x800C2284 size=1060B
// PARKED 2026-10-06: re-audited S1E60 against the
// WANT and fixed a real layout bug.  The struct had a stray
// `char pad_0D0[0x68]` BEFORE the a_0Dx/a_0Ex/a_0Fx triples and was missing
// the pads after them, so a_0D0 actually landed at 0x138 and every later
// member (a_*, i_120, m_138.., q_158, p_170, t_1340) compiled 0x68 low:
// `lfs ...,0xd0(r31)` came out 0x138(r31), `p_170` as 0x15c, `t_1340` as
// 0x132c.  All members now sit at their retail-name offsets (pads added at
// 0xdc/0xec/0xfc/0x15c, i_120 pinned to 0x120), verified displacement-by-
// displacement against the WANT.  Body otherwise unchanged: the dominant
// residual is still the frame (0x2d0 vs 0x160) from the 39 named mode(PS)
// temps (RESIDUAL below), and the 63 op-4 words are undecodable by capstone
// (needs tools/ps_disasm.py) — an unmeasurable full redraft here.
// extra_cflags: -mps-float
//
// VERDICT 2026-09-27: DIFF.  masked 1.3%, got 1212B vs retail 1060B.
// No .rodata in the object (no doc-14 pool-constant blocker) and exactly the
// 7 REL24 bls + 3 REL14 branches retail has, so the call graph and control
// flow are right; the residual is the paired-single dataflow (see RESIDUAL).
//
// KEY INSIGHT (this is what turned the 0.53% husk into real code): the shared
// class Unk_D7FF95D8 in include/structs.h types EVERY field of
// this object as s32, so each f32 load compiled to an xoris/0x4330 int->double
// dance and the entire f32 body was DCE'd — the object came out 756B with a
// 0x60 frame and 13 callee-saved regs. Every offset this function touches is
// f32 except 0x120 (read with lwz). Fixed with a FILE-LOCAL typedef carrying
// the true layout. m2c's own decomposition was otherwise right; these were
// also wrong and are fixed:
//  * fn_800C65C4 is 2-arg (this, &mat0) — m2c invented a 10-arg call.
//  * m2c wrote arg0+0xE4 where retail has arg0+0xE0 in the sp28 term.
//  * fn_80036304 is `f32 f(void *, f32, f32)` and its f1 result FEEDS
//    sqrtf(f32); m2c dropped both return values.
//  * the fcmpu compares sqrtf's result against lbl_80299040, and the
//    fmsubs uses the OLD sp64 (= arg0+0x4C, the hi lane of the pair stored at
//    sp60) — m2c used the NEW sp64.
//  * fn_800C2284 / 1538 / 2320 / 6860 all take exactly this.
//  * the stack frame is a frame-template struct so retail's hole-punched
//    0x08..0x130 region (0xCC, 0xBC, 0xA4, 0x74, 0x6C, 0xD0..0xDC, ... never
//    written) keeps its exact slots; total template size 0x134 => frame 0x160.
//
// RESIDUAL — precise, not "regalloc":
//  1. FRAME 0x2D0 vs 0x160. 39 named `mode(PS)` temporaries (a0..a7, b0..b9,
//     c0..c9, d0..d9, e0..e2) each reserve an 8-byte frame slot here, so
//     0x134 (template) + 0x138 (pair temps) = 0x2C8 rounded to 0x2D0. Retail
//     recycles ~200 live PS values through 32 FPRs and spills NONE. The only
//     way to remove the slots is to un-name the intermediates so the
//     allocator can coalesce them, which is exactly the FPR-colouring problem
//     this class of function always is; §6as-10 / §6aq-219 note the opposite
//     direction (scalar f32[2] members) does not help either because the
//     builtins need a real mode(PS) type. Every one of the ~200 psq_l/psq_st
//     reloads of an already-loaded stack slot is also deliberately
//     CSE-defeated here with `volatile P2` views, which retail gets for free
//     from register recycling.
//
// SHARPENED 2026-10-05 — the frame blocker is now ARITHMETICALLY
// PINNED DOWN, which is the single most useful thing to know before anyone
// retries this.  Retail allocates a 0x160 frame with the f30/f31 saves at
// 0x150/0x158, the r31 save at 0x14c and the LR slot at 0x164,
// so retail's LOCAL AREA is 0x08..0x14B = 0x144 = 324 bytes ≈ 40 8-byte
// pair slots, i.e. essentially the FR1E60 template (0x134 -> 0x138 aligned)
// and NOTHING else.  This draft's local area is 0x2A8 = 688 bytes.  The
// delta 0x164 ≈ 0x138 = 312 bytes is 39 x 8 — exactly the 39 named
// mode(PS) temps (a0..a7 8, b0..b9 10, c0..c9 10, d0..d7+d9 8, e0..e2 3).
// So the temps are NOT just taking slots: ngccc's PS register allocator
// SPILLS them (verified by probe: 1 and 3 named PS temps in a small function
// cost nothing, but a 39-temp straight-line region cannot fit 32 FPRs and
// every survivor becomes an 8-byte frame slot).  §6aw-229's "plain __ps_t
// locals do NOT inflate frames" therefore only holds while the LIVE count
// fits in FPRs, and the fix is the one already named in (1): never name a
// PS intermediate — address it through the template's `volatile P2` view
// (`PL(sXX)`) at every use, exactly as retail re-loads its slots.  That is
// a mechanical but ~200-site rewrite, and it must be done BEFORE the
// operand-order dispute in (2) can even be measured, because with a 0x170
// displacement offset every masked compare is noise.
//  2. PS OPERAND ORDER for ps_mul / ps_madd / ps_sum0 is the documented
//     dispute (§6ax-227 vs AGENTS.md §6ae-63). tools/ps_diff.py prints
//     ps_mul as (D,A,C,B) but the builtin is 2-arg, so the third printed
//     operand is dropped and this body uses (A,C); ps_madd(a,b,c) is taken as
//     a*b+c per §6ax-227. A wrong choice here changes only the garbage hi
//     lanes (every one of these feeds muls0 or a merge), so it does not
//     affect the lo-lane semantics, but it does change the emitted words.
//  3. Because of (1) every stack displacement in the compiled body is offset
//     by +0x170 from retail's, so the position-based masked compare cannot
//     score above noise; 1.3% is NOT a semantic score.
//
// INERT: not registered in splits.txt/configure.py — never compiled by the
// real build, not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

/* paired-single type, same declaration SN_PS.h uses (include/structs.h
   only aliases __ps_t to double for non-PS builds, so declare it locally). */
typedef float P2 __attribute__((mode(PS)));

/* File-local layout: pair members are the offsets retail touches with
   psq_l/psq_st, scalar members the ones it reads with lfs/lwz. */
typedef struct {
    char pad_000[0x30];
    f32 m_030[2];
    f32 m_038[2];
    f32 m_040[2];
    f32 m_048[2];
    f32 m_050[2];
    f32 m_058[2];
    char pad_060[0x50];
    f32 m_0B0[2];
    f32 m_0B8[2];
    f32 m_0C0[2];
    f32 m_0C8[2];
    f32 a_0D0, a_0D4, a_0D8;                   /* 0xd0, 0xd4, 0xd8 */
    char pad_0DC[0x4];                         /* 0xdc..0xdf */
    f32 a_0E0, a_0E4, a_0E8;                   /* 0xe0, 0xe4, 0xe8 */
    char pad_0EC[0x4];                         /* 0xec..0xef */
    f32 a_0F0, a_0F4, a_0F8;                   /* 0xf0, 0xf4, 0xf8 */
    char pad_0FC[0x24];                        /* 0xfc..0x11f */
    s32 i_120;                                 /* 0x120 (lwz) */
    char pad_124[0x14];                        /* 0x124..0x137 */
    f32 m_138[2];                              /* 0x138 lo, 0x13c */
    f32 m_140[2];                              /* 0x140 lo, 0x144 */
    f32 m_148[2];                              /* 0x148 lo, 0x14C */
    f32 m_150[2];                              /* 0x150 lo, 0x154 */
    f32 q_158;                                 /* 0x158 */
    char pad_15C[0x14];                        /* 0x15c..0x16f */
    f32 p_170;                                 /* 0x170 */
    char pad_174[0x11CC];                      /* 0x174..0x133f */
    f32 t_1340;                                /* 0x1340 */
} S1E60;

/* Frame template: retail's local region is 0x08..0x130 with many mid-slots
   never written (0xCC, 0xBC, 0xA4, 0x8C only as a pair hi-lane, 0x74, 0x6C,
   0x64 read-before-write, ...). One struct keeps the slots in retail order. */
typedef struct {
    char _p00[8];
    f32 s08, s0C, s10, s14, s18, s1C, s20, s24;
    f32 s28, s2C, s30, s34;                        /* mat0, &mat0 == arg4 */
    f32 s38, s3C, s40, s44, s48, s4C;
    f32 s50, s54, s58, s5C, s60, s64;
    f32 s68, s6C, s70, s74, s78, s7C, s80, s84;
    f32 s88, s8C, s90, s94, s98, s9C;
    f32 sA0, sA4, sA8, sAC;
    f32 sB0, sB4, sB8, sBC;
    f32 sC0, sC4, sC8, sCC;
    f32 sD0, sD4, sD8, sDC;
    f32 sE0, sE4, sE8, sEC;
    f32 sF0, sF4, sF8, sFC;
    f32 s100, s104, s108, s10C;
    f32 s110, s114, s118, s11C;
    f32 s120, s124, s128, s12C, s130;
} FR1E60;

extern f32 lbl_80299038;
extern f32 lbl_8029903C;
extern f32 lbl_80299040;
extern f32 lbl_80299044;
extern f32 lbl_80298F18[2];

extern void fn_800C65C4(S1E60 *, void *);
extern f32 fn_80036304(void *, f32, f32);
extern f32 sqrtf(f32);
extern void fn_800C2284(S1E60 *);
extern void fn_800C6860(S1E60 *);
extern void fn_800C1538(S1E60 *);
extern void fn_800C2320(S1E60 *);

/* pair views: retail re-loads the same stack slot many times; plain C
   would CSE each psq_l into a single load. */
#define PL(o) (*(P2 *)&fr.o)
#define PM(o) (*(P2 *)&arg0->o)

void fn_800C1E60(S1E60 *arg0) {
    FR1E60 fr;
    P2 a0, a1, a2, a3, a4, a5, a6, a7;
    P2 b0, b1, b2, b3, b4, b5, b6, b7, b8, b9;
    P2 c0, c1, c2, c3, c4, c5, c6, c7, c8, c9;
    P2 d0, d1, d2, d3, d4, d5, d6, d9;
    P2 e0, e1, e2;
    f32 c038, c03c, c040, c044;
    f32 q14c, q148, q150, q154, q158, p170;
    f32 s5, s6, s7, s8, s9, s10, s11;
    f32 r6, r7, r8, r11, r13, r8b;
    f32 old64, mag, z, w;

    /* ==================== 0x1E60..0x1FC0 ==============================
       build mat0 at sp28 / sp30..34 from this->q148..q158 * this->a0D0..a0F8
       and blend this->m030 / m038; then fn_800C65C4(this, &mat0).        */
    q14c = arg0->m_148[1];                          /* f0  */
    p170 = arg0->p_170;                          /* f10 */
    s5 = q14c * arg0->a_0E0;                     /* f12 */
    s6 = q14c * arg0->a_0E4;                     /* f11 */
    q148 = arg0->m_148[0];                          /* f8  */
    q158 = arg0->q_158;                          /* f4  */
    s9 = q14c * arg0->a_0E8;                     /* f0  */
    fr.sD8 = p170;                               /* stfs 0xd8 */
    a0 = PL(sD8);                                /* f10 = {0xd8,0xdc} */
    s7 = arg0->a_0D0;                            /* f7  */
    fr.sE0 = q158;                               /* stfs 0xe0 */
    a1 = PL(sE0);                                /* f12 = {0xe0,0xe4} */
    r7 = q148 * s7 + s5;                         /* fmadds f7,f8,f7,f12 */
    q150 = arg0->m_150[0];                          /* f13 */
    s8 = arg0->a_0D4;                            /* f6  */
    r6 = q148 * s8 + s6;                         /* fmadds f6,f8,f6,f11 */
    r8 = q148 * p170 + s9;                       /* fmadds f8,f8,f10,f0 */
    s9 = arg0->a_0F4;                            /* f3  */
    fr.sF0 = q158;                               /* stfs 0xf0 */
    s10 = arg0->a_0F8;                           /* f0  */
    r11 = q150 * arg0->a_0F0 + r7;               /* fmadds -> sp28 */
    q154 = arg0->m_150[1];                          /* f7  */
    r8b = q150 * s10 + r8;                       /* fmadds -> sp30 */
    r13 = q150 * s9 + r6;                        /* fmadds -> sp2c */
    fr.s28 = r11;                                /* mat[0] */
    fr.s34 = q154;                               /* mat[3] */
    fr.s2C = r13;                                /* mat[1] */
    fr.s30 = r8b;                                /* mat[2] */

    a2 = __builtin_ps_muls0(PM(m_140), a0);      /* f2 */
    a3 = __builtin_ps_muls0(PM(m_140), a1);      /* f9 */
    a4 = __builtin_ps_muls0(PM(m_138), a1);      /* f10 */
    a5 = __builtin_ps_muls0(PM(m_138), a0);      /* f12 */
    c038 = lbl_80299038;                         /* f31 */
    fr.sE8 = q158 * c038;                        /* fmuls f4,f4,f31 */
    fr.s10 = a2;                                 /* psq_st f2  @0x10 */
    fr.s08 = a5;                                 /* psq_st f12 @0x08 */
    PM(m_030) = __builtin_ps_add(PM(m_030), a4); /* ps_add -> psq_st @0x30 */
    PM(m_038) = __builtin_ps_add(PM(m_038), a3); /* ps_add -> psq_st @0x38 */
    a6 = PL(sE8);                                /* f8 = {0xe8,0xec} */
    fr.s18 = PL(s28);                            /* psq_st f13 @0x18 */
    fr.s20 = PL(s30);                            /* psq_st f0  @0x20 */
    a2 = __builtin_ps_muls0(a2, a6);             /* f11 */
    fr.s40 = a4;                                 /* psq_st f10 @0x40 */
    fr.s48 = a3;                                 /* psq_st f9  @0x48 */
    a5 = __builtin_ps_muls0(a5, a6);             /* f12 */
    fr.s48 = a5;                                 /* psq_st f12 @0x48 (2nd) */
    a0 = PL(sF0);                                /* f10 = {0xf0,0xf4} */
    a3 = __builtin_ps_add(PM(m_0B0), a5);        /* ps_add f13 */
    a4 = __builtin_ps_add(PM(m_0B8), a2);        /* ps_add f0  */
    fr.s50 = a2;                                 /* psq_st f11 @0x50 */
    PM(m_038) = a3;                              /* psq_st f13 @0x38 */
    fr.s40 = a4;                                 /* psq_st f0  @0x40 (2nd) */
    a5 = __builtin_ps_muls0(a4, a0);             /* ps_muls0 f12 */
    a3 = __builtin_ps_muls0(a3, a0);             /* ps_muls0 f13 */
    fr.s30 = a5;                                 /* psq_st f12 @0x30 */
    fr.s28 = a3;                                 /* psq_st f13 @0x28 */
    fn_800C65C4(arg0, &fr.s28);

    /* ==================== 0x1FC4..0x21B4 ==============================
       second matrix pass; blends this->m040 / m048 (2x2 at +0x40).      */
    q158 = arg0->q_158;                          /* f9  */
    fr.sF8 = q158 * c038;                        /* fmuls f31,f9,f31 */
    a0 = PL(s18);                                /* f0  = {0x18,0x1c} */
    fr.s60 = PM(m_048);                          /* psq_st f10 @0x60 */
    c03c = lbl_8029903C;                         /* f10 */
    fr.s100 = q158 * c03c;                       /* stfs 0x100 */
    a1 = PL(sF8);                                /* f12 = {0xf8,0xfc} */
    a2 = __builtin_ps_muls0(a0, a1);             /* f0  */
    a3 = __builtin_ps_add(PM(m_0C0), a2);        /* ps_add f13 */
    fr.s48 = a2;                                 /* psq_st f0  @0x48 */
    a4 = __builtin_ps_muls0(PL(s20), a1);        /* f12 = muls0({sp20},f12) */
    PM(m_038) = a3;                              /* psq_st f13 @0x38 */
    a0 = PL(s100);                               /* f0  = {0x100,0x104} */
    c040 = lbl_80299040;                         /* f31 */
    a5 = __builtin_ps_add(PM(m_0C8), a4);        /* ps_add f7 */
    old64 = fr.s64;                              /* lfs f2,0x64(r1) */
    a3 = __builtin_ps_muls0(a3, a0);             /* ps_muls0 f13 */
    fr.s50 = a4;                                 /* psq_st f12 @0x50 */
    fr.s54 = c040;                               /* stfs 0x54 */
    a2 = __builtin_ps_muls0(a5, a0);             /* ps_muls0 f0 */
    fr.s28 = a3;                                 /* psq_st f13 @0x28 */
    fr.s30 = a2;                                 /* psq_st f0  @0x30 */
    fr.s108 = old64;                             /* stfs 0x108 */
    mag = c040;                                  /* fmr f1,f31 */
    a6 = PM(m_040);                              /* f11 = obj 0x40 */
    fr.s58 = a6;                                 /* psq_st f11 @0x58 */
    fr.s48 = fr.s28;                             /* stfs 0x48 = sp28 */
    fr.s4C = fr.s2C;                             /* stfs 0x4c = sp2c */
    a7 = PM(m_040);                              /* f13 = obj 0x40 reload */
    fr.s68 = a7;                                 /* psq_st f13 @0x68 */
    a3 = PL(s108);                               /* f10 = {0x108,0x10c} */
    a2 = PM(m_048);                              /* f0  = obj 0x48 */
    fr.s70 = a2;                                 /* psq_st f0  @0x70 */
    fr.s110 = mag;                               /* stfs 0x110 */
    fr.s50 = fr.s30;                             /* stfs 0x50 = sp30 */
    b0 = PL(s110);                               /* f11 = {0x110,0x114} */
    b1 = PL(s48);                                /* f10 = {0x48,0x4c}  */
    b2 = __builtin_ps_muls0(b1, b1);             /* f8  = muls0(f10,f9) */
    fr.s78 = b1;                                 /* psq_st f10 @0x78 */
    fr.s80 = b0;                                 /* psq_st f11 @0x80 */
    fr.s40 = b0;                                 /* psq_st f7  @0x40 */
    b3 = __builtin_ps_merge10(b1, b0);           /* f12 = merge10(f10,f11) */
    fr.sA8 = b2;                                 /* psq_st f8  @0xa8 */
    b4 = __builtin_ps_merge00(b1, b0);           /* f4  = merge00(f10,f11) */
    b5 = PM(m_040);                              /* f7  = obj 0x40 (reload) */
    b6 = __builtin_ps_muls0(b0, b1);             /* f9  = muls0(f11,f9) */
    b7 = PM(m_048);                              /* f6  = obj 0x48 (reload) */
    b8 = __builtin_ps_mul(b5, b3);               /* f12 = ps_mul(f7,f12,..) */
    c3 = *(P2 *)&lbl_80298F18;          /* f3  = psq_l 0(r9) */
    c044 = lbl_80299044;                         /* f30 */
    b9 = __builtin_ps_merge10(b5, b7);           /* f0  = merge10(f7,f6) */
    c0 = __builtin_ps_mul(b9, b1);               /* f0  = ps_mul(f0,f10,..) */
    c1 = __builtin_ps_sub(b8, c0);               /* f12 = ps_sub(f12,f0) */
    c2 = __builtin_ps_merge00(b7, b5);           /* f13 = merge00(f6,f7) */
    c0 = __builtin_ps_merge00(c1, c1);           /* f0  = merge00(f12,f12) */
    fr.s118 = c0;                                /* psq_st f0  @0x118 */
    c4 = __builtin_ps_mul(c2, b4);               /* f13 = ps_mul(f13,f4,..) */
    c5 = __builtin_ps_muls0(b7, b0);             /* f4  = muls0(f6,f5) */
    fr.sC0 = c5;                                 /* psq_st f4  @0xc0 */
    fr.s11C = c044;                              /* stfs 0x11c */
    c6 = __builtin_ps_muls0(b5, b0);             /* f5  = muls0(f7,f5) */
    c7 = __builtin_ps_mul(b7, b0);               /* f11 = ps_mul(f6,f11,..) */
    fr.sB8 = c6;                                 /* psq_st f5  @0xb8 */
    c8 = __builtin_ps_merge10(c4, c4);           /* f0  = merge10(f13,f13) */
    c9 = __builtin_ps_sub(c4, c8);               /* f13 = ps_sub(f13,f0) */
    d0 = __builtin_ps_add(b2, c6);               /* f8  = ps_add(f8,f5) */
    d1 = __builtin_ps_merge10(c1, c9);           /* f12 = merge10(f12,f13) */
    fr.s98 = d0;                                 /* psq_st f8  @0x98 */
    d2 = __builtin_ps_merge00(c7, c3);            /* f11 = merge00(f11,f3) */
    d3 = PL(s118);                               /* f13 = {0x118,0x11c} */
    d4 = __builtin_ps_add(d0, d1);               /* f8  = ps_add(f8,f12) */
    fr.sC8 = d1;                                 /* psq_st f12 @0xc8 */
    d5 = __builtin_ps_madd(b5, b1, d2);          /* f10 = ps_madd(f7,f10,f11) */
    fr.s88 = d4;                                 /* psq_st f8  @0x88 */
    d6 = __builtin_ps_add(b6, c5);               /* f9  = ps_add(f9,f4) */
    s5 = fr.s8C;                                 /* lfs f12,0x8c(r1) */
    fr.sA0 = d6;                                 /* psq_st f9  @0xa0 */
    d5 = __builtin_ps_sum0(d5, d5, d5);          /* f10 = ps_sum0 */
    s6 = fr.s88;                                 /* lfs f11,0x88(r1) */
    d6 = __builtin_ps_add(d6, d3);               /* f9  = ps_add(f9,f0) */
    fr.s120 = d5;                                /* psq_st f10 @0x120 */
    fr.s90 = d6;                                 /* psq_st f9  @0x90 */
    s7 = fr.s120;                                /* lfs f10,0x120(r1) */
    fr.s5C = s5;                                 /* stfs 0x5c = sp8c */
    fr.sD0 = d3;                                 /* psq_st f0  @0xd0 */
    s8 = fr.s90;                                 /* lfs f13,0x90(r1) */
    w = s7;                                      /* fmr f0,f10 */
    fr.s58 = s6;                                 /* stfs 0x58 = sp88 */
    s9 = old64 * mag - w;                        /* fmsubs f2,f2,f1,f0 */
    d9 = PL(s58);                                /* f11 = {0x58,0x5c} */
    fr.s60 = s8;                                 /* stfs 0x60 = sp90 */
    fr.s64 = s9;                                 /* stfs 0x64 */
    fr.s38 = d9;                                 /* psq_st f11 @0x38 */
    e0 = __builtin_ps_add(b5, d9);               /* f7  = ps_add(f7,f0) */
    e1 = PL(s60);                                /* f13 = {0x60,0x64} */
    fr.s40 = e1;                                 /* psq_st f13 @0x40 */
    e2 = __builtin_ps_add(b7, e1);               /* f6  = ps_add(f6,f13) */
    PM(m_040) = e0;                              /* psq_st f7  @0x40 */
    PM(m_048) = e2;                              /* psq_st f6  @0x48 */

    /* ============ 0x21B8..0x2234: length, fmod, final blend ============= */
    mag = fn_80036304(&arg0->m_040[0], c040, old64);
    mag = sqrtf(mag);
    if (mag > c040) {
        fr.s128 = c044 / mag;                    /* fdivs f30,f30,f1 */
        a0 = PL(s128);                           /* f10 = {0x128,0x12c} */
        PM(m_040) = __builtin_ps_muls0(PM(m_040), a0);
        PM(m_048) = __builtin_ps_muls0(PM(m_048), a0);
    }
    fr.s130 = arg0->q_158;                       /* stfs 0x130 */
    a0 = PL(s130);                               /* f12 = {0x130,0x134} */
    a2 = PM(m_148);                              /* f0  = obj 0x148 */
    a3 = PM(m_150);                              /* f11 = obj 0x150 */
    fr.s48 = __builtin_ps_muls0(a2, a0);         /* psq_st f0  @0x48 */
    fr.s50 = __builtin_ps_muls0(a3, a0);         /* psq_st f11 @0x50 */
    a2 = __builtin_ps_add(PM(m_050), PL(s48));   /* ps_add f13 */
    a3 = __builtin_ps_add(PM(m_058), PL(s50));   /* ps_add f12 */
    PM(m_050) = a2;                              /* psq_st f13 @0x50 */
    PM(m_058) = a3;                              /* psq_st f12 @0x58 */
    fn_800C2284(arg0);

    if (arg0->i_120 == 0 && arg0->t_1340 == c040) {
        fn_800C6860(arg0);
    }
    fn_800C1538(arg0);
    fn_800C2320(arg0);
}

// NOTE (2026-10-06): this slice's only provable, non-speculative
// edit was the S1E60 layout correction above (all r31 displacements now match
// the WANT's 0xd0..0x1340 offsets).  The function is not matchable from C in
// this toolchain: 88 of 265 words are paired-single (63 op-4 words carry no
// operand info in tmp_bundles and capstone stalls on them) and the 39 named
// mode(PS) temporaries make ngccc spill, giving a 0x2d0 frame against retail's
// 0x160 (every stack displacement +0x170).  A retry needs tools/ps_disasm.py
// to recover the op-4 operands, then a nameless-PS-temp rewrite (`PL(sXX)`
// views) to let the allocator coalesce ~200 live pairs through 32 FPRs.
