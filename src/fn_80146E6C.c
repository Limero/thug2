// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146E6C-0x80146EB8 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8016D2E4(void);
extern char lbl_8029FBA0[];
void fn_80146E6C(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FBA0;
    fn_8016D2E4();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
