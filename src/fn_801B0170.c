// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0170-0x801B01C0 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ABD94[];
s32 Mem_NewZero(s32);
void fn_801B0240(Unk_9994C3F5 *, s32, s32, s32);
void *fn_801B0170(CStruct *arg0) {
    arg0->unk0x4 = Mem_NewZero(5);
    fn_801B0240(arg0, (s32)lbl_802ABD94, 0x3E8, 0);
    return arg0;
}
