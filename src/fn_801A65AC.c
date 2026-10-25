// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A65AC-0x801A65EC (64B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_801A6554(CStruct *);
void fn_801A65AC(CStruct *arg0, s32 arg1) {
    fn_801A6554(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
