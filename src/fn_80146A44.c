// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146A44-0x80146A90 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FD08[];
static void fn_801342D0(void);
void fn_80146A44(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FD08;
    fn_801342D0();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
