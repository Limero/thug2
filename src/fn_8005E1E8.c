// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E1E8-0x8005E2D0 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern f32 lbl_80293AF8;
extern f32 lbl_80293AFC;
extern f32 lbl_80293B00;
extern f32 lbl_803CAF64;
extern f32 lbl_803CAF68;
extern f32 lbl_80300E04;
extern s32 lbl_80300E00;

f32 tanf(f32);
void *fn_8005DD6C(s32);
void fn_800244E0(void *);

void fn_8005E1E8(f32 farg0) {
    volatile double _dummy;
    volatile double _dummy1;
    volatile double _dummy2;
    f32 var_f13;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r31;
    void *temp_r3;

    var_f13 = farg0;
    if (var_f13 == lbl_80293AF8) {
        var_f13 = lbl_803CAF68;
    }
    temp_f29 = lbl_80293AFC;
    temp_f30 = lbl_80293B00;
    lbl_803CAF64 = var_f13;
    temp_f31 = tanf(var_f13 * temp_f29 * temp_f30);
    lbl_80300E04 = temp_f31 / tanf(lbl_803CAF68 * temp_f29 * temp_f30);
    var_r31 = 0;
    if (var_r31 < lbl_80300E00) {
        do {
            temp_r3 = fn_8005DD6C(var_r31);
            if (temp_r3 != NULL) {
                if (*(void **)((char *)temp_r3 + 0x18) != NULL) {
                    fn_800244E0(*(void **)((char *)temp_r3 + 0x18));
                }
            }
            var_r31 += 1;
        } while (var_r31 < lbl_80300E00);
    }
}
