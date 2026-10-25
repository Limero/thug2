// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019C7D4-0x8019C834 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801745B4(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
struct cat_numanims { char _pad[0x1C0]; s32 numAnims; };
bool ScriptCAT_SetNumAnims(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    struct cat_numanims *temp_r3;

    if ((temp_r3 = (struct cat_numanims *)fn_801745B4(lbl_80305EAC)) != NULL) {
        GetInteger(pParams, 0, &sp8, 1);
        temp_r3->numAnims = sp8;
        return true;
    }
    return false;
}
