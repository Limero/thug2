// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B01C0-0x801B0204 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_801B01C0(CStruct *arg0, s32 arg1) {
    Mem_Free(arg0->unk0x4);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
