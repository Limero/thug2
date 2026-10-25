// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146914-0x80146960 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FD98[];
static void fn_80124C88(void);
void fn_80146914(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FD98;
    fn_80124C88();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
