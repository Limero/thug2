// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801594D4-0x8015958C (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: ScriptSkaterCurrentScorePotGreaterThan — script command
// that compares (skater score * score-multiplier) against a given threshold.
// Suggested rename: keep ScriptSkaterCurrentScorePotGreaterThan.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801568B8(void);
s32 fn_801568F4(void);
s32 GetInteger(CStruct *, s32, s32 *, s32);
extern f64 lbl_802A8150;

bool ScriptSkaterCurrentScorePotGreaterThan(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;
    Unk_C8FEE62D *temp_r3;
    f32 var_f13;

    sp8 = 1;
    temp_r31 = fn_801568B8();
    GetInteger(pParams, QB_POINT_SCALE, &sp8, 0);
    temp_r31 = temp_r31 * sp8;
    temp_r3 = (void *)fn_801568F4();
    if (temp_r3 != NULL) {
        var_f13 = (f32)(f64)(s32)temp_r3->unk0x18
            * *((f32 *)&temp_r3->unk0x6C);
        if ((s32)var_f13 > temp_r31) {
            return true;
        }
    }
    return false;
}
