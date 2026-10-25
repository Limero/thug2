// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9494-0x801A94E8 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_801A92C4(s32 arg0, s32 arg1);
extern s32 fn_801A92F4(s32 arg0, s32 arg1);
extern void fn_801A9DE8(CStruct * arg0, s32 *arg1, s32 arg2);
bool fn_801A9494(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r5;

    fn_801A92C4(arg0, arg1);
    temp_r5 = fn_801A92F4(arg0, arg2);
    fn_801A9DE8(arg0 + 0x20, &arg1, temp_r5);
    return true;
}
