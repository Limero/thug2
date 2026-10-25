// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019CBCC-0x8019CC4C (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801745B4(s32);
void AddInteger(CStruct *, s32, s32);
bool ScriptCAT_GetFlipSkater(s32 arg0, CScript *arg1) {
    CScript *temp_r3;

    if ((temp_r3 = fn_801745B4(lbl_80305EAC)) != 0) {
        if (temp_r3->unk0x1C8 != 0) {
            AddInteger(arg1->unk0x18, QB_CAT_FLIP_SKATER_180, 1);
        } else {
            AddInteger(arg1->unk0x18, QB_CAT_FLIP_SKATER_180, 0);
        }
        return true;
    }
    return false;
}
