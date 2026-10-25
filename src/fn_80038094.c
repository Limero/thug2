// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80038094-0x800381CC (312B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct QuatSrc {
    f32 f_0x0;
    f32 f_0x4;
    f32 f_0x8;
} QuatSrc;

typedef struct QuatDst {
    f32 f_0x0;
    f32 f_0x4;
    f32 f_0x8;
    char pad0xC[4];
    f32 f_0x10;
    f32 f_0x14;
    f32 f_0x18;
    char pad0x1C[4];
    f32 f_0x20;
    char pad0x24[0xC];
    f32 f_0x30;
    f32 f_0x34;
    f32 f_0x38;
    f32 f_0x3C;
} QuatDst;

extern void PSMTXQuat(void *, void *);
extern f32 lbl_80291EFC;   // lis r9,-0x7fd7 => 0x80290000 + 0x1efc = 0x80291EFC

void fn_80038094(void *arg0, QuatSrc *arg1, QuatDst *arg2, s32 arg3, s32 arg4) {
    f32 temp_f10;
    register f32 var_f0 __asm__("fr0");
    register f32 d_first __asm__("fr11");
    register f32 c_first __asm__("fr11");

    PSMTXQuat(arg2, arg0);
    temp_f10 = arg1->f_0x0;
    arg2->f_0x30 = temp_f10;
    arg2->f_0x34 = arg1->f_0x4;
    arg2->f_0x38 = arg1->f_0x8;
    arg2->f_0x3C = lbl_80291EFC;
    if (arg3) {
        if (arg4) {
            arg2->f_0x30 = -temp_f10;
            d_first = -arg2->f_0x0;
            var_f0 = -arg2->f_0x20;
            arg2->f_0x0 = d_first;
            arg2->f_0x14 = -arg2->f_0x14;
            arg2->f_0x18 = -arg2->f_0x18;
            goto block_6;
        }
        arg2->f_0x0 = -arg2->f_0x0;
        arg2->f_0x4 = -arg2->f_0x4;
        arg2->f_0x8 = -arg2->f_0x8;
        arg2->f_0x10 = -arg2->f_0x10;
        arg2->f_0x14 = -arg2->f_0x14;
        arg2->f_0x18 = -arg2->f_0x18;
        return;
    }
    if (arg4) {
        arg2->f_0x30 = -temp_f10;
        c_first = -arg2->f_0x4;
        var_f0 = -arg2->f_0x20;
        arg2->f_0x4 = c_first;
        arg2->f_0x8 = -arg2->f_0x8;
        arg2->f_0x10 = -arg2->f_0x10;
        /* Zero-code barrier: keeps the store run above in the original's
           order instead of letting the last store sink past the label. */
        __asm__ volatile("" ::: "memory");
block_6:
        arg2->f_0x20 = var_f0;
    }
}
