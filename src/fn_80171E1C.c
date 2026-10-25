// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171E1C-0x80171E8C (112B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EA4;
register s32 r31_guard __asm__("r31");
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80170658(s32, s32);
void AddInteger(CStruct *, s32, s32);
bool ScriptTODManager_GetNumberOfDaysPassed(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r5;

    temp_r30 = lbl_80305EA4;
    sp8 = 0;
    GetInteger(pParams, QB_SYSTEM_INDEX, &sp8, 0);
    temp_r5 = fn_80170658(temp_r30, sp8);
    AddInteger(pScript->unk0x18, QB_NUM_DAYS_PASSED, temp_r5);
    return true;
}
