// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060CD8-0x80060D5C (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct T_60CD8 {
    char pad0x0[0x4];
    void *next;
} T_60CD8;

typedef struct O_60CD8 {
    char pad0x0[0x10];
    void *a;
    char pad0x14[0x1C];
    void *c;
} O_60CD8;

typedef struct FR_60CD8 {
    volatile void *sp8;
    char pad0x4[4];
    volatile void *sp10;
    char pad0x14[4];
} FR_60CD8;

void *fn_8005951C(void);
void fn_8005F418(void *, s32);

bool fn_80060CD8(O_60CD8 *arg0) {
    FR_60CD8 fr;
    T_60CD8 *t;
    T_60CD8 *v;
    T_60CD8 *w;
    void *p;
    T_60CD8 *x;
    T_60CD8 *y;
    T_60CD8 *z;

    arg0->c = fn_8005951C();
    t = arg0->a;

    fr.sp8 = t;
    v = t != NULL ? t->next : NULL;
    fr.sp10 = v;
    if (v != t) {
        do {
            w = (T_60CD8 *)fr.sp10;
            p = *(void **)w;
            fn_8005F418(*(s32 *)p, (s32)arg0->c);
            x = (T_60CD8 *)fr.sp10;
            y = (T_60CD8 *)fr.sp8;
            z = x->next;
            fr.sp10 = z;
        } while (z != y);
    }
    return true;
}
