// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019C8FC-0x8019C97C (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern char lbl_802AAC8C[];
s32 fn_801745B4(s32);
void fn_801276E8(CStruct *, void *, s32);
bool ScriptCAT_GetAnimsDone(s32 arg0, CScript *arg1) {
    CScript *temp_r3;

    if ((temp_r3 = fn_801745B4(lbl_80305EAC)) != 0) {
        if (temp_r3->unk0x1CC != 0) {
            fn_801276E8(arg1->unk0x18, (s32)lbl_802AAC8C, 1);
        } else {
            fn_801276E8(arg1->unk0x18, (s32)lbl_802AAC8C, 0);
        }
        return true;
    }
    return false;
}
