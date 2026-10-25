// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015552C-0x801555B8 (140B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 fn_8016D1A8(void);
s32 fn_8016CFDC(Unk_C7387A53 *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetText(CStruct *, void *, void *, s32);
void fn_8019FB9C(Unk_6A70655D *, s32, s32);

bool ScriptReloadViewerAnim(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 var_r30;
    s32 temp_r3;

    temp_r3 = fn_8016D1A8();
    if (temp_r3 != 0) {
        var_r30 = fn_8016CFDC(temp_r3);
        if ((var_r30 != 0) && (GetChecksum_2(pParams, 0, &sp8, 0) != 0) &&
            (GetText(pParams, 0, &spC, 0) != 0)) {
            fn_8019FB9C(var_r30, spC, sp8);
        }
    }
    return true;
}
