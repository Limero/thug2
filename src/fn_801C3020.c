// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C3020-0x801C30FC (220B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 Mem_NewZero(s32);
void *fn_801AEF14(Unk_C8FEE62D *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 fn_80009314(CStruct *, void *);

register s32 g31 __asm__("r31");

void fn_801C3020(Unk_C7387A53 *arg0, CStruct *arg1, Unk_FFAD6788 *arg2) {
    s32 sp8;
    s32 spC;
    CStruct *temp_r3;
    Unk_C7387A53 *temp_r11;
    s32 temp_r9;
    s32 var_r29;

    temp_r3 = fn_801AEF14(Mem_NewZero(0x3C));
    var_r29 = 0;
    temp_r11 = (char *)arg0 + 0x34;
    temp_r3->unk0x10 = temp_r11;
    temp_r3->unk0xC = temp_r11->unk0xC;
    *(s32 *)(temp_r11->unk0xC + (s32)0x10) = temp_r3;
    temp_r11->unk0xC = temp_r3;
    temp_r9 = arg2->unk0xB8;
    temp_r3->unk0x34 = var_r29;
    temp_r3->unk0x2C = temp_r9;
    temp_r3->unk0x38 = arg0->unk0x4C;
    sp8 = var_r29;
    GetChecksum_2(arg1, QB_GAPID, &sp8, 0);
    temp_r3->unk0x28 = sp8;
    spC = var_r29;
    GetString(arg1, QB_TRICKTEXT, &spC, 0);
    fn_80009314((s32)((char *)temp_r3 + 0x18), spC);
    temp_r3->unk0x30 = var_r29;
    GetChecksum_2(arg1, QB_TRICKSCRIPT, (char *)temp_r3 + 0x30, 1);
}
