// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801920F0-0x8019210C (28B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801920F0(Unk_C7387A53 *arg0) {
    s32 var_r0;

    var_r0 = arg0->unk0x70;
    arg0->unk0x74 = 0;
    var_r0 = var_r0 & QB_UNKNOWN_0xFF7FFFFF;
    arg0->unk0x70 = var_r0 & QB_UNKNOWN_0xFFDFFFFF;
}
