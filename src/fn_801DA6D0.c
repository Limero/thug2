// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801DA6D0-0x801DA814 (324B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
f32 fn_8014030C(s32 arg0, s32 arg1, Unk_FFAD6788 * arg2);
f32 fn_8012570C(s32 arg0, s32 arg1);
s32 fn_801A6F44(s32 arg0, s32 arg1);
s32 Script_GetInteger(s32 arg0, s32 arg1);
void fn_801A6F8C(s32 arg0, s32 arg1);
extern char lbl_80305EAC[];
extern s32 lbl_80305F04;
extern f32 lbl_802AD5D4;

f32 fn_801DA6D0(Unk_71062261 *arg0) {
    volatile double _dummy;
    f32 var_f31;
    f32 temp_f1;
    Unk_C7387A53 *temp_r9;
    void *temp_r31;
    s32 var_r3;
    char *anchor;

    temp_r9 = *((void * *)&arg0->unk0x15BC);
    temp_r31 = *((void * *)&arg0->unk0xC);
    if ((temp_r9->unk0x40 != 0) || (temp_r9->unk0xAC != 0)) {
        var_f31 = fn_8014030C(QB_PHYSICS_AIR_GRAVITY, 1, (s32)temp_r31);
        var_r3 = QB_PHYSICS_VERT_HANG_STAT;
    } else {
        var_f31 = fn_8014030C(QB_PHYSICS_AIR_GRAVITY, 1, (s32)temp_r31);
        var_r3 = QB_PHYSICS_AIR_HANG_STAT;
    }
    var_f31 = var_f31 / fn_8012570C(var_r3, 1);
    __asm__ volatile("" ::: "memory");
    if (fn_801A6F44(*(s32 *)(*(s32 *)&lbl_80305EAC + 0x24), QB_CHEAT_MOON) != 0) {
        fn_801A6F8C(*(s32 *)(*(s32 *)&lbl_80305EAC + 0x24), Script_GetInteger(QB_CHEAT_MOON, 0));
        var_f31 = var_f31 * fn_8014030C(QB_MOON_GRAVITY, 1, (s32)temp_r31);
        lbl_80305F04 = 1;
    }
    temp_f1 = fn_8012570C(QB_UNKNOWN_0xBE33A41E, 0);
    if (temp_f1 != lbl_802AD5D4) {
        if (*(f32 *)((char *)(*((void * *)&arg0->unk0xC)) + 0xBC) <= lbl_802AD5D4) {
            var_f31 = var_f31 * temp_f1;
        }
    }
    return var_f31;
}
