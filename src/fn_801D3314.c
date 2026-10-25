// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D3314-0x801D33B8 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD448;
extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
static void fn_801D19E0(void *, f32);

void fn_801D3314(Unk_99111807 *arg0) {
    volatile double _dummy;
    f32 var_f31;
    f32 ret2;
    register f32 var_f13 __asm__("fr13");
    s32 temp_r30;

    temp_r30 = arg0->unk0xC;
    var_f31 = fn_8014030C(QB_PHYSICS_CROUCHED_AIR_FRICTION, 1, temp_r30);
    ret2 = fn_8014030C(QB_PHYSICS_STANDING_AIR_FRICTION, 1, temp_r30);
    var_f13 = arg0->unk0x3B8;
    if (var_f13 != lbl_802AD448) {
        ret2 = arg0->unk0x3C4;
        __asm__("" : "+f"(ret2));
        var_f31 = ret2;
    }
    if (*(s32 *)(arg0->unk0x15BC + 0x28) != 0) {
        fn_801D19E0(arg0, var_f31);
    } else {
        fn_801D19E0(arg0, ret2);
    }
}
