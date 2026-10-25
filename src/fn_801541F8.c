// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801541F8-0x80154250 (88B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_80305EAC[];
extern char lbl_80305F9C[];

s32 fn_801754AC(s32);
s32 fn_8009CF2C(CStruct *);

s32 ScriptInSplitScreenGame(CStruct *pParams, CScript *pScript) {
    s32 temp_r31;
    s32 temp_r3;
    s32 var_r30;

    var_r30 = 0;
    temp_r31 = *(s32 *)&lbl_80305F9C;
    if (fn_801754AC(*(s32 *)&lbl_80305EAC) != 0) {
        temp_r3 = fn_8009CF2C(temp_r31);
        var_r30 = temp_r3 == 0;
    }
    return var_r30;
}
