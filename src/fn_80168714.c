// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80168714-0x80168780 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_802FFF6C;
s32 fn_80015A58(void *, s32, s32);

s32 ScriptCardIsInSlot(CStruct *pParams, CScript *pScript) {
    Unk_C7387A53 *temp_r31;
    s32 var_r3;

    temp_r31 = lbl_802FFF6C;
    if (fn_80015A58(temp_r31, 0, 0) == 0 && temp_r31->unk0x24 == 0) {
        var_r3 = 1;
        if (temp_r31->unk0x28 == 0) {
            var_r3 = 0;
        }
    } else {
        var_r3 = 1;
    }
    return var_r3;
}
