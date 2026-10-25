// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165600-0x80165634 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A83F8[];
void fn_80165600(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_802A83F8;
    if (arg1 & 1) {
        Mem_Free();
    }
}
