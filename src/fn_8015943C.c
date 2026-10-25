// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015943C-0x80159488 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801568B8(void);
s32 fn_801568F4(void);
s32 fn_801813F0(CStruct *);

bool ScriptSkaterTotalScoreGreaterThan(CStruct *pParams, CScript *pScript) {
    s32 var_r31;
    s32 temp_r3;

    var_r31 = fn_801568B8();
    temp_r3 = fn_801568F4();
    if ((temp_r3 != 0) && (fn_801813F0(temp_r3) > var_r31)) {
        return true;
    }
    return false;
}
