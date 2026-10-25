// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80141570-0x801417B8 (584B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029F788;
extern f32 lbl_8029F78C;
extern f32 lbl_8029F790;
extern char lbl_80305EAC[];
extern char lbl_80305EC0[];
extern void fn_80125000(Unk_C71E6DE1 *);
extern s32 GetPair(s32, u32, void *, s32);
extern s32 GetInteger(CStruct *, u32, s32 *, s32);
extern s32 GetFloat(CStruct *, u32, f32 *, s32);
extern f32 fn_8014137C(void *, s32);
extern s32 fn_80174A50(Unk_40426380 *);
extern s32 fn_80187934(Unk_6BF95B44 *, s32);
extern s32 IsTrue(s32, void *);

f32 fn_80141570(CScript *arg0, CStruct *arg1) {
    struct {
        f32 spA[4];
        f32 spB[4];
        f32 spC[4];
        s32 sp38;
        f32 sp3C;
        char _pad[24];
    } L;
    f32 var_f1;
    f32 cur;
    f32 max;
    f32 var_f12;
    f32 var_f31;
    f32 var_f0;
    s32 var_r31;
    s32 var_r0;
    Unk_71062261 *temp_r11;

    fn_80125000(L.spA);
    fn_80125000(L.spB);
    GetPair(arg1, 0, L.spA, 0);
    if (GetInteger(arg1, 0, &L.sp38, 0) == 0) {
        var_f1 = lbl_8029F788;
    } else {
        var_f1 = fn_8014137C(arg0, L.sp38);
    }
    cur = L.spA[1];
    max = L.spA[2];
    var_f31 = cur + (((max - cur) * var_f1) / lbl_8029F788);
    temp_r11 = arg0->unk0x2AC;
    if (*(s32 *)(temp_r11->unk0xC + 0x120) != 0) {
        var_r0 = *(s32 *)(temp_r11->unk0x15BC + 0x34);
    } else {
        var_r0 = *(s32 *)(temp_r11->unk0x15BC + 0x34) ^ 1;
    }
    if ((var_r0 != 0) && (GetPair(arg1, QB_SWITCH, L.spB, 0) != 0)) {
        var_f12 = L.spB[1] + (((L.spB[2] - L.spB[1]) * fn_8014137C(arg0, 6)) / lbl_8029F788);
        if (var_f12 < lbl_8029F78C) {
            var_f12 = lbl_8029F78C;
        }
        if (var_f12 > lbl_8029F790) {
            var_f12 = lbl_8029F790;
        }
        var_f31 *= var_f12;
    }
    var_r31 = fn_80187934(fn_80174A50(*(s32 *)&lbl_80305EAC), 0);
    if (IsTrue(*(s32 *)&lbl_80305EC0, QB_IS_CLASSIC) != 0) {
        var_r31 += 1;
    }
    if (var_r31 != 1) {
        fn_80125000(L.spC);
        if (GetPair(arg1, QB_DIFF, L.spC, 0) != 0) {
            if (var_r31 == 0) {
                var_f0 = L.spC[1];
                var_f31 *= var_f0;
            } else if (var_r31 == 2) {
                var_f0 = L.spC[2];
                var_f31 *= var_f0;
            }
        }
    }
    if (GetFloat(arg1, QB_LIMIT, &L.sp3C, 0) != 0) {
        if (cur < max) {
            if (var_f31 > L.sp3C) {
                var_f31 = L.sp3C;
            }
        } else {
            if (var_f31 < L.sp3C) {
                var_f31 = L.sp3C;
            }
        }
    }
    return var_f31;
}
