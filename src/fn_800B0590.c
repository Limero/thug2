// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B0590-0x800B05E0 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_80301B08;
s32 fn_800B0BAC(Unk_DB0E2BAB *, s32);
void fn_800B0590(void) {
    if (lbl_80301B08 != 0) {
        fn_800B05E0();
        return;
    }
    lbl_80301B08 = fn_800B0BAC(Mem_Alloc2(0x18), 4);
}
