// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153C3C-0x80153CC4 (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802A7EFC;
extern s32 lbl_80305EAC;
s32 GetFloat(CStruct *, s32, f32 *, s32);
f32 fn_80124EC4(f32);
s32 fn_801745B4(s32);
void *GetChecksum_3(Unk_6A70655D *, s32);

bool ScriptSetSlomo(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    Unk_FF487DD2 *temp_r3;
    s32 temp_r31;

    sp8 = lbl_802A7EFC;
    GetFloat(pParams, 0, &sp8, 0);
    fn_80124EC4(sp8);
    temp_r31 = lbl_80305EAC;
    if (fn_801745B4(temp_r31) != 0) {
        temp_r3 = GetChecksum_3((void *)fn_801745B4(temp_r31), QB_SKATERCOREPHYSICS);
        if (temp_r3 != NULL) {
            temp_r3->unk0x338 = sp8;
        }
    }
    return true;
}
