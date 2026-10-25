// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800367B4-0x80036810 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800367B4(Unk_C8FEE62D *arg0, s32 arg1) {
    if ((s32) arg0->unk0x18 != 0) {
        Mem_Free2(arg0->unk0x18);
    }
    if ((s32) arg0->unk0x4 != 0) {
        Mem_Free2(arg0->unk0x4);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}