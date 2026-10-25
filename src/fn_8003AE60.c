// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003AE60-0x8003AEA0 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8003AE60(Unk_31DE137E *arg0) {
    if ((s32) arg0->unk0x60 != 0) {
        Mem_Free(arg0->unk0x60);
        arg0->unk0x60 = 0;
    }
}
