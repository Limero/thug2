// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162540-0x801625CC (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern Unk_9994C3F5 * lbl_80366474;
extern char lbl_802A82FC[];
extern char lbl_802A8300[];
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_8005C284(s32, f32, f32, f32);

bool ScriptRotateTexture(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    f32 spC;
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_r3;

    GetChecksum_2(pParams, 0, &sp8, 0);
    GetFloat(pParams, QB_ANGLE, &spC, 0);
    temp_r3 = fn_8005CF80(lbl_80366474, sp8);
    if (temp_r3 != 0) {
        temp_f0 = *(volatile f32 *)&lbl_802A82FC;
        temp_f2 = *(volatile f32 *)&lbl_802A8300;
        fn_8005C284(temp_r3, spC * temp_f0, temp_f2, temp_f2);
    }
    return true;
}
