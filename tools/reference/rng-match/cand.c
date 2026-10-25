#include "dolphin/types.h"
extern s32 lbl_80311250;
extern s32 lbl_80311254;
extern s32 lbl_80311258;
s32 fn_800034E4(s32 scale) {
    s32 t = lbl_80311250 * lbl_80311254 + lbl_80311258;
    lbl_80311250 = t;
    lbl_80311254 = (lbl_80311254 ^ t) + (t >> 4);
    lbl_80311258 = (lbl_80311258 - 0x10101010) + (t >> 3);
    return ((t & 0xFFFF) * scale) >> 16;
}
