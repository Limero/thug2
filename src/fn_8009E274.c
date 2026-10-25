// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E274-0x8009E2AC (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void SetChecksumTag(Unk_C7387A53 *, s32, s32);
void fn_8009E274(Unk_31DE137E *arg0, s32 arg1) {
    arg0->unk0x1C = arg1;
    SetChecksumTag(arg0, QB_TYPE, arg1);
}
