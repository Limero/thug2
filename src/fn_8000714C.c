// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000714C-0x800071D4 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef struct {
    __ps_t p0;
    __ps_t p1;
    __ps_t p2;
    __ps_t p3;
    f32 scale;
} ShapeData;

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSValue;

extern __ps_t lbl_8028FD98;
extern char lbl_8028FE14[];
extern char lbl_8028FE18[];

f32 fn_8000714C(ShapeData *arg0) {
    __ps_t pair0;
    register __ps_t pair1 __asm__("fr11");
    register __ps_t zero __asm__("fr9");
    register __ps_t pair2 __asm__("fr13");
    register __ps_t dot __asm__("fr0");
    register __ps_t pair0_reload __asm__("fr12");
    register __ps_t d0 __asm__("fr13");
    register f32 scale __asm__("fr10");
    register f32 term0 __asm__("fr1");
    register f32 term1 __asm__("fr12");
    register char *four_thirds_pi_page __asm__("r11");
    register char *pi_page __asm__("r10");
    register f32 inverse_length __asm__("fr13");
    register f32 scalar0 __asm__("fr0");
    volatile __ps_t keep_d0;
    volatile __ps_t keep_d1;
    volatile PSValue saved_inverse;

    pair0 = arg0->p1;
    __asm__ volatile("" : "+f"(pair0));
    pair1 = arg0->p3;
    zero = lbl_8028FD98;
    __asm__ volatile("" : "+f"(zero));
    __asm__ volatile("lis %0,%1@ha" : "=r"(four_thirds_pi_page) :
                     "s"(lbl_8028FE18));
    pair1 = __builtin_ps_sub(pair1, pair0);
    pair2 = arg0->p2;
    __asm__ volatile("" : "+f"(pair2));
    pair0_reload = arg0->p0;
    __asm__ volatile("" : "+f"(pair0_reload));
    dot = __builtin_ps_mul(pair1, pair1);
    __asm__ volatile("" : "+f"(dot));
    scale = arg0->scale;
    __asm__ volatile("" : "+f"(scale));
    __asm__ volatile("lis %0,%1@ha" : "=r"(pi_page) : "s"(lbl_8028FE14));
    d0 = __builtin_ps_sub(pair2, pair0_reload);
    term0 = *(f32 *)(four_thirds_pi_page - 0x1E8);
    dot = __builtin_ps_merge00(dot, zero);
    term1 = *(f32 *)(pi_page - 0x1EC);
    dot = __builtin_ps_madd(d0, d0, dot);
    __asm__("" ::: "memory");
    keep_d0 = d0;
    __asm__("" ::: "memory");
    keep_d1 = pair1;
    __asm__("" ::: "memory");
    dot = __builtin_ps_sum0(dot, dot, dot);
    dot = __builtin_ps_rsqrte(dot);
    dot = __builtin_ps_res(dot);
    saved_inverse.ps = dot;
    term0 = scale * term0;
    __asm__ volatile("" : "+f"(term0));
    term1 = scale * term1;
    __asm__ volatile("" : "+f"(term1));
    inverse_length = saved_inverse.flt.hi;
    __asm__ volatile("" : "+f"(inverse_length));
    term0 = term0 * scale;
    __asm__ volatile("" : "+f"(term0));
    term0 = term0 * scale;
    __asm__ volatile("" : "+f"(term0));
    __asm__ volatile("fmr %0,%1" : "=f"(scalar0) : "f"(inverse_length));
    term1 = term1 * scale;
    return term1 * scalar0 + term0;
}
