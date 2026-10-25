// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E034-0x8013E068 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8013E034(s32 arg0, CStruct *arg1) {
    Unk_C7387A53 *temp_r3;
    CStruct *var_r9;

    temp_r3 = arg0 + 0x227C;
    arg1->unk0x4 = temp_r3;
    var_r9 = temp_r3->unk0xC;
    if ((s32) var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    arg1->unk0x4 = var_r9;
    if (var_r9 != NULL) {
        return var_r9->unk0x4;
    }
    return 0;
}
