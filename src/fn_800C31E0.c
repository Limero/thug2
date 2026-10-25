// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C31E0-0x800C333C (348B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef float PS __attribute__((mode(PS)));

void fn_800071D4(void *);
void fn_8000728C(void *, const void *);
void fn_80105CE8(void *, const void *);

void fn_800C31E0(void *arg0) {
    f32 lo[8];
    PS t[4];
    s32 i, off;
    s32 *p, *q;
    char *a, *b;
    s32 k;
    char *g;

    fn_800071D4(lo);
    i = *(s32 *)((char *)arg0 + 0x1AC);
    if (0 != i--) {
        off = (i * 0x10 - i) << 5;
        do {
            p = (s32 *)((char *)(*(s32 *)((char *)arg0 + 0x2F0)) + off);
            q = p + 0x20;
            off -= 0x1E0;
            fn_8000728C(lo, q);
            fn_8000728C(lo, (char *)p + 0x90);
        } while (0 != i--);
    }
    k = 1;
    g = (char *)arg0 + 0x338;
    a = (char *)arg0 + 0x280;
    b = (char *)arg0 + 0x250;
    do {
        fn_8000728C(lo, a);
        a -= 0x88;
        t[0] = *(PS *)(b + 0x30) + *(PS *)(b + 0x40);
        t[1] = *(PS *)(b + 0x38) + *(PS *)(b + 0x48);
        fn_8000728C(lo, t);
        t[0] = *(PS *)(b + 0x30) + *(PS *)(b + 0x50);
        t[1] = *(PS *)(b + 0x38) + *(PS *)(b + 0x58);
        fn_8000728C(lo, t);
        t[0] = *(PS *)(b + 0x30) + *(PS *)(b + 0x40) + *(PS *)(b + 0x50);
        t[1] = *(PS *)(b + 0x38) + *(PS *)(b + 0x48) + *(PS *)(b + 0x58);
        t[2] = *(PS *)(b + 0x30) + *(PS *)(b + 0x40);
        t[3] = *(PS *)(b + 0x38) + *(PS *)(b + 0x48);
        b -= 0x88;
        fn_8000728C(lo, t);
    } while (0 != k--);
    fn_80105CE8(g, lo);
}
