// Promoted from src/wip (m2c draft hand-refined to exact match; loop counters use the
// var -= 1; while ((var + 1) != 0) idiom that fuses into cmpwi/addi/bne).
// range 0x8005B258-0x8005B2E8 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80364C38[];
extern char lbl_80364C54[];
extern char lbl_80364CC8[];
void fn_80058FF4(void *);
void fn_80059F2C(void *);
void fn_8005B258(s32 arg0, s32 arg1) {
    s32 var_r30;
    s32 var_r31;
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        fn_80058FF4(lbl_80364C38);
        var_r30 = 3;
        var_r31 = (s32)lbl_80364C54;
        do {
            fn_80058FF4((void *)var_r31);
            var_r31 += 0x1C;
            var_r30 -= 1;
        } while ((var_r30 + 1) != 0);
        var_r30 = 0x95;
        var_r31 = (s32)lbl_80364CC8;
        do {
            fn_80059F2C((void *)var_r31);
            var_r31 += 0x28;
            var_r30 -= 1;
        } while ((var_r30 + 1) != 0);
    }
}
