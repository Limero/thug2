// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146E20-0x80146E6C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800F1554(void);
extern char lbl_8029FBB8[];
void fn_80146E20(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FBB8;
    fn_800F1554();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
