// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161158-0x801611C4 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void* lbl_80301A38;
extern s32 lbl_80305EAC;

s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_800A200C(Unk_C7387A53 *, s32);
void fn_801F12D8(s32);

bool ScriptClearPowerups(CStruct *pParams, CScript *pScript) {
    s32 var_r31;
    s32 temp_r30;

    var_r31 = 0;
    temp_r30 = lbl_80305EAC;
    do {
        if (fn_801746A4(temp_r30, var_r31) != 0) {
            fn_801F12D8(fn_800A200C(lbl_80301A38, QB_SKATERSTATE));
        }
        var_r31 += 1;
    } while (var_r31 <= 7);
    return true;
}
