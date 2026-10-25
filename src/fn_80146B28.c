// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146B28-0x80146B74 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FCA8[];
static void fn_800A18DC(void);
void fn_80146B28(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FCA8;
    fn_800A18DC();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
