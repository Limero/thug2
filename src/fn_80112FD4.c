// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112FD4-0x8011313C (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -fno-expensive-optimizations
s32 fn_8011BFD4(s32, void *);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void *fn_801195DC(void *);
void fn_8011976C(void *);
void fn_80119640(void *, s32);
s32 fn_8011C03C(s32, f32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ScriptSetStreamParams(s32 arg0) {
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s32 sp20;
    f32 sp8[6];
    f32 *p8;
    s32 var_r30;
    s32 var_r31;

    sp20 = 0;
    if (GetChecksum_2(arg0, 0, &sp20, 0) != 0) {
        var_r31 = 0;
        var_r30 = GetFloat(arg0, QB_VOLL, &sp24, 0);
        if ((GetFloat(arg0, QB_VOLR, &sp28, 0) != 0) || (var_r30 != 0)) {
            var_r31 = 1;
        }
        var_r30 = var_r31;
        if (GetFloat(arg0, QB_VOL, &sp2C, 0) != 0) {
            var_r30 = 1;
            sp24 = sp2C;
            sp28 = sp2C;
        }
        var_r31 = 1;
        if (var_r30 != 0) {
            fn_801195DC(&sp8[0]);
            fn_8011976C(&sp8[0]);
            p8 = &sp8[0];
            sp8[0] = sp24;
            p8[1] = sp28;
            var_r31 = fn_8011BFD4(sp20, p8);
            fn_80119640(p8, 2);
        }
        if (GetFloat(arg0, QB_PITCH, &sp30, 0) != 0) {
            var_r30 = 0;
            if ((fn_8011C03C(sp20, sp30) != 0) && (var_r31 != 0)) {
                var_r30 = 1;
            }
            var_r31 = var_r30;
        }
        return var_r31;
    }
    return 0;
}
