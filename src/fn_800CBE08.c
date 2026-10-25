// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBE08-0x800CBE30 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800CBE08(Unk_C7387A53 *arg0) {
    CStruct *var_r9;

    var_r9 = arg0->unk0x38;
    if ((s32) var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    if (var_r9 != NULL) {
        return var_r9->unk0x68;
    }
    return 0;
}
