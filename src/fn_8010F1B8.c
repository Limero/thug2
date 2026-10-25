// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010F1B8-0x8010F20C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_8029CEA0[];
extern s32 GetText(CStruct *, void *, void *, s32);
extern void fn_80055784(s32, s32);

bool ScriptScreenShot(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    if (GetText(pParams, QB_FILENAME, &sp8, 0) == 0) {
        sp8 = (s32)lbl_8029CEA0;
    }
    fn_80055784(sp8, 0);
    return true;
}
