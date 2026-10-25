// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AC550-0x801AC66C (284B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern void fn_801AAE94(CStruct * arg0, CStruct * arg1, CStruct * arg2, CStruct * arg3);

void fn_801AC550(Unk_C7387A53 *arg0, s32 arg1, void *arg2) {
    s32 sp8[4];
    s32 sp18[4];
    s32 var_r11 = 0;
    s32 var_r30;
    char *temp_r31;
    char *temp_r5;

    if (var_r11 < arg0->unk0x50) {
        __ps_t *p8 = (__ps_t *)sp8;
        s32 var_r28 = 0;
        s32 var_r10 = 0;
        do {
            temp_r31 = *((char *volatile *)&arg0->unk0x48) + var_r10;
            if (((Unk_CB56A529 *)temp_r31)->unk0x54 == arg1) {
                ((__ps_t *)(temp_r31 + 0x28))[0] = ((__ps_t *)arg2)[0];
                ((__ps_t *)(temp_r31 + 0x30))[0] = ((__ps_t *)arg2)[1];
                if (((Unk_CB56A529 *)temp_r31)->unk0x48 != 0) {
                    ((__ps_t *)sp8)[0] = ((Unk_CB56A529 *)temp_r31)->unk0x28;
                    p8[1] = ((Unk_CB56A529 *)temp_r31)->unk0x30;
                    {
                        char *src = *((char *volatile *)&((Unk_C7387A53 *)temp_r31)->unk0x48);
                        ((__ps_t *)sp18)[0] = ((Unk_C1F9F519 *)src)->unk0x28;
                        ((__ps_t *)sp18)[1] = ((Unk_C1F9F519 *)src)->unk0x30;
                    }
                    fn_801AAE94(p8, sp18, temp_r31 + 8, temp_r31 + 0x18);
                }
                if (((Unk_CB56A529 *)temp_r31)->unk0x4C != 0) {
                    var_r30 = 0;
                    while (var_r30 < arg0->unk0x50) {
                        temp_r5 = *((char *volatile *)&arg0->unk0x48) + var_r28;
                        if (((Unk_1D62F22E_2 *)temp_r5)->unk0x48 == (s32)temp_r31) {
                            fn_801AAE94(temp_r5 + 0x28, temp_r31 + 0x28, temp_r5 + 8, temp_r5 + 0x18);
                        }
                        var_r30++;
                    }
                }
                break;
            }
            var_r11++;
            var_r28 += 0x60;
            var_r10 += 0x60;
        } while (var_r11 < arg0->unk0x50);
    }
}
