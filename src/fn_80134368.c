// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134368-0x801343B4 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void Mem_Free_3(void *);
void fn_801348BC(void *);
void fn_80134368(Unk_9994C3F5 *arg0, s32 arg1) {
    if ((s32) arg0->unk0x8 != 0) {
        Mem_Free_3(arg0->unk0x8);
    }
    if (arg1 & 1) {
        fn_801348BC(arg0);
    }
}
