// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016D52C-0x8016D698 (364B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
extern s32 lbl_80305EE4;
extern f32 lbl_802A8C20;
extern f64 lbl_802A8C28;
extern s32 fn_80198F7C(s32);
extern s32 Script_GetInteger(s32, s32);
extern f32 fn_800144C8(void);
extern void fn_8016E1B4(Unk_E06AC104 *);
extern void fn_8016E0D8(void *, s32);
extern void fn_8016DAC0(void *, s32);
void fn_8016D52C(void *arg0) {
    register void *carg __asm__("r3");
    f32 temp_f1;
    register s32 var_r26 __asm__("r26");
    register char *var_r24 __asm__("r24");
    register char *var_r25 __asm__("r25");
    register char *var_r27 __asm__("r27");
    register s32 var_r28 __asm__("r28");
    register char *var_r30 __asm__("r30");
    register s32 var_r31 __asm__("r31");
    register s32 one_r23 __asm__("r23");
    register void *a0 __asm__("r29");
    s32 temp_r9;
    s32 temp_r11;
    char *pEE4;

    a0 = arg0;
    if ((fn_80198F7C(lbl_80305EC0) == QB_CAREER) && (Script_GetInteger(QB_TOD_MANAGER_INACTIVE, 1) != 1) && ((pEE4 = (char *)lbl_80305EE4), ((Unk_E9D95610 *)a0)->unk0x354 == 0) && (((Unk_E9D95610 *)a0)->unk0x358 != 0) && (((Unk_1D62F22E_2 *)pEE4)->unk0x48 == 0)) {
        temp_f1 = fn_800144C8() * lbl_802A8C20 * ((Unk_E9D95610 *)a0)->unk0x344;
        if (!(temp_f1 >= lbl_802A8C28)) {
            var_r26 = (s32)temp_f1;
        } else {
            var_r26 = (s32)(temp_f1 - lbl_802A8C28) ^ 0x80000000;
        }
        carg = a0;
        var_r24 = (char *)a0 + 0x158;
        var_r28 = 0;
        ((Unk_E9D95610 *)a0)->unk0x340 = ((Unk_E9D95610 *)a0)->unk0x340 + var_r26;
        var_r25 = var_r24;
        var_r27 = (char *)a0 + 0x190;
        fn_8016E1B4(carg);
        one_r23 = 1;
        var_r30 = (char *)a0 + 0x188;
        var_r31 = 0;
        do {
            temp_r9 = *(s32 *)(var_r31 + (s32)var_r25) + var_r26;
            *(s32 *)(var_r31 + (s32)var_r25) = temp_r9;
            temp_r11 = *(s32 *)(var_r31 + (s32)var_r27);
            if (temp_r11 == 0) {
                if (temp_r9 > *(s32 *)var_r30) {
                    *(s32 *)(var_r31 + (s32)var_r24) = temp_r11;
                    *(s32 *)(var_r31 + (s32)var_r27) = one_r23;
                    fn_8016E0D8(a0, var_r28);
                }
                if (*(s32 *)(var_r31 + (s32)var_r27) != 0) {
                    goto block_13;
                }
            } else {
            block_13:
                fn_8016DAC0(a0, var_r28);
            }
            var_r28 += 1;
            var_r30 += 0x190;
            var_r31 += 0x190;
        } while (var_r28 <= 1);
    }
}
