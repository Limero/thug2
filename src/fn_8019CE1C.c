// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019CE1C-0x8019CE74 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern char lbl_802AACE8[];
s32 fn_801745B4(s32);
s32 fn_801276E8(CStruct *, void *, s32);
struct cat_totalx { char _pad[0x1D8]; s32 totalX; };
bool ScriptCAT_GetTotalX(void *arg0, CScript *arg1) {
    struct cat_totalx *temp_r3;

    if ((temp_r3 = (struct cat_totalx *)fn_801745B4(lbl_80305EAC)) != NULL) {
        fn_801276E8(arg1->unk0x18, (s32)lbl_802AACE8, temp_r3->totalX);
        return true;
    }
    return false;
}
