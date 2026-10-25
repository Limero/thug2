// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80123A98-0x80123BE0 (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_8039BE58;
extern s32 lbl_8039BE5C;
extern s32 lbl_8039BE64;
extern u8 lbl_8039BE68;
extern s32 lbl_8039BE6C[];
extern u8 lbl_8039BE74;
extern char lbl_8029DEB4[];
extern char lbl_8029E364[];
void fn_80123A98(s32 arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u16 *var_r30;
    u16 *var_r31;
    u16 *var_r9;
    s16 *var_r9_2;
    u32 var_r10;
    u32 var_r10_2;
    u32 temp_r4;
    u32 temp_r0_2;
    u8 temp_r11 = lbl_8039BE68;
    s16 temp_r0;

    var_r31 = (u16 *)(lbl_8039BE6C[lbl_8039BE74] + arg0 * 2);
    var_r30 = var_r31 + 0x200;
    if ((s32)temp_r11 == 2) {
        var_r10 = 0U;
        var_r9 = (u16 *)(lbl_8039BE58 + lbl_8039BE64 * 4);
        while (var_r10 < arg1) {
            *var_r31 = var_r9[0];
            var_r31 += 1;
            *var_r30 = var_r9[1];
            var_r9 += 1;
            var_r9 += 1;
            var_r30 += 1;
            var_r10 += 1;
        }
    } else {
        if ((s32)temp_r11 != 1) {
            OSPanic(lbl_8029DEB4, 0x7EB, lbl_8029E364);
        }
        var_r10_2 = 0U;
        var_r9_2 = (s16 *)(lbl_8039BE58 + lbl_8039BE64 * 2);
        while (var_r10_2 < arg1) {
            temp_r0 = *var_r9_2;
            var_r10_2 += 1;
            var_r9_2 += 1;
            *var_r31 = (u16)temp_r0;
            *var_r30 = (u16)temp_r0;
            var_r31 += 1;
            var_r30 += 1;
        }
    }
    temp_r4 = lbl_8039BE5C;
    temp_r0_2 = lbl_8039BE64 + arg1;
    lbl_8039BE64 = temp_r0_2;
    if (temp_r0_2 >= temp_r4) {
        lbl_8039BE64 = temp_r0_2 - temp_r4;
    }
}
