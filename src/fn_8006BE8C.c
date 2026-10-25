// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006BE8C-0x8006BF04 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80294C08[];
void fn_8006BE8C(CStruct *arg0, s32 arg1) {
    arg0->unk0x28 = (s32)lbl_80294C08;
    if ((s32) arg0->unk0x0 != 0) {
        Mem_Free2(arg0->unk0x0);
    }
    if ((s32) arg0->unk0x4 != 0) {
        Mem_Free2(arg0->unk0x4);
    }
    if ((s32) arg0->unk0xC != 0) {
        Mem_Free2(arg0->unk0xC);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}