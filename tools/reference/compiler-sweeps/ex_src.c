#include "dolphin/types.h"
extern s32 lbl_80311250;
extern s32 lbl_80311254;
extern s32 lbl_80311258;
extern s32 lbl_8031125C;
extern s32 lbl_80311260;
extern s32 lbl_80311264;

void fn_800034A0(s32 arg0) {
    lbl_8031125C = arg0;
    lbl_80311260 = -(int)0xED464F5F;
    lbl_80311264 = 0x0AA2FB3F;
    lbl_80311250 = arg0;
    lbl_80311254 = -(int)0xED464F5F;
    lbl_80311258 = 0x0AA2FB3F;
}
