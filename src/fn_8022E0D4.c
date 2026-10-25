// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022E0D4-0x8022E10C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8022E33C(CStruct *, CStruct *, s32);
void fn_8022E0D4(CStruct *arg0, CStruct *arg1) {
    s32 temp_r0;
    s32 temp_r9;

    temp_r0 = arg1->unk0x4 | 0x1000;
    arg1->unk0x4 = temp_r0;
    temp_r9 = temp_r0 & 0x200;
    if (temp_r9 != 0) {
        fn_8022E33C(arg0, arg1, 0);
    }
}
