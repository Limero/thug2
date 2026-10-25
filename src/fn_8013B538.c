// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013B538-0x8013B5C4 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern u32 Crc_GenerateCRCCaseSensitive(void *, s32);

void fn_8013B538(s32 arg0, u8 *arg1, u16 *arg2, s32 arg3, s32 *arg4) {
    u16 sp8;
    u8 *var_r9;
    u8 *var_r30;
    u32 temp_r3;
    u16 temp_lo;
    u8 temp_r11;

    temp_r3 = Crc_GenerateCRCCaseSensitive(arg1, arg3);
    var_r30 = arg1;
    var_r9 = (u8 *)arg2 + 2;
    temp_lo = (u16)temp_r3;
    temp_r3 >>= 0x10;
    temp_r3 += temp_lo;
    sp8 = temp_r3;
    *arg2 = sp8;
    temp_r11 = ((Unk_E01B0030 *)&sp8)->unk0x1;
    if (arg3 > 0) {
        s32 var_ctr = arg3;
        do {
            u8 temp_r0 = *var_r30;
            var_r30 += 1;
            *var_r9 = temp_r11 ^ temp_r0;
            var_r9 += 1;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    *arg4 = arg3 + 2;
}
