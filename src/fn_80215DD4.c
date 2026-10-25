// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80215DD4-0x80215E14 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
bool fn_80215DD4(Unk_298A0A9D *arg0, CStruct *arg1) {
    arg0->unk0x7C4 = ContainsFlag(arg1, QB_ON);
    return true;
}
