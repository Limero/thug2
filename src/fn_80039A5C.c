// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80039A5C-0x80039AD4 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80291F40[];
void fn_80039A5C(Unk_7BF09EDD *arg0, s32 arg1) {
    arg0->unk0x598 = (s32)lbl_80291F40;
    if ((s32) arg0->unk0x58C != 0) {
        Mem_Free2(arg0->unk0x58C);
        arg0->unk0x58C = 0;
    }
    if ((s32) arg0->unk0x590 != 0) {
        Mem_Free2(arg0->unk0x590);
        arg0->unk0x590 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}