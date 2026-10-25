// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80178324-0x801783B4 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern s32 lbl_80305EC0;
s32 fn_8021D2C4(s32, s32);
s32 fn_80198F7C(s32);
s32 fn_8021F6CC(Unk_2EC243AC *);

s32 fn_80178324(CStruct *arg0) {
    s32 temp_r30;
    Unk_C71E6DE1 *temp_r31;
    Unk_C7387A53 *temp_r3;

    temp_r30 = *(s32 *)&lbl_80305F9C;
    temp_r3 = fn_8021D2C4(temp_r30, arg0->unk0x10);
    if (temp_r3 == NULL) {
        return 4;
    }
    temp_r31 = arg0->unk0x0;
    if (fn_80198F7C(lbl_80305EC0) == QB_NETLOBBY) {
        return 4;
    }
    if (fn_8021F6CC(temp_r30) != (s32)temp_r31->unk0x0) {
        return 4;
    }
    temp_r3->unk0x28 = temp_r31->unk0x4;
    return 1;
}
