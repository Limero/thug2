// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80008E50-0x80008EB0 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

extern char lbl_8028FE8C[];

typedef union {
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } v;
    __ps_t p[2];
} V4U;

void fn_80008E50(char *arg0) {
    register f32 y __asm__("fr11");
    register f32 y_copy __asm__("fr11");
    register f32 x __asm__("fr0");
    register f32 z __asm__("fr10");
    register f32 w __asm__("fr13");
    register f32 result __asm__("fr12");
    register f32 old __asm__("fr9");
    register s32 page __asm__("r9");
    f32 k;
    V4U v;
    __ps_t p0;
    __ps_t p1;

    y = *(f32 *)(arg0 + 0x84);
    __asm__ volatile("lis %0,%1@ha" : "=r"(page) : "s"(lbl_8028FE8C));
    x = *(f32 *)(arg0 + 0x80);
    __asm__("" : "+f"(x));
    z = *(f32 *)(arg0 + 0x88);
    __asm__("" : "+f"(z));
    __asm__ volatile("fneg %0,%1" : "=f"(y_copy) : "f"(y));
    w = *(f32 *)(arg0 + 0x8C);
    __asm__("" : "+f"(w));
    x = -x;
    old = *(f32 *)(arg0 + 0x90);
    z = -z;
    __asm__ __volatile__("" : : "f"(y_copy), "f"(w), "f"(old), "f"(z));
    *(volatile f32 *)&v.v.y = y_copy;
    w = -w;
    k = *(f32 *)(page - 0x174);
    *(volatile f32 *)&v.v.x = x;
    *(volatile f32 *)&v.v.z = z;
    result = k - old;
    *(volatile f32 *)&v.v.w = w;
    __asm__ __volatile__("" ::: "memory");
    p0 = v.p[0];
    *(f32 *)(arg0 + 0x90) = result;
    *(__ps_t *)(arg0 + 0x80) = p0;
    __asm__ __volatile__("" ::: "memory");
    p1 = v.p[1];
    *(__ps_t *)(arg0 + 0x88) = p1;
}
