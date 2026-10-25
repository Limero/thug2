// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80135D4C-0x80135E4C (256B). Byte-identical.
#include "types.h"
extern void *lbl_8039D4E4;
extern void *lbl_8039D4F8[];
extern u8 lbl_8039D4F4;
extern u8 lbl_8039D500;
extern u32 lbl_8039D4E8;
extern s32 lbl_8039D4F0;

void fn_80135D4C(s32 arg0, u32 arg1) {
    register u16 *var_r7 __asm__("r7");
    register u32 var_i __asm__("r10");
    u16 *var_r8 = (u16 *)lbl_8039D4F8[lbl_8039D500] + arg0;
    s16 *var_r9;

    var_r7 = var_r8 + 0x200;

    if (lbl_8039D4F4 == 2) {
        u16 *src = (u16 *)((s32)lbl_8039D4E4 + (*(u32 *)&lbl_8039D4F0 << 2));
        var_i = 0U;
        while (var_i < arg1) {
            u16 temp_r0 = *src;
            var_r8[0] = temp_r0;
            var_r8 += 1;
            src += 1;
            temp_r0 = *src;
            var_r7[0] = temp_r0;
            var_r7 += 1;
            src += 1;
            var_i += 1U;
        }
    } else {
        s16 *srcm = (s16 *)((s32)lbl_8039D4E4 + (*(u32 *)&lbl_8039D4F0 + *(u32 *)&lbl_8039D4F0));
        var_i = 0U;
        while (var_i < arg1) {
            s16 temp_r0 = *srcm;
            srcm += 1;
            var_r8[0] = temp_r0;
            var_r7[0] = temp_r0;
            var_r8 += 1;
            var_r7 += 1;
            var_i += 1U;
        }
    }
    {
        s32 temp_r0 = *(u32 *)&lbl_8039D4F0 + arg1;
        lbl_8039D4F0 = temp_r0;
        if ((u32)temp_r0 >= lbl_8039D4E8) {
            lbl_8039D4F0 = temp_r0 - lbl_8039D4E8;
        }
    }
}
