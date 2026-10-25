// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B90FC-0x801B9110 (20B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801B90FC(Unk_C7387A53 *arg0) {
    u32 v;

    v = *((u32 *)&arg0->unk0x24);
    v &= QB_UNKNOWN_0xFFFFFFFB;
    v &= QB_UNKNOWN_0xFFFFF9FF;
    *((u32 *)&arg0->unk0x24) = v;
}
