// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233FD0-0x80234018 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80238970(void);
void fn_8022D89C(Unk_C7387A53 *, s32);

// MATCHED @ 0x80233FD0
bool ScriptSetParkEditorMaxPlayers(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_8022D89C((void *)(*(s32 *)fn_80238970()), sp8);
    return true;
}
