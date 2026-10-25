// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146B74-0x80146BC0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FC90[];
static void fn_801A8038(void);
void fn_80146B74(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FC90;
    fn_801A8038();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
