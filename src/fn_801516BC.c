// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801516BC-0x80151784 (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305DEC;
extern s32 lbl_80305EAC;
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_8016CFE4(s32 arg0);
extern void fn_8014DB40(s32 arg0, s32 arg1, s32 arg2);
extern s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_801419CC(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_8016D1A8(void);
extern void fn_8016CA58(Unk_C7387A53 * arg0);
bool ScriptSetViewMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r3;
    s32 var_r30;

    GetInteger(pParams, 0, &sp8, 1);
    lbl_80305DEC = sp8;
    fn_8016CFE4(sp8);
    if (lbl_80305DEC == 0) {
        fn_8014DB40(QB_SKATERCAM0, 0, 0);
    } else {
        fn_8014DB40(QB_VIEWER_CAM, 0, 1);
    }
    for (var_r30 = 0; var_r30 <= 7; var_r30++) {
        temp_r3 = fn_801746A4(lbl_80305EAC, var_r30);
        if (temp_r3 != 0) {
            fn_801419CC(temp_r3, lbl_80305DEC);
        }
    }
    temp_r3 = fn_8016D1A8();
    if (temp_r3 != 0) {
        fn_8016CA58(temp_r3);
    }
    return true;
}
