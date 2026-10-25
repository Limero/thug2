// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010124-0x800101A0 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_8030018C;
extern s32 lbl_80313490;
extern char lbl_803C993C[];
extern char lbl_802905DC[];
s32 fn_8000F95C(Unk_FFAD6788 *, void *, void *, void *);
s32 fn_80010910(s32, s32, s32);
s32 fn_80009A04(s32, s32);
void fn_80010124(Unk_31DE137E *arg0) {
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r5;

    temp_r3_2 = fn_80009A04(0x1C, (s32)lbl_803C993C);
    temp_r5 = lbl_80313490;
    temp_r3 = fn_80010910(temp_r3_2, (temp_r5 + 0xF) & QB_UNKNOWN_0xFFFFFFF0, (temp_r5 + lbl_8030018C) & QB_UNKNOWN_0xFFFFFFF0);
    arg0->unk0x174 = temp_r3;
    arg0->unk0x178 = fn_8000F95C(arg0, temp_r3, 1, (s32)lbl_802905DC);
}
