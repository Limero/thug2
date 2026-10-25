// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034D24-0x80034E44 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Vec4_80034D24 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_80034D24;

typedef struct ElemHead80034D24 {
    s32 m00;
    s32 m04;
    f32 m08;
    s32 m0c;
    char pad10[4];
    Vec4_80034D24 v1;
    Vec4_80034D24 v2;
} ElemHead80034D24;

typedef struct ElemTail80034D24 {
    Vec4_80034D24 v3;
    char pad44[0x10];
    Vec4_80034D24 v4;
    s32 m64;
    s32 m68;
    s32 m6c;
    char pad70[8];
} ElemTail80034D24;

typedef struct Elem80034D24 {
    ElemHead80034D24 head;
    ElemTail80034D24 tail;
} Elem80034D24;

typedef struct Comp80034D24 {
    char pad00[4];
    s32 m04;
    s32 m08;
    s32 m0c;
    s32 m10;
    s32 m14;
    char pad18[4];
    Elem80034D24 e[4];
} Comp80034D24;

extern const f32 lbl_80291E1C;
extern const f32 lbl_80291E20;
extern char lbl_80291E58[];
s32 fn_800335E0(Comp80034D24 *);

void *fn_80034D24(Comp80034D24 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    Elem80034D24 *e;
    fn_80033538();
    arg0->m14 = (s32)lbl_80291E58;
    i = 4;
    e = arg0->e;
    do {
        Vec4_80034D24 *v = &e->tail.v4;
        v->x = lbl_80291E1C;
        v->y = lbl_80291E1C;
        v->z = lbl_80291E1C;
        v->w = lbl_80291E20;
        e++;
    } while (--i != 0);
    if (arg1 != 0) {
        arg0->m08 = fn_800335E0(arg0);
    } else {
        arg0->m08 = arg2;
    }
    i = 4;
    e = arg0->e;
    do {
        ElemTail80034D24 *t = &e->tail;
        ElemHead80034D24 *h = (ElemHead80034D24 *)((char *)t - 0x34);
        t->m64 = 0;
        t->m6c = 1;
        h->m00 = -1;
        h->v1.x = lbl_80291E1C;
        h->v1.y = lbl_80291E1C;
        h->v1.z = lbl_80291E1C;
        h->v1.w = lbl_80291E20;
        h->v2.x = lbl_80291E1C;
        h->v2.y = lbl_80291E1C;
        h->v2.z = lbl_80291E1C;
        h->v2.w = lbl_80291E20;
        t->v3.x = lbl_80291E1C;
        t->v3.y = lbl_80291E1C;
        t->v3.z = lbl_80291E1C;
        t->v3.w = lbl_80291E20;
        h->m08 = lbl_80291E20;
        t->m68 = 1;
        h->m04 = 0;
        h->m0c = 0;
        t->v4.z = lbl_80291E1C;
        t->v4.y = lbl_80291E1C;
        t->v4.x = lbl_80291E1C;
        t->v4.w = lbl_80291E20;
        e++;
    } while (--i != 0);
    return arg0;
}
