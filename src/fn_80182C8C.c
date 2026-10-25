// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182C8C-0x80182E10 (388B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802A93F4;
extern f32 lbl_802A9400;
s32 Script_GetInteger(s32, s32);

void fn_80182C8C(void *arg0, s32 arg1) {
    f32 temp_f10;
    f32 temp_f12;
    f32 var_f0;
    f32 f_d1;
    f32 f_d2;
    f32 f_d3;
    register s32 a1 __asm__("r30") = arg1;
    register void *p0 __asm__("r31") = arg0;
    register u8 *arr1 __asm__("r28");
    register u8 *arr2 __asm__("r29");
    register s32 twenty __asm__("r8");
    s32 temp_r3;

    if (a1 <= 0x9C3) {
        (((Unk_6A3B48DF *)p0)->unk0x1544)++;
        arr1 = (u8 *)((char *)p0 + 0x1BC);
        (((Unk_6A3B48DF *)p0)->unk0x1548)++;
        if (arr1[a1] == 0) {
            (((Unk_6A3B48DF *)p0)->unk0x154C)++;
            (((Unk_6A3B48DF *)p0)->unk0x1550)++;
        }
        if ((u32)arr1[a1] <= 0xFE) {
            arr1[a1] = arr1[a1] + 1;
        }
        arr2 = (u8 *)((char *)p0 + 0xB80);
        if (arr2[a1] == 0) {
            (((Unk_6A3B48DF *)p0)->unk0x1554)++;
        }
        if ((u32)arr2[a1] <= 0xFE) {
            arr2[a1] = arr2[a1] + 1;
        }
        temp_r3 = Script_GetInteger(QB_ROBOT_KICK_IN_COUNT, 0);
        if ((s32)arr2[a1] > temp_r3) {
            f_d1 = (f32)(f64)((arr2[a1] - temp_r3) + 1);
            f_d2 = (f32)(f64)(0x15 - arr1[a1]);
            twenty = 0x14;
            f_d3 = (f32)(f64)twenty;
            temp_f12 = lbl_802A93F4 / f_d1 * (f_d2 / f_d3);
            temp_f10 = lbl_802A9400;
            var_f0 = temp_f12;
            __asm__("" : "+f"(var_f0));
            ((Unk_6A3B48DF *)p0)->unk0x1558 = temp_f12;
            if (temp_f10 > temp_f12) {
                var_f0 = temp_f10;
            }
        } else {
            var_f0 = lbl_802A93F4;
        }
    } else {
        var_f0 = lbl_802A93F4;
    }
    ((Unk_6A3B48DF *)p0)->unk0x1558 = var_f0;
}
