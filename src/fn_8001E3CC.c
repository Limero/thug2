// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E3CC-0x8001E4E8 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern void (*lbl_80300280)(s32, s32);
void fn_8001E3CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg_sp8, s32 arg_spC, s32 arg_sp10, s32 arg_sp14) {
    s32 g1;
    s32 g2;
    s32 v;

    if (arg5 <= 1) {
        lbl_80300280(arg_sp10 | (arg_sp14 << 2) | (arg4 << 4) | (arg3 << 7) | (arg2 << 0xA) | (arg1 << 0xD) | (arg6 << 0x10) | ((arg5 << 0x12) & 0x40000) | (arg_sp8 << 0x13) | (arg7 << 0x14) | (arg_spC << 0x16) | ((arg0 << 0x19) + QB_UNKNOWN_0xC1000000), arg1);
        return;
    }
    v = arg_sp10 | (arg_sp14 << 2) | (arg4 << 4) | (arg3 << 7) | (arg2 << 0xA) | (arg1 << 0xD);
    g1 = ((arg5 << 0x12) & 0x40000) | 0x30000;
    g2 = (arg5 << 0x13) & 0x300000;
    v = v | g1 | (arg_sp8 << 0x13) | g2 | (arg_spC << 0x16) | ((arg0 << 0x19) + QB_UNKNOWN_0xC1000000);
    lbl_80300280(v, arg1);
}
