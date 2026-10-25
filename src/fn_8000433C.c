// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000433C-0x80004404 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef union {
    f32 f[4];
    __ps_t p[2];
} ProjectionRow;

typedef struct {
    __ps_t p[8];
} ProjectionMatrix;

extern char lbl_8028FC88[];
extern char lbl_8028FC8C[];
extern char lbl_8028FC90[];

void fn_8000433C(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    ProjectionRow sp8;
    register s32 base_r9 __asm__("r9");
    register s32 base_r11 __asm__("r11");
    register s32 dst_base __asm__("r10");
    register f32 temp_f13 __asm__("fr13");
    register f32 temp_f12 __asm__("fr12");
    register f32 temp_f0 __asm__("fr0");
    register f32 f11 __asm__("fr11");
    register f32 d_a __asm__("fr1");
    register f32 d_b __asm__("fr2");

    base_r9 = (s32)&lbl_8028FC8C - 4;
    __asm__ volatile("lis %0,%1@ha"
                     : "=r"(base_r11)
                     : "s"(lbl_8028FC88));
    temp_f13 = *(f32 *)base_r9;
    temp_f12 = farg3 - farg2;
    __asm__ volatile("lfs %0,%1@l(11)"
                     : "=f"(temp_f0)
                     : "s"(lbl_8028FC8C), "f"(temp_f12));
    base_r9 = (s32)&sp8;
    __asm__ volatile("" ::: "memory");
    d_a = temp_f13 / farg0;
    __asm__ volatile("mr %0,%1" : "=r"(dst_base) : "r"(arg0));
    base_r11 = (s32)&lbl_8028FC88 + 8;
    f11 = *(f32 *)base_r11;
    d_b = temp_f13 / farg1;

    *(f32 *)base_r9 = d_a;
    *(f32 *)(base_r9 + 8) = temp_f0;
    *(f32 *)(base_r9 + 0xC) = temp_f0;
    *(f32 *)(base_r9 + 4) = temp_f0;
    ((ProjectionMatrix *)dst_base)->p[0] = *(__ps_t *)base_r9;
    ((ProjectionMatrix *)dst_base)->p[1] = *(__ps_t *)(base_r9 + 8);

    *(f32 *)base_r9 = temp_f0;
    *(f32 *)(base_r9 + 8) = temp_f0;
    *(f32 *)(base_r9 + 0xC) = temp_f0;
    *(f32 *)(base_r9 + 4) = d_b;
    ((ProjectionMatrix *)dst_base)->p[2] = *(__ps_t *)base_r9;
    ((ProjectionMatrix *)dst_base)->p[3] = *(__ps_t *)(base_r9 + 8);

    *(f32 *)base_r9 = temp_f0;
    *(f32 *)(base_r9 + 0xC) = temp_f0;
    *(f32 *)(base_r9 + 8) = temp_f13 / temp_f12;
    *(f32 *)(base_r9 + 4) = temp_f0;
    ((ProjectionMatrix *)dst_base)->p[5] = *(__ps_t *)(base_r9 + 8);
    ((ProjectionMatrix *)dst_base)->p[4] = *(__ps_t *)base_r9;

    *(f32 *)base_r9 = temp_f0;
    *(f32 *)(base_r9 + 4) = temp_f0;
    *(f32 *)(base_r9 + 8) = -(farg3 + farg2) / temp_f12;
    *(f32 *)(base_r9 + 0xC) = f11;
    ((ProjectionMatrix *)dst_base)->p[6] = *(__ps_t *)base_r9;
    ((ProjectionMatrix *)dst_base)->p[7] = *(__ps_t *)(base_r9 + 8);
}
