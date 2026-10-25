// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004523C-0x8004549C (608B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_800421D4(void *);
void fn_8005E628(void *, u32);
void fn_8005E700(void *, f32, f32);
void fn_8005E73C(void *, u16, u16);
void fn_8005E778(void *, f32, f32);
void fn_8005E898(void *, s32, s32);
void fn_8005E8D4(void *, f32, f32);
void fn_8005E910(void *, f32);
void fn_8005E948(void *, f32);
void fn_8005E988(void *, s32);
void fn_8005E9C8(void *, u32);
void fn_8005EA00(void *, s32 *);
extern f32 lbl_80292654;
extern f32 lbl_80292658;
extern f32 lbl_8029265C;

typedef union W27 {
    u32 w;
    u8 b[4];
} W27;

typedef struct A27 {
    char pad0x0[0x3C];
    f32 unk0x3C;
    W27 v40;
} A27;

typedef struct B27 {
    char pad0x0[0x18];
    f32 unk0x18;
    f32 unk0x1C;
    s32 unk0x20;
    char pad0x24[0x8];
    f32 unk0x2C;
    f32 unk0x30;
    char pad0x34[0x8];
    f32 unk0x3C;
} B27;

typedef struct O27 {
    char pad0x0[0xC];
    u32 unk0xC;
    char pad0x10[0xB4];
    f32 unk0xC4;
    s32 unk0xC8;
    char pad0xCC[0x5C];
    f32 unk0x128;
    char pad0x12C[0x1C];
    s32 unk0x148;
    char pad0x14C[0x4];
    f32 unk0x150;
    char pad0x154[0x1C];
    f32 unk0x170;
    f32 unk0x174;
    f32 unk0x178;
    f32 unk0x17C;
    char pad0x180[0x4];
    f32 unk0x184;
    char pad0x188[0xC];
    s32 unk0x194;
    void *unk0x198;
} O27;

void fn_8004523C(O27 *arg0) {
    volatile s32 outv;
    s32 tmp;
    s32 temp_r30;
    s32 temp_r29;
    f32 temp_f11;
    f32 temp_f13;
    f32 f18;
    register A27 *ta __asm__("r11");
    A27 *in;
    register B27 *tb __asm__("r9");
    B27 *b;

    temp_r30 = 0;
    temp_f13 = arg0->unk0x150;
    if ((temp_f13 < lbl_80292654) || (temp_f13 > lbl_80292658)) {
        temp_r30 = 1;
    }
    temp_r29 = fn_800421D4(arg0);
    fn_8005E628(arg0->unk0x198, (temp_r30 != 0) || (temp_r29 != 0));
    if (arg0->unk0xC & 0x1800) {
        ta = (A27 *)((char *)arg0 + 0x88);
        temp_f11 = arg0->unk0x128;
        tmp = ta->v40.w;
        in = ta;
        if (temp_f11 >= lbl_8029265C) {
            *((u8 *)&tmp + 3) = (s8)((f32)(f64)(u32)in->v40.b[3] * temp_f11);
        } else {
            *((u8 *)&tmp + 3) = 0;
        }
        tb = (B27 *)((char *)arg0 + 0x128);
        f18 = tb->unk0x18;
        b = tb;
        __asm__("" : "+r"(tb));
        fn_8005E700(arg0->unk0x198, f18, tb->unk0x1C);
        fn_8005E73C(arg0->unk0x198, (u16)arg0->unk0x178, (u16)arg0->unk0x17C);
        fn_8005E898(arg0->unk0x198, (arg0->unk0xC >> 25) & 1, (arg0->unk0xC >> 26) & 1);
        if (arg0->unk0xC & 0x1000000) {
            fn_8005E910(arg0->unk0x198, in->unk0x3C);
        } else {
            fn_8005E910(arg0->unk0x198, b->unk0x3C);
        }
        fn_8005E8D4(arg0->unk0x198, arg0->unk0x170, arg0->unk0x174);
        fn_8005E778(arg0->unk0x198, b->unk0x2C, b->unk0x30);
        if (arg0->unk0xC & 0x80000) {
            s32 var_r9 = 0;
            if (arg0->unk0xC & 0x800000) {
                var_r9 = 0x1388;
            }
            fn_8005E988(arg0->unk0x198, b->unk0x20 + var_r9);
            fn_8005E628(arg0->unk0x198, (arg0->unk0xC & 0x100000) || (temp_r29 != 0));
            fn_8005E9C8(arg0->unk0x198, arg0->unk0x194);
        } else {
            fn_8005E948(arg0->unk0x198, arg0->unk0x184);
            fn_8005E628(arg0->unk0x198, (temp_r30 != 0) || (temp_r29 != 0));
            fn_8005E9C8(arg0->unk0x198, arg0->unk0x194);
        }
        outv = tmp;
        fn_8005EA00(arg0->unk0x198, (s32 *)&outv);
    }
}
