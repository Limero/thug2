// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E400-0x8018E49C (156B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 flag);
extern s32 AddInteger(CStruct *, s32, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8018E400(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 temp_r9;

    sp8 = 0;
    GetInteger(arg0->unk0x20, QB_NUMBER_COLLECTED, &sp8, 0);
    temp_r9 = sp8 + 1;
    sp8 = temp_r9;
    AddInteger(arg0->unk0x20, QB_NUMBER_COLLECTED, temp_r9);
    if (ContainsFlag(arg0->unk0x20, QB_USE_HUD_COUNTER) != 0) {
        Script_RunScript(QB_GOAL_UPDATE_COUNTER, arg0->unk0x20, 0, 0, 0);
    }
}
