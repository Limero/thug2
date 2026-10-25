// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010D1C0-0x8010D27C (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80301A38;
s32 fn_8005DD6C(s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
void *fn_800A398C(s32, s32);
void fn_80024344(s32, s32, void *, void *, void *);
void fn_8012772C(CStruct *, s32, f32);

bool ScriptGetObjScreenCoords(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    f32 spC;
    f32 sp10;
    s32 sp14;
    s32 temp_r31;
    void *var_r4;

    temp_r31 = fn_8005DD6C(0);
    sp8 = 0;
    fn_80128E34(pParams, QB_OBJECT, &sp8, 1);
    var_r4 = fn_800A398C(lbl_80301A38, sp8);
    if (var_r4 != 0) {
        fn_80024344(temp_r31, (s32)var_r4 + 0x58, &spC, &sp10, &sp14);
        fn_8012772C(pScript->unk0x18, QB_SCREEN_X, spC);
        fn_8012772C(pScript->unk0x18, QB_SCREEN_Y, sp10);
        return true;
    }
    return false;
}
