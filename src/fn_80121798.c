// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121798-0x80121874 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-strength-reduce
#include "types.h"
#include "qb_constants.h"
extern char lbl_8029DEB4[];
extern char lbl_8029DF50[];
extern char lbl_8029DF6C[];
extern char lbl_8039BA58[];
int OSPanic();
s32 fn_80121798(void) {
    char *mgr = lbl_8039BA58;
    s32 temp_r31;
    s32 temp_r31_2;
    s32 var_r3;
    s32 var_ctr;
    s32 var_r9;
    s32 zero;
    void *temp_r10;
    void *var_r11;

    temp_r31 = *(s32 *)(mgr + 0x90);
    if (temp_r31 == 0) {
        OSPanic(lbl_8029DEB4, 0x106, lbl_8029DF50);
    }
    temp_r31_2 = (temp_r31 + 0x37) & QB_UNKNOWN_0xFFFFFFE0;
    if (((s32 (*)(s32))*(s32 *)(mgr + 0)) == NULL) {
        OSPanic(lbl_8029DEB4, 0x10C, lbl_8029DF6C);
    }
    var_r3 = (s32)((s32 (*)(void *))*(s32 *)(mgr + 0))(temp_r31_2 * 0xA);
    *(s32 *)(mgr + 0x394) = var_r3;
    if (var_r3 == 0) {
        return 0;
    }
    temp_r10 = (void *)mgr + 0x300;
    zero = 0;
    var_r11 = temp_r10;
    var_r9 = 0;
    var_ctr = 0xA;
    do {
        *(s32 *)((char *)var_r11 - 0xC) = var_r3;
        *(s32 *)((char *)temp_r10 + var_r9) = zero;
        var_r3 += temp_r31_2;
        var_r11 += 0x10;
        var_r9 += 0x10;
        var_ctr -= 1;
    } while (var_ctr != 0);
    return 1;
}
