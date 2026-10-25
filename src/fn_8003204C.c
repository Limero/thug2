// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003204C-0x80032088 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_8003204C(Unk_C7387A53 *arg0) {
    arg0->unk0x80 = GetChecksum_3(arg0->unk0x78, QB_SKELETON);
}
