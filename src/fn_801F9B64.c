// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9B64-0x801F9B90 (44B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_801F9B64(Unk_C7387A53 *arg0, s32 count) {
    register void *p asm("r3");
    p = *((void * *)&arg0->unk0xC);
    if (count != 0 && p != NULL) {
        do {
            p = *((void * *)&((Unk_C7387A53 *)p)->unk0x24);
            count--;
        } while (count != 0 && p != NULL);
    }
}
