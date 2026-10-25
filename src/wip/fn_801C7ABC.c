// WIP DRAFT (non-matching) - hand-reconstructed from retail
// family=m2c range=0x801C7ABC-0x801C7FF0 size=1332B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED 2026-10-05 (ps-norm-triple + ngccc loop miscompile): best measured
// 13.33% (315 got words vs 333 want, 273/315 words differ).  Replaced the old
// m2c body, which scored 1.8% and had s32-typed floats / wrong 0xd8-vs-0x50
// frame / missing -mps-float, so NONE of the paired-single idioms compiled at
// all.  The new body is a faithful C transcription and reproduces:
//   * the exact 0xd8 frame, float/callee-saved register save set and 0x98/0x9C
//     int->float scratch,
//   * all four pair-multiply/merge/add/sum/reciprocal-sqrt normalise blocks
//     in the retail lane order, with the retail stack slots (vD1@0x08,
//     vPQ@0x18, vD2@0x28, vD3@0x38, s1@0x48, s2@0x50, s3@0x58, s4@0x60,
//     s5@0x68, s6@0x70),
//   * the 2^52 double int->float idiom (bias constant plus sign-bit handling
//     for signed, plain bias for unsigned),
//   * modulo-20 via multiply-high / shift / subtract / multiply,
//   * the retail stack-base pointer for the vD1 pair lanes.
// Residual: everything is one-to-two instructions out of register/schedule
// order from retail, so the byte compare collapses after the 7-word prologue
// (longest register-normalised common run = 7).  Two concrete blockers:
//  1) ngccc 3.9.3 MISCOMPILES the accumulator loop in this translation unit:
//     of the three float reductions only ONE add survives (plus it drops the
//     sign-bit count conversion and two of the three divisions), so ~18
//     wanted operations are simply never emitted. Reproduced with 8 different
//     the loop (pointer locals, break form, reversed body, literal 0.0f
//     initialisers, permuted declarations, split count temp) - all identical,
//     and the identical loop in isolation compiles correctly with all three
//     fadds, so it is a register-pressure bug in cc1's loop strength-reduce,
//     not a source-shape issue.  (A `volatile double _dummy;` was NOT needed:
//     -mps-float alone already gives the game's 0xd8 frame.)
//  2) fn_801C6F88 is a 3-arg f32 function, NOT variadic: retail passes the
//     already-loaded float argument (arg0+0x2A4, loaded for the compare) in
//     the branch and a saved copy in the other, with no status clear.
//     Getting that right fixed 2 words; everything else in the tail
//     still lands in a different order.
// Ruled out: near-twin / twin_scan (no matched sibling at 0x534B), the
// 16-aligned-frame issue (0xd8 is 8-mod-16 and -mps-float reproduces it),
// statement/store-order sweeps (not attempted - the residual is structural),
// and the -mps-float ICE at expmed.c:1115 (triggered by mixing a bare
// `__ps_t` local with the SN_PS_type unions; using SN_PS_type throughout
// compiles cleanly).
#include "types.h"
#include "dolphin/SN_PS.h"

extern const f32 lbl_802ACD98;
extern const f32 lbl_802ACD9C;
extern const f64 lbl_802ACDA0;
extern const f32 lbl_802ACDA8;
extern const f32 lbl_802ACDAC;
extern const f32 lbl_802ACDB0;
extern const f64 lbl_802ACDB8;
extern const __ps_t lbl_802ACD30;
extern s32 lbl_80305F9C;
extern s32 *lbl_80305EAC;
extern s32 lbl_8029F480;

typedef union {
    __ps_t ps[2];
    struct { s32 a, b, c, d; } i;
} Vec4;

typedef struct {
    char pad00[0x0C];
    s32 *unk0C;
    char pad10[0x18];
    s32 unk28;
    s32 unk2C;
    __ps_t ps30[4];
    char pad50[0x20];
    f32 arr70[20];
    f32 arrC0[20];
    f32 arr110[20];
    char pad160[0x140];
    s32 unk2A0;
    f32 unk2A4;
    s32 unk2A8;
    s32 unk2AC;
} T_7ABC;

s32 fn_8021B55C(s32, s32);
s32 fn_80219698(s32);
void *fn_8021D358(s32, u16);
s32 fn_8013F74C(void *);
void *fn_8013E034(void *, void *);
void *fn_8021D758(s32);
s32 fn_801AEB58(void *, s32);
s32 fn_801C6F88(T_7ABC *, s32, f32);
void fn_801C8DEC(T_7ABC *);

void fn_801C7ABC(T_7ABC *arg0) {
    Vec4 vD1;
    Vec4 vPQ;
    Vec4 vD2;
    Vec4 vD3;
    SN_PS_type s1;
    SN_PS_type s2;
    SN_PS_type s5;
    SN_PS_type s6;
    SN_PS_type s3;
    SN_PS_type s4;
    s32 k;
    s32 j;
    s32 sc;
    s32 cnt;
    f32 f9;
    f32 f10;
    f32 f8;
    f32 f29;
    f32 f31;
    __ps_t d;
    __ps_t q;
    __ps_t *pb;
    s32 g28;
    void *g25;
    void *ob;
    void *ob2;
    s32 *p;

    g28 = lbl_80305F9C;
    p = lbl_80305EAC;
    g25 = (void *)p[10];
    ob = fn_8021B55C(g28, 0);
    sc = (s32)(arg0->unk2A4 * lbl_802ACD98);
    if (fn_80219698(g28) != 0) {
        ob = *(void **)((char *)fn_8021D358(g28, *(u16 *)((char *)arg0->unk0C + 0x1A)) + 0x1C);
        cnt = 0;
        if (fn_8013F74C(ob) == 0) {
            cnt = *(s32 *)((char *)ob + 0x20B4);
        }
    } else {
        vPQ.i.b = 0;
        vPQ.i.c = (s32)&lbl_8029F480;
        ob = fn_8013E034(ob, &vPQ);
        cnt = 0;
        if (fn_8013F74C(ob) == 0) {
            cnt = *(s32 *)((char *)ob + 0x20B4);
        }
        vPQ.i.c = (s32)&lbl_8029F480;
    }
    if (sc == 0) {
        f29 = lbl_802ACD9C;
    } else {
        f29 = (f32)(f64)(u32)(cnt - sc) / (f32)(f64)(u32)sc;
        if (f29 < lbl_802ACD9C) {
            f29 = lbl_802ACD9C;
        }
    }
    f31 = lbl_802ACD9C;
    pb = vD1.ps;
    vD1.ps[0] = __builtin_ps_sub(arg0->ps30[0], arg0->ps30[2]);
    vD1.ps[1] = __builtin_ps_sub(arg0->ps30[1], arg0->ps30[3]);
    vD2.ps[0] = vD1.ps[0];
    vD2.ps[1] = pb[1];
    k = arg0->unk2A0 % 20;
    ob2 = fn_8021D758(g28);
    if (ob2 != 0) {
        p = *(s32 **)((char *)ob2 + 0x18);
        vPQ.ps[0] = *(__ps_t *)((char *)p + 0xB8);
        vPQ.ps[1] = *(__ps_t *)((char *)p + 0xC0);
        vD3.ps[0] = vD1.ps[0];
        vD3.ps[1] = pb[1];
        d = __builtin_ps_mul(vPQ.ps[1], vPQ.ps[1]);
        d = __builtin_ps_merge00(d, lbl_802ACD30);
        d = __builtin_ps_madd(vPQ.ps[0], vPQ.ps[0], d);
        d = __builtin_ps_sum0(d, d, d);
        s1.ps = d;
        if (s1.flt.hi > lbl_802ACD9C) {
            d = __builtin_ps_rsqrte(d);
            s1.ps = d;
            s1.flt.lo = lbl_802ACDA8;
            q = s1.ps;
            vPQ.ps[0] = __builtin_ps_muls0(vPQ.ps[0], d);
            vPQ.ps[1] = __builtin_ps_mul(vPQ.ps[1], q);
        }
        d = __builtin_ps_mul(vD3.ps[1], vD3.ps[1]);
        d = __builtin_ps_merge00(d, lbl_802ACD30);
        d = __builtin_ps_madd(vD3.ps[0], vD3.ps[0], d);
        d = __builtin_ps_sum0(d, d, d);
        s2.ps = d;
        if (s2.flt.hi > lbl_802ACD9C) {
            d = __builtin_ps_rsqrte(d);
            s2.ps = d;
            s2.flt.lo = lbl_802ACDA8;
            q = s2.ps;
            vD3.ps[0] = __builtin_ps_muls0(vD3.ps[0], d);
            vD3.ps[1] = __builtin_ps_mul(vD3.ps[1], q);
        }
        d = __builtin_ps_mul(vPQ.ps[1], vD3.ps[1]);
        d = __builtin_ps_merge00(d, lbl_802ACD30);
        d = __builtin_ps_madd(vPQ.ps[0], vD3.ps[0], d);
        d = __builtin_ps_sum0(d, d, d);
        s5.ps = d;
        f31 = (*(f32 *)&s5 + lbl_802ACDA8) * lbl_802ACDAC;
    }
    d = __builtin_ps_mul(pb[1], pb[1]);
    d = __builtin_ps_merge00(d, lbl_802ACD30);
    d = __builtin_ps_madd(vD1.ps[0], vD1.ps[0], d);
    d = __builtin_ps_sum0(d, d, d);
    s6.ps = __builtin_ps_res(d);
    arg0->arr70[k] = *(f32 *)&s6 / (f32)(f64)(u32)sc * lbl_802ACDB0;
    arg0->arrC0[k] = f29;
    arg0->arr110[k] = f31;
    f9 = lbl_802ACD9C;
    f10 = lbl_802ACD9C;
    f8 = lbl_802ACD9C;
    j = 0;
    arg0->unk2A0 = arg0->unk2A0 + 1;
    for (j = 0; j <= 19 && j < arg0->unk2A0; j++) {
        f9 += arg0->arr70[j];
        f10 += arg0->arrC0[j];
        f8 += arg0->arr110[j];
    }
    d = __builtin_ps_mul(pb[1], pb[1]);
    d = __builtin_ps_merge00(d, lbl_802ACD30);
    d = __builtin_ps_madd(vD1.ps[0], vD1.ps[0], d);
    d = __builtin_ps_sum0(d, d, d);
    s3.ps = d;
    if (s3.flt.hi > lbl_802ACD9C) {
        d = __builtin_ps_rsqrte(d);
        s3.ps = d;
        s3.flt.lo = lbl_802ACDA8;
        q = s3.ps;
        vD1.ps[0] = __builtin_ps_muls0(vD1.ps[0], d);
        vD1.ps[1] = __builtin_ps_mul(vD1.ps[1], q);
    }
    s4.flt.hi = f9;
    q = s4.ps;
    vD1.ps[1] = __builtin_ps_muls0(pb[1], q);
    vD1.ps[0] = __builtin_ps_muls0(vD1.ps[0], q);
    f31 = arg0->unk2A4 * f29;
    if (f31 > lbl_802ACDA8) {
        f31 = lbl_802ACDA8;
    }
    ob = fn_801AEB58(g25, *(s32 *)((char *)(arg0->unk28 * 0x88 + (arg0->unk2AC + 0x20)) + 0x80));
    while (ob != 0 && f31 > lbl_802ACD9C) {
        if (f31 > arg0->unk2A4) {
            ob = (void *)fn_801C6F88(arg0, (s32)ob, arg0->unk2A4);
        } else {
            ob = (void *)fn_801C6F88(arg0, (s32)ob, f31);
        }
        if (ob == 0) {
            *(__ps_t *)((char *)arg0->unk0C + 0x58) = arg0->ps30[0];
            *(__ps_t *)((char *)arg0->unk0C + 0x60) = arg0->ps30[1];
            fn_801C8DEC(arg0);
            return;
        }
        f31 = f31 - arg0->unk2A4;
    }
}