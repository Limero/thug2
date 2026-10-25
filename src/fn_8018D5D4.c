// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D5D4-0x8018D614 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);

s32 fn_8018D5D4(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp8;
    s32 var_r3;

    if (arg1 == 0) {
        var_r3 = arg0->unk0x24;
    } else {
        GetStructure_2(arg0->unk0x24, arg1, &sp8, 1);
        var_r3 = sp8;
    }
    return var_r3;
}
