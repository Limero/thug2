// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162C00-0x80162CB4 (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern Unk_9994C3F5 * lbl_80366474;
extern f32 lbl_802A8304;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80128CE0(CStruct *, void *, void *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_8005C3E0(s32, s32, f32);

bool ScriptAdjustTextureBrightness(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 sp10;
    f32 spC;
    s32 temp_r3;

    GetChecksum_2(pParams, 0, &sp8, 0);
    temp_r3 = fn_8005CF80(lbl_80366474, sp8);
    if (temp_r3 != 0) {
        sp10 = 0;
        spC = lbl_802A8304;
        fn_80128CE0(pParams, QB_BRIGHTNESS, &spC, 1);
        GetInteger(pParams, QB_ADJUST_CURRENT, &sp10, 0);
        fn_8005C3E0(temp_r3, (sp10 ^ 1) == 0, spC);
    }
    return true;
}
