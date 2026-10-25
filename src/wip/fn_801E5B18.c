// WIP DRAFT (non-matching) — hand rewrite from disasm (group H)
// family=m2c range=0x801E5B18-0x801E6440 size=2344B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED: 4.4% (17/385 words, got 1540B vs 2336B) - full semantic
// rewrite compiles clean under -mps-float but whole-function regalloc
// diverges from the prologue on (want saves r27-r31 + f31, frame 0xa0; got
// homes r23+). What is known:
// - ALL opcode-4 words decode clean (no XO5=6/7 wall): ps_mr XO10=72 x2,
//   ps_muls0 x4, ps_add x6 (vsel-decoded words are ps_add).
// - Prologue int->double dance is the 6j-1 manual union form: cvt.w[1] =
//   (lbl_80303150 + Tmr_GetTime()) - *(arg0+0x98) stored FIRST, then
//   cvt.w[0] = 0x43300000, minus lbl_802AD830, frsp (store order verified).
// - IF-body PS block scales vec pairs [r11+152/+160] by SPLAT of the float
//   consts lbl_802AD838/83C - the splat source is loaded as a PAIR from the
//   just-written stack slot (psq_l f11,88(r1) = [c58, junk lane]); needs an
//   escaping/partially-initialized pair local that GCC will not forward.
// - Callee arities audited: Tmr_GetTime() old-style s32; fn_8012570C(s32,s32)
//   ->f32 (kills crclr); fn_801D1458(void*,s32); fn_801EC684(void*,s32,s32);
//   fn_800DF004(s32,lbl_802ADA58,arg0+0xB0); CObject_RemoveRefLink(*t30,t30) 2-arg
//   value+ptr pair (m2c had 1-arg!); Mem_Free(t30); fn_801090B8(ptr,r27)
//   ->ptr with result kept live in r31 via or. (stored later as *t30).
// - List-pop blocks reload *t30 after storing through t29 (compiler cannot
//   prove no-alias) - m2c's shape there is CORRECT, kept.
// - MM#1 (M=r9+0x78 x N=r10n+0x70, both rowmajor 4x4) + four vec4 transforms
//   written back over their own inputs; final pair copyback order verified
//   (sp8->arg0+0x20 ... od[2]->arg0+0x58 single, od[0..1]->arg0+0x50 pair).
// Tried: this rewrite (mo[16] array + loop/unrolled hybrid). Remaining gap:
// want keeps the MM#2 M-constants in callee-saved FPRs f26-f31 loaded ONCE
// from sp98..spD4 (prologue saves 6 FPRs in E1D30 sibling; here f31 only +
// scratch reuse), exact r1-relative pair addresses for every psq op, and
// scheduling of ~200 straight-line fmadds. Retry hints: stage the 12 vector
// components as named locals before each transform (web creation order
// 6ae-7 assigns f-reg roles); frame-template struct (6q-86) to pin slots
// 0x08-0x60; try -fno-schedule-insns/-insns2; compare twin fn_801E1D30.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 4.6% ([7]rev->4.6%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80303150;
extern f64 lbl_802AD830;
extern f32 lbl_802AD838;
extern f32 lbl_802AD83C;
extern u8 lbl_802ADA58[];

s32 *fn_801090B8(s32 *, s32);
void fn_801D1458(Unk_6EBFA797 *, s32);
s32 Tmr_GetTime(void);
f32 fn_8012570C(s32, s32);
s32 fn_801EC684(Unk_E2C810EF *, s32, s32);
void fn_800DF004(Unk_C7387A53 *, void *, Unk_D3DFD83F *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void Mem_Free(void *);

typedef union { __ps_t ps; f32 f[2]; } PSQ;

void fn_801E5B18(Unk_0F353148 *arg0) {
    PSQ sp8;
    PSQ sp16;
    f32 mo[16];
    f32 sp58;
    f32 sp60;
    union { u32 w[2]; f64 d; } cvt;
    f32 var_f31;
    s32 var_r9;
    s32 var_r0;
    Unk_C8FEE62D *temp_r29;
    CStruct *temp_r30;
    s32 *temp_r31;
    s32 *temp_r3;
    s32 temp_r27;
    char *r11;

    arg0->unk0x334 = 0;
    temp_r30 = arg0->unk0x98;
    cvt.w[1] = (*(s32 *)&lbl_80303150 + Tmr_GetTime()) - (u32)temp_r30;
    cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
    var_f31 = (f32)(cvt.d - lbl_802AD830);
    if (var_f31 > fn_8012570C(QB_PHYSICS_WALLPLANT_DURATION, 0)) {
        volatile PSQ sc1;
        volatile PSQ sc2;
        __ps_t v152;
        __ps_t v160;
        __ps_t t1;
        __ps_t t2;

        fn_801D1458(arg0, 1);
        sp58 = lbl_802AD838;
        r11 = arg0->unk0xC;
        sc1.f[0] = sp58;
        v152 = ((Unk_0B6E8BDA *)r11)->unk0x98;
        v160 = ((Unk_0B6E8BDA *)r11)->unk0xA0;
        t1 = __builtin_ps_mul(v152, *(__ps_t *)&sc1);
        sp60 = lbl_802AD83C;
        sp8.ps = t1;
        t2 = __builtin_ps_mul(v160, *(__ps_t *)&sc1);
        sc2.f[0] = sp60;
        arg0->unk0x230 = sp8.ps;
        sp16.ps = t2;
        arg0->unk0x238 = *(__ps_t *)&sp16;
        sp8.ps = __builtin_ps_mul(v152, *(__ps_t *)&sc2);
        arg0->unk0x240 = sp8.ps;
        sp16.ps = __builtin_ps_mul(v160, *(__ps_t *)&sc2);
        arg0->unk0x248 = *(__ps_t *)&sp16;
        {
            __ps_t e88;
            __ps_t e96;
            e88 = ((Unk_0B6E8BDA *)r11)->unk0x58;
            e96 = ((Unk_0B6E8BDA *)r11)->unk0x60;
            e88 = __builtin_ps_add(e88, sp8.ps);
            arg0->unk0x230 = e88;
            e96 = __builtin_ps_add(e96, *(__ps_t *)&sp16);
            arg0->unk0x238 = e96;
            e88 = ((Unk_0B6E8BDA *)r11)->unk0x58;
            e88 = __builtin_ps_add(e88, *(__ps_t *)&sp8);
            arg0->unk0x240 = e88;
            e96 = ((Unk_0B6E8BDA *)r11)->unk0x60;
            e96 = __builtin_ps_add(e96, *(__ps_t *)&sp16);
            arg0->unk0x248 = e96;
        }
        if (fn_801EC684(arg0, 0x10, 0) != 0) {
            fn_800DF004(arg0->unk0x15A4, lbl_802ADA58, (char *)arg0 + 0xB0);
        }
    } else {
        arg0->unk0x274 = 0;
        arg0->unk0x25C = 0;
        temp_r29 = arg0->unk0x15C0;
        r11 = arg0->unk0xC;
        temp_r30 = *((s32 * *)&temp_r29->unk0x1C);
        temp_r27 = (s32)(r11 + 0x58);
        if (temp_r30 == NULL) {
            var_r9 = 0;
        } else {
            temp_r31 = *((s32 **)temp_r30);
            if ((s32)temp_r31 != 0) {
                var_r9 = 1;
            } else {
                temp_r29->unk0x70 = (s32)temp_r31;
                if (*((s32 **)temp_r30) != NULL) {
                    CObject_RemoveRefLink(*((s32 **)temp_r30), temp_r30);
                }
                temp_r30->unk0x0 = (s32)temp_r31;
                Mem_Free(temp_r30);
                temp_r29->unk0x1C = (s32)temp_r31;
                temp_r29->unk0x74 = *(s32 *)&lbl_80303150 + Tmr_GetTime();
                var_r9 = 0;
            }
        }
        if (var_r9 != 0) {
            temp_r3 = fn_801090B8(*((s32 * *)&temp_r29->unk0x1C), temp_r27);
            if ((s32)temp_r3 != 0) {
                var_r0 = 1;
            } else {
                temp_r30 = *((s32 * *)&temp_r29->unk0x1C);
                if (temp_r30 != NULL) {
                    temp_r29->unk0x70 = (s32)*((s32 **)temp_r30);
                    if (*((s32 **)temp_r30) != NULL) {
                        CObject_RemoveRefLink(*((s32 **)temp_r30), temp_r30);
                    }
                    temp_r30->unk0x0 = (s32)temp_r3;
                    Mem_Free(temp_r30);
                    temp_r29->unk0x1C = (s32)temp_r3;
                    temp_r29->unk0x74 = *(s32 *)&lbl_80303150 + Tmr_GetTime();
                }
                goto block_17;
            }
        } else {
block_17:
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            char *r9m;
            char *r10n;

            temp_r29 = arg0->unk0x15C0;
            r9m = arg0->unk0xC;
            r10n = *((char * *)&temp_r29->unk0x1C);
            {
                __ps_t a88;
                __ps_t a96;
                a88 = __builtin_ps_add(a88, a96);
                a96 = ((Unk_7BB6AF0E *)r10n)->unk0x60;
                a88 = ((Unk_0B6E8BDA *)r9m)->unk0x58;
                ((Unk_0B6E8BDA *)r9m)->unk0x58 = a88;
                a96 = ((Unk_7BB6AF0E *)r10n)->unk0x68;
                a96 = __builtin_ps_add(a88, a96);
                ((Unk_0B6E8BDA *)r9m)->unk0x60 = a96;
            }
            if (((Unk_FFAD6788 *)r10n)->unk0xB0 != 0) {
                int i;
                int j;
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        mo[i * 4 + j] = *(f32 *)(r9m + 0x78 + i * 0x10) * *(f32 *)(r10n + 0x70 + j * 4) +
                                        *(f32 *)(r9m + 0x78 + i * 0x10 + 4) * *(f32 *)(r10n + 0x70 + j * 4 + 0x10) +
                                        *(f32 *)(r9m + 0x78 + i * 0x10 + 8) * *(f32 *)(r10n + 0x70 + j * 4 + 0x20) +
                                        *(f32 *)(r9m + 0x78 + i * 0x10 + 0xC) * *(f32 *)(r10n + 0x70 + j * 4 + 0x30);
                    }
                }
                ((Unk_0B6E8BDA *)r9m)->unk0x78 = *(__ps_t *)&mo[0];
                ((Unk_0B6E8BDA *)r9m)->unk0x80 = *(__ps_t *)&mo[2];
                ((Unk_0B6E8BDA *)r9m)->unk0x88 = *(__ps_t *)&mo[4];
                ((Unk_0B6E8BDA *)r9m)->unk0x90 = *(__ps_t *)&mo[6];
                ((Unk_0B6E8BDA *)r9m)->unk0x98 = *(__ps_t *)&mo[8];
                ((Unk_0B6E8BDA *)r9m)->unk0xA0 = *(__ps_t *)&mo[10];
                ((Unk_0B6E8BDA *)r9m)->unk0xA8 = *(__ps_t *)&mo[12];
                ((Unk_0B6E8BDA *)r9m)->unk0xB0 = *(__ps_t *)&mo[14];
                /* four vec4 transforms */
                {
                    f32 vx;
                    f32 vy;
                    vx = ((Unk_F7C2FA01 *)arg0)->unk0x20;
                    vy = arg0->unk0x24;
                    mo[0] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x70 +
                            vx * ((Unk_7BB6AF0E *)r10n)->unk0x80 +
                            ((Unk_F7C2FA01 *)arg0)->unk0x28 * ((Unk_7BB6AF0E *)r10n)->unk0x90 +
                            arg0->unk0x2C * ((Unk_7BB6AF0E *)r10n)->unk0xA0;
                    mo[1] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x74 +
                            vx * ((Unk_7BB6AF0E *)r10n)->unk0x84 +
                            ((Unk_F7C2FA01 *)arg0)->unk0x28 * ((Unk_7BB6AF0E *)r10n)->unk0x94 +
                            arg0->unk0x2C * ((Unk_7BB6AF0E *)r10n)->unk0xA4;
                    mo[2] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x78 +
                            vx * ((Unk_7BB6AF0E *)r10n)->unk0x88 +
                            ((Unk_F7C2FA01 *)arg0)->unk0x28 * ((Unk_7BB6AF0E *)r10n)->unk0x98 +
                            arg0->unk0x2C * ((Unk_7BB6AF0E *)r10n)->unk0xA8;
                    mo[3] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x7C +
                            vx * ((Unk_7BB6AF0E *)r10n)->unk0x8C +
                            ((Unk_F7C2FA01 *)arg0)->unk0x28 * ((Unk_7BB6AF0E *)r10n)->unk0x9C +
                            arg0->unk0x2C * ((Unk_7BB6AF0E *)r10n)->unk0xAC;
                    vx = ((Unk_F7C2FA01 *)arg0)->unk0x30;
                    vy = arg0->unk0x34;
                    mo[4] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x70 +
                            vx * ((Unk_7BB6AF0E *)r10n)->unk0x80 +
                            ((Unk_F7C2FA01 *)arg0)->unk0x38 * ((Unk_7BB6AF0E *)r10n)->unk0x90 +
                            arg0->unk0x3C * ((Unk_7BB6AF0E *)r10n)->unk0xA0;
                    mo[5] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x74 +
                            vx * ((Unk_7BB6AF0E *)r10n)->unk0x84 +
                            ((Unk_F7C2FA01 *)arg0)->unk0x38 * ((Unk_7BB6AF0E *)r10n)->unk0x94 +
                            arg0->unk0x3C * ((Unk_7BB6AF0E *)r10n)->unk0xA4;
                    mo[6] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x78 +
                            vx * ((Unk_7BB6AF0E *)r10n)->unk0x88 +
                            ((Unk_F7C2FA01 *)arg0)->unk0x38 * ((Unk_7BB6AF0E *)r10n)->unk0x98 +
                            arg0->unk0x3C * ((Unk_7BB6AF0E *)r10n)->unk0xA8;
                    mo[7] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x7C +
                            vx * ((Unk_7BB6AF0E *)r10n)->unk0x8C +
                            ((Unk_F7C2FA01 *)arg0)->unk0x38 * ((Unk_7BB6AF0E *)r10n)->unk0x9C +
                            arg0->unk0x3C * ((Unk_7BB6AF0E *)r10n)->unk0xAC;
                    mo[8] = ((Unk_3F1371E8 *)r10n)->unk0x20 * ((Unk_7BB6AF0E *)r10n)->unk0x70 +
                            ((Unk_7BB6AF0E *)r10n)->unk0x24 * ((Unk_7BB6AF0E *)r10n)->unk0x80 +
                            ((Unk_3F1371E8 *)r10n)->unk0x28 * ((Unk_7BB6AF0E *)r10n)->unk0x90 +
                            ((Unk_7BB6AF0E *)r10n)->unk0x2C * ((Unk_7BB6AF0E *)r10n)->unk0xA0;
                    mo[9] = ((Unk_3F1371E8 *)r10n)->unk0x20 * ((Unk_7BB6AF0E *)r10n)->unk0x74 +
                            ((Unk_7BB6AF0E *)r10n)->unk0x24 * ((Unk_7BB6AF0E *)r10n)->unk0x84 +
                            ((Unk_3F1371E8 *)r10n)->unk0x28 * ((Unk_7BB6AF0E *)r10n)->unk0x94 +
                            ((Unk_7BB6AF0E *)r10n)->unk0x2C * ((Unk_7BB6AF0E *)r10n)->unk0xA4;
                    mo[10] = ((Unk_3F1371E8 *)r10n)->unk0x20 * ((Unk_7BB6AF0E *)r10n)->unk0x78 +
                             ((Unk_7BB6AF0E *)r10n)->unk0x24 * ((Unk_7BB6AF0E *)r10n)->unk0x88 +
                             ((Unk_3F1371E8 *)r10n)->unk0x28 * ((Unk_7BB6AF0E *)r10n)->unk0x98 +
                             ((Unk_7BB6AF0E *)r10n)->unk0x2C * ((Unk_7BB6AF0E *)r10n)->unk0xA8;
                    mo[11] = ((Unk_3F1371E8 *)r10n)->unk0x20 * ((Unk_7BB6AF0E *)r10n)->unk0x7C +
                             ((Unk_7BB6AF0E *)r10n)->unk0x24 * ((Unk_7BB6AF0E *)r10n)->unk0x8C +
                             ((Unk_3F1371E8 *)r10n)->unk0x28 * ((Unk_7BB6AF0E *)r10n)->unk0x9C +
                             ((Unk_7BB6AF0E *)r10n)->unk0x2C * ((Unk_7BB6AF0E *)r10n)->unk0xAC;
                    vx = ((Unk_F7C2FA01 *)arg0)->unk0x50;
                    vy = arg0->unk0x54;
                    mo[12] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x70 +
                             vx * ((Unk_7BB6AF0E *)r10n)->unk0x80 +
                             arg0->unk0x58 * ((Unk_7BB6AF0E *)r10n)->unk0x90 +
                             arg0->unk0x5C * ((Unk_7BB6AF0E *)r10n)->unk0xA0;
                    mo[13] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x74 +
                             vx * ((Unk_7BB6AF0E *)r10n)->unk0x84 +
                             arg0->unk0x58 * ((Unk_7BB6AF0E *)r10n)->unk0x94 +
                             arg0->unk0x5C * ((Unk_7BB6AF0E *)r10n)->unk0xA4;
                    mo[14] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x78 +
                             vx * ((Unk_7BB6AF0E *)r10n)->unk0x88 +
                             arg0->unk0x58 * ((Unk_7BB6AF0E *)r10n)->unk0x98 +
                             arg0->unk0x5C * ((Unk_7BB6AF0E *)r10n)->unk0xA8;
                    mo[15] = vy * ((Unk_7BB6AF0E *)r10n)->unk0x7C +
                             vx * ((Unk_7BB6AF0E *)r10n)->unk0x8C +
                             arg0->unk0x58 * ((Unk_7BB6AF0E *)r10n)->unk0x9C +
                             arg0->unk0x5C * ((Unk_7BB6AF0E *)r10n)->unk0xAC;
                }
                *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x20) = *(__ps_t *)&sp8;
                *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x28) = *(__ps_t *)&sp16;
                *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x30) = *(__ps_t *)&mo[4];
                *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x38) = *(__ps_t *)&mo[6];
                *((__ps_t *)&((Unk_3F1371E8 *)r10n)->unk0x20) = *(__ps_t *)&mo[8];
                *((__ps_t *)&((Unk_3F1371E8 *)r10n)->unk0x28) = *(__ps_t *)&mo[10];
                arg0->unk0x58 = mo[14];
                *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x50) = *(__ps_t *)&mo[12];
            }
        }
    }
}
