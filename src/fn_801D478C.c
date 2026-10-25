// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D478C-0x801D488C (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 lbl_80303150;
extern s32 Tmr_GetTime();
s32 fn_801EC684(Unk_E2C810EF *, s32, s32);

void fn_801D478C(Unk_5827BC2E *arg0, Unk_EA529D06 *arg1, Unk_EA529D06 *arg2, s32 arg3) {
    __ps_t v0;
    __ps_t v1;
    __ps_t w0;
    __ps_t w1;
    f32 t130;
    f32 t300;
    s32 var_r29;
    s32 temp;

    var_r29 = 0;
    {
        char *arr = (char *)arg0 + 0x38C;
        s32 ix = (arg3 ^ 1) * 4;
        s32 ent;
        s32 rel;
        for (; var_r29 <= 3; var_r29++) {
            if (var_r29 != arg3) {
                ent = *(s32 *)(arr + ix);
                rel = Tmr_GetTime();
                if ((u32)(lbl_80303150 + rel - ent) > 0x1F4U) {
                    return;
                }
            }
        }
    }
    arg0->unk0x230 = *(__ps_t *)arg1;
    arg0->unk0x238 = arg1->unk0x8;
    arg0->unk0x240 = *(__ps_t *)arg2;
    arg0->unk0x248 = arg2->unk0x8;
    if (fn_801EC684(arg0, 0x10, 0) == 0) {
        return;
    }
    v0 = arg0->unk0x2F0;
    v1 = arg0->unk0x2F8;
    w0 = arg0->unk0x148;
    w1 = arg0->unk0x150;
    t130 = arg0->unk0x130;
    v0 = __builtin_ps_add(v0, w0);
    t300 = arg0->unk0x300;
    v1 = __builtin_ps_add(v1, w1);
    arg0->unk0x2F0 = v0;
    arg0->unk0x2F8 = v1;
    if (t130 < t300) {
        arg0->unk0x300 = t130;
    }
    {
        s32 ix2 = arg3 * 4;
        char *arr2 = (char *)arg0 + 0x38C;
        *(s32 *)(arr2 + ix2) = lbl_80303150 + Tmr_GetTime();
    }
}
