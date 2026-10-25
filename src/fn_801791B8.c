// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801791B8-0x801792D4 (284B). Byte-identical.
#include "types.h"
extern f32 lbl_802A8FF4;
extern f32 lbl_802A8FF8;
extern f32 lbl_802A8FFC;
extern f32 lbl_802A9000;
extern f32 lbl_802A9004;
extern f32 lbl_802A9008;
extern f32 lbl_802A900C;
extern f32 lbl_802A9010;
extern f32 lbl_802A9014;
extern f32 lbl_802A9018;
extern f32 lbl_802A901C;
f32 fn_801791B8(u32 arg0, s32 arg1) {
    f32 ret;
    s32 t;
    s32 bit;

    ret = lbl_802A8FF4;
    switch (arg1) {
    case 0:
        t = arg0 & 3;
        if (t == 0) {
            return lbl_802A8FF8;
        }
        if (t == 1) {
            return lbl_802A8FFC;
        }
        __asm__("" : "+r"(t));
        if (t == 2) {
            return lbl_802A9000;
        }
        return ret;
    case 1:
        bit = (arg0 >> 2) & 1;
        __asm__("" : "+r"(bit));
        if (bit == 0) {
            return lbl_802A9004;
        }
        if (bit == 1) {
            return lbl_802A9000;
        }
        return ret;
    case 2:
        bit = (arg0 >> 3) & 1;
        if (bit == 0) {
            return lbl_802A9008;
        }
        if (bit == 1) {
            return lbl_802A900C;
        }
        return ret;
    case 3:
        bit = (arg0 >> 4) & 1;
        if (bit == 0) {
            return lbl_802A9010;
        }
        if (bit == 1) {
            return lbl_802A9014;
        }
        return ret;
    case 4:
        bit = (arg0 >> 5) & 1;
        if (bit == 0) {
            return lbl_802A9018;
        }
        if (bit == 1) {
            return lbl_802A901C;
        }
        return ret;
    default:
        return ret;
    }
}
