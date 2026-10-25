// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016C940-0x8016C9B8 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
void CStruct_delete(CStruct *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80129EA0(CStruct *, u8 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
bool fn_8016C940(s32 **arg0) {
    s32 *temp_r30;
    s32 temp_r29;
    s32 temp_r31;

    temp_r30 = *arg0;
    temp_r29 = *((s32 *)temp_r30);
    temp_r30 = temp_r30 + 1;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_80129EA0(temp_r31, temp_r30);
    Script_RunScript(temp_r29, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
