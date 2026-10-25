// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112178-0x80112250 (216B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
s32 fn_80128978(s32, s32);
s32 fn_8002D2A0(void);
void fn_8002D2B0(s32, s32);
void fn_8002D728(s32);
void fn_8002D2AC(s32);
bool ScriptUpdateAnimCache(s32 arg0) {
    s32 temp_r29;
    s32 temp_r31;
    s32 temp_r28;
    s32 temp_r3;
    s32 var_r9;
    s32 var_r0;

    temp_r29 = fn_80128978(arg0, QB_DISABLE);
    temp_r31 = fn_80128978(arg0, QB_ENABLE);
    temp_r28 = fn_80128978(arg0, QB_DEFRAG);
    temp_r3 = fn_80128978(arg0, QB_CLEAR);
    var_r9 = (temp_r29 != 0);
    var_r0 = (temp_r31 != 0);
    if ((var_r9 & var_r0) == 0) {
        if (temp_r29 == 0 && temp_r31 == 0) {
            if (temp_r3 != 0) {
                fn_8002D2B0(fn_8002D2A0(), 0);
            } else if (temp_r28 != 0) {
                fn_8002D728(fn_8002D2A0());
            } else {
                fn_8002D2AC(fn_8002D2A0());
            }
        }
    }
    return true;
}
