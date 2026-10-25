// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C29B4-0x800C2AB0 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// arg1: the curve. Retail reads every slot from 0xD8 up with `lfs`.
typedef struct {
    char pad0x0[0x4];
    s32 mode; /* 0x4 */
    char pad0x8[0xD0];
    f32 fD8; /* 0xD8 - first breakpoint */
    f32 fDC; /* 0xDC - second breakpoint */
    f32 fE0; /* 0xE0 - third breakpoint */
    f32 fE4; /* 0xE4 - value at breakpoint 2 */
    f32 fE8; /* 0xE8 - value at breakpoint 3 */
    f32 fEC; /* 0xEC - mode-6 curve value */
    f32 fF0; /* 0xF0 - mode-7 curve value */
} S29B4;

extern f32 lbl_80299064;
extern f32 lbl_80299068;
f32 fn_800C29B4(Unk_65DFDA7E *arg0, S29B4 *arg1, f32 farg0) {
    f32 var_f1, var_f0, var_f10, var_f11, var_f13;
    s32 var_r0, var_m;

    if (arg0->unk0x330 != 0) {
        if (arg0->unk0x328 != 0) {
            var_r0 = 6;
            var_f1 = arg1->fEC;
        } else {
            var_r0 = 7;
            __asm__("" : "+r"(var_r0));
            var_f1 = arg1->fF0;
        }
        arg1->mode = var_r0;
        __asm__ __volatile__("" ::: "memory");
        var_f0 = arg1->fD8;
        if (farg0 < var_f0) {
            arg1->mode = 2;
            return (var_f1 * farg0) / var_f0;
        }
        return var_f1;
    }
    if (arg0->unk0x32C != 0) {
        var_f10 = lbl_80299064;
    } else {
        var_f10 = lbl_80299068;
    }
    var_f0 = arg1->fD8;
    if (farg0 < var_f0) {
        arg1->mode = 2;
        return (arg1->fE4 * farg0) / var_f0;
    }
    var_f13 = arg1->fDC;
    if (farg0 < var_f13) {
        var_m = 3;
        var_f1 = arg1->fE4;
        goto shared;
    }
    goto late;
shared:
    arg1->mode = var_m;
    return var_f10 * var_f1;
late:
    var_f11 = arg1->fE0;
    if (farg0 < var_f11) {
        goto interp;
    }
    var_f1 = arg1->fE8;
    var_m = 5;
    goto shared;
interp:
    arg1->mode = 4;
    return (var_f10 * arg1->fE8) +
           (((arg1->fE4 - arg1->fE8) * (farg0 - var_f13)) / (var_f11 - var_f13));
}
