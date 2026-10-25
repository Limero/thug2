// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018148C-0x801814F0 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;

void *fn_8017471C(s32, s16);
s32 fn_8021D358(s32, u16);

s32 fn_8018148C(Unk_667BA59C *arg0) {
    s32 var_r31;
    Unk_FB68EF80 *temp_r3;

    var_r31 = lbl_80305F9C;
    temp_r3 = fn_8017471C(lbl_80305EAC, arg0->unk0xC);
    if (temp_r3 != NULL) {
        temp_r3 = (void *)fn_8021D358(var_r31, temp_r3->unk0x1A);
        if (temp_r3 != NULL) {
            return temp_r3->unk0x1C;
        }
    }
    return 0;
}
