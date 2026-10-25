// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F5188-0x801F5218 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_801F1684(s32);
void fn_801F50B0(s32, s32, CStruct *);
s32 fn_80129C08(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
s32 fn_801F5188(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r30;
    s32 temp_r31;

    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_801F50B0(arg0, fn_801F1684(arg1), temp_r31);
    temp_r30 = fn_80129C08(temp_r31, arg2, arg3, 1, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return temp_r30;
}
