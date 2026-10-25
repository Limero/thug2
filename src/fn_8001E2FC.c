// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E2FC-0x8001E3CC (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
extern u8 lbl_80300334[];
extern void (*lbl_80300280)(u32);
void fn_8001E2FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    register u32 arg2_valid __asm__("r0");
    u32 low;
    register u32 command __asm__("r0");
    register u32 arg5_valid __asm__("r7");
    register u32 arg5_field __asm__("r0");
    u32 low_word;
    register u32 callback_addr __asm__("r9");

    low = (arg2 & 7) | ((arg1 & 7) << 3);
    arg2_valid = 0;
    if (arg2 != 0xFF) {
        arg2_valid = 1;
        if (arg2 & 0x100) {
            arg2_valid = 0;
        }
    }
    command = low | (arg2_valid << 6);
    command |= (u32)lbl_80300334[arg3 & 0xF] << 7;
    command |= (arg5 & 7) << 12;
    arg2 = command | ((arg4 & 7) << 15);
    arg5_valid = 0;
    if (arg5 != 0xFF) {
        arg5_valid = 1;
        if (arg5 & 0x100) {
            arg5_valid = 0;
        }
    }
    arg5_field = arg5_valid << 18;
    low_word = arg2 | arg5_field;
    low_word |= (u32)lbl_80300334[arg6 & 0xF] << 19;
    __asm__("" : "+r"(low_word));
    callback_addr = (s32)lbl_80300280;
    ((void (*)(u32))callback_addr)(low_word | (u32)(((arg0 / 2) + 0x28) << 24));
}
