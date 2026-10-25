// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7F38-0x800A7F80 (72B). Byte-identical.
#include "types.h"
#include "mem.h"
extern s32 lbl_80301A80;
s32 fn_800A7F38(void) {
    if (lbl_80301A80 == 0) {
        Mem_Alloc2(0x10);
        lbl_80301A80 = fn_800A7F80();
    }
    return lbl_80301A80;
}
