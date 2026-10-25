// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x8005D560-0x8005D60C (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80293914[];
extern char lbl_8036645C[];
extern void fn_8001075C(void *);
extern void fn_80010760(void);
extern s32 *fn_8005D7A0(s32);
extern s32 *fn_8007B3CC(s32, s32, s32, s32, s32, s32, s32);
extern void fn_8005D844(void *, s32 *, s32 *);
s32 *fn_8005D560(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 sp8;
    s32 *var_r30;

    fn_8001075C(lbl_80293914);
    sp8 = arg0 + arg4;
    var_r30 = fn_8005D7A0(sp8);
    if (var_r30 == NULL) {
        var_r30 = fn_8007B3CC(sp8, arg1, arg2, arg3, arg4, arg5, arg6);
        *var_r30 = sp8;
        fn_8005D844((void *)lbl_8036645C, &sp8, var_r30);
    }
    fn_80010760();
    return var_r30;
}
