// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023EF88-0x8023EFC8 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8023F6D0(CStruct *);
void fn_8023EF88(CStruct *arg0, s32 arg1) {
    fn_8023F6D0(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
