// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80224774-0x80224804 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void CStruct_delete(CStruct * value, s32 flag);
bool fn_80224774(void) {
    s32 temp_r31;

    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddChecksum(temp_r31, QB_REASON, QB_NET_REASON_FULL_OBSERVERS);
    AddChecksum(temp_r31, QB_JUST_DIALOG, 0);
    Script_RunScript(QB_CREATEJOINREFUSEDDIALOG, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
