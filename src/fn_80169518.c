// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80169518-0x8016956C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305E84;
extern s32 lbl_80305E88;
extern void CStruct_delete(CStruct * arg0, s32 arg1);
bool ScriptClearMemCardDataForUpload(CStruct *pParams, CScript *pScript) {
    if (lbl_80305E84 != 0) {
        CStruct_delete(lbl_80305E84, 3);
        lbl_80305E84 = 0;
    }
    lbl_80305E88 = 0;
    return true;
}
