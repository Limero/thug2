// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E4E8-0x8001E5DC (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80300280;
void fn_8001E4E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg_sp8, s32 arg_spC) {
    s32 g;
    if (arg5 <= 1) {
        ((s32 (*)(s32))lbl_80300280)((arg4 | (arg3 << 4) | (arg2 << 8) | (arg1 << 0xC) | (arg6 << 0x10) | ((arg5 << 0x12) & 0x40000) | (arg_sp8 << 0x13) | (arg7 << 0x14) | (arg_spC << 0x16) | ((arg0 << 0x19) + 0xC0000000)));
        return;
    }
    g = ((arg5 << 0x12) & 0x40000) | 0x30000;
    ((s32 (*)(s32))lbl_80300280)((arg4 | (arg3 << 4) | (arg2 << 8) | (arg1 << 0xC) | g | (arg_sp8 << 0x13) | ((arg5 << 0x13) & 0x300000) | (arg_spC << 0x16) | ((arg0 << 0x19) + 0xC0000000)));
}
