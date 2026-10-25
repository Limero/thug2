// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A82DC-0x801A8354 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AB9B0[];
extern char lbl_802AB9C8[];
void fn_801A8548(Unk_C8FEE62D *);
void *fn_801A82DC(Unk_C8FEE62D *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    arg0->unk0x14 = (s32)lbl_802AB9B0;
    arg0->unk0x4 = arg0;
    temp_r9 = (char *)arg0 + 0x48;
    arg0->unk0x8 = 0;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    temp_r9->unk0x14 = (s32)lbl_802AB9C8;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0x8 = 0;
    temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0xC = temp_r9;
    arg0->unk0x18 = arg1;
    fn_801A8548(arg0);
    return arg0;
}
