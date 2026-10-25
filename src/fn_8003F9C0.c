// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003F9C0-0x8003FA8C (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern const f32 lbl_80292304;
void fn_8004195C(void *, void *);
typedef struct Vec {
    char _00[0x18];
    f32 x;
    f32 y;
    char _20[0xC];
    f32 a;
    f32 b;
} Vec;
typedef struct SE {
    char _00[0xC];
    s32 f_0C;
    char _10[0x160];
    f32 f_170;
    f32 f_174;
    f32 f_178;
    f32 f_17C;
} SE;
void CScreenElement_SetJust(SE *arg0, f32 x, f32 y) {
    Vec *p;
    Vec *q;
    f32 dx, dy, sx, sy;
    if (arg0->f_170 != x || arg0->f_174 != y) {
        dx = x - arg0->f_170;
        dy = y - arg0->f_174;
        p = (Vec *)((char *)arg0 + 0x88);
        q = (Vec *)((char *)arg0 + 0xD0);
        sx = p->a * arg0->f_178 * dx * lbl_80292304;
        sy = p->b * arg0->f_17C * dy * lbl_80292304;
        p->x += sx;
        p->y += sy;
        q->x += sx;
        q->y += sy;
        arg0->f_170 = x;
        arg0->f_174 = y;
        arg0->f_0C |= 0x400;
        fn_8004195C((void *)arg0, (void *)q);
    }
}
