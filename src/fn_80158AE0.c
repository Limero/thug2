// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158AE0-0x80158B2C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801568B8();                                  
void *fn_801568F4();                                

// ScriptSkaterLastScoreLandedLessThan @ 0x80158AE0
s32 ScriptSkaterLastScoreLandedLessThan(CStruct *pParams, CScript *pScript) {
    s32 temp_r31;
    s32 var_r3;
    Unk_C7387A53 *temp_r3;

    temp_r31 = fn_801568B8();
    temp_r3 = fn_801568F4();
    if ((temp_r3 == NULL) || (var_r3 = 1, (((s32) temp_r3->unk0x24 < temp_r31) == 0))) {
        var_r3 = 0;
    }
    return var_r3;
}
