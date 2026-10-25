// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018F430-0x8018F4A4 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_8018F430(Unk_C7387A53 *arg0) {
    s32 sp8;

    sp8 = 0;
    GetInteger(arg0->unk0x20, QB_UNLIMITED_TIME, &sp8, 0);
    if (ContainsFlag(arg0->unk0x20, QB_UNLIMITED_TIME) != 0) {
        sp8 = 1;
    }
    return sp8 == 0 ? 1 : 0;
}
