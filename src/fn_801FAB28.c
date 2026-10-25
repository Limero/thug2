// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FAB28-0x801FAC10 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_802AE5B0;
extern s32 fn_801F98B4(Unk_C7387A53 * arg0, Unk_EA529D06 * arg1, Unk_EA529D06 * arg2, CStruct * arg3, CStruct * arg4, s32 arg5);
s32 fn_801FAB28(Unk_C7387A53 *arg0, Unk_EA529D06 *arg1, void *arg2, f32 *arg3, s32 *arg4, s32 *arg5, s32 arg6, s32 arg7) {
    struct {
        __ps_t sp8[2];
        f32 sp18;
        s32 sp1C;
    } fr;
    __ps_t *psp;
    f32 var_f31;
    s32 var_r29;
    s32 var_r8;
    s32 temp_r0;
    CStruct *var_r31;

    var_r31 = arg0->unk0x24;
    var_f31 = lbl_802AE5B0;
    var_r29 = 0;
    if (var_r31 != NULL) {
        do {
            temp_r0 = var_r31->unk0x10;
            var_r8 = -1;
            fr.sp1C = 0;
            if (temp_r0 == arg6) {
                var_r8 = arg7;
            }
            if ((fn_801F98B4(var_r31, arg1, &fr.sp8[0], &fr.sp18, &fr.sp1C, var_r8) != 0) && (fr.sp18 < var_f31)) {
                var_f31 = fr.sp18;
                var_r29 = 1;
                psp = (__ps_t *)&fr.sp8[0];
                ((__ps_t *)arg2)[0] = fr.sp8[0];
                ((__ps_t *)arg2)[1] = psp[1];
                *arg3 = var_f31;
                *arg4 = var_r31->unk0x10;
                *arg5 = fr.sp1C;
            }
            var_r31 = var_r31->unk0x4;
        } while (var_r31 != NULL);
    }
    return var_r29;
}
