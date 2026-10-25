// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FF18-0x8009FF50 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetVector(CStruct *, s32, CStruct *, s32);
bool fn_8009FF18(s32 arg0, CStruct *arg1) {
    GetVector(arg1, QB_POSITION, arg0 + 0x58, 0);
    return true;
}
