// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233F00-0x80233FD0 (208B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80128A90(CStruct *, void *);
extern char lbl_80305FF8[];
extern char lbl_802B0970[];
extern char lbl_802B0978[];
extern char lbl_802B0980[];

// MATCHED @ 0x80233F00
s32 ScriptCustomParkMode(CStruct *pParams, CScript *pScript) {
    Unk_C7387A53 *temp_r30;
    s32 var_r3;

    temp_r30 = *(s32 *)&lbl_80305FF8;
    if (fn_80128A90(pParams, (s32)lbl_802B0970) != 0) {
        return temp_r30->unk0x44 == QB_EDIT;
    }
    if (fn_80128A90(pParams, (s32)lbl_802B0978) != 0) {
        return temp_r30->unk0x44 == QB_TEST_PLAY;
    }
    if (fn_80128A90(pParams, (s32)lbl_802B0980) != 0) {
        var_r3 = 1;
        if (temp_r30->unk0x44 == QB_OFF) {
            var_r3 = 0;
        }
        return var_r3;
    }
    return 0;
}
