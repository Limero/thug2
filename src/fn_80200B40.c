// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80200B40-0x80200C00 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef float sn_ps __attribute__((mode(PS)));

typedef union B40Vectors {
    sn_ps p[10];
    struct {
        f32 pad0[3];
        f32 f54;
        f32 pad1[3];
        f32 f64;
        f32 pad2[3];
        f32 f74;
        f32 pad3[3];
        f32 f84;
    } s;
} B40Vectors;

typedef struct B40Object {
    char pad0[0xC];
    sn_ps *dest;
    char pad1[0x38];
    B40Vectors v;
} B40Object;

extern f32 lbl_802AEB98;
extern f32 lbl_802AEB9C;

void fn_80200B40(B40Object *arg0) {
    f32 zero = lbl_802AEB9C;
    f32 one = lbl_802AEB98;
    register sn_ps p0 __asm__("fr0");
    register sn_ps *d1 __asm__("r10");
    sn_ps *d2;
    sn_ps *d3;

    *(volatile f32 *)&arg0->v.s.f64 = zero;
    *(volatile f32 *)&arg0->v.s.f84 = zero;
    *(volatile f32 *)&arg0->v.s.f74 = zero;
    p0 = arg0->v.p[0];
    __asm__ volatile("" : "+f"(p0));
    d1 = arg0->dest;
    *(volatile f32 *)&arg0->v.s.f54 = one;
    d1[11] = p0;
    d1[12] = arg0->v.p[1];
    d2 = arg0->dest;
    d2[15] = arg0->v.p[2];
    d2[16] = arg0->v.p[3];
    d2[17] = arg0->v.p[4];
    d2[18] = arg0->v.p[5];
    d2[19] = arg0->v.p[6];
    d2[20] = arg0->v.p[7];
    d2[21] = arg0->v.p[8];
    d2[22] = arg0->v.p[9];
    d3 = arg0->dest;
    d3[26] = arg0->v.p[2];
    d3[27] = arg0->v.p[3];
    d3[28] = arg0->v.p[4];
    d3[29] = arg0->v.p[5];
    d3[30] = arg0->v.p[6];
    d3[31] = arg0->v.p[7];
    d3[32] = arg0->v.p[8];
    d3[33] = arg0->v.p[9];
}
