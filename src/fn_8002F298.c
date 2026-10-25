// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002F298-0x8002F4E0 (584B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
s32 fn_80032934(void *, f32);
void *fn_80033310(s32, f32);
void *fn_800322C0(void *, s32);
s32 fn_80032AA0(s32);
#include "structs.h"
extern f32 lbl_80291988;
extern f32 lbl_8029198C;
extern s32 lbl_803003B8;
typedef s32 (*vcall_t)(void *, s32);
typedef struct V {
    s32 pad0[2];
    s16 unk8;
    s16 padA;
    vcall_t unkC;
} V_t;
typedef struct Lst Lst_t;
struct Lst {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    Lst_t *unkC;
    Lst_t *unk10;
    s32 unk14;
    V_t *unk18;
    char pad1C[0x44];
    f32 unk60;
    f32 unk64;
};
typedef struct O {
    char pad0[0x18];
    char pad18[0xC];
    Lst_t *unkC;
    Lst_t *unk10;
    char pad2C[0x4C];
    s32 unk78;
} O_t;
void fn_8002F298(O_t *arg0, f32 farg0) {
    volatile double _dummy;
    Lst_t *temp_r11;
    Lst_t *var_r29;
    s32 temp_r3;
    s32 var_r11;
    s32 var_r30;
    char *temp_r10;
    Lst_t *temp_r11_2;
    V_t *temp_r9;
    char *var_r0;
    Lst_t *var_r11_2;
    Lst_t *var_r30_2;
    char *var_r31;
    Lst_t *var_r31_2;
    char *var_r3;
    char *var_r8;
    char *var_r9;
    char *var_r9_2;
    Lst_t *var_r9_3;
    char *var_r9_4;
    register s32 var_r9_5 __asm__("r9");
    f32 var_f31;

    temp_r11 = (Lst_t *)((char *)arg0 + 0x18);
    var_r9 = (char *)temp_r11->unkC;
    if (*(s32 *)(var_r9 + 4) == -1) {
        var_r9 = NULL;
    }
    if (var_r9 != NULL) {
        var_r8 = var_r9 - 4;
    } else {
        var_r8 = NULL;
    }
    var_r29 = temp_r11;
    var_r30 = 0;
    if (var_r8 != NULL) {
        do {
            temp_r10 = var_r8 + 4;
            var_r30 += 1;
            temp_r11_2 = ((Lst_t *)temp_r10)->unkC;
            if (temp_r11_2->unk4 == -1) {
                var_r9_2 = NULL;
            } else {
                var_r9_2 = (char *)temp_r11_2;
            }
            if (var_r9_2 != NULL) {
                var_r31 = var_r9_2 - 4;
            } else {
                var_r31 = NULL;
            }
            if (var_r30 >= lbl_803003B8) {
                *(s32 *)((char *)((Lst_t *)temp_r10)->unk10 + 0xC) = (s32)temp_r11_2;
                *(s32 *)((char *)((Lst_t *)temp_r10)->unkC + 0x10) = (s32)((Lst_t *)temp_r10)->unk10;
                ((Lst_t *)temp_r10)->unkC = (Lst_t *)temp_r10;
                ((Lst_t *)temp_r10)->unk10 = (Lst_t *)temp_r10;
                if (var_r8 != NULL) {
                    temp_r9 = (V_t *)*(s32 *)(var_r8 + 0x18);
                    temp_r9->unkC(temp_r10 + temp_r9->unk8, 3);
                }
            }
            var_r8 = var_r31;
        } while (var_r8 != NULL);
    }
    var_r9_3 = var_r29->unkC;
    var_r11 = 0;
    goto loop_16_test;
loop_16_body:
    var_r9_3 = var_r9_3->unkC;
    var_r11 += 1;
loop_16_test:
    if (var_r9_3->unk4 == -1) {
        var_r9_3 = NULL;
    }
    if (var_r9_3 != NULL) {
        goto loop_16_body;
    }
    if (var_r11 != 0) {
        var_r9_4 = (char *)var_r29->unkC;
        if (*(s32 *)(var_r9_4 + 4) == -1) {
            var_r9_4 = NULL;
        }
        if (var_r9_4 != NULL) {
            var_r3 = var_r9_4 - 4;
        } else {
            var_r3 = NULL;
        }
        var_r30_2 = (Lst_t *)var_r3;
    } else {
        var_r30_2 = NULL;
    }
    if ((var_r30_2 != NULL) && (fn_80032934(var_r30_2, farg0) != 0)) {
        var_r9_5 = (s32)var_r30_2->unk10;
        var_f31 = lbl_80291988;
        if (*(s32 *)(var_r9_5 + 4) == -1) {
            var_r9_5 = 0;
        }
        if (var_r9_5 != 0) {
            var_r31_2 = (Lst_t *)(var_r9_5 - 4);
        } else {
            var_r31_2 = NULL;
        }
        if (var_r31_2 != NULL) {
            do {
                if (fn_80032AA0((s32)var_r31_2) != 0) {
                    var_f31 += var_r31_2->unk60 * var_r31_2->unk64;
                }
                var_r9_5 = (s32)var_r31_2->unk10;
                if (*(s32 *)(var_r9_5 + 4) == -1) {
                    var_r9_5 = 0;
                }
                if (var_r9_5 != 0) {
                    var_r0 = (char *)(var_r9_5 - 4);
                } else {
                    var_r0 = NULL;
                }
                var_r31_2 = (Lst_t *)var_r0;
            } while (var_r31_2 != NULL);
        }
        var_r30_2->unk64 = (lbl_8029198C - var_f31) / var_r30_2->unk60;
    }
    temp_r3 = (s32)fn_800322C0(fn_80033310(0x78, lbl_80291988), arg0->unk78);
    if (temp_r3 != 0) {
        var_r11_2 = (Lst_t *)((char *)temp_r3 + 4);
    } else {
        var_r11_2 = NULL;
    }
    var_r11_2->unk10 = var_r29;
    var_r11_2->unkC = var_r29->unkC;
    *(s32 *)((char *)var_r29->unkC + 0x10) = (s32)var_r11_2;
    var_r29->unkC = var_r11_2;
}
