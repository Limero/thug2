// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CE8A8-0x801CE8E8 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
bool fn_801CE8A8(Unk_71062261 *arg0, CStruct *arg1) {
    arg0->unk0x400 = ContainsFlag(arg1, QB_ON);
    return true;
}
