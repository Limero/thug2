// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010EFA0-0x8010EFE4 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800A2A24(Unk_C8FEE62D *);
void GetInteger(CStruct *, s32, s32 *, s32);
// ScriptResizeCOIMHeap @ 0x8010EFA0
bool ScriptResizeCOIMHeap(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, QB_NEWSIZE, &sp8, 1);
    fn_800A2A24(sp8);
    return true;
}
