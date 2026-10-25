#include "dolphin/types.h"
extern s32 lbl_80311250;
extern s32 lbl_80311254;
extern s32 lbl_80311258;
extern s32 lbl_8031125C;
extern s32 lbl_80311260;
extern s32 lbl_80311264;

void fn_800034A0(s32 arg0) {
    s32 *p;
    p = &lbl_8031125C; *p = arg0;
    p = &lbl_80311260; *p = 0x12B9B0A1;
    p = &lbl_80311264; *p = 0x0AA2FB3F;
    p = &lbl_80311250; *p = arg0;
    p = &lbl_80311254; *p = 0x12B9B0A1;
    p = &lbl_80311258; *p = 0x0AA2FB3F;
}
