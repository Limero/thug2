// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004567C-0x800456D0 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_8005EBE4(void *, u32);
extern s32 lbl_80366474;
void fn_8004567C(Unk_31DE137E *arg0, s32 arg1) {
    s32 temp_r5;
    arg0->unk0x190 = arg1;
    temp_r5 = fn_8005CF80((Unk_9994C3F5 *)lbl_80366474, arg1);
    fn_8005EBE4(arg0->unk0x194,  (u32)temp_r5);
    arg0->unk0xC = (s32) (arg0->unk0xC | 0x1000);
}
