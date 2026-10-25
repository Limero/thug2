// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801773F4-0x80177428 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A8E60[];
void fn_801773F4(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_802A8E60;
    if (arg1 & 1) {
        Mem_Free();
    }
}
