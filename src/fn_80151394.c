// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80151394-0x801513D4 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80301B40;
s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
void fn_800F1EF0(void * arg0, s32 arg1);
bool ScriptNodeArrayManUnload(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetString(pParams, 0, &sp8, 1);
    fn_800F1EF0(lbl_80301B40, sp8);
    return true;
}
