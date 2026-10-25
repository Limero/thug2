// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80232CDC-0x80232D14 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80232CDC(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        arg0->unk0x4C = (s32) (arg0->unk0x4C | (1 << arg1));
        return;
    }
    arg0->unk0x4C = (s32) (arg0->unk0x4C & ~(1 << arg1));
}
