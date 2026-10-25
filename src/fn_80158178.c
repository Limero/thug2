// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158178-0x80158210 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801A5DAC(s32, s32);
s32 fn_801A4540(s32, CStruct *);

bool ScriptResetAllToDefaultProfile(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    CStruct *arr;
    s32 item;
    u32 var_r31;

    var_r31 = 0U;
    arr = fn_801259C8(QB_MASTER_SKATER_LIST, 1);
    while (var_r31 < *((u32 *)&arr->unk0x4)) {
        item = fn_80129528(arr, var_r31);
        var_r31 += 1;
        GetChecksum_2(item, QB_NAME, &sp8, 1);
        fn_801A4540(fn_801A5DAC(lbl_80305EFC, sp8), item);
    }
    return true;
}
