// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CCF80-0x801CD014 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 fn_8012570C(s32, s32);
extern f32 lbl_802AD1D8;
f32 fn_801CCF80(Unk_C7387A53 *arg0, s32 arg1) {
    volatile double _dummy;
    f32 var_f31;

    if (*(s32 *)(arg0->unk0xC + (s32)0xC8) != 0) {
        var_f31 = fn_8012570C(QB_LANSERVERCOLLCOEFFICIENT, 1);
    } else {
        var_f31 = fn_8012570C(QB_LANCLIENTCOLLCOEFFICIENT, 1);
    }
    if (arg1 == 0) {
        return var_f31;
    }
    return var_f31 * (fn_8012570C(QB_DRIVINGCOEFFICIENTBOOSTFACTOR, 0) + lbl_802AD1D8);
}
