// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7A98-0x800A7B38 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800A79D4(CStruct *, s32, CStruct *);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);
void fn_800A7A98(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r31;
    u32 var_r30;

    arg0->unk0x50 = arg1;
    var_r30 = 0U;
    while (var_r30 < (u32) *((u32 *)&arg1->unk0x4)) {
        temp_r31 = fn_80129528(arg1, var_r30);
        sp8 = 0;
        GetChecksum_2(temp_r31, QB_CLASS, &sp8, 0);
        if (sp8 == -QB_UNKNOWN_0x2E78E62B) {
            fn_800A79D4(arg0, var_r30, temp_r31);
        }
        var_r30 += 1;
    }
}
