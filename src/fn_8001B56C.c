// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001B56C-0x8001B5B8 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80290E38[];
void fn_80119578();
void fn_8001B56C(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_80290E38;
    fn_80119578();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
