// PARKED 2026-10-03 — PS/paired-single function (`// extra_cflags: -mps-float`).
// NOT a compile failure: my single-variant harness omitted the per-object
// flag.  FPR/VMX wall.  Not a GPR-only candidate.
//
// family=m2c range=0x800A9298-0x800A93E8 size=336B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "dolphin/SN_PS.h"

extern f32 lbl_8029821C;
extern f32 lbl_80298220;
extern __ps_t lbl_802981C0;

s32 fn_800F0598(s32 obj);
s32 fn_800F0670(s32 obj, s32 flag);
s32 fn_800F078C(s32 obj, void *out);

typedef struct {
    char pad0x0[0x8];
    __ps_t pair0;
    __ps_t pair1;
    char pad0x18[0x4C];
    s32 unk0x64;
    char pad0x68[0x18];
    __ps_t pair2;
    __ps_t pair3;
    char pad0x90[0x10];
    f32 unk0xA0;
    char pad0xA4[0x4];
    f32 unk0xA8;
    char pad0xAC[0x8];
    s32 unk0xB4;
} Unk_A9298;

s32 fn_800A9298(Unk_A9298 *arg0) {
    SN_PS_type sp[6];
    __ps_t d1;
    __ps_t d2;
    __ps_t f0;
    __ps_t e1;
    __ps_t e0;
    __ps_t f12;
    SN_PS_type s;
    s32 var_r3;
    u32 var_r0;
    f32 p4;
    f32 a8;
    f32 p5;

    if (arg0->unk0xA0 != lbl_8029821C) {
        var_r3 = 0;
        if (fn_800F0598(arg0->unk0x64) != 0) {
            fn_800F078C(fn_800F0670(arg0->unk0x64, 0), (void *)&sp[0]);
            d1 = sp[1].ps - arg0->pair3;
            d2 = sp[0].ps - arg0->pair2;
            f0 = __builtin_ps_mul(d1, d1);
            sp[1].ps = d1;
            f0 = __builtin_ps_merge00(f0, lbl_802981C0);
            sp[0].ps = d2;
            f0 = __builtin_ps_madd(d2, d2, f0);
            f0 = __builtin_ps_sum0(f0, f0, f0);
            f0 = __builtin_ps_res(f0);
            f0 = __builtin_ps_rsqrte(f0);
            sp[4].ps = f0;
            {
                p4 = sp[4].flt.hi;
            }
            if (!(p4 < arg0->unk0xA0)) {
                goto block6;
            }
            e1 = arg0->pair3 - arg0->pair1;
            s.ps = arg0->pair0;
            sp[1].ps = e1;
            a8 = p4 * s.flt.hi;
            arg0->unk0xA8 = a8;
            f12 = __builtin_ps_mul(e1, e1);
            sp[3].ps = e1;
            e0 = arg0->pair2 - arg0->pair0;
            sp[2].ps = e0;
            f12 = __builtin_ps_merge00(f12, lbl_802981C0);
            sp[0].ps = e0;
            f12 = __builtin_ps_madd(e0, e0, f12);
            f12 = __builtin_ps_sum0(f12, f12, f12);
            f12 = __builtin_ps_res(f12);
            f12 = __builtin_ps_rsqrte(f12);
            sp[5].ps = f12;
            {
                p5 = sp[5].flt.hi;
            }
            if (a8 > p5) {
                arg0->unk0xA8 = p5;
            }
            var_r3 = 1;
            var_r0 = arg0->unk0xB4 | 1u;
            goto block7;
        }
        return var_r3;
    }
block6:
    var_r3 = 1;
    var_r0 = arg0->unk0xB4 & ~1u;
    arg0->unk0xA8 = arg0->unk0xA0;
block7:
    arg0->unk0xB4 = var_r0;
    return var_r3;
}
