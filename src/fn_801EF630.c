// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EF630-0x801EF66C (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801EF630(Unk_31DE137E *arg0) {
    arg0->unk0x1C = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATE);
}
