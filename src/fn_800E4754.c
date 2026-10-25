// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E4754-0x800E4790 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_800E4754(Unk_31DE137E *arg0) {
    arg0->unk0x1C = GetChecksum_3(arg0->unk0xC, QB_SUSPEND);
}
