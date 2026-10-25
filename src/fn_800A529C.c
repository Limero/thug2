// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A529C-0x800A5308 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800A4BD4(Unk_451C91CE *, s32);
void fn_800A6D54(CStruct *, s32);
extern char lbl_802980B0[];
void fn_800A529C(Unk_AD65BA9A *arg0, s32 arg1) {
    arg0->unk0xB21C = (s32)lbl_802980B0;
    if ((s32) arg0->unk0x8 != 0) {
        fn_800A6D54(arg0->unk0x8, 3);
    }
    fn_800A4BD4((char *)arg0 + 0x20, 2);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
