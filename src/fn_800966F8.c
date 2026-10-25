// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800966F8-0x80096758 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "structs.h"
#include "mem.h"
extern s32 lbl_803018A8;
void fn_80098B7C(s32, s32 *, void *);
void fn_800966F8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp8;
    s32 a;
    CStruct *temp_r3;

    temp_r3 = Mem_Alloc2(0x9C);
    a = lbl_803018A8;
    temp_r3->unk0x4 = arg1;
    temp_r3->unk0x8 = arg2;
    sp8 = arg0;
    temp_r3->unk0x0 = arg0;
    fn_80098B7C(a, &sp8, temp_r3);
}
