#include "dolphin/types.h"
extern s32 lbl_80311250;
extern s32 lbl_80311254;
extern s32 lbl_80311258;

s32 fn_800034E4(s32 scale) {
    s32 s0 = lbl_80311250;
    s32 s1 = lbl_80311254;
    s32 s2 = lbl_80311258;
    s32 t = s0 * s1 + s2;
    s32 s2n = s2 - 0x10101010;
    lbl_80311250 = t;
    lbl_80311254 = (s1 ^ t) + (t >> 4);
    lbl_80311258 = s2n + (t >> 3);
    return ((t & 0xFFFF) * scale) >> 16;
}
