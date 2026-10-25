// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800601CC-0x80060264 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct N {
    void *f0;
    struct N *f4;
} N;

typedef struct O_601CC {
    char pad0x0[0x10];
    N *f10;
} O_601CC;

typedef struct FR_601CC {
    volatile void *sp8;
    char pad0x4[4];
    volatile void *sp10;
    char pad0x14[4];
} FR_601CC;

s32 fn_80036960(void *);
s32 fn_80036968(void *);
void fn_8005F480(void *, s32, s32);

bool fn_800601CC(O_601CC *arg0, void *arg1) {
    FR_601CC fr;
    N *t;
    N *v;
    N *w;
    N *p;
    void *q;
    N *x;
    N *y;
    N *z;
    s32 c1;

    t = arg0->f10;
    fr.sp8 = t;
    v = t != NULL ? t->f4 : NULL;
    fr.sp10 = v;
    if (v != t) {
        do {
            w = (N *)fr.sp10;
            p = (N *)w->f0;
            q = (void *)p->f0;
            c1 = fn_80036960(arg1);
            fn_8005F480(q, c1, fn_80036968(arg1));
            x = (N *)fr.sp10;
            y = (N *)fr.sp8;
            z = x->f4;
            fr.sp10 = z;
        } while (z != y);
    }
    return true;
}
