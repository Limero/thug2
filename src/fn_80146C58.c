// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146C58-0x80146CA4 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FC48[];
static void fn_801B00E0(void);
void fn_80146C58(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FC48;
    fn_801B00E0();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
