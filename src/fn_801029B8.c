// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801029B8-0x80102A40 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80103280(Unk_C7387A53 *);
void fn_801029B8(Unk_A6515021 *arg0, s32 arg1) {
    if ((s32) arg0->unk0x3C != 0) {
        Mem_Free2(arg0->unk0x3C);
    }
    if ((s32) arg0->unk0x38 != 0) {
        Mem_Free2(arg0->unk0x38);
    }
    if ((s32) arg0->unk0xC != 0) {
        if ((s32) arg0->unk0xA != 0) {
            Mem_Free2(arg0->unk0xC);
        } else {
            Mem_Free2(arg0->unk0xC);
        }
    }
    fn_80103280(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}