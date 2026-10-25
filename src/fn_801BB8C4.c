// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB8C4-0x801BB910 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802AC518[];
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_801BB8C4(Unk_FD1A491C *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_802AC518;
    Mem_Free(arg0->unk0x178);
    fn_8009F558(arg0, arg1);
}
