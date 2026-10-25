// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062988-0x800629D4 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_80062AD4();
extern char lbl_80293FD0[];
extern char lbl_80293FD0[];
void fn_80062988(Unk_FFAD6788 *arg0, s32 arg1) {
    arg0->unk0xBC = (s32)lbl_80293FD0;
    fn_80062AD4();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}