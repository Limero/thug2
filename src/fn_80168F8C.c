// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80168F8C-0x80169070 (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, void *);
extern s32 lbl_80305E8C;
bool ScriptSetSectionsToApplyWhenLoading(CStruct *pParams, CScript *pScript) {
    lbl_80305E8C = 0;
    if (ContainsFlag(pParams, QB_APPLYCUSTOMSKATER) != 0) {
        lbl_80305E8C |= 8;
    }
    if (ContainsFlag(pParams, QB_APPLYSTORYSKATER) != 0) {
        lbl_80305E8C |= 4;
    }
    if (ContainsFlag(pParams, QB_APPLYSTORY) != 0) {
        lbl_80305E8C |= 2;
    }
    if (ContainsFlag(pParams, QB_APPLYGENERALOPTIONS) != 0) {
        lbl_80305E8C |= 1;
    }
    if (ContainsFlag(pParams, QB_ALL) != 0) {
        lbl_80305E8C = -1;
    }
    return true;
}
