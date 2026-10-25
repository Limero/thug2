// REBUILD (2026-10-07, worker): from-scratch reconstruction of fn_8008B428
// family=m2c range=0x8008B428-0x8008B994 size=1388B
// INERT: not registered in splits.txt/configure.py - never compiled.
//
// WHAT THIS FIXES vs src/wip/fn_8008B428.c (2.9%): (19.31%)
//  * the whole "spray/particle" command block is now typed from the two
//    byte-identical-sibling drafts fn_8008D0A4.c / fn_8008A888.c: the same
//    QB_PARTICLE command struct (`Cmd`: u32 f; u8 a,b,c; pad[0x19]; void *p;
//    s16 d; u8 e,g; pad[4]; u8 h,i,j,k; s16 l; pad[4]; u8 m; -> 0x38 bytes)
//    built at r1+8 with `fn_800231C4(&cmd, &cmd.p, 1,1,0,0,0, cmd.p)`.
//    Retail's fields land exactly where that struct puts them:
//      r1+0x08 f, 0x0c a, 0x0d b, 0x0e c, 0x28 p(=arg0->unk0x17C), 0x2c d
//      (0x60/0x61), 0x2e e(=unk0x178), 0x2f g(=unk0x179), 0x34..0x37 h..k
//      (0x80,0x80,0x80,0xff), 0x38 l, 0x3e m.
//  * the `arg0` type is the SAME arg_t as fn_8008D0A4 (verified field by
//    field against the want): v28/v2C/v30 @0x28, v68/v6C/v70 @0x68, v84,
//    v94, vF4, p100(node,stride 0x30) @0x100, v110, cA/cB/cC @0x114/8/C,
//    pts @0x124, v134, v170, v178/v179, v17C.
//  * int->float goes through the game's own 2^52 pool constants:
//    lbl_80296B00 (lfd f7, 0x6b00) is the SIGNED magic (2^52+2^31, used with
//    the `xoris r0,r0,0x8000` path for `(f32)(s32)(colt-colf)`) and
//    lbl_80296B08 (lfd f6, 0x6b08) the UNSIGNED one for `(f32)(u8)byte`;
//    lbl_80296AF4 = 0.0f (also the v110 test) and lbl_80296B10 = 255.0f
//    (the RGB clamp high bound); lbl_80296AF8 = 1.0f.
//  * tail: `if (unk0x134 != 0)` stores p0->x/y/z into A and p1->x/y/z into B,
//    else adds unk0x28/0x2C/0x30 to both; A.w is written inside the branch,
//    B.w=one at the merge; then fn_8001F0F8(A)/fn_8001F1D4(out.w[0]) and
//    fn_8001F0F8(B)/fn_8001F1D4(out.w[1]); cursor/p0/p1 advance 0x30 / +3.
//  * fn_8001F2D8 is variadic (retail emits `crclr cr1eq` before its bl -
//    same as the siblings), and the 4 per-segment calls take 3 floats / 1 int.
//
// ===== (2026-10-07, worker) - FOUR FIXES PROVEN BY THE MEASURED DIFF
// `build/b34pkt/fn_8008B428.rb.diff.txt` (retail `W:` vs this body's real
// ngccc output `G:`).  Score before this pass: 19.31%, object 1380B vs want
// 1388B (2 words short, so the index-aligned diff was only readable up to the
// loop preheader):
//
//  1. `pts` STRIDE.  Retail's p1 offset is
//        slwi r0,r9,1 / add r0,r0,r9 / mullw r0,r0,r10 / slwi r0,r0,2
//     i.e. `(v170-1) * 3 * v84` **floats** (x4 at the end).  This body had
//     `V3 *pts` and emitted `mulli r9,r9,0xc` instead.  The field is
//     `f32 *pts` and p0/p1 advance by 3 floats (`addi r16,r29,0xc` /
//     `addi r15,r27,0xc` / `mr r29,r16` / `mr r27,r15` in retail).
//  2. THE v110 BRANCH POLARITY WAS INVERTED.  Retail:
//        fcmpu cr0,f12,f30 / cror cr0un,cr0eq,cr0gt / bns 0x8008b5d0
//     `bns` == cr0[SO]==0 == (v110 < 0) -> 0x8008b5d0 = {pa=cA(0x114),
//     pb=cC(0x11c)}; the FALLTHROUGH (v110 >= 0) is the 3-stop gradient
//     {fcmpu tt,v110 / bge -> tt=(tt-v110)/(one-v110), pa=cB, pb=cC ;
//      else tt=tt/v110, pa=cA, pb=cB}.  Body round 1 had `vv >= zero` as the
//     {cA,cC} case, which reverses the whole gradient.  Now written
//     `if (v110 >= 0) { 3-stop } else { cA,cC }` so cc1 lays the blocks out
//     exactly as retail (then = fallthrough, else after the goto).
//  3. CLAMP SHAPE.  Retail emits
//        fmr f13,f4(0.0f) / fcmpu dv,0.0f / blt L1 / fmr f13,dv /
//        fcmpu dv,255.0f / ble L1 / fmr f13,255.0f / L1: fctiwz f0,f13
//     which is `t = 0.0f; if (dv >= 0.0f) { t = dv; if (dv > 255.0f)
//     t = 255.0f; }` - NOT the nested ternary this body used (that emits the
//     255 test first, plus a redundant unconditional branch per lane).
//     Note the bounds are RELOADED from lbl_80296AF4 / lbl_80296B10 per lane
//     in retail (r21/r22 are the two label pages), so the clamp must name the
//     labels directly, not the hoisted `zero`.
//  4. &A / &B IN CALLEE-SAVED REGISTERS.  Retail materialises `addi r20,r1,0x48`
//     (&A) and `addi r18,r1,0x58` (&B) in the preheader and stores the .w
//     lanes as `stfs f31,0xc(r20)` / `stfs f31,0xc(r18)` - i.e. the source
//     reaches A.w/B.w through a pointer computed before the loop, while the
//     .x/.y/.z stores stay direct (`stfs f0,0x48(r1)`).  Added as
//     `pAw`/`pBw` (`f32 *`).  This is also the only visible consumer of two
//     more callee-saved GPRs - retail saves r14..r31 (ALL 18), which is
//     exactly why the outer counter `i` has a stack home at 0x78
//     (`stw r7,0x78(r1)` ... `lwz r7,0x78(r1)`) and why the frame is 0xf0.
//
// STILL UNCERTAIN (coordinator to iterate):
//  a) FRAME: retail is -0xf0 with `stfd f30,0xe0` / `stfd f31,0xe8` /
//     `stmw r14,0x98` / LR at 0xf4, its f64 conversion scratch at 0x90/0x94
// and the counter spill at 0x78. The first attempt was -0xe0 / `stmw r15,0x8c` /
//     scratch 0x80/0x84 and had no 0x78 slot, i.e. 12B of missing local slots
//     plus one missing callee-saved GPR (fix 4 is aimed at both).  Retail
//     0x7c..0x8f is untouched scratch, so if the frame overshoots/undershoots
//     by 8, the `volatile f32 padA[2]` after `cmd` is the knob that keeps A
//     at 0x48.
//  b) the inner colour-loop end test is SIGNED in retail (`cmpw r12,r19` /
//     `ble`, r19 = r1+0x6c) but unsigned here (`cmplw`); written as
//     `(s32)dst <= (s32)((u8 *)&out + 4)` to force `cmpw`.  Retail also keeps
//     &out in its own callee-saved register (r17) while `lwz r3,0x68(r1)` for
//     out.w[0] stays direct - that shape already falls out of this body.
//  c) the 8-instruction `mr rN,r9` cluster (retail r11,r7,r5,r3,r30,r8,r6,r4)
//     rides along for free from the staging-word address casts; it is not
//     hand-forced here.
//  d) REMOVED-AND-NOTED: lane order inside the 4-lane interpolation is
//     ascending here; retail's post-scheduler order is (0,1,2,3) for the
//     interpolations and (0,1,2) for the scale/clamp pass, with the reads
// software-pipelined one lane ahead. The first attempt's output already showed
//     that pipeline falling out of cc1, so it was not restructured.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_80296AF4; /* 0.0f          */
extern f32 lbl_80296AF8; /* 1.0f          */
extern f32 lbl_80296B10; /* 255.0f        */
extern f64 lbl_80296B00; /* 2^52 + 2^31   */
extern f64 lbl_80296B08; /* 2^52          */

void fn_800231C4(void *, void *, s32, s32, s32, s32, s32, void *);
void fn_8001E6F0(s32, s32, s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void fn_8001F2D8(s32, ...);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F1D4(s32);
void fn_8001F0F4(void);

/* QB_PARTICLE command block, same map as src/wip/fn_8008D0A4.c (spawn_t) */
typedef struct {
    u32 f;         /* 0x00 */
    u8 a, b, c;    /* 0x04,0x05,0x06 */
    u8 pad0[0x19]; /* 0x07..0x1f */
    void *p;       /* 0x20 (also fn_800231C4's 2nd arg) */
    s16 d;         /* 0x24 0x60 / 0x61 */
    u8 e;          /* 0x26 self->unk0x178 */
    u8 g;          /* 0x27 self->unk0x179 */
    u8 pad1[4];    /* 0x28..0x2b */
    u8 h, i, j, k; /* 0x2c..0x2f */
    s16 l;         /* 0x30 */
    u8 pad2[4];    /* 0x32..0x35 */
    u8 m;          /* 0x36 */
} Cmd;

typedef struct {
    u8 r, g, b, a;
} rgba_t;

typedef union {
    u32 w[2];
    rgba_t c[2];
} out_t;

typedef struct {
    f32 x, y, z;
} V3;

typedef struct {
    f32 x, y, z, w;
} Vec4;

/* the 0x30-byte per-segment cursor at self->unk0x100 */
typedef struct {
    u8 pad0[0x28];
    f32 f28;
    f32 f2C;
} Pin;

typedef struct {
    u8 pad0[0x28];     /* 0x00..0x27 */
    f32 v28, v2C, v30; /* 0x28,0x2c,0x30 */
    u8 pad1[0x34];     /* 0x34..0x67 */
    f32 v68, v6C, v70; /* 0x68,0x6c,0x70 */
    u8 pad2[0x10];     /* 0x74..0x83 */
    s32 v84;           /* 0x84 */
    u8 pad3[0xC];      /* 0x88..0x93 */
    s32 v94;           /* 0x94 */
    u8 pad4[0x5C];     /* 0x98..0xf3 */
    f32 vF4;           /* 0xf4 */
    u8 pad5[8];        /* 0xf8..0xff */
    Pin *p100;         /* 0x100 */
    u8 pad6[0xC];      /* 0x104..0x10f */
    f32 v110;          /* 0x110 */
    u32 *cA;           /* 0x114 */
    u32 *cB;           /* 0x118 */
    u32 *cC;           /* 0x11c */
    u8 pad7[4];        /* 0x120 */
    f32 *pts;          /* 0x124 - f32 elements, 3 per point (retail x4) */
    u8 pad8[0xC];      /* 0x128..0x133 */
    s32 v134;          /* 0x134 */
    u8 pad9[0x38];     /* 0x138..0x16f */
    s32 v170;          /* 0x170 */
    u8 pad10[4];       /* 0x174..0x177 */
    u8 v178, v179;     /* 0x178,0x179 */
    u8 pad11[2];
    void *v17C;        /* 0x17c */
} Self;

void fn_8008B428(Self *arg0) {
    Cmd cmd;
    volatile f32 padA[2]; /* keeps A/out at retail's 0x48 (see note (a)) */
    Vec4 A;
    Vec4 B;
    out_t out;
    s32 colf;
    s32 colt;
    Pin *pin;
    f32 *p0;
    f32 *p1;
    f32 *pAw; /* &A, held in a callee-saved GPR (retail r20) */
    f32 *pBw; /* &B, held in a callee-saved GPR (retail r18) */
    u32 *pa;
    u32 *pb;
    s32 i;
    f32 tt;
    f32 vv;
    f32 sr;
    f32 sg;
    f32 sb;
    f32 one;
    f32 zero;
    f32 dv;
    f32 t;
    volatile double _dummy;  /* +16: measured prologue was 0xe0, retail 0xf0 */
    volatile double _dummy2;

    cmd.f = QB_PARTICLE;
    cmd.a = 1;
    cmd.b = 1;
    cmd.c = 2;
    cmd.p = arg0->v17C;
    cmd.d = (cmd.p != 0) ? 0x61 : 0x60;
    cmd.e = arg0->v178;
    cmd.g = arg0->v179;
    cmd.h = 0x80;
    cmd.i = 0x80;
    cmd.j = 0x80;
    cmd.k = 0xFF;
    cmd.l = 0;
    cmd.m = 0;
    fn_800231C4(&cmd, &cmd.p, 1, 1, 0, 0, 0, cmd.p);

    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    fn_8001F2D8(arg0, 2, 9, 1, 0xB, 1);

    if (arg0->v94 > 0) {
        fn_8001F0A0(0xA8, 0, (arg0->v94 * 2) & 0xFFFE);
    }

    pin = arg0->p100;
    p0 = arg0->pts;
    /* EDIT 1 (targets W:0x8008B548 `addi r9,r9,-1` + W:0x8008B550
       `slwi r0,r9,1` + W:0x8008B558 `add r0,r0,r9` + W:0x8008B560
       `mullw r0,r0,r10`): retail strength-reduces `*3` on the (v170-1)
       factor and multiplies by v84 last.  The old spelling
       `(v170-1) * 3 * v84` measured the opposite (`slwi r0,r11,1 /
       add r0,r0,r11` on v84, then `mullw` by v170-1), so the constant is
       placed on the LEFT: 3 * (v170-1) * v84 = (3*(v170-1)) * v84. */
    p1 = &arg0->pts[3 * (arg0->v170 - 1) * arg0->v84];
    pAw = (f32 *)&A;
    pBw = (f32 *)&B;

    /* hoisted into the two callee-saved FPRs (f30/f31) LAST in the
       preheader, as retail does (`lis`/`lfs f30,0x6af4` / `lfs f31,0x6af8`
       come after the p1 pointer math and the loop test).  The clamp bounds
       below still reference the labels directly, because retail reloads
       `lfs f4,0x6af4` / `lfs f5,0x6b10` inside the colour loop. */
    zero = lbl_80296AF4;
    one = lbl_80296AF8;

    i = 0;
    while (i < arg0->v94) {
        tt = pin->f28 / pin->f2C;
        vv = arg0->v110;
        if (vv >= zero) {
            /* 3-stop gradient centred on v110: then = fallthrough, as retail */
            if (tt < vv) {
                tt = tt / vv;
                pa = arg0->cA;
                pb = arg0->cB;
            } else {
                tt = (tt - vv) / (one - vv);
                pa = arg0->cB;
                pb = arg0->cC;
            }
        } else {
            pa = arg0->cA;
            pb = arg0->cC;
        }
        i++;

        sr = arg0->vF4 * arg0->v68;
        sg = arg0->vF4 * arg0->v6C;
        sb = arg0->vF4 * arg0->v70;

        {
            u8 *dst;
            dst = (u8 *)&out;
            do {
                u8 *sa;
                u8 *sk;

                colf = *pa++;
                colt = *pb++;
                sa = (u8 *)&colf;
                sk = (u8 *)&colt;

                dst[0] = (u8)(sa[0] + (s32)((f32)(sk[0] - sa[0]) * tt));
                dst[1] = (u8)(sa[1] + (s32)((f32)(sk[1] - sa[1]) * tt));
                dst[2] = (u8)(sa[2] + (s32)((f32)(sk[2] - sa[2]) * tt));
                dst[3] = (u8)(sa[3] + (s32)((f32)(sk[3] - sa[3]) * tt));

                dv = sr * (f32)dst[0];
                t = lbl_80296AF4;
                if (dv >= lbl_80296AF4) {
                    t = dv;
                    if (dv > lbl_80296B10) {
                        t = lbl_80296B10;
                    }
                }
                dst[0] = (u8)t;

                dv = sg * (f32)dst[1];
                t = lbl_80296AF4;
                if (dv >= lbl_80296AF4) {
                    t = dv;
                    if (dv > lbl_80296B10) {
                        t = lbl_80296B10;
                    }
                }
                dst[1] = (u8)t;

                dv = sb * (f32)dst[2];
                t = lbl_80296AF4;
                if (dv >= lbl_80296AF4) {
                    t = dv;
                    if (dv > lbl_80296B10) {
                        t = lbl_80296B10;
                    }
                }
                dst[2] = (u8)t;

                dst += 4;
            } while ((s32)dst <= (s32)((u8 *)&out + 4));
        }

        if (arg0->v134 != 0) {
            A.x = p0[0];
            A.y = p0[1];
            A.z = p0[2];
            pAw[3] = one;
            B.x = p1[0];
            B.y = p1[1];
            B.z = p1[2];
        } else {
            A.x = p0[0] + arg0->v28;
            A.y = p0[1] + arg0->v2C;
            A.z = p0[2] + arg0->v30;
            pAw[3] = one;
            B.x = p1[0] + arg0->v28;
            B.y = p1[1] + arg0->v2C;
            B.z = p1[2] + arg0->v30;
        }
        pBw[3] = one;

        fn_8001F0F8(A.x, A.y, A.z);
        fn_8001F1D4(out.w[0]);
        fn_8001F0F8(B.x, B.y, B.z);
        fn_8001F1D4(out.w[1]);

        pin++;
        p0 += 3;
        p1 += 3;
    }

    if (arg0->v94 > 0) {
        fn_8001F0F4();
    }
}

// ---------------------------------------------------------------------------
// SUPERSEDED BODY (m2c husk) — earlier findings preserved verbatim below.
// The body above replaced it (worker rebuild + measured-diff repair loop,
// 2); keep these notes, they are still the local lore.
// ---------------------------------------------------------------------------
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// PARKED 2026-10-07: first divergence is the frame (want 0xf0 saving only
//   f30/f31 vs this body's 0x1b8 saving f26-f31).  Root cause: the loop's byte
//   interpolation is spelled as (f32)(f64) conversions of s32 locals, each needing
//   a spill slot; retail uses the 0x4330 uint->double magic at r1+0x90.  Also
//   fn_8001F0F8 is called with 10 args here where retail passes 3 floats.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.9% ([18]rev->1.2% [12]rev->2.9%).
