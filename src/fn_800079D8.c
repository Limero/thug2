// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800079D8-0x80007A4C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
typedef struct {
    f32 min_x;
    f32 min_y;
    f32 min_z;
    f32 max_x;
    f32 max_y;
    f32 max_z;
} Bounds6;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;
extern char lbl_8028FE38[];
extern char lbl_8028FE3C[];
void fn_800079D8(s32 arg0, Bounds6 *arg1) {
    volatile Vec4 out;
    volatile f32 *bounds = (volatile f32 *)arg1;
    register s32 ratio_page __asm__("r10");
    register s32 w_page __asm__("r8");
    register s32 outbase __asm__("r9");
    register s32 dstbase __asm__("r11");
    register f32 minx __asm__("fr10");
    register f32 ratio __asm__("fr11");
    register f32 maxx __asm__("fr12");
    register f32 minz __asm__("fr8");
    register f32 maxz __asm__("fr0");
    register f32 miny __asm__("fr9");
    register f32 maxy __asm__("fr13");
    f32 dx;
    f32 fx;
    f32 dz;
    f32 w;
    f32 fz;
    f32 fy;

    minx = bounds[0];
    __asm__ volatile("lis %0,%1@ha" : "=r"(ratio_page) : "s"(lbl_8028FE38));
    maxx = bounds[4];
    __asm__ volatile("lis %0,%1@ha" : "=r"(w_page) : "s"(lbl_8028FE3C));
    ratio = *(volatile f32 *)((char *)ratio_page - 0x1C8);
    outbase = (s32)&out.x;
    dx = maxx - minx;
    __asm__ volatile("" : "+f"(dx));
    minz = bounds[2];
    maxz = bounds[6];
    __asm__ volatile("" : "+f"(maxz));
    fx = dx * ratio + minx;
    miny = bounds[1];
    __asm__ volatile("mr %0,%1" : "=r"(dstbase) : "r"(arg0));
    maxy = bounds[5];
    dz = maxz - minz;
    __asm__ volatile("" : "+f"(dz));
    w = *(volatile f32 *)((char *)w_page - 0x1C4);
    fz = dz * ratio + minz;
    __asm__ volatile("" : "+f"(fz));
    fy = (maxy - miny) * ratio + miny;

    out.x = fx;
    *(f32 *)((char *)outbase + 12) = w;
    *(f32 *)((char *)outbase + 8) = fz;
    *(f32 *)((char *)outbase + 4) = fy;
    *(__ps_t *)((char *)dstbase + 8) = *(__ps_t *)((char *)outbase + 8);
    *(__ps_t *)dstbase = *(__ps_t *)outbase;
}
