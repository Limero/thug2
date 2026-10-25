// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801552DC-0x801553CC (240B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern Unk_C7387A53 * lbl_80305DEC;
extern char lbl_80305EAC[];

s32 fn_8016D1A8(void);
void fn_8016CFE4(u32 v);
void fn_8014DB40(s32, s32, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_801419CC(Unk_C7387A53 *, s32);
s32 fn_8016D008(void *, CStruct *);
void fn_80129570(s32, s32);
void fn_8016C9B8(Unk_C7387A53 *, Unk_1ECA8143 *);

bool ScriptSetViewerModel(Unk_1ECA8143 *arg0) {
    s32 temp_r31;
    s32 var_r30;
    s32 temp_r3;

    temp_r31 = fn_8016D1A8();
    lbl_80305DEC = 1;
    fn_8016CFE4(1);
    if (lbl_80305DEC == 0) {
        fn_8014DB40(QB_SKATERCAM0, 0, 0);
    } else {
        fn_8014DB40(QB_VIEWER_CAM, 0, 1);
    }
    var_r30 = 0;
    do {
        temp_r3 = fn_801746A4(*(s32 *)&lbl_80305EAC, var_r30);
        if (temp_r3 != 0) {
            fn_801419CC(temp_r3, lbl_80305DEC);
        }
        var_r30 += 1;
    } while (var_r30 <= 7);
    if (temp_r31 != 0) {
        fn_8016D008(temp_r31, arg0);
        fn_80129570(arg0, 0);
        fn_8016C9B8(temp_r31, arg0);
    }
    return true;
}
