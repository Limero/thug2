// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137C5C-0x80137CB4 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80137C5C(Unk_C7387A53 *arg0, s32 arg1) {
    if (((s32) arg0->unk0x2C != 0) && ((s32) arg0->unk0x40 == 0)) {
        Mem_Free2(arg0->unk0x2C);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
