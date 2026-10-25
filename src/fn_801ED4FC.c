// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ED4FC-0x801ED5F0 (244B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD938;
extern f32 lbl_802AD93C;
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_800B68A0(Unk_C7387A53 *);
void fn_801F0F58(void *);
void fn_801ED4FC(Unk_6F11F76C *arg0) {
    s32 temp_r30;
    f32 var_f13;

    if (arg0->unk0x328 == 0) {
        return;
    }
    temp_r30 = GetChecksum_3(arg0->unk0xC, QB_MODEL);
    var_f13 = arg0->unk0x330 - arg0->unk0x338;
    arg0->unk0x330 = var_f13;
    if (*(s32 *)(arg0->unk0x15BC + 0x1C) != 1) {
        fn_800B68A0((void *)temp_r30);
        arg0->unk0x330 = lbl_802AD938;
        arg0->unk0x328 = 0;
        arg0->unk0x420 = 0;
        arg0->unk0x334 = 0;
    } else {
        if (var_f13 <= lbl_802AD93C) {
            arg0->unk0x420 = 0;
        }
        {
            f32 temp_f0;
            f32 temp_f13;

            temp_f0 = arg0->unk0x330;
            temp_f13 = lbl_802AD938;
            if (temp_f0 <= temp_f13) {
                s32 temp_r9;

                temp_r9 = arg0->unk0x32C;
                arg0->unk0x328 = 0;
                arg0->unk0x330 = temp_f13;
                if (temp_r9 != 0) {
                    fn_801F0F58(GetChecksum_3(arg0->unk0xC, QB_SKATERFLIPANDROTATE));
                }
                fn_800B68A0((void *)temp_r30);
            }
        }
    }
}
