// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801542A4-0x80154330 (140B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_80305EC0[];

s32 fn_80127358(CStruct *, Unk_C7387A53 *);
s32 IsTrue(s32, void *);

bool ScriptGameModeEquals(CStruct *pParams, CScript *pScript) {
    CStruct *var_r31;

    var_r31 = (void *)fn_80127358(pParams, 0);
    while (var_r31 != NULL) {
        if ((var_r31->unk0x4 == 0) &&
            ((*((u32 *)&var_r31->unk0x0) & 0x7F0000) == 0xD0000) &&
            (IsTrue(*(s32 *)&lbl_80305EC0, var_r31->unk0x8) != 0)) {
            return true;
        }
        var_r31 = (void *)fn_80127358(pParams, (s32)var_r31);
    }
    return false;
}
