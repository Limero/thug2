// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802199E4-0x80219A80 (156B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
void CStruct_delete(CStruct *, s32);
void AddInteger(CStruct *, s32, s32);
s32 CStruct_ctor(s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_802199E4(s32 arg0, s32 arg1) {
    s32 temp_r31;

    Script_RunScript(QB_KILL_TEAM_FLAGS, 0, 0, 0, 0);
    if (arg1 != 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddInteger(temp_r31, QB_NUM_TEAMS, arg1);
        Script_RunScript(QB_CREATE_TEAM_FLAGS, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
}
