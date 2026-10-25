// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024D5C4-0x8024D61C (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80250EAC(CStruct *, s32);
u8 fn_8024D5C4(Unk_C7387A53 *arg0) {
    u8 var_r31;

    var_r31 = 0;
    goto check;
body:
    var_r31 = var_r31 + 1;
check:
    if ((var_r31 <= 3U) && (fn_80250EAC(arg0->unk0x44, 1) == 0)) {
        goto body;
    }
    return var_r31;
}
