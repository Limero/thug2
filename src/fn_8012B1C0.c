// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012B1C0-0x8012B2A0 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef union {
    f32 f;
    s32 i;
} F32I;

typedef struct {
    u32 hi:9;
    u32 ty:7;
    u32 lo:16;
} FLAGS;

typedef union {
    FLAGS f;
    u32 w;
} HEAD;

typedef struct {
    HEAD h;
    s32 pad4;
    F32I v;
} OBJ;

typedef struct {
    char p0[2];
    u8 ty;
    char p3[9];
    F32I v;
} TMP;

void *fn_80125480(s32 a0);

void fn_8012B1C0(OBJ *o)
{
    TMP *t;
    u8 ty;

    if ((o->h.w & 0x7F0000u) != 0xD0000u) {
        return;
    }
    t = (TMP *)fn_80125480(o->v.i);
    if (t == NULL) {
        return;
    }
    ty = t->ty;
    switch ((s32)ty) {
    case 1: o->h.f.ty = ty; o->v.i = t->v.i; break;
    case 2: o->h.f.ty = ty; o->v.f = t->v.f; break;
    case 3: o->h.f.ty = ty; o->v.i = t->v.i; break;
    case 4: o->h.f.ty = ty; o->v.i = t->v.i; break;
    case 5: o->h.f.ty = ty; o->v.i = t->v.i; break;
    case 6: o->h.f.ty = ty; o->v.i = t->v.i; break;
    case 10: o->h.f.ty = ty; o->v.i = t->v.i; break;
    case 12: o->h.f.ty = ty; o->v.i = t->v.i; break;
    case 13: o->h.f.ty = ty; o->v.i = t->v.i; break;
    }
}
