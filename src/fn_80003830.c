// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80003830-0x80003984 (340B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef struct {
    f32 m00;
    f32 m01;
    f32 m02;
    f32 m03;
    f32 m10;
    f32 m11;
    f32 m12;
    f32 m13;
    f32 m20;
    f32 m21;
    f32 m22;
    f32 m23;
    f32 m30;
    f32 m31;
    f32 m32;
    f32 m33;
} Matrix44;

extern char lbl_8028FBF4[];
extern char lbl_8028FBF8[];
f32 sinf(f32);
f32 cosf(f32);

void *fn_80003830(Matrix44 *arg0, f32 farg0, f32 farg1, f32 farg2) {
    volatile double frame_pad0;
    volatile double frame_pad1;
    volatile double frame_pad2;
    s32 var_ctr;
    register s32 page_one __asm__("r11");
    register s32 page_zero __asm__("r9");
    void *result;
    register f32 c0 __asm__("fr31");
    register f32 s0 __asm__("fr28");
    register f32 c1 __asm__("fr27");
    register f32 s1 __asm__("fr30");
    register f32 c2 __asm__("fr29");
    register f32 s2 __asm__("fr1");
    register f32 c0s1 __asm__("fr8");
    register f32 s0s1 __asm__("fr10");
    register f32 s0c2 __asm__("fr5");
    register f32 c0s2 __asm__("fr7");
    register f32 c0c2 __asm__("fr6");
    register f32 m33 __asm__("fr12");
    register f32 zero __asm__("fr0");
    register f32 m21 __asm__("fr11");
    register f32 m10 __asm__("fr13");
    register f32 m01 __asm__("fr9");
    f32 s0s2;

    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);

    c0 = cosf(farg0);
    s0 = sinf(farg0);
    c1 = cosf(farg1);
    s1 = sinf(farg1);
    c2 = cosf(farg2);
    s2 = sinf(farg2);

    __asm__ volatile("lis %0,%1@ha" : "=r"(page_one) : "s"(lbl_8028FBF8));
    c0s1 = c0 * s1;
    __asm__ volatile("" : "+f"(c0s1));
    m33 = *(f32 *)(page_one - 0x408);
    __asm__ volatile("" : "+f"(m33));
    s0s1 = s0 * s1;
    __asm__ volatile("" : "+f"(s0s1));
    s0c2 = s0 * c2;
    __asm__ volatile("" : "+f"(s0c2));
    __asm__ volatile("lis %0,%1@ha" : "=r"(page_zero) : "s"(lbl_8028FBF4));
    arg0->m33 = m33;
    c0s2 = c0 * s2;
    __asm__ volatile("" : "+f"(c0s2));
    c0c2 = c0 * c2;
    __asm__ volatile("" : "+f"(c0c2));
    zero = *(f32 *)(page_zero - 0x40c);
    __asm__ volatile("" : "+f"(zero));
    m33 = -s0;
    __asm__ volatile("mr %0,%1" : "=r"(result) : "r"(arg0));
    m21 = -c0s1;
    arg0->m03 = zero;
    __asm__ volatile("" ::: "memory");
    m01 = -c1;
    arg0->m32 = zero;
    __asm__ volatile("" ::: "memory");
    m10 = -s0s1;
    arg0->m31 = zero;
    __asm__ volatile("" ::: "memory");
    c0 = c0 * c1;
    arg0->m30 = zero;
    __asm__ volatile("" ::: "memory");
    m33 = m33 * c1;
    arg0->m23 = zero;
    __asm__ volatile("" ::: "memory");
    s0 = s0 * s2;
    arg0->m13 = zero;
    __asm__ volatile("" ::: "memory");
    m21 = m21 * s2 + s0c2;
    arg0->m22 = c0;
    m10 = m10 * c2 + c0s2;
    arg0->m21 = m21;
    s0s1 = s0s1 * s2 + c0c2;
    arg0->m10 = m10;
    m01 = m01 * s2;
    arg0->m11 = s0s1;
    s0s2 = -s1;
    arg0->m01 = m01;
    c0s1 = c0s1 * c2 + s0;
    arg0->m02 = s0s2;
    c1 = c1 * c2;
    arg0->m12 = m33;
    arg0->m20 = c0s1;
    __asm__ volatile("" ::: "memory");
    arg0->m00 = c1;

    return result;
}
