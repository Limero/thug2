// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010EFE4-0x8010F068 (132B). Byte-identical.
#include "types.h"
extern s32 lbl_80301A38;
#include "qb_constants.h"
#include "structs.h"
s32 fn_800A200C(Unk_C7387A53 *, s32);
void fn_800B0EEC(void);
bool ScriptProximCleanup(CStruct *pParams, CScript *pScript) {
    Unk_C8FEE62D *var_r3;
    Unk_C8FEE62D *var_r3_2;

    var_r3 = fn_800A200C((void *)lbl_80301A38, QB_SOUND);
    if (var_r3 != NULL) {
        do {
            var_r3->unk0xC4 = 0;
            var_r3 = var_r3->unk0x14;
        } while (var_r3 != NULL);
    }
    var_r3_2 = fn_800A200C((void *)lbl_80301A38, QB_STREAM);
    if (var_r3_2 != NULL) {
        do {
            var_r3_2->unk0x2C = 0;
            var_r3_2 = var_r3_2->unk0x14;
        } while (var_r3_2 != NULL);
    }
    fn_800B0EEC();
    return true;
}
