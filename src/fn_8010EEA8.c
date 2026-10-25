// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010EEA8-0x8010EFA0 (248B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029CE94;
extern f64 lbl_8029CE98;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_800A2740(s32, Unk_C8FEE62D *, s32, s32);

bool ScriptInitCOIM(CStruct *pParams, CScript *pScript) {
    f32 sp14;
    s32 sp8;
    s32 spC;
    s32 sp10;
    f32 temp_f13;
    s32 var_r6;

    sp14 = lbl_8029CE94;
    sp8 = 0;
    sp10 = 0;
    spC = 0;
    GetInteger(pParams, QB_SIZE, &sp8, 1);
    GetInteger(pParams, QB_BLOCKALIGN, &spC, 1);
    GetInteger(pParams, QB_UNKNOWN_0xBB9A31B5, &sp10, 1);
    GetFloat(pParams, QB_UNKNOWN_0x03D6DE47, &sp14, 1);
    temp_f13 = sp14 * sp14;
    if (!(temp_f13 >= lbl_8029CE98)) {
        var_r6 = (s32)temp_f13;
    } else {
        var_r6 = (s32)(temp_f13 - lbl_8029CE98);
        var_r6 ^= (s32)0x80000000;
    }
    fn_800A2740(sp10, sp8, spC, var_r6);
    return true;
}
