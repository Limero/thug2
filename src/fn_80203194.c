// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80203194-0x802031E4 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"

void CStruct_delete(CStruct *, s32);
void fn_80203194(s32 *arg0, s32 arg1) {
    if (*arg0) {
        CStruct_delete((s32 *)*arg0, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
