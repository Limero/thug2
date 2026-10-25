// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A33E4-0x800A3470 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "structs.h"
extern char lbl_80301A78[];
void fn_800A500C(CScript *, s32, s32, s32);
void fn_800A33E4(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 var_r0;
    CStruct *temp_r8;
    Unk_C7387A53 *temp_r9;

    fn_800A500C(*(s32 *)&lbl_80301A78, arg1, arg0->unk0x24, arg0->unk0x28);
    temp_r8 = (char *)arg1 + 0x2C;
    var_r0 = 1;
    temp_r9 = temp_r8->unk0x10;
    if (temp_r9 == temp_r8) {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        temp_r9->unk0xC =  temp_r8->unk0xC;
        *(s32 *)(*(s32 *)((char *)((char *)temp_r8) + 0xC) + 0x10) =  temp_r8->unk0x10;
        temp_r8->unk0xC = temp_r8;
        temp_r8->unk0x10 = temp_r8;
        arg1->unk0x10 = 0;
        arg0->unk0x20 = -1;
    }
}
