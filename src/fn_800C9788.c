// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C9788-0x800C9808 (128B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_80037968(Unk_C8FEE62D *, void *, s32);
bool fn_800C9788(Unk_31DE137E *arg0, CStruct *arg1) {
    s32 spC;
    s32 sp8;
    s32 var_r5;
    s32 temp_r3;
    s32 temp_r4;

    GetChecksum_2(arg1, QB_BONE, &sp8, 1);
    GetInteger(arg1, QB_ACTIVE, &spC, 1);
    var_r5 = 1;
    temp_r3 = arg0->unk0x1C;
    temp_r4 = sp8;
    if (spC == 0) {
        var_r5 = 0;
    }
    fn_80037968(temp_r3, (void *) temp_r4, var_r5);
    return true;
}
