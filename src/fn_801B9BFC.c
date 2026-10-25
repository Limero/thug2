// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9BFC-0x801B9C5C (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801B301C(Unk_C7387A53 *, s32, Unk_C8FEE62D *);
bool fn_801B9BFC(Unk_C7387A53 *arg0) {
    if (arg0->unk0x24 & 0x1000) {
        fn_801B301C((s32)arg0, QB_PED_SKATER_START_MOVING, 0);
        arg0->unk0x24 = (s32) (arg0->unk0x24 & QB_UNKNOWN_0xFFFFEFFF);
    }
    arg0->unk0x24 = (s32) (arg0->unk0x24 | 2);
    return true;
}
