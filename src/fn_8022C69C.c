// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022C69C-0x8022C6D0 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B03E0[];
void fn_8022C69C(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_802B03E0;
    if (arg1 & 1) {
        Mem_Free();
    }
}
