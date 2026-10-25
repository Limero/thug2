// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F05C0-0x800F0610 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetArray(CStruct *, s32, s32 *, s32);
void GetChecksum(CStruct *, s32);
void fn_800F05C0(CStruct *arg0, s32 arg1) {
    s32 sp8;

    sp8 = 0;
    GetArray(arg0, QB_LINKS, &sp8, 0);
    GetChecksum(sp8, arg1);
}
