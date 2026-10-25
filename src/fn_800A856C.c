// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A856C-0x800A85A0 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80298240[];
void fn_800A856C(Unk_FFAD6788 *arg0, s32 arg1) {
    arg0->unk0xF4 = (s32)lbl_80298240;
    if (arg1 & 1) {
        Mem_Free();
    }
}
