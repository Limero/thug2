// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B484-0x8022B524 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
void CStruct_delete(CStruct *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void AddChecksum(CStruct *, s32, s32);
s32 CStruct_ctor(s32);
void fn_8022B484(s32 arg0, s32 arg1) {
    s32 temp_r31;

    temp_r31 = CStruct_ctor(CStruct_new(8));
    if (arg1 != 0) {
        AddChecksum(temp_r31, QB_REFOCUS, QB_REFOCUS);
    }
    Script_RunScript(QB_DESTROY_SERVER_MENU_CHILDREN, temp_r31, 0, 0, 0);
    Script_RunScript(QB_ADD_NO_SERVERS_FOUND_MESSAGE, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
}
