// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154138-0x801541A0 (104B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_80305F9C[];

s32 fn_8022BD14(CScript *);
void fn_8022BD0C(CScript *, s32);
void fn_8022BC98(Unk_C5BAE83F *, s32);

bool ScriptStartLobbyList(CStruct *pParams, CScript *pScript) {
    s32 temp_r31;

    temp_r31 = *(s32 *)&lbl_80305F9C;
    if (fn_8022BD14(temp_r31) == 2) {
        fn_8022BD0C(temp_r31, 0xD);
        fn_8022BC98(temp_r31, 1);
    } else {
        fn_8022BC98(temp_r31, 0xD);
    }
    return true;
}
