// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060D5C-0x80060DE4 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct T_60D5C {
    char pad0x0[0x4];
    void *next;         /* +0x4, list link */
} T_60D5C;

typedef struct O_60D5C {
    char pad0x0[0x10];
    void *a;            /* +0x10, list head seeded into the walk */
    char pad0x14[0x1C];
    void *c;            /* +0x30, cleared then handed to fn_8005953C */
} O_60D5C;

typedef struct FR_60D5C {
    volatile void *sp8; /* 8(r1), the walk's stop node */
    char pad0x4[4];
    volatile void *sp10;/* 0x10(r1), the current node */
    char pad0x14[4];
} FR_60D5C;

void fn_8005953C(void *);
void fn_8005F418(void *, s32);

// fn_80060D5C: hand arg0+0x30 to fn_8005953C, clear it, then walk the list at
// arg0+0x10 calling fn_8005F418 on every entry's payload until the walk comes
// back around to the starting node. Always returns 1.
bool fn_80060D5C(O_60D5C *arg0) {
    FR_60D5C fr;
    T_60D5C *t;
    T_60D5C *v;
    T_60D5C *w;
    void *p;
    T_60D5C *x;
    T_60D5C *y;
    T_60D5C *z;

    fn_8005953C(arg0->c);
    t = arg0->a;
    arg0->c = NULL;
    fr.sp8 = t;
    v = t != NULL ? t->next : NULL;
    fr.sp10 = v;
    if (v != t) {
        do {
            w = (T_60D5C *)fr.sp10;
            p = *(void **)w;
            fn_8005F418(*(s32 *)p, 0);
            x = (T_60D5C *)fr.sp10;
            y = (T_60D5C *)fr.sp8;
            z = x->next;
            fr.sp10 = z;
        } while (z != y);
    }
    return true;
}
