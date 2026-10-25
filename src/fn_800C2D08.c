// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C2D08-0x800C319C (1172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct {
    f32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    f32 sp1C;
    f32 sp20;
    f32 sp24;
    f32 sp28;
    f32 sp2C;
    f32 sp30;
    f32 sp34;
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    volatile f32 sp48;
    volatile f32 sp4C;
    volatile f32 sp50;
    volatile f32 sp54;
    volatile f32 sp58;
    volatile f32 sp5C;
    volatile f32 sp60;
    volatile f32 sp64;
    volatile f32 sp68;
    volatile f32 sp6C;
    volatile f32 sp70;
    volatile f32 sp74;
    volatile f32 sp78;
    volatile f32 sp7C;
    volatile f32 sp80;
    volatile f32 sp84;
    void *sp88;
} Frame_t;

#define sp8 fr.sp8
#define spC fr.spC
#define sp10 fr.sp10
#define sp14 fr.sp14
#define sp18 fr.sp18
#define sp1C fr.sp1C
#define sp20 fr.sp20
#define sp24 fr.sp24
#define sp28 fr.sp28
#define sp2C fr.sp2C
#define sp30 fr.sp30
#define sp34 fr.sp34
#define sp38 fr.sp38
#define sp3C fr.sp3C
#define sp40 fr.sp40
#define sp44 fr.sp44
#define sp48 fr.sp48
#define sp4C fr.sp4C
#define sp50 fr.sp50
#define sp54 fr.sp54
#define sp58 fr.sp58
#define sp5C fr.sp5C
#define sp60 fr.sp60
#define sp64 fr.sp64
#define sp68 fr.sp68
#define sp6C fr.sp6C
#define sp70 fr.sp70
#define sp74 fr.sp74
#define sp78 fr.sp78
#define sp7C fr.sp7C
#define sp80 fr.sp80
#define sp84 fr.sp84
#define sp88 fr.sp88

void fn_800C2D08(Unk_C7387A53 *arg0) {
    Frame_t fr;
    register f32 sx __asm__("fr4");
    register f32 sy __asm__("fr5");
    register f32 sz __asm__("fr8");
    f32 temp_f7;
    f32 temp_f8_2;
    f32 temp_f9;
    f32 temp_f10;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 p2load;
    f32 temp_f10_2;
    f32 temp_f9_2;
    f32 temp_f8_3;
    f32 temp_f7_3;
    register f32 p0 __asm__("fr10");
    register f32 p1 __asm__("fr7");
    register f32 p2 __asm__("fr6");
    register f32 p3 __asm__("fr9");
    register f32 p4 __asm__("fr13");
    register f32 p5 __asm__("fr0");
    register f32 p6 __asm__("fr4");
    register f32 p7 __asm__("fr5");
    register f32 p8 __asm__("fr8");
    register f32 q6 __asm__("fr3");
    register f32 q7 __asm__("fr12");
    register f32 q8 __asm__("fr11");
    f32 v0;
    f32 v1;
    register f32 v2 __asm__("fr1");
    register f32 v3 __asm__("fr13");
    f32 v4;
    register f32 v5 __asm__("fr12");
    f32 v6;
    f32 v7;
    f32 v8;
    f32 v9;
    f32 v10;
    f32 v11;
    f32 v12;
    f32 v13;
    f32 v14;
    f32 v15;
    s32 var_ctr;
    register s32 base8 __asm__("r11");
    register s32 base88 __asm__("r9");

    sx = *(f32 *)((char *)arg0 + 0x178);
    __asm__ volatile("li 0, 4" ::: "r0", "ctr");
    sy = *(f32 *)((char *)arg0 + 0x17C);
    __asm__ volatile("mtctr 0" ::: "r0", "ctr");
    sz = *(f32 *)((char *)arg0 + 0x180);
    base8 = (s32)&sp8;
    __asm__ volatile("" : "+r"(base8) : "f"(sz));
    p0 = *(f32 *)((char *)arg0 + 0x70);
    base88 = (s32)&sp88;
    p1 = *(f32 *)((char *)arg0 + 0x74);
    p2load = *(f32 *)((char *)arg0 + 0x78);
    p0 = sx * p0;
    p1 = sy * p1;
    p2 = sz * p2load;
    p3 = *(f32 *)((char *)arg0 + 0x80);
    p4 = *(f32 *)((char *)arg0 + 0x84);
    p5 = *(f32 *)((char *)arg0 + 0x88);
    p3 = sx * p3;
    p4 = sy * p4;
    p5 = sz * p5;
    q6 = *(f32 *)((char *)arg0 + 0x90);
    q7 = *(f32 *)((char *)arg0 + 0x94);
    q8 = *(f32 *)((char *)arg0 + 0x98);
    p6 = sx * q6;
    p7 = sy * q7;
    p8 = sz * q8;
    *(f32 *)((char *)arg0 + 0xD0) = p0;
    *(f32 *)((char *)arg0 + 0xD4) = p1;
    *(f32 *)((char *)arg0 + 0xD8) = p2;
    *(f32 *)((char *)arg0 + 0xE0) = p3;
    *(f32 *)((char *)arg0 + 0xE4) = p4;
    *(f32 *)((char *)arg0 + 0xE8) = p5;
    *(f32 *)((char *)arg0 + 0xF0) = p6;
    *(f32 *)((char *)arg0 + 0xF4) = p7;
    *(f32 *)((char *)arg0 + 0xF8) = p8;
    __asm__ volatile("bdnz ." ::: "memory");

    if ((void *)((char *)arg0 + 0x70) == (void *)base8) {
        temp_f13_2 = (temp_f13 = spC, sp18);
        sp18 = temp_f13;
        spC = temp_f13_2;
        __asm__ volatile("" ::: "memory");
        temp_f13_2 = *(f32 *)((char *)base8 + 0x8);
        *(f32 *)((char *)base8 + 0x8) = sp28;
        sp28 = temp_f13_2;
        temp_f10 = sp14;
        temp_f10_2 = sp38;
        sp14 = temp_f10_2;
        sp38 = temp_f10;
        temp_f9 = sp20;
        temp_f9_2 = sp2C;
        sp20 = temp_f9_2;
        sp2C = temp_f9;
        temp_f8_2 = sp24;
        temp_f8_3 = sp3C;
        sp24 = temp_f8_3;
        sp3C = temp_f8_2;
        temp_f7 = sp34;
        temp_f7_3 = sp40;
        sp34 = temp_f7_3;
        sp40 = temp_f7;
    } else {
        v0 = *(f32 *)((char *)arg0 + 0x70);
        v1 = *(f32 *)((char *)arg0 + 0x80);
        v2 = *(f32 *)((char *)arg0 + 0x90);
        __asm__ volatile("" : "+f"(v2));
        sp8 = v0;
        spC = v1;
        __asm__ volatile("" ::: "memory");
        v3 = *(f32 *)((char *)arg0 + 0x74);
        v4 = *(f32 *)((char *)arg0 + 0xA0);
        v5 = *(f32 *)((char *)arg0 + 0x84);
        v6 = *(f32 *)((char *)arg0 + 0x94);
        v7 = *(f32 *)((char *)arg0 + 0xA4);
        v8 = *(f32 *)((char *)arg0 + 0x78);
        v9 = *(f32 *)((char *)arg0 + 0x88);
        v10 = *(f32 *)((char *)arg0 + 0x98);
        v11 = *(f32 *)((char *)arg0 + 0xA8);
        v12 = *(f32 *)((char *)arg0 + 0x7C);
        v13 = *(f32 *)((char *)arg0 + 0x8C);
        v14 = *(f32 *)((char *)arg0 + 0x9C);
        v15 = *(f32 *)((char *)arg0 + 0xAC);
        *(f32 *)((char *)base8 + 0x8) = v2;
        sp14 = v4;
        sp18 = v3;
        sp1C = v5;
        sp20 = v6;
        sp24 = v7;
        sp28 = v8;
        sp2C = v9;
        sp30 = v10;
        sp34 = v11;
        sp38 = v12;
        sp3C = v13;
        sp40 = v14;
        sp44 = v15;
    }

    sp88 = (char *)arg0 + 0xD0;
    *(s32 *)((char *)base88 + 0x4) = (s32)base8;

    sp48 = (*(f32 *)((char *)sp88 + 0xC) * sp38) + ((*(f32 *)((char *)sp88 + 0x8) * sp28) + ((*(f32 *)((char *)sp88 + 0x0) * sp8) + (*(f32 *)((char *)sp88 + 0x4) * sp18)));
    sp4C = (*(f32 *)((char *)sp88 + 0xC) * sp3C) + ((*(f32 *)((char *)sp88 + 0x8) * sp2C) + ((*(f32 *)((char *)sp88 + 0x0) * spC) + (*(f32 *)((char *)sp88 + 0x4) * sp1C)));
    sp50 = (*(f32 *)((char *)sp88 + 0xC) * sp40) + ((*(f32 *)((char *)sp88 + 0x8) * sp30) + ((*(f32 *)((char *)sp88 + 0x0) * *(f32 *)((char *)base8 + 0x8)) + (*(f32 *)((char *)sp88 + 0x4) * sp20)));
    sp54 = (*(f32 *)((char *)sp88 + 0xC) * sp44) + ((*(f32 *)((char *)sp88 + 0x8) * sp34) + ((*(f32 *)((char *)sp88 + 0x0) * sp14) + (*(f32 *)((char *)sp88 + 0x4) * sp24)));
    sp58 = (*(f32 *)((char *)sp88 + 0x1C) * sp38) + ((*(f32 *)((char *)sp88 + 0x18) * sp28) + ((*(f32 *)((char *)sp88 + 0x10) * sp8) + (*(f32 *)((char *)sp88 + 0x14) * sp18)));
    sp5C = (*(f32 *)((char *)sp88 + 0x1C) * sp3C) + ((*(f32 *)((char *)sp88 + 0x18) * sp2C) + ((*(f32 *)((char *)sp88 + 0x10) * spC) + (*(f32 *)((char *)sp88 + 0x14) * sp1C)));
    sp60 = (*(f32 *)((char *)sp88 + 0x1C) * sp40) + ((*(f32 *)((char *)sp88 + 0x18) * sp30) + ((*(f32 *)((char *)sp88 + 0x10) * *(f32 *)((char *)base8 + 0x8)) + (*(f32 *)((char *)sp88 + 0x14) * sp20)));
    sp64 = (*(f32 *)((char *)sp88 + 0x1C) * sp44) + ((*(f32 *)((char *)sp88 + 0x18) * sp34) + ((*(f32 *)((char *)sp88 + 0x10) * sp14) + (*(f32 *)((char *)sp88 + 0x14) * sp24)));
    sp68 = (*(f32 *)((char *)sp88 + 0x2C) * sp38) + ((*(f32 *)((char *)sp88 + 0x28) * sp28) + ((*(f32 *)((char *)sp88 + 0x20) * sp8) + (*(f32 *)((char *)sp88 + 0x24) * sp18)));
    sp6C = (*(f32 *)((char *)sp88 + 0x2C) * sp3C) + ((*(f32 *)((char *)sp88 + 0x28) * sp2C) + ((*(f32 *)((char *)sp88 + 0x20) * spC) + (*(f32 *)((char *)sp88 + 0x24) * sp1C)));
    sp70 = (*(f32 *)((char *)sp88 + 0x2C) * sp40) + ((*(f32 *)((char *)sp88 + 0x28) * sp30) + ((*(f32 *)((char *)sp88 + 0x20) * *(f32 *)((char *)base8 + 0x8)) + (*(f32 *)((char *)sp88 + 0x24) * sp20)));
    sp74 = (*(f32 *)((char *)sp88 + 0x2C) * sp44) + ((*(f32 *)((char *)sp88 + 0x28) * sp34) + ((*(f32 *)((char *)sp88 + 0x20) * sp14) + (*(f32 *)((char *)sp88 + 0x24) * sp24)));
    sp78 = (*(f32 *)((char *)sp88 + 0x3C) * sp38) + ((*(f32 *)((char *)sp88 + 0x38) * sp28) + ((*(f32 *)((char *)sp88 + 0x30) * sp8) + (*(f32 *)((char *)sp88 + 0x34) * sp18)));
    sp7C = (*(f32 *)((char *)sp88 + 0x3C) * sp3C) + ((*(f32 *)((char *)sp88 + 0x38) * sp2C) + ((*(f32 *)((char *)sp88 + 0x30) * spC) + (*(f32 *)((char *)sp88 + 0x34) * sp1C)));
    sp80 = (*(f32 *)((char *)sp88 + 0x3C) * sp40) + ((*(f32 *)((char *)sp88 + 0x38) * sp30) + ((*(f32 *)((char *)sp88 + 0x30) * *(f32 *)((char *)base8 + 0x8)) + (*(f32 *)((char *)sp88 + 0x34) * sp20)));
    sp84 = (*(f32 *)((char *)sp88 + 0x3C) * sp44) + ((*(f32 *)((char *)sp88 + 0x38) * sp34) + ((*(f32 *)((char *)sp88 + 0x30) * sp14) + (*(f32 *)((char *)sp88 + 0x34) * sp24)));

    *(volatile __ps_t *)((char *)arg0 + 0xD0) = *(volatile __ps_t *)&sp48;
    *(volatile __ps_t *)((char *)arg0 + 0xD8) = *(volatile __ps_t *)&sp50;
    *(volatile __ps_t *)((char *)arg0 + 0xE0) = *(volatile __ps_t *)&sp58;
    *(volatile __ps_t *)((char *)arg0 + 0xE8) = *(volatile __ps_t *)&sp60;
    *(volatile __ps_t *)((char *)arg0 + 0xF0) = *(volatile __ps_t *)&sp68;
    *(volatile __ps_t *)((char *)arg0 + 0x108) = *(volatile __ps_t *)&sp80;
    *(volatile __ps_t *)((char *)arg0 + 0xF8) = *(volatile __ps_t *)&sp70;
    *(volatile __ps_t *)((char *)arg0 + 0x100) = *(volatile __ps_t *)&sp78;
}
