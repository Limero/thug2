// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80151320-0x80151394 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_803A0010[];
extern void* lbl_80301B48;
s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
void strcpy(char *arg0, char *arg1);
void fn_800F2628(Unk_C7387A53 * arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
bool ScriptNodeArrayManLoad(CStruct *pParams, CScript *pScript) {
    s32 sp10;

    GetString(pParams, 0, &sp10, 1);
    strcpy(lbl_803A0010, (char *)sp10);
    fn_800F2628(lbl_80301B48, sp10, 0xB, 0, 0, 0, 0, 0, 0, 0);
    return true;
}
