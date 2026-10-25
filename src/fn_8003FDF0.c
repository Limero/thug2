// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FDF0-0x8003FE18 (40B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8003FDF0(Unk_C7387A53 *arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->unk0xC = (s32) (arg0->unk0xC | 0x20000);
        return;
    }
    arg0->unk0xC = (s32) (arg0->unk0xC & QB_UNKNOWN_0xFFF9FFFF);
}
