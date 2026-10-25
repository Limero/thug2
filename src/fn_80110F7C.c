// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80110F7C-0x80111050 (212B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
f32 fn_800593B4(s32);
f32 fn_800593D4(s32, s32);
void fn_8012772C(CStruct *, s32, f32);
bool ScriptGetDynamicLightModulationFactor(CStruct *pParams, CScript *pScript) {
    volatile double sp8_store;
    volatile double _dummy;
    volatile double _dummy2;
    f32 var_f30;
    f32 var_f31;

    *(s32 *)&sp8_store = 0;
    if (ContainsFlag(pParams, QB_AMBIENT) != 0) {
        var_f30 = fn_800593B4(1);
        var_f31 = fn_800593B4(0);
    } else {
        GetInteger(pParams, QB_DIRECTIONAL, (void *)&sp8_store, 0);
        var_f30 = fn_800593D4(*(s32 *)&sp8_store, 1);
        var_f31 = fn_800593D4(*(s32 *)&sp8_store, 0);
    }
    fn_8012772C(pScript->unk0x18, QB_MOD_VALUE_LO, var_f30);
    fn_8012772C(pScript->unk0x18, QB_MOD_VALUE_HI, var_f31);
    return true;
}
