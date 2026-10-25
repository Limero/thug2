// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024D4D0-0x8024D558 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_802B1610[];
extern s32 fn_80250E24(CStruct *, s32);
extern void fn_80250E6C(CStruct *, unsigned);
s32 fn_8024D4D0(Unk_C7387A53 *arg0) {
    u32 temp_r30;
    u32 var_r3;

    goto check;
body:
    fn_80250E6C(*((void * *)&arg0->unk0x44), 9);
check:
    if (fn_80250E24(*((void * *)&arg0->unk0x44), 9) <= 0x100U) {
        var_r3 = fn_80250E24(*((void * *)&arg0->unk0x44), 9);
    } else {
        var_r3 = 0x100;
    }
    if ((s32)var_r3 == 1) {
        goto body;
    }
    temp_r30 = lbl_802B1610[var_r3];
    fn_80250E6C(*((void * *)&arg0->unk0x44), temp_r30 >> 0x11U);
    return temp_r30 & 0x1FFFF;
}
