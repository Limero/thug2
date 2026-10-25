// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010646C-0x801064C8 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void Mem_Free_3(s32);
void fn_8010646C(Unk_C7387A53 *arg0, s32 arg1) {
    if ((s32) arg0->unk0x28 != 0) {
        Mem_Free2(arg0->unk0x28);
    }
    if ((s32) arg0->unk0x2C != 0) {
        Mem_Free_3(arg0->unk0x2C);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}