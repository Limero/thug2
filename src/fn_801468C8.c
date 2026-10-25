// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801468C8-0x80146914 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FDB0[];
static void fn_800A4EE0(void);
void fn_801468C8(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FDB0;
    fn_800A4EE0();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
