// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017EE70-0x8017EF1C (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_8017EE70(void *arg0, s32 arg1) {
    s32 temp_r31;

    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddChecksum(temp_r31, QB_TRICK_TEXT_CONTAINER_ID, arg1 + QB_TRICK_TEXT_CONTAINER);
    AddChecksum(temp_r31, QB_THE_TRICK_TEXT_ID, arg1 + QB_THE_TRICK_TEXT);
    AddChecksum(temp_r31, QB_THE_SCORE_POT_TEXT_ID, arg1 + QB_THE_SCORE_POT_TEXT);
    Script_RunScript(QB_TRICK_TEXT_BAIL, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
}
