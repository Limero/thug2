// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234EBC-0x80234F04 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80128170(CStruct *, void *, void *, s32);
s32 fn_80238964(void);
void fn_80235D1C(void *, s32);
extern char lbl_802B0928[];
bool ScriptSetCustomParkName(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    fn_80128170(pParams, (s32)lbl_802B0928, &sp8, 1);
    fn_80235D1C(fn_80238964(), sp8);
    return true;
}
