// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022722C-0x80227288 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern CStruct * lbl_80305F1C;
void fn_801A9528(CStruct *);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8021F500(s32);
bool fn_8022722C(CScript *arg0) {
    s32 temp_r30;

    temp_r30 = arg0->unk0x18;
    fn_801A9528(lbl_80305F1C);
    Script_RunScript(QB_CREATE_GAME_ENDED_DIALOG, 0, 0, 0, 0);
    fn_8021F500(temp_r30);
    return true;
}
