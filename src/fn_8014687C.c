// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014687C-0x801468C8 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FDC8[];
static void fn_8000DB60(void);
void fn_8014687C(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FDC8;
    fn_8000DB60();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
