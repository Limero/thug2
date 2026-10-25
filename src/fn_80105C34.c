// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80105C34-0x80105C74 (64B). Byte-identical.
#include "types.h"
#include "mem.h"
void fn_80106184(void *);
void fn_80105C34(s32 arg0, s32 arg1) {
    fn_80106184(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
