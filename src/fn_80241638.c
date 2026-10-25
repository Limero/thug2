// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80241638-0x802416A0 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
extern char lbl_802B11E8[];
void *fn_80241638(CStruct *arg0) {
    arg0->unk0x38 = (s32)lbl_802B11E8;
    fn_80240B0C(arg0, 0, 0, 0, 0, 0, 0);
    arg0->unk0x8 = 0;
    arg0->unk0x28 = 0;
    arg0->unk0x2C = 0;
    arg0->unk0x30 = 0;
    return arg0;
}
