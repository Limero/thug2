// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C2398-0x801C23E8 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801C2870(CStruct *, s32 *, s32 *);
void fn_801C23E8(Unk_C7387A53 *, s32, s32);
void fn_801C2398(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 spC;

    arg0->unk0x4C = arg0->unk0x4C + 1;
    fn_801C2870(arg0, &sp8, &spC);
    fn_801C23E8(arg0, sp8, spC);
}
