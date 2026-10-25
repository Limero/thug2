// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80073880-0x80073A5C (476B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_803016D8[];
extern f32 lbl_802955F4;
extern bool lbl_8030166C;
extern s32 lbl_80301670;
void fn_8001EA14(s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, s32, s32, s32, s32, s32);
s32 fn_80016EC4(s32);
void fn_8001EDE0(s32, s32, s32, s32);
s32 fn_80016EAC(s32);
void fn_80073880(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r23;
    s32 var_r25;
    s32 var_r26;
    s32 temp_r5;
    u16 temp_r30;
    u16 temp_r30_2;
    u16 temp_r30_3;
    u16 temp_r30_4;
    u16 temp_r30_5;
    register f32 a __asm__("fr1");
    register f32 b __asm__("fr2");
    f32 c;
    s32 one;

    var_r25 = 0;
    if ((arg0 == 0) || (arg0 == 9) || (arg0 == 0xA)) {
        var_r25 = 1;
    }
    temp_r30 = (u16) (fn_80016EAC(arg0) >> var_r25);
    var_r23 = 4;
    fn_8001EDE0(arg3, 1, temp_r30, (u16) (fn_80016EC4(arg0) >> var_r25));
    var_r26 = 0;
    temp_r30_2 = (u16) (fn_80016EAC(arg0) >> var_r25);
    fn_8001EDE0(arg3 + 1, 1, temp_r30_2, (u16) (fn_80016EC4(arg0) >> var_r25));
    temp_r30_3 = (u16) (fn_80016EAC(arg0) >> var_r25);
    fn_8001EDE0(arg3 + 2, 1, temp_r30_3, (u16) (fn_80016EC4(arg0) >> var_r25));
    temp_r30_4 = (u16) (fn_80016EAC(arg0) >> var_r25);
    fn_8001EDE0(arg3 + 3, 1, temp_r30_4, (u16) (fn_80016EC4(arg0) >> var_r25));
    if (lbl_8030166C != 0) {
        var_r26 = 1;
    }
    if (arg1 == 1) {
        var_r23 = 1;
    }
    if (arg1 == 2) {
        var_r26 = 0;
        var_r23 = lbl_80301670;
    }
    if (arg1 == 3) {
        var_r23 = 6;
    }
    temp_r30_5 = (u16) (fn_80016EAC(arg0) >> var_r25);
    temp_r5 = fn_80016EC4(arg0) >> var_r25;
    one = 1;
    fn_8001EA14(lbl_803016D8[arg0], temp_r30_5, (u16) temp_r5, var_r23, 0, 0, 0,
                var_r26, (a = lbl_802955F4), (c = a), (b = c), var_r26, 0, one, 0, arg2);
}
