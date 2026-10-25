// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F4EAC-0x800F4EEC (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void Mem_Free_3(s32);
void fn_800F4EAC(Unk_C7387A53 *arg0) {
    if ((s32) arg0->unk0x24 != 0) {
        Mem_Free_3(arg0->unk0x24);
        arg0->unk0x24 = 0;
    }
}
