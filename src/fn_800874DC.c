// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800874DC-0x8008757C (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800121D8(s32);
CStruct *fn_8006EF68(void);
bool fn_800874DC(CStruct *arg0, s32 *arg1, s32 arg2) {
    s32 temp_r9;
    char *temp_r10;
    CStruct *temp_r31;
    CStruct *temp_r3;

    temp_r9 = (*arg1 & ((1 << arg0->unk0x0) - 1)) * 0xC;
    temp_r10 = arg0->unk0x4;
    temp_r31 = (CStruct *)(temp_r10 + temp_r9);
    if ((s32) temp_r31->unk0x4 != 0) {
        fn_800121D8(0);
        temp_r3 = fn_8006EF68();
        temp_r3->unk0x0 = (s32) *arg1;
        temp_r3->unk0x4 = arg2;
        temp_r3->unk0x8 =  temp_r31->unk0x8;
        temp_r31->unk0x8 = temp_r3;
    } else {
        *(s32 *)(temp_r10 + temp_r9) = *arg1;
        temp_r31->unk0x4 = arg2;
    }
    arg0->unk0x8 = (s32) (arg0->unk0x8 + 1);
    return true;
}
