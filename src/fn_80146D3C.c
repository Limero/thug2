// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146D3C-0x80146D88 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80215EC4(void);
extern char lbl_8029FC00[];
void fn_80146D3C(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FC00;
    fn_80215EC4();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
