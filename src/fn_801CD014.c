// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CD014-0x801CD118 (260B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80219680(CStruct *);
extern f32 fn_8012570C(s32, s32);
extern void* lbl_80305F9C;
extern f32 lbl_802AD1DC;
extern f32 lbl_802AD1E0;
f32 fn_801CD014(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    volatile double _dummy;
    volatile double _dummy2;
    s32 var_r3;
    register f32 temp_f31 __asm__("fr31");
    f32 var_f30;

    if (*(s32 *)(arg0->unk0xC + 0xC8) != 0) {
        if (fn_80219680(lbl_80305F9C) != 0) {
            temp_f31 = fn_8012570C(QB_INTERNETSERVERCOLLRADIUS, 1);
        } else {
            temp_f31 = fn_8012570C(QB_LANSERVERCOLLRADIUS, 1);
        }
    } else {
        if (fn_80219680(lbl_80305F9C) != 0) {
            temp_f31 = fn_8012570C(QB_INTERNETCLIENTCOLLRADIUS, 1);
        } else {
            temp_f31 = fn_8012570C(QB_LANCLIENTCOLLRADIUS, 1);
        }
    }
    var_f30 = lbl_802AD1DC;
    if (arg1 != 0) {
        var_f30 = lbl_802AD1E0;
    }
    if (arg2 != 0) {
        var_f30 += lbl_802AD1E0;
    }
    return temp_f31 * (var_f30 * fn_8012570C(QB_DRIVINGRADIUSBOOSTFACTOR, 1) + lbl_802AD1E0);
}
