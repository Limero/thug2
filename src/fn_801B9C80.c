// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9C80-0x801B9CE0 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
bool fn_801B9C80(s32 arg0, CStruct *arg1) {
    GetFloat(arg1, QB_DISTABOVE, arg0 + 0xDC, 0);
    GetFloat(arg1, QB_DISTBELOW, arg0 + 0xE0, 0);
    return true;
}
