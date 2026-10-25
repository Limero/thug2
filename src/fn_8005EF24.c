// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EF24-0x8005EF7C (88B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80293C78[];
void fn_8005EF24(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_80293C78;
    if ((s32) arg0->unk0xC != 0) {
        Mem_Free(arg0->unk0xC);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
