// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B3C0-0x8005B420 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802935C0[];
void fn_8005B3C0(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_802935C0;
    if ((s32) arg0->unk0x10 != 0) {
        Mem_Free2(*((void * *)&arg0->unk0x10));
        arg0->unk0x10 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
