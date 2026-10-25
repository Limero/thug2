// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A4BD4-0x800A4C28 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800A670C(CStruct *, s32);
void fn_800A4BD4(Unk_451C91CE *arg0, s32 arg1) {
    if ((s32) arg0->unk0xB008 != 0) {
        fn_800A670C(arg0->unk0xB008, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
