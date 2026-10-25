// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019899C-0x801989CC (48B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddChecksum(CStruct *, s32, s32);
void fn_8019899C(s32 arg0, s32 arg1) {
    AddChecksum(arg0 + 4, QB_GOALS, arg1);
}
