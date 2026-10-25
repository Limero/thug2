// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802416A0-0x802416F8 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802B11E8[];
void fn_802416A0(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0x38 = (s32)lbl_802B11E8;
    if ((s32) arg0->unk0x28 != 0) {
        Mem_Free(arg0->unk0x28);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
