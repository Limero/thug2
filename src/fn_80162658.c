// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162658-0x801626D0 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern Unk_9994C3F5 * lbl_80366474;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_8005C250(s32, f32, f32);

bool ScriptScaleTexture(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    f32 spC;
    s32 temp_r3;

    GetChecksum_2(pParams, 0, &sp8, 0);
    GetFloat(pParams, QB_SCALE, &spC, 0);
    temp_r3 = fn_8005CF80(lbl_80366474, sp8);
    if (temp_r3 != 0) {
        fn_8005C250(temp_r3, spC, spC);
    }
    return true;
}
