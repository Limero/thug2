// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6FE4-0x801F707C (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AE3A0[];
extern s32 fn_801F16A0(CStruct * arg0);
extern s32 fn_801F5A0C(s32 arg0, s32 arg1);
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern void fn_801276E8(CStruct * arg0, void * arg1, s32 arg2);
bool fn_801F6FE4(s32 arg0, CStruct *arg1, CScript *arg2) {
    s32 temp_r3;
    s32 var_r31;

    temp_r3 = fn_801F16A0(arg1);
    var_r31 = fn_801F5A0C(arg0, temp_r3);
    if ((temp_r3 == 0) && (ContainsFlag(arg1, QB_EXCLUDEPARKEDITORGOALS) != 0)) {
        var_r31 -= fn_801F5A0C(arg0, QB_LOAD_SK5ED);
    }
    fn_801276E8(arg2->unk0x18, (s32)lbl_802AE3A0, var_r31);
    return true;
}
