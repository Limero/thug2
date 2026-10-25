// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801063B4-0x801063FC (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80381098[];
extern char lbl_8029C1F8[];
void fn_801063B4(s32 arg0, s32 arg1) {
    Unk_4C649A8C *p;
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        p = lbl_80381098;
        p->unk0x14 = (s32)lbl_8029C1F8;
        p->unk0x4 = -1;
        p->unk0x8 = 0;
        p->unk0x10 = (s32)p;
        ((Unk_41EA2015 *)p)->unk0xC = (s32)p;
    }
}
