// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019CCAC-0x8019CD04 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern char lbl_802AACC8[];
s32 fn_801745B4(s32);
void fn_80127798(CStruct *, void *, f32);
s32 ScriptCAT_GetHoldTime(s32 arg0, CScript *arg1) {
    s32 var_r3;
    CScript *temp_r3;

    if ((temp_r3 = fn_801745B4(lbl_80305EAC)) == 0) {
        var_r3 = 0;
    } else {
        fn_80127798(arg1->unk0x18, (s32)lbl_802AACC8, temp_r3->unk0x1D4);
        var_r3 = 1;
    }
    return var_r3;
}
