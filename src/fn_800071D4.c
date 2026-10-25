// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800071D4-0x8000723C (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

extern f32 lbl_8028FE1C;
extern f32 lbl_8028FE20;
extern f32 lbl_8028FE24;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;
typedef union {
    V4 v;
    __ps_t p[2];
} V4U;

void fn_800071D4(char *arg0) {
    register s32 dstbase __asm__("r11");
    V4U t;
    f32 one;

    one = lbl_8028FE20;
    dstbase = (s32)arg0;

    t.v.x = lbl_8028FE1C;
    t.v.y = lbl_8028FE1C;
    t.v.z = lbl_8028FE1C;
    t.v.w = one;
    *(__ps_t *)((char *)dstbase + 0x00) = t.p[0];
    *(__ps_t *)((char *)dstbase + 0x08) = t.p[1];

    t.v.x = lbl_8028FE24;
    t.v.y = lbl_8028FE24;
    t.v.z = lbl_8028FE24;
    t.v.w = one;
    *(__ps_t *)((char *)dstbase + 0x18) = t.p[1];
    *(__ps_t *)((char *)dstbase + 0x10) = t.p[0];
}
