// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A4F5C-0x800A500C (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800A4C28(Unk_451C91CE *, void *, s32, s32, s32, s32, s32);
void fn_800A6A0C(CStruct *, s32 *, s32);
void fn_800A6910(CStruct *, s32 *);
s32 fn_800A68BC(s32, s32, s32);
void fn_800A4F5C(CStruct *arg0, CScript *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r9;
    Unk_C7387A53 *temp_r3;

    sp8 = arg1->unk0x18;
    temp_r3 = fn_800A68BC(arg0->unk0xC, &sp8, 1);
    if (temp_r3 != NULL) {
        temp_r9 = temp_r3->unk0x44;
        if (temp_r9 > 0) {
            temp_r3->unk0x44 = (s32) (temp_r9 - 1);
        }
        spC = arg1->unk0x18;
        fn_800A6910(arg0->unk0xC, &spC);
    }
    sp10 = arg1->unk0x18;
    fn_800A6A0C(arg0->unk0x8, &sp10, arg1);
    fn_800A4C28((char *)arg0 + 0x20, 0, arg1->unk0x18, QB_SYSTEM, 0, 0, 4);
}
