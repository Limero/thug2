// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003D50C-0x8003D590 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80129528(CStruct *, s32);
s32 fn_801259C8(s32, s32);
s32 fn_8003D4D8(void);
s32 fn_8003D50C(s32 arg0, s32 arg1, void * arg2) {
    s32 temp_r31;
    s32 var_r27 = 0;
    void *temp_r29 = fn_801259C8(arg0, 1);
    u32 i;
    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < (u32) *((u32 *)&((CStruct *)temp_r29)->unk0x4); i++) {
        temp_r31 = fn_80129528(temp_r29, i);
        if (fn_8003D4D8() == arg1) {
            var_r27 = temp_r31;
            break;
        }
    }
    return var_r27;
}
