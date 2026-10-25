// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146BC0-0x80146C0C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FC78[];
static void fn_8019804C(void);
void fn_80146BC0(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FC78;
    fn_8019804C();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
