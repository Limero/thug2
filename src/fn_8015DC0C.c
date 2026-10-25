// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015DC0C-0x8015DCB4 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_801403CC(void * arg0);
extern s32 fn_80180204(Unk_F515CE8D * arg0, s32 arg1);
bool ScriptResetScorePot(CStruct *pParams, CScript *pScript) {
    s32 temp_r29;
    s32 temp_r30;
    Unk_C7387A53 *temp_r28;
    u32 var_r31;
    u32 var_r11;
    CStruct *var_r9;

    temp_r30 = lbl_80305EAC;
    var_r31 = 0U;
    temp_r29 = ContainsFlag(pParams, QB_USEBAILSTYLE);
    temp_r28 = (char *)temp_r30 + 0x2C;
loop_1:
    var_r9 = temp_r28->unk0xC;
    var_r11 = 0U;
    goto loop_3;
loop_step:
    var_r9 = var_r9->unk0xC;
    var_r11 += 1;
loop_3:
    if ((s32)var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    if (var_r9 != NULL) {
        goto loop_step;
    }
    if (var_r31 < var_r11) {
        s32 entry = fn_801746A4(temp_r30, var_r31);
        if (((Unk_FFAD6788 *)entry)->unk0xC8 != 0) {
            fn_80180204(fn_801403CC(entry), temp_r29 ^ 1);
        }
        var_r31 += 1;
        goto loop_1;
    }
    return true;
}
