// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162244-0x801622D4 (144B). Byte-identical.
#include "types.h"
extern s32 lbl_80366474;
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8005C10C(s32, s32, s32);

bool ScriptPut32BitImageIntoTexture(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    GetChecksum_2(pParams, 0, &sp8, 0);
    temp_r3 = fn_8005CF80(lbl_80366474, sp8);
    if (temp_r3 != 0) {
        GetInteger(pParams, QB_PALETTE_GEN, (spC = 0, &spC), 0);
        fn_8005C10C(temp_r3, (spC ^ 1) == 0, 0);
    }
    return true;
}
