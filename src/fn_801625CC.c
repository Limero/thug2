// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801625CC-0x80162658 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern Unk_9994C3F5 * lbl_80366474;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_8005C21C(s32, s32, s32);

bool ScriptResizeTextureInto(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 temp_r3;
    s32 temp_r4;

    GetChecksum_2(pParams, 0, &sp8, 0);
    GetChecksum_2(pParams, QB_SRC, &spC, 0);
    temp_r3 = fn_8005CF80(lbl_80366474, sp8);
    if (temp_r3 != 0) {
        temp_r4 = fn_8005CF80(lbl_80366474, spC);
        if (temp_r4 != 0) {
            fn_8005C21C(temp_r3, temp_r4, 0);
        }
    }
    return true;
}
