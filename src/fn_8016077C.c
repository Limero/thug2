// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016077C-0x8016081C (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE7C;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8000BA88(s32, s32, s32);
void fn_8000C5D8(Unk_A0A7249E *, s32, s32);

bool ScriptVibrateController(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    GetInteger(pParams, QB_PORT, &sp8, (s32 *)1);
    GetInteger(pParams, (s32 *)QB_ACTUATOR, &spC, 1);
    GetInteger(pParams, (s32 *)QB_PERCENT, &sp10, 1);
    temp_r3 = fn_8000BA88(lbl_802FFE7C, sp8, 0);
    if (temp_r3 != 0) {
        fn_8000C5D8(temp_r3, spC, sp10);
        return true;
    }
    return false;
}
