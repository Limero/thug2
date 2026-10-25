// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80056308-0x80056500 (504B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern char lbl_80293214[];
extern char lbl_80293218[];
extern char lbl_8029321C[];

typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x4];
    s32 unk0xC;
} Arg1_80056308;

typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} Sp8_80056308;

typedef struct {
    char pad0x0[0x8];
    u16 unk8;
} Cell_80056308;

typedef struct {
    char pad0x0[0x28];
    s16 unk28;
    void (*unk2C)(void *, void *);
} Vtbl_80056308;

void *Mem_Alloc(s32 size);
void fn_800FE130(void *);
s32 fn_80102A40(void *, void *, void *, s32, void *, void *, void *);
void fn_80103234(void *);
void fn_8000728C(void *, void *);

bool fn_80056308(void *arg0, Arg1_80056308 *arg1, s32 *arg2, void **arg3, void **arg4, void *arg5) {
    Sp8_80056308 sp8;
    volatile double _dummy;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f31;
    void *temp_r10;
    void *temp_r23;
    void *temp_r26;
    void *temp_r24;
    void *temp_r20;
    void *temp_r29;
    void *var_r30;
    s32 temp_r9;
    s32 temp_r30;
    s32 var_r31;
    s32 var_r21;
    s32 var_r29;
    s32 var_r30_2;
    s32 var_r31_2;
    Vtbl_80056308 *temp_r9_2;
    void *temp_r3;
    void *temp_r4;
    s32 u8v;

    temp_r10 = (char *)arg1 + 0x10;
    *arg2 = arg1->unk0x4;
    *arg4 = temp_r10;
    var_r21 = 0;
    temp_r9 = arg1->unk0xC;
    temp_r23 = temp_r10 + (*arg2 << 6);
    {
        s32 t3 = (s32) (temp_r9 * 3LL);
        temp_r26 = (char *) temp_r23 + t3;
        temp_r26 = (void *) (((s32) temp_r26 + 3) & QB_UNKNOWN_0xFFFFFFFC);
    }
    {
        char *var_r9 = (char *) temp_r26 + (temp_r9 * 0xA);
        if (temp_r9 & 1) {
            var_r9 = var_r9 + 2;
        }
        temp_r30 = arg1->unk0x4;
        temp_r24 = var_r9 + 4;
        var_r31 = temp_r30 - 1;
        temp_r20 = temp_r24 + *(s32 *)var_r9;
        temp_r29 = (char *)Mem_Alloc((temp_r30 << 4) | 8) + 8;
        *(s32 *)((char *)temp_r29 - 0x8) = temp_r30;
        var_r30 = temp_r29;
        if (temp_r30 != 0) {
            do {
                fn_800FE130(var_r30);
                var_r30 = (char *)var_r30 + 0x10;
            } while (0 != var_r31--);
        }
    }
    *arg3 = temp_r29;
    var_r30_2 = 0;
    if (var_r30_2 < arg1->unk0x4) {
        var_r29 = 0;
        var_r31_2 = 0;
        do {
            fn_80102A40((char *) *arg4 + var_r31_2, arg0, temp_r23, 0, temp_r26, temp_r24, temp_r20);
            fn_80103234((char *) *arg4 + var_r31_2);
            temp_r3 = (void *) (var_r29 + (s32) (char *) *arg3);
            temp_r9_2 = *(Vtbl_80056308 **) ((char *) temp_r3 + 0xC);
            temp_r9_2->unk2C(temp_r3 + temp_r9_2->unk28, (char *) *arg4 + var_r31_2);
            temp_r4 = (void *) (var_r31_2 + (s32) (char *) *arg4);
            u8v = ((Cell_80056308 *) temp_r4)->unk8;
            if (u8v > 0) {
                fn_8000728C(arg5, (void *) ((s32) temp_r4 + 0x10));
                var_r21 = 1;
                fn_8000728C(arg5, (void *) (var_r31_2 + (s32) (char *) *arg4 + 0x20));
            }
            var_r30_2 += 1;
            var_r29 += 0x10;
            var_r31_2 += 0x40;
        } while (var_r30_2 < arg1->unk0x4);
    }
    if (var_r21 == 0) {
        Sp8_80056308 *p8 = &sp8;
        temp_f0 = *(f32 *)lbl_80293214;
        temp_f31 = *(f32 *)lbl_80293218;
        *(f32 *) &sp8 = temp_f0;
        p8->f4 = temp_f0;
        p8->f8 = temp_f0;
        p8->fC = temp_f31;
        fn_8000728C(arg5, p8);
        temp_f0_2 = *(f32 *)lbl_8029321C;
        *(f32 *) &sp8 = temp_f0_2;
        p8->f4 = temp_f0_2;
        p8->f8 = temp_f0_2;
        p8->fC = temp_f31;
        fn_8000728C(arg5, p8);
    }
    return true;
}
