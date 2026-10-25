// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146A90-0x80146ADC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FCF0[];
static void fn_800F20D4(void);
void fn_80146A90(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FCF0;
    fn_800F20D4();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
