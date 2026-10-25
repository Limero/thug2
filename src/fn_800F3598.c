// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3598-0x800F3610 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800F3684(void *, s32);
extern char lbl_8029B488[];
extern char lbl_8029B548[];
void *fn_800F3598(Unk_A9157FE7 *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    arg0->unk0x50 = (s32)lbl_8029B488;
    temp_r9 = (Unk_C8FEE62D *)((char *)arg0 + 0x38);
    temp_r9->unk0x14 = (s32)lbl_8029B548;
    temp_r9->unk0x4 = -1;
    *(Unk_C8FEE62D **)&temp_r9->unk0xC = temp_r9;
    *(Unk_C8FEE62D **)&temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0x8 = 0;
    *((s32 *)&arg0->unk0x34) = 0;
    arg0->unk0x8 = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x24 = 0;
    *((s32 *)&arg0->unk0x28) = 0;
    fn_800F3684(arg0, arg1);
    return arg0;
}
