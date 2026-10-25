// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010ED3C-0x8010EDA4 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_800F0F84(s32, s32);
extern void fn_80127C14(CStruct *, s32, CStruct *);

bool ScriptGetNode(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r3;

    GetChecksum_2(pParams, 0, &sp8, 1);
    temp_r3 = fn_800F0F84(sp8, 0);
    if (temp_r3 == 0) {
        return false;
    }
    fn_80127C14(pScript->unk0x18, QB_NODE, temp_r3);
    return true;
}
