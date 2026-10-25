// WIP DRAFT (non-matching) — hand-rebuilt from disasm (PS rotation-matrix fn)
// family=m2c range=0x801C7FF0-0x801C84E8 size=1272B
// PARKED 2026-09-21: paired-single rotation-matrix fn, best 61.9% with
// -mps-float (its recorded per-object flag).  Flag sweep with -mps-float held
// on: -fno-gcse 61.9% (tie), -fno-schedule-insns2 19.8%,
// -fno-schedule-insns 20.1%, -fno-expensive-optimizations 5.0% — default is
// already the winner.  Residual is the PS schedule + fp-pool/regalloc of a
// 1272B body, not a flag.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 51.7% while git revision 6ed950850 scores 61.9%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 17 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
#include "types.h"
extern char lbl_802ACD30[];
extern f32 lbl_802ACDC0;
extern f32 lbl_802ACDC4;
extern f32 lbl_802ACDC8;
extern f32 lbl_802ACDCC;
extern f32 lbl_802ACDD0;
f32 acosf(f32);
f32 fn_8012570C(s32, s32);
void *fn_80003EB0(void *, f32);
f32 sinf(f32);
f32 cosf(f32);

f32 fn_801C7FF0(void *arg0, void *arg1, f32 *arg2) {
    char sp8[0x40];
    f32 res[16];
    struct {
        void *vec;
        void *mat;
    } holder;
    volatile f32 sp98;
    volatile f32 sp9C;
    volatile f32 spA0;
    volatile f32 spA4;
    f32 maxv;
    f32 minv;
    f32 angle;
    f32 chk;
    f32 resv;
    f32 zf;
    f32 var_f30;
    f32 temp_f31;
    void *hp;
    char *matbase;
    s32 m1;
    s32 m2;
    s32 m3;
    __ps_t A23;
    __ps_t M80;
    __ps_t ZEROPAIR;
    __ps_t M78;
    __ps_t A01;
    __ps_t t;
    __ps_t X;
    __ps_t Y;
    __ps_t PCOS;
    __ps_t PSIN;
    __ps_t PCOS2;
    __ps_t t0;
    __ps_t t1;
    SN_PS_type dot;

    A23 = *(__ps_t *)((char *)arg1 + 8);
    m1 = *(s32 *)((char *)arg0 + 0xC);
    M80 = *(__ps_t *)((char *)m1 + 128);
    ZEROPAIR = *(__ps_t *)&lbl_802ACD30;
    t = __builtin_ps_mul(M80, A23);
    M78 = *(__ps_t *)((char *)m1 + 120);
    A01 = *(__ps_t *)((char *)arg1 + 0);
    t = __builtin_ps_merge00(t, ZEROPAIR);
    dot.ps = __builtin_ps_madd(M78, A01, t);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    maxv = lbl_802ACDC0;
    minv = lbl_802ACDC4;
    angle = dot.flt.hi;
    chk = angle;
    __asm__("" : "+f"(chk));
    if (chk > maxv) {
        angle = maxv;
    }
    resv = angle;
    __asm__("" : "+f"(resv));
    if (angle < minv) {
        resv = minv;
    }
    var_f30 = acosf(resv);
    if (var_f30 > lbl_802ACDC8) {
        var_f30 -= lbl_802ACDCC;
    }
    __asm__("" :: "r"(&holder));
    hp = &holder;
    temp_f31 = var_f30 * fn_8012570C(0xE07EE1A9, 1);
    *arg2 = temp_f31;
    m2 = *(s32 *)((char *)arg0 + 0xC);
    spA0 = sinf(temp_f31);
    sp98 = cosf(temp_f31);
    zf = lbl_802ACDD0;
    __asm__ volatile("li 0, 4\n\tmtctr 0");
    sp9C = zf;
    spA4 = zf;
    X = *(__ps_t *)((char *)m2 + 184);
    Y = *(__ps_t *)((char *)m2 + 192);
    __asm__("" ::: "memory");
    PCOS = *(__ps_t volatile *)&sp98;
    t0 = __builtin_ps_mul(X, PCOS);
    PSIN = *(__ps_t volatile *)&spA0;
    t1 = __builtin_ps_mul(X, PSIN);
    t0 = __builtin_ps_madds0(PSIN, Y, t0);
    __asm__("" ::: "memory");
    PCOS2 = *(__ps_t volatile *)&sp98;
    t0 = __builtin_ps_merge01(t0, X);
    t1 = __builtin_ps_msub(PCOS2, Y, t1);
    *(__ps_t *)((char *)m2 + 184) = t0;
    t1 = __builtin_ps_merge01(t1, Y);
    *(__ps_t *)((char *)m2 + 192) = t1;
    m3 = *(s32 *)((char *)arg0 + 0xC);
    matbase = (char *)m3 + 0x78;
    __asm__ volatile("bdnz $");
    holder.vec = fn_80003EB0(sp8, *arg2);
    holder.mat = matbase;
    __asm__("" :: "r"(hp));
    {
        f32 *vv = (f32 *)holder.vec;
        f32 *mm = (f32 *)matbase;

        res[0] = vv[1] * mm[4] + vv[0] * mm[0] + vv[2] * mm[8] + vv[3] * mm[12];
        res[1] = vv[1] * mm[5] + vv[0] * mm[1] + vv[2] * mm[9] + vv[3] * mm[13];
        res[2] = vv[1] * mm[6] + vv[0] * mm[2] + vv[2] * mm[10] + vv[3] * mm[14];
        res[3] = vv[1] * mm[7] + vv[0] * mm[3] + vv[2] * mm[11] + vv[3] * mm[15];
        res[4] = vv[5] * mm[4] + vv[4] * mm[0] + vv[6] * mm[8] + vv[7] * mm[12];
        res[5] = vv[5] * mm[5] + vv[4] * mm[1] + vv[6] * mm[9] + vv[7] * mm[13];
        res[6] = vv[5] * mm[6] + vv[4] * mm[2] + vv[6] * mm[10] + vv[7] * mm[14];
        res[7] = vv[5] * mm[7] + vv[4] * mm[3] + vv[6] * mm[11] + vv[7] * mm[15];
        res[8] = vv[9] * mm[4] + vv[8] * mm[0] + vv[10] * mm[8] + vv[11] * mm[12];
        res[9] = vv[9] * mm[5] + vv[8] * mm[1] + vv[10] * mm[9] + vv[11] * mm[13];
        res[10] = vv[9] * mm[6] + vv[8] * mm[2] + vv[10] * mm[10] + vv[11] * mm[14];
        res[11] = vv[9] * mm[7] + vv[8] * mm[3] + vv[10] * mm[11] + vv[11] * mm[15];
        res[12] = vv[13] * mm[4] + vv[12] * mm[0] + vv[14] * mm[8] + vv[15] * mm[12];
        res[13] = vv[13] * mm[5] + vv[12] * mm[1] + vv[14] * mm[9] + vv[15] * mm[13];
        res[14] = vv[13] * mm[6] + vv[12] * mm[2] + vv[14] * mm[10] + vv[15] * mm[14];
        res[15] = vv[13] * mm[7] + vv[12] * mm[3] + vv[14] * mm[11] + vv[15] * mm[15];
    }
    *(__ps_t *)((char *)matbase + 0) = *(__ps_t *)((char *)res + 0);
    *(__ps_t *)((char *)matbase + 8) = *(__ps_t *)((char *)res + 8);
    *(__ps_t *)((char *)matbase + 16) = *(__ps_t *)((char *)res + 16);
    *(__ps_t *)((char *)matbase + 24) = *(__ps_t *)((char *)res + 24);
    *(__ps_t *)((char *)matbase + 32) = *(__ps_t *)((char *)res + 32);
    *(__ps_t *)((char *)matbase + 40) = *(__ps_t *)((char *)res + 40);
    *(__ps_t *)((char *)matbase + 48) = *(__ps_t *)((char *)res + 48);
    *(__ps_t *)((char *)matbase + 56) = *(__ps_t *)((char *)res + 56);
    return var_f30;
}
