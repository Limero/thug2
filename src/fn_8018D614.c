// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D614-0x8018D684 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8018D5D4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_80128978(s32 arg0, s32 arg1);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);

s32 fn_8018D614(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp8;
    s32 temp_r31;
    s32 var_r3;

    temp_r31 = fn_8018D5D4(arg0, arg3);
    if (fn_80128978(temp_r31, arg1) == 0) {
        var_r3 = 0;
    } else {
        GetInteger(temp_r31, arg1, &sp8, 1);
        var_r3 = sp8;
        var_r3 = arg2 == var_r3;
    }
    return var_r3;
}
