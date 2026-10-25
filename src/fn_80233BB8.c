// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233BB8-0x80233C68 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38;
extern s32 lbl_80305FF8;
extern char lbl_802B0928[];
extern char lbl_802B0930[];
s32 fn_800A398C(s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80127848(CStruct *, void *, u32);
s32 fn_80125A08(char *, s32);
void fn_800A1AE8(s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_80233328(s32);
bool ScriptSwitchToParkEditorCamera(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;
    s32 temp_r31;

    if (fn_800A398C(lbl_80301A38, QB_PARKED_CAM) == 0) {
        fn_80127848((temp_r31 = CStruct_ctor(CStruct_new(8))), lbl_802B0928,
                    QB_PARKED_CAM);
        temp_r30 = lbl_80301A38;
        fn_800A1AE8(temp_r30, fn_80125A08(lbl_802B0930, 0), temp_r31, 1);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    fn_80233328(lbl_80305FF8);
    return true;
}
