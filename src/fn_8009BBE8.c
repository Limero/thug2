// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009BBE8-0x8009BC14 (44B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009BBE8(CStruct *arg0) {
    if (((s32) arg0->unk0x34 == 0) || ((s32) arg0->unk0x44 != 0)) {
        arg0->unk0x4 = (s32) ((arg0->unk0x4 & QB_UNKNOWN_0xFFFFFFFD) | 4);
    }
}
