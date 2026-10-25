// WIP DRAFT — PARKED: big -mps-float allocator/scheduler wall (~3% masked).
// Hand-rebuilt from disasm 2026-08-24 (m2c draft was corrupt: lost the PS
// dot-product prologue, one chained sqrtf call, float field divide
// `lfs f13,0x30(r30)` (m2c made it s32), all three manual int->float cvt
// dances sharing ONE stack slot r1+0xa8/0xac, and the dead pair spills).
// Semantics below are faithful to WANT; every block is present. It does NOT
// byte-match: ngccc's GCSE hoists the lbl_802AC0D0 page anchor into a
// callee-saved reg live across calls (want rematerializes lis per site),
// the hash-arg setup is emitted adjacent to its bl instead of interleaved
// into the pre-call PS block, and the whole body lands in saved regs
// r21-r28 that want keeps in scratch (want saves only r29/r30/r31; r30 is
// recycled &out -> temp_r30). Tried: plain locals, volatile __ps_t spill
// array, alias-symbol reads (6ad-144), volatile f64 loads, register pin on
// var_r29, "+r" opaque pointer barriers, call-position move — all ~3%
// masked, mnemonic-sequence similarity only ~54%. Same wall class as the
// M5.0n spill/regalloc parks and the doc-15/GCSE-anchor family. Do not
// re-grind without a new lever for GCSE anchor insertion point.
// family=m2c range=0x801B56C8-0x801B5A54 size=908B
// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-fno-expensive-optimizations` -> 2.20% to 24.23%.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float -fno-expensive-optimizations
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 24.7% ([3]rev->24.7%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802AC0CC;
extern f64 lbl_802AC0D0;
extern f32 lbl_802AC0D8;
extern f32 lbl_802AC0DC;
extern f32 lbl_802AC0E0;
extern f32 lbl_802AC0E4;
extern char lbl_802ABFB8[];

extern f32 fn_8012570C(s32, s32);
extern void fn_801B62EC(void *);
extern s32 Script_GetInteger(s32, s32);
extern void fn_801B6310(Unk_A9157FE7 *);
extern void *GetChecksum_3(Unk_6A70655D *, s32);
extern f32 fn_80005E20(void *, void *);
extern f32 cosf(f32);
extern f32 sqrtf(f32);
extern void fn_801B5BF8(void *, void *, f32);

typedef union { u32 w[2]; f64 d; } cvt_u;

s32 fn_801B56C8(Unk_61ECF642 *arg0) {
    volatile __ps_t sa[6];
    __ps_t sq;
    __ps_t tab;
    __ps_t z;
    __ps_t s0r;
    __ps_t s1r;
    __ps_t s2r;
    __ps_t dd1;
    __ps_t d2v;
    __ps_t mgd;
    SN_PS_type dot;
    __ps_t fr[10];
    Unk_DF2324A8 *r11;
    register s32 var_r29 __asm__("r29");
    Unk_C7387A53 *temp_r30;
    s32 t;
    s32 cnt;
    f32 var_f30;
    f32 var_f12;
    f32 prod;
    f32 ang;
    s32 tt;
    f32 df;
    f32 g;

    var_r29 = 0;
    sa[0] = arg0->unk0x78;
    g = lbl_802AC0CC;
    sa[1] = arg0->unk0x80;
    r11 = (void *)arg0->unk0xC;
    sa[2] = r11->unk0x58;
    tab = *(__ps_t *)&lbl_802ABFB8;
    z = r11->unk0x60;
    s0r = sa[0];
    sa[3] = z;
    *(f32 volatile *)((char *)&sa[2] + 4) = g;
    s1r = sa[1];
    s2r = sa[2];
    dd1 = z - s1r;
    sq = __builtin_ps_mul(dd1, dd1);
    sa[5] = dd1;
    d2v = s2r - s0r;
    mgd = __builtin_ps_merge00(sq, tab);
    sa[4] = d2v;
    dot.ps = __builtin_ps_madd(d2v, d2v, mgd);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    df = dot.flt.hi;
    var_f30 = fn_8012570C(QB_PED_TARGET_NODE_BIAS, 1);
    fn_801B62EC(arg0);
    if (arg0->unk0x60 == arg0->unk0x58) {
        if (df <= fn_8012570C(QB_PED_WALKER_MIN_SQUARE_DISTANCE_TO_DEAD_END, 1)) {
            fn_801B6310(arg0);
        }
    } else {
        s32 var_r3;
        s32 t0;

        if (arg0->unk0x1C == 2) {
            var_r3 = Script_GetInteger(QB_PED_SKATER_FADE_TARGET_BIAS_MAX_DISTANCE_SQUARE, 1);
        } else {
            var_r3 = Script_GetInteger(QB_PED_FADE_TARGET_BIAS_MAX_DISTANCE_SQUARE, 1);
        }
        t0 = arg0->unk0x9C;
        if (t0 != 0 && *((s32 *)&arg0->unk0x98) >= t0) {
            fn_801B6310(arg0);
        } else if (arg0->unk0x60 != 0) {
            cvt_u cv;

            cv.w[1] = (u32)var_r3 ^ 0x80000000;
            cv.w[0] = QB_INT_TO_DOUBLE_BIAS;
            if (df < (f32)(cv.d - lbl_802AC0D0)) {
                __ps_t a80;
                __ps_t a70;
                __ps_t a90;
                __ps_t v1;
                __ps_t v0;
                __ps_t va0;
                __ps_t vb0;
                __ps_t va1;
                __ps_t vb1;
                __ps_t t12;
                __ps_t t13;
                f32 cs;

                a80 = arg0->unk0x80;
                fr[4] = arg0->unk0x88;
                fr[2] = arg0->unk0x78;
                fr[0] = arg0->unk0x68;
                temp_r30 = GetChecksum_3((void *)arg0->unk0xC, QB_MOTION);
                df = df + df;
                *(f32 *)((char *)&fr[4] + 4) = lbl_802AC0CC;
                *(f32 *)((char *)&fr[0] + 4) = lbl_802AC0CC;
                *(f32 *)((char *)&fr[2] + 4) = lbl_802AC0CC;
                a70 = arg0->unk0x70;
                v1 = fr[2];
                fr[1] = a70;
                v0 = fr[0];
                a80 = arg0->unk0x80;
                va0 = v1 - v0;
                fr[3] = a80;
                t13 = v1;
                v1 = fr[4];
                a90 = arg0->unk0x90;
                t12 = arg0->unk0x70;
                vb0 = v1 - t13;
                fr[5] = a90;
                vb1 = arg0->unk0x90;
                va1 = a80 - t12;
                vb1 = vb1 - a80;
                fr[7] = va1;
                fr[8] = vb0;
                fr[9] = vb1;
                fr[6] = va0;
                ang = fn_80005E20(&fr[6], &fr[8]) * lbl_802AC0D8;
                cs = cosf(ang) + lbl_802AC0DC;
                tt = (s32)((sqrtf(sqrtf(df * cs)) /
                            *((f32 *)&temp_r30->unk0x30)) * lbl_802AC0E0);
                arg0->unk0x9C = tt;
                if (tt <= 0) {
                    arg0->unk0x9C = 1;
                }
                t = arg0->unk0x9C;
                var_r29 = 1;
                cnt = *((s32 *)&arg0->unk0x98);
                if (t == 0) {
                    var_f12 = lbl_802AC0CC;
                } else {
                    cvt_u ca;
                    cvt_u cb;

                    cb.w[1] = (u32)t ^ 0x80000000;
                    cb.w[0] = QB_INT_TO_DOUBLE_BIAS;
                    ca.w[1] = (u32)(t - cnt) ^ 0x80000000;
                    ca.w[0] = QB_INT_TO_DOUBLE_BIAS;
                    var_f12 = (lbl_802AC0DC -
                               ((f32)(cb.d - lbl_802AC0D0) / (f32)(ca.d - lbl_802AC0D0))) *
                              lbl_802AC0E4;
                }
                *((s32 *)&arg0->unk0x98) = cnt + 1;
                prod = var_f30 * var_f12;
                var_f30 = var_f30 - prod;
                fr[0] = arg0->unk0x88;
                fr[1] = arg0->unk0x90;
                fn_801B5BF8(arg0, fr, prod);
            }
        }
    }
    fr[0] = arg0->unk0x78;
    fr[1] = arg0->unk0x80;
    fn_801B5BF8(arg0, fr, var_f30);
    return var_r29;
}
