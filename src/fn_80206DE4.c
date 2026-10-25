// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206DE4-0x80206E24 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void GetStructure_2(CStruct *, s32, s32 *, s32);

s32 fn_80206DE4(void *a, CStruct *b) {
    s32 out = 0;
    GetStructure_2(b, QB_ALT_TRIGGER, &out, 0);
    return out;
}
