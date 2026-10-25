// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019CED4-0x8019CF2C (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern char lbl_802AACF8[];
s32 fn_801745B4(s32);
s32 fn_801276E8(CStruct *, void *, s32);
struct cat_totalz { char _pad[0x1E0]; s32 totalZ; };
bool ScriptCAT_GetTotalZ(void *arg0, CScript *arg1) {
    struct cat_totalz *temp_r3;

    if ((temp_r3 = (struct cat_totalz *)fn_801745B4(lbl_80305EAC)) != NULL) {
        fn_801276E8(arg1->unk0x18, (s32)lbl_802AACF8, temp_r3->totalZ);
        return true;
    }
    return false;
}
