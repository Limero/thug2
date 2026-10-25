// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015958C-0x80159618 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: ScriptSkaterCurrentScorePotLessThan — sibling of the
// ScorePotGreaterThan command; same score*multiply comparison, reversed sign.
// Suggested rename: keep ScriptSkaterCurrentScorePotLessThan.
#include "types.h"
#include "structs.h"
s32 fn_801568B8(void);
s32 fn_801568F4(void);
extern f64 lbl_802A8158;

bool ScriptSkaterCurrentScorePotLessThan(CStruct *pParams, CScript *pScript) {
    s32 temp_r31;
    Unk_C8FEE62D *temp_r3;
    f32 var_f13;

    temp_r31 = fn_801568B8();
    temp_r3 = (void *)fn_801568F4();
    if (temp_r3 != NULL) {
        var_f13 = (f32)(f64)(s32)temp_r3->unk0x18
            * *((f32 *)&temp_r3->unk0x6C);
        if ((s32)var_f13 < temp_r31) {
            return true;
        }
    }
    return false;
}
