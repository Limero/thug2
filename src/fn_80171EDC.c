// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171EDC-0x80171FB0 (212B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
s32 fn_80170F7C(s32);
void fn_80170670(void *, s32);
extern s32 lbl_80305EA4;
bool ScriptTODManager_AdvanceTODState(CStruct *pParams, CScript *pScript) {
    s32 var_r4;
    s32 temp_r31;
    s32 temp_r3;

    temp_r31 = lbl_80305EA4;
    if (temp_r31 != 0) {
        temp_r3 = fn_80170F7C(temp_r31);
        switch ((u32)temp_r3) {
        case QB_MORNING:
            var_r4 = QB_AFTERNOON;
            break;
        case QB_AFTERNOON:
            var_r4 = QB_EVENING;
            break;
        case QB_EVENING:
            var_r4 = QB_NIGHT;
            break;
        case QB_NIGHT:
            var_r4 = QB_MORNING;
            break;
        default:
            var_r4 = 0;
            break;
        }
        fn_80170670(temp_r31, var_r4);
        return true;
    }
    return false;
}
