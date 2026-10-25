// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CF5AC-0x801CF618 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80303150;
extern s32 ContainsFlag(CStruct *, s32);
extern s32 Tmr_GetTime(void);
bool fn_801CF5AC(Unk_71062261 *arg0, CStruct *arg1) {
    s32 *temp_r30;
    s32 var_r3;

    var_r3 = ContainsFlag(arg1, QB_OFF) ^ 1;
    temp_r30 = (s32 *)(arg0->unk0x15BC + (s32)0xCC);
    if (temp_r30[1] != var_r3) {
        temp_r30[1] = var_r3;
        temp_r30[2] = lbl_80303150 + Tmr_GetTime();
    }
    return true;
}
