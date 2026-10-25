// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800439B0-0x80043A34 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80058E78(s32, s32);
s32 fn_8004DD70(Unk_31DE137E *);
void fn_800439B0(Unk_E80761A5 *arg0) {
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;

    temp_r3 = fn_800414B0();
    if (temp_r3 != 0) {
        if ((s32) arg0->unk0x1A4 != 0) {
            temp_r30 = **((s32 * *)&arg0->unk0x19C);
            fn_80058E78(temp_r30, fn_8004DD70(temp_r3));
        }
        if ((s32) arg0->unk0x1AC != 0) {
            temp_r30_2 = **((s32 * *)&arg0->unk0x1A0);
            fn_80058E78(temp_r30_2, fn_8004DD70(temp_r3));
        }
    }
}
