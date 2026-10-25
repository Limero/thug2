// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001EEE0-0x8001EF84 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern void (*lbl_80300280)(u32);
extern char lbl_80300288[];
extern char lbl_80300344[];

void fn_8001EEE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    char *bb;
    s32 a1s;
    s32 dec;
    s32 bval;

    ((void (*)(s32, s32))*(void **)&lbl_80300288)(0x103F, arg0);
    ((void (*)(s32, s32))*(void **)&lbl_80300288)(0x1009, arg1);

    a1s = arg1 * 0x10;
    bb = (char *)&lbl_80300344;
    dec = arg2 - 1;
    bval = *(u8 *)(bb + arg4);

    lbl_80300280(arg0 | a1s | (dec << 0xA) | (bval << 0xE) | (arg3 << 0x10));
}
