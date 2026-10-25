// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5390-0x800A5418 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800A6A0C(CStruct *, s32 *, s32);
void fn_800A6910(CStruct *, s32 *);
s32 fn_800A68BC(s32, s32, s32);
void fn_800A5390(Unk_C7387A53 *arg0, s32 arg1, Unk_C7387A53 *arg2) {
    s32 sp8;
    s32 temp_r9;
    Unk_C7387A53 *temp_r3;

    sp8 = arg1;
    temp_r3 = fn_800A68BC(arg0->unk0xC, &sp8, 1);
    if (temp_r3 != NULL) {
        temp_r9 = temp_r3->unk0x44;
        if (temp_r9 > 0) {
            temp_r3->unk0x44 = (s32) (temp_r9 - 1);
        }
        fn_800A6910(arg0->unk0xC, &sp8);
    }
    arg2->unk0x44 = (s32) (arg2->unk0x44 + 1);
    fn_800A6A0C(arg0->unk0xC, &sp8, arg2);
}
