#include "dolphin/types.h"
extern u32 lbl_80311250;
extern u32 lbl_80311254;
extern u32 lbl_80311258;
extern u32 lbl_8031125C;
extern u32 lbl_80311260;
extern u32 lbl_80311264;

void fn_800034A0(u32 arg0) {
    lbl_8031125C = arg0;
    lbl_80311260 = 0x12B9B0A1;
    lbl_80311264 = 0x0AA2FB3F;
    lbl_80311250 = arg0;
    lbl_80311254 = 0x12B9B0A1;
    lbl_80311258 = 0x0AA2FB3F;
}
