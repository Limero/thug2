// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060264-0x800602E4 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct T_60264 {
    char pad0x0[0x4];
    void *next;
} T_60264;

typedef struct O_60264 {
    char pad0x0[0x8];
    s32 c8;
    s32 b;
    void *a;
} O_60264;

typedef struct FR_60264 {
    volatile void *sp8;
    char pad0x4[4];
    volatile void *sp10;
    char pad0x14[4];
} FR_60264;

void fn_8005F4B4(void *, s32, s32);

void fn_80060264(O_60264 *arg0, s32 arg1) {
    FR_60264 fr;
    T_60264 *t;
    T_60264 *v;
    T_60264 *w;
    void *p;
    T_60264 *x;
    T_60264 *y;
    T_60264 *z;

    t = arg0->a;
    arg0->b = arg1;
    fr.sp8 = t;
    v = t != NULL ? t->next : NULL;
    fr.sp10 = v;
    if (v != t) {
        do {
            w = (T_60264 *)fr.sp10;
            p = *(void **)w;
            fn_8005F4B4(*(s32 *)p, arg0->b, arg0->c8);
            x = (T_60264 *)fr.sp10;
            y = (T_60264 *)fr.sp8;
            z = x->next;
            fr.sp10 = z;
        } while (z != y);
    }
}
