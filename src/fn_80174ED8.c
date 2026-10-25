// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80174ED8-0x80174F88 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EA4;
extern char lbl_80305F1C[];
extern char lbl_80305F9C[];
extern void fn_80174814(Unk_40426380 * arg0);
extern void ScriptParseNodeArray(s32 arg0, s32 arg1);
extern void fn_801A97C4(Unk_C7387A53 * arg0);
extern s32 Game_GetGoalManager(void);
extern s32 fn_8009CF2C(CStruct * arg0);
extern void fn_80185F9C(Unk_C8FEE62D * arg0);
extern void fn_80184628(s32 arg0);
extern void fn_80187838(Unk_9994C3F5 * arg0);
extern void fn_80171844(CStruct * arg0);
extern void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_80174ED8(Unk_C7387A53 *arg0) {
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_a97;

    temp_r29 = *(s32 *)&lbl_80305F9C;
    fn_80174814(arg0);
    ScriptParseNodeArray(0, 0);
    temp_a97 = *(s32 *)&lbl_80305F1C;
    arg0->unk0x54 = 0;
    fn_801A97C4(temp_a97);
    temp_r30 = Game_GetGoalManager();
    if (fn_8009CF2C(temp_r29) != 0) {
        fn_80185F9C(temp_r30);
    } else {
        fn_80184628(temp_r30);
    }
    fn_80187838(temp_r30);
    fn_80171844(lbl_80305EA4);
    Script_RunScript(QB_RESET_LEVEL, 0, 0, 0, 0);
}
