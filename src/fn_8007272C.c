// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007272C-0x8007297C (592B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802954D8;
extern f32 lbl_802954DC;
extern f32 lbl_802954E0;
extern f32 lbl_802954E4;
extern f32 lbl_802954E8;
extern f32 lbl_802954EC;
extern f32 lbl_802954F0;
extern f32 lbl_802954F4;
extern f32 lbl_802954F8;
extern f32 lbl_802954FC;
extern f32 lbl_80295500;
extern f32 lbl_80295504;
extern f32 lbl_80295508;
extern f32 lbl_8029550C;
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F4(void);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F164(s32, s32, s32, s32);
void fn_8001F200(f32, f32);
void fn_8007272C(s32 arg0) {
    volatile double _d0;
    volatile double _d1;
    volatile double _d2;
    volatile double _d3;
    f32 temp_f10;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f30;
    f32 temp_f31;
    register f32 a0 __asm__("fr1");
    f32 var_f28;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;

    var_f28 = lbl_802954D8;
    var_f31 = lbl_802954DC;
    var_f30 = lbl_802954E0;
    temp_f10 = lbl_802954E4;
    var_f29 = var_f28;
    if (arg0 == 1) {
        var_f28 = temp_f10 * lbl_802954E8;
        var_f31 = temp_f10 * lbl_802954EC;
        var_f30 = temp_f10 * lbl_802954F0;
    }
    if (arg0 == 2) {
        var_f29 = temp_f10 * lbl_802954F0;
        var_f28 = temp_f10 * lbl_802954E8;
        var_f30 = var_f29;
        var_f31 = temp_f10 * lbl_802954EC;
    }
    if (arg0 == 3) {
        var_f28 = temp_f10 * lbl_802954E8;
        var_f29 = temp_f10 * lbl_802954F4;
        var_f31 = temp_f10 * lbl_802954EC;
        var_f30 = temp_f10 * lbl_802954F0;
    }
    if (arg0 == 4) {
        var_f30 = temp_f10 * lbl_802954EC;
        var_f28 = temp_f10 * lbl_802954F8;
        var_f31 = var_f30;
        var_f29 = temp_f10 * lbl_802954FC;
    }
    if (arg0 == 5) {
        var_f28 = lbl_802954D8;
        var_f31 = lbl_80295500;
        var_f30 = lbl_80295504;
        var_f29 = var_f28;
    }
    if (arg0 == 6) {
        var_f29 = lbl_80295504;
        var_f31 = lbl_80295500;
        var_f28 = lbl_802954D8;
        var_f30 = var_f29;
    }
    fn_8001F0A0(0x80, 0, 4);
    temp_f31 = var_f28 + var_f31;
    fn_8001F0F8(var_f28, var_f29, lbl_80295508);
    temp_f30 = var_f29 + var_f30;
    fn_8001F164(0xFF, 0xFF, 0xFF, 0xFF);
    temp_f1 = lbl_802954D8;
    fn_8001F200(temp_f1, temp_f1);
    a0 = temp_f31;
    __asm__("" : "+f"(a0));
    fn_8001F0F8(a0, var_f29, lbl_80295508);
    fn_8001F164(0xFF, 0xFF, 0xFF, 0xFF);
    fn_8001F200(lbl_8029550C, lbl_802954D8);
    fn_8001F0F8(temp_f31, temp_f30, lbl_80295508);
    fn_8001F164(0xFF, 0xFF, 0xFF, 0xFF);
    temp_f1_2 = lbl_8029550C;
    fn_8001F200(temp_f1_2, temp_f1_2);
    fn_8001F0F8(var_f28, temp_f30, lbl_80295508);
    fn_8001F164(0xFF, 0xFF, 0xFF, 0xFF);
    fn_8001F200(lbl_802954D8, lbl_8029550C);
    fn_8001F0F4();
}
