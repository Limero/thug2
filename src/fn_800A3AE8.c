// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3AE8-0x800A3B44 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void CStruct_delete(CStruct *, s32);
void fn_800A3AE8(CStruct *arg0, s32 arg1) {
    if ((arg0->unk0xC & 4) != 0 && (s32) arg0->unk0x10 != 0) {
        CStruct_delete(arg0->unk0x10, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
