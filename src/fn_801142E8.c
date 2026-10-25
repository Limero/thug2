// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801142E8-0x80114388 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029D120[];
extern char lbl_8029D128[];
s32 fn_8009DC9C(s32);
void fn_8009DE1C(s32, s32, s32);
s32 fn_80128294(CStruct *, void *, void *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);

bool ScriptSetCaptureAttribute(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;

    sp10 = 0;
    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        temp_r30 = fn_8009DC9C(sp8);
        if (fn_80128294(pParams, (s32)lbl_8029D120, &spC, 0) != 0) {
            fn_80128294(pParams, (s32)lbl_8029D128, &sp10, 0);
            fn_8009DE1C(temp_r30, spC, sp10);
        }
    }
    return true;
}
