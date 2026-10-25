// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234018-0x80234060 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80238970(void);
void fn_801276E8(CStruct *, void *, s32);
extern char lbl_802B098C[];

// MATCHED @ 0x80234018
bool ScriptGetParkEditorMaxPlayers(void *arg0, CScript *arg1) {
    s32 temp_r30;

    temp_r30 = arg1->unk0x18;
    fn_801276E8((void *)temp_r30, (s32)lbl_802B098C,
                *(s32 *)((char *)(*(s32 *)fn_80238970()) + (s32)0x20));
    return true;
}
