// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802213D0-0x80221440 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_802195B4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 lbl_80305F9C;
bool ScriptSetJoinMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;

    sp8 = 0;
    temp_r31 = lbl_80305F9C;
    GetInteger(pParams, 0, &sp8, 0);
    if (sp8 == 0) {
        fn_802195B4(temp_r31, 0);
    } else {
        fn_802195B4(temp_r31, 1);
    }
    return true;
}
