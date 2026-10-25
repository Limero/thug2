// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802353D0-0x80235438 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_8022D284(s32, s32);
void Mem_Free_3(s32);
void fn_802353D0(CStruct *arg0, s32 arg1) {
    if ((s32) arg0->unk0x7C != 0) {
        Mem_Free_3(arg0->unk0x7C);
        arg0->unk0x7C = 0;
    }
    if ((s32) arg0->unk0x0 != 0) {
        fn_8022D284(arg0->unk0x0, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
