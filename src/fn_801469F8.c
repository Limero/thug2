// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801469F8-0x80146A44 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FD20[];
static void fn_80013B58(void);
void fn_801469F8(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FD20;
    fn_80013B58();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
