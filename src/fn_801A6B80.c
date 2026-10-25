// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6B80-0x801A6C4C (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_801259C8(s32 arg0, s32 arg1);
extern s32 GetChecksum(CStruct * arg0, s32 arg1);
extern s32 fn_80125A3C(void * arg0, s32 arg1);
extern s32 fn_801A6B64(Unk_93C2DF4D * arg0, s32 arg1);
extern s32 fn_801A6CE8(s32 arg0, s32 arg1);
extern s32 fn_801AF6CC(CStruct * arg0);
bool fn_801A6B80(Unk_93C2DF4D *arg0) {
    CStruct *temp_r28;
    u32 temp_r29;
    s32 var_r30;
    u32 var_r31;

    var_r30 = 0;
    temp_r28 = fn_801259C8(QB_LEVELS_WITH_GAPS, 1);
    temp_r29 = *((u32 *)&temp_r28->unk0x4);
    for (var_r30 = 0; var_r30 <= 20U; var_r30++) {
        for (var_r31 = 0U; var_r31 < temp_r29; var_r31++) {
            if (var_r30 == fn_80125A3C(GetChecksum(temp_r28, var_r31), 1)) {
                break;
            }
        }
        if (var_r31 != temp_r29) {
            var_r31 = fn_801A6B64(arg0, var_r30);
            if (fn_801A6CE8(arg0, var_r30) == 0) {
                return false;
            }
            if (fn_801AF6CC(var_r31) == 0) {
                return false;
            }
        }
    }
    return true;
}
