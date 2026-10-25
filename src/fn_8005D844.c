// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x8005D844-0x8005D8E4 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800121D8(s32);
s32 fn_8005D814(void);
bool fn_8005D844(CStruct *arg0, s32 *arg1, s32 arg2) {
    register s32 arg2_r __asm__("r28");
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r9;
    CStruct *temp_r31;
    CStruct *temp_r3;

    arg2_r = arg2;
    temp_r11 = *arg1;
    temp_r10 = arg0->unk0x4;
    temp_r9 = (temp_r11 & ((1 << arg0->unk0x0) - 1)) * 0xC;
    temp_r31 = (CStruct *)(temp_r10 + temp_r9);
    if (temp_r31->unk0x4 != 0) {
        fn_800121D8(0);
        temp_r3 = (CStruct *)fn_8005D814();
        temp_r3->unk0x0 = *arg1;
        temp_r3->unk0x4 = arg2_r;
        temp_r3->unk0x8 = temp_r31->unk0x8;
        temp_r31->unk0x8 = temp_r3;
    } else {
        *(s32 *)((char *)temp_r10 + temp_r9) = temp_r11;
        temp_r31->unk0x4 = arg2_r;
    }
    arg0->unk0x8 = arg0->unk0x8 + 1;
    return true;
}
