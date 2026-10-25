// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158B2C-0x80158B7C (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 AddInteger(CStruct *, s32, s32);
s32 ScriptSkaterGetLastScoreLanded(void *arg0, CScript *arg1) {
    s32 var_r3;
    Unk_C7387A53 *temp_r3;

    temp_r3 = fn_801568F4();
    var_r3 = 0;
    if (temp_r3 != NULL) {
        AddInteger(arg1->unk0x18, QB_LAST_SCORE_LANDED, temp_r3->unk0x24);
        var_r3 = 1;
    }
    return var_r3;
}
