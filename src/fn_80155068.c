// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155068-0x801550C8 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305F9C;
extern void *lbl_80305EAC;
s32 fn_8009CF2C(CStruct *);

s32 ScriptEnteringNetGame(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;
    s32 var_r30;
    Unk_6BAF5070 *temp_r31;

    var_r30 = 0;
    temp_r31 = lbl_80305EAC;
    if (fn_8009CF2C(lbl_80305F9C) != 0) {
        temp_r30 = temp_r31->unk0x38C ^ QB_LOAD_MAINMENU;
        var_r30 = temp_r30 == 0;
    }
    return var_r30;
}
