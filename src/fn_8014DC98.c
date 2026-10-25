// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014DC98-0x8014DD04 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_802A7BD8[];
extern s32 fn_80174A58(void * arg0, CStruct * arg1);
extern s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
extern s32 fn_801A5818(s32 arg0, void * arg1);
bool ScriptSetCustomSkaterFilename(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    temp_r30 = fn_80174A58(*(s32 *)&lbl_80305EAC, 0);
    sp8 = (s32)lbl_802A7BD8;
    GetString(pParams, 0, &sp8, 0);
    fn_801A5818(temp_r30, sp8);
    return true;
}
