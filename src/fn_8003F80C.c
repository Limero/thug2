// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003F80C-0x8003F93C (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct CScreenElement {
    char _00[0xC];
    s32 f_0C;        // flag word (0x400 = dirty, 0x80000 = set-by-script)
    char _10[0x80];
    V4 f_90;         // "previous"/reference vector
    char _A0[0x38];
    V4 f_D8;         // "current" vector
    char _E8[0x90];
    f32 f_178;
    f32 f_17C;
} CScreenElement;
extern void fn_8004195C(void *, void *);

// CScreenElement_SetVector — arg1 is the requested vector, arg2 selects
// whether the 0x90 reference slot is refreshed too.
void fn_8003F80C(CScreenElement *arg0, V4 *arg1, s32 arg2) {
    V4 *cur = &arg0->f_D8;
    s32 same;

    same = 0;
    if ((cur->x == arg1->x) && (cur->y == arg1->y) && (cur->z == arg1->z)) {
        same = (cur->w == arg1->w);
    }
    if (same == 0) {
        ((__ps_t *)&arg0->f_D8)[0] = ((__ps_t *)arg1)[0];
        ((__ps_t *)&arg0->f_D8)[1] = ((__ps_t *)arg1)[1];
        arg0->f_0C |= 0x400;
        fn_8004195C((void *)arg0, (void *)((char *)arg0 + 0xD0));
    }
    if (arg2 != 0) {
        V4 *ref = &arg0->f_90;
        same = 0;
        if ((ref->x == arg1->x) && (ref->y == arg1->y) && (ref->z == arg1->z)) {
            same = (ref->w == arg1->w);
        }
        if (same == 0) {
            ((__ps_t *)&arg0->f_90)[0] = ((__ps_t *)arg1)[0];
            ((__ps_t *)&arg0->f_90)[1] = ((__ps_t *)arg1)[1];
            arg0->f_0C |= 0x400;
        }
    }
    arg0->f_0C |= 0x80000;
}
