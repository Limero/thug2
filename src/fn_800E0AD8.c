// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E0AD8-0x800E0B14 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_800E0AD8(CStruct *arg0) {
    arg0->unk0x6C = GetChecksum_3(arg0->unk0xC, QB_MODEL);
}
